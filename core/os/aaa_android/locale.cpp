#include "framework.h"

//thread_pointer < lconv > t_plconv;

//extern "C"
//{

#if 0

   struct lconv *localeconv(void)
   {

      lconv * plconv = (lconv *) get_task()->value("localeconv").iptr();

      if(plconv == nullptr)
      {

         plconv = new lconv;

         plconv->decimal_point = ".";

         get_task()->value("localeconv") = (iptr)plconv;

      }

      return plconv;

   }

#endif

//} // extern "C"











