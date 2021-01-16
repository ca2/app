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


   ::e_status validate::Validate(string& strParam, ::user::interaction * pinteraction)
   {

      switch (pinteraction->get_data_type())
      {
      case e_control_data_type_string:
         return true;
      case e_control_data_type_natural:
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



