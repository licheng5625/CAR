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
        EV_LOG("CAR",getHostName()+"road "+myroad);
        IPSocket socket(gate("ipOut"));
        socket.registerProtocol(IP_PROT_MANET);

       // DATAliftime= par("DATAliftime");
       // nextRUtimer= par("nextRUtimer");
      //  RUliftime= par("RUliftime");
        routingTable = check_and_cast<IRoutingTable *>(getModuleByPath(par("routingTableModule")));

        //reBoardcastRDTimer = new cMessage("ReBoardcastRDTimer");;
    }else{
    if (stage == 4)
        {
        RouteInterface::configureInterfaces(par("interfaces"));
        EV_LOG("CAR",getHostName());
      //  std::list<std::string> interjections=tracimanager->commandGetJunctionIds();
       /* for(std::list<std::string>::iterator iter=interjections.begin();iter!=interjections.end();++iter)
        {
            RBVTP_EV<<*iter<<"   "<<tracimanager->commandGetJunctionPosition(*iter)<<endl;
        }*/
        globlePositionTable.setHostName(getSelfIPAddress(),getHostName());
        }
    }
 }



void CAR::processSelfMessage(cMessage * message)
{
       // case RTSTimeOutTimer:
        //    processRTStTimer(nextCPtimer);
        //    break;
    EV_LOG("CAR", "processSelfMessage" );
    CAR_EV<<"processSelfMessage  "<<message->getName()<<endl;

   /* if (message == CPTimer)
       {
            EV_LOG("RBVTR", "process  CPTimer" );
            processCPTimer(nextCPtimer);
            return ;
        }
    */

}


INetfilter::IHook::Result CAR::datagramPreRoutingHook(IPv4Datagram * datagram, const InterfaceEntry * inputInterfaceEntry, const InterfaceEntry *& outputInterfaceEntry, IPv4Address & nextHop){
     EV_LOG("CAR","datagramPreRoutingHook");
     Enter_Method("datagramPreRoutingHook");
      return ACCEPT;
}
INetfilter::IHook::Result CAR::datagramPostRoutingHook(IPv4Datagram * datagram, const InterfaceEntry * inputInterfaceEntry, const InterfaceEntry *& outputInterfaceEntry, IPv4Address & nextHop)
{
    EV_LOG("CAR","datagramPostRoutingHook");
       const IPv4Address & destination = datagram->getDestAddress();

       if (destination.isMulticast() || destination.isLimitedBroadcastAddress()|| routingTable->isLocalAddress(destination))
                  return ACCEPT;
       else{
           return ACCEPT;

       }
       return ACCEPT;

}
INetfilter::IHook::Result CAR::datagramLocalOutHook(IPv4Datagram * datagram, const InterfaceEntry *& outputInterfaceEntry, IPv4Address & nextHop) {
       EV_LOG("CAR","datagramLocalOutHook");
       Enter_Method("datagramLocalOutHook");
       const IPv4Address & destination = datagram->getDestAddress();
       if (destination.isMulticast() || destination.isLimitedBroadcastAddress()|| routingTable->isLocalAddress(destination)||destination==IPv4Address::LOOPBACK_ADDRESS)
       {
           EV_LOG("CAR","Multicast");
           return ACCEPT;
       }
           else {
               EV_LOG("CAR","check rbvtppacket");

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
  /*  RBVTPPacket *rbvtpPacket = dynamic_cast<RBVTPPacket *>(ctrlPacket);
    if(rbvtpPacket->getLifetime()<simTime())
    {
        EV_LOG("RBVTR","Time out droped");
        return;
    }
     switch( rbvtpPacket->getPacketType())
    {
     case RBVTP_DATA:
               EV_LOG("RBVTR","Process RBVTP_DATA");
               //processRDPACKET(rbvtpPacket);
               break;
     case RBVTP_CP:
               EV_LOG("RBVTR","Process RBVTP_CP");
               processCPPACKET(rbvtpPacket);
               break;
     case RBVTP_RTS:
                EV_LOG("RBVTR","Process RBVTP_RTS");
                processRTSPACKET(rbvtpPacket);
                break;
     case RBVTP_CTS:
                EV_LOG("RBVTR","Process RBVTP_CTS");
                processCTSPACKET(rbvtpPacket);
                break;

     case RBVTP_RU:
               EV_LOG("RBVTR","Process RBVTP_RU");
              // processRUPACKET(rbvtpPacket);
               break;
     default :
         throw cRuntimeError("Unknown packet type");
    }*/
}

