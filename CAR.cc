/*
 * RBVTPPacket.cpp
 *
 *  Created on: Jul 6, 2015
 *      Author: chengli
 */

#include <CAR/CAR.h>
#define CAR_EV EV << "CAR at " << getHostName() << " "
#define LOG_EV inFile <<"#"<<EventNumber()<<"  "<<simTime()<< " " << getHostName() << " "
#include "TraCIMobility.h"
#include "Radio80211aControlInfo_m.h"
Define_Module(CAR);

CAR::CAR(){
    interfaceTable=NULL;
}

CAR::~CAR(){

}
void CAR::initialize( int stage){
    RouteInterface::initialize(stage);

    if (stage == 0)
    {
        std::string myroad=getRoadID();
        EV_LOG(getHostName()+"road "+myroad);
        IPSocket socket(gate("ipOut"));
        socket.registerProtocol(IP_PROT_MANET);
        checkTime = 0;
        arrivalTime=0;
        seqNumOfPGB=0;
        neardistence=60;
        beaconInterval = par("beaconInterval");
        communicationRange = par("communicationRange");
        neighborValidityInterval = par("neighborValidityInterval");         // maybe will not be used
        maxJitter = par("maxJitter");
       // nextRUtimer= par("nextRUtimer");
      //  RUliftime= par("RUliftime");
        routingTable = check_and_cast<IRoutingTable *>(getModuleByPath(par("routingTableModule")));
        alpha = par("alpha");
        RouteInterface::protocalname="CAR";
        //reBoardcastRDTimer = new cMessage("ReBoardcastRDTimer");;
    }else{
    if (stage == 4)
        {
        RouteInterface::configureInterfaces(par("interfaces"));
        EV_LOG(getHostName());
      //  std::list<std::string> interjections=tracimanager->commandGetJunctionIds();
       /* for(std::list<std::string>::iterator iter=interjections.begin();iter!=interjections.end();++iter)
        {
            RBVTP_EV<<*iter<<"   "<<tracimanager->commandGetJunctionPosition(*iter)<<endl;
        }*/
        globalPositionTable.setHostName(getSelfIPAddress(),getHostName());
        beaconTimer = new cMessage("BeaconTimer");
        purgeNeighborsTimer = new cMessage("PurgeNeighborsTimer");
        scheduleBeaconTimer();
        schedulePurgeNeighborsTimer();
        }
    }
 }



void CAR::processSelfMessage(cMessage * message)
{
       // case RTSTimeOutTimer:
        //    processRTStTimer(nextCPtimer);
        //    break;
    EV_LOG( "processSelfMessage" );
    CAR_EV<<"processSelfMessage  "<<message->getName()<<endl;

    if (message == beaconTimer)
         processBeaconTimer();
     else if (message == purgeNeighborsTimer)
         processPurgeNeighborsTimer();
     else
         throw cRuntimeError("Unknown self message");

}


