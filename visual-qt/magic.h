#ifndef MAGIC_H
#define MAGIC_H

#define LINK_OBJECT(FROM, TO) protected:\
    FROM * _##FROM;\
    public:\
    virtual TO * set##FROM(FROM * _new##FROM) {\
        _##FROM = _new##FROM;\
        return this;\
    }\
    FROM * get##FROM() {\
        return _##FROM;\
    }

#define ADD_FIELD(CLASS, TYPE, NAME) protected:\
    TYPE _field_##NAME; \
    bool _field_##NAME##_updated = false;\
    public:\
        virtual TYPE get##NAME () const\
{\
    return this->_field_##NAME;\
}\
        virtual CLASS * set##NAME(TYPE NAME)\
{\
    this->_field_##NAME = NAME;\
    this->_field_##NAME##_updated = true;\
    return this;\
}

#define ADD_FIELD_VAL(CLASS, TYPE, NAME, VALUE) protected:\
    TYPE _field_##NAME = VALUE; \
    bool _field_##NAME##_updated = false;\
    public:\
        virtual TYPE get##NAME () const\
{\
    return this->_field_##NAME;\
}\
        virtual CLASS * set##NAME(const TYPE NAME)\
{\
    this->_field_##NAME = NAME;\
    this->_field_##NAME##_updated = true;\
    return this;\
}

#define ADD_DATE_FIELD(CLASS, NAME) protected:\
    ADD_FIELD(CLASS, QDateTime *, NAME)\
    public:\
        virtual uint get##NAME##TimeStamp() const {return this->_field_##NAME->toTime_t();}\
        virtual CLASS * set##NAME(uint timestamp) {\
    QDateTime * date = new QDateTime();\
    date->setTime_t(timestamp);\
    return this->set##NAME(date);\
    }

#define ADD_DYN_FIELD(CLASS, TYPE, NAME) protected:\
    TYPE _field_##NAME; \
    bool _field_##NAME##_updated;\
    virtual public:\
        TYPE get##NAME ()\
{\
    return this->_field_##NAME;\
}\
        virtual CLASS * set##NAME(TYPE NAME)\
{\
    this->_field_##NAME = NAME;\
    this->_field_##NAME##_updated = true;\
    return this;\
}

#endif // MAGIC_H
