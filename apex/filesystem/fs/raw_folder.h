// From fs/native by camilo on 2025-03-10 20:22 <3ThomasBorregaardSorensen!!
#pragma once


#include "data.h"


namespace fs
{


   class CLASS_DECL_APEX raw_folder :
      virtual public ::fs::data
   {
   public:

      
      //::file::path      m_pathFolder;
      bool              m_bInstalled;
      bool              m_bCalculatedInstalled;


      raw_folder();
      ~raw_folder() override;


      void on_initialize_particle() override;


      virtual void calculate_installed();

      virtual bool is_installed();


      virtual ::file::path raw_path(const ::file::path & path);


      virtual ::file::path base_folder_path();

      virtual ::file::path _base_folder_path();


      //bool _enumerates(::file::listing & listing) override;
      bool enumerate(::file::listing & listing) override;
      // virtual ::file::listing & ls_relative_name(::file::listing & listing) override;


      bool is_link(const ::file::path & path) override;

      // optional if ls_dir is implemented
      bool has_subdir(const ::file::path & pszPath) override;


      bool fast_has_subdir(const ::file::path & pszPath) override;

      int is_dir(const ::file::path & path) override;
      ::file::listing & root_ones(::file::listing & listing) override;

      bool file_exists(const ::file::path & pszPath) override;

      bool file_move(const ::file::path & pszDst, const ::file::path & pszSrc) override;

      file_pointer get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception > * ppfileexception = nullptr) override;


   };


} // namespace fs



