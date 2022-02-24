#include "framework.h"
#include "apex/networking/sockets/_.h"
//#include "apex/platform/app_core.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/filesystem/filesystem/acme_file.h"


//CLASS_DECL_APEX string task_get_name();

#include <stdio.h>
// #include <stdarg.h>

#if defined(LINUX) || defined(ANDROID)
//#include <sys/types.h>
//

#ifdef COMPILE_WITH_VALGRIND

#if !defined(RASPBIAN) && !defined(ANDROID)
#include <valgrind/valgrind.h>
#endif

#endif


#define ENABLE_TRACE 1
#elif defined(WINDOWS_DESKTOP)
#define ENABLE_TRACE 1
#endif

namespace apex
{





   log::log()
   {

#if !ENABLE_TRACE

      m_bTrace = false;

#else

      defer_create_mutex();
      
#endif
      

   }


   void log::initialize_log(enum_trace_level etracelevelMin, const ::atom & atom)
   {

      /*auto estatus = */ __compose_new(m_ptrace);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_bLog               = true;

      m_pfile              = nullptr;

      m_bInitialized       = false;

      m_bLogFileName       = false;

      m_bLogFunctionName   = false;

      m_bLogThreadName     = false;



      m_iYear           = -1;
      m_iMonth          = -1;
      m_iDay            = -1;
      m_straSeparator.add("\r\n");
      m_straSeparator.add("\r");
      m_straSeparator.add("\n");

      for (index i = e_trace_category_first; i < e_trace_category_count; i++)
      {

         set_trace_category((enum_trace_category)i, etracelevelMin);

      }

      //set_trace_category(trace_category_general, e_trace_level_information);
      //set_trace_category(trace_category_com, e_trace_level_warning);
      //set_trace_category(trace_category_qi, e_trace_level_warning);
      //set_trace_category(trace_category_registrar, "category_Registrar", e_trace_level_warning);
      //set_trace_category(trace_category_refcount, "category_Refcount", e_trace_level_warning);
      //set_trace_category(trace_category_windowing, "category_Windowing", e_trace_level_warning);
      //set_trace_category(trace_category_controls, "category_Controls", e_trace_level_warning);
      //set_trace_category(trace_category_hosting, "category_Hosting", e_trace_level_warning);
      //set_trace_category(trace_category_dbclient, "category_DBClient", e_trace_level_warning);
      //set_trace_category(trace_category_dbprovider, "category_DBProvider", e_trace_level_warning);
      //set_trace_category(trace_category_snapin, "category_Snapin", e_trace_level_warning);
      //set_trace_category(trace_category_notimpl, "category_NotImpl", e_trace_level_warning);
      //set_trace_category(trace_category_allocation, "category_Allocation", e_trace_level_warning);
      //set_trace_category(trace_category_exception, "category_Exception", e_trace_level_warning);
      //set_trace_category(trace_category_time, "category_Time", e_trace_level_warning);
      //set_trace_category(trace_category_cache, "category_Cache", e_trace_level_warning);
      //set_trace_category(trace_category_stencil, "category_Stencil", e_trace_level_warning);
      //set_trace_category(trace_category_string, "category_String", e_trace_level_warning);
      //set_trace_category(trace_category_map, "category_Map", e_trace_level_warning);
      //set_trace_category(trace_category_util, "category_Util", e_trace_level_warning);
      //set_trace_category(trace_category_security, "category_Security", e_trace_level_warning);
      //set_trace_category(trace_category_sync, "category_Sync", e_trace_level_warning);
      //set_trace_category(trace_category_isapi, "category_ISAPI", e_trace_level_warning);

      //set_trace_category(trace_category_user, "category_User", e_trace_level_warning);
      //set_trace_category(trace_category_user2, "category_User2", e_trace_level_warning);
      //set_trace_category(trace_category_user3, "category_User3", e_trace_level_warning);
      //set_trace_category(trace_category_user4, "category_User4", e_trace_level_warning);


      //set_trace_category(trace_category_appmsg, "AppMsg", e_trace_level_warning);        // Main message pump trace (includes DDE)
      //set_trace_category(trace_category_winmsg, "category_WinMsg", e_trace_level_warning);         // Windows message tracing
      //set_trace_category(trace_category_cmdrouting, "category_CmdRouting", e_trace_level_warning);     // Windows command routing trace
      //set_trace_category(trace_category_ole, "category_Ole", e_trace_level_warning);           // special OLE callback trace
      //set_trace_category(trace_category_database, "category_Database", e_trace_level_warning);      // special database trace
      //set_trace_category(trace_category_internet, "category_Internet", e_trace_level_warning);      // special Internet client trace
      //set_trace_category(trace_category_dumpcontext, "category_dumpContext", e_trace_level_warning);    // traces from dump_context
      //set_trace_category(trace_category_memory, "category_Memory", e_trace_level_warning);       // matter non-kernel memory traces
      //set_trace_category(trace_category_html, "category_Html", e_trace_level_warning);          // Html traces
      //set_trace_category(trace_category_socket, "category_Socket", e_trace_level_warning);       // socket traces


      synchronous_lock synchronouslock(mutex());

      if (m_bInitialized)
      {

         return;

      }

      m_atom = atom;

      m_bInitialized = true;


      ::file::path pathTrace = m_psystem->m_pacmedir->system() / "trace.txt";

#ifdef __DEBUG

      if (!m_psystem->m_pacmefile->exists(pathTrace))
      {

         m_psystem->m_pacmefile->put_contents(pathTrace, "yes");

      }


#endif // __DEBUG

#ifdef COMPILE_WITH_VALGRIND

#if !defined(RASPBIAN) && !defined(ANDROID) && !defined(WINDOWS)
      if (!RUNNING_ON_VALGRIND)
#endif
      {

         m_bTrace = ::file_is_true_dup(pathTrace) || ::is_debugger_attached();

         //m_bTrace = ::file_is_true_dup(pathTrace);

      }

#endif

      if (m_psystem->m_pacmefile->is_true(m_psystem->m_pacmedir->system() / "log.txt"))
      {

         m_bLog = true;

      }

#ifdef COMPILE_WITH_VALGRIND

#if defined(LINUX) && !defined(RASPBIAN)

      else if (RUNNING_ON_VALGRIND)
      {

         m_bLog = false;

      }

#endif

#endif


      else
      {


         m_bLog = false;
         //m_bLog = is_debugger_attached() != false;

      }
      

      synchronouslock.unlock();

      INFORMATION("<log>Log Initialized!!</log>");

//      return true;


      //return ::success;

   }


