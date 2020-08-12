#ifndef __GNUC__
#pragma once
#endif

#ifdef __OBJC__

#ifdef MACOS

#include "aura/os/macos/_mm.h"

#else

#include "aura/os/ios/_mm.h"

#endif

#include <CoreText/CoreText.h>

#import <Foundation/Foundation.h>

#else

#include "_.h"

#include "aura/_defer.h"

#endif




