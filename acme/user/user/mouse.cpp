// Created by camilo on 2023-06-14 01:51 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "mouse.h"


namespace user
{


   ::user::mouse & mouse::operator = (const ::user::mouse & mouse)
   {

      if (this != &mouse)
      {

         ::particle::operator = (mouse);

         m_ebuttonstate          = mouse.m_ebuttonstate;
         m_pointHost             = mouse.m_pointHost;
         m_pointAbsolute         = mouse.m_pointAbsolute;
         m_pointDesired          = mouse.m_pointDesired;
         m_pwindowingcursor      = mouse.m_pwindowingcursor;
         m_puserinteractionHit   = mouse.m_puserinteractionHit;

      }

      return *this;

   }


   //void mouse::initialize_mouse_cursor(::windowing::cursor* pcursor)
   //{

   //   m_pcursor = pcursor;

   //   ::information() << "mouse::initialize_mouse_cursor : " << pcursor->m_ecursor;

   //}


   //void mouse::aaa_set_mouse_cursor(::windowing::cursor* pcursor)
   //{

   //   m_pcursor = pcursor;

   //   ::information() << "mouse::aaa_set_mouse_cursor : " << pcursor->m_ecursor;

   //}


   //::windowing::cursor* mouse::get_mouse_cursor()
   //{

   //   return m_pcursor;

   //}



} // namespace user



