#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif


namespace base
{


   application::application(const char * pszAppId) :
      ::axis::application(pszAppId)
   {

      m_pbaseapplication = this;

   }


   ::estatus     application::initialize(::layered * pobjectContext)
   {

      auto estatus = ::axis::application::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      estatus = ::user::document_manager_container::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   application::~application()
   {

   }

   void application::assert_valid() const
   {

      ::axis::application::assert_valid();

   }


   void application::dump(dump_context & dumpcontext) const
   {

      ::axis::application::dump(dumpcontext);

   }



   ::user::document *application::place_hold(::user::interaction * pinteraction)
   {

      return nullptr;

   }

   void application::on_create_split_view(::user::split_view* psplit)
   {

   }


   void application::on_change_cur_sel(::user::tab* ptab)
   {



   }




   ::estatus     application::create_impact_system()
   {

      return ::success;

   }



   void application::on_create_impact(::user::impact_data* pimpactdata)
   {


   }


   void application::close(::apex::enum_end eend)
   {

      if (Session->m_puser)
      {

         auto puser = User;

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

   __pointer(::user::document) application::defer_create_view(string strView, ::user::interaction* puiParent, ewindowflag ewindowflag, const ::id& id)
   {

      //auto pcontroller = ::aura::application::defer_create_view(strView, puiParent, ewindowflag, id);

      //if (pcontroller)
      //{

      //   return pcontroller;

      //}

      return nullptr;

   }


} // namespace base



