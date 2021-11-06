#include "framework.h"
#include "_console.h"


#include "aura/os/binreloc.h"


const char * br_init_get_symbol();


console::console(int argc, wchar_t* argv[])
{

   m_bConsole = true;
   m_bDraw2d = false;
   m_bUser = false;
   m_bUserEx = false;
   m_bShowApplicationInformation = false;

   int iResult = 0;

#ifdef GET_COMMAND_LINE

   char* pszCommandLine = GET_COMMAND_LINE(argc, argv);

#elif defined(MAIN_STRING)

   char* pszCommandLine = strdup(MAIN_STRING);

#elif defined (_WIN32)

   char* pszCommandLine = _strdup("");

#else

   char* pszCommandLine = strdup("");

#endif

#ifdef LINUX

   br_init_set_symbol(br_init_get_symbol());

#endif

#ifdef ACID_APP

   PFN_NEW_AURA_APPLICATION pfnNewAuraApplication = &new_aura_application;

#else

   PFN_NEW_AURA_APPLICATION pfnNewAuraApplication = nullptr;

#endif

#ifdef ACID_LIBRARY

   PFN_NEW_AURA_LIBRARY pfnNewLibrary = &new_aura_library;

#else

   PFN_NEW_AURA_LIBRARY pfnNewLibrary = nullptr;

#endif

   auto psystem = __new(::aura::system());

   psystem->system_construct(this, argc, argv);

   if (!psystem->system_beg())
   {

      throw ::exception("The application didn't started.");

   }

   bool bOk = psystem->system_ini();

   if (!bOk)
   {

      throw ::exception("The application didn't started. (2)");

   }

   psystem->system_start();

}

console::console(int argc, char * argv[])
{

   m_bConsole = true;
   m_bDraw2d = false;
   m_bUser = false;
   m_bUserEx = false;
   m_bShowApplicationInformation = false;

   int iResult = 0;

#ifdef GET_COMMAND_LINE

   char* pszCommandLine = GET_COMMAND_LINE(argc, argv);

#elif defined(MAIN_STRING)

   char* pszCommandLine = strdup(MAIN_STRING);

#elif defined (_WIN32)

   char* pszCommandLine = _strdup("");

#else

   char* pszCommandLine = strdup("");

#endif

#ifdef LINUX

   br_init_set_symbol(br_init_get_symbol());

#endif

#ifdef ACID_APP

   PFN_NEW_AURA_APPLICATION pfnNewAuraApplication = &new_aura_application;

#else

   PFN_NEW_AURA_APPLICATION pfnNewAuraApplication = nullptr;

#endif

#ifdef ACID_LIBRARY

   PFN_NEW_AURA_LIBRARY pfnNewLibrary = &new_aura_library;

#else

   PFN_NEW_AURA_LIBRARY pfnNewLibrary = nullptr;

#endif

   m_psystem = __new(::aura::system());

   m_psystem->construct_system(this, argc, argv, pszCommandLine);

   //m_pmaindata->m_pappcore = __new(app_core(m_pmaindata));

   if (!m_psystem->system_beg())
   {

      throw ::exception("The application didn't started.");

   }

   bool bOk = m_psystem->system_ini();

   if (!bOk)
   {

      throw ::exception("The application didn't started. (2)");

   }

   m_psystem->start();


}


console::~console()
{

   //m_psystem->system_end();

}



