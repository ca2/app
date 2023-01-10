#include "framework.h"
#include "application.h"
#include "session.h"
#include "system.h"
#include "acme/filesystem/file/item_array.h"
#include "acme/platform/request.h"
#include "aura/user/user/interaction.h"
#include "base/user/user/impact_system.h"
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

         auto puser = psession->user();

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


} // namespace base



