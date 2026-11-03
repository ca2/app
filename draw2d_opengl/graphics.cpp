#include "platform.h"
#include "_draw2d_opengl.h"
#include "_draw2d.h"
#include "bitmap.h"
#include "draw2d.h"
#include "pen.h"
#include "path.h"
#include "font.h"
#include "brush.h"
#include "image.h"
#include "color.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/task.h"
#include "acme/platform/application.h"
#include "acme/prototype/geometry2d/item.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "aura/graphics/draw2d/domain.h"
#include "aura/graphics/graphics/buffer_item.h"
#include "bred/gpu/_model.h"
#include "bred/gpu/bred_approach.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/buffer.h"
#include "bred/gpu/device.h"
#include "bred/gpu/window_attachment.h"
#include "bred/gpu/layer.h"
#include "bred/gpu/model_buffer.h"
#include "bred/gpu/pixmap.h"
//#include "bred/gpu/aaa_render.h"
#include "bred/gpu/render_target.h"
#include "bred/gpu/texture_site.h"
#include "bred/graphics3d/types.h"
#ifdef WINDOWS_DESKTOP
#include "gpu_opengl/device_win32.h"
#endif
#include "gpu_opengl/lock.h"
#include "gpu_opengl/renderer.h"
#include "gpu_opengl/texture.h"
#include "aura/graphics/write_text/font_enumeration_item.h"
#include "aura/user/user/interaction.h"
#ifdef WINDOWS_DESKTOP
#include "windowing_win32/window.h"
#include <dwmapi.h>
#define GLAD_GLAPI_EXPORT

#include <glad/glad_wgl.h>
//#define WGL_CONTEXT_FLAGS_ARB 0X2094
#define WGL_CONTEXT_COREPROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define FONT_POINT_DENOMINATOR 28.0
#define FONT_PIXEL_DENOMINATOR 35.0
HGLRC initialize_opengl_version(HDC hdc, int iMajor, int iMinor);
#else
#include "aura/windowing/window.h"
#endif
//
//
//
#include <math.h>
#include "acme/prototype/geometry2d/_defer_item.h"
//#include <gl/freeglut.h>
//int  opengl_init();

#define __expand_float_pre_rgba(color) (color.f32_opacity()*color.f32_red()),(color.f32_opacity()* color.f32_green()), (color.f32_opacity()*color.f32_blue()), color.f32_opacity()





namespace opengl
{

#include "line1.h"

}

#ifdef WINDOWS_DESKTOP
BOOL CALLBACK draw2d_opengl_EnumFamCallBack(LPLOGFONT lplf, LPNEWTEXTMETRIC lpntm, unsigned int FontType, LPVOID p);
#endif

class draw2d_opengl_enum_fonts
{
public:


   ::write_text::font_enumeration_item_array& m_itema;


   draw2d_opengl_enum_fonts(::write_text::font_enumeration_item_array& itema) :
      m_itema(itema)
   {

   }


};


namespace draw2d_opengl
{







//   const char proto_vert[] = R"vert(
//#version 330 core
//
//layout(location = 0) in vec2 inPos;
//layout(location = 1) in vec4 inColor;
//
//out vec4 fragColor;
//
//void main() {
//    gl_Position = vec4(inPos, 0.0, 1.0);
//    fragColor = inColor;
//})vert";
//   const char proto_frag[] = R"frag(
//            #version 330 core
//
//               in vec4 fragColor;      // Input from the vertex shader (location = 0)
//            out vec4 outColor;      // Output to framebuffer (location = 0)
//
//            void main() {
//               outColor = fragColor;
//            }
//)frag";

   //ATOM class_atom = NULL;



   graphics* thread_graphics()
   {

      return ::get_task()->payload("draw2d_opengl::graphics").cast < graphics >();

   }


   graphics::graphics()
   {

 
      //m_hrc = nullptr;
      //m_hwnd = nullptr;
      //m_hglrc = nullptr;
      //m_pointTranslate = ::i32_point();
      m_bPrinting = false;
      m_pimageAlphaBlend = nullptr;
      m_size.set(0, 0);
      //m_hdc = nullptr;
      //m_hdcGraphics = nullptr;
      m_ewritetextrendering = ::write_text::e_rendering_anti_alias_grid_fit;
//      m_dFontFactor = 1.0;

   }


   //void graphics::assert_ok() const
   //{

   //   object::assert_ok();

   //}


   //void graphics::dump(dump_context& dumpcontext) const
   //{
   //   
   //   object::dump(dumpcontext);

   //   dumpcontext << "m_hdc = " << (iptr) m_hdc;
   //   dumpcontext << "\nm_hAttribDC = " << (iptr) m_hdc;
   //   dumpcontext << "\nm_bPrinting = " << m_bPrinting;

   //   dumpcontext << "\n";

   //}


   graphics::~graphics()
   {

      //opengl_delete_offscreen_buffer();

      DeleteDC();

   }

#ifdef _DEBUG

   long long graphics::increment_reference_count()
   {

      return ::particle::increment_reference_count();

   }


   long long graphics::decrement_reference_count()
   {

      return ::particle::decrement_reference_count();

   }


#endif

   //bool graphics::IsPrinting() const
   //{

   //   return m_bPrinting;

   //}


   bool graphics::CreateDC(const ::scoped_string& lpszDriverName, const ::scoped_string& lpszDeviceName, const char* lpszOutput, const void* lpInitData)
   {
      //return Attach(::CreateDC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*)lpInitData));
      return false;
   }


   bool graphics::CreateIC(const ::scoped_string& lpszDriverName, const ::scoped_string& lpszDeviceName, const char* lpszOutput, const void* lpInitData)
   {
      //return Attach(::CreateIC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*) lpInitData));
      return false;
   }


   //void graphics::create_memory_graphics(const ::i32_size & size)
   //{

   //   ::gpu::graphics::create_memory_graphics(size);

   //   // ::i32_size size(sizeParam);
   //   //
   //   // if (sizeParam.is_empty())
   //   // {
   //   //
   //   //    size = { 1920, 1080 };
   //   //
   //   // }
   //   //
   //   // opengl_create_offscreen_buffer(size);
   //   //
   //   // set_ok_flag();

   //}


   //void graphics::_create_memory_graphics(const ::i32_size& size)
   //{

   //   opengl_create_offscreen_buffer(size);

   //   // __UNREFERENCED_PARAMETER(size);
   //   //
   //   // create_compatible_graphics(nullptr);
   //   // //if (!create_compatible_graphics(nullptr))
   //   // //{
   //   //
   //   // //   return false;
   //   //
   //   // //}
   //   //
   //   // //return true;

   //}



   //void graphics::set_hint_window_output()
   //{

   //   if(!m_pgpucontextCompositor)
   //   {

   //      throw ::exception(error_wrong_state, "No GPU context available for setting hint window output.");

   //   }

   //   m_pgpucontextCompositor->m_pgpucontextCompositor->m_pgpurenderer->m_eoutputOnEndDraw = ::gpu::e_output_swap_chain;

   //}


   //void graphics::create_window_graphics(::windowing::window* pwindow)
   //{

   //   m_pwindow = pwindow;

   //   opengl_defer_create_window_context(pwindow);

   //   set_ok_flag();

   //}


   //void graphics::create_compatible_graphics(::draw2d::graphics * pdraw2dgraphics)
   //{

   //   opengl_create_offscreen_buffer({ 1920, 1080 });
   //   //opengl_create_offscreen_buffer(pdraw2dgraphics->m_pimage->size());

   //}


   void graphics::create_for_window_draw2d(::user::interaction * puserinteraction, const ::i32_size& sizeRawParameter)
   {

      if (!puserinteraction)
      {

         throw ::exception(error_bad_argument, "No user interaction available for OpenGL offscreen buffer creation.");

         return;

      }

      ::gpu::graphics::create_for_window_draw2d(puserinteraction, sizeRawParameter);

      //if (m_puserinteractionDraw2dGraphics == nullptr)
      //{

      //   m_puserinteractionDraw2dGraphics = dynamic_cast <::user::interaction*>(pacmeuserinteractionMain.m_p);

      //   if (m_puserinteractionDraw2dGraphics == nullptr)
      //   {

      //      informationf("No user interaction available for OpenGL offscreen buffer creation.");

      //      return;

      //   }

      //}

      auto rectangleOutput = puserinteraction->m_pacmewindowingwindow->get_window_rectangle();

      auto pointOutput = rectangleOutput.origin();

      auto size = rectangleOutput.size();

      auto sizeRaw = sizeRawParameter.maximum(size);

      if (m_pgraphicsbufferitem)
      {

         constructø(m_pgraphicsbufferitem->m_pimageBufferItem);

         m_pgraphicsbufferitem->m_pimageBufferItem->update_as_render_target(sizeRaw, puserinteraction->draw2d_domain(), this);

      }


      auto pgpuapproach = application()->get_gpu_approach();

      auto pgpudevice = pgpuapproach->get_gpu_device(m_puserinteractionTopic->draw2d_domain());

      auto pgpucontextNew = pgpudevice->allocate_gpu_context();

      pgpucontextNew->create_draw2d_gpu_context(
         // ::gpu::e_output_gpu_buffer
         pgpudevice, 
         m_puserinteractionTopic->draw2d_domain(),
         this,
         {},
         pointOutput,
         size, 
         sizeRaw);

      m_sizeScaleOutput = {1.0, -1.0};

      m_pointTranslateOutput = { 0.0, (double)rectangleOutput.height()};

      if (!pgpucontextNew)
      {

         return;

      }

      set_gpu_context(pgpucontextNew);

      auto pcontext = gpu_context();

///      ::gpu::context_lock contextlock(pcontext);

      pcontext->m_pgpucompositor = this;

      if (!pcontext->m_pgpurenderer)
      {

         pcontext->get_gpu_renderer();

      }

      bool bYSwap = m_papplication->m_gpu.m_bUseSwapChainWindow;

      //::opengl::resize(recta, bYSwap);

      set_ok_flag();

   }


   void graphics::_create_memory_graphics(const ::i32_size & size, ::draw2d::domain * pdraw2ddomain)
//   bool graphics::opengl_create_offscreen_buffer(const ::i32_size & size)
   {

      set_draw2d_domain(pdraw2ddomain);

      //if (!draw2d_opengl()->m_popenglcontext) {
      //   informationf("MS GDI - RegisterClass failed");
      //   informationf("last-error code: %d\n", GetLastError());
      //   return false;
      //}

      //if (m_puserinteractionDraw2dGraphics == nullptr)
      //{

      //   m_puserinteractionDraw2dGraphics = dynamic_cast <::user::interaction*>(pacmeuserinteractionMain.m_p);

      //   if (m_puserinteractionDraw2dGraphics == nullptr)
      //   {

      //      informationf("No user interaction available for OpenGL offscreen buffer creation.");

      //      return false;

      //   }

      //}

      auto pgpuapproach = application()->get_gpu_approach();

      //   ASSERT(m_puserinteractionDraw2dGraphics);

      auto pgpudevice = pgpuapproach->get_gpu_device(draw2d_domain());

      auto pgpucontextNew = pgpudevice->allocate_gpu_context();

      // The pbuffer context has no window attachment. Give it an offscreen
      // frame attachment so model buffers used while drawing the image cache
      // can use the same per-frame pool as window-backed graphics.
      construct_newø(pgpucontextNew->m_pgpuwindowattachmentOffscreen);
      pgpucontextNew->m_pgpuwindowattachmentOffscreen->initialize_offscreen_frame(pgpucontextNew);

      //::i32_rectangle rectanglePlacement(size);

      // A memory graphics target is an offscreen image and may have no
      // owning interaction. Its raw buffer is the requested image size.
      auto sizeRaw = size;

      pgpucontextNew->create_draw2d_gpu_context(
         //::gpu::e_output_gpu_buffer,
         pgpudevice,
         draw2d_domain(),
         this,
         {},
         {},
         size,
         sizeRaw);

      pgpucontextNew->m_pgpucompositor = this;  

      set_gpu_context(pgpucontextNew);

      m_sizeScaleOutput = { 1.0, -1.0 };

      m_pointTranslateOutput = { 0.0, (double)size.cy };

//      auto pgpucontext = gpu_context();

//      auto pgpurenderer = pgpucontext->get_gpu_renderer();

      //auto pgpucontext = pgpudevice->get_main_context();

      //if (!m_pgpucontextCompositor->m_pgpurenderer)
      //{

      //   auto pgpu = application()->get_gpu();

      //   ASSERT(m_puserinteractionDraw2dGraphics);

      //   auto pgpudevice = pgpu->get_device();

      //   ::cast < ::gpu_opengl::device_win32> pdeviceWin32 = pgpudevice;

      //   if (callbackOnImagePixels)
      //   {

      //      pgpucontext = pgpudevice->start_cpu_buffer_context(this, callbackOnImagePixels, rectanglePlacement);

      //   }
      //   else
      //   {

      //      pgpucontext = pgpudevice->start_gpu_output_context(this, ::gpu::e_output_gpu_buffer, rectanglePlacement);

      //   }

      //}

      //auto pcontext = gpu_context();

      //if (!pcontext)
      //{

      //   return false;
      //   //auto psystem = system();

      //   //auto pgpu = application()->get_gpu();

      //   //m_pgpucontextOpenGL = pgpu->create_context(this);

      //   //if (m_pgpucontextOpenGL)
      //   //{

      //   //   m_pgpucontextOpenGL->initialize(this);

      //   //}

      //}

      //if (defer_constructø(m_pgpucontextOpenGL))
      //{

      //if (!m_pgpucontextCompositor)
      //{

      //   m_pgpucontextCompositor = pgpudevice->create_draw2d_context(::gpu::e_output_gpu_buffer, size);

      //}

      //if (pgpucontext->m_eoutput == ::gpu::e_output_cpu_buffer)
      //{

      //   pgpucontext->create_cpu_buffer(rectanglePlacement.size());

      //}

      //}

      //LPCTSTR lpClassName = L"draw2d_opengl_offscreen_buffer_window";
      //LPCTSTR lpWindowName = L"draw2d_opengl_offscreen_buffer_window";
      ////unsigned int dwStyle = WS_CAPTION | WS_POPUPWINDOW; // | WS_VISIBLE
      //unsigned int dwExStyle = 0;
      //unsigned int dwStyle = WS_OVERLAPPEDWINDOW;
      //dwStyle |= WS_POPUP;
      ////dwStyle |= WS_VISIBLE;
      ////dwStyle |= WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
      //dwStyle &= ~WS_CAPTION;
      ////dwStyle = 0;
      //dwStyle &= ~WS_THICKFRAME;
      //dwStyle &= ~WS_BORDER;
      //int x = 0;
      //int y = 0;
      //int nWidth = size.cx;
      //int nHeight = size.cy;
      //HWND hWndParent = nullptr;
      //HMENU hMenu = nullptr;
      /////HINSTANCE hInstance = psystem->m_hinstance;
      //LPVOID lpParam = nullptr;

      ////HWND window = CreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y,  nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
      //HWND window = CreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, nullptr, lpParam);

      //if (window == nullptr) 
      //{
      //   informationf("MS GDI - CreateWindow failed");
      //   informationf("last-error code: %d\n", GetLastError());
      //   return false;
      //}

      //// create WGL context, make current

      //PIXELFORMATDESCRIPTOR pixformat;
      //int chosenformat;
      //HDC hdc = GetDC(window);
      //if (hdc == nullptr)
      //{
      //   informationf("MS GDI - GetDC failed");
      //   informationf("last-error code: %d\n", GetLastError());
      //   return false;
      //}

      //ZeroMemory(&pixformat, sizeof(pixformat));
      //pixformat.nSize = sizeof(pixformat);
      //pixformat.nVersion = 1;
      //pixformat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
      //pixformat.iPixelType = PFD_TYPE_RGBA;
      //pixformat.cColorBits = 24;
      //pixformat.cAlphaBits = 8;
      //pixformat.cDepthBits = 24;
      //pixformat.cStencilBits = 8;

      //chosenformat = ChoosePixelFormat(hdc, &pixformat);
      //if (chosenformat == 0) 
      //{
      //   informationf("MS GDI - ChoosePixelFormat failed");
      //   informationf("last-error code: %d\n", GetLastError());
      //   return false;
      //}

      //bool spfok = SetPixelFormat(hdc, chosenformat, &pixformat);
      //if (!spfok) 
      //{
      //   informationf("MS GDI - SetPixelFormat failed");
      //   informationf("last-error code: %d\n", GetLastError());
      //   return false;
      //}

      //HGLRC hglrcTime = wglCreateContext(hdc);
      //if (hglrcTime == nullptr)
      //{
      //   informationf("MS WGL - wglCreateContext failed");
      //   informationf("last-error code: %d\n", GetLastError());
      //   ReleaseDC(m_hwnd, m_hdc);
      //   return false;
      //}

      //bool okMakeCurrent = wglMakeCurrent(hdc, hglrcTime);
      //if (!okMakeCurrent)
      //{
      //   informationf("MS WGL - wglMakeCurrent failed");
      //   informationf("last-error code: %d\n", GetLastError());
      //   return false;
      //}
      ////glfwInit();
      //// ... <snip> ... setup a window and a context
      //
      //auto wglCurrentContext = wglGetCurrentContext();

      //// Load all OpenGL functions using the glfw loader function
      //// If you use SDL you can use: https://wiki.libsdl.org/SDL_GL_GetProcAddress
      ////if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      ////   std::cout << "Failed to initialize OpenGL context" << std::endl;
      ////   return -1;
      ////}
      //if (!gladLoadWGL(hdc))
      //{
      //   // Problem: glewInit failed, something is seriously wrong.
      //   informationf("gladLoadWGL failed");
      //   //return false;
      //   //throw resource_exception();

      //   return false;

      //}
      //int attribs[] =
      //{
      //   WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
      //   WGL_CONTEXT_MINOR_VERSION_ARB, 1,
      //   WGL_CONTEXT_FLAGS_ARB, 0,
      //   WGL_CONTEXT_PROFILE_MASK_ARB,
      //   WGL_CONTEXT_COREPROFILE_BIT_ARB, 0
      //};

      ////PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
      ////wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

      //auto hglrc =  wglCreateContextAttribsARB(hdc, 0, attribs);
      //wglMakeCurrent(nullptr, nullptr);
      //wglDeleteContext(hglrcTime);
      //   wglMakeCurrent(hdc, m_hglrc);
      ////draw2d_opengl()->defer_initialize_glew();
      //
      ////draw2d_opengl()->defer_initialize_glew();


      //m_hwnd = window;
      //m_hdc = hdc;
      //m_hglrc = hglrc;
      //m_size = size;

      bool bYSwap = m_papplication->m_gpu.m_bUseSwapChainWindow;

      ::opengl::resize(size, bYSwap);

      //return true;

   }


   void graphics::create_bitmap_graphics(::draw2d::bitmap * pdraw2dbitmap, ::draw2d::domain * pdraw2ddomain)
   {

      throw ::interface_only();

   }


   void graphics::begin_draw(bool bExternalRendering, ::user::interaction * puserinteraction, const ::i32_rectangle & rectangleFrame, ::image::image * pimageTarget)
   {

      ::gpu::graphics::begin_draw(bExternalRendering, puserinteraction, rectangleFrame, pimageTarget);

      ::gpu::context_lock contextlock(m_pgpucontextOwned);

      auto pcommandbuffer = m_pgpucontextOwned->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_layer());

      auto rectangleOutput = rectangleFrame;

      rectangleOutput.offset(-rectangleOutput.origin());

      pcommandbuffer->set_viewport(rectangleOutput, m_pgpucontextOwned->m_sizeRaw);

