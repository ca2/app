#include "framework.h"
#include "acme/primitive/geometry2d/_geometry2d.h"


bool os_init_imaging()
{

   return true;

}


void os_term_imaging()
{


}



namespace draw2d
{


   string default_font_name()
   {

      return "Arial";

   }


} // namespace draw2d


CLASS_DECL_AURA ::size_i32 winrt_get_big_back_buffer_size()
{

   return ::size_i32(1920, 1080);

}



