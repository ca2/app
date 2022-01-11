#include "framework.h"


#ifdef LINUX


inline i32 _stprintf_s(char * pszBuffer, i32 iBufferLen, const char * pszFormat, ...)
{

   __UNREFERENCED_PARAMETER(iBufferLen);

   va_list args;

   va_start (args, pszFormat);

   vsprintf(pszBuffer, pszFormat, args);

   va_end (args);

   return 0;

}

inline size_t lstrlen(const char * psz)
{
   return strlen(psz);
}

#endif


i32 dump_context::GetDepth() const
{
   
   return m_nDepth;

}


void dump_context::SetDepth(i32 nNewDepth)
{
   
   m_nDepth = nNewDepth;

}


void dump_context::output_string(const char * psz)
{

   // use C-runtime/output_debug_string when m_p is nullptr
   if (!m_p)
   {

      ::output_debug_string(psz);

      return;

   }

   ASSERT(psz != nullptr);

   if (psz == nullptr)
   {

      __throw(error_null_pointer);

   }

   // otherwise, write the string to the file
   m_p->write(psz, strlen(psz)*sizeof(char));

}


dump_context::dump_context(::file::file * pfile) :
   text_stream(pfile)
{

   m_nDepth = 0;

}


dump_context::~dump_context()
{


}


//void dump_context::destroy()
//{
//
//   auto estatus = text_stream::destroy();
//
//   return estatus;
//
//}


void dump_context::flush()
{

   if (m_p)
   {

      m_p->flush();

   }

}


void dump_context::write(const char * psz)
{

   if (psz == nullptr)
   {

      output_string("nullptr");

      return;

   }

   ASSERT(psz != nullptr);

   if (psz == nullptr)
   {

      __throw(error_null_pointer);

   }

   if (!m_p)
   {

      char szBuffer[512];

      char * pdata = szBuffer;

      while (*psz != '\0')
      {

         if (pdata > szBuffer + _countof(szBuffer) - 3)
         {

            *pdata = '\0';

            output_string(szBuffer);

            pdata = szBuffer;

         }

         if (*psz == '\n')
         {

            *pdata++ = '\r';

         }

         *pdata++ = *psz++;

      }

      *pdata = '\0';

      output_string(szBuffer);

      return;

   }

   m_p->write(psz, strlen(psz)*sizeof(char));

   return;

}


void dump_context::write(char i)
{

   string str;

   str.format("%d", (i32) i);

   output_string(str);

   return;

}


void dump_context::write(u8 u)
{

   string str;

   str.format("%u", (i32) u);

   output_string(str);

   return;

}


void dump_context::write(i16 i)
{

   string str;

   str.format("%d", (i32) i);

   output_string(str);

   return;

}


void dump_context::write(u16 u)
{

   string str;

   str.format("%u", (u16) u);

   output_string(str);

   return;

}


void dump_context::write(i32 i)
{

   string str;

   str.format("%d", i);

   output_string(str);

   return;

}


void dump_context::write(u32 u)
{

   string str;

   str.format("%u", u);

   output_string(str);

   return;

}


void dump_context::write(i64 i)
{

   string str;

   str.format("%l64d", i);

   output_string(str);

   return;

}


void dump_context::write(u64 u)
{

   string str;

   str.format("%l64u", u);

   output_string(str);

   return;

}


void dump_context::hex_dump(i8 i)
{

   string str;

   str.format("0x%02x", (u32) i);

   output_string(str);

   return;

}


void dump_context::hex_dump(u8 u)
{

   string str;

   str.format("0x%02x", (u32)u);

   output_string(str);

   return;

}


void dump_context::hex_dump(i16 i)
{

   string str;

   str.format("0x%04x", (u32) i);

   output_string(str);

   return;

}


void dump_context::hex_dump(u16 u)
{

   string str;

   str.format("0x%04x", (u32) u);

   output_string(str);

   return;

}


void dump_context::hex_dump(i32 i)
{

   string str;

   str.format("0x%08x", i);

   output_string(str);

   return;

}


void dump_context::hex_dump(u32 u)
{

   string str;

   str.format("0x%08x", u);

   output_string(str);

   return;

}


void dump_context::hex_dump(i64 i)
{

   string str;

   str.format("0x%016l64x", i);

   output_string(str);

   return;

}


void dump_context::hex_dump(u64 u)
{

   string str;

   str.format("0x%016l64x", u);

   output_string(str);

   return;

}


void dump_context::write(const ::matter * pobject)
{

   if (pobject == nullptr)
   {

      *this << "nullptr";

   }
   else
   {

      pobject->dump(*this);

   }

   return;

}


void dump_context::write(const ::matter & matter)
{

   matter.dump(*this);

   return;

}


void dump_context::write(const void * p)
{

   string str;

   // prefix a pointer with "$" and print in hex
   str.format("$%point_i32", p);

   output_string(str);

   return;

}


//void dump_context::write(oswindow h)
//{
//
//   return write((void *)h);
//
//}


//void dump_context::write(HDC h)
//{
//
//   return write((void *)h);
//
//}
//
//
//#ifdef WINDOWS
//
//
//void dump_context::write(HMENU h)
//{
//
//   return write((void *)h);
//
//}
//
//
//void dump_context::write(HACCEL h)
//{
//
//   return write((void *)h);
//
//}
//
//
//void dump_context::write(HFONT h)
//{
//
//   return write((void *)h);
//
//}
//
//
//#endif


/////////////////////////////////////////////////////////////////////////////
// Formatted output

void dump_context::hex_dump(const char * pszLine, byte* pby, i32 nBytes, i32 nWidth)
// do a simple hex-dump (8 per line) to a dump_context
//  the "pszLine" is a string to print at the start of each line
//    (%lx should be used to expand the current address)
{

   ASSERT(nBytes > 0);

   if (nBytes <= 0)
   {

      __throw(error_invalid_argument);

   }

   ASSERT(nWidth > 0);

   if (nWidth <= 0)
   {

      __throw(error_invalid_argument);

   }

   ASSERT(__is_valid_string(pszLine));

   if (pszLine == nullptr)
   {

      __throw(error_invalid_argument);

   }

   ASSERT(__is_valid_address(pby, nBytes, false));
   if( pby == nullptr )
      __throw(error_invalid_argument);

   i32 nRow = 0;
   string str;


   while (nBytes--)
   {

      if (nRow == 0)
      {
         str.format(pszLine, pby);

         *this << str;
      }

      str.format(" %02X", *pby);
      *this << str;

      pby++;

      if (++nRow >= nWidth)
      {
         *this << "\n";
         nRow = 0;
      }
   }
   if (nRow != 0)
      *this << "\n";
}


#ifdef WINDOWS


void dump_context::write(const unichar * psz)
{

   if (psz == nullptr)
   {

      output_string("(nullptr)");

      return;

   }

   return write(::str::international::unicode_to_utf8(psz));
   
}


#endif


void dump_context::write(const ::string & str)
{

   return write((const char *) str.c_str());

}



