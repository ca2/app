

//int main(int argc, char* argv[])
//{
//
//   //class apex_apex apex_apex;
//
//   //{
//
//   //   ::apex_main_struct mainstruct;
//
//   //   console_initialize(mainstruct);
//
//   //   {
//
//   //      auto psystem = __new(::apex::system());
//
//   //      psystem->system_construct(&mainstruct, argc, argv);
//
//   //      return apex_run_system(psystem);
//
//   //   }
//
//   //}
//
//   auto psystem = __new(::apex::system());
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
//      estatus = get_app()->m_estatus;
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



class console
{
public:

   
   void m_estatus;
   ::pointer<::apex::system>acmesystem();

   
   void create_system()
   {

      apex_ref();

      string strAppId = executable_get_app_id();

      acmesystem() = ::pointer_transfer(platform_create_system(strAppId));

      acmesystem()->m_bConsole = true;
      //acmesystem()->console_initialize();

   }
   

   void common_construct()
   {

      create_system();

      application_common(acmesystem());

   }


   console(int argc, char ** argv, char ** envp)
   {

      common_construct();
      
      acmesystem()->system_construct(argc, argv, envp);

      init();

   }


   console(int argc, wchar_t ** argv, wchar_t ** envp)
   {

      common_construct();

      acmesystem()->system_construct(argc, argv, envp);

      init();

   }


   void init()
   {

      m_estatus = (void) acmesystem()->inline_init();

   }


   int result()
   {

      m_estatus = m_pcontext->acmeapplication()->m_estatus;

      ::i32 iErrorStatus = m_estatus.error_status();

      acmesystem()->inline_term();

      acmesystem().release();

      return iErrorStatus;

   }


   ~console()
   {

      if (acmesystem())
      {

         result();

      }


   }


};


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



