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

   ::acme::initialize();

}


app::~app()
{

//   ::acme::finalize_system();

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


void app::set_args(int argc, char * argv[], char * envp[])
{

   m_argc = argc;

   m_argv = argv;

   m_envp = envp;

//m_pmain->m_strAppId = __APP_ID;

   //m_bConsole = false;
}


int app::main_loop()
{

   __main(*this);

   return m_iExitCode;

}

//
//class ::main main(argc, argv, envp);
//
//__main(main);
//
//class ::main main(argc, argv, envp);
//
//__main(main);




