// Created by camilo on 2026-11-01 11:45 <3ThomasBorregaardSorensen!! Mummi!! bilbo!!
#include "platform.h"
#include "gpu_shader_host.h"
#include "acme/constant/id.h"
#include "acme/exception/interface_only.h"
#include "apex/gpu/approach.h"
#include "bred/gpu/block.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/debug_scope.h"
#include "bred/gpu/window_attachment.h"
#include "bred/gpu/layer.h"
#include "bred/graphics3d/asset_manager.h"
#include "bred/graphics3d/engine_instance.h"
#include "bred/graphics3d/input.h"
#include "bred/graphics3d/scene_base.h"
#include "acme/constant/user_message.h"
#include "acme/graphics/image/image32_t.h"
#include "acme/handler/topic.h"
#include "acme/platform/node.h"
#include "acme/platform/session.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "aura/graphics/draw2d/graphics_context.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/aaa_target.h"
#include "aura/message/user.h"
#include "aura/windowing/window.h"
#include "bred/graphics3d/types.h"
#include "aura/platform/application.h"
#include "bred/gpu/graphics.h"
#include "bred/gpu/renderer.h"
#include "bred/gpu/texture_site.h"
#include "bred/prodevian/immersion.h"
#include <atomic>
#include <cstdlib>


namespace user
{


  
      gpu_shader_host::gpu_shader_host()
      {

         m_bTransparent = true;

         m_enonclient.erase(::user::e_non_client_background);

         m_enonclient.erase(::user::e_non_client_focus_rect);

         //m_colorBackground = {};

         m_bDefaultClickHandling = true;

      }


      gpu_shader_host::~gpu_shader_host()
      {

      }


      //::user::enum_translucency gpu_shader_host::get_translucency(::user::style * pstyle)
      //{

      //   return ::user::e_translucency_present;

      //}


      void gpu_shader_host::install_message_routing(::channel * psender)
      {

         ::user::gpu_interaction::install_message_routing(psender);
         USER_MESSAGE_LINK(::user::e_message_create, psender, this, &gpu_shader_host::on_message_create);
         USER_MESSAGE_LINK(::user::e_message_destroy, psender, this, &gpu_shader_host::on_message_destroy);
         USER_MESSAGE_LINK(::user::e_message_key_down, psender, this, &gpu_shader_host::on_message_key_down);
         //USER_MESSAGE_LINK(::user::e_message_switch, psender, this, &gpu_shader_host::on_message_switch);

      }




      void gpu_shader_host::on_message_create(::message::message * pmessage)
      {

         ::pointer<::message::create>pcreate(pmessage);

         pcreate->previous();

         if (pcreate->m_bRet)
         {

            return;

         }

         //      {
         //
         //         tool().add_item(allocateø ::item(e_element_close_button, id_close_app));
         //
         ////         auto pitem = user_item(::e_element_close_button);
         ////
         ////         if (pitem)
         ////         {
         ////
         ////            *pitem = ::e_element_close_icon;
         ////
         ////         }
         //
         //      }

         {

            //         auto pitem = user_item(::e_element_switch_button);
            //
            //         *pitem = ::e_element_switch_button;

         }

         //      {
         //
         //
         //
         //         //auto pitem = user_item(::e_element_maximize_button);
         //
         ////         if (pitem)
         ////         {
         ////
         ////            *pitem = ::e_element_maximize_icon;
         ////
         ////         }
         //
         //      }


         //      {
         //
         //
         //         tool().add_item(allocateø ::item(e_element_minimize_button, id_minimize));
         //
         ////         auto pitem = user_item(::e_element_minimize_button);
         ////
         ////         if (pitem)
         ////         {
         ////
         ////            *pitem = ::e_element_minimize_icon;
         ////
         ////         }
         //
         //      }
         //tool().add_item(allocateø::item(::e_element_maximize_button, ::id_maximize));

         //      top_level()->set_fps_interest();
         //add_graphical_output_purpose(this, ::graphics::e_output_purpose_screen_fps);


         //switch_shader();

      }


