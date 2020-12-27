#include "framework.h"
#include "_os_impl.h"
#include "aura/user/interaction_thread.h"
#include "aura/user/interaction_prodevian.h"


extern "C"
JNIEXPORT void JNICALL Java_com_android_1app_impact_render_1impact(JNIEnv * env, jobject  obj, jobject bitmap, jlong  time_ms, jobject result)
{

   set_context(env);

   AndroidBitmapInfo    info = {};
   int                  ret;

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

   color32_t * pixels = nullptr;

   if ((ret = AndroidBitmap_lockPixels(env, bitmap, (void * *) &pixels)) < 0)
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
JNIEXPORT jboolean JNICALL Java_com_android_1app_impact_InputConnectionSetComposingText(JNIEnv * env, jobject  obj, jstring text, jint newCursorPosition)
{

   set_context(env);

   const wd16char* utf16 = (wd16char*)env->GetStringChars(text, NULL);

   if (utf16 == NULL)
   {

      return false;

   }

   size_t length = (size_t)env->GetStringLength(text);

   auto psession = Session;

   if (psession->get_focus_ui())
   {

      wd16string wstr(utf16, length);

      string str(wstr);

      const char * pszComposingText = str;

      psession->get_focus_ui()->InputConnectionSetComposingText(str, newCursorPosition);

   }
   else
   {

      //android_on_text(os_text_keyboard, utf16, length);

   }

   env->ReleaseStringChars(text, (jchar*)utf16);

   return TRUE;

}


extern "C"
JNIEXPORT jboolean JNICALL Java_com_android_1app_impact_InputConnectionSetComposingRegion(JNIEnv * env, jobject obj, jint start, jint end)
{

   set_context(env);

   auto psession = Session;

   if (psession->get_focus_ui())
   {

      psession->get_focus_ui()->InputConnectionSetComposingRegion(start, end);

   }
   else
   {

      //android_on_text(os_text_keyboard, utf16, length);

   }

   return TRUE;

}


extern "C"
JNIEXPORT jboolean JNICALL Java_com_android_1app_impact_InputConnectionFinishComposingText(JNIEnv * env, jobject  obj)
{

   set_context(env);

   auto psession = Session;

   if (psession->get_focus_ui())
   {

      psession->get_focus_ui()->InputConnectionFinishComposingText();

   }
   else
   {

      //android_on_text(os_text_keyboard, utf16, length);

   }

   return TRUE;

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
JNIEXPORT void JNICALL Java_com_android_1app_impact_aura_1size_1changed(JNIEnv * env, jobject  obj)
{

   set_context(env);

   ::rect rect;

   rect.left = 0;
   rect.top = 0;
   rect.right = g_posremote->getWidth();
   rect.bottom = g_posremote->getHeight();

   SetMainScreenRect(rect);

   //auto pimpl = puserinteraction->m_pimpl.cast < ::user::interaction_impl >();

   //if (pimpl)
   //{

   //   pimpl->m_pprodevian->prodevian_update_buffer(true);

   //   //oslocal()->m_bRedraw = true;

   //}

   //auto puiptraChild = puserinteraction->m_puiptraChild;

   //if (puiptraChild)
   //{

   //   for (auto & puserinteractionChild : puiptraChild->interactiona())
   //   {

   //      try
   //      {

   //         puserinteractionChild->send_message(e_message_display_change);

   //         //__pointer(::user::interaction_impl) pimpl = puserinteraction->m_pimpl;

   //         //if (pimpl)
   //         //{

   //         //   pimpl->m_puserthread->do_events();

   //         //   pimpl->m_pprodevian->do_events();

   //         //   pimpl->m_puserthread->do_events();

   //         //   pimpl->m_pprodevian->do_events();

   //         //   pimpl->m_puserthread->do_events();

   //         //   pimpl->m_pprodevian->do_events();

   //         //}

   //      }
   //      catch (...)
   //      {

   //      }

   //   }

   //}

}



