// Created by camilo on 2021-11-10 10:38 BRT <3ThomasBorregaardSørensen!!
#pragma once


class CLASS_DECL_ACME folder :
   virtual public ::file::listing_provider,
   virtual public ::object
{
public:


   filesize             m_iFilePosition;
   ::string             m_strCurrent;
   ::file::enum_type    m_etypeCurrent;


   folder();
   ~folder() override;


   ::e_status initialize(::object* pobject) override;


   virtual bool is_reading() const;


   virtual ::e_status open_for_reading(file_pointer pfile, int iBufferLevel = 2);


   virtual bool locate(const char* pszFileName);
   virtual ::file_transport get_file(const char* pszFile = nullptr);
   inline ::file::enum_type type(const char* pszItem = nullptr)
   {

      if (::is_set(pszItem)) locate(pszItem);

      return m_etypeCurrent;

   }
   virtual bool has_sub_folder(const char* pszDir = nullptr);
   virtual ::e_status extract(memory& m, const char* pszFile = nullptr);
   virtual bool is_compressed(const char* pszItem = nullptr);


   virtual ::e_status extract_all(const char* pszTargetDir, const char * pszSourceDir = nullptr, ::file::patha* ppatha = nullptr, string_array* pstraFilter = nullptr, bool_array* pbaBeginsFilterEat = nullptr);


   ::file::listing& perform_file_listing(::file::listing& listing) override;
   ::file::listing& perform_file_relative_name_listing(::file::listing& listing) override;


   virtual ::e_status open_for_writing(file_pointer pfile);


   virtual void add_file(const ::file::path& pszRelative, ::file::file* pfile);


};



