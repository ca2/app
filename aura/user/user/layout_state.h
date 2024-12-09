// Split to visual_state.h and zorder.h by camilo on 2022-08-27 02:11 <3ThomasBorregaardSorensen!!
#pragma once


#include "visual_state.h"
#include "zorder.h"
#include "acme/user/user/activation.h"



namespace user
{


   class CLASS_DECL_AURA layout_state :
      public visual_state
   {
   public:


      ::zorder                            m_zorder;
      ::user::activation                  m_activation;


      void reset_pending()
      {

         m_zorder.clear_request();
         m_activation.clear();
         //m_bImpactUpdateGoingOn = false;

      }

      const class visual_state& visual() const { return* this; }

      using visual_state::operator =;

      layout_state& operator = (const ::zorder& zorder) { m_zorder = zorder; return *this; }

      ::zorder & zorder() { return m_zorder; }
      const ::zorder & zorder() const { return m_zorder; }

      void _patch_order(int iOrder) { m_zorder.m_iZOrder = iOrder; }

      ::user::activation activation() const { return m_activation; }
      bool has_activation_request() const
      {

         return m_activation.is_change_request() ||
            m_zorder.is_change_request();


      }
      
      layout_state& operator = (const ::user::activation & useractivation) { m_activation = useractivation; return *this; }
      layout_state& operator += (const ::user::activation & useractivation) { m_activation |= useractivation; return *this; }

      bool operator == (const layout_state & state) const
      {
         return
         this->m_zorder == state.m_zorder
         && this->m_activation == state.m_activation
         && visual_state::operator == (state);
      }
      //bool operator != (const layout_state & layoutstate) const { return !operator == (layoutstate); }

      layout_state & copy_size(const layout_state & layoutstate)
      {

         m_size = layoutstate.m_size;

         return *this;

      }

      layout_state & copy_position(const layout_state & layoutstate)
      {

         m_point2 = layoutstate.m_point2;

         return *this;

      }

      layout_state & copy_zorder(const layout_state & layoutstate)
      {

         m_zorder = layoutstate.m_zorder;

         return *this;

      }


      layout_state & copy_display(const layout_state & layoutstate)
      {

         m_edisplay = layoutstate.m_edisplay;
         m_eappearance = layoutstate.m_eappearance;
         m_activation = layoutstate.m_activation;

         return *this;

      }


      layout_state & operator = (const layout_state & layoutstate)
      {

         visual_state::operator=(layoutstate);
         m_zorder = layoutstate.m_zorder;
         m_activation = layoutstate.m_activation;

         return *this;

      }


   };


} // namespace user
