#include "framework.h"
#include "approach.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/platform/application.h"
#include "bred/gpu/context.h"
#include "windowing_win32/window.h"
#include "glad_wgl.h"

#include <dwmapi.h>

namespace gpu_opengl
{//// Helper to create dummy OpenGL context
   //HGLRC CreateDummyContext(HDC hdc) {
   //   PIXELFORMATDESCRIPTOR pfd = {
   //       sizeof(PIXELFORMATDESCRIPTOR), 1,
   //       PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
   //       PFD_TYPE_RGBA, 32,
   //       0, 0, 0, 0, 0, 0,
   //       0, 0, 0, 0, 0, 0, 0,
   //       24, 8, 0,
   //       PFD_MAIN_PLANE,
   //       0, 0, 0, 0
   //   };

   //   int pixelFormat = ChoosePixelFormat(hdc, &pfd);
   //   SetPixelFormat(hdc, pixelFormat, &pfd);
   //   return wglCreateContext(hdc);
   //}
   // WGL extension function pointer

   // Create dummy window and context to load WGL extensions
   HGLRC CreateDummyContext(HDC* outDC, HWND* outHWND) {
      WNDCLASSW wc = { 0 };
      wc.style = CS_OWNDC;
      wc.lpfnWndProc = DefWindowProc;
      wc.hInstance = GetModuleHandle(NULL);
      wc.lpszClassName = L"DummyGL";

      RegisterClass(&wc);
      HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"", WS_OVERLAPPEDWINDOW,
         0, 0, 1, 1, NULL, NULL, wc.hInstance, NULL);

      HDC dc = GetDC(hwnd);
      PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR), 1 };
      pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
      pfd.iPixelType = PFD_TYPE_RGBA;
      pfd.cColorBits = 32;

      int pf = ChoosePixelFormat(dc, &pfd);
      SetPixelFormat(dc, pf, &pfd);

      HGLRC rc = wglCreateContext(dc);
      wglMakeCurrent(dc, rc);

      *outDC = dc;
      *outHWND = hwnd;
      return rc;
   }
   PFNWGLCREATECONTEXTATTRIBSARBPROC loaded_wglCreateContextAttribsARB = NULL;
   PFNWGLCHOOSEPIXELFORMATARBPROC loaded_wglChoosePixelFormatARB = NULL;
   // Load only required WGL extensions
   void LoadWGLExtensions() {
      loaded_wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)
         wglGetProcAddress("wglCreateContextAttribsARB");
      loaded_wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)
         wglGetProcAddress("wglChoosePixelFormatARB");
   }

   void defer_load_wgl_extensions()
   {
      if (loaded_wglCreateContextAttribsARB &&
         loaded_wglChoosePixelFormatARB)
      {
         return;
      }

      // Step 1: Create dummy context to load WGL extensions
      HDC dummyDC;
      HWND dummyHWND;
      HGLRC dummyRC = CreateDummyContext(&dummyDC, &dummyHWND);

      LoadWGLExtensions();

      wglMakeCurrent(NULL, NULL);
      wglDeleteContext(dummyRC);
      ReleaseDC(dummyHWND, dummyDC);
      DestroyWindow(dummyHWND);

   }


 

   void approach::_on_before_create_window(::windowing::window* pwindow)
   {
      //::cast < ::gpu_opengl::approach > papproach = m_papplication->get_gpu_approach();
      //papproach->_on_before_create_window(pwindow);
      defer_load_wgl_extensions();

   }

   //void opengl_on_create_window(HWND hwnd, HINSTANCE hInstance, HGLRC* outRC, HDC* outDC)
   void opengl_on_create_window(HWND hwnd, HINSTANCE hInstance)
   {


      //HDC dc = GetDC(hwnd);

      //int pixelAttribs[] = {
      //    WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
      //    WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
      //    WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
      //    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
      //    WGL_COLOR_BITS_ARB, 32,
      //    WGL_DEPTH_BITS_ARB, 24,
      //    WGL_STENCIL_BITS_ARB, 8,
      //    0
      //};

      //int format;
      //UINT numFormats;
      //loaded_wglChoosePixelFormatARB(dc, pixelAttribs, NULL, 1, &format, &numFormats);
      //PIXELFORMATDESCRIPTOR pfd;
      //DescribePixelFormat(dc, format, sizeof(pfd), &pfd);
      //SetPixelFormat(dc, format, &pfd);

      //int contextAttribs[] = {
      //    WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
      //    WGL_CONTEXT_MINOR_VERSION_ARB, 3,
      //    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
      //    0
      //};

      ///*HGLRC rc = wglCreateContextAttribsARB(dc, 0, contextAttribs);
      //wglMakeCurrent(dc, rc);

      //*outRC = rc;
      //*outDC = dc;*/
      //::ReleaseDC(hwnd, dc);
   }


   void approach::_on_create_window(::windowing::window* pwindowParam)
   {
      
      ::cast < ::windowing_win32::window > pwindow = pwindowParam;

      auto hwnd = pwindow->m_hwnd;

      opengl_on_create_window(hwnd, (HINSTANCE) system()->m_hinstanceThis);

      DWM_BLURBEHIND bb = { 0 };
      HRGN hRgn = CreateRectRgn(0, 0, -1, -1);
      bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
      bb.hRgnBlur = hRgn;
      bb.fEnable = TRUE;
      DwmEnableBlurBehindWindow(hwnd, &bb);

   }


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