      void gpu_shader_host::on_message_destroy(::message::message * pmessage)
      {


      }


      //void gpu_shader_host::on_message_key_down(::message::message * pmessage)
      //{

      //   auto pkey = pmessage->m_union.m_pkey;

      //   if (pkey->m_ekey == ::user::e_key_s)
      //   {

      //      m_bSaveFrame = true;

      //   }


      //}





      void gpu_shader_host::handle(::topic * ptopic, ::handler_context * phandlercontext)
      {

         if (ptopic->id() == "simple_checkbox"
            || ptopic->id() == "no_client_frame")
         {

            set_need_redraw();

         }

         ::user::interaction::handle(ptopic, phandlercontext);

      }


      bool gpu_shader_host::keyboard_focus_is_focusable()
      {

         return true;

      }


      ::image::image * gpu_shader_host::drawn_frame_image()
      {

         auto rectangleX = this->rectangle();

         auto prender = get_current_render();

         if (::is_null(prender))
         {

            return nullptr;

         }

         prender->initialize_app_shader_render(this);

         auto pimageTarget = prender->drawn_frame_image();

         if (m_bSaveFrame)
         {

            m_bSaveFrame = false;

            ::image::image_pointer pimage = pimageTarget->clone();

            //auto pimage = image()->create_image(rectangleX.size(), draw2d_domain());

            //auto pdraw2dgraphics = pimage->acquire_graphics();

            //prender->_001OnDraw(pdraw2dgraphics);

            fork([this, pimage]()
                  {

                        ::image::encoding_options encodingoptions;

                        encodingoptions.m_eformat = ::image::e_format_png;

                        string strDate = datetime()->date_time_text_for_file();

                        image()->save_image("image://app_simple_shader-" + strDate + ".png", pimage, encodingoptions);

                  });

         }
         //      }

               // The shader has finished; draw controls on the same active UI target.

         return pimageTarget;

      }


      void gpu_shader_host::_001OnNcPostDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
      {

         ::user::gpu_shader_host::_001OnNcPostDraw(pdraw2dgraphics);

      }


      void gpu_shader_host::on_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
      {

         auto rectangleX = this->rectangle();

         if (rectangleX.is_empty())
         {

            return;

         }

         auto & prender = m_maprender[m_strCurrentShaderPath];

         if (::is_set(prender))
         {

            prender->m_rectangle = rectangleX;

            prender->on_layout(pdraw2dgraphics);

         }

         ::user::gpu_shader_host::on_layout(pdraw2dgraphics);




      }


      bool gpu_shader_host::on_click(::item * pitem, ::user::mouse * pmouse)
      {

         if (::user::interaction::on_click(pitem, pmouse))
         {

            return true;

         }

         return true;

      }


      ::user::gpu_render * gpu_shader_host::get_current_render()
      {

         synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         auto & prender = m_mapusergpurender[m_strCurrentShaderPath];

         if (!prender)
         {

            synchronouslock.unlock();

            //::user::lock_sketch_to_design lockSketchToDesign(this);

            auto prenderNew = create_newø < ::user::gpu_render >();

            if (!prenderNew)
            {

               throw ::exception(error_failed);

               return nullptr;

            }

            prenderNew->initialize_app_shader_render(this);

            string strText;

            prenderNew->m_strShaderPath = m_strCurrentShaderPath;

            prenderNew->update_shader();

            {

               synchronouslock.lock();

               prender = prenderNew;

               synchronouslock.unlock();

            }

            //set_need_layout();

         }

         //post_redraw();

         return prender;

      }


      void gpu_shader_host::_001DrawItem(::draw2d::graphics_pointer & pdraw2dgraphics, ::user::item & useritem, const ::user::e_state & estate)
      {

         ::user::interaction::_001DrawItem(pdraw2dgraphics, useritem, estate);

      }



