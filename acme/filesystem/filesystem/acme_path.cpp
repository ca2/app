// Create on 2021-03-21 00:11 <3ThomasBS_
#include "framework.h"
#include "acme_path.h"
#include "acme_directory.h"
#include "acme/primitive/string/hex.h"
#include "acme/exception/interface_only.h"
#include "acme/platform/system.h"


acme_path::acme_path()
{

}


acme_path::~acme_path()
{

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


::file::path acme_path::final(const ::file::path & path)
{

   ::file::path pathFull = _final(path);

   if (pathFull.is_empty())
   {

      return path;

   }

   return pathFull;

}


::file::path acme_path::_final(const ::file::path & path)
{

   throw ::interface_only();

   return "";

}


bool acme_path::final_begins_eat_ci(string & str, const ::scoped_string & scopedstrPrefix)
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

      strFull = acmepath()->final(str);

      string strFullPath;

      strFullPath = acmepath()->final(strPath);

      if (strFull.case_insensitive_begins_eat(strFullPath))
      {

         str = strFull;

         return true;

      }

   }

   return false;

}


bool acme_path::final_is_same(const ::file::path & path1, const ::file::path & path2)
{

   ::file::path pathFull1 = final(path1);

   ::file::path pathFull2 = final(path2);

   return pathFull1.has_char() && pathFull1.case_insensitive_order(pathFull2) == 0;

}


::file::enum_type acme_path::get_type(const ::file::path & path)
{

   throw ::interface_only();

   return ::file::e_type_unknown;

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


::file::path acme_path::get_absolute_path(const ::scoped_string& scopedstr)
{

   throw interface_only();

   return {};

}



