#include "framework.h"
#include "number_double.h"


namespace math
{


   void number_double::set_value_string(const char * psz)
   {

   }


   string number_double::get_value_string()
   {
      
      return "";

   }

   
   CLASS_DECL_AQUA bool convert_to_double(double & d, string str)
   {

      str.replace(" ", "");
      
      str.replace("\t", "");

      str.replace("\n", "");

      str.replace("\r", "");

      bool bDouble = false;

      if (str.get_length() >= 1)
      {

         if (ansi_char_is_digit(str[0]))
         {

            bDouble = true;

         }
         else if (str[0] == '-' || str[0] == '+')
         {

            if (str.get_length() >= 2)
            {

               if (ansi_char_is_digit(str[1]))
               {

                  bDouble = true;

               }

            }

         }

      }

      if (!bDouble)
      {

         return false;

      }

      d = atof(str);

      return true;

   }


} // namespace math



