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

#include "PositionTableforCar.h"


std::vector<IPvXAddress> PositionTableforCar::getAddresses() const {
    std::vector<IPvXAddress> addresses;
    for (AddressToPositionMap::const_iterator it = addressToPositionMap.begin(); it != addressToPositionMap.end(); it++)
        addresses.push_back(it->first);
    return addresses;
}

int PositionTableforCar::getLengthOfPositionTable()
{
    int i=0;
    std::vector<IPvXAddress> addresses;
    for (AddressToPositionMap::const_iterator it = addressToPositionMap.begin(); it != addressToPositionMap.end(); it++)
        i++;
    return i;

}

bool PositionTableforCar::hasPosition(const IPvXAddress & address) const {
    AddressToPositionMap::const_iterator it = addressToPositionMap.find(address);
    return it != addressToPositionMap.end();
}

Coord PositionTableforCar::getPosition(const IPvXAddress & address) const {
    AddressToPositionMap::const_iterator it = addressToPositionMap.find(address);
    if (it == addressToPositionMap.end())
        return Coord(NaN, NaN, NaN);
    else
        return it->second.position;
}

void PositionTableforCar::setPosition(const IPvXAddress & address, const Coord & position,const Coord & speed,const std::string hostname) {
    ASSERT(!address.isUnspecified());
    addressToPositionMap[address] = CarInformation(simTime(),hostname, position,speed);
}
simtime_t PositionTableforCar::getCreateTime(const IPvXAddress & address) {
    AddressToPositionMap::const_iterator it = addressToPositionMap.find(address);
        if (it == addressToPositionMap.end())
            return SimTime::getMaxTime();
        else
            return it->second.createTime;
}
Coord PositionTableforCar::getSpeed(const IPvXAddress & address) const {
    AddressToPositionMap::const_iterator it = addressToPositionMap.find(address);
    if (it == addressToPositionMap.end())
        return Coord(NaN, NaN, NaN);
    else
        return it->second.speed;
}

void PositionTableforCar::setSpeed(const IPvXAddress & address, const Coord & speed) {
    ASSERT(!address.isUnspecified());
    addressToPositionMap[address].speed = speed;
}

void PositionTableforCar::setHostName(const IPvXAddress & address, const std::string hostname)
{
    ASSERT(!address.isUnspecified());
    addressToPositionMap[address].hostName = hostname;
}

std::string PositionTableforCar::getHostName(const IPvXAddress & address) const
{
    AddressToPositionMap::const_iterator it = addressToPositionMap.find(address);
    if (it == addressToPositionMap.end()) {
        return "NONE";
    }
    else {
        return it->second.hostName;
    }
}


void PositionTableforCar::removePosition(const IPvXAddress & address) {
    AddressToPositionMap::iterator it = addressToPositionMap.find(address);
    addressToPositionMap.erase(it);
}

void PositionTableforCar::setIfCoordinator(const IPvXAddress & address, const bool & iscoordinator)
{
    ASSERT(!address.isUnspecified());
    addressToPositionMap[address].Coordinator = iscoordinator;
}

bool PositionTableforCar::getIfCoordinator(const IPvXAddress & address) const
{
    AddressToPositionMap::const_iterator it = addressToPositionMap.find(address);
    if (it == addressToPositionMap.end()) {
        return false;
    }
    else {
        return it->second.Coordinator;
    }
}


void PositionTableforCar::removeOldPositions(simtime_t timestamp) {
    for (AddressToPositionMap::iterator it = addressToPositionMap.begin(); it != addressToPositionMap.end();)
        if (it->second.createTime <= timestamp) {
            addressToPositionMap.erase(it);
            it++;
        }
        else
            it++;
}

void PositionTableforCar::clear() {
    addressToPositionMap.clear();
}

simtime_t PositionTableforCar::getOldestPosition() const {
    simtime_t oldestPosition = SimTime::getMaxTime();
    for (AddressToPositionMap::const_iterator it = addressToPositionMap.begin(); it != addressToPositionMap.end(); it++) {
        const simtime_t & time = it->second.createTime;
        if (time < oldestPosition)
            oldestPosition = time;
    }
    return oldestPosition;
}
