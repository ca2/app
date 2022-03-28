// Create on 2021-03-21 00:11 <3ThomasBS_
#pragma once


class CLASS_DECL_ACME acme_path :
   virtual public matter
{
public:


   ::OPERATING_SYSTEM_NAMESPACE::acme_path *   m_pplatformpath;


   acme_directory *                          m_pacmedirectory;
   acme_file *                         m_pacmefile;


   acme_path();
   ~acme_path() override;



   virtual  string from(string str);



   virtual ::file::path final(const char * path);

   virtual ::file::path _final(const char * path);



   virtual bool final_begins_eat_ci(string & str, const char * pcszPrefix);

   virtual bool final_is_same(const char * path1, const char * path2);

   virtual ::file::enum_type get_type(const char * path);



   virtual void create_symbolic_link(const char * pszLink, const char * pszSource);

   virtual bool is_symbolic_link(const char * pszLink);

   virtual ::file::path symbolic_link_destination(const char * pszLink);



   virtual bool has_custom_icon(const char * path);


   ::file::path defer_process_relative_path(const ::file::path & path);

   

};



