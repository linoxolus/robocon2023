const url = 'http://192.168.12';

const controlBtns = Array.from(document.querySelectorAll('.control .item'));
let intervals = {};
controlBtns.forEach((controlBtn) => {
    function move() {
        console.log(
            url + '/post/move/?direction=' + controlBtn.getAttribute('name')
        );
        fetch(url + '/post/move/?direction=' + controlBtn.getAttribute('name'), {
            method: 'POST',
            body: controlBtn.getAttribute('name'),
            mode: 'no-cors',
        })
            .then((respons) => respons)
            .then((data) => data)
            .catch(() => {
                console.log('error');
            });
    }

    controlBtn.onmousedown = controlBtn.ontouchstart = (e) => {
        let index = controlBtn.getAttribute("name");
        intervals.index = setInterval(() => {
            move();
        }, 200);
    };
    controlBtn.onmouseup = controlBtn.ontouchend = (e) => {
        let index = controlBtn.getAttribute("name");
        clearInterval(intervals.index);
    };
    controlBtn.onclick = move;
});
