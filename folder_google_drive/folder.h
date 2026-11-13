#pragma once
#include "acme/filesystem/file/folder.h"
#include "apex/filesystem/fs/data.h"
#include "apex/platform/api_client.h"

namespace folder_google_drive
{
   // Drive folder provider. File contents are read-only; URI components are Drive IDs.
   class CLASS_DECL_FOLDER_GOOGLE_DRIVE folder :
      virtual public ::folder,
      virtual public ::fs::data
   {
   public:
      ::pointer < ::api_client > m_papiclient;
      ::pointer < ::api_client > m_papiclientWrite;
      ::file::path m_pathContent;
      ::file::path m_pathMetadata;

      ~folder() override;
      void initialize(::particle * pparticle) override;
      ::string file_id(const ::file::path & path);
      ::payload request(const ::scoped_string & scopedstrUrl);
      ::payload api_request(::api_client * pclient, const ::scoped_string & scopedstrUrl, ::property_set & set);
      ::file::path create_folder(const ::file::path & pathParent, const ::scoped_string & scopedstrName) override;
      ::payload metadata(const ::file::path & path);
      bool enumerate(::file::listing_base & listing) override;
      ::file::listing_base & root_ones(::file::listing_base & listing) override;
      ::file::e_type file_type(const ::file::path & path) override;
      ::i32 is_dir(const ::file::path & path) override;
      bool file_exists(const ::file::path & path) override;
      ::payload file_length(const ::file::path & path) override;
      bool has_subdir(const ::file::path & path) override;
      bool fast_has_subdir(const ::file::path & path) override;
      bool locate_file(const ::file::path & path) override;
      bool locate_folder(const ::file::path & path) override;
      bool has_sub_folder(const ::file::path & path = nullptr) override;
      bool is_compressed(const ::file::path & path = nullptr) override;
      ::file_pointer get_file(const ::file::path & path) override;
      ::file_pointer get_file() override;
      ::file_pointer get_file(const ::payload & payloadFile, ::file::e_open eopen,
         ::pointer < ::file::exception > * pexception = nullptr) override;
      void extract(::memory & memory, const ::file::path & path = nullptr) override;
   };
}