      pcommandbuffer->set_scissor(rectangleOutput, m_pgpucontextOwned->m_sizeRaw);

   }


   void graphics::on_acquire_memory_graphics(
      bool bExternalRendering,
      ::image::image * pimage,
      const ::i32_size & size,
      ::draw2d::domain * pdraw2ddomain)
   {

      ::gpu::texture * pgputextureActiveLayer = nullptr;

      if (pimage)
      {

         ::gpu::context_lock contextlock(gpu_context());

         auto pgpucommandbuffer = ::gpu::current_command_buffer();

         if (pgpucommandbuffer && pgpucommandbuffer->m_pgpurendertarget)
         {

            auto pgputexturesiteActiveLayer =
               pgpucommandbuffer->m_pgpurendertarget->current_texture(
                  ::gpu::current_layer(),
                  false);

            if (pgputexturesiteActiveLayer)
            {

               pgputextureActiveLayer = pgputexturesiteActiveLayer->gpu_texture();

            }

         }

         glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &m_iDrawFramebufferBeforeImageTarget);
         glGetIntegerv(GL_DRAW_BUFFER, &m_iDrawBufferBeforeImageTarget);
         glGetIntegerv(GL_VIEWPORT, m_iViewportBeforeImageTarget);
         glGetIntegerv(GL_SCISSOR_BOX, m_iScissorBoxBeforeImageTarget);
         m_bScissorTestBeforeImageTarget = glIsEnabled(GL_SCISSOR_TEST) == GL_TRUE;
         m_bImageTargetStateSaved = true;

      }

      ::gpu::graphics::on_acquire_memory_graphics(
         bExternalRendering,
         pimage,
         size,
         pdraw2ddomain);

      if (pimage)
      {

         ::gpu::context_lock contextlock(gpu_context());

         ::gpu::texture * pgputextureImageTarget = m_pgputexturesiteTarget
            ? m_pgputexturesiteTarget->gpu_texture()
            : nullptr;

         auto bNestedImageTarget = !pgputextureActiveLayer
            || pgputextureImageTarget != pgputextureActiveLayer;

         if (bNestedImageTarget)
         {

            auto sizeRaw = pimage->raw_size();

            glViewport(0, 0, sizeRaw.cx, sizeRaw.cy);
            ::opengl::check_error("");
            glEnable(GL_SCISSOR_TEST);
            ::opengl::check_error("");
            glScissor(0, 0, sizeRaw.cx, sizeRaw.cy);
            ::opengl::check_error("");

         }
         else
         {

            // The window UI lease is backed by the active layer texture itself.
            // Its framebuffer must remain current through layer finalization.
            m_bImageTargetStateSaved = false;

         }

      }

   }


   void graphics::on_release_memory_graphics()
   {

      if (m_bImageTargetStateSaved)
      {

         ::gpu::context_lock contextlock(gpu_context());

         gpu_context()->defer_unbind_shader(m_pgpucommandbufferGpuGraphics);

         if (m_pgputexturesiteTarget)
         {

            auto pgputextureTarget = m_pgputexturesiteTarget->gpu_texture();

            if (pgputextureTarget)
            {

               // The image can be sampled immediately by another shared OpenGL
               // context, so publish completion before restoring the UI target.
               pgputextureTarget->defer_fence();

            }

         }

         glBindFramebuffer(
            GL_DRAW_FRAMEBUFFER,
            (GLuint)m_iDrawFramebufferBeforeImageTarget);
         ::opengl::check_error("");
         glDrawBuffer((GLenum)m_iDrawBufferBeforeImageTarget);
         ::opengl::check_error("");
         glViewport(
            m_iViewportBeforeImageTarget[0],
            m_iViewportBeforeImageTarget[1],
            m_iViewportBeforeImageTarget[2],
            m_iViewportBeforeImageTarget[3]);
         ::opengl::check_error("");
         glScissor(
            m_iScissorBoxBeforeImageTarget[0],
            m_iScissorBoxBeforeImageTarget[1],
            m_iScissorBoxBeforeImageTarget[2],
            m_iScissorBoxBeforeImageTarget[3]);
         ::opengl::check_error("");

         if (!m_bScissorTestBeforeImageTarget)
         {

            glDisable(GL_SCISSOR_TEST);
            ::opengl::check_error("");

         }

         m_bImageTargetStateSaved = false;

      }

      ::gpu::graphics::on_release_memory_graphics();

   }


   void graphics::end_draw()
   {

      ::gpu::graphics::end_draw();

   }


   //bool graphics::opengl_delete_offscreen_buffer()
   //{

   //   //if (m_hglrc == NULL && m_hdc == NULL && m_hwnd == NULL)
   //   //{

   //   //   return true;

   //   //}

   //   //wglMakeCurrent(nullptr, nullptr);
   //   //wglDeleteContext(m_hglrc);
   //   //::ReleaseDC(m_hwnd, m_hdc);
   //   //::DestroyWindow(m_hwnd);
   //   m_size.set(0, 0);
   //   //m_hglrc = NULL;
   //   //m_hwnd = NULL;
   //   //m_hdc = NULL;
   //   return true;

   //}


   //bool graphics::opengl_defer_create_window_context(::windowing::window* pwindow)
   //{

   //   //if (!m_pgpucontextCompositor)
   //   //{

   //   //   return false;

   //   //}

   //   //if (!pgpucontext)
   //   //{

   //   //   auto pgpu = application()->get_gpu();

   //   //   auto pgpudevice = pgpu->get_device();

   //   //   pgpucontext = pgpudevice->start_swap_chain_context(this, pwindow);

   //   //}

   //   auto pcontext = gpu_context();

   //   pcontext->defer_create_window_context(pwindow);

   //   //      ::opengl::resize(size);

   //   return true;

   //}



   int graphics::ExcludeUpdateRgn(::user::interaction_base* pwindow)
   {
      // ASSERT(m_hdc != nullptr);
      //throw ::interface_only();
      ////return ::ExcludeUpdateRgn(m_hdc, WIN_WINDOW(pwindow)->get_handle());
      return 0;
   }

   //double graphics::GetDeviceCaps(double nIndex) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetDeviceCaps(m_hdc, nIndex);
   //   return 0;
   //}

   i32_point graphics::GetBrushOrg() const
   {
      // ASSERT(m_hdc != nullptr);
      ::i32_point point;
      //VERIFY(::GetBrushOrgEx(m_hdc, &point));
      return point;
   }

   i32_point graphics::SetBrushOrg(int x, int y)
   {
      // ASSERT(m_hdc != nullptr);
      ::i32_point point;
      //VERIFY(::SetBrushOrgEx(m_hdc, x, y, &point));
      return point;
   }

   i32_point graphics::SetBrushOrg(const ::i32_point& point)
   {
      // ASSERT(m_hdc != nullptr);
      //VERIFY(::SetBrushOrgEx(m_hdc, point.x, point.y, &point));
      return point;
   }


   // int graphics::EnumObjects(int nObjectType, int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
   // {
   //    // ASSERT(m_hdc != nullptr);
   //    //return ::EnumObjects(m_hdc, nObjectType, (GOBJENUMPROC)lpfn, lpData);
   //    return 0;
   // }

   ::draw2d::bitmap* graphics::SelectObject(::draw2d::bitmap* pdraw2dbitmap)
   {

      if (m_pdraw2dbitmap == pdraw2dbitmap)
      {

         return m_pdraw2dbitmap;

      }

      //opengl_delete_offscreen_buffer();

      //if (!opengl_create_offscreen_buffer(pdraw2dbitmap->get_size()))
      //{

      //   return NULL;

      //}

      bool bYSwap = m_papplication->m_gpu.m_bUseSwapChainWindow;

      ::opengl::resize(pdraw2dbitmap->size(), bYSwap);

      //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      m_pdraw2dbitmap = pdraw2dbitmap;

      return m_pdraw2dbitmap;

   }


   ::draw2d::object* graphics::SelectObject(::draw2d::object* pObject)
   {
      /*      // ASSERT(m_hdc != nullptr);
         if(pObject == nullptr)
            return nullptr;
         return SelectGdiObject(get_app(), m_hdc, pObject->get_os_data()); */
      return nullptr;
   }

   //HGDIOBJ graphics::SelectObject(HGDIOBJ hObject) // Safe for nullptr handles
   //{

   //   unsigned int uType = GetObjectType(hObject);

   //   if(uiType == OBJ_BITMAP)
   //   {

   //      HBITMAP hbitmap = (HBITMAP) hObject;

   //      if(m_pdraw2dbitmap.is_null())
   //         m_pdraw2dbitmap.create();

   //      if(m_pdraw2dbitmap.is_null())
   //         return nullptr;

   //      //(dynamic_cast < ::draw2d_opengl::bitmap * > (m_pdraw2dbitmap.m_p))->m_pdraw2dbitmap = ___new plusplus::Bitmap (hbitmap, nullptr);

   //      //if(m_pgraphics != nullptr)
   //      //{

   //      //   try
   //      //   {

   //      //      delete m_pgraphics;

   //      //   }
   //      //   catch(...)
   //      //   {

   //      //      informationf("graphics::SelectObject(HGDIOBJ) OBJ_BITMAP : Failed to delete plusplus::Graphics");

   //      //   }

   //      //   m_pgraphics = nullptr;

   //      //}

   //      //m_pgraphics = allocateø< plusplus::Graphics((plusplus::Bitmap *) m_pdraw2dbitmap->get_os_data >());

   //      //m_pgraphics->SetPageUnit(plusplus::UnitPixel);

   //      //set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

   //      return hbitmap;

   //   }

   //   //*ASSERT(m_hdc == m_hdc); // ASSERT a simple graphics object
   //   //return (hObject != nullptr) ? ::SelectObject(m_hdc, hObject) : nullptr; */
   //   return nullptr;
   //}


   color32_t graphics::GetNearestColor(color32_t crColor) const
   {

      //return ::GetNearestColor(m_hdc, crColor);
      return color::transparent;

   }


   unsigned int graphics::RealizePalette()
   {
      //return ::RealizePalette(m_hdc);
      return 0;
   }

   void graphics::UpdateColors()
   {
      //::UpdateColors(m_hdc);
   }


   int graphics::GetPolyFillMode() const
   {
      //return ::GetPolyFillMode(m_hdc);
      return 0;
   }


   int graphics::GetROP2() const
   {
      //return ::GetROP2(m_hdc);
      return 0;
   }


   int graphics::GetStretchBltMode() const
   {
      //return ::GetStretchBltMode(m_hdc);
      return 0;
   }


   int graphics::GetMapMode() const
   {
      //return ::GetMapMode(m_hdc);
      return 0;
   }


   int graphics::GetGraphicsMode() const
   {
      //return ::GetGraphicsMode(m_hdc);
      return 0;
   }


   // bool graphics::GetWorldTransform(XFORM* pXform) const
   // {
   //
   //
   //
   //    //m_pgraphics->GetTransform(((graphics *)this)->m_pm);
   //
   //    //plusplus::REAL ::f64_rectangle[6];
   //
   //    //m_pm->GetElements(rectangle);
   //
   //    //pXform->eM11 = ::f64_rectangle[0];
   //    //pXform->eM12 = ::f64_rectangle[1];
   //    //pXform->eM21 = ::f64_rectangle[2];
   //    //pXform->eM22 = ::f64_rectangle[3];
   //
   //    //pXform->eDx = ::f64_rectangle[4];
   //    //pXform->eDy = ::f64_rectangle[5];
   //
   //
   //    return true;
   //
   // }

   i32_size graphics::get_context_extents() const
   {
      ::i32_size size;
      //::Get_wiewportExtEx(m_hdc, &size);
      return size;
   }

   i32_point graphics::GetWindowOrg() const
   {
      ::i32_point point;
      //::GetWindowOrgEx(m_hdc, &point);
      return point;
   }

   i32_size graphics::GetWindowExt() const
   {
      ::i32_size size;
      //::GetWindowExtEx(m_hdc, &size);
      return size;
   }

   //// non-virtual helpers calling virtual mapping functions
   //i32_point graphics::set_origin(const ::i32_point& point)
   //{

   //   return set_origin(point.x, point.y);

   //}

   //i32_size graphics::set_context_extents(const ::i32_size & size)
   //{
   //   return set_context_extents(size.cx, size.cy);
   //}

   i32_point graphics::SetWindowOrg(const ::i32_point& point)
   {
      return SetWindowOrg(point.x, point.y);
   }

   i32_size graphics::set_window_ext(const ::i32_size& size)
   {
      return set_window_ext(size.cx, size.cy);
   }

   void graphics::DPtoLP(::f64_point* lpPoints, ::collection::count nCount)
   {
      //::DPtoLP(m_hdc, lpPoints, (int) nCount);
   }

   void graphics::DPtoLP(::f64_rectangle* prectangle)
   {
      //::DPtoLP(m_hdc, (::f64_point *)rectangle, 2);
   }

   void graphics::LPtoDP(::f64_point* lpPoints, ::collection::count nCount)
   {
      //::LPtoDP(m_hdc, lpPoints, (int)  nCount);
   }

   void graphics::LPtoDP(::f64_rectangle* prectangle)
   {
      //::LPtoDP(m_hdc, (::f64_point *)rectangle, 2);
   }

   bool graphics::FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush)
   {

      //return ::FillRgn(m_hdc, (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data()) != false;
      return false;

   }


   bool graphics::FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, int nWidth, int nHeight)
   {

      //return ::FrameRgn(m_hdc, (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data(), nWidth, nHeight) != false;
      return false;

   }

   bool graphics::InvertRgn(::draw2d::region* pRgn)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::InvertRgn(m_hdc, (HRGN)pRgn->get_os_data()) != false;
      return false;

   }

   //bool graphics::PaintRgn(::draw2d::region* pRgn)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //return ::PaintRgn(m_hdc, (HRGN)pRgn->get_os_data())  != false;

   //   return ::draw2d::graphics::PaintRgn(pRgn);

   //}


   bool graphics::PtVisible(int x, int y) const
   {

      // ASSERT(m_hdc != nullptr);

      //return ::PtVisible(m_hdc, x, y) != false;
      //return ::draw2d::graphics::PtVisible(x, y);

      return true;

   }


   bool graphics::PtVisible(const ::i32_point& point) const
   {

      // ASSERT(m_hdc != nullptr);   // call virtual
      return PtVisible(point.x, point.y);

   }


   //bool graphics::rectVisible(const ::f64_rectangle & ::f64_rectangle) const
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //return ::rectVisible(m_hdc, &rectangle) != false;
   //   return false;

   //}


   //i32_point graphics::GetCurrentPosition() const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //::i32_point point(m_po;
   //   //VERIFY(::GetCurrentPositionEx(m_hdc, &point));
   //   //return point;
   //   return ::draw2d::graphics::G;
   //}

   void graphics::polyline(const ::f64_point* lpPoints, ::collection::count nCount)
   {

      if (nCount <= 0)
      {

         //return true;

         return;

      }

      //bool bOk1 = false;

      //plusplus::Point * ppoints = ___new plusplus::Point[nCount];

      //try
      //{

      //   for(double i = 0; i < nCount; i++)
      //   {
      //      ppoints[i].X = lpPoints[i].x;
      //      ppoints[i].Y = lpPoints[i].y;
      //   }

      //   bOk1 = m_pgraphics->DrawLines(gl2d_pen(),ppoints,(::double) nCount) == plusplus::Status::Ok;

      //}
      //catch(...)
      //{
      //}

      //try
      //{
      //   delete ppoints;
      //}
      //catch(...)
      //{
      //}


      //return bOk1;
   }


   void graphics::arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   {

      //auto pmathematics = mathematics();

      double centerx = (x2 + x1) / 2.0;
      double centery = (y2 + y1) / 2.0;

      double start = atan2(y3 - centery, x3 - centerx) * 180.0 / π;
      double end = atan2(y4 - centery, x4 - centerx) * 180.0 / π;
      double sweep = fabs(end - start);

      /*if(GetArcDirection() == AD_COUNTERCLOCKWISE)
      {
         sweep = -sweep;
      }
      */

      return arc(x1, y1, x2 - x1, y2 - y1, start, sweep);

   }


   //void graphics::arc(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4)
   //{

   //   double centerx    = (x2 + x1) / 2.0;
   //   double centery    = (y2 + y1) / 2.0;

   //   double start      = atan2(y3 - centery,x3 - centerx) * 180.0 / π;
   //   double end        = atan2(y4 - centery,x4 - centerx) * 180.0 / π;
   //   double sweep      = fabs(end - start);

   //   /*if(GetArcDirection() == AD_COUNTERCLOCKWISE)
   //   {
   //      sweep = -sweep;
   //   }
   //   */

   //   return Arc(x1,y1, x2-x1, y2-y1, start, sweep);

   //}


   void graphics::arc(double x1, double y1, double w, double h, double start, double extends)
   {

      //::plusplus::f64_rectangle ::f64_rectangle(x1,y1,w,h);

      //return m_pgraphics->DrawArc(gl2d_pen(),rectangle,(plusplus::REAL) start,(plusplus::REAL) extends) == plusplus::Status::Ok;

      //return true;

   }


   //void graphics::arc(double x1,double y1,double w,double h,double start,double extends)
   //{

   //   //::plusplus::rectF float_rectangle((plusplus::REAL) x1,(plusplus::REAL) y1,(plusplus::REAL) w,(plusplus::REAL) h);

   //   //return m_pgraphics->DrawArc(gl2d_pen(),float_rectangle,(plusplus::REAL) start,(plusplus::REAL) extends) == plusplus::Status::Ok;

   //   return true;

   //}

   //void vertex2f(const ::f64_rectangle& rectangle, float fZ)
   //{

   //   glVertex3f((GLfloat)rectangle.left, (GLfloat)rectangle.top, fZ);
   //   glVertex3f((GLfloat)rectangle.right, (GLfloat)rectangle.top, fZ);
   //   glVertex3f((GLfloat)rectangle.right, (GLfloat)rectangle.bottom, fZ);
   //   glVertex3f((GLfloat)rectangle.left, (GLfloat)rectangle.bottom, fZ);

   //}


   void graphics::fill_rectangle(const ::f64_rectangle& rectangle, const ::color::color& color)
   {

      ::gpu::graphics::fill_rectangle(rectangle, color);



   //   auto pcontext = gpu_context();

   //   ::cast < ::gpu::renderer >prenderer = pcontext->m_pgpurenderer;

   //   ::cast < ::gpu::context > pgpucontext = prenderer->m_pgpucontext;

   //   ::cast < ::gpu::device > pgpudevice = pgpucontext->m_pgpudevice;

   //   ::gpu::context_lock contextlock(pcontext);

   //   //// Rectangle descriptors
   //   //if (!m_psetdescriptorlayoutRectangle)
   //   //{

   //   //   int iFrameCount = prenderer->get_frame_count();

   //   //   m_psetdescriptorlayoutRectangle = ::gpu_vulkan::descriptor_set_layout::Builder(m_pgpucontextCompositor)
   //   //      .addBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
   //   //      .build();

   //   //   auto pdescriptorpoolbuilder = allocateø::gpu_vulkan::descriptor_pool::Builder();

   //   //   pdescriptorpoolbuilder->initialize_builder(m_pgpucontextCompositor);
   //   //   pdescriptorpoolbuilder->setMaxSets(iFrameCount * 10);
   //   //   pdescriptorpoolbuilder->addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, iFrameCount * 10);

   //   //   m_psetdescriptorlayoutRectangle = pdescriptorpoolbuilder->build();

   //   //}

   //   //// Rectangle descriptors
   //   //if (!m_psetdescriptorlayoutRectangle)
   //   //{

   //   //   int iFrameCount = prenderer->get_frame_count();

   //   //   m_psetdescriptorlayoutRectangle = ::gpu_vulkan::descriptor_set_layout::Builder(m_pgpucontextCompositor)
   //   //      .addBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
   //   //      .build();

   //   //   auto pdescriptorpoolbuilder = allocateø::gpu_vulkan::descriptor_pool::Builder();

   //   //   pdescriptorpoolbuilder->initialize_builder(m_pgpucontextCompositor);
   //   //   pdescriptorpoolbuilder->setMaxSets(iFrameCount * 10);
   //   //   pdescriptorpoolbuilder->addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, iFrameCount * 10);

   //   //   m_psetdescriptorlayoutRectangle = pdescriptorpoolbuilder->build();

   //   //}

   //   ::gpu::shader* pshader = nullptr;

   //   if (m_ealphamode == ::draw2d::e_alpha_mode_set)
   //   {
   //      if (!m_pshaderSourceRectangle)
   //      {

   //         //auto pshadervertexinput = allocateø::gpu_vulkan::shader_vertex_input();

   //         //pshadervertexinput->m_bindings.add(
   //         //   {
   //         //      .binding = 0,
   //         //      .stride = sizeof(RectangleVertex),
   //         //      .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
   //         //   });

   //         //pshadervertexinput->m_attribs.add({ .location = 0, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(RectangleVertex, pos) });
   //         //pshadervertexinput->m_attribs.add({ .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32A32_SFLOAT, .offset = offsetof(RectangleVertex, color) });


   //         auto pshaderRectangle = create_newø<::gpu::shader>();

   //         m_pshaderSourceRectangle = pshaderRectangle;
   //         //m_pshaderBlendRectangle->m_bDisableDepthTest = true;
   //         m_pshaderSourceRectangle->m_bDisableDepthTest = true;
   //         //m_pshaderRectangle->m_iColorAttachmentCount = 2;
   //         m_pshaderSourceRectangle->m_bEnableBlend = false;
   //         //m_pshaderRectangle->m_bAccumulationEnable = true;

   //         auto pcontext = gpu_context();

   //         //::cast < ::gpu_vulkan::device > pgpudevice = pgpucontext->m_pgpudevice;
   //         pshaderRectangle->initialize_shader_with_block(
   //            pcontext->m_pgpurenderer,
   //            as_memory_block(proto_vert),
   //            //as_memory_block(g_uaAccumulationFragmentShader),
   //            as_memory_block(proto_frag),
   //            {},
   //            {},
   //            {},
   //            pcontext->input_layout<::graphics3d::sequence2_color>());

   //      }
   //      pshader = m_pshaderSourceRectangle;

   //   }
   //   else
   //   {

   //      if (!m_pshaderBlendRectangle)
   //      {

   //         //auto pshadervertexinput = allocateø::gpu_vulkan::shader_vertex_input();

   //         //pshadervertexinput->m_bindings.add(
   //         //   {
   //         //      .binding = 0,
   //         //      .stride = sizeof(RectangleVertex),
   //         //      .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
   //         //   });

   //         //pshadervertexinput->m_attribs.add({ .location = 0, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(RectangleVertex, pos) });
   //         //pshadervertexinput->m_attribs.add({ .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32A32_SFLOAT, .offset = offsetof(RectangleVertex, color) });

   //         auto pshaderRectangle = create_newø<::gpu::shader>();

   //         m_pshaderBlendRectangle = pshaderRectangle;
   //         //m_pshaderBlendRectangle->m_bDisableDepthTest = true;
   //         m_pshaderBlendRectangle->m_bDisableDepthTest = true;
   //         //m_pshaderRectangle->m_iColorAttachmentCount = 2;
   //         m_pshaderBlendRectangle->m_bEnableBlend = true;
   //         //m_pshaderRectangle->m_bAccumulationEnable = true;

   //         auto pcontext = gpu_context();

   //         ::cast < ::gpu::device > pgpudevice = pgpucontext->m_pgpudevice;
   //         pshaderRectangle->initialize_shader_with_block(
   //            pcontext->m_pgpurenderer,
   //            as_memory_block(proto_vert),
   //            //as_memory_block(g_uaAccumulationFragmentShader),
   //            as_memory_block(proto_frag),
   //            { },
   //            {},
   //            {},
   //            pcontext->input_layout<::graphics3d::sequence2_color>());

   //      }

   //      pshader = m_pshaderBlendRectangle;

   //   }

   //   //auto pcontext = gpu_context();

   //   //::cast < ::gpu_vulkan::context > pcontext = m_pgpucontextCompositor;

   //   auto pmodelbufferRectangle = m_poolmodelbufferRectangle.get();

   //   if (pmodelbufferRectangle->is_new())
   //   {

   //      pmodelbufferRectangle->sequence2_color_create_rectangle(pcontext);

   //   }

   //   //   auto & pmodelbuffer = m_pmodelbufferRectangle;

   //   //if (!pmodelbuffer)
   //   //{

   //   //   

   //   //   //   pmodel->m_vertexBuffer = createQuadVertexBuffer(
   //   //   //      pgpucontext->logicalDevice(),
   //   //   //      pgpucontext->m_pgpudevice->m_pphysicaldevice->m_physicaldevice,
   //   //   //      &pmodel->m_vertexMemory);

   //   //   //   pmodel->m_indexBuffer = nullptr;
   //   //   //   pmodel->m_indexMemory = nullptr;

   //   //   //}


   //   //}

   //   f64_point points[4] = {
   //{rectangle.top_left()},
   //{rectangle.top_right()},
   //{rectangle.bottom_right()},
   //{rectangle.bottom_left()}
   //   };

   //   f64_point quad[4];

   //   quad[0] = points[0];
   //   m_m1.transform(quad[0]);
   //   quad[1] = points[1];
   //   m_m1.transform(quad[1]);
   //   quad[2] = points[2];
   //   m_m1.transform(quad[2]);
   //   quad[3] = points[3];
   //   m_m1.transform(quad[3]);

   //   //pmodelbuffer->sequence3_color_set_rectangle();
   //   //pgpucontext = pgpudevice->get_main_context();
   //   //editQuadVertexBuffer(
   //   //   pgpucontext->logicalDevice(),
   //   //   pmodel->m_vertexMemory,
   //   //   quad, color, pgpucontext->size());

   //   pmodelbufferRectangle->sequence2_color_set_rectangle(
   //      quad,
   //      color,
   //      pgpucontext->size());


   //   pshader->bind();

   //   //vkCmdBeginRenderPass(cmd, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
   //   auto pcommandbuffer = prenderer->getCurrentCommandBuffer2(::gpu::current_layer());
   //   //VkDeviceSize offset = 0;
   //   ///vkCmdBindPipeline(pcommandbuffer->m_vkcommandbuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
   //   //vkCmdBindVertexBuffers(pcommandbuffer->m_vkcommandbuffer, 0, 1, &pmodelbuffer->m_vertexBuffer, &offset);

   //   pmodelbufferRectangle->bind(pcommandbuffer);

   //   pmodelbufferRectangle->draw(pcommandbuffer);

   //   //vkCmdDraw(pcommandbuffer->m_vkcommandbuffer, 6, 1, 0, 0); // 6 vertexes for two triangles
   //   //vkCmdEndRenderPass(cmd);


   //   pshader->unbind();
   //   //vkvg_rectangle(m_pdc, rectangle.left, rectangle.top, rectangle.right - rectangle.left,
   //     // rectangle.bottom - rectangle.top);

   //   //m_particleaResetOnTopFrameEnd.add(pmodelbufferRectangle);

   //   //push_on_end_top_frame(m_modelbufferaRectangle, pmodelbufferRectangle);

   //   //g_z -= 0.0001;


   }

   void graphics::fill_rectangle_2025_06(const ::f64_rectangle& rectangle, ::draw2d::brush* pdraw2dbrush)
   {

      auto pcontext = gpu_context();

      ::gpu::context_lock contextlock(pcontext);
      //thread_select();

      ::opengl::color(pdraw2dbrush->m_color);

      ::f64_polygon polygon;

      polygon = rectangle;

      for (auto& p : polygon)
      {
       
         m_m1.transform(p);

      }

      //glBegin(GL_QUADS);

      //::opengl::vertex2f(polygon, m_z);

      //glEnd();
      //::opengl::check_error("");

      //return false;

   }


   void graphics::fill_rectangle(const ::f64_rectangle& rectangle, ::draw2d::brush* pdraw2dbrush)
   {

      ::gpu::graphics::fill_rectangle(rectangle, pdraw2dbrush);

   }


   void graphics::frame_rectangle(const ::f64_rectangle& rectangleParam, ::draw2d::brush* pBrush)
   {

      //// ASSERT(m_hdc != nullptr);

      //::FrameRect(m_hdc,&rectangleParam,(HBRUSH)pBrush->get_os_data());

   }


   void graphics::invert_rectangle(const ::f64_rectangle& rectangleParam)
   {

      // ASSERT(m_hdc != nullptr);

      //::InvertRect(m_hdc,&rectangleParam);

   }


   //bool graphics::DrawIcon(double x, double y, ::image::icon * picon)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   if(picon == nullptr)
   //      return false;

   //   //return ::DrawIcon(m_hdc, x, y, (HICON) picon->m_picon) != false;

   //   return false;

   //}

   //bool graphics::DrawIcon(const ::i32_point & point, ::image::icon * picon)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   if(picon == nullptr)
   //      return false;

   //   //return ::DrawIcon(m_hdc, point.x, point.y, (HICON) picon->m_picon) != false;

   //   return false;

   //}

   //bool graphics::DrawIcon(double x, double y, ::image::icon * picon, double cx, double cy, unsigned int istepIfAniCur, HBRUSH hbrFlickerFreeDraw, unsigned int diFlags)
   //{

   //   //try
   //   //{

   //   //   if(picon == nullptr)
   //   //      return false;

   //   //   if(m_pgraphics == nullptr)
   //   //      return false;

   //   //   bool bOk = false;

   //   //   BITMAPINFO info;
   //   //   color32_t * pimage32;

   //   //   ZeroMemory(&info, sizeof (BITMAPINFO));

   //   //   info.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
   //   //   info.bmiHeader.biWidth         = cx;
   //   //   info.bmiHeader.biHeight        = - cy;
   //   //   info.bmiHeader.biPlanes        = 1;
   //   //   info.bmiHeader.biBitCount      = 32;
   //   //   info.bmiHeader.biCompression   = BI_RGB;
   //   //   info.bmiHeader.biSizeImage     = cx * cy * 4;

   //   //   HBITMAP hbitmap = ::CreateDIBSection(nullptr, &info, DIB_RGB_COLORS, (void **) &pimage32, nullptr, 0);

   //   //   HDC hdc = ::CreateCompatibleDC(nullptr);

   //   //   HBITMAP hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);

   //   //   ICONINFO ii;
   //   //   BITMAPINFO biC;
   //   //   BITMAPINFO biM;

   //   //   zero(biC);
   //   //   zero(biM);



   //   //   if(::GetIconInfo((HICON)picon->m_picon,&ii))
   //   //   {

   //   //      ::GetObject(ii.hbmColor,sizeof(biC),(LPVOID)&biC);

   //   //      ::GetObject(ii.hbmMask,sizeof(biM),(LPVOID)&biM);

   //   //   }



   //   //   if(!::DrawIconEx(hdc,0,0,(HICON)picon->m_picon,cx,cy,istepIfAniCur,nullptr,DI_IMAGE | DI_MASK))
   //   //   {

   //   //      informationf("nok");
   //   //   }
   //   //   else
   //   //   {

   //   //      bool bAllZeroAlpha = true;
   //   //      bool bTheresunsigned int = false;

   //   //      int area = cx * cy;

   //   //      color32_t * pc = pimage32;
   //   //      unsigned char * pA = &((unsigned char *) pimage32)[3];

   //   //      for(int i = 0; i < area; i++)
   //   //      {
   //   //         if(*pc != 0)
   //   //         {
   //   //            bTheresunsigned int = true;
   //   //         }
   //   //         if(*pA != 0)
   //   //         {
   //   //            bAllZeroAlpha = false;
   //   //            break;
   //   //         }
   //   //         pc++;
   //   //         pA +=4;
   //   //      }

   //   //      if(bAllZeroAlpha && bTheresunsigned int)
   //   //      {

   //   //         pc = pimage32;
   //   //         pA = &((unsigned char *)pimage32)[3];

   //   //         for(int i = 0; i < area; i++)
   //   //         {
   //   //            if(*pc != 0)
   //   //            {
   //   //               *pA = 255;
   //   //            }
   //   //            pc++;
   //   //            pA +=4;
   //   //         }
   //   //      }

   //   //      ::SelectObject(hdc, hbitmapOld);

   //   //      try
   //   //      {

   //   //         plusplus::Bitmap b(cx, cy, cx * 4 , PixelFormat32bppARGB, (unsigned char *) pimage32);

   //   //         bOk = m_pgraphics->DrawImage(&b, x, y, 0, 0, cx, cy, plusplus::UnitPixel) == plusplus::Ok;

   //   //      }
   //   //      catch(...)
   //   //      {
   //   //      }

   //   //   }

   //   //   ::DeleteDC(hdc);

   //   //   ::DeleteObject(hbitmap);

   //   //   return bOk;

   //   //}
   //   //catch(...)
   //   //{
   //   //   return false;
   //   //}

   //   //return ::DrawIconEx(m_hdc, x, y, picon->m_hicon, cx, cy, istepIfAniCur, hbrFlickerFreeDraw, diFlags);

   //   return true;

   //}

//   bool graphics::DrawState(const ::i32_point & point, const ::i32_size & size, HBITMAP hBitmap, unsigned int nFlags, HBRUSH hBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, hBrush, nullptr, (LPARAM)hBitmap, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_BITMAP) != false;
//      return false;
//
//   }

//   bool graphics::DrawState(const ::i32_point & point, const ::i32_size & size, ::draw2d::bitmap* pBitmap, unsigned int nFlags, ::draw2d::brush* pBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)pBitmap->get_os_data(), 0, point.x, point.y, size.cx, size.cy, nFlags|DST_BITMAP) != false;
//
//      return false;
//
//   }
//
//   bool graphics::DrawState(const ::i32_point & point, const ::i32_size & size, HICON hIcon, unsigned int nFlags, HBRUSH hBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, hBrush, nullptr, (LPARAM)hIcon, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_ICON) != false;
//
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::i32_point & point, const ::i32_size & size, HICON hIcon, unsigned int nFlags, ::draw2d::brush* pBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)hIcon, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_ICON) != false;
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::i32_point & point, const ::i32_size & size, const ::string & lpszText, unsigned int nFlags, bool bPrefixText, double nTextLen, HBRUSH hBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, hBrush,  nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x, point.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != false;
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::i32_point & point, const ::i32_size & size, const ::string & lpszText, unsigned int nFlags, bool bPrefixText, double nTextLen, ::draw2d::brush* pBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x, point.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != false;
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::i32_point & point, const ::i32_size & size, DRAWSTATEPROC lpDrawProc, LPARAM lData, unsigned int nFlags, HBRUSH hBrush)
//   {
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, hBrush,
//          //               lpDrawProc, lData, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_COMPLEX) != false;
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::i32_point & point, const ::i32_size & size, DRAWSTATEPROC lpDrawProc, LPARAM lData, unsigned int nFlags, ::draw2d::brush* pBrush)
//   {
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, (HBRUSH)pBrush->get_os_data(),
//        //                 lpDrawProc, lData, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_COMPLEX) != false;
//      return false;
//
//   }
//

//   bool graphics::DrawEdge(const ::f64_rectangle & rectangleParam,unsigned int nEdge,unsigned int nFlags)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawEdge(m_hdc,(::f64_rectangle *)&rectangleParam,nEdge,nFlags) != false;
//      return false;
//
//   }
//

