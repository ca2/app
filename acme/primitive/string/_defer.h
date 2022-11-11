#pragma once



namespace hex
{


   inline CLASS_DECL_ACME i32 to(char ch)
   {

      if (ch >= '0' && ch <= '9')
      {

         return ch - '0';

      }
      else if (ch >= 'a' && ch <= 'f')
      {

         return ch - 'a' + 10;

      }
      else if (ch >= 'A' && ch <= 'F')
      {

         return ch - 'A' + 10;

      }
      else
      {

         throw "not hexadecimal digit";

      }

   }


} // namespace hex



