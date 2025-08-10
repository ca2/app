#include "framework.h"
#include "file.h"
#include "path.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/file/status.h"
#include "acme/_operating_system.h"
#include "acme/operating_system/console.h"
#include "acme/prototype/collection/map_interface.h"
//#if defined( FREEBSD)
//#define __XSI_VISIBLE 1
//#endif
#if defined(LINUX)
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

::file::path path_try_get_path(const scoped_string & scopedstrCommand, string_to_string_lookup * plookupEnvironment);




// If the given path looks like it's relative to the working directory, then prepend that working
// directory. This operates on unescaped paths only (so a ~ means a literal ~).
::file::path path_defer_apply_working_directory(const ::file::path &path, const ::file::path &working_directory)
{

   if (path.is_empty() || working_directory.is_empty())
   {

      return path;

   }

   // We're going to make sure that if we want to prepend the wd, that the string has no leading
   // "/".
   //bool prepend_wd =
   if (path_is_absolute_path(path)) {
      // No need to prepend the wd, so just return the path we were given.
      return path;
   }

   // Remove up to one "./".
   auto path_component = path;

   path_component.case_insensitive_begins_eat("./");
   //{
      //path_component.erase(0, 2);
   //}

//   // Removing leading /s.
//   while (string_prefixes_string(L"/", path_component)) {
//      path_component.erase(0, 1);
//   }

//   // Construct and return a ___new path.
//   wcstring new_path = working_directory;
//   append_path_component(new_path, path_component);
   auto pathResult = working_directory / path_component;

   return pathResult;

}


::file::path _path_get_path(const scoped_string & scopedstrCommand, const ::scoped_string & scopedstrPath, string_to_string_lookup * plookupEnvironment)
{

//   ::file::path pathResult;

//   // Commands cannot contain NUL byte.
//   if (scopedstrCommand.find(L'\0') != wcstring::npos)
//   {
//      pathResult.m_etype = ::file::e_type_doesnt_exist
//      return ;
//   }
      
//   printf("command: %s\n", scopedstrCommand.as_string().c_str());
   
//   fflush(stdout);
   
   // If the command has a slash, it must be an absolute or relative path and thus we don't bother
   // looking for a matching command.
   if (scopedstrCommand.contains('/'))
   {
   
      //printf("It is a path\n");

      auto PWD = plookupEnvironment->lookup("slashed_pwd");

//      printf("PWD: %s\n", PWD.c_str());
   
//      fflush(stdout);

      auto path = path_defer_apply_working_directory(scopedstrCommand, PWD);

      operating_system_determine_executable(path);

      return path;

   }

//   printf("Maybe command\n");
   
   auto pathRange = scopedstrPath();

   ::file::path pathResult("", {}, ::file::e_type_doesnt_exist);

   ::file::path pathBest("", {}, ::file::e_type_doesnt_exist);

   ::file::path pathProposed;

   ::scoped_string next_path;

   while(path_get_next_path(next_path, pathRange))
   {

      if(next_path.is_empty())
      {

         continue;

      }
      
      ::string strNextPath(next_path);
      
//      printf("trYIng tHIs pATh nOw: %s\n", strNextPath.c_str());

      pathProposed = next_path;

      pathProposed /= scopedstrCommand;

//      printf("proPOsed pATh nOw: %s\n", pathProposed.c_str());

      operating_system_determine_executable(pathProposed);

      if (pathProposed.m_etype & ::file::e_type_executable)
      {

         // We found one.
         pathBest = pathProposed;

         break;

      }
      else if (pathProposed.m_etype & ::file::e_type_doesnt_exist)
      {

         // Keep the first *interesting* error and path around.
         // ENOENT isn't interesting because not having a file is the normal case.
         // Ignore if the parent directory is already inaccessible.
         if (is_directory_accessible(pathProposed.folder()))
         {

            pathBest = pathProposed;

         }

      }

   }

   return pathBest;

}


::string path_get_default_path()
{

   return "/bin:/usr/bin:/usr/local/bin";

}


bool path_get_next_path(::scoped_string & scopedstr, ::string_range < const_char_pointer >& rangePath)
{

   if(rangePath.is_empty())
   {

      return false;

   }

   auto p = rangePath.find(':');

   if(::is_null(p))
   {
   
//      printf("path_get_next_path p is null\n");
      
//      fflush(stdout);

//      printf("rangePath : %s\n", ::string(rangePath).c_str());
  
//  	PROBLEM: Line below is not working 
//      scopedstr = rangePath;

      scopedstr.begin() = rangePath.begin();
      scopedstr.end() = rangePath.end();

//      printf("scopedstr : %s\n", ::string(scopedstr).c_str());

      rangePath.begin() = rangePath.end();

   }
   else
   {

      scopedstr.begin() = rangePath.begin();
      scopedstr.end() = p;

      rangePath.begin() = p + 1;

   }

   scopedstr.m_erange = e_range_none;

   return true;

}


::file::path path_get_path(const scoped_string & scopedstrCommand, string_to_string_lookup * plookupEnvironment)
{

   auto path = path_try_get_path(scopedstrCommand, plookupEnvironment);

   if (path.m_etype == ::file::e_type_unknown)
   {

      return {};

   }

   return ::transfer(path);

}


::file::path path_try_get_path(const scoped_string & scopedstrCommand, string_to_string_lookup * plookupEnvironment)
{

   ::scoped_string scopedstrPath;

   auto PATH = plookupEnvironment->lookup("PATH");

   if(PATH.nok())
   {
   
//      printf("PATH.nok()\n");
      
//      fflush(stdout);
   
      return _path_get_path(scopedstrCommand, path_get_default_path(), plookupEnvironment);

   }

//   printf("PATH ok\n");
      
//   fflush(stdout);
   
//   printf("PATH: %s\n", PATH.c_str());
      
   return _path_get_path(scopedstrCommand, PATH, plookupEnvironment);

}




bool path_is_absolute_path(const ::scoped_string & scopedstr)
{

   ::string str(scopedstr);

   str.trim();

   if(str.is_empty())
   {

      return false;

   }

   if(str[0] == '/')
   {

      return true;

   }
   else if(str[0] == '\\')
   {

      return true;

   }
   else if(str.length() >= 3)
   {

      if(::character_isalpha(str[0]) && str[1] == ':' && (str[2] == '/' || str[2] == '\\'))
      {

         return true;

      }

   }

   return false;

}




