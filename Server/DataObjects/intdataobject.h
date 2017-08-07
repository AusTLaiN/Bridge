#ifndef INTDATAOBJECT_H
#define INTDATAOBJECT_H

#include "dataobject.h"

namespace bridge_server {

class IntDataObject : public DataObject
{
    int m_value;
public:
    IntDataObject();
    IntDataObject(const QJsonObject& json);

    virtual QString toString() override;
    virtual QJsonObject toJson() override;
    virtual void fromJson(const QJsonObject &json) override;
};

}


#endif // INTDATAOBJECT_H
