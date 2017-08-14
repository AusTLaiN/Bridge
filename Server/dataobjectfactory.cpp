#include "dataobjectfactory.h"

using namespace bridge_game;
using namespace bridge_server;

DataObject* DataObjectFactory::getInnerDataObject(const Command::ACTION action, const QJsonObject& json)
{
    switch(action)
    {
        case Command::ACTION::GamesInfoRequest:
        case Command::ACTION::SuitOrderRequest:
        case Command::ACTION::ScoreTableRequest:
        case Command::ACTION::ActiveSuitRequest:
        case Command::ACTION::CreateGameRequest:
            return new DataObject(json);
        case Command::ACTION::ChatMessage:
            return new HtmlDataObject(json);
        case Command::ACTION::JoinToGameRequest:
            return new IntDataObject(json);
        case Command::ACTION::TurnRequest:
        case Command::ACTION::LeaveGameRequest:
            return new CardListDataObject(json);
        case Command::ACTION::ReadyResponse:
        case Command::ACTION::BridgeResponse:
            return new FlagDataObject(json);
        default:
            qDebug() << "DataObjectFactory::getInnerDataObject: Unknown Command::ACTION" << endl;
            return Q_NULLPTR;
    }
}

DataObject* DataObjectFactory::getOuterDataObject(const Command::ACTION action)
{
    switch(action)
    {
        case Command::ACTION::CardForYouself:
        case Command::ACTION::ShakeDeckAnimation:
        case Command::ACTION::SuitOrderRequest:
        case Command::ACTION::BridgeRequest:
        case Command::ACTION::ReadyRequest:
            return new DataObject();
        case Command::ACTION::SkipTurnForYouself:
        case Command::ACTION::SkipTurnForOpponent:
        case Command::ACTION::SuitOrderResponse:
        case Command::ACTION::H_Message:
        case Command::ACTION::ChatMessage:
        case Command::ACTION::GamesInfoResponse:
        case Command::ACTION::ScoreTableResponse:
        case Command::ACTION::ActiveSuitResponse:
            return new HtmlDataObject();
        case Command::ACTION::CreateGameResponse:
        case Command::ACTION::JoinToGameResponse:
        case Command::ACTION::CardForOpponent:
            return new IntDataObject();
        case Command::ACTION::TurnResponse:
            return new CardListDataObject();
        default:
            qDebug() << "DataObjectFactory::getOuterDataObject: Unknown Command::ACTION" << endl;
            return Q_NULLPTR;
    }
}
