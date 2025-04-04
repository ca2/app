#include "framework.h"
#include "_os_impl.h"


extern mutex* g_pmutexOs;


bool g_bAuraStart = false;


void os_on_finish_launching();


extern "C"
JNIEXPORT jboolean JNICALL Java_com_android_1app_app_apex_1is_1started(JNIEnv* env, jobject obj) 
{

   return g_bAuraStart;

}


extern "C"
JNIEXPORT void JNICALL Java_com_android_1app_app_apex_1init(JNIEnv * penv, jobject obj, jobject os)
{

   set_context(penv);

   if (!g_pmutexOs)
   {

      g_pmutexOs = aaa_primitive_new mutex();

   }

   if (!g_poslocal)
   {

      g_poslocal = __allocate os_local();

   }

   g_posremote = __allocate os_remote(os);

   auto premote = g_posremote;

   auto plocal = g_poslocal;

   plocal->m_iWidth = premote->getWidth();

   plocal->m_iHeight = premote->getHeight();

   plocal->m_fDpiX = premote->getDpiX();

   plocal->m_fDpiY = premote->getDpiY();

   plocal->m_fDensity = premote->getDensity();

   plocal->m_bShowKeyboard = false;


}


extern "C"
JNIEXPORT void JNICALL Java_com_android_1app_app_apex_1start(JNIEnv * penv, jobject obj)
{

   set_context(penv);

   if (g_bAuraStart)
   {

      return;

   }

   g_bAuraStart = true;

   android_apex_main();

}


extern "C"
JNIEXPORT void JNICALL Java_com_android_1app_app_sync_1mem_1free_1available(JNIEnv * env, jobject obj, jobject os)
{

   set_context(env);

   g_poslocal->m_lMemFreeAvailableKb = g_posremote->getMemFreeAvailableKb();

}



