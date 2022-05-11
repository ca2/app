/*
    src/screen.cpp -- Top-level widget and interface between NanoGUI and GLFW

    A significant redesign of this code was contributed by Christian Schueller.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "aura/graphics/image/context_image.h"
//#include <nanogui/screen.h>
//#include <nanogui/theme.h>
//#include <nanogui/opengl.h>
//#include <nanogui/window.h>
//#include <nanogui/popup.h>
//#include <nanogui/metal.h>
//#include <map>
//#include <iostream>
//
//#if defined(EMSCRIPTEN)
//#  include <emscripten/emscripten.h>
//#  include <emscripten/html5.h>
//#endif
//
//#if defined(_WIN32)
//#  ifndef NOMINMAX
//#    define NOMINMAX
//#  endif
//#  undef APIENTRY
//
//#  ifndef WIN32_LEAN_AND_MEAN
//#    define WIN32_LEAN_AND_MEAN
//# endif
//#  include <windows.h>
//
//#  define GLFW_EXPOSE_NATIVE_WGL
//#  define GLFW_EXPOSE_NATIVE_WIN32
//#  include <GLFW/glfw3native.h>
//#endif
//
///* Allow enforcing the GL2 implementation of NanoVG */
//
//#if defined(NANOGUI_USE_OPENGL) || defined(NANOGUI_USE_GLES)
//#  if defined(NANOGUI_USE_OPENGL)
//#    define NANOVG_GL3_IMPLEMENTATION
//#  elif defined(NANOGUI_USE_GLES)
//#    define NANOVG_GLES2_IMPLEMENTATION
//#  endif
//#  include <nanovg_gl.h>
//#  include "opengl_check.h"
//#elif defined(NANOGUI_USE_METAL)
//#  include <nanovg_mtl.h>
//#endif
//
//#if defined(__APPLE__)
//#  define GLFW_EXPOSE_NATIVE_COCOA 1
//#  include <GLFW/glfw3native.h>
//#endif
//
//#if !defined(GL_RGBA_FLOAT_MODE)
//#  define GL_RGBA_FLOAT_MODE 0x8820
//#endif
//
NAMESPACE_BEGIN(nanogui)
//
//std::map<GLFWwindow *, Screen *> __nanogui_screens;
//
//#if defined(NANOGUI_GLAD)
//static bool glad_initialized = false;
//#endif
//
///* Calculate pixel ratio for hi-dpi devices. */
//static float get_pixel_ratio(GLFWwindow * window) {
//#if defined(EMSCRIPTEN)
//   return emscripten_get_device_pixel_ratio();
//#else
//   float xscale, yscale;
//   glfwGetWindowContentScale(window, &xscale, &yscale);
//   return xscale;
//#endif
//}
//
//#if defined(EMSCRIPTEN)
//static EM_BOOL nanogui_emscripten_resize_callback(int eventType, const EmscriptenUiEvent *, void *) {
//   double ratio = emscripten_get_device_pixel_ratio();
//
//   int w1, h1;
//   emscripten_get_canvas_element_size("#canvas", &w1, &h1);
//
//   double w2, h2;
//   emscripten_get_element_css_size("#canvas", &w2, &h2);
//
//   double w3 = w2 * ratio, h3 = h2 * ratio;
//
//   if (w1 != (int)w3 || h1 != (int)h3)
//      emscripten_set_canvas_element_size("#canvas", w3, h3);
//
//   for (auto it : __nanogui_screens) {
//      Screen * screen = it.second;
//      screen->resize_event(Vector2i((int)w2, (int)h2));
//      screen->redraw();
//   }
//
//   return true;
//}
//#endif

//Screen::Screen()
//   : Widget(nullptr) /*, m_glfw_window(nullptr), ctx(nullptr),
//   m_cursor(Cursor::Arrow), m_background(0.3f, 0.3f, 0.32f, 1.f),
//   m_shutdown_glfw_on_destruct(false), m_fullscreen(false), m_depth_buffer(false),
//   m_stencil_buffer(false), m_float_buffer(false)*/, m_redraw(false)
//{
//
//   m_pixel_ratio = 1.0f;
//
//   common_construct();
//
//  /* memset(m_cursors, 0, sizeof(GLFWcursor *) * (size_t)Cursor::CursorCount);
//#if defined(NANOGUI_USE_OPENGL)
//   GLint n_stencil_bits = 0, n_depth_bits = 0;
//   GLboolean float_mode;
//   CHK(glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER,
//      GL_DEPTH, GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE, &n_depth_bits));
//   CHK(glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER,
//      GL_STENCIL, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, &n_stencil_bits));
//   CHK(glGetBooleanv(GL_RGBA_FLOAT_MODE, &float_mode));
//   m_depth_buffer = n_depth_bits > 0;
//   m_stencil_buffer = n_stencil_bits > 0;
//   m_float_buffer = (bool)float_mode;
//#endif*/
//}

