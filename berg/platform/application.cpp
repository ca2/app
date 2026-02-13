#include "framework.h"
#include "application.h"
#include "session.h"
#include "system.h"
#include "acme/filesystem/file/item_array.h"
#include "acme/handler/request.h"
#include "apex/platform/node.h"
//#include "apex/platform/os_context.h"

#include "aura/user/user/button.h"
#include "aura/user/user/check_box.h"
#include "aura/user/user/interaction.h"
#include "axis/user/user/form_handler.h"
#include "axis/user/user/line_layout.h"
#include "berg/user/menu/item.h"
#include "berg/user/menu/menu.h"
#include "berg/user/user/document_manager.h"
#include "berg/user/user/document_manager_container.h"
#include "berg/user/user/impact_system.h"
#include "aura/user/user/still.h"
#include "berg/user/user/tab_impact.h"
#include "berg/user/user/user.h"


namespace berg
{


   application::application()
   {

      //::base::initialize();

      //m_pbaseapplication = this;


    

   }


   void application::on_set_platform()
   {

      ::axis::application::on_set_platform();

      factory()->add_factory_item< ::berg::system, ::platform::system>();
      factory()->add_factory_item< ::berg::user, ::user::user>();

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

      auto pdataNewDocument = øcreate_new < ::data::data >();

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


   void application::close(::enum_exit eexit)
   {

      auto puser = user();

      if (puser)
      {

         ::cast < ::user::document_manager_container > pdocumentmanagercontainer = puser;

         if (pdocumentmanagercontainer)
         {

            auto pdocumentmanager = pdocumentmanagercontainer->document_manager();

            if(pdocumentmanager)
            {

               pdocumentmanager->close_all_documents(eexit != ::e_exit_close);

            }

         }

      }

      if (document_manager())
      {

         document_manager()->close_all_documents(eexit != ::e_exit_close);

      }

      ::aura::application::close(eexit);

   }


   ::pointer<::user::document>application::defer_create_impact(const ::scoped_string & scopedstrImpact, ::user::interaction* puiParent, e_window_flag ewindowflag, const ::atom& atom)
   {

      return nullptr;

   }

   
   void application::on_file_manager_open(::filemanager::data* pdata, const ::file::item_array& itema, const ::action_context& action_context)
   {

      auto prequest = øcreate_new<::request>();

      if (itema.get_size() == 1)
      {

         prequest->m_payloadFile = itema[0]->user_path();

      }
      else
      {

         string_array_base stra;

         for (auto& pitem : itema)
         {

            stra.add(pitem->user_path());

         }

         prequest->m_payloadFile = stra;

      }

      post_request(prequest);

   }

   
   // ::berg::system * application::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }
   //
   //
   // ::berg::session * application::get_session()
   // {
   //
   //    auto pacmesession = session();
   //
   //    return ::is_set(pacmesession) ? pacmesession : nullptr;
   //
   // }
   //
   //
   // ::berg::system * session::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }


   void application::create_options_impact(const ::atom &atom, ::user::interaction *pparent)
   {

      if(factory()->has_factory_item< ::user::options_impact_handler >())
      {

         øconstruct(m_poptionsimpacthandler);

      }

      auto playout = create_line_layout(pparent, e_orientation_vertical);

      create_options_header(atom, playout);
      create_options_body(atom, playout);
      create_options_footer(atom, playout);

   }


   void application::create_options_header(const ::atom &atom, ::user::interaction *pparent)
   {


   }


   void application::create_options_body(const ::atom &atom, ::user::interaction *pparent)
   {

      if(m_poptionsimpacthandler)
      {

         m_poptionsimpacthandler->create_options_impact(atom, pparent);

      }

   }


   void application::create_options_footer(const ::atom &atom, ::user::interaction *pparent)
   {

      for (auto & strLibrary : m_straOptionsFormMakerLibrary)
      {

         auto & pfactory = system()->factory(strLibrary);

         auto pformhandler = øcreate<::user::form_handler>(pfactory);

         pformhandler->design_form(pparent);

         pparent->payload("form_handler_payload_array").payload_array_reference().add(pformhandler);

      }
//)

      if (m_bEnableAutoStartOption)
      {

         create_auto_start_option(atom, pparent);

      }

      create_about_option(atom, pparent);

   }


   void application::create_auto_start_option(const ::atom &atom, ::user::interaction *pparent)
   {

      auto playoutLine = create_line_layout(pparent, e_orientation_horizontal);

      auto pcheckbox = create_check_box<::user::check_box>(playoutLine, "");

      //bool bCheck = false;

//      auto papplication = m_papexapplication;

      bool bUserAutoStart = node()->is_user_auto_start(get_executable_appid());

      pcheckbox->set_check(bUserAutoStart, ::e_source_initialize);

      pcheckbox->check_changed(this) += [this](auto & change)
      {

         bool bCheck = change.payload().as_bool();

         ///auto papplication = m_papexapplication;

         auto papplication = this;

         node()->register_user_auto_start(
            papplication,
            "--auto_start=1",
            bCheck);

      };

      create_label<::user::still>(playoutLine, "Enable Auto Start");

   }


   void application::create_about_option(const ::atom &atom, ::user::interaction *pparent)
   {

      auto pbutton = create_button<::user::button>(pparent, "About");

      pbutton->m_callbackOnClick = [this](::user::interaction * puserinteraction, ::item * pitem, ::user::activation_token * puseractivationtoken)->bool
         {

            show_about_box(puseractivationtoken);

            return true;

         };

   }


   void application::create_about_impact(const ::atom &atom, ::user::interaction *pparent)
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

         pmenu->øconstruct_new(pmenu->m_pmenuitem);

         pmenu->m_pmenuitem->m_pmenu = pmenu;

      }
      else
      {

         auto pitemNewChild = øcreate_new<::menu::item>();
         pitemNewChild->m_pmenu = pmenu;
         pitemNewChild->id() = "separator";
         pmenu->m_pmenuitem->add_item(pitemNewChild);

      }




      {

         auto pitemNewChild = øcreate_new<::menu::item>();
         pitemNewChild->m_pmenu = pmenu;
         pitemNewChild->id() = "display_about";
         pitemNewChild->m_strTitle = "About";
         pmenu->m_pmenuitem->add_item(pitemNewChild);

      }


   }


   void application::show_about_box(::user::activation_token * puseractivationtoken)
   {

      ::axis::application::show_about_box(puseractivationtoken);

      //if (!m_ptabimpactBase)
      //{

      //   ::axis::application::show_about_box();

      //   return;

      //}

      //m_ptabimpactBase->show_about_tab_pane();

   }


   void application::add_impact_system(const ::atom & atom, const ::pointer < ::user::impact_system > & pimpactsystem)
   {

      document_manager_container::add_impact_system(atom, pimpactsystem);

   }

   
   ::pointer<::user::impact_system> application::impact_system(const ::atom & atom)
   {
      
      session()->user();

      return document_manager_container::impact_system(atom);

   }


   int application::track_popup_menu(::menu::track_popup * ptrackpopup)
   {
      
      auto puser = user();

      puser->track_popup_menu(ptrackpopup);

      return 1;

   }


} // namespace berg



