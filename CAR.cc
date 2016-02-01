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
        beaconInterval = par("beaconInterval");
        communicationRange = par("communicationRange");
        neighborValidityInterval = par("neighborValidityInterval");         // maybe will not be used
        maxJitter = par("maxJitter");
       // nextRUtimer= par("nextRUtimer");
      //  RUliftime= par("RUliftime");
        routingTable = check_and_cast<IRoutingTable *>(getModuleByPath(par("routingTableModule")));

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
           return ACCEPT;

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
               EV_LOG("check rbvtppacket");

           }
        delayPacketlist.addPacket(destination,datagram);
       return  QUEUE;
}
INetfilter::IHook::Result  CAR::datagramLocalInHook(IPv4Datagram * datagram, const InterfaceEntry * inputInterfaceEntry)
{
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
    // We don't need this carPacket anymore
  /*
    else if (dynamic_cast<PGB *>(ctrlPacket))
        receivePGB((PGB *)ctrlPacket);
    else if (dynamic_cast<AGF *>(ctrlPacket))
        receiveAGF((AGF *)ctrlPacket);
    else if (dynamic_cast<stGuard *>(ctrlPacket))
        receiveStGuard((stGuard *)ctrlPacket);
    else if (dynamic_cast<trGuard *>(ctrlPacket))
        receiveTrGuard((trGuard *)ctrlPacket);*/
    else
    {
        EV_LOG("Unknown UDP packet");
        throw cRuntimeError("Unknown UDP packet");
    }
    delete ctrlPacket;
}
void CAR::scheduleBeaconTimer()
{
    EV_LOG("Scheduling beacon timer");
    //std::cout<< "The number of neighbors is: " << neighborPositionTable.getLengthOfPositionTable() << endl;
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
