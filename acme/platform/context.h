#pragma once


#include "acme/parallelization/task.h"


namespace acme
{


   class CLASS_DECL_ACME context :
      virtual public ::task
   {
   public:


      ::apex::context *                               m_papexcontext;
      ::aura::context *                               m_pauracontext;


      ::acme::application*                            m_pacmeapplication;
      ::acme::session *                               m_pacmesession;
      ::acme::system *                                m_pacmesystem;
      ::acme::node *                                  m_pacmenode;

      ::pointer<::text::translator>                   m_ptexttranslator;

      ::pointer<::context_image>                      m_pcontextimage;
      ::pointer<::dir_context>                        m_pdir;
      ::pointer<::file_context>                       m_pfile;

      ::pointer < ::os_context >                      m_poscontext;


      string                              m_strLocale;
      string                              m_strSchema;


      context();
      ~context() override;


      void initialize(::particle * pparticle) override;

      virtual void initialize_context();

      virtual void initialize_context_1();


      inline ::context_image* context_image() { return m_pcontextimage; }



      virtual void translate_text_data(::text::data * ptextdata);
      virtual ::text::text __text(const ::atom& atom) override;


      ::acme_file * acmefile();
      ::acme_path * acmepath();
      ::acme_directory * acmedirectory();
      ::acme::node * acmenode();
      inline ::acme::system * acmesystem() { return m_pacmesystem; }


      inline ::os_context* os_context() { return m_poscontext; }


      inline ::dir_context * dir() { return m_pdir; }
      inline ::file_context * file() { return m_pfile; }
      ::dir_system * dirsystem();
      ::file_system * filesystem();


      virtual ::payload file_payload(const ::payload & payloadFile);


      //::file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen) override;


      virtual ::file::path defer_process_path(::file::path path);

      virtual void fork_count(::count iCount, const ::function < void(index, index, index, index) > & function, const ::procedure & procedureCompletion, index iStart = 0);


   };

   
} // namespace acme



