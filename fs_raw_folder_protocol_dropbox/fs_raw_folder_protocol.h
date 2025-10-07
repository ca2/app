// From fs_folder_sync_dropbox camilo on 2025-03-10 20:33 <3ThomasBorregaardSorensen!!
// From fs/folder_sync.h filesystem_dropbox.h by camilo on 2024-04-28 00:51 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/component_implementation.h"
#include "apex/filesystem/fs/raw_folder_protocol.h"


namespace fs_raw_folder_protocol_dropbox
{


   // fs::interface - file system interface


   class CLASS_DECL_FILESYSTEM_DROPBOX folder :
      virtual public ::fs::raw_folder_protocol,
      virtual public ::component_implementation
   {
   public:

      ::file::path    m_pathDropbox;
      //::file::path    m_pathLocalFolder;

       //int m_iLastExitCode;


      folder();
      ~folder() override;


      void on_initialize_particle() override;


      ::file::path _base_folder_path() override;

      //::file::path calculate_raw_folder_base_path() override;

      void calculate_installed() override;


      virtual ::file::path dropbox_info_network_payload();

      ::string protocol() override;

      //virtual ::string _dropbox(const ::scoped_string & scopedstr, const ::function < void(const ::scoped_string&) >& callbackStatus);
      //virtual ::string_array_base _dropbox_lines(const ::scoped_string & scopedstr, const ::function < void(const ::scoped_string&) >& callbackStatus);

      //virtual bool check_files(const ::file::path& pathSourceFolder, const ::string_array_base& straSource, const ::function < void(const ::scoped_string&) >& callbackStatus) override;
      //virtual void copy_files_out(const ::file::path& pathTargetFolder, const ::file::path& pathSourceFolder, const ::string_array_base& straSource, const ::function < void(const ::scoped_string&) >& callbackStatus) override;

      //void folder_sync_touch_file(const ::file::path& path, const ::function < void(const ::scoped_string&) >& callbackStatus) override;

      //bool _enumerates(::file::listing_base & listing) override;
      //bool enumerate(::file::listing_base& listing) override;
      // virtual ::file::listing_base & ls_relative_name(::file::listing_base & listing) override;

      //::string_array_base ls(const file::path& pathCloud, const ::function < void(const ::scoped_string&) >& callbackStatus) override;
      //::string_array_base ls_folder(const file::path& pathCloud, const ::function < void(const ::scoped_string&) >& callbackStatus) override;
//#ifdef LINUX
//      
//      void start_daemon(const ::function < void(const ::scoped_string&) >& callbackStatus) override;
//      void sync_exclude(const string_array_base& stra, const ::function < void(const ::scoped_string&) >& callbackStatus) override;
//      void sync_reinclude(const string_array_base& stra, const ::function < void(const ::scoped_string&) >& callbackStatus) override;
//      ::string_array_base sync_exclusion_list(const ::function < void(const ::scoped_string&) >& callbackStatus) override;
//
//#endif

      //bool is_link(const ::file::path& path) override;

      // optional if ls_dir is implemented
      //bool has_subdir(const ::file::path & path) override;


      // bool fast_has_subdir(const ::file::p/*ath& pszPath) override;

//      int is_dir(const ::file::path& path) override;
//      ::file::listing_base& root_ones(::file::listing_base& listing) override;
//
//      bool file_exists(const ::file::path & path) override;
//
//      bool file_move(const ::file::path & pathTarget, const ::file::path & pathSource) override;
//
//      ::file_pointer get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception = nullptr) override;
//

//      ::string non__empty__file_as_string(const ::payload& payloadFile, const ::function < void(const ::scoped_string&) >& callbackStatus = {}) override;
////#if defined(LINUX)
//      void wait_folder_contains_files(const ::file::path& pathTargetFolder, const ::string_array_base& straName, int iMinimumSize, const ::function < void(const ::scoped_string&) >& callbackStatus = {}) override;
////#endif
//
//      void wait_up_and_running(const ::function < void(const ::scoped_string&) >& callbackStatus = {}) override;


      //bool _cloud_defer_check_file_txt(::file::path & pathTarget, const ::file::path & pathCloudFile, bool bForce = false, ::file::path * ppathSource = nullptr, const ::function < void(const ::scoped_string&) >& callbackStatus ={}) override;
      //::string_array_base _cloud_get_file_txt_lines(const ::file::path & pathCloudFile, bool bForce = false, ::file::path * ppathTarget = nullptr, ::file::path * ppathSource = nullptr, const ::function < void(const ::scoped_string&) >& callbackStatus ={}) override;


      //::file::path _cloud_ensure_file_txt_is_up_to_date_and_present(const ::file::path & pathCloudFile, const ::function < void(const ::scoped_string&) >& callbackStatus) override;

      //::file::path _cloud_ensure_files_in_file_txt_are_up_to_date_and_present(
      //     const ::file::path & pathCloudFile, const ::scoped_string& scopedstrFileExtension,
      //     int iMinimumFileSize, const ::function < void(const ::scoped_string&) >& callbackStatus) override;

      //void _cloud_ensure_files_are_up_to_date_and_present(
      //   const ::file::path& pathFolder, const ::string_array_base & stra,
      //   int iMinimumFileSize, const ::function<void(const ::scoped_string&)>& callbackStatus) override;


   };


} // namespace fs_raw_folder_protocol_dropbox



