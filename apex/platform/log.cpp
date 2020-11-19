#include "framework.h"
#include "apex/net/sockets/_.h"
#include "apex/platform/app_core.h"


CLASS_DECL_APEX string thread_get_name();

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

      ::file::path pathTrace = ::dir::system() / "trace.txt";

#ifdef __DEBUG

      if (!file_exists(pathTrace))
      {

         ::file_put_contents(pathTrace, "yes");

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

#endif

      defer_create_mutex();

   }


   ::estatus log::initialize_apex_log(e_trace_level etracelevelMin, const ::id & id)
   {

      auto estatus = __compose_new(m_ptrace);

      if (!estatus)
      {

         return estatus;

      }

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

      for (index i = trace_category_first; i < trace_category_count; i++)
      {

         set_trace_category((e_trace_category)i, etracelevelMin);

      }

      //set_trace_category(trace_category_general, trace_level_information);
      //set_trace_category(trace_category_com, trace_level_warning);
      //set_trace_category(trace_category_qi, trace_level_warning);
      //set_trace_category(trace_category_registrar, "category_Registrar", trace_level_warning);
      //set_trace_category(trace_category_refcount, "category_Refcount", trace_level_warning);
      //set_trace_category(trace_category_windowing, "category_Windowing", trace_level_warning);
      //set_trace_category(trace_category_controls, "category_Controls", trace_level_warning);
      //set_trace_category(trace_category_hosting, "category_Hosting", trace_level_warning);
      //set_trace_category(trace_category_dbclient, "category_DBClient", trace_level_warning);
      //set_trace_category(trace_category_dbprovider, "category_DBProvider", trace_level_warning);
      //set_trace_category(trace_category_snapin, "category_Snapin", trace_level_warning);
      //set_trace_category(trace_category_notimpl, "category_NotImpl", trace_level_warning);
      //set_trace_category(trace_category_allocation, "category_Allocation", trace_level_warning);
      //set_trace_category(trace_category_exception, "category_Exception", trace_level_warning);
      //set_trace_category(trace_category_time, "category_Time", trace_level_warning);
      //set_trace_category(trace_category_cache, "category_Cache", trace_level_warning);
      //set_trace_category(trace_category_stencil, "category_Stencil", trace_level_warning);
      //set_trace_category(trace_category_string, "category_String", trace_level_warning);
      //set_trace_category(trace_category_map, "category_Map", trace_level_warning);
      //set_trace_category(trace_category_util, "category_Util", trace_level_warning);
      //set_trace_category(trace_category_security, "category_Security", trace_level_warning);
      //set_trace_category(trace_category_sync, "category_Sync", trace_level_warning);
      //set_trace_category(trace_category_isapi, "category_ISAPI", trace_level_warning);

      //set_trace_category(trace_category_user, "category_User", trace_level_warning);
      //set_trace_category(trace_category_user2, "category_User2", trace_level_warning);
      //set_trace_category(trace_category_user3, "category_User3", trace_level_warning);
      //set_trace_category(trace_category_user4, "category_User4", trace_level_warning);


      //set_trace_category(trace_category_appmsg, "AppMsg", trace_level_warning);        // Main message pump trace (includes DDE)
      //set_trace_category(trace_category_winmsg, "category_WinMsg", trace_level_warning);         // Windows message tracing
      //set_trace_category(trace_category_cmdrouting, "category_CmdRouting", trace_level_warning);     // Windows command routing trace
      //set_trace_category(trace_category_ole, "category_Ole", trace_level_warning);           // special OLE callback trace
      //set_trace_category(trace_category_database, "category_Database", trace_level_warning);      // special database trace
      //set_trace_category(trace_category_internet, "category_Internet", trace_level_warning);      // special Internet client trace
      //set_trace_category(trace_category_dumpcontext, "category_dumpContext", trace_level_warning);    // traces from dump_context
      //set_trace_category(trace_category_memory, "category_Memory", trace_level_warning);       // matter non-kernel memory traces
      //set_trace_category(trace_category_html, "category_Html", trace_level_warning);          // Html traces
      //set_trace_category(trace_category_socket, "category_Socket", trace_level_warning);       // socket traces


      sync_lock sl(mutex());

      if (m_bInitialized)
      {

         return false;

      }

      m_id = id;

      m_bInitialized = true;

      if (file_is_true_dup(::dir::system() / "log.txt"))
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
         //m_bLog = is_debugger_attached() != FALSE;

      }

      sl.unlock();

      print("<log>Log Initialized!!</log>");

//      return true;


      return estatus;

   }


   log::~log()
   {

      //::acme::del(m_ptrace);

   }


