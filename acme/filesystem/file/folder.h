// Created by camilo on 2021-11-10 10:38 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/filesystem/enumerator.h"
////#include "acme/prototype/prototype/object.h"
#include "acme/prototype/collection/bool_array.h"


class CLASS_DECL_ACME folder :
   virtual public ::file::enumerator,
   virtual public ::object
{
public:


   filesize             m_iFilePosition;
   ::string             m_strCurrent;
   ::file::enum_type    m_etypeCurrent;
   int                  m_iConsumeFromPathBeginningWhenExtracting;


   folder();
   ~folder() override;


   void initialize(::particle * pparticle) override;


   virtual bool is_reading() const;


   virtual void open_for_reading(file_pointer pfile, int iBufferLevel = 2);


   virtual bool locate_file(const ::file::path & path);
   virtual bool locate_folder(const ::file::path & path);
   virtual ::file_pointer get_file();
   virtual ::file_pointer get_file(const ::file::path & pathFile);
   
   ::file::enum_type type(const ::file::path & pathItem = nullptr);

   virtual bool has_sub_folder(const ::file::path & pathFolder = nullptr);
   virtual void extract(memory& m, const ::file::path & pathFile = nullptr);
   virtual bool is_compressed(const ::file::path & pathItem = nullptr);

   virtual bool locate(const ::function < bool(const_char_pointer )> & function);

   virtual void e_extract_all(const ::file::path & pathTargetDir, ::file::path_array * ppatha = nullptr, string_array* pstraFilter = nullptr, bool_array* pbaBeginsFilterEat = nullptr, ::function<bool(const::scoped_string& scopedstr) > functionCallback = {});
   virtual ::file::path e_extract_first_ends(const ::file::path& pathTargetDir, const ::scoped_string & scopedstr);

   //bool _enumerates(::file::listing & listing) override;
   bool enumerate(::file::listing& listing) override;


   //bool perform_file_relative_name_listing(::file::listing& listing) override;


   virtual void open_for_writing(file_pointer pfile);


   virtual void add_file(const ::file::path & pathRelative, ::file::file* pfile);


};



