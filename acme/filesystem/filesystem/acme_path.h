// Create on 2021-03-21 00:11 <3ThomasBS_
#pragma once


#include "acme/primitive/primitive/particle.h"


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



   virtual ::file::path final(const char * path);

   virtual ::file::path _final(const char * path);



   virtual bool final_begins_eat_ci(string & str, const char * pcszPrefix);

   virtual bool final_is_same(const char * path1, const char * path2);

   virtual ::file::enum_type get_type(const char * path);



   virtual void create_symbolic_link(const scoped_string & strLink, const scoped_string & strSource);

   virtual bool is_symbolic_link(const scoped_string & strLink);

   virtual ::file::path symbolic_link_destination(const scoped_string & strLink);



   virtual bool has_custom_icon(const char * path);


   ::file::path defer_process_relative_path(const ::file::path & path);

   

};



