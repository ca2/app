﻿#pragma once


void __set_acme_application_factory(__PFN_NEW_ACME_APPLICATION pfnNewAuraApplication);
void set_acme_application_factory(PFN_NEW_ACME_APPLICATION pfnNewAuraApplication);
__PFN_NEW_ACME_APPLICATION __get_acme_application_factory();
PFN_NEW_ACME_APPLICATION get_acme_application_factory();



