//
// Generated file, do not edit! Created by opp_msgc 4.5 from networklayer/routing/carRouting/carRouting.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "carRouting_msg.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(carBeacon);

carBeacon::carBeacon(const char *name, int kind) : ::cPacket(name,kind)
{
}

carBeacon::carBeacon(const carBeacon& other) : ::cPacket(other)
{
    copy(other);
}

carBeacon::~carBeacon()
{
}

carBeacon& carBeacon::operator=(const carBeacon& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void carBeacon::copy(const carBeacon& other)
{
    this->address_var = other.address_var;
    this->speed_var = other.speed_var;
    this->position_var = other.position_var;
}

void carBeacon::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->address_var);
    doPacking(b,this->speed_var);
    doPacking(b,this->position_var);
}

void carBeacon::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->address_var);
    doUnpacking(b,this->speed_var);
    doUnpacking(b,this->position_var);
}

IPvXAddress& carBeacon::getAddress()
{
    return address_var;
}

void carBeacon::setAddress(const IPvXAddress& address)
{
    this->address_var = address;
}

Coord& carBeacon::getSpeed()
{
    return speed_var;
}

void carBeacon::setSpeed(const Coord& speed)
{
    this->speed_var = speed;
}

Coord& carBeacon::getPosition()
{
    return position_var;
}

void carBeacon::setPosition(const Coord& position)
{
    this->position_var = position;
}

class carBeaconDescriptor : public cClassDescriptor
{
  public:
    carBeaconDescriptor();
    virtual ~carBeaconDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(carBeaconDescriptor);

carBeaconDescriptor::carBeaconDescriptor() : cClassDescriptor("carBeacon", "cPacket")
{
}

carBeaconDescriptor::~carBeaconDescriptor()
{
}

bool carBeaconDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<carBeacon *>(obj)!=NULL;
}

const char *carBeaconDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int carBeaconDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int carBeaconDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *carBeaconDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "address",
        "speed",
        "position",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int carBeaconDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "address")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "speed")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "position")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *carBeaconDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "IPvXAddress",
        "Coord",
        "Coord",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *carBeaconDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int carBeaconDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    carBeacon *pp = (carBeacon *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string carBeaconDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    carBeacon *pp = (carBeacon *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getAddress(); return out.str();}
        case 1: {std::stringstream out; out << pp->getSpeed(); return out.str();}
        case 2: {std::stringstream out; out << pp->getPosition(); return out.str();}
        default: return "";
    }
}

bool carBeaconDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    carBeacon *pp = (carBeacon *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *carBeaconDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(IPvXAddress));
        case 1: return opp_typename(typeid(Coord));
        case 2: return opp_typename(typeid(Coord));
        default: return NULL;
    };
}

void *carBeaconDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    carBeacon *pp = (carBeacon *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getAddress()); break;
        case 1: return (void *)(&pp->getSpeed()); break;
        case 2: return (void *)(&pp->getPosition()); break;
        default: return NULL;
    }
}

Register_Class(PGB);

PGB::PGB(const char *name, int kind) : ::cPacket(name,kind)
{
    this->pgbCounter_var = 0;
    this->travelTime_var = 0;
    this->numOfHops_var = 0;
    this->averageNumOfNeighbors_var = 0;
    this->minimumNumOfNeighbors_var = 0;
    this->seqNum_var = 0;
    //this->aSetOfAnchorPoints_var = NULL;
}

PGB::PGB(const PGB& other) : ::cPacket(other)
{
    copy(other);
}

PGB::~PGB()
{
}

PGB& PGB::operator=(const PGB& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void PGB::copy(const PGB& other)
{
    this->originatorAddress_var = other.originatorAddress_var;
    this->destAddress_var = other.destAddress_var;
    this->previousForwarderSpeed_var = other.previousForwarderSpeed_var;
    this->previousForwarderPosition_var = other.previousForwarderPosition_var;
    this->pgbCounter_var = other.pgbCounter_var;
    this->travelTime_var = other.travelTime_var;
    this->numOfHops_var = other.numOfHops_var;
    this->averageNumOfNeighbors_var = other.averageNumOfNeighbors_var;
    this->minimumNumOfNeighbors_var = other.minimumNumOfNeighbors_var;
    this->originatorPosition_var = other.originatorPosition_var;
    this->originatorSpeed_var = other.originatorSpeed_var;
    this->seqNum_var = other.seqNum_var;
    this->aSetOfAnchorPoints_var = other.aSetOfAnchorPoints_var;
}

void PGB::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->originatorAddress_var);
    doPacking(b,this->destAddress_var);
    doPacking(b,this->previousForwarderSpeed_var);
    doPacking(b,this->previousForwarderPosition_var);
    doPacking(b,this->pgbCounter_var);
    doPacking(b,this->travelTime_var);
    doPacking(b,this->numOfHops_var);
    doPacking(b,this->averageNumOfNeighbors_var);
    doPacking(b,this->minimumNumOfNeighbors_var);
    doPacking(b,this->originatorPosition_var);
    doPacking(b,this->originatorSpeed_var);
    doPacking(b,this->seqNum_var);
    doPacking(b,this->aSetOfAnchorPoints_var);
}

