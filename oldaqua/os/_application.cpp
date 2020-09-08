#include "framework.h"



__PFN_NEW_AURA_APPLICATION __g_pfnNewAuraApplication = nullptr;


PFN_NEW_AURA_APPLICATION g_pfnNewAuraApplication = nullptr;


extern "C"
::aqua::application * __aura_application_factory()
{

   return __g_pfnNewAuraApplication();

}


void __set_aura_application_factory(__PFN_NEW_AURA_APPLICATION pfnNewAuraApplication)
{

   __g_pfnNewAuraApplication = pfnNewAuraApplication;

   g_pfnNewAuraApplication = &__aura_application_factory;

}


void set_aura_application_factory(PFN_NEW_AURA_APPLICATION pfnNewAuraApplication)
{

   g_pfnNewAuraApplication = pfnNewAuraApplication;

}


__PFN_NEW_AURA_APPLICATION __get_aura_application_factory()
{

   return __g_pfnNewAuraApplication;

}


PFN_NEW_AURA_APPLICATION get_aura_application_factory()
{

   return g_pfnNewAuraApplication;

}





