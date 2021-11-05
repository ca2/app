#include "framework.h"
//#include "src/turboc.h"


i16 getch()
{

   return get_console_application().console_prompt().getch();

}

void getch(i16 c)
{

   return get_console_application().console_prompt().ungetch(c);

}


CLASS_DECL_TURBOC ::turboc::context & get_turboc_context()
{

   return *get_turboc_application().m_pcontext;

}


CLASS_DECL_TURBOC ::turboc::application & get_turboc_application()
{

   ::aura::application * pauraapp = ::get_thread_app();

   // Thread accessing turboc application should have been created with a ::turboc::application derived class
   ASSERT(pauraapp != NULL);

   ::turboc::application * papp = dynamic_cast <::turboc::application *> (pauraapp);

   // Thread accessing turboc application should have been created with a ::turboc::application derived class
   ASSERT(papp != NULL);

   return *papp;

}


CLASS_DECL_TURBOC ::console::application & get_console_application()
{

   ::aura::application * pauraapp = ::get_thread_app();

   // Thread accessing console application should have been created with a ::console::application derived class
   ASSERT(pauraapp != NULL);

   ::console::application * papp = dynamic_cast <::console::application *> (pauraapp);

   // Thread accessing console application should have been created with a ::console::application derived class
   ASSERT(papp != NULL);

   return *papp;

}


