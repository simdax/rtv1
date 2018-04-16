let socket = new WebSocket("ws://10.11.9.14:5678")

socket.onopen = (e) => {
    console.log("websocket created")
}
socket.onerror = (e) => {
    console.log("error ??")
}
socket.onmessage = (e) => {
    console.log("j'ai recu un message")
}

$('#test').on('click', function(){
    socket.send('TEST', "test")
})
