#include "framework.h"


void quantum::set_finishing_flag()
{
   set_flag(e_flag_finishing);

   ::string strType(typeid(*this).name());

   if (strType.contains("user::thread"))
   {

      output_debug_string("123");

   }

}


void quantum::set_destroying_flag()
{
   set_flag(e_flag_destroying);
}
