using System.ComponentModel.DataAnnotations;
using System.Net.Mime;
using UNIMEET.Data;

namespace UNIMEET.Models
{
    public class CalendarUrl
    {
        public CalendarUrl() {}

        public CalendarUrl(string url)
        {
            Url = url;
        }
        
        public int Id { get; set; }
        
        [Required]
        [StringLength(200)]
        public string Url { get; set; }


        // Foreign key 
        public string ApplicationUserId { get; set; }
        
        // Navigation property
        public ApplicationUser ApplicationUser { get; set; }

    }
}