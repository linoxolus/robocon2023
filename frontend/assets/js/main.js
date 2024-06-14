const mainUrl = 'http://192.168.1.11';
const camUrl = 'http://192.168.1.11/capture';
const apiUrl = 'http://192.168.1.11/api';
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