Screen::Screen(::user::interaction* puserinteraction,
               const Vector2i & size, const std::string & caption, bool resizable,
   bool fullscreen, bool depth_buffer, bool stencil_buffer,
   bool float_buffer, unsigned int gl_major, unsigned int gl_minor)
   : Widget(nullptr)  /*,  m_glfw_window(nullptr), ctx(nullptr),
   m_cursor(Cursor::Arrow)*/, m_background(0.3f, 0.3f, 0.32f, 1.f) /*, m_caption(caption),
   m_shutdown_glfw_on_destruct(false), m_fullscreen(fullscreen), m_depth_buffer(depth_buffer),
   m_stencil_buffer(stencil_buffer), m_float_buffer(float_buffer)*/, m_redraw(false)
{
   initialize(puserinteraction);
   m_puserinteraction = puserinteraction;
   
   common_construct();
      
   m_size = size;
   m_modifiers = ::user::e_key_none;
      
      
   // memset(m_cursors, 0, sizeof(GLFWcursor *) * (int)Cursor::CursorCount);
//
//#if defined(NANOGUI_USE_OPENGL)
//   glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
//
//   /* Request a forward compatible OpenGL gl_major.gl_minor core profile context.
//      Default value is an OpenGL 3.3 core profile context. */
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
//   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//#elif defined(NANOGUI_USE_GLES)
//   glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
//   glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, NANOGUI_GLES_VERSION);
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//#elif defined(NANOGUI_USE_METAL)
//   glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//   m_stencil_buffer = stencil_buffer = false;
//#else
//#  error Did not select a graphics API!
//#endif
//
//   int color_bits = 8, depth_bits = 0, stencil_bits = 0;
//
//   if (stencil_buffer && !depth_buffer)
//      throw std::runtime_error(
//         "Screen::Screen(): stencil_buffer = True requires depth_buffer = True");
//   if (depth_buffer)
//      depth_bits = 32;
//   if (stencil_buffer) {
//      depth_bits = 24;
//      stencil_bits = 8;
//   }
//   if (m_float_buffer)
//      color_bits = 16;
//
//   glfwWindowHint(GLFW_RED_BITS, color_bits);
//   glfwWindowHint(GLFW_GREEN_BITS, color_bits);
//   glfwWindowHint(GLFW_BLUE_BITS, color_bits);
//   glfwWindowHint(GLFW_ALPHA_BITS, color_bits);
//   glfwWindowHint(GLFW_STENCIL_BITS, stencil_bits);
//   glfwWindowHint(GLFW_DEPTH_BITS, depth_bits);
//
//#if (defined(NANOGUI_USE_OPENGL) || defined(NANOGUI_USE_METAL)) && defined(GLFW_FLOATBUFFER)
//   glfwWindowHint(GLFW_FLOATBUFFER, m_float_buffer ? GL_TRUE : GL_FALSE);
//#else
//   m_float_buffer = false;
//#endif
//
//   glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
//   glfwWindowHint(GLFW_RESIZABLE, resizable ? GL_TRUE : GL_FALSE);
//   glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
//
//   for (int i = 0; i < 2; ++i) {
//      if (fullscreen) {
//         GLFWmonitor * monitor = glfwGetPrimaryMonitor();
//         const GLFWvidmode * mode = glfwGetVideoMode(monitor);
//         m_glfw_window = glfwCreateWindow(mode->width, mode->height,
//            caption.c_str(), monitor, nullptr);
//      }
//      else {
//         m_glfw_window = glfwCreateWindow(size.x(), size.y(),
//            caption.c_str(), nullptr, nullptr);
//      }
//
//      if (m_glfw_window == nullptr && m_float_buffer) {
//         m_float_buffer = false;
//#if defined(GLFW_FLOATBUFFER)
//         glfwWindowHint(GLFW_FLOATBUFFER, GL_FALSE);
//#endif
//         fprintf(stderr, "Could not allocate floating point framebuffer, retrying without..\n");
//      }
//      else {
//         break;
//      }
//   }
//
//   if (!m_glfw_window) {
//      (void)gl_major; (void)gl_minor;
//#if defined(NANOGUI_USE_OPENGL)
//      throw std::runtime_error("Could not create an OpenGL " +
//         std::to_string(gl_major) + "." +
//         std::to_string(gl_minor) + " context!");
//#elif defined(NANOGUI_USE_GLES)
//      throw std::runtime_error("Could not create a GLES 2 context!");
//#elif defined(NANOGUI_USE_METAL)
//      throw std::runtime_error(
//         "Could not create a GLFW window for rendering using Metal!");
//#endif
//   }
//
//#if defined(NANOGUI_USE_OPENGL) || defined(NANOGUI_USE_GLES)
//   glfwMakeContextCurrent(m_glfw_window);
//#endif
//
//   glfwSetInputMode(m_glfw_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//
//#if defined(NANOGUI_GLAD)
//   if (!glad_initialized) {
//      glad_initialized = true;
//      if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//         throw std::runtime_error("Could not initialize GLAD!");
//      glGetError(); // pull and ignore unhandled errors like GL_INVALID_ENUM
//   }
//#endif
//
//#if defined(NANOGUI_USE_OPENGL)
//   if (m_float_buffer) {
//      GLboolean float_mode;
//      CHK(glGetBooleanv(GL_RGBA_FLOAT_MODE, &float_mode));
//      if (!float_mode) {
//         fprintf(stderr, "Could not allocate floating point framebuffer.\n");
//         m_float_buffer = false;
//      }
//   }
//#endif
//
//   glfwGetFramebufferSize(m_glfw_window, &m_fbsize[0], &m_fbsize[1]);
//
//#if defined(NANOGUI_USE_OPENGL) || defined(NANOGUI_USE_GLES)
//   CHK(glViewport(0, 0, m_fbsize[0], m_fbsize[1]));
//   CHK(glClearColor(m_background[0], m_background[1],
//      m_background[2], m_background[3]));
//   CHK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
//      GL_STENCIL_BUFFER_BIT));
//
//   glfwSwapInterval(0);
//   glfwSwapBuffers(m_glfw_window);
//#endif
//
//#if defined(__APPLE__)
//   /* Poll for events once before starting a potentially
//      lengthy loading process. This is needed to be
//      classified as "interactive" by other software such
//      as iTerm2 */
//
//   glfwPollEvents();
//#endif
//
//   /* Propagate GLFW events to the appropriate Screen instance */
//   glfwSetCursorPosCallback(m_glfw_window,
//      [](GLFWwindow * w, double x, double y) {
//         auto it = __nanogui_screens.find(w);
//         if (it == __nanogui_screens.end())
//            return;
//         Screen * s = it->second;
//         if (!s->m_process_events)
//            return;
//         s->cursor_pos_callback_event(x, y);
//      }
//   );
//
//   glfwSetMouseButtonCallback(m_glfw_window,
//      [](GLFWwindow * w, int button, int action, int modifiers) {
//         auto it = __nanogui_screens.find(w);
//         if (it == __nanogui_screens.end())
//            return;
//         Screen * s = it->second;
//         if (!s->m_process_events)
//            return;
//         s->mouse_button_callback_event(button, action, modifiers);
//      }
//   );
//
//   glfwSetKeyCallback(m_glfw_window,
//      [](GLFWwindow * w, int key, int scancode, int action, int mods) {
//         auto it = __nanogui_screens.find(w);
//         if (it == __nanogui_screens.end())
//            return;
//         Screen * s = it->second;
//         if (!s->m_process_events)
//            return;
//         s->key_callback_event(key, scancode, action, mods);
//      }
//   );
//
//   glfwSetCharCallback(m_glfw_window,
//      [](GLFWwindow * w, unsigned int codepoint) {
//         auto it = __nanogui_screens.find(w);
//         if (it == __nanogui_screens.end())
//            return;
//         Screen * s = it->second;
//         if (!s->m_process_events)
//            return;
//         s->char_callback_event(codepoint);
//      }
//   );
//
//   glfwSetDropCallback(m_glfw_window,
//      [](GLFWwindow * w, int count, const char ** filenames) {
//         auto it = __nanogui_screens.find(w);
//         if (it == __nanogui_screens.end())
//            return;
//         Screen * s = it->second;
//         if (!s->m_process_events)
//            return;
//         s->drop_callback_event(count, filenames);
//      }
//   );
//
//   glfwSetScrollCallback(m_glfw_window,
//      [](GLFWwindow * w, double x, double y) {
//         auto it = __nanogui_screens.find(w);
//         if (it == __nanogui_screens.end())
//            return;
//         Screen * s = it->second;
//         if (!s->m_process_events)
//            return;
//         s->scroll_callback_event(x, y);
//      }
//   );
//
//   /* React to framebuffer size events -- includes window
//      size events and also catches things like dragging
//      a window from a Retina-capable screen to a normal
//      screen on Mac OS X */
//   glfwSetFramebufferSizeCallback(m_glfw_window,
//      [](GLFWwindow * w, int width, int height) {
//         auto it = __nanogui_screens.find(w);
//         if (it == __nanogui_screens.end())
//            return;
//         Screen * s = it->second;
//
//         if (!s->m_process_events)
//            return;
//
//         s->resize_callback_event(width, height);
//      }
//   );
//
//   // notify when the screen has lost focus (e.g. application switch)
//   glfwSetWindowFocusCallback(m_glfw_window,
//      [](GLFWwindow * w, int focused) {
//         auto it = __nanogui_screens.find(w);
//         if (it == __nanogui_screens.end())
//            return;
//
//         Screen * s = it->second;
//         // focus_event: 0 when false, 1 when true
//         s->focus_event(focused != 0);
//      }
//   );
//
//   glfwSetWindowContentScaleCallback(m_glfw_window,
//      [](GLFWwindow * w, float, float) {
//         auto it = __nanogui_screens.find(w);
//         if (it == __nanogui_screens.end())
//            return;
//         Screen * s = it->second;
//
//         s->m_pixel_ratio = get_pixel_ratio(w);
//         s->resize_callback_event(s->m_size.x(), s->m_size.y());
//      }
//   );
//
//   initialize(m_glfw_window, true);
//
//#if defined(NANOGUI_USE_METAL)
//   if (depth_buffer) {
//      m_depth_stencil_texture = new Texture(
//         stencil_buffer ? Texture::PixelFormat::DepthStencil
//         : Texture::PixelFormat::Depth,
//         Texture::ComponentFormat::Float32,
//         framebuffer_size(),
//         Texture::InterpolationMode::Bilinear,
//         Texture::InterpolationMode::Bilinear,
//         Texture::WrapMode::ClampToEdge,
//         1,
//         Texture::TextureFlags::RenderTarget
//      );
//   }
//#endif
}
//
//void Screen::initialize(GLFWwindow * window, bool shutdown_glfw) {
//   m_glfw_window = window;
//   m_shutdown_glfw_on_destruct = shutdown_glfw;
//   glfwGetWindowSize(m_glfw_window, &m_size[0], &m_size[1]);
//   glfwGetFramebufferSize(m_glfw_window, &m_fbsize[0], &m_fbsize[1]);
//
//   m_pixel_ratio = get_pixel_ratio(window);
//
//#if defined(EMSCRIPTEN)
//   double w, h;
//   emscripten_get_element_css_size("#canvas", &w, &h);
//   double ratio = emscripten_get_device_pixel_ratio(),
//      w2 = w * ratio, h2 = h * ratio;
//
//   if (w != m_size[0] || h != m_size[1]) {
//      /* The canvas element is configured as width/height: auto, expand to
//         the available space instead of using the specified window resolution */
//      nanogui_emscripten_resize_callback(0, nullptr, nullptr);
//      emscripten_set_resize_callback(nullptr, nullptr, false,
//         nanogui_emscripten_resize_callback);
//   }
//   else if (w != w2 || h != h2) {
//      /* Configure for rendering on a high-DPI display */
//      emscripten_set_canvas_element_size("#canvas", (int)w2, (int)h2);
//      emscripten_set_element_css_size("#canvas", w, h);
//   }
//   m_fbsize = Vector2i((int)w2, (int)h2);
//   m_size = Vector2i((int)w, (int)h);
//#elif defined(_WIN32) || defined(__linux__)
//   if (m_pixel_ratio != 1 && !m_fullscreen)
//      glfwSetWindowSize(window, m_size.x() * m_pixel_ratio,
//         m_size.y() * m_pixel_ratio);
//#endif
//
//#if defined(NANOGUI_GLAD)
//   if (!glad_initialized) {
//      glad_initialized = true;
//      if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//         throw std::runtime_error("Could not initialize GLAD!");
//      glGetError(); // pull and ignore unhandled errors like GL_INVALID_ENUM
//   }
//#endif
//
//   int flags = NVG_ANTIALIAS;
//   if (m_stencil_buffer)
//      flags |= NVG_STENCIL_STROKES;
//#if !defined(NDEBUG)
//   flags |= NVG_DEBUG;
//#endif
//
//#if defined(NANOGUI_USE_OPENGL)
//   ctx = nvgCreateGL3(flags);
//#elif defined(NANOGUI_USE_GLES)
//   ctx = nvgCreateGLES2(flags);
//#elif defined(NANOGUI_USE_METAL)
//   void * nswin = glfwGetCocoaWindow(window);
//   metal_window_init(nswin, m_float_buffer);
//   metal_window_set_size(nswin, m_fbsize);
//   ctx = nvgCreateMTL(metal_layer(),
//      metal_command_queue(),
//      flags | NVG_TRIPLE_BUFFER);
//#endif
//
//   if (!ctx)
//      throw std::runtime_error("Could not initialize NanoVG!");
//
//   m_visible = glfwGetWindowAttrib(window, GLFW_VISIBLE) != 0;
//   set_theme(new Theme(ctx));
//   m_mouse_pos = Vector2i(0);
   //m_mouse_state = 
   //m_modifiers = ::user::e_key_none;
