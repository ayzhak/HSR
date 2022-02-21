function serverEndpoint() {

    let serverURIPlayer =
            "https://us-central1-schere-stein-papier-eu.cloudfunctions.net/widgets/ranking"
    let serverURIPlay =
            "https://us-central1-schere-stein-papier-eu.cloudfunctions.net/widgets/play"

    async function getPlayer(){
        let response = await fetch(serverURIPlayer).catch(globalErrorHandler)
        return await response.json()
    }

    async function play(playerName, playerHand){
        let uri = serverURIPlay + "?playerName=" + playerName + "&playerHand=" + playerHand

        let response = await fetch(uri).catch(globalErrorHandler)
        return await response.json()
    }

    return {
        getPlayer : getPlayer,
        play : play
    }

}