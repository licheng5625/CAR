//
// Copyright (C) 2004 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

#ifndef __INET_POSITIONTABLEFORCAR_H_
#define __INET_POSITIONTABLEFORCAR_H_

#include <vector>
#include <map>
#include "INETDefs.h"
#include "IPvXAddress.h"
#include "Coord.h"
static double  NaN = 0.0 / 0.0;

/**
 * This class provides a mapping between node addresses and their positions.
 */
class CarInformation {
    public:
        std::string hostName;
        Coord position;
        Coord speed;
        bool Coordinator;
        simtime_t createTime;
        CarInformation(simtime_t createTime=0, std::string hostname ="", Coord  position=Coord(NaN, NaN, NaN), Coord speed=Coord(NaN, NaN, NaN))
        {
            this->createTime=createTime;
            this->hostName=hostname;
            this->position=position;
            this->speed=speed;
        }
};
class PositionTableforCar {
    private:
        typedef std::map<IPvXAddress, CarInformation> AddressToPositionMap;
        AddressToPositionMap addressToPositionMap;

    public:
        PositionTableforCar() { }

        std::vector<IPvXAddress> getAddresses() ;
        int getLengthOfPositionTable();

        bool hasPosition( IPvXAddress  address) ;
        Coord getPosition( IPvXAddress  address) ;
        void setPosition( IPvXAddress  address,  Coord  position, Coord  speed, std::string hostname);
        void setSpeed( IPvXAddress  address,  Coord  speed);
        Coord getSpeed( IPvXAddress  address) ;
        simtime_t getCreateTime( IPvXAddress  address) ;

        void setHostName( IPvXAddress  address,  std::string hostname);
        std::string getHostName( IPvXAddress  address) ;

        void setIfCoordinator( IPvXAddress  address,  bool  iscoordinator);
        bool getIfCoordinator( IPvXAddress  address) ;


        void removePosition( IPvXAddress  address);
        void removeOldPositions(simtime_t timestamp);

        void clear();

        simtime_t getOldestPosition() ;
};



#endif
