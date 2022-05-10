
fetch("/ApplicationUser/Friends")
    .then(function (response){
        return response.text();
    }).then(function (html){
    document.getElementById("users").innerHTML = html;
}).catch(function (err) {
    console.warn('Something went wrong.', err);
})
