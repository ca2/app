#include "framework.h"
#include "apex/node/windows/_windows.h"


namespace windows
{


   process::process()
   {

      __memset(&m_pi,0,sizeof(PROCESS_INFORMATION));

      __memset(&m_si,0,sizeof(STARTUPINFO));

   }


   process::~process()
   {

      if(m_pi.hProcess != INVALID_HANDLE_VALUE && m_pi.hProcess != nullptr)
      {

         CloseHandle(m_pi.hProcess);

      }

      if(m_pi.hThread != INVALID_HANDLE_VALUE && m_pi.hThread != nullptr)
      {

         CloseHandle(m_pi.hThread);

      }

   }


   bool process::create_child_process(const char * pszCmdLine, bool bPiped, const char * pszDir, ::e_priority epriority)
   {

      if (!::process::process::create_child_process(pszCmdLine, bPiped, pszDir, epriority))
      {

         return false;

      }

      string szCmdline = pszCmdLine;

      bool bSuccess = false;

      m_si.cb = sizeof(STARTUPINFO);

      if(bPiped)
      {

         pipe * ppipeOut      = m_pipe.m_sppipeOut.cast < pipe >();

         m_si.hStdError       = ppipeOut->m_hWrite;

         m_si.hStdOutput      = ppipeOut->m_hWrite;

         pipe * ppipeIn       = m_pipe.m_sppipeIn.cast < pipe >();

         m_si.hStdInput       = ppipeIn->m_hRead;

         m_si.dwFlags         |= STARTF_USESTDHANDLES;

      }

      /* STARTUPINFO si;
      PROCESS_INFORMATION pi;
      __memset(&si, 0, sizeof(si));
      __memset(&pi, 0, sizeof(pi));
      si.cb = sizeof(si);
      si.dwFlags = STARTF_USESHOWWINDOW;
      si.wShowWindow = display_none; */
      //         if(!::CreateProcess(nullptr, (LPTSTR) (const char *) Context.dir().appdata("production\\build.bat"), nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi))
      m_si.dwFlags |= STARTF_USESHOWWINDOW;
      m_si.wShowWindow = display_none;


      ::u32 dwPriorityClass = ::get_os_priority_class(epriority);

      wstring wstrDir(pszDir);

      const unichar * pwszDir;

      if (pszDir == nullptr || *pszDir == '\0')
      {

         pwszDir = nullptr;

      }
      else
      {

         pwszDir = wstrDir;

      }

      // create the child process.

      wstring wstrCommandLine;

      if(::str::ends_ci(szCmdline,".bat"))
      {

         string strCmd;

         strCmd = "";
         strCmd += szCmdline;
         strCmd += "";

         wstrCommandLine = strCmd;

      }
      else
      {

         wstrCommandLine = szCmdline;

      }

      unichar * pwszCommandLine = (unichar * ) (const unichar *) wstrCommandLine;
      ::u32 dwFlags = 0;
      if (is_true("inherit"))
      {
         dwFlags = CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT;
      }

      bSuccess = CreateProcessW(nullptr,
                                pwszCommandLine,
                                nullptr,          // process security attributes
                                nullptr,          // primary thread security attributes
                                TRUE,          // handles are inherited
                                dwFlags | dwPriorityClass,             // creation flags
                                nullptr,          // use parent's environment
                                pwszDir,
                                &m_si,  // STARTUPINFO pointer
                                &m_pi) != FALSE;  // receives PROCESS_INFORMATION

      // If an error occurs, exit the application.
      if (!bSuccess)
      {
         ::u32 dwLastError = ::get_last_error();
         string strMessage = get_system_error_message(dwLastError);
         output_debug_string(pwszCommandLine);
         output_debug_string("\r\n");
         output_debug_string("CreateProcessW Error!!");
         output_debug_string("\r\n");
         output_debug_string(strMessage + " (" + __str((u32) dwLastError) + ")");
         output_debug_string("\r\n");
         return false;
      }
      else
      {
         m_iPid = m_pi.dwProcessId;
         // close handles to the child process and its primary thread.
         // Some applications might keep these handles to monitor the status
         // of the child process, for example.

         //CloseHandle(m_pi.hProcess);
         //CloseHandle(m_pi.hThread);
      }

      return true;

   }


   bool process::has_exited()
   {

      ::u32 dwExitCode;

      bool bExited;

      if(!GetExitCodeProcess(m_pi.hProcess,&dwExitCode))
      {

         m_exitstatus.m_iExitCode = -1;

         bExited = true;

      }
      else
      {

         if(dwExitCode == STILL_ACTIVE)
         {

            bExited = false;

         }
         else
         {

            bExited = true;

         }

      }

      m_exitstatus.m_iExitCode = dwExitCode;

      return bExited;

   }


   bool process::synch_elevated(const char * pszCmdLine,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut)
   {

      ::u32 dwExitCode = 0;

      HANDLE h = nullptr;

      ::str::parse parse(pszCmdLine,strlen(pszCmdLine), "= ");

      parse.EnableQuote(true);

      string strPath;

      if(parse.getrestlen())
      {

         parse.getword(strPath);

      }

      string strParam;

      parse.getrest(strParam);

      if(VistaTools::RunElevated(nullptr,strPath,strParam,nullptr,&h))
      {

         dwExitCode = 0;

      }
      else
      {

         return false;

      }

      bool bTimedOut = true;
auto tickStart = ::tick::now();

      ::u32 tickTimeout = durationTimeOut.tick_duration();

      while(tickStart.elapsed() < tickTimeout)
      {

         if (!::GetExitCodeProcess(h, &dwExitCode))
         {

            break;

         }

         if(dwExitCode != STILL_ACTIVE)
         {

            bTimedOut = false;

            break;

         }

         Sleep(100);

      }

      ::CloseHandle(h);

      if(pbTimeOut != nullptr)
      {

         *pbTimeOut = bTimedOut;

      }

      return !bTimedOut;

   }


   bool process::kill()
   {
      ::system(string("taskkill /F /T /PID " ) + __str((i32) m_pi.dwProcessId));
      return true;
      //return TerminateProcess(m_pi.hThread, -1) != FALSE;

   }




} // namespace windows











