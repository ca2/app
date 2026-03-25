//
// From integration.h by camilo on 2024-05-11 19:25 PM <3ThomasBorregaardSørensen!!
//
#pragma once


#include "integration.h"


namespace macos
{


namespace coding
{

   class CLASS_DECL_CODING integration :
           virtual public ::coding::integration
   {
   public:


      integration();
      ~integration() override;


//       void initialize(::particle* pparticle) override;

//       virtual void initialize_integration();


//       void on_start_task_group(enum_task etaskGroup);

//       virtual void load_nodes(const ::string_array& straLines);
//       virtual ::string_array save_nodes();

//       virtual void read_nodes();
//       virtual void write_nodes();

//       virtual task_group* running_task_group();

//       virtual void on_initialize_application_integration();

//       virtual void on_initialize_application_build_tool();

//       virtual void on_initialize_application_handler();

//       virtual void open(const ::file::path& pathIntegrationFolder);

//       virtual void on_open_build_tool();

//       virtual void on_open_integration();
//       //virtual void open_integration(const ::file::path & pathIntegrationFolder);

//       virtual void on_load();

//       virtual void speak(::collection::index iIndex, ::collection::index iCount, const ::scoped_string& scopedstrText, int iExitCode);

//       virtual void _speak(const ::scoped_string& scopedstr);

//       virtual void initialize_integrate_operating_system();

//       virtual void set_impact_interface(impact_interface* pimpactinterface);

//       virtual void prepare1(const ::string & lpcszSource, const ::string & lpcszDest);
      
//       virtual void set_integrate(enum_integrate eintegrate);

//       virtual ::file::path base_integration_folder();

//       virtual ::file::path host_integration_folder();

//       virtual ::file::path integration_folder();




//       void run() override;

void prepare_build() override;

//       //virtual ::file::path log_base_folder();


//       virtual void integrate_netnode(const ::scoped_string& strNetnode);

//       virtual void start_netnode(const ::scoped_string& strNetnode);

//       virtual void monitor_netnode(const ::scoped_string& strNetnode);

//       virtual ::string netnode_short_name(const ::scoped_string& strNetnode);

//       virtual ::string netnode_long_name(const ::scoped_string& strPulse);

//       virtual ::string netnode_running_status(const ::scoped_string& strNetnode);

//       virtual void add_command(
//               const ::scoped_string & scopedstrLabel,
//               const ::scoped_string & scopedstrCommand,
//               const class ::time & timeTimeout
//       );

//       virtual void do_command(integration_command * pintegrationcommand);

//       virtual bool integrate_command_list();

// #if defined(WINDOWS)

//       virtual void integrate_new_release_prefix_windows();
//       virtual void integrate_windows(::coding::item * pitem);
//       virtual void integrate_windows_port(::coding::item* pitem);

// #endif

//       virtual ::file::path path_base_folder();

//       virtual int _do_task(::coding::task* ptask);
//       //virtual void integrate_openssl(::coding::item* pitem);
//       //virtual void integrate_ffmpeg(::coding::item* pitem);
//       virtual void integrate_task_group(enum_task etaskgroup, ::coding::item* pitem);
//       virtual void _defer_task_group(enum_task etaskGroup, ::pointer < task_group > * pptaskgroup = nullptr);


//       virtual bool should_task_group_tasks_be_sequential(enum_task etaskGroup);
//       virtual ::string task_group_id(enum_task etaskGroup);
//       virtual ::string task_group_name(enum_task etaskGroup);
//       virtual ::string task_group_speech_name(enum_task etaskGroup);
//       virtual void task_group_indexes(enum_task etaskGroup, ::numeric_array_base<::coding::enum_index>& eindexa);
//       virtual void task_group_stages(enum_task etaskGroup, ::string_array& straStage);
//       virtual void task_group_tasks_ordinals(enum_task etaskGroup, ::numeric_array_base<::coding::enum_task>& etaskaOrdinal);

// #if defined(LINUX) || defined(__BSD__)

      
//       virtual void integrate_posix(const ::scoped_string & scopedstrDistroRelease);
//       virtual bool integrate_posix_with_result(const ::scoped_string & scopedstrDistroRelease);


// #endif

// #if defined(MACOS)
// //      virtual void integrate_macos_port(::coding::item* pitem);
//       //virtual void integrate_macos_openssl(::coding::item* pitem);
//       //virtual void integrate_macos_ffmpeg(::coding::item* pitem);
//       //virtual void integrate_macos_parallels(enum_task etaskgroup, ::coding::item* pitem);
//       virtual void integrate_macos(::coding::item* pitem);
      
      
      void task_group_tasks_ordinals(::coding::enum_task etaskGroup, ::numeric_array_base < ::coding::enum_task >& etaskaOrdinal) override;

            void integrate_main2(::coding::item* pitem) override;
       virtual ::string macos_archive(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrScheme) override;
      
//       //virtual void _defer_macos_task_group(enum_task etaskGroup, ::pointer < task_group > * pptaskgroup = nullptr);


// #endif

       virtual bool on_packaging(::string & strAppId, ::string & strTarget, ::string & strSource) override;

//       bool on_more_packaging(::string & strAppId, ::string & strTarget, ::string & strSource);

//       void add_store_copy(const ::scoped_string & scopedstrAppId);
//       void add_store_copy(const ::scoped_string & scopedstrTitle, const ::file::path & pathTarget, const ::file::path & pathSource);
//       //void start_store_copy(const ::file::path & pathZip, const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrScheme);
//       //void start_store_copy(const ::file::path & pathZip, const ::scoped_string & scopedstrAppId);

//       //void store_copy(const ::scoped_string & scopedstrAppId, const ::file::path & pathTarget, const ::file::path & pathSource, const ::scoped_string & scopedstrScheme);
//       void release_package(const char * pszTitle, const char * pszTarget, const char * pszSource);

//       void store_copy(const ::scoped_string & scopedstrAppId, const ::file::path & pathTarget, const ::file::path & pathSource);
//       void store_copy_to_local_file_system_store(const ::file::path & pathFolder, const ::scoped_string & scopedstrAppId, const ::file::path & pathTarget, ::file::file * pfileSource);
//       void store_copy_to_http_server(const ::scoped_string & scopedstrAppId, const ::file::path & pathTarget, ::file::file * pfileSource);

//       //::file::path control_folder();

//       //::file::path control_file(const string & strFileName);

//       //void erase_control_file(const string & strFileName);

//       //string wait_control_file(const string & strFileName, const class time & timeTimeout, const string & strLogFile = "");

//       //virtual string send_control_command(const string & strCommand, const class time & timeTimeout);

//       //virtual void set_topic_text(const ::scoped_string& scopedstr);

//       //virtual void set_topic_text2(const ::scoped_string& scopedstr);

//       //string get_name(enum_integrate eintegrate);


//       string get_integration_name();


//       class ::time get_build_elapsed_time();

//       //void write_log(const ::string &str);


//       //void run_command(const ::string & strCommand);

//       void append_message(const ::ansi_character * pszFormat, ...);

//       virtual void on_finished();

//       bool is_upload_finished();


//       void main_status(const ::scoped_string & scopedstrMainStatus);

//       void integration_summary(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrOk);
      

//       virtual bool has_selected_build() const;



//       virtual void on_finished_finish_animations();


//       log_interface* task_log(enum_task etask);

      //void on_initialize_application_build_tool() override;
      void on_initialize_application_build_tool_operating_system_integrate_list() override;
      void on_initialize_application_build_tool_task_groups() override;

      void on_start_task_group(::coding::enum_task etaskGroup) override;
      
      
      void defer_task_groups();
      
   };


} // namespace coding


} // namespace macos



