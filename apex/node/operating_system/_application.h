﻿#pragma once


void __set_apex_application_factory(__PFN_NEW_APEX_APPLICATION pfnNewAuraApplication);
void set_apex_application_factory(PFN_NEW_APEX_APPLICATION pfnNewAuraApplication);
__PFN_NEW_APEX_APPLICATION __get_apex_application_factory();
PFN_NEW_APEX_APPLICATION get_apex_application_factory();