//   m_drag_active = false;
//   m_last_interaction = glfwGetTime();
//   m_process_events = true;
//   m_redraw = true;
//   __nanogui_screens[m_glfw_window] = this;
//
//   for (size_t i = 0; i < (size_t)Cursor::CursorCount; ++i)
//      m_cursors[i] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR + (int)i);
//
//   /// Fixes retina display-related font rendering issue (#185)
//   nvgBeginFrame(ctx, m_size[0], m_size[1], m_pixel_ratio);
//   nvgEndFrame(ctx);
//}
//
Screen::~Screen() {
   //__nanogui_screens.erase(m_glfw_window);
   //for (size_t i = 0; i < (size_t)Cursor::CursorCount; ++i) {
   //   if (m_cursors[i])
   //      glfwDestroyCursor(m_cursors[i]);
   }
//
//   if (ctx) {
//#if defined(NANOGUI_USE_OPENGL)
//      nvgDeleteGL3(ctx);
//#elif defined(NANOGUI_USE_GLES)
//      nvgDeleteGLES2(ctx);
//#elif defined(NANOGUI_USE_METAL)
//      nvgDeleteMTL(ctx);
//#endif
//   }
//
//   if (m_glfw_window && m_shutdown_glfw_on_destruct)
//      glfwDestroyWindow(m_glfw_window);
//}
//
//void Screen::set_visible(bool visible) {
//   if (m_visible != visible) {
//      m_visible = visible;
//
//      if (visible)
//         glfwShowWindow(m_glfw_window);
//      else
//         glfwHideWindow(m_glfw_window);
//   }
//}
//
//void Screen::set_caption(const std::string & caption) {
//   if (caption != m_caption) {
//      glfwSetWindowTitle(m_glfw_window, caption.c_str());
//      m_caption = caption;
//   }
//}
//
//void Screen::set_size(const Vector2i & size) {
//   Widget::set_size(size);
//
//#if defined(_WIN32) || defined(__linux__) || defined(EMSCRIPTEN)
//   glfwSetWindowSize(m_glfw_window, size.x() * m_pixel_ratio,
//      size.y() * m_pixel_ratio);
//#else
//   glfwSetWindowSize(m_glfw_window, size.x(), size.y());
//#endif
//}
//


