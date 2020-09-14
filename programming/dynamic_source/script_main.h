#pragma once


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING script_main :
      virtual public script_interface
   {
   public:


      void *                              m_posdataNetnodeScriptMain;

      __pointer(httpd_socket)             m_psocket2;
      __pointer(script_manager)           m_pmanager2;



      script_main();
      virtual ~script_main();


#ifdef DEBUG

      virtual ::i64 add_ref(OBJ_REF_DBG_PARAMS) override;

      virtual ::i64 dec_ref(OBJ_REF_DBG_PARAMS) override;

#endif

      virtual ::estatus initialize(::layered * pobjectContext) override;


      virtual void finalize() override;

      virtual bool main_initialize();
      virtual bool main_finalize();


   };


} // namespace dynamic_source



