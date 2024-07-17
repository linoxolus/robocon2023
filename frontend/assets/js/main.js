const mainUrl = 'http://192.168.96.145';
const camUrl = 'http://192.168.96.231:81/stream';
const apiUrl = 'http://192.168.96.145/api';
const backBtn = document.querySelector('.back-btn');
window.addEventListener('beforeunload', function (event) {
    localStorage.preUrl = window.location.href;
});

if (localStorage.preUrl == undefined || localStorage.preUrl == window.location.href) {
    localStorage.preUrl = '/';
}

if (backBtn) {
    backBtn.querySelector('a').href = localStorage.preUrl;
}
