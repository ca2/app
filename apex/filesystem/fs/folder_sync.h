// From fs/native.h to fs/folder_sync.h by camilo on 2024-04-28 00:34 <3ThomasBorregaardSorensen!!
#pragma once


#include "data.h"


namespace fs
{
   // fs::interface - file system interface


   class CLASS_DECL_APEX folder_sync :
      virtual public ::fs::data
   {
   public:


      ::file::path m_pathProtocol;
      ::file::path m_pathLocalFolder2;
      class ::time m_timeLastStart;
      class ::time m_timeRestartTimeout;
      class ::time m_timeLastOperation;
      class ::time m_timeOperationThrottlingTime;
      int m_iStableOkCount;


      folder_sync();
      ~folder_sync() override;


      void on_initialize_particle() override;

      virtual void defer_throttle_operation();
      virtual bool has_operation_error();

      virtual ::file::path local_path(const ::file::path& path);


      virtual void folder_sync_touch_file(const ::file::path& path,
                                          const ::function<void(const ::scoped_string&)>& callbackStatus);
      virtual bool check_files(const ::file::path& pathSourceFolder, const ::string_array& straSource,
                               const ::function<void(const ::scoped_string&)>& callbackStatus = {});
      virtual void copy_files_out(const ::file::path& pathTargetFolder, const ::file::path& pathSourceFolder,
                                  const ::string_array& straSource,
                                  const ::function<void(const ::scoped_string&)>& callbackStatus = {});
      virtual ::string non__empty__file_as_string(const ::payload& payloadFile,
                                                  const ::function<void(const ::scoped_string&)>& callbackStatus = {});
      virtual void wait_folder_contains_files(const ::file::path& pathTargetFolder, const ::string_array& straName,
                                              int iMinimumSize,
                                              const ::function<void(const ::scoped_string&)>& callbackStatus = {});


      virtual ::file::path local_folder_path();

      virtual ::string_array ls(const ::file::path& pathCloud, const ::function < void(const ::scoped_string&) >& callbackStatus);
      virtual ::string_array ls_folder(const ::file::path& pathCloud, const ::function < void(const ::scoped_string&) >& callbackStatus);
      virtual void sync_exclude(const ::string_array& stra, const ::function < void(const ::scoped_string&) >& callbackStatus);
      virtual void sync_reinclude(const ::string_array& stra, const ::function < void(const ::scoped_string&) >& callbackStatus);
      virtual ::string_array sync_exclusion_list(const ::function < void(const ::scoped_string&) >& callbackStatus);
      virtual void defer_start_daemon(const ::function < void(const ::scoped_string&) >& callbackStatus);
      virtual void start_daemon(const ::function < void(const ::scoped_string&) >& callbackStatus);


      //bool _enumerates(::file::listing & listing) override;
      bool enumerate(::file::listing& listing) override;
      // virtual ::file::listing & ls_relative_name(::file::listing & listing) override;


      bool is_link(const ::file::path& path) override;

      // optional if ls_dir is implemented
      bool has_subdir(const ::file::path & path) override;


      bool fast_has_subdir(const ::file::path & path) override;

      int is_dir(const ::file::path& path) override;
      ::file::listing& root_ones(::file::listing& listing) override;

      bool file_exists(const ::file::path & path) override;

      bool file_move(const ::file::path & pathTarget, const ::file::path & pathSource) override;

      ::file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen,
                              ::pointer<::file::exception>* ppfileexception = nullptr) override;

      virtual void wait_up_and_running(const ::function<void(const ::scoped_string&)>& callbackStatus = {});


      //      virtual ::file::path _cloud_ensure_file_txt_is_up_to_date_and_present(const ::file::path & pathCloudFile, const ::function < void(const ::scoped_string&) >& callbackStatus);

      virtual bool _cloud_defer_check_file_txt(::file::path& pathTarget, const ::file::path& pathCloudFile,
                                               bool bForce = false, ::file::path* ppathSource = nullptr,
                                               const ::function<void(const ::scoped_string&)>& callbackStatus = {});
      virtual ::string_array _cloud_get_file_txt_lines(const ::file::path& pathCloudFile, bool bForce = false,
                                                       ::file::path* ppathTarget = nullptr,
                                                       ::file::path* ppathSource = nullptr,
                                                       const ::function<void(const ::scoped_string&)>& callbackStatus =
                                                          {});

      virtual ::file::path _cloud_ensure_file_txt_is_up_to_date_and_present(
         const ::file::path& pathCloudFile, const ::function<void(const ::scoped_string&)>& callbackStatus);

      virtual ::file::path _cloud_ensure_files_in_file_txt_are_up_to_date_and_present(
         const ::file::path& pathCloudFile, const ::scoped_string& scopedstrFileExtension,
         int iMinimumFileSize, const ::function<void(const ::scoped_string&)>& callbackStatus);

      virtual void _cloud_ensure_files_are_up_to_date_and_present(
         const ::file::path& pathFolder, const ::string_array & stra,
         int iMinimumFileSize, const ::function<void(const ::scoped_string&)>& callbackStatus);

   };


} // namespace fs



