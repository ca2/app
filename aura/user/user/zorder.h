// From layout_state.h by camilo on 2022-08-27 02:04 <3ThomasBorregaardSorensen!! 
// ... elsker mig as Jeg elsker dig?!
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



