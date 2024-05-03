// Created by camilo 2024-03-07 18:41 <3ThomasBorregaardSoresen!!
#include "framework.h"
#include "shell.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/status.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/platform/node.h"


namespace acme
{

   shell::shell()
   {

      m_pshellComposite = this;

   }


   shell::~shell()
   {


   }


   void shell::prepare_argc_argv(int& argc, char** argv, char* cmd_line)
   {

      char* pPtr = nullptr;

      char* p;

      char* psz = cmd_line;

      enum enum_state
      {

         e_state_initial,

         state_quote,

         state_non_space,

      };

      enum_state e = e_state_initial;

      char quote = '\0';

      while (psz != nullptr && *psz != '\0')
      {

         if (e == e_state_initial)
         {

            if (*psz == ' ')
            {

               unicode_increment(psz);

            }
            else if (*psz == '\"')
            {

               quote = '\"';

               unicode_increment(psz);

               argv[argc++] = (char*)psz;

               e = state_quote;

            }
            else if (*psz == '\'')
            {

               quote = '\'';

               unicode_increment(psz);

               argv[argc++] = (char*)psz;

               e = state_quote;

            }
            else
            {

               argv[argc++] = (char*)psz;

               unicode_increment(psz);

               e = state_non_space;

            }

         }
         else if (e == state_quote)
         {

            if (*psz == '\\')
            {

               memory_transfer(psz, psz + 1, ansi_len(psz));

               unicode_increment(psz);

            }
            else if (*psz == quote)
            {

               p = unicode_next(psz);

               *psz = '\0';

               psz = p;

               e = e_state_initial;

            }
            else
            {

               unicode_increment(psz);

            }

         }
         else
         {

            if (*psz == ' ')
            {

               p = unicode_next(psz);

               *psz = '\0';

               psz = p;

               e = e_state_initial;

            }
            else
            {

               unicode_increment(psz);

            }

         }

      }

      argv[argc] = nullptr;

   }


   int shell::command_system(const ::scoped_string& scopedstr, const class ::time& timeOut, const ::file::path& pathWorkingDirectory, ::e_display edisplay)
   {

      trace_function tracefunction = std_inline_log();

      tracefunction.m_timeTimeout = timeOut;

      return command_system(scopedstr, tracefunction, pathWorkingDirectory, edisplay);

   }


   bool shell::is_executable_in_path(const ::scoped_string& scopedstr)
   {

      return m_pshellComposite->is_executable_in_path(scopedstr);

   }


   ::string shell::get_output(const ::scoped_string& scopedstr, const class ::time& timeOut)
   {

      status_pointer <::string> pstring;

      __construct_new(pstring);

      trace_function tracefunction = [pstring](enum_trace_level eTraceLevel, const scoped_string& str, bool bCarriage)
         {

            pstring->m_payload += str + (bCarriage ? "\r" : "\n");

         };

      tracefunction.m_timeTimeout = timeOut;

      auto iExitCode = command_system(scopedstr, tracefunction);

      if (iExitCode != 0)
      {

         throw ::exception(error_failed);

      }

      return pstring->m_payload;

   }


   ::string shell::get_command_output(const ::scoped_string& scopedstr, const class ::time& timeOut)
   {

      ::string strOutput;

      auto iExitCode = get_command_output(strOutput, scopedstr, timeOut);

      if (iExitCode != 0)
      {

         throw ::exception(error_failed);

      }

      return strOutput;

   }



   ::i32 shell::get_command_output(::string& strOutput, const ::scoped_string& scopedstr, const class ::time& timeOut)
   {

      status_pointer <::string> pstring;

      __construct_new(pstring);

      trace_function tracefunction = [pstring](enum_trace_level eTraceLevel, const scoped_string& str, bool bCarriage)
         {

            pstring->m_payload += str + (bCarriage ? "\r":"\n");

         };

      tracefunction.m_timeTimeout = timeOut;

      auto iExitCode = command(scopedstr, tracefunction);

      strOutput = pstring->m_payload;

      return iExitCode;

   }


