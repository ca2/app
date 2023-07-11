// Create on 2021-03-21 00:11 <3ThomasBS_
#pragma once


class CLASS_DECL_ACME acme_path :
   virtual public particle
{
public:


   ::IDENTIFIER_SUFFIX_OPERATING_SYSTEM(acme_)::acme_path *    m_pplatformpath;
   ::acme_directory *                                          m_pacmedirectory;
   ::acme_file *                                               m_pacmefile;


   acme_path();
   ~acme_path() override;



   virtual  string from(string str);

   virtual void safe_real_path(::file::path & path);

   virtual ::file::path safe_get_real_path(const ::file::path & path);

   virtual ::file::path _safe_real_path(const ::file::path & path);

   virtual ::file::path real_path(const ::file::path & path);

   virtual ::file::path _real_path(const ::file::path & path);



   virtual bool case_insensitive_real_path_begins_eat(string & str, const ::scoped_string & scopedstrPrefix);

   virtual bool real_path_is_same(const ::file::path & path1, const ::file::path & path2);

   virtual ::file::enum_type get_type(const ::file::path & path);

   virtual ::file::enum_type safe_get_type(const ::file::path & path);

   virtual void create_symbolic_link(const ::scoped_string & scopedstrLink, const ::scoped_string & scopedstrSource);

   virtual bool is_symbolic_link(const ::scoped_string & scopedstrLink);

   virtual ::file::path symbolic_link_destination(const ::scoped_string & scopedstrLink);



   virtual bool has_custom_icon(const ::file::path & path);


   ::file::path defer_process_relative_path(const ::file::path & path, const ::file::path & pathFolder = "");

   
   virtual ::file::path get_absolute_path(const ::scoped_string & scopedstr);


};



