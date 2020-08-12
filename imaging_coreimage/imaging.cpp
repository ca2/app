#include "framework.h"


int os_window_set_mouse_cursor(void *, void * p);


namespace coreimage_imaging
{


   imaging::imaging()
   {

   }


   imaging::~imaging()
   {

   }

   WINBOOL imaging::window_set_mouse_cursor(oswindow window, HCURSOR hcursor)
   {

      return os_window_set_mouse_cursor(window, hcursor);

   }


} // namespace coreimage_imaging




