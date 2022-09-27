//
// Created by camilo on 22/02/2022.
//
// app to application and back to acme namespace by camilo on 2022-09-17 18:54 <3ThomasBorregaardSorensen!!
#include "framework.h"


#if defined(LINUX) || defined(FREEBSD) || defined(RASPBIAN) || defined(ANDROID)
static const char * g_p1;
static const char * g_p2;
void set_res(const char * p1, const char * p2)
{

   g_p1 = p1;
   g_p2 = p2;
}
#endif
#ifdef WINDOWS
static HINSTANCE g_hinstanceThis;
static HINSTANCE g_hinstancePrev;
static int g_nCmdShow;
CLASS_DECL_ACME void set_winmain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, int nCmdShow)
{
   g_hinstanceThis = hinstanceThis;
   g_hinstancePrev = hinstancePrev;
   g_nCmdShow = nCmdShow;
}
#endif


namespace acme
{


   void initialize();


   application::application()
   {

      //if (!g_p)
      //{

      //   g_p = this;

      //}

      m_pacmeapplication = this;

      m_pacmeapplicationStartup = this;

      m_pacmeapplicationMain = this;

      ::acme::initialize();

#if defined(WINDOWS)

      m_hinstanceThis = g_hinstanceThis;
      m_hinstancePrev = g_hinstancePrev;
      m_nCmdShow = g_nCmdShow;

#elif defined(LINUX) || defined(FREEBSD) || defined(RASPBIAN) || defined(ANDROID)

      m_pchar_binary__matter_zip_start = g_p1;
      m_pchar_binary__matter_zip_end = g_p2;

#endif

   }


   application::~application()
   {

      //   ::acme::finalize_system();

   }


   void application::initialize(::object * pobject)
   {

      ::task::initialize(pobject);

      {

#include "deployment/build.h"

         m_strBuild = pszBuild;

      }

      if (m_strBuild.is_empty())
      {

         m_strBuild = "(unknown build version)";

      }

   }


   bool application::is_application() const
   {

      return true;

   }


   bool application::is_system() const
   {

      return false;

   }


   bool application::is_session() const
   {

      return true;

   }


   bool application::is_service() const
   {

      return false;

   }


   bool application::is_user_service() const
   {

      return false;

   }


#ifdef WINDOWS


   void application::get_arguments_from_command_line()
   {

      m_argc = __argc;

      m_argv = __argv;

      m_envp = *__p__environ();

      m_wargv = __wargv;

      m_wenvp = *__p__wenviron();

      m_strCommandLine = ::GetCommandLineW();

   }


#else


   void application::set_args(int argc, char * argv[], char * envp[])
   {

      m_argc = argc;

      m_argv = argv;

      m_envp = envp;

   }


#endif


   int application::__implement()
   {

      return main_loop();

   }


   int application::main_loop()
   {

      __main(this);

      return m_iExitCode;

   }


   void application::init1()
   {


      initialize_context_1();


   }


   void application::init_instance()
   {

      m_psystem->node()->add_application_capability(m_eapplicationcapabilitya);

   }


   bool application::has_capability(enum_application_capability ecapability) const
   {

      return m_eapplicationcapabilitya.contains(ecapability);

   }


   void application::add_capability(enum_application_capability ecapability)
   {

      m_eapplicationcapabilitya.add_unique(ecapability);

   }


   //
   //class ::main main(argc, argv, envp);
   //
   //__main(main);
   //
   //class ::main main(argc, argv, envp);
   //
   //__main(main);


   void * application_system(void * pApplication)
   {

      auto papp = (::acme::application *)pApplication;

      return papp->m_psystem;

   }


   void application::handle_url(const ::string & strUrl)
   {


   }



} // namespace acme




