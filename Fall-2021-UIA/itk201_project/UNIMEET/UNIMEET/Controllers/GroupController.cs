#nullable enable
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Newtonsoft.Json;
using UNIMEET.Data;
using UNIMEET.Models;

namespace UNIMEET.Controllers
{
    [Authorize]
    public class GroupController : Controller
    {
        private readonly ApplicationDbContext _context;
        private readonly UserManager<ApplicationUser> _um;

        public GroupController(ApplicationDbContext context, UserManager<ApplicationUser> um)
        {
            _context = context;
            _um = um;
        }


        [HttpPost]
        [Route("Group/AddUsersToGroup/{groupId:}")]
        public async Task<IActionResult> AddUsersToGroup(string groupId)
        {
            var group = await _context.Groups.FirstOrDefaultAsync(g => g.Id == Convert.ToInt32(groupId));
            var userIds = JsonConvert.DeserializeObject<List<string>>(Request.Form["selected"]);
            foreach (var id in userIds)
            {
                var user = await _um.Users.FirstOrDefaultAsync(u => u.Id == id);
                if (user == null)
                {
                    return NotFound();
                }
                group.ApplicationUsers.Add(user);
            }

            await _context.SaveChangesAsync();
            return Ok();
        }

        [HttpPost]
        public async Task<IActionResult> RemoveUserFromGroup(string userId, string groupId)
        {
            var applicationUser = await _context.ApplicationUser.FindAsync(userId);
            if (applicationUser == null)
            {
                return NotFound();
            }
            
            var group = await _context.Groups.FindAsync(groupId);
            if (group == null)
            {
                return NotFound();
            }

            if (group.ApplicationUsers.Contains(applicationUser))
            {
                group.ApplicationUsers.Remove(applicationUser);
                await _context.SaveChangesAsync();
                return Ok();
            }
            else
                return NotFound();
        }
        
        
        [Route("Group/GroupMembers/{groupId}")]
        public async Task<IActionResult> GroupMembers(string groupId)
        {
            var group = await _context.Groups
                .Include(g => g.ApplicationUsers)
                .ThenInclude(u => u.Contacts)
                .FirstOrDefaultAsync(g => g.Id == Convert.ToInt32(groupId));
            if (group == null)
            {
                return NotFound(); 
            }
            
            // Save the current user ID to the view bag
            ViewBag.CurrentUser = await _um.GetUserAsync(User);

            return PartialView("_GroupMembersPartial", group);
        }

        // GET: Groups
        /*
         * This function returns a partial view that consist of html code for the groups.
        */
        [HttpGet]
        public IActionResult Index()
        {
            // Query to get the user currently logged in.
            var user =_um.Users
                .Include(u => u.Groups) // Including Groups, because this is not default.
                .FirstOrDefault(u => u.Id == _um.GetUserId(User)); 
            if (user == null)
            {
                return NotFound();
            }

            return PartialView("_GroupPartial", user.Groups.ToList());
        }

        // GET: Group/Details/5
        // Returns details of the group.
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            /* Nested looping is slow. So lazy loading is turned on by default. That means we cant access ApplicationUsers by default
             Include lets you access ApplicationUsers, thus you can use it in the html */
            var group = await _context.Groups.Include(group => group.ApplicationUsers)
                .FirstOrDefaultAsync(m => m.Id == id);
            if (group == null)
            {
                return NotFound();
            }
            
            return View(group);
        }
        

        // GET: Group/Create
        // Returns a view for creating a group.
        [HttpGet]
        public IActionResult Create()
        {
            return View();
        }

        // POST: Group/Create
        [HttpPost]
        public async Task<IActionResult> CreateGroupWithMembers()
        {
            // Creating a new group (Group entity).
            var group = new Group
            {
                Name = Request.Form["name"]
            };
            
            _context.Groups.Add(group);
            await _context.SaveChangesAsync();
            // Converting json serialized javaScript array of strings to c# list of strings.
            var userIds = JsonConvert.DeserializeObject<List<string>>(Request.Form["selected"]);

            // Iterating over user ids.
            foreach (var id in userIds)
            {
                // Query for user.
                var user = await _um.Users.FirstOrDefaultAsync(u => u.Id == id);
                // Return not found if a user doesnt exist. No users will be saved.
                if (user == null)
                {
                    return NotFound();
                }
                // Adding user to group.
                group.ApplicationUsers.Add(user);
            }
            // Adding user that created the group.
            var creator = await _um.GetUserAsync(User);
            if (creator == null)
            {
                return NotFound();
            }
            group.ApplicationUsers.Add(creator);

            // Storing in database.
            await _context.SaveChangesAsync();
            
            // Redirecting user to Group/Details/groupId view.
            return RedirectToAction("Details", new { id = group.Id });
        }
        
    
        
