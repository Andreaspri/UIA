using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Net.Http;
using System.Threading.Tasks;
using Ical.Net.CalendarComponents;
using Ical.Net.DataTypes;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ValueGeneration.Internal;
using Microsoft.VisualStudio.Web.CodeGeneration;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using NodaTime;
using UNIMEET.Data;
using UNIMEET.Models;
using UNIMEET.Services;
using Calendar = Ical.Net.Calendar;

namespace UNIMEET.Controllers
{
    public class EventController : Controller
    {
        private readonly ApplicationDbContext _context;
        private readonly UserManager<ApplicationUser> _userManager;
        private readonly IEmailSender _smtpClient;
        private readonly IValidEvent _validEvent;
        public EventController(ApplicationDbContext context, UserManager<ApplicationUser> userManager, IEmailSender smtpClient, IValidEvent validEvent)
        {
            _context = context;
            _userManager = userManager;
            _smtpClient = smtpClient;
            _validEvent= validEvent;
        }

        private static readonly HttpClient Client = new HttpClient();
        
        private static readonly DateTime DefaultOnlyAfter = default(DateTime).AddHours(8);
        private static readonly DateTime DefaultOnlyBefore = default(DateTime).AddHours(16);
        private static readonly DateTime DefaultDuration = default(DateTime).AddMinutes(30);

        
        [Authorize]
        private static async Task<Calendar> LoadFromUriAsync(Uri uri)
        {
            // Provides a class for sending HTTP requests and receiving HTTP responses from a resource identified by a URI.
            // In a real application, this should be a long-lived object
            using (var response = await Client.GetAsync(uri))
            {
                response.EnsureSuccessStatusCode();
                var result = await response.Content.ReadAsStringAsync();
                return Calendar.Load(result);
            }
        }

        private async void NotValidUri(CalendarUrl urlObject, ApplicationUser user)
        {
            _context.CalendarUrls.Remove(urlObject);
                        
            // Content
            var subject = "Bad uri";
            var body = $"Hello {user.Nickname}, the calendar url you just added is not working! Therefore we removed it. <br>";

            await _smtpClient.SendEmailAsync(user.Email, subject, body);
        }
        
        private static List<CalendarEvent> Merge(List<CalendarEvent> events)
        {
            var mergedEvents = new List<CalendarEvent>();
            if (events.Count == 0)
            {
                return mergedEvents;
            }

            var currentEvent = events[0];
            for (var i = 1; i < events.Count; ++i)
            {
                if (events[i].Start.Subtract(currentEvent.End).TotalMinutes <= 0)
                {
                    if (events[i].End.Subtract(currentEvent.End).TotalMinutes > 0)
                    {
                        currentEvent.End = events[i].End;
                    }

                }
                else
                {
                    mergedEvents.Add(currentEvent);
                    currentEvent = events[i];
                }

            }
            mergedEvents.Add(events[events.Count-1]);
            
            return mergedEvents;
        }

