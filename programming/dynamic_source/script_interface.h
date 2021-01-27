#pragma once


namespace dynamic_source
{


   class script;
   class script_manager;


   class httpd_socket;
   class script_main;


   class CLASS_DECL_APP_PROGRAMMING script_interface :
      virtual public ::html::file
   {
   public:


      void *                              m_posdataNetnodeScriptInterface;
      void *                              m_posdataNetnodeScriptImpl;

      string                              m_strNote;

      __pointer(script_main)              m_pmain;
      __pointer(script_interface)         m_pinstanceParent2;
      __pointer(script)                   m_pscript2;


      i32                                 m_iDebug;

      ::payload                                 m_varRet;

      string                              m_strDebugRequestUri;
      string                              m_strDebugThisScript;


      script_interface();
      virtual ~script_interface();

      virtual const char* debug_note() const override;

      virtual ::e_status initialize(::layered * pobjectContext) override;
      virtual ::e_status init1();

      virtual void finalize() override;


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


      virtual void set_session_value(id id, ::payload value);
      virtual ::payload get_session_value(id id);
      virtual string session_id(const char * pszId = nullptr);

      
      ::payload call_run();


      virtual bool rerun();


      void current_url(string& strUrl);



      virtual void print_r(::payload payload);
      property& request(id idKey);
      property_set& geta();
      property_set& posta();
      http::cookies& cookies();
      property_set& requesta();

      property& inheader(id id);
      property& outheader(id id);

      property& inattr(id id);
      property& outattr(id id);

      virtual string& gstr(id id);
      virtual property& gprop(id id);

      inline property& get(id idKey);
      inline property& post(id idKey);
      inline http::cookie& get_cookie(id idKey);
      inline http::cookie& set_cookie(id idKey);

      void uri_set_var(string& strUrl, const char* pszUrl, const char* pszKey, ::payload payload);
      void uri_set_param(string& strUrl, const char* pszUrl, const char* pszKey, const string& strParam);
      string query_get_param(const char* pszUrl, const char* pszKey);
      ::payload query_get_var(const char* pszUrl, const char* pszKey);



   };


} // namespace dynamic_source



