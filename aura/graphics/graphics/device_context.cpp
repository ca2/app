#include "framework.h"
//#include "_.h"
//#include "_graphics.h"
#include "device_context.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/user/user/interaction_impl.h"
#include "aura/user/user/interaction.h"


namespace graphics
{


   device_context::device_context()
   {

   }


   device_context::~device_context()
   {

   }



   buffer_item * device_context::on_begin_draw()
   {

      auto pitem = get_buffer_item();

      if (m_spgraphics.is_null())
      {

         __construct(m_spgraphics);

      }

      if (m_spgraphics->get_os_data() == nullptr)
      {

         //bool bOk = 
         
         m_spgraphics->CreateWindowDC(m_pimpl->oswindow());

         //if (!bOk)
         //{

         //   throw ::exception(error_failed, "failed to reference");

         //}

      }

      m_spgraphics->on_begin_draw(m_pimpl->oswindow(), m_pimpl->m_puserinteraction->const_layout().design().size());

      //return m_spgraphics;

      return pitem;

   }


   bool device_context::update_window()
   {

      try
      {

         m_spgraphics->on_end_draw(m_pimpl->oswindow());

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   //::size_i32 window_buffer::window_size()
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



