#pragma checksum "C:\Users\Andreas\ikt201g21h\assignments\solutions\assignment_2\Views\Calculator\Index.cshtml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "13bf91cfeda3e32c78cf76b100d5069a8d15a35a"
// <auto-generated/>
#pragma warning disable 1591
[assembly: global::Microsoft.AspNetCore.Razor.Hosting.RazorCompiledItemAttribute(typeof(AspNetCore.Views_Calculator_Index), @"mvc.1.0.view", @"/Views/Calculator/Index.cshtml")]
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
#line 1 "C:\Users\Andreas\ikt201g21h\assignments\solutions\assignment_2\Views\_ViewImports.cshtml"
using assignment_2;

#line default
#line hidden
#nullable disable
#nullable restore
#line 2 "C:\Users\Andreas\ikt201g21h\assignments\solutions\assignment_2\Views\_ViewImports.cshtml"
using assignment_2.Models;

#line default
#line hidden
#nullable disable
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"13bf91cfeda3e32c78cf76b100d5069a8d15a35a", @"/Views/Calculator/Index.cshtml")]
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"e7465b36b83c4e27f419f4bd909cd5a296ce6175", @"/Views/_ViewImports.cshtml")]
    public class Views_Calculator_Index : global::Microsoft.AspNetCore.Mvc.Razor.RazorPage<dynamic>
    {
        #pragma warning disable 1998
        public async override global::System.Threading.Tasks.Task ExecuteAsync()
        {
#nullable restore
#line 1 "C:\Users\Andreas\ikt201g21h\assignments\solutions\assignment_2\Views\Calculator\Index.cshtml"
  
    ViewData["Title"] = "Calculator";

#line default
#line hidden
#nullable disable
            WriteLiteral(@"
<div class=""text-center"">
    <h1 class=""display-4"">Calculator</h1>
    
    <div id=""display"">0</div>
    <div id=""buttons"">
        
        <button id=""reset"" onclick=""reset()"">C</button>
        <button id=""clear"" onclick=""clears()"">CE</button>
        <button id=""remove"" onclick=""remove()"">←</button>
        <button id=""seven"" onclick=""seven()"">7</button>
        <button id=""eight"" onclick=""eight()"">8</button>
        <button id=""nine"" onclick=""nine()"">9</button>
        <button id=""divide"" onclick=""divide()"">/</button>
        <button id=""four"" onclick=""four()"">4</button>
        <button id=""five"" onclick=""five()"">5</button>
        <button id=""six"" onclick=""six()"">6</button>
        <button id=""multiply"" onclick=""multiply()"">*</button>
        <button id=""one"" onclick=""one()"">1</button>
        <button id=""two"" onclick=""two()"">2</button>
        <button id=""three"" onclick=""three()"">3</button>
        <button id=""minus"" onclick=""minus()"">-</button>
        <button id=""equals"" oncl");
            WriteLiteral("ick=\"equals()\">=</button>\r\n        <button id=\"zero\" onclick=\"zero()\">0</button>\r\n        <button id=\"plus\" onclick=\"plus()\">+</button>\r\n\r\n\r\n\r\n    </div>\r\n    \r\n    \r\n    \r\n</div>");
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
        public global::Microsoft.AspNetCore.Mvc.Rendering.IHtmlHelper<dynamic> Html { get; private set; }
    }
}
#pragma warning restore 1591
