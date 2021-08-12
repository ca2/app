// Create on 2021-03-21 00:11 <3ThomasBS_
#include "framework.h"
#include "acme_path.h"
#include "acme_dir.h"


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

      if (ansi_char_is_alphanumeric(str[i]))
      {

         strFsSafe += str[i];

      }
      else
      {

         strFsSafe += "-" + ::hex::lower_from(str[i]);

      }

   }

   return strFsSafe;

}




//bool acme_path::final_is_same(const char * pszPath1, const char * pszPath2)
//{
//
//   __throw(error_interface_only);
//
//   return false;
//
//}
//

::file::path acme_path::final(const char * path)
{

   ::file::path pathFull = _final(path);

   if (pathFull.is_empty())
   {

      return path;

   }

   return pathFull;

}


::file::path acme_path::_final(const char * path)
{

   __throw(error_interface_only);

   return "";

}


bool acme_path::final_begins_eat_ci(string & str, const char * pcszPrefix)
{

   ::file::path path(pcszPrefix);

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

      str.Empty();

      return true;

   }
   else if (::str::begins_eat_ci(str, strPath))
   {

      return true;

   }
   else
   {

      string strFull;

      strFull = m_psystem->m_pacmepath->final(str);

      string strFullPath;

      strFullPath = m_psystem->m_pacmepath->final(strPath);

      if (::str::begins_eat_ci(strFull, strFullPath))
      {

         str = strFull;

         return true;

      }

   }

   return false;

}


bool acme_path::final_is_same(const char * path1, const char * path2)
{

   ::file::path pathFull1 = final(path1);

   ::file::path pathFull2 = final(path2);

   return pathFull1.has_char() && pathFull1.compare_ci(pathFull2) == 0;

}


bool acme_path::is_file_or_dir(const char * path, ::file::enum_type * petype)
{

   __throw(error_interface_only);

   return false;

}