      void gpu_shader_host::on_user_interface_switch()
      {

         switch_shader();

      }


      void gpu_shader_host::switch_shader()
      {

         auto papp = get_app();

         auto strNextShaderPath = papp->get_next_shader_path(m_strCurrentShaderPath);

         if (strNextShaderPath == m_strCurrentShaderPath)
         {

            return;

         }

         information() << "app_shader switch: " << m_strCurrentShaderPath << " -> " << strNextShaderPath;

         m_strCurrentShaderPath = strNextShaderPath;

         set_need_layout();

         set_need_redraw();

         post_redraw();

      }


   } // namespace app_shader





   gpu_shader_host::gpu_shader_host()
   {

      //m_emouse = ::gpu_shader_host::e_mouse_updateLook;
      //m_ekeyboard = ::gpu_shader_host::e_keyboard_updateMovement;
      ////m_bAbsoluteMousePosition = false;
      //m_bShouldClose = false;
      m_bFramebufferResized = false;
      m_psession = nullptr;
   }


   gpu_shader_host::~gpu_shader_host()
   {

   }


   ::i64 gpu_shader_host::increment_reference_count()
   {
      
      return ::object::increment_reference_count();

   }


   ::i64 gpu_shader_host::decrement_reference_count()
   {
      
      return ::object::decrement_reference_count();

   }



   void gpu_shader_host::install_message_routing(::channel * pchannel)
   {

      ::user::box::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &gpu_shader_host::on_message_create);
      USER_MESSAGE_LINK(::user::e_message_destroy, pchannel, this, &gpu_shader_host::on_message_destroy);
      USER_MESSAGE_LINK(::user::e_message_key_down, pchannel, this, &gpu_shader_host::on_message_key_down);
      USER_MESSAGE_LINK(::user::e_message_key_up, pchannel, this, &gpu_shader_host::on_message_key_up);

   }


   bool gpu_shader_host::keyboard_focus_is_focusable()
   {

      return true;

   }

   //void gpu_shader_host::on_kill_keyboard_focus()
   //{
   //   if (m_pinput)
   //      m_pinput->reset_keyboard_input();
   //   ::user::box::on_kill_keyboard_focus();
   //}

   //void gpu_shader_host::_on_show_window()
   //{
   //   ::user::box::_on_show_window();
   //   if (!is_window_screen_visible(::user::e_layout_layout) && m_pinput)
   //      m_pinput->reset_keyboard_input();
   //}


   //void gpu_shader_host::on_message_key_down(::message::message * pmessage)
   //{

   //   if (std::getenv("CA2_TRACE_INPUT"))
   //      informationf("CA2_INPUT view key=%d down=1", (int)pmessage->m_union.m_pkey->m_ekey);

   //   if (m_pinput)
   //      m_pinput->on_key_event(pmessage->m_union.m_pkey->m_ekey, true);

   //   pmessage->m_bRet = true;

   //}


   //void gpu_shader_host::on_message_key_up(::message::message * pmessage)
   //{

   //   if (std::getenv("CA2_TRACE_INPUT"))
   //      informationf("CA2_INPUT view key=%d down=0", (int)pmessage->m_union.m_pkey->m_ekey);

   //   if (m_pinput)
   //      m_pinput->on_key_event(pmessage->m_union.m_pkey->m_ekey, false);

   //   pmessage->m_bRet = true;

   //}


   //void gpu_shader_host::on_message_mouse_move(::message::message * pmessage)
   //{

   //   auto pmouse = pmessage->m_union.m_pmouse;

   //   pmessage->m_bRet = true;

   //   if (m_pinput)
   //   {

   //      auto point = pmouse->m_pointHost;

   //      host_to_client()(point);

   //      on_mouse_move(point);

   //      track_mouse_leave();

   //   }

   //}


   //void gpu_shader_host::on_mouse_move(const i32_point & point)
   //{

   //   auto pinput = m_pinput;

   //   if (pinput)
   //   {

   //      pinput->_001OnMouseMove(point);

   //   }

   //}


   void gpu_shader_host::defer_initialize_gpu_shader_host(const ::i32_rectangle & rectanglePlacement)
   {

      //if (!m_pgraphics3dengineinstance)
      //{

      //   ::string strImplementation = get_app()->graphics3d_get_implementation_name();

      //   auto pfactoryGpu = system()->factory("gpu", strImplementation);

      //   pfactoryGpu->merge_to_global_factory();

      //   auto pfactoryGraphics3d = system()->factory("gpu_shader_host", strImplementation);

      //   pfactoryGraphics3d->merge_to_global_factory();

      //   m_pkeymap = get_default_key_map();

      //   m_pkeymap->m_pimpact = this;

      //   constructø(m_pgraphics3dengineinstance);

      //   m_pgraphics3dengineinstance->initialize_graphics3d_engine_instance(this);

      //   m_pgraphics3dengineinstance->defer_start(this, rectanglePlacement);

      //}

   }


   //::pointer < ::prodevian::immersion > gpu_shader_host::create_immersion()
   //{

   //   throw ::interface_only();

   //   return {};

   //}


   //void gpu_shader_host::on_load_engine()
   //{

   //   auto pgpucontextEngine = m_pgraphics3dengineinstance->gpu_context();

   //   pgpucontextEngine->m_pgraphics3dengineinstance = m_pgraphics3dengineinstance;

   //   auto pimmersion = create_immersion();

   //   pimmersion->initialize_immersion_layer(m_pgraphics3dengineinstance);

   //   m_pgraphics3dengineinstance->m_pimmersionlayer = pimmersion;

   //   m_pgraphics3dengineinstance->m_pimmersionlayer->m_pgraphics3dengineinstance = m_pgraphics3dengineinstance;

   //   m_pgraphics3dengineinstance->m_pimmersionlayer->m_passetmanager->preloadGlobalAssets();

   //   auto psceneMain = m_pgraphics3dengineinstance->m_pimmersionlayer->create_main_scene();

   //   m_pgraphics3dengineinstance->m_pimmersionlayer->m_pscene = psceneMain;

   //   psceneMain->m_pgpucontext = pgpucontextEngine;

   //   //auto pblockGlobalUbo1 = psceneMain->global_ubo1(pgpucontextEngine);

   //   //pblockGlobalUbo1->create_gpu_block(pgpucontextEngine);

   //   //psceneMain->generateIbl();

   //   //auto pimmersion = create_immersion();

   //   // auto psceneMain = create_main_scene();
   //   //
   //   // m_pgraphics3dengineinstance->m_pimmersionlayer->set_current_scene(psceneMain);



   //}


   //void gpu_shader_host::on_message_mouse_leave(::message::message * pmessage)
   //{

   //   on_mouse_out();

   //}


   //void gpu_shader_host::on_mouse_out()
   //{

   //   if (m_pgraphics3dengineinstance)
   //   {

   //      if (m_pgraphics3dengineinstance->m_pinput)
   //      {

   //         m_pgraphics3dengineinstance->m_pinput->_001OnMouseOut();

   //      }

   //   }

   //}


   //void gpu_shader_host::on_message_left_button_down(::message::message * pmessage)
   //{

   //   auto pengine = m_pgraphics3dengineinstance;

   //   if (::is_null(pengine))
   //   {

   //      return;

   //   }

   //   auto pinput = pengine->m_pinput;

   //   if (::is_null(pinput))
   //   {

   //      return;

   //   }
   //   auto pmouse = pmessage->m_union.m_pmouse;

   //   pmessage->m_bRet = true;

   //   set_keyboard_focus();

   //   auto point = pmouse->m_pointHost;

   //   host_to_client()(point);

   //   auto & mousestate = pinput->m_mousestate;

   //   mousestate.m_position.x = (::f32)point.x;
   //   mousestate.m_position.y = (::f32)point.y;
   //   mousestate.m_buttons.left = true;

   //   set_mouse_capture();

   //}


   //void gpu_shader_host::on_message_left_button_up(::message::message * pmessage)
   //{

   //   auto pmouse = pmessage->m_union.m_pmouse;

   //   pmessage->m_bRet = true;

   //   release_mouse_capture();

   //   auto point = pmouse->m_pointHost;

   //   host_to_client()(point);

   //   m_pgraphics3dengineinstance->m_pinput->m_mousestate.m_position.x = (::f32)point.x;
   //   m_pgraphics3dengineinstance->m_pinput->m_mousestate.m_position.y = (::f32)point.y;
   //   m_pgraphics3dengineinstance->m_pinput->m_mousestate.m_buttons.left = false;



   //}



   void gpu_shader_host::on_message_create(::message::message * pmessage)
   {
      m_psession = session();

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }


      //get_app()->m_pimpact = this;


   }


   void gpu_shader_host::on_message_destroy(::message::message * pmessage)
   {

   }


   void gpu_shader_host::operator()(::timer * ptimer)
   {

   }


   void gpu_shader_host::handle(::topic * ptopic, ::handler_context * phandlercontext)
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


