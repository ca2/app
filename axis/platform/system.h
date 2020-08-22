#pragma once


namespace axis
{


   class CLASS_DECL_AXIS system:
      virtual public ::aura::system
   {
   public:


      __composite(class ::account::user_set)             m_puserset;

      __composite(class ::xml::department)               m_pxml;


      __composite(class ::geo::department)               m_pgeo;


      __composite(::net::email_department)               m_pemaildepartment;


      system();
      virtual ~system();


      void common_construct();

      virtual ::estatus  initialize_system(::object * pobjectContext, app_core * pappcore);

      virtual ::estatus init();
      virtual ::estatus inline_init() override;
      virtual ::estatus inline_term() override;

      virtual ::estatus init_system();
      virtual void term_system();

      virtual void term();



      virtual ::estatus process_init();

      virtual ::estatus init1();

      virtual ::estatus init2();

      virtual ::estatus defer_xml();


      virtual ::estatus verb() override; // ambigous inheritance from ::aura::system/::axis::application



      virtual void on_request(::create * pcreate) override;




      ::net::email_department &                    email();

      ::xml::department &                          xml();

      ::geo::department &                          geo();

      __pointer(::account::user_set)               userset();


      virtual __pointer(regex) create_regular_expression(const char* pszStyle, const string& str);
      virtual __pointer(regex_context) create_regular_expression_context(const char* pszStyle, int iCount);

      virtual __pointer(regex) create_pcre(const string& str);
      virtual __pointer(regex_context) create_pcre_context(int iCount);
      virtual int pcre_add_tokens(string_array& stra, const string& strTopic, const string& strRegexp, int nCount);



      //virtual ::estatus thread_loop() override;

      //virtual ::estatus init();

      //virtual ::estatus init1();

      //virtual ::estatus init2();

      virtual ::estatus initial_check_directrix();

      //virtual void term_system();

      virtual void term2();

      virtual void term1();

      //virtual void term();

      virtual void TermApplication();


      virtual void process_term();




      void assert_valid() const override;
      void dump(dump_context& action_context) const override;



 
   };


} // namespace axis




