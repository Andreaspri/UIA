#pragma checksum "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_SearchGroupContactsPartial.cshtml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "7fe5c6654ddd72d5edb2536e442a36ece81b89c1"
// <auto-generated/>
#pragma warning disable 1591
[assembly: global::Microsoft.AspNetCore.Razor.Hosting.RazorCompiledItemAttribute(typeof(AspNetCore.Views_Shared__SearchGroupContactsPartial), @"mvc.1.0.view", @"/Views/Shared/_SearchGroupContactsPartial.cshtml")]
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
#line 1 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_SearchGroupContactsPartial.cshtml"
using Newtonsoft.Json;

#line default
#line hidden
#nullable disable
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"7fe5c6654ddd72d5edb2536e442a36ece81b89c1", @"/Views/Shared/_SearchGroupContactsPartial.cshtml")]
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"4cedd0e0588076dd7dac34d5a11fdd632ec62af8", @"/Views/_ViewImports.cshtml")]
    public class Views_Shared__SearchGroupContactsPartial : global::Microsoft.AspNetCore.Mvc.Razor.RazorPage<IEnumerable<UNIMEET.Data.ApplicationUser>>
    {
        #pragma warning disable 1998
        public async override global::System.Threading.Tasks.Task ExecuteAsync()
        {
            WriteLiteral("\r\n");
#nullable restore
#line 4 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_SearchGroupContactsPartial.cshtml"
  
    var selected = JsonConvert.DeserializeObject<List<string>>(ViewBag.selected);

#line default
#line hidden
#nullable disable
#nullable restore
#line 7 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_SearchGroupContactsPartial.cshtml"
 foreach (var user in Model)
{

#line default
#line hidden
#nullable disable
            WriteLiteral("<tr>\r\n    <td>\r\n");
#nullable restore
#line 11 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_SearchGroupContactsPartial.cshtml"
          
            var isSelected = false;
            foreach (var id in selected)
            {
                if (user.Id == id)
                {
                    isSelected = true;
                }
            }
            if (isSelected)
            {

#line default
#line hidden
#nullable disable
            WriteLiteral("                <button class=\"btn btn-success\"");
            BeginWriteAttribute("onclick", " onclick=\"", 541, "\"", 575, 3);
            WriteAttributeValue("", 551, "selectMember(\'", 551, 14, true);
#nullable restore
#line 22 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_SearchGroupContactsPartial.cshtml"
WriteAttributeValue("", 565, user.Id, 565, 8, false);

#line default
#line hidden
#nullable disable
            WriteAttributeValue("", 573, "\')", 573, 2, true);
            EndWriteAttribute();
            WriteLiteral(">");
#nullable restore
#line 22 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_SearchGroupContactsPartial.cshtml"
                                                                              Write(user.Nickname);

#line default
#line hidden
#nullable disable
            WriteLiteral("</button>\r\n");
#nullable restore
#line 23 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_SearchGroupContactsPartial.cshtml"
            }
            else
            {

#line default
#line hidden
#nullable disable
            WriteLiteral("                <button class=\"btn btn-primary\"");
            BeginWriteAttribute("onclick", " onclick=\"", 697, "\"", 731, 3);
            WriteAttributeValue("", 707, "selectMember(\'", 707, 14, true);
#nullable restore
#line 26 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_SearchGroupContactsPartial.cshtml"
WriteAttributeValue("", 721, user.Id, 721, 8, false);

#line default
#line hidden
#nullable disable
            WriteAttributeValue("", 729, "\')", 729, 2, true);
            EndWriteAttribute();
            WriteLiteral(">");
#nullable restore
#line 26 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_SearchGroupContactsPartial.cshtml"
                                                                              Write(user.Nickname);

#line default
#line hidden
#nullable disable
            WriteLiteral("</button>\r\n");
#nullable restore
#line 27 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_SearchGroupContactsPartial.cshtml"
            }
            
        

#line default
#line hidden
#nullable disable
            WriteLiteral("        \r\n    </td>\r\n</tr>\r\n");
#nullable restore
#line 33 "C:\Users\Andreas\ikt201_project\UNIMEET\UNIMEET\Views\Shared\_SearchGroupContactsPartial.cshtml"
}

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n\r\n");
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
