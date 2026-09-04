#include "platform.h"
#include "buffer_item.h"
#include "graphics.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/windowing/window.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/user/user/interaction.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/image.h"


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

      auto pacmeuserinteractionAffinity = m_pwindow->m_pacmeuserinteraction;

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

         if (!m_pdraw2dgraphics->m_pacmeuserinteractionAffinity
            && pacmeuserinteractionAffinity)
         {

            m_pdraw2dgraphics->m_pacmeuserinteractionAffinity = pacmeuserinteractionAffinity;

         }

         if (!pacmeuserinteractionAffinity)
         {

            pacmeuserinteractionAffinity = m_pdraw2dgraphics->m_pacmeuserinteractionAffinity;

         }

         m_pdraw2dgraphics->m_egraphics = egraphics;

         m_pdraw2dgraphics->m_pgraphicsbufferitem = pbufferitem;



         //         auto pimage = pbufferitem->m_pimageBufferItem;

         auto pimage = m_pdraw2dgraphics->get_current_target_image();

         if (!pimage->m_pacmeuserinteractionAffinity
            && pacmeuserinteractionAffinity)
         {

            pimage->m_pacmeuserinteractionAffinity = pacmeuserinteractionAffinity;

         }

         if (!pacmeuserinteractionAffinity)
         {

            pacmeuserinteractionAffinity = pimage->m_pacmeuserinteractionAffinity;

         }

         return draw2d()->acquire_owned_graphics(
            false,
            m_pdraw2dgraphics,
            pimage,
            pimage->raw_size(),
            pacmeuserinteractionAffinity);

         }

      }
      else
      {

         return ::transfer(pbufferitem->acquire_graphics());

      }

   }


   bool graphics::_on_begin(buffer_item * pbufferitem)
   {

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

      //__UNREFERENCED_PARAMETER(pitem);


      //return true;

   }


   bool graphics::update_buffer(buffer_item * pitem)
   {

      debug() << "GRAPHICS::GRAPHICS::UPDATE_BUFFER returning true...";

      return true;

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



