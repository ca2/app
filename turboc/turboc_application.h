#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC application:
      virtual public ::sphere::application
   {
   public:
      enum enum_type
      {

         type_normal,
         type_mili,

      };


      enum_type                                 m_etype;


      string                                 m_strTurboC;
      string                                 m_strAlternateTurboC;

      bool                                   m_bMultiverseChat;


      ::user::single_document_template *     m_ptemplateHelloMultiverseMain;
      ::user::single_document_template *     m_ptemplateHelloMultiverseView;
      ::user::single_document_template *     m_ptemplateHelloMultiverseSwitcher;

      ::mutex                                  m_mutexAiFont;

      i32                                m_iErrorAiFont;
      bool                                   m_bLoadAiFont;
      void *                                 m_faceAi;

      action_context *                              m_pcontext;

      ::turboc::main *                       m_pmain;

      PFN_MAIN                               m_pfnmainMain;


      application(::object * pobject);
      virtual ~application();


      virtual bool initialize_application();


      virtual bool start_main();
      virtual bool start_main(PFN_MAIN pfnMain);







      virtual i32  exit_application() override;

      virtual void on_request(::create * pcreate);

      static ::u32 thread_proc_load_ai_font(void * pparam);
      virtual void load_ai_font();

   };


} // namespace userstack




