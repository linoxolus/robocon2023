function indexPage(apiUrl) {
    var components = Array.from(document.querySelectorAll('.main-item'));
    components = components.filter(
        (component) => !Array.from(component.classList).includes('no-data')
    );
    setInterval(() => {
        for (let i = 0; i < components.length; i++) {
            var url = apiUrl + '/get/' + components[i].id;
            let postfix =
                components[i].querySelector('.main-item-data').dataset.postfix;
            
            fetch(url, {
                headers: {
                },
                method: 'GET',
            })
            .then(data => data.text())
            .then(data => {
                components[i].querySelector('.main-item-data').innerText =
                    data + postfix;
            })
            
        }
        // console.log('tes');
    }, 1000);
}

export default indexPage;
