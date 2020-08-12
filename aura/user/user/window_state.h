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


   __memory(window_state)
   {

      ::point                                m_pointScreen;
      ::point                                m_point;
      ::size                                 m_size;
      ::zorder                               m_zorder;
      ::edisplay                             m_edisplay3;
      ::eactivation                          m_eactivation; // "one-shot"
      ::eappearance                          m_eappearance;



      bool operator == (const window_state & windowstate) const { return !memcmp(this, &windowstate, sizeof(window_state)); }
      bool operator != (const window_state & windowstate) const { return !operator == (windowstate); }

      inline auto screen_rect() { return ::rect(m_pointScreen, m_size); }
      inline auto rect() { return ::rect(m_point, m_size); }
      //inline void place(const ::rect & rect) { m_point = rect.origin(); m_size = rect.size(); }

      

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
