#pragma once


#include "string_buffer.h"
#include "stream.h"





inline ::string ellipsis(const_char_pointer psz, character_count len);
inline unsigned long long consume_natural(const_char_pointer &psz, const_char_pointer pszBegin, int iRadix = 10);
inline long long consume_integer(const_char_pointer &psz, const_char_pointer pszBegin, int iRadix = 10);
inline double consume_floating(const_char_pointer &psz, const_char_pointer pszBegin, int iRadix = 10);


#include "write_text_stream.h"

#include "read_sz_stream.h"


//using std_string_stream = ::write_text_stream;


class CLASS_DECL_ACME string_reference_stream :
   public write_text_stream,
   public string_reference_buffer
{
public:


   string_reference_stream(::string& str) : string_reference_buffer(str) { m_pfile = this; }


};






//// template < typename FILE >
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


//// template < typename FILE >
//inline write_text_stream < FILE >::~write_text_stream()
//{
//
//
//}


//// template < typename FILE >
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


//// template < typename FILE >
//bool text_stream < FILE >::is_stream_null()
//{
//
//   return !m_pfile;
//
//}
//
//
//// template < typename FILE >
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


//// template < typename FILE >
//string text_stream < FILE >::as_string() const
//{
//
//   return m_pfile->as_string();
//
//}


//// template < typename FILE >
//bool text_stream < FILE >::is_stream_set()
//{
//
//   return m_pfile;
//
//}


//// template < typename FILE >
//text_stream < FILE>& text_stream < FILE >::operator >>(char& ch)
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


//// template < typename FILE >
//void text_stream < FILE >::close()
//{
//
//   m_pfile->close();
//
//}


//// template < typename FILE >
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
//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(char ch)
//{
//
//   m_pfile->write(&ch, sizeof(ch)); // treat as char - character
//
//   return *this;
//
//}


//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(uchar uch)
//{
//
//   operator <<((unsigned int)uch);
//
//   return *this;
//
//}
//
//
//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(short i)
//{
//
//   operator <<((int)i);
//
//   return *this;
//
//}
//
//
//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(unsigned short u)
//{
//
//   operator <<((unsigned int)u);
//
//   return *this;
//
//}
//
//
//#ifdef WINDOWS
//
//// template < typename FILE >
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
//// template < typename FILE >
//void text_stream < FILE >::print_number(const ::scoped_string & scopedstr)
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


//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(int i)
//{
//
//   print_number(as_string(i));
//
//   return *this;
//
//}
//
//
//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(unsigned int u)
//{
//
//   print_number(as_string(u));
//
//   return *this;
//
//}
//
//
//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(long long i)
//{
//
//   print_number(as_string(i));
//
//   return *this;
//
//}
//
//
//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(unsigned long long u)
//{
//
//   print_number(as_string(u));
//
//   return *this;
//
//}
//
//
//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(float f)
//{
//
//   string str;
//
//   str.formatf("%f", f);
//
//   print_number(str);
//
//   return *this;
//
//}
//
//
//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(double d)
//{
//
//   string str;
//
//   str.formatf("%f", d);
//
//   print_number(as_string(d));
//
//   return *this;
//
//}


//text_stream & text_stream < FILE >::operator <<(const ::int_rectangle &rectangle)
//{
//
//   this->m_estrflag = (e_str_flag)((int)this->m_estrflag & ~(int)str_flag_ifnumberparenthesizeandspace);
//
//   *this << prectangle->left() << prectangle->top() << prectangle->right() << prectangle->bottom();
//
//}
//
//
//text_stream & text_stream < FILE >::operator <<(const ::int_size * psize)
//{
//
//   this->m_estrflag = (e_str_flag)((int)this->m_estrflag & ~(int)str_flag_ifnumberparenthesizeandspace);
//
//   *this << psize->cx() << psize->cy();
//
//}
//
//
//
//text_stream & text_stream < FILE >::operator <<(const ::int_point * ppoint)
//{
//
//   this->m_estrflag = (e_str_flag)((int)this->m_estrflag & ~(int)str_flag_ifnumberparenthesizeandspace);
//
//   *this << ppoint->x << ppoint->y;
//
//}


