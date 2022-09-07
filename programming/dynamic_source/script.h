#pragma once


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING script :
      virtual public ::object
   {
   public:


      __pointer(script_manager)                 m_pmanager;
      string                                    m_strName;
      memory_file_pointer                       m_pfileError;
      ::text_stream                             m_streamError;
      string                                    m_strError;
      bool                                      m_bNew;


      script();
      ~script() override;


      void on_initialize_object() override;


      virtual __pointer(::dynamic_source::script_instance) create_instance() = 0;

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


      virtual __pointer(script_instance) create_instance()
      {
         
         return __new(T());

      }

   };


} // namespace dynamic_source



