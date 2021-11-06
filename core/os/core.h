#pragma once


#include "file.h"


#include "threading.h"

#include "cross.h"


#include "time.h"





#ifdef __cplusplus

#include "windowing.h"

#endif


#include "graphics.h"


#pragma once




#ifdef AMD64
#define OS64BIT
#elif defined(__LP64)
#define OS64BIT
#else
#define OS32BIT
#endif











