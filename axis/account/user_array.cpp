#include "framework.h"


namespace account
{


   user_array::user_array(department * pdepartment) :
      ::object(pdepartment),
      m_pdepartment(pdepartment)
   {

      defer_create_mutex();

   }


   user_array::~user_array()
   {

      cleanup_account();

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

      {

         string strHost = System.url().get_server(pathUrl);

         auto estatus = __construct(puser);

         if (!estatus)
         {

            return;

         }

         sync_lock sl(mutex());

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

      try
      {

         Context.file().del(::dir::appdata()/"license_auth/00001.data");

      }
      catch(...)
      {

      }

      try
      {

         Context.file().del(::dir::appdata()/"license_auth/00002.data");

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

      sync_lock sl(mutex());

      auto map = m_map;

      sl.unlock();

      for(auto & pair : map)
      {

         if(!pair.element2()->is_authenticated())
         {

            auto psession = Session;

            psession->on_remove_user(pair.element2());

            sl.lock();

            m_map.remove_key(pair.element1());

            sl.unlock();

         }

      }

   }



   user * user_array::get_user(::file::path pathUrl, bool bFetch, bool bInteractive)
   {

      if(pathUrl.is_empty())
      {

         auto psession = Session;

         pathUrl = psession->account()->get_default_url();

      }

      string strHost = System.url().get_server(pathUrl);

      {

         sync_lock sl(mutex());

         auto & puser = m_map[strHost];

         if (bFetch && (puser.is_null() || !puser->is_authenticated()))
         {

            sl.unlock();

            _get_user(pathUrl, bInteractive);

         }

      }

      return m_map[strHost];

   }


   bool user_array::is_authenticated(::file::path pathUrl, bool bInteractive)
   {

      auto puser = Application.get_user(pathUrl, true, bInteractive);

      if(::is_null(puser))
      {

         return false;

      }

      return puser->is_authenticated();

   }


   void user_array::on_clock(enum_clock eclock)
   {

      if(eclock == e_clock_slow)
      {

         sync_lock sl(mutex());

         auto map = m_map;

         sl.unlock();

         for(auto & pair : map)
         {

            pair.element2()->on_clock(eclock);

         }

      }

   }


} // namespace account



