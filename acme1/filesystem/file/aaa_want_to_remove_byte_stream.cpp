#include "framework.h"


stream & stream::read(string & str)
{

   strsize_storage iWrittenLength = -1;

   read(iWrittenLength);

   if (fail())
   {

      return *this;

   }

   try
   {

      char* psz = str.get_string_buffer(iWrittenLength);

      auto iReadLength = read(psz, iWrittenLength);

      if (iReadLength < iWrittenLength)
      {

         set_fail_bit();

      }

   }
   catch (...)
   {

      set_fail_bit();

   }

   return *this;

}



stream & stream::write(const string & str)
{

   strsize_storage iLength = str.get_length();

   write(iLength);

   write(str, iLength);

   return *this;

}
