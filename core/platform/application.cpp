#include "framework.h"
#include "application.h"
#include "system.h"
#include "session.h"
#include "acme/platform/system_setup.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/node.h"
//#include "apex/platform/os_context.h"

#include "aura/platform/node.h"
#include "aura/user/user/check_box.h"
#include "aura/user/user/still.h"
#include "axis/user/user/line_layout.h"
#include "core/filesystem/filemanager/document.h"
#include "core/filesystem/filemanager/filemanager.h"
#include "core/user/user/user.h"
#include "core/user/userex/progress.h"
#include "core/user/userex/pane_tab_impact.h"


namespace core
{


   //void initialize()
   //{

   //   factory()->add_factory_item < ::core::system, ::acme::system >();

   //}


   application::application()
   {

      //::core::initialize();

      m_pcoreapplication = this;

      //m_strAppId = "app-complex/drawing";

   }


   application::~application()
   {

   }



   void application::common_construct()
   {


   }


   void application::on_set_platform()
   {

      ::bred::application::on_set_platform();

      factory()->add_factory_item < ::core::system, ::acme::system >();
      factory()->add_factory_item < ::core::session, ::acme::session >();
      factory()->add_factory_item < ::core::user, ::user::user >();



   }

   ::core::session * application::get_session()
   {

      auto pacmesession = session();

      return ::is_set(pacmesession) ? pacmesession->m_pcoresession : nullptr;

   }


   ::core::system * application::get_system()
   {

      auto pacmesystem = system();

      return ::is_set(pacmesystem) ? pacmesystem->m_pcoresystem : nullptr;

   }


   void application::initialize(::particle * pparticle)
   {

      //auto estatus =

      ::base::application::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   ::pointer<progress::real>application::show_progress(::user::interaction * puiParent, const ::string & pszTitle, ::collection::count iProgressCount)
   {

      auto pprogresscontrol = __create_new <  ::userex::progress_control >();

      pprogresscontrol->defer_show(puiParent, pszTitle, iProgressCount);

      return ::transfer(pprogresscontrol);

   }


   void application::initialize_rich_text_kit()
   {

      auto psession = get_session();

      auto puser = psession->user()->m_pcoreuser;

      puser->will_use_impact_hint(COLORSEL_IMPACT);
      puser->will_use_impact_hint(FONTSEL_IMPACT);

      auto psystem = system()->m_pcoresystem;

      psystem->initialize_rich_text();

      auto pfactory = psystem->factory("text_format", "rtf");

      //if (!pfactory)
      //{


      //   warning() <<"exiting application. Could not do factory_item exchange text_format rtf.";

      //   return pfactory;

      //}

      pfactory->merge_to_global_factory();


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

      strApplicationTitle = get_app()->m_papexapplication->title();

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

      auto strMenuImpactPartialHtml = file()->safe_get_string("matter://options.partial.html");

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

      strOptionsHtml += system()->m_pnode->m_pauranode->system_options_html();

      strOptionsHtml += "</body>";
      strOptionsHtml += "</html>";

      return strOptionsHtml;

   }


   ::filemanager::filemanager * application::filemanager() const
   {

      auto & pfilemanager = ((application *)this)->m_pfilemanager;

      if (!pfilemanager)
      {

         ((application *)this)->__construct_new(pfilemanager);

         pfilemanager->initialize_filemanager_component(((application *)this));

      }

      return pfilemanager;

   }


   void application::create_options_footer(::user::interaction * puserinteraction)
   {

      ::base::application::create_options_footer(puserinteraction);

      //if (m_bEnableAutoStartOption)
      //{

        // create_auto_start_option(pparent);

      //}

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


   void application::term_instance()
   {

      m_ppaneimpactCore.release();

      ::bred::application::term_instance();

   }


   void application::create_auto_start_option(::user::interaction * pparent)
   {

      auto playoutLine = create_line_layout(pparent, e_orientation_horizontal);

      auto pcheckbox = create_check_box<::user::check_box>(playoutLine, "");

      bool bCheck = false;

      auto papplication = m_papexapplication;

      bool bUserAutoStart = node()->is_user_auto_start(papplication->get_executable_appid());

      pcheckbox->set_check(bUserAutoStart, ::e_source_initialize);

      pcheckbox->check_changed(this) += [this](::data::check_property & checkproperty, const ::payload & payload, const ::action_context & actioncontext)
         {

            bool bCheck = payload.as_bool();

            auto papplication = m_papexapplication;

            node()->register_user_auto_start(
               papplication,
               "--auto_start=1",
               bCheck);

         };

      create_label<::user::still>(playoutLine, "Enable Auto Start");

   }


   void application::on_prompt_write_file(::user::controller * pusercontroller)
   {

      file_manager_save_as(pusercontroller);

   }


   void application::file_manager_save_as(::user::controller *pusercontroller)
   {
      
      ::pointer < ::user::document > puserdocument = pusercontroller;
      
      if(m_ppaneimpactCore && puserdocument)
      {
         
         m_ppaneimpactCore->set_current_tab_by_id("file_manager_save");
         
         m_ppaneimpactCore->filemanager_document("file_manager_save")->FileManagerSaveAs(puserdocument);

      }


   }


} // namespace core



