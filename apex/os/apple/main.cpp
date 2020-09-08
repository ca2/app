//
//  apple_main.cpp
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 02/10/17.
//

#include "framework.h"
#include "apex/os/_.h"
#include "apex/os/_os.h"
#include "_.h"


u32 __start_system_with_file(const char ** pszaFile, int iCount);


u32 __start_system_with_file(const char * pszFileName)
{

   if(pszFileName == nullptr)
   {

      return __start_system_with_file(nullptr, 0);

   }

   const char ** psza = (const char **) malloc(sizeof(const char *) * 1);

   psza[0] = strdup(pszFileName);

   return __start_system_with_file(psza, 1);

}

u32 __start_system_with_file(const char ** pszaFile, int iCount)
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

         ::create * pcreate = new ::create(::get_context_system());

         pcreate->m_pcommandline = new command_line(::get_context_system(), get_command_line_dup());

         ::get_context_system()->request({ pcreate });

      }

      return 0;

   }



}



string ca2_command_line();



string apple_get_bundle_identifier();

string get_bundle_app_id()
{
   
   string str = apple_get_bundle_identifier();

   if(!::str::begins_eat_ci(str, "cc.ca2."))
   {

      ::str::begins_eat_ci(str, "com.ca2.");

   }

   string_array stra;

   stra.explode(".", str);

   if(stra.get_size() >= 2)
   {

      stra[1].replace('-', '_');

   }

   string strAppId;
   
   strAppId = stra.implode("/");

   return strAppId;
   
}


string get_bundle_app_library_name()
{
   
   string strLibraryName = get_bundle_app_id();
   
   strLibraryName.replace("/", "_");
   
   strLibraryName.replace("-", "_");
   
   return strLibraryName;
   
}


string ca2_command_line2()
{

   string strAppId = get_bundle_app_id();

#ifdef APPLE_IOS

   return "app : app=" + strAppId + " client_only";

#else

   return "app : app=" + strAppId;

#endif

}

