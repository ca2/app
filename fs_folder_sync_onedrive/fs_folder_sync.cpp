// From fs/folder_sync.cpp to folder_sync.cpp by camilo on 2024-04-28 00:55 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "fs_folder_sync.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/primitive/data/listener.h"
#include "acme/primitive/string/international.h"
#include "acme/filesystem/filesystem/dir_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/context.h"
#include "apex/platform/node.h"


namespace fs_folder_sync_onedrive
{


   folder_sync::folder_sync()
   {

      m_pathProtocol = "onedrive://";

   }


   folder_sync::~folder_sync()
   {


   }


   bool folder_sync::check_files(
      const ::file::path& pathSourceFolder,
      const ::string_array& straSource,
      const ::function < void(const ::scoped_string&) >& callbackStatus)
   {

      return ::fs::folder_sync::check_files(pathSourceFolder, straSource, callbackStatus);

   }


   void folder_sync::copy_files_out(
      const ::file::path& pathTargetFolder,
      const ::file::path& pathSourceFolderParam,
      const ::string_array& straSource,
      const ::function < void(const ::scoped_string&) >& callbackStatus)
   {

      ::fs::folder_sync::copy_files_out(pathTargetFolder, pathSourceFolderParam, straSource, callbackStatus);

   }


   // optional if ls_dir is implemented
   bool folder_sync::has_subdir(const ::file::path& path)
   {

      return ::fs::folder_sync::has_subdir(path);

   }


   bool folder_sync::fast_has_subdir(const ::file::path& path)
   {

      return ::fs::folder_sync::fast_has_subdir(path);

   }


   bool folder_sync::enumerate(::file::listing& listing)
   {

      return ::fs::folder_sync::enumerate(listing);

   }


   bool folder_sync::is_link(const ::file::path& path)
   {

      return ::fs::folder_sync::is_link(path);

   }



   /*::file::listing & folder_sync::ls_relative_name(::file::listing & listing)
   {

      dir()->ls_relative_name(listing);

      return listing;

   }*/



   int folder_sync::is_dir(const ::file::path& path)
   {

      return ::fs::folder_sync::is_dir(path);

   }


   ::file::listing& folder_sync::root_ones(::file::listing& listing)
   {

      return ::fs::folder_sync::root_ones(listing);

   }


   //void folder_sync::get_ascendants_path(const ::file::path & pszPath,::file::path_array & stra)
   //{

   //   return file()->get_ascendants_path(pszPath, stra);

   //}


   //void folder_sync::get_ascendants_name(const ::file::path & path,::file::path_array & straParam)

   //{

   //   return file()->get_ascendants_name(pcsz, straParam);


   //}


   //string folder_sync::eat_end_level(const ::file::path & path, i32 iCount)
   //{

   //   string strPath(pszPath);

   //   while(iCount > 0)
   //   {

   //      strPath = dir()->name(strPath);

   //      iCount--;

   //   }

   //   return strPath;

   //}


   //string folder_sync::file_name(const ::file::path & path)
   //{

   //   return file()->name_(pszPath);

   //}


   //string folder_sync::dir_path(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2)
   //{

   //   return ::file::path(psz1) / ::file::path(psz2);

   //}


   bool folder_sync::file_move(const ::file::path& pszDst, const ::file::path& pszSrc)
   {

      return ::fs::folder_sync::file_move(pszDst, pszSrc);

   }


   file_pointer folder_sync::get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception)
   {

      return ::fs::folder_sync::get_file(payloadFile, eopen, ppfileexception);

   }


   bool folder_sync::file_exists(const ::file::path& path)
   {

      return ::fs::folder_sync::file_exists(path);

   }


} // namespace fs_folder_sync_onedrive



