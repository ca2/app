#include "framework.h"
#include "aura/user/_user.h"


namespace graphics
{


   graphics::graphics()
   {

      defer_create_mutex();

      m_bNewBuffer = false;

   }


   graphics::~graphics()
   {

      // destroy_buffer();

      //destroy_();

      finalize();

   }


   ::e_status graphics::initialize_graphics_graphics(::user::interaction_impl * pimpl)
   {

      try
      {

         finalize();

      }
      catch (...)
      {

      }

      auto estatus = object::initialize(pimpl);

      if (!estatus)
      {

         return estatus;

      }

      m_pimpl = pimpl;

      m_pwindow = pimpl->get_window();

      return estatus;

   }


   void graphics::finalize()
   {

      destroy_buffer();

      object::finalize();

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

      auto size = m_pimpl->m_puserinteraction->layout().design().size();

      return size;

   }


   bool graphics::update_window()
   {

      return true;

   }


   ::sync * graphics::get_draw_lock()
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

      return false;

   }


   ::image_pointer & graphics::get_buffer_image()
   {

      image_pointer * pimage = nullptr;

      return *pimage;

   }


   sync * graphics::get_buffer_sync()
   {

      return mutex();

   }


   ::image_pointer & graphics::get_screen_image()
   {

      image_pointer * pimage = nullptr;

      return *pimage;

   }


   sync * graphics::get_screen_sync()
   {

      return mutex();

   }


   i64 graphics::_001GetTopLeftWeightedOpaqueArea(const RECTANGLE_I32 * lpcrect)
   {

      sync_lock sl(get_screen_sync());

      ::color::color colorTransparent(0);

      return get_screen_image()->_001GetTopLeftWeightedOpaqueArea(colorTransparent, lpcrect);

   }

} // namespace graphics



