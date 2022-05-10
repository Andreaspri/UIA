let raw_1 = document.getElementById("user-id");
let userId = raw_1.attributes["value"].value;
fetch(`/ApplicationUser/CommonGroups/${userId}`).then(function (response){
    return response.text();
}).then(function (html){
    document.getElementById("common-groups").innerHTML = html;
}).catch(function (err) {
    console.warn('Something went wrong.', err);
})