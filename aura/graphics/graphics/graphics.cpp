#include "platform.h"
#include "buffer_item.h"
#include "graphics.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/user/user/interaction.h"
#include "aura/graphics/draw2d/domain.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/image.h"
#include "aura/windowing/display.h"
#include "aura/windowing/window.h"
#include "aura/windowing/windowing.h"


// multiple buffers implies prodevian mode
//
// What does it mean?
//
// With multiple buffers (including ::f64 buffering)
// every pixel of the buffer should be set again.
// This mean also that damaged areas (m_rectangleaNeedRedraw)
// wouldn't make sense with multiple buffers, as
// entire buffer is always damaged.


namespace graphics
{


   graphics::graphics()
   {

      //m_uptrBuffer = 0;

      m_bNewBuffer = false;

      auto & pdraw2dgraphics = m_pdraw2dgraphics.m_p;

      ::informationf("pdraw2dgraphics %p");

   }


   graphics::~graphics()
   {

      // destroy_buffer();

      //destroy_();

      //destroy();

   }


   void graphics::initialize_graphics_graphics(::windowing::window * pwindow)
   {

      //auto estatus = 

      object::initialize(pwindow);

      defer_create_synchronization();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //m_pimpl = pimpl;

      m_pwindow = pwindow;

      //return estatus;

   }


   void graphics::destroy()
   {

      m_bufferitema.defer_destroy_and_release();

      destroy_buffer();

      //auto estatus = 

      object::destroy();

      //m_pwindow.release();

      //m_pimpl.release();

      //return estatus;

   }


   void graphics::destroy_buffer()
   {


      m_bufferitema.defer_destroy_and_release();
      // for (auto & i : m_bufferitema)
      // {
      //
      //    try
      //    {
      //
      //       i.defer_destroy();
      //
      //    }
      //    catch (...)
      //    {
      //
      //
      //    }
      //
      // }
      //
      //
      // m_bufferitema.clear();


   }


   bool graphics::is_single_buffer_mode() const
   {

      return true;

   }


   void graphics::on_after_graphical_update()
   {


   }


   //   bool graphics::presentation_complete()
   //   {
   //
   //      return true;
   //
   //   }


   void graphics::buffer_size_and_position(buffer_item * pbufferitem)
   {

      synchronous_lock synchronouslock(m_pwindow->m_pmutexBufferSizeAndPosition);

      debug() << "::graphics::graphics::buffer_size_and_position (1)";

      if (::is_null(m_pwindow) || ::is_null(m_pwindow->user_interaction()))
      {

         return;

      }

      debug() << "::graphics::graphics::buffer_size_and_position (2)";

      auto puserinteraction = m_pwindow->user_interaction();

      //puserinteraction->top_sketch_to_lading();
      puserinteraction->sketch_to_lading();

      auto &y5 = puserinteraction->const_layout().lading().m_point2.y;

      auto rectangleDesign = ::i32_rectangle(puserinteraction->const_layout().lading().origin(),
         puserinteraction->const_layout().lading().size());

      auto rectangleRaw = ::i32_rectangle(m_pwindow->m_sizeRaw);

      auto rectangleFixed = rectangleDesign.intersection(rectangleRaw);

      auto pointDesign = puserinteraction->const_layout().lading().origin();

      if (pbufferitem->m_pointBufferItem != pointDesign)
      {

         pbufferitem->m_pointBufferItem = pointDesign;

         pbufferitem->m_pointBufferFixed = rectangleFixed.top_left();

         pbufferitem->m_sizeBufferFixed = rectangleFixed.size();

      }

      auto sizeDesign = puserinteraction->const_layout().lading().size();

      if (pbufferitem->m_sizeBufferItem != sizeDesign)
      {

         pbufferitem->m_sizeBufferItem = sizeDesign;

         pbufferitem->m_pointBufferFixed = rectangleFixed.top_left();

         pbufferitem->m_sizeBufferFixed = rectangleFixed.size();

      }

      if (pbufferitem->m_sizeBufferItem.is_empty())
      {

         pbufferitem->m_sizeBufferItem = puserinteraction->window()->get_window_rectangle().size();

      }

      m_pwindow->m_pointWindowBuffer = pbufferitem->m_pointBufferItem;

      m_pwindow->m_sizeWindowBuffer = pbufferitem->m_sizeBufferItem;

      //pbufferitem->m_point = m_pimpl->m_puserinteraction->const_layout().layout().origin();

      //pbufferitem->m_size = m_pimpl->m_puserinteraction->const_layout().layout().size();

   }


