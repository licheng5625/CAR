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

#ifndef __INET_ANCHOR_H_
#define __INET_ANCHOR_H_

#include <vector>
#include <map>
#include "INETDefs.h"
#include "IPvXAddress.h"
#include "Coord.h"


class INET_API anchor : public ::cObject
{
  protected:
    Coord positionOfPreviousForwarder_var;
    Coord positionOfCurrentNode_var;
    Coord speedOfPreviousForwarder_var;
    Coord speedOfCurrentNode_var;
    std::string  PreviousForwarderHostName;
    std::string  CurrentHostName;
    double currentForwarderAngel;
    double previousForwarderAngel;

  private:
    void copy(const anchor& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const anchor&);

  public:
    anchor();
    anchor(const anchor& other);
    virtual ~anchor();
    anchor& operator=(const anchor& other);


    // field getter/setter methods
    virtual Coord& getPositionOfPreviousForwarder();
    virtual const Coord& getPositionOfPreviousForwarder() const {return const_cast<anchor*>(this)->getPositionOfPreviousForwarder();}
    virtual void setPositionOfPreviousForwarder(const Coord& positionOfPreviousForwarder);
    virtual Coord& getPositionOfCurrentNode();
    virtual const Coord& getPositionOfCurrentNode() const {return const_cast<anchor*>(this)->getPositionOfCurrentNode();}
    virtual void setPositionOfCurrentNode(const Coord& positionOfCurrentNode);
    virtual Coord& getSpeedOfPreviousForwarder();
    virtual const Coord& getSpeedOfPreviousForwarder() const {return const_cast<anchor*>(this)->getSpeedOfPreviousForwarder();}
    virtual void setSpeedOfPreviousForwarder(const Coord& speedOfPreviousForwarder);
    virtual Coord& getSpeedOfCurrentNode();
    virtual const Coord& getSpeedOfCurrentNode() const {return const_cast<anchor*>(this)->getSpeedOfCurrentNode();}
    virtual void setSpeedOfCurrentNode(const Coord& speedOfCurrentNode);
    virtual Coord& getPreviousForwarderPosition();
    virtual Coord& getCurrentNodePosition();
   // virtual const Coord& getPosition() const {return const_cast<anchor*>(this)->getPosition();}
    virtual void setPreviousForwarderPosition(const Coord& position);
    virtual void setCurrentNodePosition(const Coord& position);
    virtual std::string& getPreviousForwarderHostName();
    virtual void setPreviousForwarderHostName(std::string& PreviousForwarderHostName);
    virtual std::string& getCurrentHostName();
    virtual void setPosition(const Coord& forposition,const Coord& curposition);
    virtual void setCurrentHostName(std::string& CurrentHostName);
    virtual double& getPreviousForwarderAngel();
    virtual void setPreviousForwarderAngel(double& previousForwarderAngel);
    virtual double& getCurrentForwarderAngel();
    virtual void setCurrentForwarderAngel(double& currentForwarderAngel);
};
#endif /* RBVTRPACKET_H_ */
