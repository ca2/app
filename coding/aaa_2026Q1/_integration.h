//
// Created by camilo on 12/12/21  05:16 PM <3ThomasBorregaardSørensen!!
//
#pragma once


#include "build.h"


#if defined(LINUX)


#include "linux.h"


#elif defined(WINDOWS_DESKTOP)


//#include "windows.h"


#else


#error "not implemented"


#endif