   void graphics::update_screen()
   {

      //return true;

   }


   //::particle * graphics::get_draw_lock()
   //{

   //   return synchronization();

   //}


   ::draw2d::graphics_lease graphics::on_begin_layout()
   {
      
      return ::transfer(on_begin(e_graphics_layout)); 
   
   }


   ::draw2d::graphics_lease graphics::on_begin_draw()
   {

      return ::transfer(on_begin(e_graphics_draw));

   }


   ::draw2d::graphics_lease graphics::on_begin(::e_graphics egraphics)
   {

      debug() << "::graphics::graphics::on_begin_draw";

      auto pbufferitem = get_buffer_item();

      debug() << "::graphics::graphics::on_begin_draw : " << (::uptr) pbufferitem;

      pbufferitem->m_egraphics = egraphics;

      debug() << "::graphics::graphics::going to call buffer_size_and_position";

      auto pacmeuserinteractionTopic = m_pwindow->m_pacmeuserinteraction;

      // A move can be followed directly by a draw acquisition, without a layout
      // acquisition in between. Keep the buffer rectangle current for both cases;
      // otherwise a reusable graphics renders the new frame at the previous window
      // position in the oversized backing bitmap.
      buffer_size_and_position(pbufferitem);

      if (pbufferitem->m_sizeBufferItem.is_empty())
      {

         if (egraphics & e_graphics_layout)
         {

            pbufferitem->m_sizeBufferItem = { 512, 256 };

         }
         else
         {

            information() << "window size is zero in begin draw!!";

            return {};

         }

      }

      if (!_on_begin(pbufferitem))
      {

         return {};

      }

      //if (pbufferitem->m_pgraphicsBufferItem)
      //{

      //   if (pbufferitem->m_pgraphicsBufferItem.ok())
      //   {

      //      pbufferitem->m_pgraphicsBufferItem->__on_begin_draw();

      //   }

      //}

      //return ::transfer(pbufferitem->acquire_graphics());

      if (m_pdraw2dgraphics)
      {

         auto & reference_bBeginDraw = m_pdraw2dgraphics->m_bBeginDraw;

         m_pdraw2dgraphics->m_egraphics = egraphics;

         auto p = m_pdraw2dgraphics.m_p;

         auto & pimg = p->m_pimageTarget.m_p;

         //if (m_bNewFrame)
         if (egraphics == e_graphics_draw)
         {

            return ::transfer(pbufferitem->acquire_graphics());

         }
         else
         {

            m_pdraw2dgraphics->start_frame();

            //m_bNewFrame = false;

         //}


         /// auto pdraw2dgraphics = pgraphicscontext->draw2d_graphics();

         //if (egraphics == e_graphics_layout)
         //{

            //  pdraw2dgraphics->start_layer(true, user_interaction());

            m_pdraw2dgraphics->start_layer(true, m_pwindow->user_interaction());

         //}

         if (!m_pdraw2dgraphics->m_puserinteractionTopic
            && pacmeuserinteractionTopic)
         {

            m_pdraw2dgraphics->m_puserinteractionTopic = pacmeuserinteractionTopic;

         }

         if (!pacmeuserinteractionTopic)
         {

            pacmeuserinteractionTopic = m_pdraw2dgraphics->m_puserinteractionTopic;

         }

         m_pdraw2dgraphics->m_egraphics = egraphics;

         m_pdraw2dgraphics->m_pgraphicsbufferitem = pbufferitem;



         //         auto pimage = pbufferitem->m_pimageBufferItem;

         auto pimage = m_pdraw2dgraphics->get_current_target_image();

         if (::is_null(pimage->draw2d_domain())
            && ::is_set(m_pdraw2dgraphics->draw2d_domain()))
         {

            pimage->set_draw2d_domain(m_pdraw2dgraphics->draw2d_domain());

         }

//         if (!pacmeuserinteractionTopic)
//         {
//
//            pacmeuserinteractionTopic = pimage->m_puserinteractionTopic;
//
//         }

         pimage->m_eacquire = ::draw2d::e_acquire_dont_load;

         return draw2d()->acquire_owned_graphics(
            false,
            m_pdraw2dgraphics,
            pimage,
            pimage->raw_size());

         }

      }
      else
      {

         return ::transfer(pbufferitem->acquire_graphics());

      }

   }


