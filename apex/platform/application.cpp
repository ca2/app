#include "framework.h"
#include "application.h"
#include "application_menu.h"
#include "session.h"
#include "system.h"
#include "os_context.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/exception/exit.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/not_implemented.h"
#include "acme/filesystem/file/folder.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/handler/request.h"
#include "acme/primitive/primitive/url.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/event.h"
#include "acme/parallelization/install_mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/profiler.h"
#include "acme/primitive/datetime/datetime.h"
#include "acme/primitive/string/command_line.h"
#include "acme/primitive/string/str.h"
#include "acme/primitive/text/context.h"
#include "apex/message/application.h"
//#include "apex/id.h"
#include "acme/platform/version.h"
#include "apex/platform/machine_event_data.h"
#include "apex/platform/machine_event.h"
#include "apex/platform/machine_event_central.h"
#include "apex/platform/node.h"
#include "apex/interprocess/call.h"
#include "apex/interprocess/communication.h"
#include "apex/interprocess/target.h"
#include "apex/interprocess/task.h"
#include "apex/database/_binary_stream.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/networking/application/application.h"
#include "apex/networking/http/context.h"
#include "apex/user/language_map.h"


//void shell_restart();
//int shell_pin_to_taskbar(const wchar_t * path);
//int shell_unpin_from_taskbar(const wchar_t * path);

//#include "apex/operating_system/_node.h"
#include "node.h"
//#include "apex/os/_os.h"
#include "application_impl.h"



//extern "C"
//{
//
//   typedef void FN_factory(::factory::factory * pfactory);
//
//   typedef FN_factory * PFN_factory;
//
//}

//PFN_factory g_pfnfactoryDraw2d = nullptr;
//
//
//PFN_factory ([a-z0-9_]+)_factory(::factory::factory * pfactory)
//{
//
//   return g_pfnfactoryDraw2d;
//
//}

//
//void ([a-z0-9_]+)_factory(PFN_factory pfnfactoryDraw2d)
//{
//
//   g_pfnfactoryDraw2d = pfnfactoryDraw2d;
//
//}



//#ifdef WINDOWS_DESKTOP
//
//CLASS_DECL_ACME void windows_install_crash_dump_reporting(const ::string & strModuleNameWithTheExeExtension);
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

//#include "apex/operating_system/ansios/ansios.h"
//#include "apex/operating_system/linux/_linux.h"

//#include <X11/cursorfont.h>
#include <sys/time.h>
#include <link.h>
#include "acme/operating_system/ansi/_pthread.h"

#endif
#define _GNU_SOURCE
//#include <link.h>
#elif defined(__APPLE__)
//#include <dlfcn.h>
#elif defined(ANDROID)

//#include "apex/operating_system/ansios/ansios.h"
//#include "apex/operating_system/android/_.h"

//#elif defined(WINDOWS_DESKTOP)

//#include "apex/operating_system/windows/windows_registry.h"

#endif


#if defined(APPLE_IOS) || defined(UNIVERSAL_WINDOWS)
CLASS_DECL_APEX int ui_open_url(const ::string & psz);
#endif


//extern void * g_pf1;

namespace parallelization
{

   void initialize();


} // namespace parallelization



namespace apex
{


   //void initialize()
   //{


   //}


   application::application()
   {

      //::apex::initialize();

      factory()->add_factory_item < ::apex::system, ::acme::system >();
      factory()->add_factory_item < ::apex::session, ::acme::session >();
      factory()->add_factory_item < ::apex::context, ::acme::context >();

      ::parallelization::initialize();


      m_bEnableAutoStartOption = false;
      //m_bProcessingApplicationExitRequest = false;
      m_papexapplication = this;
      ::object::m_pcontext = this;
      m_pcontext = this;

      //set_layer(LAYERED_APEX, this);


#ifdef LINUX
      m_bSnLauncheeSetup = false;
#endif

      //m_pappParent = nullptr;
      m_bMessageThread = true;
      m_bSimpleMessageLoop = false;
      m_ethreadcontextClose = e_thread_context_none;

      //m_puiMainContainer = nullptr;

      m_bRequiresInstallation = false;
      m_bReadStringTable = true;

      //m_puiCurrent = nullptr;

      //m_bInitializeDataCentral = true;

      m_bInitializeDataCentral = false;

      m_bContextTheme = false;

      m_bAttendedFirstRequest = false;

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

      factory()->add_factory_item < ::networking::application >();


      //m_pevAppBeg = nullptr;
      //m_pevAppEnd = nullptr;

      //m_bAgreeExit = true;
      //m_bAgreeExitOk = true;
      //m_bFranceExit = true;

      m_bLicense = false;

      m_bInterprocessCommunication = false;

      //m_pimaging = nullptr;


      //m_phandler = __new(::handler(this));


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

      srand((u32)::integral_nanosecond());

      m_bService = false;

      m_iResourceId = 8001;

      ::acme::profiler::initialize();

      //m_pdocmanager = nullptr;

      m_eexclusiveinstance = e_exclusive_instance_none;
      m_strLocale = "_std";
      m_strSchema = "_std";

      //m_timeGcomBackgroundUpdate = 30_s;

      //m_pappimpl = memory_new application_impl;


   }


   application::~application()
   {

      //acme::del(m_pappimpl);

   }


   void application::initialize(::particle * pparticle)
   {

      //auto estatus = ::thread::initialize(pparticle);

      ::thread::initialize(pparticle);

      ::acme::application::initialize(pparticle);

      m_pacmesystem = m_pcontext->m_pacmesystem;

      //if (!estatus)
      //{
      //
      //return estatus;
      //
      //}

      //m_pappimpl->initialize(this);
      ///initialize(this OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE);

      //set_context_app(this);

      //m_pcontext = this;

      //if (::is_set(m_pappParent))
      //{

      //   set_context_session(m_pappParent->get_session());

      //   //set_context_system(m_pappParent->psystem);

      //}

      //return estatus;

   }


   //void application::on_initialize_application(::main* pmain)
   //{

   //   pmain->m_psubsystem->factory()->add_factory_item< ::apex::system, ::acme::system >();

   //}



   application_menu & application::applicationmenu()
   {

      if (m_pappmenu.is_null())
      {

         m_pappmenu = __new(application_menu);

      }

      return *m_pappmenu;

   }


   ::file::path application::local_application_path()
   {

      return acmedirectory()->roaming() / "application" / m_strAppName;


   }


   ::file::path application::local_application_home_path()
   {

      return local_application_path() / "home";


   }


   void application::application_menu_update()
   {

#ifdef LINUX

      auto psystem = acmesystem()->m_papexsystem;

      if (acmeapplication()->m_bGtkApp)
      {

         auto pnode = psystem->node();

         if (pnode)
         {

            pnode->set_application_menu(m_pappmenu, this);

         }

      }

#endif

   }


   void application::destroy()
   {

      m_puserlanguagemap.release(OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

      //auto estatus = 
      ::apex::context::destroy();

      //return estatus;

   }


   ::property_object * application::parent_property_set_holder() const
   {

      return nullptr;

   }


   void application::on_change_theme()
   {


   }


   //string application::get_theme()
   //{

   //   return "lite";

   //}


   //bool application::is_set_finish() const
   //{

   //   return ::thread::is_set_finish() || m_ethreadClose != thread_none;

   //}


   void application::set_has_installer(bool bSet)
   {

      m_bAppHasInstallerProtected = bSet;

      m_bAppHasInstallerChangedProtected = true;

   }


   //   void application::show_wait_cursor(bool bShow)
   //   {
   //
   //      auto psystem = acmesystem()->m_papexsystem;
   //
   //      auto papexnode = psystem->m_papexnode;
   //
   //      papexnode->show_wait_cursor(bShow);
   //
   //   }


//   void application::assert_ok() const
//   {
//
//      thread::assert_ok();
//
//   }
//
//
//   void application::dump(dump_context & dumpcontext) const
//   {
//
//      thread::dump(dumpcontext);
//
//      //#ifdef WINDOWS
//      //
//      //      dumpcontext << "m_hinstance = " << (void *)m_hinstance;
//      //
//      //#endif
//
//      //dumpcontext << "\nm_strCmdLine = " << m_strCmdLine;
//      //dumpcontext << "\nm_nCmdShow = " << m_nCmdShow;
//      //dumpcontext << "\nm_bHelpMode = " << m_strAppName;
//
//      //dumpcontext << "\n";
//
//   }


   string application::__get_text(string str)
   {

      if (!m_puserlanguagemap)
      {

         return str;

      }

      return m_puserlanguagemap->__get_text(str);

   }


   //void application::process_command_line(command_line* pcommandline)
   //{
   //
   //
   //}


   //::user::style* application::get_user_style() const
   //{

   //   if (m_psession)
   //   {

   //      return m_psession->get_user_style();

   //   }

   //   return nullptr;

   //}


   //string application::dialog_box(const ::string & pszMatter, property_set & propertyset)
   //{

   //   throw_todo();

   //   return "";

   //}


   void application::install_message_routing(::channel * pchannel)
   {

      ::thread::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CLOSE, pchannel, this, &application::on_message_close);

      add_command_handler("app_exit", { this, &application::on_message_app_exit });
      add_command_handler("switch_context_theme", { this, &application::_001OnSwitchContextTheme });

   }


   //imaging & application::imaging()
   //{

   //   return *m_pimaging;

   //}


   bool application::enable_application_events(::particle * pparticle, bool bEnable)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (bEnable)
      {

         if (pparticle == this)
         {

            return true;

         }

         m_particleaddressaEventHook.add_unique(pparticle);

      }
      else
      {

         m_particleaddressaEventHook.erase(pparticle);

      }

