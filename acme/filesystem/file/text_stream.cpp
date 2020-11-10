#include "framework.h"


text_stream::~text_stream()
{

}


bool text_stream::is_stream_null()
{

   return !m_p;

}


void text_stream::finalize()
{

   m_p.release();

   stream::finalize();

}



void text_stream::to_string(const class string_exchange & str) const
{
   
   m_p->to_string(str);
   
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


void text_stream::write(u16 ui)
{

   write((u32)ui);

}


#ifdef WINDOWS

void text_stream::write(unichar wch)
{

   raw_print(::str::uni_to_utf8(wch));

}

#endif


void text_stream::print_number(const string & str)
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

   print_number(__str(i));

}


void text_stream::write(u32 ui)
{

   print_number(__str(ui));

}


void text_stream::write(i64 i)
{

   print_number(__str(i));

}


void text_stream::write(u64 ui)
{

   print_number(__str(ui));

}


void text_stream::write(float f)
{

   string str;

   str.Format("%f", f);

   print_number(str);

}


void text_stream::write(double d)
{

   string str;

   str.Format("%f", d);

   print_number(__str(d));

}


//void text_stream::write(const RECT32 & rect)
//{
//
//   this->m_estrflag = (e_str_flag)((int)this->m_estrflag & ~(int)str_flag_ifnumberparenthesizeandspace);
//
//   *this << prect->left << prect->top << prect->right << prect->bottom;
//
//}
//
//
//void text_stream::write(const SIZE32 * psize)
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
//void text_stream::write(const POINT32 * ppoint)
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

void text_stream::raw_print(const string & str)
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

void text_stream::read(u16 & ui)
{
   m_p->read(&ui, sizeof(ui));
}

void text_stream::read(i32 & i)
{
   u64 uiRead = m_p->read(&i, sizeof(i));
   if (uiRead != sizeof(i))
      __throw(::exception::exception("failed to read i32"));
}

void text_stream::read(u32 & ui)
{
   u64 uiRead = m_p->read(&ui, sizeof(ui));
   if (uiRead != sizeof(ui))
      __throw(::exception::exception("failed to read u32"));
}

void text_stream::read(i64 & i)
{
   m_p->read(&i, sizeof(i));
}

void text_stream::read(u64 & ui)
{
   m_p->read(&ui, sizeof(ui));
}

void text_stream::read(float & f)
{
   m_p->read(&f, sizeof(f));
}

void text_stream::read(double & d)
{
   m_p->read(&d, sizeof(d));
}

//void text_stream::read(RECT32 * prect)
//
//{
//   m_p->read(&prect->left, sizeof(prect->left));
//
//   m_p->read(&prect->top, sizeof(prect->top));
//
//   m_p->read(&prect->right, sizeof(prect->right));
//
//   m_p->read(&prect->bottom, sizeof(prect->bottom));
//   
//}
//
//void text_stream::read(SIZE32 * psize)
//{
//   m_p->read(&psize->cx, sizeof(psize->cx));
//   m_p->read(&psize->cy, sizeof(psize->cy));
//}
//
//void text_stream::read(POINT32 * ppoint)
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

   __exchange_load_array(*this, set);

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


//void text_stream::json_write(const ::matter & matter)
//{
//
//   var_stream s;
//
//   string strJson;
//
//   s.set_storing();
//
//   ::__exchange(s, t);
//
//   strJson = s.m_pvar->get_json();
//
//   string_write(strJson);
//
//}
//
//
//void text_stream::json_read(::matter & matter)
//{
//
//   var_stream s;
//
//   string strJson;
//
//   string_read(strJson);
//
//   s.m_pvar->parse_json(strJson);
//
//   s.set_loading();
//
//   ::__exchange(s, t);
//
//}



