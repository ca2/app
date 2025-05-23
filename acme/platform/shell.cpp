// Created by camilo 2024-03-07 18:41 <3ThomasBorregaardSoresen!!
#include "framework.h"
#include "shell.h"
#include "acme/constant/posix_shell.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/status.h"
#include "acme/filesystem/filesystem/directory_system.h"
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

      tracefunction.set_timeout(timeOut);

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

      tracefunction.set_timeout(timeOut);

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



   int shell::get_command_output(::string& strOutput, const ::scoped_string& scopedstr, const class ::time& timeOut)
   {

      status_pointer <::string> pstring;

      __construct_new(pstring);

      trace_function tracefunction = [pstring](enum_trace_level eTraceLevel, const scoped_string& str, bool bCarriage)
         {

            pstring->m_payload += str + (bCarriage ? "\r":"\n");

         };

      tracefunction.set_timeout(timeOut);

      auto iExitCode = command(scopedstr, tracefunction);

      strOutput = pstring->m_payload;

      return iExitCode;

   }


   ::string shell::get_posix_shell_command_output(const ::scoped_string& scopedstr, enum_posix_shell eposixshell, const class ::time& timeOut)
   {

      ::string strOutput;

      auto iExitCode = get_posix_shell_command_output(strOutput, scopedstr, eposixshell, timeOut);

      if (iExitCode != 0)
      {

         throw ::exception(error_failed);

      }

      return strOutput;

   }


   int shell::get_posix_shell_command_output(::string& strOutput, const ::scoped_string& scopedstr, enum_posix_shell eposixshell, const class ::time& timeOut)
   {

      status_pointer <::string> pstring;

      __construct_new(pstring);

      trace_function tracefunction = [pstring](enum_trace_level eTraceLevel, const scoped_string& str, bool bCarriage)
         {

            pstring->m_payload += str + (bCarriage ? "\r":"\n" );

         };

      tracefunction.set_timeout(timeOut);

      auto iExitCode = posix_shell_command(scopedstr, eposixshell, tracefunction);

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

      throw ::interface_only();

      //return has_posix_shell_command(scopedstrCommand, eposix);

      return false;

   }


   bool shell::has_posix_shell_command(const ::scoped_string& scopedstrCommand, enum_posix_shell eposixshell)
   {

      try
      {

         ::string strCommand;

         strCommand.formatf("command -v %s", scopedstrCommand.c_str());

         ::string strOutput;

         auto iExitCode = get_posix_shell_command_output(strOutput, strCommand, eposixshell, 1_min);

         return iExitCode == 0 || strOutput.has_character();

      }
      catch (...)
      {

      }

      return false;

   }


   bool shell::posix_shell_protocol_begins_eat(enum_posix_shell& eposixshell, ::string& str)
   {

      if (str.case_insensitive_begins_eat("posix://"))
      {
         
#if defined(WINDOWS_DESKTOP)

         eposixshell = e_posix_shell_git_bash;
         
#else
         
         eposixshell = e_posix_shell_system_default;
         
#endif

         return true;

      }
#if defined(WINDOWS_DESKTOP)
      else if (str.case_insensitive_begins_eat("msys2://"))
      {

         eposixshell = e_posix_shell_msys2;

         return true;

      }
#endif
      return false;

   }


   void shell::defer_install_posix_shell_command(const ::scoped_string& scopedstr, enum_posix_shell eposixshell, const trace_function& tracefunction)
   {

      int iTry = 0;

      ::string strOutput;

      for(; iTry < 3; iTry++)
      {

         if (has_posix_shell_command(scopedstr, eposixshell))
         {

            return;

         }

         if (iTry > 0)
         {

            ::string strLine;
            
            strLine.append_formatf("Retrying to install_posix_shell_command(\"%s\",...) Attempt no. %d...", scopedstr.c_str(), iTry + 2);

            tracefunction(e_trace_level_warning, strOutput, false);

         }

         install_posix_shell_command(scopedstr, eposixshell, tracefunction);

         preempt((iTry + 1) * 3_s);

      }

      ::string strMessage;

      strMessage.formatf("Failed to install command \"%s\" after %d attempts with output: \"%s\"",
         scopedstr.c_str(), iTry, strOutput.c_str());

      tracefunction(e_trace_level_error, strMessage, false);

      throw ::exception(error_failed, strMessage);

   }

   
   //bool shell::has_posix_shell_command(const ::scoped_string& scopedstr, enum_posix_shell eposixshell)
   //{

   //   throw ::interface_only();

   //   return false;

   //}

   
   void shell::install_posix_shell_command(const ::scoped_string& scopedstr, enum_posix_shell eposixshell, const ::trace_function & tracefunction)
   {

      throw ::interface_only();

   }


   ::string shell::posix_shell_command_install_package(const ::scoped_string& scopedstr, enum_posix_shell eposixshell)
   {

      return scopedstr;

   }


   int shell::synchronous_posix_terminal(const ::scoped_string& scopedstrCommand, enum_posix_shell eposixshell, const trace_function& tracefunction)
   {

      throw interface_only();

      return -1;

   }


   int shell::posix_shell_command(const ::scoped_string& scopedstrCommand, enum_posix_shell eposixshell, const trace_function& tracefunction)
   {
      
      if(m_pshellComposite != this)
      {
       
         return m_pshellComposite->posix_shell_command(scopedstrCommand, eposixshell, tracefunction);
         
      }

      try
      {

         string strEscaped = scopedstrCommand;

         ::string strCommand;

         informationf("Current Directory: %s\n", directory_system()->get_current().c_str());
         informationf("%s\n", strEscaped.c_str());

#ifdef WINDOWS_DESKTOP

         if (eposixshell == e_posix_shell_msys2)
         {

            strCommand = "\"C:\\msys64\\usr\\bin\\bash.exe\" -l -c \'" + strEscaped + "\'";

         }
         else
         {

            strCommand = "\"C:\\Program Files\\Git\\bin\\bash.exe\" -l -c \"" + strEscaped + "\"";

         }

#else

         strCommand = strEscaped;

#endif 

         auto iExitCode = this->command_system(strCommand, tracefunction);

         ///command_system("cmd.exe -c \"C:\\msys64\\msys2_shell.cmd\" \"" + strEscaped + "\"");

         return iExitCode;

      }
      catch (...)
      {

      }

      return -1;

   }


   //::string shell::posix_shell_command_string(const ::scoped_string& scopedstrCommand, enum_posix_shell eposixshell)
   //{

   //   ::string strLog;

   //   auto iExitCode = posix_shell_command(scopedstrCommand, eposixshell, [&strLog](auto etracelevel, auto str, bool bCarriage)
   //      {

   //         strLog += ::string(str) + (bCarriage? "\r":"\n");

   //      });

   //   return strLog;

   //}


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


   //int shell::_msys2_shell_command_output(::string& strOutput, const ::scoped_string& scopedstr, const class ::time& timeOut)
   //{

   //   status_pointer <::string> pstring;

   //   __construct_new(pstring);

   //   trace_function tracefunction = [pstring](enum_trace_level eTraceLevel, const scoped_string& str, bool bCarriage)
   //      {

   //         pstring->m_payload += str + (bCarriage ? "\r" : "\n");

   //      };

   //   tracefunction.m_timeTimeout = timeOut;

   //   auto iExitCode = posix_shell_command(scopedstr, eposixshell, tracefunction);

   //   strOutput = pstring->m_payload;

   //   return iExitCode;

   //}


#endif

   void shell::launch_process(const ::scoped_string & scopedstr)
   {
      
      
   }
   
} // namespace acme



