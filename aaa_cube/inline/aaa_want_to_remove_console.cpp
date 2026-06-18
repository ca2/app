#include "framework.h"
#include "_console.h"


#include "aura/os/binreloc.h"


const_char_pointer br_init_get_symbol();


console::console(::i32 argc, wchar_t* argv[])
{

   m_bConsole = true;
   m_bDraw2d = false;
   m_bUser = false;
   m_bUserEx = false;
   m_bShowApplicationInformation = false;

   ::i32 iResult = 0;

#ifdef GET_COMMAND_LINE

   char_pointer pszCommandLine = GET_COMMAND_LINE(argc, argv);

#elif defined(MAIN_STRING)

   char_pointer pszCommandLine = strdup(MAIN_STRING);

#elif defined (_WIN32)

   char_pointer pszCommandLine = _strdup("");

#else

   char_pointer pszCommandLine = strdup("");

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

   auto psystem = allocateø ::aura::system();

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

console::console(::i32 argc, char_pointer argv[])
{

   m_bConsole = true;
   m_bDraw2d = false;
   m_bUser = false;
   m_bUserEx = false;
   m_bShowApplicationInformation = false;

   ::i32 iResult = 0;

#ifdef GET_COMMAND_LINE

   char_pointer pszCommandLine = GET_COMMAND_LINE(argc, argv);

#elif defined(MAIN_STRING)

   char_pointer pszCommandLine = strdup(MAIN_STRING);

#elif defined (_WIN32)

   char_pointer pszCommandLine = _strdup("");

#else

   char_pointer pszCommandLine = strdup("");

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

   system() = allocateø ::aura::system();

   system()->construct_system(this, argc, argv, pszCommandLine);

   //m_pmaindata->m_pappcore = allocateø app_graphics3d(m_pmaindata);

   if (!system()->system_beg())
   {

      throw ::exception("The application didn't started.");

   }

   bool bOk = system()->system_ini();

   if (!bOk)
   {

      throw ::exception("The application didn't started. (2)");

   }

   system()->start();


}


console::~console()
{

   //system()->system_end();

}



