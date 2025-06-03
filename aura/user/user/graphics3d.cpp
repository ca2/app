#include "framework.h"
#include "graphics3d.h"
#include "aura/graphics/gpu/context.h"
#include "aura/graphics/graphics3d/engine.h"
#include "aura/graphics/graphics3d/input.h"
#include "acme/constant/message.h"
#include "acme/graphics/image/image32.h"
#include "acme/handler/topic.h"
#include "acme/platform/node.h"
#include "acme/platform/session.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/target.h"
#include "aura/message/user.h"
#include "aura/graphics/graphics3d/types.h"
#include "aura/platform/application.h"
//#include "vulkan/vk_container.h"


int run_vulkan_example();

int run_vulkan_example2(const ::image32_callback& callback);

int run_vulkan_example5(::graphics3d::mouse_state* pmousestate, const ::image32_callback& callback);


//namespace vulkan
//{
//
//
//   ::pointer<::vulkan::application > start_offscreen_application(vkc::VkContainer* pvkcontainer, mouse_state* pmousestate);
//
//
//} // namespace vulkan
//




//#include "aura/update.h"
//#include <math.h>
// http://stackoverflow.com/questions/4052940/how-to-make-an-opengl-rendering-context-with-transparent-background
//http://stackoverflow.com/users/176769/karlphillip
//#include <windows.h>
//#ifdef WINDOWS
//#include <windowsx.h>
//#endif

//
//#ifdef LINUX
//
//#define WIDTH 3200
//#define HEIGHT 1800f
//
//const int sbAttrib[] = {GLX_DOUBLEBUFFER, 0, GLX_RED_SIZE, 1,GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1,GLX_ALPHA_SIZE, 1, GLX_DEPTH_SIZE, 16,None};
//int pbAttrib[] = {GLX_PBUFFER_WIDTH, WIDTH,GLX_PBUFFER_HEIGHT, HEIGHT,GLX_PRESERVED_CONTENTS, True,None };
//
//#endif
//
//
////extern CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time1;
//GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.00f };
//GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.00f };
//GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.00f };
////GLfloat LightPosition2[] = { -5.0f, -5.0f, 32.0f, 1.00f };

//#ifdef WINDOWS
//typedef BOOL(WINAPI * PFNWGLDESTROYPBUFFERARBPROC) (HPBUFFERARB hPbuffer);
//typedef BOOL(WINAPI * PFNWGLQUERYPBUFFERARBPROC) (HPBUFFERARB hPbuffer, int iAttribute, int *piValue);
//typedef HDC(WINAPI * PFNWGLGETPBUFFERDCARBPROC) (HPBUFFERARB hPbuffer);
//typedef HPBUFFERARB(WINAPI * PFNWGLCREATEPBUFFERARBPROC) (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int *piAttribList);
//typedef int (WINAPI * PFNWGLRELEASEPBUFFERDCARBPROC) (HPBUFFERARB hPbuffer, HDC hDC);
//
//PFNWGLDESTROYPBUFFERARBPROC                       wglDestroyPbufferARB;
//PFNWGLQUERYPBUFFERARBPROC                         wglQueryPbufferARB;
//PFNWGLGETPBUFFERDCARBPROC                         wglGetPbufferDCARB;
//PFNWGLCREATEPBUFFERARBPROC                        wglCreatePbufferARB;
//PFNWGLRELEASEPBUFFERDCARBPROC                     wglReleasePbufferDCARB;
//
//
//typedef BOOL(WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, unsigned int nMaxFormats, int *piFormats, unsigned int *nNumFormats);
//typedef BOOL(WINAPI * PFNWGLGETPIXELFORMATATTRIBFVARBPROC) (HDC hdc, int iPixelFormat, int iLayerPlane, unsigned int nAttributes, const int *piAttributes, FLOAT *pfValues);
//typedef BOOL(WINAPI * PFNWGLGETPIXELFORMATATTRIBIVARBPROC) (HDC hdc, int iPixelFormat, int iLayerPlane, unsigned int nAttributes, const int *piAttributes, int *piValues);
//
//PFNWGLCHOOSEPIXELFORMATARBPROC                    wglChoosePixelFormatARB;
//PFNWGLGETPIXELFORMATATTRIBFVARBPROC               wglGetPixelFormatAttribfvARB;
//PFNWGLGETPIXELFORMATATTRIBIVARBPROC               wglGetPixelFormatAttribivARB;
//
//
//#endif

