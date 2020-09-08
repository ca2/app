#pragma once


void __set_ace_application_factory(__PFN_NEW_ace_APPLICATION pfnNewaceApplication);
void set_ace_application_factory(PFN_NEW_ace_APPLICATION pfnNewaceApplication);
__PFN_NEW_ace_APPLICATION __get_ace_application_factory();
PFN_NEW_ace_APPLICATION get_ace_application_factory();



