#pragma once


#include "string_buffer.h"
#include "stream.h"
#include "acme/primitive/string/string.h"

enum enum_start_reference
{

   e_start_reference,

};


inline ::string ellipsis(const char* psz, strsize len)
{

   auto lenTotal = string_safe_length(psz, len);

   if (lenTotal < 0)
   {

      return ::string(psz, len - 3) + "...";

   }
   else
   {

      return psz;

   }

}


inline ::u64 consume_natural(const char*& psz, const char* pszBegin, int iRadix = 10)
{

   char* endptr = nullptr;

   auto u = strtoull(psz, &endptr, iRadix);

   if (!endptr)
   {

      if (::is_null(pszBegin))
      {

         pszBegin = psz;

      }

      throw_exception(error_premature_end_of_file, "not natural number near \"" + ellipsis(maximum(psz - 10, pszBegin), 20) + "\"");

   }

   psz = endptr;

   return u;

}


inline ::i64 consume_integer(const char * & psz, const char * pszBegin, int iRadix = 10)
{

   char* endptr = nullptr;

   auto i = strtoll(psz, &endptr, 10);

   if (!endptr)
   {

      if (::is_null(pszBegin))
      {

         pszBegin = psz;

      }

      throw_exception(error_parsing, "not integer near \"" + ellipsis(maximum(psz - 10, pszBegin), 20) + "\"");

   }

   psz = endptr;

   return i;

}


inline ::f64 consume_floating(const char*& psz, const char* pszBegin, int iRadix = 10)
{

   char* endptr = nullptr;

   auto d = strtod(psz, &endptr);

   if (!endptr)
   {

      if (::is_null(pszBegin))
      {

         pszBegin = psz;

      }

      throw_exception(error_premature_end_of_file, "not floating near \"" + ellipsis(maximum(psz - 10, pszBegin), 20) + "\"");

   }

   psz = endptr;

   return d;

}


