#pragma once


#include  "apex/_.h"


#include "_constant.h"


#include "acme/primitive/geometry2d/rectangle.h"


CLASS_DECL_ACME ::critical_section * children_critical_section();


namespace aura
{


   class draw_context;


} // namespace aura


namespace appearance
{


   class appearance;


} // namespace appearance


namespace windowing
{


   class windowing;
   class display;
   class icon;


} // namespace windowing



namespace user
{


   class interaction;

   class interaction_impl;

   class interaction_scaler;

   class interaction_listener;

   class style;

   class alpha_source;

   class button;

   class check_box;

   class still;

   class plain_edit;

   class message;

   class frame;

   class frame_window;

   class tool_window;

   class control_bar;

   class toolbar;

   class scroll_info;

   class scroll_bar;

   class scroll_data;

   class split_layout;

   class notify_icon;

   class primitive_pointer_array;

   class shell;

   class text_composition_client_base;
   class text_composition_client;
   class text_composition_composite;


   class progress;


   CLASS_DECL_AURA bool is_descendant(::user::interaction * puiParent, ::user::interaction * puiChild);


   //class form;
   class tooltip;


   class calc_size;

   class copydesk;
   //class system;
   class control_event;
   //class control_descriptor;
   class interaction_child;
   class interaction_impl;
   class interaction_array;


   class interaction_ptra;


   //class place_holder;
   //class tab;
   //class tab_pane;
   //class check_box;
   //class menu_interaction;
   //class menu_button;
   //class menu_item;
   //class menu_item_ptra;
   //class frame_window;
   class toolbar;
   class scroll_bar;
   class split_layout;
   class style;
   class scroll_info;
   //class window_map;
   //class system_interaction;


   //class place_holder;

   //#if defined UNIVERSAL_WINDOWS
   //
   //   class CLASS_DECL_AURA native_window_initialize
   //   {
   //   public:
   //
   //
   //      Agile < ::winrt::Windows::UI::Core::CoreWindow >         m_window;
   //      ::aura::system_window ^                         m_pwindow;
   //
   //
   //   };
   //
   //#elif defined(APPLE_IOS) || defined(ANDROID)
#if defined(APPLE_IOS) || defined(ANDROID)

   class CLASS_DECL_AURA native_window_initialize
   {
   public:

      ::rectangle_i32   m_rectangle;

   };

#else

   class native_window_initialize;

#endif


   class control_bar;


   class control_event;
   //class frame_window;

   class notify_icon;

   CLASS_DECL_AURA ::user::interaction_impl * message_interaction_impl(::user::message * pusermessage);

   CLASS_DECL_AURA ::user::interaction * message_user_interaction(::user::message * pusermessage);


} // namespace user


class prodevian;


namespace experience
{

   class updown;

} // namespace experience

//#include "control_event_listener.h"
namespace message
{


   class key;
   class drag_and_drop;
   class mouse_base;


} // namespace message


//#include "aura/graphics/user/control_box_button.h"
//#include "aura/graphics/user/control_box_icon.h"


//#include "aura/platform/drawable.h"
//#include "aura/user/user/layout_state.h"
//#include "aura/user/callback.h"


//#include "aura/user/user/style_control.h"
//
//
//#include "aura/user/user/style_base.h"
//#include "aura/user/user/style.h"


class zorder;


class form_document;


namespace user
{



   //class interaction_impl;
//class frame_window;
   class mdi_child_window;
   //class control_bar;


   


   class user;
   class interaction_array;
   class keyboard;
   class copydesk;
   class main_frame;
   class plain_edit;


   class system;


   class plain_text_set_sel_command;
   class plain_text_tree;
   class plain_text_command;
   class tree_draw_item;
   class interaction_child;
   class box;
   class control_style;
   class plain_edit_style;
   //class plain_edit_style;
   class form_callback;
   class impact;
   class key;
   class thread;

   namespace rich_text
   {


      class edit_impl;


   } // namespace rich_text


   //class menu_item_ptra;
   //class menu_item;
   //class menu_item_ptra;
   class front_end;
   //class menu_item;

   //class list_column_array;

      //class list_header;
   class scroll_bar;
   //class list_column_array;

   namespace rich_text
   {


      class edit;
      class data;


   }  // namespace rich_text


} // namespace user



namespace user
{
   
}



struct __SIZEPARENTPARAMS;


#if defined(LINUX) || defined(FREEBSD)
typedef struct _AppIndicator AppIndicator;
#endif

namespace user
{

   class shell;

} // namespace user


namespace user
{


   class user;


} // namespace user



namespace userex
{


   class color_impact;


} // namespace userex


class cregexp;
//
//namespace database
//{
//
//   class selection;
//
//} // namespace database

class image_list;
//class simple_list_data;

CLASS_DECL_AURA ::user::primitive* __user_primitive(::windowing::window * pwindow);

inline wparam __scroll_message_wparam(enum_scroll_command ecommand, int iPosition)
{

   return ((((int)ecommand) & 0xffff) | ((iPosition << 16) & 0xffff0000));

}



//#include "system.h"
//
//#include "acme/constant/button_state.h"
//
////#include "mouse.h"
//
//#include "aura/user/user/message.h"
//
//#include "windowing.h"
//
//#include "key.h"
//
//#include "acme/constant/activate.h"
//
//#include "aura/message/user.h"
//
//
//#include "range.h"
//
//
//#include "aura/user/user/interaction.h"
//
//
//#include "aura/user/user/button.h"
//
//
////#include "message_window_listener.h"






struct __SIZEPARENTPARAMS;    // control bar implementationproperca2_property.h

// Classes declared in this file

//::draw2d::graphics_pointer
class thumbnail_dc;               // Virtual DC for print thumbnail

class mini_dock_frame_window;


CLASS_DECL_AURA ::user::e_mouse user_key_to_user_mouse(::user::e_key ekeyButton);


struct size_parent_layout;