   log::~log()
   {

      //::acme::del(m_ptrace);

   }


//   extern __pointer(::application) g_papp;

   CLASS_DECL_APEX i32 SimpleDebugReport(i32 iReportType, const char * pszFileName,i32 iLine,const char *,const char * pszFormat, va_list list)
   {
#ifdef WIN32

      if(iReportType == _CRT_ASSERT)
      {

         if(is_debugger_attached())
         {

            string str;

            str += "\r\nAssertion Failed \r\n";
            str += "File : ";
            str += pszFileName;
            str += "\r\nLine : ";
            str += __string(iLine);
            str += "\r\n";

            string strCaption;

            strCaption = "Assertion Failed";

            output_debug_string(wstring(str));
            /*if(message_box(nullptr, str, strCaption, e_message_box_icon_information | MB_OKCANCEL | MB_DEFBUTTON1) == e_dialog_result_cancel)
            {
               string strCmdLine = "\"C:\\Program Files (x86)\\Microsoft Visual Studio 11.0\\Common7\\IDE\\devenv.exe\" /edit \""+string(pszFileName)+ "\" /command \"edit.goto "+__string(iLine)+"\"";
               class ::system(strCmdLine);
               exit(0);
            }
            */
         }



      }
      else
      {

         char buf[2048];
         vsnprintf_s(buf, sizeof(buf), sizeof(buf), pszFormat, list);
         output_debug_string(wstring(buf));

      }

#else
      vprintf(pszFormat, list);
#endif
      return 0;
   }



