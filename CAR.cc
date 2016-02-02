/*
 * RBVTPPacket.cpp
 *
 *  Created on: Jul 6, 2015
 *      Author: chengli
 */

#include <CAR/CAR.h>
#define CAR_EV EV << "CAR at " << getHostName() << " "
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
        beaconInterval = par("beaconInterval");
        communicationRange = par("communicationRange");
        neighborValidityInterval = par("neighborValidityInterval");         // maybe will not be used
        maxJitter = par("maxJitter");
       // nextRUtimer= par("nextRUtimer");
      //  RUliftime= par("RUliftime");
        routingTable = check_and_cast<IRoutingTable *>(getModuleByPath(par("routingTableModule")));
        alpha = par("alpha");

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
           EV_LOG("get a carPacket0");
           carPacket * datapacket= (dynamic_cast<carPacket *>((dynamic_cast<cPacket *>(datagram))->getEncapsulatedPacket()));
          // carPacket * datapacket=dynamic_cast<carPacket *>( (dynamic_cast<UDPPacket *>((dynamic_cast<cPacket *>(datagram))->getEncapsulatedPacket()))->getEncapsulatedPacket());
           if (datapacket)
              {
                  EV_LOG("get a carPacket");
                  IPv4Address bestNextHopAddress=IPv4Address::LOOPBACK_ADDRESS;
                  Coord nextReverseAnchorPosition = datapacket->getCopyOfASetOfAnchorPoints().back().getPosition();
                  double bestDistance = ( getSelfPosition()-nextReverseAnchorPosition).length();
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
                     if(bestNextHopAddress!=IPv4Address::LOOPBACK_ADDRESS)
                         {
                            EV_LOG("get a carPacket2");
                            if( bestDistance<20)
                            {
                                EV_LOG("get a carPacket3");
                              datapacket->getCopyOfASetOfAnchorPoints().pop_back();
                            }
                            nextHop=bestNextHopAddress;
                          }
                     else
                     {
                         EV_LOG("get a carPacket4");
                         DROP;
                     }
              }else
              {
                  EV_LOG("get a carPacket5");
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
       startRouteDiscovery(destination);
        delayPacketlist.addPacket(destination,datagram);
       return  QUEUE;
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

            UDPPacket * updPacket =check_and_cast<UDPPacket*>(dataPacket->decapsulate());
            cout<<updPacket<<endl;
            networkPacket->encapsulate(updPacket);
            //delete dataPacket;
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
    arrivalTime = beacon->getArrivalTime();
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
    anchor * newAnchorPoint = addAsAnAnchor(mobility->getCurrentSpeed(), mobility->getCurrentSpeed(), mobility->getCurrentPosition(), mobility->getCurrentPosition());
    aSetOfAnchorPoints.push_back(*newAnchorPoint);
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
    agfPacket->setASetOfAnchorPoints(a);
  //  anchorIndexReverse = aSetOfAnchorPoints.size();

    return agfPacket;
}
carPacket * CAR::createDataPacket(const IPvXAddress & destAddress,cPacket * datagram)
{
    std::string name=std::string("dataPacket_")+datagram->getName();
    carPacket * dataPacket = new carPacket(name.c_str());
    dataPacket->setOriginatorAddress(getSelfAddress());
    dataPacket->setDestinationAddress(destAddress);
    dataPacket->setASetOfAnchorPoints( AnchorTable[destAddress]);
    dataPacket->makeACopy();
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
    CAR_EV << "Sending AGF Route Reply to "<< agfPacket->getOriginatorAddress() << endl;
    std::cout << "Sending AGF Route Reply to "<< agfPacket->getOriginatorAddress() << "   nexthop to "<<nextHop<< endl;
    sendRIPacket(agfPacket,nextHop,255,delay);
}
/******************/
/**** position ****/
/******************/

