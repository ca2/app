// Create on 2021-03-21 00:11 <3ThomasBS_
#include "framework.h"
#include "path_system.h"
#include "directory_system.h"
#include "file_system.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/file_system_options.h"
#include "acme/filesystem/filesystem/link.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/http.h"
#include "acme/prototype/collection/map_interface.h"

CLASS_DECL_ACME::string get_operating_system_name();

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

path_system::path_system()
{

}


path_system::~path_system()
{

}


::string path_system::discrete_shell_path(const ::file::path& path)
{

   return path;

}


::string path_system::shell_path(const ::file::path & path)
{

   ::string str = path;

   if (str.contains(' '))
   {

      str = "\"" + str + "\"";

   }

   return str;

}


::string path_system::tool_folder_operating_system_name()
{

#ifdef TOOL_FOLDER_OPERATING_SYSTEM_NAME

   return TOOL_FOLDER_OPERATING_SYSTEM_NAME;

#else

   return ::get_operating_system_name();

#endif

}


::file::path path_system::tool_folder_path()
{

   //::string strToolFolderName = "tool-" + tool_folder_operating_system_name();
   ::string strToolFolderName = "tool";

   ::file::path pathToolFolder;

// #ifdef WINDOWS_DESKTOP

//    pathToolFolder = "C:" / strToolFolderName;

// #elif defined(MACOS)

//    pathToolFolder = directory_system()->home() / "workspace/operating_system" / strToolFolderName;

// #else

//    pathToolFolder = directory_system()->home() / "cmake/operating_system" / strToolFolderName;

// #endif

   pathToolFolder = directory_system()->home() / "code/operating_system" / strToolFolderName;

   return pathToolFolder;

}




::string path_system::icloud_container_identifier(const char * psz_iCloudContainerIdentifier)
{
   
   ::string str_iCloudContainerIdentifier(psz_iCloudContainerIdentifier);
   
   if(str_iCloudContainerIdentifier.is_empty())
   {

      str_iCloudContainerIdentifier = application()->m_pfilesystemoptions->m_str_iCloudContainerIdentifier;

   }

   return str_iCloudContainerIdentifier;
   
}


//::string path_system::icloud_container_id_from_app_id(const char * pszAppId)
//{
//   
//   ::string strAppId(pszAppId);
//   
//   if(strAppId.is_empty())
//   {
//      
//      
//      strAppId = application()->m_strAppId;
//      
//      
//   }
//   
//   strAppId.find_replace("/", ".");
//   strAppId.find_replace("_", "-");
//   
//   //return "iCloud." + strAppId;
//   
//   return strAppId;
//   
//}


::file::path path_system::defer_get_icloud_container_path(const ::file::path & path, const char * pszAppId)
{
   
   if(directory_system()->is_icloud_container(path, pszAppId))
   {
      
      return path;
      
   }
   
   return directory_system()->icloud_container2(pszAppId) / path;
   
}


void path_system::defer_get_icloud_container_path_name(::string & strName, ::string & str_iCloudContainerIdentifier, const ::file::path & path)
{
   
   str_iCloudContainerIdentifier = icloud_container_identifier(str_iCloudContainerIdentifier);
   
   if(!directory_system()->is_icloud_container(path, str_iCloudContainerIdentifier))
   {
      
      strName = path;
      
      return;
      
   }
   
   strName = path;
   
   strName.begins_eat(directory_system()->icloud_container2(str_iCloudContainerIdentifier));

   strName.trim_left("/");
   
}



string path_system::from(string str)
{

   string strFsSafe;

   for (::collection::index i = 0; i < str.length(); i++)
   {

      if (character_isalnum(str[i]))
      {

         strFsSafe += str[i];

      }
      else
      {

         strFsSafe += "-" + ::hex::lower_case_from(str[i]);

      }

   }

   return strFsSafe;

}


//bool path_system::final_is_same(const ::file::path & path1, const ::file::path & path2)
//{
//
//   throw ::interface_only();
//
//   return false;
//
//}
//


void path_system::safe_real_path(::file::path & path)
{

   try
   {

      path = safe_get_real_path(path);

   }
   catch (...)
   {


   }

}


