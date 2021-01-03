#include "framework.h"
#include "aqua/xml.h"
#include "acme/const/id.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "_linux.h"
#undef USE_MISC

#ifdef RASPBIAN
#include <sys/types.h>
#include <unistd.h>
#endif


inline bool linux_dir_myspace(char ch)
{

   return ch == ' ' ||
          ch == '\t' ||
          ch == '\r' ||
          ch == '\n';

}


::file::path xdg_get_dir(string str)
{

   ::file::path pathHome;

   pathHome = getenv("HOME");

   ::file::path path;

   path = pathHome / ".config/user-dirs.dirs";

   string strDirs = file_as_string(path);

   string_array stra;

   stra.add_lines(strDirs);

   string strPrefix = str + "=";

   stra.filter_begins_ci(strPrefix);

   if(stra.get_size() != 1)
   {

      return "";

   }

   path = stra[0];

   ::str::begins_eat_ci(path, strPrefix);

   path.replace("$HOME", pathHome);

   path.trim("\"");

   return path;

}


namespace linux
{


   dir_context::dir_context()
   {


   }


   dir_context::~dir_context()
   {


   }


   ::e_status dir_context::initialize(::layered * pobjectContext)
   {

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      __refer(m_pfilesystem, System.m_pfilesystem);

      __refer(m_pdirsystem, System.m_pdirsystem);

      return ::success;

   }


   ::e_status dir_context::init_system()
   {

      if(!::dir_context::init_system())
      {

         return false;

      }

      auto pathCa2 = ca2module();

      pathCa2.go_up(3);

      m_pdirsystem->m_pathCa2 = pathCa2;

      auto pdocument = create_xml_document();

      pdocument->load(Context.file().as_string(appdata() /"configuration\\directory.xml"));

      if(pdocument->root() && pdocument->root()->get_name() == "directory_configuration")
      {

         m_pdirsystem->m_pathTimeFolder = pdocument->root()->get_child_value("time");

         m_pdirsystem->m_pathNetSeedFolder = pdocument->root()->get_child_value("netseed");

      }

#ifdef LINUX

      m_pdirsystem->m_pathTimeFolder = "/payload/tmp/ca2/time";

#else

      if(m_pdirsystem->m_pathTimeFolder.is_empty())
      {

         m_pdirsystem->m_pathTimeFolder = appdata() / "time";

      }

#endif

      if(m_pdirsystem->m_pathNetSeedFolder.is_empty())
      {

         m_pdirsystem->m_pathNetSeedFolder = install() / "netd";

      }

      mk(m_pdirsystem->m_pathTimeFolder);

      if(!is(m_pdirsystem->m_pathTimeFolder))
      {

         return false;

      }

      mk(m_pdirsystem->m_pathTimeFolder / "time");

      ::file::path pathHome = getenv("HOME");

      string pathInstall;

      pathInstall = install();

      index iFind = pathInstall.find(':');

      if(iFind >= 0)
      {

         strsize iFind1 = pathInstall.reverse_find("\\", iFind);

         strsize iFind2 = pathInstall.reverse_find("/", iFind);

         strsize iStart = max(iFind1 + 1, iFind2 + 1);

         pathInstall = pathInstall.Left(iFind - 1) + "_" + pathInstall.Mid(iStart, iFind - iStart) + pathInstall.Mid(iFind + 1);

      }

      return true;

   }


