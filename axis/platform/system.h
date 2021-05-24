#pragma once


namespace axis
{


   class CLASS_DECL_AXIS system:
      virtual public ::aura::system
   {
   public:


      __composite(class ::account::user_set)            m_puserset;

      //__composite(class ::xml::department)              m_pxml;


      __composite(class ::geo::department)              m_pgeo;


      __composite(::net::email_department)              m_pemaildepartment;


      __composite(::html::html)                         m_phtml;

      __pointer(::factory_map)                           m_pfactorymapRegularExpressionPcre;


      system();
      virtual ~system();


      void common_construct();

      virtual ::e_status initialize(::object * pobject) override;

      virtual void on_add_session(::apex::session * papexsession) override;

      virtual ::e_status init() override;
      virtual ::e_status inline_init() override;
      virtual ::e_status inline_term() override;

      virtual ::e_status init_system() override;
      virtual void term_system() override;

      virtual void term() override;



      virtual ::e_status process_init() override;

      virtual ::e_status init1() override;

      virtual ::e_status init2() override;

      // virtual ::e_status defer_xml();


      virtual ::e_status verb() override; // ambigous inheritance from ::aura::system/::axis::application



      //virtual void on_request(::create * pcreate) override;




      ::net::email_department &                    email();

      //::xml::department &                          xml();

      ::geo::department &                          geo();

      __pointer(::account::user_set)               userset();


      //virtual __pointer(regex) create_regular_expression(const char* pszStyle, const string& str) override;
      //virtual __pointer(regex_context) create_regular_expression_context(const char* pszStyle, int iCount) override;


      //virtual ::e_status thread_loop() override;

      //virtual ::e_status init();

      //virtual ::e_status init1();

      //virtual ::e_status init2();

      virtual ::e_status post_creation_requests() override;

      //virtual void term_system();

      virtual void term2() override;

      virtual void term1() override;

      //virtual void term();

      virtual void TermSystem() override;


      virtual void process_term() override;

      virtual ::e_status create_html();

      virtual ::e_status defer_create_html();


      void assert_valid() const override;
      void dump(dump_context& action_context) const override;



 
   };


} // namespace axis




