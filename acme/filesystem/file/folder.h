// Created by camilo on 2021-11-10 10:38 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/filesystem/filesystem/enumerator.h"
#include "acme/primitive/primitive/object.h"
#include "acme/primitive/collection/bool_array.h"


class CLASS_DECL_ACME folder :
   virtual public ::file::enumerator,
   virtual public ::object
{
public:


   filesize             m_iFilePosition;
   ::string             m_strCurrent;
   ::file::enum_type    m_etypeCurrent;


   folder();
   ~folder() override;


   void initialize(::object* pobject) override;


   virtual bool is_reading() const;


   virtual void open_for_reading(file_pointer pfile, int iBufferLevel = 2);


   virtual bool locate_file(const char* pszFileName);
   virtual bool locate_folder(const char* pszFileName);
   virtual ::file_pointer get_file(const char* pszFile = nullptr);
   
   ::file::enum_type type(const char * pszItem = nullptr);

   virtual bool has_sub_folder(const char* pszDir = nullptr);
   virtual void extract(memory& m, const char* pszFile = nullptr);
   virtual bool is_compressed(const char* pszItem = nullptr);

   virtual bool locate(const ::function < bool(const char *) > & function);

   virtual void extract_all(const char* pszTargetDir, ::file::path_array * ppatha = nullptr, string_array* pstraFilter = nullptr, bool_array* pbaBeginsFilterEat = nullptr);


   //bool _enumerates(::file::listing & listing) override;
   bool enumerate(::file::listing& listing) override;


   //bool perform_file_relative_name_listing(::file::listing& listing) override;


   virtual void open_for_writing(file_pointer pfile);


   virtual void add_file(const ::file::path& pszRelative, ::file::file* pfile);


};