   ::e_status dir_context::init_context()
   {

      auto estatus = ::dir_context::init_context();

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::file::listing & dir_context::root_ones(::file::listing & listing)
   {

      listing.add("/");

      listing.m_straTitle.add("Filesystem");

      return listing;

   }


   ::file::listing & dir_context::ls(::file::listing & listing)
   {

      if(::dir_context::ls(listing).succeeded())
      {

         return listing;

      }

      if(listing.m_bRecursive)
      {

         index iStart = listing.get_count();

         {

            __restore(listing.m_pathUser);

            __restore(listing.m_pathFinal);

            __restore(listing.m_eextract);

            ::file::listing straDir;

            Context.dir().ls_dir(straDir, listing.m_pathFinal);

            for(i32 i = 0; i < straDir.get_count(); i++)
            {

               string strDir = straDir[i];

               if(strDir == listing.m_pathFinal)
               {

                  continue;

               }

               if(listing.m_bDir)
               {

                  ::file::path & path = listing.add_get(::file::path(strDir));

                  path.m_iSize = 0;

                  path.m_iDir = 1;

               }

               listing.m_pathUser = strDir;

               listing.m_pathFinal = strDir;

               Context.dir().ls(listing);


            }

         }

         if(listing.m_bFile)
         {

            __restore(listing.m_bRecursive);

            listing.m_bRecursive = false;

            Context.dir().ls_file(listing, listing.m_pathFinal);

         }

         for(index i = iStart; i < listing.get_size(); i++)
         {

            listing[i].m_iRelative = listing.m_pathFinal.get_length() + 1;

         }

      }
      else
      {

         ::file::patha stra;

         ::dir::ls(stra, listing.m_pathFinal);

         for(i32 i = 0; i < stra.get_count(); i++)
         {

            auto & strPath = stra[i];

            if(!::str::begins(strPath, listing.m_pathFinal))
               continue;

            bool bIsDir;

            if(strPath.m_iDir >= 0)
            {

               bIsDir = strPath.m_iDir != 0;

            }
            else
            {

               bIsDir = ::dir_context::is(strPath);

            }

            if(!bIsDir && !matches_wildcard_criteria(listing.m_straPattern, strPath.name()))
               continue;

            if((bIsDir && !listing.m_bDir) || (!bIsDir && !listing.m_bFile))
               continue;

            ::file::path & path = listing.add_get(strPath);

            path.m_iDir = bIsDir ? 1 : 0;

            if(bIsDir)
            {

               path.m_iSize = 0;

            }
            else
            {

               path.m_iSize = file_length_dup(strPath);

            }

         }

      }

      return listing;

   }


   bool dir_context::is(const ::file::path & path)
   {

      if(::dir::is(path))
      {

         return true;

      }

      bool bIsDir = ::dir::_is(path);

      return bIsDir;

   }


   bool dir_context::name_is(const ::file::path & str)
   {
      //output_debug_string(str);
      strsize iLast = str.get_length() - 1;
      while(iLast >= 0)
      {
         if(str[iLast] != '\\' && str[iLast] != '/' && str[iLast] != ':')
            break;
         iLast--;
      }
      while(iLast >= 0)
      {
         if(str[iLast] == '\\' || str[iLast] == '/' || str[iLast] == ':')
            break;
         iLast--;
      }
      if(iLast >= 0)
      {
         while(iLast >= 0)
         {
            if(str[iLast] != '\\' && str[iLast] != '/' && str[iLast] != ':')
            {
               iLast++;
               break;
            }
            iLast--;
         }
      }
      else
      {
         return true; // assume empty string is root_ones directory
      }

      if(thread_is_set(id_thread_zip_is_dir) && iLast >= 3  && !ansi_count_compare_ci(&((const char *) str)[iLast - 3], ".zip", 4))
      {

         return true;

      }

      wstring wstrPath;

      wstrPath = ::str::international::utf8_to_unicode(str, iLast + 1);

      bool bIsDir = ::dir_context::is(::str::international::unicode_to_utf8(wstrPath));

      return bIsDir;

   }


   ::file::path dir_context::time()
   {

      return m_pdirsystem->m_pathTimeFolder;

   }


   ::file::path dir_context::element_commonappdata(const string & strElement)
   {

      return ::file::path(strElement) / "commonappdata";

   }


   ::file::path dir_context::stage()
   {

      return install() / "stage";

   }


   ::file::path dir_context::stageapp()
   {

      return stage() / "basis";

   }


   ::file::path dir_context::netseed()
   {

      return m_pdirsystem->m_pathNetSeedFolder;

   }


   ::file::path dir_context::time_square()
   {

      return time() / "time";

   }


   ::file::path dir_context::time_log(const string & pszId)
   {

      ::file::path strLogBaseDir;

      strLogBaseDir = appdata() / "log";

      return strLogBaseDir / pszId;

   }


   bool dir_context::mk(const ::file::path & pcsz)
   {

      if(is(pcsz))
      {

         return true;

      }

      ::file::patha stra;

      pcsz.ascendants_path(stra);

      index i = stra.get_upper_bound();

      for(; i >= 0; i--)
      {

         if(is(stra[i]))
         {

            i++;

            break;

         }

      }

      if(i < 0)
      {

         return false;

      }

      for(; i < stra.get_size(); i++)
      {

         if(!::dir::mkdir(stra[i]))
         {

            auto estatus = ::get_last_status();

            if(estatus == error_already_exists)
            {

               string str;

               str = stra[i];

               str.trim_right("\\/");

               try
               {

                  Context.file().del(str);

               }
               catch(...)
               {

               }

               str = stra[i];

               str.trim_right("\\/");

               try
               {

                  Context.file().del(str);

               }
               catch(...)
               {

               }

               ::e_status estatus = ::success;

               if(::dir::mkdir(stra[i]))
               {

               }
               else
               {

                  estatus = ::get_last_status();

               }

            }

            char * pszError;

            if(!is(stra[i]))
            {

               return false;

            }

         }

      }

      return true;

   }


   bool dir_context::rm(const ::file::path & psz, bool bRecursive)
   {

      if(bRecursive)
      {

         ::file::listing straPath(::get_context());

         straPath.ls(psz);

         for(i32 i = 0; i < straPath.get_count(); i++)
         {

            if(is(straPath[i]))
            {

               rm(psz / straPath[i].name(), true);

            }
            else
            {

               ::unlink(straPath[i]);

            }

         }

      }

      return ::rmdir(psz) != FALSE;

   }


   ::file::path dir_context::trash_that_is_not_trash(const ::file::path & psz)
   {

      if(psz[1] == ':')
      {

         string strDir = psz.name();
         string str;
         str = strDir.Left(2);
         str += "\\trash_that_is_not_trash\\";
         string strFormat;
         ::datetime::time time;
         time = ::datetime::time::get_current_time();
         strFormat.Format("%04d-%02d-%02d %02d-%02d-%02d\\", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
         str += strFormat;
         if(strDir[2] == '\\')
         {
            str += strDir.Mid(3);
         }
         else
         {
            str += strDir.Mid(2);
         }
         return str;
      }

      return "";

   }


   ::file::path dir_context::appdata()
   {

      return ::dir_context::appdata();

   }


   ::file::path dir_context::commonappdata()
   {

      ::file::path path;

      path = ::file::path(getenv("HOME")) / ".config/ca2/commonappdata";

      string strRelative;

      strRelative = install();

      return path / "ca2" / strRelative;

   }


   ::file::path dir_context::userquicklaunch(::layered * pobjectContext)
   {

      ::file::path path;

      path = ::file::path(getenv("HOME")) / "Microsoft\\Internet Explorer\\Quick Launch";

      return path;

   }


   ::file::path dir_context::userprograms(::layered * pobjectContext)
   {

      ::file::path path;

      path = "/usr/bin";

      return path;

   }


   ::file::path dir_context::commonprograms()
   {

      ::file::path path;

      path = "/usr/share/";

      return path;

   }


   bool dir_context::is_inside_time(const ::file::path & pszPath)
   {

      return is_inside(time(), pszPath);

   }


   bool dir_context::is_inside(const ::file::path & pszDir, const ::file::path & pszPath)
   {

      return ::str::begins_ci(pszDir, pszPath);

   }


   bool dir_context::has_subdir(const ::file::path & pszDir)
   {

      ::file::listing listing(get_context());

      listing.ls_dir(pszDir);

      return listing.get_size() > 0;

   }


   ::file::path dir_context::music()
   {

      ::file::path path = xdg_get_dir("XDG_MUSIC_DIR");

      if(path.has_char())
      {

         return path;

      }

      path = getenv("HOME");

      path /= "Music";

      return path;

   }


   ::file::path dir_context::video()
   {

      ::file::path path = xdg_get_dir("XDG_VIDEOS_DIR");

      if(path.has_char())
      {

         return path;

      }

      path = getenv("HOME");

      path /= "Videos";

      return path;

   }


   ::file::path dir_context::image()
   {

      ::file::path path = xdg_get_dir("XDG_PICTURES_DIR");

      if(path.has_char())
      {

         return path;

      }

      path = getenv("HOME");

      path /= "Pictures";

      return path;

   }


   ::file::path dir_context::document()
   {

      ::file::path path = xdg_get_dir("XDG_DOCUMENTS_DIR");

      if(path.has_char())
      {

         return path;

      }

      path = getenv("HOME");

      path /= "Documents";

      return path;

   }


   ::file::path dir_context::download()
   {

      ::file::path path = xdg_get_dir("XDG_DOWNLOAD_DIR");

      if(path.has_char())
      {

         return path;

      }

      path = getenv("HOME");

      path /= "Downloads";

      return path;

   }


} // namespace linux



