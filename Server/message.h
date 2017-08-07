#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include "command.h"
#include "DataObjects/dataobject.h"
#include "dataobjectfactory.h"

namespace bridge_server {

class Message  : public Serializable
{
    Command m_cmd; // instead header
    DataObjectPtr m_dataObj;

public:
    Message(Command& cmd, DataObjectPtr dataObj);
    Message(const QJsonObject &json);

    virtual QJsonObject toJson();
    virtual void fromJson(const QJsonObject &json);
};

} // bridge_server

#endif // MESSAGE_H
