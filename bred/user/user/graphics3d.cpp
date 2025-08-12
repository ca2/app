#include "framework.h"
#include "graphics3d.h"
#include "acme/exception/interface_only.h"
#include "bred/gpu/context.h"
#include "bred/gpu/frame.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/input.h"
#include "bred/graphics3d/scene.h"
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

      if (!m_pengine)
      {

         return;

      }

      if (!m_pengine->m_bLoadedEngine)
      {

         return;

      }

      //return;

      ::cast < ::gpu::compositor > pcompositor = pgraphics;

      //::gpu::frame* pgpuframe = nullptr;

      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         if(pcompositor)
         {

            pcompositor->gpu_context()->m_pgpurenderer->frame_suffix();

            //double_rectangle r;

            //r.left() = 400.0;
            //r.top() = 200.0;
            //r.set_size(50.0, 50.0);

            //pgraphics->fill_solid_rectangle(r, argb(1.0, 0.5, 0.75, 0.95));
            //
            //pgpuframe = pcompositor->end_gpu_layer(::gpu::current_frame());

         }

      }
            
      if (1)
      {

         m_pengine->_001OnDraw(pgraphics);

      }

      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         if (pcompositor)
         {

            pcompositor->gpu_context()->m_pgpurenderer->frame_prefix();
            //pcompositor->start_gpu_layer(pgpuframe);

         }

      }

   }


   void graphics3d::_001OnNcPostDraw(::draw2d::graphics_pointer& pgraphics)
   {


   }


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

      pmap->map_base(e_key_moveLeft, ::user::e_key_a);
      pmap->map_base(e_key_moveRight, ::user::e_key_d);
      pmap->map_base(e_key_moveForward, ::user::e_key_w);
      pmap->map_base(e_key_moveBackward, ::user::e_key_s);
      pmap->map_base(e_key_moveUp, ::user::e_key_e);
      pmap->map_base(e_key_moveDown, ::user::e_key_q);
      pmap->map_base(e_key_lookLeft, ::user::e_key_left);
      pmap->map_base(e_key_lookRight, ::user::e_key_right);
      pmap->map_base(e_key_lookUp, ::user::e_key_up);
      pmap->map_base(e_key_lookDown, ::user::e_key_down);
      pmap->map_base(e_key_Exit, ::user::e_key_escape);

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



