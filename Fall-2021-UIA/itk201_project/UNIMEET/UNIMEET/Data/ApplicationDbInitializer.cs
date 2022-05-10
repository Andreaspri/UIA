using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;
using Ical.Net;
using Ical.Net.Serialization;
using Microsoft.AspNetCore.Identity;
using UNIMEET.Models;

namespace UNIMEET.Data
{
    public class ApplicationDbInitializer
    {
        public static void Initialize(ApplicationDbContext db, UserManager<ApplicationUser> um)
        {
            // Delete the database before we initialize it. This is common to do during development.
            
            // Reenable this after first build
            db.Database.EnsureDeleted();
            
            // Recreate the database and tables according to our models
            db.Database.EnsureCreated();
            
            var user1 = new ApplicationUser { Firstname = "Andreas", Lastname = "Primstad", Nickname = "Andy", UserName = "user1@uia.no", Email = "user1@uia.no", EmailConfirmed = true, About = "I'm Andy. Full Stack Designer I enjoy creating user-centric, delightful and human experiences."};
            
            // Generating random string of lenght 16.
            Random random1 = new Random();
            int length1 = 16;
            var rString1 = "";
            for (var i = 0; i < length1; i++)
            {
                rString1 += ((char)(random1.Next(1, 26) + 64)).ToString().ToLower();
            }
            
            // This will be the security key to prevent everyone from accessing the private calendar. 
            user1.CalenderFile = rString1;
            
            var url_1 = new CalendarUrl();
            url_1.Url = "https://calendar.google.com/calendar/ical/gabri.torland%40gmail.com/public/basic.ics";
            user1.CalendarUrls.Add(url_1);
            um.CreateAsync(user1, "Password1.").Wait();
            
            var user2 = new ApplicationUser { Firstname = "Gabriel", Lastname = "Torland", Nickname = "Gabriella", UserName = "user2@uia.no", Email = "user2@uia.no", EmailConfirmed = true, About = "I'm Gabby. Full Stack Designer I enjoy creating user-centric, delightful and human experiences." };
            
            // Generating random string of lenght 16.
            Random random2 = new Random();
            int length2 = 16;
            var rString2 = "";
            for (var i = 0; i < length2; i++)
            {
                rString2 += ((char)(random2.Next(1, 26) + 64)).ToString().ToLower();
            }
            
            // This will be the security key to prevent everyone from accessing the private calendar. 
            user2.CalenderFile = rString2;
            
            var url_2 = new CalendarUrl();
            url_2.Url = "https://cloud.timeedit.net/uia/web/tp/ri63965Xg65650Q0g0QY9115Z96YX118767Y530yZ06Q75X6X716902Q77dt29248n47537F9679Z4QZ88F51t9Q21B5X1BZ75EFCBAB4C1D71.ics";
            user1.CalendarUrls.Add(url_2);
            um.CreateAsync(user2, "Password1.").Wait();
            
            var user3 = new ApplicationUser { Firstname = "Odd", Lastname = "Mathisen", Nickname = "Odd", UserName = "user3@uia.no", Email = "user3@uia.no", EmailConfirmed = true, About = "I'm Oddone. Full Stack Designer I enjoy creating user-centric, delightful and human experiences." };
            
            var url_3 = new CalendarUrl();
            url_3.Url = "https://cloud.timeedit.net/uia/web/tp/ri67650y162659QZ4YQZnQ6QZ3.ics";
            user1.CalendarUrls.Add(url_3);
            um.CreateAsync(user3, "Password1.").Wait();
            
            var user4 = new ApplicationUser { Firstname = "Ylva", Lastname = "Grønningsæter", Nickname = "Ylvis", UserName = "user4@uia.no", Email = "user4@uia.no", EmailConfirmed = true, About = "I'm Ylvis. Full Stack Designer I enjoy creating user-centric, delightful and human experiences."};
            
            var url_4 = new CalendarUrl();
            url_4.Url = "https://cloud.timeedit.net/uia/web/tp/ri67650y162659QZ4YQZnQ6QZ3.ics";
            user1.CalendarUrls.Add(url_4);
            um.CreateAsync(user4, "Password1.").Wait();
            
            var user5 = new ApplicationUser { Firstname = "Kim", Lastname = "Svalde", Nickname = "Kim", UserName = "user5@uia.no", Email = "user5@uia.no", EmailConfirmed = true, About = "I'm Kim. Full Stack Designer I enjoy creating user-centric, delightful and human experiences." };
            um.CreateAsync(user5, "Password1.").Wait();
            
            var user6 = new ApplicationUser { Firstname = "Abraham", Lastname = "Anderson", Nickname = "Abraham", UserName = "user6@uia.no", Email = "user6@uia.no", EmailConfirmed = true, About = "I'm Abraham. Full Stack Designer I enjoy creating user-centric, delightful and human experiences." };
            um.CreateAsync(user6, "Password1.").Wait();
            
            var group = new[]
            {
                new Group("Super Awesome Group"),
                new Group("Gabriel er noob group"),
                new Group("Cheese group"),
            };
            
            db.Groups.AddRange(group);
            
            db.SaveChanges();
            
            // Creating relationships
            user1.Groups.Add(group[0]);
            
            group[0].ApplicationUsers.Add(user1);
            group[0].ApplicationUsers.Add(user2);
            group[0].ApplicationUsers.Add(user3);
            group[0].ApplicationUsers.Add(user4);
            group[0].ApplicationUsers.Add(user5);
            group[0].ApplicationUsers.Add(user6);
            
            
            group[1].ApplicationUsers.Add(user2);
            
            group[2].ApplicationUsers.Add(user4);
            group[2].ApplicationUsers.Add(user6);
            group[2].ApplicationUsers.Add(user5);
            
            user1.Groups.Add(group[2]);
            
            db.SaveChanges();
            
            
            user1.Contacts.Add(user2);
            user2.Contacts.Add(user1);
            user1.Contacts.Add(user3);
            user3.Contacts.Add(user1);
            
            user4.Contacts.Add(user5);
            user5.Contacts.Add(user4);
            
            
            
            user6.ContactRequestReceiver.Add(user1);
            user5.ContactRequestReceiver.Add(user1);
            
            user2.ContactRequestReceiver.Add(user4);
            user3.ContactRequestReceiver.Add(user2);
            
            
            
            
            
            db.SaveChanges();
            


        }
    }
}