INetfilter::IHook::Result CAR::datagramPreRoutingHook(IPv4Datagram * datagram, const InterfaceEntry * inputInterfaceEntry, const InterfaceEntry *& outputInterfaceEntry, IPv4Address & nextHop){
     EV_LOG("datagramPreRoutingHook");
     Enter_Method("datagramPreRoutingHook");
      return ACCEPT;
}
INetfilter::IHook::Result CAR::datagramPostRoutingHook(IPv4Datagram * datagram, const InterfaceEntry * inputInterfaceEntry, const InterfaceEntry *& outputInterfaceEntry, IPv4Address & nextHop)
{
    EV_LOG("datagramPostRoutingHook");
     const IPv4Address & destination = datagram->getDestAddress();

      if (destination.isMulticast() || destination.isLimitedBroadcastAddress()|| routingTable->isLocalAddress(destination))
                  return ACCEPT;
       else{
           carPacket * datapacket= (dynamic_cast<carPacket *>((dynamic_cast<cPacket *>(datagram))->getEncapsulatedPacket()));
          // carPacket * datapacket=dynamic_cast<carPacket *>( (dynamic_cast<UDPPacket *>((dynamic_cast<cPacket *>(datagram))->getEncapsulatedPacket()))->getEncapsulatedPacket());
           if (datapacket)
              {
                  EV_LOG("get a carPacket"+std::string(datagram->getName()));
                  IPv4Address bestNextHopAddress=IPv4Address::LOOPBACK_ADDRESS;
                  anchor aimanchor =datapacket->getASetOfAnchorPoints()[datapacket->anchorIndex];
                  Coord nextReverseAnchorPosition = aimanchor.getCurrentNodePosition();
                  EV_LOG("aim anchor is form "+aimanchor.getPreviousForwarderHostName()+"  "+aimanchor.getCurrentHostName());
                  double bestDistance = 10000;//( getSelfPosition()-nextReverseAnchorPosition).length();
                  double myDistance = ( getSelfPosition()-nextReverseAnchorPosition).length();
                //  double angle1 = adjustVectorAngle(aimanchor.getCurrentForwarderAngel())/ (2 * PI) * 360;
                //  double angle2 = adjustVectorAngle(getAngel()) / (2 * PI) * 360;
                  double delta;// = angle1 - angle2;
                 if( myDistance<neardistence&&isParallel(aimanchor.getCurrentForwarderAngel(),getAngel(),alpha,delta))
                     {
                         EV_LOG(" neighbors: "+globalPositionTable.getHostName(getSelfIPAddress())+" near "+std::to_string(myDistance)+" and in same line "+std::to_string(delta));
                         datapacket->anchorIndex=datapacket->anchorIndex+1;
                         aimanchor=datapacket->getASetOfAnchorPoints()[datapacket->anchorIndex];
                         nextReverseAnchorPosition = aimanchor.getCurrentNodePosition();
                         EV_LOG ( "new aim anchor from "+ aimanchor.getPreviousForwarderHostName()+"  to  "+aimanchor.getCurrentHostName());
                     }
                else
                    {
                        EV_LOG(" neighbors: "+globalPositionTable.getHostName(bestNextHopAddress)+" to far "+std::to_string(myDistance)+" not in same line "+std::to_string(delta));
                    }
              std::vector<IPvXAddress> neighborAddresses = neighborPositionTable.getAddresses();
              for (std::vector<IPvXAddress>::iterator it = neighborAddresses.begin(); it !=neighborAddresses.end(); it++)
                 {
                     const IPvXAddress & neighborAddress = * it;
                     EV_LOG("I have neighbors: "+globalPositionTable.getHostName(neighborAddress));
                     Coord neighborPosition = neighborPositionTable.getPosition(neighborAddress);
                     double distance = (neighborPosition-nextReverseAnchorPosition).length();
                     if (distance < bestDistance) {
                         bestDistance = distance;
                         bestNextHopAddress = neighborAddress.get4();
                     }
                 }
                     if(bestNextHopAddress!=IPv4Address::LOOPBACK_ADDRESS)
                         {
                            EV_LOG("send to neighbors: "+globalPositionTable.getHostName(bestNextHopAddress));
                            nextHop=bestNextHopAddress;
                          }
                     else
                     {
                         EV_LOG("no next hop");
                         DROP;
                     }
              }else
              {
                  EV_LOG("not datapacket");
              }
          }
          return ACCEPT;
   }

INetfilter::IHook::Result CAR::datagramLocalOutHook(IPv4Datagram * datagram, const InterfaceEntry *& outputInterfaceEntry, IPv4Address & nextHop) {
       EV_LOG("datagramLocalOutHook");
       Enter_Method("datagramLocalOutHook");
       const IPv4Address & destination = datagram->getDestAddress();
       if (destination.isMulticast() || destination.isLimitedBroadcastAddress()|| routingTable->isLocalAddress(destination)||destination==IPv4Address::LOOPBACK_ADDRESS)
       {
           EV_LOG("Multicast");
           return ACCEPT;
       }
           else {
               EV_LOG("check PGB");
               PGB * PGBpacket=dynamic_cast<PGB *>( (dynamic_cast<UDPPacket *>((dynamic_cast<cPacket *>(datagram))->getEncapsulatedPacket()))->getEncapsulatedPacket());
               AGF * AGFpacket=dynamic_cast<AGF *>( (dynamic_cast<UDPPacket *>((dynamic_cast<cPacket *>(datagram))->getEncapsulatedPacket()))->getEncapsulatedPacket());
               if(PGBpacket!=NULL||AGFpacket!=NULL)
               {
                   return ACCEPT;
               }
           }
       if(AnchorTable.find(destination)==AnchorTable.end()){
           startRouteDiscovery(destination);
           delayPacketlist.addPacket(destination,datagram);
           return  QUEUE;
       }else
       {
           CAR_EV << "Sending datagram: source " << datagram->getSrcAddress() << ", destination " << datagram->getDestAddress() << endl;
          cPacket * networkPacket = dynamic_cast<cPacket *>(datagram);
          carPacket *dataPacket= createDataPacket(datagram->getDestAddress(), networkPacket->decapsulate());
          networkPacket->encapsulate(dataPacket);
          return ACCEPT;
       }
}
void CAR::startRouteDiscovery(const IPv4Address & destAddr)
{
    CAR_EV << "Starting route discovery with originator "<< getSelfAddress()<< " and destination "<< destAddr << endl;
    //aSetOfAnchorPoints.clear();
    //std::cout<< aSetOfAnchorPoints.size() << endl;
    PGB * pgbPacket = createPGB(destAddr);
    //seqNumOfPGB++;
    //pgbPacket->setSeqNum(seqNumOfPGB);
    sendPGB(pgbPacket, 0.0);
 }

