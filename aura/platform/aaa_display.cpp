#include "framework.h"


CLASS_DECL_AURA e_display equivalence_sink(e_display edisplay)
{

   if (edisplay == display_restore
      || edisplay == display_compact
      || edisplay == display_broad)
   {

      return display_normal;

   }

   return edisplay;

}


CLASS_DECL_AURA int windows_show_window(e_display edisplay, e_activation eactivation)
{

   auto bNoActivate = eactivation & activation_no_activate;

   switch (edisplay)
   {
   case display_default:
      return SW_SHOWDEFAULT;
   case display_normal:
      if (bNoActivate)
         return SW_SHOWNA;
      else
         return SW_NORMAL;
   case display_iconic:
      if (bNoActivate)
         return SW_SHOWMINNOACTIVE;
      else
         return SW_MINIMIZE;
   case display_zoomed:
      return SW_MAXIMIZE;

   case display_full_screen:
      return SW_NORMAL;
   default:
      if (edisplay <= 0)
         return SW_HIDE;
      else
         return SW_NORMAL;
   };

}



CLASS_DECL_AURA e_display windows_show_window_to_edisplay(int iShowWindow, e_activation & eactivation)
{

   eactivation = activation_none;

   if (iShowWindow <= SW_HIDE)
   {

      return display_none;

   }

   switch (iShowWindow)
   {
   case SW_SHOWDEFAULT:
      return display_default;
   case SW_SHOW:
      return display_normal;
   case SW_RESTORE:
      return display_normal;
   case SW_MINIMIZE:
      return display_iconic;
   case SW_MAXIMIZE:
      return display_zoomed;
   case SW_SHOWNA:
      eactivation = activation_no_activate;
      return display_normal;
   case SW_SHOWMINNOACTIVE:
      eactivation = activation_no_activate;
      return display_iconic;
   default:
         return display_normal;
   }

}






CLASS_DECL_AURA string __str(e_display edisplay)
{

   if(is_docking_appearance(edisplay))
   {

      string str;

      if(edisplay & display_left)
      {

         str += "left;";

      }

      if(edisplay & display_top)
      {

         str += "top;";

      }

      if(edisplay & display_right)
      {

         str += "right;";

      }

      if(edisplay & display_bottom)
      {

         str += "bottom;";

      }

      return str;

   }

   switch (edisplay)
   {
   case display_default:
      return "default";
   case display_normal:
      return "normal";
   case display_iconic:
      return "iconic";
   case display_zoomed:
      return "zoomed";
   case display_full_screen:
      return "full_screen";
   default:
      return "(not stringfied)";
   };

}
