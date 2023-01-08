#pragma once


#include "apex/filesystem/file/html_file.h"


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING script_interface :
      virtual public ::html_file
   {
   public:


      ::netnode::script_interface *       m_pnetnodescriptinterface;
      ::netnode::script_impl *            m_pnetnodescriptimpl;

      string                              m_strNote;

      ::pointer<script_main>             m_pmain;
      ::pointer<script_interface>        m_pinstanceParent2;
      ::pointer<script>                  m_pscript2;


      i32                                 m_iDebug;

      ::payload                           m_varRet;

      string                              m_strDebugRequestUri;
      string                              m_strDebugThisScript;


      script_interface();
      ~script_interface() override;

      virtual const char* debug_note() const override;

      virtual void initialize(::particle * pparticle) override;
      virtual void init1();

      //void destroy() override;

      void destroy() override;
      virtual void     run() override;


      virtual void dinit();
      virtual void dprint(const ::string &);
      virtual void dprint_recursive(const ::payload & payload);


      property_set& inattra();


      //virtual property & get(const ::string & pszKey);




      virtual ::file::file * output_file();


      virtual void on_initialize();
      //virtual void initialize_dynamic_source_script_interface(script_interface * pinterfaceMain, script_interface * pinterfaceParent, httpd_socket * pdssocket, script_manager * pmanager);

      script_main * main() { return m_pmain; }
      script_interface * parent() { return m_pinstanceParent2; }
      httpd_socket* netnodesocket();
      script_manager* manager();


      virtual void set_session_payload(const ::atom & atom, const ::payload & payload);
      virtual ::payload get_session_payload(const ::atom & atom);
      virtual ::atom session_id(const ::atom & atom = nullptr);

      virtual string get_auth_email();
      virtual void set_auth_email(const string & strEmail);
      virtual void auth(const string& strAuth);
      
      ::payload run_script();


      virtual bool rerun();


      void current_url(string& strUrl);



      virtual void print_r(::payload payload);
      property& request(const ::atom & atom);
      property_set& geta();
      property_set& posta();
      http::cookies& cookies();
      property_set& requesta();

      property& inheader(const ::atom & atom);
      property& outheader(const ::atom & atom);

      property& inattr(const ::atom & atom);
      property& outattr(const ::atom & atom);

      virtual string& gstr(const ::atom & atom);
      virtual property& gprop(const ::atom & atom);

      inline property& get(const ::atom & atom);
      inline property& post(const ::atom & atom);
      inline http::cookie& get_cookie(const ::scoped_string & scopedstr);
      inline http::cookie& set_cookie(const ::scoped_string & scopedstr);

      void uri_set_var(string& strUrl, const ::string & pszUrl, const ::string & pszKey, ::payload payload);
      void uri_set_param(string& strUrl, const ::string & pszUrl, const ::string & pszKey, const string& strParam);
      string query_get_param(const ::string & pszUrl, const ::string & pszKey);
      ::payload query_get_var(const ::string & pszUrl, const ::string & pszKey);



   };


} // namespace dynamic_source



