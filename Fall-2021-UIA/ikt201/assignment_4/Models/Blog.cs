using System;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Dynamic;
using Microsoft.AspNetCore.Identity;

namespace assignment_4.Models
{
    public class Blog
    {
        public Blog() {}

        public Blog(string title, string summary, string content, DateTime time)
        {
            Title = title;
            Summary = summary;
            Content = content;
            Time = time;
        }
        public int Id { get; set; }
        
        [Required]
        [StringLength(30)]
        [DisplayName("Title")]
        public string Title { get; set; }
        
        
        [Required]
        [StringLength(200)]
        [DisplayName("Summary")]
        public string Summary { get; set; }
        
        
        [Required]
        [StringLength(1000)]
        [DisplayName("Content")]
        public string Content { get; set; }
        
        [DataType(DataType.Date)]
        [DisplayName("Time")]
        [DisplayFormat(ApplyFormatInEditMode = true, DataFormatString = "{0:dd.MM.yyyy}")]
        public DateTime Time { get; set; }

        
        

        
        public string ApplicationUserId {get; set;}
        
        public ApplicationUser ApplicationUser {get; set;}




    }
}