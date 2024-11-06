#include "framework.h"
#include "validate.h"
////#include "acme/exception/exception.h"
#include "aura/user/user/interaction.h"


namespace user
{


   validate::validate()
   {


   }


   validate::~validate()
   {

   }


   void validate::Validate(string& strParam, ::user::interaction * pinteraction)
   {

      switch (pinteraction->get_data_type())
      {
      case e_control_data_type_string:
         return;
      case e_control_data_type_natural:
      {
         string str = strParam;
         str.trim_left();
         str.trim_right();
         for (int i = 0; i < str.length(); i++)
         {
            if (str[i] >= L'0'
               && str[i] <= L'9')
            {
            }
            else
            {
               throw ::exception(error_failed);
            }

         }
         //return true;
      }
      break;
      default:;
         //return true;
      }
   }


} // namespace user



