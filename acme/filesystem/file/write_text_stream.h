//
// Created by camilo on 23/12/2022. <3ThomasBorregaardSørensen!!
//
#pragma once


template < typename FILE >
class write_text_stream :
        public PARTICLE_FLAGS,
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


    void print(const ::scoped_string& str);
    void print(::ansi_character ansicharacter) { write(&ansicharacter, 1); }
    void print(::wd16_character wd16character) { char sz[8]; write(&sz, wd16_to_ansi(sz, &wd16character, 1)); }
    void print(::wd32_character wd32character) { char sz[8]; write(&sz, wd32_to_ansi(sz, &wd32character, 1)); }


    template < primitive_number NUMBER >
    void write_number(NUMBER number);

    template < primitive_number NUMBER >
    void write_number(NUMBER number, const ::ansi_character * pszFormat);

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

    void append_format(const ::ansi_character * pszFormat, ...);
//    {
//
//       ::string strText;
//
//       ASSERT(__is_valid_string(pszFormat));
//
//       va_list argList;
//
//       va_start(argList, pszFormat);
//
//       strText.format_arguments(pszFormat, argList);
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


    write_text_stream& operator <<(bool b);
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


    write_text_stream& operator <<(char ch);
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

    write_text_stream& operator <<(enum_start_reference);
//    {
//
//       return *this;
//
//    }


    write_text_stream& operator <<(uchar uch);
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


    write_text_stream& operator <<(unichar wch);
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
    write_text_stream& operator <<(SIGNED i);
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
    write_text_stream& operator <<(UNSIGNED u);
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
    void print_string_copy(const T& t);
//    {
//
//       ::string str;
//
//       ::copy(str, t);
//
//       print(str);
//
//    }

    write_text_stream& operator <<(integral_byte integralbyte);
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
    write_text_stream& operator <<(FLOATING f);
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

    // void write(const POINT_I32 & point) ;
    // void write(const SIZE_I32 & size) ;
    // void write(const ::rectangle_i32 &rectangle) ;

    write_text_stream& operator <<(const ::ansi_character * psz);
//    {
//
//       if (m_fmtflags & ::file::network_payload)
//       {
//
//          print("\"");
//
//       }
//
//       print(psz);
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

    write_text_stream & operator <<(const ::string & str);
//    {
//
//       return this->operator <<((const ::scoped_string &)str);
//
//    }

    //text_stream & operator <<(const ::atom & atom) ;
    write_text_stream& operator <<(const ::scoped_string & scopedstr);
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


    template < primitive_character CHARACTER2, strsize sizeMaximumLength >
    write_text_stream& operator <<(const ::inline_string < CHARACTER2, sizeMaximumLength > & inlinestring);
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
    //text_stream & operator <<(const property_set& set) ;
    template < typename TYPE >
    write_text_stream & write(const TYPE& t);
//    {
//
//       return *this << t;
//
//    }

    // void network_payload_write(const ::matter & matter);


    void raw_print(const ::string& str);
//    {
//
//       print(str);
//
//    }


    //void print_number(const ::string& str)
    //{

    //   print_number(str);

    //}

    //::string get_location() const;

    //::filesize get_position() const ;
    void write(const void* psz, strsize s);
//    {
//
//       m_pfile->write(psz, s);
//
//    }

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



