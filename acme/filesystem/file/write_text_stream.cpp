// Created by camilo on 2023-06-14 18:06 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "string_buffer.h"
#include "write_text_stream.h"
#include "acme/parallelization/task.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"


write_text_stream_struct::write_text_stream_struct()
{

   auto pcontext = ::get_task();

   if (!pcontext)
   {

      pcontext = ::system()->application();

   }

   m_pprintingformat = pcontext;

}


// // template < typename FILE >
write_text_stream::write_text_stream()
{


}


// // template < typename FILE >
write_text_stream::write_text_stream(const ::file_pointer & pfile) :
   m_pfile(pfile)
{

   //set_ok_flag();

   //if (pfile->has_storing_flag())
   //{

   //   defer_set_storing_flag();

   //}

}


write_text_stream::write_text_stream(::file_pointer && pfile) :
   m_pfile(::transfer(pfile))
{

}


write_text_stream::write_text_stream(const write_text_stream & stream) :
   write_text_stream_struct(stream)
{

   m_pfile = stream.m_pfile;

}


write_text_stream::write_text_stream(write_text_stream && stream) :
   write_text_stream_struct(::transfer(stream)),
   m_pfile(::transfer(stream.m_pfile))
{


}



//// // template < typename FILE >
//write_text_stream write_text_stream(const write_text_stream& stream) = delete;


write_text_stream::write_text_stream(const ::file_pointer & pfile, write_text_stream_struct && streamstruct) :
   write_text_stream_struct(streamstruct) 
{

   m_pfile.reset(pfile);

}


