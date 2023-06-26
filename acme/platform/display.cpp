#include "framework.h"
// #include "acme/primitive/string/string.h"
//#include "acme/operating_system.h"


CLASS_DECL_ACME enum_display equivalence_sink(enum_display edisplay)
{

   if (edisplay == e_display_normal
      || edisplay == e_display_compact
      || edisplay == e_display_broad)
   {

      return e_display_normal;

   }

   return edisplay;

}


//CLASS_DECL_ACME string as_string(enum_display edisplay)
//{
//
//   if(is_docking_appearance(edisplay))
//   {
//
//      string str;
//
//      if(edisplay & e_display_left)
//      {
//
//         str += "left;";
//
//      }
//
//      if(edisplay & e_display_top)
//      {
//
//         str += "top;";
//
//      }
//
//      if(edisplay & e_display_right)
//      {
//
//         str += "right;";
//
//      }
//
//      if(edisplay & e_display_bottom)
//      {
//
//         str += "bottom;";
//
//      }
//
//      return str;
//
//   }
//
//   switch (edisplay)
//   {
//   case e_display_default:
//      return "default";
//   case e_display_normal:
//      return "normal";
//   case e_display_broad:
//      return "broad";
//   case e_display_compact:
//      return "compact";
//   case e_display_stored_state:
//      return "stored_state";
//   case e_display_iconic:
//      return "iconic";
//   case e_display_zoomed:
//      return "zoomed";
//   case e_display_full_screen:
//      return "full_screen";
//   default:
//      return "(not stringfied)";
//   };
//
//}


string as_string(const ::e_display & edisplay) 
{
   
   return as_string((::enum_display)edisplay); 

}



