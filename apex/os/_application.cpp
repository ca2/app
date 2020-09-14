#include "framework.h"



__PFN_NEW_APEX_APPLICATION __g_pfnNewAuraApplication = nullptr;


PFN_NEW_APEX_APPLICATION g_pfnNewAuraApplication = nullptr;


extern "C"
::apex::application * __apex_application_factory()
{

   return __g_pfnNewAuraApplication();

}


void __set_apex_application_factory(__PFN_NEW_APEX_APPLICATION pfnNewAuraApplication)
{

   __g_pfnNewAuraApplication = pfnNewAuraApplication;

   g_pfnNewAuraApplication = &__apex_application_factory;

}


void set_apex_application_factory(PFN_NEW_APEX_APPLICATION pfnNewAuraApplication)
{

   g_pfnNewAuraApplication = pfnNewAuraApplication;

}


__PFN_NEW_APEX_APPLICATION __get_apex_application_factory()
{

   return __g_pfnNewAuraApplication;

}


PFN_NEW_APEX_APPLICATION get_apex_application_factory()
{

   return g_pfnNewAuraApplication;

}





