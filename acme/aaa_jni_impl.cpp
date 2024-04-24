#include "framework.h"
#include <jni.h>
//#include "_os_impl.h"




extern android_proxy * g_pandroidproxy;


thread_local JNIEnv * t_pjnienv;




::pointer< ::mutex > g_pmutexOs;


::pointer< ::mutex > osmutex()
{

   return g_pmutexOs;

}


extern thread_local JNIEnv * t_pjnienv;


int get_mem_free_available_kb()
{

   return g_pandroidproxy->m_lMemFreeAvailableKb;

}




string get_string(jstring jstring)
{

   const char * nativeString = t_pjnienv->GetStringUTFChars(jstring, 0);

   string str = nativeString;

   t_pjnienv->ReleaseStringUTFChars(jstring, nativeString);

   return str;

}







void set_jni_context(JNIEnv * penv)
{

   t_pjnienv = penv;

}


JNIEnv * get_jni_env()
{

   return t_pjnienv;

}
