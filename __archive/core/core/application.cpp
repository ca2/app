#include "framework.h"
#include "acme/profiler2.h"
#include "core/user/userex/_userex.h"



namespace acme
{


   const char application::gen_FileSection[] = "Recent File List";
   const char application::gen_FileEntry[] = "File%d";
   const char application::gen_PreviewSection[] = "Settings";
   const char application::gen_PreviewEntry[] = "PreviewPages";


   application::application()
   {

      create_factory < ::user::user >();
      create_factory < ::userfs::userfs >();

      m_pmainpane = nullptr;

      m_ppaneviewMain = nullptr;

      // almost always forgotten, assumed, as exception, responsability of application to add first ref on constructor.
      //::add_ref(this);

      srand((u32) ::get_tick());

      m_bService = false;

      m_iResourceId = 8001;

      ::acme::profiler::initialize();

//      m_pdocmanager = nullptr;

      m_eexclusiveinstance = ExclusiveInstanceNone;
      m_strLocale = "_std";
      m_strSchema = "_std";

      m_iGcomBackgroundUpdateMillis = -1;

   }


   application::~application()
   {

   }


   ::e_status application::initialize(::matter * pobjectContext)
   {

      auto estatus = ::acme::application::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   bool application::on_application_menu_action(const char * pszCommand)
   {

      if (m_puiMain1 != nullptr)
      {

         ::user::command command;

         command.m_id = ::id(pszCommand);

         m_puiMain1->route_command_message(&command);

         if (command.m_bRet)
         {

            return true;

         }

      }

      return false;

   }


   //::acme::application * application::get_context_application() const
   //{

   //   return (application *) this;

   //}








   bool application::is_system() const
   {

      return false;

   }


   bool application::is_session() const
   {

      return false;

   }


   u32 application::guess_code_page(const string & str)
   {

      return 0;

   }

   //   bool application::is_installing()
   //   {
   //
   //      return ::acme::application::is_installing();
   //
   //   }
   //
   //
   //   bool application::is_unstalling()
   //   {
   //
   //      return ::acme::application::is_unstalling();
   //
   //   }


   bool application::is_serviceable() const
   {

      return ::acme::application::is_serviceable();

   }


   ::e_status     application::main()
   {

      return ::acme::application::main();

   }


   ::e_status application::os_native_bergedge_start()
   {

      if (!::acme::application::os_native_bergedge_start())
      {

         return false;

      }

      return true;

   }


   ::e_status application::process_init()
   {

      INFO("start");

      if (!::acme::application::process_init())
      {

         ERR(".1");

         return false;

      }


      if (!userfs_process_init())
      {

         ERR(".2");

         return false;

      }

      INFO("success");

      return true;

   }


   ::e_status application::init1()
   {

      if (!initialize_contextualized_theme())
      {

         FATAL("Failed to initialize_contextualized_theme");

         return false;

      }

      INFO("start");

      if (!::acme::application::init1())
      {

         ERR(".1");

         return false;

      }

      if (!initialize1_experience())
      {

         ERR(".2");

         return false;

      }
      m_millisHeartBeat.Now();

      auto estatus = __compose(m_puserfs);

      if(!estatus)
      {

         return estatus;

      }

      if (!userfs_init1())
      {

         ERR(".3");

         return false;

      }



      /*if(!m_spuser->init1())
      return false;
      if(!m_spuser->init2())
      return false;*/




      return true;

   }


   ::e_status application::init2()
   {

      if (!::acme::application::init2())
         return false;

      return true;

   }


   ::e_status application::init3()
   {

      if (!::acme::application::init3())
         return false;

      return true;

   }











   void application::on_request(::create * pcreate)
   {



      ::acme::application::on_request(pcreate);

   }







   /*   ::papaya::array & application::array()
   {

   return *m_ppapayaarray;

   }
   */

   ::e_status application::init_instance()
   {


      auto estatus = ::acme::application::init_instance();

      if (!estatus)
      {

         return estatus;

      }

      estatus = create_impact_system();

      if (failed(estatus))
      {

         return false;

      }


   if (!is_system() && !is_session())
   {

      string str;
      // if system locale has changed (compared to last recorded one by acme)
      // use the system locale
      if (data_get({ "system_locale", true }, str))
      {

         if (str.has_char())
         {

            if (str != get_locale())
            {

               try
               {

                  data_set({ "system_locale", true }, get_locale());

                  data_set({ "locale", true }, get_locale());

               }
               catch (...)
               {

               }

            }

         }

      }
      else
      {

         data_set({ "system_locale", true }, get_locale());

      }

      if (command_value("locale").get_count() > 0)
      {

         str = command_value("locale").stra()[0];

         data_set({ "system_locale", true }, str);

         data_set({ "locale", true }, str);

         set_locale(str, ::e_source_database);

      }
      else if (command_value("lang").get_count() > 0)
      {

         str = command_value("lang").stra()[0];

         data_set({ "system_locale", true }, str);

         data_set({ "locale", true }, str);

         set_locale(str, ::e_source_database);

      }
      else if (data_get({ "locale", true }, str))
      {

         if (str.has_char())
         {

            set_locale(str, ::e_source_database);

         }

      }
      // if system schema has changed (compared to last recorded one by acme)
      // use the system schema
      if (data_get({ "system_schema", true }, str))
      {

         if (str.has_char())
         {

            if (str != get_schema())
            {

               try
               {

                  data_set({ "system_schema", true }, get_schema());

                  data_set({ "schema", true }, get_schema());

               }
               catch (...)
               {

               }

            }

         }

      }
      else
      {

         data_set({ "system_schema", true }, get_schema());

      }

      if (command() && command_value("schema").get_count() > 0)
      {

         str = command_value("schema").stra()[0];

         data_set({ "system_schema", true }, str);

         data_set({ "schema", true }, str);

         set_schema(str, ::e_source_database);

      }
      else if (data_get({ "schema", true }, str))
      {

         if (str.has_char())
         {

            set_schema(str, ::e_source_database);

         }

      }

      data_pulse_change({ "ca2.savings", true }, nullptr);

      Sys(this).appa_load_string_table();

   }
   if (!is_system() && !is_session())
   {

      string str;
      // if system locale has changed (compared to last recorded one by acme)
      // use the system locale
      if (data_get({ "system_locale", true }, str))
      {

         if (str.has_char())
         {

            if (str != get_locale())
            {

               try
               {

                  data_set({ "system_locale", true }, get_locale());

                  data_set({ "locale", true }, get_locale());

               }
               catch (...)
               {

               }

            }

         }

      }
      else
      {

         data_set({ "system_locale", true }, get_locale());

      }

      if (command_value("locale").get_count() > 0)
      {

         str = command_value("locale").stra()[0];

         data_set({ "system_locale", true }, str);

         data_set({ "locale", true }, str);

         set_locale(str, ::e_source_database);

      }
      else if (command_value("lang").get_count() > 0)
      {

         str = command_value("lang").stra()[0];

         data_set({ "system_locale", true }, str);

         data_set({ "locale", true }, str);

         set_locale(str, ::e_source_database);

      }
      else if (data_get({ "locale", true }, str))
      {

         if (str.has_char())
         {

            set_locale(str, ::e_source_database);

         }

      }
      // if system schema has changed (compared to last recorded one by acme)
      // use the system schema
      if (data_get({ "system_schema", true }, str))
      {

         if (str.has_char())
         {

            if (str != get_schema())
            {

               try
               {

                  data_set({ "system_schema", true }, get_schema());

                  data_set({ "schema", true }, get_schema());

               }
               catch (...)
               {

               }

            }

         }

      }
      else
      {

         data_set({ "system_schema", true }, get_schema());

      }

      if (command() && command_value("schema").get_count() > 0)
      {

         str = command_value("schema").stra()[0];

         data_set({ "system_schema", true }, str);

         data_set({ "schema", true }, str);

         set_schema(str, ::e_source_database);

      }
      else if (data_get({ "schema", true }, str))
      {

         if (str.has_char())
         {

            set_schema(str, ::e_source_database);

         }

      }

      data_pulse_change({ "ca2.savings", true }, nullptr);

      Sys(this).appa_load_string_table();

   }

   return ::success;

}

   ::e_status application::init_application()
   {

//#ifdef _DEBUG
//
//      debug_ca2_variadic_template_base_formatting_integer_zero_padding();
//
//#endif

      INFO("start");

      //try
      //{

      //   throw_numeric_parser_exception("little test of numeric parser exception at sys (main?) function stack?");

      //}
      //catch (numeric_parser_exception & exp)
      //{

      //   output_debug_string("caught!!!! : " + exp.m_strMessage);

      //}

      if (!::acme::application::init_application())
      {

         ERR(".1");

         return false;

      }

      INFO(".2");

      if (!is_session() && !is_system())
      {

         if (command() && has_property("install"))
         {

            if (is_user_service())
            {

//               if (psession->account()->m_puser != nullptr && psession->account()->m_puser->m_strLogin == "system")
//               {
//
//                  psession->account()->m_puser = nullptr;
//
//               }
//
//               if (!m_strAppId.begins_ci("app-core/netnode") && m_strAppId != "app-core/mydns")
//               {
//
//                  ApplicationUser;
//
//               }

            }

         }
         else
         {

            //psession->keyboard();

         }

         ERR("1.1");

         index i = applicationmenu().get_count();

         applicationmenu().add_item(i++, _("Transparent Frame"), "transparent_frame");

         application_menu_update();

      }

      INFO("success");

      return true;

   }


   void application::term_application()
   {

      try
      {

         close(::acme::end_app);

      }
      catch (...)
      {

      }


      //try
      //{

      //   m_spobjectUserFs.release();

      //}
      //catch (...)
      //{


      //}

      //m_puserfs = nullptr;

      m_pexperience.release();

      try
      {

         ::acme::application::term_application();

      }
      catch (...)
      {

      }

      try
      {

         m_pdocmanager.release();

      }
      catch (...)
      {

      }


   }


   LRESULT application::GetPaintMsgProc(i32 nCode, WPARAM wParam, LPARAM lParam)
   {

      UNREFERENCED_PARAMETER(nCode);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);

      return 0;

   }


