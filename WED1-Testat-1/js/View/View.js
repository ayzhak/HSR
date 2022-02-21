async function updateView() {
    //View switching
    if(state === 'ranking') {
        await createRanking(rankingList)
        switchTo().ranking()
        updateSwichButton()
    } else if (state === 'loading'){
        switchTo().loading()
    } else if (state === 'game') {
        updateGameText()
        createGameButtons()
        switchTo().game()
    } else if (state === 'gameMove') {
        disableAllButtons(3)
        createHistoryEntry()
        updateGameText()
        await updatePressedButton()
        await countdownOnMove(timeout)
        enableAllButtons(timeout)
    }  else if(state === 'countdownAndDisableButtons') {
        switchTo().game()
    }

}



