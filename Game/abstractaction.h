#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

#include "global.h"

#include <QObject>

namespace bridge_game {

class AbstractAction : public QObject, public Serializable
{
    Q_OBJECT

public:
    enum TargetType {
        NoTarget,
        SingleTarget,
        MultipleTargets,
        Global,  
        Special,
        UndefinedTargetType
    };
    Q_ENUM(TargetType)

public:
    explicit AbstractAction(Game *game, QObject *parent = 0);
    virtual ~AbstractAction();

    Player *getOwner();
    TargetType getTargetType();
    const QList<Player*>& getTargets();
    Game* getGame();
    Card* getCard();

    bool noTargets();

    virtual QJsonObject toJson() override;
    virtual void fromJson(const QJsonObject &json) override;

public slots:
    virtual void execute() = 0;

    void setTargetType(TargetType type);

    void setTarget(PlayerPtr target, TargetType type = SingleTarget);
    void setTarget(Player *target, TargetType type = SingleTarget);

    void setTargets(const QList<PlayerPtr> &targets, TargetType type = MultipleTargets);
    void setTargets(const QList<Player *> &targets, TargetType type = MultipleTargets);

    void addTarget(PlayerPtr player);
    void addTarget(Player *player);

    void addTargets(const QList<PlayerPtr> &targets);
    void addTargets(const QList<Player *> &targets);


    void setCard(Card *card);
    void setOwner(Player *player);

    void setInfo(Card *card, Player *owner);

protected slots:
    bool checkTargetType();

protected:
    Player *m_owner;

    TargetType m_target_type;
    QList<Player*> m_targets;

    Game *m_game;

    Card *m_caused_by;
};

}





#endif // ABSTRACTACTION_H
