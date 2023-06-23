//
//  apex_application_ptra.cpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 12/11/18.
//
#include "framework.h"
#include "application_array.h"
#include "application.h"


namespace acme
{


   application_array::application_array()
   {

   }


   application_array::application_array(const application_array & array) :
      pointer_array < ::acme::application >(array)
   {

   }


   application_array & application_array::operator = (const application_array & array)
   {

      pointer_array < ::acme::application >::operator = (array);

      return *this;

   }


   application_array::application_array(application_array && array) :
      pointer_array < ::acme::application >(array)
   {

   }


   application_array & application_array::operator = (application_array && array)
   {

      pointer_array < ::acme::application >::operator = (array);

      return *this;

   }


   application_array::~application_array()
   {

      //if(::is_set(get_app()))
      //{

      //   if(get_app()->mutex() == mutex())
      //   {

      //      mutex() = nullptr;

      //   }

      //}

   }


   ::acme::application * application_array::find_by_app_id(const string & strAppId)
   {

      //synchronous_lock synchronouslock(this->synchronization());

   restart:

      for (auto & papplication : *this)
      {

         try
         {

            if (papplication.is_null())
            {

               erase(papplication);

               goto restart;

            }

            if (papplication->m_strAppId == strAppId)
            {

               return papplication;

            }

         }
         catch (...)
         {

         }

      }

      return nullptr;

   }


   ::acme::application * application_array::find_running_defer_try_quit_damaged(const string & strAppId)
   {

      auto papplication = find_by_app_id(strAppId);

      if (::is_null(papplication))
      {

         return nullptr;

      }

      //if (papp->safe_is_running())
      //{

      //   return papp;

      //}

      //try
      //{
      //
      //   papp->finish();
      //
      //}
      //catch (...)
      //{
      //
      //}

      try
      {

         ::release(papplication);

      }
      catch (...)
      {

      }

      return nullptr;

   }


   bool application_array::lookup(const string & strAppId, ::pointer<::acme::application>& papp)
   {

      papp = find_running_defer_try_quit_damaged(strAppId);

      return papp.is_set();

   }


} // namespace apex



