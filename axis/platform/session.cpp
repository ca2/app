#include "framework.h"
#include "axis/user/_user.h"
#include "acme/const/id.h"
#include "apex/platform/app_core.h"
#include "apex/platform/static_setup.h"


CLASS_DECL_AXIS ::user::interaction * create_system_message_window(::object* pobject);


#if defined(APPLE_IOS)

#include "aura/node/ios/interaction_impl.h"

#endif


#if defined(APPLE_IOS) || defined(_UWP) || defined(ANDROID)


namespace PLATFORM_NAMESPACE
{


   CLASS_DECL_AXIS ::user::interaction * create_host_window();


} // namespace PLATFORM_NAMESPACE


#endif


#ifdef CUBE
extern "C"
::aura::application * cube_get_app();
#endif

void defer_term_ui();


//bool is_verbose();

//extern string_map < __pointer(::apex::library) >* g_pmapLibrary;
//extern ::mutex * &System.m_mutexLibrary;
//extern string_map < PFN_NEW_AURA_LIBRARY >* g_pmapNewAuraLibrary;

int_bool point_is_window_origin(POINT_I32 ptHitTest, oswindow oswindowExclude, int iMargin);

#ifdef _UWP

#include "aura/os/uwp/_uwp.h"

#elif defined(LINUX)

void x11_on_start_session();

#endif


namespace axis
{


   session::session()
   {

      m_paxissession = this;

   }


   session::~session()
   {

      output_debug_string("axis::session::~session()");

      m_paxissession = nullptr;

   }


   ::e_status session::initialize(::layered * pobjectContext)
   {

      auto estatus = ::thread::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      m_bIfs                           = true;

      m_bProgrammerMode                = false;

      m_bSystemSynchronizedCursor      = true;

      m_pimplPendingFocus2             = nullptr;

      set_context_session(this);

      if (get_context_system() != nullptr)
      {

         auto psystem = &System;

         m_bSystemSynchronizedCursor   = psystem->m_bSystemSynchronizedCursor;

      }

      m_pappCurrent                    = nullptr;

      m_puiLastLButtonDown             = nullptr;

      m_pmapKeyPressed                 = nullptr;

      m_puiMouseMoveCapture            = nullptr;

      m_bZipIsDir2                     = true;

      m_iEdge                          = 0;

      m_bShowPlatform                  = false;

      m_pappCurrent                    = nullptr;


      //m_strAppId = "base_session";
//m_strAppName = "base_session";
//m_strBaseSupportId = "base_session";
//m_strInstallToken = "base_session";

      m_puiMouseMoveCapture = nullptr;

      return estatus;

   }


   ::e_status session::process_init()
   {

      INFO("axis::session::process_init");

      auto estatus = ::aura::session::process_init();

      if (!estatus)
      {

         return estatus;

      }



      INFO("axis::session::process_init success");

      return ::success;

   }



   void session::term2()
   {

      ::aura::session::term2();

   }


   void session::term1()
   {

      ::aura::session::term1();

   }


   void session::process_term()
   {

      ::aura::session::process_term();

   }


   //::aura::application * session::application_get(const char * pszAppId, bool bCreate, bool bSynch, ::create * pcreate)
   //{

   //   __pointer(::apex::application) papp;

   //   if (m_applicationa.lookup(pszAppId, papp))
   //   {

   //      return papp;

   //   }
   //   else
   //   {

   //      if (!bCreate)
   //      {

   //         return nullptr;

   //      }

   //      papp = nullptr;

   //      try
   //      {

   //         papp = create_application(pszAppId, bSynch, pcreate);

   //      }
   //      catch (::exception_pointer pe)
   //      {

   //         // aura::session, axis::session and ::base::session, could get more specialized handling in aura::application (aura::system)
   //         // Thank you Mummi (em Santos, cuidando do Lucinho e ajudando um monte a Carô e o Lúcio e Eu 2019-01-15) !! Thank you God!! <3tbs

   //         handle_exception(pe);

   //         //if (!Sys(this).on_run_exception(esp))
   //         //{

   //         //   if (!App(this).on_run_exception(esp))
   //         //   {

   //         //      papp = nullptr;

   //         //   }

   //         //}

   //         //papp = nullptr;

   //      }
   //      catch (...)
   //      {

