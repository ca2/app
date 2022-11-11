//
// Created by camilo on 12/11/2020.
//
#include "framework.h"
#include "acme/primitive/string/string.h"
#include "acme/primitive/string/hex.h"



CLASS_DECL_ACME ::e_status worst(enum_status e1, enum_status e2)
{

   // heuristic/simple/easy implementation

   return (::e_status)minimum((::i64)e1, (::i64)e2);

}


CLASS_DECL_ACME ::e_status operator & (enum_status e1, enum_status e2)
{

   return worst(e1, e2);

}


CLASS_DECL_ACME int _status_exit_code(enum_status estatus)
{

   
   if (succeeded(estatus))
   {

      return 0;

   }

#ifdef WINDOWS
   
   return -(i32)estatus;

#else

   if (estatus >= -125)
   {

      return -(int)(estatus);

   }
   else
   {

      return 125;

   }

#endif

}







CLASS_DECL_ACME ::string __string(const ::e_status & estatus)
{

   string str = "estatus=";

   if(estatus == success)
   {

      str += "success";

   }
   else if(::succeeded(estatus))
   {

      str += "\"succeeded status=" + ::hex::lower_from(estatus) + "...\"";

   }
   else if(estatus == error_not_implemented)
   {

      str += "error_not_implemented";

   }
   else if(estatus == error_no_factory)
   {

      str += "error_no_factory";

   }
   else if (estatus == error_file_not_found)
   {

      str += "error_file_not_found";

   }
   else if (estatus == error_bad_path)
   {

      str += "error_bad_path";

   }
   else if (estatus == error_library_not_found)
   {

      str += "error_library_not_found";

   }
   else if(estatus == error_failed)
   {

      str += "error_failed";

   }
   else if (estatus == error_already_exists)
   {

      str += "error_already_exists";

   }
   else if (estatus == error_wrong_state)
   {

      str += "error_wrong_state";

   }
   else if(failed(estatus))
   {

      str += "\"failed status=" + ::hex::lower_from(estatus) + "...\"";

   }

   return str;

}