//   bool graphics::DrawFrameControl(const ::f64_rectangle & rectangleParam,unsigned int nType,unsigned int nState)
//   {
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawFrameControl(m_hdc,(::f64_rectangle *) &rectangleParam,nType,nState) != false;
//      return false;
//
//   }


   bool graphics::Chord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::Chord(m_hdc, x1, y1, x2, y2, x3, y3, x4, y4) != false;
      return false;

   }


   bool graphics::Chord(const ::i32_rectangle& rectangleParam, const ::i32_point& pointStart, const ::i32_point& pointEnd)
   {

      // ASSERT(m_hdc != nullptr);
      //return ::Chord(m_hdc,rectangleParam.left,rectangleParam.top,
      //               rectangleParam.right,rectangleParam.bottom,ptStart.x,ptStart.y,
      //               ptEnd.x, ptEnd.y) != false;

      return false;

   }


   void graphics::DrawFocusRect(const ::i32_rectangle& rectangleParam)
   {
      // ASSERT(m_hdc != nullptr);
      //::DrawFocusRect(m_hdc,&rectangleParam);

   }


   //bool graphics::DrawEllipse(double x1, double y1, double x2, double y2)
   //{

   //   //set_smooth_mode(::draw2d::e_smooth_mode_high);

   //   //return (m_pgraphics->DrawEllipse(gl2d_pen(), x1, y1, x2 - x1, y2 - y1)) == plusplus::Status::Ok;

   //   return true;
   //}


   struct Vertex {
      float x, y;
   };

   // Generates vertices for a thick circle using a triangle list.
   void  graphics::_createThickCircle(::array<::floating_sequence2> & vertices, float centerX, float centerY, float radiusPixels, float thicknessPixels, int numSegments)
   {

      vertices.erase_all();

      if (numSegments < 3 || radiusPixels <= 0.0f || thicknessPixels <= 0.0f)
      {

         return;

      }

      const float rOuter = radiusPixels + thicknessPixels * 0.5f;
      const float rInner = ::maximum(0.0f, radiusPixels - thicknessPixels * 0.5f);
      const float angleStep = 2.0f * 3.14159265f / (float) numSegments;

      for (int i = 0; i < numSegments; ++i)
      {

         const float angle0 = (float) i * angleStep;
         const float angle1 = (float) (i + 1) * angleStep;

         const float cos0 = std::cos(angle0);
         const float sin0 = std::sin(angle0);
         const float cos1 = std::cos(angle1);
         const float sin1 = std::sin(angle1);

         const ::floating_sequence2 outer0 =
            { centerX + cos0 * rOuter, centerY + sin0 * rOuter };
         const ::floating_sequence2 inner0 =
            { centerX + cos0 * rInner, centerY + sin0 * rInner };
         const ::floating_sequence2 outer1 =
            { centerX + cos1 * rOuter, centerY + sin1 * rOuter };
         const ::floating_sequence2 inner1 =
            { centerX + cos1 * rInner, centerY + sin1 * rInner };

         vertices.add(outer0);
         vertices.add(inner0);
         vertices.add(outer1);

         vertices.add(outer1);
         vertices.add(inner0);
         vertices.add(inner1);

      }


   }

   

   void graphics::draw_ellipse_1(const ::f64_rectangle& rectangleParam)
   {

      //set_smooth_mode(::draw2d::e_smooth_mode_high);

      //return (m_pgraphics->DrawEllipse(gl2d_pen(),rectangleParam.left,rectangleParam.top,rectangleParam.right - rectangleParam.left,rectangleParam.bottom - rectangleParam.top)) == plusplus::Status::Ok;

      //return true;

      // Setup Buffers (Run once during initialization)
   // Note: Ensure your Projection Matrix translates pixel coordinates into NDC.

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      auto pcontext = gpu_context();

      auto prenderer = pcontext->m_pgpurenderer;

      ::gpu::context_lock contextlock(pcontext);


      auto pshader = sequence2_with_uniform_color_shader();

      auto pcommandbuffer = prenderer->getCurrentCommandBuffer2(::gpu::current_layer());


      set_gpu_shader(pcommandbuffer, pshader);


            // 1. Calculate optimal number of segments based on radius
      int numSegments = static_cast<int>(::ceil(2.0f * 3.14159265f * ::sqrt(rectangleParam.width() / 2.0)));
      numSegments = ::maximum(numSegments, 16); // Safety floor for tiny circles

      
      //unsigned int VAO, VBO;
      //glGenVertexArrays(1, &VAO);
      //glGenBuffers(1, &VBO);

      //glBindVertexArray(VAO);
      //glBindBuffer(GL_ARRAY_BUFFER, VBO);
      //glBufferData(GL_ARRAY_BUFFER, circleVertices.size() * sizeof(Vertex), circleVertices.data(), GL_STATIC_DRAW);

      //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
      //glEnableVertexAttribArray(0);

      //// Rendering Loop Call:
      //// Each segment adds 2 vertices; loops back around adding 2 final matching vertices.
      //int totalVertices = (numSegments + 1) * 2;
      //glDrawArrays(GL_TRIANGLE_STRIP, 0, totalVertices);


      
      auto contextmatrix = this->context_matrix(e_transform_context_geometry);

      ::array <::floating_sequence2> vertices;

      auto pmodelbuffer = createø<::gpu::model_buffer>();

      pmodelbuffer->initialize_gpu_context_object(pcontext);

      pmodelbuffer->create_vertexes< ::floating_sequence2>(numSegments * 6);


      ::array< ::f64_point > seq2aCenter;

      seq2aCenter.set_size(1);
      
      seq2aCenter[0].x = rectangleParam.center_x();
      
      seq2aCenter[0].y = rectangleParam.center_y();

      __transform(seq2aCenter);

      _createThickCircle(
         vertices, 
         seq2aCenter[0].x,
         seq2aCenter[0].y,
         rectangleParam.minimum_dimension()/2.0, 
         m_pdraw2dpen->m_dWidth * draw2d_domain()->get_density(),
         numSegments);

      contextmatrix.transform(vertices);

      pmodelbuffer->_set_vertexes(vertices);

      auto color = m_pdraw2dpen->m_color;

      //::array<::graphics3d::sequence2_color> quadVertices;
      //for (auto & point : pointa)
      //   quadVertices.add({ {(float)point.x, (float)point.y}, {fR, fG, fB, fA} });

      pmodelbuffer->initialize_gpu_context_object(pcontext);


      //auto ptextureTarget = pcommandbuffer->m_pgpurendertarget->current_texture(::gpu::current_layer());

      ::floating_sequence4 seq4Color;
      seq4Color.a = color.f32_opacity();
      seq4Color.r = color.f32_red() * seq4Color.a;
      seq4Color.g = color.f32_green() * seq4Color.a;
      seq4Color.b = color.f32_blue() * seq4Color.a;


      pshader->set_sequence4("uniformFragmentColor", seq4Color);

      pshader->push_properties(pcommandbuffer);


      //pmodelbuffer->bind(pcommandbuffer);

      pcommandbuffer->draw(pmodelbuffer);
      //
            //      pmodelbuffer->unbind(pcommandbuffer);

      pcontext->defer_unbind(pcommandbuffer, pshader);

   }


   void graphics::draw_ellipse(const ::f64_rectangle & rectangleParam)
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      auto pcontext = gpu_context();

      auto prenderer = pcontext->m_pgpurenderer;

      ::gpu::context_lock contextlock(pcontext);


      auto pshader = circle_shader();

      auto pcommandbuffer = prenderer->getCurrentCommandBuffer2(::gpu::current_layer());


      set_gpu_shader(pcommandbuffer, pshader);


      // 1. Calculate optimal number of segments based on radius
      int numSegments = static_cast<int>(::ceil(2.0f * 3.14159265f * ::sqrt(rectangleParam.width() / 2.0)));
      numSegments = ::maximum(numSegments, 16); // Safety floor for tiny circles


      //unsigned int VAO, VBO;
      //glGenVertexArrays(1, &VAO);
      //glGenBuffers(1, &VBO);

      //glBindVertexArray(VAO);
      //glBindBuffer(GL_ARRAY_BUFFER, VBO);
      //glBufferData(GL_ARRAY_BUFFER, circleVertices.size() * sizeof(Vertex), circleVertices.data(), GL_STATIC_DRAW);

      //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
      //glEnableVertexAttribArray(0);

      //// Rendering Loop Call:
      //// Each segment adds 2 vertices; loops back around adding 2 final matching vertices.
      //int totalVertices = (numSegments + 1) * 2;
      //glDrawArrays(GL_TRIANGLE_STRIP, 0, totalVertices);



      auto contextmatrix = this->context_matrix(e_transform_context_geometry);

      ::array <::floating_sequence2> vertices;

      auto pmodelbuffer = createø<::gpu::model_buffer>();

      pmodelbuffer->initialize_gpu_context_object(pcontext);

      auto radius = rectangleParam.minimum_dimension() / 2.0;

      auto thickness = m_pdraw2dpen->m_dWidth * draw2d_domain()->get_density();

      auto extent = radius + thickness / 2.0f + 2.0f;

      pmodelbuffer->create_vertexes< ::gpu::circle_vertex>(6);
      
      auto centerX = rectangleParam.center_x();

      auto centerY = rectangleParam.center_y();

      ::array<::gpu::circle_vertex> vertexa =
      {
         // Triangle 1
         {{centerX - extent, centerY - extent}, {-extent, -extent}},
         {{centerX + extent, centerY - extent}, { extent, -extent}},
         {{centerX + extent, centerY + extent}, { extent,  extent}},

         // Triangle 2
         {{centerX - extent, centerY - extent}, {-extent, -extent}},
         {{centerX + extent, centerY + extent}, { extent,  extent}},
         {{centerX - extent, centerY + extent}, {-extent,  extent}},
      };

      // These operations must transform circle_vertex::position only.
      // circle_vertex::local_position must remain unchanged.
      __transform(vertexa);
      contextmatrix.global_transform(vertexa);

      //pmodelbuffer->_set_vertexes(vertexa);

      //::array< ::gpu::circle_vertex > vertexa=
      //   {
      //      {{centerX, centerY}, {0, 0}},
      //      {{centerX, centerY}, {0, 0}},
      //      {{centerX, centerY}, {0, 0}},

      //      {{centerX, centerY}, {0, 0}},
      //      {{centerX, centerY}, {0, 0}},
      //      {{centerX, centerY}, {0, 0}},
      //   };
      //   //{
      ////   {{centerX - extent, centerY - extent}, {-extent, -extent}},
      ////   {{centerX + extent, centerY - extent}, {+extent, -extent}},
      ////   {{centerX + extent, centerY + extent}, {+extent, +extent}},
      //__transform(vertexa);

      //contextmatrix.global_transform(vertexa);

      //auto & circlevertex0 = vertexa[0];
      //circlevertex0.position.x -= extent;
      //circlevertex0.position.y -= extent;
      //circlevertex0.local_position.x = -extent;
      //circlevertex0.local_position.y = -extent;
      //vertexa[1].position.x += extent;
      //vertexa[1].position.y -= extent;
      //vertexa[1].local_position.x =  extent;
      //vertexa[1].local_position.y = -extent;
      //vertexa[2].position.x += extent;
      //vertexa[2].position.y += extent;
      //vertexa[2].local_position.x = extent;
      //vertexa[2].local_position.y =  extent;


      ////   {{centerX - extent, centerY - extent}, {-extent, -extent}},
      ////   {{centerX + extent, centerY + extent}, {+extent, +extent}},
      ////   {{centerX - extent, centerY + extent}, {-extent, +extent}},
      ////};


      //vertexa[3].position.x -= extent;
      //vertexa[3].position.y -= extent;
      //vertexa[3].local_position.x = -extent;
      //vertexa[3].local_position.y = -extent;
      //vertexa[4].position.x += extent;
      //vertexa[4].position.y += extent;
      //vertexa[4].local_position.x = extent;
      //vertexa[4].local_position.y = extent;
      //vertexa[5].position.x -= extent;
      //vertexa[5].position.y += extent;
      //vertexa[5].local_position.x = -extent;
      //vertexa[5].local_position.y = extent;


      //seq2aCenter.set_size(1);

      //seq2aCenter[0].x = rectangleParam.center_x();

      //seq2aCenter[0].y = rectangleParam.center_y();

      //_createThickCircle(
      //   vertices,
      //   seq2aCenter[0].x,
      //   seq2aCenter[0].y,
      //   rectangleParam.minimum_dimension() / 2.0,
      //   m_pdraw2dpen->m_dWidth,
//         numSegments);

      
      pmodelbuffer->_set_vertexes(vertexa);

      auto color = m_pdraw2dpen->m_color;

      //::array<::graphics3d::sequence2_color> quadVertices;
      //for (auto & point : pointa)
      //   quadVertices.add({ {(float)point.x, (float)point.y}, {fR, fG, fB, fA} });



      //auto ptextureTarget = pcommandbuffer->m_pgpurendertarget->current_texture(::gpu::current_layer());

      ::floating_sequence4 seq4Color;
      seq4Color.a = color.f32_opacity();
      seq4Color.r = color.f32_red() * seq4Color.a;
      seq4Color.g = color.f32_green() * seq4Color.a;
      seq4Color.b = color.f32_blue() * seq4Color.a;


      pshader->set_sequence4("uniformFragmentColor", seq4Color);
      pshader->set_f32("radius", radius);
      pshader->set_f32("thickness", thickness);
      pshader->push_properties(pcommandbuffer);


      //pmodelbuffer->bind(pcommandbuffer);

      pcommandbuffer->draw(pmodelbuffer);
      //
            //      pmodelbuffer->unbind(pcommandbuffer);

      pcontext->defer_unbind(pcommandbuffer, pshader);

   }

   //bool graphics::FillEllipse(double x1, double y1, double x2, double y2)
   //{

   //   //set_smooth_mode(::draw2d::e_smooth_mode_high);

   //   //return (m_pgraphics->FillEllipse(gl2d_brush(), x1, y1, x2 - x1, y2 - y1)) == plusplus::Status::Ok;

   //   return true;

   //}


   void graphics::fill_ellipse(const ::f64_rectangle& rectangleParam)
   {

      ::gpu::graphics::fill_ellipse(rectangleParam);

   }


   //bool graphics::draw_ellipse(double x1,double y1,double x2,double y2)
   //{

   //   //set_smooth_mode(::draw2d::e_smooth_mode_high);

   //   //return (m_pgraphics->DrawEllipse(gl2d_pen(),(plusplus::REAL)x1,(plusplus::REAL)y1,(plusplus::REAL)(x2 - x1),(plusplus::REAL)(y2 - y1))) == plusplus::Status::Ok;

   //   return true;

   //}


   //bool graphics::draw_ellipse(const ::f64_rectangle & rectectParam)
   //{

   //   //set_smooth_mode(::draw2d::e_smooth_mode_high);

   //   //return (m_pgraphics->DrawEllipse(gl2d_pen(),(plusplus::REAL)rectangleParam.left,(plusplus::REAL)rectangleParam.top,
   //   //                                 (plusplus::REAL)(rectangleParam.right - rectangleParam.left),
   //   //                                 (plusplus::REAL)(rectangleParam.bottom - rectangleParam.top))) == plusplus::Status::Ok;

   //   return true;

   //}


   //bool graphics::FillEllipse(double x1,double y1,double x2,double y2)
   //{

   //   //set_smooth_mode(::draw2d::e_smooth_mode_high);

   //   //return (m_pgraphics->FillEllipse(gl2d_brush(),(plusplus::REAL)x1,(plusplus::REAL)y1,(plusplus::REAL)(x2 - x1),(plusplus::REAL)(y2 - y1))) == plusplus::Status::Ok;

   //   return true;

   //}


   //bool graphics::FillEllipse(const ::f64_rectangle & rectectParam)
   //{

   //   //set_smooth_mode(::draw2d::e_smooth_mode_high);

   //   //return (m_pgraphics->FillEllipse(gl2d_brush(),(plusplus::REAL)rectangleParam.left,(plusplus::REAL)rectangleParam.top,
   //   //                                 (plusplus::REAL)(rectangleParam.right - rectangleParam.left),
   //   //                                 (plusplus::REAL)(rectangleParam.bottom - rectangleParam.top))) == plusplus::Status::Ok;

   //   return true;

   //}


   //bool graphics::Pie(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   //{
   //
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::Pie(m_hdc, x1, y1, x2, y2, x3, y3, x4, y4) != false;
   //   return false;

   //}


   //bool graphics::Pie(const ::f64_rectangle & rectangleParam,const ::i32_point & pointStart,const ::i32_point & pointEnd)
   //{

   //   // ASSERT(m_hdc != nullptr);
   //   //return ::Pie(m_hdc, rectangleParam.left, rectangleParam.top,
   //   //             rectangleParam.right, rectangleParam.bottom, ptStart.x, ptStart.y,
   //   //             ptEnd.x, ptEnd.y) != false;

   //   return false;

   //}


   void graphics::fill_polygon(const ::f64_point* lpPoints, ::collection::count nCount)
   {

      ::gpu::graphics::fill_polygon(lpPoints, nCount);

   }


   //void graphics::fill_polygon(const ::f64_point* lpPoints,::collection::count nCount)
   //{

   //   //   if(nCount <= 0)
   //   //      return true;

   //   //   bool bOk1 = false;

   //   //   plusplus::Point * ppoints = ___new plusplus::Point[nCount];

   //   //   try
   //   //   {

   //   //      for(double i = 0; i < nCount; i++)
   //   //      {
   //   //         ppoints[i].X = lpPoints[i].x;
   //   //         ppoints[i].Y = lpPoints[i].y;
   //   //      }

   //   //      m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

   //   //      bOk1 = m_pgraphics->FillPolygon(gl2d_brush(), ppoints, (::double)  nCount, gl2d_get_fill_mode()) == plusplus::Status::Ok;

   //   //   }
   //   //   catch(...)
   //   //   {
   //   //   }

   //   //   try
   //   //   {
   //   //      delete ppoints;
   //   //   }
   //   //   catch(...)
   //   //   {
   //   //   }


   //   //   return bOk1;

   //   return true;

   //}


   void graphics::draw_polygon(const ::f64_point* lpPoints, ::collection::count nCount)
   {

      //if (nCount <= 0)
      //   return true;

      //bool bOk1 = false;

      //plusplus::Point * ppoints = ___new plusplus::Point[nCount];

      //try
      //{

      //   for (double i = 0; i < nCount; i++)
      //   {
      //      ppoints[i].X = lpPoints[i].x;
      //      ppoints[i].Y = lpPoints[i].y;
      //   }

      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

      //   set_smooth_mode(::draw2d::e_smooth_mode_high);

      //   bOk1 = m_pgraphics->DrawPolygon(gl2d_pen(), ppoints, (::double) nCount) == plusplus::Status::Ok;

      //}
      //catch (...)
      //{
      //}

      //try
      //{
      //   delete ppoints;
      //}
      //catch (...)
      //{
      //}


      //return bOk1;
      //return true;

   }


   //void graphics::draw_polygon(const ::f64_point* lpPoints,::collection::count nCount)
   //{

   //   //if(nCount <= 0)
   //   //   return true;

   //   //bool bOk1 = false;

   //   //plusplus::PointF * ppoints = ___new plusplus::PointF[nCount];

   //   //try
   //   //{

   //   //   for(double i = 0; i < nCount; i++)
   //   //   {
   //   //      ppoints[i].X = (plusplus::REAL) lpPoints[i].x;
   //   //      ppoints[i].Y = (plusplus::REAL) lpPoints[i].y;
   //   //   }

   //   //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

   //   //   bOk1 = m_pgraphics->DrawPolygon(gl2d_pen(),ppoints,(::double) nCount) == plusplus::Status::Ok;

   //   //}
   //   //catch(...)
   //   //{
   //   //}

   //   //try
   //   //{
   //   //   delete ppoints;
   //   //}
   //   //catch(...)
   //   //{
   //   //}


   //   //return bOk1;

   //   return true;

   //}


   void graphics::polygon(const ::f64_point* lpPoints, ::collection::count nCount)
   {

      //if(nCount <= 0)
      //   return true;

      //bool bOk1 = false;

      //bool bOk2 = false;

      //plusplus::Point * ppoints = ___new plusplus::Point[nCount];

      //try
      //{

      //   for(double i = 0; i < nCount; i++)
      //   {
      //      ppoints[i].X = lpPoints[i].x;
      //      ppoints[i].Y = lpPoints[i].y;
      //   }


      //   set_smooth_mode(::draw2d::e_smooth_mode_high);

      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);


      //   bOk1 = m_pgraphics->FillPolygon(gl2d_brush(), ppoints, (::double) nCount, gl2d_get_fill_mode()) == plusplus::Status::Ok;

      //   bOk2 = m_pgraphics->DrawPolygon(gl2d_pen(), ppoints, (::double) nCount) == plusplus::Status::Ok;

      //}
      //catch(...)
      //{
      //}

      //try
      //{
      //   delete ppoints;
      //}
      //catch(...)
      //{
      //}


      //return bOk1 && bOk2;

      //return true;

   }


   void graphics::poly_polygon(const ::f64_point* lpPoints, const int* lpPolyCounts, ::collection::count nCount)
   {

      // ASSERT(m_hdc != nullptr);


      //return ::PolyPolygon(m_hdc, lpPoints, (const ::double *) lpPolyCounts, (int) nCount) != false;
      //return false;

   }


   //bool graphics::f64_rectangle(double x1, double y1, double x2, double y2)
   //{

   //   //plusplus::rectF float_rectangle((plusplus::REAL) x1, (plusplus::REAL) y1, (plusplus::REAL) (x2 - x1), (plusplus::REAL) (y2 - y1));

   //   //bool bOk1 = m_pgraphics->FillRectangle(gl2d_brush(), float_rectangle) == plusplus::Status::Ok;

   //   //bool bOk2 = m_pgraphics->DrawRectangle(gl2d_pen(), float_rectangle) == plusplus::Status::Ok;

   //   //return bOk1 && bOk2;

   //   return true;

   //}


   //void graphics::polygon(const ::f64_point* lpPoints,::collection::count nCount)
   //{

   //   //if(nCount <= 0)
   //   //   return true;

   //   //bool bOk1 = false;

   //   //bool bOk2 = false;

   //   //plusplus::PointF * ppoints = ___new plusplus::PointF[nCount];

   //   //try
   //   //{

   //   //   for(double i = 0; i < nCount; i++)
   //   //   {
   //   //      ppoints[i].X = (plusplus::REAL) lpPoints[i].x;
   //   //      ppoints[i].Y = (plusplus::REAL) lpPoints[i].y;
   //   //   }

   //   //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

   //   //   if(m_ealphamode == ::draw2d::e_alpha_mode_set)
   //   //   {

   //   //      set_smooth_mode(::draw2d::e_smooth_mode_none);

   //   //   }
   //   //   else
   //   //   {

   //   //      set_smooth_mode(::draw2d::e_smooth_mode_high);

   //   //   }


   //   //   bOk1 = m_pgraphics->FillPolygon(gl2d_brush(),ppoints,(::double) nCount,gl2d_get_fill_mode()) == plusplus::Status::Ok;

   //   //   bOk2 = m_pgraphics->DrawPolygon(gl2d_pen(),ppoints,(::double) nCount) == plusplus::Status::Ok;

   //   //}
   //   //catch(...)
   //   //{
   //   //}

   //   //try
   //   //{
   //   //   delete ppoints;
   //   //}
   //   //catch(...)
   //   //{
   //   //}


   //   //return bOk1 && bOk2;

   //   return true;

   //}


   void graphics::rectangle(const ::f64_rectangle& rectangleParam)
   {

      fill_rectangle(rectangleParam);

      draw_rectangle(rectangleParam);

      //return ::f64_rectangle(rectangleParam.left, rectangleParam.top, rectangleParam.right, rectangleParam.bottom);

      //return bOk1 && bOk2;

   }

   
   void graphics::draw_rectangle(const ::f64_rectangle& rectangle, ::draw2d::pen* pdraw2dpen)
   {

      if (::is_null(pdraw2dpen) || pdraw2dpen->m_epen == ::draw2d::e_pen_null)
      {

         return;

      }

      if (pdraw2dpen->m_epen == ::draw2d::e_pen_solid && pdraw2dpen->m_dWidth <= 0.0)
      {

         return;

      }

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      auto pcontext = gpu_context();

      auto prenderer = pcontext->m_pgpurenderer;

      ::gpu::context_lock contextlock(pcontext);

      auto pshader = rectangle_shader();

      //float g_z = 0.0f; // Assuming z is 0 for 2D rendering, adjust as needed

      ::block_array < ::f64_point, 4 > pointa1;

      rectangle.add_clockwise_edges(pointa1);

      for(auto & item : pointa1) __transform(item);

      ::f64_point pointPen(pdraw2dpen->m_dWidth * draw2d_domain()->get_density(), pdraw2dpen->m_dWidth * draw2d_domain()->get_density());

      ::f64_point_array pointa;

      ::draw2d::make_draw_rectangle(
         pointa,
         pointa1,
         pointPen);

      auto contextmatrix = this->context_matrix(e_transform_context_geometry);

      contextmatrix.transform(pointa);


      auto color = m_pdraw2dpen->m_color;

      float fA = color.f32_opacity();
      float fR = color.f32_red() * fA;
      float fG = color.f32_green() * fA;
      float fB = color.f32_blue() * fA;

      ::array<::graphics3d::sequence2_color> quadVertices;
      for (auto& point : pointa)
         quadVertices.add({ {(float)point.x, (float)point.y}, {fR, fG, fB, fA} });

      auto pmodelbuffer = model_buffer(::draw2d::e_model_draw_rectangle);

      if (pmodelbuffer->is_new())
      {

         pmodelbuffer->initialize_gpu_context_object(pcontext);

         pmodelbuffer->create_vertexes< ::graphics3d::sequence2_color>(24);

      }

      pmodelbuffer->set_vertexes(quadVertices);

      auto pcommandbuffer = prenderer->getCurrentCommandBuffer2(::gpu::current_layer());

      //auto ptextureTarget = pcommandbuffer->m_pgpurendertarget->current_texture(::gpu::current_layer());

      set_gpu_shader(pcommandbuffer, pshader);

      //pmodelbuffer->bind(pcommandbuffer);

      pcommandbuffer->draw(pmodelbuffer);
//
      //      pmodelbuffer->unbind(pcommandbuffer);

      pcontext->defer_unbind(pcommandbuffer, pshader);

   }


   void graphics::draw_rectangle(const ::f64_rectangle& rectangle)
   {

      draw_rectangle(rectangle, m_pdraw2dpen);

   }


   void graphics::fill_rectangle(const ::f64_rectangle& rectangle)
   {

      fill_rectangle(rectangle, m_pdraw2dbrush);

   }


   //void graphics::round_rectangle(double x1, double y1, double x2, double y2, double x3, double y3)
   //{
   //
   //   //// ASSERT(m_hdc != nullptr);
   //   //return ::RoundRect(m_hdc, x1, y1, x2, y2, x3, y3) != false;

   //   //return false;

   //}


   void graphics::round_rectangle(const ::f64_rectangle& rectangleParam, const ::i32_point& point)
   {
      //// ASSERT(m_hdc != nullptr);
      //return ::RoundRect(m_hdc, rectangleParam.left, rectangleParam.top,
        //                 rectangleParam.right, rectangleParam.bottom, point.x, point.y) != false;

      //return false;

   }


   //   bool graphics::PatBlt(double x, double y, double nWidth, double nHeight)
   //   {
   //      //// ASSERT(m_hdc != nullptr);
   //      //return ::PatBlt(m_hdc, x, y, nWidth, nHeight, dwRop) != false;
   //
   //      return false;
   //
   //   }
   //
   //
   //   bool graphics::BitBltRaw(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc)
   //   {
   ////      if (m_pgraphics == nullptr)
   ////         return false;
   ////
   ////      if (::draw2d::graphics::BitBlt(x, y, nWidth, nHeight, pgraphicsSrc, xSrc, ySrc, dwRop))
   ////         return true;
   ////
   //      try
   //      {
   //
   //         if(pgraphicsSrc == nullptr)
   //            return false;
   //
   //         if (pgraphicsSrc->get_current_bitmap() == nullptr)
   //            return false;
   //
   //         if (pgraphicsSrc->get_current_bitmap()->get_os_data() == nullptr)
   //            return false;
   //
   //         ::pointer<bitmap>pdraw2dbitmap = pgraphicsSrc->get_current_bitmap();
   //
   //         //pdraw2dbitmap->create_texture(0);
   //
   //         //glBegin(GL_QUADS);
   //         //// Front Face
   //         //glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
   //         //glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
   //         //glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
   //         //glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
   //
   //
   ////
   ////
   ////         return m_pgraphics->DrawImage(
   ////                   (plusplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data(),
   ////                   x, y, xSrc + pgraphicsSrc->get_origin().x, ySrc + pgraphicsSrc->get_origin().y, nWidth, nHeight, plusplus::UnitPixel) == plusplus::Status::Ok;
   ////
   //      }
   //      catch(...)
   //      {
   //         return false;
   //      }
   ////
   ////      //return ::BitBlt(m_hdc, x, y, nWidth, nHeight, GL2D_HDC(pgraphicsSrc), xSrc, ySrc);
   ////
   ////gdi_fallback:
   ////
   ////      HDC hdcDst = get_hdc();
   ////
   ////      if(hdcDst == nullptr)
   ////         return false;
   ////
   ////      HDC hdcSrc = GL2D_GRAPHICS(pgraphicsSrc)->get_hdc();
   ////
   ////      if(hdcSrc == nullptr)
   ////      {
   ////
   ////         release_hdc(hdcDst);
   ////
   ////         return false;
   ////
   ////      }
   ////
   ////      bool bOk = ::BitBlt(hdcDst, x, y, nWidth, nHeight, hdcSrc, x, y, dwRop) != false;
   ////
   ////      GL2D_GRAPHICS(pgraphicsSrc)->release_hdc(hdcSrc);
   ////
   ////      release_hdc(hdcDst);
   ////
   ////      return bOk;
   //
   //      return true;
   //
   //   }
   //
   //
   //   bool graphics::StretchBltRaw(double xDst, double yDst, double nDstWidth, double nDstHeight, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, double nSrcWidth, double nSrcHeight)
   //   {
   //
   //      //if(pgraphicsSrc == nullptr)
   //      //   return false;
   //
   //      //plusplus::rectF dstRect((plusplus::REAL) xDst, (plusplus::REAL) yDst, (plusplus::REAL) nDstWidth, (plusplus::REAL) nDstHeight);
   //
   //      //plusplus::rectF srcRect((plusplus::REAL) xSrc, (plusplus::REAL) ySrc, (plusplus::REAL) nSrcWidth, (plusplus::REAL) nSrcHeight);
   //
   //      //if(pgraphicsSrc == nullptr || pgraphicsSrc->get_current_bitmap() == nullptr)
   //      //   return false;
   //
   //      //try
   //      //{
   //      //   return m_pgraphics->DrawImage((plusplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data(),  dstRect, srcRect, plusplus::UnitPixel) == plusplus::Status::Ok;
   //      //}
   //      //catch(...)
   //      //{
   //
   //      //}
   //
   //      //return false;
   //
   //      ////return ::StretchBlt(m_hdc, x, y, nWidth, nHeight, GL2D_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth, nSrcHeight);
   //
   //      return true;
   //
   //   }


   ::color::color graphics::GetPixel(int x, int y) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetPixel(m_hdc, x, y);
      return color::transparent;

   }


   ::color::color graphics::GetPixel(const ::i32_point& point) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetPixel(m_hdc, point.x, point.y);
      return color::transparent;

   }


   ::color::color graphics::SetPixel(double x, double y, ::color::color crColor)
   {

      return color::transparent;

   }


   ::color::color graphics::SetPixel(const ::i32_point& point, ::color::color crColor)
   {

      //fill_solid_rect_coord(point.x,point.y,1,1,crColor);

      return crColor;

   }


   //   bool graphics::FloodFill(double x, double y, color32_t crColor)
   //   {
   //
   //      // ASSERT(m_hdc != nullptr);
   //      //return ::FloodFill(m_hdc, x, y, crColor) != false;
   //      return 0;
   //
   //   }
   //
   //
   //   bool graphics::ExtFloodFill(double x, double y, color32_t crColor, unsigned int nFillType)
   //   {
   //
   //      // ASSERT(m_hdc != nullptr);
   //      //return ::ExtFloodFill(m_hdc, x, y, crColor, nFillType) != false;
   //
   //      return 0;
   //
   //   }


      //i32_size graphics::GetTabbedTextExtent(const ::string & lpszString, character_count nCount, ::collection::count nTabPositions, LPINT lpnTabStopPositions)
      //{

      //   // ASSERT(m_hdc != nullptr);

      //   return nullptr;

      //}


      //i32_size graphics::GetTabbedTextExtent(const ::string & str, ::collection::count nTabPositions, LPINT lpnTabStopPositions)
      //{

      //   // ASSERT(m_hdc != nullptr);

      //   return nullptr;

      //}


      //i32_size graphics::GetOutputTabbedTextExtent(const ::string & lpszString, character_count nCount, ::collection::count nTabPositions, LPINT lpnTabStopPositions)
      //{

      //   // ASSERT(m_hdc != nullptr);

      //   //return ::GetTabbedTextExtent(m_hdc, lpszString, (double) nCount, (int) nTabPositions, lpnTabStopPositions);
      //   return nullptr;

      //}


      //i32_size graphics::GetOutputTabbedTextExtent(const ::string & str, ::collection::count nTabPositions, LPINT lpnTabStopPositions)
      //{

      //   // ASSERT(m_hdc != nullptr);

      //   //return ::GetTabbedTextExtent(m_hdc, str, (double) str.length(), (int) nTabPositions, lpnTabStopPositions);
      //   return nullptr;

      //}


      //bool graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, double), LPARAM lpData, double nCount,double x, double y, double nWidth, double nHeight)
      //{

      //   // ASSERT(m_hdc != nullptr);

      //   //return ::GrayString(m_hdc, (HBRUSH)pBrush->get_os_data(),(GRAYSTRINGPROC)lpfnOutput, lpData, nCount, x, y, nWidth, nHeight) != false;
      //   return false;

      //}


   unsigned int graphics::GetTextAlign()
   {

      // ASSERT(m_hdc != nullptr);

      //return ::GetTextAlign(m_hdc);
      return 0;

   }


   //double graphics::GetTextFace(::collection::count nCount, char * lpszFacename)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //return ::GetTextFace(m_hdc, (int) nCount, lpszFacename);
   //   return -1;

   //}


   //double graphics::GetTextFace(string & rString)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //double nResult = ::GetTextFace(m_hdc, 256, rString.GetBuffer(256));
   //   //rString.ReleaseBuffer();

   //   //return nResult;
   //   return -1;

   //}


   void graphics::get_text_metrics(::write_text::text_metric* lpMetrics)
   {
     
      ::gpu::graphics::get_text_metrics(lpMetrics);

      //set(m_pwritetextfont);
      ////if (!set(m_pwritetextfont))
      ////{

      ////   return false;

      ////}

      ////::pointer<font>pwritetextfont = m_pwritetextfont;

      ////TEXTMETRIC tm;

      ////GetTextMetrics(pwritetextfont->m_hdcFont, &tm);

      ////lpMetrics->m_dAscent = tm.tmAscent;
      ////lpMetrics->m_dHeight = tm.tmHeight;
      ////lpMetrics->m_dDescent = tm.tmDescent;
      //////lpMetrics->tmAveCharWidth = tm.tmAveCharWidth;

      //////if (m_pgraphics == nullptr)
      ////   return false;

      ////graphics * pdraw2dgraphics = ((graphics *)this);

      ////if(pdraw2dgraphics->gl2d_font() == nullptr)
      ////   return false;

      ////plusplus::Font * pwritetextfont = pdraw2dgraphics->gl2d_font();

      ////plusplus::FontFamily family;

      ////pwritetextfont->GetFamily(&family);

      ////::double iStyle = pwritetextfont->GetStyle();

      ////double dHeight = family.GetEmHeight(iStyle);

      ////double dSize = pwritetextfont->GetSize();

      ////double dFontHeight = pwritetextfont->GetHeight((plusplus::REAL) pdraw2dgraphics->get_dpiy());

      ////lpMetrics->tmAscent              = (::double) (dSize * family.GetCellAscent(iStyle) / dHeight);
      ////lpMetrics->tmDescent             = (::double) (dSize * family.GetCellDescent(iStyle) / dHeight);
      ////lpMetrics->tmHeight              = (::double)dFontHeight;

      ////double dLineSpacing = maximum(dFontHeight, dSize * family.GetLineSpacing(iStyle) / dHeight);

      ////lpMetrics->tmInternalLeading     = (::double) (lpMetrics->tmAscent + lpMetrics->tmDescent - lpMetrics->tmHeight);
      ////lpMetrics->tmExternalLeading     = (::double) (dLineSpacing - (lpMetrics->tmAscent + lpMetrics->tmDescent));

      ////const plusplus::FontFamily * pfamilyMono = family.GenericMonospace();

      ////::plusplus::Font font2(pfamilyMono, pfamilyMono->GetEmHeight(((graphics * )this)->gl2d_font()->GetStyle()));

      ////wstring wstr(L"123AWZwmc123AWZwmcpQg");
      ////plusplus::rectF ::f64_rectangle(0.f, 0.f, 1024.f * 1024.f, 1024.f * 1024.f);
      ////plusplus::rectF rect2;
      ////plusplus::PointF origin(0, 0);

      ////m_pgraphics->MeasureString(wstr, (::double) wstr.get_length(), ((graphics * )this)->gl2d_font(), origin, &rectangle);


      /////*wstr = L"";
      ////m_pgraphics->MeasureString(wstr.m_pwsz, -1, (plusplus::Font *) m_pwritetextfont->get_os_data(), origin, &rect2);*/

      ////lpMetrics->tmAveCharWidth = (::double) (rectangle.Width * get_current_font()->m_dFontWidth / (double) wstr.get_length());

      ////return true;

   }


   void graphics::get_output_text_metrics(::write_text::text_metric* lpMetrics)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::GetTextMetricsW(m_hdc, lpMetrics) != false;

      //throw ::interface_only();

      //return false;

   }


   //double graphics::GetTextCharacterExtra()
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetTextCharacterExtra(m_hdc);
   //   return 0;

   //}


   //bool graphics::GetCharWidth(unsigned int nFirstChar, unsigned int nLastChar, LPINT lpBuffer) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetCharWidth(m_hdc, nFirstChar, nLastChar, lpBuffer) != false;

   //   return false;

   //}


   //bool graphics::GetOutputCharWidth(unsigned int nFirstChar, unsigned int nLastChar, LPINT lpBuffer) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetCharWidth(m_hdc, nFirstChar, nLastChar, lpBuffer) != false;
   //   return false;

   //}


   unsigned int graphics::GetFontLanguageInfo() const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetFontLanguageInfo(m_hdc);

      return 0;

   }


   //unsigned int graphics::GetCharacterPlacement(const ::string & lpString, character_count nCount, character_count nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) const
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   // return ::GetCharacterPlacement(m_hdc, lpString, (int)nCount, (int)nMaxExtent, lpResults, dwFlags);
   //   return false;

   //}


   //unsigned int graphics::GetCharacterPlacement(string & str, character_count nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) const
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //return ::GetCharacterPlacement(m_hdc, (const ::string &)str, (double) str.length(), (int) nMaxExtent, lpResults, dwFlags);
   //   return false;

   //}


   //i32_size graphics::GetAspectRatioFilter() const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   ::i32_size size;
   //   // VERIFY(::GetAspectRatioFilterEx(m_hdc, &size));
   //   return size;

   //}


   //bool graphics::ScrollDC(double Δx, double Δy,
   //                        const ::f64_rectangle & lpRectScroll,const ::f64_rectangle & rectangleClip,
   //                        ::draw2d::region* pRgnUpdate, ::f64_rectangle * lpRectUpdate)
   //{
   //   
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::ScrollDC(m_hdc,Δx,Δy,&rectangleClip,
   //     //                &rectangleClip, (HRGN)pRgnUpdate->get_os_data(), lpRectUpdate) != false;
   //   return 0;

   //}


   // Printer Escape Functions
   int graphics::Escape(int nEscape, int nCount, const ::scoped_string& lpszInData, void * lpOutData)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::Escape(m_hdc, nEscape, nCount, lpszInData, lpOutData);
      return 0;

   }


   // graphics 3.1 Specific functions
   unsigned int graphics::SetBoundsRect(const ::f64_rectangle& rectangleBounds, unsigned int flags)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::SetBoundsRect(m_hdc, &rectangleBounds, flags);
      return 0;

   }


   unsigned int graphics::GetBoundsRect(::f64_rectangle* rectangleBounds, unsigned int flags)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetBoundsRect(m_hdc, rectangleBounds, flags);
      return 0;

   }


   void graphics::resize(const ::i32_size& sizeWindow)
   {

      m_sizeWindow = sizeWindow;

      bool bYSwap = m_papplication->m_gpu.m_bUseSwapChainWindow;

      ::opengl::resize(sizeWindow, bYSwap);

   }



   //bool graphics::ResetDC(const DEVMODE* lpDevMode)
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::ResetDC(m_hdc, lpDevMode) != nullptr;
   //   return false;

   //}


   //unsigned int graphics::GetOutlineTextMetrics(unsigned int cbData, LPOUTLINETEXTMETRICW lpotm) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetOutlineTextMetricsW(m_hdc, cbData, lpotm);
   //   return 0;
   //}


   //bool graphics::GetCharABCWidths(unsigned int nFirstChar, unsigned int nLastChar, LPABC lpabc) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetCharABCWidths(m_hdc, nFirstChar, nLastChar, lpabc) != false;
   //   return false;

   //}


   //unsigned int graphics::GetFontData(unsigned int dwTable, unsigned int dwOffset, LPVOID lpData,
   //                               unsigned int cbData) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetFontData(m_hdc, dwTable, dwOffset, lpData, cbData);
   //   return 0;

   //}


   //double graphics::GetKerningPairs(double nPairs, LPKERNINGPAIR lpkrnpair) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetKerningPairs(m_hdc, nPairs, lpkrnpair);
   //   return 0;

   //}


   //unsigned int graphics::GetGlyphOutline(unsigned int nChar, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPGLYPHMETRICS lpgm,
   //                                   unsigned int cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetGlyphOutline(m_hdc, nChar, nFormat,
   //     //                       lpgm, cbBuffer, lpBuffer, lpmat2);
   //   return 0;

   //}


   // // ::user::document handling functions
   // int graphics::StartDoc(LPDOCINFO lpDocInfo)
   // {
   //
   //    //ASSERT(m_hdc != nullptr);
   //
   //    //return ::StartDoc(m_hdc, lpDocInfo);
   //    return 0;
   //
   // }