   bool application::CreateFileFromRawResource(::u32 nID, const char * pcszType, const char * pcszFilePath)
   {

      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(pcszType);
      UNREFERENCED_PARAMETER(pcszFilePath);

      return false;

   }


#ifdef WINDOWS

   bool application::OnMessageWindowMessage(LPMESSAGE pmsg)

   {

      UNREFERENCED_PARAMETER(pmsg);


      return false;

   }

#elif defined(LINUX)

   bool application::OnX11WindowMessage(void  * pXevent) // XEvent *
   {

      UNREFERENCED_PARAMETER(pXevent);

      return false;

   }

#endif

   void application::OnUpdateRecentFileMenu(::user::command * pcommand)
   {

      UNREFERENCED_PARAMETER(pcommand);

   }


   bool application::GetResourceData(::u32 nID, const char * pcszType, memory &storage)

   {

      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(pcszType);

      UNREFERENCED_PARAMETER(storage);

      return false;

   }


#ifdef WINDOWS_DESKTOP

   HENHMETAFILE application::LoadEnhMetaFile(::u32 uResource)
   {

      memory storage;

      if (!GetResourceData(uiResource, "EnhMetaFile", storage))
      {

         return nullptr;

      }

      return SetEnhMetaFileBits((::u32)storage.get_size(), storage.get_data());

   }

#endif

   /////////////////////////////////////////////////////////////////////////////
   // WinApp UI related functions

   void application::EnableModelessEx(bool bEnable)
   {
      UNREFERENCED_PARAMETER(bEnable);
#ifdef ___NO_OLE_SUPPORT
      UNUSED(bEnable);
#endif


   }



   ::e_status     application::run()
   {

      return ::acme::application::run();

   }


   bool application::on_idle(::i32 lCount)
   {

      return false;

   }


   bool application::process_exception(::exception_pointer e)
   {

      return ::acme::application::process_exception(e);

   }


   void application::process_window_procedure_exception(::exception::exception * pexception, ::message::message * pmessage)
   {

      ENSURE_ARG(pexception != nullptr);

      ENSURE_ARG(pmessage != nullptr);

      SCAST_PTR(::message::base, pbase, pmessage);

      // handle certain messages in thread

      switch (pbase->m_id)
      {
      case e_message_create:
      case e_message_paint:

         return thread::process_window_procedure_exception(pexception, pmessage);

      }

      // handle all the rest
      //linux ::u32 nIDP = __IDP_INTERNAL_FAILURE;   // matter message string
      const char * nIDP = "Internal Failure";
      pbase->m_lresult = 0;        // sensible default
      if (pbase->m_id == e_message_command)
      {
         if (pbase->m_lparam == 0)
            //linux nIDP = __IDP_COMMAND_FAILURE; // command (not from a control)
            nIDP = "Command Failure";
         pbase->m_lresult = (LRESULT)TRUE;        // pretend the command was handled
      }

      __pointer(::exception::exception) pbaseexception = pexception;

      if (pbaseexception.is < memory_exception >())
      {
         report_error(pbaseexception, e_message_box_icon_exclamation | e_message_box_system_modal, nIDP);

      }
      else if (pbaseexception.is < user_exception >())
      {

         // ::account::user has not been alerted yet of this catastrophic problem

         report_error(pbaseexception, e_message_box_icon_stop, nIDP);

      }

   }


   void application::route_command_message(::user::command * pcommand)
   {

      ::acme::application::route_command_message(pcommand);

   }



   /*
   bool application::hex_to_memory(memory & memory, const char * pszHex)
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
   ::count count = memory.get_size();
   char * psz = strHex.get_string_buffer(count * 2);

   for(index i = 0; i < count; i++)
   {
   *psz++ = ::hex::lower_from((byte) ((memory.get_data()[i] >> 4) & 0xf));

   *psz++ = ::hex::lower_from((byte) (memory.get_data()[i] & 0xf));

   }
   strHex.ReleaseBuffer(count * 2);
   }
   */











   // // BEGIN_MESSAGE_MAP(application, channel)
   //{{__MSG_MAP(application)
   // Global File commands
   //   ON_COMMAND(ID_APP_EXIT, &application::OnAppExit)
   // MRU - most recently used file menu
   //   ON_UPDATE_::user::command(ID_FILE_MRU_FILE1, &application::OnUpdateRecentFileMenu)
   //   ON_COMMAND_EX_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE16, &application::OnOpenRecentFile)
   //}}__MSG_MAP
   // // END_MESSAGE_MAP()

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

   return ( s_pfnActivateActCtx( m_hCtxt, &m_uCookie) == TRUE );
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
   return ( s_pfnDeactivateActCtx(0, uCookie) == TRUE );
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


   bool application::LoadSysPolicies()
   {
      return _LoadSysPolicies();
   }

   // This function is not exception safe - will leak a registry key if exceptions are thrown from some places
   // To reduce risk of leaks, I've declared the whole function noexcept. This despite the fact that its callers have
   // no dependency on non-throwing.
   bool application::_LoadSysPolicies() noexcept
   {

#ifdef WINDOWS_DESKTOP

      HKEY hkPolicy = nullptr;
      ::u32 dwValue = 0;
      ::u32 dwDataLen = sizeof(dwValue);
      ::u32 dwType = 0;

      //// clear current policy settings.
      //m_dwPolicies = ___SYSPOLICY_NOTINITIALIZED;

      //static __system_policy_data rgExplorerData[] =
      //{
      //   {"NoRun",___SYSPOLICY_NORUN},
      //   {"NoDrives",___SYSPOLICY_NODRIVES},
      //   {"RestrictRun",___SYSPOLICY_RESTRICTRUN},
      //   {"NoNetConnectDisconnect",___SYSPOLICY_NONETCONNECTDISCONNECTD},
      //   {"NoRecentDocsHistory",___SYSPOLICY_NORECENTDOCHISTORY},
      //   {"NoClose",___SYSPOLICY_NOCLOSE},
      //   {nullptr,0}
      //};

      //static __system_policy_data rgNetworkData[] =
      //{
      //   {"NoEntireNetwork",___SYSPOLICY_NOENTIRENETWORK},
      //   {nullptr,0}
      //};

      //static __system_policy_data rgComDlgData[] =
      //{
      //   {"NoPlacesBar",___SYSPOLICY_NOPLACESBAR},
      //   {"NoBackButton",___SYSPOLICY_NOBACKBUTTON},
      //   {"NoFileMru",___SYSPOLICY_NOFILEMRU},
      //   {nullptr,0}
      //};

      //static __system_policies rgPolicies[] =
      //{
      //   {  "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",
      //      rgExplorerData
      //   },
      //   {  "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",
      //      rgNetworkData
      //   },
      //   {  "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Comdlg32",
      //      rgComDlgData
      //   },
      //   {nullptr,0}
      //};

      //__system_policies *pPolicies = rgPolicies;
      //__system_policy_data *pData = nullptr;

      //while (pPolicies->szPolicyKey != nullptr)
      //{

      //   if (ERROR_SUCCESS == ::RegOpenKeyEx(
      //            HKEY_CURRENT_USER,
      //            pPolicies->szPolicyKey,
      //            0,
      //            KEY_QUERY_VALUE,
      //            &hkPolicy
      //         ))
      //   {
      //      pData = pPolicies->pData;
      //      while (pData->szPolicyName)
      //      {
      //         if (ERROR_SUCCESS == ::RegQueryValueEx(
      //                  hkPolicy,
      //                  pData->szPolicyName,
      //                  nullptr,
      //                  &dwType,
      //                  (byte*)&dwValue,
      //                  &dwDataLen))
      //         {
      //            if (dwType == REG_DWORD)
      //            {
      //               if (dwValue != 0)
      //                  m_dwPolicies |= pData->dwID;
      //               else
      //                  m_dwPolicies &= ~pData->dwID;
      //            }
      //         }
      //         dwValue = 0;
      //         dwDataLen = sizeof(dwValue);
      //         dwType = 0;
      //         pData++;
      //      }
      //      ::RegCloseKey(hkPolicy);
      //      hkPolicy = nullptr;
      //   }
      //   pPolicies++;
      //};

#endif

      return TRUE;


   }

