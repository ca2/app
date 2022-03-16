#include "framework.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/constant/timer.h"


namespace account
{


   user_array::user_array()
   {

      defer_create_mutex();

   }


   user_array::~user_array()
   {

      cleanup_account();

   }


   void user_array::initialize_user_array(department* pdepartment)
   {

      //auto estatus = 
      
      ::object::initialize(pdepartment);

      //if(!estatus)
      //{

      //   return estatus;
      //
      //}

      m_paccount = pdepartment;

      ///return estatus;

   }

   void user_array::cleanup_networking()
   {

   }


   void user_array::cleanup_account()
   {

      cleanup_networking();

   }


   void user_array::_get_user(::file::path pathUrl, bool bInteractive)
   {

      __pointer(user) puser;

      auto psystem = m_psystem;

      auto purl = psystem->url();

      {

         string strHost = purl->get_server(pathUrl);

         //auto estatus = 
         
         __construct(puser);

         //if (!estatus)
         //{

         //   return;

         //}

         synchronous_lock synchronouslock(mutex());

         m_map[strHost] = puser;

      }

      if(puser == nullptr)
      {

         return;

      }

      puser->logon(pathUrl, bInteractive);

   }


   void user_array::logout()
   {

      if(get_user() == nullptr)
      {

         return;

      }

      auto pcontext = get_context();

      try
      {

         pcontext->m_papexcontext->file().erase(m_psystem->m_pacmedirectory->appdata()/"license_auth/00001.data");

      }
      catch(...)
      {

      }

      try
      {

         pcontext->m_papexcontext->file().erase(m_psystem->m_pacmedirectory->appdata()/"license_auth/00002.data");

      }
      catch(...)
      {

      }

   }


   __pointer(user) user_array::allocate_user()
   {

      return __create < user > ();

   }


   bool user_array::authorize_user(::account::user * puser)
   {

      return true;

   }


//   user * user_array::interactive_get_user(::file::path pathUrl)
//   {
//
//      if(get_user22(pathUrl) != nullptr)
//      {
//
//         return get_user22(pathUrl);
//
//      }
//
//      return _get_user(pathUrl, true);
//
//   }
//
//
//   user * user_array::noninteractive_get_user(::file::path pathUrl)
//   {
//
//      if(get_user22(pathUrl) != nullptr)
//      {
//
//         return get_user22(pathUrl);
//
//      }
//
//      return _get_user(pathUrl, false);
//
//   }


   void user_array::cleanup_users()
   {

      synchronous_lock synchronouslock(mutex());

      auto map = m_map;

      synchronouslock.unlock();

      __pointer(::axis::session) psession = get_session();

      for(auto & pair : map)
      {

         if(!pair.element2()->is_authenticated())
         {

            psession->on_erase_user(pair.element2());

            synchronouslock.lock();

            m_map.erase_key(pair.element1());

            synchronouslock.unlock();

         }

      }

   }



   user * user_array::get_user(::file::path pathUrl, bool bFetch, bool bInteractive)
   {

      __pointer(axis::session) psession = get_session();

      if(pathUrl.is_empty())
      {

         pathUrl = psession->account()->get_default_url();

      }

      auto psystem = m_psystem;

      auto purl = psystem->url();

      string strHost = purl->get_server(pathUrl);

      {

         synchronous_lock synchronouslock(mutex());

         auto & puser = m_map[strHost];

         if (bFetch && (puser.is_null() || !puser->is_authenticated()))
         {

            synchronouslock.unlock();

            _get_user(pathUrl, bInteractive);

         }

      }

      return m_map[strHost];

   }


   bool user_array::is_authenticated(::file::path pathUrl, bool bInteractive)
   {

      __pointer(::axis::application) papp = get_app();

      auto puser = papp->get_user(pathUrl, true, bInteractive);

      if(::is_null(puser))
      {

         return false;

      }

      return puser->is_authenticated();

   }


   void user_array::on_clock(enum_timer etimer)
   {

      if(etimer == e_timer_slow)
      {

         synchronous_lock synchronouslock(mutex());

         auto map = m_map;

         synchronouslock.unlock();

         for(auto & pair : map)
         {

            pair.element2()->on_clock(etimer);

         }

      }

   }


} // namespace account