//    int graphics::StartPage()
//    {
//
//       //ASSERT(m_hdc != nullptr);
//
//       //::StartPage(m_hdc);
//
//       //m_pgraphics = ___new plusplus::Graphics (m_hdc);
//
//       //m_pgraphics->SetPageUnit(plusplus::UnitPixel);
//
//       return 1;
//
//    }
//
//
//    int graphics::EndPage()
//    {
//
//       /* ASSERT(m_hdc != nullptr);
//
//        delete m_pgraphics;
//
//       */
//       //return ::EndPage(m_hdc);
//       return 0;
//
//    }
//
//
//    int graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, int))
//    {
//
//       //ASSERT(m_hdc != nullptr);
//
//       //return ::SetAbortProc(m_hdc, (ABORTPROC)lpfn);
//       return 0;
//
//    }
//
//
//    int graphics::AbortDoc()
//    {
//
//       //ASSERT(m_hdc != nullptr);
//
//       //return ::AbortDoc(m_hdc);
//       return 0;
//
//    }
//
//
//    int graphics::EndDoc()
//    {
//
//       //ASSERT(m_hdc != nullptr);
//
//       //return ::EndDoc(m_hdc);
//       return 0;
//
//    }


   //   bool graphics::MaskBlt(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc,
   //                          double xSrc, double ySrc, ::draw2d::bitmap& maskBitmap, double xMask, double yMask)
   //   {
   //      // ASSERT(m_hdc != nullptr);
   //      //return ::MaskBlt(m_hdc, x, y, nWidth, nHeight, GL2D_HDC(pgraphicsSrc),
   //        //               xSrc, ySrc,  (HBITMAP)maskBitmap.get_os_data(), xMask, yMask, dwRop) != false;
   //      return 0;
   //
   //   }
   //
   //
   //   bool graphics::PlgBlt(::f64_point * lpPoint, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc,
   //                         double nWidth, double nHeight, ::draw2d::bitmap& maskBitmap, double xMask, double yMask)
   //   {
   //
   //      /*try
   //      {
   //
   //         if(pgraphicsSrc == nullptr)
   //            return false;
   //
   //         if(pgraphicsSrc->get_current_bitmap() == nullptr)
   //            return false;
   //
   //         if(pgraphicsSrc->get_current_bitmap()->get_os_data() == nullptr)
   //            return false;
   //
   //         plusplus::Point p[3];
   //
   //         p[0].X = lpPoint[0].x;
   //         p[0].Y = lpPoint[0].y;
   //         p[1].X = lpPoint[1].x;
   //         p[1].Y = lpPoint[1].y;
   //         p[2].X = lpPoint[2].x;
   //         p[2].Y = lpPoint[2].y;
   //
   //         return m_pgraphics->DrawImage((plusplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data(), p, 3) == plusplus::Status::Ok;
   //
   //      }
   //      catch(...)
   //      {
   //         return false;
   //      }
   //      */
   //      return true;
   //
   //   }



   void graphics::SetPixelV(int x, int y, ::color::color crColor)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::SetPixelV(m_hdc, x, y, crColor) != false;
      //return 0;

   }


   void graphics::SetPixelV(const ::i32_point& point, ::color::color crColor)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::SetPixelV(m_hdc, point.x, point.y, crColor) != false;
      //return 0;

   }


   void graphics::angle_arc(double x, double y, double nRadius, ::f64_angle fStartAngle, ::f64_angle fSweepAngle)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::AngleArc(m_hdc, x, y, nRadius, fStartAngle, fSweepAngle) != false;
      //return 0;

   }



   void graphics::arc_to(const ::i32_rectangle& rectangleParam, const ::i32_point& pointStart, const ::i32_point& pointEnd)
   {
      // ASSERT(m_hdc != nullptr);
      //return ArcTo(rectangleParam.left, rectangleParam.top, rectangleParam.right,
        //           rectangleParam.bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);

      //return false;

   }


   //int graphics::GetArcDirection() const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   // return ::GetArcDirection(m_hdc);
   //   return 0;

   //}


   void graphics::poly_polyline(const ::f64_point* lpPoints, const int* lpPolyPoints, ::collection::count nCount)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::poly_polyline(m_hdc, lpPoints, (LPDWORD) lpPolyPoints, (unsigned int) nCount) != false;
      //return false;

   }


   // bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const
   // {
   //    // ASSERT(m_hdc != nullptr);
   //    //return ::GetColorAdjustment(m_hdc, lpColorAdjust) != false;
   //    return false;
   //
   // }


   void graphics::set_target_image(::image::image * pimage)
   {

      ::cast < ::draw2d_opengl::image > popenglimage = pimage;

      if (!popenglimage)
      {

         throw ::exception(error_wrong_state, "OpenGL target image has an incompatible backend type");

      }

      ::cast < ::draw2d_opengl::bitmap > pdraw2dbitmap = popenglimage->m_pdraw2dbitmap;

      if (!pdraw2dbitmap)
      {

         throw ::exception(error_wrong_state, "OpenGL target image has no OpenGL bitmap");

      }

      ::cast < ::gpu_opengl::texture > ptexture = pdraw2dbitmap->m_pgputexture;

      if (!ptexture)
      {

         throw ::exception(error_wrong_state, "OpenGL target bitmap has no GPU texture");

      }

      ptexture->bind_render_target();

   }


   ::draw2d::pen* graphics::get_current_pen()
   {

      return m_pdraw2dpen;

   }

   ::draw2d::brush* graphics::get_current_brush()
   {

      return m_pdraw2dbrush;

   }

   //::draw2d::palette_pointer graphics::get_current_palette()
   //{

   //   return (::draw2d::palette *)nullptr;

   //}

   ::write_text::font* graphics::get_current_font()
   {

      return m_pwritetextfont;

   }

   ::draw2d::bitmap* graphics::get_current_bitmap()
   {

      return m_pdraw2dbitmap;

   }


   void graphics::poly_bezier(const ::f64_point* lpPoints, ::collection::count nCount)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::poly_bezier(m_hdc, lpPoints, (unsigned int) nCount) != false;
      //return false;

   }


   int graphics::DrawEscape(int nEscape, int nInputSize, const ::scoped_string& lpszInputData)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::DrawEscape(m_hdc, nEscape, nInputSize, lpszInputData);
      return 0;


   }


   int graphics::Escape(int nEscape, int nInputSize, const char* lpszInputData, int nOutputSize, char* lpszOutputData)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::ExtEscape(m_hdc, nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);
      return 0;

   }


   //bool graphics::GetCharABCWidths(unsigned int nFirstChar, unsigned int nLastChar,
   //                                LPABCFLOAT lpABCF) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetCharABCWidthsFloat(m_hdc, nFirstChar, nLastChar, lpABCF) != false;
   //   return false;
   //}


   //bool graphics::GetCharWidth(unsigned int nFirstChar, unsigned int nLastChar, float* lpFloatBuffer) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetCharWidthFloat(m_hdc, nFirstChar, nLastChar, lpFloatBuffer) != false;
   //   return false;

   //}


   void graphics::abort_path()
   {
      //if(m_ppath != nullptr)
      //{
      //   delete m_ppath;
      //   m_ppath = nullptr;
      //}
      //return true;

   }


   void graphics::begin_path()
   {

      /*     if(m_ppath != nullptr)
              delete m_ppath;

           m_ppath = ___new plusplus::GraphicsPath ();
      */
      //      return m_ppath != nullptr;

            //return true;

   }


   void graphics::close_figure()
   {
      //ASSERT(m_ppath != nullptr);
      //return m_ppath->CloseFigure() == plusplus::Status::Ok;
      //return true;

   }


   void graphics::end_path()
   {

      //if(m_ppath == nullptr)
      //   return false;

      //m_ppathPaint   = m_ppath;
      //m_ppath        = nullptr;

      //return true;

   }


   void graphics::fill_path()
   {

      //return m_pgraphics->FillPath(gl2d_brush(), m_ppath) == plusplus::Status::Ok;
      //return true;

   }


   void graphics::flatten_path()
   {
      //      return m_ppath->Flatten() == plusplus::Status::Ok;
            //return true;

   }


   void graphics::stroke_and_fill_path()
   {


   }


   void graphics::stroke_path()
   {


   }


   void graphics::widen_path()
   {


   }


   float graphics::GetMiterLimit()
   {
      // ASSERT(m_hdc != nullptr);
      //float fMiterLimit;
      //VERIFY(::GetMiterLimit(m_hdc, &fMiterLimit));
      //::GetMiterLimit(m_hdc, &fMiterLimit);
      //;;; return fMiterLimit;
      return 0.f;
   }


   //void graphics::GetPath(::f64_point * lpPoints, unsigned char * lpTypes, ::collection::count nCount)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //return ::GetPath(m_hdc, lpPoints, lpTypes, (int) nCount);

   //   ::GetPath(m_hdc, lpPoints, lpTypes, (int)nCount);

   //}


   void graphics::SetMiterLimit(float fMiterLimit)
   {
      // ASSERT(m_hdc != nullptr);
      ///return ::SetMiterLimit(m_hdc, fMiterLimit, nullptr) != false;
      //::SetMiterLimit(m_hdc, fMiterLimit, nullptr);

   }


   //void graphics::StrokeAndFillPath()
   //{

   //   //bool bOk1 = m_pgraphics->FillPath(gl2d_brush(), m_ppathPaint) == plusplus::Status::Ok;

   //   //bool bOk2 = m_pgraphics->DrawPath(gl2d_pen(), m_ppathPaint) == plusplus::Status::Ok;

   //   //return bOk1 && bOk2;

   //   //return true;

   //}


//   void graphics::StrokePath()
//   {
//
////      return m_pgraphics->DrawPath(gl2d_pen(), m_ppathPaint) == plusplus::Status::Ok;
//
//      //return true;
//
//   }


   //void graphics::WidenPath()
   //{

   //   //return m_ppath->Widen(gl2d_pen()) == plusplus::Status::Ok;

   //   //return true;

   //}


   void graphics::draw(::draw2d::path* pdraw2dpath)
   {

      draw(pdraw2dpath, m_pdraw2dpen);
      //m_pgraphics->SetSmoothingMode(plusplus::SmoothingModeAntiAlias);
      //m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);


      //return m_pgraphics->DrawPath(gl2d_pen(),(dynamic_cast < ::draw2d_opengl::path * > (pdraw2dpath))->get_os_path(m_pgraphics)) == plusplus::Status::Ok;
      //return true;

   }


   void graphics::draw(::draw2d::path* pdraw2dpath, ::draw2d::pen* pdraw2dpen)
   {
      //bool bLastPoint = false;
      ::f64_point pointLast;
      for (int i = 0; i < pdraw2dpath->m_itema.size(); i++)
      {
         auto& pitem = pdraw2dpath->m_itema[i];

         auto etype = pitem->type();

         switch (etype)
         {
         case  ::draw2d::e_item_line:
         {

            ::cast< ::geometry2d::line_item> plineitem = pitem;
            ::draw2d::graphics::line(plineitem->m_item.m_p1, plineitem->m_item.m_p2);
            //if (!bLastPoint || !pointLast.is_same_by(0.00001, plineitem->m_item.m_p1))
            //{
            //   glVertex3f(
            //      (float)plineitem->m_item.m_p1.x,
            //      (float)plineitem->m_item.m_p1.y,
            //      0.0f);
            //}
            //glVertex3f(
            //   (float)plineitem->m_item.m_p2.x,
            //   (float)plineitem->m_item.m_p2.y,
            //   0.0f);
            pointLast = plineitem->m_item.m_p2;
         }
            break;
            default:
               break;

         }

      }
      //return m_pgraphics->DrawPath((::plusplus::Pen *) pdraw2dpen->get_os_data(),(dynamic_cast < ::draw2d_opengl::path * > (pdraw2dpath))->get_os_path(m_pgraphics)) == plusplus::Status::Ok;

      //return true;

   }


   void graphics::fill(::draw2d::path* pdraw2dpath)
   {

      ::gpu::graphics::fill(pdraw2dpath);

   }


   void graphics::fill(::draw2d::path* pdraw2dpath, ::draw2d::brush* pdraw2dbrush)
   {

      ::gpu::graphics::fill(pdraw2dpath, pdraw2dbrush);

   }


   //void graphics::AddMetaFileComment(unsigned int nDataSize, const unsigned char* pCommentData)
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GdiComment(m_hdc, nDataSize, pCommentData) != false;
   //   //return false;

   //}


   /*bool CALLBACK metaCallback(
      EmfPlusRecordType recordType,
      unsigned int flags,
      unsigned int dataSize,
      const uchar* pStr,
      void* callbackData)
   {
      // Play only EmfPlusRecordTypeFillEllipse records.
      if (recordType == EmfPlusRecordTypeFillEllipse)
      {
      // Explicitly cast callbackData as a metafile pointer, and use it to call
      // the PlayRecord method.
      static_cast < Metafile* > (callbackData)->PlayRecord(recordType, flags, dataSize, pStr);
      }
      return true;
   }

   VOID Example_EnumerateMetafile9(HDC hdc)
   {
      Graphics graphics(hdc);
      // Create a Metafile object from an existing disk metafile.
      Metafile* pMeta = ___new Metafile(L"SampleMetafile.emf", hdc);
      {
         // Fill a ::f64_rectangle and an ellipse in pMeta.
         Graphics metaGraphics(pMeta);
         metaGraphics.FillRectangle(&SolidBrush(Color(255, 0, 0, 0)), 0, 0, 100, 100);
     metaGraphics.FillEllipse(&SolidBrush(Color(255, 255, 0, 0)), 100, 0, 200, 100);
      }
      // Enumerate pMeta to the destination rectangle, passing pMeta as the callback data.
      graphics.EnumerateMetafile(
      pMeta,
      Rect(0, 0, 300, 50),
      metaCallback,
      pMeta);
      // Draw pMeta as an pimage->
      graphics.DrawImage(pMeta, Point(0, 150));
      delete pMeta;;
   }*/


   //bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, const ::f64_rectangle & rectangleBounds)
   //{

   //   //plusplus::rectF ::f64_rectangle((plusplus::REAL) rectangleBounds.left,(plusplus::REAL) rectangleBounds.top,(plusplus::REAL) width(rectangleBounds),(plusplus::REAL) height(rectangleBounds));

   //   //plusplus::Metafile* pMeta = ___new plusplus::Metafile (hEnhMF, false);

   //   ////m_pgraphcis->EnumerateMetafile(pMeta, rectangle, metaCallback, PMETAHEADER);

   //   //bool bOk = m_pgraphics->DrawImage(pMeta, rectangle) == plusplus::Status::Ok;

   //   //delete pMeta;

   //   //return bOk ? true : false;
   //   //return ::PlayEnhMetaFile(m_hdc, hEnhMF, lpBounds);

   //   return true;

   //}

   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   // COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

