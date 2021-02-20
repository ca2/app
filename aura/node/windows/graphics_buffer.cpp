#include "framework.h"
#include "apex/operating_system.h"
#include "aura/message.h"
#include "aura/user/_user.h"
#include "buffer.h"


extern point_i32 g_pointLastBottomRight;


#include "__debug_power.h"

#undef REDRAW_HINTING
//#define REDRAW_HINTING

#ifdef __DEBUG_POWER
#undef SQUARY_HINT
#define SQUARY_HINT
#endif

//int iSquaryHint = 0;
