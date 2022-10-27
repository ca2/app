#include "framework.h"
#include "native.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/filesystem/listing.h"
//#include "apex/filesystem/fs/_fs.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/platform/context.h"


namespace fs
{


   native::native()
   {

   }


   native::~native()
   {


   }


   // optional if ls_dir is implemented
   bool native::has_subdir(const ::file::path & path)
   {

      return m_pcontext->m_papexcontext->dir().has_subdir(path);

   }


   bool native::enumerate(::file::listing & listing)
   {

      return m_pcontext->m_papexcontext->dir().enumerate(listing);

   }


   bool native::is_link(const ::file::path & path)
   {

      if(::fs::data::is_link(path))
      {

         return true;

      }

      if(m_pcontext->m_papexcontext->os_is_alias(path))
      {

         return true;

      }

      return false;

   }



   /*::file::listing & native::ls_relative_name(::file::listing & listing)
   {

      m_pcontext->m_papexcontext->dir().ls_relative_name(listing);

      return listing;

   }*/



   int native::is_dir(const ::file::path & path)
   {

      return m_pcontext->m_papexcontext->dir().is(path) ? 1 : 0;

   }


   ::file::listing & native::root_ones(::file::listing & listing)
   {

      m_pcontext->m_papexcontext->dir().root_ones(listing);

      ::file::path pathDropbox = m_pcontext->m_papexcontext->defer_process_path("dropbox://");

      if(pathDropbox.has_char() && m_pcontext->m_papexcontext->dir().is(pathDropbox))
      {

         ::file::path & path = listing.insert_at(0, "dropbox://");

         path.m_iDir = 1;

         listing.m_straTitle.insert_at(0, unitext("Dropbox"));

      }

      ::file::path pathDropboxApp = m_pcontext->m_papexcontext->defer_process_path("dropbox-app://");

      if(pathDropboxApp.has_char() && m_pcontext->m_papexcontext->dir().is(pathDropboxApp))
      {

         ::file::path & path = listing.insert_at(0, "dropbox-app://");

         path.m_iDir = 1;

         listing.m_straTitle.insert_at(0, unitext("Dropbox-App"));

      }

      ::file::path pathOneDrive = m_pcontext->m_papexcontext->defer_process_path("onedrive://");
      
      if(pathOneDrive.has_char() && m_pcontext->m_papexcontext->dir().is(pathOneDrive))
      {
         
         ::file::path & path = listing.insert_at(0, "onedrive://");

         path.m_iDir = 1;

         listing.m_straTitle.insert_at(0, unitext("OneDrive"));
         
      }

      {

         ::file::path & path = listing.insert_at(0, "video://");

         path.m_iDir = 1;

         listing.m_straTitle.insert_at(0, unitext("Video"));

      }

      {


         ::file::path & path = listing.insert_at(0, "image://");

         path.m_iDir = 1;

         listing.m_straTitle.insert_at(0, unitext("Image"));

      }

      {

         ::file::path & path = listing.insert_at(0, "music://");

         path.m_iDir = 1;

         listing.m_straTitle.insert_at(0, unitext("Music"));

      }

      {

         ::file::path & path = listing.insert_at(0, "download://");

         path.m_iDir = 1;

         listing.m_straTitle.insert_at(0, unitext("Download"));

      }

      {

         ::file::path & path = listing.insert_at(0, "document://");

         path.m_iDir = 1;

         listing.m_straTitle.insert_at(0, unitext("Document"));

      }

      {

         ::file::path & path = listing.insert_at(0, "desktop://");

         path.m_iDir = 1;

         listing.m_straTitle.insert_at(0, unitext("Desktop"));

      }

//#ifdef WINDOWS_DESKTOP
//
//      ::file::path strDesktopFolder;
//
//      ::windows::shell_get_special_folder_path(
//         nullptr,
//         strDesktopFolder,
//         CSIDL_DESKTOP,
//         false);
//
//      ::file::path & path = listing.insert_at(0,strDesktopFolder);
//      path.m_iDir = 1;
//      listing.m_straTitle.insert_at(0,unitext("Desktop"));
//
//#endif

      return listing;

   }


   //void native::get_ascendants_path(const ::file::path & pszPath,::file::path_array & stra)
   //{

   //   return m_pcontext->m_papexcontext->file().get_ascendants_path(pszPath, stra);

   //}


   //void native::get_ascendants_name(const ::file::path & pcsz,::file::path_array & straParam)

   //{

   //   return m_pcontext->m_papexcontext->file().get_ascendants_name(pcsz, straParam);


   //}


   //string native::eat_end_level(const char * pszPath, i32 iCount)
   //{

   //   string strPath(pszPath);

   //   while(iCount > 0)
   //   {

   //      strPath = m_pcontext->m_papexcontext->dir().name(strPath);

   //      iCount--;

   //   }

   //   return strPath;

   //}


   //string native::file_name(const char * pszPath)
   //{

   //   return m_pcontext->m_papexcontext->file().name_(pszPath);

   //}


   //string native::dir_path(const char * psz1, const char * psz2)
   //{

   //   return ::file::path(psz1) / ::file::path(psz2);

   //}


   bool native::file_move(const ::file::path & pszDst,const ::file::path & pszSrc)
   {

      m_pcontext->m_papexcontext->file().move(pszDst, pszSrc);

      return true;

   }


   file_pointer native::get_file(const ::file::path & path, const ::file::e_open & eopen)
   {

      file_pointer pfile;

      //if (eopen & ::file::e_open_text)
      //{

      //   pfile = __create_new<::stdio_file>();

      //}
      //else
      //{

         pfile.create(this);

//      }

      //auto result =
         pfile->open(path, eopen);

      //if(!result)
      //{

      //   return result;

      //}

      return pfile;

   }


   bool native::file_exists(const ::file::path & path)
   {

      return m_pcontext->m_papexcontext->file().exists(path);

   }


} // namespace fs