// Thank you
// Jiju George T
// Web Developer
// India India
// Member


//   void graphics::alpha_blend(double xDest, double yDest, double nDestWidth, double nDestHeight, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, double nSrcWidth, double nSrcHeight, double dRate)
//   {
//
////      if (m_pgraphics == nullptr)
////         return false;
////
////      if(m_pimageAlphaBlend->is_set())
////      {
////
////
////         ::f64_rectangle rectangleIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());
////
////
////         ::image::image_pointer pimageWork = nullptr;
////         ::image::image_pointer pimageWork2 = nullptr;
//////         ::image::image_pointer pimageWork3 = nullptr;
////         ::image::image_pointer pimageWork4 = nullptr;
////
////
////         ::i32_point pointSrc(xSrc, ySrc);
////         ::i32_point ptDest(xDest, yDest);
////         ::i32_size size(nDestWidth, nDestHeight);
////
////
////
////         ::image::image_pointer pimage;
////         if(imageWork == nullptr)
////         {
////            pimage->create(this);
////            imageWork = pimage;
////         }
////         if(imageWork == nullptr)
////            return false;
////         if(!imageWork = create_image(size))
////            return false;
////         if(!imageWork.from(::i32_point(), pgraphicsSrc, pointSrc, size))
////            return false;
////
////
////
////
////         ::image::image_pointer pimage2;
////         if(imageWork2 == nullptr)
////         {
////            pimage2->create(this);
////            imageWork2 = pimage2;
////         }
////
////
////         ::image::image_pointer pimage4;
////         if(imageWork4 == nullptr)
////         {
////            image4.create(this);
////            imageWork4 = image4;
////         }
////         if(imageWork4 == nullptr)
////            return false;
////         if(!imageWork4 = create_image(size))
////            return false;
////
////
////         imageWork4.Fill(255, 0, 0, 0);
////
////         imageWork4.from(i32_point(maximum(0, m_pointAlphaBlend.x - xDest), maximum(0, m_pointAlphaBlend.y - yDest)),
////                         m_pimageAlphaBlend->get_graphics(), i32_point(maximum(0, xDest - m_pointAlphaBlend.x), maximum(0, yDest - m_pointAlphaBlend.y)), size);
////
////         imageWork.channel_multiply(::color::e_channel_opacity, imageWork4);
////
////
////         keep < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);
////
////
////         return BitBlt(ptDest.x, ptDest.y, size.cx, size.cy, imageWork.get_graphics(), pointSrc.x, pointSrc.y);
////
////
////      }
////
////
////      float fA = (float) dRate;
////
////      plusplus::ColorMatrix matrix = {
////         1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
////         0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
////         0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
////         0.0f, 0.0f, 0.0f, fA  , 0.0f,
////         0.0f, 0.0f, 0.0f, 0.0f, 1.0f
////      };
////
////      plusplus::ImageAttributes attributes;
////
////      attributes.SetColorMatrix(&matrix, plusplus::ColorMatrixFlagsDefault, plusplus::ColorAdjustTypeBitmap);
////
////      plusplus::rectF dstRect((plusplus::REAL) xDest, (plusplus::REAL) yDest, (plusplus::REAL) nDestWidth, (plusplus::REAL) nDestHeight);
////
////      if(pgraphicsSrc == nullptr)
////         return false;
////
////      if(pgraphicsSrc->get_current_bitmap() == nullptr)
////         return false;
////
////      plusplus::Bitmap * pdraw2dbitmap = nullptr;
////
////      try
////      {
////
////         pdraw2dbitmap = (plusplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data();
////
////      }
////      catch(...)
////      {
////      }
////
////      if(pdraw2dbitmap != nullptr)
////      {
////
////         m_pgraphics->DrawImage(pdraw2dbitmap,dstRect,(plusplus::REAL) xSrc,(plusplus::REAL) ySrc,(plusplus::REAL) nSrcWidth,(plusplus::REAL) nSrcHeight,plusplus::UnitPixel,&attributes);
////
////      }
////
//      //return true;
//
//   }


   /*bool graphics::alpha_blend(double xDest, double yDest, double nDestWidth, double nDestHeight,
      ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, double nSrcWidth, double nSrcHeight, BLENDFUNCTION blend)
   {

      throw ::interface_only();
      //if(m_hdc == nullptr)
        // return false;


      if(m_pimageAlphaBlend->is_set())
      {


         ::f64_rectangle rectangleIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());


         ::image::image_pointer pimageWork = nullptr;
         ::image::image_pointer pimageWork2 = nullptr;
   //         ::image::image_pointer pimageWork3 = nullptr;
         ::image::image_pointer pimageWork4 = nullptr;


         ::i32_point pointSrc(xSrc, ySrc);
         ::i32_point ptDest(xDest, yDest);
         ::i32_size size(nDestWidth, nDestHeight);



         ::image::image_pointer pimage;
         if(imageWork == nullptr)
         {
            pimage->create(this);
            imageWork = pimage;
         }
         if(imageWork == nullptr)
            return false;
         if(!imageWork = create_image(size))
            return false;
         if(!imageWork.from(::i32_point(), pgraphicsSrc, pointSrc, size))
            return false;




         ::image::image_pointer pimage2;
         if(imageWork2 == nullptr)
         {
            pimage2->create(this);
            imageWork2 = pimage2;
         }


         ::image::image_pointer pimage4;
         if(imageWork4 == nullptr)
         {
            image4.create(this);
            imageWork4 = image4;
         }
         if(imageWork4 == nullptr)
            return false;
         if(!imageWork4 = create_image(size))
            return false;


         imageWork4.Fill(255, 0, 0, 0);

         imageWork4.from(i32_point(maximum(0, m_pointAlphaBlend.x - xDest), maximum(0, m_pointAlphaBlend.y - yDest)),
            m_pimageAlphaBlend->get_graphics(), i32_point(maximum(0, xDest - m_pointAlphaBlend.x), maximum(0, yDest - m_pointAlphaBlend.y)), size);

         imageWork.channel_multiply(::color::e_channel_opacity, imageWork4);


         keep < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);


         return psystem->imaging().true_blend(this, ptDest, size, imageWork.get_graphics(), pointSrc);


      }

      return ::AlphaBlend(m_hdc, xDest, yDest,
         nDestWidth, nDestHeight, GL2D_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,
         nSrcHeight, blend) != false;
   }*/


   //bool graphics::TransparentBlt(double xDest, double yDest, double nDestWidth, double nDestHeight, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, double nSrcWidth, double nSrcHeight, unsigned int crTransparent)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //return ::TransparentBlt(m_hdc, xDest, yDest,  nDestWidth, nDestHeight, GL2D_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,  nSrcHeight, crTransparent) != false;

   //   return true;

   //}


   //bool graphics::GradientFill(TRIVERTEX* pVertices, ULONG nVertices, void * pMesh, ULONG nMeshElements, unsigned int dwMode)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //return ::GradientFill(m_hdc, pVertices, nVertices, pMesh, nMeshElements, dwMode) != false;

   //   return true;

   //}

   // This is aura API library.
   //
   //
   //
   //
   //
   //
   //
   //

   // // Always Inline. Functions only in Win98/Win2K or later
   //
   // inline color32_t graphics::GetDCBrushColor() const
   // {
   //    // ASSERT(m_hdc != nullptr);
   //    //return ::GetDCBrushColor(m_hdc);
   //    return color::transparent;
   // }
   //
   //
   // inline color32_t graphics::SetDCBrushColor(color32_t crColor)
   // {
   //    // ASSERT(m_hdc != nullptr);
   //    //return ::SetDCBrushColor(m_hdc, crColor);
   //    return color::transparent;
   //
   // }
   //
   //
   // inline color32_t graphics::GetDCPenColor() const
   // {
   //    // ASSERT(m_hdc != nullptr);
   //    //return ::GetDCPenColor(m_hdc);
   //    return color::transparent;
   //
   //
   // }
   //
   //
   // inline color32_t graphics::SetDCPenColor(color32_t crColor)
   // {
   //    // ASSERT(m_hdc != nullptr);
   //    //return ::SetDCPenColor(m_hdc, crColor);
   //    return color::transparent;
   //
   // }
   //
   //
   // inline bool graphics::GetCharABCWidthsI(unsigned int giFirst, unsigned int cgi, LPWORD pgi, LPABC lpabc) const
   // {
   //    // ASSERT(m_hdc != nullptr);
   //    //return ::GetCharABCWidthsI(m_hdc, giFirst, cgi, pgi, lpabc) != false;
   //    return false;
   //
   // }
   //
   //
   // inline bool graphics::GetCharWidthI(unsigned int giFirst, unsigned int cgi, LPWORD pgi, LPINT lpBuffer) const
   // {
   //    // ASSERT(m_hdc != nullptr);
   //    //return ::GetCharWidthI(m_hdc, giFirst, cgi, pgi, lpBuffer) != false;
   //    return false;
   //
   // }


   //inline bool graphics::GetTextExtentExPointI(LPWORD pgiIn, double cgi, double nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE32 LPSIZE32) const
   //{
   //   ENSURE(LPSIZE32 != nullptr);
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetTextExtentExPointI(m_hdc, pgiIn, cgi, nMaxExtent, lpnFit, alpDx, LPSIZE32) != false;
   //   return false;

   //}


   //inline bool graphics::GetTextExtentPointI(LPWORD pgiIn, double cgi, LPSIZE32 LPSIZE32) const
   //{
   //   ENSURE(LPSIZE32 != nullptr);
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetTextExtentPointI(m_hdc, pgiIn, cgi, LPSIZE32) != false;
   //   return false;

   //}


#define HIMETRIC_INCH   2540    // HIMETRIC units per inch

   void graphics::DPtoHIMETRIC(::f64_size* psize)
   {
      //      ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::i32_size)));
      //
      //      double nMapMode;
      //      if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
      //            nMapMode != MM_TEXT)
      //      {
      //         // when using a constrained map mode, map against physical inch
      //         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
      //         DPtoLP(LPSIZE32);
      //         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
      //      }
      //      else
      //      {
      //         
      //         double cxPerInch, cyPerInch;
      //         if (this != nullptr)
      //         {
      //            ASSERT_VALID(this);
      //            // ASSERT(m_hdc != nullptr);  // no HDC attached or created?
      //            cxPerInch = GetDeviceCaps(LOGPIXELSX);
      //            cyPerInch = GetDeviceCaps(LOGPIXELSY);
      //         }
      //         else
      //         {

      //         }
      //         ASSERT(cxPerInch != 0 && cyPerInch != 0);
      //         LPSIZE32->cx = MulDiv(LPSIZE32->cx, HIMETRIC_INCH, cxPerInch);
      //         LPSIZE32->cy = MulDiv(LPSIZE32->cy, HIMETRIC_INCH, cyPerInch);
      //      }
   }


   void graphics::HIMETRICtoDP(::f64_size* psize)
   {
      //      ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::i32_size)));
      //
      //      double nMapMode;
      //      if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
      //            nMapMode != MM_TEXT)
      //      {
      //         // when using a constrained map mode, map against physical inch
      //         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
      //         LPtoDP(LPSIZE32);
      //         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
      //      }
      //      else
      //      {
      //         
      //         double cxPerInch, cyPerInch;
      //         if (this != nullptr)
      //         {
      //            ASSERT_VALID(this);
      //            // ASSERT(m_hdc != nullptr);  // no HDC attached or created?
      //            cxPerInch = GetDeviceCaps(LOGPIXELSX);
      //            cyPerInch = GetDeviceCaps(LOGPIXELSY);
      //         }
      //         else
      //         {

      //         }
      //         ASSERT(cxPerInch != 0 && cyPerInch != 0);
      //         LPSIZE32->cx = MulDiv(LPSIZE32->cx, cxPerInch, HIMETRIC_INCH);
      //         LPSIZE32->cy = MulDiv(LPSIZE32->cy, cyPerInch, HIMETRIC_INCH);
      //      }
   }


   void graphics::LPtoHIMETRIC(::f64_size* psize)
   {
      //ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::i32_size)));

      //LPtoDP(LPSIZE32);
      //DPtoHIMETRIC(LPSIZE32);
   }


   void graphics::HIMETRICtoLP(::f64_size* psize)
   {
      //ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::i32_size)));

      //HIMETRICtoDP(LPSIZE32);
      //DPtoLP(LPSIZE32);

   }

//    /////////////////////////////////////////////////////////////////////////////
//    // special graphics drawing primitives/helpers
//
//    ::draw2d::brush* graphics::GetHalftoneBrush()
//    {
//       /*      ::aura::LockGlobals(CRIT_HALFTONEBRUSH);
//             if (gen_HalftoneBrush == nullptr)
//             {
//                unsigned short grayPattern[8];
//                for (double i = 0; i < 8; i++)
//                   grayPattern[i] = (unsigned short)(0x5555 << (i & 1));
//                HBITMAP grayBitmap = CreateBitmap(8, 8, 1, 1, grayPattern);
//                if (grayBitmap != nullptr)
//                {
//                   gen_HalftoneBrush = ::CreatePatternBrush(grayBitmap);
//                   ::DeleteObject(grayBitmap);
//                }
//             }
//             if (!gen_WingdixTerm)
//                gen_WingdixTerm = (char)!atexit(&__win_gdi_x_term);
//             ::aura::UnlockGlobals(CRIT_HALFTONEBRUSH);
//
//       //      return ::draw2d_opengl::brush::from_handle(papp, gen_HalftoneBrush);*/
//       return nullptr;
//    }


   //void graphics::DrawDragRect(const ::f64_rectangle & rectangle, const ::i32_size & size, const ::f64_rectangle & lpRectLast, const ::i32_size & sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
   //{

   //   //throw ::interface_only();

   //   /*

   //         ASSERT(is_memory_segment_ok(rectangle, sizeof(::f64_rectangle), false));
   //         ASSERT(lpRectLast == nullptr ||
   //            is_memory_segment_ok(lpRectLast, sizeof(::f64_rectangle), false));

   //         // first, determine the update region and select it
   //         ::draw2d::region rgnNew;
   //         ::draw2d::region rgnOutside, rgnInside;
   //         rgnOutside.create_rect(rectangle);
   //         const ::f64_rectangle & rectangle = *rectangle;
   //         rectangle.inflate(-size.cx, -size.cy);
   //         rectangle.intersect(rectangle, rectangle);
   //         rgnInside.create_rect(rectangle);
   //         rgnNew.create_rect(0, 0, 0, 0);
   //         rgnNew.combine(&rgnOutside, &rgnInside, RGN_XOR);

   //         ::draw2d::brush* pBrushOld = nullptr;
   //         if (pBrush == nullptr)
   //         {
   //            pBrush = graphics::GetHalftoneBrush(this);
   //         }

   //         ENSURE(pBrush);

   //         if (pBrushLast == nullptr)
   //         {
   //            pBrushLast = pBrush;
   //         }

   //         ::draw2d::region rgnLast, rgnUpdate;
   //         if (lpRectLast != nullptr)
   //         {
   //            // find difference between ___new region and old region
   //            rgnLast.create_rect(0, 0, 0, 0);
   //            rgnOutside.SetRectRgn(lpRectLast);
   //            rectangle = *lpRectLast;
   //            rectangle.inflate(-sizeLast.cx, -sizeLast.cy);
   //            rectangle.intersect(rectangle, lpRectLast);
   //            rgnInside.SetRectRgn(rectangle);
   //            rgnLast.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

   //            // only diff them if brushes are the same
   //            if (pBrush->get_os_data() == pBrushLast->get_os_data())
   //            {
   //               rgnUpdate.create_rect(0, 0, 0, 0);
   //               rgnUpdate.CombineRgn(&rgnLast, &rgnNew, RGN_XOR);
   //            }
   //         }
   //         if (pBrush->get_os_data() != pBrushLast->get_os_data() && lpRectLast != nullptr)
   //         {
   //            // brushes are different -- erase old region first
   //            SelectClipRgn(&rgnLast);
   //            get_clip_box(&rectangle);
   //            pBrushOld = SelectObject(pBrushLast);
   //            PatBlt(rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), PATINVERT);
   //            SelectObject(pBrushOld);
   //            pBrushOld = nullptr;
   //         }

   //         // draw into the update/___new region
   //         SelectClipRgn(rgnUpdate.get_os_data() != nullptr ? &rgnUpdate : &rgnNew);
   //         get_clip_box(&rectangle);
   //         pBrushOld = SelectObject(pBrush);
   //         PatBlt(rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), PATINVERT);

   //         // cleanup DC
   //         if (pBrushOld != nullptr)
   //            SelectObject(pBrushOld);
   //         SelectClipRgn(nullptr);

   //   */
   //}

   /*void graphics::FillSolidRect(const ::f64_rectangle & rectangle, color32_t clr)
   {
      ::SetBkColor(m_hdc, clr);
      ::ExtTextOut(m_hdc, 0, 0, ETO_OPAQUE, rectangle, nullptr, 0, nullptr);
   }*/

   /*void graphics::fill_rectangle(const f64_rectangle & rectangle, color32_t clr)
   {
      ::f64_rectangle rect32;
      copy(rect32, rectangle);
      FillSolidRect(rect32, clr);
   }
*/

/*

void graphics::FillSolidRect(double x, double y, double cx, double cy, color32_t clr)
{
   ::SetBkColor(m_hdc, clr);
   ::f64_rectangle rectangle(x, y, x + cx, y + cy);
   ::ExtTextOut(m_hdc, 0, 0, ETO_OPAQUE, &rectangle, nullptr, 0, nullptr);
}

*/


//void graphics::draw_inset_3d_rectangle(const ::f64_rectangle & rectangleParam,
//                          const ::color::color & clrTopLeft, const ::color::color & clrBottomRight,
//   const ::e_border & eborder)
//{

//   //draw3d_rectangle(rectangleParam.left, rectangleParam.top, rectangleParam.right - rectangleParam.left,
//     //         rectangleParam.bottom - rectangleParam.top, clrTopLeft, clrBottomRight);

//}

//
//void graphics::draw_inset_rectangle(const ::f64_rectangle & rectangle, const ::color::color & color, const ::e_border & eborder)
//{


//}


//void graphics::Draw3dRect(double x, double y, double cx, double cy,
//                          color32_t clrTopLeft, color32_t clrBottomRight)
//{
//   fill_solid_rect_coord(x, y, cx - 1, 1, clrTopLeft);
//   fill_solid_rect_coord(x, y, 1, cy - 1, clrTopLeft);
//   fill_solid_rect_coord(x + cx - 1, y, 1, cy, clrBottomRight);
//   fill_solid_rect_coord(x, y + cy - 1, cx, 1, clrBottomRight);
//}





