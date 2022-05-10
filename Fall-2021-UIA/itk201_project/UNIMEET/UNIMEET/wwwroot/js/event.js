
let CALENDAR;



function validateDateBetweenTwoDates(fromDate,toDate,givenDate){
    return getValidDate(givenDate) <= getValidDate(toDate) && getValidDate(givenDate) >= getValidDate(fromDate);
}





let raw = document.getElementById("group-id");
let Id = raw.attributes["value"].value;
fetch(`/Event/Create/${Id}`).then(function (response){
    return response.text();
}).then(function (html){
    document.getElementById("event-showcase").innerHTML = html;
}).catch(function (err) {
    console.warn('Something went wrong.', err);
})

var getValidDate = function(d){ return new Date(d) }




function loadCalendar(timeslots) {
    let TIMESLOTS = JSON.parse(timeslots["TimeSlots"]);
    
    let viableTimeSlots = []
    
    for (let i = 0; i < TIMESLOTS.length; i++) 
    {
        viableTimeSlots.push({
            start: TIMESLOTS[i]['Start'],
            end: TIMESLOTS[i]['End'],
            display: 'background',
            color: 'green'
        })
    }
    
    let calendarEl = document.getElementById('timeSlotsCalendar');

    CALENDAR = new FullCalendar.Calendar(calendarEl, {
        initialView: 'timeGridWeek',
        snapDuration: 1,
        selectable: 'true',
        contentHeight: 'auto',
        timeZone: 'CET',
        events: viableTimeSlots,
        headerToolbar: {
            left: 'prev,next today',
            center: 'title',
            right: 'dayGridMonth,timeGridWeek'
        },
        validRange:
            {
                start: TIMESLOTS[0]['Start'],
                end: TIMESLOTS[TIMESLOTS.length - 1]['End'],
            },
        select: function(info)
        {
            let checkOldEvent = CALENDAR.getEventById(0)
            if (checkOldEvent)
            {
                checkOldEvent.remove()
            }
            
            let viableTimeSlots = []

            for (let i = 0; i < TIMESLOTS.length; i++)
            {
                viableTimeSlots.push({
                    start: TIMESLOTS[i]['Start'],
                    end: TIMESLOTS[i]['End'],
                })
            }

            for (let i = 0; i < TIMESLOTS.length; i++) 
            {
                    if (validateDateBetweenTwoDates(TIMESLOTS[i]['Start'],TIMESLOTS[i]['End'],info.startStr) &&
                    validateDateBetweenTwoDates(TIMESLOTS[i]['Start'],TIMESLOTS[i]['End'],info.endStr))
                    {
                        CALENDAR.addEventSource([{
                            id: timeslots["Id"],
                            start: info.startStr,
                            end: info.endStr,
                            title: timeslots['Name'],
                            constraint: viableTimeSlots,
                            durationEditable: 'true',
                            editable: 'true',
                            extendedProps:
                                {
                                    Name: timeslots['Name'],
                                    Description: timeslots['Description'],
                                    Summary: timeslots['Name'],
                                    GroupId: timeslots['GroupId'],
                                    Sequence: timeslots['Sequence'],
                                }
                        }])
                        break
                    }
            }


        }
        
    })
    

    CALENDAR.render();
    document.getElementById("submitCalenderEvent").type="button"
    
}

function submitCalenderEvent()
{
    let calenderEvent = CALENDAR.getEventById(0);
    let form_data = new FormData();
    let start = new Date(calenderEvent['startStr']);
    let end = new Date( calenderEvent['endStr'])
    form_data.append("Name", calenderEvent['extendedProps']['Name']);
    form_data.append("Summary", calenderEvent['extendedProps']['Name']);
    form_data.append("Description", calenderEvent['extendedProps']['Description']);
    form_data.append("EventTimeFrom", calenderEvent['startStr']);
    form_data.append("EventTimeTo", calenderEvent['endStr']);
    form_data.append("Duration", ((end.getTime() - start.getTime())/1000).toString());
    form_data.append("GroupId", calenderEvent['extendedProps']['GroupId']);
    form_data.append("Sequence", calenderEvent['extendedProps']['Sequence']);
    
    // Sending the FormData with a post request to CalendarAlgorithm.
    fetch("/Event/CreateEvent", {method: "post", body: form_data}).then(function (response){
        // Converting the response to text.
        if (response.ok)
        {
            return response.text();
        }
        else 
        {
            let popup = document.getElementById("calendarEventSuccessfullyCreated");
            popup.className = "calendar-event-not-successfully-created";
            popup.innerHTML = "Something went wrong when trying to create a new event for your group";
            throw "exit";
        }
    }).then(function (html){
        let event = document.getElementById("event-showcase");
        event.innerHTML = html;
        let popup = document.getElementById("calendarEventSuccessfullyCreated");
        popup.className = "calendar-event-successfully-created";
        popup.innerHTML = "Successfully added a new event to your group";
    }).catch(function (err) {
        console.warn('Something went wrong.', err);
        
    })
    document.getElementById("submitCalenderEvent").type="hidden";
    CALENDAR.destroy();
    
}


