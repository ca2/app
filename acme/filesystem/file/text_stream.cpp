#include "framework.h"
#include "text_stream.h"
#include "acme/exception/exception.h"


string __string_image(const ::property_set & set)
{

   throw ::exception(todo);

}


text_stream::~text_stream()
{
   
   
}


string text_stream::read_string()
{

   string str;

   m_p->read_string(str);

   return str;

}



bool text_stream::is_stream_null()
{

   return !m_p;

}


void text_stream::destroy()
{

   m_p.release();

   ///* auto estatus = */ stream::destroy();

   /* return estatus; */

}


string text_stream::as_string() const
{
   
   return m_p->as_string();
   
}


bool text_stream::is_stream_set()
{

   return m_p;

}

text_stream & text_stream::operator >>(i8 & ch)
{

   m_gcount = m_p->read(&ch, 1);

   if (m_gcount <= 0)
   {

      throw ::exception(error_io);

   }

   return *this;

}


void text_stream::close()
{

   m_p->close();

}



text_stream & text_stream::operator <<(bool b)
{

   if (b)
   {

      raw_print("true");

   }
   else
   {

      raw_print("false");

   }

   return *this;

}


text_stream & text_stream::operator <<(char ch)
{

   m_p->write(&ch, sizeof(ch)); // treat as char - character

   return *this;

}


text_stream & text_stream::operator <<(uchar uch)
{

   operator <<((u32)uch);

   return *this;

}


text_stream & text_stream::operator <<(i16 i)
{

    operator <<((i32)i);

    return *this;

}


text_stream & text_stream::operator <<(u16 u)
{

   operator <<((u32)u);

   return *this;

}


#ifdef WINDOWS

text_stream & text_stream::operator <<(unichar wch)
{

   raw_print(::str().uni_to_utf8(wch));

   return *this;

}

#endif


void text_stream::print_number(const ::string & str)
{

   auto estrflag = this->m_estrflag;

   if (estrflag & str_flag_ifnumberparenthesize)
   {

      raw_print("(");

   }

   raw_print(str);

   if (estrflag & str_flag_ifnumberparenthesize)
   {

      raw_print(")");

   }

   if (estrflag & str_flag_ifnumberspace)
   {

      raw_print(" ");

   }

}


text_stream & text_stream::operator <<(i32 i)
{

   print_number(__string(i));

   return *this;

}


text_stream & text_stream::operator <<(u32 u)
{

   print_number(__string(u));

   return *this;

}


text_stream & text_stream::operator <<(i64 i)
{

   print_number(__string(i));

   return *this;

}


text_stream & text_stream::operator <<(u64 u)
{

   print_number(__string(u));

   return *this;

}


text_stream & text_stream::operator <<(float f)
{

   string str;

   str.format("%f", f);

   print_number(str);

   return *this;

}


text_stream & text_stream::operator <<(double d)
{

   string str;

   str.format("%f", d);

   print_number(__string(d));

   return *this;

}


//text_stream & text_stream::operator <<(const ::rectangle_i32 &rectangle)
//{
//
//   this->m_estrflag = (e_str_flag)((int)this->m_estrflag & ~(int)str_flag_ifnumberparenthesizeandspace);
//
//   *this << prectangle->left << prectangle->top << prectangle->right << prectangle->bottom;
//
//}
//
//
//text_stream & text_stream::operator <<(const SIZE_I32 * psize)
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
//text_stream & text_stream::operator <<(const POINT_I32 * ppoint)
//{
//
//   this->m_estrflag = (e_str_flag)((int)this->m_estrflag & ~(int)str_flag_ifnumberparenthesizeandspace);
//
//   *this << ppoint->x << ppoint->y;
//
//}



text_stream & text_stream::operator <<(const char * psz)
{

   if (::is_null(psz))
   {

      throw ::exception(error_io);

   }
   else
   {

      write(psz, strlen(psz));

   }

   return *this;

}


text_stream & text_stream::operator <<(const ::atom & atom)
{

   operator <<(atom.string());

   return *this;

}


text_stream & text_stream::operator <<(const ::string & str)
{

   operator <<(str.c_str());

   return *this;

}


text_stream & text_stream::operator <<(const property_set& set)
{

   operator << (__string_image(set));

   return *this;

}


