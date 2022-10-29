#include "framework.h"
#include "_ios.h"
#include "aqua/xml.h"


bool _ui_library_dir(char * psz, unsigned int * puiSize);


namespace ios
{


   dir_context::dir_context()
   {


   }


   dir_context::~dir_context()
   {
   
   
   }


   ::file::listing & dir_context::root_ones(::file::listing & listing)
   {

      listing.add("/");

      listing.m_straTitle.add("File System");

      return listing;

   }


   ::file::listing & dir_context::ls(::file::listing & listing)
   {

      if(listing.m_bRecursive)
      {

         index iStart = listing.get_size();

         {

            ___scoped_restore(listing.m_pathUser);

            ___scoped_restore(listing.m_pathFinal);

            ___scoped_restore(listing.m_eextract);

            if(::dir_context::ls(listing))
            {

               listing = ::error_failed;

               return listing;

            }

            ::file::listing dira(get_app());

            dira.ls_dir(listing.m_pathFinal);

            for(i32 i = 0; i < dira.get_count(); i++)
            {

               ::file::path dir_context = dira[i];

               if(dir_context == listing.m_pathFinal)
                  continue;

               listing.m_pathUser.Empty();
               listing.m_pathFinal = dir_context;

               if(listing.m_eextract != extract_all)
               {

                  listing.m_eextract = extract_none;

               }

               listing.ls();

            }

         }

         ::file::path_array  straPath;

         ::dir::ls(straPath, listing.m_pathFinal);

//            file_find file_find;

         //          bool bWorking = file_find.FindFile(listing.m_path / listing.os_pattern()) != false;

         for(auto & strPath : straPath)
         {

            bool bDir = is(strPath);

            if((listing.m_bDir && bDir) || (listing.m_bFile && !bDir))
            {

               if(!bDir && !matches_wildcard_criteria(listing.m_straPattern, strPath.name()))
                  continue;

               listing.add(strPath);

               listing.last().m_iDir = bDir ? 1 : 0;

            }

         }

         for(index i = iStart; i < listing.get_size(); i++)
         {

            listing[i].m_iRelative = listing.m_pathFinal.get_length() + 1;

         }

      }
      else
      {

         if(::dir_context::ls(listing).succeeded())
         {

            return listing;

         }

         ::file::path_array  straPath;

         ::dir::ls(straPath, listing.m_pathFinal);

         // file_find file_find;

         // bool bWorking = file_find.FindFile(listing.m_path / listing.os_pattern()) != false;

         for(auto & strPath : straPath)
         {

            bool bDir = is(strPath);

            if((listing.m_bDir && bDir) || (listing.m_bFile && !bDir))
            {

               if(!bDir && !matches_wildcard_criteria(listing.m_straPattern, strPath.name()))
                  continue;

               listing.add(strPath);

               listing.last().m_iDir = bDir ? 1 : 0;

            }

         }

      }

      return listing;

   }


   bool dir_context::is(const ::file::path & path)
   {

      if(         auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->is(path))
      {

         return true;

      }

      string strPath(path);

#ifdef WINDOWS

      if(strPath.get_length() >= MAX_PATH)
      {

         if(::str().begins(strPath, "\\\\"))
         {

            strPath = "\\\\?\\UNC" + strPath.Mid(1);

         }
         else
         {

            strPath = "\\\\?\\" + strPath;

         }

      }

#endif

      bool bIsDir = ::dir::_is(strPath);

      return bIsDir;

   }


   bool dir_context::mk(const ::file::path & pcsz)
   {

      if(is(pcsz))
      {
         
         return true;
         
      }

      ::file::path_array stra;

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

         return true;

      }

      for(; i < stra.get_size(); i++)
      {

         if(!is(stra[i]))
         {

            if(::dir::mkdir(stra[i]))
            {

            }

            if(!         auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->is(stra[i]))
            {

               return false;

            }

         }

      }

