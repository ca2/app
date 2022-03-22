#include "framework.h"
//#include "aura/user/_user.h"
#include "_.h"
#include "_graphics.h"


namespace graphics
{


   graphics::graphics()
   {

      defer_create_mutex();

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

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pimpl = pimpl;

      m_pwindow = pimpl->get_window();

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


   ::size_i32 graphics::window_size()
   {

      if (::is_null(m_pimpl))
      {

         return nullptr;

      }

      if (!m_pimpl->m_puserinteraction)
      {

         return nullptr;

      }

      auto & d = m_pimpl->m_puserinteraction->layout().design();

      if(d.m_size.cx == 1)
      {

         printf("cx=1");

      }
      else
      {
         printf("cx!=1");

      }

      return d.m_size;

   }


   bool graphics::update_window()
   {

      return true;

   }


   ::synchronization_object * graphics::get_draw_lock()
   {

      return mutex();

   }


   ::draw2d::graphics * graphics::on_begin_draw()
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


   bool graphics::update_window(::image * pimage)
   {


      return true;

   }


   bool graphics::update_buffer(const ::size_i32 & size, int iStrideParam)
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


   ::image_pointer & graphics::get_buffer_image()
   {

      image_pointer * pimage = nullptr;

      return *pimage;

   }


   synchronization_object * graphics::get_buffer_sync()
   {

      return mutex();

   }


   ::image_pointer & graphics::get_screen_image()
   {

      image_pointer * pimage = nullptr;

      return *pimage;

   }


   synchronization_object * graphics::get_screen_sync()
   {

      return mutex();

   }


   i64 graphics::_001GetTopLeftWeightedOpaqueArea(const RECTANGLE_I32 * lpcrect)
   {

      synchronous_lock synchronouslock(get_screen_sync());

      ::color::color colorTransparent(0);

      return get_screen_image()->_001GetTopLeftWeightedOpaqueArea(colorTransparent, lpcrect);

   }

} // namespace graphics