   bool graphics::_on_begin(buffer_item * pbufferitem)
   {

      //auto pbufferitem = get_buffer_item();

      //buffer_size_and_position(pbufferitem);

      //if (pbufferitem->m_size.is_empty())
      //{

      //}

//      auto pimageBufferItem = pbufferitem->m_pimageBufferItem;

//      auto & sizeImageBufferItem = pimageBufferItem->m_size;

//      if (sizeImageBufferItem != pbufferitem->m_sizeBufferItem)

      auto pwindowing = m_pwindow->user_interaction()->windowing();

      auto pdisplay = pwindowing->display();

      auto rectangleUnion = pdisplay->get_monitor_union_rectangle();

      m_pwindow->m_sizeRaw = m_pwindow->m_sizeRaw.maximum(rectangleUnion.size());

      auto & sizeWindow = m_pwindow->m_sizeWindow;

      auto & cxWindow = sizeWindow.cx;

      auto & cyWindow = sizeWindow.cy;

      //RECT r;

      ////::GetWindowRect(::as_HWND(m_pwindow->operating_system_window()), &r);

      //m_pwindow

      auto sizeBufferItem = pbufferitem->m_pimageBufferItem->m_size;

      auto & pointBufferItem1 = pbufferitem->m_pimageBufferItem->m_point;
      auto & pointBufferItem2 = pbufferitem->m_pointBufferItem;
      auto & sizeBufferItem1 = pbufferitem->m_pimageBufferItem->m_size;
      auto & sizeBufferItem2 = pbufferitem->m_sizeBufferItem;
      auto & sizeRawBufferItem1 = pbufferitem->m_pimageBufferItem->m_sizeRaw;
      auto & sizeRawBufferItem2 = m_pwindow->m_sizeRaw;


      if (pbufferitem->m_pimageBufferItem.nok()
         || pbufferitem->m_pimageBufferItem->m_point != pbufferitem->m_pointBufferItem
         || pbufferitem->m_pimageBufferItem->m_size != pbufferitem->m_sizeBufferItem
         || pbufferitem->m_pimageBufferItem->m_sizeRaw != m_pwindow->m_sizeRaw)
      {

         if (!update_buffer(pbufferitem))
         {

            return false;

         }

      }

      //if (!m_papplication->m_gpu.m_bUseSwapChainWindow)
      //{

      //   if (!double_buffer_graphics::_on_begin(pbufferitem))
      //   {

      //      return false;

      //   }

      //}

      return true;

   }


   void graphics::on_end_layout()
   {

      on_end(e_graphics_layout);

   }


   void graphics::on_end_draw()
   {

      on_end(e_graphics_draw);

   }


   void graphics::on_end(::e_graphics egraphics)
   {

      if (egraphics == e_graphics_draw)
      {

         buffer_lock_round_swap_key_buffers();

      }

   }


   bool graphics::buffer_lock_round_swap_key_buffers()
   {

      return true;

   }


   void graphics::on_update_screen(buffer_item * pitem)
   {

      m_pwindow->window_update_screen();
      
      //__UNREFERENCED_PARAMETER(pitem);


      //return true;

   }


