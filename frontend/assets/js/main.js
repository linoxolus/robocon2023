const mainUrl = 'http://192.168.94.145';
const camUrl = 'http://192.168.94.231:81/stream';
const apiUrl = 'http://192.168.94.145/api';
const backBtn = document.querySelector('.back-btn');
window.addEventListener('beforeunload', function (event) {
    localStorage.preUrl = window.location.href;
});

if (
    localStorage.preUrl == undefined ||
    localStorage.preUrl == window.location.href
) {
    localStorage.preUrl = '/';
}

if (backBtn) {
    backBtn.querySelector('a').href = localStorage.preUrl;
}

function getFetchFn(url, method = 'none', thenCb, catchCb) {
    fetch(url, {
        headers: {},
        method: 'GET',
    })
        .then((res) => {
         if (method != 'none') {
             return res[method]();
         }
         return res;
        })
        .then(thenCb)
        .catch(catchCb);
}

function postFetchFn(url, body, thenCb, catchCb) {
    fetch(url, {
        headers: {},
        mode: 'no-cors',
        method: 'POST',
        body: body,
    })
        .then(thenCb)
        .catch(catchCb);
}
