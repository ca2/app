// Created by camilo on 2021-11-05 16:34 PM <3ThomasBorregaardSørensen!!
#pragma once


#include "axis/_.h"


#ifdef _API_GOOGLE_LIBRARY
#define CLASS_DECL_API_GOOGLE  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_API_GOOGLE  CLASS_DECL_IMPORT
#endif

