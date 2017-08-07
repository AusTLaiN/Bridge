#include "standartdeckfactory.h"
#include "standartcardfactory.h"
#include "deck.h"

#include <QMetaEnum>

using namespace bridge_game;

StandartDeckFactory::StandartDeckFactory()
{

}

DeckPtr StandartDeckFactory::createDeck()
{
    DeckPtr deck(new Deck);
    CardFactoryPtr card_factory(new StandartCardFactory);
    QMetaEnum suits = QMetaEnum::fromType<Card::Suit>();

    for (int i = 0; i < 4; ++i)
    {
        auto suit = static_cast<Card::Suit>(suits.value(i));

        for (int i = Card::Six; i <= Card::Ace; ++i)
        {
            auto rank = static_cast<Card::Rank>(i);
            CardPtr card = card_factory->createCard(rank, suit);

            if (card == nullptr)
            {
                qDebug() << "StandartDeckFactory::createDeck: Card is null" << endl
                         << "Rank = " << rank << endl
                         << "Suit = " << suit << endl;
                continue;
            }

            deck->addToDeck(card);
        }
    }

    return deck;
}

DeckPtr StandartDeckFactory::createDeck(const QJsonObject &json)
{
    DeckPtr deck(new Deck());
    deck->fromJson(json);
    return deck;
}