void PGB::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->originatorAddress_var);
    doUnpacking(b,this->destAddress_var);
    doUnpacking(b,this->previousForwarderSpeed_var);
    doUnpacking(b,this->previousForwarderPosition_var);
    doUnpacking(b,this->pgbCounter_var);
    doUnpacking(b,this->travelTime_var);
    doUnpacking(b,this->numOfHops_var);
    doUnpacking(b,this->averageNumOfNeighbors_var);
    doUnpacking(b,this->minimumNumOfNeighbors_var);
    doUnpacking(b,this->originatorPosition_var);
    doUnpacking(b,this->originatorSpeed_var);
    doUnpacking(b,this->seqNum_var);
    doUnpacking(b,this->aSetOfAnchorPoints_var);
}

IPvXAddress& PGB::getOriginatorAddress()
{
    return originatorAddress_var;
}

void PGB::setOriginatorAddress(const IPvXAddress& originatorAddress)
{
    this->originatorAddress_var = originatorAddress;
}

IPvXAddress& PGB::getDestAddress()
{
    return destAddress_var;
}

void PGB::setDestAddress(const IPvXAddress& destAddress)
{
    this->destAddress_var = destAddress;
}

Coord& PGB::getPreviousForwarderSpeed()
{
    return previousForwarderSpeed_var;
}

void PGB::setPreviousForwarderSpeed(const Coord& previousForwarderSpeed)
{
    this->previousForwarderSpeed_var = previousForwarderSpeed;
}

Coord& PGB::getPreviousForwarderPosition()
{
    return previousForwarderPosition_var;
}

void PGB::setPreviousForwarderPosition(const Coord& previousForwarderPosition)
{
    this->previousForwarderPosition_var = previousForwarderPosition;
}

unsigned int PGB::getPgbCounter() const
{
    return pgbCounter_var;
}

void PGB::setPgbCounter(unsigned int pgbCounter)
{
    this->pgbCounter_var = pgbCounter;
}

simtime_t PGB::getTravelTime() const
{
    return travelTime_var;
}

void PGB::setTravelTime(simtime_t travelTime)
{
    this->travelTime_var = travelTime;
}

unsigned int PGB::getNumOfHops() const
{
    return numOfHops_var;
}

void PGB::setNumOfHops(unsigned int numOfHops)
{
    this->numOfHops_var = numOfHops;
}

unsigned int PGB::getAverageNumOfNeighbors() const
{
    return averageNumOfNeighbors_var;
}

void PGB::setAverageNumOfNeighbors(unsigned int averageNumOfNeighbors)
{
    this->averageNumOfNeighbors_var = averageNumOfNeighbors;
}

unsigned int PGB::getMinimumNumOfNeighbors() const
{
    return minimumNumOfNeighbors_var;
}

void PGB::setMinimumNumOfNeighbors(unsigned int minimumNumOfNeighbors)
{
    this->minimumNumOfNeighbors_var = minimumNumOfNeighbors;
}

Coord& PGB::getOriginatorPosition()
{
    return originatorPosition_var;
}

void PGB::setOriginatorPosition(const Coord& originatorPosition)
{
    this->originatorPosition_var = originatorPosition;
}

Coord& PGB::getOriginatorSpeed()
{
    return originatorSpeed_var;
}

void PGB::setOriginatorSpeed(const Coord& originatorSpeed)
{
    this->originatorSpeed_var = originatorSpeed;
}

unsigned int PGB::getSeqNum() const
{
    return seqNum_var;
}

void PGB::setSeqNum(unsigned int seqNum)
{
    this->seqNum_var = seqNum;
}

std::vector<anchor> PGB::getASetOfAnchorPoints() const
{
    return aSetOfAnchorPoints_var;
}

void PGB::setASetOfAnchorPoints(std::vector<anchor> aSetOfAnchorPoints)
{
    this->aSetOfAnchorPoints_var = aSetOfAnchorPoints;
}

class PGBDescriptor : public cClassDescriptor
{
  public:
    PGBDescriptor();
    virtual ~PGBDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(PGBDescriptor);

PGBDescriptor::PGBDescriptor() : cClassDescriptor("PGB", "cPacket")
{
}

PGBDescriptor::~PGBDescriptor()
{
}

bool PGBDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<PGB *>(obj)!=NULL;
}

const char *PGBDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int PGBDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 13+basedesc->getFieldCount(object) : 13;
}

unsigned int PGBDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<13) ? fieldTypeFlags[field] : 0;
}

