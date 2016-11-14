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
#include "CAR/carRouting_msg.h"
class packetInfor
{
public:
    Coord speed;
    simtime_t Traveltime;
    Coord position;
    double direction;
};
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
    simtime_t maxJitter;
    cMessage * RUTimer;
    simtime_t nextRUtimer;
    bool isendpoint;
    int seqNumOfPGB;
    bool usingCommunacteDirection;
    bool isUsingJunctionCars;
    // communication Range
    double communicationRange;
    double GuardedRadius;
    simtime_t stGuardTTL;
    std::map < IPvXAddress, std::vector<std::pair < simtime_t,int > > > PGBTable;
    std::map < IPvXAddress, std::vector<anchor> > AnchorTable;
    std::map < IPvXAddress, packetInfor > desInfor;
    std::map <cMessage * ,AGF* > AGFTable;
    std::map <cMessage * ,carPacket* > DATATable;
    std::vector<std::string> packetlist;
    double alpha;
    double neardistence;
    PositionTableforCar neighborPositionTable;
    PositionTableforCar guardsTable;
    std::vector <Guard>  ListOfguards;
    double olddirection;
    bool is0and180Pall;
    int stGuardID;
    int trGuardID;
private:
    virtual Result datagramPreRoutingHook(IPv4Datagram * datagram, const InterfaceEntry * inputInterfaceEntry, const InterfaceEntry *& outputInterfaceEntry, IPv4Address & nextHop);
    virtual Result datagramForwardHook(IPv4Datagram * datagram, const InterfaceEntry * inputInterfaceEntry, const InterfaceEntry *& outputInterfaceEntry, IPv4Address & nextHop){ return ACCEPT; }
    virtual Result datagramPostRoutingHook(IPv4Datagram * datagram, const InterfaceEntry * inputInterfaceEntry, const InterfaceEntry *& outputInterfaceEntry, IPv4Address & nextHop) ;
    virtual Result datagramLocalInHook(IPv4Datagram * datagram, const InterfaceEntry * inputInterfaceEntry);//{ return ACCEPT; }
    virtual Result datagramLocalOutHook(IPv4Datagram * datagram, const InterfaceEntry *& outputInterfaceEntry, IPv4Address & nextHop);

    void EV_LOG(std::string context);
    void scheduleBeaconTimer();
    void schedulePurgeNeighborsTimer();

    void purgeNeighbors();
    simtime_t getNextNeighborExpiration();
    void clearListofGuards();
    std::vector <Guard>  getVaildListofGuards();
    void addTOListofGuards(Guard guard);

    void processMessage(cPacket * ctrlPacket,IPv4ControlInfo *udpProtocolCtrlInfo);
    void processBeaconTimer();
    void processBeacon(carBeacon * beacon);
    void processRUTimer(simtime_t timer);

    carBeacon * createBeacon();
    void sendBeacon(carBeacon * beacon, double delay);
    Coord caculateEstimatedPosition(Coord oldposition,Coord speed,simtime_t time);
    void startRouteDiscovery(const IPv4Address & destAddr);
    PGB * createPGB(const IPvXAddress & destAddress);
    AGF * createAGF(PGB * pgbPacket);
    carPacket * createDataPacket(const IPvXAddress & destAddress,cPacket * datagram);
    carPacket * createDataPacket(carPacket * srcpacket);
    stGuard createStguard();
    trGuard createTrguard();

    void  sendPGB(PGB * pgbPacket, double delay);
    void sendAGF(AGF * agfPacket, const IPv4Address& nextHop, double delay);
    Coord caculateTheCoordOfTheAnchor(Coord position1, Coord position2);
    anchor  addAsAnAnchor(Coord speed1, Coord speed2, Coord position1, Coord position2,std::string preHostName,std::string CurrHostName, double preangel, double nextangel);
    anchor  addAsAnAnchor(Coord speed1, Coord position1,std::string preHostName,double preangel);
    bool isSeenPGB(IPvXAddress ipadd, int seqnum);
    void receivePGB(PGB * pgbPacket);
    void receiveAGF(AGF * agfPacket);
    void trysendAGF(AGF * agfPacket,cMessage* timer);
    IPvXAddress findReverseNextHop(anchor reverseRoute,bool forwarding);
    bool isParallel(double angel1,double angel2,double degree,double& diffdegree);
    double getVectorAngle(Coord vector);
    double adjustVectorAngle(double angle);
    void completeRouteDiscovery(const IPv4Address & destAddr);


 };

#endif /* RBVTRPACKET_H_ */
