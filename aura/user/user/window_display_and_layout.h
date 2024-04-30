// Split to visual_state.h and zorder.h by camilo on 2022-08-27 02:11 <3ThomasBorregaardSorensen!!
#pragma once


//#include "visual_state.h"
//#include "zorder.h"
#include "acme/memory/memory.h"


namespace user
{


   class CLASS_DECL_AURA window_display_and_layout :
      public raw_block < window_display_and_layout >
   {
   public:

      //using raw_block_tag = raw_block_t;

      e_display                  m_edisplayPrevious;
      e_display                  m_edisplayLastNormal;
      e_display                  m_edisplay;
      e_appearance               m_eappearance;
      rectangle_i32              m_rectangleSnapped;
      rectangle_i32              m_rectangleNormal;
      rectangle_i32              m_rectangleBroad;
      rectangle_i32              m_rectangleCompact;
      rectangle_i32              m_rectangleWindow;
      int                        m_iControlBoxRightToLeft;
      ::raw::index                      m_iWorkspace;

      //using memory_template < window_rectangle >::operator=;
      // bool operator == (const window_rectangle & rectangle) const {return memory_order(this, &rectangle, sizeof(window_rectangle)) == 0; }
      // bool operator != (const window_rectangle & rectangle) const {return !operator==(rectangle); }

   };


} // namespace user