const char *PGBDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "originatorAddress",
        "destAddress",
        "previousForwarderSpeed",
        "previousForwarderPosition",
        "pgbCounter",
        "travelTime",
        "numOfHops",
        "averageNumOfNeighbors",
        "minimumNumOfNeighbors",
        "originatorPosition",
        "originatorSpeed",
        "seqNum",
        "aSetOfAnchorPoints",
    };
    return (field>=0 && field<13) ? fieldNames[field] : NULL;
}

int PGBDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "originatorAddress")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddress")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "previousForwarderSpeed")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "previousForwarderPosition")==0) return base+3;
    if (fieldName[0]=='p' && strcmp(fieldName, "pgbCounter")==0) return base+4;
    if (fieldName[0]=='t' && strcmp(fieldName, "travelTime")==0) return base+5;
    if (fieldName[0]=='n' && strcmp(fieldName, "numOfHops")==0) return base+6;
    if (fieldName[0]=='a' && strcmp(fieldName, "averageNumOfNeighbors")==0) return base+7;
    if (fieldName[0]=='m' && strcmp(fieldName, "minimumNumOfNeighbors")==0) return base+8;
    if (fieldName[0]=='o' && strcmp(fieldName, "originatorPosition")==0) return base+9;
    if (fieldName[0]=='o' && strcmp(fieldName, "originatorSpeed")==0) return base+10;
    if (fieldName[0]=='s' && strcmp(fieldName, "seqNum")==0) return base+11;
    if (fieldName[0]=='a' && strcmp(fieldName, "aSetOfAnchorPoints")==0) return base+12;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *PGBDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "IPvXAddress",
        "IPvXAddress",
        "Coord",
        "Coord",
        "unsigned int",
        "simtime_t",
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "Coord",
        "Coord",
        "unsigned int",
        "unsigned int",
    };
    return (field>=0 && field<13) ? fieldTypeStrings[field] : NULL;
}

const char *PGBDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int PGBDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    PGB *pp = (PGB *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string PGBDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    PGB *pp = (PGB *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getOriginatorAddress(); return out.str();}
        case 1: {std::stringstream out; out << pp->getDestAddress(); return out.str();}
        case 2: {std::stringstream out; out << pp->getPreviousForwarderSpeed(); return out.str();}
        case 3: {std::stringstream out; out << pp->getPreviousForwarderPosition(); return out.str();}
        case 4: return ulong2string(pp->getPgbCounter());
        case 5: return double2string(pp->getTravelTime());
        case 6: return ulong2string(pp->getNumOfHops());
        case 7: return ulong2string(pp->getAverageNumOfNeighbors());
        case 8: return ulong2string(pp->getMinimumNumOfNeighbors());
        case 9: {std::stringstream out; out << pp->getOriginatorPosition(); return out.str();}
        case 10: {std::stringstream out; out << pp->getOriginatorSpeed(); return out.str();}
        case 11: return ulong2string(pp->getSeqNum());
        //case 12: return ulong2string(pp->getASetOfAnchorPoints());
        default: return "";
    }
}

bool PGBDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    PGB *pp = (PGB *)object; (void)pp;
    switch (field) {
        case 4: pp->setPgbCounter(string2ulong(value)); return true;
        case 5: pp->setTravelTime(string2double(value)); return true;
        case 6: pp->setNumOfHops(string2ulong(value)); return true;
        case 7: pp->setAverageNumOfNeighbors(string2ulong(value)); return true;
        case 8: pp->setMinimumNumOfNeighbors(string2ulong(value)); return true;
        case 11: pp->setSeqNum(string2ulong(value)); return true;
        //case 12: pp->setASetOfAnchorPoints(string2ulong(value)); return true;
        default: return false;
    }
}

const char *PGBDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(IPvXAddress));
        case 1: return opp_typename(typeid(IPvXAddress));
        case 2: return opp_typename(typeid(Coord));
        case 3: return opp_typename(typeid(Coord));
        case 9: return opp_typename(typeid(Coord));
        case 10: return opp_typename(typeid(Coord));
        default: return NULL;
    };
}

void *PGBDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    PGB *pp = (PGB *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getOriginatorAddress()); break;
        case 1: return (void *)(&pp->getDestAddress()); break;
        case 2: return (void *)(&pp->getPreviousForwarderSpeed()); break;
        case 3: return (void *)(&pp->getPreviousForwarderPosition()); break;
        case 9: return (void *)(&pp->getOriginatorPosition()); break;
        case 10: return (void *)(&pp->getOriginatorSpeed()); break;
        default: return NULL;
    }
}

Register_Class(AGF);

AGF::AGF(const char *name, int kind) : ::cPacket(name,kind)
{
    this->travelTime_var = 0;
    this->numOfHops_var = 0;
    this->averageNumOfNeighbors_var = 0;
    this->minimumNumOfNeighbors_var = 0;
    //this->aSetOfAnchorPoints_var = NULL;
    //this->copyOfASetOfAnchorPoints_var = NULL;
}

