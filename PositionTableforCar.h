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
        CarInformation()//simtime_t createTime,const std::string hostname ,const Coord  position,const Coord speed)
        {
           // this->createTime=createTime;
           // this->hostName=hostname;
           // this->position=position;
          //  this->speed=speed;
        }
};
class INET_API PositionTableforCar {
    private:
        typedef std::map<IPvXAddress, CarInformation> AddressToPositionMap;
        AddressToPositionMap addressToPositionMap;

    public:
        PositionTableforCar() { }

        std::vector<IPvXAddress> getAddresses() const;
        int getLengthOfPositionTable();

        bool hasPosition(const IPvXAddress & address) const;
        Coord getPosition(const IPvXAddress & address) const;
        void setPosition(const IPvXAddress & address, const Coord & position,const Coord & speed,const std::string hostname);
        void setSpeed(const IPvXAddress & address, const Coord & speed);
        Coord getSpeed(const IPvXAddress & address) const;

        void setHostName(const IPvXAddress & address, const std::string hostname);
        std::string getHostName(const IPvXAddress & address) const;

        void setIfCoordinator(const IPvXAddress & address, const bool & iscoordinator);
        bool getIfCoordinator(const IPvXAddress & address) const;


        void removePosition(const IPvXAddress & address);
        void removeOldPositions(simtime_t timestamp);

        void clear();

        simtime_t getOldestPosition() const;
};



#endif
