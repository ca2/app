#include "framework.h"
#include "acme/node/posix/pipe.h"
#include "acme/node/apple/process.h"
#include "acme/platform/app_core.h"
#include "acme/platform/static_start.h"

#include <spawn.h>
extern char * const * environ;


struct chldstatus
{

   bool m_bRet;
   int  m_iExitCode;


};


typedef int_ptr_map < chldstatus > chldstatus_map;


critical_section * g_pcsPid2 = nullptr;


chldstatus_map * g_ppid = nullptr;


critical_section * get_pid_cs()
{

   cslock cs(::acme::g_pcsGlobal);

   if(g_pcsPid2 == nullptr)
   {

      g_pcsPid2 = aaa_primitive_new critical_section();

      g_ppid = aaa_primitive_new chldstatus_map();


   }

   return g_pcsPid2;

}


chldstatus get_chldstatus(int iPid)
{

   cslock synchronouslock(get_pid_cs());

   return g_ppid->operator[](iPid);

}

// must be called under get_pid_cs lock
void init_chldstatus(int iPid)
{

   auto & s = g_ppid->operator[](iPid);

   s.m_bRet = false;

   s.m_iExitCode = 0;

}


void ansios_sigchld_handler(int sig)
{

   int saved_errno = errno;

   int iExitCode;

   int iPid;

   while((iPid = waitpid(-1, &iExitCode,
                         WUNTRACED
#ifdef WNOHANG
                         | WNOHANG
#endif
#ifdef WCONTINUED
                         | WCONTINUED
#endif
                        )) > 0)
   {

      {

         cslock synchronouslock(get_pid_cs());

         auto ppair = g_ppid->plookup(iPid);

         if(ppair != nullptr)
         {

            ppair->element2().m_bRet = true;

            ppair->element2().m_iExitCode = iExitCode;

         }

      }

   }

   errno = saved_errno;

}


void install_sigchld_handler()
{

   struct sigaction sa;

   zero(sa);

   sa.sa_handler = &ansios_sigchld_handler;

   sigemptyset(&sa.sa_mask);

   sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;

   sigaction(SIGCHLD, &sa, nullptr);

}


CLASS_DECL_ACME void process_get_os_priority(int * piOsPolicy, int iCa2Priority);


namespace apple
{


   operating_system::process()
   {

   }


   process::~process()
   {

   }


   bool process::create_child_process(const ::scoped_string & scopedstrCmdLine,bool bPiped,const ::scoped_string & scopedstrDir, ::enum_priority epriority)
   {

      if(!::operating_system::process::create_child_process(scopedstrCmdLine, bPiped, pszDir, epriority))
      {
         
         return false;
         
      }

      string_array straParam;

      address_array < char * > argv;

      straParam.explode_command_line(scopedstrCmdLine, &argv);

      posix_spawnattr_t attr;

      posix_spawnattr_init(&attr);



      posix_spawn_file_actions_t actions;

      posix_spawn_file_actions_init(&actions);

//      if(bPiped)
//      {
//
//         pipe * ppipeOut = m_pipe.m_sppipeOut.cast < pipe >();
//
//         posix_spawn_file_actions_adddup2(&actions, ppipeOut->m_fd[1],STDOUT_FILENO);
//
//         posix_spawn_file_actions_adddup2(&actions, ppipeOut->m_fd[1],STDERR_FILENO);
//
//         pipe * ppipeIn = m_pipe.m_sppipeIn.cast < pipe >();
//
//         posix_spawn_file_actions_adddup2(&actions, ppipeIn->m_fd[0],STDIN_FILENO);
//
//      }

      address_array < char * > env;

      char * const * e = environ;

      string strFallback;

#ifdef MACOS

      strFallback = ::dir::ca2_module();

#endif

      if(case_insensitive_string_begins(strFallback, "/Users/"))
      {

         ::collection::index i = 0;

         int iPrevious = -1;

         const ::scoped_string & scopedstr;

         while((scopedstr = environ[i]) != nullptr)
         {
            if(i <= iPrevious)
               break;

            env.add((char *) psz);

            iPrevious = (int) i;

            i++;

         }

#ifdef MACOS

         string strCurrent = getenv("DYLD_FALLBACK_LIBRARY_PATH");

         if(strCurrent.has_character())
         {

            strFallback += ":" + strCurrent;

         }

         strFallback = string("DYLD_FALLBACK_LIBRARY_PATH=") + strFallback;

         env.add((char *) (const char *) strFallback);

#endif

         env.add(nullptr);

         e = (char * const *)env.get_data();

      }


      int status = 0;

      {

         cslock synchronouslock(get_pid_cs());

         status = posix_spawn(&m_iPid,argv[0],&actions,&attr,(char * const *)argv.get_data(),e);

         init_chldstatus(m_iPid);

      }


      if(epriority != (int) ::e_priority_none)
      {

         int iOsPriority;
         
         process_get_os_priority(&iOsPriority, epriority);

         setpriority(PRIO_PROCESS,m_iPid,iOsPriority);

      }

      return status == 0;

   }


