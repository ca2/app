#include "framework.h"
#include "_.h"
#include "context_egl.h"


namespace opengl
{


   ::gpu::context * create_egl_context()
   {

      return new context_egl();

   }


   context_egl::context_egl()
   {
      if (glewInit() != GLEW_NO_ERROR)
      {
         //cout << "Failed to initialize GLEW... " << endl;
         //return -1;

      }


      m_emode = e_mode_egl;

   }


   context_egl::~context_egl()
   {


   }


   ::e_status context_egl::_create_offscreen_buffer(const ::size_i32 & size)
   {

      auto psystem = m_psystem->m_paurasystem;

      auto pgpu = psystem->get_gpu();

      __pointer(opengl) popengl = pgpu;

      if (::is_null(popengl))
      {

         return ::error_failed;

      }

      EGLint attribList[]=
      {

         EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
         EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
         EGL_CONFORMANT, EGL_OPENGL_BIT,
         EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
         EGL_RED_SIZE, 8,
         EGL_GREEN_SIZE, 8,
         EGL_BLUE_SIZE, 8,
         EGL_ALPHA_SIZE, 8,
         EGL_LEVEL, 0,
         EGL_BUFFER_SIZE, 24,
         EGL_NONE

      };

      //synchronous_lock synchronouslock(x11_mutex());

      //xdisplay display(x11_get_display());

      //m_display = eglGetDisplay((EGLNativeDisplayType)display);

      m_display = eglGetDisplay((EGLNativeDisplayType)0);

      if (m_display == EGL_NO_DISPLAY)
      {

         fprintf(stderr, "Got no EGL display.\n");

         return false;

      }

      if (!eglInitialize(m_display, NULL, NULL))
      {

         fprintf(stderr, "Unable to initialize EGL\n");

         return false;

      }

      eglBindAPI(EGL_OPENGL_ES_API);

      int iConfigCount = 0;

      if (!eglChooseConfig(m_display, attribList, &m_config, 1, &iConfigCount))
      {

         int iError = eglGetError();

         const char * pszError = (const char *) eglQueryString(m_display, iError);

         fprintf(stderr, "Failed to choose config (eglError: %s : 0x%x)\n", pszError, iError);

         return false;

      }

      if (iConfigCount != 1)
      {

         fprintf(stderr, "Didn't get just one config, but %d\n", iConfigCount);

         return false;

      }

      //#if OSMESA_MAJOR_VERSION * 100 + OSMESA_MINOR_VERSION >= 305
      //   /* specify Z, stencil, accum sizes */
      //   m_mesacontext = OSMesaCreateContextExt( GL_RGBA, 16, 0, 0, NULL );
      //#else
      //   m_mesacontext = OSMesaCreateContext( GL_RGBA, NULL );
      //#endif
      //   if (!m_mesacontext)
      //   {
      //
      //      printf("OSMesaCreateContext failed!\n");
      //
      //      return 0;
      //
      //   }

      EGLint pbufferAttribs[5];
      pbufferAttribs[0] = EGL_WIDTH;
      pbufferAttribs[1] = size.cx;
      pbufferAttribs[2] = EGL_HEIGHT;
      pbufferAttribs[3] = size.cy;
      pbufferAttribs[4] = EGL_NONE;

      // Step 6 - Create a surface to draw to.
      m_surface = eglCreatePbufferSurface(m_display, m_config, pbufferAttribs);

      if (m_surface == EGL_NO_SURFACE)
      {

         return false;

      }

      // Step 7 - Create a context.
      //EGLContext eglContext;
      m_context = eglCreateContext(m_display, m_config, NULL, NULL);
      //qDebug() << "egl error" << eglGetError();

      if (m_context == EGL_NO_CONTEXT)
      {

         //qDebug() << "context issue";
         return false;

      }

      return ::success;

   }


   ::e_status context_egl::make_current()
   {

      bool bMakeCurrentOk = eglMakeCurrent(
            m_display,
            m_surface,
            m_surface,
            m_context);

      if (!bMakeCurrentOk)
      {

         printf("eglMakeCurrent failed!\n");

         return ::error_failed;

      }

      return ::success;

   }


   ::e_status context_egl::resize_offscreen_buffer(const ::size_i32& size)
   {

      auto estatus = ::gpu::context::resize_offscreen_buffer(size);

      if(!estatus)
      {

         return estatus;

      }

      EGLint pbufferAttribs[5];
      pbufferAttribs[0] = EGL_WIDTH;
      pbufferAttribs[1] = size.cx;
      pbufferAttribs[2] = EGL_HEIGHT;
      pbufferAttribs[3] = size.cy;
      pbufferAttribs[4] = EGL_NONE;

      // Step 6 - Create a surface to draw to.
      auto surface = eglCreatePbufferSurface(m_display, m_config, pbufferAttribs);

      if (surface == EGL_NO_SURFACE)
      {

         return ::error_failed;

      }

      auto surfaceOld = m_surface;

      m_surface = surface;

      eglDestroySurface(m_display, surfaceOld);

      return ::success_none;

   }


   ::e_status context_egl::destroy_offscreen_buffer()
   {

      ::e_status estatus = error_failed;

      return estatus;

   }


   string context_egl::get_shader_version_text()
   {

      return "version 300 es";

   }


   void context_egl::_translate_shader(string_array & stra)
   {

      strsize iFindPrecision = stra.find_first_begins_ci("precision ");

      if(iFindPrecision >= 0)
      {

         stra[iFindPrecision] = "precision highp float;";

      }
      else
      {

         stra.insert_at(1, "precision highp float;");

         iFindPrecision = 1;

      }

      strsize iFind = stra.find_first_begins_ci("out vec4 ");

      if(iFind >= 0)
      {

         stra[iFind] = "out vec4 fragmentColor;";

      }
      else
      {

         stra.insert_at(iFindPrecision + 1, "out vec4 fragmentColor;");

      }

      stra.replace("gl_FragColor", "fragmentColor");

   }


} // namespace gpu



