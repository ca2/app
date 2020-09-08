#include "framework.h"



__PFN_NEW_ace_APPLICATION __g_pfnNewaceApplication = nullptr;


PFN_NEW_ace_APPLICATION g_pfnNewaceApplication = nullptr;


extern "C"
::acme::application * __ace_application_factory()
{

   return __g_pfnNewaceApplication();

}


void __set_ace_application_factory(__PFN_NEW_ace_APPLICATION pfnNewaceApplication)
{

   __g_pfnNewaceApplication = pfnNewaceApplication;

   g_pfnNewaceApplication = &__ace_application_factory;

}


void set_ace_application_factory(PFN_NEW_ace_APPLICATION pfnNewaceApplication)
{

   g_pfnNewaceApplication = pfnNewaceApplication;

}


__PFN_NEW_ace_APPLICATION __get_ace_application_factory()
{

   return __g_pfnNewaceApplication;

}


PFN_NEW_ace_APPLICATION get_ace_application_factory()
{

   return g_pfnNewaceApplication;

}





