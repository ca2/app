#include "framework.h"
//#include "_internal.h"
#include "acme/filesystem/filesystem/acme_file.h"



namespace folder_zip
{

   file_function_definitions g_filefunctiondefinitions;

   folder::folder() :
      m_unzfile(nullptr),
      m_zipfile(nullptr)
   {

      defer_create_mutex();
      //m_pzlibfilefuncdef = zip_filefuncdef_malloc();
          
   }


   folder::~folder()
   {

      if (m_unzfile)
      {

         unzClose(m_unzfile);

         m_unzfile = nullptr;

      }

      if (m_zipfile)
      {

         zipClose(m_zipfile, "zipFile");

         m_zipfile = nullptr;

      }

      //if (m_pzlibfilefuncdef)
      //{

      //   ::free(m_pzlibfilefuncdef);

      //   m_pzlibfilefuncdef = nullptr;

      //}

   }




   void folder::initialize(::object* pobject)
   {

      //auto estatus =
      ::object::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void folder::open_for_writing(file_pointer pfile)
   {

      //m_filea.erase_all();

      //m_infilea.erase_all();

      //m_straPath.erase_all();

      //m_straPrefix.erase_all();

      //string strFile;

      //strFile = pszFileName;


      //index iFind = -1;

      //index iStart = 0;

      //while((iFind = ::str::find_file_extension("zip:",pszFileName,iStart)) >= 0)

      //{

      //   m_straPath.add(string(&pszFileName[iStart],iFind + strlen(".zip")));


      //   iStart = iFind + strlen(".zip:");

      //}

      //if(::str::ends_ci(pszFileName,".zip"))

      //{

      //   m_straPath.add(string(&pszFileName[iStart]));


      //}

      //if(m_straPath.get_size() == 0)
      //{

      //   return false;

      //}

      //m_filea.add(__new(::zip::file()));

      auto zipfile = zipOpen2("pad", APPEND_STATUS_CREATE, nullptr, (zlib_filefunc_def *)&g_filefunctiondefinitions, pfile.m_p);

      //if(!zipfile)
      //{

      //   return false;

      //}

      m_zipfile = zipfile;

//      return true;

   }


   void folder::open_for_reading(::file_pointer pfile, int iBufferLevel)
   {

      auto unzfile = unzOpen2("pad", (zlib_filefunc_def*)&g_filefunctiondefinitions, pfile.m_p);

      //if (!unzfile)
      //{

      //   return false;

      //}

      m_pfile = pfile;

      m_unzfile = unzfile;

      //return true;
   }




   //bool folder::unzip_open(::zip::file * pzfile,const char * pcszFileName)

   //{

   //   ASSERT(__is_valid_string(pcszFileName));


   //   m_filea.add(pzfile);

   //   if(!locate(pcszFileName))

   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool folder::zip_open(::zip::file * pzfile,const char * pcszFileName)

   //{

   //   ASSERT(__is_valid_string(pcszFileName));


   //   m_filea.add(pzfile);

   //   m_strZipFile = pcszFileName;

   //   return true;
   //}

   //bool folder::dump(file_pointer  pfile)
   //{
   //   if(m_strFileName.is_empty())
   //      return false;
   //   byte buf[1024];
   //   memsize iRead;
   //   while((iRead = read(buf,sizeof(buf))) > 0)
   //   {
   //      pfile->write(buf,iRead);
   //   }
   //   return true;
   //}


   //bool folder::dump(memory & m)
   //{

   //   byte buf[1024];

   //   memsize iRead;

   //   while((iRead = read(buf,sizeof(buf))) > 0)
   //   {

   //      m.append(buf, iRead);

   //   }

   //   return true;

   //}



   /* Error Codes */
#ifndef LINUX

#define EPERM           1
#define ENOENT          2
#define ESRCH           3
#define EINTR           4
#define EIO             5
#define ENXIO           6
#define E2BIG           7
#define ENOEXEC         8
#define EBADF           9
#define ECHILD          10
#if !defined(__APPLE__) && !defined(FREEBSD)
#define EAGAIN          11
#endif
#define ENOMEM          12
#define EACCES          13
#define EFAULT          14
#define EBUSY           16
#define EEXIST          17
#define EXDEV           18
#define ENODEV          19
#define ENOTDIR         20
#define EISDIR          21
#define EINVAL          22
#define ENFILE          23
#define EMFILE          24
#define ENOTTY          25
#define EFBIG           27
#define ENOSPC          28
#define ESPIPE          29
#define EROFS           30
#define EMLINK          31
#define EPIPE           32
#define EDOM            33
#define ERANGE          34


#ifdef WINDOWS

#define EDEADLK         36
#define ENAMETOOLONG    38
#define ENOLCK          39
#define ENOSYS          40
#define ENOTEMPTY       41
#define EILSEQ          42

#endif




   /*
    * Support EDEADLOCK for compatibiity with older MS-C versions.
    */
#define EDEADLOCK       EDEADLK

#endif


   //bool in_file::is_opened() const
   //{

   //   return get_zip_file() != nullptr;

   //}


   //::zip::file * in_file::get_zip_file()
   //{

   //   if (m_filea.get_count() <= 0)
   //   {

   //      return nullptr;

   //   }

   //   return m_filea.last_pointer();

   //}


   //const ::zip::file * in_file::get_zip_file() const
   //{

   //   return m_filea.get_last_pointer();

   //}


   void folder::add_file(const ::file::path & pszRelative, ::file::file * pfile)
   {

      //::file::path strPath(pszDir / pszRelative);

      ::file::file_status status;

      pfile->get_status(status);

      zip_fileinfo zipfi;

      __memset(&zipfi,0,sizeof(zipfi));

      zipfi.tmz_date.tm_hour = status.m_ctime.hour();
      zipfi.tmz_date.tm_sec  = status.m_ctime.second();
      zipfi.tmz_date.tm_min  = status.m_ctime.minute();
      zipfi.tmz_date.tm_year = status.m_ctime.year();
      zipfi.tmz_date.tm_mon  = status.m_ctime.month();
      zipfi.tmz_date.tm_mday = status.m_ctime.day();

      zipOpenNewFileInZip(m_zipfile,pszRelative,&zipfi,nullptr,0,nullptr,0,nullptr,Z_DEFLATED,Z_DEFAULT_COMPRESSION);

      memory mem;

      mem.set_size(256 * 1024);

      memsize uRead;

      while((uRead = pfile->read(mem,mem.get_size())) > 0)
      {

         zipWriteInFileInZip(m_zipfile,mem.get_data(),(u32)uRead);

      }

      zipCloseFileInZip(m_zipfile);

   }


   bool folder::perform_file_listing(::file::listing & listing)
   {

      synchronous_lock synchronouslock(mutex());

      unzFile pf = m_unzfile;

      if (pf == nullptr)
      {

         throw_status(error_failed);

         //return listing;

      }

      string str;
      string wstrFolder;
      string_array wstraFolder;

      unz_file_info unzfileinfo;

      string strPrefix = listing.m_pathFinal;

      strPrefix.trim("\\/");

      if (strPrefix.has_char())
      {

         strPrefix += "/";

      }

      strPrefix.replace_with("/", "\\");

      int err = unzGoToFirstFile(pf);



      while (err == UNZ_OK)
      {

         char szTitle[_MAX_PATH];

         unzGetCurrentFileInfo(
         pf,
         &unzfileinfo,
         szTitle,
         _MAX_PATH,
         nullptr, // extra Field
         0,
         nullptr, // comment
         0);
            
         string strTitle(szTitle);

         if (strPrefix.is_empty() || strTitle.begins_eat_ci(strPrefix))
         {

            if (listing.m_bRecursive || strTitle.find("/") < 0 || strTitle.find("/") == (strTitle.get_length() - 1))
            {
               
               if (strTitle.has_char())
               {

                  listing.add(::file::path(strPrefix) / ::file::path(strTitle));

                  listing.last().m_iDir = ::str::ends(szTitle, "/") || ::str::ends(szTitle, "\\") || ::str::ends(szTitle, ".zip");

                  listing.last().m_iSize = unzfileinfo.uncompressed_size;

               }

            }

         }

         err = unzGoToNextFile(pf);

      }

      return listing;

   }


   bool folder::perform_file_relative_name_listing(::file::listing & listing)
   {

      synchronous_lock synchronouslock(mutex());

      unzFile pf = m_unzfile;

      if (pf == nullptr)
      {

         //listing = error_failed;

         //return listing;

         throw_status(error_failed);

      }

      string str;
      string wstrFolder;
      string_array wstraFolder;
      unz_file_info unzfileinfo;

      while (true)
      {

         char szTitle[_MAX_PATH];

         unzGetCurrentFileInfo(
         pf,
         &unzfileinfo,
         szTitle,
         _MAX_PATH,
         nullptr, // extra Field
         0,
         nullptr, // comment
         0);
            
         string strTitle(szTitle);

         if (listing.m_bRecursive || strTitle.find("/") < 0 || strTitle.find("/") == (strTitle.get_length() - 1))
         {

            listing.add(::file::path(strTitle));

            listing.last().m_iDir = ::str::ends(szTitle, "/") || ::str::ends(szTitle, "\\") || ::str::ends(szTitle, ".zip");

            listing.last().m_iSize = unzfileinfo.uncompressed_size;

         }

         if (unzGoToNextFile(pf) != UNZ_OK)
         {

            break;

         }

      }

      return listing;

   }


   ::file_pointer folder::get_file(const char* pszFile)
   {

      synchronous_lock synchronouslock(mutex());

      if (::is_set(pszFile))
      {

         if (!locate(pszFile))
         {

            return nullptr;

         }

      }

      auto pfile = __new(::folder_zip::file);

      pfile->m_pfolder = this;

      return pfile;

   }


   bool folder::has_sub_folder(const char* pszFileName)
   {

      return false;

   }


   void folder::extract(memory& m, const char* pszFile)
   {

      auto pfile = get_file(pszFile);

      pfile->full_read(m);

   }


   bool folder::is_compressed(const char* pszFileName)
   {

      return false;

   }


   void folder::extract_all(const char* pszTargetDir, ::file::patha* ppatha, string_array* pstraFilter, bool_array* pbaBeginsFilterEat)
   {

      ::file::listing listing;

      perform_file_listing(listing);

      ::file::path pathTargetFolder;

      pathTargetFolder = pszTargetDir;

      for (auto & path : listing)
      {

         ::memory memory;

         //auto preader = extract(memory, path);
         
         extract(memory, path);

         if (memory.has_data())
         {

            auto pathTarget = pathTargetFolder / path;

            m_psystem->m_pacmefile->put_block(pathTarget, memory);

         }

      }

      //return true;

   }


   //::file::listing& file_container::perform_file_listing(::file::listing& listing)
   //{

   //   throw interface_only_exception();

   //   return listing;

   //}



   //::file::listing& file_container::perform_file_relative_name_listing(::file::listing& listing)
   //{

   //   throw interface_only_exception();

   //   return listing;

   //}



   //void file_container::open_for_writing(file_pointer pfile)
   //{

   //   m_zipfile = zipOpen2("pad", APPEND_STATUS_CREATE, nullptr, (zlib_filefunc_def*)pfile->m_pvoidFileFuncDef);
   //   if (pf == nullptr)
   //      return nullptr;

   //   // m_mapUnzip.set_at(pf, pfile);

   //   return pf;

   //}


   bool folder::locate(const char* pszFileName)
   {

      synchronous_lock synchronouslock(mutex());

      m_iFilePosition = -1;
      string strFile(pszFileName);
      index iFind = strFile.find(":");
      if (iFind >= 0)
         strFile = strFile.Left(iFind);
      
      strFile.replace_with("/", "\\");

      if (unzLocateFile(m_unzfile, strFile, 0) != UNZ_OK)
      {

         strFile.replace_with("\\", "/");

         if (unzLocateFile(m_unzfile, strFile, 0) != UNZ_OK)
         {

            return false;

         }

      }

      if (unzOpenCurrentFile(m_unzfile) != UNZ_OK)
      {

         return false;

      }

      if (unzGetCurrentFileInfo(m_unzfile,
         &m_unzfileinfo,
         nullptr,
         0,
         nullptr,
         0,
         nullptr,
         0) != UNZ_OK)
      {

         return false;

      }

      m_iFilePosition = 0;

      m_strCurrent = strFile;

      return true;

   }


} // namespace zip



