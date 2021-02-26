//
//
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
//   ::e_status estatus = (::e_status) psystem->inline_init();
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



      class console
      {
      public:


         ::e_status m_estatus;

         __pointer(::apex::system) m_psystem;

         void create_system()
         {

            apex_ref();

            string strAppId = executable_get_app_id();

            m_psystem = ::move_transfer(platform_create_system(strAppId));

            auto papplicationStartup = m_psystem->new_application(strAppId);

            __bind(m_psystem, m_papplicationStartup, papplicationStartup);

            m_psystem->set_main_struct(*m_psystem->m_papplicationStartup);

            m_psystem->m_bConsole = true;

         }


         void common_construct()
         {

            create_system();

            application_common(m_psystem);

         }


         console(int argc, char** argv, char ** envp)
         {

            common_construct();

            m_psystem->system_construct(argc, argv, envp);

            init();

         }


         console(int argc, wchar_t** argv, wchar_t **  envp)
         {

            common_construct();

            m_psystem->system_construct(argc, argv, envp);

            init();

         }


         void init()
         {

            m_estatus = (::e_status) m_psystem->inline_init();

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



static const char * s_pszBinRelocInitGetSymbol = "br_init_get_symbol";


const char * br_init_get_symbol()
{

   return s_pszBinRelocInitGetSymbol;

}


