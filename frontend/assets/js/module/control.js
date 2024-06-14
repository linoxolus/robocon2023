function controlMoveFn(apiUrl) {
    var intervals = {};
    const controlMoveBtns = Array.from(
        document.querySelectorAll('.control-move .item')
    );
    controlMoveBtns.forEach((controlMoveBtn) => {
        function move() {
            var url =
                apiUrl +
                '/post/move?direction=' +
                controlMoveBtn.getAttribute('name');
            console.log(url);
            fetch(url, {
                headers: {
                    Accept: 'application/json',
                    'Content-Type': 'application/json',
                    'Access-Control-Request-Headers': '*',
                },
                mode: 'no-cors',
                method: 'POST',
                body: 'move posted',
            }).then((res) => {
                console.log('res move: ', res);
            });
        }

        controlMoveBtn.onclick = (e) => {
            move();
        };

        controlMoveBtn.onmousedown = controlMoveBtn.ontouchstart = (e) => {
            let index = controlMoveBtn.getAttribute('name');
            intervals.index = setInterval(() => {
                move();
            }, 200);
        };
        controlMoveBtn.onmouseup = controlMoveBtn.ontouchend = (e) => {
            let index = controlMoveBtn.getAttribute('name');
            clearInterval(intervals.index);
        };
        controlMoveBtn.onclick = move;
    });
}

export default controlMoveFn;
