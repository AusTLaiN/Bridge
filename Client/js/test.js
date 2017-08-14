function onMessage(e) {
//    $("#test-area").html(e.data);
//    alert(e.data);
    var inObj = JSON.parse(e.data);
    alert(inObj.dataobject.html);
    switch(parseInt(inObj.action)) 
    {
        case Actions.GamesInfoResponse:
            $("#test-area").html(inObj.dataobject.html);
            break;
        case Actions.ChatMessage:
            $("#test-area").html(inObj.dataobject.html);
            break;
        default:
            break;
    }
};

function onOpen(e) {
    alert("Connected to server");  
};

function onClose(e) {
    alert("Disconnected");
};

function onError(e){
    alert("Error");  
};

function sendMessage(outObj) {
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
    
    var data = { dataString: "Hello World!" };
    var msg = new OuterMessage(Actions.ChatMessage, data);
    
    if ( websocket != null )
    {
        websocket.send(JSON.stringify(msg));
        alert(JSON.stringify(msg));
    }
};