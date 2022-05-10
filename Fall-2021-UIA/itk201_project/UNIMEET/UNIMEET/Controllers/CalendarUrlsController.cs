using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using Ical.Net;
using Ical.Net.CalendarComponents;
using Ical.Net.DataTypes;
using Ical.Net.Serialization;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding.Validation;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using UNIMEET.Data;
using UNIMEET.Models;

namespace UNIMEET.Controllers
{
    public class CalendarUrlsController : Controller
    {
        private readonly UserManager<ApplicationUser> _userManager;

        public CalendarUrlsController(UserManager<ApplicationUser> userManager)
        {
            _userManager = userManager;
        }
        
        
        
        /* This function handle the get request from other calendars. The function returns a page with an ics-file(calendar format) that can be read. Everyone have access to this calendar if they have the url.
        To lower the risk, we generate a random key that is stored in the application user. TODO : Warn the user to not share this url in the email.*/
        [HttpGet]
        [ResponseCache(NoStore = true, Duration = 0, Location=ResponseCacheLocation.None)]
        [Route("CalendarUrls/{key:}/{email:}/calendar.ics")]
        public async Task<ActionResult> GetCalendar(string email, string key)
        {
            // Query for a user.
            var user = await _userManager.Users
                .Include(u => u.Groups)
                .ThenInclude(x => x.Events) // Including Groups, because this is not default. 
                .Where(x => x.CalenderFile == key) // Checking if the key is correct.
                .Where(x => x.Email == email) // Checking if the email is correct.
                .AsNoTracking()
                .FirstOrDefaultAsync();
            if (user == null)
            {
                return NotFound();
            }
            try
            {
                // Generating the calendar object.
                var calendar = new Calendar();
                foreach (var group in user.Groups)
                {
                    foreach (var myEvent in group.Events.OrderBy(u => u.EventTimeFrom))
                    {
                        var iCalEvent = new CalendarEvent
                        {
                            // Event data:
                            Name = "VEVENT",
                            Summary = "Group name: " + group.Name + "\n" + myEvent.Summary,
                            Uid = myEvent.Id + "6f67449c-e123-4163-b0f1-0ac03bc4bc72",
                            Description = myEvent.Description,
                            Created = new CalDateTime(myEvent.EventTimeFrom.Year, myEvent.EventTimeFrom.Month, myEvent.EventTimeFrom.Day,
                                myEvent.EventTimeFrom.Hour, myEvent.EventTimeFrom.Minute, myEvent.EventTimeFrom.Second),
                            Duration = new TimeSpan(myEvent.Duration.Hour,myEvent.Duration.Minute,myEvent.Duration.Second),
                            Start = new CalDateTime(myEvent.EventTimeFrom.Year, myEvent.EventTimeFrom.Month, myEvent.EventTimeFrom.Day,
                                myEvent.EventTimeFrom.Hour, myEvent.EventTimeFrom.Minute, myEvent.EventTimeFrom.Second),
                            End = new CalDateTime(myEvent.EventTimeTo.Year, myEvent.EventTimeTo.Month, myEvent.EventTimeTo.Day,
                                myEvent.EventTimeTo.Hour, myEvent.EventTimeTo.Minute, myEvent.EventTimeTo.Second)
                        };
                        // Adding the event to the calendar object.
                        calendar.Events.Add(iCalEvent);
                    }
                }
                // Converting the calendar to a string and returning it. 
                var iCalSerializer = new CalendarSerializer();
                string myResult = iCalSerializer.SerializeToString(calendar);
                var file = File(Encoding.UTF8.GetBytes(myResult),"text/calendar; charset=UTF-8","basic.ics");
                file.LastModified = DateTimeOffset.Now;
                return file;
            }
            catch
            {
                return NotFound();
            }
            
        }
    }
}
