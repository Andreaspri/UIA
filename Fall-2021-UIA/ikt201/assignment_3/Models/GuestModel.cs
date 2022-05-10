using System;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;

namespace assignment_3.Models
{
    public class GuestModel
    {
        public GuestModel() {}

        public GuestModel(string name,string title,string message)
        {
            Name = name;
            Title = title;
            Message = message;
        }
        
        public int Id { get; set; }
        
        [Required(ErrorMessage = "Name is required")]
        [StringLength(20, MinimumLength = 1)]
        [DisplayName("Name")]
        public string Name { get; set; }
        
        
        

        [Required(ErrorMessage = "Title is required")]
        [MinLength(5, ErrorMessage = "Must be at least 5 chars"),MaxLength(50)]
        [DisplayName("Title")]
        public string Title { get; set; }
        
        

        [Required(ErrorMessage = "Message is required")]
        [MinLength(20, ErrorMessage = "Must be at least 20 chars"),MaxLength(200)]
        [DisplayName("Message")]
        public string Message { get; set; }
        
        
        
    }
}