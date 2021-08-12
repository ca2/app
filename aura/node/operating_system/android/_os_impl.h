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

//#include "_os_object.h"
//#include "_os_local.h"
//#include "_os_remote.h"

#include "acme/node/operating_system/android/_os_object.h"
#include "acme/node/operating_system/android/_os_local.h"
#include "acme/node/operating_system/android/_os_remote.h"


void android_on_text(e_os_text etext, const wchar_t* pwch, size_t len);


#define  LOG_TAG    "aura : os : _os_binding"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

int SetMainScreenRect(const RECTANGLE_I32 * lpcrect);

void android_aura_main();

void android_fill_plasma(AndroidBitmapInfo * info, color32_t * pixels, double  t);

void android_mouse(unsigned int message, float x, float y);

void android_key(unsigned int message, int keyCode, int iUni);

extern int g_iScreenW;

extern int g_iScreenH;

extern const char * g_pszCommandLine;

extern const char * g_pszCacheDir;

extern __pointer(os_remote) g_posremote;

extern __pointer(os_local) g_poslocal;

CLASS_DECL_AURA string get_string(jstring jstring);


CLASS_DECL_AURA void set_context(JNIEnv* penv);
CLASS_DECL_AURA JNIEnv* get_jni_env();

CLASS_DECL_AURA void android_exchange();



