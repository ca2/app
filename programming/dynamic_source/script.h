#pragma once


////#include "acme/primitive/primitive/object.h"


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING script :
      virtual public ::object
   {
   public:


      ::pointer<script_manager>                 m_pmanager;
      string                                    m_strName;
      memory_file_pointer                       m_pfileError;
      ::write_text_stream                       m_textstreamError;
      string                                    m_strError;
      bool                                      m_bNew;


      script();
      ~script() override;


      void on_initialize_particle() override;


      virtual ::pointer<::dynamic_source::script_instance>create_instance() = 0;

      virtual void run(script_instance * pinstance);

      virtual bool ShouldBuild();

      virtual bool HasCompileOrLinkError();


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
         
         return __new(T());

      }

   };


} // namespace dynamic_source



