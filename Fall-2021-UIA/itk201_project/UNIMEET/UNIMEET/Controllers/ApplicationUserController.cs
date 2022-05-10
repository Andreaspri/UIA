using System;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Internal;
using UNIMEET.Data;
using UNIMEET.Models;

namespace UNIMEET.Controllers
{
    public class ApplicationUserController : Controller
    {
        private readonly ApplicationDbContext _context;
        private readonly UserManager<ApplicationUser> _um;
        
        public ApplicationUserController(ApplicationDbContext context, UserManager<ApplicationUser> um)
        {
            _context = context;
            _um = um;
        }

        // GET: ApplicationUser/Details/5
        [HttpGet]
        [Authorize]
        public async Task<IActionResult> Details(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var applicationUser = await _context.ApplicationUser.
                Include(applicationUser => applicationUser.Groups).
                Include(applicationUser => applicationUser.Contacts).
                Include(applicationUser => applicationUser.OtherUser).
                Include(applicationUser => applicationUser.ContactRequestReceiver).
                Include(applicationUser => applicationUser.ContactRequestSender).
                FirstOrDefaultAsync(m => m.Id == id);
            if (applicationUser == null)
            {
                return NotFound();
            }

            ViewBag.currentUser = _um.Users.
                Where(a => a.Id == _um.GetUserId(User)).
                Include(a => a.Contacts).
                Include(a => a.ContactRequestReceiver).
                Include(a => a.ContactRequestSender).
                FirstOrDefaultAsync().Result;

            return View(applicationUser);
        }

        // Helper function for sidebar preview. 
        [HttpGet]
        public async Task<IActionResult> SidebarPreview()
        {
            var user = await _um.GetUserAsync(User);
            // User is not signed in.
            if (user == null)
            {
                return NoContent();
            }

            string url = Request.Headers["Referer"].ToString();
            
            // User is in account setting. 
            if (url.Contains("Account"))
            {
                return NoContent();
            }
            
            return PartialView("_SideBarPartial");
        }
        
        
        /* This function gets the authorized users contacts.*/
        [HttpGet]
        [Authorize]
        public async Task<IActionResult> Friends()
        {
            // UserId authorized.
            var id = _um.GetUserId(User);
            // Need to get the user authorized with their contacts. 
            var applicationUser = await _context.ApplicationUser.
                Include(applicationUser => applicationUser.Contacts).
                Include(u => u.ContactRequestSender).
                FirstOrDefaultAsync(m => m.Id == id);
            
            if (applicationUser == null)
            {
                return NotFound();
            }

            return View(applicationUser);
        }
        
        /* This function gets the authorized users contact requests and returns a partial view. */
        [HttpGet]
        [Authorize]
        public async Task<IActionResult> FriendRequests()
        {
            // UserId authorized.
            var id = _um.GetUserId(User);
            // Need to get the user authorized with their contact requests. 
            var applicationUser = await _context.ApplicationUser.
                Include(applicationUser => applicationUser.ContactRequestSender).
                FirstOrDefaultAsync(m => m.Id == id);
            
            if (applicationUser == null)
            {
                return NotFound();
            }

            return PartialView("_FriendRequestPartial" ,applicationUser);
        }
        
        

        // Function for searching after user
        [HttpGet]
        [Authorize]

        public async Task<IActionResult> SearchApplicationUser(string searchString)
        { 
            // Convert search string to lower case, if the string is not empty
            if (!String.IsNullOrEmpty(searchString))
            {
                searchString = searchString.ToLower();
            }
            //Contacts needs to be in included inorder to check if the user already has the current user as a contact
             //ContactRequestReceiver needs to be added inorder to check if the current user has sent a contact request to the user
             //ContactRequestSender need to be added inorder to check if the user has sent a contact request to the current user
             var result = _context.ApplicationUser.
                Include(m => m.Contacts).
                Include(m => m.ContactRequestReceiver).
                Include(m => m.ContactRequestSender).
                Where(m => m.Nickname.ToLower().Contains(searchString) || m.Email.ToLower().Contains(searchString)).
                Where(m => m.Id != _um.GetUserId(User)).
                OrderBy(m => m.Email).
                Take(10); // Only taking 10 results to prevent a huge response in the view
            
            
            var currentApplicationUser = await _context.ApplicationUser.
                FirstOrDefaultAsync(m => m.Id == _um.GetUserId(User));
            
            // Storing the current user in ViewData so that it can be accessed in the view to check for contacts and contact requests
            ViewData["CurrentApplicationUser"] = currentApplicationUser;

            return PartialView("_UsersPartial", result.ToList());
        }
        
