// From layout_state.h by camilo on 2022-08-27 02:08 <3ThomasBorregaardSorense!! *8*8infinitywithThommy*8*8!!
#pragma once


namespace user
{


   class CLASS_DECL_AURA visual_state
   {
   public:


      ::point_i32                            m_point;
      ::size_i32                             m_size;
      ::e_display                            m_edisplay;
      ::e_appearance                         m_eappearance;
      bool                                   m_bProdevian = false;



      visual_state() { }


      ::e_display display() const { return m_edisplay; }
      ::e_display & display() { return m_edisplay; }

      bool is_visible() const { return ::is_visible(display()); }
      bool is_screen_visible() const { return ::is_screen_visible(display()); }

      ::e_appearance appearance() const;

      visual_state & operator = (const enum_appearance & eappearance);
      visual_state & operator |= (const enum_appearance & eappearance);
      visual_state & operator -= (const enum_appearance & eappearance);
      visual_state & operator ^= (const enum_appearance & eappearance);

      ::point_i32 origin() const { return m_point; }
      ::point_i32 & origin() { return m_point; }

      ::size_i32 size() const { return m_size; }
      ::size_i32 & size() { return m_size; }

      template < primitive_rectangle RECTANGLE >
      visual_state & operator = (const RECTANGLE & rectangle) { m_point = rectangle.origin(); m_size = rectangle.size(); return *this; }

      ::i32 left() const { return m_point.x; }
      ::i32 & left() { return m_point.x; }

      ::i32 top() const { return m_point.y; }
      ::i32 & top() { return m_point.y; }

      ::i32 width() const { return m_size.cx; }
      ::i32 & width() { return m_size.cx; }

      ::i32 height() const { return m_size.cy; }
      ::i32 & height() { return m_size.cy; }

      bool operator == (const visual_state & visualstate) const { return !memcmp(this, &visualstate, sizeof(visual_state)); }
      bool operator != (const visual_state & visualstate) const { return !operator == (visualstate); }

      auto client_rect() const { return ::rectangle_i32(m_size); }
      void client_rect(RECTANGLE_I32 & rect) const { rect = client_rect(); }

      auto parent_client_rect() const { return ::rectangle_i32(m_point, m_size); }
      void parent_client_rect(RECTANGLE_I32 & rect) const { rect = parent_client_rect(); }

      void bottom_right(const ::point_i32 & point) { m_size = point - m_point; }


   };



} // namespace user



