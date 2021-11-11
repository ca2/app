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


      ::e_status initialize(::object* pobject) override;


      ::e_status open_for_reading(file_pointer pfile, int iBufferLevel = 2) override;

      bool locate(const char* pszFileName) override;

      bool has_sub_folder(const char* pszDir = nullptr) override;

      ::e_status extract(memory& m, const char* pszFile = nullptr) override;

      bool is_compressed(const char* pszItem = nullptr) override;

      ::file_transport get_file(const char* pszFile = nullptr) override;

      ::e_status extract_all(const char* pszTargetDir, const char* pszSourceDir, ::file::patha* ppatha, string_array* pstraFilter, bool_array* pbaBeginsFilterEat) override;

      ::e_status open_for_writing(file_pointer pfile) override;


      //void write_to_file(file_pointer  pfile, const widechar * pcsz);

      virtual void add_file(const ::file::path& pszRelative, ::file::file* pfile);


      ::file::listing& perform_file_listing(::file::listing& listing) override;
      ::file::listing& perform_file_relative_name_listing(::file::listing& listing) override;



   };


} // namespace folder_zip