INetfilter::IHook::Result  CAR::datagramLocalInHook(IPv4Datagram * datagram, const InterfaceEntry * inputInterfaceEntry)
{
    EV_LOG("datagramLocalInHook");
     cPacket * networkPacket = dynamic_cast<cPacket *>(datagram);
     carPacket * dataPacket = dynamic_cast<carPacket *>(networkPacket->getEncapsulatedPacket());
        if (dataPacket) {
            networkPacket->decapsulate();
            //UDPPacket * updPacket =check_and_cast<UDPPacket*>(dataPacket);
            if(std::find(packetlist.begin(),packetlist.end(),dataPacket->getName())==packetlist.end())
            {
            UDPPacket * updPacket =check_and_cast<UDPPacket*>(dataPacket->decapsulate());
            cout<<updPacket<<endl;
            networkPacket->encapsulate(updPacket);
            packetlist.push_back(dataPacket->getName());
            }else{
             CAR_EV << "Already seen it DROP";
            return DROP;
            }
        }
        return ACCEPT;
}
void CAR::processMessage(cPacket * ctrlPacket,IPv4ControlInfo *udpProtocolCtrlInfo)
{
    EV_LOG("processMessage "+string(ctrlPacket->getName()));
     if (dynamic_cast<carBeacon *>(ctrlPacket))
     {
        EV_LOG("processMessage: Beacon");
        processBeacon((carBeacon *)ctrlPacket);
     }

    else if (dynamic_cast<PGB *>(ctrlPacket))
        receivePGB((PGB *)ctrlPacket);
    else if (dynamic_cast<AGF *>(ctrlPacket))
        receiveAGF((AGF *)ctrlPacket);
      /*  else if (dynamic_cast<stGuard *>(ctrlPacket))
        receiveStGuard((stGuard *)ctrlPacket);
    else if (dynamic_cast<trGuard *>(ctrlPacket))
        receiveTrGuard((trGuard *)ctrlPacket);*/
    else
    {
        EV_LOG("Unknown UDP packet");
        throw cRuntimeError("Unknown UDP packet");
    }
    //delete ctrlPacket;
}
void CAR::scheduleBeaconTimer()
{
    EV_LOG("Scheduling beacon timer");
    //todo :  The fewer neighbors there are, the more frequent is a node¡¯s HELLO beaconing.
    scheduleAt(simTime() + beaconInterval, beaconTimer);
}
void CAR::purgeNeighbors()
{
    EV_LOG("purgeNeighbors");
    std::vector<IPvXAddress> neighborAddresses = neighborPositionTable.getAddresses();
    Coord selfPosition =getSelfPosition();
    for (std::vector<IPvXAddress>::iterator it = neighborAddresses.begin(); it != neighborAddresses.end(); it++)
    {
        const IPvXAddress & neighborAddress = *it;
        Coord neighborPosition = neighborPositionTable.getPosition(neighborAddress);
        simtime_t deltaTime = simTime() - neighborPositionTable.getCreateTime(neighborAddress);
        double distance = (selfPosition-caculateEstimatedPosition(neighborPosition,neighborPositionTable.getSpeed(neighborAddress),deltaTime)).length();
        if (deltaTime >= 2 * beaconInterval || distance >= 0.8 * communicationRange)
                {
                    neighborPositionTable.removePosition(neighborAddress);
                }
    }
}
Coord CAR::caculateEstimatedPosition(Coord oldposition,Coord speed,simtime_t time)
{
   return  oldposition+speed*SIMTIME_DBL(time);
}
simtime_t CAR::getNextNeighborExpiration()
{
    simtime_t oldestPosition = neighborPositionTable.getOldestPosition();
    if (oldestPosition == SimTime::getMaxTime())
        return oldestPosition;
    else
        return oldestPosition + neighborValidityInterval;
}

void CAR::schedulePurgeNeighborsTimer()
{
    EV_LOG("Scheduling purge neighbors timer");
    simtime_t nextExpiration = getNextNeighborExpiration();
    if (nextExpiration == SimTime::getMaxTime()) {
        if (purgeNeighborsTimer->isScheduled())
            cancelEvent(purgeNeighborsTimer);
    }
    else {
        if (!purgeNeighborsTimer->isScheduled())
        {
            scheduleAt(nextExpiration, purgeNeighborsTimer);
        }
        else {
            if (purgeNeighborsTimer->getArrivalTime() != nextExpiration) {
                cancelEvent(purgeNeighborsTimer);
                scheduleAt(nextExpiration, purgeNeighborsTimer);
            }
        }
    }
}
void CAR::processPurgeNeighborsTimer()
{
    EV_LOG("Processing purge neighbors timer");
    purgeNeighbors();
    schedulePurgeNeighborsTimer();
}
carBeacon * CAR::createBeacon()
{
    EV_LOG("Create Beacon");
    carBeacon * beacon = new carBeacon(getHostName().c_str());
    beacon->setAddress(getSelfAddress());
    beacon->setPosition(getSelfPosition());
    beacon->setSpeed(getSelfSpeed());
    return beacon;
}
void CAR::processBeaconTimer()
{
    CAR_EV << "Processing beacon timer" << endl;
       IPvXAddress selfAddress = getSelfAddress();
       if (!selfAddress.isUnspecified())
       {
           sendBeacon(createBeacon(), uniform(0, maxJitter).dbl());
       }
       scheduleBeaconTimer();
       schedulePurgeNeighborsTimer();
}
void CAR::sendBeacon(carBeacon * beacon, double delay)
{
    MulticastRIPacket(beacon,255,delay);
}
void CAR::processBeacon(carBeacon * beacon)
{
    EV_LOG("Process Beacon");
    CAR_EV << "Processing beacon: address = " << beacon->getAddress() << ", position = "
            << beacon->getPosition() << ", speed = " << beacon->getSpeed() << endl;
    if(beacon->getAddress()==getSelfAddress())
    {
        EV_LOG("self Beacon Drop");
        return;
    }
    CAR_EV<<"add neighbor"<<globalPositionTable.getHostName(beacon->getAddress())<<endl;
    neighborPositionTable.setPosition(beacon->getAddress(), beacon->getPosition(),beacon->getSpeed(),globalPositionTable.getHostName(beacon->getAddress()));
}
void CAR::EV_LOG(std::string context)
{
    RouteInterface::EV_LOG("CAR",context);
}

