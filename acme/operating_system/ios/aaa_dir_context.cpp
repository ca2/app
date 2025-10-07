#include "framework.h"
#include "_ios.h"
//#include "acme/xml/_.h"


bool _ui_library_dir(char * psz, unsigned int * puiSize);


namespace ios
{


   directory_context::directory_context()
   {


   }


   directory_context::~directory_context()
   {
   
   
   }


   ::file::listing & directory_context::root_ones(::file::listing & listing)
   {

      listing.add("/");

      listing.m_straTitle.add("File ::acmeacmesystem()");

      return listing;

   }


   ::file::listing & directory_context::ls(::file::listing & listing)
   {

      if(listing.m_bRecursive)
      {

         ::collection::index iStart = listing.get_size();

         {

            scoped_restore(listing.m_pathUser);

            scoped_restore(listing.m_pathFinal);

            scoped_restore(listing.m_eextract);

            if(::directory_context::ls(listing))
            {

               listing = ::error_failed;

               return listing;

            }

            ::file::listing dira(get_app());

            dira.ls_dir(listing.m_pathFinal);

            for(int i = 0; i < dira.get_count(); i++)
            {

               ::file::path directory_context = dira[i];

               if(directory_context == listing.m_pathFinal)
                  continue;

               listing.m_pathUser.empty();
               listing.m_pathFinal = directory_context;

               if(listing.m_eextract != e_extract_all)
               {

                  listing.m_eextract = e_extract_none;

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

         for(::collection::index i = iStart; i < listing.get_size(); i++)
         {

            listing[i].m_iRelative = listing.m_pathFinal.get_length() + 1;

         }

      }
      else
      {

         if(::directory_context::ls(listing).succeeded())
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


   bool directory_context::is(const ::file::path & path)
   {

      if(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->is(path))
      {

         return true;

      }

      string strPath(path);

#ifdef WINDOWS

      if(strPath.length() >= MAX_PATH)
      {

         if(string_begins(strPath, "\\\\"))
         {

            strPath = "\\\\?\\UNC" + strPath.substr(1);

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

         return true;

      }

      for(; i < stra.get_size(); i++)
      {

         if(!is(stra[i]))
         {

            if(::dir::mkdir(stra[i]))
            {

            }

            if(!         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->is(stra[i]))
            {

               return false;

            }

         }

      }

      return true;

   }


   //   bool dir::rm(::platform::application *   papp, const ::file::path & psz, bool bRecursive)
   //   {
   //      if(bRecursive)
   //      {
   //         string_array_base straPath;
   //         string_array_base straTitle;
   //         ls(papp, psz, &straPath, &straTitle);
   //         for(int i = 0; i < straPath.get_count(); i++)
   //         {
   //            if(is(straPath[i], papp))
   //            {
   //               rm(papp, path(scopedstr, straTitle[i]), true);
   //            }
   //            else
   //            {
   //               ::unlink(straPath[i]);
   //            }
   //         }
   //      }
   //      return ::rmdir(scopedstr) != false;
   //   }
   //
   //
   //   string ::file_path_folder(const ::file::path & path1)
   //   {
   //      const ::scoped_string & scopedstr = path1 + strlen(path1) - 1;
   //      while(scopedstr >= path1)
   //      {
   //         if(*psz != '\\' && *psz != '/' && *psz != ':')
   //            break;
   //         psz--;
   //      }
   //      while(scopedstr >= path1)
   //      {
   //         if(*psz == '\\' || *psz == '/' || *psz == ':')
   //            break;
   //         psz--;
   //      }
   //      if(scopedstr >= path1) // strChar == "\\" || strChar == "/"
   //      {
   //         const ::ansi_character * pszEnd = psz;
   //         /*while(scopedstr >= path1)
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
   //   string ::file_path_folder(const ::scoped_string & scopedstr)
   //   {
   //
   //      character_count iLast = str.length() - 1;
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
   //         return str.left(iLast + 1);
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



//   ::file::path directory_context::trash_that_is_not_trash(const ::file::path & psz)
//   {
//      if(scopedstr == nullptr)
//         return "";
//
//      if(scopedstr[1] == ':')
//      {
//         string strDir = name(scopedstr);
//         string str;
//         str = strDir.left(2);
//         str += "\\trash_that_is_not_trash\\";
//         string strFormat;
//         ::earth::time time;
//         time = ::earth::time::now();
//         strFormat.formatf("%04d-%02d-%02d %02d-%02d-%02d\\", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
//         str += strFormat;
//         if(strDir.m_pszData[2] == '\\')
//         {
//            str += strDir.substr(3);
//         }
//         else
//         {
//            str += strDir.substr(2);
//         }
//         return str;
//      }
//
//      return "";
//   }


   bool directory_context::has_subdir(const ::file::path & pszDir)
   {
      ::file::listing stra(get_context());
      stra.ls_dir(scopedstrDir);
      return stra.get_size() > 0;

   }



   ::file::path directory_context::time()
   {
      
      return ::acmeacmesystem()->m_pdirectorysystem->m_pathModule;
      
   }


   ::file::path directory_context::stage()
   {
      return install() / "stage";
   }

   ::file::path directory_context::stageapp()
   {
      return stage() / "basis";
   }

//   ::file::path directory_context::netseed()
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


   ::file::path directory_context::module()
   {

      return ::acmeacmesystem()->m_pdirectorysystem->m_pathModule;

   }


   ::file::path directory_context::ca2module()
   {

      return ::acmeacmesystem()->m_pdirectorysystem->m_pathCa2Module;

   }


   ::file::path directory_context::time_square(const ::scoped_string & scopedstrPrefix,const ::scoped_string & scopedstrSuffix)
   {

      __UNREFERENCED_PARAMETER(strPrefix);
      __UNREFERENCED_PARAMETER(strSuffix);
      return time() / "time";

   }


   ::file::path directory_context::time_log()
   {

      return appdata() / "log";

   }

   bool directory_context::rm(const ::file::path & psz, bool bRecursive)
   {
      if(bRecursive)
      {
         ::file::listing patha(get_context());
         patha.ls(scopedstr);
         for(auto & path : patha)
         {
            if(is(path))
            {
               rm(scopedstr / path.name(), true);
            }
            else
            {
               ::unlink(path);
            }
         }
      }
      return ::rmdir(scopedstr) == 0;
   }


   
//   ::file::path directory_context::name(const ::file::path & str)
//   {
//
//      character_count iLast = str.length() - 1;
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
//         return str.left(iLast + 1);
//      }
//      else
//      {
//         return "";
//      }
//   }


   void directory_context::initialize(::particle * pparticle)
   {

      auto estatus = ::directory_context::initialize(pparticle);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      m_pdirectorysystem = ::acmeacmesystem()->m_pdirectorysystem;
      
      m_pfilesystem = ::acmeacmesystem()->m_pfilesystem;

      
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

         char * psz = str.get_buffer(uiSize);

         _ui_library_dir(scopedstr, &uiSize);

         str.release_buffer(uiSize);

         m_pdirectorysystem->m_strCa2 = str;

      }


      ::file::path pathHome;

      pathHome = m_pdirectorysystem->m_strCa2/"Documents";

      ::acmeacmesystem()->m_strIosHome = pathHome;

      m_pdirectorysystem->m_pathHome = m_pdirectorysystem->m_strCa2/"Documents";

      //nodeos_set_home(::acmeacmesystem()->m_strIosHome);

      ::file::path str = m_pdirectorysystem->m_strCa2 / ".ca2/appdata";

//      m_pathUser = m_strCa2 / ".ca2/user";

      string strRelative;

      strRelative = install();

      m_pdirectorysystem->m_strCa2AppData = str / "ca2" / strRelative;

      str = m_pdirectorysystem->m_pathModule.folder();

      m_pdirectorysystem->m_strCommonAppData = str / "commonappdata";



      str = "/usr/bin";

      m_pdirectorysystem->m_strPrograms = str;

      str = "/usr/share/";

      m_pdirectorysystem->m_strCommonPrograms = str;

      return true;

   }

   void directory_context::init_context()
   {

      xml::document doc;

      string strPath = appdata() / "configuration/directory.xml";

      
      string strDocument = file()->as_string(strPath);

      if(doc.load(strDocument))
      {

         if(doc.root()->get_name() == "directory_configuration")
         {

            m_pdirectorysystem->m_strTimeFolder = doc.root()->get_child_value("time");

            m_pdirectorysystem->m_strNetSeedFolder = doc.root()->get_child_value("netseed");

         }

      }

      if(m_pdirectorysystem->m_strTimeFolder.is_empty())
      {

         m_pdirectorysystem->m_strTimeFolder = m_pdirectorysystem->m_strCa2 / "Library/Cache/time";

      }

      if(m_pdirectorysystem->m_strNetSeedFolder.is_empty())
      {

         m_pdirectorysystem->m_strNetSeedFolder = install() / "net";

      }

      mk(m_pdirectorysystem->m_strTimeFolder);

      if(!is(m_pdirectorysystem->m_strTimeFolder))
      {

         return false;

      }

      string strTime = m_pdirectorysystem->m_strTimeFolder / "time";

      mk(strTime);

      if(!is(strTime))
      {

         return false;

      }

      ::acmeacmesystem()->m_strIosTemp = strTime;

      //nodeos_set_temp(::acmeacmesystem()->m_strIosTemp);
      
      string str;

      str = "/usr/bin";

      m_pdirectorysystem->m_strPrograms = str;

      str = "/usr/share/";

      m_pdirectorysystem->m_strCommonPrograms = str;

      return true;

   }


   ::file::path directory_context::appdata()
   {

      return m_pdirectorysystem->m_strCa2AppData;

   }


   ::file::path directory_context::commonappdata_root()
   {

      return m_pdirectorysystem->m_strCommonAppData;

   }

   ::file::path directory_context::userquicklaunch()
   {

      return m_pdirectorysystem->m_strAppData / "Microsoft\\Internet Explorer\\Quick Launch";

   }


   ::file::path directory_context::userprograms()
   {

      return m_pdirectorysystem->m_strPrograms;

   }


   ::file::path directory_context::commonprograms()
   {

      return m_pdirectorysystem->m_strCommonPrograms;

   }


   bool directory_context::is_inside_time(const ::file::path & pszPath)
   {

      return is_inside(time(), pszPath);

   }


   bool directory_context::is_inside(const ::file::path & pszDir, const ::file::path & pszPath)
   {

      return case_insensitive_string_begins(scopedstrDir, pszPath);

   }


} // namespace ios



