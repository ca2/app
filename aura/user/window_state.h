#pragma once


class CLASS_DECL_AURA zorder
{
public:


   enum_zorder    m_ezorder;
   iptr           m_iZOrder;


   zorder();

   zorder(const zorder & zorder);
   zorder(enum_zorder ezorder);

   zorder(iptr iZ);
   //zorder(oswindow hwnd);

   //oswindow get_os_data() const;

   operator oswindow() const;

   int get_sort_ezorder() const;

   bool is_stable() const;

   bool is_change_request() const { return !is_stable(); }

   bool is_set() const;

   bool operator != (const zorder & zorder) const;

   bool operator == (const zorder & zorder) const;

   bool operator < (const zorder & zorder) const;

   bool operator <= (const zorder & zorder) const;

   ///zorder & operator = (oswindow hwnd);

   zorder & operator = (enum_zorder ezorder);

   zorder & operator = (iptr i);

   zorder & operator = (const zorder & zorder);


   void clear_request();

   void set_request();

   bool defer_set_request(int iZOrder);


};


namespace user
{


   class CLASS_DECL_EXPORT visual_state
   {
   public:


      ::point_i32                            m_point;
      ::size_i32                             m_size;
      ::e_display                            m_edisplay;
      ::e_appearance                         m_eappearance;


      visual_state() { }


      ::e_display display() const { return m_edisplay; }
      ::e_display & display() { return m_edisplay; }

      bool is_visible() const { return ::is_visible(display()); }
      bool is_screen_visible() const { return ::is_screen_visible(display()); }

      ::e_appearance appearance() const;

      visual_state& operator = (const enum_appearance& eappearance);
      visual_state& operator |= (const enum_appearance& eappearance);
      visual_state& operator -= (const enum_appearance& eappearance);
      visual_state& operator ^= (const enum_appearance& eappearance);

      ::point_i32 origin() const { return m_point; }
      ::point_i32 & origin() { return m_point; }

      ::size_i32 size() const { return m_size; }
      ::size_i32 & size() { return m_size; }

      template < primitive_rectangle RECTANGLE >
      visual_state& operator = (const RECTANGLE & rectangle) { m_point = rectangle.origin(); m_size = rectangle.size(); return *this; }

      ::i32 left() const { return m_point.x; }
      ::i32 & left()  { return m_point.x; }

      ::i32 top() const { return m_point.y; }
      ::i32 & top() { return m_point.y; }

      ::i32 width() const { return m_size.cx; }
      ::i32 & width()  { return m_size.cx; }

      ::i32 height() const { return m_size.cy; }
      ::i32 & height() { return m_size.cy; }

      bool operator == (const visual_state & visualstate) const { return !memcmp(this, &visualstate, sizeof(visual_state)); }
      bool operator != (const visual_state & visualstate) const { return !operator == (visualstate); }

      auto client_rect() const { return ::rectangle_i32(m_size); }
      void client_rect(RECTANGLE_I32 * lprect) const { *lprect = client_rect(); }

      auto parent_client_rect() const { return ::rectangle_i32(m_point, m_size); }
      void parent_client_rect(RECTANGLE_I32 * lprect) const { *lprect = parent_client_rect(); }


   };


   class CLASS_DECL_EXPORT window_state :
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

      window_state& operator = (const ::zorder& zorder) { m_zorder = zorder; return *this; }

      class ::zorder zorder() const { return m_zorder; }

      void _patch_order(int iOrder) { m_zorder.m_iZOrder = iOrder; }

      ::e_activation activation() const { return m_eactivation; }
      window_state& operator = (const enum_activation& eactivation) { m_eactivation = eactivation; return *this; }
      window_state& operator += (const enum_activation& eactivation) { m_eactivation |= eactivation; return *this; }

      bool operator == (const window_state & windowstate) const { return !memcmp(this, &windowstate, sizeof(window_state)); }
      bool operator != (const window_state & windowstate) const { return !operator == (windowstate); }

      window_state & copy_size(window_state & windowstate)
      {

         m_size = windowstate.m_size;

         return *this;

      }

      window_state & copy_position(window_state & windowstate)
      {

         m_point = windowstate.m_point;

         return *this;

      }

      window_state & copy_zorder(window_state & windowstate)
      {

         m_zorder = windowstate.m_zorder;

         return *this;

      }

      window_state & copy_display(window_state & windowstate)
      {

         m_edisplay = windowstate.m_edisplay;
         m_eappearance = windowstate.m_eappearance;
         m_eactivation = windowstate.m_eactivation;

         return *this;

      }


   };


   __memory(window_rectangle)
   {

      edisplay                   m_edisplayPrevious = e_display_none;
      edisplay                   m_edisplay = e_display_none;
      eappearance                m_eappearance = e_appearance_none;
      rectangle_i32              m_rectangleSnapped = nullptr;
      rectangle_i32              m_rectangleRestored = nullptr;
      rectangle_i32              m_rectangleWindow = nullptr;
      int                        m_iControlBoxRightToLeft = 0;
      index                      m_iWorkspace = 0;

      using memory_template < window_rectangle >::operator=;
      bool operator == (const window_rectangle & rectangle) const {return !memcmp(this, &rectangle, sizeof(window_rectangle)); }
      bool operator != (const window_rectangle & rectangle) const {return !operator==(rectangle); }

   };


} // namespace user