#if !defined(LINUX) && !defined(__APPLE__) && !defined(__BSD__)

      gladLoadGL();

      informationf("GL Version: %s\n", glGetString(GL_VERSION));

      m_bGpuLibraryInit = true;

#endif

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
//            const ::ansi_character * pszErrorString = (const char *) glewGetErrorString(err);
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

   
   ::gpu::payload approach::load_dds(const ::scoped_string & scopedstrImagePath) 
   {

      auto fp = file()->get_reader(scopedstrImagePath);

      unsigned char header[124];

      //FILE * fp;

      ///* try to open the file */
      //fp = fopen(strImagePath, "rb");
      //if (fp == NULL) {
      //   printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", strImagePath.c_str()); getchar();
      //   return 0;
      //}

      /* verify the type of file */
      char filecode[4];
      fread(filecode, 1, 4, fp);
      if (::string(filecode, 4).case_insensitive_order("DDS ") != 0) {
         //fclose(fp);
         return {};
      }

      /* get the surface desc */
      fread(&header, 124, 1, fp);

      unsigned int height = *(unsigned int *)&(header[8]);
      unsigned int width = *(unsigned int *)&(header[12]);
      unsigned int linearSize = *(unsigned int *)&(header[16]);
      unsigned int mipMapCount = *(unsigned int *)&(header[24]);
      unsigned int fourCC = *(unsigned int *)&(header[80]);


      unsigned char * buffer;
      unsigned int bufsize;
      /* how big is it going to be including all mipmaps? */
      bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
      buffer = (unsigned char *)malloc(bufsize * sizeof(unsigned char));
      fread(buffer, 1, bufsize, fp);
      /* close the file pointer */
      //fclose(fp);

      //unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
      unsigned int format;
      switch (fourCC)
      {
      case FOURCC_DXT1:
         format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
         break;
      case FOURCC_DXT3:
         format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
         break;
      case FOURCC_DXT5:
         format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
         break;
      default:
         free(buffer);
         return {};
      }

      // Create one OpenGL texture
      GLuint textureID;
      glGenTextures(1, &textureID);

      // "Bind" the newly created texture : all future texture functions will modify this texture
      glBindTexture(GL_TEXTURE_2D, textureID);
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

      unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
      unsigned int offset = 0;

      /* load the mipmaps */
      for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
      {
         unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
         glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
            0, size, buffer + offset);

         offset += size;
         width /= 2;
         height /= 2;

         // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
         if (width < 1) width = 1;
         if (height < 1) height = 1;

      }

      free(buffer);

      gpu::payload payload;

      payload.m_iUniform = textureID;

      return payload;


   }


   ::file::path approach::shader_path(const ::file::path& pathShader)
   {

      if (pathShader.begins("matter://shaders/"))
      {

         auto pathFolder = pathShader.folder();

         return pathFolder / "opengl" / pathShader.name();

      }

      return pathShader;

   }





} // namespace gpu_opengl



