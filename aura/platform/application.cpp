#include "framework.h"
#include "application.h"
#include "shell_open.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/file/folder.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/prototype/prototype/url.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/prototype/string/base64.h"
#include "acme/handler/request.h"
#include "acme/platform/http.h"
#include "acme/platform/profiler.h"
#include "acme/prototype/text/context.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/handler/signal.h"
#include "apex/platform/node.h"
#include "apex/interprocess/communication.h"
#include "apex/interprocess/target.h"
#include "apex/networking/http/context.h"
#include "apex/platform/node.h"
//#include "apex/platform/os_context.h"

#include "apex/user/user/message.h"
#include "aqua/game/game.h"
#include "aura/constant/idpool.h"
#include "aura/platform/component.h"
#include "aura/platform/node.h"
#include "aura/graphics/image/icon.h"
#include "aura/user/user/interaction_array.h"
#include "aura/user/user/interaction.h"
#include "aura/user/user/user.h"
//#include "aura/user/user/interaction_impl.h"
#include "aura/user/user/system.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/user/user/plain_edit.h"
#include "aura/platform/system.h"
#include "aura/platform/session.h"
#include "aura/platform/theme.h"
#include "aura/windowing/icon.h"
#include "aura/windowing/window.h"
#include "aura/windowing/windowing.h"
//#include "bred/gpu/approach.h"


extern "C"
{

   typedef void FN_factory(::factory::factory * pfactory);

   typedef FN_factory * PFN_factory;

}


//#ifdef WINDOWS_DESKTOP
//
//
//CLASS_DECL_ACME void windows_install_crash_dump_reporting(const ::string & strModuleNameWithTheExeExtension);
//
//
//#endif


#ifdef MACOS
::file::path macos_app_path(string strApp);
//void ns_app_terminate();
// 0x00010000 NSWorkspaceLaunchAsync
// 0x00080000 NSWorkspaceLaunchNewInstance
void ns_launch_app(const ::scoped_string & scopedstr, const char ** argv, int iFlags);
#endif

#if defined(LINUX)
#ifdef _GNU_SOURCE
#undef _GNU_SOURCE

//#include "aura/node/ansios/ansios.h"
//#include "aura/operating_system/linux/_linux.h"

//#include <X11/cursorfont.h>
#include <sys/time.h>
#include <link.h>
//#include <pthread.h>

#endif
#define _GNU_SOURCE
//#include <link.h>
#elif defined(__APPLE__)
//#include <dlfcn.h>
#elif defined(__ANDROID__)

//#include "aura/node/ansios/ansios.h"
//#include "aura/operating_system/android/_.h"

//#elif defined(WINDOWS_DESKTOP)

//#include "aura/node/windows/windows_registry.h"

#endif


#if defined(APPLE_IOS) || defined(UNIVERSAL_WINDOWS)
CLASS_DECL_AURA int ui_open_url(const ::string & psz);
#endif


//extern void * g_pf1;


namespace aura
{


   application::application()
   {

      //m_pauraapplication = this;
#if defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)
      //m_bSnLauncheeSetup = false;
      m_bGtkApp = false;
#endif

      //m_bConsole = false;
      m_pappParent = nullptr;

      //m_bSimpleMessageLoop = false;
      m_ethreadcontextClose = e_thread_context_none;

      m_puiMainContainer = nullptr;

      m_bRequiresInstallation = false;
      m_bReadStringTable = true;

      //m_puiCurrent = nullptr;

      //m_bInitializeDataCentral = true;

      m_bInitializeDataCentral = false;

      m_bContextTheme = false;



      m_strLocale = "_std";
      m_strSchema = "_std";


      // default value for acid apps
      // (but any acid app can have installer, just machine this flag to true in the derived application class constructor).
      m_bAppHasInstallerProtected = true;
      m_bAppHasInstallerChangedProtected = false;

      m_strHttpUserAgentToken = "ca2";
      m_strHttpUserAgentVersion = "1.0";

      //m_http.set_app(this);

      m_eexclusiveinstance = e_exclusive_instance_none;

      //m_pevAppBeg = nullptr;
      //m_pevAppEnd = nullptr;

      //m_bAgreeExit = true;
      //m_bAgreeExitOk = true;
      //m_bFranceExit = true;

      //m_bLicense = false;

      //m_bInterprocessCommunication = false;

      //m_pimaging = nullptr;


      //m_phandler = __allocate ::handler(this);


      //m_bAuraProcessInitialize = false;
      //m_bAuraProcessInitializeResult = false;

      //m_bAuraInitialize1 = false;
      //m_bAuraInitialize1Result = false;

      //m_bAuraInitialize = false;
      //m_bAuraInitializeResult = false;

      //m_bAuraInitializeInstance = false;
      //m_bAuraInitializeInstanceResult = false;

      //add_factory_item < ::user::user >();
      //add_factory_item < ::userfs::userfs >();

      //m_pmainpane = nullptr;

      //m_ppaneimpactMain = nullptr;

      // almost always forgotten, assumed, as exception, responsability of application to add first ref on constructor.
      //::increment_reference_count(this);

      //srand((unsigned int) ::get_nanos());

      m_bService = false;

      m_iResourceId = 8001;

      ::acme::profiler::initialize();

      //m_pdocmanager = nullptr;

      m_eexclusiveinstance = e_exclusive_instance_none;
      m_strLocale = "_std";
      m_strSchema = "_std";

      //m_iGcomBackgroundUpdateMillis = -1;


   }


   application::~application()
   {

   }


   ::user::user * application::user()
   {

      auto psession = session();

      if (!psession)
      {

         return nullptr;

      }

      auto puser = psession->user();

      if (!puser)
      {

         return nullptr;

      }

      return puser;

   }


   void application::initialize(::particle * pparticle)
   {

      //auto estatus =
      
      ::aqua::application::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =
      
      __construct_new(m_puserinteractiona);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      __construct_new(m_puserinteractionaFrame);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //m_pauracontext = this;

      //return estatus;

   }


   void application::on_set_platform()
   {

      ::aqua::application::on_set_platform();

      factory()->add_factory_item < ::aura::system, ::platform::system >();
      
      factory()->add_factory_item < ::aura::session, ::platform::session >();

      factory()->add_factory_item < ::user::user >();
      
      factory()->add_factory_item < ::aura::component, ::component >();

   }



   //::message::application::message::application(e_::message::application esignal)
   //{

   //   id() = ::message::type_application;
   //   m_esignal = esignal;
   //   m_bOk = true;

   //}


   //application_menu & application::applicationmenu()
   //{

   //   if(m_pappmenu.is_null())
   //   {

   //      m_pappmenu = __allocate application_menu();

   //   }

   //   return *m_pappmenu;

   //}


   //::file::path application::local_application_path()
   //{

   //   return directory_system()->localconfig() / "application" / m_strAppName ;


   //}


   //::file::path application::local_application_home_path()
   //{

   //   return local_application_path() / "home";


   //}


   /*void application::application_menu_update()
   {

      ::application::application_menu_update();

   }
*/


   void application::close_application()
   {

      if (m_puserinteractionaFrame)
      {

         auto timeStartDestroying = ::time::now();

         while (m_puserinteractionaFrame &&
            m_puserinteractionaFrame->has_interaction())
         {

            auto framea = m_puserinteractionaFrame->interactiona();

            for (auto pframe : framea)
            {

               pframe->destroy_window();

            }
#ifdef _DEBUG
            if (timeStartDestroying.elapsed() > 10_min)
#else
            if (timeStartDestroying.elapsed() > 20_s)
#endif
            {

               break;

            }

            preempt(300_ms);

         }

         m_puserinteractionaFrame.release();

      }


      if (m_puserinteractiona)
      {

         auto timeStartDestroying = ::time::now();

         while (m_puserinteractiona &&
            m_puserinteractiona->has_interaction())
         {

            auto framea = m_puserinteractiona->interactiona();

            for (auto pframe : framea)
            {

               pframe->destroy_window();

            }
#ifdef _DEBUG
            if (timeStartDestroying.elapsed() > 10_min)
#else
            if (timeStartDestroying.elapsed() > 20_s)
#endif
            {

               break;

            }

            preempt(300_ms);

         }

         m_puserinteractiona.release();

      }

      if (m_pacmeuserinteractionMain)
      {

         auto timeStartDestroying = ::time::now();

         while (m_pacmeuserinteractionMain)
         {

            m_pacmeuserinteractionMain->destroy_window();

#ifdef _DEBUG
            if (timeStartDestroying.elapsed() > 10_min)
#else
            if (timeStartDestroying.elapsed() > 20_s)
#endif
            {

               break;

            }

            preempt(300_ms);

         }

         m_pacmeuserinteractionMain.release();

      }

      ::apex::application::close_application();

   }


   void application::destroy()
   {

      ::aqua::application::destroy();

   }


   void application::enumerate_composite(matter_array& a)
   {

      auto puserinteractiona = m_puserinteractiona.get();

      if (puserinteractiona)
      {

         for (auto& puserinteraction : puserinteractiona->interactiona())
         {

            if (::is_set(puserinteraction))
            {

               a.add_unique(puserinteraction);

            }

         }

      }

      auto puserinteractionaFrame = m_puserinteractionaFrame.get();

      if (puserinteractionaFrame)
      {

         for (auto& puserinteraction : puserinteractionaFrame->interactiona())
         {

            if (::is_set(puserinteraction))
            {

               a.add_unique(puserinteraction);

            }

         }

      }

   }


   ::property_object * application::parent_property_set_holder() const
   {

      return nullptr;

   }


   void application::on_change_theme()
   {


   }



   /*bool application::is_set_finish() const
   {

      return ::thread::is_set_finish() || m_ethreadClose != thread_none;

   }*/


   //void application::set_has_installer(bool bSet)
   //{

   //   m_bAppHasInstallerProtected = bSet;

   //   m_bAppHasInstallerChangedProtected = true;

   //}


//   void application::assert_ok() const
//   {
//
//      ::aqua::application::assert_ok();
//
//   }
//
//
//   void application::dump(dump_context & dumpcontext) const
//   {
//
//      ::aqua::application::dump(dumpcontext);
//
//      //dumpcontext << "\nm_bHelpMode = " << m_strAppName;
//
//      //dumpcontext << "\n";
//
//   }


   void application::install_message_routing(::channel * pchannel)
   {

      ::aqua::application::install_message_routing(pchannel);

      //add_command_handler("app_exit", &application::on_message_app_exit);
      add_command_handler("switch_context_theme", { this, &application::_001OnSwitchContextTheme });

   }


   //void application::call_request(::request * prequest)
   //{

   //   auto psystem = system();

   //   if (psystem->payload("exit_on_application_call_request").is_true())
   //   {

   //      exit(0);

   //      return;

   //   }

   //   auto purl = psystem->url();

   //   if (pcreate->m_ecommand == ::e_command_protocol)
   //   {

   //      string str;
   //      
   //      str = pcreate->m_payloadFile;

   //      if (!m_pinterprocesscommunication)
   //      {

   //         ::pointer<::user::interaction>pinteraction;

   //         get_frame(pinteraction);

   //         if (pinteraction == nullptr)
   //         {

   //            return;

   //         }

   //         auto papp = pinteraction->get_app();

   //         if (papp == nullptr)
   //         {

   //            return;

   //         }

   //         if (papp->m_pinterprocesscommunication == nullptr)
   //         {

   //            return;

   //         }

   //      }

   //      if (str.case_insensitive_begins(m_pinterprocesscommunication->m_ptarget->m_strBaseChannel + "://"))
   //      {

   //         m_pinterprocesscommunication->_handle_uri(str);

   //         //   if (str.case_insensitive_begins_eat("send?message="))
   //         //   {

   //         //      m_pinterprocesscommunication->_handle_call(m_pinterprocesscommunication->m_prx, ::url::decode(str));

   //         //   }
   //         //   else if (str.case_insensitive_begins_eat("send?messagebin="))
   //         //   {

   //         //      auto pFind = str.find(',');

   //         //      if (::is_set(pFind))
   //         //      {

   //         //         int message = atoi(str(0, pFind));

   //         //         memory m;

   //         //         auto psystem = system();

   //         //         auto pbase64 = psystem->base64();

   //         //         pbase64->decode(m, ::url::decode(str(pFind + 1)));

   //         //         m_pinterprocesscommunication->on_interprocess_receive(m_pinterprocesscommunication->m_prx, message, ::transfer(m));

   //         //      }

   //         //   }

   //         //}

   //      }


   //   }
   //   //else if (pcreate->m_ecommand == ::command_on_agree_exit)
   //   //{

   //   //   m_bAgreeExit = _001OnAgreeExit();

   //   //   m_bAgreeExitOk = true;

   //   //   return;

   //   //}
   //   else if (pcreate->m_ecommand == ::e_command_request_exit)
   //   {

   //      request_exit_application();

   //      return;

   //   }
   //   else
   //   {

   //      on_request(pcreate);

   //   }

   //   m_bAttendedFirstRequest = true;

   //   defer_process_activation_message();
   //   //return ::success;

   //}


   //void application::on_request(::request * prequest)
   //{

   //   if (is_service())
   //   {

   //      ::aura::application::on_service_request(pcreate);

   //   }
   //   else
   //   {

   //      try
   //      {

   //         do_request(pcreate);

   //      }
   //      // catch (not_installed * pexception)
   //      // {

   //      //    ::exception_pointer esp(pexception);

   //      //    psystem->on_run_exception(esp);

   //      //    throw ::exception(exit_exception(esp->get_app(), ::exit_application));

   //      // }
   //      catch (const ::exception & e)
   //      {

   //         handle_exception(e);

   //      }

   //      auto psystem = system();

   //      // Verry Sory for the per request overhead here for the needed information of only first request
   //      if (::is_set(psystem) && psystem->m_timeAfterApplicationFirstRequest.is_null())
   //      {

   //         psystem->m_timeAfterApplicationFirstRequest.Now(); // cross your fingers that the first recorded is not 0, it will be cleaned up by other requests.

   //      }

   //      try
   //      {

   //         pcreate->get_property_set().unset("document");

   //      }
   //      catch (...)
   //      {

   //      }

   //      //::pointer<::aura::session>pbergedge = pcreate->payload("bergedge_callback").cast < ::aura::session >();
   //      // todobergedge
   //      /*if(pbergedge != nullptr)
   //      {
   //      pbergedge->on_app_request_bergedge_callback(this);
   //      }*/
   //      pcreate->m_happeningReady.set_happening();

   //   }

   //}


   //void application::message_box_synchronous(::user::interaction_base * puiOwner, const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox, ::callback callback)
   //{

   //   return ::auto pmessagebox = __initialize_new ::message_box(puiOwner->get_safe_handle(), pszMessage, pszTitle, emessagebox, callback);

//pmessagebox->sync();

   //}


   //void application::ui_message_box(::user::interaction_base* puiOwner, const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox, ::callback callback)
   //{

   //   if (!Session || !psession->userex())
   //   {

   //      return ::error_failed;

   //   }

   //   return psession->userex()->ui_message_box(this, puiOwner, pszMessage, pszTitle, emessagebox, callback);

   //}


   //void application::ui_message_box_timeout(::user::interaction_base* puiOwner, const ::string & pszMessage, const ::string & pszTitle, const class time & timeTimeout, const ::e_message_box & emessagebox, ::callback callback)
   //{

   //   if (!Session || !psession->userex())
   //   {

   //      return ::error_failed;

   //   }

   //   return psession->userex()->ui_message_box_timeout(this, puiOwner, pszMessage, pszTitle, timeTimeout, emessagebox, callback);

   //}


   //void application::message_box(::user::interaction_base* puiOwner, const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox, ::callback callback)
   //{

   //   auto estatus = ui_message_box(puiOwner, pszMessage, pszTitle, emessagebox, callback);

   //   if(!estatus)
   //   {

   //      return estatus;

   //   }

   //   return auto pmessagebox = __initialize_new ::message_box(puiOwner, pszMessage, pszTitle, emessagebox, callback);

//pmessagebox->sync();

   //}


   //void application::message_box_timeout(::user::interaction_base* puiOwner, const ::string & pszMessage, const ::string & pszTitle, const class time & timeTimeout, const ::e_message_box & emessagebox, ::callback callback)
   //{

   //   auto estatus = ui_message_box_timeout(puiOwner, pszMessage, pszTitle, timeTimeout, emessagebox, callback);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return auto pmessagebox = __initialize_new ::message_box(puiOwner, pszMessage, pszTitle, emessagebox, callback);

//pmessagebox->sync();

   //}


   //void application::message_box(const ::payload & payload)
   //{

   //   ::pointer<::user::interaction_base>puiOwner;

   //   string strMessage;

   //   string strTitle;

   //   unsigned long long uFlags = 0;

   //   ::time timeTimeout;

   //   ::function_arg function;

   //   if (payload.get_type() != e_type_property_set)
   //   {

   //      strMessage = payload;

   //   }
   //   else
   //   {

   //      puiOwner = payload["owner"].cast < ::user::interaction_base >();
   //      strMessage = payload["message"];
   //      strTitle = payload["title"];
   //      uFlags = payload["flags"];
   //      timeTimeout = payload["time"];
   //      function = payload["function_arg"];

   //   }

   //   if (timeTimeout.is_null())
   //   {

   //      return message_box(puiOwner, strMessage, strTitle, (unsigned int) uFlags, function);

   //   }
   //   else
   //   {

   //      return message_box_timeout(puiOwner, strMessage, strTitle, timeTimeout, (unsigned int) uFlags, function);

   //   }

   //}


   //// lang string
   //// load string
   //string application::lstr(const ::atom & atom, string strDefault)
   //{

   //   string str;

   //   if (!load_string(str, atom))
   //   {

   //      if (strDefault.has_character())
   //         return strDefault;

   //      return "";

   //   }

   //   return str;

   //}




   //void application::on_file_new()
   //{

   //}


   //string application::load_string(const ::atom & atom)
   //{
   //   string str;
   //   if (!load_string(str, atom))
   //   {
   //      return (const string &)atom;
   //   }
   //   return str;
   //}

   //bool application::load_string(string & str, const ::atom & atom)
   //{
   //   if (!load_cached_string(str, atom, true))
   //   {
   //      return false;
   //   }
   //   return true;
   //}

   /*bool application::load_cached_string(string & str, const ::atom & atom, bool bLoadStringTable)
   {

      ::xml::document doc;

      if (!doc.load(atom))
      {

         if (load_cached_string_by_id(str, atom, bLoadStringTable))
         {

            return true;

         }

      }

      if (doc.get_name() == "string")
      {

         string strId = doc.attribute("id");

         if (load_cached_string_by_id(str, strId, bLoadStringTable))
         {

            return true;
         }

         str = doc.get_value();

         return true;

      }

      return false;

   }*/


   //bool application::load_cached_string_by_id(string & str, const ::atom & atom, bool bLoadStringTable)
   //{

   //   string strId(atom.str());

   //   string strTable;

   //   string strString;

   //   ::pointer<string_to_string>pmap;

   //   auto pFind = 0;

   //   if ((iFind = strId.find(':')) <= 0)
   //   {

   //      strTable = "";

   //      strString = strId;

   //   }
   //   else
   //   {

   //      strTable = strId(0, pFind);

   //      strString = strId(pFind + 1);

   //   }

   //   _synchronous_lock synchronouslock(m_pmutexStr);

   //   if (m_stringtableStd.lookup(strTable, pmap))
   //   {

   //      if (pmap->lookup(strString, str))
   //      {

   //         return true;

   //      }

   //   }
   //   else if (m_stringtable.lookup(strTable, pmap))
   //   {

   //      if (pmap->lookup(strString, str))
   //      {

   //         return true;

   //      }

   //   }
   //   else if (bLoadStringTable)
   //   {

   //      synchronouslock.unlock();

   //      load_string_table(strTable, "");

   //      return load_cached_string_by_id(str, atom, false);

   //   }

   //   return false;

   //}


   //void application::load_string_table(const string & pszApp, const string & pszId)
   //{

   //}




   //void application::load_string_table()
   //{
   //   load_string_table("", "");
   //}





   //object * application::alloc(::type info)
   //{

   //   return psystem->alloc(this, info);

   //}


   //object * application::alloc(const  atom & idType)
   //{

   //   return psystem->alloc(this, idType);

   //}


   //bool application::is_system() const
   //{

   //   return false;

   //}


 /*  bool application::is_session() const
   {

      return false;

   }*/


   //bool application::is_serviceable() const
   //{

   //   return false;

   //}


   //bool application::is_user_service() const
   //{

   //   bool bIsUserService = true;

   //   bool bIsService = is_serviceable();

   //   return bIsUserService && bIsService;

   //}



//   ::file::path command_find_path(const ::string & pszCommand)
//   {
//
//#ifdef UNIVERSAL_WINDOWS
//
//      return "";
//
//#else
//
//      string strPath = getenv("PATH");
//
//      string_array straPath;
//
//      straPath.explode(":", strPath);
//
//      for (auto & str : straPath)
//      {
//
//         ::file::path path;
//
//         path = str;
//
//         path /= pszCommand;
//
//         if (file_system()->exists(path))
//         {
//
//            return path;
//
//         }
//
//      }
//
//      return pszCommand;
//
//#endif
//
//   }
//#ifdef WINDOWS_DESKTOP
//
//
//   class open_browser_enum
//   {
//   public:
//
//      string                           m_strWindowEnd;
//      string                           m_strTopic;
//      string                           m_strCounterTopic;
//      oswindow                         m_hwnd;
//      comparable_array < oswindow >    m_hwndaTopic;
//      comparable_array < oswindow >    m_hwndaCounterTopic;
//
//   };
//
//
//   int_bool CALLBACK enum_proc(oswindow hwnd, lparam lparam)
//   {
//
//      open_browser_enum * penum = (open_browser_enum *)lparam;
//
//      string str = ::str::get_window_text_timeout(hwnd, 1000);
//
//      if (case_insensitive_string_ends(str, penum->m_strWindowEnd))
//      {
//
//         penum->m_hwnd = hwnd;
//
//         return false;
//
//      }
//
//      return true;
//
//   }
//
//
//   int_bool CALLBACK enum_proc_ff_topic(oswindow hwnd, lparam lparam)
//   {
//
//      open_browser_enum * penum = (open_browser_enum *)lparam;
//
//      string str = ::str::get_window_text_timeout(hwnd);
//
//      if (case_insensitive_string_ends(str, penum->m_strTopic))
//      {
//
//         penum->m_hwndaTopic.add(hwnd);
//
//      }
//
//      return true;
//
//   }
//
//   int_bool CALLBACK enum_proc_ff_counter_topic(oswindow hwnd, lparam lparam)
//
//   {
//
//      open_browser_enum * penum = (open_browser_enum *)lparam;
//
//
//      string str = ::str::get_window_text_timeout(hwnd, 1000);
//
//      if (case_insensitive_string_ends(str, penum->m_strCounterTopic))
//      {
//
//         penum->m_hwndaCounterTopic.add(hwnd);
//
//      }
//
//      return true;
//
//   }
//
//#endif




   //::file::path application::defer_process_path(::file::path path)
   //{

   //   return psystem->defer_process_path(path, this);

   //}


   //::file::path application::full_process_path(::file::path path)
   //{

   //   if (!(path & ::file::e_flag_dont_resolve_alias))
   //   {

   //      path |= ::file::e_flag_resolve_alias;

