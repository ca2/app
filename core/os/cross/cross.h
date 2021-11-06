#pragma once



#ifndef WINDOWS_DESKTOP

#ifdef LINUX
#undef inline
#endif

#include "windows/_.h"

#endif


#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(SOLARIOS)

//#include "ansios/ansios_file_raw.h"

#else

//#include "ansios/ansios.h"

#endif

