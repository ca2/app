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

   }


   application::~application()
   {

   }


   void application::common_construct()
   {


   }


   ::e_status application::initialize(::object * pobject)
   {

      auto estatus = ::base::application::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   __pointer(progress::real) application::show_progress(::user::interaction* puiParent, const ::string & pszTitle, ::count iProgressCount)
   {

      auto pprogresscontrol = __create_new <  ::userex::progress_control >();

      pprogresscontrol->defer_show(puiParent, pszTitle, iProgressCount);

      return ::move(pprogresscontrol);

   }


   string application::prepare_menu_impact()
   {

      string strHeader = prepare_menu_impact_header();

      string strMainBody = prepare_menu_impact_main_body();

      string strFooter = prepare_menu_impact_footer();

      string strMenuImpact;

      strMenuImpact = strHeader + strMainBody + strFooter;

      return strMenuImpact;

   }


   string application::prepare_menu_impact_header()
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


   string application::prepare_menu_impact_main_body()
   {

      return file().as_string("matter://menu_impact.partial.html");

   }


   string application::prepare_menu_impact_footer()
   {

      string strOptionsHtml;

      strOptionsHtml += m_psystem->m_pnode->m_pauranode->system_options_html();

      strOptionsHtml += "</body>";
      strOptionsHtml += "</html>";

      return strOptionsHtml;

   }


} // namespace core



