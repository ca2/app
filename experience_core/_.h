#pragma once


#include "base/_.h"
#include "base/user/user/_user.h"       // thank you (mummy)
#include "base/user/experience/_experience.h"       // thank you (mummy)


#ifdef _APP_EXPERIENCE_CORE_LIBRARY
    #define CLASS_DECL_APP_EXPERIENCE_CORE  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_APP_EXPERIENCE_CORE  CLASS_DECL_IMPORT
#endif


#include "experience/_experience.h"
#include "user/_user.h"



