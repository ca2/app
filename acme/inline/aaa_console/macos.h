



//
//class console
//{
//public:
//
//
//   ::e_status m_estatus;
//   //__pointer(::apex::system) m_psystem;
//
//   void create_system()
//   {
//
//      acme_ref();
//
////      m_psystem = ::move_transfer(platform_create_system(nullptr));
////
////      //      m_psystem = __new(class ::system());
////
////      m_psystem->console_initialize();
////
//
//
//   }
//
////   void common_construct()
////   {
////
////      create_system();
////
////      application_common(m_psystem);
////
////   }
////
//
//   console(int argc, char** argv)
//   {
//
////      common_construct();
////
////      m_psystem->system_construct(argc, argv);
////
////      init();
//
//   }
//
//
//   console(int argc, wchar_t** argv)
//   {
//
//      common_construct();
//
//      m_psystem->system_construct(argc, argv);
//
//      init();
//
//   }
//
//
//   void init()
//   {
//
//      m_estatus = (::e_status) m_psystem->inline_init();
//
//   }
//
//
//   int result()
//   {
//
//      m_estatus = papplication->m_estatus;
//
//      ::i32 iErrorStatus = m_estatus.error_status();
//
//      m_psystem->inline_term();
//
//      m_psystem.release();
//
//      return iErrorStatus;
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
//      }
//
//
//   }
//
//
//
//};
//
//

//int main(int argc, char* argv[])
//
//int main(int argc, char* argv[])
//{
//
//   //class acme_acme acme_acme;
//
//   //{
//
//   //   ::acme_main_struct mainstruct;
//
//   //   console_initialize(mainstruct);
//
//   //   {
//
//   //      auto psystem = __new(class ::system());
//
//   //      psystem->system_construct(&mainstruct, argc, argv);
//
//   //      return acme_run_system(psystem);
//
//   //   }
//
//   //}
//
//   auto psystem = __new(class ::system());
//
//   psystem->console_initialize();
//
//   application_common(psystem);
//
//   psystem->system_construct(argc, argv);
//
//   ::e_status estatus = (::e_status) psystem->inline_init();
//
//   if (::succeeded(estatus))
//   {
//
//      main();
//
//      estatus = papplication->m_estatus;
//
//   }
//
//   ::i32 iErrorStatus = estatus.error_status();
//
//   psystem->inline_term();
//
//   return iErrorStatus;
//
//}
//
//
//


//static const char * s_pszBinRelocInitGetSymbol = "br_init_get_symbol";
//
//
//const char * br_init_get_symbol()
//{
//
//   return s_pszBinRelocInitGetSymbol;
//
//}



