//
// Created by camilo on 01/01/2021. 6:52 BRT <3Tbs, Mummi and bilbo!!
//
// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#pragma once


namespace sandbox_windowing
{


   class window;
   class windowing;


} // namespace sandbox_windowing


namespace windowing
{


   class display;
   class window;
   class windowing;
   class text_editor_interface;


   enum enum_status
   {

      e_status_none = 0,
      e_status_checked = 1 << 0,
      e_status_disabled = 1 << 1,
      e_status_set_checked = 1 << 8,
      e_status_set_disabled = 1 << 9,


   };

   DECLARE_ENUMERATION(e_status, enum_status);

} // namespace windowing



