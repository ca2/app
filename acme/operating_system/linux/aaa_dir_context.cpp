#include "framework.h"
////#include "acme/xml/_.h"
#include "acme/constant/id.h"
#include "_linux.h"
#undef USE_MISC

#ifdef RASPBERRYPIOS
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

   string strDirs = file_system()->as_string(path);

   string_array stra;

   stra.add_lines(strDirs);

   string strPrefix = str + "=";

   stra.case_insensitive_filter_begins(strPrefix);

   if(stra.get_size() != 1)
   {

      return "";

   }

   path = stra[0];

   path.case_insensitive_begins_eat(strPrefix);

   path.replace("$HOME", pathHome);

   path.trim("\"");

   return path;

}


namespace linux
{


   directory_context::directory_context()
   {


   }


   directory_context::~directory_context()
   {


   }


   void directory_context::initialize(::particle * pparticle)
   {

      auto estatus = ::matter::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      __refer(m_pfilesystem, ::acmeacmesystem()->m_pfilesystem);

      __refer(m_pdirectorysystem, ::acmeacmesystem()->m_pdirectorysystem);

      return ::success;

   }


   void directory_context::init_system()
   {

      if(!::directory_context::init_system())
      {

         return false;

      }

      auto pathCa2 = ca2module();

      pathCa2.go_up(3);

      m_pdirectorysystem->m_pathCa2 = pathCa2;

//      auto pdocument = create_xml_document();
//
//      pdocument->load(file()->as_string(appdata() /"configuration\\directory.xml"));
//
//      if(pdocument->root() && pdocument->root()->get_name() == "directory_configuration")
//      {
//
//         m_pdirectorysystem->m_pathTimeFolder = pdocument->root()->get_child_value("time");
//
//         m_pdirectorysystem->m_pathNetSeedFolder = pdocument->root()->get_child_value("netseed");
//
//      }

#ifdef LINUX

      m_pdirectorysystem->m_pathTimeFolder = "/::payload/tmp/ca2/time";

#else

      if(m_pdirectorysystem->m_pathTimeFolder.is_empty())
      {

         m_pdirectorysystem->m_pathTimeFolder = appdata() / "time";

      }

#endif

      if(m_pdirectorysystem->m_pathNetSeedFolder.is_empty())
      {

         m_pdirectorysystem->m_pathNetSeedFolder = install() / "netd";

      }

      mk(m_pdirectorysystem->m_pathTimeFolder);

      if(!is(m_pdirectorysystem->m_pathTimeFolder))
      {

         return false;

      }

      mk(m_pdirectorysystem->m_pathTimeFolder / "time");

      ::file::path pathHome = getenv("HOME");

      string pathInstall;

      pathInstall = install();

      auto pFind = pathInstall.find(':');

      if(::is_set(pFind))
      {

         strsize iFind1 = pathInstall(pFind).rear_find("\\");

         strsize iFind2 = pathInstall(pFind).rear_find("/");

         strsize iStart = maximum(iFind1 + 1, iFind2 + 1);

         pathInstall = pathInstall.left(iFind - 1) + "_" + pathInstall.substr(iStart, iFind - iStart) + pathInstall(pFind + 1);

      }

      return true;

   }


