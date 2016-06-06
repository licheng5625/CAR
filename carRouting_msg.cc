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
    this->ListOfguards_var = other.ListOfguards_var;
}

void carBeacon::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->address_var);
    doPacking(b,this->speed_var);
    doPacking(b,this->position_var);
    doPacking(b,this->ListOfguards_var);
}

void carBeacon::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->address_var);
    doUnpacking(b,this->speed_var);
    doUnpacking(b,this->position_var);
    doUnpacking(b,this->ListOfguards_var);
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
std::vector <Guard> carBeacon::getListOfguards()
{
    return ListOfguards_var;
}
void carBeacon::setListOfguards(std::vector <Guard> ListOfguards)
{
    this->ListOfguards_var = ListOfguards;
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
    this->previousForwarderHostName = other.previousForwarderHostName;
    this->previousForwarderAngel = other.previousForwarderAngel;
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
    doPacking(b,this->previousForwarderHostName);
    doPacking(b,this->previousForwarderAngel);
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
    doUnpacking(b,this->previousForwarderHostName);
    doUnpacking(b,this->previousForwarderAngel);
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
std::string& PGB::getPreviousForwarderHostName()
{
    return this->previousForwarderHostName;
}

void PGB::setPreviousForwarderHostName(std::string previousForwarderHostName)
{
    this->previousForwarderHostName = previousForwarderHostName;
}
double& PGB::getPreviousForwarderAngel()
{
    return previousForwarderAngel;
}
void PGB::setPreviousForwarderAngel(double previousForwarderAngel)
{
    this->previousForwarderAngel=previousForwarderAngel;
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
    this->nexthopAddress_var=other.nexthopAddress_var;
    this->travelTime_var = other.travelTime_var;
    this->numOfHops_var = other.numOfHops_var;
    this->averageNumOfNeighbors_var = other.averageNumOfNeighbors_var;
    this->minimumNumOfNeighbors_var = other.minimumNumOfNeighbors_var;
    this->destPosition_var = other.destPosition_var;
    this->destSpeed_var = other.destSpeed_var;
    this->aSetOfAnchorPoints_var = other.aSetOfAnchorPoints_var;
    this->anchorIndex = other.anchorIndex;
}

void AGF::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->nexthopAddress_var);
    doPacking(b,this->originatorAddress_var);
    doPacking(b,this->destAddress_var);
    doPacking(b,this->travelTime_var);
    doPacking(b,this->numOfHops_var);
    doPacking(b,this->averageNumOfNeighbors_var);
    doPacking(b,this->minimumNumOfNeighbors_var);
    doPacking(b,this->destPosition_var);
    doPacking(b,this->destSpeed_var);
    doPacking(b,this->aSetOfAnchorPoints_var);
    doPacking(b,this->anchorIndex);
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
    doUnpacking(b,this->nexthopAddress_var);
    doUnpacking(b,this->anchorIndex);
}
IPvXAddress& AGF::getnexthopAddress()
{
    return nexthopAddress_var;
}

