#include "framework.h"


zorder::zorder()
{

   m_ezorder = zorder_top;

   m_iZOrder = 0;

}

zorder::zorder(const zorder & zorder)
{

   operator = (zorder);

}

zorder::zorder(e_zorder ezorder)
{

   operator = (ezorder);

}


zorder::zorder(iptr iZ)
{

   operator = (iZ);

}


zorder::zorder(oswindow oswindow)
{

   operator = (oswindow);

}


bool zorder::is_stable() const
{

   return m_ezorder == zorder_normal_anchor || m_ezorder == zorder_top_most_anchor;

}


void zorder::clear_request()
{

   if (m_ezorder == zorder_top_most || m_ezorder == zorder_top_most_anchor)
   {

      m_ezorder = zorder_top_most_anchor;

   }
   else
   {

      m_ezorder = zorder_normal_anchor;

   }

}


void zorder::set_request()
{

   if (m_ezorder == zorder_top_most || m_ezorder == zorder_top_most_anchor)
   {

      m_ezorder = zorder_top_most;

   }
   else
   {

      m_ezorder = zorder_normal;

   }

}


bool zorder::defer_set_request(int iZOrder)
{

   if (iZOrder == m_iZOrder)
   {

      clear_request();

      return false;

   }
   else
   {

      m_iZOrder = iZOrder;

      set_request();

      return true;

   }

}


oswindow zorder::get_os_data() const
{

   {

      if (m_ezorder == zorder_normal)
      {

         if (::is_window((oswindow)m_iZOrder))
         {

            return (oswindow)m_iZOrder;

         }
         else
         {

            return nullptr;

         }

      }
      else if (m_ezorder == zorder_top)
      {

         return (oswindow) HWND_TOP;

      }
      else if (m_ezorder == zorder_top_most)
      {

         return (oswindow) HWND_TOPMOST;

      }
      else if (m_ezorder == zorder_bottom)
      {

         return (oswindow) HWND_BOTTOM;

      }
      else
      {

         return nullptr;

      }

   }

}


zorder::operator oswindow() const
{

   return get_os_data();

}


bool zorder::is_set() const
{

   return m_ezorder != zorder_none;

}


bool zorder::operator != (const zorder & zorder) const
{

   return !operator ==(zorder);

}

int zorder::get_sort_ezorder() const
{

   if (m_ezorder == zorder_normal_anchor)
   {

      return zorder_normal;

   }
   else if (m_ezorder == zorder_top_most_anchor)
   {

      return zorder_top_most;

   }
   else
   {

      return m_ezorder;

   }

}


bool zorder::operator == (const zorder & zorder) const
{

   return get_sort_ezorder() == zorder.get_sort_ezorder() && m_iZOrder == zorder.m_iZOrder;

}


bool zorder::operator < (const zorder & zorder) const
{

   if (m_ezorder == zorder.m_ezorder)
   {

      return m_iZOrder < zorder.m_iZOrder;

   }
   else
   {

      return get_sort_ezorder() < zorder.get_sort_ezorder();

   }

}


bool zorder::operator <= (const zorder & zorder) const
{

   if (operator ==(zorder))
   {

      return true;

   }

   return operator <(zorder);

}


zorder & zorder::operator = (oswindow oswindow)
{

   if (oswindow == (::oswindow) HWND_BOTTOM)
   {

      m_ezorder = zorder_bottom;

      m_iZOrder = 0;

   }
   else if (oswindow == (::oswindow)HWND_NOTOPMOST)
   {

      m_ezorder = zorder_no_top_most;

      m_iZOrder = 0;

   }
   else if (oswindow == (::oswindow)HWND_TOP)
   {

      m_ezorder = zorder_top;

      m_iZOrder = 0;

   }
   else if (oswindow == (::oswindow)HWND_TOPMOST)
   {

      m_ezorder = zorder_top_most;

      m_iZOrder = 0;

   }
   else if (::is_window(oswindow))
   {

      m_ezorder = zorder_hwnd;

      m_iZOrder = (iptr)oswindow;

   }
   else
   {

      m_ezorder = zorder_top;

      m_iZOrder = 0;

   }

   return *this;

}

zorder & zorder::operator = (e_zorder ezorder)
{

   if (ezorder == zorder_none)
   {

      m_ezorder = zorder_normal;

      m_iZOrder = 0;

   }
   else if (ezorder == zorder_bottom)
   {

      m_ezorder = zorder_bottom;

      m_iZOrder = 0;

   }
   else if (ezorder == zorder_no_top_most)
   {

      m_ezorder = zorder_no_top_most;

      m_iZOrder = 0;

   }
   else if (ezorder == zorder_top)
   {

      m_ezorder = zorder_top;

      m_iZOrder = 0;

   }
   else if (ezorder == zorder_top_most)
   {

      m_ezorder = zorder_top_most;

      m_iZOrder = 0;

   }
   else
   {

      m_ezorder = zorder_top;

      m_iZOrder = 0;

   }

   return *this;

}


zorder & zorder::operator = (iptr i)
{

   m_ezorder = zorder_normal;

   m_iZOrder = i;

   return *this;

}


zorder & zorder::operator = (const zorder & zorder)
{

   if (this != &zorder)
   {

      m_ezorder = zorder.m_ezorder;

      m_iZOrder = zorder.m_iZOrder;

   }

   return *this;

}
