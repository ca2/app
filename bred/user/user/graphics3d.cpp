#include "framework.h"
#include "graphics3d.h"
#include "acme/exception/interface_only.h"
#include "bred/gpu/context.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/input.h"
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
#include "bred/graphics3d/types.h"
#include "aura/platform/application.h"
#include "bred/gpu/graphics.h"
#include "bred/gpu/renderer.h"



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


   ::pointer < ::graphics3d::scene > graphics3d::create_main_scene()
   {

      throw ::interface_only();

      return {};

   }


   void graphics3d::on_load_engine()
   {

      m_pengine->m_pinput->m_fMoveSpeed = 3.f;
      m_pengine->m_pinput->m_fLookSpeed =  1.5f;

      auto psceneMain = create_main_scene();

      m_pengine->set_current_scene(psceneMain);



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

      //return;

      ::int_rectangle rectangleHostUpperLayer;

      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         rectangleHostUpperLayer = pgraphics->end_gpu_layer();

      }
            
      if (1)
      {

         if (m_papplication->m_gpu.m_bUseSwapChainWindow)
         {

            auto rectangleHost = host_rectangle();

            m_pengine->m_pgpurendererGraphics3D->start_layer(rectangleHost);

         }

         m_pengine->_001OnDraw(pgraphics);

         if (m_papplication->m_gpu.m_bUseSwapChainWindow)
         {

            m_pengine->m_pgpurendererGraphics3D->end_layer();

         }

      }

      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         pgraphics->start_gpu_layer(rectangleHostUpperLayer);

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



