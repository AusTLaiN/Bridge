#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QStack>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "global.h"
#include "serializable.h"
#include "card.h"
#include "player.h"

using namespace bridge_game;

namespace bridge_server {

class DataObject : public Serializable
{
    QList<QString> m_errors;
    bool m_state;
    // uint m_gameId; // ???
    bridge_game::PlayerPtr m_player;

public:
    DataObject();
    DataObject(const QJsonObject& json);

    void setPlayer(bridge_game::PlayerPtr& pl);
    void setState(bool state);
    PlayerPtr& getPlayer();
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
