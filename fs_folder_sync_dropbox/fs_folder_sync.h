// From fs/folder_sync.h fs_folder_sync_dropbox.h by camilo on 2024-04-28 00:51 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/filesystem/fs/folder_sync.h"


namespace fs_folder_sync_dropbox
{


   // fs::interface - file system interface


   class CLASS_DECL_FS_FOLDER_SYNC_DROPBOX folder_sync :
      virtual public ::fs::folder_sync
   {
   public:

      //::file::path    m_pathProtocol;
      //::file::path    m_pathLocalFolder;


      folder_sync();
      ~folder_sync() override;


      virtual bool check_files(const ::file::path& pathSourceFolder, const ::string_array& straSource, const ::function < void(const ::scoped_string&) >& callbackStatus);
      virtual void copy_files_out(const ::file::path& pathTargetFolder, const ::file::path& pathSourceFolder, const ::string_array& straSource, const ::function < void(const ::scoped_string&) >& callbackStatus);


      //bool _enumerates(::file::listing & listing) override;
      bool enumerate(::file::listing& listing) override;
      // virtual ::file::listing & ls_relative_name(::file::listing & listing) override;


      bool is_link(const ::file::path& path) override;

      // optional if ls_dir is implemented
      bool has_subdir(const ::file::path& pszPath) override;


      bool fast_has_subdir(const ::file::path& pszPath) override;

      int is_dir(const ::file::path& path) override;
      ::file::listing& root_ones(::file::listing& listing) override;

      bool file_exists(const ::file::path& pszPath) override;

      bool file_move(const ::file::path& pszDst, const ::file::path& pszSrc) override;

      ::file_pointer get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception = nullptr) override;


      ::string non__empty__file_as_string(const ::payload& payloadFile, const ::function < void(const ::scoped_string&) >& callbackStatus = {}) override;
      void wait_folder_contains_files(const ::file::path& pathTargetFolder, const ::string_array& straName, int iMinimumSize, const ::function < void(const ::scoped_string&) >& callbackStatus = {}) override;

   };


} // namespace fs_folder_sync_dropbox



