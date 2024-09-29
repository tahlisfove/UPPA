/**
 * Character.js
 */

'use strict';

let Character = function (image /* Image */, name) {
    chai.assert.isTrue(image !== undefined && image !== null && image instanceof Image && image.complete, 'Character._image');
//      Size of images must be changed so that feature detection algorithms work better...
    if (image.width / image.height < 0.9) {
        image.width = Math.max(image.width, image.height, 256);
        image.height = Math.max(image.width, image.height, 256);
    } else {
        if (image.height / image.width < 0.9) {
            image.width = Math.min(image.width, image.height);
            image.height = Math.min(image.width, image.height);
        }
    }
    /** GENERAL NOTES: detection results differ between Firefox and Chrome! */
    /**                changing 'tracking.js' parameters gives poor results */
    /** Eyes */
    this._eyes = new Promise(function (ready) { // Computed by Tracking.js
        let tracker = new tracking.ObjectTracker(['eye']);
        tracker.setInitialScale(1.);
        tracker.setStepSize(1.);
        tracker.setEdgesDensity(0.1);
        tracker.on('track', event => {
            ready(event.data === null ? new Array() : event.data);
        });
        tracking.track(image, tracker);
    });
    /** Face */
    this._face = new Promise(function (ready) { // Computed by Tracking.js
        let tracker = new tracking.ObjectTracker(['face']);
        tracker.setInitialScale(1.);
        tracker.setStepSize(1.);
        tracker.setEdgesDensity(0.1);
        tracker.on('track', event => {
            ready(event.data);
        });
        tracking.track(image, tracker);
    });
    /** Mouth */
    this._mouth = new Promise(function (ready) { // Computed by Tracking.js
        let tracker = new tracking.ObjectTracker(['mouth']);
        tracker.setInitialScale(1.);
        tracker.setStepSize(1.);
        tracker.setEdgesDensity(0.1);
        tracker.on('track', event => {
            ready(event.data === null ? new Array() : event.data);
        });
        tracking.track(image, tracker);
    });

    /** Ex. of post-processing */
    this._mouth.then(function (mouth) {
        // Bouche la plus basse sur la photo mais ne tient pas compte que la bouche est incluse dans la face (voir Macron !) :
        if (mouth !== null && mouth.length > 1)
            mouth.sort(function (mouth1, mouth2) {
                return mouth2.y - mouth1.y;
            }).splice(1, mouth.length - 1);
    });
    /** End of ex. of post-processing */

    /**
     * Ajouter d'autres heuristiques ici..
     */

    Promise.all([this._eyes, this._face, this._mouth]).then(function (features) {
        if (features[1] !== null && features[1].length === 1) { // Une seule face calculée sinon tentative de rectification peu sensée...
            /** EYES */
            const estimated_eye_left_x = features[1][0].x + 3 * features[1][0].width / 16;
            const estimated_eye_right_x = features[1][0].x + 9 * features[1][0].width / 16;
            const estimated_eye_y = features[1][0].y + features[1][0].height / 3;
            const estimated_eye_height = features[1][0].height / 6;
            const estimated_eye_width = features[1][0].width / 4;
            if (features[0].length === 0) {
                features[0].push({total: 0, width: estimated_eye_width, height: estimated_eye_height, x: estimated_eye_left_x, y: estimated_eye_y});
                features[0].push({total: 0, width: estimated_eye_width, height: estimated_eye_height, x: estimated_eye_right_x, y: estimated_eye_y});
            } else {
                if (features[0].length === 1) {
                    features[0].forEach(eye => {
                        if (estimated_eye_left_x < eye.x * 0.75 || estimated_eye_left_x > eye.x / 0.75) {
                            if (estimated_eye_right_x < eye.x * 0.75 || estimated_eye_right_x > eye.x / 0.75) {
                                alert(name + " estimated_eye_x: " + estimated_eye_right_x + " eye.x min: " + (eye.x * 0.75) +
                                        " eye.x max: " + (eye.x / 0.75));
                                // Correct and become left eye:
                                eye.x = estimated_eye_left_x;
                                eye.width = estimated_eye_width;
                                // Add right eye
                                features[0].push({total: 0, width: estimated_eye_width, height: estimated_eye_height, x: estimated_eye_right_x, y: estimated_eye_y});
                            } else
                                // Add left eye
                                features[0].push({total: 0, width: estimated_eye_width, height: estimated_eye_height, x: estimated_eye_left_x, y: estimated_eye_y});
                        } else
                            // Add right eye
                            features[0].push({total: 0, width: estimated_eye_width, height: estimated_eye_height, x: estimated_eye_right_x, y: estimated_eye_y});
                        if (estimated_eye_y < eye.y * 0.75 || estimated_eye_y > eye.y / 0.75) {
                            alert(name + " estimated_eye_y: " + estimated_eye_y + " eye.y min: " + (eye.y * 0.75) +
                                    " eye.y max: " + (eye.y / 0.75));
                            eye.y = estimated_eye_y;
                            eye.height = estimated_eye_height;
                        }
                    });
                }
            }
            /** MOUTH */
            const estimated_mouth_x = features[1][0].x + features[1][0].width / 4;
            const estimated_mouth_y = features[1][0].y + 2 * features[1][0].height / 3;
            const estimated_mouth_height = features[1][0].height / 5;
            const estimated_mouth_width = features[1][0].width / 2;
            if (features[2].length === 0)
                features[2].push({total: 0, width: estimated_mouth_width, height: estimated_mouth_height, x: estimated_mouth_x, y: estimated_mouth_y});
            else {
                features[2].forEach(mouth => {
                    if (estimated_mouth_x < mouth.x * 0.85 || estimated_mouth_x > mouth.x / 0.85) {
                        mouth.x = estimated_mouth_x;
                        mouth.width = estimated_mouth_width;
                    }
                    if (estimated_mouth_y < mouth.y * 0.85 || estimated_mouth_y > mouth.y / 0.85) {
                        mouth.y = estimated_mouth_y;
                        mouth.height = estimated_mouth_height;
                    }
                });
            }
        }
        /** Display */
        let canvas = document.createElement("CANVAS");
        canvas.width = image.width;
        canvas.height = image.height;
        canvas.getContext('2d').drawImage(image, 0, 0, image.width, image.height);
        canvas.getContext('2d').lineWidth = 3;
        canvas.getContext('2d').strokeStyle = 'red';
        for (let i = 0; i < features[0].length; ++i) {
            canvas.getContext('2d').strokeRect(Math.round(features[0][i].x), Math.round(features[0][i].y), Math.round(features[0][i].width), Math.round(features[0][i].height));
        }
        canvas.getContext('2d').strokeStyle = 'blue';
        for (let i = 0; i < features[1].length; ++i) {
            canvas.getContext('2d').strokeRect(Math.round(features[1][i].x), Math.round(features[1][i].y), Math.round(features[1][i].width), Math.round(features[1][i].height));
        }
        canvas.getContext('2d').strokeStyle = 'green';
        for (let i = 0; i < features[2].length; ++i) {
            canvas.getContext('2d').strokeRect(Math.round(features[2][i].x), Math.round(features[2][i].y), Math.round(features[2][i].width), Math.round(features[2][i].height));
        }
        canvas.style.width = "250px";
        canvas.style.height = "250px";
        document.getElementById('Feature_detection').insertBefore(canvas, document.getElementById('Feature_detection').childNodes[0]);
    });
};