template < typename FILE >
class write_text_stream :
   public FLAGS,
   public print_formatting
{
public:


   FILE *         m_pfile;
   char           m_chSeparator = ' ';
#ifdef WINDOWS
   const char* m_pszEolSeparator = "\r\n";
#else
   const char* m_pszEolSeparator = "\n";
#endif


   write_text_stream();
   write_text_stream(FILE* pfile);
   write_text_stream(const write_text_stream& stream) = delete;
   ~write_text_stream();


   // void destroy() ;

   //void destroy() {}

   //string as_string() const;


   //FILE * get_file()  { return m_pfile; }


   //::file::file* get_file()
   //{

   //   return m_pfile;

   //}

   //template < primitive_integral INTEGRAL >
   //void number_read(TYPE& t)
   //{

   //   const char endptr = nullptr;

   //   auto ull = strtoull(m_str, &endptr, 10);

   //   if (!endptr)
   //   {

   //      set_fail_flag();

   //   }
   //   else
   //   {

   //      

   //   }

   //   ::copy(t, str);

   //}


   void print(const ::string& str)
   {

      m_pfile->write(str.c_str(), str.get_length_in_bytes());

   }


   template < primitive_number NUMBER >
   void write_number(NUMBER number) { print(as_string(number)); }
   
   template < primitive_number NUMBER >
   void write_number(NUMBER number, const char * pszFormat) { print(as_string(number, pszFormat)); }

   /*template < typename TYPE >
   void number_exchange(TYPE& t)
   {

      has_loading_flag() ? number_read(t) : number_write(t);

   }*/


   //template < typename TYPE >
   //void string_read(TYPE& t)
   //{

   //   string str = read_string();

   //   ::from_string(t, str);

   //}


   //template < typename TYPE >
   //void string_write(const TYPE& t)
   //{

   //   string str;

   //   str = as_string(t);

   //   print(str);

   //}


   //template < typename TYPE >
   //void string_exchange(TYPE& t)
   //{

   //   has_loading_flag() ? string_read(t) : string_write(t);

   //}


   //template < typename TYPE >
   //void network_payload_exchange(TYPE& t);


   /*template < typename TYPE >
   void write_only(TYPE & t) { is_loading() ? throw_exception(error_io) : operator <<(t); }

   template < typename TYPE >
   void exchange(const ::atom & atom, TYPE & t) { ::__string_exchange(*this, t); }*/

   void append_format(const char* pszFormat, ...)
   {

      ::string strText;

      ASSERT(__is_valid_string(pszFormat));

      va_list argList;

      va_start(argList, pszFormat);

      strText.format_arguments(pszFormat, argList);

      va_end(argList);

      print(strText);

   }


   //bool is_stream_null();
   //bool is_stream_set();

   //void close() {}

   void new_line()
   {

      if (m_fmtflags & ::file::separated)
      {

         m_pfile->unget_if(m_chSeparator);

      }

      print(m_pszEolSeparator);

   }


   write_text_stream& operator <<(bool b)
   {

      if(b)
      {

         print("1");

      }
      else
      {

         print("0");

      }

      if (m_fmtflags & ::file::separated)
      {

         print(m_chSeparator);

      }

      return *this;

   }


   write_text_stream& operator <<(char ch)
   {

      write(&ch, 1);

      if (m_fmtflags & ::file::separated)
      {

         print(m_chSeparator);

      }

      return *this;

   }

   write_text_stream& operator <<(enum_start_reference)
   {

      return *this;

   }


   write_text_stream& operator <<(uchar uch)
   {

      write(&uch, 1);

      if (m_fmtflags & ::file::separated)
      {

         print(m_chSeparator);

      }

      return *this;

   }


#ifdef WINDOWS


   write_text_stream& operator <<(unichar wch)
   {
      
      char sz[10];

      wd16_to_ansi(sz, &wch, 1);

      print(sz);

      if (m_fmtflags & ::file::separated)
      {

         print(m_chSeparator);

      }

      return *this;

   }


#endif

   template < primitive_signed_not_8bit SIGNED >
   write_text_stream& operator <<(SIGNED i)
   {

      write_number(i);

      if (m_fmtflags & ::file::separated)
      {

         print(m_chSeparator);

      }

      return *this;

   }


   template < primitive_unsigned_not_8bit UNSIGNED >
   write_text_stream& operator <<(UNSIGNED u)
   {

      write_number(u);

      if (m_fmtflags & ::file::separated)
      {

         print(m_chSeparator);

      }

      return *this;

   }

   template < typename T >
   void print_string_copy(const T& t)
   {

      ::string str;

      ::copy(str, t);

      print(str);

   }

   write_text_stream& operator <<(integral_byte integralbyte)
   {

      print_string_copy(integralbyte);

      if (m_fmtflags & ::file::separated)
      {

         print(m_chSeparator);

      }

      return *this;

   }

   //write_text_stream& operator <<(i32 i)
   //{

   //   write_integer(i);

   //   print(m_chSeparator);

   //   return *this;

   //}


   //write_text_stream& operator <<(u32 u)
   //{

   //   write_natural(u);

   //   print(m_chSeparator);

   //   return *this;

   //}


   //write_text_stream& operator <<(i64 i)
   //{

   //   write_integer(i);

   //   print(m_chSeparator);

   //   return *this;

   //}


   //write_text_stream& operator <<(u64 u)
   //{

   //   write_natural(u);

   //   print(m_chSeparator);

   //   return *this;

   //}


   template < primitive_floating FLOATING >
   write_text_stream& operator <<(FLOATING f)
   {

      write_number(f);

      if (m_fmtflags & ::file::separated)
      {

         print(m_chSeparator);

      }

      return *this;

   }

//#ifdef _MSC_VER
//
//   write_text_stream& operator <<(long l)
//   {
//
//      write_integer(l);
//
//      print(m_chSeparator);
//
//      return *this;
//
//   }
//
//#endif
//
//
//   write_text_stream& operator <<(double d)
//   {
//
//      write_floating(d);
//
//      print(m_chSeparator);
//
//      return *this;
//
//   }
//

   // void write(const POINT_I32 & point) ;
   // void write(const SIZE_I32 & size) ;
   // void write(const ::rectangle_i32 &rectangle) ;

   write_text_stream& operator <<(const char* psz)
   {

      if (m_fmtflags & ::file::network_payload)
      {

         print("\"");

      }

      print(psz);

      if (m_fmtflags & ::file::network_payload)
      {

         print("\"");

      }

      if (m_fmtflags & ::file::separated)
      {

         print(m_chSeparator);

      }

      return *this;

   }

   //text_stream & operator <<(const ::atom & atom) ;
   write_text_stream& operator <<(const ::string& str)
   {

      if (m_fmtflags & ::file::network_payload)
      {

         print("\"");

      }

      print(str);

      if (m_fmtflags & ::file::network_payload)
      {

         print("\"");

      }

      if (m_fmtflags & ::file::separated)
      {

         print(m_chSeparator);

      }

      return *this;

   }


   template < primitive_character CHARACTER2, strsize sizeMaximumLength >
   write_text_stream& operator <<(const ::inline_string < CHARACTER2, sizeMaximumLength > & inlinestring)
   {

      if (m_fmtflags & ::file::network_payload)
      {

         print("\"");

      }

      write(inlinestring.get_data(), inlinestring.get_size());

      if (m_fmtflags & ::file::network_payload)
      {

         print("\"");

      }

      if (m_fmtflags & ::file::separated)
      {

         print(m_chSeparator);

      }

      return *this;

   }
   //text_stream & operator <<(const property_set& set) ;
   template < typename TYPE >
   write_text_stream & write(const TYPE& t)
   {

      return *this << t;

   }

   // void network_payload_write(const ::matter & matter);


   void raw_print(const ::string& str)
   {

      print(str);

   }


   //void print_number(const ::string& str)
   //{

   //   print_number(str);

   //}

   //::string get_location() const;

   //::filesize get_position() const ;
   void write(const void* psz, strsize s)
   {

      m_pfile->write(psz, s);

   }

   //operator void* () { return this; }

//   text_stream& operator >>(bool& b);
//   text_stream& operator >>(char& ch);
//   text_stream& operator >>(uchar& uch);
//#ifdef WINDOWS
//   text_stream& operator >>(unichar& wch);
//#endif
//   text_stream& operator >>(i8& i);
//   text_stream& operator >>(i16& sh);
//   text_stream& operator >>(u16& u);
//   text_stream& operator >>(i32& i);
//   text_stream& operator >>(u32& u);
//   text_stream& operator >>(i64& i);
//   text_stream& operator >>(u64& u);
//   text_stream& operator >>(float& f);
//   text_stream& operator >>(double& d);
//   text_stream& operator >>(string& str);
//   //text_stream & operator >>(property_set& set) ;
//   //text_stream & operator >>(::atom & atom) ;
//
//   template < typename TYPE >
//   void network_payload_read(TYPE& matter);
//

};


