using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using UNIMEET.Data;

namespace UNIMEET.Models
{
    public class Group
    {
        
        public Group() {}

        public Group(string name)
        {
            Name = name;
        }
        
        public int Id { get; set; }
        
        [Required]
        [StringLength(20,MinimumLength = 3)]
        public string Name { get; set; }
        
        
        // Many to many between Groups and ApplicationUsers
        public ICollection<ApplicationUser> ApplicationUsers { get; set; } = new List<ApplicationUser>();
        
        // Making many to one relation so that groups can have events
        public ICollection<Event> Events { get; set; } = new List<Event>();
        
    }
}