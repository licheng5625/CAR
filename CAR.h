/*
 * RBVTRPacket.h
 *
 *  Created on: Jul 6, 2015
 *      Author: chengli
 */

#ifndef __INET_CAR_H_
#define __INET_CAR_H_

#include <cmessage.h>
#include <RouteInterface.h>
 #include "IPSocket.h"
#include "TraCIScenarioManager.h"
#include <algorithm>
#include <string>
#include "routeInterface/BroadcastWaitingTable.h"
#include "routeInterface/DelayPacketTable.h"
#include "CAR/PositionTableforCar.h"

class INET_API CAR:public RouteInterface {
public:
    CAR();
    virtual ~CAR();

protected:

    IInterfaceTable *interfaceTable;

    void processSelfMessage(cMessage * message);
    void processPurgeNeighborsTimer();

    void initialize(int stage);
    cMessage * beaconTimer;
    cMessage * purgeNeighborsTimer;

    simtime_t beaconInterval;
    simtime_t checkTime;
    simtime_t arrivalTime;
    simtime_t neighborValidityInterval;

    // communication Range
      double communicationRange;

    PositionTableforCar neighborPositionTable;
    PositionTableforCar guardsTable;
private:
    virtual Result datagramPreRoutingHook(IPv4Datagram * datagram, const InterfaceEntry * inputInterfaceEntry, const InterfaceEntry *& outputInterfaceEntry, IPv4Address & nextHop);
    virtual Result datagramForwardHook(IPv4Datagram * datagram, const InterfaceEntry * inputInterfaceEntry, const InterfaceEntry *& outputInterfaceEntry, IPv4Address & nextHop){ return ACCEPT; }
    virtual Result datagramPostRoutingHook(IPv4Datagram * datagram, const InterfaceEntry * inputInterfaceEntry, const InterfaceEntry *& outputInterfaceEntry, IPv4Address & nextHop) ;
    virtual Result datagramLocalInHook(IPv4Datagram * datagram, const InterfaceEntry * inputInterfaceEntry);//{ return ACCEPT; }
    virtual Result datagramLocalOutHook(IPv4Datagram * datagram, const InterfaceEntry *& outputInterfaceEntry, IPv4Address & nextHop);


    void scheduleBeaconTimer();
    void schedulePurgeNeighborsTimer();

    void purgeNeighbors();
    simtime_t getNextNeighborExpiration();

    void processMessage(cPacket * ctrlPacket,IPv4ControlInfo *udpProtocolCtrlInfo);

 };

#endif /* RBVTRPACKET_H_ */