void Screen::common_construct()
{
   
   m_pfontsink = m_puserinteraction->__create_new < ::nano2d::font_sink >();
   
   set_theme(new Theme());
   
}


void Screen::clear(NVGcontext * ctx)
{

#if defined(NANOGUI_USE_OPENGL) || defined(NANOGUI_USE_GLES)
   CHK(glClearColor(m_background[0], m_background[1], m_background[2], m_background[3]));
   CHK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
#elif defined(NANOGUI_USE_METAL)
   nvgClearWithColor(ctx, m_background);
#endif


   nvgBeginPath(ctx);
   nvgRect(ctx, (float)m_pos.x(), (float)m_pos.y(), (float)m_size.x(), (float)m_size.y());
   nvgFillColor(ctx, m_background);
   nvgFill(ctx);

}




void Screen::draw_setup(NVGcontext * ctx)
{
   
#if defined(NANOGUI_USE_OPENGL) || defined(NANOGUI_USE_GLES)
   glfwMakeContextCurrent(m_glfw_window);
#elif defined(NANOGUI_USE_METAL)
   void * nswin = glfwGetCocoaWindow(m_glfw_window);
   metal_window_set_size(nswin, m_fbsize);
   m_metal_drawable = metal_window_next_drawable(nswin);
   m_metal_texture = metal_drawable_texture(m_metal_drawable);
   mnvgSetColorTexture(ctx, m_metal_texture);
#endif

//#if !defined(EMSCRIPTEN)
//   glfwGetFramebufferSize(m_glfw_window, &m_fbsize[0], &m_fbsize[1]);
//   glfwGetWindowSize(m_glfw_window, &m_size[0], &m_size[1]);
//#else
//   emscripten_get_canvas_element_size("#canvas", &m_size[0], &m_size[1]);
//   m_fbsize = m_size;
//#endif

#if defined(_WIN32) || defined(__linux__) || defined(EMSCRIPTEN)
   //m_fbsize = m_size;
   //m_size = Vector2i(Vector2f(m_size) / m_pixel_ratio);
#else
   /* Recompute pixel ratio on OSX */
//   if (m_size[0])
//      m_pixel_ratio = (float)m_fbsize[0] / (float)m_size[0];
#if defined(NANOGUI_USE_METAL)
   metal_window_set_content_scale(nswin, m_pixel_ratio);
#endif
#endif

#if defined(NANOGUI_USE_OPENGL) || defined(NANOGUI_USE_GLES)
   CHK(glViewport(0, 0, m_fbsize[0], m_fbsize[1]));
#endif
}


