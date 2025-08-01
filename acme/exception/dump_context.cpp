#include "framework.h"
//#include "dump_context.h"
//
//
//#ifdef LINUX
//
//
//inline int _stprintf_s(char * pszBuffer, int iBufferLen, const ::scoped_string & scopedstrFormat, ...)
//{
//
//   __UNREFERENCED_PARAMETER(iBufferLen);
//
//   va_list args;
//
//   va_start (args, pszFormat);
//
//   vsprintf(scopedstrBuffer, pszFormat, args);
//
//   va_end (args);
//
//   return 0;
//
//}
//
//inline size_t lstrlen(const ::scoped_string & scopedstr)
//{
//   return strlen(scopedstr);
//}
//
//#endif
//
//
//int dump_context::GetDepth() const
//{
//   
//   return m_nDepth;
//
//}
//
//
//void dump_context::SetDepth(int nNewDepth)
//{
//   
//   m_nDepth = nNewDepth;
//
//}
//
//
//void dump_context::output_string(const ::scoped_string & scopedstr)
//{
//
//   //// use C-runtime/information when m_p is nullptr
//   //if (!m_p)
//   //{
//
//   //   ::information(scopedstr);
//
//   //   return;
//
//   //}
//
//   //ASSERT(scopedstr != nullptr);
//
//   //if (scopedstr == nullptr)
//   //{
//
//   //   throw ::exception(error_null_pointer);
//
//   //}
//
//   // otherwise, write the string to the file
//   //m_p->write(scopedstr, strlen(scopedstr)*sizeof(char));
//
//}
//
//
//dump_context::dump_context(::file::file * pfile)// :
//   //text_stream(pfile)
//{
//
//   m_nDepth = 0;
//
//}
//
//
//dump_context::~dump_context()
//{
//
//
//}
//
//
////void dump_context::destroy()
////{
////
////   auto estatus = text_stream::destroy();
////
////   return estatus;
////
////}
//
//
////void dump_context::flush()
////{
////
////   if (m_p)
////   {
////
////      m_p->flush();
////
////   }
////
////}
////
////
////void dump_context::write(const ::scoped_string & scopedstr)
////{
////
////   if (scopedstr == nullptr)
////   {
////
////      output_string("nullptr");
////
////      return;
////
////   }
////
////   ASSERT(scopedstr != nullptr);
////
////   if (scopedstr == nullptr)
////   {
////
////      throw ::exception(error_null_pointer);
////
////   }
////
////   if (!m_p)
////   {
////
////      char szBuffer[512];
////
////      char * pdata = szBuffer;
////
////      while (*psz != '\0')
////      {
////
////         if (pdata > szBuffer + _countof(szBuffer) - 3)
////         {
////
////            *pdata = '\0';
////
////            output_string(szBuffer);
////
////            pdata = szBuffer;
////
////         }
////
////         if (*psz == '\n')
////         {
////
////            *pdata++ = '\r';
////
////         }
////
////         *pdata++ = *psz++;
////
////      }
////
////      *pdata = '\0';
////
////      output_string(szBuffer);
////
////      return;
////
////   }
////
////   m_p->write(scopedstr, strlen(scopedstr)*sizeof(char));
////
////   return;
////
////}
////
////
////void dump_context::write(char i)
////{
////
////   string str;
////
////   str.formatf("%d", (int) i);
////
////   output_string(str);
////
////   return;
////
////}
////
////
////void dump_context::write(unsigned char u)
////{
////
////   string str;
////
////   str.formatf("%u", (int) u);
////
////   output_string(str);
////
////   return;
////
////}
////
////
////void dump_context::write(short i)
////{
////
////   string str;
////
////   str.formatf("%d", (int) i);
////
////   output_string(str);
////
////   return;
////
////}
////
////
////void dump_context::write(unsigned short u)
////{
////
////   string str;
////
////   str.formatf("%u", (unsigned short) u);
////
////   output_string(str);
////
////   return;
////
////}
////
////
////void dump_context::write(int i)
////{
////
////   string str;
////
////   str.formatf("%d", i);
////
////   output_string(str);
////
////   return;
////
////}
////
////
////void dump_context::write(unsigned int u)
////{
////
////   string str;
////
////   str.formatf("%u", u);
////
////   output_string(str);
////
////   return;
////
////}
////
////
////void dump_context::write(long long i)
////{
////
////   string str;
////
////   str.formatf("%l64d", i);
////
////   output_string(str);
////
////   return;
////
////}
////
////
////void dump_context::write(unsigned long long u)
////{
////
////   string str;
////
////   str.formatf("%l64u", u);
////
////   output_string(str);
////
////   return;
////
////}
////
////
////void dump_context::hex_dump(char i)
////{
////
////   string str;
////
////   str.formatf("0x%02x", (unsigned int) i);
////
////   output_string(str);
////
////   return;
////
////}
////
////
////void dump_context::hex_dump(unsigned char u)
////{
////
////   string str;
////
////   str.formatf("0x%02x", (unsigned int)u);
////
////   output_string(str);
////
////   return;
////
////}
////
////
////void dump_context::hex_dump(short i)
////{
////
////   string str;
////
////   str.formatf("0x%04x", (unsigned int) i);
////
////   output_string(str);
////
////   return;
////
////}
////
////
////void dump_context::hex_dump(unsigned short u)
////{
////
////   string str;
////
////   str.formatf("0x%04x", (unsigned int) u);
////
////   output_string(str);
////
////   return;
////
////}
////
////
////void dump_context::hex_dump(int i)
////{
////
////   string str;
////
////   str.formatf("0x%08x", i);
////
////   output_string(str);
////
////   return;
////
////}
////
////
////void dump_context::hex_dump(unsigned int u)
////{
////
////   string str;
////
////   str.formatf("0x%08x", u);
////
////   output_string(str);
////
////   return;
////
////}
////
////
////void dump_context::hex_dump(long long i)
////{
////
////   string str;
////
////   str.formatf("0x%016l64x", i);
////
////   output_string(str);
////
////   return;
////
////}
////
////
////void dump_context::hex_dump(unsigned long long u)
////{
////
////   string str;
////
////   str.formatf("0x%016l64x", u);
////
////   output_string(str);
////
////   return;
////
////}
////
////
////void dump_context::write(const ::particle * pparticle)
////{
////
////   if (pparticle == nullptr)
////   {
////
////      *this << "nullptr";
////
////   }
////   else
////   {
////
////      pparticle->dump(*this);
////
////   }
////
////   return;
////
////}
////
////
////void dump_context::write(const ::matter & matter)
////{
////
////   matter.dump(*this);
////
////   return;
////
////}
////
////
////void dump_context::write(const void * p)
////{
////
////   string str;
////
////   // prefix a pointer with "$" and print in hex
////   str.formatf("$%int_point", p);
////
////   output_string(str);
////
////   return;
////
////}
////
////
//////void dump_context::write(oswindow h)
//////{
//////
//////   return write((void *)h);
//////
//////}
////
////
//////void dump_context::write(HDC h)
//////{
//////
//////   return write((void *)h);
//////
//////}
//////
//////
//////#ifdef WINDOWS
//////
//////
//////void dump_context::write(HMENU h)
//////{
//////
//////   return write((void *)h);
//////
//////}
//////
//////
//////void dump_context::write(HACCEL h)
//////{
//////
//////   return write((void *)h);
//////
//////}
//////
//////
//////void dump_context::write(HFONT h)
//////{
//////
//////   return write((void *)h);
//////
//////}
//////
//////
//////#endif
////
////
/////////////////////////////////////////////////////////////////////////////////
////// Formatted output
////
////void dump_context::hex_dump(const ::scoped_string & scopedstrLine, unsigned char* pby, int nBytes, int nWidth)
////// do a simple hex-dump (8 per line) to a dump_context
//////  the "pszLine" is a string to print at the start of each line
//////    (%lx should be used to expand the current address)
////{
////
////   ASSERT(nBytes > 0);
////
////   if (nBytes <= 0)
////   {
////
////      throw ::exception(error_bad_argument);
////
////   }
////
////   ASSERT(nWidth > 0);
////
////   if (nWidth <= 0)
////   {
////
////      throw ::exception(error_bad_argument);
////
////   }
////
////   ASSERT(is_string_ok(scopedstrLine));
////
////   if (scopedstrLine == nullptr)
////   {
////
////      throw ::exception(error_bad_argument);
////
////   }
////
////   ASSERT(is_memory_segment_ok(pby, nBytes, false));
////   if( pby == nullptr )
////      throw ::exception(error_bad_argument);
////
////   int nRow = 0;
////   string str;
////
////
////   while (nBytes--)
////   {
////
////      if (nRow == 0)
////      {
////         str.formatf(scopedstrLine, pby);
////
////         *this << str;
////      }
////
////      str.formatf(" %02X", *pby);
////      *this << str;
////
////      pby++;
////
////      if (++nRow >= nWidth)
////      {
////         *this << "\n";
////         nRow = 0;
////      }
////   }
////   if (nRow != 0)
////      *this << "\n";
////}
////
////
////#ifdef WINDOWS
////
////
////void dump_context::write(const unichar * psz)
////{
////
////   if (scopedstr == nullptr)
////   {
////
////      output_string("(nullptr)");
////
////      return;
////
////   }
////
////   return write(unicode_to_utf8(scopedstr));
////   
////}
////
////
////#endif
////
////
////void dump_context::write(const ::scoped_string & scopedstr)
////{
////
////   return write((const_char_pointer )str.c_str());
////
////}
////
////
////
