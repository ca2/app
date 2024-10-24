#pragma once


#include "aura/platform/system.h"


namespace axis
{


   class CLASS_DECL_AXIS system:
      virtual public ::aura::system
   {
   public:


      ::pointer<class ::account::user_set>            m_puserset;

      //::pointer<class ::xml::department>              m_pxml;


      ::pointer<class ::geo::geo>                     m_pgeo;


      ::pointer<::networking::email_department>      m_pemaildepartment;


      ::pointer<::html::html>                        m_phtml;

      ::pointer<::factory::factory>                          m_pfactoryRegularExpressionPcre;


      system();
      ~system() override;


      void common_construct();

      void on_set_platform() override;

      void on_initialize_particle() override;

      void on_add_session(::platform::session * papexsession) override;

      virtual void init() override;
      virtual void inline_init() override;
      virtual void inline_term() override;

      virtual void init_system() override;
      virtual void term_system() override;

      virtual void term() override;



      virtual void process_init() override;

      virtual void init1() override;

      virtual void init2() override;

      // virtual void defer_xml();


      virtual void verb() override; // ambigous inheritance from ::aura::system/::axis::application



      //virtual void on_request(::request * prequest) override;




      ::networking::email_department &             email();

      //::xml::department &                          xml();

      ::geo::geo *                          geo();

      ::pointer<::account::user_set>              userset();


      //virtual ::pointer<regex>create_regular_expression(const ::string & pszStyle, const string& str) override;
      //virtual ::pointer<regex_context>create_regular_expression_context(const ::string & pszStyle, int iCount) override;


      //virtual void thread_loop() override;

      //virtual void init();

      //virtual void init1();

      //virtual void init2();

      //virtual void post_pending_requests() override;

      //virtual void term_system();

      virtual void term2() override;

      virtual void term1() override;

      //virtual void term();

      virtual void TermSystem() override;


      virtual void process_term() override;

      virtual void create_html();

      virtual void defer_create_html();


      // void assert_ok() const override;
      //void dump(dump_context& action_context) const override;



 
   };


} // namespace axis




