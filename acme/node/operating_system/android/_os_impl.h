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

#include "_os_object.h"
#include "_os_local.h"
#include "_os_remote.h"


void android_on_text(e_os_text etext, const wchar_t* pwch, size_t len);


#define  LOG_TAG    "acme : os : _os_binding"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


CLASS_DECL_ACME string get_string(jstring jstring);



