#pragma once


#include "acme/parallelization/task.h"


namespace acme
{


   class CLASS_DECL_ACME context :
      virtual public ::task
   {
   public:


      ::acme::application *                           m_pacmeapplication;
      ::apex::application *                           m_papexapplication;
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

      ::pointer<::text::translator>                   m_ptexttranslator;

      ::pointer<::context_image>                      m_pcontextimage;
      ::pointer<::dir_context>                        m_pdir;
      ::pointer<::file_context>                       m_pfile;



      context();
      ~context() override;


      void initialize(::particle * pparticle) override;

      virtual void initialize_context();

      virtual void initialize_context_1();


      inline ::context_image* context_image() { return m_pcontextimage; }



      virtual void translate_text_data(::text::data * ptextdata);
      virtual ::text::text __text(const ::atom& atom) override;


      inline ::acme_file * acmefile();
      inline ::acme_path * acmepath();
      inline ::acme_directory * acmedirectory();
      inline ::acme::node * acmenode();
      inline ::acme::system * acmesystem() { return m_pacmesystem; }

      inline ::dir_context * dir() { return m_pdir; }
      inline ::file_context * file() { return m_pfile; }
      ::dir_system * dirsystem();
      ::file_system * filesystem();




      virtual ::payload file_payload(const ::payload & payloadFile);


      //::file_pointer get_file(const ::payload& payloadFile, const ::file::e_open& eopen) override;


      virtual ::file::path defer_process_path(::file::path path);


   };

   
} // namespace acme