   bool application::GetSysPolicyValue(u32 dwPolicyID, bool *pbValue)
   {
      if (!pbValue)
         return FALSE; // bad pointer
      *pbValue = (m_dwPolicies & dwPolicyID) != 0;
      return TRUE;
   }

   bool application::InitApplication()
   {


      LoadSysPolicies();

      return TRUE;


   }



   /*   void application::LoadStdProfileSettings(::u32 nMaxMRU)
   {
   UNREFERENCED_PARAMETER(nMaxMRU);
   ASSERT_VALID(this);

   // 0 by default means not set
   m_nNumPreviewPages = GetProfileInt(gen_PreviewSection, gen_PreviewEntry, 0);
   }*/

   /*void application::ParseCommandLine(CCommandLineInfo& rCmdInfo)
   {
   for (i32 i = 1; i < __argc; i++)
   {
   const char * pszParam = __targv[i];
   bool bFlag = FALSE;
   bool bLast = ((i + 1) == __argc);
   if (pszParam[0] == '-' || pszParam[0] == '/')
   {
   // remove flag specifier
   bFlag = TRUE;
   ++pszParam;
   }
   rCmdInfo.ParseParam(pszParam, bFlag, bLast);
   }
   }*/

   /////////////////////////////////////////////////////////////////////////////
   // CCommandLineInfo implementation

   /*CCommandLineInfo::CCommandLineInfo()
   {
   m_bShowSplash = TRUE;
   m_bRunEmbedded = FALSE;
   m_bRunAutomated = FALSE;
   m_nShellCommand = FileNew;
   }

   CCommandLineInfo::~CCommandLineInfo()
   {
   }

   void CCommandLineInfo::ParseParam(const char* pszParam,bool bFlag,bool bLast)
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
   void CCommandLineInfo::ParseParam(const char* pszParam, bool bFlag, bool bLast)
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
   void CCommandLineInfo::ParseParamFlag(const char* pszParam)
   {
   // OLE command switches are case insensitive, while
   // shell command switches are case sensitive

   if (lstrcmpA(pszParam, "point") == 0)
   m_nShellCommand = FilePrintTo;
   else if (lstrcmpA(pszParam, "point") == 0)
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
   m_bRunEmbedded = TRUE;
   m_bShowSplash = FALSE;
   }
   else if (::__invariant_stricmp(pszParam, "Automation") == 0)
   {
   m_bRunAutomated = TRUE;
   m_bShowSplash = FALSE;
   }
   }

   void CCommandLineInfo::ParseParamNotFlag(const char* pszParam)
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
   void CCommandLineInfo::ParseParamNotFlag(const char* pszParam)
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

   /////////////////////////////////////////////////////////////////////////////
   // App termination

   void application::SaveStdProfileSettings()
   {
      ASSERT_VALID(this);


      //      if (m_nNumPreviewPages != 0)
      //       WriteProfileInt(gen_PreviewSection, gen_PreviewEntry, m_nNumPreviewPages);
   }


//
//
//
//
//#ifdef WINDOWS_DESKTOP
//
//
//   /////////////////////////////////////////////////////////////////////////////
//   // WinHelp Helper
//
//
//   void application::WinHelp(uptr dwData, ::u32 nCmd)
//   {
//      UNREFERENCED_PARAMETER(dwData);
//      UNREFERENCED_PARAMETER(nCmd);
//
//      // return global cast help mode state to FALSE (backward compatibility)
//      m_bHelpMode = FALSE;
//      // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update
//
//      //trans pMainWnd->WinHelp(dwData, nCmd);
//   }
//
//   /////////////////////////////////////////////////////////////////////////////
//   // HtmlHelp Helper
//
//   void application::HtmlHelp(uptr dwData, ::u32 nCmd)
//   {
//
//      UNREFERENCED_PARAMETER(dwData);
//
//      UNREFERENCED_PARAMETER(nCmd);
//
//      // return global cast help mode state to FALSE (backward compatibility)
//      m_bHelpMode = FALSE;
//      // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update
//
//      // trans pMainWnd->HtmlHelp(dwData, nCmd);
//   }
//
//
//   void application::WinHelpInternal(uptr dwData, ::u32 nCmd)
//   {
//      UNREFERENCED_PARAMETER(dwData);
//      UNREFERENCED_PARAMETER(nCmd);
//      //   __pointer(::user::interaction) pMainWnd = System.m_puiMain;
//      //   ENSURE_VALID(pMainWnd);
//
//      // return global cast help mode state to FALSE (backward compatibility)
//      m_bHelpMode = FALSE;
//      // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update
//      // trans pMainWnd->WinHelpInternal(dwData, nCmd);
//   }
//
//
//#endif
//




   /////////////////////////////////////////////////////////////////////////////
   // application idle processing

   void application::DevModeChange(char * pDeviceName)

   {
      UNREFERENCED_PARAMETER(pDeviceName);


#ifdef WINDOWS
      if (m_hDevNames == nullptr)
         return;

#endif

   }


   //bool application::process_exception(::exception_pointer e)
   //{

   //   return ::acme::application::on_run_exception(pexception))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool application::final_handle_exception(::exception::exception * pexception)
   //{

   //   UNREFERENCED_PARAMETER(pexception);

   //   if (!is_system())
   //   {

   //      if (System.final_handle_exception(pexception))
   //      {

   //         return true;

   //      }

   //   }

   //   return false;

   //}


   /*   bool application::open_link(const char * pszLink, const char * pszTarget)
   {
   UNREFERENCED_PARAMETER(pszLink);
   UNREFERENCED_PARAMETER(pszTarget);
   return false;
   }
   */










   void application::_001OnFileNew()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if (strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      /*      if (m_pdocmanager != nullptr)
      document_manager()->_001OnFileNew();*/
   }

   void application::on_file_open()
   {
      ENSURE(m_pdocmanager != nullptr);
      //document_manager()->on_file_open();
   }


   // This is acme API library.
   //
   //
   //
   //
   //
   //
   //
   //




   /*void ::acme::FormatString1(string & rString, ::u32 nIDS, const char * psz1)

   {
   __format_strings(rString, nIDS, &psz1, 1);

   }

   void ::acme::FormatString2(string & rString, ::u32 nIDS, const char * psz1,

   const char * psz2)

   {
   const char * rgpsz[2];
   rgpsz[0] = psz1;

   rgpsz[1] = psz2;

   __format_strings(rString, nIDS, rgpsz, 2);
   }*/

   /////////////////////////////////////////////////////////////////////////////


   /////////////////////////////////////////////////////////////////////////////
   // Basic Help support (for backward compatibility to acme API 2.0)

   void application::OnHelp()  // use context to derive help context
   {
      if (m_dwPromptContext != 0)
      {
         // do not call WinHelp when the error is failing to lauch help
         //         if (m_dwPromptContext != HID_BASE_PROMPT+__IDP_FAILED_TO_LAUNCH_HELP)
         //          WinHelpInternal(m_dwPromptContext);
         return;
      }

      // otherwise, use window::OnHelp implementation
      /* trans ::user::interaction_impl * pwindow = System.m_puiMain;
      ENSURE_VALID(pwindow);
      if (!pwindow->is_frame_window())
      pwindow->OnHelp();
      else
      ((pwindow))->OnHelp();*/
   }


   void application::OnHelpIndex()
   {
//
//#ifdef WINDOWS_DESKTOP
//
//      WinHelpInternal(0L, HELP_INDEX);
//
//#endif
//
   }


   void application::OnHelpFinder()
   {

//#ifdef WINDOWS_DESKTOP
//
//      WinHelpInternal(0L, HELP_FINDER);
//
//#endif

   }


   void application::OnHelpUsing()
   {

//#ifdef WINDOWS_DESKTOP
//
//      WinHelpInternal(0L, HELP_HELPONHELP);
//
//#endif
//
   }