/************************/
/**** path discovery ****/
/************************/

PGB * CAR::createPGB(const IPvXAddress & destAddress)
{
    simtime_t travelTime = 0;
    unsigned int numOfHops = 0;
    std::string name="pgbPacket_"+getHostName()+std::to_string(seqNumOfPGB++);
    PGB * pgbPacket = new PGB(name.c_str());
    pgbPacket->setOriginatorAddress(getSelfAddress());
    pgbPacket->setPreviousForwarderHostName(getHostName());
    pgbPacket->setOriginatorPosition(getSelfPosition());
    pgbPacket->setOriginatorSpeed(getSelfSpeed());
    pgbPacket->setDestAddress(destAddress);
    pgbPacket->setPreviousForwarderSpeed(getSelfSpeed());
    pgbPacket->setPreviousForwarderPosition(getSelfPosition());
    //pgbPacket->setPgbCounter(pgbCounter);
    pgbPacket->setTravelTime(0);
    pgbPacket->setNumOfHops(0);
    pgbPacket->setSeqNum(seqNumOfPGB);
    std::vector<anchor> aSetOfAnchorPoints;
    anchor * newAnchorPoint = addAsAnAnchor(mobility->getCurrentSpeed(), mobility->getCurrentPosition(),getHostName(),getAngel());
    aSetOfAnchorPoints.push_back(*newAnchorPoint);
    pgbPacket->setPreviousForwarderAngel(getAngel());
    pgbPacket->setASetOfAnchorPoints(aSetOfAnchorPoints);
    return pgbPacket;
}

AGF * CAR::createAGF(PGB * pgbPacket)
{
    EV_LOG ( "createAGF" );
    string name =pgbPacket->getName();
    AGF * agfPacket = new AGF(name.replace(0,3,"afg").c_str());
    agfPacket->setOriginatorAddress(pgbPacket->getOriginatorAddress());
    agfPacket->setDestAddress(getSelfAddress());
    agfPacket->setDestPosition(mobility->getCurrentPosition());
    agfPacket->setDestSpeed(mobility->getCurrentSpeed());
    agfPacket->setTravelTime(pgbPacket->getTravelTime());
    agfPacket->setNumOfHops(pgbPacket->getNumOfHops());
    std::vector<anchor> a = pgbPacket->getASetOfAnchorPoints();
    anchor * newAnchorPoint = addAsAnAnchor(mobility->getCurrentSpeed(), mobility->getCurrentPosition(),getHostName(),getAngel());
    a.push_back(*newAnchorPoint);
    agfPacket->setASetOfAnchorPoints(a);
    for(int i=0;i<a.size();i++)
      {
          EV_LOG ( "anchor from "+ a[i].getPreviousForwarderHostName()+"  to  "+a[i].getCurrentHostName());
      }
  //  anchorIndexReverse = aSetOfAnchorPoints.size();
    agfPacket->setAnchorIndex(a.size()-2);
    return agfPacket;
}
carPacket * CAR::createDataPacket(const IPvXAddress & destAddress,cPacket * datagram)
{
    std::string name=std::string("dataPacket_")+datagram->getName()+"_"+getHostName();
    carPacket * dataPacket = new carPacket(name.c_str());
    dataPacket->setOriginatorAddress(getSelfAddress());
    dataPacket->setDestinationAddress(destAddress);
    dataPacket->setASetOfAnchorPoints( AnchorTable[destAddress]);
    dataPacket->anchorIndex=0;
    dataPacket->encapsulate(datagram);
    return dataPacket;
}
void CAR::sendPGB(PGB * pgbPacket, double delay)
{
    CAR_EV << "Sending PGB packet: address = " << pgbPacket->getOriginatorAddress()
            << ", position = " << pgbPacket->getOriginatorPosition() << ", speed = " << pgbPacket->getOriginatorSpeed() << endl;
    MulticastRIPacket(pgbPacket,255,delay);
}
void CAR::sendAGF(AGF * agfPacket, const IPv4Address& nextHop, double delay)
{
    CAR_EV << "Sending AGF Route Reply to "<< agfPacket->getOriginatorAddress() <<"  "<<globalPositionTable.getHostName(agfPacket->getOriginatorAddress())<<" next Hop is "<<globalPositionTable.getHostName(nextHop)<< endl;
    std::cout << "Sending AGF Route Reply to "<< agfPacket->getOriginatorAddress() <<"  "<<globalPositionTable.getHostName(agfPacket->getOriginatorAddress())<<" next Hop is "<<globalPositionTable.getHostName(nextHop)<< endl;
    sendRIPacket(agfPacket,nextHop,255,delay);
}
/******************/
/**** position ****/
/******************/

