#include "framework.h"
//#include "aura/net/sockets/_.h"
#include "aura/platform/app_core.h"


CLASS_DECL_AURA enum_trace_level get_global_trace_level();
CLASS_DECL_AURA string task_get_name();


#include <stdio.h>
// #include <stdarg.h>

#if defined(LINUX) || defined(__ANDROID__)
//#include <sys/types.h>
//

#ifdef COMPILE_WITH_VALGRIND

#if !defined(RASPBERRYPIOS) && !defined(__ANDROID__)
#include <valgrind/valgrind.h>
#endif

#endif


#define ENABLE_TRACE 1
#elif defined(WINDOWS_DESKTOP)
#define ENABLE_TRACE 1
#endif

namespace aura
{





   log::log()
   {

#if !ENABLE_TRACE

      m_bTrace = false;

#else

      ::file::path pathTrace =          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "trace.txt";

#ifdef _DEBUG

      if (!file_system()->exists(pathTrace))
      {

         ::file_system()->put_contents(pathTrace, "yes");

      }


#endif // __DEBUG

#ifdef COMPILE_WITH_VALGRIND

#if !defined(RASPBERRYPIOS) && !defined(__ANDROID__) && !defined(WINDOWS)
      if (!RUNNING_ON_VALGRIND)
#endif
      {

         m_bTrace = ::file_is_true_dup(pathTrace) || ::is_debugger_attached();

         //m_bTrace = ::file_is_true_dup(pathTrace);

      }

#endif

#endif

      defer_create_synchronization();

   }


