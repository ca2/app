#include "framework.h"
#include "acme/filesystem/file/stdio_file.h"
#include "apex/filesystem/fs/_fs.h"


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

      return Context.dir().has_subdir(path);

   }


   ::file::listing & native::ls(::file::listing & listing)
   {

      Context.dir().ls(listing);

      return listing;

   }


   bool native::is_link(const ::file::path & path)
   {

      if(::fs::data::is_link(path))
      {

         return true;

      }

      if(Context.os_is_alias(path))
      {

         return true;

      }

      return false;

   }



   ::file::listing & native::ls_relative_name(::file::listing & listing)
   {

      Context.dir().ls_relative_name(listing);

      return listing;

   }



   int native::is_dir(const ::file::path & path)
   {

      return Context.dir().is(path) ? 1 : 0;

   }


   ::file::listing & native::root_ones(::file::listing & listing)
   {

      Context.dir().root_ones(listing);

      ::file::path pathDropbox = Context.defer_process_path("dropbox://");

      if(pathDropbox.has_char() && Context.dir().is(pathDropbox))
      {

         ::file::path & path = listing.insert_at(0, "dropbox://");
         path.m_iDir = 1;
         listing.m_straTitle.insert_at(0, unitext("Dropbox"));

      }

      ::file::path pathOneDrive = Context.defer_process_path("onedrive://");
      
      if(pathOneDrive.has_char() && Context.dir().is(pathOneDrive))
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
//         FALSE);
//
//      ::file::path & path = listing.insert_at(0,strDesktopFolder);
//      path.m_iDir = 1;
//      listing.m_straTitle.insert_at(0,unitext("Desktop"));
//
//#endif

      return listing;

   }


   //void native::get_ascendants_path(const ::file::path & pszPath,::file::patha & stra)
   //{

   //   return Context.file().get_ascendants_path(pszPath, stra);

   //}


   //void native::get_ascendants_name(const ::file::path & pcsz,::file::patha & straParam)

   //{

   //   return Context.file().get_ascendants_name(pcsz, straParam);


   //}


   //string native::eat_end_level(const char * pszPath, i32 iCount)
   //{

   //   string strPath(pszPath);

   //   while(iCount > 0)
   //   {

   //      strPath = Context.dir().name(strPath);

   //      iCount--;

   //   }

   //   return strPath;

   //}


   //string native::file_name(const char * pszPath)
   //{

   //   return Context.file().name_(pszPath);

   //}


   //string native::dir_path(const char * psz1, const char * psz2)
   //{

   //   return ::file::path(psz1) / ::file::path(psz2);

   //}


   bool native::file_move(const ::file::path & pszDst,const ::file::path & pszSrc)
   {

      Context.file().move(pszDst, pszSrc);

      return true;

   }


   file_result native::get_file(const ::file::path & path,UINT nOpenFlags)
   {

      file_pointer pfile;

      if (nOpenFlags & ::file::type_text)
      {

         pfile = __create_new<::stdio_file>();

      }
      else
      {

         pfile.create(this);

      }

      auto result = pfile->open(path,nOpenFlags);

      if(!result)
      {

         return result;

      }

      return pfile;

   }


   bool native::file_exists(const ::file::path & path)
   {

      return Context.file().exists(path);

   }


} // namespace fs



