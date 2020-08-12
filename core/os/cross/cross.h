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


#define DT_TOPLEFT (DT_TOP | DT_LEFT)
#define DT_TOPCENTER (DT_TOP | DT_CENTER)
#define DT_TOPRIGHT (DT_TOP | DT_RIGHT)
#define DT_LEFTCENTER (DT_VCENTER | DT_LEFT)
#define DT_HVCENTER (DT_CENTER | DT_VCENTER)
#define DT_RIGHTCENTER (DT_VCENTER | DT_RIGHT)
#define DT_BOTTOMLEFT (DT_BOTTOM | DT_LEFT)
#define DT_BOTTOMCENTER (DT_BOTTOM | DT_CENTER)
#define DT_BOTTOMRIGHT (DT_BOTTOM | DT_RIGHT)




