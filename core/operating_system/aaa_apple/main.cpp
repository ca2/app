//
//  apple_main.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 02/10/17.
//

#include "framework.h"
#include "aura/os/_.h"
#include "aura/os/_os.h"
#include "_.h"


u32 __start_system_with_file(const ::string &* pszaFile, int iCount);


u32 __start_system_with_file(const ::string & pszFileName)
{

   if(pszFileName == nullptr)
   {

      return __start_system_with_file(nullptr, 0);

   }

   const char ** psza = (const ::string &*) malloc(sizeof(const ::string &) * 1);

   psza[0] = strdup(pszFileName);

   return __start_system_with_file(psza, 1);

}

u32 __start_system_with_file(const ::string &* pszaFile, int iCount)
{

   string strExtra;

   //if(::get_context_system() != nullptr)
   {

      if(pszaFile != nullptr)
      {

         apple_accumulate_on_open_file(pszaFile, iCount, strExtra);

      }
      else
      {

         ::create * pcreate = memory_new ::create(::get_context_system());

         pcreate->m_pcommandline = memory_new command_line(::get_context_system(), get_command_line());

         psystem->request({ pcreate });

      }

      return 0;

   }



}



string ca2_command_line();



string apple_get_bundle_identifier();



string ca2_command_line2()
{

   string str = apple_get_bundle_identifier();

   if(!::str().begins_eat_ci(str, "com."))
   {

      ::str().begins_eat_ci(str, "com.ca2.");

   }

   string_array stra;

   stra.explode(".", str);

   if(stra.get_size() >= 2)
   {

      stra[1].replace('-', '_');

   }

   str = stra.implode("/");

#ifdef APPLE_IOS

   return "app : app=" + str + " client_only";

#else

   return "app : app=" + str;

#endif

}