//::draw2d::graphics * ::draw2d_opengl::graphics::from_handle(HDC hDC)
//{
//hdc_map* pMap = ::windows_definition::MapHDC(true); //create map if not exist
//ASSERT(pMap != nullptr);
//      ::draw2d::graphics * pdraw2dgraphics = (::draw2d::graphics *)pMap->from_handle(hDC);
   //    ASSERT(pdraw2dgraphics == nullptr || (dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->m_hdc == hDC);
   //  return pdraw2dgraphics;
   // return nullptr;
   //}

   //bool graphics::Attach(HDC hdc)
   //{

   //   //if(hdc == nullptr)
   //   //   return false;

   //   //if(m_hdc == hdc)
   //   //{

   //   //   if(m_pgraphics != nullptr)
   //   //      return true;

   //   //}

   //   //if(hdc != nullptr)
   //   //{

   //   //   m_pgraphics = allocateø< ::plusplus::Graphics( >(HDC) hdc);

   //   //   m_pgraphics->SetPageUnit(plusplus::UnitPixel);

   //   //   set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

   //   //   m_hdc = (HDC) hdc;

   //   //}

   //   //return m_pgraphics != nullptr;

   //   return true;

   //   /*ASSERT(m_hdc == nullptr);      // only attach once, detach on destroy
   //   ASSERT(m_hdc == nullptr);    // only attach to an is_empty DC

   //   if (hDC == nullptr)
   //   {
   //      return false;
   //   }
   //   // remember early to avoid leak
   //   set_handle1(hDC);
   //   hdc_map* pMap = ::windows_definition::MapHDC(true); // create map if not exist
   //   ASSERT(pMap != nullptr);
   //   pMap->set_permanent(m_hdc, this);

   //   SetAttribDC(m_hdc);     // Default to same as output
   //   return true;*/
   //}


   //HDC graphics::Detach()
   //{

   //   //if(m_hdc == nullptr)
   //   //   return nullptr;

   //   //if(m_pgraphics == nullptr)
   //   //   return nullptr;

   //   //try
   //   //{

   //   //   delete m_pgraphics;

   //   //}
   //   //catch(...)
   //   //{

   //   //   informationf("graphics::Detach : Failed to delete plusplus::Graphics");

   //   //}

   //   //m_pgraphics = nullptr;

   //   //HDC hdc = m_hdc;
   //   //m_hdc = nullptr;

   //   //return hdc;

   //   return nullptr;

   //}


   //bool graphics::AttachPrinter(HDC hdc)
   //{

   //   //if (hdc == nullptr)
   //   //   return false;

   //   //if (m_hdc == hdc)
   //   //{

   //   //   return true;

   //   //}

   //   //if (hdc != nullptr)
   //   //{

   //   //   m_hdc = (HDC)hdc;

   //   //}

   //   //return m_hdc != nullptr;

   //   return true;

   //}


   //HDC graphics::DetachPrinter()
   //{

   //   //if (m_hdc == nullptr)
   //   //   return nullptr;

   //   //HDC hdc = m_hdc;

   //   //m_hdc = nullptr;

   //   //return hdc;

   //   return nullptr;

   //}


   void graphics::DeleteDC()
   {



      //HDC hdc = Detach();

      //if(hdc != nullptr)
      //{

      //   bool bDeleted = ::DeleteDC(hdc) != false;

      //   if(!bDeleted)
      //   {

      //      informationf("graphics::DeleteDC : Failed to delete GDI device context");

      //   }

      //}

      //if(m_pgraphics != nullptr)
      //{

      //   try
      //   {

      //      delete m_pgraphics;

      //   }
      //   catch(...)
      //   {

      //      informationf("graphics::DeleteDC : Failed to delete plusplus::Graphics");

      //   }

      //   m_pgraphics = nullptr;

      //}

      //if(m_ppath != nullptr)
      //{

      //   try
      //   {

      //      delete m_ppath;

      //   }
      //   catch(...)
      //   {

      //   }

      //   m_ppath = nullptr;

      //}

      //if(m_ppathPaint != nullptr)
      //{

      //   try
      //   {

      //      delete m_ppathPaint;

      //   }
      //   catch(...)
      //   {

      //   }

      //   m_ppathPaint = nullptr;

      //}

      //if (m_hdc != nullptr)
      //{

      //   //::ReleaseDC(m_hwnd, m_hdc);

      //}

      //return true;

   }


   //   void graphics::SetAttribDC(HDC hDC)  // set the Attribute DC
   //   {
   ////      set_handle2(hDC);
   //   }
   //
   //
   //   void graphics::SetOutputDC(HDC hDC)  // set the Output DC
   //   {
   //#ifdef _DEBUG
   //      /*      hdc_map* pMap = ::windows_definition::MapHDC();
   //            if (pMap != nullptr && pMap->lookup_permanent(m_hdc) == this)
   //            {
   //               information(trace_category_appmsg, 0, "Cannot set Output hDC on Attached graphics.\n");
   //               ASSERT(false);
   //            }*/
   //#endif
   //      //    set_handle1(hDC);
   //   }
   //
   //
   //   void graphics::ReleaseAttribDC()     // Release the Attribute DC
   //   {
   ////      set_handle2(nullptr);
   //   }
   //
   //
   //   void graphics::ReleaseOutputDC()     // Release the Output DC
   //   {
   //#ifdef _DEBUG
   //      /*      hdc_map* pMap = ::windows_definition::MapHDC();
   //            if (pMap != nullptr && pMap->lookup_permanent(m_hdc) == this)
   //            {
   //               information(trace_category_appmsg, 0, "Cannot Release Output hDC on Attached graphics.\n");
   //               ASSERT(false);
   //            }*/
   //#endif
   //      //set_handle1(nullptr);
   //   }

   //    /////////////////////////////////////////////////////////////////////////////
   //    // Out-of-line routines
   //
   // int graphics::StartDoc(const ::scoped_string& lpszDocName)
   // {
   //    //DOCINFO di;
   //    //memory_set(&di, 0, sizeof(DOCINFO));
   //    //di.cbSize = sizeof(DOCINFO);
   //    //di.lpszDocName = lpszDocName;
   //    //return StartDoc(&di);
   //    return -1;
   // }


   int graphics::save_graphics_context()
   {
      //      return m_pgraphics->Save();
      return 0;

   }


   void graphics::restore_graphics_context(int iSavedContext)
   {

      //return m_pgraphics->Restore(nSavedDC) != false;
      //return true;

   }

   //   ::draw2d::object* graphics::SelectGdiObject(::particle * pparticle, HDC hDC, HGDIOBJ h)
      // {
   //      return ::draw2d_opengl::object::from_handle(papp, ::SelectObject(hDC, h));
      //}
   ::draw2d_opengl::draw2d* graphics::draw2d_opengl()
   {

      return dynamic_cast <::draw2d_opengl::draw2d*>(system()->draw2d());

   }

   ::draw2d::object* graphics::SelectStockObject(int nIndex)
   {
      /*      HGDIOBJ hObject = ::GetStockObject(nIndex);
            HGDIOBJ hOldObj = nullptr;
            ASSERT(hObject != nullptr);
            if(m_hdc != nullptr && m_hdc != m_hdc)
               hOldObj = ::SelectObject(m_hdc, hObject);
            if(m_hdc != nullptr)
               hOldObj = ::SelectObject(m_hdc, hObject);
            return ::draw2d_opengl::object::from_handle(get_app(), hOldObj);*/

      return nullptr;

   }


   ::draw2d::pen* graphics::SelectObject(::draw2d::pen* pPen)
   {
      /*HGDIOBJ hOldObj = nullptr;
      if(pPen == nullptr)
         return nullptr;
      if(m_hdc != nullptr && m_hdc != m_hdc)
         hOldObj = ::SelectObject(m_hdc, pPen->get_os_data());
      if(m_hdc != nullptr)
         hOldObj = ::SelectObject(m_hdc, pPen->get_os_data());
      return dynamic_cast < pen * > (::draw2d_opengl::object::from_handle(get_app(), hOldObj));*/
      m_pdraw2dpen = pPen;
      return m_pdraw2dpen;

   }


   ::draw2d::brush* graphics::SelectObject(::draw2d::brush* pBrush)
   {
      /*      HGDIOBJ hOldObj = nullptr;
            if(pBrush == nullptr)
               return nullptr;
            if(m_hdc != nullptr && m_hdc != m_hdc)
               hOldObj = ::SelectObject(m_hdc, pBrush->get_os_data());
            if(m_hdc != nullptr)
               hOldObj = ::SelectObject(m_hdc, pBrush->get_os_data());
            return dynamic_cast < ::draw2d::brush * > (::draw2d_opengl::object::from_handle(get_app(), hOldObj));*/
      m_pdraw2dbrush = pBrush;

      return m_pdraw2dbrush;

   }


   ::write_text::font* graphics::SelectObject(::write_text::font* pwritetextfont)
   {
      /*      HGDIOBJ hOldObj = nullptr;
            if(pFont == nullptr)
               return nullptr;
            if(m_hdc != nullptr && m_hdc != m_hdc)
               hOldObj = ::SelectObject(m_hdc, pFont->get_os_data());
            if(m_hdc != nullptr)
               hOldObj = ::SelectObject(m_hdc, pFont->get_os_data());
            return dynamic_cast < ::write_text::font * > (::draw2d_opengl::object::from_handle(get_app(), hOldObj));*/

            /*ASSERT(pFont != nullptr);

            if(pFont == nullptr)
               return nullptr;

            m_fontxyz = *pFont;
            return &m_fontxyz;*/

            //if(!set(pwritetextfont))
              // return nullptr;

      set(pwritetextfont);

      return m_pwritetextfont;

   }


   int graphics::SelectObject(::draw2d::region* pRgn)
   {
      //int nRetVal = GDI_ERROR;
      int nRetVal = 1;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = (double)(iptr)::SelectObject(m_hdc, (HGDIOBJ) pRgn->get_os_data());
      //if(m_hdc != nullptr)
      //   nRetVal = (double)(iptr)::SelectObject(m_hdc, (HGDIOBJ) pRgn->get_os_data());
      return nRetVal;

   }


   ::draw2d::palette* graphics::SelectPalette(::draw2d::palette* pPalette, bool bForceBackground)
   {
      return nullptr;
      //      return dynamic_cast < ::draw2d::palette * > (::draw2d_opengl::object::from_handle(get_app(), ::SelectPalette(m_hdc, (HPALETTE)pPalette->get_os_data(), bForceBackground)));
   }


   int graphics::SetPolyFillMode(int nPolyFillMode)
   {
      int nRetVal = 0;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::SetPolyFillMode(m_hdc, nPolyFillMode);
      //if(m_hdc != nullptr)
      //   nRetVal = ::SetPolyFillMode(m_hdc, nPolyFillMode);
      return nRetVal;

   }


   int graphics::SetROP2(int nDrawMode)
   {
      int nRetVal = 0;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::SetROP2(m_hdc, nDrawMode);
      //if(m_hdc != nullptr)
      //   nRetVal = ::SetROP2(m_hdc, nDrawMode);
      return nRetVal;

   }


   int graphics::set_interpolation_mode(int nStretchMode)
   {

      //if(m_pgraphics == nullptr)
      //{

      //   return -1;

      //}

      //if(nStretchMode == 0)
      //{
      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeNearestNeighbor);
      //}
      //else if(nStretchMode == e_interpolation_mode_high_quality_bicubic)
      //{
      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);
      //}
      //else
      //{
      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeLowQuality);
      //}
      //return 1;

      return true;

      /*double nRetVal = 0;
      if(m_hdc != nullptr && m_hdc != m_hdc)
         nRetVal = ::set_interpolation_mode(m_hdc, nStretchMode);
      if(m_hdc != nullptr)
         nRetVal = ::set_interpolation_mode(m_hdc, nStretchMode);
      return nRetVal;*/
   }


   int graphics::SetGraphicsMode(int iMode)
   {

      int nRetVal = 0;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //{
      //   nRetVal = ::SetGraphicsMode(m_hdc, iMode);
      //}
      //if(m_hdc != nullptr)
      //{
      //   nRetVal = ::SetGraphicsMode(m_hdc, iMode);
      //}
      return nRetVal;

   }


   // bool graphics::SetWorldTransform(const XFORM* pXform)
   // {
   //
   //    //plusplus::REAL ::f64_rectangle[6];
   //
   //    //::f64_rectangle[0] = pXform->eDx;
   //    //::f64_rectangle[1] = pXform->eDy;
   //
   //    //::f64_rectangle[2] = pXform->eM11;
   //    //::f64_rectangle[3] = pXform->eM12;
   //    //::f64_rectangle[4] = pXform->eM21;
   //    //::f64_rectangle[5] = pXform->eM22;
   //
   //    //plusplus::Matrix m;
   //
   //    //m.SetElements(::f64_rectangle[2],::f64_rectangle[3],::f64_rectangle[4],::f64_rectangle[5],::f64_rectangle[0],::f64_rectangle[1]);
   //
   //    //m_pgraphics->SetTransform(&m);
   //
   //    return true;
   //
   // }
   //
   //
   // bool graphics::ModifyWorldTransform(const XFORM* pXform, unsigned int iMode)
   // {
   //    bool nRetVal = 0;
   //    //if(m_hdc != nullptr && m_hdc != m_hdc)
   //    //{
   //    //   nRetVal = ::ModifyWorldTransform(m_hdc, pXform, iMode) != false;
   //    //}
   //    //if(m_hdc != nullptr)
   //    //{
   //    //   nRetVal = ::ModifyWorldTransform(m_hdc, pXform, iMode) != false;
   //    //}
   //    return nRetVal;
   //
   // }


   int graphics::SetMapMode(int nMapMode)
   {
      int nRetVal = 0;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::SetMapMode(m_hdc, nMapMode);
      //if(m_hdc != nullptr)
      //   nRetVal = ::SetMapMode(m_hdc, nMapMode);
      return nRetVal;

   }


   void graphics::update_matrix()
   {

      ::gpu::graphics::update_matrix();

   }


   void graphics::_set(const ::geometry2d::matrix& matrix)
   {

      ::gpu::graphics::_set(matrix);

   }


   i32_point graphics::SetWindowOrg(int x, int y)
   {

      ::i32_point point;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   ::SetWindowOrgEx(m_hdc, x, y, &point);
      //if(m_hdc != nullptr)
      //   ::SetWindowOrgEx(m_hdc, x, y, &point);
      return point;

   }


   i32_point graphics::offset_window_org(int nWidth, int nHeight)
   {

      ::i32_point point;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   ::OffsetWindowOrgEx(m_hdc, nWidth, nHeight, &point);
      //if(m_hdc != nullptr)
      //   ::OffsetWindowOrgEx(m_hdc, nWidth, nHeight, &point);
      return point;

   }


   i32_size graphics::set_window_ext(int x, int y)
   {

      i32_size size(0, 0);
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   ::SetWindowExtEx(m_hdc, x, y, &size);
      //if(m_hdc != nullptr)
      //   ::SetWindowExtEx(m_hdc, x, y, &size);
      return size;

   }


   i32_size graphics::scale_window_ext(int xNum, int xDenom, int yNum, int yDenom)
   {

      i32_size size(0, 0);
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   ::ScaleWindowExtEx(m_hdc, xNum, xDenom, yNum, yDenom, &size);
      //if(m_hdc != nullptr)
      //   ::ScaleWindowExtEx(m_hdc, xNum, xDenom, yNum, yDenom, &size);
      return size;

   }


   int graphics::get_clip_box(::f64_rectangle* prectangle) const
   {

      //plusplus::f64_rectangle ::f64_rectangle;

      //m_pgraphics->GetClipBounds(rectangle);

      //rectangle.left = rectangle.X;
      //rectangle.top = rectangle.Y;
      //rectangle.right = rectangle.X + rectangle.Width;
      //rectangle.bottom = rectangle.Y + rectangle.Height;

      return 1;

   }


   int graphics::SelectClipRgn(::draw2d::region* pregion)
   {

      //if(pregion == nullptr)
      //{
      //   m_pgraphics->ResetClip();
      //}
      //else
      //{
      //   m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data());
      //}

      return 0;

      /*      double nRetVal = ERROR;
            if(m_hdc != nullptr && m_hdc != m_hdc)
               nRetVal = ::SelectClipRgn(m_hdc, pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
            if(m_hdc != nullptr)
               nRetVal = ::SelectClipRgn(m_hdc, pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
            return nRetVal;*/
   }


   int graphics::ExcludeClipRect(int x1, int y1, int x2, int y2)
   {

      //double nRetVal = ERROR;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::ExcludeClipRect(m_hdc, x1, y1, x2, y2);
      //if(m_hdc != nullptr)
      //   nRetVal = ::ExcludeClipRect(m_hdc, x1, y1, x2, y2);

      //return nRetVal;

      return 0;

   }


   int graphics::ExcludeClipRect(const ::i32_rectangle& rectangleParam)
   {

      //double nRetVal = ERROR;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::ExcludeClipRect(m_hdc, rectangleParam.left, rectangleParam.top,
      //                               rectangleParam.right, rectangleParam.bottom);
      //if(m_hdc != nullptr)
      //   nRetVal = ::ExcludeClipRect(m_hdc, rectangleParam.left, rectangleParam.top,
      //                               rectangleParam.right, rectangleParam.bottom);

      //return nRetVal;

      return 0;

   }


   int graphics::IntersectClipRect(int x1, int y1, int x2, int y2)
   {

      //double nRetVal = ERROR;

      int nRetVal = 0;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::IntersectClipRect(m_hdc, x1, y1, x2, y2);
      //if(m_hdc != nullptr)
      //   nRetVal = ::IntersectClipRect(m_hdc, x1, y1, x2, y2);

      return nRetVal;

   }


   int graphics::IntersectClipRect(const ::i32_rectangle& rectangleBounds)
   {

      int nRetVal = 0;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::IntersectClipRect(m_hdc,rectangleBounds.left,rectangleBounds.top,rectangleBounds.right,rectangleBounds.bottom);
      //if(m_hdc != nullptr)
      //   nRetVal = ::IntersectClipRect(m_hdc,rectangleBounds.left,rectangleBounds.top,rectangleBounds.right,rectangleBounds.bottom);

      return nRetVal;

   }


   int graphics::OffsetClipRgn(int x, int y)
   {

      int nRetVal = 0;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::OffsetClipRgn(m_hdc, x, y);
      //if(m_hdc != nullptr)
      //   nRetVal = ::OffsetClipRgn(m_hdc, x, y);

      return nRetVal;

   }


   int graphics::OffsetClipRgn(const ::i32_size& size)
   {

      int nRetVal = 0;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::OffsetClipRgn(m_hdc, size.cx, size.cy);
      //if(m_hdc != nullptr)
      //   nRetVal = ::OffsetClipRgn(m_hdc, size.cx, size.cy);

      return nRetVal;

   }


   unsigned int graphics::SetTextAlign(unsigned int nFlags)
   {

      //unsigned int nRetVal = GDI_ERROR;

      unsigned int nRetVal = 1;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   ::SetTextAlign(m_hdc, nFlags);
      //if(m_hdc != nullptr)
      //   nRetVal = ::SetTextAlign(m_hdc, nFlags);

      return nRetVal;

   }


   //int graphics::SetTextJustification(int nBreakExtra, int nBreakCount)
   //{
   // 
   //   double nRetVal = 0;

   //   //if(m_hdc != nullptr && m_hdc != m_hdc)
   //   //   nRetVal = ::SetTextJustification(m_hdc, nBreakExtra, nBreakCount);
   //   //if(m_hdc != nullptr)
   //   //   nRetVal = ::SetTextJustification(m_hdc, nBreakExtra, nBreakCount);

   //   return nRetVal;

   //}


   //double graphics::SetTextCharacterExtra(double nCharExtra)
   //{
   //   
   //   // ASSERT(m_hdc != nullptr);

   //   double nRetVal = 0x8000000;
   //   
   //   //if(m_hdc != nullptr && m_hdc != m_hdc)
   //   //   nRetVal = ::SetTextCharacterExtra(m_hdc, nCharExtra);
   //   //if(m_hdc != nullptr)
   //   //   nRetVal = ::SetTextCharacterExtra(m_hdc, nCharExtra);

   //   return nRetVal;

   //}


   //unsigned int graphics::SetMapperFlags(unsigned int dwFlag)
   //{
   //   
   //   // ASSERT(m_hdc != nullptr);

   //   unsigned int dwRetVal = GDI_ERROR;

   //   //if(m_hdc != nullptr && m_hdc != m_hdc)
   //   //   dwRetVal = ::SetMapperFlags(m_hdc, dwFlag);
   //   //if(m_hdc != nullptr)
   //   //   dwRetVal = ::SetMapperFlags(m_hdc, dwFlag);

   //   return dwRetVal;

   //}


   // typedef unsigned int (CALLBACK* __GDIGETLAYOUTPROC)(HDC);
   // typedef unsigned int (CALLBACK* __GDISETLAYOUTPROC)(HDC, unsigned int);

   unsigned int graphics::GetLayout() const
   {

      // HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
      //
      // ASSERT(hInst != nullptr);
      //
      // /*      unsigned int dwGetLayout = LAYOUT_LTR;
      //       __GDIGETLAYOUTPROC pfn;
      //       pfn = (__GDIGETLAYOUTPROC) GetProcAddress(hInst, "GetLayout");
      //       // if they API is available, just call it. If it is not
      //       // available, indicate an error.
      //       if (pfn != nullptr)
      //          dwGetLayout = (*pfn)(m_hdc);
      //       else
      //       {
      //          dwGetLayout = GDI_ERROR;
      //          set_last_error(ERROR_CALL_NOT_IMPLEMENTED);
      //       }*/
      //
      //       //return dwGetLayout;

      return 0;

   }


   unsigned int graphics::SetLayout(unsigned int dwSetLayout)
   {
      /*HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
      ASSERT(hInst != nullptr);
      unsigned int dwGetLayout = LAYOUT_LTR;
      __GDISETLAYOUTPROC pfn;
      pfn = (__GDISETLAYOUTPROC) GetProcAddress(hInst, "SetLayout");
      // If the API is availalbe, just call it. If it's not available,
      // setting anything other than LAYOUT_LTR is an error.
      if (pfn != nullptr)
         dwGetLayout = (*pfn)(m_hdc, dwSetLayout);
      else if (dwSetLayout != LAYOUT_LTR)
      {
         dwGetLayout = GDI_ERROR;
         set_last_error(ERROR_CALL_NOT_IMPLEMENTED);
      }
      return dwGetLayout;*/

      return 0;

   }
   /*
   void window::screen_to_client(::f64_rectangle * prectangle)
   {
   ASSERT(::IsWindow(m_hdc));
   ::screen_to_client(m_hdc, (::f64_point *)::f64_rectangle);
   ::screen_to_client(m_hdc, ((::f64_point *)::f64_rectangle)+1);
   if (GetExStyle() & WS_EX_LAYOUTRTL)
   ::f64_rectangle::swap_left_right(rectangle);
   }

   void window::client_to_screen(::f64_rectangle * prectangle)
   {
   ASSERT(::IsWindow(m_hdc));
   ::client_to_screen(m_hdc, (::f64_point *)::f64_rectangle);
   ::client_to_screen(m_hdc, ((::f64_point *)::f64_rectangle)+1);
   if (GetExStyle() & WS_EX_LAYOUTRTL)
   ::f64_rectangle::swap_left_right(rectangle);
   }*/


   /////////////////////////////////////////////////////////////////////////////
   // Advanced Win32 GDI functions

   void graphics::arc_to(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   {
      // ASSERT(m_hdc != nullptr);
      //bool bResult = false;
      //bool bResult = ::ArcTo(m_hdc, x1, y1, x2, y2, x3, y3, x4, y4) != false;
      //if (m_hdc != m_hdc)
      //{
      //   ::i32_point point;
      //   VERIFY(::GetCurrentPositionEx(m_hdc, &point));
      //   VERIFY(::MoveToEx(m_hdc, point.x, point.y, nullptr));
      //}
      //return bResult;
   }


   //double graphics::SetArcDirection(double nArcDirection)
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   double nResult = 0;
   //   //if (m_hdc != m_hdc)
   //   //   nResult = ::SetArcDirection(m_hdc, nArcDirection);
   //   //if (m_hdc != nullptr)
   //   //   nResult = ::SetArcDirection(m_hdc, nArcDirection);
   //   return nResult;
   //}

   //bool graphics::PolyDraw(const ::f64_point* lpPoints, const unsigned char* lpTypes, ::collection::count nCount)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   bool bResult = false;
   //   //bool bResult = ::PolyDraw(m_hdc, lpPoints, lpTypes, (int) nCount) != false;

   //   //if (m_hdc != m_hdc)
   //   //{
   //   //   ::i32_point point;
   //   //   VERIFY(::GetCurrentPositionEx(m_hdc, &point));
   //   //   VERIFY(::MoveToEx(m_hdc, point.x, point.y, nullptr));
   //   //}
   //   return bResult;
   //}

   void graphics::polyline_to(const ::f64_point* lpPoints, ::collection::count nCount)
   {
      // ASSERT(m_hdc != nullptr);
      //bool bResult = false;
      //bool bResult = ::polyline_to(m_hdc, lpPoints, (unsigned int) nCount) != false;
      //if (m_hdc != m_hdc)
      //{
      //   ::i32_point point;
      //   VERIFY(::GetCurrentPositionEx(m_hdc, &point));
      //   VERIFY(::MoveToEx(m_hdc, point.x, point.y, nullptr));
      //}
      //return bResult;
   }


   // bool graphics::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
   // {
   //    // ASSERT(m_hdc != nullptr);
   //    bool bResult = false;
   //    //if (m_hdc != m_hdc)
   //    //   bResult = ::SetColorAdjustment(m_hdc, lpColorAdjust) != false;
   //    //if (m_hdc != nullptr)
   //    //   bResult = ::SetColorAdjustment(m_hdc, lpColorAdjust) != false;
   //    return bResult;
   // }


   void graphics::poly_bezier_to(const ::f64_point* lpPoints, ::collection::count nCount)
   {
      // ASSERT(m_hdc != nullptr);
      //bool bResult = false;      //bool bResult = ::poly_bezier_to(m_hdc, lpPoints, (unsigned int) nCount) != false;
      //if (m_hdc != m_hdc)
      //{
      //   ::i32_point point;
      //   VERIFY(::GetCurrentPositionEx(m_hdc, &point));
      //   VERIFY(::MoveToEx(m_hdc, point.x, point.y, nullptr));
      //}
      //return bResult;
   }


   void graphics::SelectClipPath(int nMode)
   {
      // ASSERT(m_hdc != nullptr);

      //bool bResult = false;

      //// output DC always holds the current path
      //if (!::SelectClipPath(m_hdc, nMode))
      //   return false;

      //// transfer clipping region into the attribute DC
      //bool bResult = true;
      //if (m_hdc != m_hdc)
      //{
      //   HRGN hRgn = ::CreateRectRgn(0, 0, 0, 0);
      //   if (::GetClipRgn(m_hdc, hRgn) < 0 || !::SelectClipRgn(m_hdc, hRgn))
      //   {
      //      INFO(trace_category_appmsg, 0, "Error: unable to transfer clip region in graphics::SelectClipPath!\n");
      //      bResult = false;
      //   }
      //   ::DeleteObject(hRgn);
      //}
      //return bResult;
   }


   int graphics::SelectClipRgn(::draw2d::region* pregion, int nMode)
   {

      //if(pregion == nullptr)
      //{

      //   m_pgraphics->ResetClip();

      //}
      //else
      //{

      //   if(nMode == RGN_AND)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(), plusplus::CombineModeIntersect);

      //   }
      //   else if(nMode == RGN_OR)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(),plusplus::CombineModeUnion);

      //   }
      //   else if(nMode == RGN_XOR)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(),plusplus::CombineModeXor);

      //   }
      //   else if(nMode == RGN_COPY)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(),plusplus::CombineModeReplace);

      //   }
      //   else if(nMode == RGN_DIFF)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(),plusplus::CombineModeExclude);

      //   }

      //}

      return 0;

   }


   // /////////////////////////////////////////////////////////////////////////////
   // // Special handling for metafile playback
   //
   // double CALLBACK __enum_meta_file_procedure(HDC hDC,
   //    HANDLETABLE* pHandleTable, METARECORD* pMetaRec, double nHandles, LPARAM lParam)
   // {
   //    return 1;
   //    //      ::draw2d::graphics * pdraw2dgraphics = (::draw2d::graphics *)lParam;
   //    //      ASSERT_VALID(pdraw2dgraphics);
   //    //
   //    //      switch (pMetaRec->rdFunction)
   //    //      {
   //    //      // these records have effects different for each graphics derived class
   //    //      case META_SETMAPMODE:
   //    //         (dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->SetMapMode((double)(short)pMetaRec->rdParm[0]);
   //    //         break;
   //    //      case META_SETWINDOWEXT:
   //    //         (dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->set_window_ext(
   //    //         (double)(short)pMetaRec->rdParm[1], (double)(short)pMetaRec->rdParm[0]);
   //    //         break;
   //    //      case META_SETWINDOWORG:
   //    //         (dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->SetWindowOrg(
   //    //         (double)(short)pMetaRec->rdParm[1], (double)(short)pMetaRec->rdParm[0]);
   //    //         break;
   //    //      case META_SETVIEWPORTEXT:
   //    //         (dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->set_context_extents(
   //    //         (double)(short)pMetaRec->rdParm[1], (double)(short)pMetaRec->rdParm[0]);
   //    //         break;
   //    //      case META_SETVIEWPORTORG:
   //    //         (dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->set_origin(
   //    //         (double)(short)pMetaRec->rdParm[1], (double)(short)pMetaRec->rdParm[0]);
   //    //         break;
   //    //      case META_SCALEWINDOWEXT:
   //    //         (dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->scale_window_ext(
   //    //         (double)(short)pMetaRec->rdParm[3], (double)(short)pMetaRec->rdParm[2],
   //    //         (double)(short)pMetaRec->rdParm[1], (double)(short)pMetaRec->rdParm[0]);
   //    //         break;
   //    //      case META_SCALEVIEWPORTEXT:
   //    //         (dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->scale_context_extents(
   //    //         (double)(short)pMetaRec->rdParm[3], (double)(short)pMetaRec->rdParm[2],
   //    //         (double)(short)pMetaRec->rdParm[1], (double)(short)pMetaRec->rdParm[0]);
   //    //         break;
   //    //      case META_OFFSETVIEWPORTORG:
   //    //         (dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->offset_origin(
   //    //         (double)(short)pMetaRec->rdParm[1], (double)(short)pMetaRec->rdParm[0]);
   //    //         break;
   //    //      case META_SAVEDC:
   //    //         (dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->SaveDC();
   //    //         break;
   //    //      case META_RESTOREDC:
   //    //         (dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->RestoreDC((double)(short)pMetaRec->rdParm[0]);
   //    //         break;
   //    //      case META_SETBKCOLOR:
   //    //      {
   //    //         auto pdraw2dbrush = createø < ::draw2d::brush >();
   //    //
   //    //         pdraw2dbrush->create_solid(*(UNALIGNED color32_t*)& pMetaRec->rdParm[0]);
   //    //         (dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->SelectObject(brush);
   //    //      }
   //    //      break;
   //    //      case META_SETTEXTCOLOR:
   //    //      {
   //    //         ::draw2d::brush_pointer brush((dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->create_new, this, *(UNALIGNED color32_t*)&pMetaRec->rdParm[0]);
   //    //         (dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->SelectObject(brush);
   //    //      }
   //    //      break;
   //    //
   //    //      // need to watch out for SelectObject(HFONT), for custom font mapping
   //    //      case META_SELECTOBJECT:
   //    //      {
   //    //         HGDIOBJ hObject = pHandleTable->objectHandle[pMetaRec->rdParm[0]];
   //    //         unsigned int nObjType = GetObjectType(hObject);
   //    //         if (nObjType == 0)
   //    //         {
   //    //            // object type is unknown, determine if it is a font
   //    //            HFONT hStockFont = (HFONT)::GetStockObject(SYSTEM_FONT);
   //    //            HFONT hFontOld = (HFONT)::SelectObject((dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->m_hdc, hStockFont);
   //    //            HGDIOBJ hObjOld = ::SelectObject((dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->m_hdc, hObject);
   //    //            if (hObjOld == hStockFont)
   //    //            {
   //    //               // got the stock object back, so must be selecting a font
   //    //               throw ::not_implemented();
   //    ////                  (dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->SelectObject(::draw2d_opengl::font::from_handle(pdraw2dgraphics->get_app(), (HFONT)hObject));
   //    //               break;  // don't play the default record
   //    //            }
   //    //            else
   //    //            {
   //    //               // didn't get the stock object back, so restore everything
   //    //               ::SelectObject((dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->m_hdc, hFontOld);
   //    //               ::SelectObject((dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->m_hdc, hObjOld);
   //    //            }
   //    //            // and fall through to PlayMetaFileRecord...
   //    //         }
   //    //         else if (nObjType == OBJ_FONT)
   //    //         {
   //    //            // play back as graphics::SelectObject(::write_text::font*)
   //    ////               (dynamic_cast<::draw2d_opengl::graphics * >(pdraw2dgraphics))->SelectObject(::draw2d_opengl::font::from_handle(pdraw2dgraphics->get_app(), (HFONT)hObject));
   //    //            throw ::not_implemented();
   //    //            break;  // don't play the default record
   //    //         }
   //    //      }
   //    //      // fall through...
   //    //
   //    //      default:
   //    //         ::PlayMetaFileRecord(hDC, pHandleTable, pMetaRec, nHandles);
   //    //         break;
   //    //      }
   //    //
   //    //      return 1;
   // }


   //bool graphics::PlayMetaFile(HMETAFILE hMF)
   //{
   //   //if (::GetDeviceCaps(m_hdc, TECHNOLOGY) == DT_METAFILE)
   //   //{
   //   //   // playing metafile in metafile, just use aura windows API
   //   //   return ::PlayMetaFile(m_hdc, hMF) != false;
   //   //}

   //   //// for special playback, lParam == pdraw2dgraphics
   //   //return ::EnumMetaFile(m_hdc, hMF, __enum_meta_file_procedure, (LPARAM)this) != false;
   //   return false;

   //}


   /////////////////////////////////////////////////////////////////////////////
   // Coordinate transforms


   void graphics::LPtoDP(::f64_size* LPSIZE32)
   {

      //ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::i32_size)));

      //i32_size sizeWinExt = GetWindowExt();
      //i32_size sizeVpExt = get_context_extents();
      //LPSIZE32->cx = MulDiv(LPSIZE32->cx, abs(sizeVpExt.cx), abs(sizeWinExt.cx));
      //LPSIZE32->cy = MulDiv(LPSIZE32->cy, abs(sizeVpExt.cy), abs(sizeWinExt.cy));

   }


   void graphics::DPtoLP(::f64_size* psize)
   {

      //ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::i32_size)));

      //i32_size sizeWinExt = GetWindowExt();
      //i32_size sizeVpExt = get_context_extents();
      //LPSIZE32->cx = MulDiv(LPSIZE32->cx, abs(sizeWinExt.cx), abs(sizeVpExt.cx));
      //LPSIZE32->cy = MulDiv(LPSIZE32->cy, abs(sizeWinExt.cy), abs(sizeVpExt.cy));

   }


   void graphics::draw_text(const ::scoped_string& str, const ::f64_rectangle& rectangle, const ::e_align& ealign, const ::e_draw_text& edrawtext)
   {

      //::f64_rectangle rectangle;

      //copy(rectangle,&rectangleParam);

      //return draw_text(str, rectangle, ealign, edrawtext);
      text_out(rectangle.left, rectangle.top, str);

   }


   void graphics::draw_text(const ::scoped_string& str, const ::i32_rectangle& rectangle, const ::e_align& ealign, const ::e_draw_text& edrawtext)
   {
      text_out(rectangle.left, rectangle.top, str);
      //try
      //{

      //   if(m_pgraphics == nullptr)
      //      return false;

      //   /*

      //   switch(m_ewritetextrendering)
      //   {
      //   case ::write_text::e_rendering_anti_alias:
      //      m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //      m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintAntiAlias);
      //      break;
      //   case ::write_text::e_rendering_anti_alias_grid_fit:
      //      m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //      m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintAntiAliasGridFit);
      //      break;
      //   case ::write_text::e_rendering_single_bit_per_pixel:
      //      m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //      m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintSingleBitPerPixel);
      //      break;
      //   case ::write_text::e_rendering_clear_type_grid_fit:
      //      m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //      m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintClearTypeGridFit);
      //      break;
      //   }

      //   */
      //   m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //   m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintAntiAlias);


      //}
      //catch(...)
      //{
      //}



      //plusplus::StringFormat format(plusplus::StringFormat::GenericTypographic());


      //format.SetFormatFlags(format.GetFormatFlags()
      //                      | plusplus::StringFormatFlagsNoClip | plusplus::StringFormatFlagsMeasureTrailingSpaces
      //                      | plusplus::StringFormatFlagsLineLimit);

      //if(nFormat & e_align_left)
      //{
      //   format.SetAlignment(plusplus::StringAlignmentNear);
      //}
      //else if(nFormat & e_align_right)
      //{
      //   format.SetAlignment(plusplus::StringAlignmentFar);
      //}
      //else if(nFormat & e_align_horizontal_center)
      //{
      //   format.SetAlignment(plusplus::StringAlignmentCenter);
      //}
      //else
      //{
      //   format.SetAlignment(plusplus::StringAlignmentNear);
      //}

      //if(nFormat & e_align_bottom)
      //{
      //   format.SetLineAlignment(plusplus::StringAlignmentFar);
      //}
      //else if(nFormat & e_align_top)
      //{
      //   format.SetLineAlignment(plusplus::StringAlignmentNear);
      //}
      //else if(nFormat & e_align_vertical_center)
      //{
      //   format.SetLineAlignment(plusplus::StringAlignmentCenter);
      //}
      //else
      //{
      //   format.SetLineAlignment(plusplus::StringAlignmentNear);
      //}

      //plusplus::REAL stops[] = {16,32,48, 64,80,96,112,128};

      //format.SetTabStops(0,8,stops);

      ////m_dFontSize             = pfontSrc.m_dFontSize;

      //plusplus::Matrix m;
      //m_pgraphics->GetTransform(&m);
      //plusplus::Matrix * pmNew = m.Clone();
      //try
      //{


      //   pmNew->Translate((plusplus::REAL) rectangleParam.left,(plusplus::REAL) rectangleParam.top);
      //   pmNew->Scale((plusplus::REAL) m_pwritetextfont->m_dFontWidth,(plusplus::REAL) 1.0,plusplus::MatrixOrderAppend);

      //   plusplus::rectF float_rectangle(0,0,(plusplus::REAL) ((rectangleParam.right - rectangleParam.left) * m_pwritetextfont->m_dFontWidth),(plusplus::REAL) (rectangleParam.bottom - rectangleParam.top));

      //   m_pgraphics->SetTransform(pmNew);

      //   m_pgraphics->DrawString(utf8_to_unicode(str),-1,gl2d_font(),float_rectangle,&format,gl2d_brush());
      //}
      //catch(...)
      //{
      //}

      //m_pgraphics->SetTransform(&m);

      //delete pmNew;

      //return 1;

   }


   //void graphics::draw_text_ex(const ::scoped_string & str, const ::i32_rectangle & rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPDRAWTEXTPARAMS lpDTParams)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   // these flags would modify the string
   //   //ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
   //   //ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
   //   //wstring wstr = utf8_to_unicode(str);
   //   //return ::DrawTextExW(m_hdc,const_cast<wchar_t *>((const wchar_t *)wstr),(double)wcslen(wstr),(::f64_rectangle *) &rectangleParam,nFormat,lpDTParams);
   //   
   //   //return false;

   //}


   //void graphics::draw_text_ex(const ::scoped_string & str,const ::i32_rectangle & rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext,LPDRAWTEXTPARAMS lpDTParams)
   //{

   //   ::draw2d::graphics::draw_text_ex(str,rectangleParam,ealign, edrawtext,lpDTParams);

   //}


   //f64_size graphics::get_text_extent(const ::scoped_string & lpszString, character_count nCount, character_count iIndex)
   f64_size graphics::get_text_extent(const ::scoped_string& scopedstr)
   {

      return ::gpu::graphics::get_text_extent(scopedstr);

      //auto pcontext = gpu_context();

      //::gpu::context_lock contextlock(pcontext);

      ////return{};

      ////if(lpszString.is_empty())
      ////   return i32_size(0, 0);
      //set(m_pwritetextfont);

      //::pointer<font>pwritetextfont = m_pwritetextfont;

      //::cast < draw2d_opengl::draw2d>pdraw2d = draw2d();

      //::pointer <::typeface::face> pface = pdraw2d->get_face(pwritetextfont);

      //if (!pface->m_pgpurenderer)
      //{

      //   pface->initialize_gpu_buffer(pcontext->m_pgpurenderer);

      //}

      //   //glBindVertexArray(pwritetextfont->m_VAO);

      //// iterate through all characters
      //::string strChar;
      //::string str(lpszString);
      //auto psz = str.c_str();
  
      //float x = 0.0f;
      //float y = 0.0f;
      ////glEnable(GL_CULL_FACE);
      ////glEnable(GL_BLEND);
      ////glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      //int xpos = 0;
      //int ypos = 0;
      //while (next_unicode_character(strChar, psz))
      //{

      //   auto & ch = pface->get_character(strChar);

      //   //float xpos = x + ch.Bearing.x * scale;
      //   //float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

      //   float w = ch.Size.x;
      //   float h = ch.Size.y;
      //   y = maximum(h, y);
      //   //// update VBO for each character
      //   // render glyph texture over quad
      //   if (ch.m_ppixmap)
      //   {
      //     /* ::graphics3d::sequence2_uv vertexes[6] = {
      //          {{xpos,     ypos + h},  { 0.0f, 0.0f } },
      //      { {xpos,     ypos    },     {  0.0f, 1.0f }},
      //          {{xpos + w, ypos    },  {     1.0f, 1.0f }},
      //          {{xpos,     ypos + h},  { 0.0f, 0.0f }},
      //          {{xpos + w, ypos    },  {     1.0f, 1.0f }},
      //          {{xpos + w, ypos + h},  { 1.0f, 0.0f }}
      //      };

      //      auto pmodelbuffer = m_poolmodelbufferCharacter.get();

      //      if (pmodelbuffer->is_null())
      //      {

      //         pmodelbuffer->create_vertex_buffer < ::graphics3d::sequence2_uv>(6);

      //      }

      //      pmodelbuffer->sequence2_uv_set_vertex(vertexes, 6)*/

      //         //glBindTexture(GL_TEXTURE_2D, ch.TextureID);
      //      //// update content of VBO memory
      //      //glBindBuffer(GL_ARRAY_BUFFER, pwritetextfont->m_VBO);
      //      //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexes), vertexes); // be sure to use glBufferSubData and not glBufferData

      //      //auto pcommandbuffer = gpu_context()->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_layer());

      //      //pcommandbuffer->

      //      //pcommandbuffer->draw(ch.m_ppixmap);

      //      //ch.m_ppixmap;
      //      //glBindBuffer(GL_ARRAY_BUFFER, 0);
      //      //// render quad
      //      //glDrawArrays(GL_TRIANGLES, 0, 6);
      //      // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
      //      x += ch.Advance; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))

      //   }

      //}

      //return i32_size(x, y);

      ////wstring wstr = lpszString;

      ////character_count iRange = 0;
      ////character_count i = 0;
      ////character_count iLen;
      ////const ::scoped_string & scopedstr = lpszString;
      ////while(i < iIndex)
      ////{
      ////   iLen = ::str::get_utf8_char(psz).length();
      ////   iRange++;
      ////   i += iLen;
      ////   unicode_increment(psz);
      ////   if(psz == nullptr)
      ////      break;
      ////   if(*psz == '\0')
      ////      break;
      ////}

      ////set(m_pwritetextfont);

      ////::pointer<font>pwritetextfont = m_pwritetextfont;

      ////::i32_size s = { 0 };

      ////::GetTextExtentPointW(pwritetextfont->m_hdcFont, wstr, wstr.get_length(), &s);

      ////return s;

   }


   void graphics::line(double x1, double y1, double x2, double y2, ::draw2d::pen * pdraw2dpen)
   {

      ::gpu::graphics::line(x1, y1, x2, y2, pdraw2dpen);

      return;

      //auto pcontext = gpu_context();

      //auto prenderer = pcontext->m_pgpurenderer;

      //::gpu::context_lock contextlock(pcontext);

      ////__USES_TRANSFORM(pcontext);

      //auto pshader = rectangle_shader();

      //float g_z = 0.0f; // Assuming z is 0 for 2D rendering, adjust as needed

      //::f64_point points1[2];

      //points1[0].x = x1;
      //points1[0].y = y1;
      //points1[1].x = x2;
      //points1[1].y = y2;

      //__transform(points1[0]);
      //__transform(points1[1]);

      //auto size = pcontext->size();

      ////::geometry2d::matrix m;
      ////m.translate(0.5, -0.5);
      ////m.scale(2.0 / size.cx, 2.0 / size.cy);
      ////m.translate(-1.0, -1.0);

      //::f64_point_array pointa;

      //::f64_point pointPen(pdraw2dpen->m_dWidth, pdraw2dpen->m_dWidth);

      //::draw2d::make_line_triangles_cap_butt_square(
      //   pointa,
      //   points1[0],
      //   points1[1],
      //   pointPen);
      //
      //context_matrix().transform(pointa);

      //auto color = m_pdraw2dpen->m_color;

      //float fA = color.f32_opacity();
      //float fR = color.f32_red() * fA;
      //float fG = color.f32_green() * fA;
      //float fB = color.f32_blue() * fA;

      //::array<::graphics3d::sequence2_color> quadVertices;
      //for(auto & point : pointa)
      //   quadVertices.add({ {(float)point.x, (float)point.y}, {fR, fG, fB, fA} });

      //auto pmodelbuffer = model_buffer(::draw2d::e_model_line);

      //if (pmodelbuffer->is_new())
      //{

      //   pmodelbuffer->create_vertex_array< ::graphics3d::sequence2_color>(6);

      //}

      //pmodelbuffer->set_vertexes(quadVertices);

      //auto pcommandbuffer = prenderer->getCurrentCommandBuffer2(::gpu::current_layer());

      //pcontext->defer_bind(pshader);

      //pmodelbuffer->bind(pcommandbuffer);

      //pmodelbuffer->draw(pcommandbuffer);

      //pmodelbuffer->unbind(pcommandbuffer);

      //pcontext->defer_unbind(pshader);
 
      //m_point.x = x2;
      //m_point.y = y2;

   }


   void graphics::text_out(double x, double yParam, const ::scoped_string& scopedstr)
   {

      ::gpu::graphics::text_out(x, yParam, scopedstr);

      return;

//      //text_out_2025_06(x, yParam, scopedstr);
//
//      ::gpu::graphics::text_out(x, yParam, scopedstr);
//
//      auto pcontext = gpu_context();
//
//      //__USES_TRANSFORM(pcontext);
//
//      ::gpu::context_lock contextlock(pcontext);
//
//      //return;
//      // activate corresponding render state	
//
//      if (!m_pgpushaderTextOut)
//      {
//
//         auto pvertexshader = R"vertexshader(#version 330 core
//layout(location = 0) in vec2 pos;
//layout(location = 1) in vec2 tex;
//out vec2 TexCoords;
//
//uniform mat4 projection;
//
//void main()
//{
//   gl_Position = projection * vec4(pos, 0.0, 1.0);
//   TexCoords = vec2(tex.x, 1.0 - tex.y);
//}
//)vertexshader";
//
//
//         auto pfragmentshader = R"fragmentshader(#version 330 core
//in vec2 TexCoords;
//out vec4 color;
//
//uniform sampler2D text;
//uniform vec4 textColor;
//
//void main()
//{    
//    vec4 sampled = texture(text, TexCoords).rgba;
//vec4 c = vec4(textColor) * sampled;
//    //color = vec4(sqrt(c.r),sqrt(c.g), sqrt(c.b), sqrt(c.a));
//color = vec4(c.r,c.g, c.b, c.a);
////color = vec4(0.0, 1.0, 0.0, 1.0); // Bright debug color
//}
//)fragmentshader";
//
//         m_pgpushaderTextOut = create_newø < ::gpu_opengl::shader >();
//
//         auto pcontext = gpu_context();
//
//         m_pgpushaderTextOut->m_bEnableBlend = true;
//         m_pgpushaderTextOut->m_bDisableDepthTest = true;
//
//         m_pgpushaderTextOut->initialize_shader_with_block(
//            pcontext->m_pgpurenderer,
//            pvertexshader,
//            pfragmentshader,
//            {},
//            {},
//            {},
//            pcontext->input_layout<::graphics3d::sequence2_uv>()
//            );  
//         
//      }
//
//      pcontext->defer_bind(m_pgpushaderTextOut);
//      auto color = m_pdraw2dbrush->m_color;
//      //shader.use();
//      ::cast<::gpu_opengl::shader>pshader = m_pgpushaderTextOut;
//      pshader->_set_vec4("textColor", { __expand_float_pre_rgba(color) });
//      // glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
//      pshader->_set_int("text", 0);
//      //auto pcontext = gpu_context();
//
//      floating_matrix4 projection = glm::ortho(
//         0.0f, 
//         static_cast<float>(pcontext->width()),
//         static_cast<float>(pcontext->height()),
//         0.0f);
//      pshader->_set_matrix4("projection", projection);
//
//      set(m_pwritetextfont);
//      
//      ::pointer<font>pwritetextfont = m_pwritetextfont;
//      
//      auto pgpuface = get_face(pwritetextfont);
//
//      ::cast < ::typeface::face>pface = pgpuface;
//
//      glActiveTexture(GL_TEXTURE0);
//      ::opengl::check_error("");
//
//      //glEnable(GL_BLEND);
//      //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
//
//      //glDisable(GL_DEPTH_TEST);
//      //glDepthMask(GL_FALSE);
//
//      //glBindVertexArray(pface->m_FaceVAO);
//      //::opengl::check_error("");
//      auto pcommandbuffer = pcontext->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_layer());
//      //pface->m_pmodelbufferBox->bind(pcommandbuffer);
//
//      // iterate through all characters
//      ::string strChar;
//      ::string str(scopedstr);
//      auto psz = str.c_str();
//
//      if (str == "Options")
//      {
//
//         warning() << "draw_text: " << str;
//
//      }
//      //float scale;
//      //if (pwritetextfont->m_fontsize.eunit() == e_unit_point)
//      //{
//      //   scale = pwritetextfont->m_fontsize.as_float() / FONT_POINT_DENOMINATOR;
//      //}
//      //else
//      //{
//      //   scale = pwritetextfont->m_fontsize.as_float() / FONT_PIXEL_DENOMINATOR;
//      //}
//      //auto y = m_pgpucontextCompositor->m_rectangle.height() - yParam - pface->m_iPixelSize;
//      auto y = yParam;
//
//
//      ::i32_point point(x, y);
//      int Δx = 0;
//      __transform(point);
//
//      //auto pcontext = gpu_context();
//
//      point.y = pcontext->height() - point.y - pface->m_iPixelSize;
//
//      glDisable(GL_CULL_FACE);
//      ::opengl::check_error("");
//      //glEnable(GL_BLEND);
//      //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//      while(next_unicode_character(strChar, psz))
//      {
//
//         auto & ch = pface->get_character(strChar);
//         float h2 = (float) (ch.Size.y - ch.Bearing.y);
//         float xpos = (float) (point.x + Δx + ch.Bearing.x);
//         float ypos = (float) (point.y + h2);
//
//         float w = (float) ch.Size.x;
//         float h = (float) ch.Size.y;
//         // update VBO for each character
//         ::array <::graphics3d::sequence2_uv > vertexes = {
//             {{ xpos,     ypos + h},{   0.0f, 0.0f }},
//             {{ xpos,     ypos    },{   0.0f, 1.0f }},
//             {{ xpos + w, ypos    },{   1.0f, 1.0f }},
//             {{ xpos,     ypos + h},{   0.0f, 0.0f }},
//             {{ xpos + w, ypos    },{   1.0f, 1.0f }},
//             {{ xpos + w, ypos + h},{   1.0f, 0.0f }}
//         };
//         // render glyph texture over quad
//         if (ch.m_ppixmap)
//         {
//
//
//            auto pmodelbuffer = model_buffer(::draw2d::e_model_character);
//
//            if (pmodelbuffer->is_new())
//            {
//
//               pmodelbuffer->initialize_gpu_context_object(pcontext);
//
//               pmodelbuffer->create_vertexes < ::graphics3d::sequence2_uv>(6);
//
//               //pmodelbuffer->defer_set_input_layout(m_pgpushaderTextOut->m_pinputlayout);
//
//            }
//
//            //pmodelbuffer->set_vertex_array(vertexes, 6);
//
//            ch.m_ppixmap->bind_texture(pshader);
//            //glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//            //::opengl::check_error("");
//            //// update content of VBO memory
//            //int iVbo = pface->m_FaceVBO;
//            //glBindBuffer(GL_ARRAY_BUFFER, iVbo);
//            //::opengl::check_error("");
//            //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexes), vertexes); // be sure to use glBufferSubData and not glBufferData
//            //::opengl::check_error("");
//            //glBindBuffer(GL_ARRAY_BUFFER, 0);
//            //::opengl::check_error("");
//            // render quad
//            // 
//            // 
//            
//            auto pcommandbuffer = gpu_context()->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_layer());
//
//            //pcommandbuffer->draw(ch.m_ppixmap);
//
//            pmodelbuffer->bind(pcommandbuffer);
//
//            pmodelbuffer->m_pbufferVertex->bind();
//
//            pmodelbuffer->set_vertexes(vertexes);
//            
//            pmodelbuffer->draw(pcommandbuffer);
//
//            //pmodelbuffer->unbind(pcommandbuffer);
//
//            //glDrawArrays(GL_TRIANGLES, 0, 6);
//            //::opengl::check_error("");
//            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
//            Δx += ch.Advance; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
//
//         }
//      }
//      glBindVertexArray(0);
//      ::opengl::check_error("");
//      glBindTexture(GL_TEXTURE_2D, 0);
//      ::opengl::check_error("");
//      glDisable(GL_CULL_FACE);
//      ::opengl::check_error("");
//      pcontext->defer_unbind(m_pgpushaderTextOut);
   }


   ::gpu::enum_topology graphics::image_draw_topology() const
   {

      return ::gpu::e_topology_triangle_strip;

   }


   ::i32 graphics::image_draw_vertex_count() const
   {

      return 4;

   }


   ::gpu::enum_topology graphics::text_draw_topology() const
   {

      return ::gpu::e_topology_triangle_list;

   }


   ::i32 graphics::text_draw_vertex_count() const
   {

      return 6;

   }


   void graphics::text_out_2025_06(double x, double yParam, const ::scoped_string& scopedstr)
   {

      auto pcontext = gpu_context();

      //__USES_TRANSFORM(pcontext);

      ::gpu::context_lock contextlock(pcontext);

      //return;
      // activate corresponding render state	

      if (!m_pgpushaderTextOut)
      {

         auto pvertexshader = R"vertexshader(#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex;
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
   gl_Position = projection * vec4(pos, 0.0, 1.0);
   TexCoords = vec2(tex.x, 1.0 - tex.y);
}
)vertexshader";


         auto pfragmentshader = R"fragmentshader(#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec4 textColor;

void main()
{    
    vec4 sampled = texture(text, TexCoords).rgba;
vec4 c = vec4(textColor) * sampled;
    //color = vec4(sqrt(c.r),sqrt(c.g), sqrt(c.b), sqrt(c.a));
color = vec4(c.r,c.g, c.b, c.a);
//color = vec4(0.0, 1.0, 0.0, 1.0); // Bright debug color
}
)fragmentshader";

         m_pgpushaderTextOut = create_newø < ::gpu_opengl::shader >();

         auto pcontext = gpu_context();

         m_pgpushaderTextOut->m_bEnableBlend = true;
         m_pgpushaderTextOut->m_bDisableDepthTest = true;

         m_pgpushaderTextOut->initialize_shader_with_block(
            pcontext->m_pgpurenderer,
            pvertexshader,
            pfragmentshader,
            //{},
            //{},
            pcontext->input_layout<::graphics3d::sequence2_uv>()
         );

      }

      //pcontext->defer_bind(m_pgpushaderTextOut);

      auto color = m_pdraw2dbrush->m_color;
      //shader.use();
      ::cast<::gpu_opengl::shader>pshader = m_pgpushaderTextOut;
      pshader->_set_sequence4("textColor", { __expand_float_pre_rgba(color) });
      // glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
      pshader->_set_int("text", 0);
      //auto pcontext = gpu_context();

      floating_matrix4 projection = gpu_context()->ortho(
         0.0f,
         static_cast<float>(pcontext->width()),
         static_cast<float>(pcontext->height()),
         0.0f);
      pshader->_set_matrix4("projection", projection);

      set(m_pwritetextfont);

      ::pointer<font>pwritetextfont = m_pwritetextfont;


      auto pgpuface = get_face(pwritetextfont);

      ::cast < ::typeface::face>pface = pgpuface;

      glActiveTexture(GL_TEXTURE0);
      ::opengl::check_error("");

      //glEnable(GL_BLEND);
      //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

      //glDisable(GL_DEPTH_TEST);
      //glDepthMask(GL_FALSE);

      //glBindVertexArray(pface->m_FaceVAO);
      //::opengl::check_error("");
      auto pcommandbuffer = pcontext->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_layer());
      //pface->m_pmodelbufferBox->bind(pcommandbuffer);

      // iterate through all characters
      ::string strChar;
      ::string str(scopedstr);
      auto psz = str.c_str();

      if (str == "Options")
      {

         warning() << "draw_text: " << str;

      }
      //float scale;
      //if (pwritetextfont->m_fontsize.eunit() == e_unit_point)
      //{
      //   scale = pwritetextfont->m_fontsize.as_float() / FONT_POINT_DENOMINATOR;
      //}
      //else
      //{
      //   scale = pwritetextfont->m_fontsize.as_float() / FONT_PIXEL_DENOMINATOR;
      //}
      //auto y = m_pgpucontextCompositor->m_rectangle.height() - yParam - pface->m_iPixelSize;
      auto y = yParam;


      ::i32_point point(x, y);
      int Δx = 0;
      __transform(point);

      //auto pcontext = gpu_context();

      point.y = pcontext->height() - point.y - pface->m_iPixelSize;
      auto pgpurenderer = pcontext->m_pgpurenderer;
      glDisable(GL_CULL_FACE);
      ::opengl::check_error("");
      //glEnable(GL_BLEND);
      //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      while (next_unicode_character(strChar, psz))
      {

         auto& ch = pface->get_character(strChar);
         float h2 = (float) (ch.Size.y - ch.Bearing.y);
         float xpos = (float) (point.x + Δx + ch.Bearing.x);
         float ypos = (float) (point.y + h2);

         float w = (float) ch.Size.x;
         float h = (float) ch.Size.y;
         // update VBO for each character
         ::array < ::graphics3d::sequence2_uv > vertexes = {
             {{xpos,     ypos + h},{ 0.0f, 0.0f }},
             {{xpos,     ypos    },{ 0.0f, 1.0f }},
             {{xpos + w, ypos    },{ 1.0f, 1.0f }},
             {{xpos,     ypos + h},{ 0.0f, 0.0f }},
             {{xpos + w, ypos    },{ 1.0f, 1.0f }},
             {{xpos + w, ypos + h},{ 1.0f, 0.0f} }
         };
         // render glyph texture over quad

         auto ppixmap = ch.get_gpu_pixmap(pgpurenderer);
         if (ppixmap)
         {


            auto pmodelbuffer = model_buffer(::draw2d::e_model_character);

            if (pmodelbuffer->is_new())
            {

               pmodelbuffer->initialize_gpu_context_object(pcontext);

               pmodelbuffer->bind2(pcommandbuffer);

               pmodelbuffer->create_vertexes < ::graphics3d::sequence2_uv>(6);

               pmodelbuffer->unbind(pcommandbuffer);

               //pmodelbuffer->defer_set_input_layout(m_pgpushaderTextOut->m_pinputlayout);

            }

            //pmodelbuffer->set_vertex_array(vertexes, 6);

            ppixmap->bind_texture(pshader);
            //glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            //::opengl::check_error("");
            //// update content of VBO memory
            //int iVbo = pface->m_FaceVBO;
            //glBindBuffer(GL_ARRAY_BUFFER, iVbo);
            //::opengl::check_error("");
            //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexes), vertexes); // be sure to use glBufferSubData and not glBufferData
            //::opengl::check_error("");
            //glBindBuffer(GL_ARRAY_BUFFER, 0);
            //::opengl::check_error("");
            // render quad
            // 
            // 

            auto pcommandbuffer = gpu_context()->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_layer());

            //pcommandbuffer->draw(ch.m_ppixmap);

            pmodelbuffer->bind2(pcommandbuffer);

            pmodelbuffer->m_pbufferVertex->bind();

            pmodelbuffer->set_vertexes(vertexes);

            pmodelbuffer->draw2(pcommandbuffer);

            //pmodelbuffer->unbind(pcommandbuffer);

            //glDrawArrays(GL_TRIANGLES, 0, 6);
            //::opengl::check_error("");
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            Δx += ch.Advance; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))

         }
      }
      glBindVertexArray(0);
      ::opengl::check_error("");
      glBindTexture(GL_TEXTURE_2D, 0);
      ::opengl::check_error("");
      glDisable(GL_CULL_FACE);
      ::opengl::check_error("");
      //auto pcommandbuffer = gpu_context()->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_layer());
      pcontext->defer_unbind(pcommandbuffer, m_pgpushaderTextOut);
   }

   //void graphics::text_out_2024_and_before(double x, double y, const ::scoped_string& scopedstr)
   //{

   //   if (m_pwritetextfont.is_null())
   //   {

   //      return;

   //   }

   //   //::draw2d::graphics::text_out(x, y, lpszString);
   //   //if (::draw2d::graphics::text_out(x, y, lpszString, nCount))
   //   //{

   //   //   return true;

   //   //}

   //   //return true;

   //   set(m_pwritetextfont);

   //   ::pointer<font>pwritetextfont = m_pwritetextfont;

   //   float length = 0.f;

   //   for (unsigned int loop = 0; loop < scopedstr.size(); loop++)	// Loop To Find Text Length
   //   {

   //      length += pwritetextfont->m_gmf[scopedstr[loop]].gmfCellIncX;			// Increase Length By Each Characters Width

   //   }

   //   glTranslatef((float)(x), (float)(y), 0.0f);					// Center Our Text On The Screen

   //   glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
   //   glListBase(pwritetextfont->m_baseFont);									// Sets The Base Character to 0
   //   glCallLists((GLsizei)scopedstr.size(), GL_UNSIGNED_BYTE, scopedstr.begin());	// Draws The Display List Text
   //   glPopAttrib();										// Pops The Display List Bits      }

   //   glTranslatef((float)(-x), (float)(-y), 0.0f);					// Center Our Text On The Screen

   //   //return true;

   //}


   void graphics::set(::draw2d::region* pregion)
   {

      //return ::success;

   }


   void graphics::set(::draw2d::pen* pdraw2dpen)
   {

      ::draw2d::graphics::set(pdraw2dpen);
      //glLineWidth(pdraw2dpen->m_dWidth);

      //::opengl::color(pdraw2dpen->m_color);

      //return ::success;

   }



   void graphics::set(::draw2d::brush* pdraw2dbrush)
   {

      ::draw2d::graphics::set(pdraw2dbrush);
      //::opengl::color(pdraw2dbrush->m_color);

      //return ::success;

   }



   void graphics::set(::write_text::font* pwritetextfont)
   {

      if (::is_null(pwritetextfont))
      {

         //return ::error_failed;
         return;

      }

      ::draw2d::graphics::set(pwritetextfont);

      //pwritetextfont->get_os_data(this);

      //return ::success;

   }


   void graphics::set(::draw2d::bitmap* pdraw2dbitmap)
   {

      //return ::success;

   }


   ::draw2d::object* graphics::set_stock_object(int nIndex)
   {

      return nullptr;

   }


   void graphics::set_smooth_mode(::draw2d::enum_smooth_mode esmoothmode)
   {

      //if(m_esmoothmode == esmoothmode)
      //   return;

      //::draw2d::graphics::set_smooth_mode(esmoothmode);

      //try
      //{

      //   if(m_pgraphics == nullptr)
      //      return;

      //   if(m_esmoothmode == ::draw2d::e_smooth_mode_none)
      //   {

      //      m_pgraphics->SetSmoothingMode(plusplus::SmoothingModeNone);

      //   }
      //   else if(m_esmoothmode == ::draw2d::e_smooth_mode_antialias)
      //   {

      //      m_pgraphics->SetSmoothingMode(plusplus::SmoothingModeHighSpeed);

      //   }
      //   else if(m_esmoothmode == ::draw2d::e_smooth_mode_high)
      //   {

      //      m_pgraphics->SetSmoothingMode(plusplus::SmoothingModeHighQuality);

      //   }

      //}
      //catch(...)
      //{
      //return true;
      //}

   }


   void graphics::set_alpha_mode(::draw2d::enum_alpha_mode ealphamode)
   {

      if (m_ealphamode != ealphamode)
      {

         try
         {

            //if(m_pgraphics == nullptr)
            //   return;

            ::draw2d::graphics::set_alpha_mode(ealphamode);
            if (m_ealphamode == ::draw2d::e_alpha_mode_blend)
            {
               //glColorMask(false, false, false, true);
               //glColorMask(true, true, true, false);
               //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
               //glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
               //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
               //glBlendFunc(GL_ZERO, GL_SRC_ALPHA);
               //glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
               // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
               glEnable(GL_BLEND);

               glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
               glBlendEquation(GL_FUNC_ADD); // default, can be omitted if unchanged

               //glDisable(GL_DEPTH_TEST);
               //glDepthFunc(GL_NEVER);
            }
            else if (m_ealphamode == ::draw2d::e_alpha_mode_set)
            {
               
               glEnable(GL_BLEND);
               glBlendFunc(GL_ONE, GL_ZERO); // Source Copy mode

            }

         }
         catch (...)
         {
            //return false;

         }

      }

      //return true;

   }


   void graphics::_draw_raw(const ::f64_rectangle& rectangleTarget, ::image::image* pimage, const ::image::image_drawing_options& imagedrawingoptionsParam, const ::f64_point& pointSrc)
   {


   }


   void graphics::set_text_rendering_hint(::write_text::enum_rendering etextrendering)
   {

      m_ewritetextrendering = etextrendering;

      //return true;

   }


   //   void * graphics::get_os_data() const
   //   {
   //
   ////      return (void *) m_pgraphics;
   //
   //      if (!m_hglrc)
   //      {
   //         return (void *) (iptr)1;
   //      }
   //
   //      return m_hglrc;
   //
   //   }


      //void graphics::fill_rectangle(const f64_rectangle& rectangle, color32_t color32)
      //{



      //}

   //   void * graphics::get_os_data_ex(int i) const
   //   {
   //
   //      if(i == 1)
   //      {
   ////         return m_pgraphics->GetHDC();
   //      }
   //      else
   //      {
   //         return ::draw2d::graphics::get_os_data(i);
   //      }
   //
   //      return nullptr;
   //
   //   }


   //   void graphics::release_os_data_ex(int i,void * p)
   //   {
   //      if(i == 1)
   //      {
   ////         m_pgraphics->ReleaseHDC((HDC)p);
   //      }
   //      else
   //      {
   //
   //         //::draw2d::graphics::release_os_data(i, p);
   //
   //      }
   //
   //   }


      /*HDC graphics::get_handle() const
      {

         return m_hdc;

      }


      HDC graphics::m_hdc const
      {

         return get_handle();

      }


      HDC graphics::m_hdc const
      {
         return get_handle();
      }
   */

   //bool graphics::attach(void * pdata)
   //{

   //   //if(m_pgraphics != nullptr)
   //   //{

   //   //   try
   //   //   {

   //   //      delete m_pgraphics;

   //   //   }
   //   //   catch(...)
   //   //   {

   //   //      informationf("graphics::attach : Failed to delete plusplus::Graphics");

   //   //   }

   //   //   m_pgraphics = nullptr;

   //   //}

   //   //m_pgraphics = (plusplus::Graphics *) pdata;

   //   return false;

   //}


   void* graphics::detach()
   {

      //plusplus::Graphics * pdraw2dgraphics = m_pgraphics;

      //m_pgraphics = nullptr;

      //m_hdc = nullptr;

      //return pdraw2dgraphics;

      return nullptr;

   }

   //plusplus::Font * graphics::gl2d_font()
   //{
   //   if(m_pwritetextfont.is_null())
   //   {
   //      m_pwritetextfont.create(this);
   //      if(m_pwritetextfont.is_set())
   //      {
   //         m_pwritetextfont->m_powner = this;
   //      }
   //   }
   //   if(m_pwritetextfont.is_null())
   //   {
   //      return nullptr;
   //   }
   //   return (plusplus::Font *) m_pwritetextfont->get_os_data();
   //}

   //plusplus::Brush * graphics::gl2d_brush()
   //{
   //   if(m_pdraw2dbrush.is_null())
   //   {
   //      m_pdraw2dbrush.create(this);
   //      if(m_pdraw2dbrush.is_set())
   //      {
   //         m_pdraw2dbrush->m_powner = this;
   //      }
   //   }
   //   if(m_pdraw2dbrush.is_null())
   //   {
   //      return nullptr;
   //   }
   //   return (plusplus::Brush *) m_pdraw2dbrush->get_os_data();
   //}

   //plusplus::Pen * graphics::gl2d_pen()
   //{

   //   synchronous_lock synchronouslock(this->synchronization());

   //   if(m_pdraw2dpen.is_null())
   //   {
   //      m_pdraw2dpen.create(this);
   //      if(m_pdraw2dpen.is_set())
   //      {
   //         m_pdraw2dpen->m_powner = this;
   //      }
   //   }
   //   if(m_pdraw2dpen.is_null())
   //   {
   //      return nullptr;
   //   }
   //   return (plusplus::Pen *) m_pdraw2dpen->get_os_data();
   //}

   //plusplus::FillMode graphics::gl2d_get_fill_mode()
   //{
   //   return plusplus::FillModeWinding;
   //}


   bool graphics::blur(bool bExpand, double dRadius, const ::i32_rectangle& rectangleParam)
   {

      //   // Commented Out for Running in cosan machine running Windows 2008

      //   //if(m_pdraw2dbitmap.is_null() || m_pdraw2dbitmap->get_os_data() == nullptr)
      //   //   return false;

      //   //plusplus::BlurParams myBlurParams;

      //   //myBlurParams.expandEdge    = bExpand ? 1 : 0;
      //   //myBlurParams.radius        = (float) dRadius;

      //   //plusplus::Blur myBlur;
      //   //myBlur.SetParameters(&myBlurParams);

      //   //

      //   //plusplus::Matrix m;
      //   //m_pgraphics->GetTransform(&m);

      //   //plusplus::PointF points[2];

      //   //points[0].X    = (plusplus::REAL) rectangleParam.left;
      //   //points[0].Y    = (plusplus::REAL) rectangleParam.top;
      //   //points[1].X    = (plusplus::REAL) rectangleParam.right;
      //   //points[1].Y    = (plusplus::REAL) rectangleParam.bottom;

      //   //m.TransformPoints(points, 2);

      //   ////plusplus::rectF float_rectangle(points[0].X, points[0].Y, points[1].X - points[0].X, points[1].Y - points[0].Y);

      //   //::f64_rectangle ::f64_rectangle;

      //   //rectangle.left      = (::double) points[0].X;
      //   //rectangle.top       = (::double) points[0].Y;
      //   //rectangle.right     = (::double) points[1].X;
      //   //rectangle.bottom    = (::double) points[1].Y;

      //   //plusplus::Bitmap * pdraw2dbitmap = ((plusplus::Bitmap *) m_pdraw2dbitmap->get_os_data());

      //   //pdraw2dbitmap->ApplyEffect(&myBlur, &rectangle);

      //   return true;

      return true;
   }


   double graphics::get_dpix() const
   {

      //if (m_pgraphics == nullptr)
      //   return 96.0;

      //return m_pgraphics->GetDpiX();

      return 96.0;

   }


   double graphics::get_dpiy() const
   {

      //if (m_pgraphics == nullptr)
      //   return 96.0;

      //return m_pgraphics->GetDpiY();

      return 96.0;

   }


   void graphics::flush()
   {

      synchronous_lock synchronouslock(this->synchronization());

      //      m_pgraphics->Flush();

            //return true;

   }


   void graphics::sync_flush()
   {

      synchronous_lock synchronouslock(this->synchronization());

      //m_pgraphics->Flush(plusplus::FlushIntentionSync);

      //return true;

   }


   //HDC graphics::get_hdc()
   //{

   //   if(m_hdc != nullptr)
   //      return m_hdc;

   //   ////if(m_pgraphics == nullptr)
   //   //   return nullptr;

   //   //return m_pgraphics->GetHDC();

   //   return nullptr;

   //}

   //void graphics::release_hdc(HDC hdc)
   //{

   //   if(m_hdc != nullptr)
   //      return;

   //   //m_pgraphics->ReleaseHDC(hdc);

   //}


   //void graphics::enum_fonts(::write_text::font_enumeration_item_array& itema)
   //{

   //   return;

   //   synchronous_lock synchronouslock(this->synchronization());

   //   draw2d_opengl_enum_fonts fonts(itema);

   //   //HDC hdc = ::CreateCompatibleDC(nullptr);

   //   //::EnumFontFamilies(hdc,(LPCTSTR)nullptr,(FONTENUMPROC)draw2d_opengl_EnumFamCallBack,(LPARAM)&fonts);

   //   //::DeleteDC(hdc);

   //   // straPath = stra;

   //}


   //bool graphics::prefer_mapped_image_on_mix()
   //{

   //   return true;

   //}

   ::geometry2d::matrix graphics::context_matrix(enum_transform_context etransformcontext)
   {

      //auto pcontext = gpu_context();

      ::geometry2d::matrix contextmatrix;

      if (etransformcontext == e_transform_context_default
         || etransformcontext == e_transform_context_geometry)
      {

         contextmatrix.translate(0.5, -0.5);

      }

      contextmatrix.append(context_scale_matrix());

      return contextmatrix;

   }


   ::geometry2d::matrix graphics::context_scale_matrix()
   {

      auto pcontext = gpu_context();

      auto size = pcontext->size();

      ::geometry2d::matrix contextmatrix;

      contextmatrix.scale(2.0 / size.cx, -2.0 / size.cy);

      contextmatrix.translate(-1.0, 1.0);

      return contextmatrix;

   }


