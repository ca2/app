#include "framework.h"
#include "application.h"
#include "session.h"
#include "system.h"
#include "acme/filesystem/file/item_array.h"
#include "acme/handler/request.h"
#include "apex/platform/os_context.h"
#include "aura/user/user/button.h"
#include "aura/user/user/check_box.h"
#include "aura/user/user/interaction.h"
#include "axis/user/user/form_handler.h"
#include "axis/user/user/line_layout.h"
#include "base/user/menu/item.h"
#include "base/user/menu/menu.h"
#include "base/user/user/document_manager.h"
#include "base/user/user/impact_system.h"
#include "aura/user/user/still.h"
#include "base/user/user/tab_impact.h"
#include "base/user/user/user.h"


namespace base
{


   application::application()
   {

      //::base::initialize();

      m_pbaseapplication = this;


    

   }


   void application::on_set_platform()
   {

      ::axis::application::on_set_platform();

      factory()->add_factory_item< ::base::system, ::acme::system>();

   }


   void application::initialize(::particle * pparticle)
   {

      ::axis::application::initialize(pparticle);

      ::user::document_manager_container::initialize(pparticle);


   }


   void application::process_term()
   {

      m_ptabimpactBase.release();

      axis::application::process_term();

   }


   void application::destroy()
   {

      ::user::document_manager_container::destroy();

      ::axis::application::destroy();

   }


   ::pointer < ::data::data > application::create_default_new_document_data()
   {

      auto pdataNewDocument = __create_new < ::data::data >();

      return pdataNewDocument;

   }


   application::~application()
   {

   }



   ::user::document *application::place_hold(::user::interaction * pinteraction)
   {

      return nullptr;

   }


   void application::on_create_split_impact(::user::split_impact* psplit)
   {


   }


   void application::on_change_cur_sel(::user::tab* ptab)
   {


   }


   void application::create_impact_system()
   {

      //return ::success;

   }


   void application::on_create_impact(::user::impact_data* pimpactdata)
   {


   }


   void application::close(::apex::enum_end eend)
   {

      auto psession = get_session();

      if (psession->m_puser)
      {

         auto puser = psession->baseuser();

         auto pdocumentmanager = puser->document_manager();

         if (pdocumentmanager)
         {

            pdocumentmanager->close_all_documents(eend != ::apex::e_end_close);

         }

      }

      if (document_manager())
      {

         document_manager()->close_all_documents(eend != ::apex::e_end_close);

      }

      ::aura::application::close(eend);

   }


   ::pointer<::user::document>application::defer_create_impact(string strImpact, ::user::interaction* puiParent, e_window_flag ewindowflag, const ::atom& atom)
   {

      return nullptr;

   }

   
   void application::on_file_manager_open(::filemanager::data* pdata, const ::file::item_array& itema, const ::action_context& action_context)
   {

      auto prequest = __create_new<::request>();

      if (itema.get_size() == 1)
      {

         prequest->m_payloadFile = itema[0]->user_path();

      }
      else
      {

         string_array stra;

         for (auto& pitem : itema)
         {

            stra.add(pitem->user_path());

         }

         prequest->m_payloadFile = stra;

      }

      post_request(prequest);

   }

   
   ::base::system * application::get_system()
   {

      auto pacmesystem = system();

      return ::is_set(pacmesystem) ? pacmesystem->m_pbasesystem : nullptr;

   }


   ::base::session * application::get_session()
   {

      auto pacmesession = session();

      return ::is_set(pacmesession) ? pacmesession->m_pbasesession : nullptr;

   }


   ::base::system * session::get_system()
   {

      auto pacmesystem = system();

      return ::is_set(pacmesystem) ? pacmesystem->m_pbasesystem : nullptr;

   }


   void application::create_options_impact(::user::interaction * pparent)
   {

      auto playout = create_line_layout(pparent, e_orientation_vertical);

      create_options_header(playout);
      create_options_body(playout);
      create_options_footer(playout);

   }


   void application::create_options_header(::user::interaction * pparent)
   {


   }


   void application::create_options_body(::user::interaction * pparent)
   {


   }


   void application::create_options_footer(::user::interaction * pparent)
   {

      for (auto & strLibrary : m_straOptionsFormMakerLibrary)
      {

         auto & pfactory = system()->factory(strLibrary);

         auto pformhandler = __create<::user::form_handler>(pfactory);

         pformhandler->design_form(pparent);

         pparent->payload("form_handler_payload_array").payload_array_reference().add(pformhandler);

      }
//)

      if (m_bEnableAutoStartOption)
      {

         create_auto_start_option(pparent);

      }

      create_about_option(pparent);

   }


   void application::create_auto_start_option(::user::interaction* pparent)
   {

      auto playoutLine = create_line_layout(pparent, e_orientation_horizontal);

      auto pcheckbox = create_check_box<::user::check_box>(playoutLine, "");

      //bool bCheck = false;

//      auto papplication = m_papexapplication;

      bool bUserAutoStart = os_context()->is_user_auto_start(get_executable_appid());

      pcheckbox->_001SetCheck(bUserAutoStart, ::e_source_initialize);

      pcheckbox->m_callbackOnCheck = [this](auto pcheck)
      {

         bool bCheck = pcheck->bcheck();

         auto papplication = m_papexapplication;

         os_context()->register_user_auto_start(
            papplication->get_executable_appid(),
            papplication->get_executable_path(),
            "--auto_start=1",
            bCheck);

      };

      create_label<::user::still>(playoutLine, "Enable Auto Start");

   }


   void application::create_about_option(::user::interaction * pparent)
   {

      auto pbutton = create_button<::user::button>(pparent, "About");

      pbutton->m_callbackOnClick = [this](::user::interaction * puserinteraction, ::item * pitem)
         {

            show_about_box();

            return true;

         };

   }


   void application::create_about_impact(::user::interaction * pparent)
   {

      auto playoutLine = create_line_layout(pparent, e_orientation_vertical);

      auto lines = get_about_box_lines();

      for (auto & line : lines)
      {

         create_label<::user::still>(playoutLine, line);

      }

   }


   void application::on_after_prepare_impact_menu(::user::menu * pmenu)
   {
      

      if (!pmenu->m_pmenuitem)
      {

         pmenu->__construct_new(pmenu->m_pmenuitem);

         pmenu->m_pmenuitem->m_pmenu = pmenu;

      }
      else
      {

         auto pitemNewChild = __create_new<::user::menu_item>();
         pitemNewChild->m_pmenu = pmenu;
         pitemNewChild->m_atom = "separator";
         pmenu->m_pmenuitem->add_item(pitemNewChild);

      }




      {

         auto pitemNewChild = __create_new<::user::menu_item>();
         pitemNewChild->m_pmenu = pmenu;
         pitemNewChild->m_atom = "display_about";
         pitemNewChild->m_strTitle = "About";
         pmenu->m_pmenuitem->add_item(pitemNewChild);

      }


   }


   void application::show_about_box()
   {

      if (!m_ptabimpactBase)
      {

         ::axis::application::show_about_box();

         return;

      }

      m_ptabimpactBase->show_about_tab_pane();

   }


} // namespace base



