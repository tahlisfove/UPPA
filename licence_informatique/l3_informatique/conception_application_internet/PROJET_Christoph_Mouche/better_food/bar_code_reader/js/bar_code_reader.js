"use strict";
let _bar_code;
let WebS;
let cb;
/* Connection of client-side WebSockets */
function connect() {
    if (WebS !== undefined && WebS.readyState !== WebSocket.CLOSED) {
        return;
    }
    /* Creating a WebSocket */
    WebS = new WebSocket("ws://localhost:2002/ChristophMouche/WebSocket_Server");
    /* WebSocket error */
    WebS.onerror = function () { window.alert("Error on WebSocket service"); };
    /* WebSocket open */
    WebS.onopen = function () { console.log("WebSocket connected"); };
    /* WebSocket message */
    WebS.onmessage = (event) => {
        let nutriscore = window.document.getElementById('nutriscore');
        if (nutriscore && (event === null || event === void 0 ? void 0 : event.data)) {
            nutriscore.textContent = event.data;
            console.log("Nutriscore of this product is : " + event.data);
        }
        else {
            nutriscore.textContent = "undefined";
        }
    };
    /* WebSocket close */
    WebS.onclose = function () { console.log("WebSocket connection closed"); };
}
/* WebSocket send the barcode retrieved on the server side */
function send(_bar_code) { WebS.send(_bar_code); }
/* WebSocket close */
function closeSocket() { WebS.close(); }
/* Launch a connection to websockets */
connect();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* DOM initialization */
let _DOM_ready = null;
Object.defineProperty(window, "DOM_ready", {
    value: new Promise(launched_function_when_DOM_ready => {
        _DOM_ready = launched_function_when_DOM_ready;
    }), enumerable: false, configurable: false, writable: false
});
window.document.onreadystatechange = _DOM_ready;
/* DOM is ready */
window.DOM_ready.then(() => {
    /* Webcam shooting */
    const _camera = window.document.getElementById('camera');
    _camera.addEventListener('canplay', () => {
        window.console.log("The video is playing...");
    });
    const _canvas = window.document.createElement('canvas');
    /* Camera constraints initialization */
    let constraints = { video: true };
    if (window.navigator.mediaDevices.getSupportedConstraints().hasOwnProperty('facingMode')) {
        constraints = { video: { facingMode: 'environement' } };
    }
    /* Video management */
    const _video_management = () => {
        if (_camera.srcObject !== null) {
            /* Video is running, take photography */
            if (_camera.srcObject.getVideoTracks()[0].readyState === 'live') {
                /* Before stopping the camera, one records the last frame */
                _canvas.setAttribute('width', _camera.videoWidth.toString());
                _canvas.setAttribute('height', _camera.videoHeight.toString());
                _canvas.getContext('2d').drawImage(_camera, 0, 0, _camera.videoWidth, _camera.videoHeight);
                const _photo = new Image();
                _photo.onload = () => {
                    /* This immediately stops the webcam */
                    _camera.srcObject.getVideoTracks()[0].stop();
                    /* The stream is no longer active */
                    window.console.assert(_camera.srcObject.active === false);
                    window.console.assert(_camera.srcObject.getVideoTracks()[0].readyState === 'ended');
                    /* The stream is detached from the '<video>' tag */
                    _camera.srcObject = null;
                    _camera.setAttribute('poster', _photo.src);
                };
                /* From canvas to image */
                _photo.src = _canvas.toDataURL("image/png");
                /* Decoding of the obtained image using quagga */
                Quagga.decodeSingle({
                    locate: true,
                    frequency: 10,
                    decoder: {
                        readers: ["ean_reader", {
                                format: "ean_reader",
                                config: {
                                    supplements: [
                                        'ean_5_reader', 'ean_2_reader'
                                    ]
                                }
                            }],
                    },
                    locator: {
                        patchSize: "medium",
                        halfSample: true
                    },
                    src: _canvas.toDataURL("image/png")
                }, 
                /* End of decoding */
                function (result) {
                    /* If a barcode is detected it is sent to the WebSockets */
                    if (result === null || result === void 0 ? void 0 : result.codeResult) {
                        let cb = window.document.getElementById('cb');
                        console.log("Bar code dectected is:", result.codeResult.code);
                        _bar_code = result.codeResult.code;
                        cb.textContent = result.codeResult.code;
                        send(_bar_code);
                    }
                    else {
                        /* Otherwise nothing */
                        console.log("Bar code is not detected please retry");
                    }
                });
                /* Otherwise end of video */
            }
            else
                window.alert("The video ended");
            /* New stream is required*/
        }
        else {
            window.navigator.mediaDevices.getUserMedia(constraints).then((stream) => {
                _camera.srcObject = stream;
                _camera.play();
            }).catch((error) => {
                window.alert(error.message);
            });
        }
    };
    /* Launching the mouse actions video */
    if (window.PointerEvent)
        _camera.onpointerup = _video_management;
    else
        _camera.addEventListener('mouseup', _video_management, true);
});