        // Call this to return matching calendar windows in a partial view.
        [Authorize]
        [HttpPost]
        public async Task<IActionResult> CalendarAlgorithm()
        {

            // Creating new event and storing the raw data from the form in it. 
            Event @event = new Event
            {
                Name = Request.Form["Name"],
                Summary = Request.Form["Name"],
                Description = Request.Form["Description"],
                DateFrom = Convert.ToDateTime(Request.Form["DateFrom"]),
                DateTo = Convert.ToDateTime(Request.Form["DateTo"]),
                OnlyAfter = Convert.ToDateTime(Request.Form["OnlyAfter"]),
                OnlyBefore = Convert.ToDateTime(Request.Form["OnlyBefore"]),
                Duration = Convert.ToDateTime(Request.Form["Duration"]),
                GroupId = Convert.ToInt32(Request.Form["GroupId"])
            };

            if (ModelState.IsValid)
            {
                // Query for the group.
                var group = await _context.Groups
                    .Include(u => u.Events) // Have to include Events, because this is not default.
                    .Include(u => u.ApplicationUsers).ThenInclude(v => v.CalendarUrls) // Have to include CalendarUrls, because this is not default.
                    .FirstOrDefaultAsync(g => g.Id == @event.GroupId);
                if (group == null)
                {
                    return NotFound();
                }
                
                var mergedCalendar = new Calendar();
                foreach (var user in group.ApplicationUsers)
                {
                    // Adding all the events from the users calendars. 
                    foreach (var urlObject in user.CalendarUrls)
                    {
                        if (Uri.TryCreate(urlObject.Url, UriKind.Absolute, out var uri) 
                             && (uri.Scheme == Uri.UriSchemeHttp || uri.Scheme == Uri.UriSchemeHttps))
                        {
                            try
                            {
                                var result = await LoadFromUriAsync(uri);
                                var relevantEvents = result.GetOccurrences(@event.DateFrom, @event.DateTo.AddDays(1))
                                    .Select(o => o.Source)
                                    .Cast<CalendarEvent>()
                                    .Distinct()
                                    .ToList();
                                foreach (var relevantEvent in relevantEvents)
                                {
                                    if (relevantEvent.Duration.TotalMinutes > 0)
                                    {
                                        var timeZoneString = DateTimeZoneProviders.Bcl.GetSystemDefault().ToString();
                                        relevantEvent.DtStart = relevantEvent.DtStart.ToTimeZone(timeZoneString);
                                        relevantEvent.DtEnd = relevantEvent.DtEnd.ToTimeZone(timeZoneString);

                                        if (_validEvent.CalendarEventIn(relevantEvent, @event))
                                        {
                                            mergedCalendar.Events.Add(relevantEvent);
                                        }
                                    }
                                }
                            }
                            catch (Exception e)
                            {
                                Console.WriteLine(e);
                                NotValidUri(urlObject, user);   
                            }
                            
                        }
                        else
                        {
                            NotValidUri(urlObject, user);
                        }
                    }
                }
                // Adding all the shared events in the group.
                foreach (var groupEvent in @group.Events)
                {
                    if (_validEvent.EventIn(groupEvent, @event))
                    {
                        var iCalEvent = new CalendarEvent
                        {
                            // Event data:
                            Start = new CalDateTime(groupEvent.EventTimeFrom.Year, groupEvent.EventTimeFrom.Month, groupEvent.EventTimeFrom.Day,
                                groupEvent.EventTimeFrom.Hour, groupEvent.EventTimeFrom.Minute, groupEvent.EventTimeFrom.Second),
                            End = new CalDateTime(groupEvent.EventTimeTo.Year, groupEvent.EventTimeTo.Month, groupEvent.EventTimeTo.Day,
                                groupEvent.EventTimeTo.Hour, groupEvent.EventTimeTo.Minute, groupEvent.EventTimeTo.Second)
                        };
                        mergedCalendar.Events.Add(iCalEvent);
                    }
                }
                // Add blocking events
                DateTime tempDate = @event.DateTo;
                for (DateTime i = @event.DateFrom; i <= tempDate.AddDays(1); i = i.AddDays(1))
                {
                    var iCalEvent = new CalendarEvent
                    {
                        Start = new CalDateTime(i.AddDays(-1).Year, i.AddDays(-1).Month, i.AddDays(-1).Day,
                            @event.OnlyBefore.Hour, @event.OnlyBefore.Minute, @event.OnlyBefore.Second),
                        End = new CalDateTime(i.Year, i.Month, i.Day,
                            @event.OnlyAfter.Hour, @event.OnlyAfter.Minute, @event.OnlyAfter.Second)
                    };
                    mergedCalendar.Events.Add(iCalEvent);
                }

                var sorted = mergedCalendar.Events.OrderBy(u => u.Start).ToList();
                var sortedEvents = Merge(sorted);
                var dateWindow = new List<TimeSlot>();
                
                for (var i = 0; i < sortedEvents.Count; ++i)
                {
                    if (i + 1 < sortedEvents.Count)
                    {
                        TimeSpan durationTimeSpan = new TimeSpan(@event.Duration.Hour, @event.Duration.Minute, 0);
                        if (sortedEvents[i + 1].Start.Subtract(sortedEvents[i].End).TotalMinutes > durationTimeSpan.TotalMinutes)
                        {
                            var newEvent = new TimeSlot();
                            newEvent.Start = newEvent.Start = new DateTime(sortedEvents[i].End.Year, sortedEvents[i].End.Month, sortedEvents[i].End.Day, sortedEvents[i].End.Hour, sortedEvents[i].End.Minute, sortedEvents[i].End.Second);
                            newEvent.End = new DateTime(sortedEvents[i+1].Start.Year, sortedEvents[i+1].Start.Month, sortedEvents[i+1].Start.Day, sortedEvents[i+1].Start.Hour, sortedEvents[i+1].Start.Minute, sortedEvents[i+1].Start.Second);
                            dateWindow.Add(newEvent);
                        }
                    }
                }
                await _context.SaveChangesAsync();
                
                var jsonTimeslots = JObject.Parse(JsonConvert.SerializeObject(@event));
                jsonTimeslots["TimeSlots"] = JsonConvert.SerializeObject(dateWindow);
                return Ok(jsonTimeslots.ToString());
            }
            
            return Problem();
        }
        
        
        /* This function gets the users groups and returns a view. */
        [Authorize]
        [Route("Event/Create/{groupId:}")]
        [HttpGet]
        public IActionResult Create(string groupId)
        {
            if (groupId == null)
            {
                return NotFound();
            }
            ViewBag.GroupId = Int32.Parse(groupId);
            ViewBag.OnlyBefore = DefaultOnlyBefore;
            ViewBag.OnlyAfter = DefaultOnlyAfter;
            ViewBag.DefaultDuration = DefaultDuration;
            
            return PartialView("_EventPartial");
        }

