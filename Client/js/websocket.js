class WebSocketManager
{
  constructor(wsUri) {
        this.websocket = null;
        this.initWebSocket(wsUri);
  }
    
  initWebSocket(wsUri) {
    try {
        /*if (typeof MozWebSocket == 'function')
            this.WebSocket = MozWebSocket;*/
        if ( this.websocket && this.websocket.readyState == 1 ){
            alert("ALREADY CONNECTED");
            return;
        }
        this.websocket = new WebSocket(wsUri);
        this.websocket.onopen = this.onOpen;
        this.websocket.onclose = this.onClose;
        this.websocket.onmessage = this.onMessage;
        this.websocket.onerror = this.onError;
    } catch (exception) {
        alert('ERROR: ' + exception);
    }
  }
    
  stopWebSocket() {
    if (this.websocket)
        this.websocket.close();
  }
    
  checkSocket() {
    if (this.websocket != null) {
        var stateStr;
        switch (this.websocket.readyState) {
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
        return stateStr;
    } else {
        alert("WebSocket is null");
    }
  }
    
  onMessage(e) {
    var inObj = JSON.parse(e.data);
    switch(parseInt(inObj.action)) 
    {
        case ACTION.GamesInfoResponse:
            $("#test-area").html(inObj.dataobject.html);
            break;
        case ACTION.ChatMessage:
            $("#test-area").html(inObj.dataobject.html);
            break;
        default:
            break;
    }
  };

  onOpen(e) {
    alert("Connected to server");  
  };

  onClose(e) {
    alert("Disconnected");
  };

  onError(e){
    alert("Error");  
  };

  sendMessage(outObj) {
    //var msg = document.getElementById("inputText").value;
    /*var msg = {
        'action': 202, 
        'dataobject': {
            'state': true,
            'player': {
                'id': 0,
                'name': "testName",
                'address': "testAddr",
                'score': 0,
                'turns blocked': 0,
                'cards': [
                        {'playable': true,
                         'value': 8,
                         'rank': 6,
                         'suit': 3,
                         'name': "somename"
                        },
                        {'playable': true,
                         'value': 9,
                         'rank': 8,
                         'suit': 2,
                         'name': "somename"
                        }
                    ]
            },
            'value': 22
        }
    };*/
    
    var data = "Hello World!";
    var msg = new Message(DIRECTION.Out, ACTION.ChatMessage, data);
    
    if ( this.websocket != null )
    {
        this.websocket.send(JSON.stringify(msg));
        //alert(JSON.stringify(msg));
    }
  };

}