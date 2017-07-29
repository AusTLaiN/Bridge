#include "abstractaction.h"
#include "game.h"

#include <QMetaEnum>

using namespace bridge_game;

AbstractAction::AbstractAction(Game *game, QObject *parent) :
    QObject(parent),
    m_target_type(UndefinedTargetType),
    m_game(game),
    m_caused_by(nullptr),
    m_owner(nullptr)
{

}

AbstractAction::~AbstractAction()
{

}

Player* AbstractAction::getOwner()
{
    return m_owner;
}

AbstractAction::TargetType AbstractAction::getTargetType()
{
    return m_target_type;
}

const QList<Player*> &AbstractAction::getTargets()
{
    return m_targets;
}

Game* AbstractAction::getGame()
{
    return m_game;
}

Card* AbstractAction::getCard()
{
    return m_caused_by;
}

bool AbstractAction::noTargets()
{
    return m_targets.empty();
}

QJsonObject AbstractAction::toJson()
{
    QJsonObject json;

    if (m_game)
        json["game id"] = m_game->getId();
    else
        json["game id"] = "nullptr";

    if (m_owner)
    {
        auto owner = m_owner->toJson();
        Player::hideCards(owner);
        json["owner"] = owner;
    }
    else
        json["owner"] = "nullptr";

    if (m_caused_by)
        json["caused by"] = m_caused_by->toJson();
    else
        json["caused by"] = "nullptr";

    json["target type"] = m_target_type;
    json["target type name"] = QMetaEnum::fromType<AbstractAction::TargetType>().valueToKey(m_target_type);

    // Shared ptr's without deleters

    QJsonArray arr;

    for (Player *player : m_targets)
    {
        PlayerPtr item(player, [](Player *obj){});
        auto j_item = item->toJson();
        Player::hideCards(j_item);

        arr.append(j_item);
    }

    json["targets"] = arr;

    return json;
}

void AbstractAction::fromJson(const QJsonObject &json)
{
    qDebug() << "AbstractAction::fromJson: impossible to deserialize abstract class";
}

void AbstractAction::setOwner(Player *player)
{
    m_owner = player;
}

void AbstractAction::setTargetType(AbstractAction::TargetType type)
{
    m_target_type = type;
}

void AbstractAction::setTarget(PlayerPtr target, AbstractAction::TargetType type)
{
    setTarget(target.data(), type);
}

void AbstractAction::setTarget(Player *target, AbstractAction::TargetType type)
{
    m_target_type = type;
    addTarget(target);
}

void AbstractAction::setTargets(const QList<PlayerPtr> &targets, AbstractAction::TargetType type)
{
    m_target_type = type;
    addTargets(targets);
}

void AbstractAction::setTargets(const QList<Player *> &targets, AbstractAction::TargetType type)
{
    m_targets.clear();
    m_targets = targets;
    m_target_type = type;
}

void AbstractAction::addTarget(PlayerPtr player)
{
    addTarget(player.data());
}

void AbstractAction::addTarget(Player *player)
{
    m_targets.append(player);
}

void AbstractAction::addTargets(const QList<PlayerPtr> &targets)
{
    for (PlayerPtr player : targets)
    {
        m_targets.append(player.data());
    }
}

void AbstractAction::addTargets(const QList<Player *> &targets)
{
    m_targets.append(targets);
}

void AbstractAction::setCard(Card *card)
{
    m_caused_by = card;
}

void AbstractAction::setInfo(Card *card, Player *owner)
{
    m_caused_by = card;
    m_owner = owner;
}

bool AbstractAction::checkTargetType()
{
    if (m_target_type == NoTarget)
        return m_targets.count() == 0;
    if (m_target_type == SingleTarget)
        return m_targets.count() == 1;
    if (m_target_type == MultipleTargets)
        return m_targets.count() > 1;

    // For any other target types
    return true;
}
