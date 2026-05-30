// From layout_state.h by camilo on 2022-08-27 02:04 <3ThomasBorregaardSorensen!! 
// ... elsker mig as Jeg elsker dig?!
#pragma once


struct win32_zorder_t{};

class CLASS_DECL_AURA zorder
{
public:


   enum_zorder    m_ezorder;
   iptr           m_iZOrder;


   zorder();

   zorder(const zorder & zorder);
   zorder(enum_zorder ezorder);
   zorder(const e_zorder & ezorder);

   zorder(win32_zorder_t, iptr iZ);
   //zorder(oswindow hwnd);

   //oswindow get_os_data() const;

   //operator operating_system_window() const;

   void * __win32_HWND() const;

   ::i32 get_sort_ezorder() const;

   bool is_stable() const;

   bool is_change_request() const { return !is_stable(); }

   bool is_set() const;

   bool operator == (const zorder & zorder) const;

   bool operator < (const zorder & zorder) const;

   bool operator <= (const zorder & zorder) const;

   ///zorder & operator = (oswindow hwnd);

   zorder & operator = (enum_zorder ezorder);

   zorder & operator = (iptr i);

   zorder & operator = (const zorder & zorder);


   void clear_request();

   void set_request();

   bool defer_set_request(::i32 iZOrder);


};