        // Function for returning the partial view of the search for users view
        [HttpGet]
        [Authorize]
        public IActionResult SearchForContactPartial()
        {
            return PartialView("_SearchForNewContactPartial");
        }
        
        // Function for returning the partial view of the outgoing contact requests
        [HttpGet]
        [Authorize]
        public async Task<IActionResult> OutgoingContactRequestsPartial()
        {
            // UserId authorized.
            var id = _um.GetUserId(User);
            
            if (id == null)
            {
                return NotFound(); 
            }
            
            // Need to get the user authorized with their contact requests. 
            var applicationUser = await _context.ApplicationUser.
                Include(applicationUser => applicationUser.ContactRequestReceiver).
                FirstOrDefaultAsync(m => m.Id == id);

            return PartialView("_ContactsOutgoingPartial", applicationUser);
        }
        
        // Function for returning partial view for incoming contact requests
        [HttpGet]
        [Authorize]
        public async Task<IActionResult> IncomingContactRequestPartial()
        {
            var id = _um.GetUserId(User);
            var applicationUser = await _context.ApplicationUser
                .Include(applicationUser => applicationUser.ContactRequestSender).
                FirstOrDefaultAsync(m => m.Id == id);

            return PartialView("_incomingContactRequest", applicationUser);
        }

        // Function for returning the partial view of the groups the current user has in common with userId
        [Route("ApplicationUser/CommonGroups/{userId}")]
        public async Task<IActionResult> CommonGroups(string userId)
        {
            var currentUser = await _um.GetUserAsync(User);
            
            if (currentUser == null)
            {
                return NotFound(); 
            }

            var otherUser = _um.Users.FirstOrDefault(u => u.Id == userId);
            
            if (otherUser == null)
            {
                return NotFound(); 
            }
            
            // Get the groups the userID has, and the groups the current user has in common
            var commonGroups = _context.Groups
                .Include(g => g.ApplicationUsers)
                .Where(g => g.ApplicationUsers.Contains(otherUser) && g.ApplicationUsers.Contains(currentUser))
                .OrderBy(g => g.Name)
                .Take(40);
            

            return PartialView("_commonGroupsPartial", commonGroups);
        }
        
        
        // Function for searching and display contacts the current user has accepted
        [HttpGet]
        [Authorize]
        public async Task<IActionResult> SearchApplicationContact(string searchString)
        {
            // Convert search string to lower case, if the string is not empty
            if (!String.IsNullOrEmpty(searchString))
            {
                searchString = searchString.ToLower();
            }
            //Contacts needs to be in included inorder to check if the user already has the current user as a contact
            var result = _um.Users.
                Include(m => m.Contacts).
                Where(m => m.Nickname.ToLower().Contains(searchString) || m.Email.ToLower().Contains(searchString)).
                Where(m => m.Id != _um.GetUserId(User)).
                OrderBy(m => m.Email).
                Take(10); 
            
            var currentApplicationUser = await _context.ApplicationUser.
                FirstOrDefaultAsync(m => m.Id == _um.GetUserId(User));
            
            // Storing the current user in ViewData so that it can be accessed in the view to check for contacts and contact requests
            ViewData["CurrentApplicationUser"] = currentApplicationUser;

            return PartialView("_CreateGroupUserPartial", result.ToList());
        }

        // Functions for adding sending a contact request 
        [HttpPost]
        [Authorize]
        public async Task<IActionResult> NewContactRequest(string id)
        {
            if (id == null)
            {
                return NotFound();
            }
            
            // Including ContactRequestSender to check for duplicate contact requests
            var otherApplicationUser = await _context.ApplicationUser.
                Include(m => m.ContactRequestSender).
                FirstOrDefaultAsync(m => m.Id == id);
            if (otherApplicationUser == null)
            {
                return NotFound();
            }
            
            var currentApplicationUser = await _context.ApplicationUser.FindAsync(_um.GetUserId(User));
            
            if (currentApplicationUser == null)
            {
                return NotFound();
            }
            
            // Safety measure to make sure two users can send friend request to each other 
            if (otherApplicationUser.ContactRequestSender.Contains(currentApplicationUser))
                return Redirect(Request.Headers["Referer"].ToString());
            
            // Adding the other user to the receiver column. The current user will automatically be added to the sender column
            currentApplicationUser.ContactRequestReceiver.Add(otherApplicationUser);
            await _context.SaveChangesAsync();

            return Redirect(Request.Headers["Referer"].ToString());

        }
        