   //   }

   //   return psystem->full_process_path(path, this);

   //}




   //void application::sync_open_profile_link(string strUrl, string strProfile, string strTarget)
   //{

   //   browser(strUrl, "", strProfile, strTarget);

   //}


   //bool application::open_link(string strLink, string strProfile, string strTarget)
   //{

   //   if (is_system())
   //   {

   //      if (strLink.case_insensitive_begins("mailto:"))
   //      {

   //         return os().file_open(this, strLink);

   //      }

   //      open_profile_link(strLink, strProfile, strTarget);

   //      return true;

   //   }
   //   else
   //   {

   //      return psession->open_link(strLink, strProfile, strTarget);

   //   }

   //   return false;

   //}


//#ifdef WINDOWS_DESKTOP
//
//   void application::TermThread(HINSTANCE hInstTerm)
//   {
//
//      throw ::interface_only();
//
//   }
//
//
//#endif


   //bool application::_001OnDDECommand(const ::string & pcsz)

   //{

   //   throw ::interface_only();

   //   return false;

   //}



   /*::user::document *  application::_001OpenDocumentFile(::payload payloadFile)
   {

      throw ::interface_only();

      return nullptr;

   }*/


   //void application::_001OnFileNew(::message::message * pmessage)
   //{

   //   throw ::interface_only();

   //}


//bool application::update_module_paths()
//{


//   if(is_system())
//   {

//      if(!m_pimpl->update_module_paths())
//         return false;


//   }

//   return true;


//}





   //void application::_001CloseApplication()
   //{

   //   throw ::exception(todo);

   //}












   //void application::DoWaitCursor(int nCode) // 0 => restore, 1=> begin, -1=> end
   //{

   //   __UNREFERENCED_PARAMETER(nCode);

   //}


//   void application::show_wait_cursor(bool bShow)
//   {
//
//      if (m_pappimpl.is_null())
//         return;
//
//      m_pappimpl->show_wait_cursor(bShow);
//
//
//   }
//
//

//   string CLASS_DECL_AURA application::get_cred(const ::string & strRequestUrl, const ::int_rectangle & rectangle, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive)
// {

//  throw ::not_implemented();

//}




   //bool application::get_temp_file_name_template(string & strRet, const ::string & lpszName, const ::string & pszExtension, const ::string & pszTemplate)
   //{

   //   throw ::not_implemented();

   //   return false;

   //}


   //bool application::get_temp_file_name(string & strRet, const ::string & lpszName, const ::string & pszExtension)
   //{

   //   return get_temp_file_name_template(strRet, lpszName, pszExtension, nullptr);

   //}


   //bool application::process_exception(const ::exception & e)
   //{

   //   return ::thread::process_exception(pe);

   //}


   //void application::init_thread()
   //{

   //   try
   //   {

   //      psession->add_reference(this);

   //   }
   //   catch (...)
   //   {

   //   }

   //   try
   //   {

   //      if (!pre_run())
   //      {

   //         return false;

   //      }

   //   }
   //   catch (const ::exception & e)
   //   {

   //      handle_exception(pe);

   //      return false;

   //   }
   //   catch (...)
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //void application::term_thread()
   //{

   //   information() << "aura::application::term_thread";

   //   ping();

   //   try
   //   {

   //      pos_run();

   //   }
   //   catch (...)
   //   {

   //   }

   //   ::thread::term_thread();

   //}


//   void application::pre_run()
//   {
//
//      information() << "aura::application::pre_run";
//
//      try
//      {
//
//         ping();
//
//         if(!application_pre_run())
//         {
//
//            m_bReady = true;
//
//            return false;
//
//         }
//
//         //    if(!check_install())
//         //    {
//
//         //       m_bReady = true;
//
//         //       return false;
//
//         //    }
//
////         if(!is_system() && !is_session())
////         {
////
////            if(!is_installed())
////            {
////
////
////            }
////
////         }
//
//         //xxdebug_box("pre_run 1 ok", "pre_run 1 ok", e_message_box_icon_information);
//
//         if (!initial_check_directrix())
//         {
//
//            m_bReady = true;
//
//            return false;
//
//         }
//
//         ping();
//
//         if (!os_native_bergedge_start())
//         {
//
//            m_bReady = true;
//
//            return false;
//
//         }
//
//         information() << "aura::application::pre_run success";
//
//         return true;
//
//      }
//      catch (const ::exception & e)
//      {
//
//         handle_exception(pe);
//
//      }
//      catch (...)
//      {
//
//         information() << "aura::application::pre_run exception.4";
//
//      }
//
//      return false;
//
//   }


//   void application::on_run()
//   {
//
//      void     estatus = ::success;
//
//      try
//      {
//
//         ::message::application message(::message::application_begin);
//
//         route_message(&message);
//
//      }
//      catch (...)
//      {
//
//      }
//
//      //thisstart << m_iErrorCode;
//
//      thread * pthread = ::get_task();
//
//      install_message_routing(pthread);
//
//      //thisok << 1 << m_iErrorCode;
//
//      //try
//      //{
//
//      m_bReady = true;
//
//      //   if (m_pevAppBeg != nullptr)
//      //   {
//
//      //      m_pevAppBeg->set_happening();
//
//      //   }
//
//      //}
//      //catch (...)
//      //{
//
//      //}
//
//      //if(::is_set(get_context_system()))
//      //{
//
//      //   psystem->add_reference(this);
//
//      //}
//
//      //if(::is_set(get_session()))
//      //{
//
//      //   get_session()->add_reference(this);
//
//      //}
//
//      //if(::is_set(m_pappParent))
//      //{
//
//      //   m_pappParent->__add_reference(this);
//
//      //}
//
//      if (::is_set(m_pappParent))
//      {
//
//         m_pappParent->add_reference(this);
//
//      }
//
//      try
//      {
//
//resume_on_exception:
//
//         try
//         {
//
//            estatus = run();
//
//         }
//         catch (const ::exception & e)
//         {
//
//            if (handle_exception(e))
//            {
//
//               goto resume_on_exception;
//
//            }
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//      //try
//      //{
//
//      //   if (m_pevAppEnd != nullptr)
//      //   {
//
//      //      m_pevAppEnd->set_happening();
//
//      //   }
//
//      //}
//      //catch (...)
//      //{
//
//      //}
//
//      return estatus;
//
//   }

   //void application::on_pos_run_thread()
   //{

   //   ::aqua::application::on_pos_run_thread();

   //}




   //void application::pos_run()
   //{

   //   information() << "aura::application::pos_run";

   //   try
   //   {

   //      ping();

   //      application_pos_run();

   //      //xxdebug_box("pre_run 1 ok", "pre_run 1 ok", e_message_box_icon_information);

   //   }
   //   catch (...)
   //   {

   //      information() << "aura::application::pos_run exception.4";

   //   }

   //}


   void application::init_instance()
   {

      //auto estatus =
      
      ::aqua::application::init_instance();



      {

         ::string strImplementation = application_file_setting("draw2d.txt");

         strImplementation.make_lower();

         if (strImplementation == "directx11")
         {

            strImplementation = "directx11";

         }
         else if (strImplementation == "directx12")
         {

            strImplementation = "directx12";

         }
         else if (strImplementation == "opengl")
         {

            strImplementation = "opengl";

         }
         else if (strImplementation == "vulkan")
         {

            strImplementation = "vulkan";

         }
         else if (strImplementation == "direct2d")
         {

            strImplementation = "direct2d";

         }
         else
         {

            strImplementation.empty();

         }

         m_strDraw2dImplementation = strImplementation;

      }


      {

         ::string strImplementation = application_file_setting("graphics3d.txt");

         strImplementation.make_lower();

         if (strImplementation == "directx11")
         {

            strImplementation = "directx11";

         }
         else if (strImplementation == "directx12")
         {

            strImplementation = "directx12";

         }
         else if (strImplementation == "opengl")
         {

            strImplementation = "opengl";

         }
         else if (strImplementation == "vulkan")
         {

            strImplementation = "vulkan";

         }
         else
         {

            strImplementation = "opengl";

         }

         m_strGraphics3DImplementation = strImplementation;

      }

      {

         ::string strOutput = application_file_setting("graphics3d_output.txt");

         strOutput.make_lower();

         if (strOutput.equals("swap_chain") || strOutput.equals("on_screen"))
         {

            m_gpu.m_bUseSwapChainWindow = true;

         }
         else
         {

            m_gpu.m_bUseSwapChainWindow = false;

         }

      }

      ::cast < ::manager > pmanager = system();
 
      if(pmanager)
      {
         auto psignal = pmanager->signal(id_app_activated);
      
         psignal->add_handler(this);
      }

   }


   void application::term_instance()
   {


   }

   //void application::notify_init3()
   //{

   //   ::message::application message(::message::application_init3);

   //   route_message(&message);

   //   return message.m_bOk;

   //}


   void application::_001InitializeShellOpen()
   {

      //ASSERT(m_atomApp == nullptr && m_atomSystemTopic == nullptr); // do once

      //m_atomApp            = ::GlobalAddAtomW(utf8_to_unicode(m_strAppName));

      //m_atomSystemTopic    = ::GlobalAddAtomW(L"system");

      //auto estatus =

#ifdef WINDOWS_DESKTOP
      
      __øconstruct(m_pshellopen);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      m_pshellopen->initialize_shell_open();

#endif

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }

   //void application::application_pos_run()
   //{

   //   try
   //   {

   //      //if (!is_installing() && !is_unstalling())
   //      {

   //         term_instance();

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   try
   //   {

   //      term_application();

   //   }
   //   catch (...)
   //   {

   //   }

   //   ping();

   //   try
   //   {

   //      process_term();

   //   }
   //   catch (...)
   //   {

   //   }

   //   //try
   //   //{

   //   //   TermApplication();

   //   //}
   //   //catch (...)
   //   //{

   //   //}



   //}

 
   void application::do_install()
   {

      auto psystem = system();


      on_install();
      //if (!on_install())
      //{

      //   informationf("Failed at on_install : " + m_strAppId + "\n\n");

      //   psystem->m_result.add(error_failed);

      //   return false;

      //}

      string strBuild = m_strBuild;

      string strAppId = m_strAppId;

      //xxdebug_box("on_install1", strAppId, 0);

      system_add_app_install(strAppId, strBuild);


      //return true;

   }


   void application::on_before_launching()
   {

      auto psession = session();

      string strLicense = get_license_id();

      auto psystem = system();

      bool bHasInstall = psystem->is_true("install");

      bool bHasUninstall = psystem->is_true("uninstall");

      if (!(bHasInstall || bHasUninstall)
            && m_bLicense
            && strLicense.has_character())
      {

         if (!assert_user_logged_in())
         {
            //return false;

            throw ::exception(error_authentication_none);

         }

         // call application's is_licensed function
         // because if delay is needed for authentication -
         // or either asking for authentication -
         // current application startup won't be
         // exited by timeout.

         int iRetry = 1;

retry_license:

         iRetry--;

         if (!psession->is_licensed(strLicense))
         {

            if (iRetry > 0)
               goto retry_license;

            //return false;

            throw ::exception(error_licensing);

         }

      }

      information() << "initial_check_directrix : ok ("<< ::type(this).name() << ")" << m_strAppId;

      //return true;

   }


   void application::do_uninstall()
   {

      on_uninstall();

//      if (!on_uninstall())
//      {
//
//         return false;
//
////         psystem->install().erase_spa_start(m_XstrAppId);
//
//      }

      //return true;

   }


   void application::on_install()
   {

      if (is_service())
      {

         ::aqua::application::on_install();

         //if (!init_service())
         //{

         //   return false;

         //}

         //os_start_service();

      }
      else
      {

// #ifdef WINDOWS_DESKTOP

//          auto psystem = system();

//          string strModuleName = psystem->file()->module();

//          system()->m_pnode->install_crash_dump_reporting(strModuleName);

// #endif

      }
      //return true;

   }


   void application::on_uninstall()
   {

      //bool bOk = axis::application::on_uninstall();

      bool bOk = true;


      if (is_service())
      {
         ::aqua::application::on_uninstall();

         //if (!os_erase_service())
         //{

         //   bOk = false;

         //}

      }

      //return bOk;

   }


   void application::process_init()
   {

      //auto estatus =
      
      ::aqua::application::process_init();

      //if (!estatus)
      //{

      //   return estatus;

      //}


      information() << "axis::application::process_init";


      information() << "aura::application::process_init success";


      //return true;

   }


   //void application::process_term()
   //{


   //   apex::application::process_term();


   //
   //}


//   void application::init_application()
//   {
//
//      auto estatus = ::application::init_application();
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      information() << "aura::application::init_application";
//
//      //m_bAuraInitializeInstance = true;
//
//      //m_bAuraInitializeInstanceResult = false;
//
//      ping();
//
//      if (!init1())
//      {
//
//         //dappy(::type(this).name() + " : init1 failure : " + as_string(m_iErrorCode));
//
//         return false;
//
//      }
//
//      psystem->install_progress_add_up(); // 2
//
//      //xxdebug_box("init1 ok", "init1 ok", e_message_box_icon_information);
//
//      ping();
//
//      if (!init2())
//      {
//
//         //dappy(::type(this).name() + " : init2 failure : " + as_string(m_iErrorCode));
//
//         return false;
//
//      }
//
//      psystem->install_progress_add_up(); // 3
//
//      //xxdebug_box("init2 ok", "init2 ok", e_message_box_icon_information);
//
//      ping();
//
//      if (!init3())
//      {
//
//         //dappy(::type(this).name() + " : init3 failure : " + as_string(m_iErrorCode));
//
//         return false;
//
//      }
//
//      psystem->install_progress_add_up(); // 4
//
//      //xxdebug_box("init3 ok", "init3 ok", e_message_box_icon_information);
//
//      ping();
//
//      //dappy(::type(this).name() + " : init3 ok : " + as_string(m_iErrorCode));
//
//      try
//      {
//
//         if (!init())
//         {
//
//            //dappy(::type(this).name() + " : initialize failure : " + as_string(m_iErrorCode));
//
//            return false;
//
//         }
//
//      }
//      catch (const ::string & psz)
//      {
//
//         if (!strcmp(psz, "You have not logged in! Exiting!"))
//         {
//
//            return false;
//
//         }
//
//         return false;
//
//      }
//
//      psystem->install_progress_add_up(); // 5
//
////      m_bAuraInitializeInstanceResult = true;
//
//      return true;
//
//   }


   //::pointer<::interprocess::communication>application::create_interprocess_communication()
   //{

   //   try
   //   {

   //      return __allocate ::interprocess::communication(m_strAppName);

   //   }
   //   catch (...)
   //   {

   //      return nullptr;

   //   }

   //}


   void application::init1()
   {

      //::e_status estatus = 
      
      ::aqua::application::init1();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto psystem = system();

      //if (psystem->m_bImaging)
      //{

      //   //estatus = 
      //   __øconstruct(m_pimagecontext);

      //   //if (!estatus)
      //   //{

      //   //   information() << "ERROR: image_context required but missing.";

      //   //   //output_error_message("image_context required but missing.\n\nIs it a image library missing?", get_app_user_friendly_task_bar_name(), ::e_message_box_icon_information);

      //   //   return estatus;

      //   //}

      //}
      //else
      //{

         

      // if (!m_pimagecontext)
      // {

      //    //estatus = 
         
      //    __construct_new(m_pimagecontext);

      //    //if (!estatus)
      //    //{

      //    //   information() << "ERROR: image_context required but missing.";

      //    //   //output_error_message("image_context required but missing.\n\nIs it a image library missing?", get_app_user_friendly_task_bar_name(), ::e_message_box_icon_information);

      //    //   return estatus;

      //    //}

      // }


      information() << "apex::application::init1 end";

      ping();

      //return ::success;

   }


   void application::term1()
   {

      //try
      //{

      //   impl_term1();

      //}
      //catch (...)
      //{

      //}

      try
      {

         notify_term1();

      }
      catch(...)
      {

      }

   }

   void application::init2()
   {

      ::aqua::application::init2();

      //if (!impl_init2())
      //{

      //   return false;

      //}

      notify_init2();

      //if (!notify_init2())
      //{

      //   return false;

      //}

      //return true;

   }


   void application::term2()
   {

      //try
      //{

      //   impl_term2();

      //}
      //catch (...)
      //{

      //}

      try
      {

         notify_term2();

      }
      catch(...)
      {

      }

   }

   void application::init3()
   {

      string strFolder = m_strAppName;

      strFolder.replace_with("_", ".");
      strFolder.replace_with("-", "::");
      strFolder.replace_with("_", ":");

      m_strRelativeFolder = strFolder;

      //if (!impl_init3())
      //{

      //   return false;

      //}

      notify_init3();

      //if (!notify_init3())
      //{

      //   return false;

      //}

      //return true;

   }


   void application::term3()
   {

      //try
      //{

      //   impl_term3();

      //}
      //catch (...)
      //{

      //}

      try
      {

         notify_term3();

      }
      catch(...)
      {

      }

   }


   void application::term_application()
   {

      release_exclusive();

      try
      {

         //if(::is_set(m_pappParent))
         //{

         //   m_pappParent->app_erase(this);

         //}

         //if(::is_set(get_session()))
         //{

         //   get_session()->post_message(e_message_erase_application, 0, this);

         //}


         try
         {

            term();

         }
         catch(...)
         {


         }

         try
         {

            term3();

         }
         catch(...)
         {


         }

         try
         {

            term2();

         }
         catch(...)
         {


         }

         try
         {

            term1();

         }
         catch(...)
         {


         }


      }
      catch (...)
      {

      }

   }


   bool application::Ex2OnAppInstall()
   {

      return true;

   }


   bool application::Ex2OnAppUninstall()
   {

      return true;

   }


   //void application::on_set_scalar(enum_scalar escalar, long long iValue, int iFlags)
   //{

   //   //if (escalar == scalar_app_install_progress)
   //   //{

   //   //   m_iProgressInstallStep = iValue;

   //   //}
   //   //else if (escalar == scalar_app_install_progress_min)
   //   //{

   //   //   m_iProgressInstallStart = iValue;

   //   //}
   //   //else if (escalar == scalar_app_install_progress_max)
   //   //{

   //   //   m_iProgressInstallEnd = iValue;

   //   //}
   //   //else
   //   {

   //      return ::int_scalar_source::on_set_scalar(escalar, iValue, iFlags);

   //   }

   //}


   //void application::get_scalar_minimum(enum_scalar escalar, long long & i)
   //{

   //   //if (escalar == scalar_app_install_progress)
   //   //{

   //   //   i = m_iProgressInstallStart;

   //   //}
   //   //else if (escalar == scalar_app_install_progress_min)
   //   //{

   //   //   i = 0;

   //   //}
   //   //else if (escalar == scalar_app_install_progress_max)
   //   //{

   //   //   i = 0;

   //   //}
   //   //else
   //   {

   //      ::int_scalar_source::get_scalar_minimum(escalar, i);

   //   }

   //}

   //void application::get_scalar(enum_scalar escalar, long long & i)
   //{

   //   //if (escalar == scalar_app_install_progress)
   //   //{

   //   //   i = m_iProgressInstallStep;

   //   //}
   //   //else if (escalar == scalar_app_install_progress_min)
   //   //{

   //   //   i = m_iProgressInstallStart;

   //   //}
   //   //else if (escalar == scalar_app_install_progress_max)
   //   //{

   //   //   i = m_iProgressInstallEnd;

   //   //}
   //   //else
   //   {

   //      ::int_scalar_source::get_scalar(escalar, i);

   //   }

   //}

   //void application::get_scalar_maximum(enum_scalar escalar, long long & i)
   //{

   //   //if (escalar == scalar_download_size)
   //   //{

   //   //   i = m_iProgressInstallEnd;

   //   //}
   //   //else if (escalar == scalar_app_install_progress_min)
   //   //{

   //   //   i = I32_MAXIMUM;

   //   //}
   //   //else if (escalar == scalar_app_install_progress_max)
   //   //{

   //   //   i = I32_MAXIMUM;

   //   //}
   //   //else
   //   {

   //      ::int_scalar_source::get_scalar_minimum(escalar, i);

   //   }

   //}


   ////int application::sync_message_box_timeout(::user::interaction_base * puserinteractionOwner, ::payload payload, const ::string & pszTitle, ::time timeTimeOut, unsigned int fuStyle)
   ////{

   ////   __UNREFERENCED_PARAMETER(timeTimeOut);

   ////   return sync_message_box(puserinteractionOwner, payload, pszTitle, fuStyle);

   ////}









   //string application::http_get_locale_schema(const ::string & pszUrl, const ::string & pszLocale, const ::string & pszSchema)
   //{

   //   throw ::interface_only();

   //   return "";

   //}




   //void application::message_handler(::user::message * pusermessage)
   //{

   //   ::thread::message_handler(pusermessage);

   //}


   //void application::set_locale(const string & pcsz, const ::action_context & context)

   //{

   //   string strLocale(pcsz);


   //   strLocale.trim();

   //   m_strLocale = strLocale;

   //   on_set_locale(m_strLocale, context);

   //}


   //void application::set_schema(const string & pcsz, const ::action_context & context)

   //{

   //   string strSchema(pcsz);


   //   strSchema.trim();

   //   m_strSchema = strSchema;

   //   on_set_schema(m_strSchema, context);

   //}


   //void application::on_set_locale(const string & pcsz, const ::action_context & context)

   //{
   //   __UNREFERENCED_PARAMETER(context);
   //   __UNREFERENCED_PARAMETER(pcsz);

   //   //psystem->appa_load_string_table();
   //}


   //void application::on_set_schema(const string & pcsz, const ::action_context & context)

   //{
   //   __UNREFERENCED_PARAMETER(context);
   //   __UNREFERENCED_PARAMETER(pcsz);

   //   //psystem->appa_load_string_table();
   //}


   //string application::get_locale_schema_dir()
   //{

   //   return ::str::_001Concat(get_locale(), "/", get_schema());

   //}


   //string application::get_locale_schema_dir(const ::string & strLocale)
   //{

   //   return ::str::_001Concat(strLocale.is_empty() ? get_locale() : strLocale, "/", get_schema());

   //}


   //void application::matter_locator_locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema)
   //{

   //   if (strLocale.is_empty() || strSchema.is_empty())
   //   {

   //      return;

   //   }

   //   for (auto & strMatterLocator : straMatterLocator)
   //   {

   //      string strLs = get_locale_schema_dir(strLocale, strSchema);

   //      stra.add_unique(::file::path(strMatterLocator) / strLs);

   //   }

   //}


   //void application::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema)
   //{

   //  if (straMatterLocator.has_elements())
   //  {

   //     stra.add_unique(::file::path(straMatterLocator.first()) / get_locale_schema_dir("map", "map"));

   //  }

   //  matter_locator_locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

   //  ::text::context * pcontext = psession->textcontext();

   //  for (int i = 0; i < localeschema().m_straLocale.get_count(); i++)
   //  {

   //     string strLocale = localeschema().m_straLocale[i];

   //     string strSchema = localeschema().m_straSchema[i];

   //     matter_locator_locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

   //  }

   //  matter_locator_locale_schema_matter(stra, straMatterLocator, "en", "en");

   //  matter_locator_locale_schema_matter(stra, straMatterLocator, "_std", "_std");

   //  if (straMatterLocator.has_elements())
   //  {

