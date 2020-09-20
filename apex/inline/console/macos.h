

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
//   ::estatus estatus = (::estatus) psystem->inline_init();
//
//   if (::succeeded(estatus))
//   {
//    
//      main();
//
//      estatus = Application.m_estatus;
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

   
   ::estatus m_estatus;
   __pointer(::apex::system) m_psystem;

   void create_system()
   {

      apex_ref();

      string strAppId = apple_get_bundle_id();

      m_psystem = ::move_transfer(platform_create_system(strAppId));

//      m_psystem = __new(::apex::system());

      m_psystem->console_initialize();



   }

   void common_construct()
   {

      create_system();

      application_common(m_psystem);

   }


   console(int argc, char ** argv)
   {

      common_construct();
      
      m_psystem->system_construct(argc, argv);

      init();

   }


   console(int argc, wchar_t ** argv)
   {

      common_construct();

      m_psystem->system_construct(argc, argv);

      init();

   }


   void init()
   {

      m_estatus = (::estatus) m_psystem->inline_init();

   }


   int result()
   {

      m_estatus = Application.m_estatus;

      ::i32 iErrorStatus = m_estatus.error_status();

      m_psystem->inline_term();

      m_psystem.release();

      return iErrorStatus;

   }


   ~console()
   {

      if (m_psystem)
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



