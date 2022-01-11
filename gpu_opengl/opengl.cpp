#include "framework.h"
#include "_.h"


namespace opengl
{


#ifdef WINDOWS_DESKTOP

   ::gpu::context * create_system_context();

#elif defined(__APPLE__)

#if 1

   ::gpu::context * create_fbo_context();

#else

   ::gpu::context * create_cgl_context();

#endif

#else

   ::gpu::context * create_egl_context();

   ::gpu::context * create_glx_context();

#endif


   opengl::opengl()
   {

      m_bGlewInit = false;

#ifdef WINDOWS_DESKTOP

      m_atomClass = 0;

#endif

   }


   opengl::~opengl()
   {

   }


#ifdef WINDOWS_DESKTOP


   LRESULT CALLBACK Draw2OpenGLWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
   {

      return DefWindowProc(hwnd, message, wparam, lparam);

   }


#endif // WINDOWS_DESKTOP


   void opengl::initialize(::object * pobject)
   {

      void estatus = ::object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

#ifdef WINDOWS_DESKTOP

      if (!m_atomClass)
      {

         WNDCLASSW wndclass = {};

         wndclass.style = CS_OWNDC;
         wndclass.lpfnWndProc = &Draw2OpenGLWndProc;
         wndclass.hInstance = ::GetModuleHandleW(L"gpu_opengl.dll");
         wndclass.lpszClassName = L"draw2d_opengl_offscreen_buffer_window";

         m_atomClass = RegisterClassW(&wndclass);

         if (!m_atomClass)
         {

            return ::error_failed;

         }

      }

#endif

      return estatus;

   }


   ::gpu::context * opengl::create_context()
   {

#ifdef WINDOWS_DESKTOP

      return create_system_context();

#elif defined(__APPLE__)
      
#if 1

      return create_fbo_context();
      
#else
      
      return create_cgl_context();
      
#endif

#else

      string strWaylandDisplay(getenv("WAYLAND_DISPLAY"));

      if(strWaylandDisplay.has_char())
      {

         return create_egl_context();

      }
      else
      {

         return create_glx_context();

      }

#endif

   }


   void opengl::defer_init_glew()
   {

      if (!m_bGlewInit)
      {
         
#if !defined(__APPLE__)

         glewExperimental = GL_TRUE;

         GLenum err = glewInit();

         if (err != GLEW_OK)
         {

            const char * pszErrorString = (const char *) glewGetErrorString(err);

            //__throw(error_resource);
            // Problem: glewInit failed, something is seriously wrong.
            FORMATTED_TRACE("glewInit failed: %s (%d)\n", pszErrorString, err);

            return ::error_failed;

         }
         
#endif

         m_bGlewInit = true;

      }

      return ::success;

   }


} // namespace opengl



