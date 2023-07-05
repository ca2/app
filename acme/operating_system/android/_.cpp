#include "framework.h"
#include "acme/constant/id.h"


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


CLASS_DECL_ACME void __node_acme_pre_init()
{

}


CLASS_DECL_ACME void __node_acme_pos_init()
{

}


//CLASS_DECL_ACME void __node_term_cross_windows_threading();


CLASS_DECL_ACME void __node_acme_pre_term()
{

   //__node_term_cross_windows_threading();

}


CLASS_DECL_ACME void __node_acme_pos_term()
{

}



CLASS_DECL_ACME int __node_is_debugger_attached()
{

   return false;

}



