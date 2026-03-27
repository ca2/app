//
// From integration.h by camilo on
// 2024-05 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "integration.h"

//
//
//#include "apex/platform/app_consumer.h"
//#include "acme/platform/integration_context.h"
//#include "acme/prototype/collection/array_union.h"
//#include "_constant.h"
//#include "acme/operating_system/summary.h"
//#include "acme/prototype/collection/bool_array.h"
//#include "log_interface.h"
////
//
//#ifdef WINDOWS
//
//#define INTEGRATE_WINDOWS
//#define INTEGRATE_ANDROID
//
//#elif defined(LINUX)
//
//#define INTEGRATE_LINUX
//
//#elif defined(__APPLE__)
//
//#define INTEGRATE_MACOS
//
//#endif


namespace windows
{

      namespace coding
      {

   class CLASS_DECL_CODING integration :
           virtual public ::coding::integration
   {
   public:


//      ::string                               m_strRepositoryPath;
//
//      ::string_array                         m_straOperatingSystem;
//      ::numeric_array_base < enum_integrate >     m_eintegrateaOperatingSystem;
//      //::numeric_array_base < enum_integrate_group >     m_eintegrategroupa;
//      ::string_array                         m_straMachineBox;
//      ::string_array                         m_straNetnode;
//      
//
//      ::string_array                         m_straNetnodePulse;
//      enum_task                              m_etaskGroupRunning;
//
//
//      string_array                           m_straNode; // Netnode serialization
//      bool_array                             m_baNodeEnabled; // Netnode serialization
//      bool_array                             m_baTaskOrdinalEnable;
//      ::string_array                         m_straTaskOrdinal;
//
//      ::pointer_array < group >              m_groupa;
//      ::pointer < group_new_release_prefix > m_pgroupnewreleaseprefix;
//      ::pointer < group_netnode >            m_pgroupnetnode;
//
//
//      ::file::path                           m_pathParentIntegration;
//
//
//      ::earth::time                          m_timeStart;
//      ::earth::time                          m_timeStarted;
//
//      bool_array                             m_baPhaseEnable;
//      string_array                           m_straPhaseId;
//      string_array                           m_straPhaseText;
//
//      //bool                                   m_bNewReleasePrefix;
//      //bool                                   m_bCheckout;
//      //bool                                   m_bApplicationList;
//      //bool                                   m_bPrepareApplications;
//      //bool                                   m_bProjectList;
//      //bool                                   m_bPrepareProjects;
//      //bool                                   m_bCmake;
//      //bool                                   m_bClean;
//      ::file::path                           m_pathLogFolder;
//
//      e_integrate                               m_eintegrate;
//
//      ::file::path                              m_pathStartBuild;
//      ::file::path                              m_pathBuildThenPowerOff;
//      ::file::path                              m_pathCheckoutThenPowerOff;
//      //::string                                  m_strCheckoutForAnotherSystem;
//      ///::file::path                              m_pathIntegration;
//      ::string                                  m_strIntegration;
//      //::pointer<listener>                       m_plistener;
//
//      ::pointer <::coding::context>        m_pintegrationcontext;
//
//      pointer_array < item >                    m_itema;
//
//      ::pointer<item>                           m_pitem;
//
//      ::pointer<impact_interface>               m_pimpactinterface;
//
//      string                                    m_strCurrentHost;
//
//      string_array                              m_straError;
//
//      class ::time                              m_timeStart2;
//      class ::time                              m_timeEnd2;
//      bool                                      m_bEnableUpdateElapsed;
//      e_integrate                               m_eintegrateMask;
//
//#ifdef WINDOWS
//      string                                    m_strVs;
//      string                                    m_strVsTools;
//      string                                    m_strVCVersion;
//#endif
//
//      string                                    m_strEnv;
//
//      string                                    m_strTime;
//      string                                    m_strSdk1;
//      string                                    m_strPlat1;
//      string                                    m_strPlat2;
//      string                                    m_strPlatform;
//      string                                    m_strStagePlatform;
//      string                                    m_strLibPlatform;
//      ::earth::time                             m_timeBuild;
//
//      string_array                              m_straLine3;
//      string_array                              m_straPinnedLast2;
//      //map < enum_task, ::pointer < log_interface > >  m_tasklog;
//
//      numeric_array_base < enum_task >  m_etaskaGroup;
//      map < enum_task, ::pointer < task_group > >  m_taskgroup;
//
//      ::array_union < string_array >            m_straunion;
//
//      //int m_iTaskCount;
//      //int m_iFFMPEGOk;
//      //int m_iFFMPEGNok;
//      //string                                    m_strOutput;
//      //string                                    m_strError;
//      ::pointer < ::particle >                  m_pmutexLines;
////#ifdef LINUX
////      ::string                                  m_strDistroRelease;
////#endif
//      //string                                    m_strTopic;
//      //string                                    m_strTopic2;
//      
//      
//      string                                    m_strReleaseDot;
//      string                                    m_strReleaseDash;
//      string                                    m_strReleaseComma;
//      string                                    m_strReleaseDatetime;
//      string                                    m_strReleaseFilename;
//
//
//      string                                    m_strBuildResult;
//
//      ::file::path                              m_pathBox;
//      //::file::path                              m_pathBuildFolder;
//
//      ::array < item_time >                     m_itemtimeaSummary;
//
//      ::string                                  m_strFinishedStatus;
//      
//      class ::time                              m_timeTopicStart;
//      
//      ::task_pointer                            m_ptaskCopy;
//
//      ::pointer_array < copy_item >             m_copyitemaStore;
//      ::collection::index                                   m_iCurrentStoreCopyItem;
//
//      ::file::path                              m_pathStorageFolder;
//
//      ::file::path                              m_pathStoreFolder1;
//
//      bool                                      m_bBuildFinished;
//
//      ::pointer < ::operating_system::summary > m_poperatingsystemsummary;
//
//      ::string                                  m_strLastUpstreamServerStatus;
//      class ::time                              m_timeLastUpstreamServerStatus;
//
//      ::string                                  m_strLastUpstreamServerSummary;
//      class ::time                              m_timeLastUpstreamServerSummary;
//
//      bool                                      m_bSummaryError;
//
//      ::particle_pointer                        m_pparticleHttpSynchronization;
//
//      class ::time                              m_timeSpeechSpamControl;
//
//      //::string_array                            m_straCommand;
//      //::string_array                            m_straLabel;
//      //::array < class ::time >                  m_timea;
//      ::pointer_array < integration_command >   m_integrationcommanda;
//      ::collection::index                                   m_iCommandStep;
//
//      bool m_bSpeaking = false;
//
//      int m_iFailedTasks = 0;

      integration();
      ~integration() override;


      //void initialize(::particle* pparticle) override;

      //virtual void initialize_integration();


      void on_start_task_group(::coding::enum_task etaskGroup) override;

      //virtual void load_nodes(const ::string_array& straLines);
      //virtual ::string_array save_nodes();

      //virtual void read_nodes();
      //virtual void write_nodes();

      //virtual integration::task_group* running_task_group();

      //virtual void on_initialize_application_integration();

      //virtual void on_initialize_application_build_tool();

      //virtual void on_initialize_application_handler();

      //virtual void open(const ::file::path& pathIntegrationFolder);

      //virtual void on_open_build_tool();

      //virtual void on_open_integration();
      ////virtual void open_integration(const ::file::path & pathIntegrationFolder);

      //virtual void on_load();

      //virtual void speak(::collection::index iIndex, ::collection::index iCount, const ::scoped_string& scopedstrText, int iExitCode);

      //virtual void _speak(const ::scoped_string& scopedstr);

      //virtual void initialize_integrate_operating_system();

      //virtual void set_impact_interface(::coding::impact_interface* pimpactinterface);

      //virtual void prepare1(const ::string & lpcszSource, const ::string & lpcszDest);
      //
      //virtual void set_integrate(::coding::enum_integrate eintegrate);

      //virtual ::file::path base_integration_folder();

      //virtual ::file::path host_integration_folder();

      //virtual ::file::path integration_folder();


//
//
//      void run() override;
//
      void prepare_build() override;
//
//      //virtual ::file::path log_base_folder();
//
//
//      virtual void integrate_netnode(const ::scoped_string& strNetnode);
//
//      virtual void start_netnode(const ::scoped_string& strNetnode);
//
//      virtual void monitor_netnode(const ::scoped_string& strNetnode);
//
//      virtual ::string netnode_short_name(const ::scoped_string& strNetnode);
//
//      virtual ::string netnode_long_name(const ::scoped_string& strPulse);
//
//      virtual ::string netnode_running_status(const ::scoped_string& strNetnode);
//
//      virtual void add_command(
//              const ::scoped_string & scopedstrLabel,
//              const ::scoped_string & scopedstrCommand,
//              const class ::time & timeTimeout
//      );
//
//      virtual void do_command(::coding::integration_command * pintegrationcommand);
//
//      virtual bool integrate_command_list();
//
//#if defined(WINDOWS)
//
      
      
      void task_group_tasks_ordinals(::coding::enum_task etaskGroup, ::numeric_array_base < ::coding::enum_task >& etaskaOrdinal) override;

      virtual void integrate_new_release_prefix_windows() override;
      virtual void integrate_main2(::coding::item * pitem) override;
      //virtual void integrate_windows_port(::coding::item* pitem);
//
//#endif
//
     //::file::path path_base_folder() override;
//
//      virtual int _do_task(::coding::task* ptask);
//      //virtual void integrate_openssl(::coding::item* pitem);
//      //virtual void integrate_ffmpeg(::coding::item* pitem);
//      //virtual void integrate_task_group(enum_task etaskgroup, ::coding::item* pitem);
//virtual void _defer_task_group(::coding::enum_task etaskGroup, ::pointer < task_group > * pptaskgroup = nullptr) override;


//void _defer_task_group(::coding::enum_task etaskGroup, ::pointer < ::coding::task_group >* pptaskgroup = nullptr) override;
//
//
//      //virtual bool should_task_group_tasks_be_sequential(enum_task etaskGroup);
//      //virtual ::string task_group_id(enum_task etaskGroup);
//      //virtual ::string task_group_name(enum_task etaskGroup);
//      //virtual ::string task_group_speech_name(enum_task etaskGroup);
//      //virtual void task_group_indexes(enum_task etaskGroup, ::numeric_array_base<::coding::enum_index>& eindexa);
//      //virtual void task_group_stages(enum_task etaskGroup, ::string_array& straStage);
//      //virtual void task_group_tasks_ordinals(enum_task etaskGroup, ::numeric_array_base<::coding::enum_task>& etaskaOrdinal);
//
//#if defined(LINUX) || defined(__BSD__)
//
//      
//      virtual void integrate_posix(const ::scoped_string & scopedstrDistroRelease);
//      virtual bool integrate_posix_with_result(const ::scoped_string & scopedstrDistroRelease);
//
//
//#endif
//
//#if defined(MACOS)
////      virtual void integrate_macos_port(::coding::item* pitem);
//      //virtual void integrate_macos_openssl(::coding::item* pitem);
//      //virtual void integrate_macos_ffmpeg(::coding::item* pitem);
//      //virtual void integrate_macos_parallels(enum_task etaskgroup, ::coding::item* pitem);
//      virtual void integrate_macos(::coding::item* pitem);
//      virtual ::string macos_archive(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrScheme);
//      
//      //virtual void _defer_macos_task_group(enum_task etaskGroup, ::pointer < task_group > * pptaskgroup = nullptr);
//
//
//#endif
//
      bool on_packaging(::string & strAppId, ::string & strTarget, ::string & strSource) override;
//
//      bool on_more_packaging(::string & strAppId, ::string & strTarget, ::string & strSource);
//
//      void add_store_copy(const ::scoped_string & scopedstrAppId);
//      void add_store_copy(const ::scoped_string & scopedstrTitle, const ::file::path & pathTarget, const ::file::path & pathSource);
//      //void start_store_copy(const ::file::path & pathZip, const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrScheme);
//      //void start_store_copy(const ::file::path & pathZip, const ::scoped_string & scopedstrAppId);
//
//      //void store_copy(const ::scoped_string & scopedstrAppId, const ::file::path & pathTarget, const ::file::path & pathSource, const ::scoped_string & scopedstrScheme);
//      void release_package(const char * pszTitle, const char * pszTarget, const char * pszSource);
//
//      void store_copy(const ::scoped_string & scopedstrAppId, const ::file::path & pathTarget, const ::file::path & pathSource);
//      void store_copy_to_local_file_system_store(const ::file::path & pathFolder, const ::scoped_string & scopedstrAppId, const ::file::path & pathTarget, ::file::file * pfileSource);
//      void store_copy_to_http_server(const ::scoped_string & scopedstrAppId, const ::file::path & pathTarget, ::file::file * pfileSource);
//
//      //::file::path control_folder();
//
//      //::file::path control_file(const string & strFileName);
//
//      //void erase_control_file(const string & strFileName);
//
//      //string wait_control_file(const string & strFileName, const class time & timeTimeout, const string & strLogFile = "");
//
//      //virtual string send_control_command(const string & strCommand, const class time & timeTimeout);
//
//      //virtual void set_topic_text(const ::scoped_string& scopedstr);
//
//      //virtual void set_topic_text2(const ::scoped_string& scopedstr);
//
//      //string get_name(enum_integrate eintegrate);
//
//
//      string get_integration_name();
//
//
//      class ::time get_build_elapsed_time();
//
//      //void write_log(const ::string &str);
//
//
//      //void run_command(const ::string & strCommand);
//
//      void append_message(const ::ansi_character * pszFormat, ...);
//
//      virtual void on_finished();
//
//      bool is_upload_finished();
//
//
//      void main_status(const ::scoped_string & scopedstrMainStatus);
//
//      void integration_summary(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrOk);
//      
//
//      virtual bool has_selected_build() const;
//
//
//
//      virtual void on_finished_finish_animations();
//
//
//      //log_interface* task_log(enum_task etask);
      void on_initialize_application_build_tool_operating_system_integrate_list() override;
      void on_initialize_application_build_tool_task_groups() override;

   };

   } // namespace coding


} // namespace windows



