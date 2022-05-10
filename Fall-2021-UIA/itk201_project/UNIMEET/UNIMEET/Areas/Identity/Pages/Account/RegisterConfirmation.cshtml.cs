using System.Net.Mail;
using Microsoft.AspNetCore.Authorization;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.WebUtilities;
using UNIMEET.Data;
using UNIMEET.Areas.Identity.Pages.Account;
using UNIMEET.Services;

namespace UNIMEET.Areas.Identity.Pages.Account
{
    [AllowAnonymous]
    public class RegisterConfirmationModel : PageModel
    {
        private readonly UserManager<ApplicationUser> _userManager;
        private readonly IEmailSender _smtpClient;

        public RegisterConfirmationModel(UserManager<ApplicationUser> userManager, IEmailSender smtpClient)
        {
            _userManager = userManager;
            _smtpClient = smtpClient;
        }

        public string Email { get; set; }

        public bool DisplayConfirmAccountLink { get; set; }

        public string EmailConfirmationUrl { get; set; }

        public async Task<IActionResult> OnGetAsync(string email, string returnUrl = null)
        {
            if (email == null)
            {
                return RedirectToPage("/Index");
            }

            var user = await _userManager.FindByEmailAsync(email);
            if (user == null)
            {
                return NotFound($"Unable to load user with email '{email}'.");
            }

            Email = email;

            DisplayConfirmAccountLink = false;
            
            var userId = await _userManager.GetUserIdAsync(user);
            var code = await _userManager.GenerateEmailConfirmationTokenAsync(user);
            code = WebEncoders.Base64UrlEncode(Encoding.UTF8.GetBytes(code));
            EmailConfirmationUrl = Url.Page(
                "/Account/ConfirmEmail",
                pageHandler: null,
                values: new { area = "Identity", userId = userId, code = code, returnUrl = returnUrl },
                protocol: Request.Scheme);
            
                    
            // Content
            var subject = "Email confirmation";
            var body = $"Hello {user.Nickname}, you need to confirm your email address <a href={EmailConfirmationUrl}>confirm email</a>. <br>";

            await _smtpClient.SendEmailAsync(user.Email, subject, body);
            
            return Page();
        }
    }
}