AGF::AGF(const AGF& other) : ::cPacket(other)
{
    copy(other);
}

AGF::~AGF()
{
}

AGF& AGF::operator=(const AGF& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void AGF::copy(const AGF& other)
{
    this->originatorAddress_var = other.originatorAddress_var;
    this->destAddress_var = other.destAddress_var;
    this->travelTime_var = other.travelTime_var;
    this->numOfHops_var = other.numOfHops_var;
    this->averageNumOfNeighbors_var = other.averageNumOfNeighbors_var;
    this->minimumNumOfNeighbors_var = other.minimumNumOfNeighbors_var;
    this->destPosition_var = other.destPosition_var;
    this->destSpeed_var = other.destSpeed_var;
    this->aSetOfAnchorPoints_var = other.aSetOfAnchorPoints_var;
    this->copyOfASetOfAnchorPoints_var = other.copyOfASetOfAnchorPoints_var;
}

void AGF::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->originatorAddress_var);
    doPacking(b,this->destAddress_var);
    doPacking(b,this->travelTime_var);
    doPacking(b,this->numOfHops_var);
    doPacking(b,this->averageNumOfNeighbors_var);
    doPacking(b,this->minimumNumOfNeighbors_var);
    doPacking(b,this->destPosition_var);
    doPacking(b,this->destSpeed_var);
    doPacking(b,this->aSetOfAnchorPoints_var);
    doPacking(b,this->copyOfASetOfAnchorPoints_var);
}

void AGF::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->originatorAddress_var);
    doUnpacking(b,this->destAddress_var);
    doUnpacking(b,this->travelTime_var);
    doUnpacking(b,this->numOfHops_var);
    doUnpacking(b,this->averageNumOfNeighbors_var);
    doUnpacking(b,this->minimumNumOfNeighbors_var);
    doUnpacking(b,this->destPosition_var);
    doUnpacking(b,this->destSpeed_var);
    doUnpacking(b,this->aSetOfAnchorPoints_var);
    doUnpacking(b,this->copyOfASetOfAnchorPoints_var);
}

IPvXAddress& AGF::getOriginatorAddress()
{
    return originatorAddress_var;
}

void AGF::setOriginatorAddress(const IPvXAddress& originatorAddress)
{
    this->originatorAddress_var = originatorAddress;
}

IPvXAddress& AGF::getDestAddress()
{
    return destAddress_var;
}

void AGF::setDestAddress(const IPvXAddress& destAddress)
{
    this->destAddress_var = destAddress;
}

simtime_t AGF::getTravelTime() const
{
    return travelTime_var;
}

void AGF::setTravelTime(simtime_t travelTime)
{
    this->travelTime_var = travelTime;
}

unsigned int AGF::getNumOfHops() const
{
    return numOfHops_var;
}

void AGF::setNumOfHops(unsigned int numOfHops)
{
    this->numOfHops_var = numOfHops;
}

unsigned int AGF::getAverageNumOfNeighbors() const
{
    return averageNumOfNeighbors_var;
}

void AGF::setAverageNumOfNeighbors(unsigned int averageNumOfNeighbors)
{
    this->averageNumOfNeighbors_var = averageNumOfNeighbors;
}

unsigned int AGF::getMinimumNumOfNeighbors() const
{
    return minimumNumOfNeighbors_var;
}

void AGF::setMinimumNumOfNeighbors(unsigned int minimumNumOfNeighbors)
{
    this->minimumNumOfNeighbors_var = minimumNumOfNeighbors;
}

Coord& AGF::getDestPosition()
{
    return destPosition_var;
}

void AGF::setDestPosition(const Coord& destPosition)
{
    this->destPosition_var = destPosition;
}

Coord& AGF::getDestSpeed()
{
    return destSpeed_var;
}

void AGF::setDestSpeed(const Coord& destSpeed)
{
    this->destSpeed_var = destSpeed;
}

std::vector<anchor> AGF::getASetOfAnchorPoints() const
{
    return aSetOfAnchorPoints_var;
}

void AGF::setASetOfAnchorPoints(std::vector<anchor> aSetOfAnchorPoints)
{
    this->aSetOfAnchorPoints_var = aSetOfAnchorPoints;
}

void AGF::makeACopy()
{
    copyOfASetOfAnchorPoints_var = aSetOfAnchorPoints_var;
}

std::vector<anchor> AGF::getCopyOfASetOfAnchorPoints() const
{
    return copyOfASetOfAnchorPoints_var;
}

void AGF::setCopyOfASetOfAnchorPoints(std::vector<anchor> copyOfASetOfAnchorPoints)
{
    this->copyOfASetOfAnchorPoints_var = copyOfASetOfAnchorPoints;
}

class AGFDescriptor : public cClassDescriptor
{
  public:
    AGFDescriptor();
    virtual ~AGFDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(AGFDescriptor);

AGFDescriptor::AGFDescriptor() : cClassDescriptor("AGF", "cPacket")
{
}

AGFDescriptor::~AGFDescriptor()
{
}

bool AGFDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<AGF *>(obj)!=NULL;
}

