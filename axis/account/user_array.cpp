#include "framework.h"
#include "user_array.h"
#include "user.h"
#include "department.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/constant/timer.h"
#include "acme/prototype/prototype/url.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "axis/platform/session.h"
#include "axis/platform/application.h"


namespace account
{


   user_array::user_array()
   {

      defer_create_synchronization();

   }


   user_array::~user_array()
   {

      cleanup_account();

   }


   void user_array::initialize_user_array(department* pdepartment)
   {

      //auto estatus = 
      
      ::matter::initialize(pdepartment);

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


   void user_array::_get_user(const ::file::path & pathUrl, bool bInteractive)
   {

      ::pointer<::account::user>puser;

      ::url::url url(pathUrl);

      {

         string strHost = url.connect().host();

         //auto estatus = 
         
         __øconstruct(puser);

         //if (!estatus)
         //{

         //   return;

         //}

         synchronous_lock synchronouslock(this->synchronization());

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

         file()->erase(directory_system()->appdata()/"license_auth/00001.data");

      }
      catch(...)
      {

      }

      try
      {

         file()->erase(directory_system()->appdata()/"license_auth/00002.data");

      }
      catch(...)
      {

      }

   }


   ::pointer<user>user_array::allocate_user()
   {

      return __øcreate < ::account::user > ();

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

      synchronous_lock synchronouslock(this->synchronization());

      auto map = m_map;

      synchronouslock.unlock();

      auto psession = session();

      for(auto & pair : map)
      {

         if(!pair.element2()->is_authenticated())
         {

            psession->on_erase_user(pair.element2());

            synchronouslock.lock();

            m_map.erase(pair.element1());

            synchronouslock.unlock();

         }

      }

   }



   user * user_array::get_user(const ::file::path & pathUrlParam, bool bFetch, bool bInteractive)
   {

      auto pathUrl = pathUrlParam;

      auto psession = session();

      if(pathUrl.is_empty())
      {

         pathUrl = psession->account()->get_default_url();

      }

      ::url::url url(pathUrl);

      string strHost = url.connect().host();

      {

         synchronous_lock synchronouslock(this->synchronization());

         auto & puser = m_map[strHost];

         if (bFetch && (puser.is_null() || !puser->is_authenticated()))
         {

            synchronouslock.unlock();

            _get_user(pathUrl, bInteractive);

         }

      }

      return m_map[strHost];

   }


   bool user_array::is_authenticated(const ::file::path & pathUrl, bool bInteractive)
   {

      ::pointer<::axis::application>papp = application();

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

         synchronous_lock synchronouslock(this->synchronization());

         auto map = m_map;

         synchronouslock.unlock();

         for(auto & pair : map)
         {

            pair.element2()->on_clock(etimer);

         }

      }

   }


} // namespace account



