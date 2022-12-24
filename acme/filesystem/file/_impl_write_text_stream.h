//
// Created by camilo on 23/12/22.
//
#pragma once




//    public PARTICLE_FLAGS,
//        public print_formatting
//{
//public:


//    FILE *         m_pfile;
//    char           m_chSeparator = ' ';
//#ifdef WINDOWS
//    const char* m_pszEolSeparator = "\r\n";
//#else
//    const char* m_pszEolSeparator = "\n";
//#endif

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
//write_text_stream < FILE > write_text_stream(const write_text_stream& stream) = delete;

template < typename FILE >
write_text_stream < FILE >::~write_text_stream()
{


}


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

//template < typename FILE >
//void write_text_stream < FILE >::print(const ::string& str)
//{
//
//   m_pfile->write(str.c_str(), str.length_in_bytes());
//
//}

template < typename FILE >
template < primitive_number NUMBER >
void write_text_stream < FILE >::write_number(NUMBER number)
{

   print(as_string(number));

}


template < typename FILE >
template < primitive_number NUMBER >
void write_text_stream < FILE >::write_number(NUMBER number, const ::ansi_character * pszFormat)
{

   print(as_string(number, pszFormat));

}

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

 template < typename FILE >
 void write_text_stream < FILE >::append_format(const ::ansi_character * pszFormat, ...)
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


template < typename FILE >
void write_text_stream < FILE >::new_line()
{

   if (m_fmtflags & ::file::separated)
   {

      m_pfile->unget_if(m_chSeparator);

   }

   print(m_pszEolSeparator);

}


template < typename FILE >
write_text_stream < FILE > & write_text_stream < FILE >::operator <<(bool b)
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


template < typename FILE >
write_text_stream < FILE > & write_text_stream < FILE >::operator <<(char ch)
{

   write(&ch, 1);

   if (m_fmtflags & ::file::separated)
   {

      print(m_chSeparator);

   }

   return *this;

}


template < typename FILE >
write_text_stream < FILE > & write_text_stream < FILE >::operator <<(enum_start_reference)
{

   return *this;

}


template < typename FILE >
write_text_stream < FILE > & write_text_stream < FILE >::operator <<(uchar uch)
{

   write(&uch, 1);

   if (m_fmtflags & ::file::separated)
   {

      print(m_chSeparator);

   }

   return *this;

}


#ifdef WINDOWS


template < typename FILE >
write_text_stream < FILE > & write_text_stream < FILE >::operator <<(unichar wch)
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


template < typename FILE >
template < primitive_signed_not_8bit SIGNED >
write_text_stream < FILE > & write_text_stream < FILE >::operator <<(SIGNED i)
{

   write_number(i);

   if (m_fmtflags & ::file::separated)
   {

      print(m_chSeparator);

   }

   return *this;

}


template < typename FILE >
template < primitive_unsigned_not_8bit UNSIGNED >
write_text_stream < FILE > & write_text_stream < FILE >::operator <<(UNSIGNED u)
{

   write_number(u);

   if (m_fmtflags & ::file::separated)
   {

      print(m_chSeparator);

   }

   return *this;

}


template < typename FILE >
template < typename T >
void write_text_stream < FILE >::print_string_copy(const T& t)
{

   ::string str;

   ::copy(str, t);

   print(str);

}


template < typename FILE >
write_text_stream < FILE > & write_text_stream < FILE >::operator <<(integral_byte integralbyte)
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


template < typename FILE >
template < primitive_floating FLOATING >
write_text_stream < FILE > & write_text_stream < FILE >::operator <<(FLOATING f)
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


template < typename FILE >
write_text_stream < FILE > & write_text_stream < FILE >::operator <<(const ::ansi_character * psz)
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


