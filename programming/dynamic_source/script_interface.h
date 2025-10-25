#pragma once


#include "apex/filesystem/file/html_file.h"
#include "acme/filesystem/filesystem/file_system_interface.h"
#include "acme/filesystem/filesystem/file_system_real_path_interface.h"


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING script_interface :
      virtual public ::html_file,
      virtual public ::object,
      virtual public ::file_system_interface,
      virtual public ::file_system_real_path_interface
   {
   public:


      bool                                               m_bOnTopicInclude;

      ::pointer < ::netnode::script_interface >          m_pnetnodescriptinterface;
      ::pointer < ::netnode::script_impl >               m_pnetnodescriptimpl;

      ::pointer<httpd_socket>                            m_phttpdsocket1;
      ::pointer < ::dynamic_source::script_manager >     m_pscriptmanager1;

      string                                             m_strNote;

      ::pointer < script_main >                          m_pscriptmain1;
      ::pointer<script_interface>                        m_pinstanceParent1;
      ::pointer<script>                                  m_pscript1;

      int                                                m_iDebug;

      ::payload                                          m_varRet;

      string                                             m_strDebugRequestUri;
      string                                             m_strDebugThisScript;

      class ::time                                       m_timeLastIncludingChildElapsed;


      script_interface();
      ~script_interface() override;

      virtual const_char_pointer debug_note() const override;

      void initialize(::particle * pparticle) override;
      virtual void initialize_with_socket_thread(::httpd::socket_thread* psocketthread);
      virtual void init1();


      void on_initialize_particle() override;


      //void finalize() override;

      void destroy() override;
      virtual void     run() override;

      virtual void dinit();
      virtual void dprint(const ::scoped_string & scopedstr) override;
      virtual void dprint_recursive(const ::payload & payload);


      ::property_set& inattra();


      //virtual property & get(const ::scoped_string & scopedstrKey);

      //virtual void transfer_proper_data_to_parent_script();
      virtual void transfer_proper_data_to_data_object(::dynamic_source::data_object * pdataobject);


      virtual ::file::file * output_file();


      virtual ::file_system_cache_item netnode_file_path(const ::scoped_string& scopedstrName);

      ::file_system_real_path_interface* get_file_system_real_path_interface() override;
      
      virtual ::file_system_cache_item & netnode_include_file_system_cache_item(const ::scoped_string& scopedstrName, const ::unique_index& uniqueindex);

      virtual void on_initialize();
      //virtual void initialize_dynamic_source_script_interface(script_interface * pinterfaceMain, script_interface * pinterfaceParent, httpd_socket * pdssocket, script_manager * pmanager);

      inline script_main * main() { return m_pscriptmain1; }
      script_interface * parent() { return m_pinstanceParent1; }
      httpd_socket* netnodesocket() { return m_phttpdsocket1; }
      script_manager* manager() { return m_pscriptmanager1; }


      virtual void set_session_payload(const ::atom & atom, const ::payload & payload);
      virtual ::payload get_session_payload(const ::atom & atom);
      virtual ::string session_id(bool bForceCreateNew = false);
      virtual void set_session_id(const ::scoped_string & scopedstrSessionId);

      virtual string get_auth_email();
      virtual void set_auth_email(const ::scoped_string & scopedstrEmail);
      virtual void auth(const ::scoped_string & scopedstrAuth);
      
      ::payload run_script();


      virtual bool rerun();


      void current_url(string& strUrl);



      virtual void print_r(::payload payload);
      virtual ::property& request(const ::atom & atom);
      virtual ::property_set& geta();
      virtual ::property_set& posta();
      virtual http::cookies& cookies();
      virtual ::property_set& requesta();

      virtual ::property& inheader(const ::atom & atom);
      virtual ::property& outheader(const ::atom & atom);

      virtual ::property& inattr(const ::atom & atom);
      virtual ::property& outattr(const ::atom & atom);

      virtual string& gstr(const ::atom & atom);
      virtual ::property& gprop(const ::atom & atom);

      inline ::property& get(const ::atom & atom);
      inline ::property& post(const ::atom & atom);
      inline http::cookie& get_cookie(const ::scoped_string & scopedstr);
      inline http::cookie& set_cookie(const ::scoped_string & scopedstr);

      void uri_set_var(string& strUrl, const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrKey, ::payload payload);
      void uri_set_param(string& strUrl, const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrParam);
      string query_get_param(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrKey);
      ::payload query_get_var(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrKey);



   };


} // namespace dynamic_source



