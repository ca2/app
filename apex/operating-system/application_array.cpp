//
//  apex_application_ptra.cpp
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 12/11/18.
//

#include "framework.h"



application_array::application_array()
{

}


application_array::application_array(const application_array & array):
   __pointer_array(::application)(array)
{

}


application_array & application_array::operator = (const application_array & array)
{

   __pointer_array(::application)::operator = (array);

   return *this;

}


application_array::application_array(application_array && array):
   __pointer_array(::application)(array)
{

}


application_array & application_array::operator = (application_array && array)
{

   __pointer_array(::application)::operator = (array);

   return *this;

}


application_array::~application_array()
{

   //if(::is_set(get_application()))
   //{

   //   if(get_application()->mutex() == mutex())
   //   {

   //      mutex() = nullptr;

   //   }

   //}

}


::application * application_array::find_by_app_name(string strAppName)
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


::application * application_array::find_running_defer_try_quit_damaged(string strAppName)
{

   __pointer(::application) papp = find_by_app_name(strAppName);

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


bool application_array::lookup(string strAppName, __pointer(::application) & papp)
{

   papp = find_running_defer_try_quit_damaged(strAppName);

   return papp.is_set();

}






