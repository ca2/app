

////CLASS_DECL_ACME string executable_get_app_id(hinstance hinstance);
//CLASS_DECL_ACME hinstance get_module_handle(const platform_char* psz);
//
//
//class console : 
//   virtual public object
//{
//public:
//
//
//   void                       m_estatus;
//
//
//   void create_system()
//   {
//
//      apex_ref();
//
//      string strAppId;
//
////#ifdef _APP_ID
////
////      strAppId = _APP_ID;
////
////#else
////
////      auto hinstance = get_module_handle(NULL);
////
////      strAppId = executable_get_app_id(hinstance);
////
////#endif
//
//      auto psystem = platform_create_system(strAppId);
//
//      if (!psystem)
//      {
//
//         throw ::exception(error_resource);
//
//      }
//
//      auto pappStartup = psystem->new_application(strAppId);
//
//      if (!pappStartup)
//      {
//
//         throw ::exception(error_resource);
//
//      }
//
//      psystem->__refer(psystem->m_pappStartup, pappStartup);
//
//      psystem->m_bConsole = false;
//
//      application_common(psystem);
//
//      psystem->m_bConsole = true;
//
//      m_psystem = psystem;
//
//   }
//
//
//   void common_construct()
//   {
//
//      create_system();
//
//   }
//
//
//   console(int argc, char** argv, char ** envp)
//   {
//
//      common_construct();
//
//      m_psystem->system_construct(argc, argv, envp);
//
//      init();
//
//   }
//
//
//   console(int argc, wchar_t** argv, wchar_t ** envp)
//   {
//
//      common_construct();
//
//      m_psystem->system_construct(argc, argv, envp);
//
//      init();
//
//   }
//
//
//   void init()
//   {
//
//      m_estatus = (void) m_psystem->inline_init();
//
//      auto papp = m_psystem->m_papexsystem->m_pappStartup;
//
//      __refer(m_psystem->m_papexsystem->m_pappMain, m_psystem->m_papexsystem->m_pappStartup.get());
//
//      __unbind(m_psystem->m_papexsystem, m_pappStartup OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_NOTE(m_psystem, ""));
//
//   }
//
//
//   int result()
//   {
//
//      auto estatus = m_psystem->inline_term();
//
//      ::acme::del(m_psystem);
//
//      return estatus;
//
//   }
//
//
//   ~console()
//   {
//
//      if (m_psystem)
//      {
//
//         result();
//
//         
//      }
//
//
//   }
//
//
//};



//int wmain(int argc, wchar_t* argv[])
//{
//
//   console console(argc, argv);
//
//   main();
//
//   return console.result();
//
//}



