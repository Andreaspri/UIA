using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Mail;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.WebUtilities;
using UNIMEET.Data;
using UNIMEET.Services;

namespace UNIMEET.Areas.Identity.Pages.Account
{
    [AllowAnonymous]
    public class ConfirmEmailModel : PageModel
    {
        private readonly UserManager<ApplicationUser> _userManager;
        private readonly IEmailSender _smtpClient;

        public ConfirmEmailModel(UserManager<ApplicationUser> userManager, IEmailSender smtpClient)
        {
            _userManager = userManager;
            _smtpClient = smtpClient;
        }

        [TempData]
        public string StatusMessage { get; set; }

        public async Task<IActionResult> OnGetAsync(string userId, string code)
        {
            if (userId == null || code == null)
            {
                return RedirectToPage("/Index");
            }

            var user = await _userManager.FindByIdAsync(userId);
            if (user == null)
            {
                return NotFound($"Unable to load user with ID '{userId}'.");
            }

            code = Encoding.UTF8.GetString(WebEncoders.Base64UrlDecode(code));
            var result = await _userManager.ConfirmEmailAsync(user, code);
            StatusMessage = result.Succeeded ? "Thank you for confirming your email." : "Error confirming your email.";
            if (result.Succeeded)
            {
                // Content
                var subject = "Welcome to UNIMEET";
                var body = $"Hello {user.Nickname}, you just signed up to our website. <br>" +
                            $"Here is your calender link: <a href=https://{Request.Headers["Host"].ToString()}/CalendarUrls/{user.CalenderFile}/{user.Email}/calendar.ics>copy this link</a>. <br>" +
                            "Dont share this link to anyone! <br>" +
                            "Tutorial for importing events in google calendar: <a href=https://support.google.com/calendar/answer/37118?hl=en&co=GENIE.Platform%3DDesktop>tutorial</a>. <br>";
                await _smtpClient.SendEmailAsync(user.Email, subject, body);
            }
            return Page();
        }
    }
}
