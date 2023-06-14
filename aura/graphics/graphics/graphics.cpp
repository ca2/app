#include "framework.h"
#include "graphics.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/windowing/window.h"
#include "aura/user/user/interaction_impl.h"
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


   graphics::graphics()
   {

      m_uptrBuffer = 0;

      m_bNewBuffer = false;

   }


   graphics::~graphics()
   {

      // destroy_buffer();

      //destroy_();

      destroy();

   }


   void graphics::initialize_graphics_graphics(::user::interaction_impl * pimpl)
   {

      //auto estatus = 
      
      object::initialize(pimpl);

      defer_create_synchronization();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pimpl = pimpl;

      m_pwindow = pimpl->window();

      //return estatus;

   }


   void graphics::destroy()
   {

      destroy_buffer();

      //auto estatus = 
      
      object::destroy();

      //return estatus;

   }


   void graphics::destroy_buffer()
   {

   }


   bool graphics::is_single_buffer_mode() const
   {

      return true;

   }


   void graphics::on_after_graphical_update()
   {


   }


   void graphics::buffer_size_and_position(buffer_item * pitem)
   {

      if (::is_null(m_pimpl))
      {

         return;

      }

      if (!m_pimpl->m_puserinteraction)
      {

         return;

      }



      //buffer_item * pitem = get_buffer_item();

      pitem->m_point = m_pimpl->m_puserinteraction->const_layout().design().origin();

      pitem->m_size = m_pimpl->m_puserinteraction->const_layout().design().size();

//      if(d.m_size.cx() == 1)
//      {
//
//         printf("cx=1");
//
//      }
//      else
//      {
//         printf("cx!=1");
//
//      }

      //return d.m_size;

   }


   bool graphics::update_screen()
   {

      return true;

   }


   //::particle * graphics::get_draw_lock()
   //{

   //   return synchronization();

   //}


   buffer_item * graphics::on_begin_draw()
   {

      return nullptr;

   }


   void graphics::on_end_draw()
   {

      buffer_lock_round_swap_key_buffers();

   }


   bool graphics::buffer_lock_round_swap_key_buffers()
   {

      return true;

   }


   bool graphics::on_update_screen(buffer_item * pitem)
   {

      //UNREFERENCED_PARAMETER(pitem);


      return true;

   }


   bool graphics::update_buffer(buffer_item * pitem)
   {

      return true;

   }


   bool graphics::ipc_copy(const pixmap* ppixmap)
   {

      return false;

   }


   void graphics::set_bitmap_source(const string& strBitmapSource)
   {

      throw ::interface_only();

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


   //::image_pointer & graphics::get_buffer_image()
   //{

   //   image_pointer * pimage = nullptr;

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


   i64 graphics::_001GetTopLeftWeightedOpaqueArea(const ::rectangle_i32 &rect)
   {

      _synchronous_lock synchronouslock(get_screen_item()->m_pmutex);

      return get_screen_item()->m_pimage->_001GetTopLeftWeightedOpaqueArea(0, rect);

   }


} // namespace graphics



