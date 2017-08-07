#include "game.h"
#include "standartdeckfactory.h"
#include "abstractaction.h"
#include "Actions/actions.h"

#include <QMetaEnum>

using namespace bridge_game;

QString Game::toString(Game::GameStates state)
{
    QMetaEnum metaState = QMetaEnum::fromType<GameStates>();

    return QString(metaState.valueToKey(state));
}

Game::Game(int id, QObject *parent) :
    QObject(parent),
    m_id(id),
    m_active_player(-1),
    m_state(NotStarted),
    m_active_suit(Card::AnySuit)
{
    m_deck_factory.reset(new StandartDeckFactory);
}

Game::~Game()
{
}

Game::GameStates Game::getState() { return m_state; }

const PlayersList& Game::getPlayers() { return m_players; }

PlayerPtr Game::getPlayer(int index)
{
    if (index < 0)
        handleError("Game::getPlayer: index < 0");
    else if (index > m_players.count())
        handleError("Game::getPlayer: index > players count");
    else
    {
        return m_players[index];
    }

    return PlayerPtr(nullptr);
}

PlayerPtr Game::getPlayerById(int id)
{
    if (id < 0)
        handleError("Game::getPlayerById: id < 0");
    else if (id > m_players.count())
        handleError("Game::getPlayerById: id > players count");
    else
    {
        for (PlayerPtr player : m_players)
            if (player->getId() == id)
                return player;
    }

    return PlayerPtr(nullptr);
}

PlayerPtr Game::getActivePlayer()
{
    if (m_active_player < 0)
        handleError("Game::getActivePlayer: active player index < 0");
    else if (m_active_player > m_players.count())
        handleError("Game::getActivePlayer: active player index > players count");
    else
        return m_players[m_active_player];

    return PlayerPtr(nullptr);
}

PlayerPtr Game::getNextPlayer()
{
    if (m_players.count() == 1)
        handleError("Game::getNextPlayer: Only 1 player in game");
    else if (m_active_player < 0 || m_active_player > m_players.count())
        handleError("Game::getNextPlayer: invalid active player");
    else
    {
        if (m_players[m_active_player] == m_players.last())
            return m_players.first();
        return m_players[m_active_player + 1];
    }

    return PlayerPtr(nullptr);
}

DeckPtr Game::getDeck()
{
    return m_deck;
}

int Game::getId()
{
    return m_id;
}

QJsonObject Game::toJson()
{
    QJsonObject json;

    json["deck"] = m_deck->toJson();
    json["players"] = Serializable::listToJson(m_players, Player::serialize);
    json["state"] = m_state;
    json["id"] = m_id;

    json["active player"] = m_active_player;
    json["active suit"] = m_active_suit;

    json["active suit name"] = Card::toString(m_active_suit);
    json["state name"] = toString(m_state);

    return json;
}

void Game::fromJson(const QJsonObject &json)
{
    m_deck->fromJson(json["deck"].toObject());
    m_players.clear();
    Serializable::listFromJson(m_players, json["players"].toArray(), Player::deserialize);

    m_state = static_cast<Game::GameStates>(json["state"].toInt());
    m_id = json["id"].toInt();

    m_active_player = json["active player"].toInt();
    m_active_suit = static_cast<Card::Suit>(json["active suit"].toInt());
}

void Game::newRound()
{
    qDebug() << "Game::newRound";

    m_active_suit = Card::AnySuit;
    m_active_player = 0;

    m_deck = m_deck_factory->createDeck();
    m_deck->shuffle();

    changeGameState(InProgress);

    ActionPtr start(new ActionGameStart(this));
    start->setTargets(m_players, AbstractAction::Global);

    //QList<ActionPtr> actions;
    //actions.append(start);
    execute(start);

    qDebug() << "Game::newRound: end";

    emit newRoundStarted();
}

void Game::join(PlayerPtr player)
{
    if (player == nullptr)
    {
        handleError("Game::join: player is null");
        return;
    }

    m_players.append(player);
    emit playerJoined(player);
}

void Game::leave(PlayerPtr player)
{
    if (player == nullptr)
    {
        handleError("Game::leave: player is null");
        return;
    }

    m_players.removeOne(player);
    emit playerLeft(player);
}

void Game::playCard(PlayerPtr player, int card_num)
{
    if (player == nullptr)
    {
        handleError("Game::playCard: player is null");
        return;
    }
    if (card_num < 0 || card_num > player->getCards().count())
    {
        handleError("Game::playCard: invalid card number");
        return;
    }

    CardPtr card = player->getCards()[card_num];

    playCard(player, card);
}

