// Please see documentation at https://docs.microsoft.com/aspnet/core/client-side/bundling-and-minification
// for details on configuring this project to bundle and minify static web assets.

// Write your JavaScript code.


// Function to search for a contact name in your contacts list and return the result it as a partial view
async function searchUsers() 
{
    let searchString = document.getElementById("searchbarUsers").value;
    
    let result = await fetch("/ApplicationUser/SearchApplicationUser?searchString=" + searchString)
    
    document.getElementById("search-contacts-result").innerHTML = await result.text();
}

async function contactsIncomingPartial() {
    fetch("/ApplicationUser/IncomingContactRequestPartial")
        .then(function (response){
            return response.text();
        }).then(function (html){
        document.getElementById("contacts-main-view").innerHTML = html;
    }).catch(function (err) {
        console.warn('Something went wrong.', err);
    })
}

// Loading the sidebar with groups and contacts. 
fetch("/ApplicationUser/SidebarPreview").then(function (response){
    let data = response.text();
    if (data != null)
        return data;
    else
        return null;
}).then(function (html){
    if (html != null)
        document.getElementById("main-sidebar").innerHTML = html;
});


// Better to use built in functionality from asp.net
/*
// Function to populate the contact list in the contacts view with your contacts and return that partial view.
async function showContactsView()
{

    let searchString = document.getElementById("searchbarUsers").value;

    let result = await fetch("/Home/ReturnContactsView")

    document.getElementById("main-page-wrapper").innerHTML = await result.text();
}

// Function to populate a selected group view with the persons in that group, and return that partial view.
async function showGroupView(groupId)
{

    let result = await fetch("/Home/ReturnGroupView?groupId=" + groupId)

    document.getElementById("main-page-wrapper").innerHTML = await result.text();
}

// Function to return the partial view allowing for creation of a new group.
async function showCreateGroupView()
{

    let result = await fetch("/Home/ReturnCreateGroupView")

    document.getElementById("main-page-wrapper").innerHTML = await result.text();
}
*/

// Function to return the partial view allowing for creation of a new contact.
async function searchForUserPartial() {
    fetch("/ApplicationUser/SearchForContactPartial")
        .then(function (response){
            return response.text();
        }).then(function (html){
        document.getElementById("contacts-main-view").innerHTML = html;
    }).catch(function (err) {
        console.warn('Something went wrong.', err);
    })
}

// Function to return the partial view containing outgoing contact requests.
async function contactsOutgoingPartial() {
    fetch("/ApplicationUser/OutgoingContactRequestsPartial")
        .then(function (response){
            return response.text();
        }).then(function (html){
        document.getElementById("contacts-main-view").innerHTML = html;
    }).catch(function (err) {
        console.warn('Something went wrong.', err);
    })
}
