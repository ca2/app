#include "framework.h"
#include "device_context.h"


namespace graphics
{


   device_context::device_context()
   {

   }


   device_context::~device_context()
   {

   }



   ::draw2d::graphics * device_context::on_begin_draw()
   {

      if (m_spgraphics.is_null())
      {

         __construct(m_spgraphics);

      }

      if (m_spgraphics->get_os_data() == nullptr)
      {

         bool bOk = m_spgraphics->CreateWindowDC(m_pimpl->m_oswindow);

         if (!bOk)
         {

            __throw(::exception::exception("failed to reference"));

         }

      }

      m_spgraphics->on_begin_draw(m_pimpl->m_oswindow, m_pimpl->m_puserinteraction->ui_state().m_size);

      return m_spgraphics;

   }


   bool device_context::update_window()
   {

      try
      {

         m_spgraphics->on_end_draw(m_pimpl->m_oswindow);

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   //::size window_buffer::window_size()
   //{
   //
   //   if (::is_null(m_pimpl))
   //   {
   //
   //      return nullptr;
   //
   //   }
   //
   //   return m_pimpl->m_puserinteraction->size();
   //
   //}


} // namespace graphics



