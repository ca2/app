#pragma once


#include <android/log.h>
#include <android/bitmap.h>
#include <jni.h>
#include <dlfcn.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>
#include <android/log.h>
#include <android/bitmap.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "jni_object.h"
#include "proxy_to_android_operating_system.h"
#include "android_operating_system.h"


void android_on_text(e_os_text etext, const wchar_t* pwch, size_t len);




CLASS_DECL_ACME string get_string(jstring jstring);