class read_sz_stream :
   public FLAGS
{
public:


   const char * m_psz;
   const char* m_pszBegin;


   read_sz_stream(const char * psz, const char* pszBegin = nullptr);
   read_sz_stream(const read_sz_stream& stream) = delete;
   ~read_sz_stream();


   // void destroy() ;

   //void destroy() {}

   //string as_string() const;


   //FILE * get_file()  { return m_pfile; }


   //::file::file* get_file()
   //{

   //   return m_pfile;

   //}

   ::u64 read_natural(int iRadix = 10)
   {

      return consume_natural(m_psz, m_pszBegin, iRadix);

   }


   ::i64 read_integer(int iRadix = 10)
   {

      return consume_integer(m_psz, m_pszBegin, iRadix);

   }


   ::f64 read_floating()
   {

      return consume_floating(m_psz, m_pszBegin);


   }


   ::string get_word(const char* pszBreakCharacters = " \n\t\r,;")
   {

      return read_span_excluding(pszBreakCharacters);

   }

   ::string read_span_excluding(const char * pszBreakCharacters)
   {

      auto size = string_span_excluding(m_psz, pszBreakCharacters);

      ::string str(m_psz, size);

      m_psz += size;

      return ::move(str);

   }


   //void close() {}

//   text_stream& operator <<(bool b);
//   text_stream& operator <<(char ch);
//   text_stream& operator <<(uchar uch);
//#ifdef WINDOWS
//   text_stream& operator <<(unichar wch);
//#endif
//   text_stream& operator <<(i16 sh);
//   text_stream& operator <<(u16 u);
//   text_stream& operator <<(i32 i);
//   text_stream& operator <<(u32 u);
//   text_stream& operator <<(i64 i);
//   text_stream& operator <<(u64 u);
//   text_stream& operator <<(float f);
//   text_stream& operator <<(double d);
//   // void write(const POINT_I32 & point) ;
//   // void write(const SIZE_I32 & size) ;
//   // void write(const ::rectangle_i32 &rectangle) ;
//
//   text_stream& operator <<(const char* psz);
//   //text_stream & operator <<(const ::atom & atom) ;
//   text_stream& operator <<(const ::string& str);
//   //text_stream & operator <<(const property_set& set) ;
//   template < typename TYPE >
//   void network_payload_write(const TYPE& t);
//
//   // void network_payload_write(const ::matter & matter);



   read_sz_stream& operator >>(bool& b)
   {

      auto strWord = get_word();

      strWord.trim_left("\"'([{");

      strWord.trim_right("\"')]}");

      if (strWord.compare_ci("no") == 0
         || strWord.compare_ci("false") == 0
         || strWord.compare_ci("0") == 0)
      {

         b = false;

      }
      else
      {

         b = true;

      }

      return *this;

   }

   read_sz_stream& operator >>(char& ch)
   {

      ch = *m_psz;

      if (!ch)
      {

         throw_exception(error_premature_end_of_file);

      }

      m_psz++;

      return *this;

   }


   read_sz_stream& operator >>(uchar& uch)
   {

      return operator >>((char&)uch);

   }

#ifdef WINDOWS
   read_sz_stream& operator >>(unichar& wch)
   {

      ::i32 len = 0;

      auto iIndex = unicode_index_length(m_psz, len);

      if (iIndex < 0)
      {

         throw_exception(error_premature_end_of_file);

      }
      else if (iIndex >= 65536)
      {

         wch = 65535; // (INVALID CHAR CODE)?

      }

      wch = iIndex;

      m_psz += len;

      return *this;

   }

#endif
   read_sz_stream& operator >>(i8& i)
   {

      return operator >>((char&)i);

   }


   read_sz_stream& operator >>(i16& sh)
   {

      auto iRead = read_integer();

      if (iRead < SHRT_MIN)
      {

         throw_exception(error_standard_int_overflow);

      }
      else if (iRead > SHRT_MAX)
      {

         throw_exception(error_standard_int_overflow);

      }

      sh = (::i16)iRead;

      return *this;

   }


   read_sz_stream& operator >>(u16& u)
   {

      auto uRead = read_natural();

      if (uRead > USHRT_MAX)
      {

         throw_exception(error_standard_int_overflow);

      }

      u = (::u16)uRead;

      return *this;

   }   


   read_sz_stream& operator >>(i32& i)
   {

      auto iRead = read_integer();

      if (iRead < INT_MIN)
      {

         throw_exception(error_standard_int_overflow, "INT_MIN overflow: " + as_string(iRead));

      }
      else if (iRead > INT_MAX)
      {

         throw_exception(error_standard_int_overflow, "INT_MAX overflow: " + as_string(iRead));

      }

      i = (::i32)iRead;

      return *this;

   }


   read_sz_stream& operator >>(u32& u)
   {

      auto uRead = read_natural();

      if (uRead > UINT_MAX)
      {

         throw_exception(error_standard_int_overflow);

      }

      u = (::u32) uRead;

      return *this;

   }


   read_sz_stream& operator >>(i64& i)
   {

      i = read_integer();

      return *this;

   }  


   read_sz_stream& operator >>(u64& u)
   {

      u = read_natural();

      return *this;

   }


   read_sz_stream& operator >>(float& f)
   {

      f = (float) read_floating();

      return *this;

   }
   

   read_sz_stream& operator >>(double& d)
   {

      d = read_floating();

      return *this;

   }


   read_sz_stream& operator >>(string& str)
   {

      str = get_word();

      return *this;

   }


   ////text_stream & operator >>(property_set& set) ;
   ////text_stream & operator >>(::atom & atom) ;


   template < typename TYPE >
   read_sz_stream & read(TYPE& t)
   {

      *this = t;

      return *this;
   
   }


};