void Screen::draw_teardown(NVGcontext * ctx) {
#if defined(NANOGUI_USE_OPENGL) || defined(NANOGUI_USE_GLES)
   glfwSwapBuffers(m_glfw_window);
#elif defined(NANOGUI_USE_METAL)
   mnvgSetColorTexture(ctx, nullptr);
   metal_present_and_release_drawable(m_metal_drawable);
   m_metal_texture = nullptr;
   m_metal_drawable = nullptr;
#endif
}

::image_pointer Screen::create_image(const ::size_i32 & size)
{

   return m_puserinteraction->m_pcontext->context_image()->create_image(size);

}

//
void Screen::draw_all(NVGcontext * ctx) 
{

   //if (!m_redraw)
   //{

   //   return;

   //}

   m_redraw = false;

#if defined(NANOGUI_USE_METAL)
      void * pool = autorelease_init();
#endif

      draw_setup(ctx);
      draw_contents(ctx);
      draw_widgets(ctx);
      draw_teardown(ctx);

#if defined(NANOGUI_USE_METAL)
      autorelease_release(pool);
#endif
  //}
}

void Screen::draw_contents(NVGcontext * ctx) 
{
   clear(ctx);
}
//
//void Screen::nvg_flush() {
//   NVGparams * params = nvgInternalParams(ctx);
//   params->renderFlush(params->userPtr);
//   params->renderViewport(params->userPtr, m_size[0], m_size[1], m_pixel_ratio);
//}
//

void Screen::draw(NVGcontext * ctx) 
{

   
   synchronous_lock lock(m_puserinteraction->mutex());

   //Widget::draw(ctx);
   //return;
   draw_all(ctx);

   //draw_widgets(ctx);

}
void Screen::draw_widgets(NVGcontext * ctx) {
   //nvgBeginFrame(ctx, m_size[0], m_size[1], m_pixel_ratio);

   //draw(ctx);

   Widget::draw(ctx);

   auto elapsed = m_last_interaction.elapsed();

   if (elapsed > 0.5_s) {
      /* Draw tooltips */
      const Widget * widget = find_widget(m_mouse_pos);
      if (widget && !widget->tooltip().empty()) {
         int tooltip_width = 150;

         float bounds[4];
         nvgFontFace(ctx, "sans");
         nvgFontSize(ctx, 15.0f);
         nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
         nvgTextLineHeight(ctx, 1.1f);
         Vector2i pos = widget->absolute_position() +
            Vector2i(widget->width() / 2, widget->height() + 10);

         nvgTextBounds(ctx, (float)pos.x(), (float)pos.y(),
            widget->tooltip().c_str(), nullptr, bounds);

         int h = (int) ((bounds[2] - bounds[0]) / 2.f);
         if (h > tooltip_width / 2) {
            nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_TOP);
            nvgTextBoxBounds(ctx, (float)pos.x(), (float)pos.y(), (float)tooltip_width,
               widget->tooltip().c_str(), nullptr, bounds);

            h = (int) ((bounds[2] - bounds[0]) / 2.f);
         }
         int shift = 0;

         if (pos.x() - h - 8 < 0) {
            /* Keep tooltips on screen */
            shift = pos.x() - h - 8;
            pos.x() -= shift;
            bounds[0] -= shift;
            bounds[2] -= shift;
         }

         nvgGlobalAlpha(ctx,
            minimum(1.f, 2.f * (elapsed - 0.5f)) * 0.8f);

         nvgBeginPath(ctx);
         nvgFillColor(ctx, Color(0, 255));
         nvgRoundedRect(ctx, bounds[0] - 4.f - h, bounds[1] - 4.f,
            (bounds[2] - bounds[0]) + 8.f,
            (bounds[3] - bounds[1]) + 8.f, 3.f);

         int px = (int)(((bounds[2] + bounds[0]) / 2.f) - h + shift);
         nvgMoveTo(ctx, (float)px, bounds[1] - 10.f);
         nvgLineTo(ctx, px + 7.f, bounds[1] + 1.f);
         nvgLineTo(ctx, px - 7.f, bounds[1] + 1.f);
         nvgFill(ctx);

         nvgFillColor(ctx, Color(255, 255));
         nvgFontBlur(ctx, 0.0f);
         nvgTextBox(ctx, (float)(pos.x() - h), (float)pos.y(), (float)tooltip_width,
            widget->tooltip().c_str(), nullptr);
      }
   }

   //nvgEndFrame(ctx);
}

