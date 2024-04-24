// Created by camilo on 2021-11-05 16:34 PM <3ThomasBorregaardSorensen!!
#pragma once


#include "axis/_.h"


#if defined(_api_ca2_project)
#define CLASS_DECL_API_CA2  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_API_CA2  CLASS_DECL_IMPORT
#endif

