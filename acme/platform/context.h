#pragma once


namespace acme
{


   class CLASS_DECL_ACME context :
      virtual public ::task
   {
   public:


      ::app *                                         m_papp;
      ::application *                                 m_papplication;
      ::aqua::application *                           m_paquaapplication;
      ::aura::application *                           m_pauraapplication;
      ::axis::application *                           m_paxisapplication;
      ::base::application *                           m_pbaseapplication;
      ::bred::application *                           m_pbredapplication;
      ::core::application *                           m_pcoreapplication;
      ::apex::context *                               m_papexcontext;
      ::aura::context *                               m_pauracontext;
      ::apex::session *                               m_papexsession;
      ::aqua::session *                               m_paquasession;
      ::aura::session *                               m_paurasession;
      ::axis::session *                               m_paxissession;
      ::base::session *                               m_pbasesession;
      ::bred::session *                               m_pbredsession;
      ::core::session *                               m_pcoresession;
      class ::system *                                m_pacmesystem;
      ::apex::system *                                m_papexsystem;
      ::aqua::system *                                m_paquasystem;
      ::aura::system *                                m_paurasystem;
      ::axis::system *                                m_paxissystem;
      ::base::system *                                m_pbasesystem;
      ::bred::system *                                m_pbredsystem;
      ::core::system *                                m_pcoresystem;
      ::acme::node *                                  m_pacmenode;
      ::apex::node *                                  m_papexnode;
      ::aura::node *                                  m_pauranode;

      __pointer(::text::translator)                   m_ptexttranslator;

      __composite(::context_image)                    m_pcontextimage;


      context();
      ~context() override;


      inline ::context_image* context_image() { return m_pcontextimage; }


      virtual void initialize_context();

      virtual void translate_text_data(::text::data * ptextdata);
      virtual ::text::text __text(const ::atom& atom) override;


      virtual ::payload file_payload(const ::payload & payloadFile);


      ::file_pointer get_file(const ::payload& payloadFile, const ::file::e_open& eopen) override;


      virtual ::file::path defer_process_path(::file::path path);


   };

   
} // namespace acme



