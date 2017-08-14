#include "message.h"

using namespace bridge_server;

Message::Message(Command::ACTION action, DataObject* dataObj) : m_dataObj(dataObj), m_action(action)
{
}

Message::Message(const QString& mes) : m_dataObj(Q_NULLPTR), m_action(Command::ACTION::UndefinedAction)
{
    QJsonObject json;
    QJsonDocument doc = QJsonDocument::fromJson(mes.toUtf8());

    if(!doc.isNull())
    {
        if(doc.isObject())
            json = doc.object();
        else
            qDebug() << "Document is not an object" << endl;
    }
    else
        qDebug() << "Invalid JSON...\n" << mes << endl;

    this->fromJson(json);
}

QJsonObject Message::toJson()
{
    QJsonObject jObj;

    jObj["dataobject"] = m_dataObj->toJson();
    jObj["action"] = m_action;

    return jObj;
}

void Message::fromJson(const QJsonObject &json)
{
    //!!!!!!!!!if(json)
    m_action = static_cast<Command::ACTION>(json["action"].toInt());
    m_dataObj.reset(DataObjectFactory::getInnerDataObject(m_action, json["dataobject"].toObject()));
    //else
    //    qDebug() <<
}

Command::ACTION Message::getAction()
{
    return m_action;
}

DataObject* Message::getDataObject()
{
    return m_dataObj.data();
}
