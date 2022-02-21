
let winSymbol = true
let lostSymbol = false
let drawnSymbol = undefined

let resultMatrix = {
    Stein :          {Stein : drawnSymbol,  Schere : winSymbol,     Papier : lostSymbol,    Brunnen : lostSymbol,   Streichholz : winSymbol},
    Schere :         {Stein : lostSymbol,   Schere : drawnSymbol,   Papier : winSymbol,     Brunnen : lostSymbol,   Streichholz : winSymbol},
    Papier :         {Stein : winSymbol,    Schere : lostSymbol,    Papier : drawnSymbol,   Brunnen : winSymbol,    Streichholz : lostSymbol},
    Brunnen :        {Stein : winSymbol,    Schere : winSymbol,     Papier : lostSymbol,    Brunnen : drawnSymbol,  Streichholz : lostSymbol},
    Streichholz :    {Stein : lostSymbol,   Schere : lostSymbol,    Papier : winSymbol,     Brunnen : winSymbol,    Streichholz : drawnSymbol}
}


function localEndpoint() {
    let playerList = {}

    function buttonIndexAsText(id) {
        return Object.keys(resultMatrix)[id]
    }

    function ifNotExistPlayerCreatePlayer(playerName){
        if(playerList[playerName] === undefined) {
            playerList[playerName] = {
                user :  playerName,
                win :   0,
                lost :  0
            }
        }
    }

    function updatePlayerStat(playerName, result){
        if(result === true){
            playerList[playerName].win++
        } else if (result === false) {
            playerList[playerName].lost++
        }
    }

     async function play(playerName, playerHand) {
        // Server choice
        let resultMatrixEntriesLength = Object.entries(resultMatrix).length
        let computerHand = buttonIndexAsText(Math.round((resultMatrixEntriesLength - 1) * Math.random()))

        // get result from matrix
         let gameResult = resultMatrix[playerHand][computerHand]

         await ifNotExistPlayerCreatePlayer(playerName)
         updatePlayerStat(playerName, gameResult)

         return {
             choice : computerHand,
             win : gameResult
         }
    }


    async function getPlayer(){
        return playerList
    }

    return {
        getPlayer : getPlayer,
        play : play
    }
}