# Date events in ical format:
#   BEGIN:VEVENT
#   DTSTART:20211015T071500Z
#   DTEND:20211015T073000Z
#   DTSTAMP:20211018T144435Z
#   UID:uniqueID_scramble@google.com
#   ATTENDEE;X-NUM-GUESTS=0:mailto:email@gmail.com
#   SUMMARY:Busy
#   END:VEVENT

# Assume we have managed to build a list for each calendar consisting of [start,end] times as such:
SampleCalendarInput1 = [["1000", "1200"], ["1500", "1630"], ["1730", "1900"]]
SampleCalendarInput2 = [["0800", "1100"], ["1200", "1430"], ["1930", "2000"]]
# The above is simplified to get an understanding of the logic. Actual times are in zulutime.
# Meeting time in minutes
minimum_time_window = 40
# Meeting blacklist (not available for booking)
earliest = "0800"  # Lowest possible is 0000
latest = "2100"  # Highest possible is 2359

# Assumes we feed it with zulutime, and that zulutime can be compared like this.
def compare_times(time1, time2):
    if time1 > time2:
        return 1  # time 1 is biggest
    elif time2 > time1:
        return -1  # time 2 is biggest
    else:
        return 0  # times are equal


def flatten_calendars(cal1, cal2, earliest, latest):
    first_time = min(int(cal1[0][0]), int(cal2[0][0]))
    # more flatten logic here, not important for overall logic


# Assumes a calendar with a start and end time on each end of the calendar.
def remove_invalid_timeslots(calendar, min_window):
    fixed_timeslots = []
    if len(calendar) > 0:
        # Every window minus the last
        for i in range(len(calendar) - 1):
            if calendar[i + 1][0] - calendar[i][1] > min_window:
                fixed_timeslots.append([calendar[i][1], calendar[i + 1][0]])
    return fixed_timeslots


meeting_window = flatten_calendars(
    SampleCalendarInput1, SampleCalendarInput2, earliest, latest
)
# Should get a result like this:
meeting_window = [
    ["0000", earliest],
    ["0800", "1430"],
    ["1500", "1630"],
    ["1730", "1900"],
    ["1930", "2000"],
    [latest, "2359"],
]

meeting_window = remove_invalid_timeslots(meeting_window, minimum_time_window)
# Should get a result like this:
meeting_window = [["1630", "1730"], ["2000", "2100"]]

# let users pick between available time slots with an offset.
# This means they could for instance get a 5 hour long window, but offset their
# meeting with X minutes, to give some space around the time slots.
# Snap to every 5 minutes.
