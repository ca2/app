// Created by camilo on 2021-01-22 06:11 AM <3ThomasBorregaardSorensen
#include "framework.h"
#include "drag.h"
#include "drag_client.h"
#include "acme/user/user/mouse.h"


namespace user
{


   drag::drag()
   {

      //m_eelement = e_element_none;
      

      m_ecursor = e_cursor_none;

      m_bDrag = false;

      m_bLButtonDown = false;

      m_pmouse = nullptr;

   }


   drag::~drag()
   {


   }


   void drag::drag_start(::user::mouse * pmouse, ::user::drag_client* pdragclient, ::item * pitem, const ::point_i32 & pointDrag)
   {

      m_pmouse = pmouse;

      m_bLButtonDown = true;

      m_bDrag = false;

      m_pointLButtonDown2 = pdragclient->drag_mouse_cursor_position(pitem, pmouse->m_pointAbsolute);
      
      m_pointInitial = pointDrag;

      //m_sizeLButtonDownOffset = m_pointLButtonDown - pointDrag;

   }


   void drag::drag_end()
   {

      m_bLButtonDown = false;

      m_bDrag = false;

      m_pmouse.release();

   }


   

} // namespace user



