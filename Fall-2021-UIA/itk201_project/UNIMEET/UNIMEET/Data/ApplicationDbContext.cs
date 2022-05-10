using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using UNIMEET.Models;

namespace UNIMEET.Data
{
    public class ApplicationDbContext : IdentityDbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }
        

        
        public DbSet<CalendarUrl> CalendarUrls { get; set; }
        public DbSet<Group> Groups { get; set; }
        public DbSet<ApplicationUser> ApplicationUser { get; set; }
        
        
        // Creating the many to many relations for ApplicationUser on itself
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {

            modelBuilder.Entity<ApplicationUser>()
                .HasMany<ApplicationUser>(s => s.ContactRequestSender)
                .WithMany(c => c.ContactRequestReceiver); // Add on-delete cascade
                /*.Map(cs =>
                {
                    cs.MapLeftKey("SenderId");
                    cs.MapRightKey("ReceiverId");
                    cs.ToTable("ContactRequest");
                }).OnDelete(DeleteBehavior.Cascade);*/

            modelBuilder.Entity<ApplicationUser>()
                .HasMany<ApplicationUser>(s => s.Contacts)
                .WithMany(c => c.OtherUser); // Add on-delete cascade
                /*.Map(cs =>
                {
                    cs.MapLeftKey("Contact");
                    cs.MapRightKey("Contacted");
                    cs.ToTable("Contact");
                }).OnDelete(DeleteBehavior.Cascade);*/

            base.OnModelCreating(modelBuilder);

        }
        
        
        // Creating the many to many relations for ApplicationUser on itself
        public DbSet<UNIMEET.Models.Event> Event { get; set; }
  

        
        
        
    }
}