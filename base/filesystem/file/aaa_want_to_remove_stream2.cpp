#include "framework.h"


namespace file
{



   stream2::stream2()
   {
   }

   stream2::stream2(::file::file * pwriter)
   {

      m_p = pwriter;

   }

   stream2::~stream2()
   {
   }





   stream2 & stream2::operator << (uchar uch)
   {
      write(uch);
      return *this;
   }

   stream2 & stream2::operator << (u16 ui)
   {
      write(ui);
      return *this;
   }

   stream2 & stream2::operator << (i32 i)
   {
      write(i);
      return *this;
   }

   stream2 & stream2::operator << (u32 ui)
   {
      write(ui);
      return *this;
   }

   stream2 & stream2::operator << (const RECT * prect)
   {
      write(prect);
      return *this;
   }


   stream2 & stream2::operator << (const char * psz)
   {
      write((void *)psz, strlen(psz));
      return *this;
   }

   stream2 & stream2::operator << (const string & str)
   {
      operator <<((const char *)str);
      return *this;
   }


} // namespace file



