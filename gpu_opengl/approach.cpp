#include "framework.h"
#include "_gpu_opengl.h"
#include "approach.h"
#include "device.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/platform/application.h"
#include "acme/user/user/interaction.h"
#include "acme/windowing/window.h"
#include "bred/gpu/context.h"

//
//#if defined(WINDOWS_DESKTOP)
//#include "windowing_win32/window.h"
//#include <glad/glad_wgl.h>
//#include <dwmapi.h>
//
//namespace gpu_opengl
//{
//
//   // void opengl_on_create_window(HWND hwnd, HINSTANCE hInstance, HGLRC* outRC, HDC* outDC)
//   void opengl_on_create_window(HWND hwnd, HINSTANCE hInstance);
//
//} // namespace gpu_opengl
//
//
//#endif


namespace gpu_opengl
{


   approach::approach()
   {

      m_bGpuLibraryInit = false;

#ifdef WINDOWS_DESKTOP

      m_atomClass = 0;

#endif

   }


   approach::~approach()
   {

   }


#ifdef WINDOWS_DESKTOP


   LRESULT CALLBACK Draw2OpenGLWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
   {

      return DefWindowProc(hwnd, message, wparam, lparam);

   }


#endif // WINDOWS_DESKTOP


   void approach::initialize(::particle * pparticle)
   {

      ::object::initialize(pparticle);

      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         m_papplication->m_gpu.m_eoutputDraw2d = ::gpu::e_output_gpu_buffer;
         m_papplication->m_gpu.m_eoutputEngine = ::gpu::e_output_gpu_buffer;

      }
      else
      {

         m_papplication->m_gpu.m_eoutputDraw2d = ::gpu::e_output_cpu_buffer;
         m_papplication->m_gpu.m_eoutputEngine = ::gpu::e_output_cpu_buffer;

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

            throw ::exception(error_failed);

         }

      }

#endif

   }




   void approach::defer_init_gpu_library()
   {

      if (m_bGpuLibraryInit)
      {

         return;

      }

//#if !defined(LINUX) && !defined(__APPLE__) && !defined(__BSD__)

      gladLoadGL();

      informationf("GL Version: %s\n", glGetString(GL_VERSION));

      m_bGpuLibraryInit = true;

//#endif

//      if (!m_bGlewInit)
//      {
//         
//#if !defined(__APPLE__) && !defined(__ANDROID__)
//
//         glewExperimental = GL_TRUE;
//
//         GLenum err = glewInit();
//
//         if (err != GLEW_OK)
//         {
//
//            const_char_pointer pszErrorString = (const_char_pointer )glewGetErrorString(err);
//
//            //throw ::exception(error_resource);
//            // Problem: glewInit failed, something is seriously wrong.
//            informationf("glewInit failed: %s (%d)\n", pszErrorString, err);
//
//            throw ::exception(error_failed);
//
//         }
//         
//#endif
//
//         m_bGlewInit = true;

//      }

      //return ::success;

   }


#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

   int approach::fread(void* data, int c, int s, ::file::file* pfile)
   {

      return (int) (pfile->read(data,s * c) / c);

   }

   
   void approach::gpu_on_before_create_window(::acme::windowing::window* pwindow)
   {

      ::cast < ::gpu_opengl::approach > papproach = m_papplication->get_gpu_approach();

      papproach->_on_before_create_window(pwindow);
      //      defer_load_wgl_extensions();

   }


   

   void approach::gpu_on_create_window(::acme::windowing::window *pacmewindowingwindow)
   {

      ::gpu::bred_approach::gpu_on_create_window(pacmewindowingwindow);


   }


} // namespace gpu_opengl