anchor * CAR::addAsAnAnchor(Coord forspeed, Coord curspeed, Coord forposition, Coord curposition,std::string preHostName,std::string CurrHostName, double preangel, double nextangel)
{
    EV_LOG ( "add anchor from "+ preHostName+"  to  "+CurrHostName);
    anchor * anchorPoint = new anchor();
    anchorPoint->setPositionOfCurrentNode(curposition);
    anchorPoint->setPositionOfPreviousForwarder(forposition);
    anchorPoint->setSpeedOfCurrentNode(curspeed);
    anchorPoint->setSpeedOfPreviousForwarder(forspeed);
    anchorPoint->setPreviousForwarderHostName(preHostName);
    anchorPoint->setCurrentHostName(CurrHostName);
    anchorPoint->setCurrentForwarderAngel(nextangel);
    anchorPoint->setPreviousForwarderAngel(preangel);
    //Coord position = caculateTheCoordOfTheAnchor(position1, position2);
    anchorPoint->setPosition(forposition,curposition);
    std::cout << "Next Anchor is : " << getHostName() << endl;
    return anchorPoint;
}
anchor * CAR::addAsAnAnchor(Coord speed1, Coord position1,std::string preHostName,double preangel)
{
    EV_LOG ( "add anchor from "+ preHostName+"  to  "+preHostName);
    anchor * anchorPoint = new anchor();
    anchorPoint->setPositionOfCurrentNode(position1);
    anchorPoint->setPositionOfPreviousForwarder(position1);
    anchorPoint->setSpeedOfCurrentNode(speed1);
    anchorPoint->setSpeedOfPreviousForwarder(speed1);
    anchorPoint->setPreviousForwarderHostName(preHostName);
    anchorPoint->setCurrentHostName(preHostName);
   // Coord position = caculateTheCoordOfTheAnchor(position1, position1);
    anchorPoint->setPosition(position1,position1);
    anchorPoint->setCurrentForwarderAngel(preangel);
    anchorPoint->setPreviousForwarderAngel(preangel);
    std::cout << "Next Anchor is : " << getHostName() << endl;
    return anchorPoint;
}
Coord CAR::caculateTheCoordOfTheAnchor(Coord position1, Coord position2)
{
    // how to determine the coordination of the anchor is still not decided
    double x1 = position1.x;
    double y1 = position1.y;
    double x2 = position2.x;
    double y2 = position2.y;
    double x = (x2+x1)/2;
    double y = (y1+y2)/2;
    return Coord(x, y, 0);
}

bool CAR::isSeenPGB(IPvXAddress ipadd, int seqnum)
{
    if (PGBTable.count(ipadd) == 0 )
       {
        EV_LOG ("PGBTable.count =0");
        return false;
       }else
       {
           EV_LOG ("PGBTable.count !=0");

           bool flag =false;
           std::vector<std::pair < simtime_t,int > > oldlist= PGBTable[ipadd];
           EV_LOG (std::to_string(oldlist.size()));
           std::vector<std::pair < simtime_t,int > > newlist;
           for(int i=0;i<oldlist.size();i++)
           {
              if( simTime()- (oldlist[i].first) <60)
              {
                  if(oldlist[i].second==seqnum)
                  {
                      flag =true;
                      oldlist[i].first=simTime();
                  }
                  newlist.push_back(oldlist[i]);
              }
           }
           PGBTable[ipadd]=newlist;
           return flag;
       }
}

