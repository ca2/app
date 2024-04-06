// Created by camilo 2024-03-07 18:37 <3ThomasBorregaardSoresen!!
#pragma once


#include "trace.h"


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
      virtual bool has_unix_shell_command(const ::scoped_string& scopedstrCommand);

      virtual int unix_shell_command(const ::scoped_string& scopedstrCommand, const trace_function& tracefunction = nullptr);

      virtual ::string unix_shell_command_string(const ::scoped_string& scopedstrCommand);


      virtual void prepare_argc_argv(int& argc, char** argv, char* cmd_line);
      virtual int command(const ::scoped_string& scopedstr, const trace_function& tracefunction = nullptr);



      //virtual void command_system(string_array & straOutput, int & iExitCode, const ::scoped_string & scopedstr, enum_command_system ecommandsystem = e_command_system_none, const class ::time & waitTimeout = ::time::infinity(), ::particle * pparticleSynchronization = nullptr, ::file::file * pfileLog = nullptr);
//      virtual int command_system(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrPipe, const trace_function & tracefunction = nullptr);
      virtual int command_system(const ::scoped_string& scopedstr, const trace_function& tracefunction = nullptr);
      //      virtual int command_system(const ::scoped_string & scopedstr, const trace_function & tracefunction = nullptr);
            /// This version of command_system is originally meant for implementators
            /// to not use standard I/O redirection.
      virtual int command_system(const ::scoped_string& scopedstr, const class ::time& timeOut = 15_min);
      virtual ::string get_output(const ::scoped_string& scopedstr, const class ::time& timeOut = 15_min);

      virtual ::string get_command_output(const ::scoped_string& scopedstr, const class ::time& timeOut = 15_min);

      virtual ::i32 get_command_output(::string& strOutput, const ::scoped_string& scopedstr, const class ::time& timeOut = 15_min);

      virtual ::string get_unix_shell_command_output(const ::scoped_string& scopedstr, const class ::time& timeOut = 15_min);

      virtual ::i32 get_unix_shell_command_output(::string& strOutput, const ::scoped_string& scopedstr, const class ::time& timeOut = 15_min);



      virtual bool is_executable_in_path(const ::scoped_string& scopedstr);

      virtual void open_terminal_and_run(const ::scoped_string& scopedstr);

   };


} // namespace acme



