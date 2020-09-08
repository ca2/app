//
//  ace_application_ptra.cpp
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 12/11/18.
//

#include "framework.h"



application_array::application_array()
{

}


application_array::application_array(const application_array & array):
   __pointer_array(::acme::application)(array)
{

}


application_array & application_array::operator = (const application_array & array)
{

   __pointer_array(::acme::application)::operator = (array);

   return *this;

}


application_array::application_array(application_array && array):
   __pointer_array(::acme::application)(array)
{

}


application_array & application_array::operator = (application_array && array)
{

   __pointer_array(::acme::application)::operator = (array);

   return *this;

}


application_array::~application_array()
{

   //if(::is_set(get_context_application()))
   //{

   //   if(get_context_application()->mutex() == mutex())
   //   {

   //      mutex() = nullptr;

   //   }

   //}

}


::acme::application * application_array::find_by_app_name(string strAppName)
{

   //sync_lock sl(mutex());

restart:

   for (auto & papp : *this)
   {

      try
      {

         if (papp.is_null())
         {

            remove(papp);

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


::acme::application * application_array::find_running_defer_try_quit_damaged(string strAppName)
{

   __pointer(::acme::application) papp = find_by_app_name(strAppName);

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


bool application_array::lookup(string strAppName, __pointer(::acme::application) & papp)
{

   papp = find_running_defer_try_quit_damaged(strAppName);

   return papp.is_set();

}






