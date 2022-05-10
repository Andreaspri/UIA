// Searching for friends/contacts when creating group

async function searchFriend() {
    let searchString = document.getElementById("searchbarContacts").value;

    let result = await fetch("/ApplicationUser/SearchApplicationContact?searchString=" + searchString)

    document.getElementById("contactsResult").innerHTML = await result.text();
}

// this function appends chosen members to a list and adds id as attribute
// TODO: querySelector could be useful for finding elements by other means than just id

async function selectFriends(selected_friend, friend_id) {
    let id_checker = document.getElementById(friend_id)
    if (!id_checker){
        let ul = document.getElementById("selectedList");
        let li = document.createElement("li");
        let div_name = document.createElement("div");
        
        let delete_btn = document.createElement("img");
        delete_btn.setAttribute('src', '/assets/img/delete-stop-svgrepo-com.svg');
        delete_btn.setAttribute('width', "15");
        delete_btn.setAttribute('height', "15");
        
        
        div_name.innerHTML = selected_friend
        div_name.setAttribute(`id`, friend_id);
        div_name.setAttribute(`class`, "changeCursor");

        li.onclick = remove_selected;
        
        div_name.appendChild(delete_btn);
        li.appendChild(div_name);
        ul.appendChild(li);
    }
}

// removes the selected name inside a <li>
async function remove_selected() {
    this.remove();
}


// sends a list of chosen members to create-group-with-members controller
async function create_group_with_members() {

    let groupName = await document.getElementById("group_name").value;
    let ul = document.getElementById("selectedList");
    let formData = new FormData();
    let list = ul.getElementsByTagName('div');
    let selected = [];

    for (var i = 0; i < list.length; ++i) {
        selected.push(list[i].getAttribute('id'));
    }
    
    formData.append("selected", JSON.stringify(selected));
    formData.append("name", groupName);

    fetch(`/Group/CreateGroupWithMembers`, {method: "post", body: formData}).then(function (response) {
        if (!response.ok) {
            console.log("Failed to store application users to the database.");
        } else {
            window.location.href = response.url;
        }

    }).catch(function (err) {
        console.warn('Something went wrong.', err);
    })
}