void Game::playCard(PlayerPtr player, CardPtr card)
{
    if (player == nullptr)
    {
        handleError("Game::playCard: player is null");
        return;
    }
    if (card == nullptr)
    {
        handleError("Game::playCard: card is null");
        return;
    }

    qDebug() << "Game::playCard: card played = " << card->toJson()["name"].toString();

    ActionArgs args;

    args.game = this;
    args.made_by = player.data();

    m_deck->addToPlayed(card);
    player->playCard(args, card);
}

void Game::playCard(int player_num, CardPtr card)
{
    if (player_num < 0 || player_num > m_players.count())
    {
        handleError("Game::playCard: invalid player number");
        return;
    }

    playCard(m_players[player_num], card);
}

void Game::playCard(int player_num, int card_num)
{
    if (player_num < 0 || player_num > m_players.count())
    {
        handleError("Game::playCard: invalid player number");
        return;
    }

    playCard(m_players[player_num], card_num);
}

/*void Game::takeCard(PlayerPtr target)
{
    if (target == nullptr)
    {
        handleError("Game::takeCard: target is null");
        return;
    }

    auto card = m_deck->takeCard();
    if (card == nullptr)
    {
        for (int i = 0; i < CARDS_TO_REMOVE; ++i)
        {
            m_deck->moveToGraveyard(m_deck->lastPlayed());
        }

        m_deck->restore();
        m_deck->shuffle();

        card = m_deck->takeCard();
    }

    target->takeCard(card);
    emit playerTakenCard(target, card);
}*/

/*void Game::takeCards(PlayerPtr target, quint32 amount)
{
    if (amount && target)
        while(amount--)
            0;
            //takeCard(target);
    else
    {
        if (target == nullptr)
            handleError("Game::takeCards: target is null");
        if (amount == 0)
            handleError("Game::takeCards: amount = 0");
    }
}*/

/*void Game::skipTurn(PlayerPtr target)
{
    if (target == nullptr)
    {
        handleError("Game::skipTurn: target is null");
        return;
    }

    target->skipTurn();
    emit playerSkippedTurn(target);
}

void Game::extraTurn(PlayerPtr target)
{
    if (target == nullptr)
    {
        handleError("Game::extraTurn: target is null");
        return;
    }

    target->takeExtraTurn();
    emit playerTakenExtraTurn(target);
}*/

void Game::setActiveSuit(Card::Suit suit)
{   
    m_active_suit = suit;
    emit activeSuitChanged(suit);
}

void Game::setActivePlayer(int index)
{
    if (index < 0)
         handleError("Game::setActivePlayer: index < 0");
    else if (index > m_players.count())
         handleError("Game::setActivePlayer: index > players count");
    else
    {
        m_active_player = index;
        emit activePlayerChanged(index);
        emit activePlayerChanged(m_players[index]);
    }
}

void Game::setActivePlayer(PlayerPtr player)
{
    if (player == nullptr)
    {
        handleError("Game::setActivePlayer: player is null");
        return;
    }

    if (m_players.contains(player))
    {
        auto index = m_players.indexOf(player);
        setActivePlayer(index);
    }
}

void Game::execute(ActionPtr action)
{
    QList<ActionPtr> list;
    list.append(action);
    execute(list);
}

void Game::execute(const QList<ActionPtr> &actions)
{
    emit newActionsRecieved(actions);

    qDebug() << "Game::execute: start";

    qDebug() << "Actions recieved :";
    for (ActionPtr action : actions)
    {
        //qDebug() << action->toJsonDoc().toJson();
        //qDebug() << QJsonDocument(action->toJson()).toJson();
        //auto t = action->toJson();
        //int a = 5;

        QTextStream qcout(stdout);

        qcout << action->toJsonDoc().toJson();
    }

    for (ActionPtr action : actions)
    {
        action->execute();
    }

    qDebug() << "Game::execute: end";

    emit actionsExecuted(actions);
}

void Game::finish()
{
    changeGameState(Finished);
}

void Game::start()
{
    changeGameState(InProgress);
}

void Game::pause()
{
    changeGameState(Paused);
}

void Game::changeGameState(Game::GameStates state)
{
    this->m_state = state;
    emit gameStateChanged(state);
}

void Game::handleError(const QString &message)
{
    qDebug() << "Game error : " << message;
    emit errorOccured(message);
}
