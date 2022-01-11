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

      __pointer(::factory::factory)                           m_pfactoryRegularExpressionPcre;


      system();
      virtual ~system();


      void common_construct();

      virtual void initialize(::object * pobject) override;

      virtual void on_add_session(::apex::session * papexsession) override;

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



      //virtual void on_request(::create * pcreate) override;




      ::net::email_department &                    email();

      //::xml::department &                          xml();

      ::geo::department &                          geo();

      __pointer(::account::user_set)               userset();


      //virtual __pointer(regex) create_regular_expression(const ::string & pszStyle, const string& str) override;
      //virtual __pointer(regex_context) create_regular_expression_context(const ::string & pszStyle, int iCount) override;


      //virtual void thread_loop() override;

      //virtual void init();

      //virtual void init1();

      //virtual void init2();

      virtual void post_creation_requests() override;

      //virtual void term_system();

      virtual void term2() override;

      virtual void term1() override;

      //virtual void term();

      virtual void TermSystem() override;


      virtual void process_term() override;

      virtual void create_html();

      virtual void defer_create_html();


      void assert_valid() const override;
      void dump(dump_context& action_context) const override;



 
   };


} // namespace axis




