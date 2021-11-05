﻿#include "framework.h"
#include "_os_impl.h"
#include "apex/user/interaction_thread.h"
#include "apex/user/interaction_prodevian.h"


int SetMainScreenRect(LPCRECT32 lpcrect);

extern "C"
JNIEXPORT void JNICALL Java_com_android_1app_impact_render_1impact(JNIEnv * env, jobject  obj, jobject bitmap, jlong  time_ms, jobject result)
{

   set_context(env);

   AndroidBitmapInfo    info;
   void* pixels;
   int                  ret;
   static int           init;

   if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0)
   {

      LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);

      return;

   }

   if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888)
   {

      LOGE("Bitmap format is not RGB_565 !");

      return;

   }

   if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0)
   {

      LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);

   }

   try
   {

      android_fill_plasma(&info, pixels, time_ms);

   }
   catch (...)
   {

      LOGE("exception at g_android_fill_plasma");

   }

   AndroidBitmap_unlockPixels(env, bitmap);

}


extern "C"
JNIEXPORT void JNICALL Java_com_android_1app_impact_native_1on_1timer(JNIEnv * env, jobject  obj)
{

   set_context(env);

   try
   {

      android_exchange();

   }
   catch (...)
   {

   }

}


extern "C"
JNIEXPORT void JNICALL Java_com_android_1app_impact_keyDown(JNIEnv * env, jobject  obj, jint keyCode)
{

   set_context(env);

   LOGI("%s\n", "Java_com_android_1app_impact_keyDown");

}


extern "C"
JNIEXPORT void JNICALL Java_com_android_1app_impact_keyUp(JNIEnv * env, jobject  obj, jint keyCode)
{

   set_context(env);

   LOGI("%s\n", "Java_com_android_1app_impact_keyUp");

}


extern "C"
JNIEXPORT void JNICALL Java_com_android_1app_impact_keyPreImeDown(JNIEnv * env, jobject  obj, jint keyCode, jint iUni)
{

   set_context(env);

   android_key(e_message_key_down, keyCode, iUni);

}


extern "C"
JNIEXPORT void JNICALL Java_com_android_1app_impact_keyPreImeUp(JNIEnv * env, jobject  obj, jint keyCode, jint iUni)
{

   set_context(env);

   android_key(e_message_key_up, keyCode, iUni);

}


extern "C"
JNIEXPORT void JNICALL Java_com_android_1app_impact_onReceivedShowKeyboard(JNIEnv * env, jobject  obj)
{

   set_context(env);

}


extern "C"
JNIEXPORT void JNICALL Java_com_android_1app_impact_onReceivedHideKeyboard(JNIEnv * env, jobject  obj)
{

   set_context(env);

}


extern "C"
JNIEXPORT void JNICALL Java_com_android_1app_impact_lButtonDown(JNIEnv * env, jobject  obj, jfloat x, jfloat y)
{

   set_context(env);

   android_mouse(e_message_left_button_down, x, y);

}

extern "C"
JNIEXPORT jboolean JNICALL Java_com_android_1app_impact_apex_1on_1text_1composition(JNIEnv * env, jobject  obj, jstring str, jint i)
{

   set_context(env);

   const wd16char* utf16 = (wd16char*)env->GetStringChars(str, NULL);

   if (utf16 == NULL)
   {

      return false;

   }

   size_t length = (size_t)env->GetStringLength(str);

   if (::apex::get_system()->get_session()->get_focus_ui())
   {

      wd16string wstr(utf16, length);

      ::apex::get_system()->get_session()->get_focus_ui()->on_text_composition(wstr);

   }
   else
   {

      //android_on_text(os_text_keyboard, utf16, length);

   }

   env->ReleaseStringChars(str, (jchar*)utf16);

   return true;

}

extern "C"
JNIEXPORT void JNICALL Java_com_android_1app_impact_mouseMove(JNIEnv * env, jobject  obj, jfloat x, jfloat y)
{

   set_context(env);

   android_mouse(e_message_mouse_move, x, y);

}


extern "C"
JNIEXPORT void JNICALL Java_com_android_1app_impact_lButtonUp(JNIEnv * env, jobject  obj, jfloat x, jfloat y)
{

   set_context(env);

   android_mouse(e_message_left_button_up, x, y);

}


extern "C"
JNIEXPORT void JNICALL Java_com_android_1app_impact_onText(JNIEnv * env, jobject  obj, jstring bytes)
{

   set_context(env);

   if (bytes == NULL)
   {

      return;

   }

   const wchar_t* utf16 = (wchar_t*)env->GetStringChars(bytes, NULL);

   if (utf16 == NULL)
   {

      return;

   }

   size_t length = (size_t)env->GetStringLength(bytes);

   android_on_text(os_text_keyboard, utf16, length);

   env->ReleaseStringChars(bytes, (jchar*)utf16);

}


extern "C"
JNIEXPORT void JNICALL Java_com_android_1app_impact_apex_1size_1changed(JNIEnv * env, jobject  obj)
{

   set_context(env);

   ::rectangle rectangle;

   rectangle.left = 0;
   rectangle.top = 0;
   rectangle.right = g_posremote->getWidth();
   rectangle.bottom = g_posremote->getHeight();

   SetMainScreenRect(rectangle);

   ::point_i32 p;

   ::size s(g_posremote->getWidth(), g_posremote->getHeight());

   ::user::interaction* puserinteractionHost = ::apex::get_system()->get_session()->m_puserinteractionHost;

   puserinteractionHost->m_statePrevious2.m_point = p;
   puserinteractionHost->m_stateRequest2.m_point = p;
   puserinteractionHost->m_stateProcess2.m_point = p;
   puserinteractionHost->m_state2.m_point = p;
   puserinteractionHost->m_stateWindow3.m_point = p;

   puserinteractionHost->m_statePrevious2.m_size = s;
   puserinteractionHost->m_stateRequest2.m_size = s;
   puserinteractionHost->m_stateProcess2.m_size = s;
   puserinteractionHost->m_state2.m_size = s;
   puserinteractionHost->m_stateWindow3.m_size = s;

   for (auto& puserinteraction : puserinteractionHost->m_uiptraChild)
   {

      try
      {

         puserinteraction->send_message(e_message_display_change);

         //__pointer(::user::interaction_impl) pimpl = puserinteraction->m_pimpl;

         //if (pimpl)
         //{

         //   pimpl->m_puserthread->do_events();

         //   pimpl->m_pprodevian->do_events();

         //   pimpl->m_puserthread->do_events();

         //   pimpl->m_pprodevian->do_events();

         //   pimpl->m_puserthread->do_events();

         //   pimpl->m_pprodevian->do_events();

         //}

      }
      catch (...)
      {

      }

   }

}



