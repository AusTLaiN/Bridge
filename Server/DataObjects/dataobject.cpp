#include "dataobject.h"

using namespace bridge_game;
using namespace bridge_server;

// Base class DataObject
DataObject::DataObject()
    : Serializable(), m_errors(), m_player(Q_NULLPTR), m_state(true)
{
}

DataObject::~DataObject()
{
    qDebug() << "Data object destructor called";
}

DataObject::DataObject(const QJsonObject& json) : DataObject()
{
    fromJson(json);
}

void DataObject::setPlayer(bridge_game::PlayerPtr& pl)
{
    m_player = pl;
}

void DataObject::setState(bool state)
{
    m_state = state;
}

PlayerPtr& DataObject::getPlayer()
{
    return m_player;
}

bool DataObject::getState()
{
    return m_state;
}

bool DataObject::isValid()
{
    return m_state && !m_player.isNull() && m_player->getId() > 0;
}

QString DataObject::toString()
{
    return QString("DataObject");
}

QJsonObject DataObject::toJson()
{
    QJsonObject json;

    json["state"] = m_state && hasJsonError();
    if(this->isValid())
        json["player"] = Player::serialize(m_player);
    else
    {
        qDebug() << "DataObject::toJson: Invalid DataObject";
        json["player"] = QJsonObject();
    }

    json["name"] = toString();

    return json;
}

void DataObject::fromJson(const QJsonObject &json)
{
    if(!json["state"].isUndefined() && json["state"].isBool())
        m_state = json["state"].toBool();
    else
        addJsonError("state");

    if(!json["player"].isUndefined() && json["player"].isObject())
        m_player = Player::deserialize(json["player"].toObject());
    else
        addJsonError("player");

    hasJsonError(true);
}

bool DataObject::hasJsonError(bool printErrors) const
{
    if(!m_errors.isEmpty())
    {
        if(printErrors)
            for(auto it : m_errors)
                qDebug() << it << endl;

        return true;
    }

    return false;
}

void DataObject::clearErrorStack()
{
    m_errors.clear();
    setState(true);
}

void DataObject::addJsonError(const QString& err)
{
    m_errors << toString() + "::fromJson: [" + err + "] node is undefined or has invalid type";
    setState(false);
}
