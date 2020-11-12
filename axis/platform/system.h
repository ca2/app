#pragma once


namespace axis
{


   class CLASS_DECL_AXIS system:
      virtual public ::aura::system
   {
   public:


      __composite(class ::account::user_set)            m_puserset;

      __composite(class ::xml::department)              m_pxml;


      __composite(class ::geo::department)              m_pgeo;


      __composite(::net::email_department)              m_pemaildepartment;


      __composite(::html::html)                         m_phtml;


      system();
      virtual ~system();


      void common_construct();

      virtual ::estatus initialize(::layered * pobjectContext) override;

      virtual ::estatus init() override;
      virtual ::estatus inline_init() override;
      virtual ::estatus inline_term() override;

      virtual ::estatus init_system() override;
      virtual void term_system() override;

      virtual void term() override;



      virtual ::estatus process_init() override;

      virtual ::estatus init1() override;

      virtual ::estatus init2() override;

      // virtual ::estatus defer_xml();


      virtual ::estatus verb() override; // ambigous inheritance from ::aura::system/::axis::application



      virtual void on_request(::create * pcreate) override;




      ::net::email_department &                    email();

      ::xml::department &                          xml();

      ::geo::department &                          geo();

      __pointer(::account::user_set)               userset();


      virtual __pointer(regex) create_regular_expression(const char* pszStyle, const string& str) override;
      virtual __pointer(regex_context) create_regular_expression_context(const char* pszStyle, int iCount) override;

      virtual __pointer(regex) create_pcre(const string& str);
      virtual __pointer(regex_context) create_pcre_context(int iCount);
      virtual int pcre_add_tokens(string_array& stra, const string& strTopic, const string& strRegexp, int nCount);



      //virtual ::estatus thread_loop() override;

      //virtual ::estatus init();

      //virtual ::estatus init1();

      //virtual ::estatus init2();

      virtual ::estatus post_create_requests() override;

      //virtual void term_system();

      virtual void term2() override;

      virtual void term1() override;

      //virtual void term();

      virtual void TermSystem() override;


      virtual void process_term() override;

      virtual ::estatus create_html();

      virtual ::estatus defer_create_html();


      void assert_valid() const override;
      void dump(dump_context& action_context) const override;



 
   };


} // namespace axis