void CAR::receivePGB(PGB * pgbPacket)
{
    EV_LOG("Process PGB");

    CAR_EV <<getSelfAddress()<< "  Receiving PGB from " << pgbPacket->getOriginatorAddress() << " to " << pgbPacket->getDestAddress() << endl;
    std::cout <<getSelfAddress()<< "  Receiving PGB from " << pgbPacket->getOriginatorAddress() << " to " << pgbPacket->getDestAddress() << endl;
    if(getSelfAddress()==pgbPacket->getOriginatorAddress())
    {
        EV_LOG("  Receiving self PGB drop " );
        return;
    }
    simtime_t arrivalTime = pgbPacket->getArrivalTime();
    std::string PreviousForwarderHostName=pgbPacket->getPreviousForwarderHostName();
    Coord theSpeedOfPreviousForwarder = pgbPacket->getPreviousForwarderSpeed();
    Coord thePositionOfPrreviousForwarder = pgbPacket->getPreviousForwarderPosition();
    double previousForwarderAngel=pgbPacket->getPreviousForwarderAngel();
    Coord currentSpeed = getSelfSpeed();
    Coord currentPosition = getSelfPosition();
    std::vector<anchor> anchorSet = pgbPacket->getASetOfAnchorPoints();
    std::cout<< pgbPacket->getSeqNum()<<"   " << pgbPacket->getOriginatorAddress()<< endl;
    if (!isSeenPGB(pgbPacket->getOriginatorAddress(),pgbPacket->getSeqNum()))
    {
        EV_LOG("  not a seen PGB " );
        //simTime() as arrivaltime
        PGBTable[pgbPacket->getOriginatorAddress()].push_back(std::pair < simtime_t,int >(simTime(), pgbPacket->getSeqNum()));
        if (pgbPacket->getDestAddress() == getSelfAddress())
               {
                   EV_LOG ( "The PGB packet reaches its destination!!!" );
                   LOG_EV<<"The PGB packet reaches its destination!!!"<<endl;
                   //double angle1 = adjustVectorAngle(previousForwarderAngel)/ (2 * PI) * 360;
                 //  double angle2 = adjustVectorAngle(getAngel()) / (2 * PI) * 360;
                   double delta;// = angle1 - angle2;
                   //delta=delat.cabs();
                   if(isParallel(previousForwarderAngel,getAngel(),alpha,delta))
                       {
                           cout<<theSpeedOfPreviousForwarder <<"   "<< previousForwarderAngel<<endl;
                           CAR_EV<<theSpeedOfPreviousForwarder <<"   "<< previousForwarderAngel<<endl;
                           cout<<currentSpeed <<"   "<< getAngel()<<endl;
                           CAR_EV<<currentSpeed <<"   "<< getAngel()<<endl;
                           EV_LOG ( "add anchor with angel: " +std::to_string(delta));
                           anchor * newAnchorPoint = addAsAnAnchor(theSpeedOfPreviousForwarder, currentSpeed, thePositionOfPrreviousForwarder, currentPosition,PreviousForwarderHostName,getHostName(),previousForwarderAngel,getAngel());
                           anchorSet.push_back(*newAnchorPoint);
                           pgbPacket->setASetOfAnchorPoints(anchorSet);
                         //  std::cout<<getHostName()<<"    "<< pgbPacket->getASetOfAnchorPoints().back().getPosition()<<"   "<< pgbPacket->getASetOfAnchorPoints().size()<< endl;
                       }else
                       {
                           EV_LOG ( "don't add anchor with angel: " +std::to_string(delta));
                       }
                   AGF * agfPacket = createAGF(pgbPacket);
                   std::vector<anchor> reverseRoute = agfPacket->getASetOfAnchorPoints();
                   for(int i=0;i<reverseRoute.size();i++)
                   {
                       EV_LOG ( "anchor from "+ reverseRoute[i].getPreviousForwarderHostName()+"  to  "+reverseRoute[i].getCurrentHostName());
                       LOG_EV<<"anchor from "<< reverseRoute[i].getPreviousForwarderHostName()<<"  to  "+reverseRoute[i].getCurrentHostName()<<endl;
                   }
                   IPvXAddress bestNextHopAddress = findReverseNextHop(reverseRoute);
                   EV_LOG ( "selct nexthop "+globalPositionTable.getHostName(bestNextHopAddress));
                   if(bestNextHopAddress!=IPv4Address::LOOPBACK_ADDRESS)
                   {
                       sendAGF(agfPacket, bestNextHopAddress.get4(), uniform(0, maxJitter).dbl());
                   }else
                   {
                       EV_LOG ( "no next hop to reply PGB packet" );
                   }
               }
            else
                {
                    EV_LOG ( "passing on the PGB packet" );
                    std::cout << pgbPacket->getPreviousForwarderSpeed() << "    " << getSelfSpeed();
                    pgbPacket->setPreviousForwarderSpeed(currentSpeed);
                    pgbPacket->setPreviousForwarderPosition(currentPosition);
                    pgbPacket->setTravelTime(pgbPacket->getTravelTime() + simTime() - pgbPacket->getSendingTime());
                    pgbPacket->setNumOfHops(pgbPacket->getNumOfHops() + 1);
                    pgbPacket->setPreviousForwarderHostName(getHostName());
                    pgbPacket->setPreviousForwarderAngel(getAngel());
                   // double angle1 = adjustVectorAngle(previousForwarderAngel)/ (2 * PI) * 360;
                    //double angle2 = adjustVectorAngle(getAngel()) / (2 * PI) * 360;
                    double delta;// = angle1 - angle2;
                    if(isParallel(previousForwarderAngel,getAngel(),alpha,delta) )
                        {
                            cout<<theSpeedOfPreviousForwarder <<"   "<< previousForwarderAngel<<endl;
                            CAR_EV<<theSpeedOfPreviousForwarder <<"   "<< previousForwarderAngel<<endl;
                            cout<<currentSpeed <<"   "<< getAngel()<<endl;
                            CAR_EV<<currentSpeed <<"   "<< getAngel()<<endl;
                            EV_LOG ( "add anchor with angel: " +std::to_string(delta));
                            anchor * newAnchorPoint = addAsAnAnchor(theSpeedOfPreviousForwarder, currentSpeed, thePositionOfPrreviousForwarder, currentPosition,PreviousForwarderHostName,getHostName(),previousForwarderAngel,getAngel());
                            std::cout<< pgbPacket->getASetOfAnchorPoints().size()<< endl;
                            anchorSet.push_back(*newAnchorPoint);
                            pgbPacket->setASetOfAnchorPoints(anchorSet);
                          //  std::cout<<getHostName()<<"    "<< pgbPacket->getASetOfAnchorPoints().back().getPosition()<<"   "<< pgbPacket->getASetOfAnchorPoints().size()<< endl;
                        }else
                        {
                            EV_LOG ( "don't add anchor with angel: " +std::to_string(delta));
                        }
                    sendPGB(pgbPacket, uniform(0, maxJitter).dbl());
                }
    }
    else
    {
        EV_LOG("  Receiving same PGB drop " );
        return;
    }
}
void CAR::receiveAGF(AGF * agfPacket)
{
    CAR_EV << "Receiving AGF Route Reply from: " << agfPacket->getDestAddress() << "back to " << agfPacket->getOriginatorAddress() << endl;
    std::cout <<getSelfAddress()<< "Receiving AGF Route Reply from: " << agfPacket->getDestAddress() << "back to " << agfPacket->getOriginatorAddress() << endl;
    if (getSelfAddress() == agfPacket->getOriginatorAddress())
    {
        EV_LOG ("The AGF Route Reply reaches the originator!!!");
        AnchorTable[agfPacket->getDestAddress()]=agfPacket->getASetOfAnchorPoints();
       // routeDiscoveryIsFinished = true;
      //  routingTableCar routeInfo ;
      //  routeInfo.setRouteInfo(agfPacket->getASetOfAnchorPoints());
        completeRouteDiscovery(agfPacket->getDestAddress().get4());
    }
    else
    {
        IPv4Address bestNextHopAddress=IPv4Address::LOOPBACK_ADDRESS;
        int index =agfPacket->anchorIndex;
        EV_LOG("index "+std::to_string(index));
        if (index>=0)
        {
             IPvXAddress selfAddress = getSelfAddress();
            Coord selfPosition = getSelfPosition();
             double bestDistance =1000;// (selfPosition-nextReverseAnchorPosition).length();
            std::vector<IPvXAddress> neighborAddresses = neighborPositionTable.getAddresses();
            std::cout << "neighborAddresses   "<<neighborAddresses.size() <<endl;
            anchor aimanchor =agfPacket->getASetOfAnchorPoints()[index];
            Coord nextReverseAnchorPosition = aimanchor.getPreviousForwarderPosition();
            EV_LOG("aim anchor is form "+aimanchor.getPreviousForwarderHostName()+"  "+aimanchor.getCurrentHostName());
            //double angle1 = adjustVectorAngle(aimanchor.getPreviousForwarderAngel())/ (2 * PI) * 360;
           // double angle2 = adjustVectorAngle(getAngel()) / (2 * PI) * 360;
            double delta;// = angle1 - angle2;
            double myDistance =(selfPosition-aimanchor.getPreviousForwarderPosition()).length();
            if(index!=0&& myDistance<neardistence&&isParallel(aimanchor.getPreviousForwarderAngel(),getAngel(),alpha,delta))
            {
                EV_LOG("pop the last anchor");
                //EV_LOG(" neighbors: "+globalPositionTable.getHostName(getSelfIPAddress())+" near "+std::to_string(bestDistance)+" and in same line "+std::to_string(delta));
                agfPacket->anchorIndex=agfPacket->anchorIndex-1;
                aimanchor=agfPacket->getASetOfAnchorPoints()[agfPacket->anchorIndex];
                nextReverseAnchorPosition = aimanchor.getPreviousForwarderPosition();
                EV_LOG ( "new aim anchor from "+ aimanchor.getPreviousForwarderHostName()+"  to  "+aimanchor.getCurrentHostName());
            }
            else
            {
                EV_LOG(" neighbors: "+globalPositionTable.getHostName(getSelfIPAddress())+" too far "+std::to_string(myDistance)+" not in same line "+std::to_string(delta));
            }
            EV_LOG("anchor position is x= "+std::to_string(nextReverseAnchorPosition.x)+" y= "+std::to_string(nextReverseAnchorPosition.y));
            EV_LOG("anchor pre-position is "+aimanchor.getPreviousForwarderHostName()+" x= "+std::to_string(aimanchor.getPositionOfPreviousForwarder().x)+" y= "+std::to_string(aimanchor.getPositionOfPreviousForwarder().y));
            EV_LOG("anchor cur-position is "+aimanchor.getCurrentHostName()+" x= "+std::to_string(aimanchor.getPositionOfCurrentNode().x)+" y= "+std::to_string(aimanchor.getPositionOfCurrentNode().y));
            for (std::vector<IPvXAddress>::iterator it = neighborAddresses.begin(); it !=neighborAddresses.end(); it++)
            {
                const IPvXAddress & neighborAddress = * it;
                Coord neighborPosition = neighborPositionTable.getPosition(neighborAddress);
                double distance = (neighborPosition-nextReverseAnchorPosition).length();
                EV_LOG("I have neighbors: "+globalPositionTable.getHostName(*it)+" position is x= "+std::to_string(neighborPosition.x)+" y= "+std::to_string(neighborPosition.y)+" distence is "+std::to_string(distance));
                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestNextHopAddress = neighborAddress.get4();
                }
            }
            EV_LOG("bestDistance"+std::to_string(bestDistance));
        }
        if(bestNextHopAddress!=IPv4Address::LOOPBACK_ADDRESS)
          {
            sendAGF(agfPacket, bestNextHopAddress, uniform(0, maxJitter).dbl());
          }else
          {
              EV_LOG( "Can't find next hop droped" );
          }
    }
}
bool CAR::isParallel(double angle1,double angle2,double degree,double& diffdegree)
{
    double adjustedangle1 = adjustVectorAngle(angle1)/ (2 * PI) * 360;
    double adjustedangle2 = adjustVectorAngle(angle2) / (2 * PI) * 360;
    diffdegree = angle1 - angle2;
    if(diffdegree<0)
        diffdegree=-diffdegree;
   if( diffdegree >= degree)
   {
       return false;
   }
   return true;
}
IPvXAddress CAR::findReverseNextHop(std::vector<anchor>& reverseRoute)
{
    EV_LOG( "Finding the reverse next hop for the Routing" );
    CAR_EV <<  reverseRoute.size()  << endl;
    std::cout <<  reverseRoute.size()  << endl;

    IPvXAddress selfAddress = getSelfAddress();
    IPvXAddress bestNextHopAddress=IPv4Address::LOOPBACK_ADDRESS;
    Coord selfPosition = getSelfPosition();
    anchor nextAnchorPoint = reverseRoute.back();
    EV_LOG ( "need to reach anchor from "+ nextAnchorPoint.getPreviousForwarderHostName()+"  to  "+nextAnchorPoint.getCurrentHostName());
    Coord nextReverseAnchorPosition = nextAnchorPoint.getCurrentNodePosition();
    double bestDistance = 10000;//(selfPosition- nextReverseAnchorPosition).length();
    std::vector<IPvXAddress> neighborAddresses = neighborPositionTable.getAddresses();
    for (std::vector<IPvXAddress>::iterator it = neighborAddresses.begin(); it !=neighborAddresses.end(); it++)
    {
        const IPvXAddress & neighborAddress = * it;
        Coord neighborPosition = neighborPositionTable.getPosition(neighborAddress);
        double distance = (neighborPosition-nextReverseAnchorPosition).length();
        if (distance < bestDistance) {
            bestDistance = distance;
            bestNextHopAddress = neighborAddress.get4();
        }
    }
    std::cout <<  bestNextHopAddress  << endl;
    return bestNextHopAddress;
}