      return true;

   }


   //   bool dir::rm(::aura::application *   papp, const ::file::path & psz, bool bRecursive)
   //   {
   //      if(bRecursive)
   //      {
   //         string_array straPath;
   //         string_array straTitle;
   //         ls(papp, psz, &straPath, &straTitle);
   //         for(i32 i = 0; i < straPath.get_count(); i++)
   //         {
   //            if(is(straPath[i], papp))
   //            {
   //               rm(papp, path(psz, straTitle[i]), true);
   //            }
   //            else
   //            {
   //               ::unlink(straPath[i]);
   //            }
   //         }
   //      }
   //      return ::rmdir(psz) != false;
   //   }
   //
   //
   //   string ::file_path_folder(const ::string & path1)
   //   {
   //      const char * psz = path1 + strlen(path1) - 1;
   //      while(psz >= path1)
   //      {
   //         if(*psz != '\\' && *psz != '/' && *psz != ':')
   //            break;
   //         psz--;
   //      }
   //      while(psz >= path1)
   //      {
   //         if(*psz == '\\' || *psz == '/' || *psz == ':')
   //            break;
   //         psz--;
   //      }
   //      if(psz >= path1) // strChar == "\\" || strChar == "/"
   //      {
   //         const char * pszEnd = psz;
   //         /*while(psz >= path1)
   //          {
   //          if(*psz != '\\' && *psz != '/' && *psz != ':')
   //          break;
   //          psz--;
   //          }*/
   //         return string(path1, pszEnd - path1 + 1);
   //      }
   //      else
   //      {
   //         return "";
   //      }
   //   }
   //
   //   string ::file_path_folder(const ::string & str)
   //   {
   //
   //      strsize iLast = str.get_length() - 1;
   //
   //      while(iLast >= 0)
   //      {
   //         if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
   //            break;
   //         iLast--;
   //      }
   //      while(iLast >= 0)
   //      {
   //         if(str.m_pszData[iLast] == '\\' || str.m_pszData[iLast] == '/' || str.m_pszData[iLast] == ':')
   //            break;
   //         iLast--;
   //      }
   //      if(iLast >= 0)
   //      {
   //         while(iLast >= 0)
   //         {
   //            if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
   //               break;
   //            iLast--;
   //         }
   //         return str.Left(iLast + 1);
   //      }
   //      else
   //      {
   //         return "";
   //      }
   //   }
   //
   //
   //   class ::file::path & dir::path()
   //   {
   //      return m_path;
   //   }



//   ::file::path dir_context::trash_that_is_not_trash(const ::file::path & psz)
//   {
//      if(psz == nullptr)
//         return "";
//
//      if(psz[1] == ':')
//      {
//         string strDir = name(psz);
//         string str;
//         str = strDir.Left(2);
//         str += "\\trash_that_is_not_trash\\";
//         string strFormat;
//         ::earth::time time;
//         time = ::earth::time::now();
//         strFormat.format("%04d-%02d-%02d %02d-%02d-%02d\\", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
//         str += strFormat;
//         if(strDir.m_pszData[2] == '\\')
//         {
//            str += strDir.Mid(3);
//         }
//         else
//         {
//            str += strDir.Mid(2);
//         }
//         return str;
//      }
//
//      return "";
//   }


   bool dir_context::has_subdir(const ::file::path & pszDir)
   {
      ::file::listing stra(get_context());
      stra.ls_dir(pszDir);
      return stra.get_size() > 0;

   }



   ::file::path dir_context::time()
   {
      
      return psystem->m_pdirsystem->m_pathModule;
      
   }


   ::file::path dir_context::stage()
   {
      return install() / "stage";
   }

   ::file::path dir_context::stageapp()
   {
      return stage() / "basis";
   }

//   ::file::path dir_context::netseed()
//   {
//      return m_strNetSeedFolder;
//   }

   // stage in ca2os spalib
//   ::file::path dir::install()
//   {
//
//      single_lock synchronouslock(m_pmutex, true);
//
//      return m_strCa2;
//
//   }


   ::file::path dir_context::module()
   {

      return psystem->m_pdirsystem->m_pathModule;

   }


   ::file::path dir_context::ca2module()
   {

      return psystem->m_pdirsystem->m_pathCa2Module;

   }


   ::file::path dir_context::time_square(const ::string & strPrefix, const ::string & strSuffix)
   {

      __UNREFERENCED_PARAMETER(strPrefix);
      __UNREFERENCED_PARAMETER(strSuffix);
      return time() / "time";

   }


   ::file::path dir_context::time_log()
   {

      return appdata() / "log";

   }

   bool dir_context::rm(const ::file::path & psz, bool bRecursive)
   {
      if(bRecursive)
      {
         ::file::listing patha(get_context());
         patha.ls(psz);
         for(auto & path : patha)
         {
            if(is(path))
            {
               rm(psz / path.name(), true);
            }
            else
            {
               ::unlink(path);
            }
         }
      }
      return ::rmdir(psz) == 0;
   }


   
