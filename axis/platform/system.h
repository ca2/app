#pragma once


#include "aura/platform/system.h"


namespace axis
{


   class CLASS_DECL_AXIS system:
      virtual public ::aura::system
   {
   public:


      //::pointer<class ::account::user_set>            m_puserset;

      ////::pointer<class ::xml::department>              m_pxml;


      //::pointer<class ::geo::geo>                     m_pgeo;


      //::pointer<::networking::email_department>      m_pemaildepartment;


      //::pointer<::html::html>                        m_phtml;

      //::pointer<::factory::factory>                          m_pfactoryRegularExpressionPcre;


      system();
      ~system() override;


      void common_construct();

      //void on_set_platform() override;

      void on_initialize_particle() override;

      void on_add_session(::platform::session * papexsession) override;

      void init() override;
      void inline_init() override;
      void inline_term() override;

      void init_system() override;
      void term_system() override;

      void term() override;



      void process_init() override;

      void init1() override;

      void init2() override;

      // virtual void defer_xml();


      void verb() override; // ambigous inheritance from ::aura::system/::axis::application



      //virtual void on_request(::request * prequest) override;




      ::networking::email_department *             email() override;

      //::xml::department &                          xml();

      ::geo::geo *                          geo() override;

      ::pointer<::account::user_set>              userset() override;


      //virtual ::pointer<regex>create_regular_expression(const ::scoped_string & scopedstrStyle, const ::scoped_string & scopedstr) override;
      //virtual ::pointer<regex_context>create_regular_expression_context(const ::scoped_string & scopedstrStyle, int iCount) override;


      //virtual void thread_loop() override;

      //virtual void init();

      //virtual void init1();

      //virtual void init2();

      //virtual void post_pending_requests() override;

      //virtual void term_system();

      void term2() override;

      void term1() override;

      //virtual void term();

      void TermSystem() override;


      void process_term() override;

      void create_html() override;

      void defer_create_html() override;


      // void assert_ok() const override;
      //void dump(dump_context& action_context) const override;



 
   };


} // namespace axis




