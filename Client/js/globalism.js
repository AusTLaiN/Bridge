var wsUri = "ws://localhost:8080";
var websocket = null;

const Actions = {
    UndefinedAction:     0,
    CardForYouself:      1, 
    CardForOpponent:     2,
    SkipTurnForYouself:  3,
    SkipTurnForOpponent: 4,
    ShakeDeckAnimation:  5,

    // OuterCommand
    CreateGameResponse: 101,
    JoinToGameResponse: 102,
    StartGameResponse:  103,
    SuitOrderRequest:   104,
    BridgeRequest:      105,
    GamesInfoResponse:  106,
    ReadyRequest:       107,
    TurnResponse:       108,
    ScoreTableResponse: 109,
    ActiveSuitResponse: 110,
    H_Message:          111,
    ChatMessage:        112,
    
    // InnerCommand
    CreateGameRequest:  201,
    JoinToGameRequest:  202,
    StartGameRequest:   203,
    SuitOrderResponse:  204,
    BridgeResponse:     205,
    GamesInfoRequest:   206,
    ReadyResponse:      207,
    TurnRequest:        208,
    ScoreTableRequest:  209,
    ActiveSuitRequest:  210,
    LeaveGameRequest:   211
};

var player = {
    id: 0,
    name: "somename",
    address: "someaddress",
    score: 0,
    'turns blocked': 0,
    cards: []
};

class OuterMessage
{
    constructor(action, data) { 
        this.action = action;
        this.dataobject = this.getDataObject(data);
    }
    
    getDataObject(data) {
        var dataObj;
        switch(this.action)
        {
            case Actions.CreateGameRequest:
            {
                dataObj = {
                    state: true,
                    player: player,
                    html: data.dataString,
                }
                return dataObj;
            }
            case Actions.ChatMessage:
            {
                dataObj = {
                    state: true,
                    player: player,
                    html: data.dataString,
                }
                return dataObj;
            }
        }
    }
    
    
    foo() { alert("bar"); }
}

function initWebSocket() {
    try {
        if (typeof MozWebSocket == 'function')
            WebSocket = MozWebSocket;
        if ( websocket && websocket.readyState == 1 ){
            alert("ALREADY CONNECTED");
            return;
        }
        websocket = new WebSocket( wsUri );
        websocket.onopen = onOpen;
        websocket.onclose = onClose;
        websocket.onmessage = onMessage;
        websocket.onerror = onError;
    } catch (exception) {
        alert('ERROR: ' + exception);
    }
}
function stopWebSocket() {
    if (websocket)
        websocket.close();
}
function checkSocket() {
    if (websocket != null) {
        var stateStr;
        switch (websocket.readyState) {
            case 0: {
                stateStr = "CONNECTING";
                break;
            }
            case 1: {
                stateStr = "OPEN";
                break;
            }
            case 2: {
                stateStr = "CLOSING";
                break;
            }
            case 3: {
                stateStr = "CLOSED";
                break;
            }
            default: {
                stateStr = "UNKNOW";
                break;
            }
        }
        debug("WebSocket state = " + websocket.readyState + " ( " + stateStr + " )");
    } else {
        debug("WebSocket is null");
    }
}
