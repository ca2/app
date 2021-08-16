// Create on 2021-03-21 00:11 <3ThomasBS_
#pragma once


class CLASS_DECL_ACME acme_path :
   virtual public matter
{
public:


   ::PLATFORM_NAMESPACE::acme_path *   m_pplatformpath;


   acme_dir *                          m_pacmedir;
   acme_file *                         m_pacmefile;


   acme_path();
   ~acme_path() override;



   virtual  string from(string str);

   //virtual ::file::path app_module();
   //virtual ::file::path ca2_module();

   virtual ::file::path final(const char * path);

   virtual ::file::path _final(const char * path);

   virtual bool final_begins_eat_ci(string & str, const char * pcszPrefix);

   virtual bool final_is_same(const char * path1, const char * path2);

   virtual bool is_file_or_dir(const char * path, ::file::enum_type * petype);

   //virtual bool is_link(const char * path);


};



