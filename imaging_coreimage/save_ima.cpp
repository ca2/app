#include "framework.h"


int os_window_set_mouse_cursor(void *, void * p);


namespace coreimage_imaging
{


   context_image::context_image()
   {

   }


   context_image::~context_image()
   {

   }

   WINBOOL context_image::window_set_mouse_cursor(oswindow window, HCURSOR hcursor)
   {

      return os_window_set_mouse_cursor(window, hcursor);

   }


} // namespace coreimage_imaging




