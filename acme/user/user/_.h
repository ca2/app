#pragma once


#include  "_constant.h"


#include  "_style.h"


class item;

struct os_theme_colors;


namespace user
{


   class user;


   class acme_content;
   class acme_tool;



   DECLARE_ENUMERATION(e_state, enum_state);
   CLASS_DECL_ACME string get_wallpaper(::collection::index iIndex);


   class controller;
   class control;
   class property;
   class check;
   class text;

   class impact_system;

   //class interaction_base;


} // namespace user


namespace windowing
{


   class cursor;


} // namespace windowing


#include "acme/constant/button_state.h"

//class property_container;


namespace user
{


    DECLARE_ENUMERATION(e_button_state, enum_button_state);


    //using item_pointer = ::pointer < ::user::item >;


} // namespace user


//#include "mouse.h"


//#include "os_colors.h"
//#include "theme_colors.h"

//#include "drag.h"

namespace experience
{


   enum enum_frame
   {

      e_frame_none = 0,
      e_frame_sizing_left = 1,
      e_frame_sizing_top = 2,
      e_frame_sizing_right = 4,
      e_frame_sizing_bottom = 8,
      e_frame_sizing_top_left = e_frame_sizing_top | e_frame_sizing_left,
      e_frame_sizing_top_right = e_frame_sizing_top | e_frame_sizing_right,
      e_frame_sizing_bottom_left = e_frame_sizing_bottom | e_frame_sizing_left,
      e_frame_sizing_bottom_right = e_frame_sizing_bottom | e_frame_sizing_right,
      e_frame_client = 16,
      e_frame_title_bar = 32,
//      e_frame_move = 32,

   };


} // namespace experience


