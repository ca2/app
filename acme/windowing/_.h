//
// Created by camilo on 2022-10-24 08:45 <3ThomasBorregaardSorensen!!
//
//
// Created by camilo on 2024-09-26 00:32 <3ThomasBorregaardSorensen!!
// // Merged from (acme)windowing and (acme)windowing_system by
// //   camilo on 2024-10-05 11:01 <3ThomasBorregaardSorensen!!
// //   (acme)windowing_system::windowing_system
// //       ---->windowing::windowing_base
// // //       ---->micro::user
// //   (acme)windowing::window_base
// //       ---->micro::interchange
//
//
// (windowing_system) Created by 
//    camilo on 2024-05-26 22:45 <3ThomasBorregaardSorensen!!
// Merged from windowing_system to
//     windowing by camilo on 2024-10-05 10:35 <3ThomasBorregaardSorensen!!
//

#pragma once


#include "acme/platform/reference_referer.h"
#include "acme/constant/windowing.h"


namespace acme
{

   namespace windowing
   {

      //class user;


      ////class device;
      //class child;

      class display;

      class window;

      class windowing;

      //class theme;

      ////class window_implementation;


      ////class icon;
      //class button;
      //class still;

      //class display;

      //// class brush;
      //// class pen;
      //// class font;
      ////
      ////
      ////
      ////    CLASS_DECL_ACME ::pointer<brush>create_solid_brush(::particle * pparticle, color32_t color);
      ////    CLASS_DECL_ACME ::pointer<font>create_point_font(::particle * pparticle, int iPoint, enum_font efont, bool bBold = false);
      ////    CLASS_DECL_ACME ::pointer<pen>create_pen(::particle * pparticle, int iWidth, color32_t color);


   } //namespace windowing


} // namespace acme


namespace windowing
{

   
   class window_base;


   class windowing;


   //CLASS_DECL_ACME::enum_display_type get_display_type();


   //CLASS_DECL_ACME::windowing::enum_windowing calculate_ewindowing();
   //CLASS_DECL_ACME::windowing::enum_windowing get_ewindowing();


   CLASS_DECL_ACME::windowing::enum_desktop calculate_edesktop();
   CLASS_DECL_ACME::windowing::enum_desktop get_edesktop();


   CLASS_DECL_ACME::windowing::enum_toolkit calculate_etoolkit();
   CLASS_DECL_ACME::windowing::enum_toolkit get_etoolkit();


   CLASS_DECL_ACME::windowing::enum_display_type initialize_edisplaytype();
   CLASS_DECL_ACME::windowing::enum_display_type get_edisplaytype();


} // namespace windowing



