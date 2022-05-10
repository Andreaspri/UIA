using System.Threading.Tasks;
using Ical.Net.CalendarComponents;
using UNIMEET.Models;

namespace UNIMEET.Services
{
    public interface IValidEvent
    {
        bool CalendarEventIn(CalendarEvent @in, Event @event);

        bool EventIn(Event @in, Event @event);
    }
}