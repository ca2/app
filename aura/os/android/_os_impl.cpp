#include "framework.h"
#include "_os_impl.h"


void android_edit_on_set_focus(int l, int t, int r, int b, const char* pszText, int iBeg, int iEnd);
void android_edit_on_kill_focus();


::mutex* g_pmutexOs;


::mutex* osmutex()
{

   return g_pmutexOs;

}


extern thread_local JNIEnv* t_pjnienv;


int get_mem_free_available_kb()
{

   return g_poslocal->m_lMemFreeAvailableKb;

}


typedef int32_t  Fixed;


int g_iScreenW = 0;
int g_iScreenH = 0;
const char* g_pszCommandLine = NULL;
const char* g_pszCacheDir = NULL;


void android_fill_plasma(AndroidBitmapInfo * info, color32_t * pixels, double  t)
{

   if (::get_context_system() == nullptr)
   {

      output_debug_string("android_fill_plasma : aura_system is null");

      return;

   }

   auto psession = ::aura::get_system()->get_session();

   if (psession == nullptr)
   {

      output_debug_string("android_fill_plasma : context_session is null");

      return;

   }

   auto puserinteraction = __user_interaction(psession->get_user_interaction_host());

   if (puserinteraction == nullptr)
   {

      output_debug_string("android_fill_plasma : Host Window is null");

      return;

   }

   if (puserinteraction->m_pimpl == nullptr)
   {

      output_debug_string("android_fill_plasma : Host Window impl is null");

      return;

   }

   if (puserinteraction->get_window_graphics() == nullptr)
   {

      return;

   }

   auto pbuffer = dynamic_cast <::graphics::double_buffer *> (puserinteraction->get_window_graphics());

   if(pbuffer == nullptr)
   {

      output_debug_string("android_fill_plasma : double_buffer is null");

      return;

   }

   synchronization_lock slScreen(pbuffer->get_screen_sync());

   auto pimage = pbuffer->get_screen_image();

   if (!::is_ok(pimage))
   {

      output_debug_string("android_fill_plasma : image is null or empty");

      return;

   }

   pimage->map();

   auto buffer_data = pimage->get_data();

   auto buffer_width = pimage->width();

   auto buffer_height = pimage->height();

   auto buffer_stride = pimage->m_iScan;

   auto window_data = (color32_t *)pixels;

   auto window_width = info->width;

   auto window_height = info->height;

   auto window_stride = info->stride;

   auto transfer_width = minimum(buffer_width, window_width);

   auto transfer_height = minimum(buffer_height, window_height);

   ::copy_colorref_swap_red_blue(
      window_data,
      transfer_width,
      transfer_height,
      window_stride,
      buffer_data,
      buffer_stride);

}


void* load_lib(const char* l)
{

   void* handle = dlopen(l, RTLD_NOW | RTLD_GLOBAL);

   if (handle)
   {

      LOGI("dlopen(\"%s\"){3}: Library Opened Successfully : %s", l, l);

   }
   else
   {

      LOGE("dlopen(\"%s\"): %s", l, strerror(errno));

   }

   return handle;

}


::e_status os_application_system_run(::aura::system* psystem);




void android_aura_main()
{

   auto premote = g_posremote;

   auto plocal = g_poslocal;

   string strApplicationIdentifier = plocal->m_strApplicationIdentifier;

   auto psystem = platform_create_system(strApplicationIdentifier);

   psystem->m_pathCacheDirectory = premote->getCacheDirectory();

   psystem->system_construct(plocal, e_display_default);

   ::e_status estatus = psystem->os_application_system_run();
   
   if (!estatus)
   {

      printf("os_application_system_run failed\n");

      return;

   }

   ::rectangle_i32 rectangle;

   rectangle.left = 0;
   rectangle.top = 0;
   rectangle.right = premote->getWidth();
   rectangle.bottom = premote->getHeight();

   auto psession = ::aura::get_system()->get_session();

   psession->defer_initialize_host_window(rectangle);

   SetMainScreenRect(rectangle);

   //auto puserinteraction = __user_interaction(::aura::get_system()->get_session()->m_puserinteractionHost);

   //puserinteraction->place(rectangle);

   //puserinteraction->display(e_display_normal);

   //puserinteraction->set_need_layout();

   ////puserinteraction->post_redraw();

   //auto pimpl = puserinteraction->m_pimpl.cast < ::user::interaction_impl >();

   //if (pimpl)
   //{

   //   pimpl->m_pprodevian->prodevian_update_buffer(true);

   //   //oslocal()->m_bRedraw = true;

   //}


}



string get_string(jstring jstring)
{

   const char* nativeString = t_pjnienv->GetStringUTFChars(jstring, 0);

   string str = nativeString;

   t_pjnienv->ReleaseStringUTFChars(jstring, nativeString);

   return str;

}




thread_local JNIEnv* t_pjnienv;


void set_context(JNIEnv* penv)
{

   t_pjnienv = penv;

}


JNIEnv* get_jni_env()
{

   return t_pjnienv;

}


