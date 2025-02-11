//
// Created by camilo on 2024-10-04 07:29 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace x11
{


   struct display_t
   {


   };


   using window_t = long long;


   struct visual_t
   {


   };


   struct handle_t
   {


      ::x11::display_t *      m_pdisplay;
      ::x11::window_t         m_window;
      ::x11::visual_t *       m_pvisual;


   };


   struct event_t
   {


   };


} // namespace x11



