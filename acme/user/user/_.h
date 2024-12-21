#pragma once


#include  "_constant.h"


#include  "_style.h"
#include "acme/constant/_constant.h"


class item;

struct os_theme_colors;


namespace user
{


   class activation_token;


   class user;





   class acme_content;
   class acme_tool;

   class system;

   DECLARE_ENUMERATION(e_state, enum_state);
   CLASS_DECL_ACME string get_wallpaper(::collection::index iIndex);


   class controller;
   class control;
   class property;
   class check;
   class text;

   class impact_system;

   class interaction_base;

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

   class thread;
   class graphics_thread;

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





namespace acme
{

   namespace user
   {

      //class user;


      //class device;
      //class child;


      class interaction;


   }// namespace user


} // namespace acme



namespace user
{

class main_frame;

}



class form_document;


CLASS_DECL_ACME bool is_docking(enum_display edisplay);


CLASS_DECL_ACME enum_display default_equivalence_sink(enum_display edisplay);