   bool graphics::update_buffer(buffer_item * pbufferitem)
   {

      if (!pbufferitem->m_pimageBufferItem)
      {

         constructø(pbufferitem->m_pimageBufferItem);

      }

      //auto pwindowing = m_pwindow->user_interaction()->windowing();

      //auto pdisplay = pwindowing->display();

      //auto rectangleUnion = pdisplay->get_monitor_union_rectangle();

      //auto sizeRaw = m_pwindow->m_sizeWindow.maximum(rectangleUnion.size());

      if (pbufferitem->m_pimageBufferItem.nok()
         || pbufferitem->m_pimageBufferItem->m_point != pbufferitem->m_pointBufferItem
         || pbufferitem->m_pimageBufferItem->m_size != pbufferitem->m_sizeBufferItem
         || pbufferitem->m_pimageBufferItem->m_sizeRaw != m_pwindow->m_sizeRaw)
      {

         //auto pwindowbuffer = m_pwindowbuffer;

         ::pointer < ::pixmap > ppixmapPreviousWindowBuffer;

         ////m_bDibIsHostingBuffer = false;

         //if (playeredwindowbuffer
         //   && !m_papplication->m_gpu.m_bUseSwapChainWindow)
         //{


         //::pointer < layered_window_buffer > playeredwindowbuffer = m_pwindowbuffer;

         //if (pwindowbuffer && !m_papplication->m_gpu.m_bUseSwapChainWindow)
         if (!m_papplication->m_gpu.m_bUseSwapChainWindow)
         {

            //if (m_bDibIsHostingBuffer)
            //{
            //   //::pointer < ::pixmap > ppixmapPreviousWindowBuffer;

            //   //m_bDibIsHostingBuffer = false;

            //   //if (playeredwindowbuffer
            //   //   && !m_papplication->m_gpu.m_bUseSwapChainWindow)
            //   //{

            //   //   ppixmapPreviousWindowBuffer =
            //   //      playeredwindowbuffer->m_ppixmapWindowBuffer;

            //   //   playeredwindowbuffer->update_window_pixmap_buffer(pbufferitem);

            //   //   auto ppixmapWindowBuffer =
            //   //      playeredwindowbuffer->m_ppixmapWindowBuffer;

            //   playeredwindowbuffer->update_window_pixmap_buffer(pbufferitem);




            //   //   //ppixmapPreviousWindowBuffer =
            //   //   //   playeredwindowbuffer->m_ppixmapWindowBuffer;

            //   //   //playeredwindowbuffer->update_window_pixmap_buffer(pbufferitem);

            //   //   //auto ppixmapWindowBuffer =
            //   //   //   playeredwindowbuffer->m_ppixmapWindowBuffer;

            //   //   //if (ppixmapWindowBuffer)
            //   //   {

            //   //     // ppixmapWindowBuffer->m_point = pbufferitem->m_pointBufferItem;

            //   //      //ppixmapWindowBuffer->m_size = pbufferitem->m_sizeBufferItem;

            //   //      pbufferitem->m_pimageBufferItem->m_bHintCpuBackingEnabled = true;

            //   //      pbufferitem->m_pimageBufferItem->m_point.clear();

            //   //      auto & sizeRaw = pbufferitem->m_pimageBufferItem->m_sizeRaw;

            //   //      pbufferitem->m_pimageBufferItem->update_as_render_target(m_pwindow->m_sizeRaw, m_pwindow->user_interaction());

            //   //      auto & sizeRaw2 = pbufferitem->m_pimageBufferItem->m_sizeRaw;

            //   //     //m_bDibIsHostingBuffer =
            //   //         //pbufferitem->m_pimageBufferItem->host(
            //   //         //   m_pwindowbuffer,
            //   //         //   m_pwindow,
            //   //         //   m_pwindow->m_sizeRaw);

            //   //   }

            //   //}

            //   if (!m_pdraw2dgraphics)
            //   {

            //      m_pdraw2dgraphics = system()->draw2d()->allocate_graphics(m_pwindow->m_pacmeuserinteraction);

            //      m_pdraw2dgraphics->m_pgraphicsbufferitem = pbufferitem;

            //      m_pdraw2dgraphics->create_for_window_draw2d(m_pwindow->user_interaction(), m_pwindow->m_sizeRaw);

            //   }

            //   pbufferitem->m_pimageBufferItem->update_as_render_target(m_pwindow->m_sizeRaw,
            //      m_pwindow->user_interaction(),
            //      m_pdraw2dgraphics);

            //   //::f64_size sizef64Raw = m_pwindow->m_sizeRaw;

            //   //if (m_pdraw2dgraphics && m_pdraw2dgraphics->m_sizeTotal2 != sizef64Raw)
            //   //{

            //   auto & point = pbufferitem->m_pimageBufferItem->m_point;

            //   auto & size = pbufferitem->m_pimageBufferItem->m_size;

            //   auto & sizeRaw = pbufferitem->m_pimageBufferItem->m_sizeRaw;



            //   point = pbufferitem->m_pointBufferItem;

            //   size = pbufferitem->m_sizeBufferItem;

            //   sizeRaw = m_pwindow->m_sizeRaw;

            //   informationf("m_pimageBufferItem point(%d-%d) size(%d-%d) sizeRaw(%d-%d)", point.x, point.y, size.cx, size.cy, sizeRaw.cx, sizeRaw.cy);

            //   //m_pdraw2dgraphics->defer_set_size(m_pwindow->m_sizeRaw);

            ////}

            ////if (pbufferitem->m_pimageBufferItem->m_sizeRaw != sizeRaw)
            ////{

            ////   //pbufferitem->m_pimageBufferItem->create_as_render_target(sizeRaw, m_pwindow->user_interaction());

            ////   pbufferitem->m_pimageBufferItem->create_as_top_draw2d_target(sizeRaw, m_pwindow->user_interaction(), m_pdraw2dgraphics);

            ////}

            ////pbufferitem->m_pimageBufferItem->pixmap_map({ m_pwindow->m_pointWindow, m_pwindow->m_sizeWindow });

            ////if (pbufferitem->m_pimageBufferItem->m_size != pbufferitem->m_sizeBufferItem)
            ////{
            ////   pbufferitem->m_pimageBufferItem->picreate_as_render_target(pbufferitem->m_sizeBufferItem);
            ////}

            //}
            //else
            //{

              // //::pointer < ::pixmap > ppixmapPreviousWindowBuffer;

              ////m_bDibIsHostingBuffer = false;

              ////if (playeredwindowbuffer
              ////   && !m_papplication->m_gpu.m_bUseSwapChainWindow)
              ////{

              ////   ppixmapPreviousWindowBuffer =
              ////      playeredwindowbuffer->m_ppixmapWindowBuffer;

              ////   playeredwindowbuffer->update_window_pixmap_buffer(pbufferitem);

              ////   auto ppixmapWindowBuffer =
              ////      playeredwindowbuffer->m_ppixmapWindowBuffer;

              //playeredwindowbuffer->update_window_pixmap_buffer(pbufferitem);




              //   //ppixmapPreviousWindowBuffer =
              //   //   playeredwindowbuffer->m_ppixmapWindowBuffer;

              //   //playeredwindowbuffer->update_window_pixmap_buffer(pbufferitem);

              //   //auto ppixmapWindowBuffer =
              //   //   playeredwindowbuffer->m_ppixmapWindowBuffer;

              //   //if (ppixmapWindowBuffer)
              //   {

              //     // ppixmapWindowBuffer->m_point = pbufferitem->m_pointBufferItem;

              //      //ppixmapWindowBuffer->m_size = pbufferitem->m_sizeBufferItem;

              //      pbufferitem->m_pimageBufferItem->m_bHintCpuBackingEnabled = true;

              //      pbufferitem->m_pimageBufferItem->m_point.clear();

              //      auto & sizeRaw = pbufferitem->m_pimageBufferItem->m_sizeRaw;

              //      pbufferitem->m_pimageBufferItem->update_as_render_target(m_pwindow->m_sizeRaw, m_pwindow->user_interaction());

              //      auto & sizeRaw2 = pbufferitem->m_pimageBufferItem->m_sizeRaw;

              //     //m_bDibIsHostingBuffer =
              //         //pbufferitem->m_pimageBufferItem->host(
              //         //   m_pwindowbuffer,
              //         //   m_pwindow,
              //         //   m_pwindow->m_sizeRaw);

              //   }

              //}

            if (!m_pdraw2dgraphics)
            {

               m_pdraw2dgraphics = system()->draw2d()->allocate_graphics(m_pwindow->draw2d_domain());

               m_pdraw2dgraphics->m_pgraphicsbufferitem = pbufferitem;

               defer_constructø(m_pdraw2dgraphics->m_pgraphicsbufferitem->m_pimageBufferItem);

               m_pdraw2dgraphics->m_pgraphicsbufferitem->m_pimageBufferItem->m_bHintCpuBackingEnabled = false;

               m_pdraw2dgraphics->create_for_window_draw2d(m_pwindow->user_interaction(), m_pwindow->m_sizeRaw);

            }
//            else
//            {

               pbufferitem->m_pimageBufferItem->m_bHintCpuBackingEnabled = false;

               pbufferitem->m_pimageBufferItem->update_as_render_target(m_pwindow->m_sizeRaw,
                  //m_pwindow->user_interaction(),
                                                                        m_pdraw2dgraphics->draw2d_domain(),
                  m_pdraw2dgraphics);

  //          }

            //::f64_size sizef64Raw = m_pwindow->m_sizeRaw;

            //if (m_pdraw2dgraphics && m_pdraw2dgraphics->m_sizeTotal2 != sizef64Raw)
            //{

            auto & point = pbufferitem->m_pimageBufferItem->m_point;

            auto & size = pbufferitem->m_pimageBufferItem->m_size;

            auto & sizeRaw = pbufferitem->m_pimageBufferItem->m_sizeRaw;



            point = pbufferitem->m_pointBufferItem;

            size = pbufferitem->m_sizeBufferItem;

            sizeRaw = m_pwindow->m_sizeRaw;

            informationf("m_pimageBufferItem point(%d-%d) size(%d-%d) sizeRaw(%d-%d)", point.x, point.y, size.cx, size.cy, sizeRaw.cx, sizeRaw.cy);


            //}

         }
         else
         {


            //   //ppixmapPreviousWindowBuffer =
            //   //   playeredwindowbuffer->m_ppixmapWindowBuffer;

            //   //playeredwindowbuffer->update_window_pixmap_buffer(pbufferitem);

            //   //auto ppixmapWindowBuffer =
            //   //   playeredwindowbuffer->m_ppixmapWindowBuffer;

            //   //if (ppixmapWindowBuffer)
            //   {

            //     // ppixmapWindowBuffer->m_point = pbufferitem->m_pointBufferItem;

            //      //ppixmapWindowBuffer->m_size = pbufferitem->m_sizeBufferItem;

            //      pbufferitem->m_pimageBufferItem->m_bHintCpuBackingEnabled = true;

            //      pbufferitem->m_pimageBufferItem->m_point.clear();

            //      auto & sizeRaw = pbufferitem->m_pimageBufferItem->m_sizeRaw;

            //      pbufferitem->m_pimageBufferItem->update_as_render_target(m_pwindow->m_sizeRaw, m_pwindow->user_interaction());

            //      auto & sizeRaw2 = pbufferitem->m_pimageBufferItem->m_sizeRaw;

            //     //m_bDibIsHostingBuffer =
            //         //pbufferitem->m_pimageBufferItem->host(
            //         //   m_pwindowbuffer,
            //         //   m_pwindow,
            //         //   m_pwindow->m_sizeRaw);

            //   }

            //}

            if (!m_pdraw2dgraphics)
            {

               m_pdraw2dgraphics = system()->draw2d()->allocate_graphics(m_pwindow->draw2d_domain());

               m_pdraw2dgraphics->m_pgraphicsbufferitem = pbufferitem;

               m_pdraw2dgraphics->create_for_window_draw2d(m_pwindow->user_interaction(), m_pwindow->m_sizeRaw);

               pbufferitem->m_pimageBufferItem->m_bHintCpuBackingEnabled = !m_papplication->m_gpu.m_bUseSwapChainWindow;

            }

            pbufferitem->m_pimageBufferItem->update_as_gpu_render_target(m_pwindow->m_sizeRaw,
               //m_pwindow->user_interaction(),
               m_pdraw2dgraphics);

            //::f64_size sizef64Raw = m_pwindow->m_sizeRaw;

            //if (m_pdraw2dgraphics && m_pdraw2dgraphics->m_sizeTotal2 != sizef64Raw)
            //{

            auto & point = pbufferitem->m_pimageBufferItem->m_point;

            auto & size = pbufferitem->m_pimageBufferItem->m_size;

            auto & sizeRaw = pbufferitem->m_pimageBufferItem->m_sizeRaw;



            point = pbufferitem->m_pointBufferItem;

            size = pbufferitem->m_sizeBufferItem;

            sizeRaw = m_pwindow->m_sizeRaw;

            informationf("m_pimageBufferItem point(%d-%d) size(%d-%d) sizeRaw(%d-%d)", point.x, point.y, size.cx, size.cy, sizeRaw.cx, sizeRaw.cy);

            //m_pdraw2dgraphics->defer_set_size(m_pwindow->m_sizeRaw);

         //}

         //if (pbufferitem->m_pimageBufferItem->m_sizeRaw != sizeRaw)
         //{

         //   //pbufferitem->m_pimageBufferItem->create_as_render_target(sizeRaw, m_pwindow->user_interaction());

         //   pbufferitem->m_pimageBufferItem->create_as_top_draw2d_target(sizeRaw, m_pwindow->user_interaction(), m_pdraw2dgraphics);

         //}

         //pbufferitem->m_pimageBufferItem->pixmap_map({ m_pwindow->m_pointWindow, m_pwindow->m_sizeWindow });

         //if (pbufferitem->m_pimageBufferItem->m_size != pbufferitem->m_sizeBufferItem)
         //{
         //   pbufferitem->m_pimageBufferItem->picreate_as_render_target(pbufferitem->m_sizeBufferItem);
         //}



         }

      }
      //HWND hwnd = get_hwnd();

        //auto uExStyle = ::GetWindowLong(hwnd, GWL_EXSTYLE);

        //bool bLayered = (uExStyle & WS_EX_LAYERED) != 0;

        //::pointer < layered_window_buffer > playeredwindowbuffer;

        //if (bLayered && ! m_papplication->m_gpu.m_bUseSwapChainWindow)
        //{

        //   auto & pwindowbuffer = m_pwindowbuffer;

        //   ::cast < ::windowing_win32::layered_window_buffer > playeredwindowbuffer = pwindowbuffer;

        //   if (!playeredwindowbuffer)
        //   {

        //      auto playeredwindowbuffer1 = create_newø<layered_window_buffer >();

        //      m_pwindowbuffer = playeredwindowbuffer1;

        //      playeredwindowbuffer = playeredwindowbuffer1;

        //      m_pwindowbuffer->initialize_window_buffer(m_pwindow);

        //   }


        //   //if (playeredwindowbuffer->m_ppixmapWindowBuffer->m_sizeRaw.cx > sizeLargeInternalBitmap.cx)
        //   //{

        //   //   sizeLargeInternalBitmap.cx = playeredwindowbuffer->m_ppixmapWindowBuffer->m_sizeRaw.cx;

        //   //}

        //   //if (playeredwindowbuffer->m_ppixmapWindowBuffer->m_sizeRaw.cy > sizeLargeInternalBitmap.cy)
        //   //{

        //   //   sizeLargeInternalBitmap.cy = playeredwindowbuffer->m_ppixmapWindowBuffer->m_sizeRaw.cy;

        //   //}

        //   //if (playeredwindowbuffer->m_ppixmapWindowBuffer->m_sizeRaw.cx < sizeLargeInternalBitmap.cx
        //   //   || playeredwindowbuffer->m_ppixmapWindowBuffer->m_sizeRaw.cy < sizeLargeInternalBitmap.cy)
        //   //{

        //   //   HBITMAP hbitmap = ::windows::create_windows_dib(sizeLargeInternalBitmap, &iScan, &pimage32);

        //   //   if (hbitmap == nullptr || pimage32 == nullptr || iScan == 0)
        //   //   {

        //   //      if (hbitmap != nullptr)
        //   //      {

        //   //         ::DeleteObject(hbitmap);

        //   //      }

        //   //      return false;

        //   //   }

        //   //   playeredwindowbuffer->m_ppixmapWindowBuffer->initialize_pixmap(sizeLargeInternalBitmap, pimage32, iScan);

        //   //   ::cast < ::windows::device_independent_bitmap > pdeviceindepende/*ntbitmap = playeredwindowbuffer->m_ppixmapWindowBuffer;

        //   //   if (playeredwindowbuffer->m_hbitmap != nullptr)
        //   //   {

        //   //      ::DeleteObject(playeredwindowbuffer->m_hbitmap);

        //   //   }

        //   //   playeredwindowbuffer->m_hbitmap = hbitmap;

        //   //   bool bCreatedCompatibleDC = false;

        //   //   if (playeredwindowbuffer->m_hdc == nullptr)
        //   //   {

        //   //      playeredwindowbuffer->m_hdc = ::CreateCompatibleDC(nullptr);

        //   //      bCreatedCompatibleDC = true;

        //   //   }

        //   //   if (playeredwindowbuffer->m_hdc == nullptr)
        //   //   {

        //   //      destroy_buffer();

        //   //      throw ::exception(error_null_pointer);

        //   //   }

        //   //   HBITMAP hbitmapPrevious = (HBITMAP) ::SelectObject(playeredwindowbuffer->m_hdc, playeredwindowbuffer->m_hbitmap);

        //   //   if (bCreatedCompatibleDC)
        //   //   {

        //   //      playeredwindowbuffer->m_hbitmapOld = hbitmapPrevious;

        //   //   }*/

        //   //}

        //   if (playeredwindowbuffer->m_ppixmapWindowBuffer
        //      && playeredwindowbuffer->m_ppixmapWindowBuffer->size() == pbufferitem->m_sizeBufferItem)
        //   {

        //      return true;

        //   }

        //   auto pwindowing = m_pwindow->user_interaction()->windowing();

        //   auto pdisplay = pwindowing->display();

        //   auto rectangleUnion = pdisplay->get_monitor_union_rectangle();

        //   auto sizeLargeInternalBitmap = rectangleUnion.size();

        //   auto sizeRaw = pbufferitem->m_sizeBufferItem.maximum(sizeLargeInternalBitmap);

        //   if (pbufferitem->m_pimageBufferItem->host(m_pwindowbuffer, m_pwindow, sizeRaw))
        //   {

        //      m_bDibIsHostingBuffer = true;

        //   }
        //   else
        //   {

        //      try
        //      {

        //         pbufferitem->m_pimageBufferItem->create_as_render_target(playeredwindowbuffer->m_ppixmapWindowBuffer->m_sizeRaw);

        //      }
        //      catch (...)
        //      {

        //         return false;

        //      }

        //      m_bDibIsHostingBuffer = false;

        //   }

        //}
        //else
  //      {
  //
  //         if (!pbufferitem->m_pgraphicsBufferItem || pbufferitem->m_pgraphicsBufferItem.nok())
  //         {
  //
  //            constructø(pbufferitem->m_pgraphicsBufferItem);
  //
  //            auto puserinteraction = dynamic_cast < ::user::interaction * >( m_pwindow->m_pacmeuserinteraction.m_p);
  //
  //            ////if (m_papplication->m_gpu.m_bUseSwapChainWindow)
  //            ////{
  //
  //            ////   pbufferitem->m_pgraphics->create_offscreen_graphics_for_swap_chain_blitting(pbufferitem->m_sizeBufferItemDraw);
  //
  //            ////}
  //            ////else
  //            ////{
  //            //pbufferitem->m_pimageBufferItem->create_as_descriptor(pbufferitem->m_sizeBufferItem);
  //            pbufferitem->m_pgraphicsBufferItem->create_for_window_draw2d(puserinteraction, pbufferitem->m_sizeBufferItem);
  //
  //            pbufferitem->m_pgraphicsBufferItem->set_ok_flag();
  //
  //            pbufferitem->m_pgraphicsBufferItem->m_estatus = success;
  //
  ////               //pbufferitem->m_pgraphics->create_memory_graphics(pbufferitem->m_sizeBufferItemDraw);
  ////
  //////            }
  ////
  ////            //pbufferitem->m_pgraphics->set_hint_window_output();
  ////
  ////            //pbufferitem->m_pgraphics->create_window_graphics(m_pwindow);
  //
  //         }
  //         //else
  //         //{
  //
  //         //   //pbufferitem->m_pgraphicsBufferItem->defer_set_size(pbufferitem->m_sizeBufferItem);
  //         //   pbufferitem->m_pimageBufferItem->create_as_descriptor(pbufferitem->m_sizeBufferItem);
  //
  //         //}
  //
  //
  //      }

      return true;


      //debug() << "GRAPHICS::GRAPHICS::UPDATE_BUFFER returning true...";

      //return true;

   }