bool Screen::keyboard_event(::user::enum_key ekey, int scancode, int action, const ::user::e_key & ekeyModifiers) {
   if (m_focus_path.size() > 0) {
      for (auto it = m_focus_path.rbegin() + 1; it != m_focus_path.rend(); ++it)
         if ((*it)->focused() && (*it)->keyboard_event(ekey, scancode, action, ekeyModifiers))
            return true;
   }

   return false;
}

bool Screen::keyboard_character_event(unsigned int codepoint) {
   if (m_focus_path.size() > 0) {
      for (auto it = m_focus_path.rbegin() + 1; it != m_focus_path.rend(); ++it)
         if ((*it)->focused() && (*it)->keyboard_character_event(codepoint))
            return true;
   }
   return false;
}

bool Screen::resize_event(const Vector2i & size) {
   if (m_resize_callback)
      m_resize_callback(size);
   //m_redraw = true;
   //draw_all();

   // m_puserinteraction->set_need_layout();


   return true;
}

//void Screen::redraw() {
//   if (!m_redraw) {
//      m_redraw = true;
//#if !defined(EMSCRIPTEN)
//      glfwPostEmptyEvent();
//#endif
//   }
//}
//

bool Screen::on_mouse_move(const ::point_i32 & point, const ::user::e_key & ekeyModifiers)
{
   Vector2i p((int)point.x, (int)point.y);

//#if defined(_WIN32) || defined(__linux__) || defined(EMSCRIPTEN)
//   p = Vector2i(Vector2f(p) / m_pixel_ratio);
//#endif

//   m_last_interaction = glfwGetTime();
   m_last_interaction.Now();
   //try {
      p -= Vector2i(1, 2);

      bool ret = false;
      if (!m_drag_active || !m_drag_widget) {
         //Widget * widget = find_widget(p);
         //if (widget != nullptr && widget->cursor() != m_cursor) {
           // m_cursor = widget->cursor();
            //glfwSetCursor(m_glfw_window, m_cursors[(int)m_cursor]);
         //}
      }
      else 
      {

         if (!screen()->m_pwidgetLeftButtonDown)
         {

            ret = m_drag_widget->mouse_drag_event(p - m_drag_widget->parent()->absolute_position(), p - m_mouse_pos, ekeyModifiers);

         }

      }

      if (!ret)
      {

         ret = Widget::mouse_motion_event(p, p - m_mouse_pos, ekeyModifiers);

      }

      m_mouse_pos = p;
      m_redraw |= ret;

      if (m_redraw)
      {

         if (m_puserinteraction)
         {

            m_puserinteraction->set_need_redraw();

            m_puserinteraction->post_redraw();

         }

      }
   //}
   //catch()
   //catch (const std::exception & e) {
     // std::cerr << "Caught exception in event handler: " << e.what() << std::endl;
   //}
      return ret;
}


void Screen::on_close()
{


}


bool Screen::mouse_button_event(const Vector2i & p, int button, bool down, const ::user::e_key & ekeyModifiers)
{
   m_modifiers = ekeyModifiers;
  // m_last_interaction = glfwGetTime();
   m_last_interaction.Now();

//#if defined(__APPLE__)
   //if (button == GLFW_MOUSE_BUTTON_1 && modifiers == GLFW_MOD_CONTROL)
      //button = GLFW_MOUSE_BUTTON_2;
//#endif

   //try {
      if (m_focus_path.size() > 1) {
         const Window * window =
            dynamic_cast<Window *>(m_focus_path[m_focus_path.size() - 2]);
         if (window && window->modal()) {
            if (!window->contains(m_mouse_pos))
               return false;
         }
      }

      ////if (action == GLFW_PRESS)
      //if (down)
      //{
      //   m_mouse_state |= 1 << button;

      //}
      //else
      //   m_mouse_state &= ~(1 << button);

      auto drop_widget = find_widget(m_mouse_pos);
      //if (m_drag_active && action == GLFW_RELEASE &&
      if (m_drag_active && !down && m_drag_widget && drop_widget != m_drag_widget
         && m_pwidgetLeftButtonDown== nullptr)
      {

         m_redraw |= m_drag_widget->mouse_button_event(
            m_mouse_pos - m_drag_widget->parent()->absolute_position(), button,
            false, ekeyModifiers);
         
      }

 /*     if (drop_widget != nullptr && drop_widget->cursor() != m_cursor) {
         m_cursor = drop_widget->cursor();
         glfwSetCursor(m_glfw_window, m_cursors[(int)m_cursor]);
      }*/

      //bool btn12 = button == GLFW_MOUSE_BUTTON_1 || button == GLFW_MOUSE_BUTTON_2;
      bool btn12 = button == __MOUSE_LEFT_BUTTON || button == __MOUSE_RIGHT_BUTTON;

      //if (!m_drag_active && action == GLFW_PRESS && btn12) {
      if (!m_drag_active && down && btn12) {
         m_drag_widget = find_widget(m_mouse_pos);
         if (m_drag_widget == this)
            m_drag_widget = nullptr;
         m_drag_active = m_drag_widget != nullptr;
         if (!m_drag_active)
            update_focus(nullptr);
      }
      //else if (m_drag_active && action == GLFW_RELEASE && btn12) {
      else if (m_drag_active && !down && btn12) {
         m_drag_active = false;
         m_drag_widget = nullptr;
      }

      bool bRet = Widget::mouse_button_event(m_mouse_pos, button,
         down, m_modifiers);
      m_redraw |= bRet;
  //   action == GLFW_PRESS, m_modifiers);
   //}
   //catch (const std::exception & e) {
   //   std::cerr << "Caught exception in event handler: " << e.what() << std::endl;
   //}
      if (!down)
      {
         m_pwidgetLeftButtonDown = nullptr;
      }
      return bRet;
}

