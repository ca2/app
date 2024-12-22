#include "framework.h"


void quantum::set_finishing_flag()
{
   
   set_flag(e_flag_finishing);

   ::string strType(typeid(*this).name());

   if (strType.contains("user::thread"))
   {

      output_debug_string("quantum::set_finishing_flag user::thread");

   }
   else if (strType.contains("main_frame"))
   {

      output_debug_string("quantum::set_finishing_flag main_frame");

   }

}


void quantum::set_destroying_flag()
{
   
   set_flag(e_flag_destroying);

}



