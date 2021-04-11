#pragma once


namespace acme
{


   class CLASS_DECL_ACME context :
      virtual public ::object
   {
   public:


      ::apex::context *                               m_papexcontext;
      ::aura::context *                               m_pauracontext;
      ::apex::application *                           m_papexapplication;
      ::aqua::application *                           m_paquaapplication;
      ::aura::application *                           m_pauraapplication;
      ::axis::application *                           m_paxisapplication;
      ::base::application *                           m_pbaseapplication;
      ::bred::application *                           m_pbredapplication;
      ::core::application *                           m_pcoreapplication;
      ::apex::session *                               m_papexsession;
      ::aqua::session *                               m_paquasession;
      ::aura::session *                               m_paurasession;
      ::axis::session *                               m_paxissession;
      ::base::session *                               m_pbasesession;
      ::bred::session *                               m_pbredsession;
      ::core::session *                               m_pcoresession;
      ::acme::system *                                m_pacmesystem;
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
      virtual ~context();


      inline ::context_image* context_image() { return m_pcontextimage; }


      virtual ::e_status initialize_context();

      virtual void translate_text_data(::text::data * ptextdata);
      virtual ::text::text __text(const ::id& id);


      virtual ::payload file_payload(const ::payload & payloadFile);


      ::file_result get_file(const ::payload& varFile, const ::file::e_open& eopen) override;




   };

   
} // namespace acme