//using std_string_stream = ::write_text_stream;


class CLASS_DECL_ACME string_reference_stream :
   public write_text_stream < string_reference_buffer >,
   public string_reference_buffer
{
public:


   string_reference_stream(::string& str) : write_text_stream(this),string_reference_buffer(str) { }


};


class CLASS_DECL_ACME string_stream :
   public write_text_stream < string_buffer >
{
public:

   
   string_buffer   m_stringbuffer;


   string_stream() : write_text_stream(&m_stringbuffer) { }


   ::string as_string() const { return m_stringbuffer.m_strOwnStorage; }
   ::string & as_string()  { return m_stringbuffer.m_strOwnStorage; }


};


template < typename FILE >
inline write_text_stream < FILE >::write_text_stream()
{


}


template < typename FILE >
inline write_text_stream < FILE >::write_text_stream(FILE* pfile)
{

   m_pfile = pfile;

   set_ok_flag();

   //if (pfile->has_storing_flag())
   //{

   //   defer_set_storing_flag();

   //}

}


//template < typename FILE >
//inline text_stream < FILE >::text_stream(const stream_base& stream)
//{
//
//   m_pfile = dynamic_cast <FILE*>(((stream_base&)stream).get_file());
//
//   if (!m_pfile)
//   {
//
//      throw_exception(error_wrong_type);
//
//   }
//
//   if (stream.nok())
//   {
//      set_nok();
//   }
//   else
//   {
//
//      set_ok_flag();
//
//   }
//
//   if (stream.has_storing_flag())
//   {
//
//      defer_set_storing_flag();
//
//   }
//}


