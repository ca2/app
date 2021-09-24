#pragma once


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING script :
      virtual public ::object
   {
   public:


      __pointer(script_manager)                 m_pmanager;
      string                                    m_strName;
      memory_file_pointer                       m_pfileError;
      ::text_stream                             m_streamError;
      string                                    m_strError;
      bool                                      m_bNew;


      script();
      ~script() override;


      ::e_status on_initialize_object() override;


      virtual __pointer(::dynamic_source::script_instance) create_instance() = 0;

      virtual void run(script_instance * pinstance);

      virtual bool ShouldBuild();

      virtual bool HasCompileOrLinkError();


   };


   class CLASS_DECL_APP_PROGRAMMING ds_script :
      virtual public script
   {
   public:


      __pointer(::acme::library)       m_plibrary;


      filetime_set                     m_ft;
      filetime_set                     m_ftDs;

      bool                             m_bLastVersionCheck;
      millis                           m_millisLastVersionCheck;
      ::file::path                     m_strSourcePath;
      ::file::path                     m_strSourceDir;
      ::file::path                     m_strCppPath;
      ::file::path                     m_strScriptPath;
      manual_reset_event               m_evCreationEnabled;
      millis                           m_millisLastBuildTime;
      bool                             m_bShouldBuild;
      bool                             m_bShouldCalcTempError;
      bool                             m_bHasTempError;
      bool                             m_bHasTempOsError;
      bool                             m_bHasFatalError;
      bool                             m_bUnloading;
      NET_NODE_CREATE_INSTANCE_PROC    m_lpfnCreateInstance;


      ds_script();
      virtual ~ds_script();


      virtual void defer_build();
      virtual void on_start_build();

      bool DoesMatchVersion();
      bool ShouldBuild() override;
      virtual bool HasCompileOrLinkError() override;
      bool HasTempError();
      bool CalcHasTempError();
      bool HasDelayedTempError();
      bool HasTimedOutLastBuild();
      void Load();
      void Unload();

      string get_stage_path();


      //virtual ::aura::application * get_application() const override;

      __pointer(script_instance) create_instance() override;


   };


   template < class T >
   class t_script :
      virtual public script
   {
   public:


      t_script()
      {


      };


      virtual __pointer(script_instance) create_instance()
      {
         
         return __new(T());

      }

   };


} // namespace dynamic_source



