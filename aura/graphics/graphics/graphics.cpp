#include "framework.h"
#include "graphics.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/windowing/window.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/user/user/interaction.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/image.h"


// multiple buffers implies prodevian mode
//
// What does it mean?
//
// With multiple buffers (including double buffering)
// every pixel of the buffer should be set again.
// This mean also that damaged areas (m_rectangleaNeedRedraw)
// wouldn't make sense with multiple buffers, as
// entire buffer is always damaged.


namespace graphics
{


   ::draw2d::graphics_pointer buffer_item::g()
   {

      auto pgraphics = m_pgraphics ? m_pgraphics.m_p : m_pimage2->g();

      pgraphics->m_egraphics = m_egraphics;

      //if (!pgraphics->m_callbackImage32CpuBuffer)
      //{

      //   pgraphics->m_callbackImage32CpuBuffer = [this](const ::image32_t * pimage32, int cx, int cy, int scan)
      //      {

      //         //_synchronous_lock synchronouslock(this->m_pmutex);

      //         m_pimage2->image32()->copy(cx, cy, m_pimage2->m_iScan, pimage32, scan);

      //      };

      //}

      return pgraphics;

   }


   void buffer_item::destroy()
   {

      ::particle::destroy();

      m_pmutex.release();

      m_pimage2.defer_destroy();

      m_pgraphics.release();

      m_pparticleData.release();

   }


   graphics::graphics()
   {

      m_uptrBuffer = 0;

      m_bNewBuffer = false;

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

      destroy_buffer();

      //auto estatus = 

      object::destroy();

      //m_pwindow.release();

      //m_pimpl.release();

      //return estatus;

   }


   void graphics::destroy_buffer()
   {

      for (auto & i : m_bufferitema)
      {

         try
         {

            i.defer_destroy();

         }
         catch (...)
         {


         }

      }


      m_bufferitema.clear();


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

      debug() << "::graphics::graphics::buffer_size_and_position (1)";

      if (::is_null(m_pwindow) || ::is_null(m_pwindow->user_interaction()))
      {

         return;

      }

      debug() << "::graphics::graphics::buffer_size_and_position (2)";

      auto puserinteraction = m_pwindow->user_interaction();

      auto pointDesign = puserinteraction->const_layout().design().origin();

      if (pbufferitem->m_pointBufferItemDraw != pointDesign)
      {

         pbufferitem->m_pointBufferItemDraw = pointDesign;

      }

      auto sizeDesign = puserinteraction->const_layout().design().size();

      if (pbufferitem->m_sizeBufferItemDraw != sizeDesign)
      {

         pbufferitem->m_sizeBufferItemDraw = sizeDesign;

      }

      if (pbufferitem->m_sizeBufferItemDraw.is_empty())
      {

         pbufferitem->m_sizeBufferItemDraw = puserinteraction->window()->get_window_rectangle().size();

      }

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


   ::graphics::buffer_item * graphics::on_begin_draw(::e_graphics egraphics)
   {

      debug() << "::graphics::graphics::on_begin_draw";

      auto pbufferitem = get_buffer_item();

      debug() << "::graphics::graphics::on_begin_draw : " << (::uptr) pbufferitem;

      pbufferitem->m_egraphics = egraphics;

      debug() << "::graphics::graphics::going to call buffer_size_and_position";

      buffer_size_and_position(pbufferitem);

      if (pbufferitem->m_sizeBufferItemDraw.is_empty())
      {

         if (egraphics & e_graphics_layout)
         {

            pbufferitem->m_sizeBufferItemDraw = { 512, 256 };

         }
         else
         {

            information() << "window size is zero in begin draw!!";

            return nullptr;

         }

      }

      if (!_on_begin_draw(pbufferitem))
      {

         return nullptr;

      }

      if (pbufferitem->m_pgraphics &&
         pbufferitem->m_pgraphics.ok())
      {

         pbufferitem->m_pgraphics->__on_begin_draw();

      }

      return pbufferitem;

   }


   bool graphics::_on_begin_draw(buffer_item * pbufferitem)
   {

      return true;

   }


   void graphics::on_end_draw()
   {

      buffer_lock_round_swap_key_buffers();

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


   void graphics::set_bitmap_source(const string & strBitmapSource)
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


   long long graphics::_001GetTopLeftWeightedOpaqueArea(const ::int_rectangle & rect)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      _synchronous_lock synchronouslockMutex(get_screen_item()->m_pmutex);

      return get_screen_item()->m_pimage2->_001GetTopLeftWeightedOpaqueArea(0, rect);

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



