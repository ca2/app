#include "framework.h"
#include "application.h"
#include "system.h"
#include "acme/platform/system_setup.h"
#include "aura/platform/node.h"
#include "core/user/userex/progress.h"
#include "core/user/userex/pane_tab_impact.h"


namespace core
{


   void initialize()
   {

      ::factory::add_factory_item < ::core::system, ::acme::system >();

   }


   application::application()
   {

      ::core::initialize();

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


   ::pointer<progress::real>application::show_progress(::user::interaction* puiParent, const ::string & pszTitle, ::count iProgressCount)
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

      strApplicationTitle = get_app()->title();

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

      auto strMenuImpactPartialHtml = file().safe_get_string("matter://options.partial.html");

      return strMenuImpactPartialHtml;

   }


   string application::prepare_impact_options_footer()
   {

      string strOptionsHtml;

      if (m_bEnableAutoStartOption)
      {

         strOptionsHtml += "<br/>";
         strOptionsHtml += "<br/>";
         strOptionsHtml += "<input type=\"checkbox\" id=\"user_auto_start_checkbox\" />";
         strOptionsHtml += "&nbsp;Enable Auto Start";
         strOptionsHtml += "<br/>";
         strOptionsHtml += "<br/>";


      }

      strOptionsHtml += m_psystem->m_pnode->m_pauranode->system_options_html();

      strOptionsHtml += "</body>";
      strOptionsHtml += "</html>";

      return strOptionsHtml;

   }

   
   bool application::handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, property_set & propertyset)
   {

      if (strObject == "pane_tab_impact")
      {

         if (strMember == "add_pane_tab_impact_handler_library")
         {

            string strLibrary = propertyset["handler_library"];

            m_ppaneimpactCore->add_pane_tab_impact_handler_library(strLibrary);

            return true;

         }

      }

      return ::bred::application::handle_call(payload, strObject, strMember, propertyset);

   }


} // namespace core



