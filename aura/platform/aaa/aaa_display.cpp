#include "framework.h"


CLASS_DECL_AURA enum_display equivalence_sink(enum_display edisplay)
{

   if (edisplay == e_display_restore
      || edisplay == e_display_compact
      || edisplay == e_display_broad)
   {

      return e_display_normal;

   }

   return edisplay;

}


CLASS_DECL_AURA int windows_show_window(enum_display edisplay, enum_activation eactivation)
{

   auto bNoActivate = eactivation & e_activation_no_activate;

   switch (edisplay)
   {
   case e_display_default:
      return SW_SHOWDEFAULT;
   case e_display_normal:
      if (bNoActivate)
         return SW_SHOWNA;
      else
         return SW_NORMAL;
   case e_display_iconic:
      if (bNoActivate)
         return SW_SHOWMINNOACTIVE;
      else
         return SW_MINIMIZE;
   case e_display_zoomed:
      return SW_MAXIMIZE;

   case e_display_full_screen:
      return SW_NORMAL;
   default:
      if (edisplay <= 0)
         return SW_HIDE;
      else
         return SW_NORMAL;
   };

}



CLASS_DECL_AURA enum_display windows_show_window_to_edisplay(int iShowWindow, enum_activation & eactivation)
{

   eactivation = e_activation_default;

   if (iShowWindow <= SW_HIDE)
   {

      return e_display_none;

   }

   switch (iShowWindow)
   {
   case SW_SHOWDEFAULT:
      return e_display_default;
   case SW_SHOW:
      return e_display_normal;
   case SW_RESTORE:
      return e_display_normal;
   case SW_MINIMIZE:
      return e_display_iconic;
   case SW_MAXIMIZE:
      return e_display_zoomed;
   case SW_SHOWNA:
      eactivation = e_activation_no_activate;
      return e_display_normal;
   case SW_SHOWMINNOACTIVE:
      eactivation = e_activation_no_activate;
      return e_display_iconic;
   default:
         return e_display_normal;
   }

}






CLASS_DECL_AURA string as_string(enum_display edisplay)
{

   if(is_docking_appearance(edisplay))
   {

      string str;

      if(edisplay & e_display_left)
      {

         str += "left;";

      }

      if(edisplay & e_display_top)
      {

         str += "top;";

      }

      if(edisplay & e_display_right)
      {

         str += "right;";

      }

      if(edisplay & e_display_bottom)
      {

         str += "bottom;";

      }

      return str;

   }

   switch (edisplay)
   {
   case e_display_default:
      return "default";
   case e_display_normal:
      return "normal";
   case e_display_iconic:
      return "iconic";
   case e_display_zoomed:
      return "zoomed";
   case e_display_full_screen:
      return "full_screen";
   default:
      return "(not stringfied)";
   };

}
