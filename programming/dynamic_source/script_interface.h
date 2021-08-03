#pragma once


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING script_interface :
      virtual public ::html::file
   {
   public:


      ::netnode::script_interface *       m_pnetnodescriptinterface;
      ::netnode::script_impl *            m_pnetnodescriptimpl;

      string                              m_strNote;

      __pointer(script_main)              m_pmain;
      __pointer(script_interface)         m_pinstanceParent2;
      __pointer(script)                   m_pscript2;


      i32                                 m_iDebug;

      ::payload                           m_varRet;

      string                              m_strDebugRequestUri;
      string                              m_strDebugThisScript;


      script_interface();
      ~script_interface() override;

      virtual const char* debug_note() const override;

      virtual ::e_status initialize(::object * pobject) override;
      virtual ::e_status init1();

      //::e_status destroy() override;

      ::e_status destroy() override;
      virtual ::e_status     run() override;


      virtual void dinit();
      virtual void dprint(const char *) override;
      inline void dprint_r(::payload payload);


      property_set& inattra();


      virtual property & get(const char * pszKey);




      virtual ::file::file * file();


      virtual ::e_status on_initialize();
      //virtual ::e_status initialize_dynamic_source_script_interface(script_interface * pinterfaceMain, script_interface * pinterfaceParent, httpd_socket * pdssocket, script_manager * pmanager);

      script_main * main() { return m_pmain; }
      script_interface * parent() { return m_pinstanceParent2; }
      httpd_socket* netnodesocket();
      script_manager* manager();


      virtual void set_session_value(const ::id & id, ::payload value);
      virtual ::payload get_session_value(const ::id & id);
      virtual ::id session_id(const ::id & id = nullptr);

      
      ::payload call_run();


      virtual bool rerun();


      void current_url(string& strUrl);



      virtual void print_r(::payload payload);
      property& request(const ::id & id);
      property_set& geta();
      property_set& posta();
      http::cookies& cookies();
      property_set& requesta();

      property& inheader(const ::id & id);
      property& outheader(const ::id & id);

      property& inattr(const ::id & id);
      property& outattr(const ::id & id);

      virtual string& gstr(const ::id & id);
      virtual property& gprop(const ::id & id);

      inline property& get(const ::id & id);
      inline property& post(const ::id & id);
      inline http::cookie& get_cookie(const ::id & id);
      inline http::cookie& set_cookie(const ::id & id);

      void uri_set_var(string& strUrl, const char* pszUrl, const char* pszKey, ::payload payload);
      void uri_set_param(string& strUrl, const char* pszUrl, const char* pszKey, const string& strParam);
      string query_get_param(const char* pszUrl, const char* pszKey);
      ::payload query_get_var(const char* pszUrl, const char* pszKey);



   };


} // namespace dynamic_source



