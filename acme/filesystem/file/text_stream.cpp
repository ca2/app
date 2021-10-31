#include "framework.h"


text_stream::~text_stream()
{

}


bool text_stream::is_stream_null()
{

   return !m_p;

}


::e_status text_stream::destroy()
{

   m_p.release();

   auto estatus = stream::destroy();

   return estatus;

}


string text_stream::get_string() const
{
   
   return m_p->get_string();
   
}


bool text_stream::is_stream_set()
{

   return m_p;

}
//
//void text_stream::read(char & ch)
//{
//
//   m_gcount = m_p->read(&ch, 1);
//
//   if (m_gcount <= 0)
//   {
//
//      set_fail_bit();
//
//   }
//
//
//}


void text_stream::close()
{

   m_p->close();

}



void text_stream::write(bool b)
{

   if (b)
   {

      raw_print("true");

   }
   else
   {

      raw_print("false");

   }

}


void text_stream::write(char ch)
{

   m_p->write(&ch, sizeof(ch)); // treat as char - character

}


void text_stream::write(uchar uch)
{

   write((u32)uch);

}


void text_stream::write(i16 i)
{

    write((i32)i);

}


void text_stream::write(u16 u)
{

   write((u32)u);

}


#ifdef WINDOWS

void text_stream::write(unichar wch)
{

   raw_print(::str::uni_to_utf8(wch));

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


void text_stream::write(i32 i)
{

   print_number(__string(i));

}


void text_stream::write(u32 u)
{

   print_number(__string(u));

}


void text_stream::write(i64 i)
{

   print_number(__string(i));

}


void text_stream::write(u64 u)
{

   print_number(__string(u));

}


void text_stream::write(float f)
{

   string str;

   str.format("%f", f);

   print_number(str);

}


void text_stream::write(double d)
{

   string str;

   str.format("%f", d);

   print_number(__string(d));

}


//void text_stream::write(const RECTANGLE_I32 & rectangle)
//{
//
//   this->m_estrflag = (e_str_flag)((int)this->m_estrflag & ~(int)str_flag_ifnumberparenthesizeandspace);
//
//   *this << prectangle->left << prectangle->top << prectangle->right << prectangle->bottom;
//
//}
//
//
//void text_stream::write(const SIZE_I32 * psize)
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
//void text_stream::write(const POINT_I32 * ppoint)
//{
//
//   this->m_estrflag = (e_str_flag)((int)this->m_estrflag & ~(int)str_flag_ifnumberparenthesizeandspace);
//
//   *this << ppoint->x << ppoint->y;
//
//}



void text_stream::write(const char * psz)
{

   if (::is_null(psz))
   {

      this->set_fail_bit();

   }
   else
   {

      write(psz, strlen(psz));

   }

}


void text_stream::write(const ::id & id)
{

   write(id.to_string());

}


void text_stream::write(const ::string & str)
{

   write(str.c_str());

}


void text_stream::write(const property_set& set)
{

   __exchange_save_array(*this, set);

}

void text_stream::raw_print(const ::string & str)
{

   write(str.c_str(), str.size());

   this->m_estrflag = (e_str_flag)((int)this->m_estrflag & ~(int)str_flag_ifnumberparenthesize);

}


void text_stream::read(bool & b)
{

   m_p->read(&b, sizeof(b));

}


void text_stream::read(signed char & ch)
{

   return read((char &)ch);

}


void text_stream::read(char & ch)
{

   m_gcount = m_p->read(&ch, sizeof(ch));

   if (m_gcount <= 0)
   {

      set_fail_bit();

   }

}


void text_stream::read(uchar & uch)
{

   m_p->read(&uch, sizeof(uch));
   
}


#ifdef WINDOWS


void text_stream::read(unichar & wch)
{
   
   m_p->read(&wch, sizeof(wch));
   
}

#endif

void text_stream::read(i16 & sh)
{
   m_p->read(&sh, sizeof(sh));
}

void text_stream::read(u16 & u)
{
   m_p->read(&u, sizeof(u));
}

void text_stream::read(i32 & i)
{
   u64 uRead = m_p->read(&i, sizeof(i));
   if (uRead != sizeof(i))
      __throw(error_io, "failed to read i32");
}

void text_stream::read(u32 & u)
{
   u64 uRead = m_p->read(&u, sizeof(u));
   if (uRead != sizeof(u))
      __throw(error_io, "failed to read u32");
}


void text_stream::read(i64 & i)
{

   m_p->read(&i, sizeof(i));

}


void text_stream::read(u64 & u)
{
   m_p->read(&u, sizeof(u));
}

void text_stream::read(float & f)
{
   m_p->read(&f, sizeof(f));
}

void text_stream::read(double & d)
{
   m_p->read(&d, sizeof(d));
}

//void text_stream::read(RECTANGLE_I32 * prectangle)
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
//void text_stream::read(SIZE_I32 * psize)
//{
//   m_p->read(&psize->cx, sizeof(psize->cx));
//   m_p->read(&psize->cy, sizeof(psize->cy));
//}
//
//void text_stream::read(POINT_I32 * ppoint)
//{
//   m_p->read(&ppoint->x, sizeof(ppoint->x));
//   m_p->read(&ppoint->y, sizeof(ppoint->y));
//}


void text_stream::read(string & str)
{

   str.Empty();

   char ch = 0;

   while(true)
   {

      read(ch);

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

}


void text_stream::read(property_set& set)
{
#undef new
   __exchange_load_array(*this, set);
#define new ACME_NEW

}


void text_stream::read(::id & id)
{

   string str;

   read(str);


   id = str;


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
//   var_stream s;
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
//   var_stream s;
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



