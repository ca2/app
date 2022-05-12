#pragma once


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


      void initialize(::object* pobject) override;


      void open_for_reading(file_pointer pfile, int iBufferLevel = 2) override;

      bool locate_file(const char* pszFileName) override;

      bool locate_folder(const char* pszFileName) override;

      bool locate(const ::function < bool(const char*) >& function) override;

      bool has_sub_folder(const char* pszDir = nullptr) override;

      void extract(memory& m, const char* pszFile = nullptr) override;

      bool is_compressed(const char* pszItem = nullptr) override;

      ::file_pointer get_file(const char* pszFile = nullptr) override;

      void extract_all(const char* pszTargetDir, ::file::path_array* ppatha, string_array* pstraFilter, bool_array* pbaBeginsFilterEat) override;

      void open_for_writing(file_pointer pfile) override;


      void add_file(const ::file::path & pathRelative, ::file::file * pfile) override;


      bool enumerate(::file::listing& listing) override;
      //bool perform_file_relative_name_listing(::file::listing& listing) override;



   };


} // namespace folder_zip




