#ifndef __GNUC__
#pragma once
#endif


#include "acme/_start.h"


#ifdef __cplusplus

#ifdef __OBJC__

#include "aura/include/objcpp.h"

#else

#include "axis/_.h"
#include "axis/platform/_platform.h"
#if !defined(BROAD_PRECOMPILED_HEADER)
#define BROAD_PRECOMPILED_HEADER 1
#endif
#if BROAD_PRECOMPILED_HEADER
#include "axis/user/_user.h"
#include "axis/html/html_lite/_.h"
#include "axis/geoip/_.h"
#endif
#include "axis/mathematics/_.h"
#include "axis/mathematics/calculator/_.h"
#include "axis/mathematics/kissfft/_.h"
//#include "aura/crypto/crypto_openssl.h"
#include "aura/_defer.h"



#endif

#else

#ifdef __OBJC__

#include "aura/include/objc.h"

#else

#include "aura/_.h"

#endif

#endif



