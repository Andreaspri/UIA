#pragma checksum "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_UsersPartial.cshtml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "ebd6ca97afea8478bb9278dcf15d5a690e0ea565"
// <auto-generated/>
#pragma warning disable 1591
[assembly: global::Microsoft.AspNetCore.Razor.Hosting.RazorCompiledItemAttribute(typeof(AspNetCore.Views_Shared__UsersPartial), @"mvc.1.0.view", @"/Views/Shared/_UsersPartial.cshtml")]
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
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"ebd6ca97afea8478bb9278dcf15d5a690e0ea565", @"/Views/Shared/_UsersPartial.cshtml")]
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"4cedd0e0588076dd7dac34d5a11fdd632ec62af8", @"/Views/_ViewImports.cshtml")]
    public class Views_Shared__UsersPartial : global::Microsoft.AspNetCore.Mvc.Razor.RazorPage<IEnumerable<UNIMEET.Data.ApplicationUser>>
    {
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_0 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("class", new global::Microsoft.AspNetCore.Html.HtmlString("nav-link text-danger"), global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_1 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("asp-controller", "ApplicationUser", global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_2 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("asp-action", "Details", global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_3 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("class", new global::Microsoft.AspNetCore.Html.HtmlString("row col-sm-12"), global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_4 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("asp-action", "NewContactRequest", global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
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
        private global::Microsoft.AspNetCore.Mvc.TagHelpers.FormTagHelper __Microsoft_AspNetCore_Mvc_TagHelpers_FormTagHelper;
        private global::Microsoft.AspNetCore.Mvc.TagHelpers.RenderAtEndOfFormTagHelper __Microsoft_AspNetCore_Mvc_TagHelpers_RenderAtEndOfFormTagHelper;
        private global::Microsoft.AspNetCore.Mvc.TagHelpers.AnchorTagHelper __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper;
        #pragma warning disable 1998
        public async override global::System.Threading.Tasks.Task ExecuteAsync()
        {
            WriteLiteral("\r\n <dl class=\"row\">\r\n\r\n     <dt class=\"col-sm-4\">Nickname</dt> <dt class=\"col-sm-4\">Email</dt> <dt class=\"col-sm-4\">Status</dt>\r\n");
#nullable restore
#line 6 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_UsersPartial.cshtml"
      foreach(var a in Model)
     {

#line default
#line hidden
#nullable disable
            WriteLiteral("             ");
            __tagHelperExecutionContext = __tagHelperScopeManager.Begin("form", global::Microsoft.AspNetCore.Razor.TagHelpers.TagMode.StartTagAndEndTag, "ebd6ca97afea8478bb9278dcf15d5a690e0ea5655430", async() => {
                WriteLiteral("\r\n                 <input name=\"id\" type=\"hidden\"");
                BeginWriteAttribute("value", " value=\"", 339, "\"", 352, 1);
#nullable restore
#line 9 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_UsersPartial.cshtml"
WriteAttributeValue("", 347, a.Id, 347, 5, false);

#line default
#line hidden
#nullable disable
                EndWriteAttribute();
                WriteLiteral("/>\r\n                 <dd class=\"col-sm-4\"> ");
                __tagHelperExecutionContext = __tagHelperScopeManager.Begin("a", global::Microsoft.AspNetCore.Razor.TagHelpers.TagMode.StartTagAndEndTag, "ebd6ca97afea8478bb9278dcf15d5a690e0ea5656152", async() => {
#nullable restore
#line 10 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_UsersPartial.cshtml"
                                                                                                                                             Write(a.Nickname);

#line default
#line hidden
#nullable disable
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
#line 10 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_UsersPartial.cshtml"
                                                                                                                               WriteLiteral(a.Id);

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
                WriteLiteral("</dd>\r\n                 <dd class=\"col-sm-4\">");
#nullable restore
#line 11 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_UsersPartial.cshtml"
                                 Write(a.Email);

#line default
#line hidden
#nullable disable
                WriteLiteral("</dd>\r\n");
#nullable restore
#line 12 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_UsersPartial.cshtml"
                  if (a.Contacts.Contains(ViewData["CurrentApplicationUser"]))
                 {

#line default
#line hidden
#nullable disable
                WriteLiteral("                     <dd class=\"col-sm-4\"> ");
#nullable restore
#line 14 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_UsersPartial.cshtml"
                                       Write("Contact of yours");

#line default
#line hidden
#nullable disable
                WriteLiteral("</dd>\r\n");
#nullable restore
#line 15 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_UsersPartial.cshtml"
                 }
                 else if (a.ContactRequestSender.Contains(ViewData["CurrentApplicationUser"]))
                 {

#line default
#line hidden
#nullable disable
                WriteLiteral("                     <dd class=\"col-sm-4\"> ");
#nullable restore
#line 18 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_UsersPartial.cshtml"
                                       Write("Contact request sent");

#line default
#line hidden
#nullable disable
                WriteLiteral("</dd>\r\n");
#nullable restore
#line 19 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_UsersPartial.cshtml"
                 }
                 else if (a.ContactRequestReceiver.Contains(ViewData["CurrentApplicationUser"]))
                 {

#line default
#line hidden
#nullable disable
                WriteLiteral("                     <dd class=\"col-sm-4\"> ");
#nullable restore
#line 22 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_UsersPartial.cshtml"
                                       Write("You have a contact request from this user");

#line default
#line hidden
#nullable disable
                WriteLiteral("</dd>\r\n");
#nullable restore
#line 23 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_UsersPartial.cshtml"
                 }
                 else
                 {

#line default
#line hidden
#nullable disable
                WriteLiteral("                     <dd class=\"col-sm-4\">\r\n                         <button class=\"btn btn-primary\" type=\"submit\">Send contact request</button>\r\n                     </dd>\r\n");
#nullable restore
#line 29 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_UsersPartial.cshtml"
                 }

#line default
#line hidden
#nullable disable
                WriteLiteral("             ");
            }
            );
            __Microsoft_AspNetCore_Mvc_TagHelpers_FormTagHelper = CreateTagHelper<global::Microsoft.AspNetCore.Mvc.TagHelpers.FormTagHelper>();
            __tagHelperExecutionContext.Add(__Microsoft_AspNetCore_Mvc_TagHelpers_FormTagHelper);
            __Microsoft_AspNetCore_Mvc_TagHelpers_RenderAtEndOfFormTagHelper = CreateTagHelper<global::Microsoft.AspNetCore.Mvc.TagHelpers.RenderAtEndOfFormTagHelper>();
            __tagHelperExecutionContext.Add(__Microsoft_AspNetCore_Mvc_TagHelpers_RenderAtEndOfFormTagHelper);
            __tagHelperExecutionContext.AddHtmlAttribute(__tagHelperAttribute_3);
            __Microsoft_AspNetCore_Mvc_TagHelpers_FormTagHelper.Action = (string)__tagHelperAttribute_4.Value;
            __tagHelperExecutionContext.AddTagHelperAttribute(__tagHelperAttribute_4);
            await __tagHelperRunner.RunAsync(__tagHelperExecutionContext);
            if (!__tagHelperExecutionContext.Output.IsContentModified)
            {
                await __tagHelperExecutionContext.SetOutputContentAsync();
            }
            Write(__tagHelperExecutionContext.Output);
            __tagHelperExecutionContext = __tagHelperScopeManager.End();
            WriteLiteral("\r\n");
#nullable restore
#line 31 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_UsersPartial.cshtml"

     }

#line default
#line hidden
#nullable disable
            WriteLiteral(" </dl>\r\n");
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
        public global::Microsoft.AspNetCore.Mvc.Rendering.IHtmlHelper<IEnumerable<UNIMEET.Data.ApplicationUser>> Html { get; private set; }
    }
}
#pragma warning restore 1591
