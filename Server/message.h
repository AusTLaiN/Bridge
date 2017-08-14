#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include "command.h"
#include "DataObjects/dataobject.h"
#include "dataobjectfactory.h"

namespace bridge_server {

class Message  : public bridge_game::Serializable
{
    Command::ACTION m_action; // instead header
    DataObjectPtr m_dataObj;

public:
    Message(Command::ACTION action, DataObject* dataObj);
    Message(const QString& mes);

    Command::ACTION getAction();
    DataObject* getDataObject();

    virtual QJsonObject toJson();
    virtual void fromJson(const QJsonObject &json);
};

} // bridge_server

#endif // MESSAGE_H