::file::path path_system::get_uniform_resource_locator(const ::file::path& path)
{

   auto str = http()->get(path.as_url());

   return str;

}


::file::path path_system::safe_get_real_path(const ::file::path & path)
{

   ::file::path pathFull = _safe_real_path(path);

   if (pathFull.is_empty())
   {

      return path;

   }

   return pathFull;

}


::file::path path_system::_safe_real_path(const ::file::path & path)
{

   try
   {

      return _real_path(path);

   }
   catch (...)
   {

   }

   return path;

}


::file::path path_system::real_path(const ::file::path & path)
{

   ::file::path pathFull = _real_path(path);

   if (pathFull.is_empty())
   {

      return path;

   }

   return pathFull;

}


::file::path path_system::_real_path(const ::file::path & path)
{

   throw ::interface_only();

   return "";

}


bool path_system::case_insensitive_real_path_begins_eat(string & str, const ::scoped_string & scopedstrPrefix)
{

   ::file::path path(scopedstrPrefix);

   if (path.is_empty())
   {

      return true;

   }

   if (str.is_empty())
   {

      return false;

   }

   string strPath;

   strPath = path;

   if (::url::is(strPath))
   {

      strPath += "/";

   }
   else
   {

      strPath += file_path_separator(e_path_file);

   }

   if (str == path || str == strPath)
   {

      str.empty();

      return true;

   }
   else if (str.case_insensitive_begins_eat(strPath))
   {

      return true;

   }
   else
   {

      string strFull;

      strFull = this->real_path(str);

      string strFullPath;

      strFullPath = this->real_path(strPath);

      if (strFull.case_insensitive_begins_eat(strFullPath))
      {

         str = strFull;

         return true;

      }

   }

   return false;

}


bool path_system::real_path_is_same(const ::file::path & path1, const ::file::path & path2)
{

   ::file::path pathFull1 = real_path(path1);

   ::file::path pathFull2 = real_path(path2);

   return pathFull1.has_character() && pathFull1.case_insensitive_order(pathFull2) == 0;

}


::file::enum_type path_system::get_type(const ::file::path & path)
{

   return ::get_file_system_item_type(path);

}


::file::enum_type path_system::safe_get_type(const ::file::path & path)
{

   return ::safe_get_file_system_item_type(path);

}


void path_system::create_symbolic_link(const ::scoped_string & scopedstrLink, const ::scoped_string & scopedstrSource)
{
   
   throw ::interface_only();
   
   //throw ::interface_only();
   
}


bool path_system::is_symbolic_link(const ::scoped_string & scopedstrLink)
{
   
   throw ::interface_only();
   
   //throw ::interface_only();

   return false;
   
}


::file::path path_system::symbolic_link_destination(const ::scoped_string & scopedstrLink)
{
   
   throw ::interface_only();
   
   return "";
   
}


bool path_system::has_custom_icon(const ::file::path & path)
{
   
   throw ::interface_only();
      
   return false;
   
}



::file::path path_system::defer_process_relative_path(const ::file::path & path, const ::file::path & pathFolderParam)
{

   auto pathFolder = pathFolderParam;

   if(pathFolder.is_empty())
   {

      pathFolder = m_pdirectorysystem->m_pathFolder;

   }

   if(path.is_empty())
   {

      return pathFolder;

   }

   if (file_path_is_absolute(path))
   {

      return path;

   }

   auto pathFolderCurrent = pathFolder;

   ::file::path pathAbsolute = pathFolderCurrent / path;

   return pathAbsolute;

}


bool path_system::defer_process_protocol_path(::file::path & path)
{
   
   return node()->defer_process_protocol_path(path);
   
}



::file::path path_system::get_absolute_path(const ::scoped_string& scopedstr)
{

   throw interface_only();

   return {};

}


bool path_system::is_absolute_path(const ::scoped_string & scopedstr)
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