      return true;

   }


   string application::title()
   {

      if (m_textAppTitle.get_text().has_char())
      {

         return m_textAppTitle.get_text();

      }

      string_array stra;

      stra.explode("/", m_strAppName);

      string strTitle;

      if (stra.get_count() > 1)
      {

         strTitle = stra.implode("/", 1);

         if (strTitle.length() > 0)
         {

            return strTitle;

         }

      }

      if (m_strAppName.has_char())
      {

         return m_strAppName;

      }

      stra.explode("/", m_strAppId);

      if (stra.get_count() > 1)
      {

         strTitle = stra.implode("/", 1);

         if (strTitle.length() > 0)
         {

            return strTitle;

         }

      }

      if (m_strAppId.has_char())
      {

         return m_strAppId;

      }

      return file()->module().title();

   }


   string_array application::get_categories()
   {

      return m_straAppCategory;

   }



   //bool application::app_data_set(const ::atom & atom, stream & os)
   //{

   //   return false;

   //}


   //bool application::app_data_get(const ::atom & atom, stream & is)
   //{

   //   return false;

   //}


   bool application::app_data_set(const ::atom & atom, ::object & obj)
   {

      return false;

   }


   bool application::app_data_get(const ::atom & atom, ::object & obj)
   {

      return false;

   }


   //void application::on_request_message(::request * prequest)
   //{

   //   pcreate->m_pcontext = this;

   //   request(pcreate);

   //}


   //void application::call_request(::request * prequest)
   //{

   //   do_request(pcreate);

   //   //auto psystem = acmesystem()->m_papexsystem;

   //   //if (pcreate->m_ecommand == ::command_protocol)
   //   //{

   //   //   string str;
   //   //
   //   //   str = pcreate->m_payloadFile;

   //   //      // apex commented
   //   //      //throw ::exception(todo("interaction"));

   //   //   /*if (!m_pinterprocesscommunication)
   //   //   {

   //   //      ::pointer<::user::interaction>pinteraction;

   //   //      get_frame(pinteraction);

   //   //      if (pinteraction == nullptr)
   //   //      {

   //   //         return error_failed;

   //   //      }

   //   //      auto papp = pinteraction->get_app();

   //   //      if (papp == nullptr)
   //   //      {

   //   //         return error_failed;

   //   //      }

   //   //      if (papp->m_pinterprocesscommunication == nullptr)
   //   //      {

   //   //         return error_failed;

   //   //      }

   //   //   }*/

   //   //   if (str.case_insensitive_begins_eat(m_pinterprocesscommunication->m_prx->m_strBaseChannel))
   //   //   {

   //   //      if (str.case_insensitive_begins_eat(":///"))
   //   //      {

   //   //         if (str.case_insensitive_begins_eat("send?message="))
   //   //         {

   //   //            m_pinterprocesscommunication->on_interprocess_receive(m_pinterprocesscommunication->m_prx, ::url::decode(str));

   //   //         }
   //   //         else if (str.case_insensitive_begins_eat("send?messagebin="))
   //   //         {

   //   //            auto pFind = str.find(',');

   //   //            if (::is_set(pFind))
   //   //            {

   //   //               int message = atoi(str(0, pFind));

   //   //               memory m;

   //   //               pbase64->decode(m, ::url::decode(str(pFind + 1)));

   //   //               m_pinterprocesscommunication->on_interprocess_receive(m_pinterprocesscommunication->m_prx, message, m.get_data(), m.size());

   //   //            }

   //   //         }

   //   //      }

   //   //   }


   //   //}
   //   //else if (pcreate->m_ecommand == ::command_on_agree_exit)
   //   //{

   //   //   m_bAgreeExit = _001OnAgreeExit();

   //   //   m_bAgreeExitOk = true;

   //   //   return ::success;

   //   //}
   //   //else if (pcreate->m_ecommand == ::command_france_exit)
   //   //{

   //   //   _001FranceExit();

   //   //   return ::success;

   //   //}
   //   //else
   //   //{

   //   //   on_request(pcreate);

   //   //}

   //   //return ::success;

   //}


   void application::request(::request * prequest)
   {

      m_prequest = prequest;

      if (is_service())
      {

         on_service_request(prequest);

      }
      else
      {

         try
         {

            on_request(prequest);

         }
         // catch (not_installed * pexception)
         // {

         //    ::exception_pointer esp(pexception);

         //    psystem->on_run_exception(esp);

         //    throw ::exception(exit_exception(esp->get_app(), ::exit_application));

         // }
         catch (const ::exception & e)
         {

            handle_exception(e);

         }

         auto psystem = acmesystem()->m_papexsystem;

         // Verry Sory for the per request overhead here for the needed information of only first request
         if (::is_set(psystem) && psystem->m_timeAfterApplicationFirstRequest <= 0_s)
         {

            psystem->m_timeAfterApplicationFirstRequest = 0_s; // cross your fingers that the first recorded is not 0, it will be cleaned up by other requests.

         }

         try
         {

            prequest->get_property_set().unset("document");

         }
         catch (...)
         {

         }

         m_bAttendedFirstRequest = true;
         //::pointer<::apex::session>pbergedge = pcreate->payload("bergedge_callback").cast < ::apex::session >();
         // todobergedge
         /*if(pbergedge != nullptr)
         {
         pbergedge->on_app_request_bergedge_callback(this);
         }*/
         prequest->m_eventReady.SetEvent();

      }

   }


   //void application::message_box_synchronous(::user::primitive * puiOwner, const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox, ::callback callback)
   //{

   //   return ::message_box_synchronous(puiOwner->get_safe_handle(), pszMessage, pszTitle, emessagebox, callback);

   //}


   //void application::ui_message_box(::user::primitive* puiOwner, const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox, ::callback callback)
   //{

   //   if (!get_session() || !psession->userex())
   //   {

   //      return ::error_failed;

   //   }

   //   return psession->userex()->ui_message_box(this, puiOwner, pszMessage, pszTitle, emessagebox, callback);

   //}


   //void application::ui_message_box_timeout(::user::primitive* puiOwner, const ::string & pszMessage, const ::string & pszTitle, const class time & timeTimeout, const ::e_message_box & emessagebox, ::callback callback)
   //{

   //   if (!get_session() || !psession->userex())
   //   {

   //      return ::error_failed;

   //   }

   //   return psession->userex()->ui_message_box_timeout(this, puiOwner, pszMessage, pszTitle, timeTimeout, emessagebox, callback);

   //}


   //void application::message_box(::user::primitive* puiOwner, const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox, ::callback callback)
   //{

   //   auto estatus = ui_message_box(puiOwner, pszMessage, pszTitle, emessagebox, callback);

   //   if(!estatus)
   //   {

   //      return estatus;

   //   }

   //   return message_box_synchronous(puiOwner, pszMessage, pszTitle, emessagebox, callback);

   //}


   //void application::message_box_timeout(::user::primitive* puiOwner, const ::string & pszMessage, const ::string & pszTitle, const class time & timeTimeout, const ::e_message_box & emessagebox, ::callback callback)
   //{

   //   auto estatus = ui_message_box_timeout(puiOwner, pszMessage, pszTitle, timeTimeout, emessagebox, callback);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return message_box_synchronous(puiOwner, pszMessage, pszTitle, emessagebox, callback);

   //}


   //void application::message_box(const ::payload & payload)
   //{

   //   ::pointer<::user::primitive>puiOwner;

   //   string strMessage;

   //   string strTitle;

   //   u64 uFlags = 0;

   //   ::time timeTimeout;

   //   ::function_arg function;

   //   if (payload.get_type() != e_type_property_set)
   //   {

   //      strMessage = payload;

   //   }
   //   else
   //   {

   //      puiOwner = payload["owner"].cast < ::user::primitive >();
   //      strMessage = payload["message"];
   //      strTitle = payload["title"];
   //      uFlags = payload["flags"];
   //      timeTimeout = payload["time"];
   //      function = payload["function_arg"];

   //   }

   //   if (timeTimeout.is_null())
   //   {

   //      return message_box(puiOwner, strMessage, strTitle, (::u32) uFlags, function);

   //   }
   //   else
   //   {

   //      return message_box_timeout(puiOwner, strMessage, strTitle, timeTimeout, (::u32) uFlags, function);

   //   }

   //}


   //// lang string
   //// load string
   //string application::lstr(const ::atom & atom, string strDefault)
   //{

   //   string str;

   //   if (!load_string(str, atom))
   //   {

   //      if (strDefault.has_char())
   //         return strDefault;

   //      return "";

   //   }

   //   return str;

   //}




   void application::on_file_new()
   {

   }


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


   bool application::load_cached_string_by_id(string & str, const ::atom & atom, bool bLoadStringTable)
   {

      string strId(atom);

      string strTable;

      string strString;

      ::pointer<string_to_string>pmap;

      ::index iFind = 0;

      if ((iFind = strId.find_index(':')) <= 0)
      {

         strTable = "";

         strString = strId;

      }
      else
      {

         strTable = strId(0, iFind);

         strString = strId(iFind + 1);

      }

      synchronous_lock synchronouslock(m_pmutexStr);

      if (m_stringtableStd.lookup(strTable, pmap))
      {

         if (pmap->lookup(strString, str))
         {

            return true;

         }

      }
      else if (m_stringtable.lookup(strTable, pmap))
      {

         if (pmap->lookup(strString, str))
         {

            return true;

         }

      }
      else if (bLoadStringTable)
      {

         synchronouslock.unlock();

         load_string_table(strTable, "");

         return load_cached_string_by_id(str, atom, false);

      }

      return false;

   }


   //void application::load_string_table(const string & pszApp, const string & pszId)
   //{

   //}




   void application::load_string_table()
   {
      load_string_table("", "");
   }





   //object * application::alloc(::type info)
   //{

   //   return psystem->alloc(this, info);

   //}


   //object * application::alloc(const  atom & idType)
   //{

   //   return psystem->alloc(this, idType);

   //}


   bool application::is_system() const
   {

      return false;

   }


   bool application::is_session() const
   {

      return false;

   }


   bool application::is_service() const
   {

      return false;

   }


   bool application::is_user_service() const
   {

      bool bIsUserService = true;

      bool bIsService = is_service();

      return bIsUserService && bIsService;

   }





   bool application::_001OnDDECommand(const ::string & str)
   {

      throw ::interface_only();

      return false;

   }



   void application::_001CloseApplication()
   {

      post_message(MESSAGE_CLOSE, 0, 0);

   }





   void application::get_temp_file_name_template(string & strRet, const ::string & lpszName, const ::string & pszExtension, const ::string & pszTemplate)
   {

      throw ::not_implemented();

      ///return false;

   }


   void application::get_temp_file_name(string & strRet, const ::string & lpszName, const ::string & pszExtension)
   {

      return get_temp_file_name_template(strRet, lpszName, pszExtension, nullptr);

   }


   void application::exit_application()
   {

      try_close_application();

      ///return ::success;

   }


   void application::process_exception(const ::exception & e)
   {

      return ::thread::process_exception(e);

   }


   //bool application::final_handle_exception(const ::exception & e)
   //{

   //   __UNREFERENCED_PARAMETER(pe);

   //   //linux      exit(-1);

   //   if (!is_system())
   //   {

   //      // get_app() may be it self, it is ok...
   //      if (psystem->final_handle_exception(pe))
   //         return true;


   //   }

   //   return false;
   //}


   //   void     application::main()
   //   {
   //
   //
   //      return ::thread::main();
   //
   ////
   ////      INFORMATION("apex::application::main");
   ////
   ////      try
   ////      {
   ////
   ////         m_bReady = true;
   ////
   ////         m_estatus = on_run();
   ////
   //////         if(m_iErrorCode != 0)
   //////         {
   //////
   //////            dappy(__type_name(this) + " : on_run failure : " + as_string(m_iErrorCode));
   //////
   //////            ::output_debug_string("application::main on_run termination failure\n");
   //////
   //////         }
   ////
   ////      }
   ////      catch (const ::exception & e)
   ////      {
   ////
   ////         if (!handle_exception(e))
   ////         {
   ////
   ////
   ////         }
   ////
   ////      }
   ////      catch (...)
   ////      {
   ////
   ////         //dappy(__type_name(this) + " : on_run general exception");
   ////
   ////      }
   ////
   ////      return m_estatus;
   //
   //   }


   void application::init_task()
   {

      try
      {

         pre_run();
         //{

         //   return false;

         //}

      }
      catch (const ::exception & e)
      {

         handle_exception(e);

         acmesession()->set_finish();

         throw e;

      }
      catch (...)
      {

         //      return false;

         throw ::exception(error_exception);

      }

      //return true;

   }


   void application::term_task()
   {

      INFORMATION("apex::application::term_thread");

      m_timeHeartBeat.Now();

      try
      {

         pos_run();

      }
      catch (...)
      {

      }

      ::thread::term_task();

   }


   void application::pre_run()
   {

      INFORMATION("apex::application::pre_run");

      try
      {

         m_timeHeartBeat.Now();

         application_pre_run();

         //{

         //   m_bReady = true;

         //   return false;

         //}

         //    if(!check_install())
         //    {

         //       m_bReady = true;

         //       return false;

         //    }

         //         if(!is_system() && !is_session())
         //         {
         //
         //            if(!is_installed())
         //            {
         //
         //
         //            }
         //
         //         }

         //xxdebug_box("pre_run 1 ok", "pre_run 1 ok", e_message_box_icon_information);

         //auto estatus = 
         on_before_launching();

         //if(!estatus)
         //{

         //   m_bReady = true;

         //   return estatus;

         //}

         m_timeHeartBeat.Now();

         os_native_bergedge_start();
         //{

         //   m_bReady = true;

         //   return false;

         //}

         INFORMATION("apex::application::pre_run success");

         //return true;

      }
      catch (const ::exception & e)
      {

         handle_exception(e);

         throw e;

      }
      catch (...)
      {

         INFORMATION("apex::application::pre_run exception.4");

         throw ::exception(error_exception);

      }

      //return false;

   }


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
   //      //      m_pevAppBeg->SetEvent();
   //
   //      //   }
   //
   //      //}
   //      //catch (...)
   //      //{
   //
   //      //}
   //
   //      //if(::is_set(psystem))
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
   //      //      m_pevAppEnd->SetEvent();
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


   void application::on_pos_run_thread()
   {

      ::thread::on_pos_run_thread();

      synchronous_lock synchronouslock(this->synchronization());

      //try
      //{

      //   for (auto & papp : m_applicationa)
      //   {

      //      try
      //      {

      //         if (papp != this && papp->get_app() == this)
      //         {

      //            set_object(nullptr);

      //         }

      //         if (is_session())
      //         {

      //            ::apex::session * psessionThis = dynamic_cast <::apex::session *>(this);

      //            if (papp->get_session() == psessionThis && papp != this)
      //            {

      //               papp->get_session() = nullptr;

      //            }

      //         }

      //         if (is_system())
      //         {

      //            ::apex::system * psystemThis = dynamic_cast <::apex::system *>(this);

      //            if (papp->psystem == psystemThis && papp != this)
      //            {

      //               papp->psystem = nullptr;

      //            }

      //         }

      //      }
      //      catch (...)
      //      {

      //      }

      //   }

      //}
      //catch (...)
      //{

      //}

   }


   void application::pos_run()
   {

      INFORMATION("apex::application::pos_run");

      try
      {

         m_timeHeartBeat.Now();

         application_pos_run();

         //xxdebug_box("pre_run 1 ok", "pre_run 1 ok", e_message_box_icon_information);

      }
      catch (...)
      {

         INFORMATION("apex::application::pos_run exception.4");

      }

   }


   void application::init_instance()
   {

      ::acme::application::init_instance();

      defer_interprocess_communication();

      if (m_bInterprocessCommunication)
      {

         __raw_construct_new(m_pinterprocesscommunication);
         
         //m_pinterprocesscommunication->m_p= create_interprocess_communication(OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_NOTE("::application::init_instance"));

         m_pinterprocesscommunication->initialize_interprocess_communication(this, m_strAppId);

      }

      INFORMATION("apex::application::init_application .1");

      bool bHandled = false;

#if !defined(ANDROID)

      if (!check_exclusive(bHandled))
      {

         if (!bHandled &&
            (!has_property("install")
               && !has_property("uninstall")))
         {

            class time timeTimeout;

            //#ifdef __DEBUG
            //
            //          timeTimeout = minutes(5);
            //
            //#else //__DEBUG

            timeTimeout = 5_s;

            //#endif //!__DEBUG

            string strMessage;

            strMessage = "Another instance of \"" + m_strAppName + "\" is already running (and some exclusivity policy is active).";

            //          payload["prefix_html"] = "<img src=\"matter://system/exclusive.png\" width=80 height=80 style=\"display:block;\"><br/><br/>";

            //message_box(strMessage, m_strAppName, timeTimeout, e_message_box_icon_asterisk);

            //message_box(strMessage, m_strAppName, e_message_box_icon_asterisk);

            output_debug_string(strMessage + m_strAppName);

            INFORMATION("apex::application::init_application exit");

            throw exit_exception(error_exit_application, this, "Another install of the application is running.");

         }

      }

#endif

      INFORMATION("apex::application::init_application .2");

      if (m_pinterprocesscommunication)
      {

         auto pathModule = file()->module();

         auto processId = m_pcontext->m_papexcontext->os_context()->get_pid();

         m_pinterprocesscommunication->on_new_instance(pathModule, processId);

      }

      //xxdebug_box("check_exclusive ok", "check_exclusive ok", e_message_box_icon_information);

      //if (m_bInitializeDataCentral)
      //{


      //   ::file::path pathDatabase;

      //   ::file::path pathFolder = dir()->appdata();

      //   if (is_system())
      //   {

      //      pathDatabase = pathFolder / "system.sqlite";

      //   }
      //   else if (is_session())
      //   {

      //      pathDatabase = pathFolder / "session.sqlite";

      //   }
      //   else
      //   {

      //      pathDatabase = pathFolder / "app.sqlite";

      //   }

      //   //throw ::exception(todo("database"));

      //   //auto estatus = m_psimpledb->initialize_simpledb_server(this, pathDatabase);

      //   //if (!estatus)
      //   //{

      //   //   m_result.add(estatus);

      //   //   return false;

      //   //}

      //   //set_data_server(m_psimpledb);

      //}

      //m_bAxisInitializeInstanceResult = true;

      INFORMATION("axis::application::init_instance success");

      //auto estatus = 
      create_impact_system();

      //if (failed(estatus))
      //{
      //
      //return false;
      //
      //}


      if (!is_system() && !is_session())
      {

         if (m_pdataserver)
         {

            string str;
            // if system locale has changed (compared to last recorded one by apex)
            // use the system locale
            if (datastream()->get({ "system_locale", true }, str))
            {

               if (str.has_char())
               {

                  if (str != get_locale())
                  {

                     try
                     {

                        datastream()->set({ "system_locale", true }, get_locale());

                        datastream()->set({ "locale", true }, get_locale());

                     }
                     catch (...)
                     {

                     }

                  }

               }

            }
            else
            {

               datastream()->set({ "system_locale", true }, get_locale());

            }

            if (payload("locale").get_count() > 0)
            {

               str = payload("locale").stra()[0];

               datastream()->set({ "system_locale", true }, str);

               datastream()->set({ "locale", true }, str);

               set_locale(str, ::e_source_database);

            }
            else if (payload("lang").get_count() > 0)
            {

               str = payload("lang").stra()[0];

               datastream()->set({ "system_locale", true }, str);

               datastream()->set({ "locale", true }, str);

               set_locale(str, ::e_source_database);

            }
            else if (datastream()->get({ "locale", true }, str))
            {

               if (str.has_char())
               {

                  set_locale(str, ::e_source_database);

               }

            }
            // if system schema has changed (compared to last recorded one by apex)
            // use the system schema
            if (datastream()->get({ "system_schema", true }, str))
            {

               if (str.has_char())
               {

                  if (str != get_schema())
                  {

                     try
                     {

                        datastream()->set({ "system_schema", true }, get_schema());

                        datastream()->set({ "schema", true }, get_schema());

                     }
                     catch (...)
                     {

                     }

                  }

               }

            }
            else
            {

               datastream()->set({ "system_schema", true }, get_schema());

            }

            if (payload("schema").get_count() > 0)
            {

               str = payload("schema").stra()[0];

               datastream()->set({ "system_schema", true }, str);

               datastream()->set({ "schema", true }, str);

               set_schema(str, ::e_source_database);

            }
            else if (datastream()->get({ "schema", true }, str))
            {

               if (str.has_char())
               {

                  set_schema(str, ::e_source_database);

               }

            }

         }

         //data_pulse_change({ "ca2.savings", true }, nullptr);

         auto psystem = acmesystem()->m_papexsystem;

         psystem->appa_load_string_table();

      }
      if (!is_system() && !is_session())
      {

         if (m_pdataserver)
         {
            string str;
            // if system locale has changed (compared to last recorded one by apex)
            // use the system locale
            if (datastream()->get({ "system_locale", true }, str))
            {

               if (str.has_char())
               {

                  if (str != get_locale())
                  {

                     try
                     {

                        datastream()->set({ "system_locale", true }, get_locale());

                        datastream()->set({ "locale", true }, get_locale());

                     }
                     catch (...)
                     {

                     }

                  }

               }

            }
            else
            {

               datastream()->set({ "system_locale", true }, get_locale());

            }

            if (payload("locale").get_count() > 0)
            {

               str = payload("locale").stra()[0];

               datastream()->set({ "system_locale", true }, str);

               datastream()->set({ "locale", true }, str);

               set_locale(str, ::e_source_database);

            }
            else if (payload("lang").get_count() > 0)
            {

               str = payload("lang").stra()[0];

               datastream()->set({ "system_locale", true }, str);

               datastream()->set({ "locale", true }, str);

               set_locale(str, ::e_source_database);

            }
            else if (datastream()->get({ "locale", true }, str))
            {

               if (str.has_char())
               {

                  set_locale(str, ::e_source_database);

               }

            }
            // if system schema has changed (compared to last recorded one by apex)
            // use the system schema
            if (datastream()->get({ "system_schema", true }, str))
            {

               if (str.has_char())
               {

                  if (str != get_schema())
                  {

                     try
                     {

                        datastream()->set({ "system_schema", true }, get_schema());

                        datastream()->set({ "schema", true }, get_schema());

                     }
                     catch (...)
                     {

                     }

                  }

               }

            }
            else
            {

               datastream()->set({ "system_schema", true }, get_schema());

            }

            if (payload("schema").get_count() > 0)
            {

               str = payload("schema").stra()[0];

               datastream()->set({ "system_schema", true }, str);

               datastream()->set({ "schema", true }, str);

               set_schema(str, ::e_source_database);

            }
            else if (datastream()->get({ "schema", true }, str))
            {

               if (str.has_char())
               {

                  set_schema(str, ::e_source_database);

               }

            }

            //data_pulse_change({ "ca2.savings", true }, nullptr);

            auto psystem = acmesystem()->m_papexsystem;

            psystem->appa_load_string_table();

         }
      }
      //return true;

      //acmenode()->m_papexnode->on_start_application(this);

      on_start_application();

   }


   void application::defer_interprocess_communication()
   {


      if (m_bInterprocessCommunication)
      {

         __raw_construct_new(m_pinterprocesscommunication);

         //m_pinterprocesscommunication->m_p= create_interprocess_communication(OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_NOTE("::application::init_instance"));

         m_pinterprocesscommunication->initialize_interprocess_communication(this, m_strAppId);

      }

   }


   void application::on_create_app_shortcut()
   {

#if defined(ANDROID) || defined(WINDOWS) || defined(MACOS) || defined(LINUX)

      acmenode()->m_papexnode->on_create_app_shortcut(this);

#else

      throw todo();

#endif

   }


   void application::create_app_shortcut()
   {

      acmenode()->create_app_shortcut(this);

   }


   void application::term_instance()
   {


   }


   //void application::TermApplication()
   //{
   //
   //
   //}


   void application::application_pre_run()
   {
      //
      //INFORMATION("apex::application::application_pre_run");
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //MSG msg;
      //
      //// Create Windows Message Queue
      //::PeekMessageA(&msg, nullptr, 0, 0xffff, 0);
      //
      //MESSAGE message;
      //
      //copy(message, msg);
      //
      //auto psystem = acmesystem()->m_papexsystem;
      //
      //if (!is_system() && is_true("SessionSynchronizedInput"))
      //{
      //
      //::AttachThreadInput(GetCurrentThreadId(), (u32)psystem->get_itask(), true);
      //
      //}
      //
      //#endif

      m_timeHeartBeat.Now();

      //try
      //{
      //
      //if (!InitApplication())
      //{
      //
      //return false;
      //
      //}
      //
      //}
      //catch (::exit_exception * pe)
      //{
      //
      //throw pe;
      //
      //}
      //catch (const ::exception * pe)
      //{
      //
      ////thisexc << 1 << m_iErrorCode;
      //
      //::acme::del(pe);
      //
      //return false;
      //
      //}
      //catch (...)
      //{
      //
      ////thisexcall << 1 << m_iErrorCode;
      //
      //return false;
      //
      //}

      m_timeHeartBeat.Now();

      //::e_status estatus = ::success;

      try
      {

         //estatus = 

         process_init();

         //if(!estatus)
         //{
         //
         //return false;
         //
         //}

      }
      catch (::exit_exception * pe)
      {

         throw pe;

      }
      catch (const ::exception * pe)
      {

         ::acme::del(pe);

         //return false;

      }
      catch (...)
      {

         //return false;

      }

      //auto psystem = acmesystem()->m_papexsystem;

      //      auto psystem = acmesystem();
      //
      //      psystem->install_progress_add_up();

      m_timeHeartBeat.Now();

      try
      {

         //if (!init_application())
         init_application();
         //{
         //
         //return false;
         //
         //}

      }
      catch (const ::exception & e)
      {

         handle_exception(e);

         message_box_synchronous(this, "Application failed to initialize (1).\n\n" + e.m_strMessage, m_strAppName, e_message_box_ok, e.m_strMessage + "\n" + e.m_strDetails);

         throw e;

      }
      catch (...)
      {

         message_box_synchronous(this, "Application failed to initialize (2). Unknown exception", m_strAppName);

         throw "Unknown exception";

      }

      m_timeHeartBeat.Now();

      try
      {

         auto psystem = acmesystem();

         //if (!is_system() && !is_session())
         {

            if (psystem->is_true("uninstall"))
            {

               do_uninstall();

               //return false;

            }
            else if (psystem->is_true("install"))
            {

               do_install();

               //return false;

            }

         }

         init_instance();

         //if (!init_instance())
         //{
         //
         ////return false;
         //
         //}

         //on_update_matter_locator();

      }
      catch (const ::exit_exception & exception)
      {

         throw exception;

      }
      catch (const ::exception & exception)
      {

         message_box_synchronous(this, "Application failed to initialize (4). Unknown exception", m_strAppName, e_message_box_ok,
            exception.m_strMessage + "\n\n" + exception.m_strDetails + "\n\n" + exception.m_strCallstack);

         throw exception;

      }
      catch (...)
      {

         message_box_synchronous(this, "Application failed to initialize (4). Unknown exception", m_strAppName);

         throw "Unknown exception";

      }

      //return true;

   }


   void application::application_pos_run()
   {

      try
      {

         //if (!is_installing() && !is_unstalling())
         {

            term_instance();

         }

      }
      catch (...)
      {

      }

      try
      {

         term_application();

      }
      catch (...)
      {

      }

      m_timeHeartBeat.Now();

      try
      {

         process_term();

      }
      catch (...)
      {

      }

      //try
      //{
      //
      //TermApplication();
      //
      //}
      //catch (...)
      //{
      //
      //}



   }

   //bool application::InitApplication()
   //{
   //
   //   LoadSysPolicies();
   //
   //return true;
   //
   //}



   void application::do_install()
   {

      auto psystem = acmesystem()->m_papexsystem;

      //if (!on_install())
      on_install();
      //{

      //   ::output_debug_string("Failed at on_install : " + m_strAppId + "\n\n");

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

      string strLicense = get_license_id();

      //::payload & varTopicQuey = psystem->m_varTopicQuery;

      auto psystem = acmesystem()->m_papexsystem;

      bool bHasInstall = psystem->is_true("install");

      bool bHasUninstall = psystem->is_true("uninstall");

      if (!(bHasInstall || bHasUninstall)
         && m_bLicense
         && strLicense.has_char())
      {

         assert_user_logged_in();
         //if (!assert_user_logged_in())
         //{

         //   //return false;

         //}

         // call application's is_licensed function
         // because if delay is needed for authentication -
         // or either asking for authentication -
         // current application startup won't be
         // exited by timeout.

         i32 iRetry = 1;

         auto psession = acmesession()->m_papexsession;

      retry_license:

         iRetry--;

         if (!psession->is_licensed(strLicense))
         {

            if (iRetry > 0)
            {

               goto retry_license;

            }

            //return false;

         }

      }

      INFORMATION("initial_check_directrix : ok (" << __type_name(this) << ")" << m_strAppId);

      //return true;

   }



   void application::do_uninstall()
   {

      on_uninstall();

      //if (!on_uninstall())
      //{
      //
      //return false;
      //
      ////         psystem->install().erase_spa_start(m_strAppId);
      //
      //}
      //
      //return true;

   }


   void application::on_install()
   {

      if (is_service())
      {

         //auto estatus = enable_service();
         enable_service();

         //if (!estatus)
         //{
         //
         //return estatus;
         //
         //}
         //return estatus;

      }
      else
      {

         // #ifdef WINDOWS_DESKTOP

         // acmesystem()->m_pnode->install_crash_dump_reporting(file()->module().name());

         // #endif

      }

      //return ::success;

   }


   void application::on_uninstall()
   {

      //bool bOk = axis::application::on_uninstall();

      bool bOk = true;


      if (is_service())
      {

         //auto estatus = 
         disable_service();

         //if(!estatus)
         //{
         //
         //return estatus;
         //
         //}
         //
         //return estatus;

      }

      //return bOk;

   }




   bool application::system_add_app_install(const ::string & pszId, const ::string & pszBuild)
   {

      // cool install

      string strBuild(pszBuild);

      if (strBuild.is_empty())
      {

         strBuild = "0000-00-00 00:00:00";

      }

      auto psystem = acmesystem()->m_papexsystem;

      synchronous_lock synchronouslock(psystem->m_pmutexSystemAppData);

      string strId(pszId);
      string strSystemLocale = psystem->m_strLocale;
      string strSystemSchema = psystem->m_strSchema;
      string_array straLocale;
      string_array straSchema;

      straLocale = payload("locale").stra();
      straSchema = payload("schema").stra();

      ::file::path pathExe = acmefile()->module();

      straLocale.insert_at(0, strSystemLocale);
      straSchema.insert_at(0, strSystemSchema);
      straLocale.insert_at(0, "_std");
      straSchema.insert_at(0, "_std");


      for (index i = 0; i < straLocale.get_count() && i < straSchema.get_count(); i++)
      {

         string strLocale = straLocale[i];

         string strSchema = straSchema[i];

         acmesystem()->m_pacmenode->m_papexnode->set_application_installed(pathExe, strId, strBuild, psystem->get_system_platform(), psystem->get_system_configuration(), strLocale, strSchema);

      }

      //psystem->install().erase_spa_start(strId);
      //psystem->install().add_app_install(strId, strBuild, strSystemLocale, m_strSchema);
      //psystem->install().add_app_install(strId, strBuild, strSystemLocale, strSystemSchema);
      //psystem->install().add_app_install(strId, strBuild, m_strLocale, m_strSchema);

      //for (index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      //{

      //   psystem->install().add_app_install(strId, strBuild, straLocale[iLocale], m_strSchema);

      //}

      //for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      //{

      //   psystem->install().add_app_install(strId, strBuild, m_strLocale, straSchema[iSchema]);

      //}

      //for (index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      //{

      //   for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      //   {

      //      psystem->install().add_app_install(strId, strBuild, straLocale[iLocale], straSchema[iSchema]);

      //   }

      //}

      //psystem->install().add_app_install(strId, strBuild, strSystemLocale, "");
      //psystem->install().add_app_install(strId, strBuild, m_strLocale, "");

      //for (index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      //{

      //   psystem->install().add_app_install(strId, strBuild, straLocale[iLocale], "");

      //}

      //psystem->install().add_app_install(strId, strBuild, "", m_strSchema);
      //psystem->install().add_app_install(strId, strBuild, "", strSystemSchema);

      //for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      //{

      //   psystem->install().add_app_install(strId, strBuild, "", straSchema[iSchema]);

      //}

      //psystem->install().add_app_install(strId, strBuild, "", "");

      return true;

   }


   void application::os_native_bergedge_start()
   {

      //return true;

   }


   bool application::on_application_menu_action(const ::string & pszCommand)
   {

      return false;

   }


   void application::run()
   {

      return ::thread::run();

   }


   ::pointer<::service>application::create_service()
   {

      return nullptr;

   }


   void application::process_init()
   {

      string_array stra;

      stra.explode("/", m_strAppId);

      m_strRoot = stra[0];

      m_strDomain = stra.slice(1).implode("/");

      add_matter_locator(this);

      auto psystem = acmesystem()->m_papexsystem;

      if (!m_bAppHasInstallerChangedProtected)
      {

#ifdef UNIVERSAL_WINDOWS

         set_has_installer(false);

#else

         //if (psystem->m_pappcore == nullptr)
         //{

         //   set_has_installer(false);

         //}
         //else
 /*        {

            set_has_installer(!psystem->has_apex_application_factory());

         }*/

#endif

      }

      //auto estatus = initialize_context();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //if (m_bAuraProcessInitialize)
      //{

      //   return m_bAuraProcessInitializeResult;

      //}

      INFORMATION("apex::application::process_init");

      m_bThreadToolsForIncreasedFps = psystem->m_bThreadToolsForIncreasedFps;

      if (::get_task() == nullptr)
      {

         ::set_task(dynamic_cast <task *> (this));

      }

      notify_process_init();

      //if (!notify_process_init())
      //{
      //
      //FATAL("apex::application::process_init .1");
      //
      //return false;
      //
      //}

      //if (!impl_process_init())
      //{

      //   FATAL("apex::application::process_init .2");

      //   return false;

      //}

      //      m_bAuraProcessInitializeResult = true;

      INFORMATION("apex::application::process_init success");

      //add_factory_item < ::database::field_array >();
      //add_factory_item < ::database::row >();
      //add_factory_item < ::database::row_array >();

      //if (m_bAxisProcessInitialize)
      //{

      //   return m_bAxisProcessInitializeResult;

      //}

      INFORMATION("axis::application::process_init");

      //m_bAxisProcessInitialize = true;

      //m_bAxisProcessInitializeResult = false;

      //if (m_psimpledb.is_null())
      //{

      //   __construct_new(m_psimpledb);

      //}

      //if (!::application::process_init())
      //{

      //   FATAL("axis::application::process_init .1");

      //   return false;

      //}


      //m_bAxisProcessInitializeResult = true;

      INFORMATION("axis::application::process_init success");

      //return true;

      //auto estatus =

      userfs_process_init();

      //if()
      //{
      //
      //ERROR(".2");
      //
      //return false;
      //
      //}

      INFORMATION("success");

      //return true;

      initialize_context();


   }


   void application::process_term()
   {


      if (::is_set(acmesession()))
      {

         acmesession()->m_papexsession->post_message(e_message_erase_application, 0, this);

      }


      try
      {

         notify_process_term();

      }
      catch (...)
      {

      }

      try
      {

         release_exclusive();

      }
      catch (...)
      {

      }

      auto psystem = acmesystem()->m_papexsystem;
      try
      {


         if (psystem != nullptr)
         {

            psystem->check_exit();

         }


      }
      catch (...)
      {

      }

      try
      {

         m_stringtable.erase_all();

         m_stringtableStd.erase_all();

      }
      catch (...)
      {

      }

   }


   void application::init_application()
   {

      auto psystem = acmesystem()->m_papexsystem;

      INFORMATION("apex::application::init_application");

      m_timeHeartBeat.Now();

      init1();

      //if (!init1())
      //{
      //
      ////dappy(__type_name(this) + " : init1 failure : " + as_string(m_iErrorCode));
      //
      //return false;
      //
      //}

      psystem->install_progress_add_up(); // 2

      //xxdebug_box("init1 ok", "init1 ok", e_message_box_icon_information);

      m_timeHeartBeat.Now();

      init2();

      //if (!init2())
      //{
      //
      ////dappy(__type_name(this) + " : init2 failure : " + as_string(m_iErrorCode));
      //
      //return false;
      //
      //}

      psystem->install_progress_add_up(); // 3

      //xxdebug_box("init2 ok", "init2 ok", e_message_box_icon_information);

      m_timeHeartBeat.Now();

      init3();

      //if (!init3())
      //{
      //
      ////dappy(__type_name(this) + " : init3 failure : " + as_string(m_iErrorCode));
      //
      //return false;
      //
      //}

      psystem->install_progress_add_up(); // 4

      //xxdebug_box("init3 ok", "init3 ok", e_message_box_icon_information);

      m_timeHeartBeat.Now();

      //dappy(__type_name(this) + " : init3 ok : " + as_string(m_iErrorCode));

      //try
      //{

      init();
      //{
      //
      ////dappy(__type_name(this) + " : initialize failure : " + as_string(m_iErrorCode));
      //
      //return false;
      //
      //}
      //
      //}
      //catch (const ::string & psz)
      //{
      //
      //if (!strcmp(psz, "You have not logged in! Exiting!"))
      //{
      //
      //return false;
      //
      //}
      //
      //return false;

      //}

      psystem->install_progress_add_up(); // 5

      //      m_bAuraInitializeInstanceResult = true;

      //return true;

   }


   //::pointer<::interprocess::channel> application::create_interprocess_channel()
   //{

   //   try
   //   {

   //      return __new(::interprocess::channel());

   //   }
   //   catch (...)
   //   {

   //      return nullptr;

   //   }

   //}


   void application::init1()
   {


      initialize_context_1();

      //auto estatus = 

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto psystem = acmesystem()->m_papexsystem;

      //estatus = 
      m_puserlanguagemap = __new(::user::language_map OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_NOTE("::application::init1"));

      //if (!estatus)
      //{

      //   return estatus;

      //}

      if (psystem)
      {

         if (psystem->m_pintstringLanguageResourceMap != nullptr)
         {

            m_puserlanguagemap->set_language_resource_map(psystem->m_pintstringLanguageResourceMap);

         }

      }

      if (m_bLocalization)
      {

         string strLang = psystem->get_user_language();

         if (!m_puserlanguagemap->set_language(this, strLang))
         {

            m_puserlanguagemap->set_default_language(this);

         }

      }

      m_timeHeartBeat.Now();

      notify_init1();
      //if (!notify_init1())
      /*{

         return ::error_failed;

      }*/

      if (acmeapplication()->m_bLocalization)
      {

         string strLocale;

         string strSchema;

         //if (psystem->get_user_language().has_char())
         //{

         m_strLocale = psystem->get_user_language();

         m_strSchema = m_strLocale;

         //}

         if (strLocale.is_empty())
         {

            strLocale = "_std";

         }

         if (strSchema.is_empty())
         {

            strSchema = strLocale;

         }

         if (psystem->payload("locale").get_count() > 0)
         {

            strLocale = psystem->payload("locale").stra()[0];

         }

         if (psystem->payload("schema").get_count() > 0)
         {

            strSchema = psystem->payload("schema").stra()[0];

         }

         if (get_app()->payload("locale").get_count() > 0)
         {

            strLocale = get_app()->payload("locale").stra()[0];

         }

         if (get_app()->payload("schema").get_count() > 0)
         {

            strSchema = get_app()->payload("schema").stra()[0];

         }

         set_locale(strLocale, ::e_source_database);

         set_schema(strSchema, ::e_source_database);

      }

      //if (!initialize_contextualized_theme())
      initialize_contextualized_theme();
      //{

      //   FATAL("Failed to initialize_contextualized_theme");

      //   return false;

      //}

      INFORMATION("start");

      m_timeHeartBeat.Now();

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
      catch (...)
      {

      }

   }

   void application::init2()
   {

      //if (!impl_init2())
      //{

      //   return false;

      //}

      notify_init2();

      //if (!notify_init2())
      //{
      //
      //return false;
      //
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
      catch (...)
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
      //
      //return false;
      //
      //}
      //
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
      catch (...)
      {

      }

   }


   void application::term_application()
   {

      try
      {

         close(::apex::e_end_app);

      }
      catch (...)
      {

      }

      release_exclusive();

      try
      {

         try
         {

            m_pinterprocesscommunication.release();

         }
         catch (...)
         {

         }

         try
         {

            term();

         }
         catch (...)
         {


         }

         try
         {

            term3();

         }
         catch (...)
         {


         }

         try
         {

            term2();

         }
         catch (...)
         {


         }

         try
         {

            term1();

         }
         catch (...)
         {


         }


      }
      catch (...)
      {

      }

   }


   //::pointer<::acme::exclusive>application_impl::get_exclusive(string strId ARG_SEC_ATTRS)
   //{

   //   auto & pexclusive = m_mapExclusive[strId];

   //   if (!pexclusive)
   //   {

   //      auto pexclusiveNew = acmenode()->get_exclusive(this, strId ADD_PARAM_SEC_ATTRS);

   //      pexclusive = pexclusiveNew;

   //   }

   //   return pexclusive;

   //}


   //bool application_impl::erase_exclusive(string strId ARG_SEC_ATTRS)
   //{

   //   auto & pexclusive = m_mapExclusive[strId];

   //   if (!pexclusive)
   //   {

   //      return true;

   //   }

   //   pexclusive.release();

   //   m_mapExclusive.erase_key(strId);

   //   return true;

   //}


   //bool application::exclusive_fails(string strId ARG_SEC_ATTRS)
   //{

   //   auto pexclusive = m_pappimpl->get_exclusive(strId ADD_PARAM_SEC_ATTRS);

   //   if (!pexclusive)
   //   {

   //      return false;

   //   }

   //   return pexclusive->exclusive_fails();

   //}


   //bool application::exclusive_erase(string strId ARG_SEC_ATTRS)
   //{

   //   if (!m_pappimpl->erase_exclusive(strId ADD_PARAM_SEC_ATTRS))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   bool application::check_exclusive(bool & bHandled)
   {

#ifdef UNIVERSAL_WINDOWS

      return true;

#endif

      bool bResourceException = false;

      auto psystem = acmesystem();

      auto pnode = psystem->node();

      memory memorySecurityAttributes;

      auto psecurityattributes = pnode->get_application_exclusivity_security_attributes();

      bool bGlobalExclusiveFail = exclusive_fails(get_global_mutex_name(), psecurityattributes);

      if (bGlobalExclusiveFail && m_eexclusiveinstance == e_exclusive_instance_global)
      {

         INFORMATION("A instance of the application:<br><br> - " << m_strAppName << +"<br><br>seems to be already running at the same machine<br>Only one instance of this application can run globally: at the same machine.<br><br>Exiting this memory_new instance.");

         try
         {

            on_exclusive_instance_conflict(bHandled, e_exclusive_instance_global, "");
            //{

            //   return false;

            //}

         }
         catch (...)
         {

            return false;

         }

      }

      if (m_eexclusiveinstance == e_exclusive_instance_global_id)
      {

         bool bGlobalIdExclusiveFail = exclusive_fails(get_global_id_mutex_name(), psecurityattributes);

         if (bGlobalIdExclusiveFail)
         {

            INFORMATION("A instance of the application:<br><br>-" << m_strAppName << "with the atom \"" << get_local_mutex_id() << "\" <br><br>seems to be already running at the same machine<br>Only one instance of this application can run globally: at the same machine with the same atom.<br><br>Exiting this memory_new instance.");

            try
            {

               on_exclusive_instance_conflict(bHandled, e_exclusive_instance_global_id, get_global_mutex_id());

            }
            catch (...)
            {

               return false;

            }

         }

      }

      bool bLocalExclusiveFail = exclusive_fails(get_local_mutex_name(), psecurityattributes);

      if (bLocalExclusiveFail && m_eexclusiveinstance == e_exclusive_instance_local)
      {

         INFORMATION("A instance of the application:<br><br>-" << m_strAppName << "<br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same account.<br><br>Exiting this memory_new instance.");

         on_exclusive_instance_conflict(bHandled, e_exclusive_instance_local, "");

         return false;

      }

      if (m_eexclusiveinstance == e_exclusive_instance_local_id)
      {

         bool bLocalIdExclusiveFail = exclusive_fails(get_local_id_mutex_name(), psecurityattributes);

         if (bLocalIdExclusiveFail)
         {

            try
            {

               // Should in some way activate the other instance
               INFORMATION("A instance of the application:<br><br> - " << m_strAppName << " with the atom \"" << get_local_mutex_id() << "\" <br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same ac::count with the same atom.<br><br>Exiting this memory_new instance.");

               on_exclusive_instance_conflict(bHandled, e_exclusive_instance_local_id, get_local_mutex_id());
               //if(!)
               //{

               //   return false;

               //}

            }
            catch (...)
            {

               return false;

            }

         }

      }

      return true;

   }


   bool application::erase_exclusive(const ::string & strId)
   {

      auto psecurityattributes = acmenode()->get_application_exclusivity_security_attributes();

      bool bErased = exclusive_erase(strId);

      return true;

   }


   void application::notify_process_init()
   {

      ::message::application message(::message::application_process_init);

      route_message(&message);

      //return true;

   }


   void application::notify_init1()
   {

      ::message::application message(::message::application_init1);

      route_message(&message);

      //return message.m_bOk;false

   }


   void application::notify_init2()
   {

      ::message::application message(::message::application_init2);

      route_message(&message);

      //return message.m_bOk;

   }


   void application::notify_init3()
   {

      ::message::application message(::message::application_init3);

      route_message(&message);

      //return message.m_bOk;

   }




   void application::notify_term3()
   {

      ::message::application message(::message::application_init3);

      route_message(&message);

      //      if (!message.m_bOk)
      //         return false;
      //
      //      return true;

   }


   void application::notify_term2()
   {

      ::message::application message(::message::application_term2);

      route_message(&message);

   }


   void application::notify_term1()
   {

      ::message::application message(::message::application_term1);

      try
      {

         route_message(&message);

      }
      catch (...)
      {

      }

      //return message.m_bOk;

   }


   void application::notify_process_term()
   {

      ::message::application message(::message::application_process_term);

      route_message(&message);

      //return message.m_bOk;

   }







   string application::get_local_mutex_name()
   {

      return acmesystem()->m_pnode->get_local_mutex_name(get_mutex_name_gen());

   }


   string application::get_local_id_mutex_name()
   {

      return acmesystem()->m_pnode->get_local_id_mutex_name(get_mutex_name_gen(), get_local_mutex_id());

   }


   string application::get_global_mutex_name()
   {

      return acmesystem()->m_pnode->get_global_mutex_name(get_mutex_name_gen());

   }


   string application::get_global_id_mutex_name()
   {

      return acmesystem()->m_pnode->get_global_id_mutex_name(get_mutex_name_gen(), get_global_mutex_id());

   }


   void application::on_exclusive_instance_conflict(bool & bHandled, enum_exclusive_instance eexclusive, string strId)
   {

      if (eexclusive == e_exclusive_instance_local)
      {

         return on_exclusive_instance_local_conflict(bHandled);

      }
      else if (eexclusive == e_exclusive_instance_local_id)
      {

         return on_exclusive_instance_local_conflict_id(bHandled, strId);

      }

      //return false;

   }


   void application::on_exclusive_instance_local_conflict(bool & bHandled)
   {

      bool bContinue = false;

      try
      {

         auto psystem = acmesystem()->m_papexsystem;

         if (m_pinterprocesscommunication)
         {

            auto pcall = m_pinterprocesscommunication->create_call("application", "on_additional_local_instance");

            (*pcall)["module"] = file()->module();

            (*pcall)["pid"] = m_pcontext->m_papexcontext->os_context()->get_pid();

            (*pcall)["command_line"] = psystem->command_line_text();

            //string strId;

            //pcall->add_parameter(strId);

            pcall->send_call();

            for (auto & pair : pcall->m_mapTask)
            {

               auto & pinterprocesstask = pair.element2();

               if (bContinue && pinterprocesstask->m_tristateContinue.is_set())
               {

                  bContinue = pinterprocesstask->m_tristateContinue;

               }

               if (!bHandled && pinterprocesstask->m_tristateHandled.is_set())
               {

                  bHandled = pinterprocesstask->m_tristateHandled.is_true();

               }

            }

         }

      }
      catch (...)
      {

      }

      //return bContinue;

   }


   void application::on_exclusive_instance_local_conflict_id(bool & bHandled, string strId)
   {

      //bool bContinue = false;
      auto psystem = acmesystem()->m_papexsystem;
      try
      {

         if (m_pinterprocesscommunication)
         {

            auto pcall = m_pinterprocesscommunication->create_call("application", "on_additional_local_instance");

            (*pcall)["module"] = file()->module();

            (*pcall)["pid"] = m_pcontext->m_papexcontext->os_context()->get_pid();

            (*pcall)["command_line"] = psystem->command_line_text();

            (*pcall)["id"] = strId;

            for (auto & ptask : pcall->m_mapTask.payloads())
            {

               if (!bHandled)
               {

                  bHandled = ptask->m_tristateHandled.is_true();

                  //if (bHandled)
                  //{

                     //bContinue = ptask->m_tristateContinue.is_true();

                  //}

               }

            }

         }

      }
      catch (...)
      {

      }

      //return bContinue;

   }


   void application::on_additional_local_instance(bool & bHandled, string strModule, int iPid, string strCommandLine)
   {

      auto prequest = __create_new < ::request >();

      prequest->initialize_command_line2(strCommandLine);

      post_request(prequest);

      bHandled = true;

      //return false;

   }


   void application::on_new_instance(string strModule, const ::atom & iPid)
   {

   }


   //string application::get_mutex_name_gen()
   //{
   //   return m_strAppName;
   //}


   string application::get_local_mutex_id()
   {

      string str;

      str = payload("local_mutex_id");

      return str;

   }


   string application::get_global_mutex_id()
   {

      string str;

      str = payload("global_mutex_id");

      return str;

   }


   bool application::Ex2OnAppInstall()
   {

      return true;

   }


   bool application::Ex2OnAppUninstall()
   {

      return true;

   }


   bool application::on_set_scalar(enum_scalar escalar, ::number number, int iFlags)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   m_iProgressInstallStep = iValue;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   m_iProgressInstallStart = iValue;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   m_iProgressInstallEnd = iValue;

      //}
      //else
      {

         //return ::int_scalar_source::on_set_scalar(escalar, iValue, iFlags);

      }

      return false;

   }


   ::number application::get_scalar_minimum(enum_scalar escalar)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   i = m_iProgressInstallStart;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = 0;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = 0;

      //}
      //else
      {

         //::int_scalar_source::get_scalar_minimum(escalar, i);

      }

      return e_number_none;

   }


   ::number application::get_scalar(enum_scalar escalar)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   i = m_iProgressInstallStep;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = m_iProgressInstallStart;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = m_iProgressInstallEnd;

      //}
      //else
      {

         //::int_scalar_source::get_scalar(escalar, i);

      }

      return e_number_none;

   }


   ::number application::get_scalar_maximum(enum_scalar escalar)
   {

      //if (escalar == scalar_download_size)
      //{

      //   i = m_iProgressInstallEnd;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = 0x7fffffff;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = 0x7fffffff;

      //}
      //else
      {

         //::int_scalar_source::get_scalar_minimum(escalar, i);

      }

      return e_number_none;

   }


   //i32 application::sync_message_box_timeout(::user::primitive * puserinteractionOwner, ::payload payload, const ::string & pszTitle, ::time timeTimeOut, ::u32 fuStyle)
   //{

   //   __UNREFERENCED_PARAMETER(timeTimeOut);

   //   return sync_message_box(puserinteractionOwner, payload, pszTitle, fuStyle);

   //}






   string application::http_get_locale_schema(const ::string & pszUrl, const ::string & pszLocale, const ::string & pszSchema)
   {

      throw ::interface_only();

      return "";

   }


   void application::message_handler(::message::message * pmessage)
   {

      ::thread::message_handler(pmessage);

      //return false;

   }


   void application::set_locale(const string & pcsz, const ::action_context & context)
   {

      string strLocale(pcsz);


      strLocale.trim();

      m_strLocale = strLocale;

      on_set_locale(m_strLocale, context);

   }


   void application::set_schema(const string & pcsz, const ::action_context & context)

   {

      string strSchema(pcsz);


      strSchema.trim();

      m_strSchema = strSchema;

      on_set_schema(m_strSchema, context);

   }


   void application::on_set_locale(const string & pcsz, const ::action_context & context)

   {
      __UNREFERENCED_PARAMETER(context);
      __UNREFERENCED_PARAMETER(pcsz);

      //psystem->appa_load_string_table();
   }


   void application::on_set_schema(const string & pcsz, const ::action_context & context)

   {
      __UNREFERENCED_PARAMETER(context);
      __UNREFERENCED_PARAMETER(pcsz);

      //psystem->appa_load_string_table();
   }





   string application::get_locale_schema_dir()
   {

      return _001Concatenate(get_locale(), "/", get_schema());

   }


   string application::get_locale_schema_dir(const ::string & strLocale)
   {

      return _001Concatenate(strLocale.is_empty() ? get_locale() : strLocale, "/", get_schema());

   }


   void application::matter_locator_locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema)
   {

      if (strLocale.is_empty() || strSchema.is_empty())
      {

         return;

      }

      for (auto & strMatterLocator : straMatterLocator)
      {

         string strLs = get_locale_schema_dir(strLocale, strSchema);

         stra.add_unique(::file::path(strMatterLocator) / strLs);

      }

   }


   void application::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema)
   {

      if (straMatterLocator.has_elements())
      {

         stra.add_unique(::file::path(straMatterLocator.first()) / get_locale_schema_dir("map", "map"));

      }

      matter_locator_locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

      auto psession = acmesession();

      auto ptextcontext = psession->text_context();

      for (i32 i = 0; i < ptextcontext->localeschema().m_idaLocale.get_count(); i++)
      {

         string strLocale = ptextcontext->localeschema().m_idaLocale[i];

         string strSchema = ptextcontext->localeschema().m_idaSchema[i];

         matter_locator_locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

      }

      matter_locator_locale_schema_matter(stra, straMatterLocator, "en", "en");

      matter_locator_locale_schema_matter(stra, straMatterLocator, "_std", "_std");

      if (straMatterLocator.has_elements())
      {

         stra.add_unique(::file::path(straMatterLocator.first()) / get_locale_schema_dir("404", "404"));

      }

   }


   string application::get_locale_schema_dir(const ::string & strLocale, const ::string & strSchema)
   {

      return _001Concatenate(strLocale, "/", strSchema);

   }


   void application::fill_locale_schema(::text::international::locale_schema & localeschema, const string & pszLocale, const string & pszSchema)
   {

      localeschema.m_idaLocale.erase_all();
      localeschema.m_idaSchema.erase_all();


      string strLocale(pszLocale);
      string strSchema(pszSchema);


      localeschema.m_atomLocale = pszLocale;
      localeschema.m_atomSchema = pszSchema;


      localeschema.add_locale_variant(strLocale, strSchema);
      localeschema.add_locale_variant(get_locale(), strSchema);
      localeschema.add_locale_variant("std", strSchema);
      localeschema.add_locale_variant("en", strSchema);

      localeschema.destroy();

   }


   void application::fill_locale_schema(::text::international::locale_schema & localeschema)
   {


      localeschema.m_idaLocale.erase_all();
      localeschema.m_idaSchema.erase_all();


      //localeschema.m_bAddAlternateStyle = true;


      string_array straLocale;
      string_array straSchema;

      straLocale.add(get_locale());
      straSchema.add(get_schema());


      string_array stra;

      stra = payload("locale").stra();

      stra.erase_ci("_std");

      straLocale.append_unique(payload("locale").stra());

      stra.empty();

      stra = payload("schema").stra();

      stra.erase_ci("_std");

      straSchema.append_unique(payload("schema").stra());

      localeschema.m_atomLocale = straLocale[0];
      localeschema.m_atomSchema = straSchema[0];

      for (index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      {

         for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
         {

            localeschema.add_locale_variant(straLocale[iLocale], straSchema[iSchema]);

         }

      }

      for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(get_locale(), straSchema[iSchema]);

      }

      for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant("std", straSchema[iSchema]);

      }


      for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant("en", straSchema[iSchema]);

      }

      localeschema.destroy();

   }


   bool application::platform_open_by_file_extension(index iEdge, const ::string & pszPathName, ::request * prequest)
   {

      return false;

   }


   bool application::platform_open_by_file_extension(index iEdge, ::request * prequest)
   {

      return false;

   }




   //i32 application::hotplugin_host_starter_start_sync(const ::string & pszCommandLine, ::apex::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin)
   //{

   //   return -1;

   //}


   bool application::is_application() const
   {

      return !is_session() && !is_system();

   }



   //bool application::_001OnAgreeExit()
   //{

   //   return true;

   //}


   //void application::france_exit()
   //{
   //
   //   HideApplication();
   //
   //   finish();
   //
   //   return ::success;
   //
   //}


   //void application::_001FranceExit()
   //{
   //
   //france_exit();
   //
   //m_bFranceExit = true;
   //
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

   void application::post_critical_error_message(const ::string & pszMessage, bool bShowLog)
   {

      string strMessage;

      auto psystem = acmesystem();

      auto pdatetime = psystem->m_pdatetime;

      strMessage = pdatetime->international().get_date_time();
      strMessage += " ";
      strMessage += pszMessage;
      strMessage += "\n";

      {

         synchronous_lock synchronouslock(this->synchronization());

         file()->add_contents(dir()->appdata() / (file()->module().name() + "_log_error.txt"), strMessage);

      }

      if (bShowLog)
      {

         show_critical_error_log();

      }

   }


   string application::get_app_user_friendly_task_bar_name()
   {

      ::file::path path = m_strAppName;

      string strTitle = path.title();

      return strTitle;

   }



   void application::show_critical_error_log()
   {

      static int g_iCount = 0;

      string strFile = dir()->appdata() / (file()->module().name() + "_log_error.txt");

      g_iCount++;

      if (g_iCount == 1)
      {

         m_pcontext->m_papexcontext->os_context()->file_open(strFile);

      }

      //#ifdef UNIVERSAL_WINDOWS
      //
      //      output_debug_string(strFile);
      //
      //#elif defined(WINDOWS)
      //
      //      call_async("C:\\Program Files (x86)\\Notepad++\\Notepad++.exe", "\"" + strFile + "\"", "", e_display_restored, false);
      //
      //#elif defined(LINUX)
      //
      //      call_async("gedit", "\"" + strFile + "\"", "", e_display_restored, false);
      //
      //#else
      //
      //      ::fork(this, [=]()
      //      {
      //
      //         system("open \"" + strFile + "\"");
      //
      //      });
      //
      //
      //#endif




   }


   //void application::signal(::signal * psignal)
   //{
   //
   //
   //}


   //void application::handle(::topic * ptopic, ::context * pcontext)
   //{


   //}


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


   ::file::path application::get_executable_path()
   {

      return acmedirectory()->module() / (get_executable_title() + get_executable_extension());


   }


   string application::get_executable_extension()
   {

#ifdef WINDOWS

      return ".exe";

#else

      return "";

#endif

   }


   string application::get_executable_title()
   {

      return acmenode()->executable_title_from_appid(get_executable_appid());

   }


   string application::get_executable_appid()
   {

      return m_strAppId;

   }


   void application::app_set(string strPath, string strValue)
   {

      return m_pcontext->m_papexcontext->sys_set(::file::path(m_strAppName) / strPath, strValue);

   }


   string application::app_get(string strPath, string strDefault)
   {

      return m_pcontext->m_papexcontext->sys_get(::file::path(m_strAppName) / strPath, strDefault);

   }


   bool application::on_open_document_file(::payload payloadFile)
   {

      //request_file(payloadFile);

      //return payloadFile["document"].cast < ::object > () != nullptr;

      return false;

   }



   void application::install_trace(const ::string & str)
   {

      synchronous_lock synchronouslock(this->synchronization());

      //::install::trace_file(this, m_strInstallTraceLabel).print(str);

   }


   void application::install_trace(double dRate)
   {

      synchronous_lock synchronouslock(this->synchronization());

      //::install::trace_file(this, m_strInstallTraceLabel).print(dRate);

   }


   void application::register_application_as_spa_file_type_handler()
   {

      auto psystem = acmesystem();

      auto pnode = psystem->node();

      //auto bOk= 

      pnode->register_spa_file_type(m_strAppId);

      //if (!bOk)
      //{

      //   return false;

      //}

      //return true;

   }





   string application::get_app_id(string wstr)
   {

      if (wstr.length() <= 0)
      {

         return "";

      }

      wstr.trim();

      ::str::trim_any_quotes(wstr);

      wstr.trim();

      if (wstr.length() <= 0)
      {

         return "";

      }


      ::string strPath = wstr.c_str();

      ::string strContents = acmefile()->as_string(strPath.c_str());

      throw ::exception(todo, "xml");

      //::xml::document doc;

      //if (!doc.load(strContents.c_str()))
      //{

      //   return "";

      //}

      //const ::string & psz = doc.GetChildAttrValue("launch", "app");

      //if (psz == nullptr || *psz == '\0')
      //{

      //   return "";

      //}

      //return psz;

      return nullptr;

   }


   //LPWAVEOUT application::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
   //{

   //   throw ::exception(interface_only_exception(nullptr));

   //   return nullptr;

   //}


   void application::defer_create_keyboard()
   {

      //set_keyboard_layout(nullptr,::e_source_database);

   }


   bool application::keyboard_focus_is_focusable(const ::user::primitive * pue)
   {

      return false;

   }


   bool application::keyboard_focus_OnSetFocus(::user::primitive * pue)
   {

      return true;

   }


   bool application::send_message_to_windows(const ::atom & atom, wparam wparam, lparam lparam) // with tbs in <3
   {

      //::pointer<::user::interaction>puserinteraction;

      //try
      //{

      //   while (get_frame(puserinteraction))
      //   {

      //      try
      //      {

      //         if (puserinteraction && puserinteraction->is_window())
      //         {

      //            try
      //            {

      //               puserinteraction->send_message(message, wparam, lparam);


      //            }
      //            catch (...)
      //            {

      //            }

      //            try
      //            {

      //               puserinteraction->send_message_to_descendants(message, wparam, lparam);


      //            }
      //            catch (...)
      //            {


      //            }

      //         }

      //      }
      //      catch (...)
      //      {

      //      }

      //   }

      //}
      //catch (...)
      //{

      //}

      throw ::interface_only();

      return false;

   }


   bool application::route_message_to_windows(::message::message * pmessage) // with tbs in <3
   {

      throw ::interface_only();

      //::pointer<::user::interaction>puserinteraction;

      //try
      //{

      //   while (get_frame(puserinteraction))
      //   {

      //      try
      //      {

      //         if (puserinteraction && puserinteraction->is_window())
      //         {

      //            try
      //            {

      //               puserinteraction->route_message(pmessage);

      //            }
      //            catch (...)
      //            {

      //            }

      //            try
      //            {

      //               puserinteraction->route_message_to_descendants(pmessage);

      //            }
      //            catch (...)
      //            {


      //            }

      //         }

      //      }
      //      catch (...)
      //      {

      //      }

      //   }

      //}
      //catch (...)
      //{


      //}

      return false;

   }


   void application::send_language_change_message()
   {

      ::message::message message(e_message_language);

      route_message_to_windows(&message);

   }


   //::user::interaction * application::main_window()
   //{

   //   if (!m_puserinteractionMain)
   //   {

   //      return nullptr;

   //   }

   //   return m_puserinteractionMain->m_puiThis;

   //}


   string application::preferred_experience()
   {

      string strExperience;

      strExperience = payload("experience");

      if (strExperience.has_char())
      {

         return strExperience;

      }

      return "core";

   }

   //::user::document *application::place_hold(::user::interaction * pinteraction)
   //{

   //   return nullptr;

   //}


   void application::post_message(const ::atom & atom, wparam wparam, lparam lparam)
   {

      //return ::thread::post_message(atom, wparam, lparam);

      ::thread::post_message(atom, wparam, lparam);

   }


   //::draw2d::icon * application::set_icon(object * pparticle, ::draw2d::icon * picon, bool bBigIcon)
   //{

   //   ::draw2d::icon * piconOld = get_icon(pparticle, bBigIcon);

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


   //::draw2d::icon * application::get_icon(object * pparticle, bool bBigIcon) const
   //{

   //   if (bBigIcon)
   //   {

   //      return ((object *)pparticle)->cast < ::draw2d::icon >("big_icon");

   //   }
   //   else
   //   {

   //      return ((object *)pparticle)->cast <::draw2d::icon>("small_icon");

   //   }

   //}


   void application::on_message_app_exit(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      _001TryCloseApplication();

   }


   void application::on_message_close(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      if (pmessage->m_wparam == 1)
      {

         if (!try_close_application())
         {

            pmessage->m_lresult = -1;

         }

      }
      else
      {

         close_application();

      }

   }


   bool application::is_equal_file_path(const ::file::path & path1Param, const ::file::path & path2Param)
   {

      if (path1Param.is_empty())
      {

         if (path2Param.is_empty())
         {

            return true;

         }
         else
         {

            return false;

         }

      }
      else if (path2Param.is_empty())
      {

         return false;

      }

      ::file::path path1;

      ::file::path path2;

      path1 = m_pcontext->m_papexcontext->defer_process_path(path1Param);

      path2 = m_pcontext->m_papexcontext->defer_process_path(path2Param);

      path1 = acmepath()->real_path(path1);

      path2 = acmepath()->real_path(path2);

      return strcmp(path1, path2) == 0;

   }


   //   void application::on_event(::u64 u, ::particle * pparticle)
   //   {
   //
   //      object_ptra ptra;
   //
   //      {
   //
   //         synchronous_lock synchronouslock(this->synchronization());
   //
   //         ptra = m_particleaddressaEventHook;
   //
   //      }
   //
   //      for(auto & pparticle : ptra)
   //      {
   //
   //         pparticle->on_event(u, pparticle);
   //
   //      }
   //
   //
   //   }


   ::file::path application::appconfig_folder()
   {

      return acmedirectory()->config() / m_strAppName;

   }


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

   //   return __type(::user::interaction);

   //}


   //::type application::control_type_from_id(const ::atom & atom, ::user::enum_control_type & econtroltype)
   //{

   //   econtroltype = ::user::e_control_type_none;

   //   return __type(::user::interaction);

   //}


   ::atom application::translate_property_id(const ::atom & atom)
   {

      if (atom == "hide_recycle_bin")
      {

         return id_hide_recycle_bin;

      }
      else if (atom == "show_recycle_bin")
      {

         return id_show_recycle_bin;

      }


      //if(!is_system())
      //{

      // if(!is_session())
      //{

      // return psession->translate_property_id(atom);

      //}
      //else
      //{

      // return psystem->translate_property_id(atom);

      //}

      //}

      return atom;

   }


   //void application::record(::create * pcommand)
   //{

   //   synchronous_lock synchronouslock(this->synchronization());

   //   get_command()->m_createa.add(pcommand);

   //}


   bool application::on_start_application()
   {

      string strAppId = m_strAppId;

      auto psystem = acmesystem()->m_papexsystem;

      string strNetworkPayload = file()->safe_get_string(acmedirectory()->config() / strAppId / +"http.network_payload");

      if (strNetworkPayload.has_char())
      {

         try
         {

            psystem->http().m_setHttp.parse_network_payload(strNetworkPayload);

         }
         catch (...)
         {

         }

      }

      acmesystem()->m_pacmenode->m_papexnode->set_last_run_application_path(strAppId);

      acmenode()->m_papexnode->on_start_application(this);

//      if (!os_on_start_application())
//      {
//
//         return false;
//
//      }

      if (!is_service())
      {

         if ((m_bConsole && m_bCreateAppShorcut.is_true())
            || (!m_bConsole && m_bCreateAppShorcut.is_true_or_not_set()))
         {

            on_create_app_shortcut();

         }

      }

      return true;

   }




   void application::HideApplication()
   {


      //try
      //{
      throw ::exception(todo, "interaction");

      //   if (m_puserinteractionMain)
      //   {

      //      m_puserinteractionMain->display(::e_display_hide);

      //      m_puserinteractionMain->set_need_redraw();

      //      m_puserinteractionMain->post_redraw();

      //   }

      //}
      //catch (...)
      //{

      //}

   }


   string application::load_string(const ::atom & atom)
   {

      synchronous_lock synchronouslock(m_pmutexStr);

      string str;

      if (m_stringmap.lookup(atom, str))
      {

         return str;

      }

      if (!load_string(str, atom))
      {

         return atom;

      }

      m_stringmap.set_at(atom, str);

      return str;

   }


   bool application::load_string(string & str, const ::atom & atom)
   {

      if (!load_cached_string(str, atom, true))
      {

         return false;

      }

      return true;

   }


   bool application::load_cached_string(string & str, const ::atom & atom, bool bLoadStringTable)
   {


      //throw ::exception(todo("xml"));

      //auto pdocument = __new(::xml::document);

      //if (!pdocument->load(atom) || !*pdocument)
      //{

      //   return load_cached_string_by_id(str, atom, bLoadStringTable);

      //}

      //auto pnodeRoot = pdocument->root();

      //if (pnodeRoot->get_name() == "string")
      //{

      //   string strId = pnodeRoot->attribute("id");

      //   if (!load_cached_string_by_id(str, strId, bLoadStringTable))
      //   {

      //      str = pnodeRoot->get_value();

      //   }

      //   return true;

      //}

      return false;

   }


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

   //   synchronous_lock synchronouslock(m_pmutexStr);

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


   void application::load_string_table(const string & pszApp, const string & pszId)
   {


   }




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


   ::database::server * application::dataserver()
   {

      //return simpledb();

      return nullptr;

   }


   void application::verb()
   {

      //return true;

   }


   void application::_001TryCloseApplication()
   {

      post_message(MESSAGE_CLOSE, 1, 0);

   }


   bool application::try_close_application()
   {

      if (!can_close_application())
      {

         return false;

      }

      close_application();

      return true;

   }

   bool application::can_close_application()
   {

      return true;

   }


   void application::close_application()
   {

      //#ifdef UNIVERSAL_WINDOWS
      //
      //::winrt::Windows::ApplicationModel::Core::CoreApplication::MainImpact->CoreWindow->Dispatcher->RunAsync(
      //::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal,
      //ref memory_new ::winrt::Windows::UI::Core::DispatchedHandler([this]()
      //{
      //::winrt::Windows::UI::ImpactManagement::ApplicationImpact::GetForCurrentImpact()->TryConsolidateAsync();
      //}));
      //
      //#else

      set_finish();

      //#endif

   }


   //bool application::process_exception(const ::exception & e)
   //{

   //   return apex::application::process_exception(e);

   //}


   //void     application::main()
   //{

   //   return ::application::main();

   //}


   void application::on_run()
   {

      //try
      //{

      //   ::apex::message::application signal(::apex::message::application_begin);

      //   route_message(&signal);

      //}
      //catch (...)
      //{

      //}

      auto ptask = ::get_task()->get_thread();

      install_message_routing(ptask);

      m_bReady = true;

      //try
      //{

      string strType = __type_name(this);

      //if(::is_set(acmesystem()))
      //{

      //   acmesystem()->add_reference(this);

      //}

      //if(::is_set(m_psession))
      //{

      //   m_psession->add_reference(this);

      //}

      //if (::is_set(m_pappParent))
      //{
      //
      //m_pappParent->add_reference(this);
      //
      //}

         //resume_on_exception:

      try
      {

         //m_estatus = run();

         run();

      }
      catch (const ::exception & e)
      {

         handle_exception(e);

         //if (handle_exception(e))
         //{

         //   goto resume_on_exception;

         //}

         //m_estatus = e.m_estatus;

         //}

      }
      catch (...)
      {

      }

      try
      {

         thread * pthread = this;

         if (pthread != nullptr && pthread->m_peventReady != nullptr)
         {

            pthread->m_peventReady->SetEvent();

         }

      }
      catch (...)
      {

         //   // m_result.add(error_failed);

      }

      //return m_estatus;

   }


   //void application::destroy()
   //{
   //
   //   auto estatus = ::apex::context::destroy();
   //
   //   if (!estatus)
   //   {
   //
   //      return estatus;
   //
   //   }
   //
   //   return estatus;
   //
   //}


   //void application::init_application()
   //{

   //   return ::application::init_application();

   //}


   //void application::application_pre_run()
   //{

   //   return ::application::application_pre_run();

   //}



   //bool application::InitApplication()
   //{

   //   return true;

   //}


   //bool application::do_install()
   //{


   //   if (!::application::do_install())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool application::do_uninstall()
   //{

   //   bool bOk = apex::application::do_uninstall();

   //   return bOk;

   //}


   //bool application::on_install()
   //{

   //   if (!apex::application::on_install())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool application::on_uninstall()
   //{

   //   if (!apex::application::on_uninstall())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //void application::os_native_bergedge_start()
   //{

   //   if (!::application::os_native_bergedge_start())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   void application::on_request(::request * prequest)
   {

   }


   //void     application::run()
   //{

   //   return ::application::run();

   //}


   //::pointer<::apex::application>application::assert_running(const ::string & pszAppId)
   //{

   //   ::pointer<::apex::application>papp;

   //   papp = psession->m_applicationa.find_running_defer_try_quit_damaged(pszAppId);

   //   if(papp.is_null())
   //   {

   //      ::pointer<::create>spcreate(e_create);

   //      papp = psession->start_application(pszAppId,spcreate);

   //   }

   //   return papp;

   //}


   //void application::process_init()
   //{

   //   add_factory_item < ::database::field_array >();
   //   add_factory_item < ::database::row >();
   //   add_factory_item < ::database::row_array >();

   //   //if (m_bAxisProcessInitialize)
   //   //{

   //   //   return m_bAxisProcessInitializeResult;

   //   //}

   //   INFORMATION("axis::application::process_init");

   //   //m_bAxisProcessInitialize = true;

   //   //m_bAxisProcessInitializeResult = false;

   //   if (m_psimpledb.is_null())
   //   {

   //      __construct_new(m_psimpledb);

   //   }

   //   if (!::application::process_init())
   //   {

   //      FATAL("axis::application::process_init .1");

   //      return false;

   //   }


   //   //m_bAxisProcessInitializeResult = true;

   //   FATAL("axis::application::process_init success");

   //   return true;

   //}


   //void application::init_instance()
   //{

   //   //if (m_bAxisInitializeInstance)
   //   //{

   //   //   return m_bAxisInitializeInstanceResult;

   //   //}

   //   INFORMATION("axis::application::init_instance .1");

   //   //m_bAxisInitializeInstance = true;

   //   //m_bAxisInitializeInstanceResult = false;

   //   if (!::application::init_instance())
   //   {

   //      FATAL("axis::application::init_instance .2");

   //      return false;

   //   }


   //   if (m_bInitializeDataCentral)
   //   {


   //      ::file::path pathDatabase;

   //      if (is_system())
   //      {

   //         pathDatabase = dir()->appdata() / "system.sqlite";

   //      }
   //      else if (is_session())
   //      {

   //         pathDatabase = dir()->appdata() / "session.sqlite";

   //      }
   //      else
   //      {

   //         pathDatabase = dir()->appdata() / "app.sqlite";

   //      }

   //      auto estatus = m_psimpledb->initialize_simpledb_server(this, pathDatabase);

   //      if (!estatus)
   //      {

   //         m_result.add(estatus);

   //         return false;

   //      }

   //      set_data_server(m_psimpledb);

   //   }



   //   //m_bAxisInitializeInstanceResult = true;

   //   INFORMATION("axis::application::init_instance success");

   //   return true;

   //}


   //::database::key application::calc_data_key()
   //{

   //   return ::database::key("app://" + m_strAppName, is_local_data());

   //}




   //void application::init1()
   //{

   //   //if (m_bAxisInitialize1)
   //   //{

   //   //   return m_bAxisInitialize1Result;

   //   //}

   //   //m_bAxisInitialize1 = true;

   //   //m_bAxisInitialize1Result = false;

   //   m_timeHeartBeat.Now();

   //   if (!::application::init1())
   //   {

   //      return false;

   //   }

   //   /*     if (!acmesystem()->m_phtml->initialize())
   //        {

   //           return false;

   //        }*/



   //        //m_bAxisInitialize1Result = true;

   //   return true;

   //}


   //void application::init2()
   //{

   //   if (!::application::init2())
   //      return false;

   //   return true;

   //}


   //void application::init3()
   //{

   //   if (!::application::init3())
   //   {

   //      return false;

   //   }

   //   return true;

   //}

   //


   void application::init()
   {

      m_timeHeartBeat.Now();

      if (has_property("install"))
      {

         // apex level app install
         Ex2OnAppInstall();
         //if (!)
         //{
         //
         ////return false;
         //
         //}

      }
      else if (has_property("uninstall"))
      {

         Ex2OnAppUninstall();
         // apex level app uninstall
         //if (!Ex2OnAppUninstall())
         //{
         //
         //return false;
         //
         //}

      }
      else
      {
         //#ifdef WINDOWS_DESKTOP
         //// when this process is started in the context of a system account,
         //// for example, this code ensure that the process will
         //// impersonate a loggen on ::account::user
         //HANDLE hprocess;
         //HANDLE htoken;
         //
         //hprocess = ::GetCurrentProcess();
         //
         //if (!OpenProcessToken(
         //hprocess,
         //TOKEN_ALL_ACCESS,
         //&htoken))
         //return false;
         //
         //if (!ImpersonateLoggedOnUser(htoken))
         //{
         //TRACELASTERROR();
         //return false;
         //}
         //#endif
      }

      m_timeHeartBeat.Now();

      ensure_app_interest();

      INFORMATION(".2");

      if (is_true("install"))
      {

         if (is_user_service())
         {


         }

      }

      ERROR("1.1");

      index i = applicationmenu().get_count();

      //applicationmenu().add_item(i++, _("Transparent Frame"), "transparent_frame");

      applicationmenu().add_item(i++, "Transparent Frame", "transparent_frame");

      application_menu_update();

      INFORMATION("success");

      //return true;

   }


   void application::term()
   {



   }


   bool application::is_running()
   {

      return is_alive();

   }


   bool application::pump_runnable()
   {

      defer_process_activation_message();

      return ::thread::pump_runnable();

   }


   void application::add_activation_message(const ::string & strMessage)
   {

      {

         synchronous_lock synchronouslock(this->synchronization());

         m_straActivationMessage.add(strMessage);

      }

      defer_process_activation_message();

   }


   bool application::has_activation_message() const
   {

      synchronous_lock synchronouslock(this->synchronization());

      return m_straActivationMessage.has_element();

   }


   bool application::defer_process_activation_message()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (!m_bAttendedFirstRequest)
      {

         return false;

      }

      //preempt(25_s);

      if (m_straActivationMessage.is_empty())
      {

         return false;

      }

      auto pinterprocesscommunication = m_pinterprocesscommunication;

      if (::is_null(pinterprocesscommunication))
      {

         return false;

      }

      do
      {

         auto strUri = m_straActivationMessage.pick_first();

         synchronouslock.unlock();

         //preempt(25_s);

         payload("activation.note2") = "m_straActivationMessage.pick_first()=\"" + strUri + "\"";

         pinterprocesscommunication->_handle_uri(strUri);

         synchronouslock.lock();

      } while (m_straActivationMessage.has_element());

      return true;

   }


   //bool application::Ex2OnAppInstall()
   //{
   //   return true;
   //}


   //bool application::Ex2OnAppUninstall()
   //{

   //   return true;

   //}


   void application::update_appmatter(::pointer<::sockets::http_session>& psession, const ::file::path & pszRoot, const string & pszRelative)
   {

      auto psystem = acmesystem()->m_papexsystem;

      auto plocaleschema = __create_new < ::text::international::locale_schema >();

      //psession->fill_locale_schema(localeschema);

      bool bIgnoreStdStd = string(pszRoot) == "app" && (string(pszRelative) == "main" || string(pszRelative) == "bergedge");

      //update_appmatter(h, psession, pszRoot, pszRelative, plocaleschema->m_atomLocale, plocaleschema->m_atomSchema);

      ::count iCount = plocaleschema->m_idaLocale.get_count();

      for (index i = 0; i < iCount; i++)
      {

         if (plocaleschema->m_idaLocale[i] == "std" && plocaleschema->m_idaSchema[i] == "std" && bIgnoreStdStd)
            continue;

         string strLocale;

         strLocale = plocaleschema->m_idaLocale[i];

         string strSchema;

         strSchema = plocaleschema->m_idaSchema[i];

         update_appmatter(psession, pszRoot, pszRelative, strLocale, strSchema);

         psystem->install_progress_add_up();

      }


      ///return true;

   }


   void application::update_appmatter(::pointer<::sockets::http_session>& psession, const ::file::path & pszRoot, const string & pszRelative, const string & pszLocale, const string & pszStyle)
   {

      string strLocale;
      string strSchema;
      INFORMATION("update_appmatter(root=" << pszRoot << ", relative=" << pszRelative << ", locale=" << pszLocale << ", style=" << pszStyle << ")");
      ::file::path strRelative = ::file::path(pszRoot) / "_matter" / pszRelative / get_locale_schema_dir(pszLocale, pszStyle) + ".zip";
      ::file::path strFile = dir()->install() / strRelative;
      ::file::path strUrl(::e_path_url);

      if (acmenode()->is_debug_build())
      {
         strUrl = "http://basis-server.ca2.software/api/spaignition/download?authnone&configuration=basis&stage=";
      }
      else
      {
         strUrl = "http://stage-server.ca2.software/api/spaignition/download?authnone&configuration=stage&stage=";
      }

      auto psystem = acmesystem();

      auto purl = psystem->url();

      strUrl += ::url::encode(strRelative);

      if (psession == nullptr)
      {

         while (true)
         {

            property_set setEmpty;

            if (m_pcontext->m_papexcontext->http().open(psession, purl->get_server(strUrl), purl->get_protocol(strUrl), setEmpty, nullptr))
            {

               break;

            }

            sleep(200_ms);

         }

      }

      property_set set;

      set["get_memory"] = "";

      m_pcontext->m_papexcontext->http().request(psession, strUrl, set);
      //{
      //
      //m_pdraw2d->init()
      //
      //}

      ::memory_file file;

      if (set["get_memory"].cast < memory >() != nullptr && set["get_memory"].cast < memory >()->size() > 0)
      {

         //zip_context zip(this);

         auto pfolder = ::particle::file()->get_folder(&file, "zip", ::file::e_open_read);

         string strDir = strFile;

         strDir.case_insensitive_ends_eat(".zip");

         //try
         //{

         pfolder->e_extract_all(strDir);

         //}
         //catch (...)
         //{
         //
         //// spa app_app_admin.exe would recover by retrying or someone would fix the resource packaging problem and then zip extraction at least should work.
         //
         ////return false;
         //
         //}

         //psystem->compress().e_extract_all(strFile, this);

      }

      //return true;

   }





   bool application::assert_user_logged_in()
   {

      string strRequestUrl;

      if (acmefile()->as_string(acmedirectory()->system() / "config\\system\\ignition_server.txt").has_char())
      {

         strRequestUrl = "https://" + acmefile()->as_string(acmedirectory()->system() / "config\\system\\ignition_server.txt") + "/api/spaignition";

      }

      if (acmesession() == nullptr)
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

      string strMatter = dir()->matter(::file::path(pszMatter) / pszMatter2);

      payloadFile["url"] = strMatter;

      return file()->as_string(payloadFile);

   }

   //string application::dir()->matter(const ::string & pszMatter,const ::string & pszMatter2)
   //{

   //   return dir()->matter(pszMatter,pszMatter2);

   //}

   //bool application::is_inside_time_dir(const ::string & pszPath)
   //{
   //   return dir()->is_inside_time(pszPath);
   //}


   //bool application::file_is_read_only(const ::string & pszPath)
   //{

   //   return false;
   //   //return file()->is_read_only(pszPath);

   //}



   //void application::process_message_filter(i32 code, ::message::message * pmessage)
   //{

   //   //::pointer<::user::message>pusermessage(pmessage);

   //   __UNREFERENCED_PARAMETER(code);

   //   __UNREFERENCED_PARAMETER(pmessage);


   //}







   void application::DoWaitCursor(i32 nCode)
   {

      if (nCode < 0)
      {

         m_iWaitCursorCount = 0;

         auto psystem = acmesystem();

         auto pnode = psystem->node()->m_papexnode;

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

            auto psystem = acmesystem();

            auto pnode = psystem->node()->m_papexnode;

            pnode->show_wait_cursor(true);

         }

         m_iWaitCursorCount = 0;

         auto psystem = acmesystem();

         auto pnode = psystem->node()->m_papexnode;

         pnode->show_wait_cursor(false);

      }
      else
      {

         if (m_iWaitCursorCount < 0)
         {
            m_iWaitCursorCount = 0;
         }

         m_iWaitCursorCount++;

         auto psystem = acmesystem();

         auto pnode = psystem->node()->m_papexnode;

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



   //::draw2d::printer * application::get_printer(const ::string & pszDeviceName)
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   ::pointer<::progress::real>application::show_progress(::user::interaction * puiParent, const ::string & strTitle, ::count iProgressCount)
   {

      throw ::exception(todo);

      return nullptr;

   }


   void application::userfs_init1()
   {

      //return error_not_implemented;

   }


   void application::userfs_process_init()
   {

      //return error_not_implemented;

   }


   string application::dialog_box(const ::string & pszMatter, property_set & propertyset)
   {

      throw ::exception(todo, "core and os");

      return"";

   }

   //bool application::do_prompt_file_name(::payload & payloadFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument)
   //{

   //   __UNREFERENCED_PARAMETER(payloadFile);
   //   __UNREFERENCED_PARAMETER(nIDSTitle);

   //   return false;

   //}






   //void application::get_temp_file_name_template(string & strRet,const ::string & lpszName,const ::string & pszExtension,const ::string & pszTemplate)
   //{

   //   throw ::not_implemented();

   //}


   //bool application::get_temp_file_name(string & strRet,const ::string & lpszName,const ::string & pszExtension)
   //{

   //   return get_temp_file_name_template(strRet,lpszName,pszExtension,nullptr);

   //}








   //::draw2d::icon * application::set_icon(object * pparticle, ::draw2d::icon * picon, bool bBigIcon)
   //{

   //   return nullptr;

   //}


   //::draw2d::icon * application::get_icon(object * pparticle, bool bBigIcon) const
   //{

   //   return nullptr;

   //}


   //void application::on_service_request(::request * prequest)
   //{

   //   ::application::on_service_request(pcreate);

   //}


   string application::get_mutex_name_gen()
   {

      string str = m_strAppId;

      str.find_replace("/", "_");

      str.find_replace("-", "_");

      str.find_replace(".", "_");

      return str;

   }



   string application::get_license_id()
   {

      if (m_strLicense.has_char())
         return m_strLicense;

      if (m_strInstallToken.has_char())
         return m_strInstallToken;

      return m_strAppId;

   }






   //bool application::assert_user_logged_in()
   //{

   //   return axis::application::assert_user_logged_in();

   //}


   void application::hotplugin_host_starter_start_sync(const ::string & pszCommandLine, ::apex::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin)
   {

      {

         auto pmutex = acmenode()->get_install_mutex(this, acmenode()->process_platform_name(), "");

         if (pmutex->has_already_exists_flag())
         {

            //            output_error_message("Could not launch spa installer. It is already running.", e_message_box_ok);

              // return -35;

         }

      }

      string strValue;

      if (get_command_line_parameter(strValue, pszCommandLine, "enable_desktop_launch"))
      {

#ifdef UNIVERSAL_WINDOWS

         //return -1;

         return;

#else

         ::property_set set;

         auto psystem = acmesystem();

         auto pnode = psystem->node();

         ::file::path pathApp;

         ::file::path pathFolder;

         string strPlatformName;

         strPlatformName = acmenode()->process_platform_name();

         string strConfigurationName;

         strConfigurationName = acmenode()->process_configuration_name();

         pathFolder = acmedirectory()->app_app(strPlatformName, strConfigurationName);

         pathApp = pathFolder;

         int iExitCode = 0;

         return pnode->call_sync(pathApp, pszCommandLine, pathFolder, e_display_restored, 2_minute, set, &iExitCode);

#endif

      }
      else
      {

         return hotplugin_host_host_starter_start_sync(pszCommandLine, get_app()->m_papexapplication, nullptr);

      }

   }


   void application::hotplugin_host_host_starter_start_sync(const ::string & pszCommandLine, ::apex::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin)
   {

      ///return -1;

   }



   //void application::handle(::topic * ptopic, ::context * pcontext)
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


   //void application::on_update_impact(::user::impact * pimpact, ::user::impact * pviewSender, LPARAM lHint, object * pHint)
   //{


   //}

   //void application::handle(::topic * ptopic, ::context * pcontext)
   //{

   //}


   //void application::on_notify_control_event(::user::control_event* pevent)
   //{


   //}


   //void application::route(::topic * ptopic, ::context * pcontext)
   //{

   //   handle(ptopic, pcontext);

   //   if (ptopic->m_bRet)
   //   {

   //      return;

   //   }

   //   on_notify_control_event(pevent);

   //   if (ptopic->m_bRet)
   //   {

   //      return;

   //   }

   //}



   //   void     application::interactive_credentials(::account::credentials * pcredentials)
   //   {
   //
   //      return ::apex::applciation::interactive_credentials(pcredentials);
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

   //   return memory_new ::html::html(get_app());

   //}


   //string application::http_get(const ::string & strUrl, ::property_set & set)
   //{

   //   return http().get(strUrl, set);

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


//   bool application::is_local_data()
//   {
//
//      return m_strDataKey.m_bLocalData;
//
//   }







   //const char application::gen_FileSection[] = "Recent File List";
   //const char application::gen_FileEntry[] = "File%d";
   //const char application::gen_ThumbnailSection[] = "Settings";
   //const char application::gen_ThumbnailEntry[] = "ThumbnailPages";


   //application::application()
   //{

   //   add_factory_item < ::user::user >();
   //   add_factory_item < ::userfs::userfs >();

   //   m_pmainpane = nullptr;

   //   m_ppaneimpactMain = nullptr;

   //   // almost always forgotten, assumed, as exception, responsability of application to add first ref on constructor.
   //   //::increment_reference_count(this);

   //   srand((u32) ::get_tick());

   //   m_bService = false;

   //   m_iResourceId = 8001;

   //   ::apex::profiler::initialize();

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

   //   auto estatus = ::application::initialize(pparticle);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

   //}




   //::application * application::get_app() const
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


   //u32 application::guess_code_page(const string& str)
   //{
   //
   //return 0;
   //
   //}


   //LRESULT application::GetPaintMsgProc(i32 nCode, WPARAM wParam, LPARAM lParam)
   //{

   //   __UNREFERENCED_PARAMETER(nCode);
   //   __UNREFERENCED_PARAMETER(wParam);
   //   __UNREFERENCED_PARAMETER(lParam);

   //   return 0;

   //}


   //bool application::CreateFileFromRawResource(::u32 nID, const ::string & pcszType, const ::string & pcszFilePath)
   //{
   //
   //__UNREFERENCED_PARAMETER(nID);
   //__UNREFERENCED_PARAMETER(pcszType);
   //__UNREFERENCED_PARAMETER(pcszFilePath);
   //
   //return false;
   //
   //}


   //#ifdef WINDOWS
   //
   //bool application::OnMessageWindowMessage(MESSAGE * pmsg)
   //
   //{
   //
   //__UNREFERENCED_PARAMETER(pmsg);
   //
   //
   //return false;
   //
   //}
   //
   //#elif defined(LINUX)
   //
   //bool application::OnX11WindowMessage(void* pXevent) // XEvent *
   //{
   //
   //__UNREFERENCED_PARAMETER(pXevent);
   //
   //return false;
   //
   //}
   //
   //#endif
   //
   //void application::OnUpdateRecentFileMenu(::message::command* pcommand)
   //{
   //
   //__UNREFERENCED_PARAMETER(pcommand);
   //
   //}
   //
   //
   //bool application::GetResourceData(::u32 nID, const ::string & pcszType, memory& storage)
   //
   //{
   //
   //__UNREFERENCED_PARAMETER(nID);
   //__UNREFERENCED_PARAMETER(pcszType);
   //
   //__UNREFERENCED_PARAMETER(storage);
   //
   //return false;
   //
   //}


   //#ifdef WINDOWS_DESKTOP
   //
   //   HENHMETAFILE application::LoadEnhMetaFile(::u32 uResource)
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
   //      return SetEnhMetaFileBits((::u32)storage.size(), storage.get_data());
   //
   //   }
   //
   //#endif

   ///////////////////////////////////////////////////////////////////////////////
   //// WinApp UI related functions
   //
   //void application::EnableModelessEx(bool bEnable)
   //{
   //__UNREFERENCED_PARAMETER(bEnable);
   //#ifdef ___NO_OLE_SUPPORT
   //UNUSED(bEnable);
   //#endif
   //
   //
   //}



   /* void     application::run()
   {

   return ::application::run();

   }*/


   bool application::on_idle(::i32 lCount)
   {

      return false;

   }


   void application::process_window_procedure_exception(const ::exception & e, ::message::message * pmessage)
   {

      ENSURE_ARG(pmessage != nullptr);

      //::pointer<::user::message>pusermessage(pmessage);

      // handle certain messages in thread

      switch (pmessage->m_atom.m_emessage)
      {
      case e_message_create:
      case e_message_paint:

         return thread::process_window_procedure_exception(e, pmessage);
            
      default:
            break;
            
      }

      // handle all the rest
      //linux ::u32 nIDP = __IDP_INTERNAL_FAILURE;   // matter message string
      const ::string & nIDP = "Internal Failure";
      pmessage->m_lresult = 0;        // sensible default
      if (pmessage->m_atom == e_message_command)
      {

         if (pmessage->m_lparam == 0)
         {
            //linux nIDP = __IDP_COMMAND_FAILURE; // command (not from a control)
            //nIDP = "Command Failure";

         }

         pmessage->m_lresult = true;        // pretend the command was handled

      }

      if (e.estatus() == error_no_memory)
      {

         report_error(e, e_message_box_icon_exclamation | e_message_box_system_modal, nullptr);

      }
      else if (e.estatus() == error_user)
      {

         // ::account::user has not been alerted yet of this catastrophic problem

         report_error(e, e_message_box_icon_stop, nullptr);

      }

   }


   void application::route_command(::message::command * pcommand, bool bRouteKeyToDescedant)
   {

      ::thread::route_command(pcommand);

   }


   /*
   bool application::hex_to_memory(memory & memory, const ::string & pszHex)
   {
   ::count len = strlen(pszHex);
   ::count count = (len + 1) / 2;
   memory.set_size(count);
   index i = 0;
   byte b;
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
   ::count count = memory.size();
   char * psz = strHex.get_string_buffer(count * 2);

   for(index i = 0; i < count; i++)
   {
   *psz++ = ::hex::lower_from((byte) ((memory.get_data()[i] >> 4) & 0xf));

   *psz++ = ::hex::lower_from((byte) (memory.get_data()[i] & 0xf));

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

   typedef bool (WINAPI * PFNDeactivateActCtx)(u32, uptr);
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


   //bool application::LoadSysPolicies()
   //{
   //return _LoadSysPolicies();
   //}

   //// This function is not exception safe - will leak a registry key if exceptions are thrown from some places
   //// To reduce risk of leaks, I've declared the whole function noexcept. This despite the fact that its callers have
   //// no dependency on non-throwing.
   //bool application::_LoadSysPolicies() noexcept
   //{
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //HKEY hkPolicy = nullptr;
   //::u32 dwValue = 0;
   //::u32 dwDataLen = sizeof(dwValue);
   //::u32 dwType = 0;
   //
   ////// clear current policy settings.
   ////m_dwPolicies = ___SYSPOLICY_NOTINITIALIZED;
   //
   ////static __system_policy_data rgExplorerData[] =
   ////{
   ////   {"NoRun",___SYSPOLICY_NORUN},
   ////   {"NoDrives",___SYSPOLICY_NODRIVES},
   ////   {"RestrictRun",___SYSPOLICY_RESTRICTRUN},
   ////   {"NoNetConnectDisconnect",___SYSPOLICY_NONETCONNECTDISCONNECTD},
   ////   {"NoRecentDocsHistory",___SYSPOLICY_NORECENTDOCHISTORY},
   ////   {"NoClose",___SYSPOLICY_NOCLOSE},
   ////   {nullptr,0}
   ////};
   //
   ////static __system_policy_data rgNetworkData[] =
   ////{
   ////   {"NoEntireNetwork",___SYSPOLICY_NOENTIRENETWORK},
   ////   {nullptr,0}
   ////};
   //
   ////static __system_policy_data rgComDlgData[] =
   ////{
   ////   {"NoPlacesBar",___SYSPOLICY_NOPLACESBAR},
   ////   {"NoBackButton",___SYSPOLICY_NOBACKBUTTON},
   ////   {"NoFileMru",___SYSPOLICY_NOFILEMRU},
   ////   {nullptr,0}
   ////};
   //
   ////static __system_policies rgPolicies[] =
   ////{
   ////   {  "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",
   ////      rgExplorerData
   ////   },
   ////   {  "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",
   ////      rgNetworkData
   ////   },
   ////   {  "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Comdlg32",
   ////      rgComDlgData
   ////   },
   ////   {nullptr,0}
   ////};
   //
   ////__system_policies *pPolicies = rgPolicies;
   ////__system_policy_data *pData = nullptr;
   //
   ////while (pPolicies->szPolicyKey != nullptr)
   ////{
   //
   ////   if (ERROR_SUCCESS == ::RegOpenKeyEx(
   ////            HKEY_CURRENT_USER,
   ////            pPolicies->szPolicyKey,
   ////            0,
   ////            KEY_QUERY_VALUE,
   ////            &hkPolicy
   ////         ))
   ////   {
   ////      pData = pPolicies->pData;
   ////      while (pData->szPolicyName)
   ////      {
   ////         if (ERROR_SUCCESS == ::RegQueryValueEx(
   ////                  hkPolicy,
   ////                  pData->szPolicyName,
   ////                  nullptr,
   ////                  &dwType,
   ////                  (byte*)&dwValue,
   ////                  &dwDataLen))
   ////         {
   ////            if (dwType == REG_DWORD)
   ////            {
   ////               if (dwValue != 0)
   ////                  m_dwPolicies |= pData->dwID;
   ////               else
   ////                  m_dwPolicies &= ~pData->dwID;
   ////            }
   ////         }
   ////         dwValue = 0;
   ////         dwDataLen = sizeof(dwValue);
   ////         dwType = 0;
   ////         pData++;
   ////      }
   ////      ::RegCloseKey(hkPolicy);
   ////      hkPolicy = nullptr;
   ////   }
   ////   pPolicies++;
   ////};
   //
   //#endif
   //
   //return true;
   //
   //
   //}
   //
   //bool application::GetSysPolicyValue(u32 dwPolicyID, bool* pbValue)
   //{
   //if (!pbValue)
   //return false; // bad pointer
   //*pbValue = (m_dwPolicies & dwPolicyID) != 0;
   //return true;
   //}
   //
   ////bool application::InitApplication()
   ////{
   //
   //
   ////   LoadSysPolicies();
   //
   ////   return true;
   //
   //
   ////}
   //
   //

   /*   void application::LoadStdProfileSettings(::u32 nMaxMRU)
   {
   __UNREFERENCED_PARAMETER(nMaxMRU);
   ASSERT_VALID(this);

   // 0 by default means not set
   m_nNumThumbnailPages = GetProfileInt(gen_ThumbnailSection, gen_ThumbnailEntry, 0);
   }*/

   /*void application::ParseCommandLine(CCommandLineInfo& rCmdInfo)
   {
   for (i32 i = 1; i < __argc; i++)
   {
   const ::string & pszParam = __targv[i];
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

   if (lstrcmpA(pszParam, "point_i32") == 0)
   m_nShellCommand = FilePrintTo;
   else if (lstrcmpA(pszParam, "point_i32") == 0)
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
   //
   //void application::SaveStdProfileSettings()
   //{
   //ASSERT_VALID(this);
   //
   //
   ////      if (m_nNumThumbnailPages != 0)
   ////       WriteProfileInt(gen_ThumbnailSection, gen_ThumbnailEntry, m_nNumThumbnailPages);
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
   //   void application::WinHelp(uptr dwData, ::u32 nCmd)
   //   {
   //      __UNREFERENCED_PARAMETER(dwData);
   //      __UNREFERENCED_PARAMETER(nCmd);
   //
   //      // return global cast help mode state to false (backward compatibility)
   //      m_bHelpMode = false;
   //      // trans pMainWnd->PostMessage(e_message_kick_idle); // trigger idle task
   //
   //      //trans pMainWnd->WinHelp(dwData, nCmd);
   //   }
   //
   //   /////////////////////////////////////////////////////////////////////////////
   //   // HtmlHelp helper
   //
   //   void application::HtmlHelp(uptr dwData, ::u32 nCmd)
   //   {
   //
   //      __UNREFERENCED_PARAMETER(dwData);
   //
   //      __UNREFERENCED_PARAMETER(nCmd);
   //
   //      // return global cast help mode state to false (backward compatibility)
   //      m_bHelpMode = false;
   //      // trans pMainWnd->PostMessage(e_message_kick_idle); // trigger idle task
   //
   //      // trans pMainWnd->HtmlHelp(dwData, nCmd);
   //   }
   //
   //
   //   void application::WinHelpInternal(uptr dwData, ::u32 nCmd)
   //   {
   //      __UNREFERENCED_PARAMETER(dwData);
   //      __UNREFERENCED_PARAMETER(nCmd);
   //      //   ::pointer<::user::interaction>pMainWnd = psystem->m_puiMain;
   //      //   ENSURE_VALID(pMainWnd);
   //
   //      // return global cast help mode state to false (backward compatibility)
   //      m_bHelpMode = false;
   //      // trans pMainWnd->PostMessage(e_message_kick_idle); // trigger idle task
   //      // trans pMainWnd->WinHelpInternal(dwData, nCmd);
   //   }
   //
   //
   //#endif
   //




   ///////////////////////////////////////////////////////////////////////////////
   //// application idle processing
   //
   //void application::DevModeChange(char * pDeviceName)
   //
   //{
   //__UNREFERENCED_PARAMETER(pDeviceName);
   //
   //
   ////#ifdef WINDOWS
   ////      if (m_hDevNames == nullptr)
   ////         return;
   ////
   ////#endif
   //
   //}


   //bool application::process_exception(const ::exception & e)
   //{

   //   return ::application::on_run_exception(pexception))
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
      //string strId = m_strId;
      //char chFirst = '\0';
      //if (strId.length() > 0)
      //{
      //   chFirst = strId[0];
      //}
      ///*      if (m_pdocmanager != nullptr)
      //document_manager()->_001OnFileNew();*/
   }

   void application::on_file_open()
   {
      //ENSURE(m_pdocmanager != nullptr);
      //document_manager()->on_file_open();
   }


   // This is apex API library.
   //
   //
   //
   //
   //
   //
   //
   //




   /*void ::apex::FormatString1(string & rString, ::u32 nIDS, const ::string & psz1)

   {
   __format_strings(rString, nIDS, &psz1, 1);

   }

   void ::apex::FormatString2(string & rString, ::u32 nIDS, const ::string & psz1,

   const ::string & psz2)

   {
   const ::string & rgpsz[2];
   rgpsz[0] = psz1;

   rgpsz[1] = psz2;

   __format_strings(rString, nIDS, rgpsz, 2);
   }*/

   /////////////////////////////////////////////////////////////////////////////

   //
   ///////////////////////////////////////////////////////////////////////////////
   //// Basic Help support (for backward compatibility to apex API 2.0)
   //
   //void application::OnHelp()  // use context to derive help context
   //{
   //if (m_dwPromptContext != 0)
   //{
   //// do not call WinHelp when the error is failing to lauch help
   ////         if (m_dwPromptContext != HID_BASE_PROMPT+__IDP_FAILED_TO_LAUNCH_HELP)
   ////          WinHelpInternal(m_dwPromptContext);
   //return;
   //}
   //
   //// otherwise, use window::OnHelp implementation
   ///* trans ::user::interaction_impl * pwindow = psystem->m_puiMain;
   //ENSURE_VALID(pwindow);
   //if (!pwindow->is_frame_window())
   //pwindow->OnHelp();
   //else
   //((pwindow))->OnHelp();*/
   //}
   //
   //
   //void application::OnHelpIndex()
   //{
   ////
   ////#ifdef WINDOWS_DESKTOP
   ////
   ////      WinHelpInternal(0L, HELP_INDEX);
   ////
   ////#endif
   ////
   //}
   //
   //
   //void application::OnHelpFinder()
   //{
   //
   ////#ifdef WINDOWS_DESKTOP
   ////
   ////      WinHelpInternal(0L, HELP_FINDER);
   ////
   ////#endif
   //
   //}
   //
   //
   //void application::OnHelpUsing()
   //{
   //
   ////#ifdef WINDOWS_DESKTOP
   ////
   ////      WinHelpInternal(0L, HELP_HELPONHELP);
   ////
   ////#endif
   ////
   //}
   //
   //
   ///////////////////////////////////////////////////////////////////////////////
   //// Context Help Mode support (backward compatibility to apex API 2.0)
   //
   //void application::OnContextHelp()
   //{
   //// just use frame_window::OnContextHelp implementation
   ///* trans   m_bHelpMode = HELP_ACTIVE;
   //::pointer<::user::frame_window>pMainWnd = (psystem->m_puiMain);
   //ENSURE_VALID(pMainWnd);
   //ENSURE(pMainWnd->is_frame_window());
   //pMainWnd->OnContextHelp();
   //m_bHelpMode = pMainWnd->m_bHelpMode;
   //pMainWnd->PostMessage(e_message_kick_idle); // trigger idle task */
   //}
   //
   ///////////////////////////////////////////////////////////////////////////////
   //
   //
   //// This is apex API library.
   ////
   ////
   ////
   ////
   ////
   ////
   ////
   ////
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
   //__UNREFERENCED_PARAMETER(bForceDefaults);
   //}


   //void application::OnFilePrintSetup()
   //{
   //}


   //#ifdef WINDOWS
   //
   //   void application::SelectPrinter(HANDLE hDevNames, HANDLE hDevMode, bool bFreeOld)
   //   {
   //      __UNREFERENCED_PARAMETER(hDevNames);
   //      __UNREFERENCED_PARAMETER(hDevMode);
   //      __UNREFERENCED_PARAMETER(bFreeOld);
   //      throw ::interface_only();
   //   }
   //
   //
   //#endif

   //::draw2d::graphics* application::CreatePrinterDC()
   //{
   //throw ::interface_only();
   //return nullptr;
   //}

   /////////////////////////////////////////////////////////////////////////////


   // This is apex API library.
   //
   //
   //
   //
   //
   //
   //
   //


   //
   ///////////////////////////////////////////////////////////////////////////////
   //// application User Interface Extensions
   //
   //void application::OnAppExit()
   //{
   //
   //// same as double-clicking on main window close box
   //
   ////ASSERT(m_puserinteractionMain != nullptr);
   //
   ////m_puserinteractionMain->m_puiThis->send_message(MESSAGE_CLOSE);
   //
   //}
   //

   //void application::HideApplication()
   //{

   //   try
   //   {

   //      if (m_puserinteractionMain == nullptr)
   //      {

   //         return;

   //      }

   //      // hide the application's windows before closing all the documents
   //      m_puserinteractionMain->m_puiThis->display(e_display_none);
   //      // trans    m_puiMain->ShowOwnedPopups(false);


   //      m_puserinteractionMain->m_puiThis->order(e_zorder_bottom);
   //      //m_puiMain->m_puiThis->m_bZ = true;
   //      // put the window at the bottom of zorder, so it isn't activated
   //      // m_puiMain->m_puiThis->zorder();

   //      //m_puiMain->m_puiThis->wait_redraw();

   //      m_puserinteractionMain->m_puiThis->display(e_display_none);


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
   //
   //void application::EnableModeless(bool bEnable)
   //{
   //DoEnableModeless(bEnable);
   //}
   //
   //void application::DoEnableModeless(bool bEnable)
   //{
   //__UNREFERENCED_PARAMETER(bEnable);
   //#ifdef ___NO_OLE_SUPPORT
   //UNUSED(bEnable);
   //#endif
   //
   //// no-op if main window is nullptr or not a frame_window
   ///*   ::pointer<::user::interaction>pMainWnd = psystem->m_puiMain;
   //if (pMainWnd == nullptr || !pMainWnd->is_frame_window())
   //return;*/
   //
   //#ifndef ___NO_OLE_SUPPORT
   //// check if notify hook installed
   ///*xxx
   //ASSERT_KINDOF(frame_window, pMainWnd);
   //::pointer<::user::frame_window>pFrameWnd = (::pointer<::user::frame_window>MainWnd;
   //if (pFrameWnd->m_pNotifyHook != nullptr)
   //pFrameWnd->m_pNotifyHook->OnEnableModeless(bEnable);
   //*/
   //#endif
   //}
   //









   //
   //
   //void application::RegisterShellFileTypes(bool bCompat)
   //{
   ////ENSURE(m_pdocmanager != nullptr);
   ////      document_manager()->RegisterShellFileTypes(bCompat);
   //}
   //
   //void application::UnregisterShellFileTypes()
   //{
   ////ENSURE(m_pdocmanager != nullptr);
   ////    document_manager()->UnregisterShellFileTypes();
   //}
   //
   //
   //i32 application::get_open_document_count()
   //{
   ////ENSURE(m_pdocmanager != nullptr);
   ////  return document_manager()->get_open_document_count();
   //return 0;
   //}
   //

   // This is apex API library.
   //
   //
   //
   //
   //
   //
   //
   //

   ///////////////////////////////////////////////////////////////////////////////
   //// application Settings Helpers
   //
   //
   //void application::SetRegistryKey(const ::string & pszRegistryKey)
   //
   //{
   ////ASSERT(m_pszRegistryKey == nullptr);
   ////ASSERT(pszRegistryKey != nullptr);
   //
   ////ASSERT(m_strAppName.has_char());
   //
   //////bool bEnable = __enable_memory_tracking(false);
   ////free((void *)m_pszRegistryKey);
   ////m_pszRegistryKey = strdup(pszRegistryKey);
   //
   ////free((void *)m_pszProfileName);
   ////m_pszProfileName = strdup(m_strAppName);
   //////__enable_memory_tracking(bEnable);
   //}
   //
   //void application::SetRegistryKey(::u32 nIDRegistryKey)
   //{
   ////__UNREFERENCED_PARAMETER(nIDRegistryKey);
   ////ASSERT(m_pszRegistryKey == nullptr);
   ////throw ::interface_only();
   /////*char szRegistryKey[256];
   ////VERIFY(::apex::LoadString(nIDRegistryKey, szRegistryKey));
   ////SetRegistryKey(szRegistryKey);*/
   //}


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
   //      //   ::u32 dw;
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
   //#endif

   /*   ::u32 application::GetProfileInt(const ::string & pszSection, const ::string & pszEntry,

   i32 nDefault)
   {
   ASSERT(pszSection != nullptr);

   ASSERT(pszEntry != nullptr);

   if (m_pszRegistryKey != nullptr) // use registry
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return nDefault;
   u32 dwValue;
   u32 dwType;
   u32 dwCount = sizeof(u32);
   ::i32 lResult = RegQueryValueEx(hSecKey, (char *)pszEntry, nullptr, &dwType,

   (byte *)&dwValue, &dwCount);
   RegCloseKey(hSecKey);
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_DWORD);
   ASSERT(dwCount == sizeof(dwValue));
   return (::u32)dwValue;
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

   const ::string & pszDefault)

   {
   ASSERT(pszSection != nullptr);

   ASSERT(pszEntry != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return pszDefault;

   string strValue;
   u32 dwType=REG_NONE;
   u32 dwCount=0;
   ::i32 lResult = RegQueryValueEx(hSecKey, (char *)pszEntry, nullptr, &dwType,

   nullptr, &dwCount);
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_SZ);
   lResult = RegQueryValueEx(hSecKey, (char *)pszEntry, nullptr, &dwType,

   (byte *)strValue.GetBuffer(dwCount/sizeof(char)), &dwCount);
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
   u32 dw = ::GetPrivateProfileString(pszSection, pszEntry,

   pszDefault, szT, _countof(szT), m_pszProfileName);

   ASSERT(dw < 4095);
   return szT;
   }
   }

   bool application::GetProfileBinary(const ::string & pszSection, const ::string & pszEntry,

   byte** ppData, ::u32* pBytes)
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

   // linux ::apex::CRegKey rkSecKey(hSecKey);

   u32 dwType=0;
   u32 dwCount=0;
   ::i32 lResult = RegQueryValueEx(hSecKey, (char *)pszEntry, nullptr, &dwType, nullptr, &dwCount);

   *pBytes = dwCount;
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_BINARY);
   *ppData = memory_new byte[*pBytes];
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
   *pBytes = ::u32(nLen)/2;
   *ppData = memory_new byte[*pBytes];
   for (i32 i=0;i<nLen;i+=2)
   {
   (*ppData)[i/2] = (byte)
   (((str[i+1] - 'A') << 4) + (str[i] - 'A'));
   }
   return true;
   }
   }


   bool application::WriteProfileInt(const ::string & pszSection, const ::string & pszEntry,

   i32 nValue)
   {
   ASSERT(pszSection != nullptr);

   ASSERT(pszEntry != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return false;
   ::i32 lResult = RegSetValueEx(hSecKey, pszEntry, nullptr, REG_DWORD,

   (byte *)&nValue, sizeof(nValue));
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

   const ::string & pszValue)

   {
   ASSERT(pszSection != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   ::i32 lResult;
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

   (byte *)pszValue, (lstrlen(pszValue)+1)*sizeof(char));

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

   byte * pData, ::u32 nBytes)
   {
   ASSERT(pszSection != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   ::i32 lResult;
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return false;
   lResult = RegSetValueEx(hSecKey, pszEntry, nullptr, REG_BINARY,

   pData, nBytes);
   RegCloseKey(hSecKey);
   return lResult == ERROR_SUCCESS;
   }

   // convert to string and write out
   char * psz = memory_new char[nBytes*2+1];

   ::u32 i;
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




   /*   property_set & application::propset(object * pparticle)
   {
   single_lock synchronouslock(&m_mapObjectSet, true);
   return m_mapObjectSet[pparticle];
   }

   property_set * application::existing_propset(object * pparticle)
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

      //if (m_puserinteractionMain != nullptr)
      //{

      //   m_puserinteractionMain->m_puiThis->display(SW_SHOWNORMAL);

      //}

      return true;

   }


   //void application::term()
   //{


   //   try
   //   {

   //      if (m_puserinteractionMain == nullptr)
   //      {

   //         return;

   //      }

   //      // hide the application's windows before closing all the documents
   //      m_puserinteractionMain->m_puiThis->display(e_display_none);
   //      // trans    m_puiMain->ShowOwnedPopups(false);


   //      m_puserinteractionMain->m_puiThis->order(e_zorder_bottom);
   //      //m_puiMain->m_puiThis->m_bZ = true;
   //      // put the window at the bottom of zorder, so it isn't activated
   //      // m_puiMain->m_puiThis->zorder();

   //      //m_puiMain->m_puiThis->wait_redraw();

   //      m_puserinteractionMain->m_puiThis->display(e_display_none);


   //   }
   //   catch (...)
   //   {
   //   }

   //   try
   //   {

   //      ::application::term();

   //   }
   //   catch (...)
   //   {

   //      m_result.add(error_failed);

   //   }

   //}


   //::user::interaction* application::get_request_parent_ui(::user::interaction* pinteraction, ::create* pcreate)
   //{

   //   ::user::interaction* puiParent = nullptr;

   //   if (puiParent == nullptr)
   //   {
   //      puiParent = dynamic_cast <::user::interaction*> (pcreate->m_puserinteractionParent);
   //   }

   //   //      if (puiParent == nullptr && pcreate->m_pappbias.is_set())
   //   //      {
   //   //         puiParent = dynamic_cast < ::user::interaction * > (pcreate->m_pappbias->m_puserinteractionParent);
   //   //      }

   //         //if(puiParent == nullptr && m_psession != nullptr && m_psession->m_psession != nullptr && !pcreate->m_bExperienceMainFrame
   //         /*if (puiParent == nullptr && m_psession != nullptr && m_psession != nullptr
   //               && !pcreate->m_bOuterPopupAlertLike && m_psession != dynamic_cast < session * > (this))
   //         {
   //            puiParent = psession->get_request_parent_ui(pinteraction, pcreate);
   //         }*/

   //   return puiParent;

   //}







   void application::_001OnFileNew(::message::message * pmessage)
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

   //   ::apex::file_system & application::file_system()
   // {
   //  return m_spfilesystem;
   //}







   //   ::user::interaction * application::get_desktop_window()
   //   {
   //#if defined(UNIVERSAL_WINDOWS) || defined(__APPLE__)
   //      throw ::exception(todo);
   //      /*#elif defined(LINUX)
   //
   //      //      synchronous_lock synchronouslock(&user_synchronization());
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
   //      return psystem->ui_from_handle(::get_desktop_window());
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
   //      ::application::dump(dumpcontext);
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
   //      dumpcontext << "\nm_dwPromptContext = " << (::u32)m_dwPromptContext;
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

   //   apex::application::install_message_routing(pchannel);

   //   add_command_handler("switch_context_theme", &application::_001OnSwitchContextTheme);

   //}

   //
   //bool application::base_support()
   //{
   //
   ////if(!application::base_support())
   //// return false;
   //
   //if (m_strBaseSupportId.is_empty())
   //{
   //
   //property_set propertyset;
   //
   //dialog_box("err\\developer\\base_support\\support_id_not_specified.xml", propertyset);
   //
   //return false;
   //
   //}
   //
   //return true;
   //}


   //string application::sync_message_box(const string & pszMatter, property_set & propertyset)
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




   void application::pre_translate_message(::message::message * pmessage)
   {

      return thread::pre_translate_message(pmessage);

   }


   //void application::on_create_split_impact(::user::split_impact* psplit)
   //{

   //}

   //
   //void application::EnableShellOpen()
   //{
   //
   ////#ifdef WINDOWS
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
   ////      // i16 file name so we need to use the i16 file name.
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
   //}


   //::pointer<::user::interaction>application::uie_from_point(const ::point_i32& point)
   //{

   //   user::interaction_pointer_array wnda = *m_puiptraFrame;

   //   user::oswindow_array oswindowa;

   //   oswindowa = wnda.get_hwnda();

   //   user::window_util::SortByZOrder(oswindowa);

   //   for (i32 i = 0; i < oswindowa.get_count(); i++)
   //   {

   //      ::pointer<::user::interaction>puieWindow = wnda.find_first(oswindowa[i]);

   //      ::pointer<::user::interaction>puie = puieWindow->_001FromPoint(point);

   //      if (puie != nullptr)
   //      {

   //         return puie;

   //      }

   //   }

   //   return nullptr;

   //}


   //bool application::on_install()
   //{

   //   if (!::application::on_install())
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

      auto psystem = acmesystem()->m_papexsystem;

      if (m_strId == "session" || m_strAppName == "session")
      {

         if (is_false("session_start"))
         {

            //::parallelization::finish(psystem);

         }

      }
      else
      {

         psystem->destroy();

      }

      return true;

   }


   //bool application::on_uninstall()
   //{

   //   bool bOk = ::application::on_uninstall();

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

            //::parallelization::finish(psystem);

         }

      }
      else
      {

         //::parallelization::finish(psystem);

      }

      return true;

   }


   void application::on_application_signal(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   //::apex::printer* application::get_printer(const ::string & pszDeviceName)
   //{

   //   return nullptr;

   //}


   //bool application::set_keyboard_layout(const ::string & pszPath, const ::action_context& context)
   //{

   //   return psession->keyboard().load_layout(pszPath, context);

   //}


   //i32 application::track_popup_menu(const ::string & pszMatter, const ::point_i32& point, ::pointer<::user::interaction>puie)
   //{

   //   __UNREFERENCED_PARAMETER(pszMatter);
   //   __UNREFERENCED_PARAMETER(point);
   //   __UNREFERENCED_PARAMETER(puie);

   //   return 1;

   //}


   bool application::get_fs_size(string & strSize, const ::string & pszPath, bool & bPending)
   {

      i64 i64Size;

      if (!get_fs_size(i64Size, pszPath, bPending))
      {

         strSize.empty();

         return false;

      }

      if (i64Size > 1024 * 1024 * 1024)
      {

         double d = (double)i64Size / (1024.0 * 1024.0 * 1024.0);

         strSize.format("%0.2f GB", d);

      }
      else if (i64Size > 1024 * 1024)
      {

         double d = (double)i64Size / (1024.0 * 1024.0);

         strSize.format("%0.1f MB", d);

      }
      else if (i64Size > 1024)
      {

         double d = (double)i64Size / (1024.0);

         strSize.format("%0.0f KB", d);

      }
      else if (i64Size > 0)
      {

         strSize.format("1 KB");

      }
      else
      {

         strSize.format("0 KB");

      }

      if (bPending)
      {

         strSize = "~" + strSize;

      }

      return true;

   }


   bool application::get_fs_size(i64 & i64Size, const ::string & pszPath, bool & bPending)
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

      auto psession = acmesession()->m_papexsession;

      psession->set_app_title(m_strAppName, pszTitle);

   }


   //bool application::_001CloseApplicationByUser(::pointer<::user::interaction>puserinteractionExcept)
   //{

   //   // Closing just this application.
   //   // It is different of a system exit.
   //   // psystem (a single ca2 process) can host
   //   // multiple ca2 application objects.

   //   // attempt to save all documents
   //   if (!save_all_modified())
   //   {

   //      return false;     // don't close it

   //   }

   //   // hide the application's windows before closing all the documents
   //   HideApplication();

   //   close(::apex::end_app);

   //   return true;

   //}


   //oswindow application::get_ca2_app_wnd(const ::string & psz)
   //{

   //   __UNREFERENCED_PARAMETER(psz);

   //   return nullptr;

   //}


   //   i32 application::send_simple_command(const ::string & psz, void* osdataSender)
   //   {
   //      string strApp;
   //      string_array stra;
   //      stra.add_tokens(psz, "::", true);
   //      if (stra.size() > 0)
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
   //
   //   i32 application::send_simple_command(void* osdata, const ::string & psz, void* osdataSender)
   //   {
   //#ifdef WINDOWS_DESKTOP
   //      ::windowing::window * pwindow = (::oswindow) osdata;
   //      if (!::IsWindow(__hwnd(oswindow)))
   //         return -1;
   //      COPYDATASTRUCT cds;
   //      memory_set(&cds, 0, sizeof(cds));
   //      cds.dwData = 888888;
   //      cds.cbData = (u32)strlen(psz);
   //      cds.lpData = (PVOID)psz;
   //
   //      return (i32)SendMessage(__hwnd(oswindow), WM_COPYDATA, (WPARAM)osdataSender, (LPARAM)&cds);
   //#else
   //      throw ::exception(todo);
   //#endif
   //   }


   void application::ensure_app_interest()
   {

      //#ifndef UNIVERSAL_WINDOWS
      //
      //      for (i32 i = 0; i < m_straAppInterest.get_count(); i++)
      //      {
      //         if (m_straAppInterest[i] != m_strAppName && !::is_window(m_mapAppInterest[m_straAppInterest[i]]))
      //         {
      //            psystem->assert_running_local(m_straAppInterest[i]);
      //         }
      //      }
      //
      //#else
      //
      //      //throw ::exception(todo);
      //
      //#endif

   }




   //::application * application::psystem
   //{

   //   return ::object::psystem;

   //}


















   /*
   ::pointer<::apex::application>application::assert_running(const ::string & pszAppId)
   {


   ::pointer<::apex::application>papp = nullptr;


   try
   {

   bool bFound = false;

   for(i32 i  = 0; i < psystem->m_appptra.get_count(); i++)
   {
   try
   {

   papp = psystem->m_appptra(i);

   if(papp->m_strAppName == pszAppId)
   {
   bFound = true;
   break;
   }

   }
   catch(...)
   {
   }

   }

   bool bCreate = !bFound;

   if(bFound)
   {

   bool bRunning = false;

   try
   {
   if(papp->is_running())
   {
   bRunning = true;
   }
   }
   catch(...)
   {
   }


   if(bCreate)
   {

   ::pointer<::create>spcreate(e_create);

   papp = psession->start_application("application", pszAppId, spcreate);

   }

   }
   catch(const ::exit_exception & e)
   {

   throw ::exception(e);

   }
   catch(const const ::exception & e)
   {

   if(!get_app()->on_run_exception((::exception &) e))
   throw ::exception(exit_exception());

   }
   catch(...)
   {

   papp = nullptr;

   }


   return papp;

   }
   */





   //typedef  void (* PFN_factory)();
















   void application::data_on_after_change(::database::client * pclient, const ::scoped_string & str, const ::payload & payload, ::topic * ptopic)
   {


   }


   //::pointer<::apex::application>application::create_platform(::apex::session* psession)
   //{
   //
   //   return __new(::apex::session);
   //
   //}


   void application::report_error(const ::exception & e, int iMessageFlags, const ::string & pszTopic)
   {

      string strMessage;

      strMessage += pszTopic;

      strMessage += " : ";

      strMessage += e.get_message();

      throw ::exception(todo, "interaction");

   }


   string application::get_theme()
   {

      return "";

   }


   void application::initialize_contextualized_theme()
   {

      //return ::success;

   }


   void application::_001OnSwitchContextTheme(::message::message * pmessage)
   {

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

   }


   void     application::create_impact_system()
   {

      //return ::success;

   }


   void application::process_message_filter(i32 code, ::message::message * pmessage)
   {


   }


   void application::on_thread_on_idle(::thread * pthread, ::i32 lCount)
   {

      throw ::exception(todo, "interaction");

      //return ::error_failed;

   }


   void application::on_song_added(const string & str)
   {

   }


   string application::as_string(const ::payload & payload)
   {

      auto path = payload.as_file_path();

      if (path.has_char())
      {

         if (::is_url(path) || acmefile()->exists(path))
         {

            return file()->as_string(path);

         }

      }

      return payload;

   }


   string application::sound_path(const ::string & psz)
   {

      string strFileName = string(psz) + string(".wav");

      string strFilePath = dir()->matter(strFileName);

      return strFilePath;

   }


   string application::get_default_playlist_path()
   {

      return "playlist/default";

   }


   void application::close(::apex::enum_end eend)
   {

      if (eend == ::apex::e_end_close)
      {

         return;

      }

      m_ethreadcontextClose = e_thread_context_application;

      if (eend == ::apex::e_end_app)
      {

         destroy();

         return;

      }

      if (eend == ::apex::e_end_session)
      {

         try
         {

            if (acmesession())
            {

               auto psession = acmesession();

               psession->destroy();

            }

         }
         catch (...)
         {

         }

         return;

      }

      if (eend == ::apex::e_end_system)
      {

         try
         {

            auto psystem = acmesystem()->m_papexsystem;

            if (psystem)
            {

               psystem->destroy();

            }

         }
         catch (...)
         {

         }

      }

   }


   //pointer< ::extended::future < ::conversation > > application::message_box(const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox)
   //{
   //
   //   auto psystem = acmesystem()->m_papexsystem;
   //
   //   return psystem->_message_box(this, pszMessage, pszTitle, emessagebox);
   //
   //}


   string application::get_version()
   {

      auto psystem = acmesystem()->m_papexsystem;

      auto papex = psystem->acmesession()->m_pacmenode->m_papexnode;

      return papex->get_version();

   }


   void application::_001InitializeShellOpen()
   {

      auto psystem = acmesystem()->m_papexsystem;

      auto papex = psystem->m_pacmenode->m_papexnode;

      return papex->_001InitializeShellOpen();

   }


