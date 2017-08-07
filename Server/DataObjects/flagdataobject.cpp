#include "flagdataobject.h"

using namespace bridge_game;
using namespace bridge_server;

FlagDataObject::FlagDataObject()
    : DataObject(), m_flag(false)
{}

FlagDataObject::FlagDataObject(const QJsonObject& json)
    : DataObject(), m_flag(false)
{
    this->fromJson(json);
}

QString FlagDataObject::toString()
{
    return QString("FlagDataObject");
}

QJsonObject FlagDataObject::toJson()
{
    QJsonObject jObj = DataObject::toJson();
    jObj["flag"] = m_flag;
    jObj["name"] = toString();

    return jObj;
}

void FlagDataObject::fromJson(const QJsonObject &json)
{
    DataObject::fromJson(json);
    if(!json["flag"].isUndefined() && json["flag"].isBool())
        m_flag = json["flag"].toBool();
    else
        addJsonError("flag");

    hasJsonError(true);
}