   //         //papp = nullptr;

   //      }

   //      if (!papp)
   //      {

   //         return nullptr;

   //      }

   //      app_add(papp);

   //      return papp;

   //   }

   //}


//   __pointer(::aura::application) session::get_new_application(::layered * pobjectContext, const char * pszAppId)
//   {
//
//      string strAppId(pszAppId);
//
//      __pointer(::aura::application) papp;
//
//      if (!papp)
//      {
//
//         if (System.m_pappcore != nullptr && System.m_pmaindata && System.m_pfnNewAuraApplication != nullptr)
//         {
//
//            papp = System.m_pfnNewAuraApplication();
//
//            if (papp.is_null())
//            {
//
//               return nullptr;
//
//            }
//
//            auto estatus = papp->initialize(pobjectContext);
//
//            if (!estatus)
//            {
//
//               m_result.add(estatus);
//
//               return nullptr;
//
//            }
//
//            papp->m_strLibraryName = strAppId;
//
//
//         }
//         synchronization_lock synchronizationlock(&System.m_mutexLibrary);
//
//         __pointer(::apex::library) & plibrary = &System.m_mapLibrary[pszAppId];
//
//         if (!plibrary)
//         {
//
//            if (System.m_pappcore != nullptr && System.m_pfnNewAuraLibrary != nullptr)
//            {
//
//               plibrary = __move_transfer(System.m_pfnNewAuraLibrary());
//
//            }
//            else
//            {
//
//               ::aura_app * pauraapp = ::aura_app::get(pszAppId);
//
//               if (pauraapp != nullptr)
//               {
//
//                  if (pauraapp->m_pfnNewAuraLibrary != nullptr)
//                  {
//
//                     plibrary = __move_transfer(pauraapp->m_pfnNewAuraLibrary());
//
//                  }
//                  else if (pauraapp->m_pfnNewAuraApplication != nullptr)
//                  {
//
//                     papp = __move_transfer(pauraapp->m_pfnNewAuraApplication());
//
//                     if (papp.is_null())
//                     {
//
//                        return nullptr;
//
//                     }
//
//                     papp->m_strLibraryName = pszAppId;
//
//                  }
//
//               }
//
//               if (papp.is_null())
//               {
//
//                  if (plibrary)
//                  {
//
//                     plibrary->initialize_aura_library(pobjectContext, 0, nullptr);
//
//                  }
//                  else
//                  {
//
//                     plibrary = __new(::apex::library);
//
//                     plibrary->initialize_aura_library(pobjectContext, 0, nullptr);
//
//                     //g_pmapLibrary[string(pszAppId)] = plibrary;
//
//                     string strLibrary = strAppId;
//
//                     strLibrary.replace("/", "_");
//
//                     strLibrary.replace("-", "_");
//
//                     if (is_verbose())
//                     {
//
//                        ::output_debug_string("\n\n::aura::session::get_new_application assembled library path " + strLibrary + "\n\n");
//
//                     }
//
//                     if (!plibrary->open(strLibrary, false))
//                     {
//
//#ifndef _UWP
//
//                        os_message_box(nullptr, "Application \"" + strAppId + "\" cannot be created.\n\nThe library \"" + strLibrary + "\" could not be loaded. " + plibrary->m_strMessage, "ca2", MB_ICONERROR);
//
//#endif
//
//                        return nullptr;
//
//                     }
//
//                     if (is_verbose())
//                     {
//
//                        ::output_debug_string("\n\n::aura::session::get_new_application Found library : " + strLibrary + "\n\n");
//
//                     }
//
//                     // error anticipation maybe counter-self-healing
//   //               if (!plibrary->is_opened())
//   //               {
//   //
//   //                  ::output_debug_string("\n\n::aura::session::get_new_application Failed to load library : " + strLibrary + "\n\n");
//   //
//   //                  return nullptr;
//   //
//   //               }
//
//                     if (is_verbose())
//                     {
//
//                        ::output_debug_string("\n\n::aura::session::get_new_application Opened library : " + strLibrary + "\n\n");
//
//                     }
//
//                     if (!plibrary->open_ca2_library())
//                     {
//
//                        ::output_debug_string("\n\n::aura::session::get_new_application open_ca2_library failed(2) : " + strLibrary + "\n\n");
//
//                        return nullptr;
//
//                     }
//
//                     if (is_verbose())
//                     {
//
//                        ::output_debug_string("\n\n\n|(5)----");
//                        ::output_debug_string("| app : " + strAppId + "\n");
//                        ::output_debug_string("|\n");
//                        ::output_debug_string("|\n");
//                        ::output_debug_string("|----");
//
//                     }
//
//                  }
//
//               }
//
//            }
//
//         }
//
//         if (papp.is_null())
//
//         {
//
//            ::apex::library & library = *plibrary;
//
//
//            papp = library.get_new_application(this, strAppId);
//
//            ::output_debug_string("\n\n\n|(4)----");
//            ::output_debug_string("| app : " + strAppId + "(papp=0x" + ::hex::upper_from((uptr)papp.m_p) + ")\n");
//            ::output_debug_string("|\n");
//            ::output_debug_string("|\n");
//            ::output_debug_string("|----");
//
//         }
//
//         if (!papp)
//         {
//
//            return nullptr;
//
//         }
//
//      }
//
//#ifdef WINDOWS_DESKTOP
//
//      WCHAR wsz[1024];
//
//      ::u32 dwSize = sizeof(wsz) / sizeof(WCHAR);
//
//      GetUserNameW(wsz, &dwSize);
//
//      string strUserName = wsz;
//
//#endif // WINDOWS_DESKTOP
//
//      if (is_verbose())
//      {
//
//         ::output_debug_string("\n\n\n|(3)----");
//         ::output_debug_string("| app : " + strAppId + "\n");
//         ::output_debug_string("|\n");
//         ::output_debug_string("|\n");
//         ::output_debug_string("|----");
//
//      }
//
//      if (is_verbose())
//      {
//
//         ::output_debug_string("\n\n\n|(2)----");
//         ::output_debug_string("| app : " + strAppId + "\n");
//         ::output_debug_string("|\n");
//         ::output_debug_string("|\n");
//         ::output_debug_string("|----");
//
//      }
//
//#if !defined(ANDROID)
//
//      if (!papp->is_serviceable() || papp->is_user_service())
//      {
//
//         System.m_spmutexUserAppData = __new(::mutex(e_create_new, false, "Local\\ca2.UserAppData"));
//         System.m_spmutexSystemAppData = __new(::mutex(e_create_new, false, "Local\\ca2.SystemAppData"));
//
//      }
//
//#endif
//
//      if (is_verbose())
//      {
//
//         ::output_debug_string("\n\n\n|(1)----");
//         ::output_debug_string("| app : " + strAppId + "\n");
//         ::output_debug_string("|\n");
//         ::output_debug_string("|\n");
//         ::output_debug_string("|----");
//
//      }
//
//      papp->m_strAppId = pszAppId;
//
//      set_context_app(papp);
//
//      return papp;
//
//   }


