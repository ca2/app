#pragma once


namespace dynamic_source
{


   class script;
   class script_instance;
   class script_manager;

   typedef   script_instance * (*NET_NODE_CREATE_INSTANCE_PROC)();


   class CLASS_DECL_APP_PROGRAMMING script :
      virtual public ::object
   {
   public:


      __pointer(script_manager)                 m_pmanager;
      string                                    m_strName;
      memory_file                               m_fileError;
      ::text_stream                             m_streamError;
      string                                    m_strError;
      bool                                      m_bNew;


      script();
      virtual ~script();


      virtual __pointer(script_instance) create_instance() = 0;

      virtual void run(script_instance * pinstance);

      virtual bool ShouldBuild();

      virtual bool HasCompileOrLinkError();


   };


   class CLASS_DECL_APP_PROGRAMMING ds_script :
      virtual public script
   {
   public:


      __pointer(::apex::library)              m_plibrary;


      filetime                        m_ft;
      filetime                        m_ftDs;

      bool                             m_bLastVersionCheck;
      tick m_tickLastVersionCheck;
      ::file::path                     m_strSourcePath;
      ::file::path                     m_strSourceDir;
      ::file::path                     m_strCppPath;
      ::file::path                     m_strScriptPath;
      //::file::path                     m_strBuildBat;
      manual_reset_event               m_evCreationEnabled;
      tick m_tickLastBuildTime;
      bool                             m_bShouldBuild;
      bool                             m_bShouldCalcTempError;
      bool                             m_bHasTempError;
      bool                             m_bHasTempOsError;
      bool                             m_bHasFatalError;
      bool                             m_bUnloading;
      NET_NODE_CREATE_INSTANCE_PROC    m_lpfnCreateInstance;


      ds_script();
      ~ds_script();


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


      //virtual ::aura::application * get_context_application() const override;

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



