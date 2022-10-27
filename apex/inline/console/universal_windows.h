

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
//      psystem->__refer(psystem->m_pacmeapplicationStartup, pappStartup);
//
//      psystem->m_bConsole = false;
//
//      application_common(psystem);
//
//      psystem->m_bConsole = true;
//
//      acmesystem() = psystem;
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
//      acmesystem()->system_construct(argc, argv, envp);
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
//      acmesystem()->system_construct(argc, argv, envp);
//
//      init();
//
//   }
//
//
//   void init()
//   {
//
//      m_estatus = (void) acmesystem()->inline_init();
//
//      auto papp = acmesystem()->m_papexsystem->m_pacmeapplicationStartup;
//
//      __refer(acmesystem()->m_papexsystem->m_pacmeapplicationMain, acmesystem()->m_papexsystem->m_pacmeapplicationStartup.get());
//
//      __unbind(acmesystem()->m_papexsystem, m_pacmeapplicationStartup OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_NOTE(acmesystem(), ""));
//
//   }
//
//
//   int result()
//   {
//
//      auto estatus = acmesystem()->inline_term();
//
//      ::acme::del(acmesystem());
//
//      return estatus;
//
//   }
//
//
//   ~console()
//   {
//
//      if (acmesystem())
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



