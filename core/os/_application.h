﻿#pragma once


void __set_aura_application_factory(__PFN_NEW_AURA_APPLICATION pfnNewAuraApplication);
void set_aura_application_factory(PFN_NEW_AURA_APPLICATION pfnNewAuraApplication);
__PFN_NEW_AURA_APPLICATION __get_aura_application_factory();
PFN_NEW_AURA_APPLICATION get_aura_application_factory();



