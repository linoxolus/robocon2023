const mainUrl = 'http://192.168.1.72/';
const camUrl = 'http://192.168.1.177/capture';
const apiUrl = 'http://192.168.1.177/api';
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
