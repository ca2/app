#include "framework.h"
#include "number_double.h"


namespace mathematics
{


   void number_double::set_value_string(const ::scoped_string & scopedstr)
   {

   }


   string number_double::get_value_string()
   {
      
      return "";

   }

   
   CLASS_DECL_ACID bool convert_to_double(double & d, string str)
   {

      str.replace_with("", " ");
      
      str.replace_with("", "\t");

      str.replace_with("", "\n");

      str.replace_with("", "\r");

      bool bDouble = false;

      if (str.length() >= 1)
      {

         if (ansi_char_isdigit(str[0]))
         {

            bDouble = true;

         }
         else if (str[0] == '-' || str[0] == '+')
         {

            if (str.length() >= 2)
            {

               if (ansi_char_isdigit(str[1]))
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

      d = atof(str.c_str());

      return true;

   }


} // namespace mathematics