   bool process::has_exited()
   {

      int iExitCode;

#if 0

      {

         int iPid;

         iPid = waitpid(m_iPid, &iExitCode,
                        WUNTRACED
#ifdef WNOHANG
                        | WNOHANG
#endif
#ifdef WCONTINUED
                        | WCONTINUED
#endif
                       );

         if(iPid == 0)
         {

            return false;

         }
         else if(iPid == -1)
         {

            return true;

         }

      }

#else

      {

         auto chldstatus = get_chldstatus(m_iPid);

         if(!chldstatus.m_bRet)
         {

            return false;

         }

         iExitCode = chldstatus.m_iExitCode;

      }

#endif

      if(WIFEXITED(iExitCode))
      {

         m_exitstatus.m_iExitCode = WEXITSTATUS(iExitCode);

         return true;

      }
      else if(WIFSIGNALED(iExitCode))
      {

         m_exitstatus.m_iExitSignal = WTERMSIG(iExitCode);

         m_exitstatus.m_iExitCode = I32_MINIMUM;

         return true;

      }
      else if(WIFSTOPPED(iExitCode))
      {

         m_exitstatus.m_iExitStop = WSTOPSIG(iExitCode);

         m_exitstatus.m_iExitCode = I32_MINIMUM;

         return true;

      }
#ifdef WIFCONTINUED
      else if(WIFCONTINUED(iExitCode))
      {

         return false;

      }
#endif

      return true;

   }


