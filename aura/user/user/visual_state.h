// From layout_state.h by camilo on 2022-08-27 02:08 <3ThomasBorregaardSorense!! *8*8infinitywithThommy*8*8!!
#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/prototype/geometry2d/rectangle.h"


namespace user
{


   class CLASS_DECL_AURA visual_state
   {
   public:


      ::int_point                            m_point2;
      ::int_size                             m_size;
      ::e_display                            m_edisplay;
      ::e_appearance                         m_eappearance;
      ::logic::boolean                       m_bImpactUpdateGoingOn;
      //bool                                   m_bAutoRefresh = false;



      visual_state() { }


      void set_visual_state_origin(const ::int_point & point){m_point2= point;}


      ::e_display display() const { return m_edisplay; }
      ::e_display & display() { return m_edisplay; }

      bool is_visible() const { return ::is_visible(display()); }
      bool is_screen_visible() const { return ::is_screen_visible(display()); }

      ::e_appearance appearance() const;

      visual_state & operator = (const enum_appearance & eappearance);
      visual_state & operator |= (const enum_appearance & eappearance);
      visual_state & operator -= (const enum_appearance & eappearance);
      visual_state & operator ^= (const enum_appearance & eappearance);


      visual_state & operator = (const visual_state & visualstate)
      {
         
         m_point2 = visualstate.m_point2;
         m_size = visualstate.m_size;
         m_edisplay = visualstate.m_edisplay;
         m_eappearance = visualstate.m_eappearance;
         m_bImpactUpdateGoingOn = visualstate.m_bImpactUpdateGoingOn;
         //m_bAutoRefresh = visualstate.m_bAutoRefresh;

         return *this;

      }

      ::int_point origin() const { return m_point2; }
      ::int_point & origin() { return m_point2; }

      ::int_size size() const { return m_size; }
      ::int_size & size() { return m_size; }

      //template < primitive_rectangle RECTANGLE >
      //visual_state & operator = (const RECTANGLE & rectangle) { m_point = rectangle.origin(); m_size = rectangle.size(); return *this; }

      int left() const { return m_point2.x; }
      //int & left() { return m_point.x; }

      int top() const { return m_point2.y; }
      //int & top() { return m_point.y; }

      int width() const { return m_size.cx(); }
      int & width() { return m_size.cx(); }

      int height() const { return m_size.cy(); }
      int & height() { return m_size.cy(); }

      bool operator == (const visual_state & state) const
      {
         return
         m_point2 == state.m_point2
         && m_size == state.m_size
         && m_edisplay == state.m_edisplay
         && m_eappearance == state.m_eappearance;
         //return !memcmp(this, &visualstate, sizeof(visual_state));
      }
      //bool operator != (const visual_state & visualstate) const { return !operator == (visualstate); }

      auto raw_rectangle() const { return ::int_rectangle(m_size); }
      //void raw_rectangle(::int_rectangle & rect) const { rect = raw_rectangle(); }

      auto parent_raw_rectangle() const { return ::int_rectangle(m_point2, m_size); }
      //void parent_raw_rectangle(::int_rectangle & rect) const { rect = parent_raw_rectangle(); }

      void bottom_right(const ::int_point & point) { m_size = point - m_point2; }


   };



} // namespace user



