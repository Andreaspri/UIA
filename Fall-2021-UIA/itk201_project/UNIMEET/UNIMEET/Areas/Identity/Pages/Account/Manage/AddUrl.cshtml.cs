using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using Humanizer;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Internal;
using Npgsql;
using SQLitePCL;
using UNIMEET.Data;
using UNIMEET.Models;
using UNIMEET.Services;


namespace UNIMEET.Areas.Identity.Pages.Account.Manage
{
    public partial class AddUrl : PageModel
    {
        
        private readonly UserManager<ApplicationUser> _userManager;
        private readonly ApplicationDbContext _context;
        private readonly IEmailSender _smtpClient;
        
        public AddUrl(ApplicationDbContext context, UserManager<ApplicationUser> userManager, IEmailSender smtpClient)

        {
            _userManager = userManager;
            _context = context;
            _smtpClient = smtpClient;

        }
        
        [TempData]
        public string StatusMessage { get; set; }
        
        
        [BindProperty]
        public InputModel Input { get; set; }
        
        public class InputModel
        {
            [Display(Name = "New Calendar Url")]
            public string NewUrl { get; set; }
            
            [Display(Name = "Remove calendar url")]
            public int UrlId { get; set; }
            
            public ICollection<CalendarUrl> Urls { get; set;}
            
        }
        
        
        private async Task LoadAsync(ApplicationUser user)
        {
            Input = new InputModel
            {

                NewUrl = null,
                UrlId = 0,
                Urls = user.CalendarUrls
            };
            await Task.CompletedTask;
        }
        
        
        public async Task<IActionResult> OnGetAsync()
        {
            var user = await _userManager.GetUserAsync(User);
            if (user == null)
            {
                return NotFound($"Unable to load user with ID '{_userManager.GetUserId(User)}'.");
            }
            
            user = _userManager.Users.Include(u => u.CalendarUrls)
                .FirstOrDefault(u => u.Id == user.Id);
            

            await LoadAsync(user);
            

            return Page();
        }
        
        
        public async Task<IActionResult> OnPostResendCalendarEmailAsync()
        {
            var user = await _userManager.GetUserAsync(User);
            if (user == null)
            {
                return NotFound($"Unable to load user with ID '{_userManager.GetUserId(User)}'.");
            }

            var subject = "Calendar url";
            var body = $"Here is your calender link: <a href=https://{Request.Headers["Host"].ToString()}/CalendarUrls/{user.CalenderFile}/{user.Email}/calendar.ics>copy this link</a>. <br>" +
                       "Dont share this link to anyone! <br>" +
                       "Tutorial for importing events in google calendar: <a href=https://support.google.com/calendar/answer/37118?hl=en&co=GENIE.Platform%3DDesktop>tutorial</a>. <br>";
            await _smtpClient.SendEmailAsync(user.Email, subject, body);
            
            return Redirect(Request.Headers["Referer"].ToString());
        }

        public async Task<IActionResult> OnPostGenerateNewCalendarCode()
        {
            var user = await _userManager.GetUserAsync(User);
            if (user == null)
            {
                return NotFound($"Unable to load user with ID '{_userManager.GetUserId(User)}'.");
            }
            
            Random random = new Random();
            int length = 16;
            var rString = "";
            for (var i = 0; i < length; i++)
            {
                rString += ((char)(random.Next(1, 26) + 64)).ToString().ToLower();
            }

            user.CalenderFile = rString;
            await _context.SaveChangesAsync();

            var subject = "New calendar url";
            var body = $"Here is your calender link: <a href=https://{Request.Headers["Host"].ToString()}/CalendarUrls/{user.CalenderFile}/{user.Email}/calendar.ics>copy this link</a>. <br>" +
                       "Dont share this link to anyone! <br>" +
                       "Tutorial for importing events in google calendar: <a href=https://support.google.com/calendar/answer/37118?hl=en&co=GENIE.Platform%3DDesktop>tutorial</a>. <br>";
            await _smtpClient.SendEmailAsync(user.Email, subject, body);
            
            return Redirect(Request.Headers["Referer"].ToString());
            
            

        }


        public async Task<IActionResult> OnPostNewUrlAsync()
        {
            if (Input.NewUrl == null) return RedirectToPage();
            var user = await _userManager.GetUserAsync(User);
            user = _userManager.Users
                .Include(u => u.CalendarUrls)
                .FirstOrDefault(u => u.Id == user.Id);
            if (user == null)
            {
                return NotFound($"Unable to load user with ID '{_userManager.GetUserId(User)}'.");
            }

            if (user.CalendarUrls.All(c => c.Url != Input.NewUrl))
            {
                user.CalendarUrls.Add(new CalendarUrl(Input.NewUrl));
                await _context.SaveChangesAsync();
                
                StatusMessage = "Successfully added a new calendar url.";

                return RedirectToPage();
            }
          
            StatusMessage = "This calendar url is already added";

            return RedirectToPage();

        }
        
        
        public async Task<IActionResult> OnPostDeleteUrlAsync()
        {
            var user = await _userManager.GetUserAsync(User);
            user = _userManager.Users
                .Include(u => u.CalendarUrls)
                .FirstOrDefault(u => u.Id == user.Id);
            if (user == null)
            {
                return NotFound($"Unable to load user with ID '{_userManager.GetUserId(User)}'.");
            }


            if (Input.UrlId == 0)
            {
                return RedirectToPage();
            }

            var url = user.CalendarUrls.FirstOrDefault(u => u.Id == Input.UrlId);
                if (url == null)
                {
                    StatusMessage = "Something went wrong.";
                    return RedirectToPage();
                }
            _context.CalendarUrls.Remove(url);
            await _context.SaveChangesAsync();
            StatusMessage = "Successfully deleted calendar url.";
            return RedirectToPage();


        }
        
        
        
    }
}