//   void gpu_shader_host::draw_gpu_statistics(::i32 yParam, const ::scoped_string & scopedstrTitle, ::draw2d::graphics_pointer & pdraw2dgraphics)
//   {
//
//      auto rectangleX = this->rectangle();
//
//      if (rectangleX.is_empty())
//      {
//
//         return;
//
//      }
//
//      {
//
//         //::color::color color_dk(dk_red());
//
//#ifdef DEBUG_WORK
//
//         ::i32_rectangle rectangleDryProWithLove_Work(5, 5, 1915, 1075);
//
//         pdraw2dgraphics->fill_rectangle(rectangleDryProWithLove_Work, argb(255, 150, 200, 255));
//
//#endif
//
//         pdraw2dgraphics->set_solid_color(::color::white);
//
//         auto psystem = system();
//
//         auto pnode = psystem->draw2d();
//
//         auto pwritetext = pnode->write_text();
//
//         auto fontsize = ::write_text::font_size(48.0 * rectangleX.height() / 1'080, e_unit_pixel);
//
//         if (!m_pfontThomasBS_)
//         {
//
//            m_pfontThomasBS_ = pwritetext->font("Fira Code", fontsize);
//
//         }
//
//         pdraw2dgraphics->set(m_pfontThomasBS_);
//
//         pdraw2dgraphics->set_text_rendering_hint(write_text::e_rendering_anti_alias);
//
//         pdraw2dgraphics->set_alpha_mode(draw2d::e_alpha_mode_blend);
//
//         string_array & stra = m_straLineStats;
//
//         //bool bWhite = true;
//
//         //::f64 x = 0.;
//
//         ::f64 y = (::f64)yParam;
//
//
//
//         ::i32_point point;
//
//         string strText;
//
//         auto pgpuwindowattachment = ::gpu::window_attachment::get(this);
//
//         ::collection::index iFrameSerial = -1;
//
//         if (pgpuwindowattachment)
//         {
//
//            iFrameSerial = pgpuwindowattachment->m_iFrameSerial2;
//
//         }
//         else
//         {
//
//            iFrameSerial = ++m_iFrameCounter;
//
//         }
//
//         strText.formatf("øçåJErDgTBS__!!; %lld", (::i64)iFrameSerial);
//
//         stra.atø(0) = scopedstrTitle;
//
//         auto size = pdraw2dgraphics->get_text_extent(strText);
//
//         m_fpscounter.update();
//
//         ::string strFps;
//
//         strFps.format("FPS {:.1f}", m_fpscounter.getAverageFps());
//
//         stra.atø(1) = strFps;
//
//         ::string strFrameTime;
//
//         strFrameTime.format("Frame Time: {:.1f}ms", m_fpscounter.getAverageFrameTime());
//
//         stra.atø(2) = strFrameTime;
//
//         //::string strGraphicsModeCompletion;
//
//         //strGraphicsModeCompletion.format("Graphics Mode Completion: {}/{} {:.3f}%", 
//         //   m_papplication->gpu_approach()->graphics3d_modes_step(),
//         //   m_papplication->gpu_approach()->graphics3d_modes_step_count(),
//         //   ((::f64)m_papplication->gpu_approach()->graphics3d_modes_step()/
//         //   (::f64)m_papplication->gpu_approach()->graphics3d_modes_step_count()) * 100.0
//         //   );
//
//         //stra.atø(3) = strGraphicsModeCompletion;
//
//         //bool bFixedPosition = true;
//
//         point = { 10, 10 };
//
//         //::color::color color;
//
//         //auto opacity = ::opacity(200);
//
//         for (auto & strItem : stra)
//         {
//
//            y += size.cy;
//
//            pdraw2dgraphics->text_out(point.x, point.y + y, strItem);
//
//         }
//
//         pdraw2dgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);
//
//      }
//
//   }
//
//
//   void gpu_shader_host::_001OnNcClip(::draw2d::graphics_pointer & pdraw2dgraphics)
//   {
//
//      ::user::box::_001OnNcClip(pdraw2dgraphics);
//
//   }
//
//
//   void gpu_shader_host::_001OnClip(::draw2d::graphics_pointer & pdraw2dgraphics)
//   {
//
//      ::user::box::_001OnClip(pdraw2dgraphics);
//
//   }
//
//
//   void gpu_shader_host::_001OnNcDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
//   {
//
//      ::user::box::_001OnNcDraw(pdraw2dgraphics);
//
//   }


   //void gpu_shader_host::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   //   //void gpu_shader_host::_000OnDraw(::draw2d::graphics_pointer& pdraw2dgraphics)
   //{

   //   ::user::gpu_interaction::_001OnDraw(pdraw2dgraphics);

   //}


   //void gpu_shader_host::_001OnNcPostDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   //{


   //}


   //   ::key::enum_state gpu_shader_host::get_key_state(const ::user::e_key & ekey)
     // {

       //  if (session()->is_key_pressed(ekey))
         //{

           // return ::key::e_state_pressed;

    //     }

      //   return ::key::e_state_none;

      //}




   ::image::image * gpu_shader_host::drawn_frame_image()
   {

      auto rectangleX = this->rectangle();

      auto prender = get_current_render();

      if (::is_null(prender))
      {

         return nullptr;

      }

      prender->initialize_app_shader_render(this);

      auto pimageTarget = prender->drawn_frame_image();

      if (m_bSaveFrame)
      {

         m_bSaveFrame = false;

         ::image::image_pointer pimage = pimageTarget->clone();

         //auto pimage = image()->create_image(rectangleX.size(), draw2d_domain());

         //auto pdraw2dgraphics = pimage->acquire_graphics();

         //prender->_001OnDraw(pdraw2dgraphics);

         fork([this, pimage]()
               {

                  ::image::encoding_options encodingoptions;

                  encodingoptions.m_eformat = ::image::e_format_png;

                  string strDate = datetime()->date_time_text_for_file();

                  image()->save_image("image://app_simple_shader-" + strDate + ".png", pimage, encodingoptions);

               });

      }
      //      }

            // The shader has finished; draw controls on the same active UI target.

      return pimageTarget;

   }


   void gpu_shader_host::_001OnNcPostDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      ::user::gpu_interaction::_001OnNcPostDraw(pdraw2dgraphics);

   }


   void gpu_shader_host::on_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      auto rectangleX = this->rectangle();

      if (rectangleX.is_empty())
      {

         return;

      }

      auto & prender = m_mapusergpurender[m_strCurrentShaderPath];

      if (::is_set(prender))
      {

         prender->m_rectangle = rectangleX;

         prender->on_layout(pdraw2dgraphics);

      }

      ::user::gpu_shader_host::on_layout(pdraw2dgraphics);




   }



   //void gpu_shader_host::on_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   //{

   //   ::user::gpu_interaction::on_layout(pdraw2dgraphics);

   //   //auto rectangleX = this->rectangle();

   //   //if (rectangleX.area() <= 0)
   //   //{

   //   //   return;

   //   //}

   //   //auto size = rectangleX.size();

   //   //m_iWidth = size.width();

   //   //m_iHeight = size.height();

   //   //if (!m_pgraphics3dengineinstance)
   //   //{

   //   //   defer_initialize_graphics3d_engine_instance(this->host_rectangle());

   //   //}
   //   //else if (m_pgraphics3dengineinstance->has_ok_flag())
   //   //{

   //   //   auto rectanglePlacement = this->host_rectangle();

   //   //   if (m_papplication->m_gpu.m_bUseSwapChainWindow)
   //   //   {

   //   //      // The interaction's cached screen origin can lag an X11 window
   //   //      // move. Compose in the current native window's coordinates.
   //   //      auto pwindow = this->window();
   //   //      rectanglePlacement.offset(pwindow->get_window_rectangle().origin());

   //   //   }
   //   //   else
   //   //   {

   //   //      rectanglePlacement.offset(-rectanglePlacement.top_left());

   //   //   }

   //   //   m_pgraphics3dengineinstance->on_layout(rectanglePlacement);

   //   //}

   //   ////reset_mouse_last_position();

   //}


   bool gpu_shader_host::wasWindowResized()
   {

      return m_bFramebufferResized;


   }


   void gpu_shader_host::resetWindowResizedFlag()
   {

      m_bFramebufferResized = false;

   }


   //::pointer < ::gpu_shader_host::key_map > gpu_shader_host::get_default_key_map()
   //{

   //   auto pmap = create_newø < ::gpu_shader_host::key_map>();
   //   using namespace ::gpu_shader_host;

   //   pmap->map(e_key_moveLeft, ::user::e_key_a);
   //   pmap->map(e_key_moveRight, ::user::e_key_d);
   //   pmap->map(e_key_moveForward, ::user::e_key_w);
   //   pmap->map(e_key_moveBackward, ::user::e_key_s);
   //   pmap->map(e_key_moveUp, ::user::e_key_e);
   //   pmap->map(e_key_moveDown, ::user::e_key_q);
   //   pmap->map(e_key_lookLeft, ::user::e_key_left);
   //   pmap->map(e_key_lookRight, ::user::e_key_right);
   //   pmap->map(e_key_lookUp, ::user::e_key_up);
   //   pmap->map(e_key_lookDown, ::user::e_key_down);
   //   pmap->map(e_key_Exit, ::user::e_key_escape);

   //   return pmap;

   //}


   ::f32 gpu_shader_host::getAspectRatio()
   {

      auto fH = fabs(static_cast<::f32>(this->height()));

      if (fH <= 0.00001)
      {

         return 1.0f;

      }

      return static_cast<::f32>(this->width()) / fH;

   }


   //void gpu_shader_host::prepare_mouse_input()
   //{

   //   m_pgraphics3dengineinstance->m_pinput->prepare_mouse_input();

   //}


   //void gpu_shader_host::process_mouse_input()
   //{

   //   m_pgraphics3dengineinstance->m_pinput->process_mouse_input();

   //}



   //void gpu_shader_host::process_keyboard_input()
   //{

   //   m_pgraphics3dengineinstance->m_pinput->process_keyboard_input();

   //}

} // namespace user



