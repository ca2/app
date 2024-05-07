// Created by camilo 2024-03-07 18:37 <3ThomasBorregaardSoresen!!
#pragma once


#include "trace.h"
#include "acme/constant/posix_shell.h"


namespace acme
{


   class CLASS_DECL_ACME shell :
      virtual public ::object
   {
   public:


      shell* m_pshellComposite;


      shell();
      ~shell() override;

      virtual bool has_command(const ::scoped_string& scopedstrCommand);
      virtual bool has_posix_shell_command(const ::scoped_string& scopedstrCommand, enum_posix_shell eposixshell = e_posix_shell_system_default);

      virtual int posix_shell_command(const ::scoped_string& scopedstrCommand, enum_posix_shell eposixshell = e_posix_shell_system_default, const trace_function& tracefunction = nullptr);

      //virtual ::string posix_shell_string(const ::scoped_string& scopedstrCommand, enum_posix_shell eposixshell = e_posix_shell_system_default);

      virtual bool posix_shell_protocol_begins_eat(enum_posix_shell& eposixshell, ::string& str);

      virtual void defer_install_posix_shell_command(const ::scoped_string& scopedstr, enum_posix_shell eposixshell = e_posix_shell_system_default, const trace_function& tracefunction = nullptr);

      virtual void install_posix_shell_command(const ::scoped_string& scopedstr, enum_posix_shell eposixshell = e_posix_shell_system_default, const trace_function& tracefunction = nullptr);


      virtual void prepare_argc_argv(int& argc, char** argv, char* cmd_line);
      virtual int command(const ::scoped_string& scopedstr, const trace_function& tracefunction = nullptr);



      //virtual void command_system(string_array & straOutput, int & iExitCode, const ::scoped_string & scopedstr, enum_command_system ecommandsystem = e_command_system_none, const class ::time & waitTimeout = ::time::infinity(), ::particle * pparticleSynchronization = nullptr, ::file::file * pfileLog = nullptr);
//      virtual int command_system(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrPipe, const trace_function & tracefunction = nullptr);
      virtual int command_system(const ::scoped_string& scopedstr, const trace_function& tracefunction = nullptr, const ::file::path& pathWorkingDirectory = {}, ::e_display edisplay = e_display_none);
      //      virtual int command_system(const ::scoped_string & scopedstr, const trace_function & tracefunction = nullptr);
            /// This version of command_system is originally meant for implementators
            /// to not use standard I/O redirection.
            /// virtual int command_system(const ::scoped_string& scopedstr, const class ::time& timeOut = 15_min);
      virtual int command_system(const ::scoped_string& scopedstr, const class ::time& timeOut = 15_min, const ::file::path& pathWorkingDirectory = {}, ::e_display edisplay = e_display_none);
      virtual ::string get_output(const ::scoped_string& scopedstr, const class ::time& timeOut = 15_min);

      virtual ::string get_command_output(const ::scoped_string& scopedstr, const class ::time& timeOut = 15_min);

      virtual ::i32 get_command_output(::string& strOutput, const ::scoped_string& scopedstr, const class ::time& timeOut = 15_min);

      virtual ::string get_posix_shell_command_output(const ::scoped_string& scopedstr, enum_posix_shell eposixshell = e_posix_shell_system_default, const class ::time& timeOut = 15_min);

      virtual ::i32 get_posix_shell_command_output(::string& strOutput, const ::scoped_string& scopedstr, enum_posix_shell eposixshell = e_posix_shell_system_default, const class ::time& timeOut = 15_min);



      virtual bool is_executable_in_path(const ::scoped_string& scopedstr);

      virtual void launch_command_system(const ::scoped_string& scopedstr, const ::file::path& pathWorkingDirectory = {}, ::e_display edisplay = e_display_none);

#ifdef WINDOWS_DESKTOP

      virtual ::file::path _get_power_shell_path();

      virtual ::file::path _get_cmd_path();

      //virtual ::string _msys2_shell_command_output(const ::scoped_string& scopedstr, const class ::time& timeOut = 15_min);

#endif

   };


} // namespace acme