   //     stra.add_unique(::file::path(straMatterLocator.first()) / get_locale_schema_dir("404", "404"));

   //  }

   //}


   //string application::get_locale_schema_dir(const ::string & strLocale, const ::string & strSchema)
   //{

   //  return ::str::_001Concat(strLocale, "/", strSchema);

   //}


   //void application::fill_locale_schema(::text::international::locale_schema & localeschema, const string & pszLocale, const string & pszSchema)
   //{


   //  localeschema.m_straLocale.erase_all();
   //  localeschema.m_straSchema.erase_all();


   //  string strLocale(pszLocale);
   //  string strSchema(pszSchema);


   //  localeschema.m_atomLocale = pszLocale;
   //  localeschema.m_atomSchema = pszSchema;


   //  localeschema.add_locale_variant(strLocale, strSchema);
   //  localeschema.add_locale_variant(get_locale(), strSchema);
   //  localeschema.add_locale_variant("std", strSchema);
   //  localeschema.add_locale_variant("en", strSchema);


   //  localeschema.destroy();


   //}


   //void application::fill_locale_schema(::text::international::locale_schema & localeschema)
   //{


   //  localeschema.m_straLocale.erase_all();
   //  localeschema.m_straSchema.erase_all();


   //  //localeschema.m_bAddAlternateStyle = true;


   //  string_array straLocale;
   //  string_array straSchema;

   //  straLocale.add(get_locale());
   //  straSchema.add(get_schema());


   //  string_array stra;

   //  stra = value("locale").stra();

   //  stra.case_insensitive_erase("_std");

   //  straLocale.add_unique(value("locale").stra());

   //  stra.empty();

   //  stra = value("schema").stra();

   //  stra.case_insensitive_erase("_std");

   //  straSchema.add_unique(value("schema").stra());

   //  localeschema.m_atomLocale = straLocale[0];
   //  localeschema.m_atomSchema = straSchema[0];

   //  for (::collection::index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
   //  {

   //     for (::collection::index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
   //     {

   //        localeschema.add_locale_variant(straLocale[iLocale], straSchema[iSchema]);

   //     }

   //  }

   //  for (::collection::index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
   //  {

   //     localeschema.add_locale_variant(get_locale(), straSchema[iSchema]);

   //  }

   //  for (::collection::index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
   //  {

   //     localeschema.add_locale_variant("std", straSchema[iSchema]);

   //  }


   //  for (::collection::index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
   //  {

   //     localeschema.add_locale_variant("en", straSchema[iSchema]);

   //  }

   //  localeschema.destroy();


   //}


//  void application::defer_add_thread_run_wait(synchronization_array & soa)
//  {
//
////      soa.add(&axiom()->m_ev);
//
//  }


   //bool application::platform_open_by_file_extension(::collection::index iEdge, const ::string & pszPathName, ::request * prequest)
   //{

   //   return false;

   //}


   //bool application::platform_open_by_file_extension(::collection::index iEdge, ::create * pcc)
   //{

   //   return false;

   //}




   ////int application::hotplugin_host_starter_start_sync(const ::string & pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin)
   ////{

   //   return -1;

   //}


   //bool application::is_application() const
   //{

   //   return !is_session() && !is_system();

   //}



   //bool application::_001OnAgreeExit()
   //{

   //   return true;

   //}


   //void application::france_exit()
   //{

   //   //if (psystem->m_pmultimedia)
   //   //{

   //   //   psystem->m_pmultimedia->france_exit();

   //   //}


   //   HideApplication();

   //   close(::apex::e_end_app);

   //}


   //void application::_001FranceExit()
   //{

   //   france_exit();

   //   m_bFranceExit = true;

   //}


   //void application::dispatch_user_message(::user::message * pusermessage)
   //{

   //   pusermessage->send();

   //}


   //void application::play_audio(::payload payloadFile, bool bSynch)
   //{

   //   __UNREFERENCED_PARAMETER(payloadFile);
   //   __UNREFERENCED_PARAMETER(bSynch);

   //}
//
//   void application::post_critical_error_message(const ::string & pszMessage, bool bShowLog)
//   {
//
//      string strMessage;
//
//      strMessage = pdatetime->international().get_gmt_date_time();
//      strMessage += " ";
//      strMessage += pszMessage;
//      strMessage += "\n";
//
//      {
//
//         _synchronous_lock synchronouslock(this->synchronization());
//
//         file()->add_contents(directory()->appdata() / (file()->module().name() + "_log_error.txt"), strMessage);
//
//      }
//
//      if (bShowLog)
//      {
//
//         show_critical_error_log();
//
//      }
//
//   }
//
//
//   string application::get_app_user_friendly_task_bar_name()
//   {
//
//      ::file::path path = m_strAppName;
//
//      string strTitle = path.title();
//
//      return strTitle;
//
//   }
//
//
//
//   void application::show_critical_error_log()
//   {
//
//      static int g_iCount = 0;
//
//      string strFile = directory()->appdata() / (file()->module().name() + "_log_error.txt");
//
//      g_iCount++;
//
//      if (g_iCount == 1)
//      {
//
//         os().file_open(strFile);
//
//      }
//
////#ifdef UNIVERSAL_WINDOWS
////
////      information(strFile);
////
////#elif defined(WINDOWS)
////
////      call_async("C:\\Program Files (x86)\\Notepad++\\Notepad++.exe", "\"" + strFile + "\"", "", e_display_normal, false);
////
////#elif defined(LINUX)
////
////      call_async("gedit", "\"" + strFile + "\"", "", e_display_normal, false);
////
////#else
////
////      ::fork(this, [=]()
////      {
////
////         system("open \"" + strFile + "\"");
////
////      });
////
////
////#endif
//
//
//
//
//   }
//
//
//   void application::handle(::topic * ptopic, ::handler_context * phandlercontext)
//   {
//
//
//   }
//



   //bool application::compress_ungz(::file::file * pfileUncompressed, ::file::file * pfileCompressed)
   //{

   //   return psystem->compress().ungz(this, pfileUncompressed, pfileCompressed);

   //}


   //bool application::compress_gz(::file::file * pfileCompressed, ::file::file * pfileUncompressed, int iLevel)
   //{

   //   return psystem->compress().gz(this, pfileCompressed, pfileUncompressed, iLevel);


   //}

   //void application::interactive_credentials(::account::credentials * pcredentials)
   //{

   //   psession->interactive_credentials(pcredentials);

   //}


   //::file::path application::get_executable_path()
   //{

   //   return directory_system()->module() / (get_executable_title() + get_executable_extension());


   //}

//
//   string application::get_executable_extension()
//   {
//
//#ifdef WINDOWS
//
//      return ".exe";
//
//#else
//
//      return "";
//
//#endif
//
//   }
//
//
//   string application::get_executable_title()
//   {
//
//      return executable_title_from_appid(get_executable_appid());
//
//   }
//

   //string application::get_executable_appid()
   //{

   //   return m_XstrAppId;

   //}




   //bool application::app_set(string strPath, string strValue)
   //{

   //   return sys_set(::file::path(m_strAppName) / strPath, strValue);

   //}


   //string application::app_get(string strPath, string strDefault)
   //{

   //   return sys_get(::file::path(m_strAppName) / strPath, strDefault);

   //}


   //bool application::on_open_document_file(::payload payloadFile)
   //{

   //   request_file(payloadFile);

   //   return payloadFile["document"].cast < ::object > () != nullptr;

   //}



   //void application::install_trace(const ::string & str)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   //::install::trace_file(this, m_strInstallTraceLabel).print(str);

   ////}


   //void application::install_trace(double dRate)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   //::install::trace_file(this, m_strInstallTraceLabel).print(dRate);

   //}

//
//   bool application::register_spa_file_type()
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      HKEY hkey;
//
//      wstring extension = L".spa";                     // file extension
//      wstring desc = L"spafile";          // file type description
//      wstring content-type = L"application/x-spa";
//
//      wstring app(directory_system()->stage(m_XstrAppId, process_platform_name(), process_configuration_name()));
//
//      wstring icon(app);
//
//      app = L"\"" + app + L"\"" + L" \"%1\"";
//      icon = L"\"" + icon + L"\",107";
//
//      wstring action = L"Open";
//
//      wstring sub = L"\\shell\\";
//
//      wstring path = L"spafile\\shell\\open\\command";
//
//
//      // 1: Create subkey for extension -> HKEY_CLASSES_ROOT\.002
//      if (RegCreateKeyExW(HKEY_CLASSES_ROOT, extension.c_str(), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0) != ERROR_SUCCESS)
//      {
//         informationf("Could not create or open a registrty key\n");
//         return 0;
//      }
//      RegSetValueExW(hkey, L"", 0, REG_SZ, (unsigned char*)desc.c_str(), unsigned int (desc.length() * sizeof(wchar_t))); // default vlaue is description of file extension
//      RegSetValueExW(hkey, L"ContentType", 0, REG_SZ, (unsigned char*)content-type.c_str(), unsigned int (content-type.length() * sizeof(wchar_t))); // default vlaue is description of file extension
//      RegCloseKey(hkey);
//
//
//
//      // 2: Create Subkeys for action ( "Open with my program" )
//      // HKEY_CLASSES_ROOT\.002\Shell\\open with my program\\command
//      if (RegCreateKeyExW(HKEY_CLASSES_ROOT, path.c_str(), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0) != ERROR_SUCCESS)
//      {
//         informationf("Could not create or open a registrty key\n");
//         return 0;
//      }
//      RegSetValueExW(hkey, L"", 0, REG_SZ, (unsigned char*)app.c_str(), unsigned int(app.length() * sizeof(wchar_t)));
//      RegCloseKey(hkey);
//
//
//      path = L"spafile\\DefaultIcon";
//
//      if (RegCreateKeyExW(HKEY_CLASSES_ROOT, path.c_str(), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0) != ERROR_SUCCESS)
//      {
//         informationf("Could not create or open a registrty key\n");
//         return 0;
//      }
//      RegSetValueExW(hkey, L"", 0, REG_SZ, (unsigned char*)icon.c_str(), unsigned int (icon.length() * sizeof(wchar_t)));
//      RegCloseKey(hkey);
//
//      wstring wstr(directory_system()->stage(m_XstrAppId, process_platform_name(), process_configuration_name()) / "spa_register.txt");
//
//      int iRetry = 9;
//
//      while (!file_system()->exists(utf8(wstr.c_str())) && iRetry > 0)
//      {
//
//                  auto psystem = system();

//         auto pdirectorysystem = psystem->m_pdirectorysystem;
//
//pdirectorysystem->create(::file_path_folder(utf8(wstr.c_str())).c_str());
//
//         file_system()->put_contents(utf8(wstr.c_str()).c_str(), "");
//
//         iRetry--;
//
//         sleep(100_ms);
//
//      }
//
//#endif
//
//      return true;
//
//   }
//
//
//   bool application::low_is_app_app_admin_running(string strPlatform, string strConfiguration)
//   {
//
//      ::install::admin_mutex smutex(strPlatform);
//
//      return smutex.already_exists();
//
//   }
//
//
//   void application::defer_start_program_files_app_app_admin(string strPlatform, string strConfiguration)
//   {
//
//      if (low_is_app_app_admin_running(strPlatform, strConfiguration))
//      {
//
//         return;
//
//      }
//
//      start_program_files_app_app_admin(strPlatform, strConfiguration);
//
//   }
//
//
//   void application::start_program_files_app_app_admin(string strPlatform, string strConfiguration)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      SHELLEXECUTEINFOW sei = {};
//
//      string str = ::path::app_app_admin(strPlatform, strConfiguration);
//
//      if (!::file_system()->exists(str))
//      {
//
//         return;
//
//      }
//
//      ::install::admin_mutex mutexStartup("-startup");
//
//      wstring wstr(str);
//
//      sei.cbSize = sizeof(SHELLEXECUTEINFOW);
//      sei.fMask = SEE_MASK_NOASYNC | SEE_MASK_NOCLOSEPROCESS;
//      sei.lpVerb = L"RunAs";
//
//      sei.lpFile = wstr.c_str();
//
//      ::ShellExecuteExW(&sei);
//      unsigned int dwGetLastError = get_last_error();
//
//#endif
//
//   }
//
//
//   string application::get_app_id(string wstr)
//   {
//
//      if (wstr.length() <= 0)
//      {
//
//         return "";
//
//      }
//
//      wstr.trim();
//
//      ::str::trim_any_quotes(wstr);
//
//      wstr.trim();
//
//      if (wstr.length() <= 0)
//      {
//
//         return "";
//
//      }
//
//
//      ::string strPath = wstr.c_str();
//
//      ::string strContents = file_system()->as_string(strPath.c_str());
//
//      throw ::exception(todo("xml"));
//
//      //::xml::document doc;
//
//      //if (!doc.load(strContents.c_str()))
//      //{
//
//      //   return "";
//
//      //}
//
//      //const ::scoped_string & scopedstr = doc.GetChildAttrValue("launch", "app");
//
//      //if (psz == nullptr || *psz == '\0')
//      //{
//
//      //   return "";
//
//      //}
//
//      //return psz;
//
//      return nullptr;
//
//   }



   void application::defer_create_keyboard()
   {

      //set_keyboard_layout(nullptr,::e_source_database);

   }


   bool application::keyboard_focus_is_focusable(const ::user::interaction_base * pue)
   {

      return false;

   }


   bool application::keyboard_focus_OnSetFocus(::user::interaction_base * pprimitive)
   {

      return true;

   }


   bool application::get_frame(::pointer<::user::interaction>& pinteraction)
   {

#ifdef __ANDROID__

      auto psession = session();

      if (psession->get_user_interaction_host() != nullptr)
      {

         if (psession->get_user_interaction_host() != nullptr)
         {

            ::pointer<::user::interaction>puserinteraction = psession->get_user_interaction_host();

            if (puserinteraction)
            {

//                _synchronous_lock synchronouslock(puserinteraction->window()->m_pparticleChildrenSynchronization);
//
//                auto pacmeuserinteractionaChildren = puserinteraction->m_pacmeuserinteractionaChildren;
//
//
//                //auto puserinteractionpointeraChild = puserinteraction->m_puserinteractionpointeraChild;
//
//               if (pacmeuserinteractionaChildren)
//               {

                  pinteraction = puserinteraction->get_first_child_window();

                  return ::is_set(pinteraction);
//
//               }

            }

         }

      }

#endif

      //_synchronous_lock synchronouslock(m_pmutexFrame);

      //_synchronous_lock slChildren(::user::pointer < ::mutex >_children2());

      auto puserinteractionFrame = m_puserinteractionaFrame;

      return puserinteractionFrame->get_child(pinteraction);

   }


   void application::add_user_interaction(::user::interaction * puserinteraction)
   {

      auto psession = session();

      if (puserinteraction == psession->m_puserprimitiveHost)
      {

         return;

      }

      if (puserinteraction->is_system_message_window())
      {

         return;

      }

      if (puserinteraction == nullptr)
      {

         return;

      }

      _synchronous_lock synchronouslock(m_pmutexFrame); // recursive lock (on m_framea.add(puserinteraction)) but m_puiMain is "cared" by m_frame.m_pmutex

      if (m_puserinteractiona->add_unique_interaction(puserinteraction))
      {

         if (puserinteraction->is_frame_window())
         {

            m_puserinteractionaFrame->add_unique_interaction(puserinteraction);

         }

         information() << "::base::application::add_user_interaction ::user::interaction = 0x" << (::iptr) (puserinteraction) << " (" << typeid(*puserinteraction).name() << ") app=" << ::type(this).name();

         if (!(puserinteraction->m_ewindowflag & e_window_flag_satellite_window))
         {

            psession->on_create_frame_window();

         }

         if (m_pacmeuserinteractionMain == nullptr)
         {

            m_pacmeuserinteractionMain = puserinteraction;

         }

         if (psession->m_puserprimitiveHost)
         {

            ::pointer<::user::interaction>puserinteractionHost = psession->m_puserprimitiveHost;

            {

               _synchronous_lock synchronouslock(puserinteractionHost->synchronization());

               puserinteractionHost->m_pacmeuserinteractionaChildren->add_unique(puserinteraction);

            }

            puserinteractionHost->set_need_layout();

            puserinteraction->set_need_redraw();

            puserinteraction->post_redraw();

         }

      }

   }


   void application::erase_user_interaction(::user::interaction * puserinteraction)
   {

      _synchronous_lock synchronouslock(m_pmutexFrame); // recursive lock (on m_framea.erase(puserinteraction)) but m_puiMain is "cared" by m_frame.m_pmutex

      if (m_pacmeuserinteractionMain == puserinteraction)
      {

         m_pacmeuserinteractionMain.release();

      }

      if (m_puserinteractiona != nullptr)
      {

         if (m_puserinteractiona->erase_interaction(puserinteraction) > 0)
         {

            information() << "::base::application::erase_user_interaction ::user::interaction = 0x"<<(iptr)puserinteraction<<" ("<<typeid(*puserinteraction).name()<<") app=" << ::type(this).name();

         }

      }

      if (m_puserinteractionaFrame != nullptr)
      {

         auto oldInteractionCount = m_puserinteractionaFrame->interaction_count();

         if (m_puserinteractionaFrame->erase_interaction(puserinteraction) > 0)
         {

            information() << "::base::application::erase_frame ::user::interaction = 0x"<<(iptr)puserinteraction<<" ("<<typeid(*puserinteraction).name()<<") app=" <<::type(this).name();

         }

         if (oldInteractionCount > 0)
         {

            if (m_puserinteractionaFrame->has_no_interaction())
            {

               synchronouslock.unlock();

               get_app()->post_message(e_message_close);

            }

         }

      }

   }