   bool process::synch_elevated(const ::scoped_string & scopedstrCmdLineParam,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut)
   {

#if defined(MACOS)

      uid_t uid = getuid();

      string str(scopedstrCmdLineParam);

      {

         string_array stra;

         address_array < char * > argv;

         stra.explode_command_line(str, &argv);

         str = argv[0];

      }

      string strFallback;

      ::file::path path = str;

      if(file()->exists(path.folder() / "libaura.dylib"))
      {

         ::file::path folderNew = path.folder();

         folderNew -= 3;

         if(file()->exists(folderNew / "libaura.dylib"))
         {

            strFallback = folderNew;

         }
         else
         {

            strFallback = path.folder();

         }

      }
      else
      {

         string strFolder = path.folder();

         if(strFolder.case_insensitive_ends_eat(path.folder()/"Contents"/ "MacOS"))
         {

            strFallback = strFolder;

         }
         else
         {

            strFallback = ::dir::ca2_module();

         }

      }

      string strFolder = strFallback;

      string strCurrent = getenv("DYLD_FALLBACK_LIBRARY_PATH");

      if(strCurrent == strFallback || string_ends(strCurrent, ":" + strFallback) || string_begins(strCurrent, strFallback + ":") || strCurrent.contains(":"+strFallback +":"))
      {

         strFallback = strCurrent;

      }
      else if(strCurrent.has_character())
      {

         strFallback += ":" + strCurrent;

      }

      setenv("DYLD_FALLBACK_LIBRARY_PATH", strFallback, true);

      // Create authorization matter
      OSStatus status;

      AuthorizationRef authorizationRef;

      // AuthorizationCreate and pass nullptr as the initial
      // AuthorizationRights set so that the AuthorizationRef gets created
      // successfully, and then later call AuthorizationCopyRights to
      // determine or extend the allowable rights.
      // http://developer.apple.com/qa/qa2001/qa1172.html
      status = AuthorizationCreate(nullptr, kAuthorizationEmptyEnvironment, kAuthorizationFlagDefaults, &authorizationRef);

      if (status != errAuthorizationSuccess)
      {

         informationf("Error Creating Initial Authorization: %d", status);

         return false;

      }

      // kAuthorizationRightExecute == "system.privilege.admin"
      AuthorizationItem right = {kAuthorizationRightExecute, 0, nullptr, 0};
      AuthorizationRights rights = {1, &right};
      AuthorizationFlags flags = kAuthorizationFlagDefaults | kAuthorizationFlagInteractionAllowed |
                                 kAuthorizationFlagPreAuthorize | kAuthorizationFlagExtendRights;



      // Call AuthorizationCopyRights to determine or extend the allowable rights.
      status = AuthorizationCopyRights(authorizationRef, &rights, nullptr, flags, nullptr);

      if (status != errAuthorizationSuccess)
      {

         informationf("Copy Rights Unsuccessful: %d", status);

         return false;

      }

      informationf("\n\n** %s **\n\n", "This command should work.");

//      string_array straParam;
//
      address_array < char * > argv;
//
//      straParam.add("/bin/bash");
//
//      straParam.add("-c");
//
//      string strC = "ignit_phase2 () { export DYLD_FALLBACK_LIBRARY_PATH=\""+strFallback+"\" ; cd "+strFolder+" ; "+string(scopedstrCmdLineParam)+" ; } ; ignit_phase2 ;";
////            string strC = "export DYLD_FALLBACK_LIBRARY_PATH="+strFallback;
//
//      straParam.add(strC);
//
//      for(::collection::index i = 0; i < straParam.get_count(); i++)
//      {
//
//         argv.add((char *)(const char *)straParam[i]);
//
//      }
//
//      argv.add(nullptr);


      //string strParam(scopedstrCmdLineParam);


      string_array straParam;

      straParam = get_c_args_for_c(scopedstrCmdLineParam);
      //straParam.add("uid=" + as_string(uid));
      for(::collection::index i = 0; i < straParam.get_count(); i++)
      {
         char * psz = (char *)(const char *)straParam[i];
         argv.add(scopedstr);

      }

      argv.add(nullptr);

      char *tool = (char * )argv[0];
      char **args = (char **) &argv.get_data()[1];
      FILE *pipe = nullptr;

//      int uid = getuid();

      informationf("---\n");
      informationf("---\n");
      informationf("---\n");
      informationf("---\n");
      informationf("---\n");
      informationf("---\n");
      informationf("---\n");
      informationf("---\n");
      informationf("---\n");
      informationf("---\n");
      informationf("---\n");
      informationf("---\n");
      informationf("---\n");
      informationf("---\n");
      informationf("---\n");
      informationf("---\n");
      informationf("---\n");
      informationf("---\n");
      informationf("---\n");
      informationf("---\n");

//      int i = setuid(0);

      //    if(i != 0)
      //  {
      //   informationf("Failed to setuid: %d", i);
      // return -1;
      //}


      /*
      string_array straParam;

      ref_array < char > argv;


      straParam.explode_command_line(scopedstrCmdLineParam, &argv);

      posix_spawnattr_t attr;

      posix_spawnattr_init(&attr);


      posix_spawn_file_actions_t actions;

      posix_spawn_file_actions_init(&actions);


      status = posix_spawn(&m_iPid,argv[0],&actions,&attr,(char * const *)argv.get_data(),environ);

      //int status = posix_spawn(&m_iPid,argv[0],nullptr,nullptr,(char * const *)argv.get_data(),environ);

      debug_print("synch_elevated : posix_spawn return status %d", status);
auto tickStart = ::duration::now();

      while(!has_exited() && tickStart.elapsed() < durationTimeOut.get_total_milliseconds())
      {
         sleep(100_ms);
      }
      unsigned int dwExitCode = 0;
      if(!has_exited(&dwExitCode))
      {
         if(pbTimeOut != nullptr)
         {
            *pbTimeOut = true;
         }
      }
      */

//      setuid(uid);

      status = AuthorizationExecuteWithPrivileges(authorizationRef, tool, kAuthorizationFlagDefaults, args, &pipe);
      if (status != errAuthorizationSuccess)
      {

         informationf("AuthorizationExecuteWithPrivileges Error: %d", status);

         return false;

      }

      /*

      straParam.erase_all();
      argv.erase_all();
      straParam.explode_command_line(scopedstrCmdLineParam, &argv);

      tool = (char * )argv[0];
      args = (char **) &argv.get_data()[1];
      pipe = nullptr;


      status = AuthorizationExecuteWithPrivileges(authorizationRef, tool, kAuthorizationFlagDefaults, args, &pipe);
      if (status != errAuthorizationSuccess)
      {
         informationf("AuthorizationExecuteWithPrivileges Error: %d", status);
         return -1;
      }

       */

      if(pipe != nullptr)
      {

//        int pptp_pid = 0;

         //       fscanf(pipe, "%d", &pptp_pid);
//         bool bNewLine = true;
//         ::collection::index i = 0;
//         while(i < 1000)
//         {
//            char szBuffer[1000];
//            memory_set(szBuffer, 0, sizeof(szBuffer));
//            fgets(szBuffer, sizeof(szBuffer), pipe);
//            if(szBuffer[sizeof(szBuffer)-2] == '\n' || szBuffer[sizeof(szBuffer)-2] == '\0')
//            {
//               if(bNewLine)
//               {
//                  string strLine = szBuffer;
//                  if(strLine.case_insensitive_begins_eat("application_pid="))
//                  {
//                     m_iPid = atoi(strLine);
//                     break;
//                  }
//               }
//               else
//               {
//                  bNewLine = true;
//               }
//            }
//            else
//            {
//               bNewLine = false;
//            }
//            i++;
      }

//         pid_t pptp_pid = 0;
//
//         fread(&pptp_pid,sizeof(pptp_pid),1,pipe); // get pid
//
//          m_iPid = pptp_pid;
auto tickStart = ::duration::now();

      unsigned int tickTimeout = (unsigned int) durationTimeOut.get_total_milliseconds();

      char sz[1025];

      int iRead;

      int iCount0 = 100;

      while(!has_exited() && tickStart.elapsed() < tickTimeout && iCount0 > 0)
      {
         memory_set(sz, 0, sizeof(sz));
         iRead =(int) fread(sz,1,1024, pipe);
         if(iRead >0)
         {
            ::information(sz);
         }
         else if(iRead <= 0)
         {
            iCount0--;
         }
         else if(ferror(pipe))
         {
            informationf("Error reading from file");
            break;
         }
         else
         {
         }

         sleep(100_ms);
      }
      if(!has_exited())
      {
         if(pbTimeOut != nullptr)
         {
            *pbTimeOut = true;
         }
      }

      /*         char c;

               int iRead;

               string strRead;

               while(true)
               {
                  iRead = fread(&c,1,1, pipe);
                  if(iRead == 1)
                  {
                     strRead += c;
                  }
                  else if(ferror(pipe))
                  {
                     informationf("Error reading from file");
                     break;
                  }
                  else
                  {
                  }
               }

               fclose(pipe);

               TRACE0(strRead);*/


      //}

      // The only way to guarantee that a credential acquired when you
      // request a right is not shared with other authorization instances is
      // to destroy the credential.  To do so, call the AuthorizationFree
      // function with the flag kAuthorizationFlagDestroyRights.
      // http://developer.apple.com/documentation/Security/Conceptual/authorization_concepts/02authconcepts/chapter_2_section_7.html
      status = AuthorizationFree(authorizationRef, kAuthorizationFlagDestroyRights);

      if (status != errAuthorizationSuccess)
      {
         informationf("AuthorizationFree Error: %d", status);
      }

      //return dwExitCode;
      return true;

#else

      string_array straParam;

      address_array < char * > argv;

#ifdef MACOS

      straParam.add("/usr/bin/osascript");
      straParam.add("-e");
      straParam.add("'do shell script \"" + string(scopedstrCmdLineParam) + "\" with administrator privileges'");

      argv.add((char *) (const char *) straParam[0]);
      argv.add((char *) (const char *) straParam[1]);
      argv.add((char *) (const char *) straParam[2]);
      argv.add(nullptr);

#else

      if (access("/usr/bin/gksu", X_OK) != 0)
      {

         m_exitstatus.m_iExitCode = -1;

         ::message_box(nullptr,"gksu is not installed, please install gksu.","Please, install gksu.",e_message_box_icon_information);

         return false;

      }

      string pszCmdLine = "/usr/bin/gksu " + string(scopedstrCmdLineParam);

      straParam.explode_command_line(scopedstrCmdLine, &argv);

#endif


      posix_spawnattr_t attr;

      posix_spawnattr_init(&attr);


      posix_spawn_file_actions_t actions;

      posix_spawn_file_actions_init(&actions);

      int status= 0;

      {

         cslock synchronouslock(get_pid_cs());

         status = posix_spawn(&m_iPid,argv[0],&actions,&attr,(char * const *)argv.get_data(),environ);

         init_chldstatus(m_iPid);

      }

      //int status = posix_spawn(&m_iPid,argv[0],nullptr,nullptr,(char * const *)argv.get_data(),environ);

      debug_print("synch_elevated : posix_spawn return status %d", status);
auto tickStart = ::duration::now();

      while(!has_exited() && tickStart.elapsed() < durationTimeOut.get_total_milliseconds())
      {

         sleep(100_ms);

      }

      unsigned int dwExitCode = 0;

      if(!has_exited())
      {

         if(pbTimeOut != nullptr)
         {

            *pbTimeOut = true;

         }

      }

#endif
      
      return true;

   }
   

} // namespace apple