::pointer < ::file::link > path_system::resolve_link(const ::file::path &path, ::file::e_link elink)
{
   
   if(path.case_insensitive_ends(".desktop"))
   {

      auto stra = file_system()->lines(path);

      stra.case_insensitive_filter_begins("exec=");

      if(stra.get_size() <= 0)
      {

         return nullptr;

      }

      auto plink = __create_new < ::file::link >();

      string strLink = stra[0];

      strLink.case_insensitive_begins_eat("exec=");

      while(true)
      {

         bool bAte = false;

         if(strLink.case_insensitive_ends_eat("%u"))
         {

            bAte = true;

         }

         if(!bAte)
         {

            break;

         }

      }

      strLink.trim();

      strLink.trim("\"");

      strLink.trim("\'");

      plink->m_pathFolder = ::file::path(strLink).folder();

      plink->m_pathTarget = strLink;

      return plink;

   }
   else
   {


#ifndef WINDOWS


#if 0



   if (::is_null(psz))
   {

      return false;

   }




   char* pszRealPath = ::realpath(psz, NULL);

   if (pszRealPath == NULL)
   {

      return false;

   }

   if (strcmp(psz, pszRealPath) == 0)
   {

      ::free(pszRealPath);

      return false;

   }

   try
   {

      path = pszRealPath;

   }
   catch (...)
   {

   }

   ::free(pszRealPath);

   return true;

}

#else

      auto plink = __create_new < ::file::link >();
      
      string strLink;

      char * psz = strLink.get_buffer(4096);

      int count = (int) readlink(path, psz, 4096);

      if (count < 0)
      {

         strLink.release_buffer(0);

         if (elink & ::file::e_link_target)
         {

            plink->m_pathTarget = path;

         }

         if(elink & ::file::e_link_folder)
         {

            plink->m_pathFolder = ::file::path(strLink).folder();

         }

         return plink;

      }

      strLink.release_buffer(count);

      if (elink & ::file::e_link_target)
      {
         
         ::file::path pathTarget = strLink;
         
         if(file_path_is_relative(pathTarget))
         {
          
            pathTarget = defer_solve_relative(pathTarget, path);
            
         }

         plink->m_pathTarget = pathTarget;

      }

      if (elink & ::file::e_link_folder)
      {

         plink->m_pathFolder = ::file::path(strLink).folder();

      }

      return plink;

#endif

#endif

   }

   return nullptr;

}



void path_system::rename(const ::file::path& pathNewName, const ::file::path& pathOldName)
{

   throw interface_only();

}


::file::path path_system::get_sequence_path(const ::file::path& path, ::collection::index iSequence, int iZeroPaddingWidth)
{

   if (iSequence <= 0)
   {

      return path;

   }

   ::string strFormat;

   ::string strFolderPathAndTitle = path.folder() / path.title();

   ::string strAllExtensions = path.all_extensions();

   ::string str;

   if (strAllExtensions.has_character())
   {

      if (iZeroPaddingWidth <= 1)
      {

         strFormat = "%s - %d.%s";

      }
      else
      {

         strFormat.formatf("%%s - %%0%dd.%%s", iZeroPaddingWidth);

      }

      str.formatf(strFormat, strFolderPathAndTitle.c_str(), iSequence, strAllExtensions.c_str());

   }
   else
   {

      if (iZeroPaddingWidth <= 1)
      {

         strFormat = "%s - %d";

      }
      else
      {

         strFormat.formatf("%%s - %%0%dd", iZeroPaddingWidth);

      }

      str.formatf(strFormat, strFolderPathAndTitle.c_str(), iSequence);

   }

   return str;

}


void path_system::defer_free_name_by_renaming_to_last_in_sequence(const ::file::path& path, int iZeroPaddingWidth)
{

   auto etype = get_type(path);

   if (!(etype & ::file::e_type_exists))
   {

      return;

   }

   for(::collection::index iSequence = 2; iSequence < ::numeric_info < decltype(iSequence) >::maximum(); iSequence++)
   {

      auto pathNew = get_sequence_path(path, iSequence, iZeroPaddingWidth);

      auto etypeNew = get_type(pathNew);

      if (!(etypeNew & ::file::e_type_exists))
      {

         rename(pathNew, path);

         return;

      }

   }

   throw ::exception(error_overflow);

}


