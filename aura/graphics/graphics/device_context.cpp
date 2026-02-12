#include "framework.h"
//#include "_.h"
//#include "_graphics.h"
#include "device_context.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/user/user/interaction.h"
#include "aura/windowing/window.h"


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

         øconstruct(m_spgraphics);

      }

      if (m_spgraphics->get_os_data() == nullptr)
      {

         //bool bOk = 
         
         m_spgraphics->CreateWindowDC(m_pwindow);

         //if (!bOk)
         //{

         //   throw ::exception(error_failed, "failed to reference");

         //}

      }

      auto puserinteraction = m_pwindow->user_interaction();

      m_spgraphics->on_begin_draw(m_pwindow, puserinteraction->const_layout().design().size());

      //return m_spgraphics;

      return pitem;

   }


   bool device_context::update_window()
   {

      try
      {

         m_spgraphics->on_end_draw(m_pwindow);

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   //::int_size window_buffer::window_size()
   //{
   //
   //   if (::is_null(m_pwindow))
   //   {
   //
   //      return nullptr;
   //
   //   }
   //
   //   return m_pwindow->m_puserinteraction->size();
   //
   //}


} // namespace graphics



