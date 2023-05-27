// Split to visual_state.h and zorder.h by camilo on 2022-08-27 02:11 <3ThomasBorregaardSørensen!!
#pragma once


#include "visual_state.h"
#include "zorder.h"
//#include "acme/memory/memory.h"


namespace user
{


   class CLASS_DECL_EXPORT layout_state :
      public visual_state
   {
   public:


      ::zorder                            m_zorder;
      ::e_activation                      m_eactivation;


      void clear_activation()
      {

         m_zorder.clear_request();
         m_eactivation = e_activation_default;

      }

      const class visual_state& visual() const { return* this; }

      using visual_state::operator =;

      layout_state& operator = (const ::zorder& zorder) { m_zorder = zorder; return *this; }

      ::zorder & zorder() { return m_zorder; }
      const ::zorder & zorder() const { return m_zorder; }

      void _patch_order(int iOrder) { m_zorder.m_iZOrder = iOrder; }

      ::e_activation activation() const { return m_eactivation; }
      layout_state& operator = (const enum_activation& eactivation) { m_eactivation = eactivation; return *this; }
      layout_state& operator += (const enum_activation& eactivation) { m_eactivation |= eactivation; return *this; }

      bool operator == (const layout_state & windowstate) const { return !memcmp(this, &windowstate, sizeof(layout_state)); }
      bool operator != (const layout_state & windowstate) const { return !operator == (windowstate); }

      layout_state & copy_size(layout_state & windowstate)
      {

         m_size = windowstate.m_size;

         return *this;

      }

      layout_state & copy_position(layout_state & windowstate)
      {

         m_point = windowstate.m_point;

         return *this;

      }

      layout_state & copy_zorder(layout_state & windowstate)
      {

         m_zorder = windowstate.m_zorder;

         return *this;

      }

      layout_state & copy_display(layout_state & windowstate)
      {

         m_edisplay = windowstate.m_edisplay;
         m_eappearance = windowstate.m_eappearance;
         m_eactivation = windowstate.m_eactivation;

         return *this;

      }


   };


   __memory(window_rectangle)
   {

      e_display                  m_edisplayPrevious = e_display_none;
      e_display                  m_edisplayLastNormal = e_display_normal;
      e_display                  m_edisplay = e_display_none;
      e_appearance               m_eappearance = e_appearance_none;
      rectangle_i32              m_rectangleSnapped = nullptr;
      rectangle_i32              m_rectangleNormal = nullptr;
      rectangle_i32              m_rectangleBroad = nullptr;
      rectangle_i32              m_rectangleCompact = nullptr;
      rectangle_i32              m_rectangleWindow = nullptr;
      int                        m_iControlBoxRightToLeft = 0;
      index                      m_iWorkspace = 0;

      using memory_template < window_rectangle >::operator=;
      bool operator == (const window_rectangle & rectangle) const {return !memcmp(this, &rectangle, sizeof(window_rectangle)); }
      bool operator != (const window_rectangle & rectangle) const {return !operator==(rectangle); }

   };


} // namespace user
