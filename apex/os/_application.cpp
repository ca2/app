#include "framework.h"


PFN_NEW_APEX_APPLICATION g_pfnNewAuraApplication = nullptr;


::apex::application * new_apex_application()
{

   return g_pfnNewAuraApplication();

}


void set_apex_application_factory(PFN_NEW_APEX_APPLICATION pfnNewAuraApplication)
{

   g_pfnNewAuraApplication = pfnNewAuraApplication;

}


PFN_NEW_APEX_APPLICATION get_apex_application_factory()
{

   return g_pfnNewAuraApplication;

}


const char * g_pszMainAppId = nullptr;


CLASS_DECL_APEX ::estatus set_main_app_id(const char * pszAppId)
{

   g_pszMainAppId = pszAppId;

   return ::success;

}


CLASS_DECL_APEX const char * get_main_app_id()
{

   return g_pszMainAppId;

}