const char *AGFDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int AGFDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 10+basedesc->getFieldCount(object) : 10;
}

unsigned int AGFDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<10) ? fieldTypeFlags[field] : 0;
}

const char *AGFDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "originatorAddress",
        "destAddress",
        "travelTime",
        "numOfHops",
        "averageNumOfNeighbors",
        "minimumNumOfNeighbors",
        "destPosition",
        "destSpeed",
        "aSetOfAnchorPoints",
        "copyOfASetOfAnchorPoints",
    };
    return (field>=0 && field<10) ? fieldNames[field] : NULL;
}

int AGFDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "originatorAddress")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddress")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "travelTime")==0) return base+2;
    if (fieldName[0]=='n' && strcmp(fieldName, "numOfHops")==0) return base+3;
    if (fieldName[0]=='a' && strcmp(fieldName, "averageNumOfNeighbors")==0) return base+4;
    if (fieldName[0]=='m' && strcmp(fieldName, "minimumNumOfNeighbors")==0) return base+5;
    if (fieldName[0]=='d' && strcmp(fieldName, "destPosition")==0) return base+6;
    if (fieldName[0]=='d' && strcmp(fieldName, "destSpeed")==0) return base+7;
    if (fieldName[0]=='a' && strcmp(fieldName, "aSetOfAnchorPoints")==0) return base+8;
    if (fieldName[0]=='c' && strcmp(fieldName, "copyOfASetOfAnchorPoints")==0) return base+9;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *AGFDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "IPvXAddress",
        "IPvXAddress",
        "simtime_t",
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "Coord",
        "Coord",
        "unsigned int",
        "unsigned int",
    };
    return (field>=0 && field<10) ? fieldTypeStrings[field] : NULL;
}

const char *AGFDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int AGFDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    AGF *pp = (AGF *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string AGFDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    AGF *pp = (AGF *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getOriginatorAddress(); return out.str();}
        case 1: {std::stringstream out; out << pp->getDestAddress(); return out.str();}
        case 2: return double2string(pp->getTravelTime());
        case 3: return ulong2string(pp->getNumOfHops());
        case 4: return ulong2string(pp->getAverageNumOfNeighbors());
        case 5: return ulong2string(pp->getMinimumNumOfNeighbors());
        case 6: {std::stringstream out; out << pp->getDestPosition(); return out.str();}
        case 7: {std::stringstream out; out << pp->getDestSpeed(); return out.str();}
        //case 8: return ulong2string(pp->getASetOfAnchorPoints());
        //case 9: return ulong2string(pp->getCopyOfASetOfAnchorPoints());
        default: return "";
    }
}

bool AGFDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    AGF *pp = (AGF *)object; (void)pp;
    switch (field) {
        case 2: pp->setTravelTime(string2double(value)); return true;
        case 3: pp->setNumOfHops(string2ulong(value)); return true;
        case 4: pp->setAverageNumOfNeighbors(string2ulong(value)); return true;
        case 5: pp->setMinimumNumOfNeighbors(string2ulong(value)); return true;
        //case 8: pp->setASetOfAnchorPoints(string2ulong(value)); return true;
        //case 9: pp->setCopyOfASetOfAnchorPoints(string2ulong(value)); return true;
        default: return false;
    }
}

const char *AGFDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(IPvXAddress));
        case 1: return opp_typename(typeid(IPvXAddress));
        case 6: return opp_typename(typeid(Coord));
        case 7: return opp_typename(typeid(Coord));
        default: return NULL;
    };
}

void *AGFDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    AGF *pp = (AGF *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getOriginatorAddress()); break;
        case 1: return (void *)(&pp->getDestAddress()); break;
        case 6: return (void *)(&pp->getDestPosition()); break;
        case 7: return (void *)(&pp->getDestSpeed()); break;
        default: return NULL;
    }
}

Register_Class(stGuard);

stGuard::stGuard(const char *name, int kind) : ::cPacket(name,kind)
{
    this->stGuardCounter_var = 0;
    this->stGuardTTL_var = 0;
    this->guardedRadius_var = 0;
}

stGuard::stGuard(const stGuard& other) : ::cPacket(other)
{
    copy(other);
}

stGuard::~stGuard()
{
}

stGuard& stGuard::operator=(const stGuard& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void stGuard::copy(const stGuard& other)
{
    this->activatorAddress_var = other.activatorAddress_var;
    this->stGuardCounter_var = other.stGuardCounter_var;
    this->stGuardTTL_var = other.stGuardTTL_var;
    this->guardedPosition_var = other.guardedPosition_var;
    this->guardedRadius_var = other.guardedRadius_var;
}

void stGuard::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->activatorAddress_var);
    doPacking(b,this->stGuardCounter_var);
    doPacking(b,this->stGuardTTL_var);
    doPacking(b,this->guardedPosition_var);
    doPacking(b,this->guardedRadius_var);
}

