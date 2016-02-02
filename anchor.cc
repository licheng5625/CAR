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

#include "anchor.h"


anchor::anchor() : ::cObject()
{
}

anchor::anchor(const anchor& other) : ::cObject(other)
{
    copy(other);
}

anchor::~anchor()
{
}

anchor& anchor::operator=(const anchor& other)
{
    if (this==&other) return *this;
    ::cObject::operator=(other);
    copy(other);
    return *this;
}

void anchor::copy(const anchor& other)
{
    this->positionOfPreviousForwarder_var = other.positionOfPreviousForwarder_var;
    this->positionOfCurrentNode_var = other.positionOfCurrentNode_var;
    this->speedOfPreviousForwarder_var = other.speedOfPreviousForwarder_var;
    this->speedOfCurrentNode_var = other.speedOfCurrentNode_var;
    this->position_var = other.position_var;
}


Coord& anchor::getPositionOfPreviousForwarder()
{
    return positionOfPreviousForwarder_var;
}

void anchor::setPositionOfPreviousForwarder(const Coord& positionOfPreviousForwarder)
{
    this->positionOfPreviousForwarder_var = positionOfPreviousForwarder;
}

Coord& anchor::getPositionOfCurrentNode()
{
    return positionOfCurrentNode_var;
}

void anchor::setPositionOfCurrentNode(const Coord& positionOfCurrentNode)
{
    this->positionOfCurrentNode_var = positionOfCurrentNode;
}

Coord& anchor::getSpeedOfPreviousForwarder()
{
    return speedOfPreviousForwarder_var;
}

void anchor::setSpeedOfPreviousForwarder(const Coord& speedOfPreviousForwarder)
{
    this->speedOfPreviousForwarder_var = speedOfPreviousForwarder;
}

Coord& anchor::getSpeedOfCurrentNode()
{
    return speedOfCurrentNode_var;
}

void anchor::setSpeedOfCurrentNode(const Coord& speedOfCurrentNode)
{
    this->speedOfCurrentNode_var = speedOfCurrentNode;
}

Coord& anchor::getPosition()
{
    return position_var;
}

void anchor::setPosition(const Coord& position)
{
    this->position_var = position;
}
