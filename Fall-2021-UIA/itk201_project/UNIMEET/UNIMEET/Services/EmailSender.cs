using System;
using System.Net;
using System.Net.Mail;
using System.Threading.Tasks;

namespace UNIMEET.Services
{
    public class EmailSender : IEmailSender
    {

        public async Task SendEmailAsync(string email, string subject, string htmlMessage)
        {
            using (var smtp = new SmtpClient("smtp.gmail.com", 587)
            {
                Credentials = new NetworkCredential("unimeet.mail@gmail.com", "Password1."),
                DeliveryMethod = SmtpDeliveryMethod.Network,
                EnableSsl = true
                
            })
            {
                // Setting up the mail.
                MailMessage mail = new MailMessage
                {
                    IsBodyHtml = true,
                    From = new MailAddress("unimeet.mail@gmail.com", "UNIMEET"),

                    // Content
                    Subject = subject,
                    Body = htmlMessage
                };

                mail.To.Add(new MailAddress(email));
                try
                {
                    await smtp.SendMailAsync(mail);
                }
                catch(SmtpException ex)
                {
                    Console.WriteLine(ex);
                }
                
            }
        }
    }
}