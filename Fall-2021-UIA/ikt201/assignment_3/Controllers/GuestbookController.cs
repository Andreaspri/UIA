using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Diagnostics;
using System.Threading.Tasks;
using assignment_3.Data;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using assignment_3.Models;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc.Infrastructure;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.EntityFrameworkCore;


namespace assignment_3.Controllers
{
    public class GuestbookController : Controller
    {
        
        private readonly ILogger<GuestbookController> _logger;
        private readonly ApplicationDbContext _db;

        public GuestbookController(ILogger<GuestbookController> logger, ApplicationDbContext db)
        {
            _logger = logger;
            _db = db;
        }

    

        public async Task<IActionResult> Index()
        {
            return View(await _db.Guests.ToListAsync());
        }
        
        
        [HttpPost]
        public IActionResult Add(GuestModel guest)
        {

            if(ModelState.IsValid){
                _db.Guests.Add(guest);
                _db.SaveChanges();
                return RedirectToAction("Index");
            }
            

            return View(guest);
            
        }
        
        [HttpGet]
        public IActionResult Add()
        {
            GuestModel guest = new GuestModel();
            return View(guest);
        }
            

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel {RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier});
        }
        
    }
}