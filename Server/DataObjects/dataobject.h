#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QStack>
#include <QJsonObject>
#include <QDebug>

#include "global.h"
#include "serializable.h"
#include "card.h"
#include "player.h"
#include "command.h"

namespace bridge_server {

class DataObject : public bridge_game::Serializable
{
    QStack<QString> m_errors;
    bool m_state;
    bridge_game::PlayerPtr m_player;
    //QList<Command::ACTION> actionList; //!!!

public:
    DataObject();
    DataObject(const QJsonObject& json);
    virtual ~DataObject();

    void setPlayer(bridge_game::PlayerPtr& pl);
    void setState(bool state);
    bridge_game::PlayerPtr& getPlayer();
    bool getState();

    bool isValid();
    virtual QString toString();

    virtual QJsonObject toJson() override;
    virtual void fromJson(const QJsonObject &json) override;

    bool hasJsonError(bool printErrors = false) const;
    void clearErrorStack();
    void addJsonError(const QString& err);
};

} // bridge_server

#endif // DATAOBJECT_H
