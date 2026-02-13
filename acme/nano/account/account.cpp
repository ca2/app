// Created by camilo on 2024-06-02 16:56 <3ThomasBorregaardSorensen!!
// From idn by camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
// Merged from acme/operating_system/linux/library.cpp by
// camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
// From dynamic_library by camilo on 2024-06-02 18:36 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "account.h"
#include "id.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"


namespace nano
{


   namespace account
   {


      account::account()
      {

      }


      account::~account()
      {


      }


      void account::on_initialize_particle()
      {

         ::platform::department::on_initialize_particle();

         defer_create_synchronization();

      }


      ::pointer<::nano::account::user> account::get_user(const ::pointer < ::nano::account::id > & pid)
      {

         _synchronous_lock lock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         auto &puser = m_usermap[pid->as_string()];

         if (!puser)
         {

            puser = _get_user(pid);

         }

         return puser;

      }


      ::pointer<::nano::account::user> account::_get_user(const ::pointer < ::nano::account::id > & pid)
      {

         throw ::interface_only();

         return nullptr;

      }


      ::pointer<::nano::account::id> account::username_id(const ::scoped_string & scopedstrUsername)
      {

         throw ::interface_only();

         return nullptr;

      }


      ::pointer<::nano::account::id> account::current_user_id()
      {

         throw ::interface_only();

         return nullptr;

      }


   } // namespace dynamic_library


} // namespace nano



