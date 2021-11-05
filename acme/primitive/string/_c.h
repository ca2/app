#pragma once





#include "x/x_charcategory.h"
#include "x/x_defines.h"
#include "x/x_tables.h"





//  OS ANCIENT          strcpy
//  OS ANCIENT WIDE     wcscpy

//  scaffold implementation: sometimes OS doesn't implement a OS ancient function or
//                           whole certain wd16/32 version, the scaffold implementation
//                           supplies a "local"/alternative implementation (even if the
//                           OS already implements it)
//  scaffold-1          __ansicpy
//  scaffold-2          __wd16cpy
//  scaffold-3          __wd32cpy


//  ready-to-use : inlined version of either OS version (default) or scaffold version
//                 (when there is no OS version).
//  ready-to-use-1      ansi_cpy
//  ready-to-use-2      wd16_cpy
//  ready-to-use-3      wd32_cpy


inline int_bool address_overlaps(const void * pszDst, const void * pszSrc, strsize srclen);





#include "_c_trait_ansi.h"


#include "_c_trait_wd16.h"


#include "_c_trait_wd32.h"


#include "_c_trait_wide.h"


#include "_c_trait.h"


#include "_c_unicode.h"


#include "_c_str.h"


#include "__c_ansi.h"
#include "__c_wd16.h"
#include "__c_wd32.h"
#include "__c_wide.h"