   ::string shell::get_unix_shell_command_output(const ::scoped_string& scopedstr, const class ::time& timeOut)
   {

      ::string strOutput;

      auto iExitCode = get_unix_shell_command_output(strOutput, scopedstr, timeOut);

      if (iExitCode != 0)
      {

         throw ::exception(error_failed);

      }

      return strOutput;

   }


   ::i32 shell::get_unix_shell_command_output(::string& strOutput, const ::scoped_string& scopedstr, const class ::time& timeOut)
   {

      status_pointer <::string> pstring;

      __construct_new(pstring);

      trace_function tracefunction = [pstring](enum_trace_level eTraceLevel, const scoped_string& str, bool bCarriage)
         {

            pstring->m_payload += str + (bCarriage ? "\r":"\n" );

         };

      tracefunction.m_timeTimeout = timeOut;

      auto iExitCode = unix_shell_command(scopedstr, tracefunction);

      strOutput = pstring->m_payload;

      return iExitCode;

   }


   int shell::command(const ::scoped_string& scopedstr, const trace_function& tracefunction)
   {

      return command_system(scopedstr, tracefunction);

   }


   int shell::command_system(const ::scoped_string& scopedstr, const trace_function& tracefunction, const ::file::path& pathWorkingDirectory, ::e_display edisplay)
   {

      return m_pshellComposite->command_system(scopedstr, tracefunction, pathWorkingDirectory, edisplay);

   }


   //void shell::open_terminal_and_run(const ::scoped_string& scopedstr)
   //{

   //   this->command_system(scopedstr, ::std_inline_log());

   //}


   void shell::launch_command_system(const ::scoped_string& scopedstr, const ::file::path& pathWorkingDirectory, ::e_display edisplay)
   {

      throw ::interface_only();

   }



   bool shell::has_command(const ::scoped_string& scopedstrCommand)
   {

      return has_unix_shell_command(scopedstrCommand);

   }


   bool shell::has_unix_shell_command(const ::scoped_string& scopedstrCommand)
   {

      try
      {

         ::string strCommand;

         strCommand.formatf("command -v %s", scopedstrCommand.c_str());

         ::string strOutput;

         auto iExitCode = get_unix_shell_command_output(strOutput, strCommand, 1_min);

         return iExitCode == 0 || strOutput.has_char();

      }
      catch (...)
      {

      }

      return false;

   }


   //#ifdef LINUX


   int shell::unix_shell_command(const ::scoped_string& scopedstrCommand, const trace_function& tracefunction)
   {

      try
      {

         string strEscaped = scopedstrCommand;

         ::string strCommand;

         informationf("Current Directory: %s\n", acmedirectory()->get_current().c_str());
         informationf("%s\n", strEscaped.c_str());

         //if (m_bMsys)
         //{

         //   strCommand = "\"C:\\msys64\\usr\\bin\\bash.exe\" -c \'" + strEscaped + "\'";

         //}
         //else
         {

            strCommand = "\"C:\\Program Files\\Git\\bin\\bash.exe\" -l -c \"" + strEscaped + "\"";

         }

         //

         auto iExitCode = this->command_system(strCommand, tracefunction);

         ///command_system("cmd.exe -c \"C:\\msys64\\msys2_shell.cmd\" \"" + strEscaped + "\"");

         return iExitCode;

      }
      catch (...)
      {

      }

      return -1;

   }


   ::string shell::unix_shell_command_string(const ::scoped_string& scopedstrCommand)
   {

      ::string strLog;

      auto iExitCode = unix_shell_command(scopedstrCommand, [&strLog](auto etracelevel, auto str, bool bCarriage)
         {

            strLog += ::string(str) + (bCarriage? "\r":"\n");

         });

      return strLog;

   }


#ifdef WINDOWS_DESKTOP


   ::file::path shell::_get_power_shell_path()
   {

      throw interface_only();

      return {};

   }


   ::file::path shell::_get_cmd_path()
   {

      throw interface_only();

      return {};

   }

#endif

   
} // namespace acme