template < typename FILE >
inline write_text_stream < FILE >::~write_text_stream()
{


}


//template < typename FILE >
//inline string write_text_stream < FILE >::read_string()
//{
//
//   string str;
//
//   m_pfile->read_string(str);
//
//   return str;
//
//}


//template < typename FILE >
//bool text_stream < FILE >::is_stream_null()
//{
//
//   return !m_pfile;
//
//}
//
//
//template < typename FILE >
//void text_stream < FILE >::destroy()
//{
//
//   m_pfile.release();
//
//   ///* auto estatus = */ stream::destroy();
//
//   /* return estatus; */
//
//}


//template < typename FILE >
//string text_stream < FILE >::as_string() const
//{
//
//   return m_pfile->as_string();
//
//}


//template < typename FILE >
//bool text_stream < FILE >::is_stream_set()
//{
//
//   return m_pfile;
//
//}


//template < typename FILE >
//text_stream < FILE>& text_stream < FILE >::operator >>(i8& ch)
//{
//
//   m_gcount = m_pfile->read(&ch, 1);
//
//   if (m_gcount <= 0)
//   {
//
//      throw_exception(error_io);
//
//   }
//
//   return *this;
//
//}


//template < typename FILE >
//void text_stream < FILE >::close()
//{
//
//   m_pfile->close();
//
//}


//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(bool b)
//{
//
//   if (b)
//   {
//
//      raw_print("true");
//
//   }
//   else
//   {
//
//      raw_print("false");
//
//   }
//
//   return *this;
//
//}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(char ch)
//{
//
//   m_pfile->write(&ch, sizeof(ch)); // treat as char - character
//
//   return *this;
//
//}


//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(uchar uch)
//{
//
//   operator <<((u32)uch);
//
//   return *this;
//
//}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(i16 i)
//{
//
//   operator <<((i32)i);
//
//   return *this;
//
//}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(u16 u)
//{
//
//   operator <<((u32)u);
//
//   return *this;
//
//}
//
//
//#ifdef WINDOWS
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(unichar wch)
//{
//
//   raw_print(unicode_to_utf8(wch));
//
//   return *this;
//
//}
//
//#endif
//
//
//template < typename FILE >
//void text_stream < FILE >::print_number(const ::string& str)
//{
//
//   auto estrflag = this->m_estrflag;
//
//   if (estrflag & str_flag_ifnumberparenthesize)
//   {
//
//      raw_print("(");
//
//   }
//
//   raw_print(str);
//
//   if (estrflag & str_flag_ifnumberparenthesize)
//   {
//
//      raw_print(")");
//
//   }
//
//   if (estrflag & str_flag_ifnumberspace)
//   {
//
//      raw_print(" ");
//
//   }
//
//}