   void log::success(const char * psz)
   {

      INFORMATION(psz);

   }


   //void log::tracev(e_trace_category ecategory, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args)
   //{

   //   string str;

   //   str.format(pszFormat, args);

   //   alog(ecategory, elevel, pszFunction, pszFile, iLine, str);

   //}


//   void log::__tracea(enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * psz) const
//   {
//
//      //const char * pszTopicText = ::is_set(pobject) ? pobject->topic_text() : nullptr;
//
//      //synchronous_lock sl2(&m_mutexTrace);
//
////      synchronous_lock sl2(mutex());
////
////      ::trace::category * pcategory = nullptr;
////
////      if (elevel != e_trace_level_none)
////      {
////
////         pcategory = m_ptrace->enabled_get(this);
////
////         if (pcategory == nullptr)
////         {
////
////            return;
////
////         }
////
////      }
////
////      if (!m_bLog)
////      {
////
////#ifndef DEBUG
////
////         if (elevel >= e_trace_level_error)
////         {
////
////#endif // !DEBUG
////
////            string str;
////
////            if (::is_set(pszTopicText))
////            {
////
////               string strTopicText(pszTopicText);
////
////               if (strTopicText.has_char())
////               {
////
////                  ::str::begins_eat_ci(strTopicText, "class ");
////
////                  ::str::begins_eat_ci(strTopicText, "struct ");
////
////                  str += strTopicText;
////
////                  str += "> ";
////
////               }
////
////            }
////
////            str += psz;
////
////            str += "\n";
////
////            output_debug_string(str);
////
////#ifndef DEBUG
////
////         }
////
////#endif // !DEBUG
////
////         return;
////
////      }
////
////      string_array stra;
////
////      stra.add_lines(psz, false);
////
////      string strPre;
////
////      ::datetime::time time;
////      time = time.get_current_time();
////      time.Format(strPre, "%Y-%m-%d %H:%M:%S");
////      string strTick;
////      auto millisTotal = ::get_millis() - ::first_milli();
////      i64 uiMillis = millisTotal % 1000;
////      i64 uiTotalSeconds = millisTotal / 1000;
////      i64 uiSeconds = uiTotalSeconds % 60;
////      i64 uiTotalMinutes = uiTotalSeconds / 60;
////      i64 uiMinutes = uiTotalMinutes % 60;
////      i64 uiTotalHours = uiTotalMinutes / 60;
////      i64 uiHours = uiTotalHours % 24;
////      i64 uiTotalDays = uiTotalHours / 24;
////      // sipman LCTV learning to format hours, minutes and seconds.... (me (re) learning too)...
////      if (uiTotalDays > 0)
////      {
////         strTick.format(" %d:%d:%d:%d.%03d ", uiTotalDays, uiHours, uiMinutes, uiSeconds, uiMillis);
////      }
////      else if(uiTotalHours > 0)
////      {
////         strTick.format(" %d:%d:%d.%03d ", uiHours, uiMinutes, uiSeconds, uiMillis);
////      }
////      else if (uiTotalMinutes > 0)
////      {
////         strTick.format(" %d:%d.%03d ", uiMinutes, uiSeconds, uiMillis);
////      }
////      else if (uiTotalSeconds > 0)
////      {
////         strTick.format(" %d.%03ds ", uiSeconds, uiMillis);
////      }
////      else
////      {
////         strTick.format(" %3dms ", uiMillis);
////      }
////
////      //string strCat(pcategory->m_pszName);
////
////      string strCat(pszTopicText);
////
////      string strMiddle;
////
////      if (m_bLogThreadName)
////      {
////
////         strMiddle += "{" + ::task_get_name() + "} ";
////
////      }
////
////      if (m_bLogFunctionName)
////      {
////
////         strMiddle += "[" + string(pszFunction) + "] ";
////
////      }
////
////      if (m_bLogFileName)
////      {
////
////         strMiddle += "\""+ string(pszFile) + "\"";
////
////         strMiddle += "(" + __string(iLine) + "): ";
////
////      }
////
////      //synchronouslock.lock();
////      if (m_bTrace &&
////         (m_pfile == nullptr
////            || m_iYear != time.GetYear()
////            || m_iMonth != time.GetMonth()
////            || m_iDay != time.GetDay()))
////      {
////         if (m_pfile != nullptr)
////         {
////            fflush(m_pfile);
////            fclose(m_pfile);
////            m_pfile = nullptr;
////         }
////         i32 iRetry = 0;
////      retry:
////
////         string strDatetime;
////
////         time.Format(strDatetime, "%Y/%m/%d/%H-%M-%S");
////
////         string strIndex;
////
////         strIndex.format("%d-%05d", get_current_process_id(), iRetry);
////
////         m_strLogPath = m_psystem->m_pacmedir->appdata() / string(m_atom) / strDatetime + "-" + strIndex + ".ca2log";
////
////         try
////         {
////
////                     auto psystem = m_psystem;
//
////         auto pacmedir = psystem->m_pacmedir;
////
////pacmedir->create(::file_path_folder(m_strLogPath));
////
////            if (!(m_pfile = fopen(m_strLogPath, "at")))
////            {
////               i32 iError = errno;
////               if (iError == ENOENT)
////               {
////                  goto skip_further_possible_recursive_impossible_logging_in_file;
////               }
////               else
////               {
////                  if (iError == EAGAIN)
////                  {
////                  }
////                  else
////                  {
////                     iRetry++;
////                     if (iRetry >= 100000)
////                        return;
////                     goto retry;
////
////                  }
////               }
////            }
////         }
////         catch (...)
////         {
////            try
////            {
////               if (m_pfile)
////               {
////                  fclose(m_pfile);
////                  m_pfile = nullptr;
////               }
////
////               iRetry++;
////               if (iRetry >= 100000)
////               {
////
////                  return;
////
////               }
////
////               goto retry;
////
////            }
////            catch (...)
////            {
////
////            }
////
////         }
////
////         m_iYear = time.GetYear();
////
////         m_iMonth = time.GetMonth();
////
////         m_iDay = time.GetDay();
////
////         print("<log>Starting Log</log>"); // <<  this is one of the "...possible_recursive_impossible_logging_in_file"...
////
////         output_debug_string("\n" + m_strLogPath + "\n");
////
////#if !defined(_UWP)
////
////         auto psystem = get_system()->m_papexsystem;
////
////         if (is_debugger_attached() && !psystem->has_apex_application_factory())
////         {
////
////            fork([this]()
////               {
////
////                  sleep(1_s);
////
////                  if (!m_psystem->m_pacmepath->app_module().contains_ci("logviewer") && m_psystem->m_pacmefile->exists(m_psystem->m_pacmedir->system() / "logviewer.txt"))
////                  {
////
////                     call_async("C:\\apex\\time\\x64\\basis\\app_core_logviewer.exe", "\"" + m_strLogPath + "\"", "C:\\apex\\time\\x64\\basis", e_display_normal, false);
////
////                  }
////
////               });
////
////         }
////
////#endif
////
////         }
////
////skip_further_possible_recursive_impossible_logging_in_file:
////
////      if(m_bTrace && m_pfile != nullptr)
////      {
////
////         fseek(m_pfile,0,SEEK_END);
////
////      }
////
////      for(i32 i = 0; i < stra.get_size(); i++)
////      {
////
////         string strLine = strPre + strTick + strCat + strMiddle + stra[i]+"\n";
////
////         try
////         {
////#ifdef ANDROID
////            ::output_debug_string(stra[i]);
////#else
////            ::output_debug_string(strLine);
////#endif
////
////            if(m_bTrace && m_pfile)
////            {
////
////               fputs(strLine,m_pfile);
////
////            }
////
////         }
////         catch(::exception &)
////         {
////
////            // Ignore exception here because this class/function is used for debugging
////
////         }
////
////      }
//
//   }

