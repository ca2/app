#pragma once


////#include "acme/prototype/prototype/object.h"
#include "programming/real_path.h"


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING script :
      virtual public ::object
   {
   public:


      script_manager *                                   m_pmanager;
      //string                                             m_strName;
      ::file::path                                       m_path;
      memory_file_pointer                                m_pfileError;
      ::write_text_stream                                m_textstreamError;
      string                                             m_strError;
      bool                                               m_bNew;
      ::string_map < programming::real_path >                       m_mapScriptPath;
      ::string_map < programming::real_path >                       m_mapRealPath1;
      ::string_map < ::string_map < programming::real_path > >      m_mapRealPath2;

      script();
      ~script() override;


      void on_initialize_particle() override;

      void destroy() override;


      virtual ::pointer<::dynamic_source::script_instance>create_instance() = 0;

      virtual void run(script_instance * pinstance);

      virtual bool ShouldBuild();

      virtual bool HasCompileOrLinkError();


      virtual programming::real_path get_script_path(const ::scoped_string& scopedstrName);
      virtual programming::real_path real_path2(const ::scoped_string& scopedstrBase, const ::scoped_string& scopedstr);

   };


   template < class T >
   class t_script :
      virtual public script
   {
   public:


      t_script()
      {


      };


      virtual ::pointer<script_instance>create_instance()
      {
         
         return øallocate T();

      }

   };


} // namespace dynamic_source