        // POST: Event/CreateEvent.
        // This functions takes in a form for an event. This event is stored in a group in the database. 
        [HttpPost]
        [Authorize]
        public async Task<IActionResult> CreateEvent()
        {
            var timeSpan = new TimeSpan(0, 0, (int)Math.Floor(float.Parse(Request.Form["Duration"], CultureInfo.InvariantCulture.NumberFormat)));
            var tempDateTime = new DateTime(2021,10,10,timeSpan.Hours,timeSpan.Minutes,timeSpan.Seconds);
            // Creating new event and storing the raw data from the form in it. 
            var @event = new Event
            {
                Name = Request.Form["Name"],
                Summary = Request.Form["Summary"],
                Description = Request.Form["Description"],
                Sequence = null,
                Duration = tempDateTime,
                EventTimeFrom = DateTime.Parse(Request.Form["EventTimeFrom"]),
                EventTimeTo = DateTime.Parse(Request.Form["EventTimeTo"]),
                GroupId = Convert.ToInt32(Request.Form["GroupId"]),
            };
            
            // Query for the group.
            var group = await _context.Groups
                .Include(u => u.Events) // Have to include Events, because this is not default.
                .Include(u => u.ApplicationUsers).ThenInclude(v => v.CalendarUrls) // Have to include CalendarUrls, because this is not default.
                .FirstOrDefaultAsync(g => g.Id == @event.GroupId);
            
            if (group == null)
            {
                return NotFound();
            }

            // Adding event to the group-
            _context.Event.Add(@event);
            // Storing changes in database.
            await _context.SaveChangesAsync();

            var user =await _userManager.GetUserAsync(User);
            
            // Sending mail to members when event is created.
            foreach (var  member in group.ApplicationUsers)
            {
                await _smtpClient.SendEmailAsync(member.Email, "Event Created",
                    user.Nickname + " just created a new event " + @event.Name + '.' + "<br>"
                    + "Go to your private calendar for more details about the event.");
            }

            ViewBag.GroupId = @event.GroupId;
            ViewBag.OnlyBefore = DefaultOnlyBefore;
            ViewBag.OnlyAfter = DefaultOnlyAfter;
            ViewBag.DefaultDuration = DefaultDuration;
            return PartialView("_EventPartial");
        }
    }
}