//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(i32 i)
//{
//
//   print_number(as_string(i));
//
//   return *this;
//
//}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(u32 u)
//{
//
//   print_number(as_string(u));
//
//   return *this;
//
//}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(i64 i)
//{
//
//   print_number(as_string(i));
//
//   return *this;
//
//}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(u64 u)
//{
//
//   print_number(as_string(u));
//
//   return *this;
//
//}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(float f)
//{
//
//   string str;
//
//   str.format("%f", f);
//
//   print_number(str);
//
//   return *this;
//
//}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(double d)
//{
//
//   string str;
//
//   str.format("%f", d);
//
//   print_number(as_string(d));
//
//   return *this;
//
//}


//text_stream & text_stream < FILE >::operator <<(const ::rectangle_i32 &rectangle)
//{
//
//   this->m_estrflag = (e_str_flag)((int)this->m_estrflag & ~(int)str_flag_ifnumberparenthesizeandspace);
//
//   *this << prectangle->left << prectangle->top << prectangle->right << prectangle->bottom;
//
//}
//
//
//text_stream & text_stream < FILE >::operator <<(const SIZE_I32 * psize)
//{
//
//   this->m_estrflag = (e_str_flag)((int)this->m_estrflag & ~(int)str_flag_ifnumberparenthesizeandspace);
//
//   *this << psize->cx << psize->cy;
//
//}
//
//
//
//text_stream & text_stream < FILE >::operator <<(const POINT_I32 * ppoint)
//{
//
//   this->m_estrflag = (e_str_flag)((int)this->m_estrflag & ~(int)str_flag_ifnumberparenthesizeandspace);
//
//   *this << ppoint->x << ppoint->y;
//
//}


