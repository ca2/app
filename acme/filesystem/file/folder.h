// Created by camilo on 2021-11-10 10:38 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/filesystem/filesystem/enumerator.h"
////#include "acme/primitive/primitive/object.h"
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


   void initialize(::particle * pparticle) override;


   virtual bool is_reading() const;


   virtual void open_for_reading(file_pointer pfile, int iBufferLevel = 2);


   virtual bool locate_file(const scoped_string & strFileName);
   virtual bool locate_folder(const scoped_string & strFileName);
   virtual ::file_pointer get_file(const scoped_string & strFile = nullptr);
   
   ::file::enum_type type(const scoped_string & strItem = nullptr);

   virtual bool has_sub_folder(const scoped_string & strDir = nullptr);
   virtual void extract(memory& m, const scoped_string & strFile = nullptr);
   virtual bool is_compressed(const scoped_string & strItem = nullptr);

   virtual bool locate(const ::function < bool(const char *) > & function);

   virtual void e_extract_all(const scoped_string & strTargetDir, ::file::path_array * ppatha = nullptr, string_array* pstraFilter = nullptr, bool_array* pbaBeginsFilterEat = nullptr);


   //bool _enumerates(::file::listing & listing) override;
   bool enumerate(::file::listing& listing) override;


   //bool perform_file_relative_name_listing(::file::listing& listing) override;


   virtual void open_for_writing(file_pointer pfile);


   virtual void add_file(const ::file::path& pszRelative, ::file::file* pfile);


};



