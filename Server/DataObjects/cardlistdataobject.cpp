#include "cardlistdataobject.h"

using namespace bridge_game;
using namespace bridge_server;

CardListDataObject::CardListDataObject()
    : DataObject(), m_cardList()
{}

CardListDataObject::CardListDataObject(const QJsonObject& json)
    : DataObject(), m_cardList()
{
    fromJson(json);
}

QString CardListDataObject::toString()
{
    return QString("CardListDataObject");
}

QJsonObject CardListDataObject::toJson()
{
    QJsonObject jObj = DataObject::toJson();

    jObj["cardList"] = Serializable::listToJson(m_cardList, Card::serialize);
    jObj["name"] = toString();

    return jObj;
}

void CardListDataObject::fromJson(const QJsonObject &json)
{
    DataObject::fromJson(json);
    if(!json["cardList"].isUndefined() && json["cardList"].isArray())
        m_cardList = Serializable::listFromJson(m_cardList, json["cardList"].toArray(), Card::deserialize);
    else
        addJsonError("cardlist");

    hasJsonError(true);
}
