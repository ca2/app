#pragma once


#include "unzip.h"
#include "zip.h"
#include "acme/filesystem/file/folder.h"


namespace folder_zip
{


   class CLASS_DECL_FOLDER_ZIP folder :
      virtual public ::folder
   {
   public:


      file_pointer            m_pfile;
      file_pointer            m_pbuffile1;
      file_pointer            m_pbuffile2;
      unzFile                 m_unzfile;
      zipFile                 m_zipfile;
      bool                    m_bOwnFile;
      unz_file_info           m_unzfileinfo;


      folder();
      ~folder() override;


      void initialize(::particle * pparticle) override;


      void open_for_reading(file_pointer pfile, int iBufferLevel = 2) override;

      bool locate_file(const ::file::path & path) override;

      bool locate_folder(const ::file::path & path) override;

      bool locate(const ::function < bool(const char*) >& function) override;

      bool has_sub_folder(const ::file::path & pathFolder = nullptr) override;

      void extract(memory& m, const ::file::path & pathFile = nullptr) override;

      bool is_compressed(const ::file::path & pathItem = nullptr) override;

      class ::time get_modification_time() const;

      ::file_pointer get_file(const ::file::path & pathFile) override;

      ::file_pointer get_file() override;

      void e_extract_all(const ::file::path& pathTargetDir, ::file::path_array* ppatha, string_array* pstraFilter, bool_array* pbaBeginsFilterEat, ::function<bool(const::scoped_string& scopedstr) > functionCallback = {}) override;
      ::file::path e_extract_first_ends(const ::file::path& pathTargetDir, const ::scoped_string& scopedstr) override;


      void open_for_writing(file_pointer pfile) override;


      void add_file(const ::file::path & pathRelative, ::file::file * pfile) override;


      bool enumerate(::file::listing& listing) override;
      //bool perform_file_relative_name_listing(::file::listing& listing) override;



   };


} // namespace folder_zip




