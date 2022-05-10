using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.CodeAnalysis;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Logging;
using UNIMEET.Data;

namespace UNIMEET.Areas.Identity.Pages.Account.Manage
{
    public class DownloadPersonalDataModel : PageModel
    {
        private readonly UserManager<ApplicationUser> _userManager;
        private readonly ILogger<DownloadPersonalDataModel> _logger;
        public DownloadPersonalDataModel(
            ApplicationDbContext context,
            UserManager<ApplicationUser> userManager,
            ILogger<DownloadPersonalDataModel> logger)
        {
            _userManager = userManager;
            _logger = logger;
        }

        public async Task<IActionResult> OnPostAsync()
        {
            var user = await _userManager.GetUserAsync(User);
            if (user == null)
            {
                return NotFound($"Unable to load user with ID '{_userManager.GetUserId(User)}'.");
            }

            _logger.LogInformation("User with ID '{UserId}' asked for their personal data.", _userManager.GetUserId(User));
            
            user = _userManager.Users.
                Include(u => u.CalendarUrls).
                Include(u => u.Contacts).
                Include(u => u.CalendarUrls).
                Include(u => u.Groups).
                ThenInclude(g => g.Events)
                .FirstOrDefault(u => u.Id == user.Id);
            
            if (user == null)
            {
                return NotFound($"Unable to load user with ID '{_userManager.GetUserId(User)}'.");
            }
            
            // Only include personal data for download
            var personalData = new Dictionary<string, string>();
            personalData.Add("Nickname", user.Nickname);
            personalData.Add("Username", user.UserName);
            personalData.Add("Email", user.Email);
            personalData.Add("About", user.About);
            var count = 1;
            foreach (var p in user.Groups)
            {
                
                personalData.Add("Group_"+count, p.Name);
                count+=1;

            }
            count = 1;
            foreach (var p in user.Contacts)
            {
                personalData.Add("Contact_"+count, p.Nickname);
                count++;

            }
            count = 1;
            foreach (var p in user.CalendarUrls)
            {
                personalData.Add("Url_"+count, p.Url);
                count++;

            }

            count = 1;
            foreach (var p in user.Groups)
            {
                foreach (var i in p.Events)
                {
                    personalData.Add("Event_"+count, i.Name + i.Description);
                    count++;
                }
                

            }

            var logins = await _userManager.GetLoginsAsync(user);
            foreach (var l in logins)
            {
                personalData.Add($"{l.LoginProvider} external login provider key", l.ProviderKey);
            }

            Response.Headers.Add("Content-Disposition", "attachment; filename=PersonalData.json");
            return new FileContentResult(JsonSerializer.SerializeToUtf8Bytes(personalData), "application/json");
        }
    }
}