//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(const char* psz)
//{
//
//   if (::is_null(psz))
//   {
//
//      throw_exception(error_io);
//
//   }
//   else
//   {
//
//      write(psz, strlen(psz));
//
//   }
//
//   return *this;
//
//}
//
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(const ::string& str)
//{
//
//   operator <<(str.c_str());
//
//   return *this;
//
//}
//
//
//
//
//template < typename FILE >
//void text_stream < FILE >::raw_print(const ::string& str)
//{
//
//   write(str.c_str(), str.size());
//
//   this->m_estrflag = (e_str_flag)((int)this->m_estrflag & ~(int)str_flag_ifnumberparenthesize);
//
//}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(bool& b)
//{
//
//   m_pfile->read(&b, sizeof(b));
//
//   return *this;
//
//}
//
////
////text_stream & text_stream < FILE >::operator >>(char & ch)
////{
////
////   return operator >>((char &)ch);
////
////}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(char& ch)
//{
//
//   m_gcount = m_pfile->read(&ch, sizeof(ch));
//
//   if (m_gcount <= 0)
//   {
//
//      throw_exception(error_io);
//
//   }
//
//   return *this;
//
//}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(uchar& uch)
//{
//
//   m_pfile->read(&uch, sizeof(uch));
//
//   return *this;
//
//}
//
//
//#ifdef WINDOWS
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(unichar& wch)
//{
//
//   m_pfile->read(&wch, sizeof(wch));
//
//   return *this;
//
//}
//
//
//#endif
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(i16& sh)
//{
//
//   m_pfile->read(&sh, sizeof(sh));
//
//   return *this;
//
//}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(u16& u)
//{
//
//   m_pfile->read(&u, sizeof(u));
//
//   return *this;
//
//}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(i32& i)
//{
//
//   number_read(i);
//
//   return *this;
//
//}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(u32& u)
//{
//
//   number_read(u);
//
//   return *this;
//
//}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(i64& i)
//{
//
//   number_read(i);
//
//   return *this;
//
//}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(u64& u)
//{
//
//   number_read(u);
//
//   return *this;
//
//}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(float& f)
//{
//
//   number_read(f);
//
//   return *this;
//
//}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(double& d)
//{
//
//   number_read(d);
//
//   return *this;
//
//}
//
////text_stream & text_stream < FILE >::operator >>(RECTANGLE_I32 * prectangle)
////
////{
////   m_pfile->read(&prectangle->left, sizeof(prectangle->left));
////
////   m_pfile->read(&prectangle->top, sizeof(prectangle->top));
////
////   m_pfile->read(&prectangle->right, sizeof(prectangle->right));
////
////   m_pfile->read(&prectangle->bottom, sizeof(prectangle->bottom));
////   
////}
////
////text_stream & text_stream < FILE >::operator >>(SIZE_I32 * psize)
////{
////   m_pfile->read(&psize->cx, sizeof(psize->cx));
////   m_pfile->read(&psize->cy, sizeof(psize->cy));
////}
////
////text_stream & text_stream < FILE >::operator >>(POINT_I32 * ppoint)
////{
////   m_pfile->read(&ppoint->x, sizeof(ppoint->x));
////   m_pfile->read(&ppoint->y, sizeof(ppoint->y));
////}
//
//
//template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(string& str)
//{
//
//   str.Empty();
//
//   char ch = 0;
//
//   while (true)
//   {
//
//      operator >>(ch);
//
//      if (ch == '\0')
//      {
//
//         break;
//
//      }
//
//      if (m_gcount <= 0)
//      {
//
//         break;
//
//      }
//
//      if (ch == '\n')
//      {
//
//         break;
//
//      }
//
//      str += ch;
//
//   }
//
//   return *this;
//
//}
//
//
////template < typename FILE >
////text_stream < FILE > & text_stream < FILE >::operator >>(property_set& set)
////{
////
////   //__exchange_load_array(*this, set);
//////#define memory_new ACME_NEW
////
////   return *this;
////
////}
//
//
////template < typename FILE >
////text_stream < FILE > & text_stream < FILE >::operator >>(::atom& atom)
////{
////
////   string str;
////
////   operator >> (str);
////
////   atom = str;
////
////   return *this;
////
////}
//
//
//template < typename FILE >
//inline  string text_stream < FILE >::get_location() const
//{
//
//   return "<unknown text_stream_base locationd>";
//
//}
//
//
////template < typename FILE >
////inline ::filesize text_stream < FILE >::get_position() const
////{
////
////   return m_pfile->get_position();
////
////}
//
//
//template < typename FILE >
//inline void text_stream < FILE >::write(const void* psz, strsize s)
//{
//
//   m_pfile->write(psz, s);
//
//}
//
//
////void text_stream < FILE >::network_payload_write(const ::matter & matter)
////{
////
////   payload_stream s;
////
////   string strNetworkPayload;
////
////   s.set_storing();
////
////   ::__exchange(s, t);
////
////   strNetworkPayload = s.m_ppayload->get_network_payload();
////
////   string_write(strNetworkPayload);
////
////}
////
////
////void text_stream < FILE >::network_payload_read(::matter & matter)
////{
////
////   payload_stream s;
////
////   string strNetworkPayload;
////
////   string_read(strNetworkPayload);
////
////   s.m_ppayload->parse_network_payload(strNetworkPayload);
////
////   s.set_loading();
////
////   ::__exchange(s, t);
////
////}
//
//
//
//
//



template < typename FILE >
inline auto __write_text_stream(FILE* pfile)
{

   return write_text_stream < FILE >(pfile);

}


template < typename FILE >
inline auto __text_stream(const ::pointer<FILE>& pfile)
{

   return __text_stream(pfile.m_p);

}


inline read_sz_stream::read_sz_stream(const char* psz, const char * pszBegin) :
   m_psz(psz),
   m_pszBegin(!pszBegin ? psz : pszBegin)
{


}


inline read_sz_stream::~read_sz_stream()
{


}



