#include "framework.h"
#include "_os_impl.h"


__pointer(os_local) g_poslocal;
__pointer(os_remote) g_posremote;


void android_edit_on_set_focus(int l, int t, int r, int b, const char* pszText, int iBeg, int iEnd);
void android_edit_on_kill_focus();


mutex* g_pmutexOs;


mutex* osmutex()
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


void android_fill_plasma(AndroidBitmapInfo * info, void * pixels, double  t)
{

   if (::get_context_system() == nullptr)
   {

      output_debug_string("android_fill_plasma : apex_system is null");

      return;

   }

   if (System.get_context_session() == nullptr)
   {

      output_debug_string("android_fill_plasma : context_session is null");

      return;

   }

   if (System.get_context_session()->m_puiHost == nullptr)
   {

      output_debug_string("android_fill_plasma : Host Window is null");

      return;

   }

   if (System.get_context_session()->m_puiHost->m_pimpl == nullptr)
   {

      output_debug_string("android_fill_plasma : Host Window impl is null");

      return;

   }

   if (System.get_context_session()->m_puiHost->get_window_graphics() == nullptr)
   {

      //   output_debug_string("android_fill_plasma : get_window_graphics returned null");

      return;

   }

   auto pbuffer = dynamic_cast <::graphics::double_buffer *> (System.get_context_session()->m_puiHost->get_window_graphics());

   if(pbuffer == nullptr)
   {

      output_debug_string("android_fill_plasma : double_buffer is null");

      return;

   }

   sync_lock slScreen(pbuffer->get_screen_sync());

   auto pimage = pbuffer->get_screen_image();

   pimage->map();

   if (!::is_ok(pimage))
   {

      output_debug_string("android_fill_plasma : image is null or empty");

      return;

   }

   auto pdata = pimage->get_data();

   auto image_width = pimage->width();

   auto image_height = pimage->height();

   auto image_stride = pimage->m_iScan;

   auto window_width = info->width;

   auto window_height = info->height;

   auto window_stride = info->stride;

   auto transfer_width = min(image_width, window_width);

   auto transfer_height = min(image_height, window_height);

   ::copy_colorref_swap_red_blue((color32_t *) pixels,
   transfer_width,
   transfer_height,
   window_stride,
   pdata,
   image_stride);

   //output_debug_string("android_fill_plasma OK (area="+__str(pbuffer->m_spimageBuffer.area())+")");

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


::estatus os_application_system_run(::apex::system* psystem);


int SetMainScreenRect(LPCRECT32 lpcrect);

void android_apex_main()
{

   auto premote = g_posremote;

   auto plocal = g_poslocal;

   auto psystem = __new(::apex::system());

   psystem->m_pathCacheDir = premote->getCacheDir();

   psystem->system_construct(plocal, display_default);

   ::estatus estatus = os_application_system_run(psystem);
   
   if (!estatus)
   {

      printf("os_application_system_run failed\n");

      return;

   }

   ::rect rect;

   rect.left = 0;
   rect.top = 0;
   rect.right = premote->getWidth();
   rect.bottom = premote->getHeight();

   System.get_context_session()->defer_initialize_host_window(rect);

   SetMainScreenRect(rect);

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

   sync_lock sl(osmutex());

   auto plocal = g_poslocal;

   auto premote = g_posremote;

   if (plocal->m_bShowKeyboard)
   {

      premote->setShowKeyboard(true);

      plocal->m_bShowKeyboard = false;

   }

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

   if (plocal->m_bEditFocusSet)
   {

      plocal->m_bEditFocusSet = false;

      premote->setEditFocusSet(true);

      premote->setEditFocusLeft(plocal->m_rectEditFocus.left);

      premote->setEditFocusTop(plocal->m_rectEditFocus.top);

      premote->setEditFocusRight(plocal->m_rectEditFocus.right);

      premote->setEditFocusBottom(plocal->m_rectEditFocus.bottom);

      premote->setEditFocusText(plocal->m_strEditFocus);

      premote->setEditFocusSelBeg(plocal->m_iEditFocusSelBeg);

      premote->setEditFocusSelEnd(plocal->m_iEditFocusSelEnd);

   }

   if (plocal->m_bEditFocusKill)
   {

      plocal->m_bEditFocusKill = false;

      premote->setEditFocusKill(true);

   }

}


void android_edit_on_set_focus(int l, int t, int r, int b, const char * pszText, int iBeg, int iEnd)
{

   auto plocal = g_poslocal;

   plocal->m_bEditFocusKill = false;

   plocal->m_rectEditFocus.left = l;
   plocal->m_rectEditFocus.top = t;
   plocal->m_rectEditFocus.right = r;
   plocal->m_rectEditFocus.bottom = b;

   plocal->m_strEditFocus = pszText;

   plocal->m_iEditFocusSelBeg = iBeg;
   plocal->m_iEditFocusSelEnd = iEnd;

   plocal->m_bEditFocusSet = true;

}


void android_edit_on_kill_focus()
{

   auto plocal = g_poslocal;

   plocal->m_bEditFocusSet = true;

   plocal->m_bEditFocusKill = false;

}



