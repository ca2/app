// Created by camilo on 2021-01-22 06:11 AM <3ThomasBorregaardSørensen
#include "framework.h"
#include "acme/user/user/mouse.h"
//#include "acme/handler/item.h"
#include "drag.h"


namespace user
{


   drag::drag()
   {

      m_eelement = e_element_none;

      m_ecursor = e_cursor_none;

      m_bDrag = false;

      m_bLButtonDown = false;

      m_pmouse = nullptr;

   }


   drag::~drag()
   {


   }


   void drag::start(::user::mouse * pmouse, const ::point_i32 & pointDrag)
   {

      m_pmouse = pmouse;

      m_bLButtonDown = true;

      m_bDrag = false;

      m_pointLButtonDown = m_pmouse->m_point;

      m_sizeLButtonDownOffset = m_pointLButtonDown - pointDrag;

   }


   void drag::end()
   {

      m_bLButtonDown = false;

      m_bDrag = false;

      m_pmouse.release();

   }


   ::point_i32 drag::point() const
   {

      auto pointDrag = m_pmouse->m_point - m_sizeLButtonDownOffset;

      return pointDrag;

   }


} // namespace user



