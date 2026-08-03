// From graphics.h by camilo on 2026-07-31 20:19 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "aura/graphics/draw2d/graphics_lease.h"
#include "aura/graphics/draw2d/graphics_pointer.h"


namespace graphics
{


   class CLASS_DECL_AURA buffer_item :
      virtual public ::particle
   {
   public:


      ::e_graphics                                 m_egraphics;
      ::image::image_pointer                       m_pimageBufferItem;
      ::mutex_pointer                              m_pmutex;
      ::draw2d::graphics_pointer                   m_pgraphicsBufferItem;
      ::i32_point                                  m_pointBufferItem;
      ::i32_size                                   m_sizeBufferItem;
      ::i32_point                                  m_pointBufferItemWindow;
      ::i32_size                                   m_sizeBufferItemWindow;
      ::pointer < manual_reset_happening >         m_pmanualresethappening;
      ::i32_size                                   m_sizeInternal;
      ::i32                                        m_iScan;


      virtual ::draw2d::graphics_lease acquire_graphics();

      virtual void switch_to_draw();

      void destroy() override;


   };


} // namespace graphics



