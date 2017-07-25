#include "standartcardfactory.h"
#include "card.h"
#include "Cards/cards.h"

using namespace bridge_game;

StandartCardFactory::StandartCardFactory()
{

}

CardPtr StandartCardFactory::createCard(Card::Rank rank, Card::Suit suit)
{
    switch (rank) {
    case Card::Six:
        return CardPtr(new Six(suit));
    //case Card::Seven:
    case Card::Eight:
        return CardPtr(new Eight(suit));
    //case Card::Nine:
    //case Card::Ten:
    case Card::Jack:
        return CardPtr(new Jack(suit));
    //case Card::Queen:
    //case Card::King:
    //case Card::Ace:
    default:
        return CardPtr(nullptr);
    }
}

CardPtr StandartCardFactory::createCard(const QJsonObject &json)
{
    Card::Rank rank = static_cast<Card::Rank>(json["rank"].toInt());
    Card::Suit suit = static_cast<Card::Suit>(json["suit"].toInt());

    return createCard(rank, suit);
}
