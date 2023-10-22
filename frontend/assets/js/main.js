const url = "http://192.168.1.10"

const controlBtns = Array.from(document.querySelectorAll(".control .item"));
controlBtns.forEach((controlBtn) => {
    let interval;
    function move() {
        console.log(url + "/move/?direction=" + controlBtn.getAttribute("name"));
        fetch(url + "/move/?direction=" + controlBtn.getAttribute("name"),  {
        method: 'POST',
        body: controlBtn.getAttribute("name"),
        mode: 'no-cors',
    })
        .then((respons) => respons)
        .then((data) => data)
        .catch(() => {
            console.log('error');
        });
    }
    
    controlBtn.onmousedown = controlBtn.ontouchstart = (e) => {
        interval = setInterval(() => {
            move();
        }, 10)
    };
    controlBtn.onmouseup = controlBtn.ontouchend = (e) => {
        clearInterval(interval);
    };
    controlBtn.onclick = move;
})