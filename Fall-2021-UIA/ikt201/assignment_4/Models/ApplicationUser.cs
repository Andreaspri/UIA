using System.Collections.Generic;
using System.Dynamic;
using Microsoft.AspNetCore.Identity;

namespace assignment_4.Models
{
    public class ApplicationUser : IdentityUser
    {
        public string Nickname { get; set; }
        
        
        public ICollection<Blog> Blogs { get; set; } = new List<Blog>();

    }
}