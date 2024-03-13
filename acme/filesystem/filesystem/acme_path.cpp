// Create on 2021-03-21 00:11 <3ThomasBS_
#include "framework.h"
#include "acme_path.h"
#include "acme_directory.h"
#include "acme_file.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/file_system_options.h"
#include "acme/filesystem/filesystem/link.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

acme_path::acme_path()
{

}


acme_path::~acme_path()
{

}


::string acme_path::icloud_container_identifier(const char * psz_iCloudContainerIdentifier)
{
   
   ::string str_iCloudContainerIdentifier(psz_iCloudContainerIdentifier);
   
   if(str_iCloudContainerIdentifier.is_empty())
   {

      str_iCloudContainerIdentifier = application()->m_pfilesystemoptions->m_str_iCloudContainerIdentifier;

   }

   return str_iCloudContainerIdentifier;
   
}


//::string acme_path::icloud_container_id_from_app_id(const char * pszAppId)
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


::file::path acme_path::defer_get_icloud_container_path(const ::file::path & path, const char * pszAppId)
{
   
   if(acmedirectory()->is_icloud_container(path, pszAppId))
   {
      
      return path;
      
   }
   
   return acmedirectory()->icloud_container2(pszAppId) / path;
   
}


void acme_path::defer_get_icloud_container_path_name(::string & strName, ::string & str_iCloudContainerIdentifier, const ::file::path & path)
{
   
   str_iCloudContainerIdentifier = icloud_container_identifier(str_iCloudContainerIdentifier);
   
   if(!acmedirectory()->is_icloud_container(path, str_iCloudContainerIdentifier))
   {
      
      strName = path;
      
      return;
      
   }
   
   strName = path;
   
   strName.begins_eat(acmedirectory()->icloud_container2(str_iCloudContainerIdentifier));

   strName.trim_left("/");
   
}



string acme_path::from(string str)
{

   string strFsSafe;

   for (index i = 0; i < str.length(); i++)
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


//bool acme_path::final_is_same(const ::file::path & path1, const ::file::path & path2)
//{
//
//   throw ::interface_only();
//
//   return false;
//
//}
//


void acme_path::safe_real_path(::file::path & path)
{

   try
   {

      path = safe_get_real_path(path);

   }
   catch (...)
   {


   }

}


::file::path acme_path::safe_get_real_path(const ::file::path & path)
{

   ::file::path pathFull = _safe_real_path(path);

   if (pathFull.is_empty())
   {

      return path;

   }

   return pathFull;

}


::file::path acme_path::_safe_real_path(const ::file::path & path)
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


::file::path acme_path::real_path(const ::file::path & path)
{

   ::file::path pathFull = _real_path(path);

   if (pathFull.is_empty())
   {

      return path;

   }

   return pathFull;

}


::file::path acme_path::_real_path(const ::file::path & path)
{

   throw ::interface_only();

   return "";

}


bool acme_path::case_insensitive_real_path_begins_eat(string & str, const ::scoped_string & scopedstrPrefix)
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

   if (is_url(strPath))
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

      strFull = acmepath()->real_path(str);

      string strFullPath;

      strFullPath = acmepath()->real_path(strPath);

      if (strFull.case_insensitive_begins_eat(strFullPath))
      {

         str = strFull;

         return true;

      }

   }

   return false;

}


bool acme_path::real_path_is_same(const ::file::path & path1, const ::file::path & path2)
{

   ::file::path pathFull1 = real_path(path1);

   ::file::path pathFull2 = real_path(path2);

   return pathFull1.has_char() && pathFull1.case_insensitive_order(pathFull2) == 0;

}


::file::enum_type acme_path::get_type(const ::file::path & path)
{

   return ::get_file_system_item_type(path);

}


::file::enum_type acme_path::safe_get_type(const ::file::path & path)
{

   return ::safe_get_file_system_item_type(path);

}


void acme_path::create_symbolic_link(const ::scoped_string & scopedstrLink, const ::scoped_string & scopedstrSource)
{
   
   throw ::interface_only();
   
   //throw ::interface_only();
   
}


bool acme_path::is_symbolic_link(const ::scoped_string & scopedstrLink)
{
   
   throw ::interface_only();
   
   //throw ::interface_only();

   return false;
   
}


::file::path acme_path::symbolic_link_destination(const ::scoped_string & scopedstrLink)
{
   
   throw ::interface_only();
   
   return "";
   
}


bool acme_path::has_custom_icon(const ::file::path & path)
{
   
   throw ::interface_only();
      
   return false;
   
}



::file::path acme_path::defer_process_relative_path(const ::file::path & path, const ::file::path & pathFolderParam)
{

   auto pathFolder = pathFolderParam;

   if(pathFolder.is_empty())
   {

      pathFolder = m_pacmedirectory->m_pathFolder;

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


bool acme_path::defer_process_protocol_path(::file::path & path)
{
   
   return node()->defer_process_protocol_path(path);
   
}



::file::path acme_path::get_absolute_path(const ::scoped_string& scopedstr)
{

   throw interface_only();

   return {};

}


::pointer < ::file::link > acme_path::resolve_link(const ::file::path &path, ::file::e_link elink)
{
   
   if(path.case_insensitive_ends(".desktop"))
   {

      auto stra = acmefile()->lines(path);

      stra.filter_begins_ci("exec=");

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



void acme_path::rename(const ::file::path& pathNewName, const ::file::path& pathOldName)
{

   throw interface_only();

}


::file::path acme_path::get_sequence_path(const ::file::path& path, ::index iSequence, int iZeroPaddingWidth)
{

   if (iSequence <= 0)
   {

      return path;

   }

   ::string strFormat;

   ::string strFolderPathAndTitle = path.folder() / path.title();

   ::string strAllExtensions = path.all_extensions();

   ::string str;

   if (strAllExtensions.has_char())
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


void acme_path::defer_free_name_by_renaming_to_last_in_sequence(const ::file::path& path, int iZeroPaddingWidth)
{

   auto etype = get_type(path);

   if (!(etype & ::file::e_type_exists))
   {

      return;

   }

   for(::index iSequence = 2; iSequence < ::numeric_info < decltype(iSequence) >::maximum(); iSequence++)
   {

      auto pathNew = get_sequence_path(path, iSequence, iZeroPaddingWidth);

      auto etype = get_type(path);

      if (!(etype & ::file::e_type_exists))
      {

         rename(pathNew, path);

         return;

      }

   }

   throw ::exception(error_overflow);

}
