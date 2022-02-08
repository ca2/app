#include "framework.h"


PFN_NEW_MATTER g_pfnnewmatterApplication = nullptr;


::matter * new_application_as_matter()
{

   return g_pfnnewmatterApplication();

}


void set_application_factory(PFN_NEW_MATTER pfnnewmatterApplication)
{

   g_pfnnewmatterApplication = pfnnewmatterApplication;

}


PFN_NEW_MATTER get_application_factory()
{

   return g_pfnnewmatterApplication;

}


const char * g_pszMainAppId = nullptr;


CLASS_DECL_APEX void set_main_app_id(const char * pszAppId)
{

   g_pszMainAppId = pszAppId;

   //return ::success;

}


CLASS_DECL_APEX const char * get_main_app_id()
{

   return g_pszMainAppId;

}



