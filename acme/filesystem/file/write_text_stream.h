//
// Created by camilo on 23/12/2022. <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/filesystem/file/print_formatting.h"
#include "acme/prototype/prototype/pointer.h"
#include "acme/prototype/string/c/encoding.h"


struct CLASS_DECL_ACME write_text_stream_struct
{


   char                               m_chSeparator = ' ';
#ifdef WINDOWS
   const_char_pointer m_pszEolSeparator = "\r\n";
#else
   const_char_pointer m_pszEolSeparator = "\n";
#endif
   print_formatting * m_pprintingformat;

   write_text_stream_struct();
   write_text_stream_struct(const write_text_stream_struct & writetextstreamstruct) = default;
   write_text_stream_struct(write_text_stream_struct && writetextstreamstruct) = default;


   void set_width(int width) { m_pprintingformat->m_width = width; }

   void set_precision(int precision) { m_pprintingformat->m_precision = precision; }


};


class string_buffer_base;


//// template < typename FILE >
class CLASS_DECL_ACME write_text_stream :
   virtual public write_text_stream_struct
{
public:


   ::file_pointer             m_pfile;


   write_text_stream();
   write_text_stream(const ::file_pointer & pfile);
   write_text_stream(::file_pointer && pfile);
   write_text_stream(const write_text_stream & stream);
   write_text_stream(write_text_stream && stream);
   write_text_stream(const ::file_pointer & pfile, write_text_stream_struct && streamstruct);
   virtual ~write_text_stream();


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

   //   auto hn = strtoull(m_str, &endptr, 10);

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

   inline ::file::fmtflags & fmtflags() { return m_pprintingformat->m_fmtflags; }
   inline ::file::fmtflags fmtflags() const { return m_pprintingformat->m_fmtflags; }


   void print(const ::range < const ansi_character * > & str);
   void print(::ansi_character ansicharacter) { write(&ansicharacter, 1); }
   void print(::wd16_character wd16character) { char sz[8]; write((const_char_pointer )&sz, wd16_to_ansi(sz, &wd16character, 1)); }
   void print(::wd32_character wd32character) { char sz[8]; write((const_char_pointer )& sz, wd32_to_ansi(sz, &wd32character, 1)); }


   template < primitive_number NUMBER >
   void write_number(NUMBER number);

   template < primitive_number NUMBER >
   void write_number(NUMBER number, const_char_pointer pszFormat);

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

   void append_format(const_char_pointer pszFormat, ...);
   //    {
   //
   //       ::string strText;
   //
   //       ASSERT(is_string_ok(scopedstrFormat));
   //
   //       va_list argList;
   //
   //       va_start(argList, pszFormat);
   //
   //       strText.formatf_arguments(scopedstrFormat, argList);
   //
   //       va_end(argList);
   //
   //       print(strText);
   //
   //    }


       //bool is_stream_null();
       //bool is_stream_set();

       //void close() {}

   void new_line();
   //    {
   //
   //       if (m_fmtflags & ::file::separated)
   //       {
   //
   //          m_pfile->unget_if(m_chSeparator);
   //
   //       }
   //
   //       print(m_pszEolSeparator);
   //
   //    }


   write_text_stream & operator <<(::file::fmtflags e)
   {

      m_pprintingformat->set_format_flags(e);

      return *this;

   }


   write_text_stream & operator <<(bool b);
   //    {
   //
   //       if(b)
   //       {
   //
   //          print("1");
   //
   //       }
   //       else
   //       {
   //
   //          print("0");
   //
   //       }
   //
   //       if (m_fmtflags & ::file::separated)
   //       {
   //
   //          print(m_chSeparator);
   //
   //       }
   //
   //       return *this;
   //
   //    }


   write_text_stream & operator <<(char ch);
   //    {
   //
   //       write(&ch, 1);
   //
   //       if (m_fmtflags & ::file::separated)
   //       {
   //
   //          print(m_chSeparator);
   //
   //       }
   //
   //       return *this;
   //
   //    }

   write_text_stream & operator <<(enum_start_reference);
   //    {
   //
   //       return *this;
   //
   //    }


   write_text_stream & operator <<(uchar uch);
   //    {
   //
   //       write(&uch, 1);
   //
   //       if (m_fmtflags & ::file::separated)
   //       {
   //
   //          print(m_chSeparator);
   //
   //       }
   //
   //       return *this;
   //
   //    }


#ifdef WINDOWS


   write_text_stream & operator <<(unichar wch);
   //   {
   //
   //      char sz[10];
   //
   //      wd16_to_ansi(sz, &wch, 1);
   //
   //      print(sz);
   //
   //      if (m_fmtflags & ::file::separated)
   //      {
   //
   //         print(m_chSeparator);
   //
   //      }
   //
   //      return *this;
   //
   //   }


#endif

   template < primitive_signed_not_8bit SIGNED >
   write_text_stream & operator <<(SIGNED i);
   //    {
   //
   //       write_number(i);
   //
   //       if (m_fmtflags & ::file::separated)
   //       {
   //
   //          print(m_chSeparator);
   //
   //       }
   //
   //       return *this;
   //
   //    }


   template < primitive_unsigned_not_8bit UNSIGNED >
   write_text_stream & operator <<(UNSIGNED u);
   //    {
   //
   //       write_number(u);
   //
   //       if (m_fmtflags & ::file::separated)
   //       {
   //
   //          print(m_chSeparator);
   //
   //       }
   //
   //       return *this;
   //
   //    }

   template < typename T >
   void print_string_copy(const T & t);
   //    {
   //
   //       ::string str;
   //
   //       ::copy(str, t);
   //
   //       print(str);
   //
   //    }

   //    {
   //
   //       print_string_copy(integralbyte);
   //
   //       if (m_fmtflags & ::file::separated)
   //       {
   //
   //          print(m_chSeparator);
   //
   //       }
   //
   //       return *this;
   //
   //    }

       //write_text_stream& operator <<(int i)
       //{

       //   write_integer(i);

       //   print(m_chSeparator);

       //   return *this;

       //}


       //write_text_stream& operator <<(unsigned int u)
       //{

       //   write_natural(u);

       //   print(m_chSeparator);

       //   return *this;

       //}


       //write_text_stream& operator <<(long long i)
       //{

       //   write_integer(i);

       //   print(m_chSeparator);

       //   return *this;

       //}


       //write_text_stream& operator <<(unsigned long long u)
       //{

       //   write_natural(u);

       //   print(m_chSeparator);

       //   return *this;

       //}


   template < primitive_floating FLOATING >
   write_text_stream & operator <<(FLOATING f);
   //    {
   //
   //       write_number(f);
   //
   //       if (m_fmtflags & ::file::separated)
   //       {
   //
   //          print(m_chSeparator);
   //
   //       }
   //
   //       return *this;
   //
   //    }

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

       // void write(const ::int_point & point) ;
       // void write(const ::int_size & size) ;
       // void write(const ::int_rectangle &rectangle) ;

   write_text_stream & operator <<(const_char_pointer psz);
   //    {
   //
   //       if (m_fmtflags & ::file::network_payload)
   //       {
   //
   //          print("\"");
   //
   //       }
   //
   //       print(scopedstr);
   //
   //       if (m_fmtflags & ::file::network_payload)
   //       {
   //
   //          print("\"");
   //
   //       }
   //
   //       if (m_fmtflags & ::file::separated)
   //       {
   //
   //          print(m_chSeparator);
   //
   //       }
   //
   //       return *this;
   //
   //    }

   write_text_stream & operator <<(const ::range < const_char_pointer >& range);
   //    {
   //
   //       return this->operator <<((const ::scoped_string &)str);
   //
   //    }

       //text_stream & operator <<(const ::atom & atom) ;
   write_text_stream & operator <<(const ::scoped_string & scopedstr);
   //template < typename ITERATOR_TYPE2, int t_size>
   //write_text_stream& operator <<(const ::const_string_range_static_array < ITERATOR_TYPE2, t_size >& a)
   //{

   //   return this->operator <<((const ::string&)a);

   //}
   //    {
   //
   //       if (m_fmtflags & ::file::network_payload)
   //       {
   //
   //          print("\"");
   //
   //       }
   //
   //       print(scopedstr);
   //
   //       if (m_fmtflags & ::file::network_payload)
   //       {
   //
   //          print("\"");
   //
   //       }
   //
   //       if (m_fmtflags & ::file::separated)
   //       {
   //
   //          print(m_chSeparator);
   //
   //       }
   //
   //       return *this;
   //
   //    }


   template < primitive_character CHARACTER2, character_count sizeMaximumLength >
   write_text_stream & operator <<(const ::inline_string < CHARACTER2, sizeMaximumLength > & inlinestring);
   //    {
   //
   //       if (m_fmtflags & ::file::network_payload)
   //       {
   //
   //          print("\"");
   //
   //       }
   //
   //       write(inlinestring.data(), inlinestring.size());
   //
   //       if (m_fmtflags & ::file::network_payload)
   //       {
   //
   //          print("\"");
   //
   //       }
   //
   //       if (m_fmtflags & ::file::separated)
   //       {
   //
   //          print(m_chSeparator);
   //
   //       }
   //
   //       return *this;
   //
   //    }
       //text_stream & operator <<(const ::property_set & set) ;
   template < typename TYPE >
   write_text_stream & write(const TYPE & t);
   //    {
   //
   //       return *this << t;
   //
   //    }

       // void network_payload_write(const ::matter & matter);


   void raw_print(const ::scoped_string & scopedstr);
   //    {
   //
   //       print(str);
   //
   //    }


       //void print_number(const ::scoped_string & scopedstr)
       //{

       //   print_number(str);

       //}

       //::string get_location() const;

       //::filesize get_position() const ;
   void write(const void * psz, character_count s);

   //void print(const ::scoped_string & scopedstr);

//    {
//
//       m_pfile->write(scopedstr, s);
//
//    }

    //operator void* () { return this; }

//   text_stream& operator >>(bool& b);
//   text_stream& operator >>(char& ch);
//   text_stream& operator >>(uchar& uch);
//#ifdef WINDOWS
//   text_stream& operator >>(unichar& wch);
//#endif
//   text_stream& operator >>(char& i);
//   text_stream& operator >>(short& sh);
//   text_stream& operator >>(unsigned short& u);
//   text_stream& operator >>(int& i);
//   text_stream& operator >>(unsigned int& u);
//   text_stream& operator >>(long long& i);
//   text_stream& operator >>(unsigned long long& u);
//   text_stream& operator >>(float& f);
//   text_stream& operator >>(double& d);
//   text_stream& operator >>(string& str);
//   //text_stream & operator >>(::property_set & set) ;
//   //text_stream & operator >>(::atom & atom) ;
//
//   template < typename TYPE >
//   void network_payload_read(TYPE& matter);
//

};