//   extern __pointer(::apex::application) g_papp;

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
            str += __str(iLine);
            str += "\r\n";

            string strCaption;

            strCaption = "Assertion Failed";

            output_debug_string(wstring(str));
            /*if(message_box(nullptr, str, strCaption, MB_ICONINFORMATION | MB_OKCANCEL | MB_DEFBUTTON1) == IDCANCEL)
            {
               string strCmdLine = "\"C:\\Program Files (x86)\\Microsoft Visual Studio 11.0\\Common7\\IDE\\devenv.exe\" /edit \""+string(pszFileName)+ "\" /command \"edit.goto "+__str(iLine)+"\"";
               ::system(strCmdLine);
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

   void log::set_extended_log(bool bSet)
   {
      m_bExtendedLog = bSet;
   }

   bool log::get_extended_log()
   {
      return m_bExtendedLog;
   }


   void log::success(const char * psz)
   {

      print(psz);

   }


   //void log::tracev(e_trace_category ecategory, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args)
   //{

   //   string str;

   //   str.Format(pszFormat, args);

   //   alog(ecategory, elevel, pszFunction, pszFile, iLine, str);

   //}


   void log::__tracea(::matter * pobjectContext, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * psz)
   {

      const char * pszTopicText = ::is_set(pobjectContext) ? pobjectContext->topic_text() : nullptr;

      sync_lock sl2(&m_mutexTrace);

      ::apex::trace::category * pcategory = nullptr;

      if (elevel != trace_level_none)
      {

         pcategory = m_ptrace->enabled_get(object_trace_category(pobjectContext), elevel);

         if (pcategory == nullptr)
         {

            return;

         }

      }

      if (!m_bLog)
      {

#ifndef DEBUG

         if (elevel >= trace_level_error)
         {

#endif // !DEBUG

            string str;

            if (::is_set(pszTopicText))
            {

               string strTopicText(pszTopicText);

               if (strTopicText.has_char())
               {

                  ::str::begins_eat_ci(strTopicText, "class ");

                  ::str::begins_eat_ci(strTopicText, "struct ");

                  str += strTopicText;

                  str += "> ";

               }

            }

            str += psz;

            str += "\n";

            output_debug_string(str);

#ifndef DEBUG

         }

#endif // !DEBUG

         return;

      }

      string_array stra;

      stra.add_lines(psz, FALSE);

      string strPre;

      ::datetime::time time;
      time = time.get_current_time();
      time.Format(strPre, "%Y-%m-%d %H:%M:%S");
      string strTick;
      auto millisTotal = ::millis::now() - ::first_millis();
      i64 uiMillis = millisTotal.m_iMilliseconds % 1000;
      i64 uiTotalSeconds = millisTotal.m_iMilliseconds / 1000;
      i64 uiSeconds = uiTotalSeconds % 60;
      i64 uiTotalMinutes = uiTotalSeconds / 60;
      i64 uiMinutes = uiTotalMinutes % 60;
      i64 uiTotalHours = uiTotalMinutes / 60;
      i64 uiHours = uiTotalHours % 24;
      i64 uiTotalDays = uiTotalHours / 24;
      // sipman LCTV learning to format hours, minutes and seconds.... (me (re) learning too)...
      if (uiTotalDays > 0)
      {
         strTick.Format(" %d:%d:%d:%d.%03d ", uiTotalDays, uiHours, uiMinutes, uiSeconds, uiMillis);
      }
      else if(uiTotalHours > 0)
      {
         strTick.Format(" %d:%d:%d.%03d ", uiHours, uiMinutes, uiSeconds, uiMillis);
      }
      else if (uiTotalMinutes > 0)
      {
         strTick.Format(" %d:%d.%03d ", uiMinutes, uiSeconds, uiMillis);
      }
      else if (uiTotalSeconds > 0)
      {
         strTick.Format(" %d.%03ds ", uiSeconds, uiMillis);
      }
      else
      {
         strTick.Format(" %3dms ", uiMillis);
      }

      //string strCat(pcategory->m_pszName);

      string strCat(pszTopicText);

      string strMiddle;

      if (m_bLogThreadName)
      {

         strMiddle += "{" + ::thread_get_name() + "} ";

      }

      if (m_bLogFunctionName)
      {

         strMiddle += "[" + string(pszFunction) + "] ";

      }

      if (m_bLogFileName)
      {

         strMiddle += "\""+ string(pszFile) + "\"";

         strMiddle += "(" + __str(iLine) + "): ";

      }

      //sl.lock();
      if (m_bTrace &&
         (m_pfile == nullptr
            || m_iYear != time.GetYear()
            || m_iMonth != time.GetMonth()
            || m_iDay != time.GetDay()))
      {
         if (m_pfile != nullptr)
         {
            fflush(m_pfile);
            fclose(m_pfile);
            m_pfile = nullptr;
         }
         i32 iRetry = 0;
      retry:

         string strDatetime;

         time.Format(strDatetime, "%Y/%m/%d/%H-%M-%S");

         string strIndex;

         strIndex.Format("%d-%05d", get_current_process_id(), iRetry);

         m_strLogPath = ::dir::appdata() / string(m_id) / strDatetime + "-" + strIndex + ".ca2log";

         try
         {

            ::dir::mk(::dir::name(m_strLogPath));

            if (!(m_pfile = fopen(m_strLogPath, "at")))
            {
               i32 iError = errno;
               if (iError == ENOENT)
               {
                  goto skip_further_possible_recursive_impossible_logging_in_file;
               }
               else
               {
                  if (iError == EAGAIN)
                  {
                  }
                  else
                  {
                     iRetry++;
                     if (iRetry >= 100000)
                        return;
                     goto retry;

                  }
               }
            }
         }
         catch (...)
         {
            try
            {
               if (m_pfile)
               {
                  fclose(m_pfile);
                  m_pfile = nullptr;
               }

               iRetry++;
               if (iRetry >= 100000)
               {

                  return;

               }

               goto retry;

            }
            catch (...)
            {

            }

         }

         m_iYear = time.GetYear();

         m_iMonth = time.GetMonth();

         m_iDay = time.GetDay();

         print("<log>Starting Log</log>"); // <<  this is one of the "...possible_recursive_impossible_logging_in_file"...

         output_debug_string("\n" + m_strLogPath + "\n");

#if !defined(_UWP)

         if (is_debugger_attached() && !System.has_apex_application_factory())
         {

            fork([this]()
               {

                  millis_sleep(1_s);

                  if (!::file::app_module().contains_ci("logviewer") && file_exists(::dir::system() / "logviewer.txt"))
                  {

                     call_async("C:\\apex\\time\\x64\\basis\\app_core_logviewer.exe", "\"" + m_strLogPath + "\"", "C:\\apex\\time\\x64\\basis", display_normal, false);

                  }

               });

         }

#endif

         }

skip_further_possible_recursive_impossible_logging_in_file:

      if(m_bTrace && m_pfile != nullptr)
      {

         fseek(m_pfile,0,SEEK_END);

      }

      for(i32 i = 0; i < stra.get_size(); i++)
      {

         string strLine = strPre + strTick + strCat + strMiddle + stra[i]+"\n";

         try
         {
#ifdef ANDROID
            ::output_debug_string(stra[i]);
#else
            ::output_debug_string(strLine);
#endif

            if(m_bTrace && m_pfile)
            {

               fputs(strLine,m_pfile);

            }

         }
         catch(::exception::exception &)
         {

            // Ignore exception here because this class/function is used for debugging

         }

      }

   }

   //void log::trace2(e_trace_category ecategory, e_trace_level elevel, const char * pszFormat, ...)
   //{
   //   if(!m_bTrace)
   //      return;
   //   va_list ptr;
   //   va_start(ptr, pszFormat);
   //   trace_v(ecategory, elevel, nullptr, nullptr, -1, pszFormat, ptr);
   //   va_end(ptr);

   //}




   void log::print(const char * pszFormat, ...)
   {

      va_list valist;

      va_start(valist, pszFormat);

      __tracef(general_trace_object(), trace_level_information, nullptr, nullptr, -1, pszFormat, valist);

      va_end(valist);

   }


   //::estatus log::initialize_apex_log(e_trace_level etracelevelMin, const char * pszId)
   //{

   //   //if (!initialize(id(pszId)))
   //   //{

   //   //   return false;

   //   //}

   //   return estatus;

   //}


   bool log::process_init()
   {

      if (is_debugger_attached() && !System.has_apex_application_factory())
      {

         /*fork([this]()
            {

               while (::thread_get_run())
               {

                  load_flags(Context.local_ini());

                  //task_sleep(10_s);

                  task_sleep(1_s);

                  //load_flags("localconfig"_ini);

                  //task_sleep(1_s);

                  //task_sleep(10_s);

               }

            });*/

      }

      return true;

   }


   void log::load_flags(const ::property_set & set)
   {

      auto & log = set["log"];

      if (::is_ref_set(log))
      {

         m_bLogThreadName = log["threadname"];

         m_bLogFileName = log["filename"];

         m_bLogFunctionName = log["functionname"];

      }

   }


   //::estatus log::initialize(e_traceid id)
   //{


   //}


   void log::finalize()
   {

      sync_lock sl(mutex());

      if (!m_bInitialized)
      {

         return;

      }

      ::object::finalize();

      if (m_pfile)
      {

         fclose(m_pfile);

         m_pfile = nullptr;

      }

      m_bInitialized = false;

   }


   void log::set_trace_category(e_trace_category ecategory,  e_trace_level elevelMin)
   {

      auto pcategory = m_ptrace->operator[](ecategory);

      pcategory->m_pszName = trace_category_name(ecategory);

      pcategory->m_ecategory = ecategory;

      pcategory->m_elevelMin = elevelMin;

      pcategory->m_bEnabled = elevelMin > trace_level_none;

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
   //   trace_v(nullptr, -1, trace_category_general, trace_level_information, pszFormat, ptr);
   //   va_end(ptr);
   //}

   /*void log::trace2(e_trace_category ecategory, e_trace_level elevel, const char * pszFormat, ...)
   {
      if(!m_bTrace)
         return;
      va_list ptr;
      va_start(ptr, pszFormat);
      trace_v(nullptr, -1, dwCategory, nLevel, pszFormat, ptr);
      va_end(ptr);
   }*/

} // namespace apex