   //void log::trace2(e_trace_category ecategory, enum_trace_level elevel, const char * pszFormat, ...)
   //{
   //   if(!m_bTrace)
   //      return;
   //   va_list ptr;
   //   va_start(ptr, pszFormat);
   //   trace_v(ecategory, elevel, nullptr, nullptr, -1, pszFormat, ptr);
   //   va_end(ptr);

   //}




   //void log::print(const char * pszFormat, ...)
   //{

   //   //::trace::log::print_v(pszFormat, valist);

   //   va_list valist;

   //   va_start(valist, pszFormat);

   //   print_v(pszFormat, valist);

   //   va_end(valist);

   //}


   //void log::initialize_apex_log(enum_trace_level etracelevelMin, const char * pszId)
   //{

   //   //if (!initialize(atom(pszId)))
   //   //{

   //   //   return false;

   //   //}

   //   return estatus;

   //}


   void log::process_init()
   {

      auto psystem = get_system()->m_papexsystem;

      if (is_debugger_attached() && !psystem->has_apex_application_factory())
      {

         /*fork([this]()
            {

               while (::task_get_run())
               {

                  load_flags(m_pcontext->m_papexcontext->local_ini());

                  //task_sleep(10_s);

                  task_sleep(1_s);

                  //load_flags("localconfig"_ini);

                  //task_sleep(1_s);

                  //task_sleep(10_s);

               }

            });*/

      }

      //return true;

   }