void stGuard::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->activatorAddress_var);
    doUnpacking(b,this->stGuardCounter_var);
    doUnpacking(b,this->stGuardTTL_var);
    doUnpacking(b,this->guardedPosition_var);
    doUnpacking(b,this->guardedRadius_var);
}

IPvXAddress& stGuard::getActivatorAddress()
{
    return activatorAddress_var;
}

void stGuard::setActivatorAddress(const IPvXAddress& activatorAddress)
{
    this->activatorAddress_var = activatorAddress;
}

unsigned int stGuard::getStGuardCounter() const
{
    return stGuardCounter_var;
}

void stGuard::setStGuardCounter(unsigned int stGuardCounter)
{
    this->stGuardCounter_var = stGuardCounter;
}

unsigned int stGuard::getStGuardTTL() const
{
    return stGuardTTL_var;
}

void stGuard::setStGuardTTL(unsigned int stGuardTTL)
{
    this->stGuardTTL_var = stGuardTTL;
}

Coord& stGuard::getGuardedPosition()
{
    return guardedPosition_var;
}

void stGuard::setGuardedPosition(const Coord& guardedPosition)
{
    this->guardedPosition_var = guardedPosition;
}

double stGuard::getGuardedRadius() const
{
    return guardedRadius_var;
}

void stGuard::setGuardedRadius(double guardedRadius)
{
    this->guardedRadius_var = guardedRadius;
}

class stGuardDescriptor : public cClassDescriptor
{
  public:
    stGuardDescriptor();
    virtual ~stGuardDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(stGuardDescriptor);

stGuardDescriptor::stGuardDescriptor() : cClassDescriptor("stGuard", "cPacket")
{
}

stGuardDescriptor::~stGuardDescriptor()
{
}

bool stGuardDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<stGuard *>(obj)!=NULL;
}

const char *stGuardDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int stGuardDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int stGuardDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *stGuardDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "activatorAddress",
        "stGuardCounter",
        "stGuardTTL",
        "guardedPosition",
        "guardedRadius",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int stGuardDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "activatorAddress")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "stGuardCounter")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "stGuardTTL")==0) return base+2;
    if (fieldName[0]=='g' && strcmp(fieldName, "guardedPosition")==0) return base+3;
    if (fieldName[0]=='g' && strcmp(fieldName, "guardedRadius")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *stGuardDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "IPvXAddress",
        "unsigned int",
        "unsigned int",
        "Coord",
        "double",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *stGuardDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int stGuardDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    stGuard *pp = (stGuard *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string stGuardDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    stGuard *pp = (stGuard *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getActivatorAddress(); return out.str();}
        case 1: return ulong2string(pp->getStGuardCounter());
        case 2: return ulong2string(pp->getStGuardTTL());
        case 3: {std::stringstream out; out << pp->getGuardedPosition(); return out.str();}
        case 4: return double2string(pp->getGuardedRadius());
        default: return "";
    }
}

bool stGuardDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    stGuard *pp = (stGuard *)object; (void)pp;
    switch (field) {
        case 1: pp->setStGuardCounter(string2ulong(value)); return true;
        case 2: pp->setStGuardTTL(string2ulong(value)); return true;
        case 4: pp->setGuardedRadius(string2double(value)); return true;
        default: return false;
    }
}

const char *stGuardDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(IPvXAddress));
        case 3: return opp_typename(typeid(Coord));
        default: return NULL;
    };
}

void *stGuardDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    stGuard *pp = (stGuard *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getActivatorAddress()); break;
        case 3: return (void *)(&pp->getGuardedPosition()); break;
        default: return NULL;
    }
}

Register_Class(trGuard);

trGuard::trGuard(const char *name, int kind) : ::cPacket(name,kind)
{
    this->trGuardCounter_var = 0;
    this->trGuardTTL_var = 0;
    this->guardedRadius_var = 0;
}

trGuard::trGuard(const trGuard& other) : ::cPacket(other)
{
    copy(other);
}

trGuard::~trGuard()
{
}

trGuard& trGuard::operator=(const trGuard& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void trGuard::copy(const trGuard& other)
{
    this->activatorAddress_var = other.activatorAddress_var;
    this->trGuardCounter_var = other.trGuardCounter_var;
    this->trGuardTTL_var = other.trGuardTTL_var;
    this->guardedPosition_var = other.guardedPosition_var;
    this->guardedRadius_var = other.guardedRadius_var;
    this->activatorSpeed_var = other.activatorSpeed_var;
}

void trGuard::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->activatorAddress_var);
    doPacking(b,this->trGuardCounter_var);
    doPacking(b,this->trGuardTTL_var);
    doPacking(b,this->guardedPosition_var);
    doPacking(b,this->guardedRadius_var);
    doPacking(b,this->activatorSpeed_var);
}