   void application::send_message_to_windows(::enum_message emessage, ::wparam wparam, ::lparam lparam) // with tbs in <3
   {

      ::pointer<::user::interaction>puserinteraction;

      try
      {

         while (get_frame(puserinteraction))
         {

            try
            {

               if (puserinteraction && puserinteraction->is_window())
               {

                  try
                  {

                     puserinteraction->send_message(emessage, wparam, lparam);

                  }
                  catch (...)
                  {

                  }

                  try
                  {

                     puserinteraction->send_message_to_descendants(emessage, wparam, lparam);

                  }
                  catch (...)
                  {


                  }

               }

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {

      }

      //return true;

   }


   void application::route_message_to_windows(::message::message * pmessage) // with tbs in <3
   {

      ::pointer<::user::interaction>puserinteraction;

      try
      {

         while (get_frame(puserinteraction))
         {

            try
            {

               if (puserinteraction && puserinteraction->is_window())
               {

                  try
                  {

                     puserinteraction->route_message(pmessage);

                  }
                  catch (...)
                  {

                  }

                  try
                  {

                     puserinteraction->route_message_to_descendants(pmessage);

                  }
                  catch (...)
                  {


                  }

               }

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {


      }

      //return true;

   }


   /*void application::send_language_change_message()
   {

      ::message::message message(::message::type_language);

      route_message_to_windows(&message);

   }
*/

   ::user::interaction * application::main_window()
   {

      if (!m_pacmeuserinteractionMain)
      {

         return nullptr;

      }
      
      ::cast < ::user::interaction > puserinteraction = m_pacmeuserinteractionMain;
      
      if(!puserinteraction)
      {
       
         return nullptr;
         
      }

      return puserinteraction;

   }


   bool application::is_sandboxed()
   {

#ifdef UNIVERSAL_WINDOWS

      return true;

#endif

      auto pwindowing = system()->windowing();

      if (::is_null(pwindowing))
      {

         throw ::exception(::error_wrong_state);

      }

      return pwindowing->is_sandboxed();

   }


   //::pointer<::user::message>application::get_user_message(MESSAGE * pmsg)
   //{

   //   ::user::interaction_base * pinteraction = nullptr;

   //   ::windowing::window * pwindow = nullptr;

   //   if (pinteraction == nullptr && pmsg->oswindow != nullptr)
   //   {

   //     if (pmsg->id() == 126)
   //     {

   //        information() << "e_message_display_change";

   //     }

   //     

   //     auto puser = psession->m_puser;

   //     auto pwindowing = system()->windowing();

   //     pwindow = pwindowing->window(pmsg->oswindow);

   //     auto pwindow = pwindow->m_pwindow;

   //     if (pwindow != nullptr)
   //     {

   //        try
   //        {

   //           pinteraction = pwindow->m_puserinteraction;

   //        }
   //        catch (...)
   //        {

   //           pinteraction = nullptr;

   //        }

   //     }

   //     //if (pinteraction == nullptr)
   //     //{

   //     //   pinteraction = pwindow;

   //     //}

   //   }

   //   if (pinteraction != nullptr)
   //   {

   //      return pinteraction->get_message(pmsg->id(), pmsg->wParam, pmsg->lParam);

   //   }

   //   auto pusermessage = __allocate ::user::message();

   //   if (!pusermessage)
   //   {

   //      return nullptr;

   //   }

   //   pusermessage->set(pmsg->oswindow, pwindow, pmsg->id(), pmsg->wParam, pmsg->lParam);

   //   return pusermessage;

   //}


   string application::preferred_experience()
   {

      string strExperience;

      strExperience = payload("experience");

      if (strExperience.has_character())
      {

         return strExperience;

      }

      return "core";

   }

   //::user::document *application::place_hold(::user::interaction * pinteraction)
   //{

   //   return nullptr;

   //}


   void application::post_message(::enum_message emessage, ::wparam wparam, ::lparam lparam )
   {

      ::thread::post_message(emessage, wparam, lparam);

   }


   void application::initialize_context()
   {
      ::aura::context::initialize_context();
      ::aqua::application::initialize_context();
   }


   void application::initialize_context_1()
   {
      ::aura::context::initialize_context_1();
      ::aqua::application::initialize_context_1();


   }


   //::image::icon * application::set_icon(object * pparticle, ::image::icon * picon, bool bBigIcon)
   //{

   //   ::image::icon * piconOld = get_icon(pparticle, bBigIcon);

   //   if (bBigIcon)
   //   {

   //      pparticle->payload("big_icon") = (::pointer<object> picon;

   //   }
   //   else
   //   {

   //      pparticle->payload("small_icon") = (::pointer<object> picon;

   //   }

   //   return piconOld;

   //}


   //::image::icon * application::get_icon(object * pparticle, bool bBigIcon) const
   //{

   //   if (bBigIcon)
   //   {

   //      return ((object *)pparticle)->cast < ::image::icon >("big_icon");

   //   }
   //   else
   //   {

   //      return ((object *)pparticle)->cast <::image::icon>("small_icon");

   //   }

   //}


   //void application::on_message_app_exit(::message::message * pmessage)
   //{

   //   pmessage->m_bRet = true;

   //   _001CloseApplication();

   //}

//
//   bool application::is_equal_file_path(const ::file::path & path1Param, const ::file::path & path2Param)
//   {
//
//      ::file::path path1;
//
//      ::file::path path2;
//
//      path1 = defer_process_path(path1Param);
//
//      path2 = defer_process_path(path2Param);
//
//      path1 = node_full_file_path(path1);
//
//      path2 = node_full_file_path(path2);
//
//      return strcmp(path1, path2) == 0;
//
//   }
//
//
////   void application::on_event(unsigned long long u, ::particle * pparticle)
////   {
////
////      object_ptra ptra;
////
////      {
////
////         _synchronous_lock synchronouslock(this->synchronization());
////
////         ptra = m_particleaddressaEventHook;
////
////      }
////
////      for(auto & pparticle : ptra)
////      {
////
////         pparticle->on_event(u, pparticle);
////
////      }
////
////
////   }


   //::file::path application::appconfig_folder()
   //{

   //   return directory_system()->config() / m_strAppName;

   //}


   //::account::user * application::get_user(::file::path pathUrl, bool bFetch, bool bInteractive)
   //{

   //   if(::is_null(get_session()))
   //   {

   //      return nullptr;

   //   }

   //   return get_session()->get_user(pathUrl, bFetch, bInteractive);

   //}


   //::account::user * application::interactive_get_user(::file::path pathUrl)
   //{

   //   return get_user(pathUrl, true, true);

   //}


   //::account::user * application::noninteractive_get_user(::file::path pathUrl)
   //{

   //   return get_user(pathUrl, true, false);

   //}


   void application::on_initial_frame_position(::user::frame_interaction * pframe)
   {

      auto psystem = system();

      psystem->on_initial_frame_position(pframe);

   }


   void application::on_graphics_ready()
   {

   }


   //::pointer<::user::document>application::defer_create_impact(string strImpact, ::user::interaction * puiParent, e_window_flag ewindowflag, const ::atom & atom)
   //{

   //   //auto pcontroller = pmultimedia->defer_create_impact(strImpact, puiParent, ewindowflag, atom);

   //   //if (pcontroller)
   //   //{

   //   //   return pcontroller;

   //   //}

   //   return nullptr;

   //}

   //void application::process_message(::user::message * pusermessage)
   //{

   //   return ::thread::process_message(pusermessage);

   //}


//   ::account::user * application::interactive_get_user(::file::path pathUrl)
//   {
//
//      if(::is_null(get_session()))
//      {
//
//         return nullptr;
//
//      }
//
//      return get_session()->interactive_get_user();
//
//   }
//
//
//   ::account::user * application::noninteractive_get_user(::file::path pathUrl)
//   {
//
//      if(::is_null(get_session()))
//      {
//
//         return nullptr;
//
//      }
//
//      return get_session()->noninteractive_get_user();
//
//   }


   //::type application::user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype)
   //{

   //   return ::type < ::user::interaction >();

   //}


   //::atom application::translate_property_id(const ::atom & atom)
   //{
   //   return ::aqua::application::translate_property_id(atom);
   //   //if(!is_system())
   //   //{

   //     // if(!is_session())
   //      //{

   //        // return psession->translate_property_id(atom);

   //      //}
   //      //else
   //      //{

   //        // return psystem->translate_property_id(atom);

   //      //}

   //   //}

   //   return atom;

   //}


   //void application::record(::create * pcommand)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   get_command()->m_createa.add(pcommand);

   //}


   //bool application::on_start_application()
   //{

   //   string strAppId = m_XstrAppId;

   //   auto& file = psystem->file();

   //   string strNetworkPayload = file.as_string(directory_system()->config() / strAppId / +"http.network_payload");

   //   if (strNetworkPayload.has_character())
   //   {

   //      try
   //      {

   //         psystem->http()->m_setHttp.parse_network_payload(strNetworkPayload);

   //      }
   //      catch (...)
   //      {

   //      }

   //   }

   //   set_last_run_application_path(strAppId);

   //   if (!os_on_start_application())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


//   bool application::start_application(bool bSynch, ::request * prequest)
//   {
//
////      try
////      {
////
////         if (pbias != nullptr)
////         {
////
////            if (pbias->m_pcallback != nullptr)
////            {
////
////               pbias->m_pcallback->connect_to(this);
////
////            }
////
////         }
////      }
////      catch (...)
////      {
////      }
//
////      if (pbias != nullptr)
////      {
////
////         m_biasCalling = *pbias;
////
////      }
//
//      if (bSynch)
//      {
//
//         if (!m_htask)
//         {
//
//            if (!begin_synch())
//            {
//
//               return false;
//
//            }
//
//         }
//
//      }
//      else
//      {
//
//         begin();
//
//      }
//
//
//      return true;
//
//   }


   void application::HideApplication()
   {


      try
      {


         if (m_pacmeuserinteractionMain)
         {

            auto puserinteractionMain = m_pacmeuserinteractionMain;

            if (::is_null(puserinteractionMain))
            {

               puserinteractionMain->display(::e_display_hide);

               puserinteractionMain->set_need_redraw();

               puserinteractionMain->post_redraw();

            }

         }

      }
      catch (...)
      {

      }

   }


   //string application::load_string(const ::atom & atom)
   //{

   //   _synchronous_lock synchronouslock(m_pmutexStr);

   //   string str;

   //   if (m_stringmap.lookup(atom, str))
   //   {

   //      return str;

   //   }

   //   if (!load_string(str, atom))
   //   {

   //      atom.to_string(str);

   //      return str;

   //   }

   //   m_stringmap.set_at(atom, str);

   //   return str;

   //}


   //bool application::load_string(string & str, const ::atom & atom)
   //{

   //   if (!load_cached_string(str, atom, true))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool application::load_cached_string(string & str, const ::atom & atom, bool bLoadStringTable)
   //{


   //   //throw ::exception(todo("xml"));

   //   //auto pdocument = __allocate ::xml::document();

   //   //if (!pdocument->load(atom) || !*pdocument)
   //   //{

   //   //   return load_cached_string_by_id(str, atom, bLoadStringTable);

   //   //}

   //   //auto pnodeRoot = pdocument->root();

   //   //if (pnodeRoot->get_name() == "string")
   //   //{

   //   //   string strId = pnodeRoot->attribute("id");

   //   //   if (!load_cached_string_by_id(str, strId, bLoadStringTable))
   //   //   {

   //   //      str = pnodeRoot->get_value();

   //   //   }

   //   //   return true;

   //   //}

   //   return false;

   //}


   //bool application::load_cached_string_by_id(string & str, const ::atom & atom, bool bLoadStringTable)
   //{

   //   string strId(atom.str());

   //   string strTable;

   //   string strString;

   //   auto pFind = 0;

   //   if ((iFind = strId.find(':')) <= 0)
   //   {

   //      strTable = "";

   //      strString = strId;

   //   }
   //   else
   //   {

   //      strTable = strId(0, pFind);

   //      strString = strId(pFind + 1);

   //   }

   //   _synchronous_lock synchronouslock(m_pmutexStr);

   //   ::pointer<string_to_string>pmap;

   //   if (m_stringtableStd.lookup(strTable, pmap))
   //   {

   //      if (pmap != nullptr && pmap->lookup(strString, str))
   //      {

   //         return true;

   //      }

   //   }
   //   else if (m_stringtable.lookup(strTable, pmap))
   //   {

   //      if (pmap != nullptr && pmap->lookup(strString, str))
   //      {

   //         return true;

   //      }

   //   }
   //   else if (bLoadStringTable)
   //   {

   //      load_string_table(strTable, "");

   //      return load_cached_string_by_id(str, atom, false);

   //   }

   //   return false;

   //}


   //void application::load_string_table(const string & pszApp, const string & pszId)
   //{


   //}




   //void application::load_string_table()
   //{

   //   load_string_table("", "");

   //}


   //bool application::is_system() const
   //{

   //   return false;

   //}


   //bool application::is_session() const
   //{

   //   return false;

   //}


   //bool application::is_serviceable() const
   //{

   //   return false;

   //}


   //::simpledb::server * application::simpledb()
   //{

   //   return m_psimpledb;

   //}


   string application::get_window_class_name(::user::enum_control_type econtroltype)
   {

      return "";

   }


   ::database::server * application::dataserver()
   {

      //return simpledb();

      return nullptr;

   }


   // void application::verb()
   // {
   //
   //    //return true;
   //
   // }
   //

   //void application::SetCurrentHandles()
   //{

   //   ::aura::application::SetCurrentHandles();

   //}


   //void application::_001CloseApplication()
   //{

   //   close(::apex::e_end_app);

   //}


   //bool application::process_exception(const ::exception & e)
   //{

   //   return aura::application::process_exception(e);

   //}


   //void     application::main()
   //{

   //   return ::aura::application::main();

   //}


   //void application::on_run()
   //{

   //   //try
   //   //{

   //   //   ::aura::message::application signal(::aura::message::application_begin);

   //   //   route_message(&signal);

   //   //}
   //   //catch (...)
   //   //{

   //   //}

   //   thread * pthread = ::get_task();

   //   install_message_routing(pthread);

   //   m_bReady = true;

   //   try
   //   {

   //      string strType = ::type(this).name();

   //      //if(::is_set(system()))
   //      //{

   //      //   system()->add_reference(this);

   //      //}

   //      //if(::is_set(m_psession))
   //      //{

   //      //   m_psession->add_reference(this);

   //      //}

   //      if (::is_set(m_pappParent))
   //      {

   //         m_pappParent->add_reference(this);

   //      }

   //   resume_on_exception:

   //      try
   //      {

   //         m_estatus = run();

   //      }
   //      catch (const ::exception & e)
   //      {

   //         if (handle_exception(pe))
   //         {

   //            goto resume_on_exception;

   //         }

   //         m_estatus = pe->m_estatus;

   //      }

   //   }
   //   catch (const ::exception & e)
   //   {

   //   }


   //   try
   //   {

   //      thread * pthread = this;

   //      if (pthread != nullptr && pthread->m_pevReady != nullptr)
   //      {

   //         pthread->m_pevReady->set_happening();

   //      }

   //   }
   //   catch (...)
   //   {

   //      m_result.add(error_failed);

   //   }

   //   return m_estatus;

   //}


   //void application::init_application()
   //{

   //   return ::aura::application::init_application();

   //}


   //void application::application_pre_run()
   //{

   //   return ::aura::application::application_pre_run();

   //}



   //bool application::InitApplication()
   //{

   //   return true;

   //}


   //bool application::do_install()
   //{


   //   if (!::aura::application::do_install())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool application::do_uninstall()
   //{

   //   bool bOk = aura::application::do_uninstall();

   //   return bOk;

   //}


   //bool application::on_install()
   //{

   //   if (!aura::application::on_install())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool application::on_uninstall()
   //{

   //   if (!aura::application::on_uninstall())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //void application::os_native_bergedge_start()
   //{

   //   if (!::aura::application::os_native_bergedge_start())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //void application::on_request(::request * prequest)
   //{

   //   aura::application::on_request(pcreate);

   //}


   //void     application::run()
   //{

   //   return ::aura::application::run();

   //}


   //::pointer<::aura::application>application::assert_running(const ::string & pszAppId)
   //{

   //   ::pointer<::aura::application>papp;

   //   papp = psession->m_applicationa.find_running_defer_try_quit_damaged(pszAppId);

   //   if(papp.is_null())
   //   {

   //      ::pointer<::create>spcreate(e_create);

   //      papp = psession->start_application(pszAppId,spcreate);

   //   }

   //   return papp;

   //}




   void application::init()
   {

      //auto estatus = 
      
      ::aqua::application::init();

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return true;

   }


   void application::term()
   {

      aqua::application::term();

   }


   //bool application::is_running()
   //{

   //   return is_alive();

   //}


   //bool application::Ex2OnAppInstall()
   //{
   //   return true;
   //}


   //bool application::Ex2OnAppUninstall()
   //{

   //   return true;

   //}


   void application::update_appmatter( ::pointer<::sockets::http_session>& psession, const ::file::path & pszRoot, const string & pszRelative)
   {

      auto plocaleschema = __create_new < ::text::international::locale_schema >();

      //psession->fill_locale_schema(localeschema);

      bool bIgnoreStdStd = string(pszRoot) == "app" && (string(pszRelative) == "main" || string(pszRelative) == "bergedge");

      //update_appmatter(h, psession, pszRoot, pszRelative, plocaleschema->m_atomLocale, plocaleschema->m_atomSchema);

      ::collection::count iCount = plocaleschema->m_straLocale.get_count();

      for (::collection::index i = 0; i < iCount; i++)
      {

         if (plocaleschema->m_straLocale[i] == "std" && plocaleschema->m_straSchema[i] == "std" && bIgnoreStdStd)
            continue;

         string strLocale;

         strLocale = plocaleschema->m_straLocale[i];

         string strSchema;

         strSchema = plocaleschema->m_straSchema[i];

         update_appmatter(psession, pszRoot, pszRelative, strLocale, strSchema);

         auto psystem = system();

         psystem->install_progress_add_up();

      }


      //return true;

   }


   void application::update_appmatter(::pointer<::sockets::http_session>& psession, const ::file::path & pszRoot, const string & pszRelative, const string & pszLocale, const string & pszStyle)
   {

      string strLocale;
      
      string strSchema;

      informationf("update_appmatter(root=%s, relative=%s, locale=%s, style=%s)", pszRoot.c_str(), pszRelative.c_str(), pszLocale.c_str(), pszStyle.c_str());
      
      ::file::path strRelative = ::file::path(pszRoot) / "_matter" / pszRelative / get_locale_schema_dir(pszLocale, pszStyle) + ".zip";

      // auto pcontext = get_context();

      ::file::path strFile = directory()->install() / strRelative;

      ::string strUrl1;

      if (node()->is_debug_build())
      {
         strUrl1 = "http://basis-ca2.network/api/spaignition/download?authnone&configuration=basis&stage=";
      }
      else
      {
         strUrl1 = "http://stage-ca2.network/api/spaignition/download?authnone&configuration=stage&stage=";
      }

      strUrl1 += ::url::encode(strRelative);

      ::url::url url(strUrl1);

      ::cast <::http::context > phttpcontext = http();

      if (psession == nullptr)
      {

         while (true)
         {

            ::property_set setEmpty;

            if (phttpcontext->open(psession, url.connect(), setEmpty, nullptr))
            {

               break;

            }

            sleep(200_ms);

         }

      }

      ::property_set set;

      set["get_memory"] = "";

      //::cast < ::http::context > phttpcontext = http();

      phttpcontext->request(psession, url.request(), set);

      //if (!http()->request(psession, strUrl, set))
      //{

      //   return false;

      //}

      ::memory_file file;

      if (set["get_memory"].cast < memory >() != nullptr && set["get_memory"].cast < memory >()->size() > 0)
      {

//         zip_context zip(this);

         auto pfolder = ::particle::file()->get_folder(&file, "zip", ::file::e_open_read);

         string strDir = strFile;

         strDir.case_insensitive_ends_eat(".zip");

         //try
         //{

            pfolder->e_extract_all(strDir);

         //}
         //catch (...)
         //{

         //   // spa app_app_admin.exe would recover by retrying or someone would fix the resource packaging problem and then zip extraction at least should work.

         //   return false;

         //}

         //psystem->compress().e_extract_all(strFile, this);

      }

      //return true;

   }





   bool application::assert_user_logged_in()
   {

      //const ::scoped_string & scopedstrRequestUrl = nullptr;

      string strRequestUrl;

      if (file_system()->as_string(directory_system()->userconfig() / "config\\system\\ignition_server.txt").has_character())
      {

         strRequestUrl = "https://" + file_system()->as_string(directory_system()->userconfig() / "config\\system\\ignition_server.txt") + "/api/spaignition";

         //pszRequestUrl = strRequestUrl;

      }

      if (!session())
      {

         return false;

      }

      //if (get_session()->account() == nullptr)
      //{

      //   return false;

      //}

      //if (interactive_get_user() == nullptr)
      //{

      //   return false;

      //}

      return true;

   }




   string application::matter_as_string(const ::string & pszMatter, const ::string & pszMatter2)
   {

      ::payload payloadFile;

      payloadFile["disable_ca2_sessid"] = true;

      // auto pcontext = get_context();

      string strMatter = directory()->matter(::file::path(pszMatter) / pszMatter2);

      payloadFile["url"] = strMatter;

      return file()->as_string(payloadFile);

   }

   //string application::directory()->matter(const ::string & pszMatter, const ::string & pszMatter2)
   //{

   //   return directory()->matter(pszMatter,pszMatter2);

   //}

   //bool application::is_inside_time_dir(const ::string & pszPath)
   //{
   //   return directory()->is_inside_time(pszPath);
   //}


   //bool application::file_is_read_only(const ::string & pszPath)
   //{

   //   return false;
   //   //return file()->is_read_only(pszPath);

   //}



   //void application::process_message_filter(int code, ::message::message * pmessage)
   //{

   //   //::pointer<::user::message>pusermessage(pmessage);

   //   __UNREFERENCED_PARAMETER(code);

   //   __UNREFERENCED_PARAMETER(pmessage);


   //}







   void application::DoWaitCursor(int nCode)
   {

      if (nCode < 0)
      {

         m_iWaitCursorCount = 0;

         auto psystem = system();

         auto pnode = psystem->node();

         pnode->show_wait_cursor(false);

      }
      else if (nCode == 0)
      {

         if (m_iWaitCursorCount > 0)
         {
            m_iWaitCursorCount--;
         }

         if (m_iWaitCursorCount > 0)
         {

            auto psystem = system();

            auto pnode = psystem->node();

            pnode->show_wait_cursor(true);

         }

         m_iWaitCursorCount = 0;

         auto psystem = system();

         auto pnode = psystem->node();

         pnode->show_wait_cursor(false);

      }
      else
      {

         if (m_iWaitCursorCount < 0)
         {
            m_iWaitCursorCount = 0;
         }

         m_iWaitCursorCount++;

         auto psystem = system();

         auto pnode = psystem->node();

         pnode->show_wait_cursor(true);

      }

   }


   //void application::show_wait_cursor(bool bShow)
   //{

   //}



   //void application::TermThread(HINSTANCE hInstTerm)
   //{

   //   throw ::interface_only();

   //}




   //string application::get_version()
   //{

   //   throw ::interface_only();

   //   return "";

   //}




//   void application::set_env_var(const string & payload,const string & value)
//   {
//
//      throw ::interface_only();
//
//   }



   ::draw2d::printer * application::get_printer(const ::string & pszDeviceName)
   {

      throw ::interface_only();

      return nullptr;

   }


   //void application::userfs_init1()
   //{

   //   return error_not_implemented;

   //}

   //void application::userfs_process_init()
   //{

   //   return error_not_implemented;

   //}


   string application::dialog_box(const ::string & pszMatter, ::property_set& propertyset)
   {

      throw ::exception(todo, "core and os");

      return"";

   }

   //bool application::do_prompt_file_name(::payload & payloadFile, string nIDSTitle, unsigned int lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument)
   //{

   //   __UNREFERENCED_PARAMETER(payloadFile);
   //   __UNREFERENCED_PARAMETER(nIDSTitle);

   //   return false;

   //}






   //bool application::get_temp_file_name_template(string & strRet, const ::string & lpszName, const ::string & pszExtension, const ::string & pszTemplate)
   //{

   //   throw ::not_implemented();

   //   return false;

   //}


   //bool application::get_temp_file_name(string & strRet, const ::string & lpszName, const ::string & pszExtension)
   //{

   //   return get_temp_file_name_template(strRet,lpszName,pszExtension,nullptr);

   //}








   //::image::icon * application::set_icon(object * pparticle, ::image::icon * picon, bool bBigIcon)
   //{

   //   return nullptr;

   //}


   //::image::icon * application::get_icon(object * pparticle, bool bBigIcon) const
   //{

   //   return nullptr;

   //}


   //void application::on_service_request(::request * prequest)
   //{

   //   ::aura::application::on_service_request(pcreate);

   //}


   string application::get_mutex_name_gen()
   {
      
      return ::aqua::application::get_mutex_name_gen();

   }


   string application::get_license_id()
   {

      if (m_strLicense.has_character())
         return m_strLicense;

      if (m_strInstallToken.has_character())
         return m_strInstallToken;

      return m_strAppId;

   }






   //bool application::assert_user_logged_in()
   //{

   //   return axis::application::assert_user_logged_in();

   //}


//
//
//
//   int application::hotplugin_host_starter_start_sync(const ::string & pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin)
//   {
//
//      {
//
//         ::installpointer< class ::pointer < ::mutex > > ::pointer < ::mutex >(process_platform_name());
//
//         if (::pointer < ::mutex >.already_exists())
//         {
//
//            //            output_error_message("Could not launch spa installer. It is already running.", e_message_box_ok);
//
//            return -35;
//
//         }
//
//      }
//
//      string strValue;
//
//      if (get_command_line_parameter(strValue, pszCommandLine, "enable_desktop_launch"))
//      {
//
//#ifdef UNIVERSAL_WINDOWS
//
//         return -1;
//
//#else
//
//         ::property_set set;
//
//         return ::call_sync(::path::app_app(process_platform_name(), process_configuration_name()), pszCommandLine, ::path::app_app(process_platform_name(), process_configuration_name()), e_display_normal, 2_min, set);
//
//#endif
//
//      }
//      else
//      {
//
//         return hotplugin_host_host_starter_start_sync(pszCommandLine, get_app(), nullptr);
//
//      }
//
//   }
//
//   int application::hotplugin_host_host_starter_start_sync(const ::string & pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin)
//   {
//
//      return -1;
//
//   }
//
//

   //void application::handle(::topic * ptopic, ::handler_context * phandlercontext)
   //{

   //}


   //bool application::on_open_document(::user::document * pdocument, ::payload payloadFile)
   //{

   //   __UNREFERENCED_PARAMETER(pdocument);
   //   __UNREFERENCED_PARAMETER(payloadFile);
   //   return true;

   //}


   //bool application::on_save_document(::user::document * pdocument, ::payload payloadFile)
   //{

   //   __UNREFERENCED_PARAMETER(pdocument);
   //   __UNREFERENCED_PARAMETER(payloadFile);
   //   return true;

   //}


   //void application::on_update_impact(::user::impact * pimpact, ::user::impact * pviewSender, lparam lHint, object * pHint)
   //{


   //}

   //void application::handle(::topic * ptopic, ::handler_context * phandlercontext)
   //{

   //}


   //void application::on_notify_control_event(::user::control_event* phappening)
   //{


   //}


   //void application::route(::topic * ptopic, ::handler_context * phandlercontext)
   //{

   //   handle(ptopic);

   //   if (ptopic->m_bRet)
   //   {

   //      return;

   //   }

   //   on_notify_control_event(phappening);

   //   if (ptopic->m_bRet)
   //   {

   //      return;

   //   }

   //}



   //   void     application::interactive_credentials(::account::credentials * pcredentials)
   //   {
   //
   //      return ::aura::applciation::interactive_credentials(pcredentials);
   //
   //   }
   //
   //
   //   string application::interactive_get_credentials(string & strUsername, string & strPassword, string strToken)
   //   {
   //
   //      return ::account::get_cred(this, strUsername, strPassword, strToken);
   //
   //   }
   //
   //   void application::set_cred(string strToken, const ::string & pszUsername, const ::string & pszPassword)
   //   {
   //
   //      ::account::set_cred(this,strToken, pszUsername, pszPassword);
   //
   //   }
   //
   //   void application::set_cred_ok(string strToken, bool bOk)
   //   {
   //
   //      ::account::set_cred_ok(this, strToken, bOk);
   //
   //   }

      //::html::html * application::create_html()
      //{

      //   return __allocate< ::html::html(get_app >());

      //}


      //string application::http_get(const ::string & strUrl, ::property_set & set)
      //{

      //   return http()->get(strUrl, set);

      //}

      //bool application::app_data_set(::const ::atom & atom, stream & stream)
      //{

      //   return data_save(atom, stream);

      //}


      //bool application::app_data_get(::const ::atom & atom, stream & stream)
      //{

      //   return datastream()->get(atom, stream);

      //}


      //bool application::app_data_set(::const ::atom & atom, ::object & obj)
      //{

      //   return datastream()->set(atom, obj);

      //}


      //bool application::app_data_get(::const ::atom & atom, ::object & obj)
      //{

      //   return datastream()->get(atom, obj);

      //}


      //bool application::compress_ungz(const ::stream & os, const ::stream & is)
      //{

      //   return psystem->compress().ungz(this, os, is);


      //}


      //bool application::compress_ungz(memory_base & mem)
      //{

      //   return psystem->compress().ungz(this, mem);

      //}


      //bool application::compress_gz(const ::stream & os, const ::stream & is, int iLevel)

      //{

      //   return psystem->compress().gz(this, os, is, iLevel);


      //}


      //bool application::compress_gz(const ::stream & os, const ::stream & is, int iLevel)
      //{

      //   return psystem->compress().gz(this, os, is, iLevel);

      //}


   //bool application::is_local_data()
   //{

   //   return m_strDataKey.m_bLocalData;

   //}





} // namespace aura



namespace aura
{
   //const char application::gen_FileSection[] = "Recent File List";
   //const char application::gen_FileEntry[] = "File%d";
   //const char application::gen_ThumbnailSection[] = "Settings";
   //const char application::gen_ThumbnailEntry[] = "ThumbnailPages";



   // application::application()
   //{

   //   add_factory_item < ::user::user >();
   //   add_factory_item < ::userfs::userfs >();

   //   m_pmainpane = nullptr;

   //   m_ppaneimpactMain = nullptr;

   //   // almost always forgotten, assumed, as exception, responsability of application to add first ref on constructor.
   //   //::increment_reference_count(this);

   //   srand((unsigned int) ::get_tick());

   //   m_bService = false;

   //   m_iResourceId = 8001;

   //   ::aura::profiler::initialize();

   //   m_pdocmanager = nullptr;

   //   m_eexclusiveinstance = e_exclusive_instance_none;
   //   m_strLocale = "_std";
   //   m_strSchema = "_std";

   //   m_iGcomBackgroundUpdateMillis = -1;

   //}


   //application::~application()
   //{

   //}


   //void application::initialize(::particle * pparticle)
   //{

   //   auto estatus = ::aura::application::initialize(pparticle);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

   //}


   bool application::on_command_final(const ::atom & atom, ::user::activation_token * puseractivationtoken)
   {

      //if (m_pacmeuserinteractionMain != nullptr)
      //{

      //   ::message::command command(atom);

      //   auto puserinteractionMain = m_pacmeuserinteractionMain;

      //   puserinteractionMain->route_command(&command);

      //   if(command.m_bRet)
      //   {

      //      return true;

      //   }

      //}

      return ::aqua::application::on_command_final(atom, puseractivationtoken);

   }


   //::aura::application * application::get_app() const
   //{

   //   return (application *) this;

   //}








   //bool application::is_system() const
   //{

   //   return false;

   //}


   //bool application::is_session() const
   //{

   //   return false;

   //}


   //unsigned int application::guess_code_page(const string& str)
   //{

   //   return 0;

   //}


   //lresult application::GetPaintMsgProc(int nCode, wparam wParam, lparam lParam)
   //{

   //   __UNREFERENCED_PARAMETER(nCode);
   //   __UNREFERENCED_PARAMETER(wParam);
   //   __UNREFERENCED_PARAMETER(lParam);

   //   return 0;

   //}


   bool application::CreateFileFromRawResource(unsigned int nID, const ::string & pcszType, const ::string & pcszFilePath)
   {

      __UNREFERENCED_PARAMETER(nID);
      __UNREFERENCED_PARAMETER(pcszType);
      __UNREFERENCED_PARAMETER(pcszFilePath);

      return false;

   }


   //#ifdef WINDOWS
   //
   //
   //   bool application::OnMessageWindowMessage(MESSAGE * pmsg)
   //   {
   //
   //      __UNREFERENCED_PARAMETER(pmsg);
   //
   //
   //      return false;
   //
   //   }
   //
   //#elif defined(LINUX)
   //
   //   bool application::OnX11WindowMessage(void* pXevent) // XEvent *
   //   {
   //
   //      __UNREFERENCED_PARAMETER(pXevent);
   //
   //      return false;
   //
   //   }
   //
   //#endif

   void application::OnUpdateRecentFileMenu(::message::command* pcommand)
   {

      __UNREFERENCED_PARAMETER(pcommand);

   }


   //bool application::GetResourceData(unsigned int nID, const ::string & pcszType, memory& storage)

   //{

   //   __UNREFERENCED_PARAMETER(nID);
   //   __UNREFERENCED_PARAMETER(pcszType);

   //   __UNREFERENCED_PARAMETER(storage);

   //   return false;

   //}


   //#ifdef WINDOWS_DESKTOP
   //
   //   HENHMETAFILE application::LoadEnhMetaFile(unsigned int uResource)
   //   {
   //
   //      memory storage;
   //
   //      if (!GetResourceData(uResource, "EnhMetaFile", storage))
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      return SetEnhMetaFileBits((unsigned int)storage.get_size(), storage.get_data());
   //
   //   }
   //
   //#endif

   //   /////////////////////////////////////////////////////////////////////////////
   //   // WinApp UI related functions
   //
   //   void application::EnableModelessEx(bool bEnable)
   //   {
   //      __UNREFERENCED_PARAMETER(bEnable);
   //#ifdef ___NO_OLE_SUPPORT
   //      UNUSED(bEnable);
   //#endif
   //
   //
   //   }



   /* void     application::run()
    {

       return ::aura::application::run();

    }*/


   bool application::on_idle(int lCount)
   {

      return false;

   }


   void application::process_window_procedure_exception(const ::exception & e, ::message::message* pmessage)
   {

      ENSURE_ARG(pmessage != nullptr);

      ::pointer<::user::message>pusermessage(pmessage);

      // handle certain messages in thread

      switch (pusermessage->m_emessage)
      {
         case e_message_create:
         case e_message_paint:

            return thread::process_window_procedure_exception(e, pmessage);

         default:
            break;

      }

      // handle all the rest
      //linux unsigned int nIDP = __IDP_INTERNAL_FAILURE;   // matter message string
      const char* nIDP = "Internal Failure";
      pusermessage->m_lresult = 0;        // sensible default
      if (pusermessage->m_emessage == e_message_command)
      {
         if (pusermessage->m_lparam == 0)
            //linux nIDP = __IDP_COMMAND_FAILURE; // command (not from a control)
               nIDP = "Command Failure";
         pusermessage->m_lresult = (lresult)true;        // pretend the command was handled
      }

      if (e.estatus() == error_no_memory)
      {

         report_error(e, e_message_box_icon_exclamation | e_message_box_system_modal, nIDP);

      }
      else if (e.estatus() == error_user)
      {

         // ::account::user has not been alerted yet of this catastrophic problem

         report_error(e, e_message_box_icon_stop, nIDP);

      }

   }


   void application::route_command(::message::command* pcommand, bool bRouteToKeyDescendant)
   {

      ::channel::route_command(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

      ::cast < ::channel > pchannel = m_psession;

      if (pchannel)
      {

         pchannel->route_command(pcommand, false);

      }

   }


   /*
   bool application::hex_to_memory(memory & memory, const ::string & pszHex)
   {
   ::collection::count len = strlen(pszHex);
   ::collection::count count = (len + 1) / 2;
   memory.set_size(count);
   ::collection::index i = 0;
   unsigned char b;
   while(*pszHex != '\0')
   {
   char ch = (char) tolower(*pszHex);
   if(ch >= '0' && ch <= '9')
   {
   b = ch - '0';
   }
   else if(ch >= 'a' && ch <= 'f')
   {
   b = ch - 'a' + 10;
   }
   else
   {
   return false;
   }
   pszHex++;
   if(*pszHex == '\0')
   {
   memory.get_data()[i] = b;
   return true;
   }
   b = b << 4;
   ch = (char) tolower(*pszHex);
   if(ch >= '0' && ch <= '9')
   {
   b |= (ch - '0');
   }
   else if(ch >= 'a' && ch <= 'f')
   {
   b |= (ch - 'a' + 10);
   }
   else
   {
   return false;
   }
   pszHex++;
   memory.get_data()[i] = b;
   i++;
   }
   return true;
   }


   void application::memory_to_hex(string & strHex, memory & memory)
   {
   ::collection::count count = memory.get_size();
   char * psz = strHex.get_buffer(count * 2);

   for(::collection::index i = 0; i < count; i++)
   {
   *psz++ = ::hex::lower_from((unsigned char) ((memory.get_data()[i] >> 4) & 0xf));

   *psz++ = ::hex::lower_from((unsigned char) (memory.get_data()[i] & 0xf));

   }
   strHex.ReleaseBuffer(count * 2);
   }
   */











   // //
   //{{__MSG_MAP(application)
   // Global File commands
   //   ON_COMMAND(ID_APP_EXIT, &application::OnAppExit)
   // MRU - most recently used file menu
   //   ON_UPDATE_::message::command(ID_FILE_MRU_FILE1, &application::OnUpdateRecentFileMenu)
   //   ON_COMMAND_EX_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE16, &application::OnOpenRecentFile)
   //}}__MSG_MAP
   // //

   /*#ifdef WINDOWS


   typedef LANGID (WINAPI*PFNGETUSERDEFAULTUILANGUAGE)();
   typedef LANGID (WINAPI*PFNGETSYSTEMDEFAULTUILANGUAGE)();


   class CActivationContext
   {
   protected :
   HANDLE m_hCtxt;
   uptr m_uCookie;

   // If pointers are nullptr then we are on a platform that does not support WinSXS.
   typedef HANDLE (WINAPI * PFNCreateActCtx)(PCACTCTX);
   static PFNCreateActCtx s_pfnCreateActCtx;

   typedef void (WINAPI * PFNReleaseActCtx)(HANDLE);
   static PFNReleaseActCtx s_pfnReleaseActCtx;

   typedef bool (WINAPI * PFNActivateActCtx)(HANDLE, uptr*);
   static PFNActivateActCtx s_pfnActivateActCtx;

   typedef bool (WINAPI * PFNDeactivateActCtx)(unsigned int, uptr);
   static PFNDeactivateActCtx s_pfnDeactivateActCtx;

   static bool s_bPFNInitialized;

   public:
   CActivationContext(HANDLE hCtxt = INVALID_HANDLE_VALUE) : m_hCtxt( hCtxt ), m_uCookie( 0 )
   {
   // Multiple threads initializing is fine since they will initialize the pointers to the
   // same value.
   if (!s_bPFNInitialized)
   {
   HMODULE hKernel = GetModuleHandle("KERNEL32");
   ENSURE (hKernel != nullptr);
   #ifdef _UNICODE
   s_pfnCreateActCtx = (PFNCreateActCtx) GetProcAddress(hKernel, "CreateActCtxW");
   #else
   s_pfnCreateActCtx = (PFNCreateActCtx) GetProcAddress(hKernel, "CreateActCtxA");
   #endif
   s_pfnReleaseActCtx = (PFNReleaseActCtx) GetProcAddress(hKernel, "ReleaseActCtx");
   s_pfnActivateActCtx = (PFNActivateActCtx) GetProcAddress(hKernel, "ActivateActCtx");
   s_pfnDeactivateActCtx = (PFNDeactivateActCtx) GetProcAddress(hKernel, "DeactivateActCtx");
   if (s_pfnCreateActCtx != nullptr)
   {
   // If one of the functions is present then all the functions have to be present.
   ENSURE( s_pfnReleaseActCtx != nullptr &&
   s_pfnActivateActCtx != nullptr &&
   s_pfnDeactivateActCtx != nullptr);
   }
   else
   {
   // If one of the functions is not present then all the functions should not be present.
   ENSURE( s_pfnReleaseActCtx == nullptr &&
   s_pfnActivateActCtx == nullptr &&
   s_pfnDeactivateActCtx == nullptr);
   }
   s_bPFNInitialized = true;
   }
   };

   ~CActivationContext()
   {
   Release();
   }

   bool create( PCACTCTX pactctx )
   {
   // nullptr on a platform that do not support WinSXS
   if (s_pfnCreateActCtx == nullptr)
   {
   return true;
   }

   ASSERT( pactctx != nullptr );
   if ( pactctx == nullptr )
   {
   return false;
   }

   ASSERT( m_hCtxt == INVALID_HANDLE_VALUE );
   if ( m_hCtxt != INVALID_HANDLE_VALUE )
   {
   return false;
   }

   return ( ( m_hCtxt = s_pfnCreateActCtx( pactctx ) ) != INVALID_HANDLE_VALUE );
   }

   void Release()
   {
   // nullptr on a platform that do not support WinSXS
   if (s_pfnReleaseActCtx == nullptr)
   {
   return;
   }

   if ( m_hCtxt != INVALID_HANDLE_VALUE )
   {
   Deactivate();
   s_pfnReleaseActCtx( m_hCtxt );
   }
   }

   bool Activate()
   {
   // nullptr on a platform that do not support WinSXS
   if (s_pfnActivateActCtx == nullptr)
   {
   return true;
   }

   ASSERT( m_hCtxt != INVALID_HANDLE_VALUE );
   if ( m_hCtxt == INVALID_HANDLE_VALUE )
   {
   return false;
   }

   ASSERT( m_uCookie == 0 );
   if ( m_uCookie != 0 )
   {
   return false;
   }

   return ( s_pfnActivateActCtx( m_hCtxt, &m_uCookie) == true );
   }

   bool Deactivate()
   {
   // nullptr on a platform that do not support WinSXS
   if (s_pfnDeactivateActCtx == nullptr)
   {
   return true;
   }

   if ( m_uCookie != 0 )
   {
   uptr uCookie = m_uCookie;
   m_uCookie = 0;
   return ( s_pfnDeactivateActCtx(0, uCookie) == true );
   }
   return true;
   }
   };


   CActivationContext::PFNCreateActCtx CActivationContext::s_pfnCreateActCtx = nullptr;
   CActivationContext::PFNReleaseActCtx CActivationContext::s_pfnReleaseActCtx = nullptr;
   CActivationContext::PFNActivateActCtx CActivationContext::s_pfnActivateActCtx = nullptr;
   CActivationContext::PFNDeactivateActCtx CActivationContext::s_pfnDeactivateActCtx = nullptr;
   bool CActivationContext::s_bPFNInitialized = false;


   // HINSTANCE of the module
   extern "C" IMAGE_DOS_HEADER __ImageBase;

   */


   /*bool application::LoadSysPolicies()
   {
      return _LoadSysPolicies();
   }*/

   //   // This function is not exception safe - will leak a registry key if exceptions are thrown from some places
   //   // To reduce risk of leaks, I've declared the whole function noexcept. This despite the fact that its callers have
   //   // no dependency on non-throwing.
   //   bool application::_LoadSysPolicies() noexcept
   //   {
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //      HKEY hkPolicy = nullptr;
   //      unsigned int dwValue = 0;
   //      unsigned int dwDataLen = sizeof(dwValue);
   //      unsigned int dwType = 0;
   //
   //      //// clear current policy settings.
   //      //m_dwPolicies = ___SYSPOLICY_NOTINITIALIZED;
   //
   //      //static __system_policy_data rgExplorerData[] =
   //      //{
   //      //   {"NoRun",___SYSPOLICY_NORUN},
   //      //   {"NoDrives",___SYSPOLICY_NODRIVES},
   //      //   {"RestrictRun",___SYSPOLICY_RESTRICTRUN},
   //      //   {"NoNetConnectDisconnect",___SYSPOLICY_NONETCONNECTDISCONNECTD},
   //      //   {"NoRecentDocsHistory",___SYSPOLICY_NORECENTDOCHISTORY},
   //      //   {"NoClose",___SYSPOLICY_NOCLOSE},
   //      //   {nullptr,0}
   //      //};
   //
   //      //static __system_policy_data rgNetworkData[] =
   //      //{
   //      //   {"NoEntireNetwork",___SYSPOLICY_NOENTIRENETWORK},
   //      //   {nullptr,0}
   //      //};
   //
   //      //static __system_policy_data rgComDlgData[] =
   //      //{
   //      //   {"NoPlacesBar",___SYSPOLICY_NOPLACESBAR},
   //      //   {"NoBackButton",___SYSPOLICY_NOBACKBUTTON},
   //      //   {"NoFileMru",___SYSPOLICY_NOFILEMRU},
   //      //   {nullptr,0}
   //      //};
   //
   //      //static __system_policies rgPolicies[] =
   //      //{
   //      //   {  "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",
   //      //      rgExplorerData
   //      //   },
   //      //   {  "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",
   //      //      rgNetworkData
   //      //   },
   //      //   {  "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Comdlg32",
   //      //      rgComDlgData
   //      //   },
   //      //   {nullptr,0}
   //      //};
   //
   //      //__system_policies *pPolicies = rgPolicies;
   //      //__system_policy_data *pData = nullptr;
   //
   //      //while (pPolicies->szPolicyKey != nullptr)
   //      //{
   //
   //      //   if (ERROR_SUCCESS == ::RegOpenKeyEx(
   //      //            HKEY_CURRENT_USER,
   //      //            pPolicies->szPolicyKey,
   //      //            0,
   //      //            KEY_QUERY_VALUE,
   //      //            &hkPolicy
   //      //         ))
   //      //   {
   //      //      pData = pPolicies->pData;
   //      //      while (pData->szPolicyName)
   //      //      {
   //      //         if (ERROR_SUCCESS == ::RegQueryValueEx(
   //      //                  hkPolicy,
   //      //                  pData->szPolicyName,
   //      //                  nullptr,
   //      //                  &dwType,
   //      //                  (unsigned char*)&dwValue,
   //      //                  &dwDataLen))
   //      //         {
   //      //            if (dwType == REG_DWORD)
   //      //            {
   //      //               if (dwValue != 0)
   //      //                  m_dwPolicies |= pData->dwID;
   //      //               else
   //      //                  m_dwPolicies &= ~pData->dwID;
   //      //            }
   //      //         }
   //      //         dwValue = 0;
   //      //         dwDataLen = sizeof(dwValue);
   //      //         dwType = 0;
   //      //         pData++;
   //      //      }
   //      //      ::RegCloseKey(hkPolicy);
   //      //      hkPolicy = nullptr;
   //      //   }
   //      //   pPolicies++;
   //      //};
   //
   //#endif
   //
   //      return true;
   //
   //
   //   }
   //
   //   bool application::GetSysPolicyValue(unsigned int dwPolicyID, bool* pbValue)
   //   {
   //      if (!pbValue)
   //         return false; // bad pointer
   //      *pbValue = (m_dwPolicies & dwPolicyID) != 0;
   //      return true;
   //   }

   //bool application::InitApplication()
   //{


   //   LoadSysPolicies();

   //   return true;


   //}



   /*   void application::LoadStdProfileSettings(unsigned int nMaxMRU)
   {
   __UNREFERENCED_PARAMETER(nMaxMRU);
   ASSERT_VALID(this);

   // 0 by default means not set
   m_nNumThumbnailPages = GetProfileInt(gen_ThumbnailSection, gen_ThumbnailEntry, 0);
   }*/

   /*void application::ParseCommandLine(CCommandLineInfo& rCmdInfo)
   {
   for (int i = 1; i < __argc; i++)
   {
   const ::scoped_string & scopedstrParam = __targv[i];
   bool bFlag = false;
   bool bLast = ((i + 1) == __argc);
   if (pszParam[0] == '-' || pszParam[0] == '/')
   {
   // erase flag specifier
   bFlag = true;
   ++pszParam;
   }
   rCmdInfo.ParseParam(pszParam, bFlag, bLast);
   }
   }*/

   /////////////////////////////////////////////////////////////////////////////
   // CCommandLineInfo implementation

   /*CCommandLineInfo::CCommandLineInfo()
   {
   m_bShowSplash = true;
   m_bRunEmbedded = false;
   m_bRunAutomated = false;
   m_nShellCommand = FileNew;
   }

   CCommandLineInfo::~CCommandLineInfo()
   {
   }

   void CCommandLineInfo::ParseParam(const ::string & pszParam,bool bFlag,bool bLast)
   {
   if (bFlag)
   {
   const astring strParam(pszParam);
   ParseParamFlag(strParam.GetString());
   }
   else
   ParseParamNotFlag(pszParam);

   ParseLast(bLast);
   }*/

   /*
   #ifdef UNICODE
   void CCommandLineInfo::ParseParam(const ::string & pszParam, bool bFlag, bool bLast)
   {
   if (bFlag)
   ParseParamFlag(pszParam);
   else
   ParseParamNotFlag(pszParam);

   ParseLast(bLast);
   }
   #endif // UNICODE
   */

   /*
   void CCommandLineInfo::ParseParamFlag(const ::string & pszParam)
   {
   // OLE command switches are case insensitive, while
   // shell command switches are case sensitive

   if (lstrcmpA(pszParam, "int_point") == 0)
   m_nShellCommand = FilePrintTo;
   else if (lstrcmpA(pszParam, "int_point") == 0)
   m_nShellCommand = FilePrint;
   else if (::__invariant_stricmp(pszParam, "Register") == 0 ||
   ::__invariant_stricmp(pszParam, "Regserver") == 0)
   m_nShellCommand = AppRegister;
   else if (::__invariant_stricmp(pszParam, "Unregister") == 0 ||
   ::__invariant_stricmp(pszParam, "Unregserver") == 0)
   m_nShellCommand = AppUnregister;
   else if (lstrcmpA(pszParam, "dde") == 0)
   {
   m_nShellCommand = FileDDE;
   }
   else if (::__invariant_stricmp(pszParam, "Embedding") == 0)
   {
   m_bRunEmbedded = true;
   m_bShowSplash = false;
   }
   else if (::__invariant_stricmp(pszParam, "Automation") == 0)
   {
   m_bRunAutomated = true;
   m_bShowSplash = false;
   }
   }

   void CCommandLineInfo::ParseParamNotFlag(const ::string & pszParam)
   {
   if (m_strFileName.is_empty())
   m_strFileName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strPrinterName.is_empty())
   m_strPrinterName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strDriverName.is_empty())
   m_strDriverName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strPortName.is_empty())
   m_strPortName = pszParam;
   }

   #ifdef UNICODE
   void CCommandLineInfo::ParseParamNotFlag(const ::string & pszParam)
   {
   if (m_strFileName.is_empty())
   m_strFileName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strPrinterName.is_empty())
   m_strPrinterName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strDriverName.is_empty())
   m_strDriverName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strPortName.is_empty())
   m_strPortName = pszParam;
   }
   #endif

   void CCommandLineInfo::ParseLast(bool bLast)
   {
   if (bLast)
   {
   if (m_nShellCommand == FileNew && !m_strFileName.is_empty())
   m_nShellCommand = FileOpen;
   m_bShowSplash = !m_bRunEmbedded && !m_bRunAutomated;
   }
   }
   */

   ///////////////////////////////////////////////////////////////////////////////
   //// App termination

   //void application::SaveStdProfileSettings()
   //{
   //   ASSERT_VALID(this);


   //   //      if (m_nNumThumbnailPages != 0)
   //   //       WriteProfileInt(gen_ThumbnailSection, gen_ThumbnailEntry, m_nNumThumbnailPages);
   //}


   //
   //
   //
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //
   //   /////////////////////////////////////////////////////////////////////////////
   //   // WinHelp helper
   //
   //
   //   void application::WinHelp(uptr dwData, unsigned int nCmd)
   //   {
   //      __UNREFERENCED_PARAMETER(dwData);
   //      __UNREFERENCED_PARAMETER(nCmd);
   //
   //      // return global cast help mode state to false (backward compatibility)
   //      m_bHelpMode = false;
   //      // trans pMainWnd->PostMessage(e_message_kick_idle); // trigger idle update
   //
   //      //trans pMainWnd->WinHelp(dwData, nCmd);
   //   }
   //
   //   /////////////////////////////////////////////////////////////////////////////
   //   // HtmlHelp helper
   //
   //   void application::HtmlHelp(uptr dwData, unsigned int nCmd)
   //   {
   //
   //      __UNREFERENCED_PARAMETER(dwData);
   //
   //      __UNREFERENCED_PARAMETER(nCmd);
   //
   //      // return global cast help mode state to false (backward compatibility)
   //      m_bHelpMode = false;
   //      // trans pMainWnd->PostMessage(e_message_kick_idle); // trigger idle update
   //
   //      // trans pMainWnd->HtmlHelp(dwData, nCmd);
   //   }
   //
   //
   //   void application::WinHelpInternal(uptr dwData, unsigned int nCmd)
   //   {
   //      __UNREFERENCED_PARAMETER(dwData);
   //      __UNREFERENCED_PARAMETER(nCmd);
   //      //   ::pointer<::user::interaction>pMainWnd = psystem->m_puiMain;
   //      //   ENSURE_VALID(pMainWnd);
   //
   //      // return global cast help mode state to false (backward compatibility)
   //      m_bHelpMode = false;
   //      // trans pMainWnd->PostMessage(e_message_kick_idle); // trigger idle update
   //      // trans pMainWnd->WinHelpInternal(dwData, nCmd);
   //   }
   //
   //
   //#endif
   //




   /////////////////////////////////////////////////////////////////////////////
   // application idle processing

   //   void application::DevModeChange(char * pDeviceName)
   //
   //   {
   //      __UNREFERENCED_PARAMETER(pDeviceName);
   //
   //
   //#ifdef WINDOWS
   //      if (m_hDevNames == nullptr)
   //         return;
   //
   //#endif
   //
   //   }
   //

   //bool application::process_exception(const ::exception & e)
   //{

   //   return ::aura::application::on_run_exception(pexception))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool application::final_handle_exception(const ::exception & e)
   //{

   //   __UNREFERENCED_PARAMETER(pexception);

   //   if (!is_system())
   //   {

   //      if (psystem->final_handle_exception(pexception))
   //      {

   //         return true;

   //      }

   //   }

   //   return false;

   //}


   /*   bool application::open_link(const ::string & pszLink, const ::string & pszTarget)
   {
   __UNREFERENCED_PARAMETER(pszLink);
   __UNREFERENCED_PARAMETER(pszTarget);
   return false;
   }
   */










   void application::_001OnFileNew()
   {
      string strId = m_strId;
      //char chFirst = '\0';
      //if (strId.length() > 0)
      //{
      //   chFirst = strId[0];
      //}
      /*      if (m_pdocmanager != nullptr)
      document_manager()->_001OnFileNew();*/
   }

   void application::on_file_open()
   {
      //ENSURE(m_pdocmanager != nullptr);
      //document_manager()->on_file_open();
   }


   // This is aura API library.
   //
   //
   //
   //
   //
   //
   //
   //




   /*void ::aura::FormatString1(string & rString, unsigned int nIDS, const ::string & psz1)

   {
   __format_strings(rString, nIDS, &psz1, 1);

   }

   void ::aura::FormatString2(string & rString, unsigned int nIDS, const ::string & psz1,

   const ::scoped_string & scopedstr2)

   {
   const char * rgpsz[2];
   rgpsz[0] = psz1;

   rgpsz[1] = psz2;

   __format_strings(rString, nIDS, rgpsz, 2);
   }*/

   /////////////////////////////////////////////////////////////////////////////


   ///////////////////////////////////////////////////////////////////////////////
   //// Basic Help support (for backward compatibility to aura API 2.0)

   //void application::OnHelp()  // use context to derive help context
   //{
   //   if (m_dwPromptContext != 0)
   //   {
   //      // do not call WinHelp when the error is failing to lauch help
   //      //         if (m_dwPromptContext != HID_BASE_PROMPT+__IDP_FAILED_TO_LAUNCH_HELP)
   //      //          WinHelpInternal(m_dwPromptContext);
   //      return;
   //   }

   //   // otherwise, use window::OnHelp implementation
   //   /* trans ::windowing::window * pwindow = psystem->m_puiMain;
   //   ENSURE_VALID(pwindow);
   //   if (!pwindow->is_frame_window())
   //   pwindow->OnHelp();
   //   else
   //   ((pwindow))->OnHelp();*/
   //}


   //void application::OnHelpIndex()
   //{
   //   //
   //   //#ifdef WINDOWS_DESKTOP
   //   //
   //   //      WinHelpInternal(0L, HELP_INDEX);
   //   //
   //   //#endif
   //   //
   //}


   //void application::OnHelpFinder()
   //{

   //   //#ifdef WINDOWS_DESKTOP
   //   //
   //   //      WinHelpInternal(0L, HELP_FINDER);
   //   //
   //   //#endif

   //}


   //void application::OnHelpUsing()
   //{

   //   //#ifdef WINDOWS_DESKTOP
   //   //
   //   //      WinHelpInternal(0L, HELP_HELPONHELP);
   //   //
   //   //#endif
   //   //
   //}


   ///////////////////////////////////////////////////////////////////////////////
   //// Context Help Mode support (backward compatibility to aura API 2.0)

   //void application::OnContextHelp()
   //{
   //   // just use frame_window::OnContextHelp implementation
   //   /* trans   m_bHelpMode = HELP_ACTIVE;
   //   ::pointer<::user::frame_window>pMainWnd = (psystem->m_puiMain);
   //   ENSURE_VALID(pMainWnd);
   //   ENSURE(pMainWnd->is_frame_window());
   //   pMainWnd->OnContextHelp();
   //   m_bHelpMode = pMainWnd->m_bHelpMode;
   //   pMainWnd->PostMessage(e_message_kick_idle); // trigger idle update */
   //}

   ///////////////////////////////////////////////////////////////////////////////


   // This is aura API library.
   //
   //
   //
   //
   //
   //
   //
   //




   /////////////////////////////////////////////////////////////////////////////
   // WinApp support for printing

   /*bool application::GetPrinterDeviceDefaults(PRINTDLG* pPrintDlg)
   {
   UpdatePrinterSelection(m_hDevNames == nullptr); //force default if no current
   if (m_hDevNames == nullptr)
   return false;               // no printer defaults

   ENSURE_ARG(pPrintDlg != nullptr);
   pPrintDlg->hDevNames = m_hDevNames;
   pPrintDlg->hDevMode = m_hDevMode;

   ::GlobalUnlock(m_hDevNames);
   ::GlobalUnlock(m_hDevMode);
   return true;
   }*/

   //void application::UpdatePrinterSelection(bool bForceDefaults)
   //{
   //   __UNREFERENCED_PARAMETER(bForceDefaults);
   //}


   //void application::OnFilePrintSetup()
   //{
   //}

   //
   //#ifdef WINDOWS_DESKTOP
   //
   //
   //   void application::SelectPrinter(HANDLE hDevNames, HANDLE hDevMode, bool bFreeOld)
   //   {
   //
   //      __UNREFERENCED_PARAMETER(hDevNames);
   //      __UNREFERENCED_PARAMETER(hDevMode);
   //      __UNREFERENCED_PARAMETER(bFreeOld);
   //      throw ::interface_only();
   //
   //   }
   //
   //
   //#endif


   //::draw2d::graphics* application::CreatePrinterDC()
   //{
   //   throw ::interface_only();
   //   return nullptr;
   //}

   /////////////////////////////////////////////////////////////////////////////


   // This is aura API library.
   //
   //
   //
   //
   //
   //
   //
   //



   /////////////////////////////////////////////////////////////////////////////
   // application User Interface Extensions

   //void application::OnAppExit()
   //{

   //   // same as double-clicking on main window close box

   //   ASSERT(m_pacmeuserinteractionMain != nullptr);

   //   auto puserinteractionMain = __user_interaction(m_pacmeuserinteractionMain);

   //   puserinteractionMain->m_puiThis->send_message(e_message_close);

   //}


   //void application::HideApplication()
   //{

   //   try
   //   {

   //      if (m_pacmeuserinteractionMain == nullptr)
   //      {

   //         return;

   //      }

   //      // hide the application's windows before closing all the documents
   //      m_pacmeuserinteractionMain->m_puiThis->display(e_display_none);
   //      // trans    m_puiMain->ShowOwnedPopups(false);


   //      m_pacmeuserinteractionMain->m_puiThis->order(e_zorder_bottom);
   //      //m_puiMain->m_puiThis->m_bZ = true;
   //      // put the window at the bottom of zorder, so it isn't activated
   //      // m_puiMain->m_puiThis->zorder();

   //      //m_puiMain->m_puiThis->wait_redraw();

   //      m_pacmeuserinteractionMain->m_puiThis->display(e_display_none);


   //   }
   //   catch (...)
   //   {
   //   }

   //}





   bool application::save_all_modified()
   {
      /*      if (m_pdocmanager != nullptr)
      return document_manager()->save_all_modified();*/
      return true;
   }



   //   bool application::OnDDECommand(char * pszCommand)
   //
   //   {
   //      /*      if (m_pdocmanager != nullptr)
   //      return document_manager()->OnDDECommand(pszCommand);
   //
   //      else*/
   //      return false;
   //   }


   //
   //   void application::EnableModeless(bool bEnable)
   //   {
   //      DoEnableModeless(bEnable);
   //   }
   //
   //   void application::DoEnableModeless(bool bEnable)
   //   {
   //      __UNREFERENCED_PARAMETER(bEnable);
   //#ifdef ___NO_OLE_SUPPORT
   //      UNUSED(bEnable);
   //#endif
   //
   //      // no-op if main window is nullptr or not a frame_window
   //      /*   ::pointer<::user::interaction>pMainWnd = psystem->m_puiMain;
   //      if (pMainWnd == nullptr || !pMainWnd->is_frame_window())
   //      return;*/
   //
   //#ifndef ___NO_OLE_SUPPORT
   //      // check if notify hook installed
   //      /*xxx
   //      ASSERT_KINDOF(frame_window, pMainWnd);
   //      ::pointer<::user::frame_window>pFrameWnd = (::pointer<::user::frame_window>MainWnd;
   //      if (pFrameWnd->m_pNotifyHook != nullptr)
   //      pFrameWnd->m_pNotifyHook->OnEnableModeless(bEnable);
   //      */
   //#endif
   //   }
   //
   //
   //
   //
   //







   void application::RegisterShellFileTypes(bool bCompat)
   {
      //ENSURE(m_pdocmanager != nullptr);
      //      document_manager()->RegisterShellFileTypes(bCompat);
   }

   void application::UnregisterShellFileTypes()
   {
      //ENSURE(m_pdocmanager != nullptr);
      //    document_manager()->UnregisterShellFileTypes();
   }


   //int application::get_open_document_count()
   //{
   //   //ENSURE(m_pdocmanager != nullptr);
   //   //  return document_manager()->get_open_document_count();
   //   return 0;
   //}


   // This is aura API library.
   //
   //
   //
   //
   //
   //
   //
   //

   /////////////////////////////////////////////////////////////////////////////
   // application Settings Helpers


   void application::SetRegistryKey(const ::string & pszRegistryKey)

   {
      //ASSERT(m_pszRegistryKey == nullptr);
      //ASSERT(pszRegistryKey != nullptr);

      //ASSERT(m_strAppName.has_character());

      ////bool bEnable = __enable_memory_tracking(false);
      //free((void *)m_pszRegistryKey);
      //m_pszRegistryKey = strdup(pszRegistryKey);

      //free((void *)m_pszProfileName);
      //m_pszProfileName = strdup(m_strAppName);
      ////__enable_memory_tracking(bEnable);
   }

   void application::SetRegistryKey(unsigned int nIDRegistryKey)
   {
      //__UNREFERENCED_PARAMETER(nIDRegistryKey);
      //ASSERT(m_pszRegistryKey == nullptr);
      //throw ::interface_only();
      ///*char szRegistryKey[256];
      //VERIFY(::aura::LoadString(nIDRegistryKey, szRegistryKey));
      //SetRegistryKey(szRegistryKey);*/
   }

   //
   //#ifdef WINDOWS_DESKTOP
   //
   //   // returns key for HKEY_CURRENT_USER\"Software"\RegistryKey\ProfileName
   //   // creating it if it doesn't exist
   //   // responsibility of the caller to call RegCloseKey() on the returned HKEY
   //   HKEY application::GetAppRegistryKey()
   //   {
   //      //ASSERT(m_pszRegistryKey != nullptr);
   //      //ASSERT(m_pszProfileName != nullptr);
   //
   //      //HKEY hAppKey = nullptr;
   //      //HKEY hSoftKey = nullptr;
   //      //HKEY hCompanyKey = nullptr;
   //      //if(RegOpenKeyEx(HKEY_CURRENT_USER,"software",0,KEY_WRITE | KEY_READ,
   //      //   &hSoftKey) == ERROR_SUCCESS)
   //      //{
   //      //   unsigned int dw;
   //      //   if(RegCreateKeyEx(hSoftKey,m_pszRegistryKey,0,REG_NONE,
   //      //      REG_OPTION_NON_VOLATILE,KEY_WRITE | KEY_READ,nullptr,
   //      //      &hCompanyKey,&dw) == ERROR_SUCCESS)
   //      //   {
   //      //      RegCreateKeyEx(hCompanyKey,m_pszProfileName,0,REG_NONE,
   //      //         REG_OPTION_NON_VOLATILE,KEY_WRITE | KEY_READ,nullptr,
   //      //         &hAppKey,&dw);
   //      //   }
   //      //}
   //      //if(hSoftKey != nullptr)
   //      //   RegCloseKey(hSoftKey);
   //      //if(hCompanyKey != nullptr)
   //      //   RegCloseKey(hCompanyKey);
   //
   ////      return hAppKey;
   //      return nullptr;
   //   }
   //
   //   // returns key for:
   //   //      HKEY_CURRENT_USER\"Software"\RegistryKey\AppName\pszSection
   //
   //   // creating it if it doesn't exist.
   //   // responsibility of the caller to call RegCloseKey() on the returned HKEY
   //   HKEY application::GetSectionKey(const ::string & pszSection)
   //   {
   //
   //      ASSERT(pszSection != nullptr);
   //
   //      HKEY hSectionKey = nullptr;
   //
   //      HKEY hAppKey = GetAppRegistryKey();
   //
   //      if (hAppKey == nullptr)
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      DWORD dw;
   //
   //      RegCreateKeyExW(hAppKey, wstring(pszSection), 0, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, nullptr, &hSectionKey, &dw);
   //
   //      RegCloseKey(hAppKey);
   //
   //      return hSectionKey;
   //
   //   }
   //
   //
   //#endif

   /*   unsigned int application::GetProfileInt(const ::string & pszSection, const ::string & pszEntry,

   int nDefault)
   {
   ASSERT(pszSection != nullptr);

   ASSERT(pszEntry != nullptr);

   if (m_pszRegistryKey != nullptr) // use registry
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return nDefault;
   unsigned int dwValue;
   unsigned int dwType;
   unsigned int dwCount = sizeof(unsigned int);
   int lResult = RegQueryValueEx(hSecKey, (char *)pszEntry, nullptr, &dwType,

   (unsigned char *)&dwValue, &dwCount);
   RegCloseKey(hSecKey);
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_DWORD);
   ASSERT(dwCount == sizeof(dwValue));
   return (unsigned int)dwValue;
   }
   return nDefault;
   }
   else
   {
   ASSERT(m_pszProfileName != nullptr);
   return ::GetPrivateProfileInt(pszSection, pszEntry, nDefault,

   m_pszProfileName);
   }
   }

   string application::GetProfileString(const ::string & pszSection, const ::string & pszEntry,

   const ::scoped_string & scopedstrDefault)

   {
   ASSERT(pszSection != nullptr);

   ASSERT(pszEntry != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return pszDefault;

   string strValue;
   unsigned int dwType=REG_NONE;
   unsigned int dwCount=0;
   int lResult = RegQueryValueEx(hSecKey, (char *)pszEntry, nullptr, &dwType,

   nullptr, &dwCount);
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_SZ);
   lResult = RegQueryValueEx(hSecKey, (char *)pszEntry, nullptr, &dwType,

   (unsigned char *)strValue.GetBuffer(dwCount/sizeof(char)), &dwCount);
   strValue.ReleaseBuffer();
   }
   RegCloseKey(hSecKey);
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_SZ);
   return strValue;
   }
   return pszDefault;

   }
   else
   {
   ASSERT(m_pszProfileName != nullptr);

   if (pszDefault == nullptr)

   pszDefault = "";   // don't pass in nullptr

   char szT[4096];
   unsigned int dw = ::GetPrivateProfileString(pszSection, pszEntry,

   pszDefault, szT, _countof(szT), m_pszProfileName);

   ASSERT(dw < 4095);
   return szT;
   }
   }

   bool application::GetProfileBinary(const ::string & pszSection, const ::string & pszEntry,

   unsigned char** ppData, unsigned int* pBytes)
   {
   ASSERT(pszSection != nullptr);

   ASSERT(pszEntry != nullptr);

   ASSERT(ppData != nullptr);
   ASSERT(pBytes != nullptr);
   *ppData = nullptr;
   *pBytes = 0;
   if (m_pszRegistryKey != nullptr)
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   {
   return false;
   }

   // ensure destruction

   // linux ::aura::CRegKey rkSecKey(hSecKey);

   unsigned int dwType=0;
   unsigned int dwCount=0;
   int lResult = RegQueryValueEx(hSecKey, (char *)pszEntry, nullptr, &dwType, nullptr, &dwCount);

   *pBytes = dwCount;
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_BINARY);
   *ppData = ___new unsigned char[*pBytes];
   lResult = RegQueryValueEx(hSecKey, (char *)pszEntry, nullptr, &dwType,

   *ppData, &dwCount);
   }
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_BINARY);
   return true;
   }
   else
   {
   delete [] *ppData;
   *ppData = nullptr;
   }
   return false;
   }
   else
   {
   ASSERT(m_pszProfileName != nullptr);

   string str = GetProfileString(pszSection, pszEntry, nullptr);

   if (str.is_empty())
   return false;
   ASSERT(str.length()%2 == 0);
   iptr nLen = str.length();
   *pBytes = unsigned int(nLen)/2;
   *ppData = ___new unsigned char[*pBytes];
   for (int i=0;i<nLen;i+=2)
   {
   (*ppData)[i/2] = (unsigned char)
   (((str[i+1] - 'A') << 4) + (str[i] - 'A'));
   }
   return true;
   }
   }


   bool application::WriteProfileInt(const ::string & pszSection, const ::string & pszEntry,

   int nValue)
   {
   ASSERT(pszSection != nullptr);

   ASSERT(pszEntry != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return false;
   int lResult = RegSetValueEx(hSecKey, pszEntry, nullptr, REG_DWORD,

   (unsigned char *)&nValue, sizeof(nValue));
   RegCloseKey(hSecKey);
   return lResult == ERROR_SUCCESS;
   }
   else
   {
   ASSERT(m_pszProfileName != nullptr);

   char szT[16];
   _stprintf_s(szT, _countof(szT), "%d", nValue);
   return ::WritePrivateProfileString(pszSection, pszEntry, szT,

   m_pszProfileName);
   }
   }

   bool application::WriteProfileString(const ::string & pszSection, const ::string & pszEntry,

   const ::scoped_string & scopedstrValue)

   {
   ASSERT(pszSection != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   int lResult;
   if (pszEntry == nullptr) //delete whole department

   {
   HKEY hAppKey = GetAppRegistryKey();
   if (hAppKey == nullptr)
   return false;
   lResult = ::RegDeleteKey(hAppKey, pszSection);

   RegCloseKey(hAppKey);
   }
   else if (pszValue == nullptr)

   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return false;
   // necessary to cast away const below
   lResult = ::RegDeleteValue(hSecKey, (char *)pszEntry);

   RegCloseKey(hSecKey);
   }
   else
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return false;
   lResult = RegSetValueEx(hSecKey, pszEntry, nullptr, REG_SZ,

   (unsigned char *)pszValue, (lstrlen(pszValue)+1)*sizeof(char));

   RegCloseKey(hSecKey);
   }
   return lResult == ERROR_SUCCESS;
   }
   else
   {
   ASSERT(m_pszProfileName != nullptr);
   ASSERT(lstrlen(m_pszProfileName) < 4095); // can't read in bigger
   return ::WritePrivateProfileString(pszSection, pszEntry, pszValue,

   m_pszProfileName);
   }
   }

   bool application::WriteProfileBinary(const ::string & pszSection, const ::string & pszEntry,

   unsigned char * pData, unsigned int nBytes)
   {
   ASSERT(pszSection != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   int lResult;
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return false;
   lResult = RegSetValueEx(hSecKey, pszEntry, nullptr, REG_BINARY,

   pData, nBytes);
   RegCloseKey(hSecKey);
   return lResult == ERROR_SUCCESS;
   }

   // convert to string and write out
   char * psz = ___new char[nBytes*2+1];

   unsigned int i;
   for (i = 0; i < nBytes; i++)
   {
   psz[i*2] = (char)((pData[i] & 0x0F) + 'A'); //low nibble

   psz[i*2+1] = (char)(((pData[i] >> 4) & 0x0F) + 'A'); //high nibble

   }
   psz[i*2] = 0;


   ASSERT(m_pszProfileName != nullptr);

   bool bResult = WriteProfileString(pszSection, pszEntry, psz);

   delete[] psz;

   return bResult;
   }

   #include "framework.h"*/




   /*   ::property_set & application::propset(object * pparticle)
   {
   single_lock synchronouslock(&m_mapObjectSet, true);
   return m_mapObjectSet[pparticle];
   }

   ::property_set * application::existing_propset(object * pparticle)
   {
   single_lock synchronouslock(&m_mapObjectSet, true);
   auto point = m_mapObjectSet.plookup(pparticle);
   if(point == nullptr)
   return nullptr;
   return &point->m_value;
   }*/



   bool application::does_launch_window_on_startup()
   {

      return true;

   }


   bool application::activate_app()
   {

      if (m_pacmeuserinteractionMain != nullptr)
      {

         auto puserinteractionMain = m_pacmeuserinteractionMain;

         puserinteractionMain->display(e_display_normal);

      }

      return true;

   }


   //void application::term()
   //{


   //   try
   //   {

   //      if (m_pacmeuserinteractionMain == nullptr)
   //      {

   //         return;

   //      }

   //      // hide the application's windows before closing all the documents
   //      m_pacmeuserinteractionMain->m_puiThis->display(e_display_none);
   //      // trans    m_puiMain->ShowOwnedPopups(false);


   //      m_pacmeuserinteractionMain->m_puiThis->order(e_zorder_bottom);
   //      //m_puiMain->m_puiThis->m_bZ = true;
   //      // put the window at the bottom of zorder, so it isn't activated
   //      // m_puiMain->m_puiThis->zorder();

   //      //m_puiMain->m_puiThis->wait_redraw();

   //      m_pacmeuserinteractionMain->m_puiThis->display(e_display_none);


   //   }
   //   catch (...)
   //   {
   //   }

   //   try
   //   {

   //      ::aura::application::term();

   //   }
   //   catch (...)
   //   {

   //      m_result.add(error_failed);

   //   }

   //}


   ::user::interaction* application::get_request_parent_ui(::user::interaction* pinteraction, ::user::system* pusersystem)
   {

      ::pointer<::user::interaction>puserinteractionParent;

      if (puserinteractionParent && pusersystem->m_prequest)
      {

         puserinteractionParent = pusersystem->m_prequest->m_puserelementParent;

      }

      return puserinteractionParent;

   }


::aura::theme*application:: theme() { return m_ptheme.get(); }



   void application::_001OnFileNew(::message::message* pmessage)
   {

      ::payload payloadFile;

      ::payload varQuery;

      varQuery["command"] = "new_file";

      //request_file(payloadFile, varQuery);

      pmessage->m_bRet = true;

   }



   //   bool application::on_open_document_file(::payload payloadFile)
   //   {
   //
   //      return _001OpenDocumentFile(payloadFile);
   //
   //   }

   //::user::document* application::_001OpenDocumentFile(::payload payloadFile)
   //{

   //   request_file(payloadFile);

   //   return payloadFile["document"].cast < ::user::document >();

   //}


   //bool application::_001OnDDECommand(const ::string & pcsz)

   //{
   //   throw ::interface_only();
   //   //return m_pimpl->_001OnDDECommand(pcsz);


   //   return false;
   //}

   //   ::aura::file_system & application::file_system()
   // {
   //  return m_spfilesystem;
   //}







   //   ::user::interaction * application::get_desktop_window()
   //   {
   //#if defined(UNIVERSAL_WINDOWS) || defined(__APPLE__)
   //      throw ::exception(todo);
   //      /*#elif defined(LINUX)
   //
   //      //      _synchronous_lock synchronouslock(&user_synchronization());
   //
   //      xdisplay pdisplay.
   //      pdisplay.open(nullptr) = x11_get_display();
   //
   //      oswindow window(pdisplay, DefaultRootWindow(pdisplay));
   //
   //      XCloseDisplay(pdisplay);
   //
   //      return window_from_os_data(window);
   //      */
   //#else
   //
   //
   //#endif
   //
   //   }





   //void application::assert_ok() const
   //{
   //   thread::assert_ok();


   //   if (::get_task() != (thread*)this)
   //      return;     // only do subset if called from different thread

   //   ASSERT(::get_task() == this);
   //   //ASSERT(::windows_definition::CurrentInstanceHandle == m_hInstance);

   //   /*      if (m_pdocmanager != nullptr)
   //   ASSERT_VALID(m_pdocmanager);*/
   //}

   //   void application::dump(dump_context& dumpcontext) const
   //   {
   //
   //      ::aura::application::dump(dumpcontext);
   //
   //      dumpcontext << "\nm_bHelpMode = " << m_bHelpMode;
   //      dumpcontext << "\nm_pszHelpFilePath = " << m_strHelpFilePath;
   //      dumpcontext << "\nm_pszProfileName = " << m_strProfileName;
   //
   //#ifdef WINDOWS
   //      dumpcontext << "\nm_hDevMode = " << (void*)m_hDevMode;
   //      dumpcontext << "\nm_hDevNames = " << (void*)m_hDevNames;
   //#endif
   //
   //      dumpcontext << "\nm_dwPromptContext = " << (unsigned int)m_dwPromptContext;
   //      //      dumpcontext << "\nm_eHelpType = " << m_eHelpType;
   //
   //
   //      /*      if (m_pdocmanager != nullptr)
   //      document_manager()->dump(dumpcontext);*/
   //
   //      dumpcontext << "\nm_nWaitCursorCount = " << m_iWaitCursorCount;
   //      dumpcontext << "\nm_nNumThumbnailPages = " << m_nNumThumbnailPages;
   //
   //      dumpcontext << "\n";
   //   }


   //void application::install_message_routing(::channel* pchannel)
   //{

   //   aura::application::install_message_routing(pchannel);

   //   add_command_handler("switch_context_theme", &application::_001OnSwitchContextTheme);

   //}


   //bool application::base_support()
   //{

   //   //if(!application::base_support())
   //   // return false;

   //   if (m_strBaseSupportId.is_empty())
   //   {

   //      ::property_set propertyset;

   //      dialog_box("err\\developer\\base_support\\support_id_not_specified.xml", propertyset);

   //      return false;

   //   }

   //   return true;
   //}


   //string application::sync_message_box(const string & pszMatter, ::property_set & propertyset)
   //{
   //
   //   __UNREFERENCED_PARAMETER(propertyset);
   //
   //   __UNREFERENCED_PARAMETER(pszMatter);
   //
   //   return "";

   //}


   //void application::bergedge_start()
   //{

   //   string strId = m_strId;

   //   char chFirst = '\0';

   //   if (strId.length() > 0)
   //   {

   //      chFirst = strId[0];

   //   }

   //   return true;

   //}

   //
   //#ifdef WINDOWS_DESKTOP
   //
   //
   //   bool Is_Vista_or_Later()
   //   {
   //      OSVERSIONINFOEX osvi;
   //      DWORDLONG dwlConditionMask = 0;
   //      unsigned char op = VER_GREATER_EQUAL;
   //
   //      // Initialize the OSVERSIONINFOEX structure.
   //
   //      ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
   //      osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
   //      osvi.dwMajorVersion = 6;
   //      //   osvi.dwMinorVersion = 1;
   //      //   osvi.wServicePackMajor = 0;
   //      //   osvi.wServicePackMinor = 0;
   //
   //      // Initialize the condition mask.
   //
   //      VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, op);
   //      //VER_SET_CONDITION( dwlConditionMask, VER_MINORVERSION, op );
   //      //VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMAJOR, op );
   //      //VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMINOR, op );
   //
   //      // Perform the test.
   //
   //      return VerifyVersionInfo(
   //         &osvi,
   //         VER_MAJORVERSION | VER_MINORVERSION |
   //         VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR,
   //         dwlConditionMask) != false;
   //   }
   //
   //
   //#endif


   void application::pre_translate_message(::message::message* pmessage)
   {

      //::pointer<::user::message>pusermessage(pmessage);

      //      if (pmessage->m_emessage == WM_USER + 124 && pmessage->userinteraction() == nullptr)
      //      {
      //
      //         /*
      //
      //         OnMachineEvent((flags < machine_event::enum_flag> *) pmsg->lParam);
      //         delete (flags < machine_event::enum_flag> *) pmsg->lParam;
      //
      //         */
      //
      //         pmessage->m_bRet = true;
      //
      //         return;
      //
      //      }

      return thread::pre_translate_message(pmessage);

   }


   //void application::on_create_split_impact(::user::split_impact* psplit)
   //{

   //}


   //   void application::EnableShellOpen()
   //   {
   ////
   ////#ifdef WINDOWS_DESKTOP
   ////
   ////      ASSERT(m_atomApp == 0 && m_atomSystemTopic == 0); // do once
   ////
   ////      if (m_atomApp != 0 || m_atomSystemTopic != 0)
   ////      {
   ////
   ////         return;
   ////
   ////      }
   ////
   ////      // Win95 & Win98 sends a WM_DDE_INITIATE with an atom that points to the
   ////      // short file name so we need to use the short file name.
   ////      string strShortName;
   ////
   ////      strShortName = file()->module();
   ////
   ////      // strip out path
   ////      //string strFileName = ::PathFindFileName(strShortName);
   ////      // strip out extension
   ////      //char * pszFileName = strFileName.GetBuffer();
   ////      //::PathRemoveExtension(pszFileName);
   ////      //strFileName.ReleaseBuffer();
   ////
   ////      //      m_atomApp = ::GlobalAddAtom(strFileName);
   ////      //    m_atomSystemTopic = ::GlobalAddAtom("system");
   ////
   ////#endif
   //
   //   }




   //bool application::on_install()
   //{

   //   if (!::aura::application::on_install())
   //   {

   //      return false;

   //   }

   //   string strId = m_strId;

   //   char chFirst = '\0';

   //   if (strId.length() > 0)
   //   {

   //      chFirst = strId[0];

   //   }

   //   return true;

   //}


   bool application::on_run_install()
   {

      if (m_strId == "session" || m_strAppName == "session")
      {

         if (is_false("session_start"))
         {

            //system()->set_finish(system());

            system()->set_finish();

         }

      }
      else
      {

         system()->destroy();

      }

      return true;

   }


   //bool application::on_uninstall()
   //{

   //   bool bOk = ::aura::application::on_uninstall();

   //   string strId = m_strId;

   //   char chFirst = '\0';

   //   if (strId.length() > 0)
   //   {

   //      chFirst = strId[0];

   //   }

   //   return bOk;

   //}


   bool application::on_run_uninstall()
   {

      if (m_strId == "session")
      {

         if (is_false("session_start"))
         {

            system()->destroy();

         }

      }
      else
      {

         system()->destroy();

      }

      return true;

   }


   void application::on_application_signal(::message::message* pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   //::aura::printer* application::get_printer(const ::string & pszDeviceName)
   //{

   //   return nullptr;

   //}


   //bool application::set_keyboard_layout(const ::string & pszPath, const ::action_context& context)
   //{

   //   return psession->keyboard().load_layout(pszPath, context);

   //}


   int application::track_popup_menu(::menu::track_popup * ptrackpopup)
   {

      __UNREFERENCED_PARAMETER(ptrackpopup);

      return 1;

   }


   bool application::get_fs_size(string& strSize, const ::string & pszPath, bool& bPending)
   {

      long long i64Size;

      if (!get_fs_size(i64Size, pszPath, bPending))
      {

         strSize.empty();

         return false;

      }

      if (i64Size > 1024 * 1024 * 1024)
      {

         double d = (double)i64Size / (1024.0 * 1024.0 * 1024.0);

         strSize.formatf("%0.2f GB", d);

      }
      else if (i64Size > 1024 * 1024)
      {

         double d = (double)i64Size / (1024.0 * 1024.0);

         strSize.formatf("%0.1f MB", d);

      }
      else if (i64Size > 1024)
      {

         double d = (double)i64Size / (1024.0);

         strSize.formatf("%0.0f KB", d);

      }
      else if (i64Size > 0)
      {

         strSize.formatf("1 KB");

      }
      else
      {

         strSize.formatf("0 KB");

      }

      if (bPending)
      {

         strSize = "~" + strSize;

      }

      return true;

   }


   bool application::get_fs_size(long long& i64Size, const ::string & pszPath, bool& bPending)
   {
      return false;
      //db_server * pcentral = dynamic_cast <db_server *> (psystem->m_psimpledb->db());

      //if (pcentral == nullptr)
      //{

      //   return false;

      //}

      //return pcentral->m_pfilesystemsizeset->get_cache_fs_size(i64Size, pszPath, bPending);

   }


   void application::set_title(const ::string & pszTitle)
   {

      auto psession = session();

      psession->set_app_title(m_strAppName, pszTitle);

   }


   bool application::_001CloseApplicationByUser(::pointer<::user::interaction>puserinteractionExcept)
   {

      // Closing just this application.
      // It is different of a system exit.
      // ::auraacmesystem() (a single ca2 process) can host
      // multiple ca2 application objects.

      // attempt to save all documents
      if (!save_all_modified())
      {

         return false;     // don't close it

      }

      // hide the application's windows before closing all the documents
      HideApplication();

      close(::e_exit_application);

      return true;

   }


   //oswindow application::get_ca2_app_wnd(const ::string & psz)
   //{

   //   __UNREFERENCED_PARAMETER(psz);

   //   return nullptr;

   //}
   //
   //
   //   int application::send_simple_command(const ::string & psz, void* osdataSender)
   //   {
   //      string strApp;
   //      string_array stra;
   //      stra.add_tokens(psz, "::", true);
   //      if (stra.get_size() > 0)
   //      {
   //         strApp = stra[0];
   //         ::windowing::window * pwindow = get_ca2_app_wnd(strApp);
   //         if (oswindow != nullptr)
   //         {
   //            return send_simple_command((void*)oswindow, psz, osdataSender);
   //         }
   //      }
   //      return -1;
   //   }
   //
   ////
   //   int application::send_simple_command(void* osdata, const ::string & psz, void* osdataSender)
   //   {
   //#ifdef WINDOWS_DESKTOP
   //      ::windowing::window * pwindow = (::oswindow) osdata;
   //      if (!::IsWindow(oswindow))
   //         return -1;
   //      COPYDATASTRUCT cds;
   //      memory_set(&cds, 0, sizeof(cds));
   //      cds.dwData = 888888;
   //      cds.cbData = (unsigned int)strlen(psz);
   //      cds.lpData = (PVOID)psz;
   //
   //      return (int)SendMessage(oswindow, WM_COPYDATA, (wparam)osdataSender, (lparam)&cds);
   //#else
   //      throw ::exception(todo);
   //#endif
   //   }


   void application::ensure_app_interest()
   {

#ifndef UNIVERSAL_WINDOWS

      auto psession = session();

      auto puser = user();

      auto pwindowing = system()->windowing();

      throw ::exception(todo);

      //for (int i = 0; i < m_straAppInterest.get_count(); i++)
      //{
      //   if (m_straAppInterest[i] != m_strAppName || pwindowing->is_window(m_mapAppInterest[m_straAppInterest[i]]))
      //   {
      //      psystem->assert_running_local(m_straAppInterest[i]);
      //   }
      //}

#else

      //throw ::exception(todo);

#endif

   }


   bool application::is_system() const
   {

      return false;

   }


   bool application::is_session() const
   {

      return false;

   }


   void application::data_on_after_change(::database::client* pclient, const ::scoped_string & scopedstr, ::topic * ptopic)
   {

   }


   int application::GetVisibleTopLevelFrameCountExcept(::pointer<::user::interaction>puserinteractionExcept)
   {

      int iCount = 0;

      return iCount;

   }


   int application::GetVisibleFrameCount()
   {

      auto uia = *m_puserinteractionaFrame;

      int iCount = 0;

      for (int i = 0; i < uia.interaction_count(); i++)
      {

         ::pointer<::user::interaction>puserinteraction = uia.interaction_at(i);

         if (puserinteraction != nullptr
            && puserinteraction->is_window()
            && puserinteraction->is_window_visible(::user::e_layout_sketch))
         {
            iCount++;
         }
      }
      return iCount;
   }


   //void application::on_create_keyboard()
   //{

   //   string str;

   //   // keyboard on_layout
   //   //if(datastream()->get("keyboard_layout",str) && str.has_character())
   //   {
   //      // psession->set_keyboard_layout(str,::e_source_database);
   //   }
   //   //else
   //   {
   //      set_keyboard_layout(nullptr, ::e_source_database);
   //   }

   //}


   //::type application::user_default_controltype_to_typeinfo(enum user::enum_control_type econtroltype)
   //{

   //   return Sess(this).userex()->controltype_to_typeinfo(econtroltype);

   //}


   //bool application::platform_open_by_file_extension(int iEdge, const ::string & pszPathName, application_bias * pappbias)
   //{

   //   return psystem->get_platform(iEdge)->open_by_file_extension(pszPathName, pappbias);
   //}

   //bool application::platform_open_by_file_extension(int iEdge, ::create * pcc)
   //{

   //   return psystem->get_platform(iEdge)->open_by_file_extension(pcc);
   //}


   //   ::pointer<::apex::application>application::create_platform(::apex::session* psession)
   //   {
   //
   //      return __allocate ::aura::session();
   //
   //   }


   //void application::on_change_cur_sel(::user::tab* ptab)
   //{



   //}


   //bool application::_001OnAgreeExit()
   //{

   //   if (!save_all_modified())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //void application::france_exit()
   //{

   //   ::aura::application::france_exit();

   //}


   void application::prepare_form(atom atom, ::form_document* pformdocument)
   {



   }


   void application::report_error(const ::exception & e, int iMessageFlags, const ::string & pszTopic)
   {

      string strMessage;

      strMessage += pszTopic;

      strMessage += " : ";

      strMessage += e.get_message();

      auto puserinteractionMain = m_pacmeuserinteractionMain;

      //puserinteractionMain->message_box(strMessage, nullptr, ::enum_message_box(iMessageFlags));

      output_error_message(strMessage, pszTopic, iMessageFlags);

   }


   bool application::can_close_application()
   {

      return true;

   }


   bool application::on_close_frame_window(::user::frame_interaction* pframe)
   {

      if (pframe->m_bCloseApplicationIfLastVisibleFrame)
      {

         if (GetVisibleTopLevelFrameCountExcept(pframe) <= 0)
         {

            //pframe->set_finish();

            pframe->hide_and_then_destroy();

            //            _001TryCloseApplication();

         }
         else
         {

            pframe->hide();

         }

      }
      else
      {

         pframe->destroy_window();

      }

      return true;

   }


   ::type_atom application::control_type_from_id(const ::atom& atom, ::user::enum_control_type& econtroltype)
   {

      string str(atom);

      if (str.case_insensitive_begins("edit_"))
      {

         econtroltype = ::user::e_control_type_edit_plain_text;

         return ::type < ::user::plain_edit >();

      }

      return ::aura::application::control_type_from_id(atom, econtroltype);

   }


   string application::get_theme()
   {

      if (!m_ptheme)
      {

         return ::aqua::application::get_theme();

      }

      return m_ptheme->get_theme();

   }


   void application::initialize_contextualized_theme()
   {

      //auto estatus =

      __construct_new(m_ptheme);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      if (m_bContextTheme)
      {

         //estatus =

         m_ptheme->initialize_contextualized_theme();

         //if (!estatus)
         //{

         //   return estatus;

         //}

      }

      //return estatus;

   }


   //void application::on_change_theme()
   //{


   //}


   void application::_001OnSwitchContextTheme(::message::message* pmessage)
   {

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

      if (!m_ptheme)
      {

         return;

      }

      if (m_bContextTheme)
      {

         m_ptheme->switch_context_theme();

      }

   }


   //application::application()
   //{

   //   add_factory_item < ::user::user >();

   //   //m_bBaseProcessInitialize         = false;
   //   //m_bBaseProcessInitializeResult   = false;

   //   //m_bBaseInitialize1               = false;
   //   //m_bBaseInitialize1Result         = false;

   //   //m_bBaseInitialize                = false;
   //   //m_bBaseInitializeResult          = false;

   //   //m_bBaseInitializeInstance        = false;
   //   //m_bBaseInitializeInstanceResult  = false;




   //}

   //application::~application()
   //{

   //}


   //void application::initialize(::particle * pparticle)
   //{

   //   auto estatus = ::aura::application::initialize(pparticle);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

   //}

   //   void application::install_message_routing(::channel * pchannel)
   //   {
   //
   //
   //
   //   }


   void application::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      //::aqua::application::handle(ptopic, phandlercontext);

      //::user::form_callback::handle(ptopic, phandlercontext);

      if(ptopic->id() == id_app_activated)
      {

         if(m_pacmeuserinteractionMain)
         {
            
            ::cast < ::user::interaction > puserinteraction = m_pacmeuserinteractionMain;
            
            if(puserinteraction)
            {
               
               puserinteraction->on_app_activated(ptopic->user_activation_token());
               //m_pacmeuserinteractionMain->frame_toggle_restore();
               
            }

         }

      }
      else if (ptopic->id() == id_application_dark_mode_change)
      {

         if (m_puserinteractionaFrame)
         {
            for (auto & pinteraction : m_puserinteractionaFrame->interactiona())
            {

               pinteraction->set_need_redraw();

               pinteraction->post_redraw();

            }
         }

      }

      if (ptopic->id() == ::id_initialize_control)
      {

         ::pointer < ::user::interaction > puserinteraction = ptopic->m_puserelement;

         if (puserinteraction->id() == "user_auto_start_checkbox")
         {

            try
            {
               ::pointer<::user::check> pcheck = puserinteraction;

               if (pcheck.is_set())
               {

                  // auto pcontext = get_context();

                  pcheck->set_check(
                     node()->is_user_auto_start(get_executable_appid()),
                     ::e_source_initialize);

                  ::pointer < ::user::interaction > puserinteractionCheck = pcheck;

                  if (puserinteractionCheck)
                  {

                     puserinteractionCheck->add_handler(this);

                  }

               }
            }
            catch (...)
            {

            }

         }

      }
      else if (ptopic->id() == ::id_set_check)
      {

         auto puserinteraction = ptopic->user_interaction();

         if (puserinteraction->id() == "user_auto_start_checkbox"
            && ptopic->m_actioncontext.is_user_source())
         {

            try
            {

               ::pointer<::user::check>pcheck = puserinteraction;

               if (pcheck.is_set())
               {

                  node()->register_user_auto_start(
                     this,
                     "--auto_start=1",
                     pcheck->echeck() == ::e_check_checked);

               }

               ptopic->m_bRet = true;

               return;

            }
            catch (...)
            {

            }

         }

      }


   }


   //void application::process_init()
   //{

   //   if (::aura::application::process_init())
   //   {

   //      return true;

   //   }

   //   return true;

   //}


   //void application::init_instance()
   //{

   //   if (!::aura::application::init_instance())
   //   {

   //      return false;

   //   }

   //   auto estatus = create_impact_system();

   //   if (failed(estatus))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   void     application::create_impact_system()
   {

      //return ::success;

   }


   void application::process_message_filter(int code, ::message::message* pmessage)
   {

      //if (pmessage == nullptr)
      //   return;   // not handled

      //::pointer<::user::message>pusermessage(pmessage);

      //::pointer<::user::frame_window>pTopFrameWnd;
      ////::user::interaction * pMainWnd;
      //::user::interaction* pMsgWnd;
      //switch (code)
      //{
      //   //case MSGF_DDEMGR:
      //   // Unlike other WH_MSGFILTER codes, MSGF_DDEMGR should
      //   //  never call the next hook.
      //   // By returning false, the message will be dispatched
      //   //  instead (the default behavior).
      //   //return;

      //case MSGF_MENU:

      //   pMsgWnd = dynamic_cast <::user::interaction*> (pusermessage->m_puserinteraction);

      //   if (pMsgWnd != nullptr)
      //   {
      //      pTopFrameWnd = pMsgWnd->top_level_frame();
      //      if (pTopFrameWnd != nullptr && pTopFrameWnd->IsTracking() &&
      //         pTopFrameWnd->m_bHelpMode)
      //      {
      //         //pMainWnd = __get_main_window();
      //         //if((m_puiMain != nullptr) && (IsEnterKey(pusermessage) || IsButtonUp(pusermessage)))
      //         //{
      //         //   //                  pMainWnd->SendMessage(e_message_command, ID_HELP);
      //         //   pusermessage->m_bRet = true;
      //         //   return;
      //         //}
      //      }
      //   }
      //   // fall through...

      //case MSGF_DIALOGBOX:    // handles message boxes as well.
      //   //pMainWnd = __get_main_window();
      //   if (code == MSGF_DIALOGBOX && m_puiActive != nullptr &&
      //      pusermessage->id() >= e_message_key_first && pusermessage->id() <= e_message_key_last)
      //   {
      //   }
      //   break;
      //}
      //// default to not handled

   }





















   /*string application::get_cred(const ::string & strRequestUrlParam,const ::int_rectangle & rectangle,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive)
   {

      string str = ::account::get_cred(this,strUsername,strPassword,strToken);

      if(str == "ok" && strUsername.has_character() && strPassword.has_character())
         return "ok";

      if(!bInteractive)
         return "failed";

      ::pointer<::account::simple_ui>pinteraction;

      string strRequestUrl(strRequestUrlParam);

      if(strRequestUrl.is_empty())
      {

         string strIgnitionServer = file_system()->as_string(directory_system()->system() / "config\\system\\ignition_server.txt");

         if(case_insensitive_string_ends(strIgnitionServer,".ca2.network"))
         {

            strRequestUrl = "https://" + strIgnitionServer + "/";

         }
         else
         {

            strRequestUrl = "https://account.ca2.network/";

         }

         strRequestUrl = "https://account.ca2.network/";

      }

      pinteraction = __allocate ::account::simple_ui(this,strRequestUrl);

      pinteraction->m_login.m_peditUser->set_window_text(strUsername);

      pinteraction->m_login.m_ppassword->set_window_text("");

      string strResult = pinteraction->get_cred(rectangle,strUsername,strPassword,strToken,strTitle);

      pinteraction->DestroyWindow();

      ::account::set_cred(this,strToken,strUsername,strPassword);

      return strResult;

   }*/


   //::pointer<::user::user>application::create_user()
   //{

   //   return __allocate ::user::user();

   //}


   void application::on_thread_on_idle(::thread* pthread, int lCount)
   {

      if (lCount <= 0)
      {

         ::pointer<::user::interaction>pinteraction;

         while (get_frame(pinteraction))
         {
            //::user::interaction * pinteraction = (::user::interaction *) pimpl->m_spuiptra->element_at(i)->m_pvoidUserInteraction;
            bool bOk = false;
            try
            {

               bOk = pinteraction != nullptr && pinteraction->is_window_visible(::user::e_layout_sketch);
            }
            catch (...)
            {
            }
            if (!bOk)
            {
               //   try
               //   {
               //      papp->erase_frame(pinteraction);
               //   }
               //   catch(...)
               //   {
               //   }
               //   try
               //   {
               //      psession->erase_frame(pinteraction);
               //   }
               //   catch(...)
               //   {
               //   }
               //   try
               //   {
               //      psystem->erase_frame(pinteraction);
               //   }
               //   catch(...)
               //   {
               //   }
            }
            else
            {
               //               synchronouslock.unlock();
               try
               {
                  pinteraction->send_message(e_message_idle_update_command_user_interface, (wparam)true);
               }
               catch (...)
               {

               }
               //             synchronouslock.lock();
            }
         }


      }
      else if (lCount >= 0)
      {
      }

      //return lCount < 0;  // nothing more to do if lCount >= 0

   }





   ////void application::on_create_impact(::user::impact_data* pimpactdata)
   ////{


   ////}


   //bool application::process_message()
   //{

   //   return ::thread::process_message();

   //}


   //void application::SetCurrentHandles()
   //{

   //   ::aura::application::SetCurrentHandles();

   //}


   //void application::term_application()
   //{

   //   try
   //   {

   //      aura::application::term_application();

   //   }
   //   catch (...)
   //   {

   //   }

   //}


   ::image::icon* application::set_icon(::object * pobject, ::image::icon* picon, bool bBigIcon)
   {

      ::image::icon* piconOld = get_icon(pobject, bBigIcon);

      if (bBigIcon)
      {

         pobject->payload("big_icon") = picon;

      }
      else
      {

         pobject->payload("small_icon") = picon;

      }

      return piconOld;

   }


   ::image::icon* application::get_icon(object* pobject, bool bBigIcon) const
   {

      if (bBigIcon)
      {

         return const_cast <object*> (pobject)->cast < ::image::icon >("big_icon");

      }
      else
      {

         return const_cast <object*> (pobject)->cast < ::image::icon >("small_icon");

      }

   }


   ::user::interaction* application::create_menu_interaction()
   {

      return nullptr;

   }


   //::pointer<::user::document>application::defer_create_impact(string strImpact, ::user::interaction* puiParent, e_window_flag ewindowflag, const ::atom& atom)
   //{

   //   auto pcontroller = ::aura::application::defer_create_impact(strImpact, puiParent, ewindowflag, atom);

   //   if (pcontroller)
   //   {

   //      return pcontroller;

   //   }

   //   return nullptr;

   //}


   void application::on_song_added(const string& str)
   {

   }


   //::form_property_set * application::get_form_property_set()
   //{

   //   auto pset = ::user::form_callback::get_form_property_set();

   //   if (::is_set(pset))
   //   {

   //      return pset;

   //   }

   //   return this;

   //}

   string application::get_visual_studio_build()
   {

      //::file::path path = directory_system()->config() / "programming/vs_build.txt";

      //string strBuild = file()->as_string(path);
      //string strBuild = "10.0.22000.0";
      string strBuild = "10.0.22621.0";

      //strBuild.trim();

      return strBuild;

   }


   string application::sound_path(const ::string & psz)
   {

      string strFileName = string(psz) + string(".wav");

      string strFilePath = directory()->matter(strFileName);

      return strFilePath;

   }


   string application::get_default_playlist_path()
   {

      return "playlist/default";

   }


   ::aura::game * application::game()
   {

      return m_paquagame->m_pauragame;

   }


   void application::_001CloseApplication()
   {

      if (m_puserinteractionaFrame && m_puserinteractionaFrame->has_interaction())
      {

         for (auto& pframe : m_puserinteractionaFrame->interactiona())
         {

            if (::is_set(pframe))
            {

               pframe->destroy();

            }

         }

      }
      else
      {

         ::aqua::application::_001CloseApplication();

      }

   }


   //   icon_pointer application::load_icon(const ::payload& payloadFile)
   //   {
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //      string_array straMatter;
   //
   //      straMatter.add("main");
   //
   //      if (::is_set(get_app()))
   //      {
   //
   //         straMatter.add(get_app()->m_straMatterLocator);
   //
   //      }
   //
   //      hicon hicon = ::load_icon(this, straMatter, "icon.ico", 24, 24);
   //
   //      if (hicon == nullptr)
   //      {
   //
   //         return ::error_failed;
   //
   //      }
   //
   //      auto picon = __create_new < ::image::icon >();
   //
   //      if (!picon)
   //      {
   //
   //         return ::error_failed;
   //
   //      }
   //
   //      picon->attach_os_data(hicon);
   //
   //      return picon;
   //
   //#else
   //
   //      return ::success;
   //
   //#endif
   //
   //   }


   //bool application::on_application_menu_action(const ::string & pszCommand)
   //{

   //   if (m_pacmeuserinteractionMain != nullptr)
   //   {

   //      ::message::command command;

   //      command.id() = ::atom(pszCommand);

   //      __channel(m_pacmeuserinteractionMain)->route_command_message(&command);

   //      if (command.m_bRet)
   //      {

   //         return true;

   //      }

   //   }

   //   return false;

   //}

   //void application::on_initial_frame_position(::user::frame_interaction* pframe)
   //{

   //   auto psystem = system();

   //   psystem->on_initial_frame_position(pframe);

   //}



   //::aura::system * applicationacmesystem()
   //{

   //   return ::is_set(system()) ? dynamic_cast <::aura::system *> (system()) : nullptr;

   //}


   // ::aura::session* application::get_session()
   // {
   //
   //    return m_papplication && m_papplication->m_psession ? m_papplication->m_psession : nullptr;
   //
   // }
   //


   void application::on_additional_local_instance(bool & bHandled, string strModule, int iPid, string strCommandLine)
   {

      auto prequest = __create_new<::request >();

      prequest->_001ParseCommandLine(strCommandLine);

      ::cast < ::user::interaction > puserinteraction = m_pacmeuserinteractionMain;
      
      if(puserinteraction)
      {
         
         puserinteraction->frame_toggle_restore(nullptr);
         
      }

      //::user::impact * pinteraction = m_ptemplateWeatherMain->get_document(0)->get_impact();

      //if (pinteraction != nullptr)
      //{

      //   ::user::frame_interaction * pframe = pinteraction->top_level_frame();

      //   if (pframe != nullptr)
      //   {

      //      pframe->frame_toggle_restore();

      //      //if (pframe->is_window_visible() && !pframe->layout().is_iconic())
      //      //{

      //      //   pframe->order(e_zorder_top);

      //      //}

      //      //pframe->display(e_display_normal);

      //   }

      //}

      bHandled = true;

   }


   // ::user::user * application::aurauser()
   // {
   //
   //    return session()->user();
   //
   // }
   //
   //
   // ::axis::user * application::axisuser()
   // {
   //
   //    return aurauser()->m_paxisuser;
   //
   // }
   //
   //
   // ::base::user * application::user()
   // {
   //
   //    return aurauser();
   //
   // }
   //
   //
   // ::bred::user * application::breduser()
   // {
   //
   //    return aurauser()->m_pbreduser;
   //
   // }
   //
   //
   // ::core::user * application::coreuser()
   // {
   //
   //    return aurauser();
   //
   // }
   //
   //
   // //::core::user * application::coreuser()
   // //{
   //
   // //   return user()->m_pcobreuser;
   //
   // //}


   void application::pick_browse(const ::function < void(const ::file::path &) > & callback)
   {

      auto puserinteraction = m_pacmeuserinteractionMain;

      if(!puserinteraction)
      {

         return;

      }

      auto pwindow = puserinteraction->window();

      if(!pwindow)
      {

         return;

      }

      pwindow->pick_browse(callback);

   }


   void application::pick_media(const char *pszMediaType)
   {

      auto puserinteraction = m_pacmeuserinteractionMain;

      if(!puserinteraction)
      {

         return;

      }

      auto pwindow = puserinteraction->window();

      if(!pwindow)
      {

         return;

      }

      pwindow->pick_media(pszMediaType);

   }


   void application::on_prompt_write_file(::user::controller *pusercontroller)
   {

      auto puserinteraction = m_pacmeuserinteractionMain;

      if(!puserinteraction)
      {

         return;

      }

      auto pwindow = puserinteraction->window();

      if(!pwindow)
      {

         return;

      }

      pwindow->on_prompt_write_file(pusercontroller);

   }




   //#if !(defined(VK_USE_PLATFORM_IOS_MVK) || defined(VK_USE_PLATFORM_MACOS_MVK) || defined(VK_USE_PLATFORM_METAL_EXT))
   //   // iOS & macOS: getAssetPath() and getShaderBasePath() implemented externally for access to Obj-C++ path utilities
   ::file::path application::assets_folder()
   {
      return "matter://assets";
      //#if defined(VK_USE_PLATFORM_ANDROID_KHR)
      //      return ""_ansi;
      //#elif defined(VK_EXAMPLE_ASSETS_DIR)
      //      return VK_EXAMPLE_ASSETS_DIR;
      //#else
      //      return "matter://";
      //#endif
   }

   ::file::path application::shaders_folder()
   {
      return "matter://shaders";
      //#if defined(VK_USE_PLATFORM_ANDROID_KHR)
      //      return "shaders/"_ansi;
      //#elif defined(VK_EXAMPLE_SHADERS_DIR)
      //      return VK_EXAMPLE_SHADERS_DIR;
      //#else
      //      return "./../shaders/";
      //#endif
   }
   //#endif



   //void application::run_application()
   //{

   //   m_pengine->run_application();

   ////   ::pointer < ::graphics::application> papp = m_papplication;


   ////   __construct_new(m_pvkcdevice);

   ////   m_pvkcdevice->initialize_device(m_pvkcontainer);

   ////   __construct_new(m_prenderer);

   ////   m_prenderer->initialize_renderer(m_pvkcontainer, m_pvkcdevice);

   ////   auto pglobalpoolbuilder = __allocate VkcDescriptorPool::Builder();

   ////   pglobalpoolbuilder->initialize_builder(m_pvkcdevice);
   ////   pglobalpoolbuilder->setMaxSets(VkcRenderPass::MAX_FRAMES_IN_FLIGHT);
   ////   pglobalpoolbuilder->addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VkcRenderPass::MAX_FRAMES_IN_FLIGHT);

   ////   m_pglobalpool = pglobalpoolbuilder->build();

   ////   //m_pglobalpool->initialize_pool(m_pvkcdevice);

   ////   //= __allocate
   ////   //   VkcDescriptorPool::Builder(m_pvkcdevice)
   ////   //   .setMaxSets(VkcSwapChain::MAX_FRAMES_IN_FLIGHT)
   ////   //   .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VkcSwapChain::MAX_FRAMES_IN_FLIGHT)
   ////   //   .build();
   ////   loadGameObjects();

   ////   //m_pvkcdevice = __allocate VkcDevice(m_pvulkandevice);

   ////   ::pointer_array<buffer> uboBuffers;

   ////   uboBuffers.set_size(VkcRenderPass::MAX_FRAMES_IN_FLIGHT);

   ////   for (int i = 0; i < uboBuffers.size(); i++)
   ////   {

   ////      uboBuffers[i] = __allocate buffer();

   ////      uboBuffers[i]->initialize_buffer(
   ////         m_pvkcdevice,
   ////         sizeof(GlobalUbo),
   ////         1,
   ////         VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
   ////         VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

   ////      uboBuffers[i]->map();

   ////   }
   ////   auto globalSetLayout = VkcDescriptorSetLayout::Builder(m_pvkcdevice)
   ////      .addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
   ////      .build();


   ////   std::vector<VkDescriptorSet> globalDescriptorSets(VkcRenderPass::MAX_FRAMES_IN_FLIGHT);

   ////   for (int i = 0; i < globalDescriptorSets.size(); i++)
   ////   {

   ////      auto bufferInfo = uboBuffers[i]->descriptorInfo();

   ////      VkcDescriptorWriter(*globalSetLayout, *m_pglobalpool)
   ////         .writeBuffer(0, &bufferInfo)
   ////         .build(globalDescriptorSets[i]);

   ////   }

   ////   simple_render_system simpleRenderSystem{
   ////       m_pvkcdevice,
   ////       m_prenderer->getRenderPass(),
   ////       globalSetLayout->getDescriptorSetLayout() };

   ////   PointLightSystem pointLightSystem{
   ////       m_pvkcdevice,
   ////       m_prenderer->getRenderPass(),
   ////       globalSetLayout->getDescriptorSetLayout()
   ////   };

   ////   //VkcCamera camera{ glm::vec3(0.0f, 2.0f, -15.0f), -90.0f, 0.0f };
   ////   VkcCamera camera{ glm::vec3(0.0f, 2.0f, -15.0f), -90.0f, 0.0f };
   ////   auto viewerObject = VkcGameObject::createGameObject();
   ////   m_pvkcontainer->m_bLastMouse = true;
   ////   viewerObject.transform.translation.z = -2.5f;
   ////   MNKController cameraController{};
   ////   /*    glfwSetInputMode(_window.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   ////       glfwSetWindowUserPointer(_window.getGLFWwindow(), &cameraController);*/
   ////   cameraController.m_bMouseAbsolute;

   ////   papp->datastream()->get_block("camera", as_memory_block(camera));
   ////   papp->datastream()->get_block("transform", as_memory_block(viewerObject.transform));
   ////   papp->datastream()->get_block("camera_controller", as_memory_block(cameraController));

   ////   auto currentTime = std::chrono::high_resolution_clock::now();
   ////   //while (!_window.shouldClose())
   ////   while (!m_pvkcontainer->m_bShouldClose && task_get_run())
   ////   {

   ////      task_iteration();
   ////      //glfwPollEvents();

   ////      auto newTime = std::chrono::high_resolution_clock::now();

   ////      float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();

   ////      currentTime = newTime;

   ////      cameraController.handleMouseInput(m_pvkcontainer);

   ////      cameraController.updateLook(m_pvkcontainer, cameraController.getX(), cameraController.getY(), viewerObject);

   ////      cameraController.updateMovement(m_pvkcontainer, frameTime, viewerObject);

   ////      //cameraController.moveInPlaneXZ(m_pvkcontainer, frameTime, viewerObject);

   ////      camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

   ////      if (m_prenderer->m_pvkcrenderpass->width() > 0
   ////         && m_prenderer->m_pvkcrenderpass->height() > 0)
   ////      {

   ////         float aspect = m_prenderer->getAspectRatio();

   ////         camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 100.f);

   ////         if (auto commandBuffer = m_prenderer->beginFrame())
   ////         {

   ////            int frameIndex = m_prenderer->getFrameIndex();

   ////            FrameInfo frameInfo{ frameIndex, frameTime, commandBuffer, camera, globalDescriptorSets[frameIndex], m_gameObjects };

   ////            // update
   ////            GlobalUbo ubo{};
   ////            ubo.projection = camera.getProjection();
   ////            ubo.view = camera.getView();
   ////            ubo.inverseView = camera.getInverseView();
   ////            pointLightSystem.update(frameInfo, ubo);
   ////            uboBuffers[frameIndex]->writeToBuffer(&ubo);
   ////            uboBuffers[frameIndex]->flush();

   ////            // render
   ////            m_prenderer->beginRenderPass(commandBuffer);

   ////            simpleRenderSystem.renderGameObjects(frameInfo);
   ////            pointLightSystem.render(frameInfo);

   ////            m_prenderer->endRenderPass(commandBuffer);
   ////            m_prenderer->endFrame();

   ////         }

   ////      }

   ////   }

   ////   papp->datastream()->set("camera_controller", as_memory_block(cameraController));
   ////   papp->datastream()->set("transform", as_memory_block(viewerObject.transform));
   ////   papp->datastream()->set("camera", as_memory_block(camera));

   ////   if (m_pvkcdevice->device() != VK_NULL_HANDLE)
   ////   {

   ////      vkDeviceWaitIdle(m_pvkcdevice->device());

   ////   }

   ////}


   ////void Application::resize(int cx, int cy)
   ////{

   ////   m_prenderer->m_pvkcrenderpass->windowExtent.width = cx;
   ////   m_prenderer->m_pvkcrenderpass->windowExtent.height = cy;

   //}


   //void application::on_loa()
   //{

   //   //{
   //   //   ::pointer<VkcModel> vkcModel = VkcModel::createModelFromFile(m_pvkcdevice, "matter://models/flat_vase.obj");
   //   //   auto flatVase = VkcGameObject::createGameObject();

   //   //   flatVase.model = vkcModel;
   //   //   flatVase.transform.translation = { -.5f, .5f, 0.f };
   //   //   flatVase.transform.scale = { 3.f, 1.5f, 3.f };
   //   //   m_gameObjects.emplace(flatVase.getId(), std::move(flatVase));
   //   //}

   //   //{
   //   //   ::pointer<VkcModel> vkcModel = VkcModel::createModelFromFile(m_pvkcdevice, "matter://models/quad.obj");
   //   //   auto floor = VkcGameObject::createGameObject();
   //   //   floor.model = vkcModel;
   //   //   assert(vkcModel);
   //   //   floor.transform.translation = { 0.f, .5f, 0.f };
   //   //   floor.transform.scale = { 8.f, 1.f, 8.f };
   //   //   m_gameObjects.emplace(floor.getId(), std::move(floor));
   //   //}

   //   //{
   //   //   ::pointer<VkcModel> vkcModel = VkcModel::createModelFromFile(m_pvkcdevice, "matter://models/smooth_vase.obj");
   //   //   auto smoothVase = VkcGameObject::createGameObject();
   //   //   smoothVase.model = vkcModel;
   //   //   smoothVase.transform.translation = { .5f, .5f, 0.f };
   //   //   smoothVase.transform.scale = { 3.f, 1.5f, 3.f };
   //   //   m_gameObjects.emplace(smoothVase.getId(), std::move(smoothVase));

   //   //}

   //   //{
   //   //   ::pointer<VkcModel> vkcModel = VkcModel::createModelFromFile(m_pvkcdevice, "matter://models/StoneSphere.obj");
   //   //   auto stoneSphere = VkcGameObject::createGameObject();
   //   //   stoneSphere.model = vkcModel;
   //   //   stoneSphere.transform.translation = { .0f, 0.f, 2.f };
   //   //   stoneSphere.transform.scale = { .5f, .5f, .5f };
   //   //   m_gameObjects.emplace(stoneSphere.getId(), std::move(stoneSphere));

   //   //}

   //   //{

   //   //   ::pointer<VkcModel> vkcModel = VkcModel::createModelFromFile(m_pvkcdevice, "matter://models/Barrel_OBJ.obj");
   //   //   auto woodBarrel = VkcGameObject::createGameObject();
   //   //   woodBarrel.model = vkcModel;
   //   //   woodBarrel.transform.translation = { 1.f, -.4f, -1.5f };
   //   //   woodBarrel.transform.scale = { 1.f, 1.f, 1.f };
   //   //   m_gameObjects.emplace(woodBarrel.getId(), std::move(woodBarrel));

   //   //}

   //   //float fLo = 0.5f;

   //   //std::vector<glm::vec3> lightColors{
   //   //      {1.f, fLo, fLo},
   //   //      {fLo, fLo, 1.f},
   //   //      {fLo, 1.f, fLo},
   //   //      {1.f, 1.f, fLo},
   //   //      {fLo, 1.f, 1.f},
   //   //      {1.f, 1.f, 1.f}
   //   //};

   //   //for (int i = 0; i < lightColors.size(); i++) {
   //   //   auto pointLight = VkcGameObject::makePointLight(0.2f);
   //   //   pointLight.color = lightColors[i];
   //   //   auto rotateLight = glm::rotate(
   //   //      glm::mat4(1.f),
   //   //      (i * glm::two_pi<float>()) / lightColors.size(),
   //   //      { 0.f, -1.f, 0.f });
   //   //   pointLight.pointLight->lightIntensity = 1.0f;
   //   //   pointLight.transform.translation = glm::vec3(rotateLight * glm::vec4(-1.f, -1.f, -1.f, 1.f));
   //   //   m_gameObjects.emplace(pointLight.getId(), std::move(pointLight));
   //   //}

   //}


   //void application::handle_mouse_move(int x, int y)
   //{



   //}

   //void application::resize(int cx, int cy)
   //{


   //}


   ::string application::draw2d_get_default_implementation_name()
   {

      if (m_gpu.m_bUseSwapChainWindow)
      {

         ::string strGraphics3DImplementation = graphics3d_get_implementation_name();

         if (strGraphics3DImplementation == "vulkan")
         {

            //return system()->implementation_name("draw2d", "vkvg");

            return system()->implementation_name("draw2d", "vulkan");

         }
         else if (strGraphics3DImplementation.begins("directx"))
         {

            if (m_strDraw2dImplementation.case_insensitive_equals(strGraphics3DImplementation))
            {

               return m_strDraw2dImplementation;

            }

            return system()->implementation_name("draw2d", "direct2d");

         }
         else
         {

            return system()->implementation_name("draw2d", strGraphics3DImplementation);

         }

      }
      else
      {

         return ::aqua::application::draw2d_get_default_implementation_name();

      }

   }


   ::string application::graphics3d_get_implementation_name()
   {

      return m_strGraphics3DImplementation;

   }


} // namespace aura


// ::pointer < ::innate_ui::icon > application::innate_ui