//   void graphics::create_window_graphics(const ::operating_system::window & operatingsystemwindow)
//   {
//
//      // http://stackoverflow.com/questions/4052940/how-to-make-an-opengl-rendering-context-with-transparent-background
//      //
//
//      //PIXELFORMATDESCRIPTOR pfd =
//      //{
//      //   sizeof(PIXELFORMATDESCRIPTOR),
//      //   1,                                // Version Number
//      //   PFD_DRAW_TO_WINDOW |         // Format Must Support Window
//      //   PFD_SUPPORT_OPENGL |         // Format Must Support OpenGL
//      //   PFD_SUPPORT_COMPOSITION |         // Format Must Support Composition
//      //   PFD_DOUBLEBUFFER,                 // Must Support Double Buffering
//      //   PFD_TYPE_RGBA,                    // Request An RGBA Format
//      //   32,                               // Select Our Color Depth
//      //   0, 0, 0, 0, 0, 0,                 // Color Bits Ignored
//      //   8,                                // An Alpha Buffer
//      //   0,                                // Shift Bit Ignored
//      //   0,                                // No Accumulation Buffer
//      //   0, 0, 0, 0,                       // Accumulation Bits Ignored
//      //   24,                               // 16Bit Z-Buffer (Depth Buffer)
//      //   8,                                // Some Stencil Buffer
//      //   0,                                // No Auxiliary Buffer
//      //   PFD_MAIN_PLANE,                   // Main Drawing Layer
//      //   0,                                // Reserved
//      //   0, 0, 0                           // Layer Masks Ignored
//      //};
//
//
//      //DWM_BLURBEHIND bb = { 0 };
//      ////HRGN hRgn = CreateRectRgn(0, 0, -1, -1);
//      ////bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
//      //bb.dwFlags = DWM_BB_ENABLE;
//      ////bb.hRgnBlur = hRgn;
//      //bb.fEnable = true;
//      //DwmEnableBlurBehindWindow(wnd, &bb);
//
//
//      //m_hdc = GetDC(wnd);
//      //int PixelFormat = ChoosePixelFormat(m_hdc, &pfd);
//      //if (PixelFormat == 0)
//      //{
//      //   ASSERT(0);
//      //   return false;
//      //}
//
//      //BOOL bResult = SetPixelFormat(m_hdc, PixelFormat, &pfd);
//      //if (bResult == false)
//      //{
//      //   ASSERT(0);
//      //   return false;
//      //}
//
//      //m_hglrc = wglCreateContext(m_hdc);
//      //if (!m_hglrc)
//      //{
//      //   ASSERT(0);
//      //   return false;
//      //}
//
////      return true;
//      //return false;
//
//   }


   //oswindow graphics::get_window_handle() const
   //{

   //   if (::is_null(m_puserinteractionDraw2dGraphics))
   //   {

   //      return nullptr;

   //   }

   //   return m_puserinteractionDraw2dGraphics->get_handle();

   //}


   void graphics::is_valid_update_window_thread()
   {

      //return ::GetCurrentThreadId() == psystem->get_twf()->m_uiThread;
      //return ::GetCurrentThreadId() == ::GetWindowThreadProcessId(m_hwnd, NULL);

   }


   //void graphics::_add_clipping_shape(const ::f64_rectangle & rectangle, ::draw2d::region * pregion)
   //{


   //}


   void graphics::send(const ::procedure& procedure)
   {

      ::gpu::graphics::send(procedure);

      //m_pgpucontextCompositor->send(procedure);

   }


   //void graphics::start_gpu_layer(::gpu::layer * pgpulayer)
   //{

   //   //auto pcontext = gpu_context();

   //   //::gpu::context_lock contextlock(pcontext);

   //   ::gpu::graphics::start_gpu_layer(pgpulayer);

   //   //glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Clear the background to transparent
   //   //::opengl::check_error("");
   //   //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers
   //   //::opengl::check_error("");
   //   //glDepthMask(GL_FALSE); // Disable writing to depth buffer
   //   //::opengl::check_error("");
   //   //glDisable(GL_DEPTH_TEST); // Disable depth testing
   //   //::opengl::check_error("");

   //   //auto ealphamode = m_ealphamode;
   //   m_ealphamode = ::draw2d::e_alpha_mode_none; // Set alpha mode to blend for GPU layer
   //   set_alpha_mode(m_ealphamode);

   //}


   //::gpu::frame * graphics::end_gpu_layer(::gpu::layer * pgpulayer)
   //{

   //   return ::gpu::graphics::end_gpu_layer(pgpulayer);

   //}


   ::gpu::context* graphics::gpu_context()
   {

      return  ::gpu::graphics::gpu_context();

   }

   //void graphics::defer_add_graphics_render(::graphics::render * pgraphicsrender)
   //{

   //   m_pgpucontextCompositor->m_rendera.add_unique(pgraphicsrender);

   //}


   void graphics::initialize(::particle* pparticle)
   {

      ::draw2d::graphics::initialize(pparticle);

      //::gpu::renderer::initialize(pparticle);

   }


   ////void graphics::on_begin_draw(oswindow wnd, const ::i32_size & sz)
   //void graphics::on_begin_draw()
   //{

   //   //thread_select();

   //   ::i32_size size;

   //   if (!m_puserinteractionDraw2dGraphics && m_papplication->m_bUseSwapChainWindow)
   //   {

   //      m_puserinteractionDraw2dGraphics = dynamic_cast <::user::interaction*>(m_pwindow->m_pacmeuserinteraction.m_p);

   //   }

   //   if (m_puserinteractionDraw2dGraphics && !m_puserinteractionDraw2dGraphics->size().is_empty())
   //   {

   //      size = m_puserinteractionDraw2dGraphics->size();

   //   }
   //   else
   //   {

   //      size = { 1920, 1080 };

   //   }

   //   bool bYSwap = m_papplication->m_bUseSwapChainWindow;

   //   ::cast < ::gpu_opengl::renderer >prenderer = m_pgpucontextCompositor->get_renderer();

   //   m_pgpucontextCompositor->set_placement({ i32_point{}, size });

   //   if (m_egraphics & e_graphics_draw)
   //   {

   //      ::cast < ::gpu_opengl::context >pgpucontext = m_pgpucontextCompositor;

   //      //pgpucontext->m_size = size;

   //      //pgpucontext->m_sizeNew = size;

   //      pgpucontext->m_sizeHost = size;

   //      pgpucontext->make_current();

   //      m_pframe = prenderer->beginFrame();

   //      prenderer->on_begin_render(m_pframe);
   //      //glEnable(GL_BLEND);
   //      //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
   //      //glEnable(GL_BLEND);
   //      //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   //      glDepthMask(GL_TRUE); // Enable writing to depth
   //      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   //      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //      glDepthMask(GL_FALSE); // Disable writing to depth

   //      glEnable(GL_BLEND);
   //      glDisable(GL_DEPTH_TEST);
   //      //glDepthFunc(GL_LEQUAL);

   //      ::opengl::resize(size, bYSwap);

   //      m_z = 0.0f;

   //      //glLoadIdentity();
   //      //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //      //glClear(GL_COLOR_BUFFER_BIT);
   //      //glEnable(GL_BLEND);
   //      //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   //      //::memory_copy(&m_pgpucontextCompositor->m_pbuffer->m_pixmap, (::pixmap *)m_pimage, sizeof(::pixmap));

   //      //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //      //m_pgpucontextCompositor->start_drawing();

   //      ///glEnable(GL_DEPTH_TEST);

   //   }

   //}


   //void graphics::on_end_draw()
   //{

   //   {

   //      if (m_egraphics & e_graphics_draw)
   //      {

   //         //vkvg_surface_resolve(m_vkvgsurface);

   //         //m_pgpucontextCompositor->m_prenderer->on_end_draw();

   //         //::f64_rectangle r{ 0.0, 0.0, 1920.0, 1080.0 };

   //         //fill_solid_rectangle(r, argb(255, 100, 200, 240));

   //         //::f64_rectangle r2{ 100.0, 100.0, 1920.0, 1980.0 };

   //         //set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //         //fill_solid_rectangle(r2, argb(155, 120, 40, 100));

   //         //m_pgpucontextCompositor->clear(::argb(100, 80, 120, 160));

   //         //vkvg_flush(m_pdc);

   //         //VkImage vkimage = vkvg_surface_get_vk_image(m_vkvgsurface);

   //         ::cast < ::gpu_opengl::renderer >prenderer = m_pgpucontextCompositor->get_renderer();

   //         prenderer->on_end_render(m_pframe);

   //         prenderer->endFrame();

   //         prenderer->endDraw(m_puserinteractionDraw2dGraphics);

   //      }

   //      ////vkPushMatrix();

   //      ////vkColor3f(0, 1, 1);
   //      //vkBegin(VK_TRIANGLES);                              // Drawing Using Triangles
   //      //

   //      //vkColor4f(1.0f, 0.0f, 0.0f, 0.5f);                      // Set The Color To Red
   //      //vkVertex3f(100.0f, -2000.0f, 0.0f);                  // Top
   //      //

   //      //vkColor3f(0.0f, 1.0f, 0.0f);                      // Set The Color To Green
   //      //vkVertex3f(0.0f, 200.0f, 0.0f);                  // Bottom Left


   //      //vkColor3f(0.0f, 0.0f, 1.0f);                      // Set The Color To Blue
   //      //vkVertex3f(2000.0f, 2000.0f, 0.0f);                  // Bottom Right

   //      //vkEnd();

   //      //vkPopMatrix();


   //      //vkFlush();
   //      //vkFinish();
   //      //vkDisable(VK_BLEND);




   //      //SwapBuffers(m_hdc);

   //      //m_pgpucontextVulkan->render

   //      //dr();


   //   }

   //   ////m_pgpucontextCompositor->make_current();

   //   //////glColor3f(0, 1, 1);
   //   ////glBegin(GL_TRIANGLES);                              // Drawing Using Triangles
   //   ////

   //   ////glColor4f(1.0f, 0.0f, 0.0f, 0.5f);                      // Set The Color To Red
   //   ////glVertex3f(100.0f, -2000.0f, 0.0f);                  // Top
   //   ////

   //   ////glColor3f(0.0f, 1.0f, 0.0f);                      // Set The Color To Green
   //   ////glVertex3f(0.0f, 200.0f, 0.0f);                  // Bottom Left


   //   ////glColor3f(0.0f, 0.0f, 1.0f);                      // Set The Color To Blue
   //   ////glVertex3f(2000.0f, 2000.0f, 0.0f);                  // Bottom Right

   //   ////glEnd();

   //   ////glPopMatrix();

   //   ////glClearColor(0.5f, 0.9f, 0.95f, 1.0f);
   //   ////glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //   //glFlush();
   //   ////glFinish();
   //   ////glDisable(GL_BLEND);


   //   ////SwapBuffers(m_hdc);

   //   ////m_pgpucontextOpenGL->render

   //   ////dr();

   //   //if (m_papplication->m_bUseSwapChainWindow)
   //   //{

   //   //   //if (m_pgpucontextCompositor->m_eoutput == ::gpu::e_output_swap_chain)
   //   //   //{

   //   //   //m_pgpucontextCompositor->swap_buffers();

   //   //   //}

   //   //   //m_pwindow->m_timeLastDrawGuard1.Now();

   //   //}
   //   //else
   //   //{

   //   //   //m_pgpucontextCompositor->swap_buffers();

   //   ////}
   //   ////else
   //   ////{

   //   //   read_to_cpu_buffer();

   //   //   m_pimage->map();

   //   //   m_pimage->copy(&m_pgpucontextCompositor->m_pcpubuffer->m_pixmap);

   //   //}

   //}


   void graphics::on_present()
   {

      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         //m_pgpucontextCompositor->swap_buffers();

      }

   }


   void graphics::thread_select()
   {


      ::gpu::graphics::thread_select();


      ////if (thread_graphics() == this)
      ////{

      //  // return;
      ////}

      ////wglMakeCurrent(m_hdc, m_hglrc);

      //m_pgpucontextCompositor->make_current();

      //thread_graphics(this);

   }


   bool graphics::_is_ok() const
   {

      if (!::is_set(this))
      {

         return false;

      }

      auto pgpucontext = ((graphics*)this)->gpu_context();

      if (!::is_set(pgpucontext))
      {

         return false;

      }

      auto pgpurenderer = pgpucontext->m_pgpurenderer;

      if (!::is_set(pgpurenderer))
      {

         return false;

      }

      return true;

   }


   void graphics::intersect_clip(const ::f64_rectangle& rectangle)
   {


   }


   void graphics::intersect_clip(::draw2d::clip_group * pclipgroup)
   {



   }


} // namespace draw2d_opengl




