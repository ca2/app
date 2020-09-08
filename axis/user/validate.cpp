#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "axis/user/_user.h"
#endif
#include "validate.h"

namespace user
{


   validate::validate()
   {


   }


   validate::~validate()
   {

   }


   ::estatus validate::Validate(string& strParam, ::user::control_descriptor* pdescriptor)
   {

      switch (control_descriptor().get_data_type())
      {
      case control_data_type_string:
         return true;
      case control_data_type_natural:
      {
         string str = strParam;
         str.trim_left();
         str.trim_right();
         for (i32 i = 0; i < str.get_length(); i++)
         {
            if (str[i] >= L'0'
               && str[i] <= L'9')
            {
            }
            else
            {
               return false;
            }

         }
         return true;
      }
      break;
      default:
         return true;
      }
   }


} // namespace user



