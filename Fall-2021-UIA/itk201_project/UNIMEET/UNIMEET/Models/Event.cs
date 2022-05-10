using System;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Security.Cryptography;
using NodaTime;

namespace UNIMEET.Models
{
    public class Event
    {
        
        public Event() {}

        public int Id { get; set; }
        
        [Required]
        [DisplayName("Name")]
        [StringLength(30)]
        public string Name { get; set; }
                
        [Required]
        [StringLength(100)]
        [DisplayName("Event Summary")]
        public string Summary { get; set; }
        
        [DisplayName("Event Description")]
        [StringLength(200)]
        public string Description { get; set; }
        
        [DisplayName("Sequence")]
        [StringLength(50)]
        public string Sequence { get; set; }
        
        [DataType(DataType.Date)]
        [DisplayName("Time range starting")]
        public DateTime DateFrom { get; set; }
        
        [DataType(DataType.Date)]
        [DisplayName("Time range ending")]
        public DateTime DateTo { get; set; }
        
        [DisplayName("Duration")]
        [DataType(DataType.Time)]        
        public DateTime Duration { get; set; }
        
        [DisplayName("Event starting date")]
        public DateTime EventTimeFrom { get; set; }
        
        [DisplayName("Event ending date")]
        public DateTime EventTimeTo { get; set; }
                
        // No meetings after this time
        [DisplayName("Only after this time")]
        [DataType(DataType.Time)]
        [DefaultValue(true)]
        public DateTime OnlyAfter { get; set; }
        
        // No meetings before this time
        [DisplayName("Only before this time")]
        [DataType(DataType.Time)]
        [DefaultValue(true)]
        public DateTime OnlyBefore { get; set; }

        // Foreign key 
        public int GroupId { get; set; }
        
        // Navigation property
        public Group Group { get; set; }
    }
}