void AGF::setnexthopAddress(const IPvXAddress& nexthopAddress_var)
{
    this->nexthopAddress_var = nexthopAddress_var;
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

int AGF::getAnchorIndex()
{
    return this->anchorIndex;
}

void AGF::setAnchorIndex(int anchorIndex)
{
    this->anchorIndex = anchorIndex;
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
        "anchorindex",
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

Guard::Guard()
{
}
Guard::Guard(int ID)
{
    this->ID=ID;
}
Guard::~Guard()
{
}
int Guard::getID()
{
    return ID;
}
void Guard::setID(int ID)
{
    this-> ID=ID;
}

IPvXAddress Guard::getActivatorAddress()
{
    return activatorAddress_var;
}

void Guard::setActivatorAddress( IPvXAddress activatorAddress)
{
    this->activatorAddress_var = activatorAddress;
}

simtime_t Guard::getGuardTTL()
{
    return GuardTTL_var;
}

void Guard::setGuardTTL(simtime_t stGuardTTL)
{
    this->GuardTTL_var = stGuardTTL;
}
Coord Guard::getGuardedPosition()
{
    return guardedPosition_var;
}

void Guard::setGuardedPosition( Coord guardedPosition)
{
    this->guardedPosition_var = guardedPosition;
}
Coord Guard::getGuardedSpeed()
{
    return guardedSpeed_var;
}

void Guard::setGuardedSpeed( Coord guardedSpeed)
{
    this->guardedSpeed_var = guardedSpeed;
}
std::string Guard::getActivatorName()
{
    return activatorHostName_var;
}
void Guard::setActivatorName( std::string activatorHostName_var)
{
    this->activatorHostName_var = activatorHostName_var;
}
double Guard::getGuardedRadius()
{
    return guardedRadius_var;
}
void Guard::setGuardedRadius(double guardedRadius)
{
    this->guardedRadius_var = guardedRadius;
}

GuardType Guard::getGuardType()
{
    return guardType;
}

void Guard::setGuardType(GuardType guardType)
{
    this->guardType = guardType;
}
bool Guard::operator==( Guard  guard)
{
    if(this->guardType==guard.guardType&&this->activatorAddress_var==guard.activatorAddress_var&&this->ID==guard.ID)
        return true;
    else
        return false;
}
double Guard::getcurrentTravelingAngel()
{
    return currentTravelingAngel;
}
void Guard::setcurrentTravelingAngel(double currentTravelingAngel)
{
    this->currentTravelingAngel = currentTravelingAngel;
}
double Guard::getpreviousTravelingAngel()
{
    return previousTravelingAngel;
}

void Guard::setpreviousTravelingAngel(double previousTravelingAngel)
{
    this->previousTravelingAngel = previousTravelingAngel;
}
stGuard::stGuard(int ID)
{
    this->ID=ID;
    setGuardType(stGuardType);
}
stGuard::~stGuard()
{
}
trGuard::trGuard(int ID)
{
    this->ID=ID;
    setGuardType(trGuardType);
}
trGuard::~trGuard()
{
}
Coord trGuard::getPreviousForwarderSpeed()
{
    return previousForwarderSpeed_var;
}

void trGuard::setPreviousForwarderSpeed( Coord previousForwarderSpeed)
{
    this->previousForwarderSpeed_var = previousForwarderSpeed;
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
    this->sourcePosition_var = other.sourcePosition_var;
    this->originatorAddress_var = other.originatorAddress_var;
    this->destinationAddress_var = other.destinationAddress_var;
    this->aSetOfAnchorPoints_var = other.aSetOfAnchorPoints_var;
    this->anchorIndex = other.anchorIndex;
    this->destSpeed_var = other.destSpeed_var;
    this->travelTime_var = other.travelTime_var;
}
void carPacket::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->destinationPosition_var);
    doPacking(b,this->sourcePosition_var);
    doPacking(b,this->originatorAddress_var);
    doPacking(b,this->destinationAddress_var);
    doPacking(b,this->aSetOfAnchorPoints_var);
    doPacking(b,this->anchorIndex);
    doPacking(b,this->destSpeed_var);
    doPacking(b,this->travelTime_var);
}

void carPacket::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->sourcePosition_var);
    doUnpacking(b,this->destinationPosition_var);
    doUnpacking(b,this->originatorAddress_var);
    doUnpacking(b,this->destinationAddress_var);
    doUnpacking(b,this->aSetOfAnchorPoints_var);
    doUnpacking(b,this->anchorIndex);
    doUnpacking(b,this->destSpeed_var);
    doUnpacking(b,this->travelTime_var);
}
simtime_t carPacket::getTravelTime() const
{
    return travelTime_var;
}

void carPacket::setTravelTime(simtime_t travelTime)
{
    this->travelTime_var = travelTime;
}
Coord& carPacket::getDestSpeed()
{
    return destSpeed_var;
}
void carPacket::setDestSpeed(const Coord& destSpeed)
{
    this->destSpeed_var = destSpeed;
}
Coord& carPacket::getsourcePosition()
{
    return sourcePosition_var;
}

void carPacket::setsourcePosition(const Coord& sourcePosition)
{
    this->sourcePosition_var = sourcePosition;
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

std::vector<anchor> carPacket::getASetOfAnchorPoints()
{
    return aSetOfAnchorPoints_var;
}

void carPacket::setASetOfAnchorPoints(std::vector<anchor>& aSetOfAnchorPoints)
{
    this->aSetOfAnchorPoints_var = aSetOfAnchorPoints;
}

int carPacket::getAnchorIndex()
{
    return this->anchorIndex;
}

void carPacket::setAnchorIndex(int anchorIndex)
{
    this->anchorIndex = anchorIndex;
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

