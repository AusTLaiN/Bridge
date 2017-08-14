#include "intdataobject.h"

using namespace bridge_game;
using namespace bridge_server;

IntDataObject::IntDataObject()
    : DataObject(), m_value(0)
{}

IntDataObject::IntDataObject(const QJsonObject& json)
    : DataObject(), m_value(0)
{
    this->fromJson(json);
}

QString IntDataObject::toString()
{
    return QString("IntDataObject");
}

QJsonObject IntDataObject::toJson()
{
    QJsonObject jObj = DataObject::toJson();
    jObj["value"] = m_value;
    jObj["name"] = toString();

    return jObj;
}

void IntDataObject::fromJson(const QJsonObject &json)
{
    DataObject::fromJson(json);
    if(!json["value"].isUndefined() && json["value"].isDouble())
        m_value = static_cast<uint>(json["value"].toInt());
    else
        addJsonError("value");

    hasJsonError(true);
}
