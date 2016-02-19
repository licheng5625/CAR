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
    this->positionOfCurrentNode_var = other.positionOfCurrentNode_var;
    this->positionOfPreviousForwarder_var = other.positionOfPreviousForwarder_var;
    this->CurrentHostName=other.CurrentHostName;
    this->PreviousForwarderHostName=other.PreviousForwarderHostName;
    this->currentForwarderAngel=other.currentForwarderAngel;
    this->currentForwarderAngel=other.currentForwarderAngel;
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

Coord& anchor::getPreviousForwarderPosition()
{
    return positionOfPreviousForwarder_var;
}
Coord& anchor::getCurrentNodePosition()
{
    return positionOfCurrentNode_var;
}
void anchor::setPreviousForwarderPosition(const Coord& position)
{
    this->positionOfPreviousForwarder_var = position;
}
void anchor::setPosition(const Coord& forposition,const Coord& curposition)
{
    this->positionOfPreviousForwarder_var = forposition;
    this->positionOfCurrentNode_var = curposition;
}
void anchor::setCurrentNodePosition(const Coord& position)
{
    this->positionOfCurrentNode_var = position;
}
std::string& anchor::getPreviousForwarderHostName()
{
    return this->PreviousForwarderHostName;
}

void anchor::setPreviousForwarderHostName(std::string& PreviousForwarderHostName)
{
    this->PreviousForwarderHostName = PreviousForwarderHostName;
}

std::string& anchor::getCurrentHostName()
{
    return this->CurrentHostName;
}

void anchor::setCurrentHostName(std::string& CurrentHostName)
{
    this->CurrentHostName = CurrentHostName;
}

double& anchor::getPreviousForwarderAngel()
{
    return previousForwarderAngel;
}
void anchor::setPreviousForwarderAngel(double& previousForwarderAngel)
{
    this->previousForwarderAngel=previousForwarderAngel;
}
double& anchor::getCurrentForwarderAngel()
{
    return currentForwarderAngel;
}
void anchor::setCurrentForwarderAngel(double& currentForwarderAngel)
{
    this->currentForwarderAngel=currentForwarderAngel;
}
