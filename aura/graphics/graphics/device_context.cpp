#include "platform.h"
//#include "_.h"
//#include "_graphics.h"
#include "aura/graphics/graphics/buffer_item.h"
#include "device_context.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/user/user/interaction.h"
#include "aura/windowing/window.h"


namespace graphics
{


   //device_context::device_context()
   //{

   //}


   //device_context::~device_context()
   //{

   //}



   //::draw2d::graphics_lease device_context::on_begin_draw()
   //{

   //   auto pitem = get_buffer_item();

   //   if (m_pdraw2dgraphics.is_null())
   //   {

   //      constructø(m_pdraw2dgraphics);

   //   }

   //   if (m_pdraw2dgraphics.nok())
   //   {

   //      //bool bOk = 
   //      
   //      m_pdraw2dgraphics->create_window_graphics(m_pwindow);

   //      //if (!bOk)
   //      //{

   //      //   throw ::exception(error_failed, "failed to reference");

   //      //}

   //   }

   //   auto puserinteraction = m_pwindow->user_interaction();

   //   m_pdraw2dgraphics->on_begin_draw(m_pwindow, puserinteraction->const_layout().design().size());

   //   //return m_pdraw2dgraphics;

   //   return pitem->acquire_graphics();

   //}


   //bool device_context::update_window()
   //{

   //   try
   //   {

   //      m_pdraw2dgraphics->on_end_draw(m_pwindow);

   //   }
   //   catch (...)
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   ////::i32_size window_buffer::window_size()
   ////{
   ////
   ////   if (::is_null(m_pwindow))
   ////   {
   ////
   ////      return nullptr;
   ////
   ////   }
   ////
   ////   return m_pwindow->m_puserinteraction->size();
   ////
   ////}


} // namespace graphics



