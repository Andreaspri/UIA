#pragma checksum "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_GroupMembersPartial.cshtml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "b9ebc5d3ac598d2c747282e59e575c141ff16d14"
// <auto-generated/>
#pragma warning disable 1591
[assembly: global::Microsoft.AspNetCore.Razor.Hosting.RazorCompiledItemAttribute(typeof(AspNetCore.Views_Shared__GroupMembersPartial), @"mvc.1.0.view", @"/Views/Shared/_GroupMembersPartial.cshtml")]
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
#nullable restore
#line 1 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_GroupMembersPartial.cshtml"
using System.Text.RegularExpressions;

#line default
#line hidden
#nullable disable
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"b9ebc5d3ac598d2c747282e59e575c141ff16d14", @"/Views/Shared/_GroupMembersPartial.cshtml")]
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"4cedd0e0588076dd7dac34d5a11fdd632ec62af8", @"/Views/_ViewImports.cshtml")]
    public class Views_Shared__GroupMembersPartial : global::Microsoft.AspNetCore.Mvc.Razor.RazorPage<UNIMEET.Models.Group>
    {
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_0 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("class", new global::Microsoft.AspNetCore.Html.HtmlString("nav-link text-dark"), global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_1 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("asp-controller", "ApplicationUser", global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_2 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("asp-action", "Details", global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
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
        private global::Microsoft.AspNetCore.Mvc.TagHelpers.AnchorTagHelper __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper;
        #pragma warning disable 1998
        public async override global::System.Threading.Tasks.Task ExecuteAsync()
        {
            WriteLiteral("\r\n<div id=\"user-id\" type=\"hidden\"></div>\r\n\r\n");
#nullable restore
#line 6 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_GroupMembersPartial.cshtml"
 foreach (var user in Model.ApplicationUsers)
{
    Regex rgx = new Regex("[^a-zA-Z0-9-]");
    var safeName = rgx.Replace(@user.Nickname, "");
    var imagePath= @"https://avatars.dicebear.com/api/initials/" + @safeName + ".svg";
    

#line default
#line hidden
#nullable disable
            WriteLiteral("<tr class=\"noBorder\">\r\n        <td class=\"noBorder\">\r\n            ");
            __tagHelperExecutionContext = __tagHelperScopeManager.Begin("a", global::Microsoft.AspNetCore.Razor.TagHelpers.TagMode.StartTagAndEndTag, "b9ebc5d3ac598d2c747282e59e575c141ff16d144883", async() => {
                WriteLiteral("\r\n                <span class=\"hovertext-left\" data-hover=\"");
#nullable restore
#line 14 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_GroupMembersPartial.cshtml"
                                                    Write(user.Nickname);

#line default
#line hidden
#nullable disable
                WriteLiteral("\">\r\n                    <img class=\"rounded-circle\"");
                BeginWriteAttribute("alt", " alt=\"", 650, "\"", 670, 1);
#nullable restore
#line 15 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_GroupMembersPartial.cshtml"
WriteAttributeValue("", 656, user.Nickname, 656, 14, false);

#line default
#line hidden
#nullable disable
                EndWriteAttribute();
                BeginWriteAttribute("src", " src=\"", 671, "\"", 687, 1);
#nullable restore
#line 15 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_GroupMembersPartial.cshtml"
WriteAttributeValue("", 677, imagePath, 677, 10, false);

#line default
#line hidden
#nullable disable
                EndWriteAttribute();
                WriteLiteral(" width=\"50\" height=\"50\">\r\n                </span>\r\n                <span class=\"hovertext-left\" data-hover=\"Not in your contacts\">\r\n");
#nullable restore
#line 18 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_GroupMembersPartial.cshtml"
                  
                    if (!user.Contacts.Contains(@ViewBag.CurrentUser) && user != ViewBag.CurrentUser)
                    {

#line default
#line hidden
#nullable disable
                WriteLiteral("                        <span class=\"add-contact-group-icon badge badge-pill badge-success\">+</span>\r\n");
#nullable restore
#line 22 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_GroupMembersPartial.cshtml"
                    }
                

#line default
#line hidden
#nullable disable
                WriteLiteral("            </span>\r\n            ");
            }
            );
            __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper = CreateTagHelper<global::Microsoft.AspNetCore.Mvc.TagHelpers.AnchorTagHelper>();
            __tagHelperExecutionContext.Add(__Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper);
            __tagHelperExecutionContext.AddHtmlAttribute(__tagHelperAttribute_0);
            __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper.Controller = (string)__tagHelperAttribute_1.Value;
            __tagHelperExecutionContext.AddTagHelperAttribute(__tagHelperAttribute_1);
            __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper.Action = (string)__tagHelperAttribute_2.Value;
            __tagHelperExecutionContext.AddTagHelperAttribute(__tagHelperAttribute_2);
            if (__Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper.RouteValues == null)
            {
                throw new InvalidOperationException(InvalidTagHelperIndexerAssignment("asp-route-id", "Microsoft.AspNetCore.Mvc.TagHelpers.AnchorTagHelper", "RouteValues"));
            }
            BeginWriteTagHelperAttribute();
#nullable restore
#line 13 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_GroupMembersPartial.cshtml"
                                                                                                  WriteLiteral(user.Id);

#line default
#line hidden
#nullable disable
            __tagHelperStringValueBuffer = EndWriteTagHelperAttribute();
            __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper.RouteValues["id"] = __tagHelperStringValueBuffer;
            __tagHelperExecutionContext.AddTagHelperAttribute("asp-route-id", __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper.RouteValues["id"], global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
            await __tagHelperRunner.RunAsync(__tagHelperExecutionContext);
            if (!__tagHelperExecutionContext.Output.IsContentModified)
            {
                await __tagHelperExecutionContext.SetOutputContentAsync();
            }
            Write(__tagHelperExecutionContext.Output);
            __tagHelperExecutionContext = __tagHelperScopeManager.End();
            WriteLiteral("\r\n        </td>\r\n    </tr>\r\n");
#nullable restore
#line 28 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_GroupMembersPartial.cshtml"
}

#line default
#line hidden
#nullable disable
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
        public global::Microsoft.AspNetCore.Mvc.Rendering.IHtmlHelper<UNIMEET.Models.Group> Html { get; private set; }
    }
}
#pragma warning restore 1591