   void log::load_flags(const ::property_set & set)
   {

      auto & log = set["log"];

      if (::is_ref_set(log))
      {

         m_bLogThreadName = log["threadname"].is_true();

         m_bLogFileName = log["filename"].is_true();

         m_bLogFunctionName = log["functionname"].is_true();

      }

   }


   //void log::initialize(e_traceid atom)
   //{


   //}


   void log::destroy()
   {

      synchronous_lock synchronouslock(mutex());

      if (m_bInitialized)
      {

         ::log::destroy();

         if (m_pfile)
         {

            fclose(m_pfile);

            m_pfile = nullptr;

         }

         m_bInitialized = false;

      }

      //return ::success;

   }


   void log::set_trace_category(enum_trace_category etracecategory,  enum_trace_level etracelevelMinimum)
   {

      auto pcategory = m_ptrace->operator[](etracecategory);

      pcategory->m_pszName = trace_category_name(etracecategory);

      pcategory->m_etracecategory = etracecategory;

      pcategory->m_etracelevelMinimum = etracelevelMinimum;

      pcategory->m_bEnabled = etracelevelMinimum > e_trace_level_none;

   }





   //void log::trace(const char * pszFormat, ...)
   //{

   //   if (void_ptr_is_null(this))
   //   {
   //      va_list ptr;
   //      va_start(ptr, pszFormat);
   //      vprintf(pszFormat, ptr);
   //      va_end(ptr);
   //      return;
   //   }

   //   va_list ptr;
   //   va_start(ptr, pszFormat);
   //   trace_v(nullptr, -1, trace_category_general, e_trace_level_information, pszFormat, ptr);
   //   va_end(ptr);
   //}

   /*void log::trace2(e_trace_category ecategory, enum_trace_level elevel, const char * pszFormat, ...)
   {
      if(!m_bTrace)
         return;
      va_list ptr;
      va_start(ptr, pszFormat);
      trace_v(nullptr, -1, dwCategory, nLevel, pszFormat, ptr);
      va_end(ptr);
   }*/

} // namespace apex




