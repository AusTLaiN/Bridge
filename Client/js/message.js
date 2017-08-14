class Message
{
    constructor(direction, action, data) { 
        this.action = action;
        
        if(direction == DIRECTION.In)
            this.dataobject = this.getInnerDataObject(data);
        else if(direction == DIRECTION.Out)
            this.dataobject = this.getOuterDataObject(data);
        else
            alert("Wrong message direction type");
    }
    
    getOuterDataObject(data) {
        var dataObj;
        switch(this.action)
        {
            case ACTION.CreateGameRequest:
            {
                dataObj = {
                    state: false,
                    player: PLAYER,
                    html: data,
                }
                return dataObj;
            }
            case ACTION.ChatMessage:
            {
                dataObj = {
                    state: false,
                    player: PLAYER,
                    html: data,
                }
                return dataObj;
            }
        }
    }
    
    getInnerDataObject(data){
        alert("No definition!");
    }
}