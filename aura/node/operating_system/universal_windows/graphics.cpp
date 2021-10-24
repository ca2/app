#include "framework.h"


bool os_init_imaging()
{

   return true;

}


void os_term_imaging()
{


}


//CLASS_DECL_AURA int_bool window_set_mouse_cursor(oswindow, HCURSOR hcursor)
//{
//
//   return false;
//
//}
//
//
//HCURSOR CreateAlphaCursor(oswindow window, const ::image* pimage, int xHotSpot, int yHotSpot)
//{
//
//   return false;
//
//}
//
//
//HCURSOR load_default_cursor(e_cursor ecursor)
//{
//
//   return nullptr;
//
//}
//
//
//int_bool delete_hcursor(HCURSOR hcursor)
//{
//
//   return true;
//
//}
//

namespace draw2d
{


   string default_font_name()
   {

      return "Arial";

   }


   //void draw2d::enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema)
   //{


   //}

} // namespace draw2d


CLASS_DECL_AURA ::size_i32 winrt_get_big_back_buffer_size()
{

   return ::size_i32(1920, 1080);

}



