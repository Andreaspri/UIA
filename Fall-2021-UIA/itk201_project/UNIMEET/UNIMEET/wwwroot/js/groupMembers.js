
let raw_1 = document.getElementById("group-id");
let groupId = raw_1.attributes["value"].value;
fetch(`/Group/GroupMembers/${groupId}`).then(function (response){
    return response.text();
}).then(function (html){
    document.getElementById("group-members").innerHTML = html;
}).catch(function (err) {
    console.warn('Something went wrong.', err);
})

async function selectMember(selected_userId)
{
    let data = document.getElementById("selected-id");
    let list = data.getElementsByTagName('li');
    let arr = Array.prototype.slice.call(list);
    if (arr.some(u => u.innerHTML === selected_userId))
    {
        for (let item of list){
            if (item.innerHTML === selected_userId)
            {
                item.remove();
            }
        }
    }
    else
    {
        const li = document.createElement("li");
        li.appendChild(document.createTextNode(selected_userId));
        data.appendChild(li);
    }
    
    await searchNewGroupMembers();
    
    if (list.length > 0)
    {
        document.getElementById("add-contact-to-group").style.visibility = "visible";
    }
    else
    {
        document.getElementById("add-contact-to-group").style.visibility = "hidden";
    }
}

async function displayContactSearch()
{
    if (document.getElementById("group-member-search-div").style.visibility === "visible")
    {
        document.getElementById("group-member-search-div").style.visibility = "hidden";
        document.getElementById("group-member-search-string").value = '';
        document.getElementById("new-group-members").style.visibility = "hidden";
        let list = document.getElementById("selected-id").getElementsByTagName('li');
        while (list.length !== 0)
        { 
            list.item(0).remove();
        }
        document.getElementById("add-contact-to-group").style.visibility = "hidden";
        await searchNewGroupMembers();
    }
    else{
        document.getElementById("group-member-search-div").style.visibility = "visible";
        document.getElementById("new-group-members").style.visibility = "visible";
    }
}

// Function to search for a contact name in your contacts list and return the result it as a partial view
async function searchNewGroupMembers()
{
    // selected users by id in format ,id_1,id_2...
    let raw = document.getElementById("selected-id");
    
    // Creating a form for the selected id's.
    let formData = new FormData();
    let list = raw.getElementsByTagName('li');
    let selected = [];
    
    for (var i = 0; i < list.length; ++i)
    {
        selected.push(list[i].innerHTML);
    }
    
    formData.append("selected", JSON.stringify(selected));
    
    // String to be search on.
    let searchString = await document.getElementById("group-member-search-string").value;
    
    // Result of the search(partial view with users). 
    fetch(`/Group/SearchGroupContacts/${groupId}/${searchString}`, {method: "post", body: formData}).then(function (response){
            if (response.ok)
            {
                return response.text();
            }
            else
            {
                // No users found.
                return "Not found";
            }
        }).then(function (html){
        // Update the search result.
        document.getElementById("new-group-members").innerHTML = html;
    }).catch(function (err) {
        console.warn('Something went wrong.', err);
    });
}

async function AddContactsToGroup()
{
    // selected users by id in format ,id_1,id_2...
    let raw = document.getElementById("selected-id");

    // Creating a form for the selected id's.
    let formData = new FormData();
    let list = raw.getElementsByTagName('li');
    let selected = [];

    for (var i = 0; i < list.length; ++i)
    {
        selected.push(list[i].innerHTML);
    }
    formData.append("selected", JSON.stringify(selected));
    
    fetch(`/Group/AddUsersToGroup/${groupId}`, {method: "post", body: formData}).then(function (response){
        if (!response.ok){
            console.log("Failed to store application users to the database.");
        }
    }).catch(function (err) {
        console.warn('Something went wrong.', err);
    })
    await displayContactSearch();
    
    window.location.reload(true);
}

function LeaveGroup()
{
    let data = 
        {
            method: "post",
            body: null
        }
    fetch(`/Group/LeaveGroup/${groupId}`, data).then(function (response){
        if (!response.ok){
            console.log("Failed to leave group.");
        }
        else
        {
            window.location.href = response.url;
        }
        
    }).catch(function (err) {
        console.warn('Something went wrong.', err);
    })
}