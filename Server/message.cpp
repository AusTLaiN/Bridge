#include "message.h"

using namespace bridge_server;

Message::Message(Command& cmd, DataObjectPtr dataObj) : m_dataObj(dataObj), m_cmd(cmd)
{
}

Message::Message(const QJsonObject &json) : m_dataObj(Q_NULLPTR), m_cmd()
{
    this->fromJson(json);
}

QJsonObject Message::toJson()
{
    QJsonObject jObj;

    jObj["dataObject"] = m_dataObj->toJson();
    jObj["action"] = m_cmd.getAction();

    return jObj;
}

void Message::fromJson(const QJsonObject &json)
{
    m_cmd = Command(static_cast<Command::ACTION>(json["action"].toInt()));
    m_dataObj = DataObjectFactory::getInnerDataObject(m_cmd, json["DataObject"].toObject());
}
