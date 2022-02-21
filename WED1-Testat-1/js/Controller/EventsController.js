'use strict'

let timeout = 3
let state = 'start'

let textBeforeComputerHand  = 'VS'
let textComputerHand = '?'
let textButtonSwitchEndpoint = ''
let textBeforeButtons = ''
let historyEntry = {}
let rankingList;

function init(){
    GUE.viewContext.buttons.backToRanking.addEventListener('click', eventGoToRanking)
    GUE.viewContext.buttons.systemSwitch.addEventListener('click',eventSwitchSystem)
    GUE.viewContext.forms.newGame.addEventListener('submit', eventGoToNewGame)

    game.init()
    state = 'ranking'
    textButtonSwitchEndpoint = "Wechseln zu " + game.nextServername
    window.game.get.ranking(10).then(value => {
        rankingList = value
        updateView()
    }).catch(globalErrorHandler)
}

async function eventSwitchSystem(){
    game.switchEndpoint()
    textButtonSwitchEndpoint = "Wechseln zu " + game.nextServername

    state = 'loading'
    await updateView()
    setTimeout(async () => {
        state = 'ranking'
        window.game.get.ranking(10).then(value => {
            rankingList = value
            textButtonSwitchEndpoint = "Wechseln zu " + game.nextServername
            updateView()
        }).catch(globalErrorHandler)
    },2000)
}
function eventGoToRanking(){
    state = 'ranking'
    window.game.get.ranking(10).then(value => {
        rankingList = value
        updateView()
    }).catch(globalErrorHandler)
}

async  function eventGoToNewGame(e){
    e.preventDefault()

    let playerName = GUE.viewContext.input.username.value

    textBeforeButtons = '<span class="game-bold">'
        + playerName
        + '!</span> Du must spielen'
    textComputerHand = '?'
    textBeforeComputerHand = 'VS'
    game.newGame(playerName).catch(globalErrorHandler)

    state = 'game'
    await updateView()

    let buttonsElement = GUE.viewContext.game.buttons
    buttonsElement.querySelectorAll("button").forEach(gameBtn => {
        gameBtn.addEventListener('click', eventGameNewMove)
    })
}
/*-----------------------------------------------*/

async function eventGameNewMove(ev){
    let playerHand = ev.target.value
    state = 'gameMove'

    game.newMove(playerHand).then(value => {
        historyEntry = value
        textComputerHand = historyEntry.playerHand2
        updateView()
    }).catch(() => {
        state = 'error'
        updateView()
    })
}

window.onload = init