::file::e_type path_system::executable_type(const ::file::path & path)
{

   return ::file::e_type_unknown;

}


void path_system::determine_executable(::file::path & path)
{

   path.m_etype = path.m_etype & (::file::e_type_executable | ::file::e_type_non_executable);

   path.m_etype |= executable_type(path);

}

// If the given path looks like it's relative to the working directory, then prepend that working
// directory. This operates on unescaped paths only (so a ~ means a literal ~).
::file::path path_system::defer_apply_working_directory(const ::file::path &path, const ::file::path &working_directory)
{

   if (path.is_empty() || working_directory.is_empty())
   {

      return path;

   }

   // We're going to make sure that if we want to prepend the wd, that the string has no leading
   // "/".
   //bool prepend_wd =
   if (is_absolute_path(path)) {
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


::file::path path_system::_path_get_path(const scoped_string & scopedstrCommand, const ::scoped_string & scopedstrPath, string_to_string_lookup * plookupEnvironment)
{

//   ::file::path pathResult;

//   // Commands cannot contain NUL byte.
//   if (scopedstrCommand.find(L'\0') != wcstring::npos)
//   {
//      pathResult.m_etype = ::file::e_type_doesnt_exist
//      return ;
//   }

   // If the command has a slash, it must be an absolute or relative path and thus we don't bother
   // looking for a matching command.
   if (scopedstrCommand.contains('/'))
   {

      auto PWD = plookupEnvironment->lookup("slashed_pwd");

      auto path = defer_apply_working_directory(scopedstrCommand, PWD);

      determine_executable(path);

      return path;

   }

   auto pathRange = scopedstrPath();

   ::file::path pathResult("", {}, ::file::e_type_doesnt_exist);

   ::file::path pathBest("", {}, ::file::e_type_doesnt_exist);

   ::file::path pathProposed;

   ::scoped_string next_path;

   while(get_next_path(next_path, pathRange))
   {

      if(next_path.is_empty())
      {

         continue;

      }

      pathProposed = next_path;

      pathProposed /= scopedstrCommand;

      determine_executable(pathProposed);

      if (pathProposed.m_etype & ::file::e_type_non_executable)
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
         if (directory_system()->is_accessible(pathProposed.folder()))
         {

            pathBest = pathProposed;

         }

      }

   }

   return pathBest;

}


::string path_system::get_default_path()
{

   return {};

}


bool path_system::get_next_path(::scoped_string & scopedstr, ::string::BASE_RANGE & rangePath)
{

   if(rangePath.is_empty())
   {

      return false;

   }

   auto p = rangePath.find(':');

   if(::is_null(p))
   {

      scopedstr.begin() = p;
      scopedstr.end() = rangePath.end();

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


::file::path path_system::path_get_path(const scoped_string & scopedstrCommand, string_to_string_lookup * plookupEnvironment)
{

   auto path = path_try_get_path(scopedstrCommand, plookupEnvironment);

   if (path.m_etype == ::file::e_type_unknown)
   {

      return {};

   }

   return ::transfer(path);

}


::file::path path_system::path_try_get_path(const scoped_string & scopedstrCommand, string_to_string_lookup * plookupEnvironment)
{

   ::scoped_string scopedstrPath;

   auto PATH = plookupEnvironment->lookup("PATH");

   if(PATH.nok())
   {

      return _path_get_path(scopedstrCommand, get_default_path(), plookupEnvironment);

   }

   return _path_get_path(scopedstrCommand, PATH, plookupEnvironment);

}


::file::path path_system::windows_posix_path(const ::file::path & path)
{

   if (path.size() > 3)
   {

      if (::character_isalpha(path[0])
         && path[1] == ':'
         && (path[2] == '/' || path[2] == '\\'))
      {

         ::string str;

         str = "/";

         str += ::character_tolower(path[0]);

         str += "/";

         str += path.substr(3);

         return str;

      }

   }

   return path;

}


void path_system::symbolic_link(const ::file::path & pathTarget, const ::file::path & pathSource)
{

   throw ::interface_only();

}
