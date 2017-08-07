#include "dataobjectfactory.h"

using namespace bridge_game;
using namespace bridge_server;

DataObjectPtr DataObjectFactory::getInnerDataObject(Command& cmd, const QJsonObject& json)
{
    switch(cmd.getAction())
    {
        case Command::ACTION::SuitOrderRequest:
        case Command::ACTION::ScoreTableRequest:
        case Command::ACTION::ActiveSuitRequest:
        case Command::ACTION::CreateGameRequest:
            return DataObjectPtr(new DataObject(json));
        case Command::ACTION::ChatMessage:
            return DataObjectPtr(new HtmlDataObject(json));
        case Command::ACTION::JoinToGameRequest:
            return DataObjectPtr(new IntDataObject(json));
        case Command::ACTION::TurnRequest:
        case Command::ACTION::LeaveGameRequest:
            return DataObjectPtr(new CardListDataObject(json));
        case Command::ACTION::ReadyResponse:
        case Command::ACTION::BridgeResponse:
            return DataObjectPtr(new FlagDataObject(json));
        default:
            qDebug() << "DataObjectFactory::getInnerDataObject: Unknown Command::ACTION" << endl;
            return DataObjectPtr(Q_NULLPTR);
    }
}

DataObjectPtr DataObjectFactory::getOuterDataObject(Command& cmd)
{
    switch(cmd.getAction())
    {
        case Command::ACTION::CardForYouself:
        case Command::ACTION::ShakeDeckAnimation:
        case Command::ACTION::SuitOrderRequest:
        case Command::ACTION::BridgeRequest:
        case Command::ACTION::ReadyRequest:
            return DataObjectPtr(new DataObject());
        case Command::ACTION::SkipTurnForYouself:
        case Command::ACTION::SkipTurnForOpponent:
        case Command::ACTION::SuitOrderResponse:
        case Command::ACTION::H_Message:
        case Command::ACTION::ChatMessage:
        case Command::ACTION::GamesInfoResponse:
        case Command::ACTION::ScoreTableResponse:
        case Command::ACTION::ActiveSuitResponse:
            return DataObjectPtr(new HtmlDataObject());
        case Command::ACTION::CreateGameResponse:
        case Command::ACTION::JoinToGameResponse:
        case Command::ACTION::CardForOpponent:
            return DataObjectPtr(new IntDataObject());
        case Command::ACTION::TurnResponse:
            return DataObjectPtr(new CardListDataObject());
        default:
            qDebug() << "DataObjectFactory::getInnerDataObject: Unknown Command::ACTION" << endl;
            DataObjectPtr(Q_NULLPTR);
    }
}