   void directory_context::init_context()
   {

      auto estatus = ::directory_context::init_context();

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::file::listing & directory_context::root_ones(::file::listing & listing)
   {

      listing.add("/");

      listing.m_straTitle.add("Filesystem");

      return listing;

   }


   ::file::listing & directory_context::ls(::file::listing & listing)
   {

      if(::directory_context::ls(listing).succeeded())
      {

         return listing;

      }

      if(listing.m_bRecursive)
      {

         ::collection::index iStart = listing.get_count();

         {

            scoped_restore(listing.m_pathUser);

            scoped_restore(listing.m_pathFinal);

            scoped_restore(listing.m_eextract);

            ::file::listing straDir(get_context());

            straDir.ls_dir(listing.m_pathFinal);

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

               listing.ls();


            }

         }

         if(listing.m_bFile)
         {

            scoped_restore(listing.m_bRecursive);

            listing.m_bRecursive = false;

            listing.ls_file(listing.m_pathFinal);

         }

         for(::collection::index i = iStart; i < listing.get_size(); i++)
         {

            listing[i].m_iRelative = listing.m_pathFinal.get_length() + 1;

         }

      }
      else
      {

         ::file::path_array stra;

         ::dir::ls(stra, listing.m_pathFinal);

         for(i32 i = 0; i < stra.get_count(); i++)
         {

            auto & strPath = stra[i];

            if(!string_begins(strPath, listing.m_pathFinal))
               continue;

            bool bIsDir;

            if(strPath.m_iDir >= 0)
            {

               bIsDir = strPath.m_iDir != 0;

            }
            else
            {

               bIsDir = ::directory_context::is(strPath);

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


   bool directory_context::is(const ::file::path & path)
   {

      if(         auto psystem = system();

         auto pacmedirectory = psystem->m_pdirectorysystem;

pacmedirectory->is(path))
      {

         return true;

      }

      bool bIsDir = ::dir::_is(path);

      return bIsDir;

   }


   bool directory_context::name_is(const ::file::path & str)
   {
      //information(str);
      strsize iLast = str.length() - 1;
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

      if(task_flag().is_set(e_task_flag_compress_is_dir) && iLast >= 3  && !case_insensitive_ansi_count_compare(&((const char *) str)[iLast - 3], ".zip", 4))
      {

         return true;

      }

      wstring wstrPath;

      wstrPath = utf8_to_unicode(str, iLast + 1);

      bool bIsDir = ::directory_context::is(unicode_to_utf8(wstrPath));

      return bIsDir;

   }


   ::file::path directory_context::time()
   {

      return m_pdirectorysystem->m_pathTimeFolder;

   }


   ::file::path directory_context::element_commonappdata(const ::string & strElement)
   {

      return ::file::path(strElement) / "commonappdata";

   }


   ::file::path directory_context::stage()
   {

      return install() / "stage";

   }


   ::file::path directory_context::stageapp()
   {

      return stage() / "basis";

   }


   ::file::path directory_context::netseed()
   {

      return m_pdirectorysystem->m_pathNetSeedFolder;

   }


   ::file::path directory_context::time_square()
   {

      return time() / "time";

   }


   ::file::path directory_context::time_log(const string & pszId)
   {

      ::file::path strLogBaseDir;

      strLogBaseDir = appdata() / "log";

      return strLogBaseDir / pszId;

   }


   bool directory_context::mk(const ::file::path & path)
   {

      if(is(pcsz))
      {

         return true;

      }

      ::file::path_array stra;

      pcsz.ascendants_path(stra);

      ::collection::index i = stra.get_upper_bound();

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

            ::u32 dwError = ::get_last_error();

            if(dwError == ERROR_ALREADY_EXISTS)
            {

               string str;

               str = stra[i];

               str.trim_right("\\/");

               try
               {

                  file()->del(str);

               }
               catch(...)
               {

               }

               str = stra[i];

               str.trim_right("\\/");

               try
               {

                  file()->del(str);

               }
               catch(...)
               {

               }

               if(::dir::mkdir(stra[i]))
               {

               }
               else
               {

                  dwError = ::get_last_error();

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


   bool directory_context::rm(const ::file::path & psz, bool bRecursive)
   {

      if(bRecursive)
      {

         ::file::listing straPath(get_context());

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

      return ::rmdir(psz) != false;

   }


   ::file::path directory_context::trash_that_is_not_trash(const ::file::path & psz)
   {

      if(psz[1] == ':')
      {

         string strDir = psz.name();
         string str;
         str = strDir.left(2);
         str += "\\trash_that_is_not_trash\\";
         string strFormat;
         ::earth::time time;
         time = ::earth::time::now();
         strFormat.formatf("%04d-%02d-%02d %02d-%02d-%02d\\", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
         str += strFormat;
         if(strDir[2] == '\\')
         {
            str += strDir.substr(3);
         }
         else
         {
            str += strDir.substr(2);
         }
         return str;
      }

      return "";

   }


   ::file::path directory_context::appdata()
   {

      return ::directory_context::appdata();

   }


   ::file::path directory_context::commonappdata()
   {

      ::file::path path;

      path = ::file::path(getenv("HOME")) / ".config/ca2/commonappdata";

      string strRelative;

      strRelative = install();

      return path / "ca2" / strRelative;

   }


   ::file::path directory_context::userquicklaunch(::particle * pparticle)
   {

      ::file::path path;

      path = ::file::path(getenv("HOME")) / "Microsoft\\Internet Explorer\\Quick Launch";

      return path;

   }


   ::file::path directory_context::userprograms(::particle * pparticle)
   {

      ::file::path path;

      path = "/usr/bin";

      return path;

   }


   ::file::path directory_context::commonprograms()
   {

      ::file::path path;

      path = "/usr/share/";

      return path;

   }


   bool directory_context::is_inside_time(const ::file::path & pszPath)
   {

      return is_inside(time(), pszPath);

   }


   bool directory_context::is_inside(const ::file::path & pszDir, const ::file::path & pszPath)
   {

      return case_insensitive_string_begins(pszDir, pszPath);

   }


   bool directory_context::has_subdir(const ::file::path & pszDir)
   {

      ::file::listing listing(get_context());

      listing.ls_dir(pszDir);

      return listing.get_size() > 0;

   }


   ::file::path directory_context::music()
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


   ::file::path directory_context::video()
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


   ::file::path directory_context::image::image()
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


   ::file::path directory_context::document()
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


   ::file::path directory_context::download()
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



