#pragma once

#ifdef CLASS_DECL_CORE
#include "core/user/user/user.h"
#include "core/platform/system.h"
#elif defined(CLASS_DECL_BRED)
#include "bred/user/user/user.h"
#include "bred/platform/system.h"
#elif defined(CLASS_DECL_BERG)
#include "berg/user/user/user.h"
#include "berg/platform/system.h"
#elif defined(CLASS_DECL_AXIS)
#include "axis/user/user/user.h"
#include "axis/platform/system.h"
#elif defined(CLASS_DECL_AURA)
#include "aura/user/user/user.h"
#include "aura/platform/system.h"
#endif


