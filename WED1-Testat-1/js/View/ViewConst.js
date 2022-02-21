'use strict'

/**
 * Game User Experience
 *
 * Used for UI feedback
 * @type {{text: {result: string, beforeResult: string, beforeButton: string}, nextRoundTimeout: number, textServerText: string, viewContext: {input: {username: Element}, game: {result: Element, beforeButtons: Element, buttons: Element, beforeResult: Element, newPlayer: Element, history: Element}, buttons: {game: [], backToRanking: Element, newGame: Element}, templates: {game: {gamebutton: Promise<WebAssembly.Module> | this}, ranking: {entry: Promise<WebAssembly.Module> | this}, history: {entry: Promise<WebAssembly.Module> | this}}, systemSwitchButton: Element, ranking: {list: Element}, sections: {game: Element, loader: Element, systemSwitch: Element, ranking: Element, gameFooter: Element}, forms: {newGame: Element}}}}
 */
const GUE = {
    state: 'start',
    prefixServerSwitch:     'Wecheln zu ',
    text: {
        beforeButton:   '',
        beforePlayerHand2:   'VS',
        computerHand:         '',
    },
    nextRoundTimeout:   4000,
    viewContext : {
        systemSwitchButton : document.querySelector('#systemSwitchButton'),
        sections :{
            systemSwitch :  document.querySelector('#systemSwitchNav'),
            loader :        document.querySelector('#loaderDiv'),
            game :          document.querySelector('#gameSection'),
            ranking :       document.querySelector('#rankingSection'),
            history :       document.querySelector('#gameHistorySection'),
            newPlayer :     document.querySelector('#gameNewPlayerSection'),
            error :         document.querySelector('#errorSection'),
            horizontalLine : document.querySelector('#horizontalLine')
        },
        game : {
            beforeButtons:  document.querySelector('#gameBeforeButtonsP'),
            buttons:        document.querySelector('#gameButtonsP'),
            beforeResult:   document.querySelector('#gameBeforeResultP'),
            result:         document.querySelector('#gameResultP')
        },
        ranking : {
            list :          document.querySelector('#rankingListOl')
        },
        templates : {
            ranking: {
                entry:      Handlebars.compile(document.querySelector('#rankingTemplate').innerHTML)
                //player: Handlebars.compile(document.querySelector('#ranking-player-template').innerHTML)
            },
            history : {
                entry:      Handlebars.compile(document.querySelector('#historyEntryTemplate').innerHTML)
            },
            game : {
                gamebutton: Handlebars.compile(document.querySelector('#gameButtonTemplate').innerHTML)
            }
        },
        buttons : {
            newGame :       document.querySelector('#startGameButton'),
            game : [],
            backToRanking : document.querySelector('#gameBackToRankingButton'),
            systemSwitch :  document.querySelector('#systemSwitchButton')

        },
        input: {
            username :      document.querySelector('#playerNameInput')
        },
        forms : {
            newGame :       document.querySelector('#gameNewPlayerForm')
        }
    }
}