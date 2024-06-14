function controlMoveFn(url) {
    var intervals = {};
    const controlMoveBtns = Array.from(document.querySelectorAll('.control-move .item'));
    controlMoveBtns.forEach((controlMoveBtn) => {
        function move() {
            console.log(
                url +
                    '/move?direction=' +
                    controlMoveBtn.getAttribute('name')
            );
            // fetch()
             
        }

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
