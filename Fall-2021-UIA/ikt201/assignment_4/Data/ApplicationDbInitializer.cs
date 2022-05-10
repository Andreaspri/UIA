using assignment_4.Models;
using Microsoft.AspNetCore.Identity;

namespace assignment_4.Data
{
    public class ApplicationDbInitializer
    {
        public static void Initialize(ApplicationDbContext db, UserManager<ApplicationUser> um, RoleManager<IdentityRole> rm)
        {
           db.Database.EnsureDeleted();
           db.Database.EnsureCreated();
        }
    }
}