// // template < typename FILE >
write_text_stream::~write_text_stream()
{

   m_pfile.release();

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

//// // template < typename FILE >
//void write_text_stream::print(const ::scoped_string & scopedstr)
//{
//
//   m_pfile->write(str.c_str(), str.length_in_bytes());
//
//}

// // template < typename FILE >

// // template < typename FILE >

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

// // template < typename FILE >
void write_text_stream::append_format(const_char_pointer pszFormat, ...)
{

   ::string strText;

   ASSERT(is_string_ok(pszFormat));

   va_list argList;

   va_start(argList, pszFormat);

   strText.formatf_arguments(pszFormat, argList);

   va_end(argList);

   print(strText);

}


//bool is_stream_null();
//bool is_stream_set();

//void close() {}


// // template < typename FILE >
void write_text_stream::new_line()
{

   if (this->fmtflags() & ::file::separated)
   {

      m_pfile->unget_if(m_chSeparator);

   }

   print(m_pszEolSeparator);

}


// // template < typename FILE >
write_text_stream & write_text_stream::operator <<(bool b)
{

   if (b)
   {

      print("1"_ansi);

   }
   else
   {

      print("0"_ansi);

   }

   if (this->fmtflags() & ::file::separated)
   {

      print(m_chSeparator);

   }

   return *this;

}


// // template < typename FILE >
write_text_stream & write_text_stream::operator <<(char ch)
{

   write(&ch, 1);

   if (this->fmtflags() & ::file::separated)
   {

      print(m_chSeparator);

   }

   return *this;

}


// // template < typename FILE >
write_text_stream & write_text_stream::operator <<(enum_start_reference)
{

   return *this;

}


// // template < typename FILE >
write_text_stream & write_text_stream::operator <<(uchar uch)
{

   write(&uch, 1);

   if (this->fmtflags() & ::file::separated)
   {

      print(m_chSeparator);

   }

   return *this;

}


#ifdef WINDOWS


// // template < typename FILE >
write_text_stream & write_text_stream::operator <<(unichar wch)
{

   char sz[10];

   wd16_to_ansi(sz, &wch, 1);

   print(as_range(sz));

   if (this->fmtflags() & ::file::separated)
   {

      print(m_chSeparator);

   }

   return *this;

}


#endif


// // template < typename FILE >

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


// // template < typename FILE >
write_text_stream & write_text_stream::operator <<(const_char_pointer psz)
{

   if (this->fmtflags() & ::file::network_payload)
   {

      print("\""_ansi);

   }

   print(psz);

   if (this->fmtflags() & ::file::network_payload)
   {

      print("\""_ansi);

   }

   if (this->fmtflags() & ::file::separated)
   {

      print(m_chSeparator);

   }

   return *this;

}


// // template < typename FILE >
write_text_stream & write_text_stream::operator <<(const ::range < const_char_pointer >& range)
{

   this->write(range.data(), range.size());

   return *this;

}

//text_stream & operator <<(const ::atom & atom) ;
// // template < typename FILE >
write_text_stream & write_text_stream::operator <<(const ::scoped_string & scopedstr)
{

   if (this->fmtflags() & ::file::network_payload)
   {

      print("\""_ansi);

   }

   print(scopedstr);

   if (this->fmtflags() & ::file::network_payload)
   {

      print("\""_ansi);

   }

   if (this->fmtflags() & ::file::separated)
   {

      print(m_chSeparator);

   }

   return *this;

}




//text_stream & operator <<(const ::property_set & set) ;



// void network_payload_write(const ::matter & matter);


// // template < typename FILE >
void write_text_stream::raw_print(const ::scoped_string & scopedstr)
{

   print(scopedstr);

}


//void print_number(const ::scoped_string & scopedstr)
//{

//   print_number(str);

//}

//::string get_location() const;

//::filesize get_position() const ;
// // template < typename FILE >
void write_text_stream::write(const void * psz, character_count s)
{

   m_pfile->write({psz, s});

}


void write_text_stream::print(const ::range < const_char_pointer >& range)
{

   m_pfile->write(range.data(), range.size());

}

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

//};


//// // template < typename FILE >
//write_text_stream & write_text_stream::operator <<(const_char_pointer psz)
//{
//
//   if (this->fmtflags() & ::file::network_payload)
//   {
//
//      print("\"");
//
//   }
//
//   print(scopedstr);
//
//   if (this->fmtflags() & ::file::network_payload)
//   {
//
//      print("\"");
//
//   }
//
//   if (this->fmtflags() & ::file::separated)
//   {
//
//      print(m_chSeparator);
//
//   }
//
//   return *this;
//
//}


//// // template < typename FILE >
//write_text_stream & write_text_stream::operator <<(const ::scoped_string & scopedstr)
//{
//
//   return this->operator <<((const ::scoped_string &)str);
//
//}


// // template < typename FILE >
//void write_text_stream::print(const ::scoped_string & str)
//{
//
//   m_pfile->write(str.as_block());
//
//}

//
//// // template < typename FILE >
//write_text_stream & write_text_stream::operator <<(const ::scoped_string & scopedstr)
//{
//
//   if (this->fmtflags() & ::file::network_payload)
//   {
//
//      print("\"");
//
//   }
//
//   print(scopedstr);
//
//   if (this->fmtflags() & ::file::network_payload)
//   {
//
//      print("\"");
//
//   }
//
//   if (this->fmtflags() & ::file::separated)
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
//// // template < typename FILE >
//template < primitive_character CHARACTER2, character_count sizeMaximumLength >
//write_text_stream & write_text_stream::operator <<(const ::inline_string < CHARACTER2, sizeMaximumLength > & inlinestring)
//{
//
//   if (this->fmtflags() & ::file::network_payload)
//   {
//
//      print("\"");
//
//   }
//
//   write(inlinestring.data(), inlinestring.size());
//
//   if (this->fmtflags() & ::file::network_payload)
//   {
//
//      print("\"");
//
//   }
//
//   if (this->fmtflags() & ::file::separated)
//   {
//
//      print(m_chSeparator);
//
//   }
//
//   return *this;
//
//}
////text_stream & operator <<(const ::property_set & set) ;
//// // template < typename FILE >
//write_text_stream & write_text_stream::write(const TYPE& t)
//{
//
//   return *this << t;
//
//}
//
//// void network_payload_write(const ::matter & matter);
//
//// // template < typename FILE >
//void write_text_stream::raw_print(const ::scoped_string & scopedstr)
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
