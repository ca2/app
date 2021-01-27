#pragma once


class CLASS_DECL_AURA zorder
{
public:


   e_zorder       m_ezorder;
   iptr           m_iZOrder;


   zorder();

   zorder(const zorder & zorder);
   zorder(e_zorder ezorder);

   zorder(iptr iZ);
   zorder(oswindow hwnd);

   oswindow get_os_data() const;

   operator oswindow() const;

   int get_sort_ezorder() const;

   bool is_stable() const;

   bool is_change_request() const { return !is_stable(); }

   bool is_set() const;

   bool operator != (const zorder & zorder) const;

   bool operator == (const zorder & zorder) const;

   bool operator < (const zorder & zorder) const;

   bool operator <= (const zorder & zorder) const;

   zorder & operator = (oswindow hwnd);

   zorder & operator = (e_zorder ezorder);

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
   protected:

      ::point                                m_pointScreen;
      ::point                                m_pointHost;
      ::point                                m_point;
      ::size                                 m_size;
      ::e_display                            m_edisplay3;
      ::e_appearance                         m_eappearance;
      bool                                   m_bReady;
      bool                                   m_bModified;
      //::user::interaction_layout *           m_playout; // had mutex dependency, not anymore for now so commented out

      //friend class interaction;
      //friend class interaction_layout;

   public:

      visual_state() { m_bReady = true; m_bModified = false; m_edisplay3 = e_display_none;  }

      //void set_interaction_layout(::user::interaction_layout* playout) { m_playout = playout; }

      inline bool is_ready() const { return m_bReady; }

      inline bool is_modified() const { return m_bModified; }

      inline void set_ready(bool bSet = true) { m_bReady = bSet; }

      inline void set_modified(bool bSet = true) { m_bModified = bSet; }

      ::e_display display() const { return m_edisplay3; }
      visual_state& operator = (const enum_display& edisplay) { set_modified(); m_edisplay3 = edisplay; return *this; }

      bool is_visible() const { return ::is_visible(display()); }
      bool is_screen_visible() const { return ::is_screen_visible(display()); }


      ::e_appearance appearance() const;
      visual_state& operator = (const enum_appearance& eappearance);
      visual_state& operator |= (const enum_appearance& eappearance);
      visual_state& operator -= (const enum_appearance& eappearance);
      visual_state& operator ^= (const enum_appearance& eappearance);


      ::point origin() const { return m_point; }
      visual_state& operator = (const ::point & point)
      { 
         set_modified(); 
         
         m_point = point; 
         
         return *this; 
      }


      ::point screen_origin() const { return m_pointScreen; }
      ::point& screen_origin() { return m_pointScreen; }

      ::point host_origin() const { return m_pointHost; }
      ::point& host_origin() { return m_pointHost; }

      ::size size() const { return m_size; }

      template < primitive_size SIZE >
      visual_state& operator = (const SIZE & size) { set_modified(); m_size = size; return *this; }


      template < primitive_rectangle RECTANGLE >
      visual_state& operator = (const RECTANGLE & rectangle) { set_modified(); m_point = rectangle.origin(); m_size = rectangle.size(); return *this; }


      ::i32 width() const { return m_size.cx; }
      ::i32 height() const { return m_size.cy; }


      bool operator == (const visual_state & visualstate) const { return !memcmp(this, &visualstate, sizeof(visual_state)); }
      bool operator != (const visual_state & visualstate) const { return !operator == (visualstate); }


      inline auto screen_rect() const { return ::rect(m_pointScreen, m_size); }
      void screen_rect(LPRECT32 lprect) const { *lprect = screen_rect(); }

      inline auto host_rect() const { return ::rect(m_pointHost, m_size); }
      void host_rect(LPRECT32 lprect) const { *lprect = host_rect(); }

      auto client_rect() const { return ::rect(m_size); }
      void client_rect(LPRECT32 lprect) const { *lprect = client_rect(); }


      auto parent_client_rect() const { return ::rect(m_point, m_size); }
      void parent_client_rect(LPRECT32 lprect) const { *lprect = parent_client_rect(); }


   };


   class CLASS_DECL_EXPORT window_state :
      public visual_state
   {
   protected:

      ::zorder                               m_zorder;
      ::e_activation                          m_eactivation; // "one-shot"

      //friend class interaction;
      //friend class interaction_layout;

   public:


      void clear_ephemeral()
      {

         m_zorder.clear_request();
         m_eactivation = e_activation_default;

      }

      const class visual_state& visual() const { return* this; }


      using visual_state::operator =;


      window_state& operator = (const ::zorder& zorder) { m_zorder = zorder; if (m_zorder.is_change_request()) set_modified(); return *this; }


      class ::zorder zorder() const { return m_zorder; }

      void _patch_order(int iOrder) { m_zorder.m_iZOrder = iOrder; }


      ::e_activation activation() const { return m_eactivation; }
      window_state& operator = (const enum_activation& eactivation) { m_eactivation = eactivation; if(m_eactivation) set_modified(); return *this; }
      window_state& operator += (const enum_activation& eactivation) { m_eactivation |= eactivation; if (m_eactivation) set_modified(); return *this; }


      bool operator == (const window_state & windowstate) const { return !memcmp(this, &windowstate, sizeof(window_state)); }
      bool operator != (const window_state & windowstate) const { return !operator == (windowstate); }


      window_state & copy_layout(window_state & windowstate)
      {

         m_size = windowstate.m_size;

         return *this;

      }

      window_state & copy_position(window_state & windowstate)
      {

         m_pointScreen = windowstate.m_pointScreen;
         m_pointHost = windowstate.m_pointHost;
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

         m_edisplay3 = windowstate.m_edisplay3;
         m_eappearance = windowstate.m_eappearance;
         m_eactivation = windowstate.m_eactivation;

         return *this;

      }

   };


   __memory(window_rect)
   {

      edisplay                   m_edisplayPrevious = e_display_none;
      edisplay                   m_edisplay = e_display_none;
      eappearance                m_eappearance = e_appearance_none;
      rect                       m_rectSnapped = nullptr;
      rect                       m_rectRestored = nullptr;
      rect                       m_rectWindow = nullptr;
      int                        m_iControlBoxRightToLeft = 0;
      index                      m_iWkspace = 0;

      using memory_template < window_rect >::operator=;
      bool operator == (const window_rect & rect) const {return !memcmp(this, &rect, sizeof(window_rect)); }
      bool operator != (const window_rect & rect) const {return !operator==(rect); }

   };


} // namespace user