#ifdef WINDOWS_DESKTOP
BOOL CALLBACK draw2d_opengl_EnumFamCallBack(LPLOGFONT lplf, LPNEWTEXTMETRIC lpntm, unsigned int FontType, LPVOID p)
{

   draw2d_opengl_enum_fonts* pfonts = (draw2d_opengl_enum_fonts*)p;

   if (FontType & RASTER_FONTTYPE)
   {

   }
   else if (FontType & TRUETYPE_FONTTYPE)
   {

      pfonts->m_itema.add(allocateø::write_text::font_enumeration_item(lplf->lfFaceName));

   }
   else
   {

   }

   return true;

}

#endif



namespace opengl
{


   void resize(const ::i32_size& size, bool bYSwap)
   {

      //double d = 200.0 / 72.0;

      //double d = 1.0;
      ////glViewport(0, 0, size.cx * d, size.cy * d);
      //glViewport(0, 0, size.cx, size.cy);
      //glMatrixMode(GL_PROJECTION);
      //glLoadIdentity();
      ////glOrtho(0, size.cx * d, size.cy * d, 0.0f, 000.0f, 1000.0f);
      ////glOrtho(0, size.cx * d, size.cy * d, 0.0f, 000.0f, 1000.0f);
      //////glOrtho(0, size.cx * d, 0.0f, size.cy * d, 000.0f, 1000.0f);
      ////glOrtho(0, size.cx, size.cy, 0.0f, -1000.0f, 1000.0f);
      //glOrtho(0.f, size.cx, 0.f, -size.cy, -1.0f, 1.0f);
      if (bYSwap)
      {
         //glOrtho(0.0f, size.cx, size.cy, 0, -1.0f, 1.0f);  // Flip Y
      }
      else
      {
         //glOrtho(0.0f, size.cx, 0, size.cy, -1.0f, 1.0f);  // Flip Y
      }
      //glMatrixMode(GL_MODELVIEW);
      //glLoadIdentity();
      //auto left = 0.;
      //auto right = (double) size.cx;
      //auto bottom = 0.;
      //auto top = (double)size.cy;
      //double dFar = 1.0;
      //double dNear = -1.0;
      //double tx = -(right + left) / (right - left);
      //double ty = -(top + bottom) / (top - bottom);
      //double tz = -(dFar + dNear) / (dFar - dNear);
      //double a[] =
      //{
      //   2.0/(right - left),0.0,0.0,tx,
      //   0.0,2.0/(top - bottom),0.0,ty,
      //   0.0,0.0,-2.0/(dFar-dNear),tz,
      //   0.0,0.0,0.0,1.0
      //};
      //glMultMatrixd(a);

      //glMatrixMode(GL_MODELVIEW);
      //glLoadIdentity();


      //gluOrtho2D(0.f, size.cx, 0.f, size.cy);
      //glMatrixMode(GL_MODELVIEW);
      //glLoadIdentity();

      // Clear
      //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
      //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      //glDisable(GL_DEPTH_TEST);

      // Translate to inside of pixel (otherwise inaccuracies can occur on certain gl implementations)
      //if (OpenGL::accuracyTweak())
      //glTranslatef(0.5f, 0.5f, 0);

   }


   ////https://community.khronos.org/t/draw-an-arc-in-opengl/57994/2
   //inline void draw_arc(float cx, float cy, float r, float start_angle, float arc_angle, int num_segments, float fZ)
   //{
   //   float theta = arc_angle / float(num_segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open

   //   float tangetial_factor = tanf(theta);

   //   float radial_factor = cosf(theta);


   //   float x = r * cosf(start_angle);//we now start at the start angle
   //   float y = r * sinf(start_angle);

   //   glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
   //   for (int ii = 0; ii < num_segments; ii++)
   //   {
   //      glVertex3f(x + cx, y + cy, fZ);

   //      float tx = -y;
   //      float ty = x;

   //      x += tx * tangetial_factor;
   //      y += ty * tangetial_factor;

   //      x *= radial_factor;
   //      y *= radial_factor;
   //   }
   //   glEnd();
   //}



} // namespace opengl



