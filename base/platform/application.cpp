#include "framework.h"
#include "application.h"
#include "session.h"
#include "system.h"
#include "acme/filesystem/file/item_array.h"
#include "acme/handler/request.h"
#include "apex/platform/os_context.h"
#include "aura/user/user/check_box.h"
#include "aura/user/user/interaction.h"
#include "axis/user/user/line_layout.h"
#include "base/user/user/document_manager.h"
#include "base/user/user/impact_system.h"
#include "aura/user/user/still.h"
#include "base/user/user/user.h"
#include "base/user/user/document_manager.h"


namespace base
{


   //void initialize()
   //{

   //}


   application::application()
   {

      //::base::initialize();

      m_pbaseapplication = this;


      factory()->add_factory_item< ::base::system, ::acme::system>();



   }


   void application::initialize(::particle * pparticle)
   {

      ::axis::application::initialize(pparticle);

      ::user::document_manager_container::initialize(pparticle);


   }


   application::~application()
   {

   }


//   void application::assert_ok() const
//   {
//
//      ::axis::application::assert_ok();
//
//   }
//
//
//   void application::dump(dump_context & dumpcontext) const
//   {
//
//      ::axis::application::dump(dumpcontext);
//
//   }


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

      auto pacmesystem = acmesystem();

      return ::is_set(pacmesystem) ? pacmesystem->m_pbasesystem : nullptr;

   }


   ::base::session * application::get_session()
   {

      auto pacmesession = acmesession();

      return ::is_set(pacmesession) ? pacmesession->m_pbasesession : nullptr;

   }


   ::base::system * session::get_system()
   {

      auto pacmesystem = acmesystem();

      return ::is_set(pacmesystem) ? pacmesystem->m_pbasesystem : nullptr;

   }


   void application::create_options_form(::user::interaction * pparent)
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

      if (m_bEnableAutoStartOption)
      {

         create_auto_start_option(pparent);

      }

   }


   void application::create_auto_start_option(::user::interaction* pparent)
   {

      auto playoutLine = create_line_layout(pparent, e_orientation_horizontal);

      auto pcheckbox = create_check_box<::user::check_box>(playoutLine, "");

      //bool bCheck = false;

      auto papplication = acmeapplication()->m_papexapplication;

      bool bUserAutoStart = os_context()->is_user_auto_start(papplication->get_executable_appid());

      pcheckbox->_001SetCheck(bUserAutoStart, ::e_source_initialize);

      pcheckbox->m_callbackOnCheck = [this](auto pcheck)
      {

         bool bCheck = pcheck->bcheck();

         auto papplication = acmeapplication()->m_papexapplication;

         os_context()->register_user_auto_start(
            papplication->get_executable_appid(),
            papplication->get_executable_path(),
            "--auto_start=1",
            bCheck);

      };

      create_label<::user::still>(playoutLine, "Enable Auto Start");

   }


} // namespace base