template < typename FILE >
write_text_stream < FILE > & write_text_stream < FILE >::operator <<(const ::string & str)
    {

       return this->operator <<((const ::scoped_string &)str);

    }

    //text_stream & operator <<(const ::atom & atom) ;
    template < typename FILE >
    write_text_stream < FILE > & write_text_stream < FILE >::operator <<(const ::scoped_string & scopedstr)
    {

       if (m_fmtflags & ::file::network_payload)
       {

          print("\"");

       }

       print(scopedstr);

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


    template < typename FILE >
    template < primitive_character CHARACTER2, strsize sizeMaximumLength >
    write_text_stream < FILE > & write_text_stream < FILE >::operator <<(const ::inline_string < CHARACTER2, sizeMaximumLength > & inlinestring)
    {

       if (m_fmtflags & ::file::network_payload)
       {

          print("\"");

       }

       write(inlinestring.data(), inlinestring.size());

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


   template < typename FILE >
    template < typename TYPE >
    write_text_stream < FILE > & write_text_stream < FILE >::write(const TYPE& t)
    {

       return *this << t;

    }

    // void network_payload_write(const ::matter & matter);


template < typename FILE >
void write_text_stream < FILE >::raw_print(const ::string& str)
    {

       print(str);

    }


    //void print_number(const ::string& str)
    //{

    //   print_number(str);

    //}

    //::string get_location() const;

    //::filesize get_position() const ;
    template < typename FILE >
    void write_text_stream < FILE >::write(const void* psz, strsize s)
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

//};


//template < typename FILE >
//write_text_stream < FILE > & write_text_stream < FILE >::operator <<(const ::ansi_character * psz)
//{
//
//   if (m_fmtflags & ::file::network_payload)
//   {
//
//      print("\"");
//
//   }
//
//   print(psz);
//
//   if (m_fmtflags & ::file::network_payload)
//   {
//
//      print("\"");
//
//   }
//
//   if (m_fmtflags & ::file::separated)
//   {
//
//      print(m_chSeparator);
//
//   }
//
//   return *this;
//
//}


//template < typename FILE >
//write_text_stream < FILE > & write_text_stream < FILE >::operator <<(const ::string & str)
//{
//
//   return this->operator <<((const ::scoped_string &)str);
//
//}


template < typename FILE >
void write_text_stream < FILE >::print(const ::scoped_string& str)
{

   m_pfile->write(str.c_str(), str.length_in_bytes());

}

//
//template < typename FILE >
//write_text_stream < FILE > & write_text_stream < FILE >::operator <<(const ::scoped_string & scopedstr)
//{
//
//   if (m_fmtflags & ::file::network_payload)
//   {
//
//      print("\"");
//
//   }
//
//   print(scopedstr);
//
//   if (m_fmtflags & ::file::network_payload)
//   {
//
//      print("\"");
//
//   }
//
//   if (m_fmtflags & ::file::separated)
//   {
//
//      print(m_chSeparator);
//
//   }
//
//   return *this;
//
//}
//
//
//template < typename FILE >
//template < primitive_character CHARACTER2, strsize sizeMaximumLength >
//write_text_stream < FILE > & write_text_stream < FILE >::operator <<(const ::inline_string < CHARACTER2, sizeMaximumLength > & inlinestring)
//{
//
//   if (m_fmtflags & ::file::network_payload)
//   {
//
//      print("\"");
//
//   }
//
//   write(inlinestring.data(), inlinestring.size());
//
//   if (m_fmtflags & ::file::network_payload)
//   {
//
//      print("\"");
//
//   }
//
//   if (m_fmtflags & ::file::separated)
//   {
//
//      print(m_chSeparator);
//
//   }
//
//   return *this;
//
//}
////text_stream & operator <<(const property_set& set) ;
//template < typename FILE >
//write_text_stream < FILE > & write_text_stream < FILE >::write(const TYPE& t)
//{
//
//   return *this << t;
//
//}
//
//// void network_payload_write(const ::matter & matter);
//
//template < typename FILE >
//void write_text_stream < FILE >::raw_print(const ::string& str)
//{
//
//   print(str);
//
//}
//
//
////#include "_impl_write_text_stream.h"
//
//
//
//
//
