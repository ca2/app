#include "framework.h"
#include "apex/operating_system.h"



CLASS_DECL_AURA bool os_init_imaging()
{



   return true;

}


CLASS_DECL_AURA void os_term_imaging()
{

}



//CLASS_DECL_AURA int_bool context_image::window_set_mouse_cursor(::windowing::window * pwindow, hcursor hcursor)
//{
//
//   if (!::SetCursor(hcursor))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}

//
//int_bool delete_hcursor(hcursor hcursor)
//{
//
//   return ::DestroyCursor(hcursor);
//
//}


namespace draw2d
{




   string default_font_name()
   {

      return "Arial";

   }


} // namespace draw2d


//bool similar_font(const ::string & pszSystem, const ::string &pszUser)
//{
//
//   if (::is_null(pszSystem) || ::is_null(pszUser))
//   {
//
//      return false;
//
//   }
//
//   if (!stricmp(pszSystem, pszUser))
//   {
//
//      return 1.0;
//
//   }
//
//
//}



//bool similar_font(const ::string & pszSystem, const ::string & pszUser)
//{
//
//   if (::is_null(pszSystem) || ::is_null(pszUser))
//   {
//
//      return false;
//
//   }
//
//   if (!stricmp(pszSystem, pszUser))
//   {
//
//      return 1.0;
//
//   }
//
//
//}

CLASS_DECL_AURA char * windows_get_system_cursor(enum_cursor ecursor);


