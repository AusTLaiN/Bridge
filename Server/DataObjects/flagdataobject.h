#ifndef FLAGDATAOBJECT_H
#define FLAGDATAOBJECT_H

#include "dataobject.h"

namespace bridge_server {

class FlagDataObject : public DataObject
{
    bool m_flag;
public:
    FlagDataObject();
    FlagDataObject(const QJsonObject& json);

    virtual QString toString() override;
    virtual QJsonObject toJson() override;
    virtual void fromJson(const QJsonObject &json) override;
};

} // bridge_server

#endif // FLAGDATAOBJECT_H
