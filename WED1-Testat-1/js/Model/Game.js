function gameFn(){
    'use strict'


    let activeEndpointNumber
    let endpoint

    let endpointList = {
        "Lokal" : localEndpoint(),
        "Server" : serverEndpoint()
    }

    function init(){

        activeEndpointNumber = 0
        endpoint =            Object.values(endpointList)[activeEndpointNumber]
        game.nextServername = Object.keys(endpointList)[(activeEndpointNumber + 1) % 2]
    }

    function switchSystem(){
        let endpointValues = Object.values(endpointList)
        let endpointEntries = Object.entries(endpointList)

        activeEndpointNumber = (activeEndpointNumber + 1) % endpointEntries.length
        endpoint = endpointValues[activeEndpointNumber]
        game.nextServername = Object.keys(endpointList)[(activeEndpointNumber + 1) % 2]
    }

    /* ------------------------ GAME ------------------------*/

    async function newGame(playerName){
        game.get.playername = playerName
    }

    async function newMove(playerHand){
        let result = await endpoint.play(game.get.playername, playerHand)
        let historyEntry = {}


        historyEntry.playerHand1 =  playerHand
        historyEntry.playerHand2 =  result.choice

        //Convert win to +, - or = for History
        if(result.win === undefined) {
            historyEntry.result = '='
        } else if(result.win === true) {
            historyEntry.result = '✔'
        } else if(result.win === false) {
            historyEntry.result = '✖'
        }

        return historyEntry
    }

    async function getRanking(getOnlyFirst = 0){
        let playerList =  await endpoint.getPlayer()

        let playerArray = Object.values(playerList)

        let sortedPlayerArray = playerArray.sort( (a, b) => {
            if (a.win > b.win) {
                return -1
            } else if (a.win < b.win) {
                return 1
            }
            return 0
        })

        let lastNumberOfWins = 0

        sortedPlayerArray.forEach( (player, index) => {
            if (index === 0) {
                player.newRank = true
                lastNumberOfWins = player.win
            } else if (lastNumberOfWins !== player.win) {
                lastNumberOfWins = player.win
                player.newRank = true
            } else {
                player.newRank = false
            }
        })

        let rank = 0
        let slicePosition = 0

        await sortedPlayerArray.forEach((value, index) => {
            if(value.newRank === true && rank <= getOnlyFirst) {
                rank++
                slicePosition = index
            }
        })

        if(rank >= getOnlyFirst) {
            return sortedPlayerArray.slice(0, slicePosition)
        } else {
            return sortedPlayerArray
        }

    }

    window.game = {
        init : init,
        newGame: newGame,
        newMove: newMove,
        switchEndpoint : switchSystem,
        nextServername : "",
        get: {
            playername : '',
            ranking: getRanking,
        }
    }
}
gameFn()


