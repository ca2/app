

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
//      psystem->__refer(psystem->application(), pappStartup);
//
//      psystem->m_bConsole = false;
//
//      application_common(psystem);
//
//      psystem->m_bConsole = true;
//
//      system() = psystem;
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
//      system()->system_construct(argc, argv, envp);
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
//      system()->system_construct(argc, argv, envp);
//
//      init();
//
//   }
//
//
//   void init()
//   {
//
//      m_estatus = (void) system()->inline_init();
//
//      auto papp = system()->application();
//
//      __refer(system()->application(), system()->application().get());
//
//      __unbind(system(), application() REFERENCING_DEBUGGING_COMMA_P_NOTE(system(), ""));
//
//   }
//
//
//   int result()
//   {
//
//      auto estatus = system()->inline_term();
//
//      ::acme::del(system());
//
//      return estatus;
//
//   }
//
//
//   ~console()
//   {
//
//      if (system())
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



