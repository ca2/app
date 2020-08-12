#include "framework.h"
#include "android.h"
#include "android_window_cairo_egl.h"



window_cairo_egl::window_cairo_egl()
{

   //m_cairoSource = nullptr;
   //m_cairosurfaceSource = nullptr;

}


window_cairo_egl::~window_cairo_egl()
{

}


void window_cairo_egl::create_window_graphics(oswindow interaction_impl,i64 cxParam,i64 cyParam,int iStrideParam)
{



   destroy_window_graphics();



   sync_lock sl(&user_mutex());

   EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

   eglInitialize(display, 0, 0);


   /*
   * Here specify the attributes of the desired configuration.
   * Below, we select an EGLConfig with at least 8 bits per color
   * component compatible with on-screen windows
   */
   const EGLint attribs[] = {
      EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
      EGL_BLUE_SIZE, 8,
      EGL_GREEN_SIZE, 8,
      EGL_RED_SIZE, 8,
      EGL_NONE
   };
   EGLConfig config;
   EGLint w, h, format;
   EGLint numConfigs;

   /* Here, the application chooses the configuration it desires. In this
   * sample, we have a very simplified selection process, where we pick
   * the first EGLConfig that matches our criteria */
   eglChooseConfig(display, attribs, &config, 1, &numConfigs);

   ANativeWindow_setBuffersGeometry(window->m_engine->app->window, 0, 0, format);

   m_cairo = eglCreateContext(display, config, nullptr, nullptr);

   EGLSurface surface = eglCreateWindowSurface(display, config, window->m_engine->app->window, nullptr);

   if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
      LOGW("Unable to eglMakeCurrent");
      return false;
   }
   
   eglQuerySurface(display, surface, EGL_WIDTH, &w);

   eglQuerySurface(display, surface, EGL_HEIGHT, &h);

   window->m_engine->display = display;
   window->m_engine->context = context;
   window->m_engine->surface = surface;
   window->m_engine->width = w;
   window->m_engine->height = h;
   window->m_engine->m_pstate->angle = 0;

   m_cairosurface = cairo_gl_surface_create_for_egl(m_cairo, surface, w, h);

   ::window_graphics::create_window_graphics(interaction_impl, cxParam, cyParam, iStride);

}





void window_cairo_egl::destroy_window_graphics()
{

   ::window_graphics::destroy_window_graphics();


}


void window_cairo_egl::update_window(oswindow interaction_impl, COLORREF * pOsBitmapData, const ::rect & rect, int iStride)
{


   copy_colorref(width(rect), height(rect), (COLORREF *) m_mem.get_data(), pOsBitmapData, iStride);


}



