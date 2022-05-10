using System;
using System.Threading.Tasks;
using Ical.Net.CalendarComponents;
using UNIMEET.Models;

namespace UNIMEET.Services
{
    public class ValidEvent : IValidEvent
    {
        // Taking to account that datetime start is not after datetime end, this i check in javaScript. 
        public bool CalendarEventIn(CalendarEvent @in, Event @event)
        {
             
            
            /* If the event is after the date range */
            if (@in.DtStart.Date.Subtract(@event.DateTo).Days > 0)
            {
                return false;
            }
        
            /* If the event is  before the date range*/
            if (@in.DtEnd.Date.Subtract(@event.DateFrom).Days < 0)
            {
                return false;
            }
            
            return true;
        }

        public bool EventIn(Event @in, Event @event)
        {

            /* If the event is after the date range */
            if (@in.EventTimeFrom.Date.Subtract(@event.DateTo).Days > 0)
            {
                return false;
            }
        
            /* If the event is  before the date range*/
            if (@in.EventTimeTo.Date.Subtract(@event.DateFrom).Days < 0)
            {
                return false;
            }
            
            return true;
        }
    }
}