template < primitive_number NUMBER >
inline void write_text_stream::write_number(NUMBER number)
{

   print(as_string(number));

}


template < primitive_number NUMBER >
inline void write_text_stream::write_number(NUMBER number, const_char_pointer pszFormat)
{

   print(as_string(number, pszFormat));

}


template < primitive_signed_not_8bit SIGNED >
inline write_text_stream & write_text_stream::operator <<(SIGNED i)
{

   write_number(i);

   if (this->fmtflags() & ::file::separated)
   {

      print(m_chSeparator);

   }

   return *this;

}


// // template < typename FILE >
template < primitive_unsigned_not_8bit UNSIGNED >
inline write_text_stream & write_text_stream::operator <<(UNSIGNED u)
{

   write_number(u);

   if (this->fmtflags() & ::file::separated)
   {

      print(m_chSeparator);

   }

   return *this;

}





// // template < typename FILE >
template < primitive_floating FLOATING >
inline write_text_stream & write_text_stream::operator <<(FLOATING f)
{

   string strFormat;

   strFormat.formatf("%%0%d.%df", m_pprintingformat->m_width, m_pprintingformat->m_precision);

   //   char szFormat[32];
   //
   //   snprintf(szFormat, sizeof(szFormat), );

   write_number(f, strFormat);

   if (this->fmtflags() & ::file::separated)
   {

      print(m_chSeparator);

   }

   return *this;

}





// // template < typename FILE >
template < typename TYPE >
inline write_text_stream & write_text_stream::write(const TYPE & t)
{

   return *this << t;

}