void trGuard::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->activatorAddress_var);
    doUnpacking(b,this->trGuardCounter_var);
    doUnpacking(b,this->trGuardTTL_var);
    doUnpacking(b,this->guardedPosition_var);
    doUnpacking(b,this->guardedRadius_var);
    doUnpacking(b,this->activatorSpeed_var);
}

IPvXAddress& trGuard::getActivatorAddress()
{
    return activatorAddress_var;
}

void trGuard::setActivatorAddress(const IPvXAddress& activatorAddress)
{
    this->activatorAddress_var = activatorAddress;
}

unsigned int trGuard::getTrGuardCounter() const
{
    return trGuardCounter_var;
}

void trGuard::setTrGuardCounter(unsigned int trGuardCounter)
{
    this->trGuardCounter_var = trGuardCounter;
}

unsigned int trGuard::getTrGuardTTL() const
{
    return trGuardTTL_var;
}

void trGuard::setTrGuardTTL(unsigned int trGuardTTL)
{
    this->trGuardTTL_var = trGuardTTL;
}

Coord& trGuard::getGuardedPosition()
{
    return guardedPosition_var;
}

void trGuard::setGuardedPosition(const Coord& guardedPosition)
{
    this->guardedPosition_var = guardedPosition;
}

double trGuard::getGuardedRadius() const
{
    return guardedRadius_var;
}

void trGuard::setGuardedRadius(double guardedRadius)
{
    this->guardedRadius_var = guardedRadius;
}

Coord& trGuard::getActivatorSpeed()
{
    return activatorSpeed_var;
}

void trGuard::setActivatorSpeed(const Coord& activatorSpeed)
{
    this->activatorSpeed_var = activatorSpeed;
}

class trGuardDescriptor : public cClassDescriptor
{
  public:
    trGuardDescriptor();
    virtual ~trGuardDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(trGuardDescriptor);

trGuardDescriptor::trGuardDescriptor() : cClassDescriptor("trGuard", "cPacket")
{
}

trGuardDescriptor::~trGuardDescriptor()
{
}

bool trGuardDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<trGuard *>(obj)!=NULL;
}

const char *trGuardDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int trGuardDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
}

unsigned int trGuardDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *trGuardDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "activatorAddress",
        "trGuardCounter",
        "trGuardTTL",
        "guardedPosition",
        "guardedRadius",
        "activatorSpeed",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int trGuardDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "activatorAddress")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "trGuardCounter")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "trGuardTTL")==0) return base+2;
    if (fieldName[0]=='g' && strcmp(fieldName, "guardedPosition")==0) return base+3;
    if (fieldName[0]=='g' && strcmp(fieldName, "guardedRadius")==0) return base+4;
    if (fieldName[0]=='a' && strcmp(fieldName, "activatorSpeed")==0) return base+5;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *trGuardDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "IPvXAddress",
        "unsigned int",
        "unsigned int",
        "Coord",
        "double",
        "Coord",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
}

const char *trGuardDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int trGuardDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    trGuard *pp = (trGuard *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string trGuardDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    trGuard *pp = (trGuard *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getActivatorAddress(); return out.str();}
        case 1: return ulong2string(pp->getTrGuardCounter());
        case 2: return ulong2string(pp->getTrGuardTTL());
        case 3: {std::stringstream out; out << pp->getGuardedPosition(); return out.str();}
        case 4: return double2string(pp->getGuardedRadius());
        case 5: {std::stringstream out; out << pp->getActivatorSpeed(); return out.str();}
        default: return "";
    }
}

bool trGuardDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    trGuard *pp = (trGuard *)object; (void)pp;
    switch (field) {
        case 1: pp->setTrGuardCounter(string2ulong(value)); return true;
        case 2: pp->setTrGuardTTL(string2ulong(value)); return true;
        case 4: pp->setGuardedRadius(string2double(value)); return true;
        default: return false;
    }
}

const char *trGuardDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(IPvXAddress));
        case 3: return opp_typename(typeid(Coord));
        case 5: return opp_typename(typeid(Coord));
        default: return NULL;
    };
}

void *trGuardDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    trGuard *pp = (trGuard *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getActivatorAddress()); break;
        case 3: return (void *)(&pp->getGuardedPosition()); break;
        case 5: return (void *)(&pp->getActivatorSpeed()); break;
        default: return NULL;
    }
}

Register_Class(carPacket);

carPacket::carPacket(const char *name, int kind) : ::cPacket(name,kind)
{
    //this->aSetOfAnchorPoints_var = 0;
   // this->copyOfASetOfAnchorPoints_var = 0;
}

carPacket::carPacket(const carPacket& other) : ::cPacket(other)
{
    copy(other);
}

carPacket::~carPacket()
{
}

