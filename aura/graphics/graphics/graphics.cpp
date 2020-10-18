#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


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


   ::estatus graphics::initialize_graphics_graphics(::user::interaction_impl * pimpl)
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

      m_oswindow = pimpl->m_oswindow;

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


   ::size graphics::window_size()
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

      sync_lock sl(mutex());

      round_swap_key_buffers();

   }


   bool graphics::round_swap_key_buffers()
   {

      return true;

   }


   bool graphics::update_window(::image * pimage)
   {


      return true;

   }


   bool graphics::update_buffer(const ::size & size, int iStrideParam)
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


   i64 graphics::_001GetTopLeftWeightedOpaqueArea(LPCRECT lpcrect)
   {

      sync_lock sl(get_screen_sync());

      color colorTransparent(0);

      return get_screen_image()->_001GetTopLeftWeightedOpaqueArea(colorTransparent, lpcrect);

   }

} // namespace graphics



