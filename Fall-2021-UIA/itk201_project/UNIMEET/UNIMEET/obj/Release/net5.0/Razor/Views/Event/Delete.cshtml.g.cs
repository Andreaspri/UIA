#pragma checksum "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Event\Delete.cshtml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "31e86201ab0467348464f8a3f666b18d01f27f95"
// <auto-generated/>
#pragma warning disable 1591
[assembly: global::Microsoft.AspNetCore.Razor.Hosting.RazorCompiledItemAttribute(typeof(AspNetCore.Views_Event_Delete), @"mvc.1.0.view", @"/Views/Event/Delete.cshtml")]
namespace AspNetCore
{
    #line hidden
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Threading.Tasks;
    using Microsoft.AspNetCore.Mvc;
    using Microsoft.AspNetCore.Mvc.Rendering;
    using Microsoft.AspNetCore.Mvc.ViewFeatures;
#nullable restore
#line 1 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\_ViewImports.cshtml"
using UNIMEET;

#line default
#line hidden
#nullable disable
#nullable restore
#line 2 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\_ViewImports.cshtml"
using UNIMEET.Models;

#line default
#line hidden
#nullable disable
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"31e86201ab0467348464f8a3f666b18d01f27f95", @"/Views/Event/Delete.cshtml")]
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"4cedd0e0588076dd7dac34d5a11fdd632ec62af8", @"/Views/_ViewImports.cshtml")]
    public class Views_Event_Delete : global::Microsoft.AspNetCore.Mvc.Razor.RazorPage<UNIMEET.Models.Event>
    {
        #pragma warning disable 1998
        public async override global::System.Threading.Tasks.Task ExecuteAsync()
        {
            WriteLiteral("\r\n");
#nullable restore
#line 3 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Event\Delete.cshtml"
  
    ViewData["Title"] = "Delete";

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n<h1>Delete</h1>\r\n\r\n<h3>Are you sure you want to delete this?</h3>\r\n<div>\r\n    <h4>Event</h4>\r\n    <hr />\r\n    <dl class=\"row\">\r\n        <dt class = \"col-sm-2\">\r\n            ");
#nullable restore
#line 15 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Event\Delete.cshtml"
       Write(Html.DisplayNameFor(model => model.Summary));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dt>\r\n        <dd class = \"col-sm-10\">\r\n            ");
#nullable restore
#line 18 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Event\Delete.cshtml"
       Write(Html.DisplayFor(model => model.Summary));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dd>\r\n        <dt class = \"col-sm-2\">\r\n            ");
#nullable restore
#line 21 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Event\Delete.cshtml"
       Write(Html.DisplayNameFor(model => model.Description));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dt>\r\n        <dd class = \"col-sm-10\">\r\n            ");
#nullable restore
#line 24 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Event\Delete.cshtml"
       Write(Html.DisplayFor(model => model.Description));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dd>\r\n        <dt class = \"col-sm-2\">\r\n            ");
#nullable restore
#line 27 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Event\Delete.cshtml"
       Write(Html.DisplayNameFor(model => model.Sequence));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dt>\r\n        <dd class = \"col-sm-10\">\r\n            ");
#nullable restore
#line 30 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Event\Delete.cshtml"
       Write(Html.DisplayFor(model => model.Sequence));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dd>\r\n        <dt class = \"col-sm-2\">\r\n            ");
#nullable restore
#line 33 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Event\Delete.cshtml"
       Write(Html.DisplayNameFor(model => model.DateFrom));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dt>\r\n        <dd class = \"col-sm-10\">\r\n            ");
#nullable restore
#line 36 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Event\Delete.cshtml"
       Write(Html.DisplayFor(model => model.DateFrom));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dd>\r\n        <dt class = \"col-sm-2\">\r\n            ");
#nullable restore
#line 39 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Event\Delete.cshtml"
       Write(Html.DisplayNameFor(model => model.DateTo));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dt>\r\n        <dd class = \"col-sm-10\">\r\n            ");
#nullable restore
#line 42 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Event\Delete.cshtml"
       Write(Html.DisplayFor(model => model.DateTo));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dd>\r\n        <dt class = \"col-sm-2\">\r\n            ");
#nullable restore
#line 45 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Event\Delete.cshtml"
       Write(Html.DisplayNameFor(model => model.Group));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dt>\r\n    </dl>\r\n    \r\n</div>\r\n");
        }
        #pragma warning restore 1998
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.ViewFeatures.IModelExpressionProvider ModelExpressionProvider { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.IUrlHelper Url { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.IViewComponentHelper Component { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.Rendering.IJsonHelper Json { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.Rendering.IHtmlHelper<UNIMEET.Models.Event> Html { get; private set; }
    }
}
#pragma warning restore 1591
