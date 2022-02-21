function globalErrorHandler(e){
    document.querySelector('#errorSection').hidden = false

    document.querySelector('#loaderDiv').hidden             = true
    document.querySelector('#gameHistorySection').hidden    = true
    document.querySelector('#gameSection').hidden           = true
    document.querySelector('#rankingSection').hidden        = true
    document.querySelector('#systemSwitchNav').hidden       = true
    document.querySelector('#gameNewPlayerSection').hidden  = true
    document.querySelector('#horizontalLine').hidden        = true


    if(e !== undefined)
        document.querySelector('#errorSection')
            .querySelector('#errorReason')
            .innerHTML = e.toString()

    console.error(e)

}

window.addEventListener('error', globalErrorHandler)