double CAR::getVectorAngle(Coord vector)
{
    double angle = atan2(-vector.y, vector.x);
    adjustVectorAngle(angle);
    return angle;
}
double CAR::adjustVectorAngle(double angle)
{
    if (angle < 0)
        angle += 2 * PI;
    if (angle > PI)
         angle -= PI;
    if (angle > PI/2)
        angle=PI-angle;
    return angle;
}
void CAR::completeRouteDiscovery(const IPv4Address & destAddr)
{
    CAR_EV << "Completing route discovery, originator " << getSelfAddress() << ", destination " << destAddr << endl;
    std::multimap<IPvXAddress, IPv4Datagram *>::iterator lt = delayPacketlist.getlowerbound(destAddr);
    std::multimap<IPvXAddress, IPv4Datagram *>::iterator ut = delayPacketlist.getupperbound(destAddr);
    for (std::multimap<IPvXAddress, IPv4Datagram *>::iterator it = lt; it != ut; it++) {
        IPv4Datagram *datagram = it->second;
        CAR_EV << "Sending queued datagram: source " << datagram->getSrcAddress() << ", destination " << datagram->getDestAddress() << endl;
        cPacket * networkPacket = dynamic_cast<cPacket *>(datagram);
        carPacket *dataPacket= createDataPacket(datagram->getDestAddress(), networkPacket->decapsulate());
        networkPacket->encapsulate(dataPacket);
        networkProtocol->reinjectQueuedDatagram(const_cast<const IPv4Datagram *>(datagram));
    }
    // clear the multimap
    delayPacketlist.removePacket(destAddr);
}