#if defined(LINUX) || defined(FREEBSD)


   string application::get_wm_class() const
   {

      string strWMClass = m_strAppId;

      strWMClass.find_replace("/", ".");

      strWMClass.find_replace("_", "-");

      return strWMClass;

   }


#endif


   class networking::application * application::networking_application()
   {

      if (!m_pnetworkingapplication)
      {

         create_networking_application();

      }

      return m_pnetworkingapplication;

   }


   void application::create_networking_application()
   {

      //auto estatus =

      __defer_construct(m_pnetworkingapplication);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =

      m_pnetworkingapplication->create_networking_application();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   ::e_status application::on_html_response(string & strHtml, const ::string & strUrl, const ::property_set & setPost)
   {

      ::e_status estatus = ::success_none;

      if (m_pnetworkingapplication)
      {

         estatus = networking_application()->on_html_response(strHtml, strUrl, setPost);

      }

      return estatus;

   }


   bool application::_handle_uri(const ::string & strUri)
   {
      
      string strHtml;
      
      property_set setPost;

      auto estatus = on_html_response(strHtml, strUri, setPost);

      if(estatus != success_none && ::succeeded(estatus))
      {
         
         return true;
         
      }

      if (m_pinterprocesscommunication)
      {

         m_pinterprocesscommunication->m_ptarget->_handle_uri(strUri);

      }
      else
      {

         //preempt(25_s);

         acmeapplication()->payload("activation.note1") = "m_pinterprocesscommunication was null for uri=\"" + strUri + "\"";

         add_activation_message(strUri);

      }

      return false;

   }


   //void application::interprocess_communication_open(const ::file::path & path)
   //{
   //   
   //   if(!m_prx)
   //   {
   //      
   //      throw ::exception(error_wrong_state);
   //      
   //   }
   //   
   //   string strMessage(pszPath);
   //   
   //   m_prx->on_interprocess_receive();
   //   
   //}


   bool application::exclusive_fails(const ::string & strName, security_attributes * psecurityattributes)
   {

      return acmenode()->m_papexnode->exclusive_fails(this, strName, psecurityattributes);

   }


   bool application::exclusive_erase(const ::string & strName)
   {

      return acmenode()->m_papexnode->erase_exclusive(strName);

   }


   void application::release_exclusive()
   {

      auto papexnode = acmenode()->m_papexnode;

      papexnode->release_exclusive();

   }


} // namespace apex


void application_on_menu_action(void * pApplication, const char * pszCommand)
{

   auto papp = (::acme::application *)pApplication;

   papp->m_papexapplication->on_application_menu_action(pszCommand);

}



