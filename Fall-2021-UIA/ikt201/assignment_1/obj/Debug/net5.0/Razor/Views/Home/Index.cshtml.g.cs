#pragma checksum "C:\Users\Andreas\ikt201g21h\assignments\solutions\assignment_1\Views\Home\Index.cshtml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "b34c094f147da8fe527f92387bc5a38bb8492f37"
// <auto-generated/>
#pragma warning disable 1591
[assembly: global::Microsoft.AspNetCore.Razor.Hosting.RazorCompiledItemAttribute(typeof(AspNetCore.Views_Home_Index), @"mvc.1.0.view", @"/Views/Home/Index.cshtml")]
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
#line 1 "C:\Users\Andreas\ikt201g21h\assignments\solutions\assignment_1\Views\_ViewImports.cshtml"
using assignment_1;

#line default
#line hidden
#nullable disable
#nullable restore
#line 2 "C:\Users\Andreas\ikt201g21h\assignments\solutions\assignment_1\Views\_ViewImports.cshtml"
using assignment_1.Models;

#line default
#line hidden
#nullable disable
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"b34c094f147da8fe527f92387bc5a38bb8492f37", @"/Views/Home/Index.cshtml")]
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"9ecb18a8d3709b374a4a0fa838a76feadc890cba", @"/Views/_ViewImports.cshtml")]
    public class Views_Home_Index : global::Microsoft.AspNetCore.Mvc.Razor.RazorPage<dynamic>
    {
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_0 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("class", new global::Microsoft.AspNetCore.Html.HtmlString("form-inline"), global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        #line hidden
        #pragma warning disable 0649
        private global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperExecutionContext __tagHelperExecutionContext;
        #pragma warning restore 0649
        private global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperRunner __tagHelperRunner = new global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperRunner();
        #pragma warning disable 0169
        private string __tagHelperStringValueBuffer;
        #pragma warning restore 0169
        private global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperScopeManager __backed__tagHelperScopeManager = null;
        private global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperScopeManager __tagHelperScopeManager
        {
            get
            {
                if (__backed__tagHelperScopeManager == null)
                {
                    __backed__tagHelperScopeManager = new global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperScopeManager(StartTagHelperWritingScope, EndTagHelperWritingScope);
                }
                return __backed__tagHelperScopeManager;
            }
        }
        private global::Microsoft.AspNetCore.Mvc.Razor.TagHelpers.HeadTagHelper __Microsoft_AspNetCore_Mvc_Razor_TagHelpers_HeadTagHelper;
        private global::Microsoft.AspNetCore.Mvc.Razor.TagHelpers.BodyTagHelper __Microsoft_AspNetCore_Mvc_Razor_TagHelpers_BodyTagHelper;
        private global::Microsoft.AspNetCore.Mvc.TagHelpers.FormTagHelper __Microsoft_AspNetCore_Mvc_TagHelpers_FormTagHelper;
        private global::Microsoft.AspNetCore.Mvc.TagHelpers.RenderAtEndOfFormTagHelper __Microsoft_AspNetCore_Mvc_TagHelpers_RenderAtEndOfFormTagHelper;
        #pragma warning disable 1998
        public async override global::System.Threading.Tasks.Task ExecuteAsync()
        {
#nullable restore
#line 1 "C:\Users\Andreas\ikt201g21h\assignments\solutions\assignment_1\Views\Home\Index.cshtml"
  
    ViewData["Title"] = "Home Page";

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n<!DOCTYPE html>\r\n<html lang=\"en\">\r\n");
            __tagHelperExecutionContext = __tagHelperScopeManager.Begin("head", global::Microsoft.AspNetCore.Razor.TagHelpers.TagMode.StartTagAndEndTag, "b34c094f147da8fe527f92387bc5a38bb8492f374123", async() => {
                WriteLiteral(@"
    <link rel=""stylesheet"" href=""css\custom.css"" type=""text/css"">
    <meta charset=""utf-8"">
    <meta name=""viewport"" content=""width=device-width, initial-scale=1"">
    <link href=""https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/css/bootstrap.min.css"" rel=""stylesheet"" integrity=""sha384-KyZXEAg3QhqLMpG8r+8fhAXLRk2vvoC2f3B09zVXn8CA5QIVfZOJ3BCsw2P0p/We"" crossorigin=""anonymous"">
    <script src=""https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/js/bootstrap.bundle.min.js"" integrity=""sha384-U1DAWAznBHeqEIlVSCgzq+c9gqGAJn5c/t99JyeKa9xxaYpSvHU5awsuZVVFIhvj"" crossorigin=""anonymous""></script>
");
            }
            );
            __Microsoft_AspNetCore_Mvc_Razor_TagHelpers_HeadTagHelper = CreateTagHelper<global::Microsoft.AspNetCore.Mvc.Razor.TagHelpers.HeadTagHelper>();
            __tagHelperExecutionContext.Add(__Microsoft_AspNetCore_Mvc_Razor_TagHelpers_HeadTagHelper);
            await __tagHelperRunner.RunAsync(__tagHelperExecutionContext);
            if (!__tagHelperExecutionContext.Output.IsContentModified)
            {
                await __tagHelperExecutionContext.SetOutputContentAsync();
            }
            Write(__tagHelperExecutionContext.Output);
            __tagHelperExecutionContext = __tagHelperScopeManager.End();
            WriteLiteral("\r\n");
            __tagHelperExecutionContext = __tagHelperScopeManager.Begin("body", global::Microsoft.AspNetCore.Razor.TagHelpers.TagMode.StartTagAndEndTag, "b34c094f147da8fe527f92387bc5a38bb8492f375713", async() => {
                WriteLiteral(@"
<div class=""container"">
<div class=""box-1"">
    <h1>My first assignment for ikt201g21h</h1>
            
</div>
<div class=""box-2"">
    <h2 id=""colors"">What this is about</h2>
    <p>On this website I will explain why I decided on going back to school to study <em>computer engineering</em>.
        Before I started at UIA I was a landscaper. I had been for the last 5 years, I felt like I was at a point in my life when I had to make a decision.
        I felt like it was now or never. Thats when i started to look at my possibilities, I relised that I didnt have the math and pyshics requirements needed for a engineer education
        and doing anything else seemed like a no go at the time. I then started to look for education for these specific subjects. And thats when I found tres at <strong>UIA</strong></p>
</div>
    
    <div class=""categories"">       
    <div class=""row"">
      
    <div class=""col-sm""><h3>Reasons for quiting my old job</h3>
        <ul> 
            <li>Tired of land");
                WriteLiteral(@"scaping</li>
            <li>Low salary</li>
            <li>Get away from my old life</li>
            <li>Learn something new</li>
        </ul>
    </div>

            
            
    <div class=""col-sm""><h3>Reasons for staying at my job</h3>
        <ul> 
            <li>Steady income</li>
            <li>Feeling of belonging</li>
            <li>Good work environment</li>
            <li>Fun at times</li>
        </ul>
    </div>
                
            
        <div class=""col-sm""><h3>Reasons for studying</h3>
            <ul> 
                <li>Learning something new everyday</li>
                <li>New friends</li>
                <li>Future looks brigth</li>
                <li>Higher salary when im done</li>
            </ul>
        </div>
        </div>
    </div>    
            
    
    
    <div class=""row"">
    <div class=""col-md-4 col-centered"">
    <div class=""adjust"">
        <h3>What i want to improve</h3>
    </div>
    </div>
    </div>
 ");
                WriteLiteral(@"   
        
        <div class=""row"">
        <div class=""col-md-2 col-centered"">
            <ol class=""my-list"">
                <li>Work more efficient</li>
                <li>Writing</li>
                <li>Go to sleep</li>
                <li>Stop wasting time</li>
            </ol>
        </div>
    </div>
    
    
            <div class=""row"">
                <div class=""col-md-3 col-centered"">
                <div class=""adjust"">
                        <h3>Contact info</h3>
                    </div>
            </div>
        
                <table class=""table"">
                    <thead>
                    <tr>
                        <th scope=""col"">#</th>
                        <th scope=""col"">First name</th>
                        <th scope=""col"">Last name</th>
                        <th scope=""col"">Email</th>
                        <th scope=""col"">Phone number</th>
                    </tr>
                    </thead>
                    <tbody>
   ");
                WriteLiteral(@"                 <tr>
                        <th scope=""row"">1</th>
                        <td>Andreas</td>
                        <td>Primstad</td>
                        <td>Andreaspr@uia.no</td>
                        <td>93864789</td>
                    </tr>
                    </tbody>
                </table>
                
                
                
                </div>
                <div class=""row"">
                    <div class=""col-md-4 col-centered"">
                    <div class=""adjust"">
                        <h3>A picture of me</h3>
                    </div>
                    </div>
                    </div>
                <img src=""css/Images/img.jpg"" alt=""A picture of me"">
                
    

    
    <div class=""move"">
        <div class=""row"">
            <div class=""col-md-4 col-centered"">
                <h3>Search for anything</h3>
                ");
                __tagHelperExecutionContext = __tagHelperScopeManager.Begin("form", global::Microsoft.AspNetCore.Razor.TagHelpers.TagMode.StartTagAndEndTag, "b34c094f147da8fe527f92387bc5a38bb8492f3710157", async() => {
                    WriteLiteral("\r\n                    <input class=\"form-control mr-sm-2\" type=\"search\" placeholder=\"Search\" aria-label=\"Search\">\r\n                    <button class=\"btn btn-outline-success my-2 my-sm-0\" type=\"submit\">Search</button>\r\n                ");
                }
                );
                __Microsoft_AspNetCore_Mvc_TagHelpers_FormTagHelper = CreateTagHelper<global::Microsoft.AspNetCore.Mvc.TagHelpers.FormTagHelper>();
                __tagHelperExecutionContext.Add(__Microsoft_AspNetCore_Mvc_TagHelpers_FormTagHelper);
                __Microsoft_AspNetCore_Mvc_TagHelpers_RenderAtEndOfFormTagHelper = CreateTagHelper<global::Microsoft.AspNetCore.Mvc.TagHelpers.RenderAtEndOfFormTagHelper>();
                __tagHelperExecutionContext.Add(__Microsoft_AspNetCore_Mvc_TagHelpers_RenderAtEndOfFormTagHelper);
                __tagHelperExecutionContext.AddHtmlAttribute(__tagHelperAttribute_0);
                await __tagHelperRunner.RunAsync(__tagHelperExecutionContext);
                if (!__tagHelperExecutionContext.Output.IsContentModified)
                {
                    await __tagHelperExecutionContext.SetOutputContentAsync();
                }
                Write(__tagHelperExecutionContext.Output);
                __tagHelperExecutionContext = __tagHelperScopeManager.End();
                WriteLiteral("\r\n\r\n            </div>\r\n            </div>\r\n        </div>\r\n    \r\n</div> <!-- container ends here -->\r\n    \r\n\r\n\r\n        \r\n");
            }
            );
            __Microsoft_AspNetCore_Mvc_Razor_TagHelpers_BodyTagHelper = CreateTagHelper<global::Microsoft.AspNetCore.Mvc.Razor.TagHelpers.BodyTagHelper>();
            __tagHelperExecutionContext.Add(__Microsoft_AspNetCore_Mvc_Razor_TagHelpers_BodyTagHelper);
            await __tagHelperRunner.RunAsync(__tagHelperExecutionContext);
            if (!__tagHelperExecutionContext.Output.IsContentModified)
            {
                await __tagHelperExecutionContext.SetOutputContentAsync();
            }
            Write(__tagHelperExecutionContext.Output);
            __tagHelperExecutionContext = __tagHelperScopeManager.End();
            WriteLiteral("\r\n\r\n</html>");
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