   void log::initialize_aura_log(enum_trace_level etracelevelMin, const ::atom & atom)
   {

      auto estatus = __construct_new(m_ptrace);

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

      for (::collection::index i = trace_category_first; i < trace_category_count; i++)
      {

         set_trace_category((e_trace_category)i, etracelevelMin);

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


      synchronous_lock synchronouslock(this->synchronization());

      if (m_bInitialized)
      {

         return false;

      }

      id() = atom;

      m_bInitialized = true;

      if (file_is_true_dup(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "log.txt"))
      {

         m_bLog = true;

      }

#ifdef COMPILE_WITH_VALGRIND

#if defined(LINUX) && !defined(RASPBERRYPIOS)

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

      print("<log>Log Initialized!!</log>");

//      return true;


      return estatus;

   }


   log::~log()
   {

      //::acme::del(m_ptrace);

   }


//   extern ::pointer<::aura::application>g_papp;

   CLASS_DECL_AURA int SimpleDebugReport(int iReportType, const ::scoped_string & scopedstrFileName,int iLine, const ::string &, const ::scoped_string & scopedstrFormat, va_list list)
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
            str += as_string(iLine);
            str += "\r\n";

            string strCaption;

            strCaption = "Assertion Failed";

            information(wstring(str));
            /*if(message_box(nullptr, str, strCaption, ::user::e_message_box_icon_information | MB_OKCANCEL | MB_DEFBUTTON1) == e_dialog_result_cancel)
            {
               string strCmdLine = "\"C:\\Program Files (x86)\\Microsoft Visual Studio 11.0\\Common7\\IDE\\devenv.exe\" /edit \""+string(scopedstrFileName)+ "\" /command \"edit.goto "+as_string(iLine)+"\"";
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
         information(wstring(buf));

      }

#else
      vprintf(scopedstrFormat, list);
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


   void log::success(const ::scoped_string & scopedstr)
   {

      print(scopedstr);

   }


   //void log::tracev(e_trace_category ecategory, enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstrFormat, va_list args)
   //{

   //   string str;

   //   str.formatf(scopedstrFormat, args);

   //   alog(ecategory, elevel, pszFunction, pszFile, iLine, str);

   //}


   void log::__tracea(::particle * pparticle, enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstr)
   {

      const ::scoped_string & scopedstrTopicText = ::is_set(pparticle) ? pparticle->topic_text() : nullptr;

      synchronous_lock sl2(m_pmutexTrace);

      ::aura::trace::category * pcategory = nullptr;

      if (elevel != e_trace_level_none)
      {

         pcategory = m_ptrace->enabled_get(object_trace_category(pparticle), elevel);

         if (pcategory == nullptr)
         {

            return;

         }

      }

      if (!m_bLog)
      {

         if (elevel >= get_global_trace_level())
         {

            string str;

            if (::is_set(scopedstrTopicText))
            {

               string strTopicText(scopedstrTopicText);

               if (strTopicText.has_character())
               {

                  strTopicText.case_insensitive_begins_eat("class ");

                  strTopicText.case_insensitive_begins_eat("struct ");

                  str += strTopicText;

                  str += "> ";

               }

            }

            str += psz;

            str += "\n";

            information(str);

         }

         return;

      }

      string_array_base stra;

      stra.add_lines(scopedstr, false);

      string strPre;

      ::earth::time time;
      time = time.get_current_time();
      time.Format(strPre, "%Y-%m-%d %H:%M:%S");
      string strTick;
      long long uiTotalMillis= ::duration::now() - ::first_millis();
      long long uiMillis = uiTotalMillis % 1000;
      long long uiTotalSeconds = uiTotalMillis / 1000;
      long long uiSeconds = uiTotalSeconds % 60;
      long long uiTotalMinutes = uiTotalSeconds / 60;
      long long uiMinutes = uiTotalMinutes % 60;
      long long uiTotalHours = uiTotalMinutes / 60;
      long long uiHours = uiTotalHours % 24;
      long long uiTotalDays = uiTotalHours / 24;
      // sipman LCTV learning to format hours, minutes and seconds.... (me (re) learning too)...
      if (uiTotalDays > 0)
      {
         strTick.formatf(" %d:%d:%d:%d.%03d ", uiTotalDays, uiHours, uiMinutes, uiSeconds, uiMillis);
      }
      else if(uiTotalHours > 0)
      {
         strTick.formatf(" %d:%d:%d.%03d ", uiHours, uiMinutes, uiSeconds, uiMillis);
      }
      else if (uiTotalMinutes > 0)
      {
         strTick.formatf(" %d:%d.%03d ", uiMinutes, uiSeconds, uiMillis);
      }
      else if (uiTotalSeconds > 0)
      {
         strTick.formatf(" %d.%03ds ", uiSeconds, uiMillis);
      }
      else
      {
         strTick.formatf(" %3dms ", uiMillis);
      }

      //string strCat(pcategory->m_pszName);

      string strCat(scopedstrTopicText);

      string strMiddle;

      if (m_bLogThreadName)
      {

         strMiddle += "{" + ::task_get_name() + "} ";

      }

      if (m_bLogFunctionName)
      {

         strMiddle += "[" + string(scopedstrFunction) + "] ";

      }

      if (m_bLogFileName)
      {

         strMiddle += "\""+ string(scopedstrFile) + "\"";

         strMiddle += "(" + as_string(iLine) + "): ";

      }

      //synchronouslock.lock();
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
         int iRetry = 0;
      retry:

         string strDatetime;

         time.Format(strDatetime, "%Y/%m/%d/%H-%M-%S");

         string strIndex;

         strIndex.formatf("%d-%05d", get_current_process_id(), iRetry);

         m_strLogPath = ::dir::appdata() / string(id()) / strDatetime + "-" + strIndex + ".ca2log";

         try
         {

                     auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->create(::file_path_folder(m_strLogPath));

            if (!(m_pfile = fopen(m_strLogPath, "at")))
            {
               int iError = errno;
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

         informationf("\n" + m_strLogPath + "\n");

#if !defined(UNIVERSAL_WINDOWS)

         if (is_debugger_attached() && !::auraacmesystem()->has_aura_application_factory())
         {

            fork([this]()
               {

                  sleep(1_s);

                  if (!path_system()->app_module().case_insensitive_contains("logviewer") && file_system()->exists(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "logviewer.txt"))
                  {

                     call_async("C:\\aura\\time\\x64\\basis\\app_core_logviewer.exe", "\"" + m_strLogPath + "\"", "C:\\aura\\time\\x64\\basis", e_display_normal, false);

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

      for(int i = 0; i < stra.get_size(); i++)
      {

         string strLine = strPre + strTick + strCat + strMiddle + stra[i]+"\n";

         try
         {
#ifdef __ANDROID__
            ::information(stra[i]);
#else
            ::information(strLine);
#endif

            if(m_bTrace && m_pfile)
            {

               fputs(strLine,m_pfile);

            }

         }
         catch(::exception &)
         {

            // Ignore exception here because this class/function is used for debugging

         }

      }

   }

   //void log::trace2(e_trace_category ecategory, enum_trace_level elevel, const ::scoped_string & scopedstrFormat, ...)
   //{
   //   if(!m_bTrace)
   //      return;
   //   va_list ptr;
   //   va_start(ptr, pszFormat);
   //   trace_v(ecategory, elevel, nullptr, nullptr, -1, pszFormat, ptr);
   //   va_end(ptr);

   //}




   void log::print(const ::scoped_string & scopedstrFormat, ...)
   {

      va_list valist;

      va_start(valist, pszFormat);

      __tracef(general_trace_object(), e_trace_level_information, nullptr, nullptr, -1, pszFormat, valist);

      va_end(valist);

   }


   //void log::initialize_aura_log(enum_trace_level etracelevelMin, const ::scoped_string & scopedstrId)
   //{

   //   //if (!initialize(atom(scopedstrId)))
   //   //{

   //   //   return false;

   //   //}

   //   return estatus;

   //}


   bool log::process_init()
   {

      if (is_debugger_attached() && !::auraacmesystem()->has_aura_application_factory())
      {

         /*fork([this]()
            {

               while (::task_get_run())
               {

                  load_flags(pcontext->local_ini());

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


   //void log::initialize(e_traceid atom)
   //{


   //}


   void log::destroy()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (!m_bInitialized)
      {

         return;

      }

      ::object::destroy();

      if (m_pfile)
      {

         fclose(m_pfile);

         m_pfile = nullptr;

      }

      m_bInitialized = false;

   }


   void log::set_trace_category(e_trace_category ecategory,  enum_trace_level elevelMin)
   {

      auto pcategory = m_ptrace->operator[](ecategory);

      pcategory->m_pszName = trace_category_name(ecategory);

      pcategory->m_ecategory = ecategory;

      pcategory->m_elevelMin = elevelMin;

      pcategory->m_bEnabled = elevelMin > e_trace_level_none;

   }





   //void log::trace(const ::scoped_string & scopedstrFormat, ...)
   //{

   //   if (void_ptr_is_null(this))
   //   {
   //      va_list ptr;
   //      va_start(ptr, pszFormat);
   //      vprintf(scopedstrFormat, ptr);
   //      va_end(ptr);
   //      return;
   //   }

   //   va_list ptr;
   //   va_start(ptr, pszFormat);
   //   trace_v(nullptr, -1, trace_category_general, e_trace_level_information, pszFormat, ptr);
   //   va_end(ptr);
   //}

   /*void log::trace2(e_trace_category ecategory, enum_trace_level elevel, const ::scoped_string & scopedstrFormat, ...)
   {
      if(!m_bTrace)
         return;
      va_list ptr;
      va_start(ptr, pszFormat);
      trace_v(nullptr, -1, dwCategory, nLevel, pszFormat, ptr);
      va_end(ptr);
   }*/

} // namespace aura




