#ifndef COMMAND_H
#define COMMAND_H

//#include <QMetaEnum>
#include "global.h"

namespace bridge_server {

// class instead header
class Command
{
public:
    // Contract with client
    enum ACTION {
        UndefinedAction = 0,

        CardForYouself,
        CardForOpponent,
        SkipTurnForYouself,
        SkipTurnForOpponent,
        ShakeDeckAnimation,

        // OuterCommand
        CreateGameResponse = 101,
        JoinToGameResponse,
        StartGameResponse,
        SuitOrderRequest,
        BridgeRequest,
        GamesInfoResponse,
        ReadyRequest,
        TurnResponse,
        ScoreTableResponse,
        ActiveSuitResponse,
        H_Message,
        ChatMessage,

        // InnerCommand
        CreateGameRequest = 201,
        JoinToGameRequest,
        StartGameRequest,
        SuitOrderResponse,
        BridgeResponse,
        GamesInfoRequest,
        ReadyResponse,
        TurnRequest,
        ScoreTableRequest,
        ActiveSuitRequest,
        LeaveGameRequest
    };
    //Q_ENUM(ACTION)

    ACTION getAction();

    Command();
    Command(ACTION action);

private:
    ACTION m_action;
};

} // bridge_server


#endif // COMMAND_H