   //void session::interactive_credentials(::account::credentials * pcredentials)
   //{

   //   //pcredentials->m_puser->m_estatusAuthentication = ::error_credentials_non_interactive;

   //}


   bool session::is_licensed(const char * pszAppId, bool bInteractive)
   {

      if (has_property("install"))
      {

         return true;

      }

      if (has_property("uninstall"))
      {

         return true;

      }

      if(m_paccount.is_null())
      {

         return false;

      }

      return m_paccount->is_licensed(pszAppId, bInteractive);

   }


   ::account::user * session::get_user(::file::path pathUrl, bool bFetch, bool bInteractive)
   {

      if(m_paccount.is_null())
      {

         return nullptr;

      }

      return m_paccount->get_user(pathUrl, bFetch, bInteractive);

   }


//   ::account::user * session::interactive_get_user(::file::path pathUrl)
//   {
//
//      if(m_paccount.is_null())
//      {
//
//         return nullptr;
//
//      }
//
//      return m_paccount->interactive_get_user();
//
//   }
//
//
//   ::account::user * session::noninteractive_get_user(::file::path pathUrl)
//   {
//
//      if(m_paccount.is_null())
//      {
//
//         return nullptr;
//
//      }
//
//      return m_paccount->noninteractive_get_user(pathUrl);
//
//   }


   bool session::get_auth(const string & pszForm, string & strUsername, string & strPassword)
   {

      throw 0;

      return false;

      //return account()->get_auth(pszForm, strUsername, strPassword);

   }