function hideErrorMessages()
{
    document.getElementById("Hour-error").style.visibility = "hidden";
    document.getElementById("Min-error").style.visibility = "hidden";
    document.getElementById("OnlyAfterError").style.visibility = "hidden";
    document.getElementById("OnlyBeforeError").style.visibility = "hidden";
    document.getElementById("DateFromError").style.visibility = "hidden";
    document.getElementById("DateToError").style.visibility = "hidden";
}

// Form from _EventPartial.
async function timeHandler(form){

    let popup = document.getElementById("calendarEventSuccessfullyCreated")
    popup.className = ""
    popup.innerHTML = ""
    
    // Converting raw form to FormData.
    let data = new FormData(form);
    let inputError = false;
    let char_error = false;
    
    let hours = await document.getElementById("Hour").value;
    let minutes = await document.getElementById("Min").value;
    if (isNaN(hours))
    {
        document.getElementById("Hour-error").innerHTML = "Hours cant be a string!";
        document.getElementById("Hour-error").style.visibility = "visible";
        inputError = true;
        char_error = true;
    }
    if (isNaN(minutes))
    {
        document.getElementById("Min-error").innerHTML = "Minutes cant be a string!";
        document.getElementById("Min-error").style.visibility = "visible";
        inputError = true;
        char_error = true;
    }
    
    if (parseInt(minutes) + parseInt(hours) <= 0 && !char_error)
    {
        inputError = true;
        document.getElementById("Hour-error").innerHTML = "Zero or negative time is not valid!";
        document.getElementById("Hour-error").style.visibility = "visible";
        document.getElementById("Min-error").innerHTML = "Zero or negative time is not valid!";
        document.getElementById("Min-error").style.visibility = "visible";
    }
    
    let dateFrom = new Date((await document.getElementById("DateFrom").value));
    let dateTo = new Date(await document.getElementById("DateTo").value);
    
    if (dateTo-dateFrom <= 0)
    {
        document.getElementById("DateFromError").innerHTML = "Bad input!";
        document.getElementById("DateToError").innerHTML = "Bad input!";
        document.getElementById("DateFromError").style.visibility = "visible";
        document.getElementById("DateToError").style.visibility = "visible";
        inputError = true;
    }
    
    let onlyBefore = new Date("2019-01-01T" + (await document.getElementById("OnlyBefore").value));
    let onlyAfter = new Date("2019-01-01T" + (await document.getElementById("OnlyAfter").value));
    
    if (onlyBefore-onlyAfter <= 0)
    {
        document.getElementById("OnlyAfterError").innerHTML = "Bad input!";
        document.getElementById("OnlyBeforeError").innerHTML = "Bad input!";
        document.getElementById("OnlyAfterError").style.visibility = "visible";
        document.getElementById("OnlyBeforeError").style.visibility = "visible";
        inputError = true;
    }
      
    if (!inputError)
    {
        let date = new Date();
        date.setHours(hours);
        date.setMinutes(minutes);
        data.set("Duration", date.toLocaleTimeString())
        // Sending the FormData with a post request to CalendarAlgorithm.
        fetch("/Event/CalendarAlgorithm", {method: "post", body: data}).then(function (response){
            // Converting the response to text.
            return response.json();
        }).then(function (json){
            hideErrorMessages();
            loadCalendar(json);
        }).catch(function (err) {
            console.warn('Something went wrong.', err);
        })
    }
}