   /////////////////////////////////////////////////////////////////////////////
   // Context Help Mode support (backward compatibility to acme API 2.0)

   void application::OnContextHelp()
   {
      // just use frame_window::OnContextHelp implementation
      /* trans   m_bHelpMode = HELP_ACTIVE;
      __pointer(::user::frame_window) pMainWnd = (System.m_puiMain);
      ENSURE_VALID(pMainWnd);
      ENSURE(pMainWnd->is_frame_window());
      pMainWnd->OnContextHelp();
      m_bHelpMode = pMainWnd->m_bHelpMode;
      pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update */
   }

   /////////////////////////////////////////////////////////////////////////////


   // This is acme API library.
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
   return FALSE;               // no printer defaults

   ENSURE_ARG(pPrintDlg != nullptr);
   pPrintDlg->hDevNames = m_hDevNames;
   pPrintDlg->hDevMode = m_hDevMode;

   ::GlobalUnlock(m_hDevNames);
   ::GlobalUnlock(m_hDevMode);
   return TRUE;
   }*/

   void application::UpdatePrinterSelection(bool bForceDefaults)
   {
      UNREFERENCED_PARAMETER(bForceDefaults);
   }


   void application::OnFilePrintSetup()
   {
   }

   void application::SelectPrinter(HANDLE hDevNames, HANDLE hDevMode, bool bFreeOld)
   {
      UNREFERENCED_PARAMETER(hDevNames);
      UNREFERENCED_PARAMETER(hDevMode);
      UNREFERENCED_PARAMETER(bFreeOld);
      ::exception::throw_not_implemented();
   }

   ::draw2d::graphics * application::CreatePrinterDC()
   {
      ::exception::throw_not_implemented();
      return nullptr;
   }

   /////////////////////////////////////////////////////////////////////////////


   // This is acme API library.
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

   void application::OnAppExit()
   {

      // same as double-clicking on main window close box

      ASSERT(m_puiMain1 != nullptr);

      m_puiMain1->m_puiThis->send_message(e_message_close);

   }


   void application::HideApplication()
   {

      try
      {

         if (m_puiMain1 == nullptr)
         {

            return;

         }

         // hide the application's windows before closing all the documents
         m_puiMain1->m_puiThis->display(e_display_none);
         // trans    m_puiMain->ShowOwnedPopups(FALSE);


         m_puiMain1->m_puiThis->order(zorder_bottom);
         //m_puiMain->m_puiThis->m_bZ = true;
         // put the window at the bottom of zorder, so it isn't activated
         // m_puiMain->m_puiThis->zorder();

         //m_puiMain->m_puiThis->wait_redraw();

         m_puiMain1->m_puiThis->display(e_display_none);


      }
      catch (...)
      {
      }

   }





   bool application::save_all_modified()
   {
      /*      if (m_pdocmanager != nullptr)
      return document_manager()->save_all_modified();*/
      return TRUE;
   }



//   bool application::OnDDECommand(char * pszCommand)
//
//   {
//      /*      if (m_pdocmanager != nullptr)
//      return document_manager()->OnDDECommand(pszCommand);
//
//      else*/
//      return FALSE;
//   }



   void application::EnableModeless(bool bEnable)
   {
      DoEnableModeless(bEnable);
   }

   void application::DoEnableModeless(bool bEnable)
   {
      UNREFERENCED_PARAMETER(bEnable);
#ifdef ___NO_OLE_SUPPORT
      UNUSED(bEnable);
#endif

      // no-op if main window is nullptr or not a frame_window
      /*   __pointer(::user::interaction) pMainWnd = System.m_puiMain;
      if (pMainWnd == nullptr || !pMainWnd->is_frame_window())
      return;*/

#ifndef ___NO_OLE_SUPPORT
      // check if notify hook installed
      /*xxx
      ASSERT_KINDOF(frame_window, pMainWnd);
      __pointer(::user::frame_window) pFrameWnd = (__pointer(::user::frame_window))pMainWnd;
      if (pFrameWnd->m_pNotifyHook != nullptr)
      pFrameWnd->m_pNotifyHook->OnEnableModeless(bEnable);
      */
#endif
   }


   //i32 application::DoMessageBox(const char * pszPrompt, ::u32 nType, ::u32 nIDPrompt)
   //{

   //   UNREFERENCED_PARAMETER(nIDPrompt);

   //   return message_box(nullptr, pszPrompt, nType);

   //}



//#ifndef VARIADIC_TEMPLATE
//
//   i32 application::message_box(::user::primitive * pwndOwner, ::u32 fuStyle, const char * pszFormat, ...)
//   {
//      va_list va;
//      va_start(va, pszFormat);
//      string str;
//      str.FormatV(pszFormat, va);
//      va_end(va);
//      return message_box(pwndOwner, str, fuStyle);
//   }
//
//#endif
//
//
   // Helper for message boxes; can work when no application can be found
   //i32 application::ShowAppMessageBox(__pointer(application)pApp, const char * pszPrompt, ::u32 nType, ::u32 nIDPrompt)

   //{

   //   __throw(not_implemented());

   //}


   /* i32 ::acme::message_box(const char * pszText, ::u32 nType, ::u32 nIDHelp)

   {
   application* papp = &System;
   if (papp != nullptr)
   {
   return papp->DoMessageBox(pszText, nType, nIDHelp);

   }
   else
   {
   return application::ShowAppMessageBox(nullptr, pszText, nType, nIDHelp);

   }
   }
   */

   /*i32 System.message_box(::u32 nIDPrompt, ::u32 nType, ::u32 nIDHelp)
   {
   string string;
   if (!string.load_string(nIDPrompt))
   {
   TRACE(trace_category_appmsg, 0, "Error: failed to load message box prompt string 0x%04x.\n",
   nIDPrompt);
   ASSERT(FALSE);
   }
   if (nIDHelp == (::u32)-1)
   nIDHelp = nIDPrompt;
   return System.message_box(string, nType, nIDHelp);
   }*/








   void application::RegisterShellFileTypes(bool bCompat)
   {
      ENSURE(m_pdocmanager != nullptr);
      //      document_manager()->RegisterShellFileTypes(bCompat);
   }

   void application::UnregisterShellFileTypes()
   {
      ENSURE(m_pdocmanager != nullptr);
      //    document_manager()->UnregisterShellFileTypes();
   }


   i32 application::get_open_document_count()
   {
      ENSURE(m_pdocmanager != nullptr);
      //  return document_manager()->get_open_document_count();
      return 0;
   }


   // This is acme API library.
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


   void application::SetRegistryKey(const char * pszRegistryKey)

   {
      //ASSERT(m_pszRegistryKey == nullptr);
      //ASSERT(pszRegistryKey != nullptr);

      //ASSERT(m_strAppName.has_char());

      ////bool bEnable = __enable_memory_tracking(FALSE);
      //free((void *)m_pszRegistryKey);
      //m_pszRegistryKey = strdup(pszRegistryKey);

      //free((void *)m_pszProfileName);
      //m_pszProfileName = strdup(m_strAppName);
      ////__enable_memory_tracking(bEnable);
   }

   void application::SetRegistryKey(::u32 nIDRegistryKey)
   {
      //UNREFERENCED_PARAMETER(nIDRegistryKey);
      //ASSERT(m_pszRegistryKey == nullptr);
      //::exception::throw_not_implemented();
      ///*char szRegistryKey[256];
      //VERIFY(::acme::LoadString(nIDRegistryKey, szRegistryKey));
      //SetRegistryKey(szRegistryKey);*/
   }


#ifdef WINDOWS_DESKTOP

   // returns key for HKEY_CURRENT_USER\"Software"\RegistryKey\ProfileName
   // creating it if it doesn't exist
   // responsibility of the caller to call RegCloseKey() on the returned HKEY
   HKEY application::GetAppRegistryKey()
   {
      //ASSERT(m_pszRegistryKey != nullptr);
      //ASSERT(m_pszProfileName != nullptr);

      //HKEY hAppKey = nullptr;
      //HKEY hSoftKey = nullptr;
      //HKEY hCompanyKey = nullptr;
      //if(RegOpenKeyEx(HKEY_CURRENT_USER,"software",0,KEY_WRITE | KEY_READ,
      //   &hSoftKey) == ERROR_SUCCESS)
      //{
      //   ::u32 dw;
      //   if(RegCreateKeyEx(hSoftKey,m_pszRegistryKey,0,REG_NONE,
      //      REG_OPTION_NON_VOLATILE,KEY_WRITE | KEY_READ,nullptr,
      //      &hCompanyKey,&dw) == ERROR_SUCCESS)
      //   {
      //      RegCreateKeyEx(hCompanyKey,m_pszProfileName,0,REG_NONE,
      //         REG_OPTION_NON_VOLATILE,KEY_WRITE | KEY_READ,nullptr,
      //         &hAppKey,&dw);
      //   }
      //}
      //if(hSoftKey != nullptr)
      //   RegCloseKey(hSoftKey);
      //if(hCompanyKey != nullptr)
      //   RegCloseKey(hCompanyKey);

//      return hAppKey;
      return nullptr;
   }

   // returns key for:
   //      HKEY_CURRENT_USER\"Software"\RegistryKey\AppName\pszSection

   // creating it if it doesn't exist.
   // responsibility of the caller to call RegCloseKey() on the returned HKEY
   HKEY application::GetSectionKey(const char * pszSection)

   {
      ASSERT(pszSection != nullptr);


      HKEY hSectionKey = nullptr;
      HKEY hAppKey = GetAppRegistryKey();
      if (hAppKey == nullptr)
         return nullptr;

      ::u32 dw;
      RegCreateKeyExW(hAppKey,wstring( pszSection), 0, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, nullptr, &hSectionKey, &dw);

      RegCloseKey(hAppKey);
      return hSectionKey;
   }