        // Function for accepting a contact request
        [HttpPost]
        [Authorize]
        public async Task<IActionResult> AcceptContactRequest(string id)
        {
            if (id == null)
            {
                return NotFound();
            }
            // Getting the user that sent the contact request
            var otherApplicationUser = await _context.ApplicationUser.FindAsync(id);
            if (otherApplicationUser == null)
            {
                return NotFound();
            }
            // Getting the current user
            var currentApplicationUser = _context.ApplicationUser.
                Include(m => m.ContactRequestSender).
                FirstOrDefault(m => m.Id == _um.GetUserId(User));
            
            if (currentApplicationUser== null)
            {
                return NotFound();
            }
            
            
            // Security measure to make sure someone cant type in someones id inside the html and add a contact
            // without having sent contact request
            if (!currentApplicationUser.ContactRequestSender.Contains(otherApplicationUser)) 
                return NotFound();
            
            // Adding them both ways so that current user becomes friend with other user and other user becomes friend with current user
            currentApplicationUser.Contacts.Add(otherApplicationUser);
            otherApplicationUser.Contacts.Add(currentApplicationUser);
            
            // Removing the contact request from the table
            currentApplicationUser.ContactRequestSender.Remove(otherApplicationUser);

            await _context.SaveChangesAsync();
            
            return Redirect(Request.Headers["Referer"].ToString());

        }
        
        // Function for removing a contact
        [Authorize]
        public async Task<IActionResult> RemoveContact(string id)
        {
            if (id == null)
            {
                return NotFound();
            }
            
            // Including contacts so that it is possible to remove contact from it
            var applicationUserToRemove = await _context.ApplicationUser.
                Include(m => m.Contacts).
                FirstOrDefaultAsync(m => m.Id == id);;
            if (applicationUserToRemove == null)
            {
                return NotFound();
            }
            
            // Including contacts so that it is possible to remove contact from it
            var currentApplicationUser = await _context.ApplicationUser.
                Include(m => m.Contacts).
                FirstOrDefaultAsync(m => m.Id == _um.GetUserId(User));
            
            if (currentApplicationUser == null)
            {
                return NotFound();
            }

            if (currentApplicationUser.Contacts.Contains(applicationUserToRemove))
            {
                // Because they are added both ways they need to be deleted both ways
                currentApplicationUser.Contacts.Remove(applicationUserToRemove);
                applicationUserToRemove.Contacts.Remove(currentApplicationUser);

                await _context.SaveChangesAsync();

                return Redirect(Request.Headers["Referer"].ToString());
            }
            else
                return NotFound();
        }
        
        // Function for declining a contact request or remove a sent contact request
        [Authorize]
        public async Task<IActionResult> RemoveContactRequest(string id)
        {
            if (id == null)
            {
                return NotFound();
            }
            // Getting the user that received or sent the contact request
            var applicationUserToRemove = await _context.ApplicationUser.FindAsync(id);
            if (applicationUserToRemove == null)
            {
                return NotFound();
            }
            
            // ContactRequestReceiver is included in case the current user sent the contact request
            // ContactRequestSender is also included in case the current user received the contact request
            var currentApplicationUser = await _context.ApplicationUser.
                Include(m=> m.ContactRequestReceiver).
                Include(m=> m.ContactRequestSender).
                FirstOrDefaultAsync(m => m.Id == _um.GetUserId(User));
            
            if (currentApplicationUser == null)
            {
                return NotFound();
            }
            
            // If the current user sent the contact request it is removed here
            if (currentApplicationUser.ContactRequestReceiver.Contains(applicationUserToRemove))
            {
                currentApplicationUser.ContactRequestReceiver.Remove(applicationUserToRemove);

                await _context.SaveChangesAsync();
                
                // Return to the previous page
                return Redirect(Request.Headers["Referer"].ToString());
            }
            // If the current user received the contact request it is removed here
            if (currentApplicationUser.ContactRequestSender.Contains(applicationUserToRemove))
            {
                currentApplicationUser.ContactRequestSender.Remove(applicationUserToRemove);

                await _context.SaveChangesAsync();
                
                // Return to the previous page
                return Redirect(Request.Headers["Referer"].ToString());
            }
            
            else
                return NotFound();
        }
    }
}
