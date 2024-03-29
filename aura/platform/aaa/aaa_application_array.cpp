//
//  aura_application_ptra.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 12/11/18.
//

#include "framework.h"



application_array::application_array()
{

}


application_array::application_array(const application_array & array):
   pointer_array < ::aura::application >(array)
{

}


application_array & application_array::operator = (const application_array & array)
{

   pointer_array < ::aura::application >::operator = (array);

   return *this;

}


application_array::application_array(application_array && array):
   pointer_array < ::aura::application >(array)
{

}


application_array & application_array::operator = (application_array && array)
{

   pointer_array < ::aura::application >::operator = (array);

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


::aura::application * application_array::find_by_app_name(string strAppName)
{

   //synchronous_lock synchronouslock(this->synchronization());

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


::aura::application * application_array::find_running_defer_try_quit_damaged(string strAppName)
{

   ::pointer<::aura::application>papp = find_by_app_name(strAppName);

   if (papp.is_null())
   {

      return nullptr;

   }

   if (papp->safe_is_running())
   {

      return papp;

   }

   //try
   //{
   //
   //   papp->set_finish();
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


bool application_array::lookup(string strAppName, ::pointer<::aura::application>& papp)
{

   papp = find_running_defer_try_quit_damaged(strAppName);

   return papp.is_set();

}






