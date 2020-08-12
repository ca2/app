#pragma once


namespace dynamic_source
{


   class script;
   class script_manager;


   class httpd_socket;


   class CLASS_DECL_PROGRAMMING script_interface :
      virtual public ::html::file
   {
   public:



      script_interface *                  m_pinstanceMain;
      script_interface *                  m_pinstanceParent;
      httpd_socket *                      m_pnetnodesocket;
      script_manager *                    m_pmanager;


      script *                            m_pscript;

      i32                                 m_iDebug;

      var                                 m_varRet;

      string                              m_strDebugRequestUri;
      string                              m_strDebugThisScript;


      script_interface();
      virtual ~script_interface();


      virtual void destroy();


      virtual ::estatus     run() override;


      virtual void dinit();
      virtual void dprint(const char *) override;



      virtual property     & get(const char * pszKey);


      virtual bool main_initialize();
      virtual bool main_finalize();


      virtual ::file::file * file();
      //virtual ::text_stream ostream();
      //virtual ::binary_stream bstream();


      virtual ::estatus on_initialize();
      virtual ::estatus initialize_dynamic_source_script_interface(script_interface * pinterfaceMain, script_interface * pinterfaceParent, httpd_socket * pdssocket, script_manager * pmanager);

      script_interface * main_instance()
      {
         return m_pinstanceMain;
      }

      script_interface * parent()
      {
         return m_pinstanceParent;
      }

      httpd_socket * netnodesocket()
      {
         return m_pnetnodesocket;
      }

      script_manager * manager()
      {
         return m_pmanager;
      }


      virtual void set_session_value(id id, var value);
      virtual var get_session_value(id id);
      virtual string session_id(const char * pszId = nullptr);

      
      var call_run();


      virtual bool rerun();


   };


} // namespace dynamic_source



