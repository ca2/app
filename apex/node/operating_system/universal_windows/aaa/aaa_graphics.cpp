﻿#include "framework.h"


bool os_init_imaging()
{

   return true;

}


void os_term_imaging()
{


}


CLASS_DECL_APEX int_bool window_set_mouse_cursor(oswindow, HCURSOR hcursor)
{

   return false;

}


HCURSOR CreateAlphaCursor(oswindow window, const ::image* pimage, int xHotSpot, int yHotSpot)
{

   return false;

}


HCURSOR load_default_cursor(e_cursor ecursor)
{

   return nullptr;

}


int_bool delete_hcursor(HCURSOR hcursor)
{

   return true;

}


namespace draw2d
{


   string default_font_name()
   {

      return "Arial";

   }


} // namespace draw2d