   bool graphics::ipc_copy(const pixmap * ppixmap)
   {

      return false;

   }


   void graphics::set_bitmap_source(const ::scoped_string & scopedstrBitmapSource, bool bCreate)
   {

      information() << "GRAPHICS::SET_BITMAP_SOURCE NOT Implemented";
      information() << "GRAPHICS::SET_BITMAP_SOURCE NOT Implemented";
      information() << "GRAPHICS::SET_BITMAP_SOURCE NOT Implemented";

   }


   void graphics::clear_bitmap_source()
   {

      throw ::interface_only();

   }


   string graphics::get_bitmap_source() const
   {

      return "";

   }


   buffer_item * graphics::get_buffer_item()
   {

      return nullptr;

   }


   //::image::image_pointer & graphics::get_buffer_image()
   //{

   //   ::image::image_pointer * pimage = nullptr;

   //   return *pimage;

   //}


   //::particle * graphics::get_buffer_sync()
   //{

   //   return synchronization();

   //}


   buffer_item * graphics::get_screen_item()
   {

      return nullptr;

   }


   ::i64 graphics::_001GetTopLeftWeightedOpaqueArea(const ::i32_rectangle & rect)
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      _synchronous_lock synchronouslockMutex(get_screen_item()->m_pmutex, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto ppixmapImageBufferItem = get_screen_item()->m_pimageBufferItem->map();

      return ppixmapImageBufferItem->_001GetTopLeftWeightedOpaqueArea(0, rect);

   }



   ::collection::index graphics::get_buffer_index() const
   {

      return 0;

   }


   ::collection::index graphics::get_screen_index() const
   {

      return 0;

   }



   ::trace_statement & graphics::trace_statement_prefix(::trace_statement & statement) const
   {

      statement << "buffer  ";

      auto pwindow = m_pwindow.m_p;

      if (pwindow)
      {

         auto puserinteraction = pwindow->user_interaction();

         if (puserinteraction)
         {

            puserinteraction->trace_statement_prefix(statement);

         }

      }

      return statement;

   }


} // namespace graphics



