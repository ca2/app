#include "framework.h"
#include "opengl_buffer.h"


namespace opengl
{


   buffer::buffer()
   {

   }


   buffer::~buffer()
   {

   }


   estatus buffer::initialize_graphics_graphics(::user::interaction_impl * pimpl)
   {

      return ::success;

   }


   bool buffer::update_buffer(const ::size & size, int iStride)
   {

      return ::graphics::buffer::update_buffer(size, iStride);

   }


   void buffer::destroy_buffer()
   {

      ::graphics::buffer::destroy_buffer();

   }


   sync * buffer::get_draw_lock()
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

      //      __throw(::exception::exception("failed to reference"););

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