#include <assert.h>
#ifdef WINDOWS
#include <tchar.h>
#endif // WINDOWS
//#ifdef  assert
//#define verify(expr) if(!expr) assert(0)
//#else verify(expr) expr
//#endif



namespace user
{



   graphics3d::graphics3d()
   {

      m_emouse = ::graphics3d::e_mouse_updateLook;
      m_ekeyboard = ::graphics3d::e_keyboard_updateMovement;
      ////m_bAbsoluteMousePosition = false;
      //m_bShouldClose = false;
      m_bFrameBufferResized = false;

   }


   graphics3d::~graphics3d()
   {

   }
   //::block graphics3d::global_ubo()
   //{

   //   return {};

   //}

   void graphics3d::install_message_routing(::channel* pchannel)
   {

      ::user::box::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &graphics3d::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &graphics3d::on_message_destroy);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &graphics3d::on_message_key_down);
      MESSAGE_LINK(e_message_key_up, pchannel, this, &graphics3d::on_message_key_up);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &graphics3d::on_message_mouse_move);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &graphics3d::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &graphics3d::on_message_left_button_up);
      MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &graphics3d::on_message_mouse_leave);

   }


   bool graphics3d::keyboard_focus_is_focusable()
   {

      return true;

   }


   void graphics3d::on_message_key_down(::message::message* pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      pmessage->m_bRet = true;

   }


   void graphics3d::on_message_key_up(::message::message* pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      pmessage->m_bRet = true;

   }


   void graphics3d::on_message_mouse_move(::message::message* pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmessage->m_bRet = true;

      if (m_pengine)
      {

         auto point = pmouse->m_pointHost;

         host_to_client()(point);

         on_mouse_move(point);

      }

   }


   void graphics3d::on_mouse_move(const int_point & point)
   {

      auto pengine = m_pengine;

      if (pengine)
      {

         auto pinput = pengine->m_pinput;

         if (pinput)
         {

            pinput->_001OnMouseMove(point);

         }

      }

   }


   void graphics3d::defer_initialize_engine(const ::int_rectangle& rectanglePlacement)
   {

      if (!m_pengine)
      {

         ::string strImplementation = get_app()->graphics3d_get_implementation_name();

         auto pfactoryGpu = system()->factory("gpu", strImplementation);

         pfactoryGpu->merge_to_global_factory();

         auto pfactoryGraphics3d = system()->factory("graphics3d", strImplementation);

         pfactoryGraphics3d->merge_to_global_factory();

         m_pkeymap = get_default_key_map();

         m_pkeymap->m_pimpact = this;

         __øconstruct(m_pengine);

         m_pengine->initialize_engine(this);

         m_pengine->defer_start(this, rectanglePlacement);

      }

   }


   void graphics3d::on_load_engine()
   {

      m_pengine->m_pinput->m_fMoveSpeed = 3.f;
      m_pengine->m_pinput->m_fLookSpeed =  1.5f;

   }


   void graphics3d::on_message_mouse_leave(::message::message* pmessage)
   {

      on_mouse_out();

   }


   void graphics3d::on_mouse_out()
   {

      if (m_emouse == ::graphics3d::e_mouse_updateLook)
      {

         m_pengine->m_pinput->_001OnMouseOut();

      }

   }


   void graphics3d::on_message_left_button_down(::message::message* pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmessage->m_bRet = true;

      auto point = pmouse->m_pointHost;

      host_to_client()(point);

      m_pengine->m_pinput->m_mousestate.m_position.x = (float) point.x();
      m_pengine->m_pinput->m_mousestate.m_position.y = (float) point.y();
      m_pengine->m_pinput->m_mousestate.m_buttons.left = true;

      set_mouse_capture();

   }


   void graphics3d::on_message_left_button_up(::message::message* pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmessage->m_bRet = true;

      release_mouse_capture();

      auto point = pmouse->m_pointHost;

      host_to_client()(point);

      m_pengine->m_pinput->m_mousestate.m_position.x = (float) point.x();
      m_pengine->m_pinput->m_mousestate.m_position.y = (float) point.y();
      m_pengine->m_pinput->m_mousestate.m_buttons.left = false;

      

   }


   //::pointer < ::graphics3d::application > graphics3d::start_graphics3d_application()
   //{

   //   auto p3dapplication = get_app()->start_graphics3d_aplication();

   //   p3dapplication->initialize_application(this);

   //   //p3dapplication->m_pmousestate = &m_mousestate;

   //   return p3dapplication;
   //   //return ::vulkan::start_offscreen_application(this, &m_mousestate);

   //}


   //::int_size graphics3d::size()
   //{

   //   return this->raw_rectangle().size();

   //}


   void graphics3d::on_message_create(::message::message* pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      //get_app()->m_pimpact = this;


   }


   void graphics3d::on_message_destroy(::message::message* pmessage)
   {

   }


   void graphics3d::on_timer(::timer* ptimer)
   {

   }


   void graphics3d::handle(::topic* ptopic, ::handler_context* phandlercontext)
   {

      if (ptopic->id() == id_initial_update)
      {

         //::pointer<::userex::pane_tab_impact>ppaneimpact = get_typed_parent < ::userex::pane_tab_impact >();
         ////if(ppaneimpact.is_set())
         ////{
         ////   ppaneimpact->m_pflagview = this;
         ////}

      }

      __UNREFERENCED_PARAMETER(ptopic);

   }


   void graphics3d::_001OnNcClip(::draw2d::graphics_pointer& pgraphics)
   {

      ::user::box::_001OnNcClip(pgraphics);

   }


   void graphics3d::_001OnClip(::draw2d::graphics_pointer& pgraphics)
   {

      ::user::box::_001OnClip(pgraphics);

   }


   void graphics3d::_001OnNcDraw(::draw2d::graphics_pointer& pgraphics)
   {

      ::user::box::_001OnNcDraw(pgraphics);

   }


   void graphics3d::_001OnDraw(::draw2d::graphics_pointer& pgraphics)
   {

      ////return;

      //pgraphics->fill_solid_rectangle(::int_rectangle_dimension(10, 10, 100, 100), argb(128, 200, 220, 255));

      ////return;

      //pgraphics->fill_solid_rectangle(::int_rectangle_dimension(110, 100, 100, 100), argb(255, 200, 220, 255));

      //auto ppen = __øcreate < ::draw2d::pen > ();

      //ppen->create_solid(10, argb(200, 20, 155, 50));

      //pgraphics->set(ppen);

      //pgraphics->draw_line(::double_point( 0.0, 0.0 ), ::double_point(300.0, 300.0));

      //pgraphics->fill_solid_rectangle(::int_rectangle_dimension(10, 150, 100, 100), argb(128, 100, 255, 120));

      //pgraphics->fill_solid_rectangle(::int_rectangle_dimension(110, 150, 100, 100), argb(255, 100, 255, 120));

      //auto ppen2 = __øcreate < ::draw2d::pen > ();

      //ppen2->create_solid(5, argb(200, 20, 155, 50));

      //pgraphics->set(ppen2);

      //pgraphics->draw_line(::double_point(300.0, 0.0), ::double_point(100.0, 300.0));

      //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

      if (1)
      {
         m_pengine->_001OnDraw(pgraphics);

      }

   }


   void graphics3d::_001OnNcPostDraw(::draw2d::graphics_pointer& pgraphics)
   {


   }


   //::user::document* graphics3d::get_document()
   //{

   //   return  (::user::box::get_document());

   //}


   ::user::enum_key_state graphics3d::get_key_state(::user::e_key ekey)
   {

      if (session()->is_key_pressed(ekey))
      {

         return ::user::e_key_state_pressed;

      }

      return ::user::e_key_state_none;

   }


   void graphics3d::on_layout(::draw2d::graphics_pointer& pgraphics)
   {

      auto rectangleX = this->rectangle();

      if (rectangleX.area() <= 0)
      {

         return;

      }

      auto size = rectangleX.size();

      m_iWidth = size.width();

      m_iHeight = size.height();

      if (!m_pengine)
      {

         defer_initialize_engine(this->host_rectangle());

      }
      else if(m_pengine->has_ok_flag())
      {

         m_pengine->on_layout(this->host_rectangle());

      }

      //reset_mouse_last_position();

   }

   //
   //void container::initWindow() 
   //{
   //   //glfwInit();
   //   //glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
   //   //glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

   //   //window = glfwCreateWindow(m_iWidth, m_iHeight, windowName.c_str(), nullptr, nullptr);
   //   //glfwSetWindowUserPointer(window, this);
   //   //glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
   //}


   //::user::enum_key_state graphics3d::get_key_state(::user::e_key ekey)
   //{

   //   return ::user::e_key_state_none;

   //}


   //bool container::is_absolute_mouse_position()
   //{


   //	return true;

   //}

   //void container::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
   //	if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
   //		throw ::exception(error_failed, "Failed to create window surface");
   //	}
   //}

   /*void container::framebufferResizeCallback(GLFWwindow* window, int m_iWidth, int m_iHeight) {
      auto Window = reinterpret_cast<container*>(glfwGetWindowUserPointer(window));
      Window->framebufferResized = true;
      Window->m_iWidth = m_iWidth;
      Window->m_iHeight = m_iHeight;
   }*/


   //bool graphics3d::is_absolute_mouse_position()
   //{

   //   return false;

   //}


   //bool graphics3d::shouldClose()
   //{

   //   return m_bShouldClose;

   //}


   //::int_size container::size()
   //{

   //   return {};

   //}


   bool graphics3d::wasWindowResized()
   {

      return m_bFrameBufferResized;


   }


   void graphics3d::resetWindowResizedFlag()
   {

      m_bFrameBufferResized = false;

   }


   ::pointer < ::graphics3d::key_map > graphics3d::get_default_key_map()
   {

      auto pmap = __create_new < ::graphics3d::key_map>();
      using namespace ::graphics3d;

      pmap->map(e_key_moveLeft, ::user::e_key_a);
      pmap->map(e_key_moveRight, ::user::e_key_d);
      pmap->map(e_key_moveForward, ::user::e_key_w);
      pmap->map(e_key_moveBackward, ::user::e_key_s);
      pmap->map(e_key_moveUp, ::user::e_key_e);
      pmap->map(e_key_moveDown, ::user::e_key_q);
      pmap->map(e_key_lookLeft, ::user::e_key_left);
      pmap->map(e_key_lookRight, ::user::e_key_right);
      pmap->map(e_key_lookUp, ::user::e_key_up);
      pmap->map(e_key_lookDown, ::user::e_key_down);
      pmap->map(e_key_Exit, ::user::e_key_escape);

      return pmap;

   }
   
   
   float graphics3d::getAspectRatio()
   {

      auto fH = fabs(static_cast<float>(this->height()));

      if (fH <= 0.00001)
      {

         return 1.0f;

      }

      return static_cast<float>(this->width()) / fH;

   }


   void graphics3d::prepare_mouse_input()
   {

      if (m_emouse == ::graphics3d::e_mouse_updateLook)
      {

         m_pengine->m_pinput->_001PrepareMouseInput();

      }

   }


   void graphics3d::process_mouse_input()
   {

      if (m_emouse == ::graphics3d::e_mouse_updateLook)
      {

         m_pengine->m_pinput->process_mouse_input_updateLook();

      }

   }


   void graphics3d::process_keyboard_input()
   {

      if (m_ekeyboard == ::graphics3d::e_keyboard_updateMovement)
      {

         m_pengine->m_pinput->process_keyboard_input_updateMovement();

      }
      else if (m_ekeyboard == ::graphics3d::e_keyboard_spaceExplorer)
      {

         m_pengine->m_pinput->process_keyboard_input_spaceExplorer();

      }

   }


} // namespace user



