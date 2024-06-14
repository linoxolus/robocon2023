function indexPage(apiUrl) {
    var components = Array.from(document.querySelectorAll('.main-item'));
    components = components.filter(
        (component) => !Array.from(component.classList).includes('no-data')
    );
    setInterval(() => {
        for (var i = 0; i < components.length; i++) {
            var url = apiUrl + '/get/' + components[i].id;
            var postfix =
                components[i].querySelector('.main-item-data').dataset.postfix;
            
            fetch(url)
            .then(data => data.json())
            .then(data => {
                components[i].querySelector('.main-item-data').innerText =
                    data + postfix;
            })
            
        }
    }, 1000);
}

export default indexPage;
