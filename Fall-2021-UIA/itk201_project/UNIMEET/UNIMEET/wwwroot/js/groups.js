

fetch("/Group").then(function (response){
    return response.text();
}).then(function (html){
    document.getElementById("sidebar-group-showcase").innerHTML = html;
}).catch(function (err) {
    console.warn('Something went wrong.', err);
})
    