//void Screen::key_callback_event(int key, int scancode, int action, int mods) {
//   m_last_interaction = glfwGetTime();
//   try {
//      m_redraw |= keyboard_event(key, scancode, action, mods);
//   }
//   catch (const std::exception & e) {
//      std::cerr << "Caught exception in event handler: " << e.what() << std::endl;
//   }
//}
//
//void Screen::char_callback_event(unsigned int codepoint) {
//   m_last_interaction = glfwGetTime();
//   try {
//      m_redraw |= keyboard_character_event(codepoint);
//   }
//   catch (const std::exception & e) {
//      std::cerr << "Caught exception in event handler: " << e.what() << std::endl;
//   }
//}
//
//void Screen::drop_callback_event(int count, const char ** filenames) {
//   std::vector<std::string> arg(count);
//   for (int i = 0; i < count; ++i)
//      arg[i] = filenames[i];
//   m_redraw |= drop_event(arg);
//}
//
//void Screen::scroll_callback_event(double x, double y) {
//   m_last_interaction = glfwGetTime();
//   try {
//      if (m_focus_path.size() > 1) {
//         const Window * window =
//            dynamic_cast<Window *>(m_focus_path[m_focus_path.size() - 2]);
//         if (window && window->modal()) {
//            if (!window->contains(m_mouse_pos))
//               return;
//         }
//      }
//      m_redraw |= scroll_event(m_mouse_pos, Vector2f(x, y));
//   }
//   catch (const std::exception & e) {
//      std::cerr << "Caught exception in event handler: " << e.what() << std::endl;
//   }
//}
//
//void Screen::resize_callback_event(int, int) {
//#if defined(EMSCRIPTEN)
//   return;
//#endif
//
//   Vector2i fb_size, size;
//   glfwGetFramebufferSize(m_glfw_window, &fb_size[0], &fb_size[1]);
//   glfwGetWindowSize(m_glfw_window, &size[0], &size[1]);
//   if (fb_size == Vector2i(0, 0) || size == Vector2i(0, 0))
//      return;
//   m_fbsize = fb_size; m_size = size;
//
//#if defined(_WIN32) || defined(__linux__) || defined(EMSCRIPTEN)
//   m_size = Vector2i(Vector2f(m_size) / m_pixel_ratio);
//#endif
//
//   m_last_interaction = glfwGetTime();
//
//#if defined(NANOGUI_USE_METAL)
//   if (m_depth_stencil_texture)
//      m_depth_stencil_texture->resize(fb_size);
//#endif
//
//   try {
//      resize_event(m_size);
//   }
//   catch (const std::exception & e) {
//      std::cerr << "Caught exception in event handler: " << e.what() << std::endl;
//   }
//   redraw();
//}

void Screen::update_focus(Widget * widget) {
   for (auto w : m_focus_path) {
      if (!w->focused())
         continue;
      w->focus_event(false);
   }
   m_focus_path.clear();
   Widget * window = nullptr;
   while (widget) {
      m_focus_path.push_back(widget);
      if (dynamic_cast<Window *>(widget))
         window = widget;
      widget = widget->parent();
   }
   for (auto it = m_focus_path.rbegin(); it != m_focus_path.rend(); ++it)
      (*it)->focus_event(true);

   if (window)
      move_window_to_front((Window *)window);
}

void Screen::dispose_window(Window * window) {
   if (std::find(m_focus_path.begin(), m_focus_path.end(), window) != m_focus_path.end())
      m_focus_path.clear();
   if (m_drag_widget == window)
      m_drag_widget = nullptr;
   remove_child(window);
}

void Screen::center_window(Window * window, NVGcontext * pcontext) {
   if (window->size() == 0) {
      window->set_size(window->preferred_size(pcontext));
      window->perform_layout(pcontext);
   }
   window->set_position((m_size - window->size()) / 2);
}

void Screen::move_window_to_front(Window * window) {
   m_children.erase(std::remove(m_children.begin(), m_children.end(), window), m_children.end());
   m_children.push_back(window);
   /* Brute force topological sort (no problem for a few windows..) */
   bool changed = false;
   do {
      size_t base_index = 0;
      for (size_t index = 0; index < m_children.size(); ++index)
         if (m_children[index] == window)
            base_index = index;
      changed = false;
      for (size_t index = 0; index < m_children.size(); ++index) {
         Popup * pw = dynamic_cast<Popup *>(m_children[index]);
         if (pw && pw->parent_window() == window && index < base_index) {
            move_window_to_front(pw);
            changed = true;
            break;
         }
      }
   } while (changed);

   m_puserinteraction->set_need_redraw();

   m_puserinteraction->post_redraw();

}

//bool Screen::tooltip_fade_in_progress() const {
//   double elapsed = glfwGetTime() - m_last_interaction;
//   if (elapsed < 0.25f || elapsed > 1.25f)
//      return false;
//   /* Temporarily increase the frame rate to fade in the tooltip */
//   const Widget * widget = find_widget(m_mouse_pos);
//   return widget && !widget->tooltip().empty();
//}
//
//Texture::PixelFormat Screen::pixel_format() const {
//#if defined(NANOGUI_USE_METAL)
//   if (!m_float_buffer)
//      return Texture::PixelFormat::BGRA;
//#endif
//   return Texture::PixelFormat::RGBA;
//}
//
//Texture::ComponentFormat Screen::component_format() const {
//   if (m_float_buffer)
//      return Texture::ComponentFormat::Float16;
//   else
//      return Texture::ComponentFormat::UInt8;
//}
//
//#if defined(NANOGUI_USE_METAL)
//void * Screen::metal_layer() const {
//   return metal_window_layer(glfwGetCocoaWindow(m_glfw_window));
//}
//#endif

