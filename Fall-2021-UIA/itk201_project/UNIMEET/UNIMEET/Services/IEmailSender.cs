using System.Threading.Tasks;

namespace UNIMEET.Services
{
    public interface IEmailSender
    {
        Task SendEmailAsync(string email, string subject, string htmlMessage);
    }
}