#endif

   /*   ::u32 application::GetProfileInt(const char * pszSection, const char * pszEntry,

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

   string application::GetProfileString(const char * pszSection, const char * pszEntry,

   const char * pszDefault)

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

   bool application::GetProfileBinary(const char * pszSection, const char * pszEntry,

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
   return FALSE;
   }

   // ensure destruction

   // linux ::acme::CRegKey rkSecKey(hSecKey);

   u32 dwType=0;
   u32 dwCount=0;
   ::i32 lResult = RegQueryValueEx(hSecKey, (char *)pszEntry, nullptr, &dwType, nullptr, &dwCount);

   *pBytes = dwCount;
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_BINARY);
   *ppData = new byte[*pBytes];
   lResult = RegQueryValueEx(hSecKey, (char *)pszEntry, nullptr, &dwType,

   *ppData, &dwCount);
   }
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_BINARY);
   return TRUE;
   }
   else
   {
   delete [] *ppData;
   *ppData = nullptr;
   }
   return FALSE;
   }
   else
   {
   ASSERT(m_pszProfileName != nullptr);

   string str = GetProfileString(pszSection, pszEntry, nullptr);

   if (str.is_empty())
   return FALSE;
   ASSERT(str.get_length()%2 == 0);
   iptr nLen = str.get_length();
   *pBytes = ::u32(nLen)/2;
   *ppData = new byte[*pBytes];
   for (i32 i=0;i<nLen;i+=2)
   {
   (*ppData)[i/2] = (byte)
   (((str[i+1] - 'A') << 4) + (str[i] - 'A'));
   }
   return TRUE;
   }
   }


   bool application::WriteProfileInt(const char * pszSection, const char * pszEntry,

   i32 nValue)
   {
   ASSERT(pszSection != nullptr);

   ASSERT(pszEntry != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return FALSE;
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

   bool application::WriteProfileString(const char * pszSection, const char * pszEntry,

   const char * pszValue)

   {
   ASSERT(pszSection != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   ::i32 lResult;
   if (pszEntry == nullptr) //delete whole department

   {
   HKEY hAppKey = GetAppRegistryKey();
   if (hAppKey == nullptr)
   return FALSE;
   lResult = ::RegDeleteKey(hAppKey, pszSection);

   RegCloseKey(hAppKey);
   }
   else if (pszValue == nullptr)

   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return FALSE;
   // necessary to cast away const below
   lResult = ::RegDeleteValue(hSecKey, (char *)pszEntry);

   RegCloseKey(hSecKey);
   }
   else
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return FALSE;
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

   bool application::WriteProfileBinary(const char * pszSection, const char * pszEntry,

   byte * pData, ::u32 nBytes)
   {
   ASSERT(pszSection != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   ::i32 lResult;
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return FALSE;
   lResult = RegSetValueEx(hSecKey, pszEntry, nullptr, REG_BINARY,

   pData, nBytes);
   RegCloseKey(hSecKey);
   return lResult == ERROR_SUCCESS;
   }

   // convert to string and write out
   char * psz = new char[nBytes*2+1];

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




   /*   property_set & application::propset(matter * pobject)
   {
   single_lock sl(&m_mapObjectSet, TRUE);
   return m_mapObjectSet[pobject];
   }

   property_set * application::existing_propset(matter * pobject)
   {
   single_lock sl(&m_mapObjectSet, TRUE);
   auto point = m_mapObjectSet.plookup(pobject);
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

      if (m_puiMain1 != nullptr)
      {

         m_puiMain1->m_puiThis->display(SW_SHOWNORMAL);

      }

      return true;

   }


   void application::term()
   {

      try
      {

         ::acme::application::term();

      }
      catch (...)
      {

         m_result.add(error_failed);

      }

   }


   ::user::interaction * application::get_request_parent_ui(::user::interaction * pinteraction, ::create * pcreate)
   {

      ::user::interaction * puiParent = nullptr;

      if (puiParent == nullptr)
      {
         puiParent = dynamic_cast < ::user::interaction * > (pcreate->m_puserinteractionParent);
      }

//      if (puiParent == nullptr && pcreate->m_papplicationbias.is_set())
//      {
//         puiParent = dynamic_cast < ::user::interaction * > (pcreate->m_papplicationbias->m_puserinteractionParent);
//      }

      //if(puiParent == nullptr && m_psession != nullptr && m_psession->m_psession != nullptr && !pcreate->m_bClientOnly
      /*if (puiParent == nullptr && m_psession != nullptr && m_psession != nullptr
            && !pcreate->m_bOuterPopupAlertLike && m_psession != dynamic_cast < session * > (this))
      {
         puiParent = psession->get_request_parent_ui(pinteraction, pcreate);
      }*/

      return puiParent;

   }







   void application::_001OnFileNew(::message::message * pmessage)
   {

      payload varFile;

      payload varQuery;

      varQuery["command"] = "new_file";

      request_file(varFile, varQuery);

      pmessage->m_bRet = true;

   }



//   bool application::on_open_document_file(payload varFile)
//   {
//
//      return _001OpenDocumentFile(varFile);
//
//   }

   ::user::document * application::_001OpenDocumentFile(payload varFile)
   {

      request_file(varFile);

      return varFile["document"].cast < ::user::document >();

   }


   bool application::_001OnDDECommand(const char * pcsz)

   {
      ::exception::throw_not_implemented();
      //return m_pimpl->_001OnDDECommand(pcsz);


      return false;
   }

   //   ::acme::file_system & application::file_system()
   // {
   //  return m_spfilesystem;
   //}







   ::user::interaction * application::get_desktop_window()
   {
#if defined(_UWP) || defined(APPLEOS)
      __throw(todo());
      /*#elif defined(LINUX)

      //      sync_lock sl(&user_mutex());

      xdisplay pdisplay.
      pdisplay.open(nullptr) = x11_get_display();

      oswindow window(pdisplay, DefaultRootWindow(pdisplay));

      XCloseDisplay(pdisplay);

      return window_from_os_data(window);
      */
#else
      return System.ui_from_handle(::get_desktop_window());
#endif
   }





   void application::assert_valid() const
   {
      thread::assert_valid();


      if (::get_task() != (thread*)this)
         return;     // only do subset if called from different thread

      ASSERT(::get_task() == this);
      //ASSERT(afxCurrentInstanceHandle == m_hInstance);

      /*      if (m_pdocmanager != nullptr)
      ASSERT_VALID(m_pdocmanager);*/
   }

   void application::dump(dump_context & dumpcontext) const
   {

      ::acme::application::dump(dumpcontext);

      dumpcontext << "\nm_bHelpMode = " << m_bHelpMode;
      dumpcontext << "\nm_pszHelpFilePath = " << m_strHelpFilePath;
      dumpcontext << "\nm_pszProfileName = " << m_strProfileName;

#ifdef WINDOWS
      dumpcontext << "\nm_hDevMode = " << (void *)m_hDevMode;
      dumpcontext << "\nm_hDevNames = " << (void *)m_hDevNames;
#endif

      dumpcontext << "\nm_dwPromptContext = " << (::u32)m_dwPromptContext;
      //      dumpcontext << "\nm_eHelpType = " << m_eHelpType;


      /*      if (m_pdocmanager != nullptr)
      document_manager()->dump(dumpcontext);*/

      dumpcontext << "\nm_nWaitCursorCount = " << m_iWaitCursorCount;
      dumpcontext << "\nm_nNumPreviewPages = " << m_nNumPreviewPages;

      dumpcontext << "\n";
   }


   void application::install_message_routing(::channel * pchannel)
   {

      acme::application::install_message_routing(pchannel);

      connect_command("switch_context_theme", &application::_001OnSwitchContextTheme);

   }


   bool application::base_support()
   {

      //if(!application::base_support())
      // return false;

      if (m_strBaseSupportId.is_empty())
      {

         property_set propertyset;

         dialog_box("err\\developer\\base_support\\support_id_not_specified.xml", propertyset);

         return false;

      }

      return true;
   }


   //string application::sync_message_box(const string & pszMatter, property_set & propertyset)
   //{
   //
   //   UNREFERENCED_PARAMETER(propertyset);
   //
   //   UNREFERENCED_PARAMETER(pszMatter);
   //
   //   return "";

   //}


