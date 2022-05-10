

fetch("/ApplicationUser/FriendRequests")
    .then(function (response){
        return response.text();
    }).then(function (html){
    document.getElementById("friend-requests").innerHTML = html;
}).catch(function (err) {
    console.warn('Something went wrong.', err);
})