void text_stream::raw_print(const ::string & str)
{

   write(str.c_str(), str.size());

   this->m_estrflag = (e_str_flag)((int)this->m_estrflag & ~(int)str_flag_ifnumberparenthesize);

}


text_stream & text_stream::operator >>(bool & b)
{

   m_p->read(&b, sizeof(b));

   return *this;

}

//
//text_stream & text_stream::operator >>(char & ch)
//{
//
//   return operator >>((char &)ch);
//
//}


text_stream & text_stream::operator >>(char & ch)
{

   m_gcount = m_p->read(&ch, sizeof(ch));

   if (m_gcount <= 0)
   {

      throw ::exception(error_io);

   }

   return *this;

}


text_stream & text_stream::operator >>(uchar & uch)
{

   m_p->read(&uch, sizeof(uch));

   return *this;
   
}


#ifdef WINDOWS


text_stream & text_stream::operator >>(unichar & wch)
{
   
   m_p->read(&wch, sizeof(wch));

   return *this;
   
}

#endif


text_stream & text_stream::operator >>(i16 & sh)
{
   
   m_p->read(&sh, sizeof(sh));

   return *this;

}


text_stream & text_stream::operator >>(u16 & u)
{
   
   m_p->read(&u, sizeof(u));

   return *this;

}


text_stream & text_stream::operator >>(i32 & i)
{
   
   number_read(i);

   return *this;

}


text_stream & text_stream::operator >>(u32 & u)
{

   number_read(u);

   return *this;

}


text_stream & text_stream::operator >>(i64 & i)
{

   number_read(i);

   return *this;

}


text_stream & text_stream::operator >>(u64 & u)
{
   
   number_read(u);

   return *this;

}


text_stream & text_stream::operator >>(float & f)
{
   
   number_read(f);

   return *this;

}


text_stream & text_stream::operator >>(double & d)
{
   
   number_read(d);

   return *this;

}

//text_stream & text_stream::operator >>(RECTANGLE_I32 * prectangle)
//
//{
//   m_p->read(&prectangle->left, sizeof(prectangle->left));
//
//   m_p->read(&prectangle->top, sizeof(prectangle->top));
//
//   m_p->read(&prectangle->right, sizeof(prectangle->right));
//
//   m_p->read(&prectangle->bottom, sizeof(prectangle->bottom));
//   
//}
//
//text_stream & text_stream::operator >>(SIZE_I32 * psize)
//{
//   m_p->read(&psize->cx, sizeof(psize->cx));
//   m_p->read(&psize->cy, sizeof(psize->cy));
//}
//
//text_stream & text_stream::operator >>(POINT_I32 * ppoint)
//{
//   m_p->read(&ppoint->x, sizeof(ppoint->x));
//   m_p->read(&ppoint->y, sizeof(ppoint->y));
//}


text_stream & text_stream::operator >>(string & str)
{

   str.Empty();

   char ch = 0;

   while(true)
   {

      operator >>(ch);

      if (ch == '\0')
      {

         break;

      }

      if (m_gcount <= 0)
      {

         break;

      }

      if (ch == '\n')
      {

         break;

      }

      str += ch;

   } 

   return *this;

}


text_stream & text_stream::operator >>(property_set& set)
{

   //__exchange_load_array(*this, set);
//#define memory_new ACME_NEW

   return *this;

}


text_stream & text_stream::operator >>(::atom & atom)
{

   string str;

   operator >> (str);

   atom = str;

   return *this;

}


string text_stream::get_location() const
{

   return "<unknown text_stream_base locationd>";

}


::filesize text_stream::get_position() const
{

   return m_p->get_position();

}


void text_stream::write(const void * psz, strsize s)
{

   m_p->write(psz, s);

}


//void text_stream::network_payload_write(const ::matter & matter)
//{
//
//   payload_stream s;
//
//   string strNetworkPayload;
//
//   s.set_storing();
//
//   ::__exchange(s, t);
//
//   strNetworkPayload = s.m_ppayload->get_network_payload();
//
//   string_write(strNetworkPayload);
//
//}
//
//
//void text_stream::network_payload_read(::matter & matter)
//{
//
//   payload_stream s;
//
//   string strNetworkPayload;
//
//   string_read(strNetworkPayload);
//
//   s.m_ppayload->parse_network_payload(strNetworkPayload);
//
//   s.set_loading();
//
//   ::__exchange(s, t);
//
//}



