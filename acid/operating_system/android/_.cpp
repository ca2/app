#include "framework.h"
#include "acid/constant/id.h"


class ::time os_get_system_update_poll_time(const ::atom& atom)
{

   if (atom == id_operating_system_user_theme_change)
   {

      return zero_t{};

   }
   else if (atom == id_operating_system_user_color_change)
   {

      return zero_t{};

   }
   //else if (atom == id_operating_system_font_change)
   //{

   //   return zero_t{};

   //}
   //else if (atom == id_operating_system_font_enumeration)
   //{

   //   return zero_t{};

   //}

   return zero_t{};

}


CLASS_DECL_ACID void __node_ace_pre_init()
{

}


CLASS_DECL_ACID void __node_ace_pos_init()
{

}


//CLASS_DECL_ACID void __node_term_cross_windows_threading();


CLASS_DECL_ACID void __node_ace_pre_term()
{

   //__node_term_cross_windows_threading();

}


CLASS_DECL_ACID void __node_ace_pos_term()
{

}



CLASS_DECL_ACID int __node_is_debugger_attached()
{

   return false;

}



