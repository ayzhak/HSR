
async function createRanking(rankingList){

    let rankingListElement = GUE.viewContext.ranking.list
    let template = GUE.viewContext.templates.ranking.entry

    if(rankingList.length === 0) {
        rankingListElement.innerHTML = "<h3>Keine Einträge vorhanden</h3>"
    } else {
        rankingListElement.innerHTML = await template(rankingList)
    }
}

function countdownOnMove(timeout = 0) {
    let beforeComputerHand = GUE.viewContext.game.beforeButtons
    let computerHand = GUE.viewContext.game.result

    for (let i = timeout; i >= 0; i--){
         setTimeout( async () => {
            if (i === timeout) {
                GUE.viewContext.game.beforeResult.innerHTML = 'VS'
                GUE.viewContext.game.result.innerHTML =  '?'
                await revokeUpdatePressedButton()
            } else {
                GUE.viewContext.game.beforeResult.innerHTML = "Nächste Runde in " + (timeout - i)
            }
        }, 1000 * i)
    }
}

async function updatePressedButton(){
    let pressedButton = await GUE.viewContext.game.buttons.querySelector('[value="' + historyEntry.playerHand1 + '"]')
    let symboleSpan = await pressedButton.querySelector(".gameButtonSpace")
    symboleSpan.innerHTML = historyEntry.result
    pressedButton.dataset.result = historyEntry.result
}

async function revokeUpdatePressedButton(){
    let pressedButton = await GUE.viewContext.game.buttons.querySelector('[value="' + historyEntry.playerHand1 + '"]')
    let symboleSpan = await pressedButton.querySelector(".gameButtonSpace")
    symboleSpan.innerHTML = ''
    pressedButton.removeAttribute("data-result")
}

function createHistoryEntry(){
    let el = GUE.viewContext.sections.history.querySelector("tbody")
    let template = GUE.viewContext.templates.history.entry
    el.innerHTML += template(historyEntry)
}

function createGameButtons(){
    let buttonsElement = GUE.viewContext.game.buttons
    let template = GUE.viewContext.templates.game.gamebutton
    let gameButtonList = Object.keys(resultMatrix)

    buttonsElement.innerHTML = template(gameButtonList)
}

function updateGameText(){
    GUE.viewContext.game.result.innerHTML =         textComputerHand
    GUE.viewContext.game.beforeResult.innerHTML =   textBeforeComputerHand
    GUE.viewContext.game.beforeButtons.innerHTML =  textBeforeButtons
}

function disableAllButtons(){
    let buttons = document.querySelectorAll('button')
    buttons.forEach(value => {
        value.disabled = true
    })
}

 function enableAllButtons(timeout = 0){
    setTimeout(async () => {
        let buttons = document.querySelectorAll('button')
        await buttons.forEach( value => {
            value.disabled = false
        })
    }, 1000 * timeout)
}

function updateSwichButton(){
    GUE.viewContext.buttons.systemSwitch.innerHTML   = textButtonSwitchEndpoint
}

function switchTo() {
    function game() {
        GUE.viewContext.sections.history.querySelector("tbody").innerHTML = ''

        GUE.viewContext.sections.history.hidden = false
        GUE.viewContext.sections.game.hidden = false
        GUE.viewContext.sections.horizontalLine.hidden = false


        GUE.viewContext.sections.ranking.hidden = true
        GUE.viewContext.sections.newPlayer.hidden = true
        GUE.viewContext.sections.systemSwitch.hidden = true
        GUE.viewContext.sections.loader.hidden = true
    }

    function ranking() {
        GUE.viewContext.sections.systemSwitch.hidden = false
        GUE.viewContext.sections.ranking.hidden = false
        GUE.viewContext.sections.newPlayer.hidden = false
        GUE.viewContext.sections.horizontalLine.hidden = false

        GUE.viewContext.sections.loader.hidden = true
        GUE.viewContext.sections.history.hidden = true
        GUE.viewContext.sections.game.hidden = true
    }

    function loading() {
        GUE.viewContext.sections.loader.hidden = false

        GUE.viewContext.sections.history.hidden = true
        GUE.viewContext.sections.game.hidden = true
        GUE.viewContext.sections.ranking.hidden = true
        GUE.viewContext.sections.systemSwitch.hidden = true
        GUE.viewContext.sections.newPlayer.hidden = true
        GUE.viewContext.sections.horizontalLine.hidden = true
    }

    return {
        loading : loading,
        ranking : ranking,
        game : game
    }
}