//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(const_char_pointer psz)
//{
//
//   if (::is_null(scopedstr))
//   {
//
//      throw_exception(error_io);
//
//   }
//   else
//   {
//
//      write(scopedstr, strlen(scopedstr));
//
//   }
//
//   return *this;
//
//}
//
//
//
//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator <<(const ::scoped_string & scopedstr)
//{
//
//   operator <<(str.c_str());
//
//   return *this;
//
//}
//// template < typename FILE >
//void text_stream < FILE >::raw_print(const ::scoped_string & scopedstr)
//{
//
//   write(str.c_str(), str.size());
//
//   this->m_estrflag = (e_str_flag)((int)this->m_estrflag & ~(int)str_flag_ifnumberparenthesize);
//
//}
//
//
//// template < typename FILE >
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
//// template < typename FILE >
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
//// template < typename FILE >
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
//// template < typename FILE >
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
//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(short& sh)
//{
//
//   m_pfile->read(&sh, sizeof(sh));
//
//   return *this;
//
//}
//
//
//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(unsigned short& u)
//{
//
//   m_pfile->read(&u, sizeof(u));
//
//   return *this;
//
//}
//
//
//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(int& i)
//{
//
//   number_read(i);
//
//   return *this;
//
//}
//
//
//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(unsigned int& u)
//{
//
//   number_read(u);
//
//   return *this;
//
//}
//
//
//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(long long& i)
//{
//
//   number_read(i);
//
//   return *this;
//
//}
//
//
//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(unsigned long long& u)
//{
//
//   number_read(u);
//
//   return *this;
//
//}
//
//
//// template < typename FILE >
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
//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(double& d)
//{
//
//   number_read(d);
//
//   return *this;
//
//}
//
////text_stream & text_stream < FILE >::operator >>(::int_rectangle * prectangle)
////
////{
////   m_pfile->read(&prectangle->left(), sizeof(prectangle->left()));
////
////   m_pfile->read(&prectangle->top(), sizeof(prectangle->top()));
////
////   m_pfile->read(&prectangle->right(), sizeof(prectangle->right()));
////
////   m_pfile->read(&prectangle->bottom(), sizeof(prectangle->bottom()));
////   
////}
////
////text_stream & text_stream < FILE >::operator >>(::int_size * psize)
////{
////   m_pfile->read(&psize->cx(), sizeof(psize->cx()));
////   m_pfile->read(&psize->cy(), sizeof(psize->cy()));
////}
////
////text_stream & text_stream < FILE >::operator >>(::int_point * ppoint)
////{
////   m_pfile->read(&ppoint->x, sizeof(ppoint->x));
////   m_pfile->read(&ppoint->y, sizeof(ppoint->y));
////}
//
//
//// template < typename FILE >
//text_stream < FILE >& text_stream < FILE >::operator >>(string& str)
//{
//
//   str.empty();
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
////// template < typename FILE >
////text_stream < FILE > & text_stream < FILE >::operator >>(::property_set & set)
////{
////
////   //__exchange_load_array(*this, set);
////
////
////   return *this;
////
////}
//
//
////// template < typename FILE >
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
//// template < typename FILE >
//inline  string text_stream < FILE >::get_location() const
//{
//
//   return "<unknown text_stream_base locationd>";
//
//}
//
//
////// template < typename FILE >
////inline ::filesize text_stream < FILE >::get_position() const
////{
////
////   return m_pfile->get_position();
////
////}
//
//
//// template < typename FILE >
//inline void text_stream < FILE >::write(const void* psz, character_count s)
//{
//
//   m_pfile->write(scopedstr, s);
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
//// template < typename FILE >
//inline auto __write_text_stream(FILE* pfile)
//{
//
//   return write_text_stream < FILE >(pfile);
//
//}

//
//// template < typename FILE >
//inline auto __text_stream(const ::pointer<FILE>& pfile)
//{
//
//   return __text_stream(pfile.m_p);
//
//}


inline read_sz_stream::read_sz_stream(const_char_pointer psz, const_char_pointer pszBegin) :
   m_psz(psz),
   m_pszBegin(!pszBegin ? psz : pszBegin)
{


}


inline read_sz_stream::~read_sz_stream()
{


}



