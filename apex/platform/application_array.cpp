//
//  apex_application_ptra.cpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/11/18.
//
#include "framework.h"
#include "application_array.h"
#include "apex/platform/application.h"


namespace apex
{


   application_array::application_array()
   {

   }


   application_array::application_array(const application_array & array) :
      pointer_array < ::apex::application >(array)
   {

   }


   application_array & application_array::operator = (const application_array & array)
   {

      pointer_array < ::apex::application >::operator = (array);

      return *this;

   }


   application_array::application_array(application_array && array) :
      pointer_array < ::apex::application >(array)
   {

   }


   application_array & application_array::operator = (application_array && array)
   {

      pointer_array < ::apex::application >::operator = (array);

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


   ::apex::application * application_array::find_by_app_name(string strAppName)
   {

      //synchronous_lock synchronouslock(mutex());

   restart:

      for (auto & papp : *this)
      {

         try
         {

            if (papp.is_null())
            {

               erase(papp);

               goto restart;

            }

            if (papp->m_strAppName == strAppName)
            {

               return papp;

            }

         }
         catch (...)
         {

         }

      }

      return nullptr;

   }


   ::apex::application * application_array::find_running_defer_try_quit_damaged(string strAppName)
   {

      ::pointer<::apex::application>papp = find_by_app_name(strAppName);

      if (papp.is_null())
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

         papp.release();

      }
      catch (...)
      {

      }

      return nullptr;

   }


   bool application_array::lookup(string strAppName, ::pointer<::apex::application>& papp)
   {

      papp = find_running_defer_try_quit_damaged(strAppName);

      return papp.is_set();

   }


} // namespace apex



