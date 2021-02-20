

CLASS_DECL_ACME string executable_get_app_id(hinstance hinstance);
CLASS_DECL_ACME hinstance get_module_handle(const platform_char* psz);


class console
{
public:


   ::e_status                       m_estatus;
   __pointer(::apex::system)        m_psystem;


   void create_system()
   {

      apex_ref();

      string strAppId;

#ifdef _APP_ID

      strAppId = _APP_ID;

#else

      auto hinstance = get_module_handle(NULL);

      strAppId = executable_get_app_id(hinstance);

#endif

      auto psystem = platform_create_system(strAppId);

      if (!psystem)
      {

         __throw(resource_exception());

      }

      auto papplicationStartup = psystem->new_application(strAppId);

      if (!papplicationStartup)
      {

         __throw(resource_exception());

      }

      __bind(psystem, m_papplicationStartup, papplicationStartup);

      psystem->m_bConsole = false;

      application_common(psystem);

      m_psystem = psystem;

      m_psystem->m_bConsole = true;

   }


   void common_construct()
   {

      create_system();

   }


   console(int argc, char** argv)
   {

      common_construct();

      m_psystem->system_construct(argc, argv);

      init();

   }


   console(int argc, wchar_t** argv)
   {

      common_construct();

      m_psystem->system_construct(argc, argv);

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



