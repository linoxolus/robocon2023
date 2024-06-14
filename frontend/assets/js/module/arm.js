function arm(apiUrl) {
    var servos = Array.from(document.querySelectorAll('.item'));
    servos.forEach((servo, index) => {
        servo.querySelector('input').addEventListener('change', (e) => {
            var url =
                apiUrl +
                `/post/arm?servo=${servo.dataset.id}&value=${
                    servo.querySelector('input').value
                }`;
            fetch(url, {
                headers: {
                    Accept: 'application/json',
                    'Content-Type': 'application/json',
                },
                method: 'POST',
                body: 'arm posted',
            }).then((res) => {
                console.log('res arm: ', res);
            });
        });
    });
}

export default arm;