//   ::e_status application::bergedge_start()
//   {
//
//      string strId = m_strId;
//
//      char chFirst = '\0';
//
//      if (strId.get_length() > 0)
//      {
//
//         chFirst = strId[0];
//
//      }
//
//      return true;
//
//   }


#ifdef WINDOWS_DESKTOP


   bool Is_Vista_or_Later()
   {
      OSVERSIONINFOEX osvi;
      DWORDLONG dwlConditionMask = 0;
      byte op = VER_GREATER_EQUAL;

      // Initialize the OSVERSIONINFOEX structure.

      ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
      osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
      osvi.dwMajorVersion = 6;
      //   osvi.dwMinorVersion = 1;
      //   osvi.wServicePackMajor = 0;
      //   osvi.wServicePackMinor = 0;

      // Initialize the condition mask.

      VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, op);
      //VER_SET_CONDITION( dwlConditionMask, VER_MINORVERSION, op );
      //VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMAJOR, op );
      //VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMINOR, op );

      // Perform the test.

      return VerifyVersionInfo(
             &osvi,
             VER_MAJORVERSION | VER_MINORVERSION |
             VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR,
             dwlConditionMask) != FALSE;
   }


#endif


   ::e_status application::init()
   {

      if (!::acme::application::init())
      {

         return false;

      }

      xxdebug_box("::acme::application::initialize ok", "::acme::application::initialize ok", e_message_box_icon_information);

      xxdebug_box("m_pcalculator::initialize ok", "m_pcalculator::initialize ok", e_message_box_icon_information);

      xxdebug_box("m_pcolorertake5::initialize ok", "m_pcolorertake5::initialize ok", e_message_box_icon_information);
m_millisHeartBeat.Now();

      if (!initialize_userex())
      {

         return false;

      }

      xxdebug_box("m_pfilemanager::initialize ok", "m_pfilemanager::initialize ok", e_message_box_icon_information);

      xxdebug_box("m_pusermail::initialize ok", "m_pusermail::initialize ok", e_message_box_icon_information);
m_millisHeartBeat.Now();

      xxdebug_box("register_bergedge_application ok", "register_bergedge_application ok", e_message_box_icon_information);
m_millisHeartBeat.Now();

      ensure_app_interest();

      xxdebug_box("ensure_app_interest ok", "ensure_app_interest ok", e_message_box_icon_information);

      return true;

   }


   void application::pre_translate_message(::message::message * pmessage)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

      if (pbase->m_id == WM_USER + 124 && pbase->m_puserinteraction == nullptr)
      {

         /*

         OnMachineEvent((flags < machine_event::enum_flag> *) pmsg->lParam);
         delete (flags < machine_event::enum_flag> *) pmsg->lParam;

         */

         pbase->m_bRet = true;

         return;

      }

      return thread::pre_translate_message(pmessage);

   }


   void application::_001CloseApplication()
   {

      acme::application::_001CloseApplication();

   }


   void application::on_create_split_view(::user::split_view * psplit)
   {

   }


   void application::EnableShellOpen()
   {

      ASSERT(m_atomApp == 0 && m_atomSystemTopic == 0); // do once

      if (m_atomApp != 0 || m_atomSystemTopic != 0)
      {

         return;

      }

      // Win95 & Win98 sends a WM_DDE_INITIATE with an atom that points to the
      // i16 file name so we need to use the i16 file name.
      string strShortName;

      strShortName = Context.file().module();

      // strip out path
      //string strFileName = ::PathFindFileName(strShortName);
      // strip out extension
      //char * pszFileName = strFileName.GetBuffer();
      //::PathRemoveExtension(pszFileName);
      //strFileName.ReleaseBuffer();

      //      m_atomApp = ::GlobalAddAtom(strFileName);
      //    m_atomSystemTopic = ::GlobalAddAtom("system");

   }


   __pointer(::user::interaction) application::uie_from_point(const ::point & point)
   {

      user::interaction_pointer_array wnda = *m_puiptraFrame;

      user::oswindow_array oswindowa;

      oswindowa = wnda.get_hwnda();

      user::window_util::SortByZOrder(oswindowa);

      for (i32 i = 0; i < oswindowa.get_count(); i++)
      {

         __pointer(::user::interaction) puieWindow = wnda.find_first(oswindowa[i]);

         __pointer(::user::interaction) puie = puieWindow->_001FromPoint(point);

         if (puie != nullptr)
         {

            return puie;

         }

      }

      return nullptr;

   }


   bool application::on_install()
   {

      if (!::acme::application::on_install())
      {

         return false;

      }

      string strId = m_strId;

      char chFirst = '\0';

      if (strId.get_length() > 0)
      {

         chFirst = strId[0];

      }

      return true;

   }


   bool application::on_run_install()
   {

      if (m_strId == "session" || m_strAppName == "session")
      {

         if (!command() || !has_property("session_start"))
         {

            ::parallelization::set_finish(&System);

         }

      }
      else
      {

         ::parallelization::set_finish(&System);

      }

      return true;

   }


   bool application::on_uninstall()
   {

      bool bOk = ::acme::application::on_uninstall();

      string strId = m_strId;

      char chFirst = '\0';

      if (strId.get_length() > 0)
      {

         chFirst = strId[0];

      }

      return bOk;

   }


   bool application::on_run_uninstall()
   {

      if (m_strId == "session")
      {

         if (!command() && !has_property("session_start"))
         {

            ::parallelization::set_finish(&System);

         }

      }
      else
      {

         ::parallelization::set_finish(&System);

      }

      return true;

   }


   void application::on_application_signal(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   ::acme::printer * application::get_printer(const char * pszDeviceName)
   {

      return nullptr;

   }


   bool application::set_keyboard_layout(const char * pszPath, const ::action_context & context)
   {

      return psession->keyboard().load_layout(pszPath, context);

   }


   i32 application::track_popup_menu(const char * pszMatter, const ::point & point, __pointer(::user::interaction) puie)
   {

      UNREFERENCED_PARAMETER(pszMatter);
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(puie);

      return 1;

   }


   bool application::get_fs_size(string & strSize, const char * pszPath, bool & bPending)
   {

      i64 i64Size;

      if (!get_fs_size(i64Size, pszPath, bPending))
      {

         strSize.Empty();

         return false;

      }

      if (i64Size > 1024 * 1024 * 1024)
      {

         double d = (double)i64Size / (1024.0 * 1024.0 * 1024.0);

         strSize.Format("%0.2f GB", d);

      }
      else if (i64Size > 1024 * 1024)
      {

         double d = (double)i64Size / (1024.0 * 1024.0);

         strSize.Format("%0.1f MB", d);

      }
      else if (i64Size > 1024)
      {

         double d = (double)i64Size / (1024.0);

         strSize.Format("%0.0f KB", d);

      }
      else if (i64Size > 0)
      {

         strSize.Format("1 KB");

      }
      else
      {

         strSize.Format("0 KB");

      }

      if (bPending)
      {

         strSize = "~" + strSize;

      }

      return true;

   }


   bool application::get_fs_size(i64 & i64Size, const char * pszPath, bool & bPending)
   {
      return false;
      //db_server * pcentral = dynamic_cast <db_server *> (&System.m_psimpledb->db());

      //if (pcentral == nullptr)
      //{

      //   return false;

      //}

      //return pcentral->m_pfilesystemsizeset->get_cache_fs_size(i64Size, pszPath, bPending);

   }


   void application::set_title(const char * pszTitle)
   {

      psession->set_app_title(m_strAppName, pszTitle);

   }


   bool application::_001CloseApplicationByUser(__pointer(::user::interaction) pwndExcept)
   {

      // Closing just this application.
      // It is different of a system exit.
      // System (a single ca2 process) can host
      // multiple ca2 application objects.

      // attempt to save all documents
      if (!save_all_modified())
      {

         return false;     // don't close it

      }

      // hide the application's windows before closing all the documents
      HideApplication();

      close(::acme::end_app);

      return true;

   }


   oswindow application::get_ca2_app_wnd(const char * psz)
   {

      UNREFERENCED_PARAMETER(psz);

      return nullptr;

   }


   i32 application::send_simple_command(const char * psz, void * osdataSender)
   {
      string strApp;
      string_array stra;
      stra.add_tokens(psz, "::", true);
      if (stra.get_size() > 0)
      {
         strApp = stra[0];
         oswindow oswindow = get_ca2_app_wnd(strApp);
         if (oswindow != nullptr)
         {
            return send_simple_command((void *)oswindow, psz, osdataSender);
         }
      }
      return -1;
   }


   i32 application::send_simple_command(void * osdata, const char * psz, void * osdataSender)
   {
#ifdef WINDOWS_DESKTOP
      ::oswindow oswindow = (::oswindow) osdata;
      if (!::IsWindow(oswindow))
         return -1;
      COPYDATASTRUCT cds;
      __memset(&cds, 0, sizeof(cds));
      cds.dwData = 888888;
      cds.cbData = (u32)strlen(psz);
      cds.lpData = (PVOID)psz;

      return (i32)SendMessage(oswindow, WM_COPYDATA, (WPARAM)osdataSender, (LPARAM)&cds);
#else
      __throw(todo());
#endif
   }


   void application::ensure_app_interest()
   {

#ifndef _UWP

      for (i32 i = 0; i < m_straAppInterest.get_count(); i++)
      {
         if (m_straAppInterest[i] != m_strAppName && !::is_window(m_mapAppInterest[m_straAppInterest[i]]))
         {
            System.assert_running_local(m_straAppInterest[i]);
         }
      }

#else

      //__throw(todo());

#endif

   }




   //::acme::application * application::get_context_system()
   //{

   //   return ::matter::get_context_system();

   //}


















   /*
   __pointer(::acme::application) application::assert_running(const char * pszAppId)
   {


   __pointer(::acme::application) papp = nullptr;


   try
   {

   bool bFound = false;

   for(i32 i  = 0; i < System.m_appptra.get_count(); i++)
   {
   try
   {

   papp = System.m_appptra(i);

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

   __pointer(::create) spcreate(e_create);

   papp = psession->start_application("application", pszAppId, spcreate);

   }

   }
   catch(const ::exit_exception & e)
   {

   __throw(e);

   }
   catch(const ::exception_pointer pe)
   {

   if(!Application.on_run_exception((::exception::exception &) e))
   __throw(exit_exception());

   }
   catch(...)
   {

   papp = nullptr;

   }


   return papp;

   }
   */





   //typedef  void (* PFN_factory_exchange)();




   file_pointer application::friendly_get_file(payload varFile, ::u32 nOpenFlags)
   {

      try
      {

         return Context.file().get_file(varFile, nOpenFlags);

      }
      catch (::file::exception & e)
      {

         string strMessage = e.get_message();

         Application.message_box(strMessage);

         return nullptr;

      }

   }









   //__pointer(::acme::application) application::create_application(const char * pszType,const char * pszId,bool bSynch,application_bias * pbias)
   //{

   //   __pointer(::acme::application) pbaseapp = instantiate_application(pszType,pszId,pbias);

   //   if(pbaseapp == nullptr)
   //      return nullptr;

   //   ::acme::application * papp = (pbaseapp);

   //   if(!papp->start_application(bSynch,pbias))
   //   {
   //      try
   //      {
   //         pbaseapp.release();
   //      }
   //      catch(...)
   //      {
   //      }
   //      return nullptr;
   //   }


   //   return pbaseapp;

   //}




   ::user::document * application::place_hold(::user::interaction * pinteraction)
   {

      return nullptr;

   }



   //::e_status application::add_library(::acme::library * plibrary)
   //{

   //   plibrary->set_context_object(this);

   //   System.add_library(plibrary);

   //   return true;

   //}


   void application::data_on_after_change(::message::message * pmessage)
   {

      SCAST_PTR(::database::change_event, pchange, pmessage);

      if (pchange->m_datakey.m_strDataKey == "ca2.savings")
      {

         psession->savings().m_eresourceflagsShouldSave = (::acme::e_resource) pchange->data_get().i32();

      }

   }


   i32 application::GetVisibleTopLevelFrameCountExcept(__pointer(::user::interaction) pwndExcept)
   {

      ::user::interaction_pointer_array wnda = *m_puiptraFrame;

      i32 iCount = 0;
      for (i32 i = 0; i < wnda.get_size(); i++)
      {
         __pointer(::user::interaction) pwnd = wnda.element_at(i);
         __pointer(simple_frame_window) pframewindow = pwnd;
         bool bDefaultNotifyIcon = (pframewindow.is_set() && pframewindow->m_bDefaultNotifyIcon);
         if (pwnd != nullptr &&
               pwnd != pwndExcept &&
               pwnd->is_window() &&
               (pwnd->is_window_visible()|| bDefaultNotifyIcon) &&
               pwnd->get_window_type() == ::user::interaction::type_frame &&
               !(pwnd->GetStyle() & WS_CHILD))
         {
            iCount++;
         }
      }
      return iCount;
   }


   i32 application::GetVisibleFrameCount()
   {

      ::user::interaction_pointer_array wnda = *m_puiptraFrame;

      i32 iCount = 0;
      for (i32 i = 0; i < wnda.get_size(); i++)
      {
         __pointer(::user::interaction) pwnd = wnda.element_at(i);
         if (pwnd != nullptr
               && pwnd->is_window()
               && pwnd->is_window_visible())
         {
            iCount++;
         }
      }
      return iCount;
   }


   void application::on_create_keyboard()
   {

      string str;

      // keyboard on_layout
      //if(data_get("keyboard_layout",str) && str.has_char())
      {
         // psession->set_keyboard_layout(str,::e_source_database);
      }
      //else
      {
         set_keyboard_layout(nullptr, ::e_source_database);
      }

   }


   //::type application::user_default_controltype_to_typeinfo(enum user::enum_control_type econtroltype)
   //{

   //   return Sess(this).userex()->controltype_to_typeinfo(econtroltype);

   //}


   //bool application::platform_open_by_file_extension(int iEdge, const char * pszPathName, application_bias * papplicationbias)
   //{

   //   return System.get_platform(iEdge)->open_by_file_extension(pszPathName, papplicationbias);
   //}

   //bool application::platform_open_by_file_extension(int iEdge, ::create * pcc)
   //{

   //   return System.get_platform(iEdge)->open_by_file_extension(pcc);
   //}


   __pointer(::acme::application) application::create_platform(::acme::session * psession)
   {

      return __new(::acme::session);

   }


   void application::on_change_cur_sel(::user::tab * ptab)
   {



   }


   bool application::_001OnAgreeExit()
   {

      if(!save_all_modified())
      {

         return false;

      }

      return true;

   }


   void application::_001OnFranceExit()
   {

      ::acme::application::_001OnFranceExit();

   }


   void application::prepare_form(id id, ::form_document * pdocument)
   {



   }


   void application::report_error(::exception::exception * pexception, int iMessageFlags, const char * pszTopic)
   {

      string strMessage;

      strMessage += pszTopic;

      strMessage += " : ";

      strMessage += pexception->get_message();

      m_puiMain1->message_box(strMessage + ::enum_message_box(iMessageFlags));

   }


   bool application::on_close_frame_window(::user::frame * pframe)
   {

      if (GetVisibleTopLevelFrameCountExcept(pframe) <= 0)
      {

         _001CloseApplication();

      }
      else
      {

         pframe->hide();

      }

      return true;

   }


   ::type application::control_type_from_id(const ::id & id, ::user::enum_control_type & econtroltype)
   {

      string str(id);

      if (str.begins_ci("combo_"))
      {

         econtroltype = ::user::e_control_type_combo_box;

         return __type(::user::combo_box);

      }
      else if (str.begins_ci("check_") || str.begins_ci("checkbox_"))
      {

         econtroltype = ::user::e_control_type_check_box;

         return __type(::user::check_box);

      }
      else if (str.begins_ci("still_"))
      {

         econtroltype = ::user::e_control_type_static;

         return __type(::user::still);

      }
      else if (str.begins_ci("label_"))
      {

         econtroltype = ::user::e_control_type_static;

         return __type(::user::still);

      }
      else if (str.begins_ci("edit_"))
      {

         econtroltype = ::user::e_control_type_edit_plain_text;

         return __type(::user::plain_edit);

      }
      else if (str.begins_ci("button_"))
      {

         econtroltype = ::user::e_control_type_button;

         return __type(::user::button);

      }

      return ::acme::application::control_type_from_id(id, econtroltype);

   }


   string application::get_theme()
   {

      if (!m_ptheme)
      {

         return ::acme::application::get_theme();

      }

      return m_ptheme->get_theme();

   }


   ::e_status application::initialize_contextualized_theme()
   {

      auto estatus = __compose_new(m_ptheme);

      if (!estatus)
      {

         return estatus;

      }

      if (m_bContextTheme)
      {

         estatus = m_ptheme->initialize_contextualized_theme();

         if (!estatus)
         {

            return estatus;

         }

      }

      return estatus;

   }


   void application::on_change_theme()
   {


   }


   void application::_001OnSwitchContextTheme(::message::message * pmessage)
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

   //   create_factory < ::user::user >();

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


   //::e_status application::initialize(::matter* pobjectContext)
   //{

   //   auto estatus = ::acme::application::initialize(pobjectContext);

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


      //void application::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
      //{

      //   ::acme::application::on_subject(psubject, pcontext);

      //   if (pupdate->m_bRet)
      //   {
      //
      //      return;

      //   }
      //
      //   ::user::form_callback::on_subject(psubject, pcontext);

      //   if (pupdate->m_bRet)
      //   {

      //      return;

      //   }

      //}


   //::e_status application::process_init()
   //{

   //   if (::acme::application::process_init())
   //   {

   //      return true;

   //   }

   //   return true;

   //}


   //::e_status application::init_instance()
   //{

   //   if (!::acme::application::init_instance())
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


   ::e_status     application::create_impact_system()
   {

      return ::success;

   }


   void application::process_message_filter(i32 code, ::message::message* pmessage)
   {

      if (pmessage == nullptr)
         return;   // not handled

      SCAST_PTR(::message::base, pbase, pmessage);

      __pointer(::user::frame_window) pTopFrameWnd;
      //::user::interaction * pMainWnd;
      ::user::interaction* pMsgWnd;
      switch (code)
      {
         //case MSGF_DDEMGR:
         // Unlike other WH_MSGFILTER codes, MSGF_DDEMGR should
         //  never call the next hook.
         // By returning FALSE, the message will be dispatched
         //  instead (the default behavior).
         //return;

      case MSGF_MENU:

         pMsgWnd = dynamic_cast <::user::interaction*> (pbase->m_puserinteraction);

         if (pMsgWnd != nullptr)
         {
            pTopFrameWnd = pMsgWnd->GetTopLevelFrame();
            if (pTopFrameWnd != nullptr && pTopFrameWnd->IsTracking() &&
               pTopFrameWnd->m_bHelpMode)
            {
               //pMainWnd = __get_main_window();
               //if((m_puiMain != nullptr) && (IsEnterKey(pbase) || IsButtonUp(pbase)))
               //{
               //   //                  pMainWnd->SendMessage(e_message_command, ID_HELP);
               //   pbase->m_bRet = true;
               //   return;
               //}
            }
         }
         // fall through...

      case MSGF_DIALOGBOX:    // handles message boxes as well.
         //pMainWnd = __get_main_window();
         if (code == MSGF_DIALOGBOX && m_puiActive != nullptr &&
            pbase->m_id >= e_message_key_first && pbase->m_id <= e_message_key_last)
         {
         }
         break;
      }
      // default to not handled

   }





















   /*string application::get_cred(const string & strRequestUrlParam,const ::rect & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive)
   {

      string str = ::account::get_cred(this,strUsername,strPassword,strToken);

      if(str == "ok" && strUsername.has_char() && strPassword.has_char())
         return "ok";

      if(!bInteractive)
         return "failed";

      __pointer(::account::simple_ui) pinteraction;

      string strRequestUrl(strRequestUrlParam);

      if(strRequestUrl.is_empty())
      {

         string strIgnitionServer = file_as_string(::dir::system() / "config\\system\\ignition_server.txt");

         if(::str::ends_ci(strIgnitionServer,".ca2.cc"))
         {

            strRequestUrl = "https://" + strIgnitionServer + "/";

         }
         else
         {

            strRequestUrl = "https://account.ca2.cc/";

         }

         strRequestUrl = "https://account.ca2.cc/";

      }

      pinteraction = __new(::account::simple_ui(this,strRequestUrl));

      pinteraction->m_login.m_peditUser->set_window_text(strUsername);

      pinteraction->m_login.m_ppassword->set_window_text("");

      string strResult = pinteraction->get_cred(rect,strUsername,strPassword,strToken,strTitle);

      pinteraction->DestroyWindow();

      ::account::set_cred(this,strToken,strUsername,strPassword);

      return strResult;

   }*/


   //__pointer(::user::user) application::create_user()
   //{

   //   return __new(::user::user);

   //}


   bool application::on_thread_on_idle(::thread * pthread, ::i32 lCount)
   {

      if (lCount <= 0)
      {

         __pointer(::user::interaction) pinteraction;

         while (get_frame(pinteraction))
         {
            //::user::interaction * pinteraction = (::user::interaction *) pimpl->m_spuiptra->element_at(i)->m_pvoidUserInteraction;
            bool bOk = false;
            try
            {

               bOk = pinteraction != nullptr && pinteraction->is_window_visible();
            }
            catch (...)
            {
            }
            if (!bOk)
            {
               //   try
               //   {
               //      Application.remove_frame(pinteraction);
               //   }
               //   catch(...)
               //   {
               //   }
               //   try
               //   {
               //      psession->remove_frame(pinteraction);
               //   }
               //   catch(...)
               //   {
               //   }
               //   try
               //   {
               //      System.remove_frame(pinteraction);
               //   }
               //   catch(...)
               //   {
               //   }
            }
            else
            {
               //               sl.unlock();
               try
               {
                  pinteraction->send_message(WM_IDLEUPDATECMDUI, (WPARAM)TRUE);
               }
               catch (...)
               {

               }
               //             sl.lock();
            }
         }


      }
      else if (lCount >= 0)
      {
      }

      return lCount < 0;  // nothing more to do if lCount >= 0

   }




   void application::on_create_impact(::user::impact_data* pimpactdata)
   {


   }


   bool application::process_message()
   {

      return ::thread::process_message();

   }


   //void application::SetCurrentHandles()
   //{

   //   ::acme::application::SetCurrentHandles();

   //}


   //void application::term_application()
   //{

   //   try
   //   {

   //      acme::application::term_application();

   //   }
   //   catch (...)
   //   {

   //   }

   //}


   ::draw2d::icon* application::set_icon(matter* pobject, ::draw2d::icon* picon, bool bBigIcon)
   {

      ::draw2d::icon* piconOld = get_icon(pobject, bBigIcon);

      if (bBigIcon)
      {

         pobject->value("big_icon") = (__pointer(matter)) picon;

      }
      else
      {

         pobject->value("small_icon") = (__pointer(matter)) picon;

      }

      return piconOld;

   }


   ::draw2d::icon* application::get_icon(matter* pobject, bool bBigIcon) const
   {

      if (bBigIcon)
      {

         return const_cast <matter*> (pobject)->cast < ::draw2d::icon >("big_icon");

      }
      else
      {

         return const_cast <matter*> (pobject)->cast < ::draw2d::icon >("small_icon");

      }

   }


   void application::on_control_event(::user::control_event* pevent)
   {

      if (pevent->m_eevent == ::user::e_event_initialize_control)
      {

         if (pevent->m_puie->m_id == __id(system_startup_checkbox))
         {

            try
            {
               __pointer(::user::check) pcheck = pevent->m_puie;

               if (pcheck.is_set())
               {

                  pcheck->_001SetCheck(
                     Context.os().is_user_auto_start(get_executable_appid()),
                     ::e_source_initialize);

               }
            }
            catch (...)
            {

            }

         }

      }
      else if (pevent->m_eevent == ::user::e_event_set_check)
      {

         if (pevent->m_puie->m_id == __id(system_startup_checkbox)
            && pevent->m_actioncontext.is_user_source())
         {

            try
            {

               __pointer(::user::check) pcheck = pevent->m_puie;

               if (pcheck.is_set())
               {

                  Context.os().register_user_auto_start(
                     get_executable_appid(),
                     get_executable_path(),
                     pcheck->echeck() == ::check_checked);

               }

               pevent->m_bRet = true;

               return;

            }
            catch (...)
            {

            }

         }

      }

   }


   ::user::interaction* application::create_menu_interaction()
   {

      return __new(::user::button);

   }


   __pointer(::user::document) application::defer_create_view(string strView, ::user::interaction* puiParent, ewindowflag ewindowflag, const ::id& id)
   {

      auto pcontroller = ::acme::application::defer_create_view(strView, puiParent, ewindowflag, id);

      if (pcontroller)
      {

         return pcontroller;

      }

      return nullptr;

   }


   void application::on_song_added(const string & str)
   {

   }


   //::type application::control_type_from_id(const ::id& id, ::user::enum_control_type& econtroltype)
   //{

   //
   //}


   //::form_property_set * application::get_form_property_set()
   //{

   //   auto pset = ::user::form_callback::get_form_property_set();

   //   if (::is_set(pset))
   //   {

   //      return pset;

   //   }

   //   return this;

   //}

} // namespace acme