   //void session::defer_initialize_user_presence()
   //{


   //}

   //void session::translate_os_key_message(::user::key * pkey)
   //{

   //}


   void session::on_remove_user(::account::user * puser)
   {

   }



   ::e_status session::init1()
   {

      auto estatus = ::aura::session::init1();

      if (!estatus)
      {

         m_result.add(estatus);

         return estatus;

      }

      return estatus;

   }



   ::e_status session::init2()
   {

      ::e_status estatus = ::aura::session::init2();

      if(!estatus)
      {

         return estatus;

      }

      //if (!InitializeLocalDataCentral())
      //{

      //   message_box("Could not initialize Local data central");

      //   return ::error_failed;

      //}

      return estatus;

   }


   ::e_status session::init()
   {

      ::e_status estatus = ::aura::session::init();

      if (!estatus)
      {

         m_result.add(estatus);

         return estatus;

      }

      return estatus;

   }


   void session::term()
   {

      ::aura::session::term();


      try
      {

         __release(m_paccount);

      }
      catch (...)
      {

         m_result.add(error_failed);

      }

   }




} // namespace axis








#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace axis
{






   //::e_status session::initialize(::layered * pobjectContext)
   //{

   //   auto estatus = ::aura::session::initialize(pobjectContext);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }


   //   return estatus;

   //}


   void session::install_message_routing(::channel* pchannel)
   {

      ::thread::install_message_routing(pchannel);

   //   //aura::application::install_message_routing(pchannel);
   //   aura::session::install_message_routing(pchannel);

   }


   //::e_status session::process_init()
   //{

   //   /*if(!::aura::application::process_init())
   //      return false;*/

   //   if (!::aura::session::process_init())
   //      return false;

   //   //auto estatus = process_init_userex();

   //   //if(!estatus)
   //   //{

   //   //   return estatus;

   //   //}
   //   auto estatus = __construct(m_puser);

   //   if (!estatus || !m_puser)
   //   {

   //      ERR(".4");

   //      return false;

   //   }

   //   INFO("end");
   //   return true;

   //}


   //::e_status session::init1()
   //{

   //   //if (!::aura::application::init1())
   //   //{

   //   //   return false;

   //   //}

   //   if (!::aura::session::init1())
   //   {

   //      return false;

   //   }



   //   if (!::aura::session::init1())
   //      return false;

   //   //if (!::aura::application::init1())
   //     // return false;

   //   //if (pstyle.is_null())
   //   //{
   //   //
   //   //   defer_create_user_style(preferred_experience());
   //   //
   //   //}

   //   if (!m_puser->init1())
   //      return false;

   //   if (!m_puser->init2())
   //      return false;



   //   auto estatus = __compose_new(m_puserex);

   //   if (!estatus)
   //   {

   //      return false;

   //   }

   //   if (!m_puserex->init())
   //   {

   //      return false;

   //   }

   //   if (!m_puserex->init1())
   //   {

   //      return false;

   //   }

   //   if (!m_puserex->init2())
   //   {

   //      return false;

   //   }

   //   return true;


   //}


   //::e_status session::init()
   //{

   //   //if (!::aura::application::init())
   //   //{

   //   //   return false;

   //   //}

   //   if (!::aura::session::init())
   //   {

   //      return false;

   //   }



   //   return true;

   //}


   //::e_status session::init2()
   //{

   //   //if (!::aura::application::init2())
   //   //{

   //   //   return false;

   //   //}

   //   if (!::aura::session::init2())
   //   {

   //      return false;

   //   }

   //   return true;

   //}



   //::e_status session::init_session()
   //{

   //   //if (!::aura::application::init_application())
   //   //{

   //   //   return false;

   //   //}

   //   if (!::aura::session::init_session())
   //   {

   //      return false;

   //   }

   //   initialize_bergedge_application_interface();

   //   //SetRegistryKey("ca2core");

   //   if (!InitializeLocalDataCentral())
   //   {

   //      message_box("Could not initialize Local data central");

   //      return false;

   //   }

   //   initialize_bergedge_application_interface();

   //   if (is_remote_session())
   //   {

   //      //psession->savings().save(::e_resource_display_bandwidth);
   //      //psession->savings().save(::e_resource_blur_background);
   //      //psession->savings().save(::e_resource_blurred_text_embossing);
   //      //psession->savings().save(::e_resource_translucent_background);

   //   }

   //   if (!initialize_filemanager_component(this))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //void session::term_session()
   //{


   //   try
   //   {

   //      ::aura::session::term_session();

   //   }
   //   catch (...)
   //   {

   //   }
   //   try
   //   {

   //      m_puser->term();

   //   }
   //   catch (...)
   //   {

   //   }


   //   m_puser.release();

   //   try
   //   {

   //      if (m_puserex.is_set())
   //      {

   //         m_puserex->term();

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   //__releasem_puserex.release();




   //   filemanager_finalize();

   //}


   //void session::term()
   //{

   //   try
   //   {

   //      ::aura::session::term();

   //   }
   //   catch (...)
   //   {

   //      m_result.add(error_failed);

   //   }

   //   //try
   //   //{

   //   //   ::aura::application::term();

   //   //}
   //   //catch(...)
   //   //{

   //   //   m_result.add(error_failed);

   //   //}

   //}


   //::e_status session::bergedge_start()
   //{

   //   return true;

   //}





   bool session::InitializeLocalDataCentral()
   {

      //m_pdatabase = new nature::database(this);

      //if(m_pdatabase == nullptr)
      //{
      //   TRACE("VmpLightApp::init_instance failed to instatiate LightDB\n");
      //   return false;
      //}

      //if(!m_pdatabase->Initialize())
      //{
      //   TRACE("VmpLightApp::init_instance failed to initialize LightDB\n");
      //   return false;
      //}

      return true;

   }


   void session::interactive_credentials(::account::credentials* pcredentials)
   {


      //if (!USER)
      //{

      //   //   //pcredentials->m_puser->m_estatusAuthentication = ::error_credentials_non_interactive;

      //   return;

      //}
      pcredentials->m_estatus = error_failed;

      manual_reset_event ev;

      if (!pcredentials->m_bInteractive)
      {

         pcredentials->m_estatus = error_credentials_non_interactive;

         return;

      }

      //if (m_pmainpane != nullptr && m_pmainpane == nullptr)
      //{

      //   try
      //   {

      //      m_pmainpane->interactive_credentials(pcredentials);

      //   }
      //   catch (...)
      //   {

      //   }

      //}

      if (pcredentials->m_estatus == ::success_credentials ||
         ::failed(pcredentials->m_estatus, STATUS_RANGE_AUTHENTICATION))
      {

         return;

      }

#if !defined(LINUX) && !defined(APPLEOS) && !defined(ANDROID)
      //attach_thread_input_to_main_thread(false);
#endif

      //::aura::session::interactive_credentials(pcredentials);

      if (pcredentials->m_estatus == ::success_credentials)
      {

         return;

      }

      if (!pcredentials->m_bInteractive)
      {

         pcredentials->m_estatus = error_credentials_non_interactive;

         return;

      }

      auto puser = pcredentials->m_puser;

      //auto pdialog = ::__create_new<::account::dialog>();

      //pdialog->initialize_account_dialog(pcredentials);

      //pdialog->get_credentials();

      //pdialog->DestroyWindow();


   }


   ::user::style * session::get_user_style()
   {

      if (!m_puser)
      {

         return nullptr;

      }

      return m_puser->m_puserstyle;

   }


   void session::on_user_logon(::account::user* puser)
   {

      // Remember:
      // (Implement items below here or at derived class 'on_user_logon'
      //  virtual member overload)
      //
      // - userpresence
      // - intelligent file system (ifs)
      //


      //if(puser->m_strPathPrefix.is_empty())
      //{

      //   puser->m_strPathPrefix = Context.dir().default_os_user_path_prefix();

      //}

      //auto puser = get_user22();

//      if(::is_null(puser))
//      {
//
//         return;
//
//      }

      puser->m_pathFolder = Context.dir().appdata() / "profile" / puser->m_strLogin;

      Context.dir().mk(puser->m_pathFolder);

      for (auto& papp : m_applicationa)
      {

         if (papp.is_set())
         {

            papp->process_subject(id_change_user);

         }

      }

   }
   __namespace_session_factory(session);

} // namespace axis



