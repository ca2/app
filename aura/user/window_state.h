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
      ::point                                m_point;
      ::size                                 m_size;
      ::edisplay                             m_edisplay3;
      ::eappearance                          m_eappearance;
      bool                                   m_bReady;
      bool                                   m_bModified;
      //::user::interaction_layout *           m_playout; // had mutex dependency, not anymore for now so commented out

      //friend class interaction;
      //friend class interaction_layout;

   public:

      visual_state() { m_bReady = true; m_bModified = false; }

      //void set_interaction_layout(::user::interaction_layout* playout) { m_playout = playout; }

      inline bool is_ready() const { return m_bReady; }

      inline bool is_modified() const { return m_bModified; }

      inline void set_ready(bool bSet = true) { m_bReady = bSet; }

      inline void set_modified(bool bSet = true) { m_bModified = bSet; }

      ::edisplay display() const { return m_edisplay3; }
      visual_state& operator = (const e_display& edisplay) { set_modified(); m_edisplay3 = edisplay; return *this; }

      bool is_visible() const { return ::is_visible(display()); }
      bool is_screen_visible() const { return ::is_screen_visible(display()); }


      ::eappearance appearance() const { return m_eappearance; }
      visual_state& operator = (const e_appearance& eappearance) { m_eappearance = eappearance; if(m_eappearance) set_modified(); return *this; }
      visual_state& operator |= (const e_appearance& eappearance) { m_eappearance |= eappearance; if (m_eappearance) set_modified(); return *this; }
      visual_state& operator -= (const e_appearance& eappearance) { m_eappearance -= eappearance; if (m_eappearance) set_modified(); return *this; }
      visual_state& operator ^= (const e_appearance& eappearance) { m_eappearance ^= eappearance; if (m_eappearance) set_modified(); return *this; }


      ::point origin() const { return m_point; }
      visual_state& operator = (const ::point & point) { set_modified(); m_point = point; return *this; }


      ::point screen_origin() const { return m_pointScreen; }
      ::point& screen_origin() { return m_pointScreen; }

      ::size size() const { return m_size; }
      visual_state& operator = (const ::size & size) { set_modified(); m_size = size; return *this; }


      visual_state& operator = (const ::rect & rect) { set_modified(); m_point = rect.origin(); m_size = rect.size(); return *this; }


      LONG width() const { return m_size.cx; }
      LONG height() const { return m_size.cy; }


      bool operator == (const visual_state & visualstate) const { return !memcmp(this, &visualstate, sizeof(visual_state)); }
      bool operator != (const visual_state & visualstate) const { return !operator == (visualstate); }


      inline auto screen_rect() const { return ::rect(m_pointScreen, m_size); }
      void screen_rect(LPRECT lprect) const { *lprect = screen_rect(); }


      auto client_rect() const { return ::rect(m_size); }
      void client_rect(LPRECT lprect) const { *lprect = client_rect(); }


      auto parent_client_rect() const { return ::rect(m_point, m_size); }
      void parent_client_rect(LPRECT lprect) const { *lprect = parent_client_rect(); }


   };


   class CLASS_DECL_EXPORT window_state :
      public visual_state
   {
   protected:

      ::zorder                               m_zorder;
      ::eactivation                          m_eactivation; // "one-shot"

      //friend class interaction;
      //friend class interaction_layout;

   public:


      void clear_ephemeral()
      { 

         m_zorder.clear_request();
         m_eactivation = activation_none; 

      }

      const class visual_state& visual() const { return* this; }
      

      using visual_state::operator =;


      window_state& operator = (const ::zorder& zorder) { m_zorder = zorder; if (m_zorder.is_change_request()) set_modified(); return *this; }


      class ::zorder zorder() const { return m_zorder; }

      void _patch_order(int iOrder) { m_zorder.m_iZOrder = iOrder; }


      ::eactivation activation() const { return m_eactivation; }
      window_state& operator = (const e_activation& eactivation) { m_eactivation = eactivation; if(m_eactivation) set_modified(); return *this; }
      window_state& operator += (const e_activation& eactivation) { m_eactivation |= eactivation; if (m_eactivation) set_modified(); return *this; }


      bool operator == (const window_state & windowstate) const { return !memcmp(this, &windowstate, sizeof(window_state)); }
      bool operator != (const window_state & windowstate) const { return !operator == (windowstate); }


      window_state & operator = (window_state & windowstate) 
      {
      
         if (this != &windowstate)
         {

            m_pointScreen  = windowstate.m_pointScreen;
            m_point = windowstate.m_point;
            m_size = windowstate.m_size;
            m_edisplay3 = windowstate.m_edisplay3;
            m_eappearance = windowstate.m_eappearance;
            m_zorder = windowstate.m_zorder;
            m_eactivation = windowstate.m_eactivation;

         }

         return *this;
      
      }


   };


   __memory(window_rect)
   {

      edisplay                   m_edisplayPrevious = display_none;
      edisplay                   m_edisplay = display_none;
      eappearance                m_eappearance = appearance_none;
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
