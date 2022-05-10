using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Data.Entity;
using Microsoft.AspNetCore.Identity;
using UNIMEET.Models;


namespace UNIMEET.Data
{
    public class ApplicationUser : IdentityUser
    {   
        [Required]
        public string Nickname { get; set; }
        public string CalenderFile { get; set; }
        
        public string Firstname { get; set; }
        
        public string Lastname { get; set; }
        
        public string About { get; set; }
        
        // Making one to many relationships
        public ICollection<CalendarUrl> CalendarUrls { get; set; } = new List<CalendarUrl>();



        // Making a many to many relationship between users and groups
        public ICollection<Group> Groups { get; set; } = new List<Group>();
        
        
        
        // Creating many to many relationships toward itself for contacts
        public ICollection<ApplicationUser> Contacts { get; set; } = new List<ApplicationUser>();
        public ICollection<ApplicationUser> OtherUser { get; set; } = new List<ApplicationUser>();
        
        // Creating many to many relationships toward itself for contact requests
        public ICollection<ApplicationUser> ContactRequestSender { get; set; } = new List<ApplicationUser>();
        public ICollection<ApplicationUser> ContactRequestReceiver { get; set; } = new List<ApplicationUser>();

  

    }
}