// From fs/folder_sync.h fs_folder_sync_onedrive.h by camilo on 2024-04-28 00:51 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/filesystem/fs/folder_sync.h"


namespace fs_folder_sync_onedrive
{


   // fs::interface - file system interface


   class CLASS_DECL_FS_FOLDER_SYNC_ONEDRIVE folder_sync :
      virtual public ::fs::folder_sync
   {
   public:

      //::file::path    m_pathProtocol;
      //::file::path    m_pathLocalFolder;


      folder_sync();
      ~folder_sync() override;


      virtual bool check_files(const ::file::path& pathSourceFolder, const ::string_array_base& straSource, const ::function < void(const ::scoped_string&) >& callbackStatus);
      virtual void copy_files_out(const ::file::path& pathTargetFolder, const ::file::path& pathSourceFolder, const ::string_array_base& straSource, const ::function < void(const ::scoped_string&) >& callbackStatus);


      //bool _enumerates(::file::listing_base & listing) override;
      bool enumerate(::file::listing_base& listing) override;
      // virtual ::file::listing_base & ls_relative_name(::file::listing_base & listing) override;


      bool is_link(const ::file::path& path) override;

      // optional if ls_dir is implemented
      bool has_subdir(const ::file::path & path) override;


      bool fast_has_subdir(const ::file::path & path) override;

      int is_dir(const ::file::path& path) override;
      ::file::listing_base& root_ones(::file::listing_base& listing) override;

      bool file_exists(const ::file::path & path) override;

      bool file_move(const ::file::path & pathTarget, const ::file::path & pathSource) override;

      file_pointer get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception = nullptr) override;


   };


} // namespace fs_folder_sync_onedrive