carPacket& carPacket::operator=(const carPacket& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void carPacket::copy(const carPacket& other)
{
    this->destinationPosition_var = other.destinationPosition_var;
    this->originatorAddress_var = other.originatorAddress_var;
    this->destinationAddress_var = other.destinationAddress_var;
    this->aSetOfAnchorPoints_var = other.aSetOfAnchorPoints_var;
    this->copyOfASetOfAnchorPoints_var = other.copyOfASetOfAnchorPoints_var;
}
void carPacket::makeACopy()
{
    copyOfASetOfAnchorPoints_var = aSetOfAnchorPoints_var;
}
void carPacket::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->destinationPosition_var);
    doPacking(b,this->originatorAddress_var);
    doPacking(b,this->destinationAddress_var);
    doPacking(b,this->aSetOfAnchorPoints_var);
    doPacking(b,this->copyOfASetOfAnchorPoints_var);
}

void carPacket::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->destinationPosition_var);
    doUnpacking(b,this->originatorAddress_var);
    doUnpacking(b,this->destinationAddress_var);
    doUnpacking(b,this->aSetOfAnchorPoints_var);
    doUnpacking(b,this->copyOfASetOfAnchorPoints_var);
}

Coord& carPacket::getDestinationPosition()
{
    return destinationPosition_var;
}

void carPacket::setDestinationPosition(const Coord& destinationPosition)
{
    this->destinationPosition_var = destinationPosition;
}

IPvXAddress& carPacket::getOriginatorAddress()
{
    return originatorAddress_var;
}

void carPacket::setOriginatorAddress(const IPvXAddress& originatorAddress)
{
    this->originatorAddress_var = originatorAddress;
}

IPvXAddress& carPacket::getDestinationAddress()
{
    return destinationAddress_var;
}

void carPacket::setDestinationAddress(const IPvXAddress& destinationAddress)
{
    this->destinationAddress_var = destinationAddress;
}

std::vector<anchor> carPacket::getASetOfAnchorPoints() const
{
    return aSetOfAnchorPoints_var;
}

void carPacket::setASetOfAnchorPoints(std::vector<anchor> aSetOfAnchorPoints)
{
    this->aSetOfAnchorPoints_var = aSetOfAnchorPoints;
}

std::vector<anchor> carPacket::getCopyOfASetOfAnchorPoints() const
{
    return copyOfASetOfAnchorPoints_var;
}

void carPacket::setCopyOfASetOfAnchorPoints(std::vector<anchor> copyOfASetOfAnchorPoints)
{
    this->copyOfASetOfAnchorPoints_var = copyOfASetOfAnchorPoints;
}

class carPacketDescriptor : public cClassDescriptor
{
  public:
    carPacketDescriptor();
    virtual ~carPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(carPacketDescriptor);

carPacketDescriptor::carPacketDescriptor() : cClassDescriptor("carPacket", "cPacket")
{
}

carPacketDescriptor::~carPacketDescriptor()
{
}

bool carPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<carPacket *>(obj)!=NULL;
}

const char *carPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int carPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int carPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *carPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "destinationPosition",
        "originatorAddress",
        "destinationAddress",
        "aSetOfAnchorPoints",
        "copyOfASetOfAnchorPoints",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int carPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationPosition")==0) return base+0;
    if (fieldName[0]=='o' && strcmp(fieldName, "originatorAddress")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationAddress")==0) return base+2;
    if (fieldName[0]=='a' && strcmp(fieldName, "aSetOfAnchorPoints")==0) return base+3;
    if (fieldName[0]=='c' && strcmp(fieldName, "copyOfASetOfAnchorPoints")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *carPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "Coord",
        "IPvXAddress",
        "IPvXAddress",
        "unsigned int",
        "unsigned int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *carPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int carPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    carPacket *pp = (carPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string carPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    carPacket *pp = (carPacket *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getDestinationPosition(); return out.str();}
        case 1: {std::stringstream out; out << pp->getOriginatorAddress(); return out.str();}
        case 2: {std::stringstream out; out << pp->getDestinationAddress(); return out.str();}
       // case 3: return ulong2string(pp->getASetOfAnchorPoints());
       // case 4: return ulong2string(pp->getCopyOfASetOfAnchorPoints());
        default: return "";
    }
}

bool carPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    carPacket *pp = (carPacket *)object; (void)pp;
    switch (field) {
       // case 3: pp->setASetOfAnchorPoints(string2ulong(value)); return true;
       // case 4: pp->setCopyOfASetOfAnchorPoints(string2ulong(value)); return true;
        default: return false;
    }
}

const char *carPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(Coord));
        case 1: return opp_typename(typeid(IPvXAddress));
        case 2: return opp_typename(typeid(IPvXAddress));
        default: return NULL;
    };
}

void *carPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    carPacket *pp = (carPacket *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getDestinationPosition()); break;
        case 1: return (void *)(&pp->getOriginatorAddress()); break;
        case 2: return (void *)(&pp->getDestinationAddress()); break;
        default: return NULL;
    }
}