anchor * CAR::addAsAnAnchor(Coord speed1, Coord speed2, Coord position1, Coord position2)
{
    anchor * anchorPoint = new anchor();
    anchorPoint->setPositionOfCurrentNode(position2);
    anchorPoint->setPositionOfPreviousForwarder(position1);
    anchorPoint->setSpeedOfCurrentNode(speed2);
    anchorPoint->setSpeedOfPreviousForwarder(speed1);
    Coord position = caculateTheCoordOfTheAnchor(position1, position2);
    anchorPoint->setPosition(position);
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
    std::cout<< pgbPacket->getSeqNum()<<"   " << pgbPacket->getOriginatorAddress()<< endl;
    if (!isSeenPGB(pgbPacket->getOriginatorAddress(),pgbPacket->getSeqNum()))
    {
        EV_LOG("  not a seen PGB " );
        //simTime() as arrivaltime
        PGBTable[pgbPacket->getOriginatorAddress()].push_back(std::pair < simtime_t,int >(simTime(), pgbPacket->getSeqNum()));
        if (pgbPacket->getDestAddress() == getSelfAddress())
               {
                   EV_LOG ( "The PGB packet reaches its destination!!!" );
                   AGF * agfPacket = createAGF(pgbPacket);
                   agfPacket->makeACopy();
                   std::vector<anchor> reverseRoute = agfPacket->getASetOfAnchorPoints();
                   IPvXAddress bestNextHopAddress = findReverseNextHop(reverseRoute);
                   agfPacket->setCopyOfASetOfAnchorPoints(reverseRoute);
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
                    Coord theSpeedOfPreviousForwarder = pgbPacket->getPreviousForwarderSpeed();
                    Coord thePositionOfPrreviousForwarder = pgbPacket->getPreviousForwarderPosition();
                    Coord currentSpeed = getSelfSpeed();
                    Coord currentPosition = getSelfPosition();
                    std::vector<anchor> anchorSet = pgbPacket->getASetOfAnchorPoints();
                    std::cout << pgbPacket->getPreviousForwarderSpeed() << "    " << getSelfSpeed();
                    pgbPacket->setPreviousForwarderSpeed(currentSpeed);
                    pgbPacket->setPreviousForwarderPosition(currentPosition);
                    pgbPacket->setTravelTime(pgbPacket->getTravelTime() + simTime() - pgbPacket->getSendingTime());
                    pgbPacket->setNumOfHops(pgbPacket->getNumOfHops() + 1);
                    double angle1 = getVectorAngle(theSpeedOfPreviousForwarder) / (2 * PI) * 360;
                    double angle2 = getVectorAngle(currentSpeed) / (2 * PI) * 360;
                    double delta = angle1 - angle2;
                    if(delta < (-alpha) || delta >= alpha)
                        {
                            EV_LOG ( "add anchor" );
                            anchor * newAnchorPoint = addAsAnAnchor(theSpeedOfPreviousForwarder, currentSpeed, thePositionOfPrreviousForwarder, currentPosition);
                            std::cout<< pgbPacket->getASetOfAnchorPoints().size()<< endl;
                            anchorSet.push_back(*newAnchorPoint);
                            pgbPacket->setASetOfAnchorPoints(anchorSet);
                            std::cout<<getHostName()<<"    "<< pgbPacket->getASetOfAnchorPoints().back().getPosition()<<"   "
                                    << pgbPacket->getASetOfAnchorPoints().size()<< endl;
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
        std::cout << "agfPacket->getCopyOfASetOfAnchorPoints()   "<<agfPacket->getCopyOfASetOfAnchorPoints().size() <<endl;
        IPv4Address bestNextHopAddress=IPv4Address::LOOPBACK_ADDRESS;
        if (agfPacket->getCopyOfASetOfAnchorPoints().size()!=0)
        {
            Coord nextReverseAnchorPosition = agfPacket->getCopyOfASetOfAnchorPoints().back().getPosition();


             IPvXAddress selfAddress = getSelfAddress();
            Coord selfPosition = getSelfPosition();
             double bestDistance = (selfPosition-nextReverseAnchorPosition).length();
            std::vector<IPvXAddress> neighborAddresses = neighborPositionTable.getAddresses();
            std::cout << "neighborAddresses   "<<neighborAddresses.size() <<endl;

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
            if(bestDistance<20&&bestNextHopAddress!=IPv4Address::LOOPBACK_ADDRESS)
                {
                        agfPacket->getCopyOfASetOfAnchorPoints().pop_back();
                 }
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
IPvXAddress CAR::findReverseNextHop(std::vector<anchor>& reverseRoute)
{
    EV_LOG( "Finding the reverse next hop for the Routing" );
    CAR_EV <<  reverseRoute.size()  << endl;
    std::cout <<  reverseRoute.size()  << endl;

    IPvXAddress selfAddress = getSelfAddress();
    IPvXAddress bestNextHopAddress=IPv4Address::LOOPBACK_ADDRESS;
    Coord selfPosition = getSelfPosition();
    anchor nextAnchorPoint = reverseRoute.back();
    Coord nextReverseAnchorPosition = nextAnchorPoint.getPosition();
    double bestDistance = (selfPosition- nextReverseAnchorPosition).length();
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
    if(bestDistance<20&&bestNextHopAddress!=IPv4Address::LOOPBACK_ADDRESS)
    {
        reverseRoute.pop_back();
    }
    std::cout <<  bestNextHopAddress  << endl;
    return bestNextHopAddress;
}

double CAR::getVectorAngle(Coord vector)
{
    double angle = atan2(-vector.y, vector.x);
    if (angle < 0)
        angle += 2 * PI;
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
