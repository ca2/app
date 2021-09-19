#include "framework.h"
#include "aura/graphics/graphics/_graphics.h"
#include "opengl_buffer.h"


namespace opengl
{


   buffer::buffer()
   {

   }


   buffer::~buffer()
   {

   }


   ::e_status buffer::initialize_graphics_graphics(::user::interaction_impl * pimpl)
   {

      return ::success;

   }


   bool buffer::update_buffer(const ::size_i32 & size, int iStride)
   {

      return ::graphics::buffer::update_buffer(size, iStride);

   }


   void buffer::destroy_buffer()
   {

      ::graphics::buffer::destroy_buffer();

   }


   synchronization_object * buffer::get_draw_lock()
   {

      return mutex();

   }


   ::draw2d::graphics * buffer::on_begin_draw()
   {

      //if (m_spgraphics.is_null())
      //{

      //   m_spgraphics.create(this);

      //}

      //if(m_spgraphics->get_os_data() == nullptr)
      //{

      //   bool bOk = m_spgraphics->CreateWindowDC(m_pimpl->m_oswindow);

      //   if (!bOk)
      //   {

      //      __throw(::exception("failed to reference"););

      //   }

      //}

      //m_spgraphics->on_begin_draw(m_pimpl->m_oswindow, m_pimpl->m_rectParentClient.size());

      //return m_spgraphics;

      return nullptr;

   }


   bool buffer::update_window()
   {

      //m_spgraphics->on_end_draw(m_pimpl->m_oswindow);
      return true;

   }




} // namespace opengl



