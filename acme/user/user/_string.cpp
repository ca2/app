//
// Created by camilo on 25/06/23.
//
#include "framework.h"
#include "_string.h"


CLASS_DECL_ACME ::string as_string(::enum_display edisplay)
{

   switch(edisplay)
   {
      case e_display_undefined:
         return "e_display_undefined";
      case e_display_notify_icon:
         return "e_display_notify_icon";
      case e_display_hide:
         return "e_display_hide";
      case e_display_none:
         return "e_display_none";
      case e_display_normal:
         return "e_display_normal";
      case e_display_compact:
         return "e_display_compact";
      case e_display_broad:
         return "e_display_broad";
      case e_display_iconic:
         return "e_display_iconic";
      case e_display_zoomed:
         return "e_display_zoomed";
      case e_display_full_screen:
         return "e_display_full_screen";
      case e_display_up:
         return "e_display_up";
      case e_display_down:
         return "e_display_down";
      case e_display_minimal:
         return "e_display_minimal";
      case e_display_left:
         return "e_display_left";
      case e_display_top:
         return "e_display_top";
      case e_display_right:
         return "e_display_right";
      case e_display_bottom:
         return "e_display_bottom";
      case e_display_top_left:
         return "e_display_top_left";
      case e_display_top_right:
         return "e_display_top_right";
      case e_display_bottom_left:
         return "e_display_bottom_left";
      case e_display_bottom_right:
         return "e_display_bottom_right";
      case e_display_full_left:
         return "e_display_full_left";
      case e_display_full_top:
         return "e_display_full_top";
      case e_display_full_right:
         return "e_display_full_right";
      case e_display_full_bottom:
         return "e_display_full_bottom";
      case e_display_docking_mask:
         return "e_display_docking_mask";
      case e_display_default:
         return "e_display_default";
      case e_display_current:
         return "e_display_current";
      case e_display_stored_state:
         return "e_display_stored_state";
      case e_display_fixed_size:
         return "e_display_fixed_size";
      case e_display_center:
         return "e_display_center";
      case e_display_last_command:
         return "e_display_last_command";
      default:
      {
         ::string str;
         str.formatf("unknown e_display %d", (iptr) edisplay);
         return str;
      }

   }


}


CLASS_DECL_ACME ::string as_string(::user::enum_activation useractivation)
{

   if(useractivation == ::user::e_activation_default)
   {

   return "::user::e_activation_default";
}
   ::string str;
   if(useractivation & ::user::e_activation_no_activate)
   {
      str += "no_activate;";
   }
   if(useractivation & ::user::e_activation_set_active)
   {
      str += "set_active;";
   }
   if(useractivation & ::user::e_activation_set_foreground)
   {
      str += "set_foreground;";
   }
   if(useractivation & ::user::e_activation_under_mouse_cursor)
   {
      str += "under_mouse_cursor;";
   }
   if(useractivation & ::user::e_activation_on_center_of_screen)
   {
      str += "on_center_of_screen;";
   }
   if(useractivation & ::user::e_activation_display_change)
   {
      str += "display_change;";
   }
   if(str.is_empty())
   {
      str.formatf("unknown e_display %d", (iptr) useractivation);
   }
   else
   {
      str = "e_activation:" + str;
   }

   return str;


}



#undef DO
#define DO(e) MAKE_STRING(e)

const_char_pointer g_pszaEnumCursor[]= {
   DO(e_cursor_unmodified),
   DO(e_cursor_draw2d),
   DO(e_cursor_default),
   DO(e_cursor_none),
   DO(e_cursor_system),
   DO(e_cursor_arrow),
   DO(e_cursor_hand),
   DO(e_cursor_text_select),
   DO(e_cursor_size_top_left),
   DO(e_cursor_size_top),
   DO(e_cursor_size_top_right),
   DO(e_cursor_size_right),
   DO(e_cursor_size_bottom_right),
   DO(e_cursor_size_bottom),
   DO(e_cursor_size_bottom_left),
   DO(e_cursor_size_left),
   DO(e_cursor_size_vertical),
   DO(e_cursor_size_horizontal),
   DO(e_cursor_move),
   DO(e_cursor_wait),
   DO(e_cursor_wait_arrow)
};


CLASS_DECL_ACME ::string as_string(enum_cursor ecursor)
{
   if(ecursor <e_cursor_unmodified || ecursor > e_cursor_wait_arrow)
      return {};
   return g_pszaEnumCursor[ecursor];

}


#undef DO
////
////
////template < typename FILE, primitive_rectangle RECTANGLE >
////inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const RECTANGLE & rectangle)
////{
////
////   return textstream << "xy(" << rectangle.left  << ", " << rectangle.top << ")-wh(" << rectangle.width() << ", " << rectangle.height() << ")";
////
////}