        // GET: Group/Edit/
        // Returns a view with an edit form for the user to fill inn.
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }
            
            // Finds the group using context and id send in.
            var @group = await _context.Groups.FindAsync(id);
            if (@group == null)
            {
                return NotFound();
            }
            return View(@group);
        }

        // POST: Group/Edit/5
        // Store the edited group data in the database.
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,Name")] Group @group)
        {
            if (id != @group.Id)
            {
                return NotFound();
            }
            // Checks if the form is send in is valid.
            if (ModelState.IsValid)
            {
                try
                {
                    // Updating the group with new parameter etc.
                    _context.Update(@group);
                    await _context.SaveChangesAsync();
                }
                // Error handler.
                catch (DbUpdateConcurrencyException)
                {
                    if (!GroupExists(@group.Id))
                    {
                        return NotFound();
                    }
                    else
                    {
                        throw;
                    }
                }
                // Redirect the user to the homepage.
                return RedirectToAction(nameof(Details), new { id = @group.Id });
            }
            return View(@group);
        }
        
        [HttpPost]
        [Route("Group/SearchGroupContacts/{groupId:}/{searchString:}")]
        public async Task<IActionResult> SearchGroupContacts(string groupId, string searchString)
        {
            var id = _um.GetUserId(User);
            if (id == null)
            {
                return NotFound();
            }
            
            var group = await _context.Groups
                .Include(g => g.ApplicationUsers)
                .FirstOrDefaultAsync(g => g.Id == Convert.ToInt32(groupId));
            
            if (group == null)
            {
                return NotFound();
            }

            var user = await _um.Users
                .Include(u => u.Contacts)
                .FirstOrDefaultAsync(u => u.Id == id);

            if (user == null)
            {
                return NotFound();
            }


            var users = user.Contacts
                .Where(u => !group.ApplicationUsers.Contains(u))
                .Where(u => u.Nickname.ToLower().Contains(searchString.ToLower()) | u.Email.ToLower().Contains(searchString.ToLower()))
                .OrderBy(u => u.Nickname)
                .Take(5);
            if (!users.Any())
            {
                return NotFound();
            }

            ViewBag.selected = Request.Form["selected"];
            return PartialView("_SearchGroupContactsPartial", users);
        }

        // POST: Group/Leave/5
        // Function for removing user from a group.
        [HttpPost]
        [Route("Group/LeaveGroup/{id:}")]
        public async Task<IActionResult> LeaveGroup(string id)
        {
            if (!int.TryParse(id, out var groupId))
            {
                return NotFound();
            }
            // Finds the group.
            var @group = await _context.Groups
                .Include(g => g.ApplicationUsers)
                .FirstOrDefaultAsync(g => g.Id == groupId);

            if (@group == null)
            {
                return NoContent();
            }
            
            // Logged in user
            var userId = _um.GetUserId(User);

            if (userId == null)
            {
                return NotFound();
            }

            var user = await _um.Users
                .Include(u => u.Groups)
                .FirstOrDefaultAsync(u => u.Id == userId);
            
            if (user == null)
            {
                return NotFound();
            }
            
            // Remove user from group if the user is a member.
            if (user.Groups.Contains(@group))
            {
                user.Groups.Remove(@group);
                await _context.SaveChangesAsync();
                
                // Removing group if there is no more members.
                if (!@group.ApplicationUsers.Any())
                {
                    _context.Remove(group);
                    await _context.SaveChangesAsync();
                }
            }
            
            // Redirect the user to the homepage.
            return RedirectToAction(nameof(Index), "Home");
        }

        private bool GroupExists(int id)
        {
            return _context.Groups.Any(e => e.Id == id);
        }
    }
}
