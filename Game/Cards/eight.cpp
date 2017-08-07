#include "eight.h"
#include "game.h"
#include "Actions/actions.h"

using namespace bridge_game;

Eight::Eight(Suit suit, QObject *parent) :
    Card(Card::Eight, suit, parent)
{

}

void Eight::action(ActionArgs args)
{
    QList<ActionPtr> actions;
    auto deck = args.game->getDeck();
    auto game = args.game;
    Player *owner = game->getActivePlayer().data();
    Card *card = this;

    for (int i = 0; i < 2; ++i)
    {
        ActionPtr take(new ActionTakeCard(game));
        take->setTarget(game->getNextPlayer());
        take->setInfo(card, owner);

        actions.append(take);

        if (deck->empty())
        {
            qDebug() << "Eight::action: No cards left in the deck";

            ActionPtr refill(new ActionTakeCard(game));
            refill->setTargetType(AbstractAction::NoTarget);

            actions.append(refill);
        }
    }

    ActionPtr skip(new ActionSkipTurn(game));
    skip->setTarget(game->getNextPlayer());
    skip->setInfo(card, owner);

    actions.append(skip);

    ActionPtr changeSuit(new ActionSetActiveSuit(game, m_suit));
    changeSuit->setInfo(card, owner);

    actions.append(changeSuit);

    args.game->execute(actions);
}
