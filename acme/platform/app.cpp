//
// Created by camilo on 22/02/2022.
//
#include "framework.h"


app * app::g_p = nullptr;

namespace acme
{


   void initialize();


} // namespace acme


app::app()
{

   if(!g_p)
   {

      g_p = this;

   }

   m_papp = this;
   
   m_pappStartup = this;
   
   m_pappMain = this;

   ::acme::initialize();

}


app::~app()
{

//   ::acme::finalize_system();

}


void app::initialize(::object* pobject)
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


bool app::is_application() const
{

   return true;

}


bool app::is_system() const
{

   return false;

}


bool app::is_session() const
{

   return true;

}


bool app::is_service() const
{

   return false;

}


bool app::is_user_service() const
{

   return false;

}


#ifdef WINDOWS


void app::get_arguments_from_command_line()
{

   m_argc = __argc;

   m_argv = __argv;

   m_envp = *__p__environ();

   m_wargv = __wargv;

   m_wenvp = *__p__wenviron();

   m_strCommandLine = ::GetCommandLineW();

}


#else


void app::set_args(int argc, char * argv[], char * envp[])
{

   m_argc = argc;

   m_argv = argv;

   m_envp = envp;

}


#endif


int app::main_loop()
{

   __main(*this);

   return m_iExitCode;

}


void app::init1()
{

   
   initialize_context_1();


}


void app::init_instance()
{

   m_psystem->node()->add_application_capability(m_eapplicationcapabilitya);

}


bool app::has_capability(enum_application_capability ecapability) const
{

   return m_eapplicationcapabilitya.contains(ecapability);

}


void app::add_capability(enum_application_capability ecapability)
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
   
   auto papp = (::app *) pApplication;
   
   return papp->m_psystem;
   
}


void app::handle_url(const ::string & strUrl)
{
   
   
}