void android_exchange()
{

   synchronization_lock synchronizationlock(osmutex());

   auto plocal = g_poslocal;

   auto premote = g_posremote;

   if (plocal->m_bHideKeyboard)
   {

      premote->setHideKeyboard(true);

      plocal->m_bHideKeyboard = false;

   }

   if (plocal->m_strOpenUrl.has_char())
   {

      premote->setOpenUrl(plocal->m_strOpenUrl);

      plocal->m_strOpenUrl.Empty();

   }

   if (plocal->m_bMessageBoxOn)
   {

      int iResult = premote->getMessageBoxResult();

      if (iResult > 0)
      {

         plocal->m_bMessageBoxOn = false;

      }

   }
   else
   {

      if (plocal->m_bMessageBox)
      {

         if (plocal->m_strMessageBox.has_char())
         {

            premote->setMessageBox(plocal->m_strMessageBox);

            plocal->m_strMessageBox.Empty();

         }

         if (plocal->m_strMessageBoxCaption.is_empty())
         {

            premote->setMessageBoxCaption(plocal->m_strMessageBoxCaption);

            plocal->m_strMessageBoxCaption.Empty();

         }

         premote->setMessageBoxButton(plocal->m_iMessageBoxButton);

         plocal->m_iMessageBoxButton = 0;

         premote->setShowMessageBox(1);

         plocal->m_bMessageBoxOn = true;

         plocal->m_bMessageBox = false;

      }

   }

   if (plocal->m_strSetUserWallpaper.has_char())
   {

      premote->setUserWallpaper(plocal->m_strSetUserWallpaper);

      plocal->m_strSetUserWallpaper.Empty();

   }

   if (plocal->m_bGetUserWallpaper)
   {

      plocal->m_strGetUserWallpaper = premote->getUserWallpaper();

      plocal->m_bGetUserWallpaper = false;

   }

   if (plocal->m_bEditorSelectionUpdated)
   {

      plocal->m_bEditorSelectionUpdated = false;

      premote->setEditorSelectionStart(plocal->m_iEditorSelectionStart);

      premote->setEditorSelectionEnd(plocal->m_iEditorSelectionEnd);

      premote->setEditorSelectionUpdated(true);

   }

   if (plocal->m_bEditorTextUpdated)
   {

      plocal->m_bEditorTextUpdated = false;

      premote->setEditorText(plocal->m_strEditorText);

      premote->setEditorTextUpdated(true);

   }

   if (plocal->m_bEditFocusSet)
   {

      plocal->m_bEditFocusSet = false;

      premote->setEditFocusSet(true);

      premote->setEditFocusLeft(plocal->m_rectEditFocus.left);

      premote->setEditFocusTop(plocal->m_rectEditFocus.top);

      premote->setEditFocusRight(plocal->m_rectEditFocus.right);

      premote->setEditFocusBottom(plocal->m_rectEditFocus.bottom);

   }

   if (plocal->m_bEditFocusKill)
   {

      plocal->m_bEditFocusKill = false;

      premote->setEditFocusKill(true);

   }

   if (plocal->m_bRedraw)
   {

      plocal->m_bRedraw = false;

      premote->setRedraw(true);

   }

   if (plocal->m_bInputMethodManagerUpdateSelection)
   {

      plocal->m_bInputMethodManagerUpdateSelection = false;

      premote->setInputMethodManagerSelectionStart(plocal->m_iInputMethodManagerSelectionStart);

      premote->setInputMethodManagerSelectionEnd(plocal->m_iInputMethodManagerSelectionEnd);

      premote->setInputMethodManagerCandidateStart(plocal->m_iInputMethodManagerCandidateStart);

      premote->setInputMethodManagerCandidateEnd(plocal->m_iInputMethodManagerCandidateEnd);

      premote->setInputMethodManagerUpdateSelection(true);

   }


   if (plocal->m_bShowKeyboard)
   {

      premote->setShowKeyboard(true);

      plocal->m_bShowKeyboard = false;

   }

}


void android_edit_on_set_focus(int l, int t, int r, int b, const char * pszText, int iBeg, int iEnd)
{

   synchronization_lock synchronizationlock(osmutex());

   auto plocal = g_poslocal;

   plocal->m_bEditFocusKill = false;

   plocal->m_rectEditFocus.left = l;
   plocal->m_rectEditFocus.top = t;
   plocal->m_rectEditFocus.right = r;
   plocal->m_rectEditFocus.bottom = b;

   plocal->m_iEditorSelectionStart = iBeg;
   plocal->m_iEditorSelectionEnd = iEnd;
   plocal->m_bEditorSelectionUpdated = true;

   plocal->m_strEditorText = pszText;
   plocal->m_bEditorTextUpdated = true;

   plocal->m_bEditFocusSet = true;

}


void android_edit_on_kill_focus()
{

   synchronization_lock synchronizationlock(osmutex());

   auto plocal = g_poslocal;

   plocal->m_bEditFocusKill = true;

   plocal->m_bEditFocusSet = false;

}



