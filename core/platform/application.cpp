#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif

#include "acme/platform/static_setup.h"
#include "core/user/userex/progress.h"


namespace core
{


   application::application()
   {

      m_pcoreapplication = this;

      m_strAppId = "app-complex/drawing";

   }


   application::~application()
   {

   }


   void application::common_construct()
   {


   }


   void application::initialize(::object * pobject)
   {

      //auto estatus =
      
      ::base::application::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   __pointer(progress::real) application::show_progress(::user::interaction* puiParent, const ::string & pszTitle, ::count iProgressCount)
   {

      auto pprogresscontrol = __create_new <  ::userex::progress_control >();

      pprogresscontrol->defer_show(puiParent, pszTitle, iProgressCount);

      return ::move(pprogresscontrol);

   }


   string application::prepare_impact_options()
   {

      string strHeader = prepare_impact_options_header();

      string strMainBody = prepare_impact_options_main_body();

      string strFooter = prepare_impact_options_footer();

      string strMenuImpact;

      strMenuImpact = strHeader + strMainBody + strFooter;

      return strMenuImpact;

   }


   string application::prepare_impact_options_header()
   {

      string strApplicationTitle;

      strApplicationTitle = get_application()->title();

      string strHeader__;

      strHeader__ += "<html>\n";
      strHeader__ += "<head>\n";
      strHeader__ += "<style>\n";
      strHeader__ += "  h1\n";
      strHeader__ += "  {\n";
      strHeader__ += "     font-family: Tahoma;\n";
      strHeader__ += "  }\n";
      strHeader__ += "\n";
      strHeader__ += "  h2\n";
      strHeader__ += "  {\n";
      strHeader__ += "     font-family: Tahoma;\n";
      strHeader__ += "  }\n";
      strHeader__ += "</style>\n";
      strHeader__ += "</head>\n";
      strHeader__ += "<body style=\"background-color: #80ffffff;\">\n";
      strHeader__ += "\n";
      strHeader__ += "<h1>" + strApplicationTitle + "</h1>\n";

      return strHeader__;

   }


   string application::prepare_impact_options_main_body()
   {

      auto strMenuImpactPartialHtml = file().as_string("matter://options.partial.html");

      return strMenuImpactPartialHtml;

   }


   string application::prepare_impact_options_footer()
   {

      string strOptionsHtml;

      if (m_bEnableAutoStartOption)
      {

         strOptionsHtml += "<br/>";
         strOptionsHtml += "<br/>";
         strOptionsHtml += "<input type=\"checkbox\" atom=\"user_auto_start_checkbox\" />";
         strOptionsHtml += "&nbsp;Enable Auto Start";
         strOptionsHtml += "<br/>";
         strOptionsHtml += "<br/>";


      }

      strOptionsHtml += m_psystem->m_pnode->m_pauranode->system_options_html();

      strOptionsHtml += "</body>";
      strOptionsHtml += "</html>";

      return strOptionsHtml;

   }


} // namespace core



