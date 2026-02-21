#include "framework.h"
#include "graphics3d.h"
#include "acme/constant/id.h"
#include "acme/exception/interface_only.h"
#include "bred/gpu/block.h"
#include "bred/gpu/context.h"
#include "bred/gpu/frame.h"
#include "bred/graphics3d/asset_manager.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/input.h"
#include "bred/graphics3d/scene_base.h"
#include "acme/constant/user_message.h"
#include "acme/graphics/image/image32.h"
#include "acme/handler/topic.h"
#include "acme/platform/node.h"
#include "acme/platform/session.h"
#include "aura/graphics/draw2d/draw2d.h"
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
#include "bred/prodevian/immersion.h"


namespace user
{


   graphics3d::graphics3d()
   {

      //m_emouse = ::graphics3d::e_mouse_updateLook;
      //m_ekeyboard = ::graphics3d::e_keyboard_updateMovement;
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

      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &graphics3d::on_message_create);
      USER_MESSAGE_LINK(::user::e_message_destroy, pchannel, this, &graphics3d::on_message_destroy);
      USER_MESSAGE_LINK(::user::e_message_key_down, pchannel, this, &graphics3d::on_message_key_down);
      USER_MESSAGE_LINK(::user::e_message_key_up, pchannel, this, &graphics3d::on_message_key_up);
      USER_MESSAGE_LINK(::user::e_message_mouse_move, pchannel, this, &graphics3d::on_message_mouse_move);
      USER_MESSAGE_LINK(::user::e_message_left_button_down, pchannel, this, &graphics3d::on_message_left_button_down);
      USER_MESSAGE_LINK(::user::e_message_left_button_up, pchannel, this, &graphics3d::on_message_left_button_up);
      USER_MESSAGE_LINK(::user::e_message_mouse_leave, pchannel, this, &graphics3d::on_message_mouse_leave);

   }


   bool graphics3d::keyboard_focus_is_focusable()
   {

      return true;

   }


   void graphics3d::on_message_key_down(::message::message* pmessage)
   {

      //auto pkey = pmessage->m_union.m_pkey;

      pmessage->m_bRet = true;

   }


   void graphics3d::on_message_key_up(::message::message* pmessage)
   {

      //auto pkey = pmessage->m_union.m_pkey;

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

         track_mouse_leave();

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

         øconstruct(m_pengine);

         m_pengine->initialize_engine(this);

         m_pengine->defer_start(this, rectanglePlacement);

      }

   }


   ::pointer < ::prodevian::immersion > graphics3d::create_immersion()
   {

      throw ::interface_only();

      return {};

   }


   void graphics3d::on_load_engine()
   {

      auto pgpucontextEngine = m_pengine->gpu_context();

      pgpucontextEngine->m_pengine = m_pengine;

      auto pimmersion = create_immersion();

      pimmersion->initialize_immersion_layer(m_pengine);

      m_pengine->m_pimmersionlayer = pimmersion;

      m_pengine->m_pimmersionlayer->m_pengine = m_pengine;

      m_pengine->m_pimmersionlayer->m_passetmanager->preloadGlobalAssets();

      auto psceneMain = m_pengine->m_pimmersionlayer->create_main_scene();

      m_pengine->m_pimmersionlayer->m_pscene = psceneMain;

      psceneMain->m_pgpucontext = pgpucontextEngine;

      //auto pblockGlobalUbo1 = psceneMain->global_ubo1(pgpucontextEngine);

      //pblockGlobalUbo1->create_gpu_block(pgpucontextEngine);

      //psceneMain->generateIbl();

      //auto pimmersion = create_immersion();

      // auto psceneMain = create_main_scene();
      //
      // m_pengine->m_pimmersionlayer->set_current_scene(psceneMain);



   }


   void graphics3d::on_message_mouse_leave(::message::message* pmessage)
   {

      on_mouse_out();

   }


   void graphics3d::on_mouse_out()
   {

      if (m_pengine)
      {

         if (m_pengine->m_pinput)
         {

            m_pengine->m_pinput->_001OnMouseOut();

         }

      }

   }


   void graphics3d::on_message_left_button_down(::message::message* pmessage)
   {

      auto pengine = m_pengine;

      if (::is_null(pengine))
      {

         return;

      }

      auto pinput = pengine->m_pinput;

      if (::is_null(pinput))
      {

         return;

      }
      auto pmouse = pmessage->m_union.m_pmouse;

      pmessage->m_bRet = true;

      auto point = pmouse->m_pointHost;

      host_to_client()(point);

      auto &mousestate = pinput->m_mousestate;

      mousestate.m_position.x = (float) point.x;
      mousestate.m_position.y = (float) point.y;
      mousestate.m_buttons.left = true;

      set_mouse_capture();

   }


   void graphics3d::on_message_left_button_up(::message::message* pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmessage->m_bRet = true;

      release_mouse_capture();

      auto point = pmouse->m_pointHost;

      host_to_client()(point);

      m_pengine->m_pinput->m_mousestate.m_position.x = (float) point.x;
      m_pengine->m_pinput->m_mousestate.m_position.y = (float) point.y;
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


   void graphics3d::draw_gpu_statistics(::draw2d::graphics_pointer& pgraphics)
   {

      auto rectangleX = this->rectangle();

      if (rectangleX.is_empty())
      {

         return;
         
      }

      {

         //::color::color color_dk(dk_red());

#ifdef DEBUG_WORK

         ::int_rectangle rectangleDryProWithLove_Work(5, 5, 1915, 1075);

         pgraphics->fill_rectangle(rectangleDryProWithLove_Work, argb(255, 150, 200, 255));

#endif

         pgraphics->set_text_color(::color::white);

         auto psystem = system();

         auto pnode = psystem->draw2d();

         auto pwritetext = pnode->write_text();

         auto fontsize = ::write_text::font_size(48.0 * rectangleX.height() / 1'080, e_unit_pixel);
         
         if(!m_pfontThomasBS_)
         {
            
            m_pfontThomasBS_ = pwritetext->font("Fira Code", fontsize);
            
         }

         pgraphics->set(m_pfontThomasBS_);

         pgraphics->set_text_rendering_hint(write_text::e_rendering_anti_alias);

         pgraphics->set_alpha_mode(draw2d::e_alpha_mode_blend);

         string_array &stra = m_straLineStats;

         //bool bWhite = true;

         //double x = 0.;

         double y = 0.;

         ::int_point point;

         string strText;

         m_iFrameCounter++;

         strText.formatf("øçåJErDgTBS__!!; %d", m_iFrameCounter);

         stra.ø(0) = strText;

         auto size = pgraphics->get_text_extent(strText);

         m_fpscounter.update();

         ::string strFps;

         strFps.format("FPS {:.1f}", m_fpscounter.getAverageFps());

         stra.ø(1) = strFps;

         ::string strFrameTime;

         strFrameTime.format("Frame Time: {:.1f}ms", m_fpscounter.getAverageFrameTime());

         stra.ø(2) = strFrameTime;

         //bool bFixedPosition = true;

         point = {10, 10};

         //::color::color color;

         //auto opacity = ::opacity(200);

         for (auto &strItem: stra)
         {

            y += size.cy;

            pgraphics->text_out(point.x, point.y + y, strItem);
            
         }

         pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

      }

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
   //void graphics3d::_000OnDraw(::draw2d::graphics_pointer& pgraphics)
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

            //r.left = 400.0;
            //r.top = 200.0;
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

      auto pmap = øcreate_new < ::graphics3d::key_map>();
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


   //void graphics3d::prepare_mouse_input()
   //{

   //   m_pengine->m_pinput->prepare_mouse_input();

   //}


   //void graphics3d::process_mouse_input()
   //{

   //   m_pengine->m_pinput->process_mouse_input();

   //}



   //void graphics3d::process_keyboard_input()
   //{

   //   m_pengine->m_pinput->process_keyboard_input();

   //}

} // namespace user