//   ::file::path dir_context::name(const ::file::path & str)
//   {
//
//      strsize iLast = str.get_length() - 1;
//
//      while(iLast >= 0)
//      {
//         if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
//            break;
//         iLast--;
//      }
//      while(iLast >= 0)
//      {
//         if(str.m_pszData[iLast] == '\\' || str.m_pszData[iLast] == '/' || str.m_pszData[iLast] == ':')
//            break;
//         iLast--;
//      }
//      if(iLast >= 0)
//      {
//         while(iLast >= 0)
//         {
//            if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
//               break;
//            iLast--;
//         }
//         return str.Left(iLast + 1);
//      }
//      else
//      {
//         return "";
//      }
//   }


   void dir_context::initialize(::particle * pparticle)
   {

      auto estatus = ::dir_context::initialize(pparticle);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      m_pdirsystem = psystem->m_pdirsystem;
      
      m_pfilesystem = psystem->m_pfilesystem;

      
//      if(!update_module_path())
//      {
//
//         return false;
//
//      }

      
//      m_strCa2 = ::file::path(getenv("HOME")) / "Library/papp Support";
      {

         string str;

         unsigned int uiSize = 4096;

         char * psz = str.get_string_buffer(uiSize);

         _ui_library_dir(psz, &uiSize);

         str.release_string_buffer(uiSize);

         m_pdirsystem->m_strCa2 = str;

      }


      ::file::path pathHome;

      pathHome = m_pdirsystem->m_strCa2/"Documents";

      psystem->m_strIosHome = pathHome;

      //m_pdirsystem->m_pathHome = m_pdirsystem->m_strCa2/"Documents";

      m_pdirsystem->m_pathHome = acmedirectory()->m_pplatformdir->m_pathDocument;


      //nodeos_set_home(psystem->m_strIosHome);

      ::file::path str = m_pdirsystem->m_strCa2 / ".ca2/appdata";

//      m_pathUser = m_strCa2 / ".ca2/user";

      string strRelative;

      strRelative = install();

      m_pdirsystem->m_strCa2AppData = str / "ca2" / strRelative;

      str = m_pdirsystem->m_pathModule.folder();

      m_pdirsystem->m_strCommonAppData = str / "commonappdata";



      str = "/usr/bin";

      m_pdirsystem->m_strPrograms = str;

      str = "/usr/share/";

      m_pdirsystem->m_strCommonPrograms = str;

      return true;

   }

   void dir_context::init_context()
   {

      xml::document doc;

      string strPath = appdata() / "configuration/directory.xml";

      
      string strDocument = pcontext->m_papexcontext->file()->as_string(strPath);

      if(doc.load(strDocument))
      {

         if(doc.root()->get_name() == "directory_configuration")
         {

            m_pdirsystem->m_strTimeFolder = doc.root()->get_child_value("time");

            m_pdirsystem->m_strNetSeedFolder = doc.root()->get_child_value("netseed");

         }

      }

      if(m_pdirsystem->m_strTimeFolder.is_empty())
      {

         m_pdirsystem->m_strTimeFolder = m_pdirsystem->m_strCa2 / "Library/Cache/time";

      }

      if(m_pdirsystem->m_strNetSeedFolder.is_empty())
      {

         m_pdirsystem->m_strNetSeedFolder = install() / "net";

      }

      mk(m_pdirsystem->m_strTimeFolder);

      if(!is(m_pdirsystem->m_strTimeFolder))
      {

         return false;

      }

      string strTime = m_pdirsystem->m_strTimeFolder / "time";

      mk(strTime);

      if(!is(strTime))
      {

         return false;

      }

      psystem->m_strIosTemp = strTime;

      //nodeos_set_temp(psystem->m_strIosTemp);
      
      string str;

      str = "/usr/bin";

      m_pdirsystem->m_strPrograms = str;

      str = "/usr/share/";

      m_pdirsystem->m_strCommonPrograms = str;

      return true;

   }


   ::file::path dir_context::appdata()
   {

      return m_pdirsystem->m_strCa2AppData;

   }


   ::file::path dir_context::commonappdata_root()
   {

      return m_pdirsystem->m_strCommonAppData;

   }

   ::file::path dir_context::userquicklaunch()
   {

      return m_pdirsystem->m_strAppData / "Microsoft\\Internet Explorer\\Quick Launch";

   }


   ::file::path dir_context::userprograms()
   {

      return m_pdirsystem->m_strPrograms;

   }


   ::file::path dir_context::commonprograms()
   {

      return m_pdirsystem->m_strCommonPrograms;

   }


   bool dir_context::is_inside_time(const ::file::path & pszPath)
   {

      return is_inside(time(), pszPath);

   }


   bool dir_context::is_inside(const ::file::path & pszDir, const ::file::path & pszPath)
   {

      return ::str().begins_ci(pszDir, pszPath);

   }


} // namespace ios



