#include "framework.h"
#include "_os_impl.h"
#include "aura/graphics/graphics/double_buffer.h"
//#include "aura/graphics/image/_image.h"


void android_edit_on_set_focus(int l, int t, int r, int b, const ::string & pszText, int iBeg, int iEnd);
void android_edit_on_kill_focus();


typedef int32_t  Fixed;


int g_iScreenW = 0;
int g_iScreenH = 0;
const char* g_pszCommandLine = NULL;
const char* g_pszCacheDir = NULL;

CLASS_DECL_ACME ::acme::system * acmesystem();


void android_fill_plasma(AndroidBitmapInfo * info, color32_t * pixels, double  t)
{

   if (g_psystem == nullptr)
   {

      output_debug_string("android_fill_plasma : aura_system is null");

      return;

   }

   auto psession = g_psystem->get_session();

   if (psession == nullptr)
   {

      output_debug_string("android_fill_plasma : context_session is null");

      return;

   }

   ::pointer<::user::interaction>puserinteraction = psession->get_user_interaction_host();

   if (puserinteraction == nullptr)
   {

      output_debug_string("android_fill_plasma : Host Window is null");

      return;

   }

   if (puserinteraction->m_pinteractionimpl == nullptr)
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

   synchronous_lock slScreen(pbuffer->get_screen_sync());

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


void* load_lib(const ::string & strLibrary)
{

   void* handle = dlopen(strLibrary, RTLD_NOW | RTLD_GLOBAL);

   if (handle)
   {

      LOGI("dlopen(\"%s\"){3}: Library Opened Successfully : %s", strLibrary.c_str(), strLibrary.c_str());

   }
   else
   {

      LOGE("dlopen(\"%s\"): %s", strLibrary.c_str(), strerror(errno));

   }

   return handle;

}


void os_application_system_run(::aura::system* psystem);