void Screen::set_size(const Vector2i & size)
{

   Widget::set_size(size);

   if (m_puserinteraction)
   {

      if (m_puserinteraction->width() != size.x()
         || m_puserinteraction->height() != size.y())
      {

         //m_puserinteraction->move_to(::size_i32(m_pos.v[0], m_pos.v[1]));

         m_puserinteraction->set_size(::size_i32(m_size.v[0], m_size.v[1]));

         m_puserinteraction->set_need_layout();

         m_puserinteraction->set_need_redraw();

         m_puserinteraction->post_redraw();

      }

   }

}


void Screen::set_user_interaction(::user::interaction * puserinteraction)
{

   ::appearance::appearance::set_user_interaction(puserinteraction);

   m_size.x() = puserinteraction->width();

   m_size.y() = puserinteraction->height();

   puserinteraction->set_need_layout();

   puserinteraction->set_need_redraw();

   puserinteraction->post_redraw();
   
}


::size_i32 Screen::preferred_size(::draw2d::graphics_pointer & pgraphics)
{

   ::nano2d::draw2d_context context;

   context.set_graphics(pgraphics);
   
   context.set_font_sink(m_pfontsink);
   
   auto array = preferred_size(&context);

   return { array.v[0], array.v[1] };

}


void Screen::perform_layout(::draw2d::graphics_pointer & pgraphics)
{

   ::nano2d::draw2d_context context;

   context.set_graphics(pgraphics);
   
   context.set_font_sink(m_pfontsink);
   
   auto size = m_puserinteraction->get_size();

   set_size({ (int)size.cx, (int)size.cy });

   resize_event(m_size);

   perform_layout(&context);

   /*if (m_puserinteraction)
   {

      auto r = m_puserinteraction->get_client_rect();
      m_size.x() = r.width();
      m_size.y() = r.height();
   }*/

}


void Screen::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   ::nano2d::draw2d_context context;

   context.set_graphics(pgraphics);
   
   context.set_font_sink(m_pfontsink);

   pgraphics->OffsetViewportOrg(-m_pos.x(), -m_pos.y());

   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   draw(&context);

}


void Screen::on_mouse_enter(const ::point_i32 & point, const ::user::e_key & ekeyModifiers)
{

   Vector2i p(point.x, point.y);

   mouse_enter_event(p, 1, ekeyModifiers);

}


void Screen::on_mouse_leave()
{

   Vector2i p(0, 0);

   mouse_enter_event(p, 0, ::user::e_key_none);

}

int user_key_to_nano2d_button(::user::e_key ekeyButton)
{

   if (ekeyButton == ::user::e_key_left_button)
   {

      return __MOUSE_LEFT_BUTTON;

   }
   else if (ekeyButton == ::user::e_key_right_button)
   {

      return __MOUSE_RIGHT_BUTTON;

   }
   else
   {

      return -1;

   }

}

bool Screen::on_button_down(::user::e_key ekeyButton, const ::point_i32 & point, const ::user::e_key & ekeyModifiers)
{

   Vector2i p(point.x, point.y);

   p += m_pos;

   int iNanoGuiButton = user_key_to_nano2d_button(ekeyButton);

   bool bRet = mouse_button_event(p, iNanoGuiButton, 1, ekeyModifiers);

   return bRet;

}


bool Screen::on_button_up(::user::e_key ekeyButton, const ::point_i32 & point, const ::user::e_key & ekeyModifiers)
{

   Vector2i p(point.x, point.y);

   p += m_pos;

   int iNanoGuiButton = user_key_to_nano2d_button(ekeyButton);

   bool bRet = mouse_button_event(p, iNanoGuiButton, 0, ekeyModifiers);

   return bRet;

}


//bool Screen::on_mouse_move(const ::point_i32 & point)
//{
//
//   Vector2i p(point.x, point.y);
//
//   p += m_pos;
//
//   Vector2i rel(m_pointMouseLast.x, m_pointMouseLast.y);
//
//   rel += m_pos;
//
//   return mouse_motion_event(p, rel, 0, 0);
//
//}
//

bool Screen::on_mouse_drag(const ::point_i32 & point, const ::user::e_key & ekeyModifiers)
{

   Vector2i p(point.x, point.y);

   p += m_pos;

   Vector2i rel(m_pointMouseLast.x, m_pointMouseLast.y);

   rel += m_pos;

   return mouse_drag_event(p, rel, ekeyModifiers);

}


bool Screen::on_key_down(::user::enum_key ekey, ::i64 scancode, const ::user::e_key & ekeyModifiers)
{

   return keyboard_event(ekey, (int) scancode, e_message_key_down, ekeyModifiers);

}


bool Screen::on_key_up(::user::enum_key ekey, ::i64 scancode, const ::user::e_key & ekeyModifiers)
{

   return keyboard_event(ekey, (int) scancode, e_message_key_up, ekeyModifiers);

}


bool Screen::on_scroll_event(const ::point_i32 & point, double x, double y)
{

   return scroll_event({ point.x, point.y }, { (float)x, (float)y });

}


void Screen::on_character(int iCharacter)
{

   keyboard_character_event(iCharacter);

}


NAMESPACE_END(nanogui)



