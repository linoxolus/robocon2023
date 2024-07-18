var speServoValue = 0;
function setSpeServoValue(val) {
    speServoValue = val;
    return speServoValue;
}

function updateSpeServoDisplay() {
    document.querySelector('.spe-servo-display').innerHTML = speServoValue;
}

updateSpeServoDisplay();

function arm(apiUrl) {
    var servos = Array.from(document.querySelectorAll('.item'));
    var speServo = document.querySelector('.item-spe');
    servos.forEach((servo, index) => {
        var getUrl = apiUrl + `/get/arm?servo=${servo.dataset.id}`;
        fetch(getUrl, {
            headers: {},
            method: 'GET',
        })
            .then((data) => data.text())
            .then((data) => {
                servo.querySelector('input').value = data;
            });

        servo.querySelector('input').addEventListener('input', (e) => {
            var url =
                apiUrl +
                `/post/arm?servo=${servo.dataset.id}&value=${
                    servo.querySelector('input').value
                }`;
            fetch(url, {
                headers: {
                    Accept: 'application/json',
                    'Content-Type': 'application/json',
                    'Access-Control-Request-Headers': '*',
                },
                mode: 'no-cors',
                method: 'POST',
                body: 'arm posted',
            }).then((res) => {
                console.log('res arm: ', res);
            });
        });
    });

    var speServoBtn = speServo.querySelectorAll('.spe-servo-btn');
    speServoBtn[0].onclick = (e) => {
        var url =
            apiUrl +
            `/post/arm?servo=2&value=${setSpeServoValue(speServoValue - 1)}`;
        // console.log(url)
        postFetchFn(url, 'arm posted', (res) => {
            console.log('res arm: ', res);
        });
        updateSpeServoDisplay();
    };
    speServoBtn[1].onclick = (e) => {
        var url =
            apiUrl +
            `/post/arm?servo=2&value=${setSpeServoValue(speServoValue + 1)}`;
        // console.log(url)
        postFetchFn(url, 'arm posted', (res) => {
            console.log('res arm: ', res);
        });
        updateSpeServoDisplay();
    };

    speServoBtn[2].onclick = (e) => {
        var url = apiUrl + `/get/detachArm?servo=2`;
        // console.log(url)
        getFetchFn(url, (res) => {
            console.log('res arm: ', res);
        });
        updateSpeServoDisplay();
    };
}

export default arm;
