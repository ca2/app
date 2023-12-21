//
// Created by camilo on 2023-12-19 04:15 <3ThomasBorregaardSorensen!!
// From https://github.com/ca2/motif_labs
//
#include "framework.h"
#include "application.h"



int g_argc;
char** g_argv;


namespace motif
{


   application::application()
   {


      m_pwidgetTop = XtVaAppInitialize (&m_pappcontext, "Application Name", NULL, 0,
                                        &g_argc, g_argv, NULL, NULL);


   }


   application::~application()
   {


      if(m_pwidgetTop)
      {

         XtDestroyWidget(m_pwidgetTop);

      }


      if(m_pappcontext)
      {

         XtDestroyApplicationContext(m_pappcontext);

      }

   }





   void application::set_exit_flag()
   {

      XtAppSetExitFlag(m_pappcontext);

   }


   void application::app_main_loop()
   {

      XtAppMainLoop (m_pappcontext);

   }


} // motif