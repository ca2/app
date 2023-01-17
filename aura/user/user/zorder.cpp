// From layout_state.cpp by camilo on 2022-08-27 12:24 <3ThomasBorregaardSørensen!! MyHusband!!
// ... elsker mig as Jeg elsker dig?!
#include "framework.h"
#include "zorder.h"


zorder::zorder()
{

   m_ezorder = e_zorder_top;

   m_iZOrder = 0;

}

zorder::zorder(const zorder & zorder)
{

   operator = (zorder);

}

zorder::zorder(enum_zorder ezorder)
{

   operator = (ezorder);

}


zorder::zorder(iptr iZ)
{

   operator = (iZ);

}


//zorder::zorder(::windowing::window * pwindow)
//{
//
//   operator = (oswindow);
//
//}


bool zorder::is_stable() const
{

   return
      m_ezorder == e_zorder_none
      || m_ezorder == e_zorder_normal_anchor
      || m_ezorder == e_zorder_top_most_anchor;

}


void zorder::clear_request()
{

   if (m_ezorder == e_zorder_top_most || m_ezorder == e_zorder_top_most_anchor)
   {

      m_ezorder = e_zorder_top_most_anchor;

   }
   else
   {

      m_ezorder = e_zorder_normal_anchor;

   }

}


void zorder::set_request()
{

   if (m_ezorder == e_zorder_top_most || m_ezorder == e_zorder_top_most_anchor)
   {

      m_ezorder = e_zorder_top_most;

   }
   else
   {

      m_ezorder = e_zorder_normal;

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



zorder::operator oswindow() const
{

   //return get_os_data();
   return nullptr;

}


bool zorder::is_set() const
{

   return m_ezorder != e_zorder_none;

}


bool zorder::operator != (const zorder & zorder) const
{

   return !operator ==(zorder);

}

int zorder::get_sort_ezorder() const
{

   if (m_ezorder == e_zorder_normal_anchor)
   {

      return e_zorder_normal;

   }
   else if (m_ezorder == e_zorder_top_most_anchor)
   {

      return e_zorder_top_most;

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



zorder & zorder::operator = (enum_zorder ezorder)
{

   if (ezorder == e_zorder_none)
   {

      m_ezorder = e_zorder_normal;

      m_iZOrder = 0;

   }
   else if (ezorder == e_zorder_bottom)
   {

      m_ezorder = e_zorder_bottom;

      m_iZOrder = 0;

   }
   else if (ezorder == e_zorder_no_top_most)
   {

      m_ezorder = e_zorder_no_top_most;

      m_iZOrder = 0;

   }
   else if (ezorder == e_zorder_top)
   {

      m_ezorder = e_zorder_top;

      m_iZOrder = 0;

   }
   else if (ezorder == e_zorder_top_most)
   {

      m_ezorder = e_zorder_top_most;

      m_iZOrder = 0;

   }
   else
   {

      m_ezorder = e_zorder_top;

      m_iZOrder = 0;

   }

   return *this;

}


zorder & zorder::operator = (iptr i)
{

   m_ezorder = e_zorder_normal;

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



