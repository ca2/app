



//
//class console
//{
//public:
//
//
//   void m_estatus;
//   //::pointer<::apex::system>system();
//
//   void create_system()
//   {
//
//      acme_ref();
//
////      system() = ::pointer_transfer(platform_create_system(nullptr));
////
////      //      system() = allocateø ::platform::system();
////
////      system()->console_initialize();
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
////      application_common(system());
////
////   }
////
//
//   console(::i32 argc, char_pointer * argv)
//   {
//
////      common_construct();
////
////      system()->system_construct(argc, argv);
////
////      init();
//
//   }
//
//
//   console(::i32 argc, wchar_t** argv)
//   {
//
//      common_construct();
//
//      system()->system_construct(argc, argv);
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
//   }
//
//
//   ::i32 result()
//   {
//
//      m_estatus = papp->m_estatus;
//
//      ::i32 iErrorStatus = m_estatus.error_status();
//
//      system()->inline_term();
//
//      system().release();
//
//      return iErrorStatus;
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

//::i32 main(::i32 argc, char_pointer argv[])
//
//::i32 main(::i32 argc, char_pointer argv[])
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
//   //      auto psystem = allocateø ::platform::system();
//
//   //      psystem->system_construct(&mainstruct, argc, argv);
//
//   //      return acme_run_system(psystem);
//
//   //   }
//
//   //}
//
//   auto psystem = allocateø ::platform::system();
//
//   psystem->console_initialize();
//
//   application_common(psystem);
//
//   psystem->system_construct(argc, argv);
//
//   ::e_status estatus = (void) psystem->inline_init();
//
//   if (::succeeded(estatus))
//   {
//
//      main();
//
//      estatus = papp->m_estatus;
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


static const_char_pointer s_pszBinRelocInitGetSymbol = "br_init_get_symbol";


const_char_pointer br_init_get_symbol()
{

   return s_pszBinRelocInitGetSymbol;

}



