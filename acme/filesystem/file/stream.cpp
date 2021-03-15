
#include "framework.h"
#include <stdio.h>
//#include "acme/xml/_.h"




::file::path stream::get_file_path() const
{

   return "";

}


void stream::add_exception(const ::exception::exception & exception)
{

   set_fail_bit();

}


void stream::on_catch_all_exception()
{

   set_fail_bit();

}


void stream::write_object(const ::id & id, ::matter * pobject)
{

   auto strId = factory_id_to_text(pobject->type_name());

   exchange(e_property_id, strId);

   pobject->exchange(*this);

}


__pointer(::matter) stream::read_object(const ::id & id)
{

   string strId;

   exchange(e_property_id, strId);

   auto pobject = create_object_from_text(strId);

   pobject->exchange(*this);

   return pobject;

}


bool stream::is_open() const
{

   return false;

}


bool stream::is_stream_null() const
{

   return true;

}


bool stream::is_stream_set() const
{

   return true;

}



void * stream::get_internal_data()
{

   return nullptr;

}


memsize stream::get_internal_data_size() const
{

   return 0;

}


bool stream::set_internal_data_size(memsize c)
{

   if (c != 0)
   {

      set_fail_bit();

      return false;

   }

   return true;

}
filesize stream::get_position() const
{

   return 0;

}


void stream::read(memory_base & m)
{


}


bool stream::is_reader_null() const
{

   return true;

}


bool stream::is_reader_set() const
{

   return false;

}


void stream::read_to_hex(string & str, filesize iStart, filesize iEnd)
{


}


void stream::write_from_hex(const void * pdata, memsize nCount)
{


}


void stream::write(const void * pdata, memsize nCount)
{


}


void stream::write(const void * pdata, memsize nCount, memsize * dwWritten)
{


}


bool stream::is_writer_null()
{

   return true;

}


bool stream::is_writer_set()
{

   return false;

}


void stream::flush()
{


}


void stream::set_length(filesize len)
{

   if (len != 0)
   {

      __throw(error_invalid_argument);

   }

}


//
//   if(m_pfile.is_null())
//      return false;
//
//   if(!m_pfile->is_open())
//      return false;
//
//   return true;
//
//}
//
//
//
////stream::stream()
////{
//
////}
//
//
////stream::stream(file * pfile):
////   m_pfile(pfile)
////{
//
////}
//
//
////   stream::stream(const stream & stream) :
////      stream(stream)
////   {
////
////   }
//
//
////stream::~stream()
////{
//
////}
//
//
////   void stream::operator = (const stream & stream)
////   {
////      istream::operator = (stream);
////      ostream::operator = (stream);
////      return;
////   }
//
//
void stream::close()
{
}
void stream::getline(char * sz, strsize n)
{

   if (n > 0)
   {

      set_fail_bit();

   }
  // m_pfile->getline(sz, n);

//   return;

}



//void static_debug_load_object()
//{
//
//   __pointer(::file::path_object) ppathobject;
//
//   memory_stream stream;
//
//   ::factory::load_object(stream, ppathobject);
//
//}





stream::~stream()
{

   close();

   if (m_pvarOptions)
   {

      ::acme::del(m_pvarOptions);

   }

}



string stream::factory_id_to_text(const ::id & id)
{

   return id.to_string();

}





::id stream::text_to_factory_id(string strType)
{

   return strType;

}


::file::fmtflags stream_meta::setf(::file::fmtflags flagsAdd)
{

   ::file::fmtflags fmtflagsOld = m_fmtflags;

   m_fmtflags = (::file::fmtflags) ((u32)m_fmtflags | (u32)flagsAdd);

   return fmtflagsOld;

}


::file::fmtflags stream_meta::setf(::file::fmtflags flagsAdd, ::file::fmtflags flagsRemove)
{

   ::file::fmtflags fmtflagsOld = m_fmtflags;

   m_fmtflags = (::file::fmtflags) (((u32)m_fmtflags | (u32)flagsAdd) & (~(u32)flagsRemove));

   return fmtflagsOld;

}





bool stream::is_version(index i)
{

   if (!m_pvarOptions)
   {

      return i <= 0;

   }

   return i <= options()["version"].i32();

}



void stream::write(const id & id)
{

   ::id::enum_type etype = id.m_etype;

   write(i8(etype));

   if (etype == ::id::e_type_text)
   {

      write(id.m_psz);

   }
   else if (etype == ::id::e_type_integer)
   {

      write(id.m_i);

   }

}


void stream::write(const ::payload & payload)
{

   enum_type etype = payload.get_type();

   ::i32 i = etype;

   *this << i;

   switch (etype)
   {
   case e_type_parareturn:
   case e_type_new:
   case e_type_null:
   case e_type_key_exists:
   case e_type_empty:
   case e_type_empty_argument:
   case e_type_not_found:
      break;
   case e_type_string:
   {
      write(payload.m_str);
   }
   break;
   case e_type_pstring:
   {
      write(*payload.m_pstr);
   }
   break;
   case e_type_i8:
      *this << payload.m_i8;
      break;
   case e_type_i16:
      *this << payload.m_i16;
      break;
   case e_type_u8:
      *this << payload.m_u8;
      break;
   case e_type_u16:
      *this << payload.m_u16;
      break;
   case e_type_i32:
      *this << payload.m_i32;
      break;
   case e_type_i64:
      *this << payload.m_i64;
      break;
   case e_type_u32:
      *this << payload.m_u32;
      break;
   case e_type_u64:
      *this << payload.m_u64;
      break;
   case e_type_pi8:
      *this << *payload.m_pi8;
      break;
   case e_type_pi16:
      *this << *payload.m_pi16;
      break;
   case e_type_pu8:
      *this << *payload.m_pu8;
      break;
   case e_type_pu16:
      *this << *payload.m_pu16;
      break;
   case e_type_pi32:
      *this << *payload.m_pi32;
      break;
   case e_type_pi64:
      *this << *payload.m_pi64;
      break;
   case e_type_pu32:
      *this << *payload.m_pu32;
      break;
   case e_type_pu64:
      *this << *payload.m_pu64;
      break;
   case e_type_double:
      *this << payload.m_d;
      break;
   case e_type_bool:
      *this << payload.m_b;
      break;
   case e_type_inta:
      *this << payload.inta();
      break;
   case e_type_memory:
      *this << payload.memory();
      break;
   case e_type_stra:
      *this << payload.stra();
      break;
   case e_type_propset:
      *this << payload.propset();
      break;
   case e_type_id:
      *this << payload.m_id;
      break;
   case e_type_element:
   case e_type_path:
   {

      __save_object(*this, payload.cast <::matter>());

   }
   break;
   default:
      __throw(::exception::exception("payload::write ::payload type not recognized"));
   }

}


void stream::write(const property & property)
{

   write(property.m_id);
   write((const ::payload &) property);

}






void stream::write(const ansichar * psz)
{

   auto len = ::str::string_safe_length(psz);

   write_buffer_length(len);

   write(psz, len);

}


void stream::write(const string & str)
{

   write_buffer_length(str.get_length());

   write(str.c_str(), str.get_length());

}


void stream::write(const ::matter * pobject)
{

   pobject->write(*this);

}


void stream::write(const ::matter & matter)
{

   matter.write(*this);

}



void stream::write(const ::property_set & set)
{

   set_fail_bit();

}

void stream::write(const block & block)
{

   write_buffer_length(block.get_size());

   write(block.get_data(), block.get_size());

}



void stream::put(char ch)
{

   write(ch);

}


void stream::write(const memory_base & m)
{

   write(m.get_data(), m.get_size());

}



//bool stream::get_object_link(const ::matter * preference, string & strLink, bool & bLink)
//{
//
//   return false;
//
//}
//
//
//void stream::set_object_link(const ::matter * preference, const string & strLink, bool bReadOnly)
//{
//
//}
//
//
//bool stream::write_link(const ::matter * pobject)
//{
//
//   string strLink;
//
//   bool bReadOnly;
//
//   if (!get_object_link(pobject, strLink, bReadOnly))
//   {
//
//      return false;
//
//   }
//
//   write_link(pobject, strLink, bReadOnly);
//
//   return true;
//
//}


//void stream::write_link(const ::matter * preference, const string & strLink, bool bReadOnly, ::matter * pobjectSaveOptions)
//{
//
//   write(bReadOnly);
//
//   write(strLink);
//
//   if (bReadOnly)
//   {
//
//      return;
//
//   }
//
//   if (strLink.has_char())
//   {
//
//      get_context()->save_to_file(strLink, m_pvarOptions, preference);
//
//   }
//
//   return;
//
//}
//
//
//void stream::read_link(::matter * preference)
//{
//
//   string strLink;
//
//   bool bReadOnly;
//
//   read(bReadOnly);
//
//   read(strLink);
//
//   //if (bReadOnly)
//   //{
//
//   //   matter["read_only_link"] = strLink;
//
//   //}
//   //else
//   //{
//
//   //   matter["link"] = strLink;
//
//   //}
//
//   set_object_link(preference, strLink, bReadOnly);
//
//   if (strLink.has_char())
//   {
//
//      get_context()->load_from_file(preference, strLink);
//
//   }
//
//   return;
//
//}


void stream::read(bool & b)
{

   set_fail_bit();

}


void stream::read(char & ch)
{

   set_fail_bit();

}


void stream::read(uchar & uch)
{

   set_fail_bit();

}


#ifdef WINDOWS
void stream::read(unichar & wch)
{

   set_fail_bit();

}



#endif
void stream::read(i8 & i)
{

   set_fail_bit();

}


void stream::read(i16 & i)
{

   set_fail_bit();

}


void stream::read(u16 & u)
{

   set_fail_bit();

}


void stream::read(i32 & i)
{

   set_fail_bit();

}


void stream::read(u32 & u)
{

   set_fail_bit();

}


void stream::read(i64 & i)
{

   set_fail_bit();

}


void stream::read(u64 & u)
{

   set_fail_bit();

}


#if defined(__APPLE__) || defined(ANDROID) || defined(WINDOWS) || defined(RASPBIAN)


void stream::read(long& l)
{

   set_fail_bit();

}


void stream::read(unsigned long & u)
{

   set_fail_bit();

}


#endif


void stream::read(float & f)
{

   set_fail_bit();

}


void stream::read(double & d)
{

   set_fail_bit();

}


//void stream::read(POINT_I32 & point)
//{
//
//   set_fail_bit();
//
//}
//
//
//void stream::read(SIZE_I32 & size)
//{
//
//   set_fail_bit();
//
//}
//
//
//void stream::read(RECTANGLE_I32 & rectangle)
//{
//
//   set_fail_bit();
//
//}


void stream::read(id & id)
{

   set_fail_bit();

}


void stream::read(::payload & payload)
{

   set_fail_bit();

}


void stream::read_var_type(enum_type & etype)
{

   set_fail_bit();

}


void stream::read_var_body(::payload & payload, enum_type etype)
{

   set_fail_bit();

}


void stream::read(property & property)
{

   set_fail_bit();

}


void stream::read(string & str)
{

   set_fail_bit();

}


void stream::read(::matter& matter)
{

   set_fail_bit();


}


void stream::read(::property_set& set)
{

   set_fail_bit();

}



void stream::read(block & block)
{

   set_fail_bit();

}



void stream::save_var_type(enum_type etype)
{

   ::i32 i((::i32) etype);

   *this << i;

   return;

}


::payload & stream::options()
{

   if (!m_pvarOptions)
   {

      m_pvarOptions = new ::payload();

   }

   return *m_pvarOptions;

}


__pointer(::matter) stream::create_object_from_text(string strText)
{

   if (strText.is_empty())
   {

      return nullptr;

   }

   auto id = text_to_factory_id(strText);

   return __id_create < ::matter >(id);

}


void stream::exchange(const ::id & id, const char * psz)
{

   if(is_loading())
   {

      __throw(error_io);

   }
   else
   {

      write(string(psz));

   }

}


#ifdef WINDOWS


void stream::exchange(const ::id & id, const unichar * wch)
{

   if(is_loading())
   {

      __throw(error_io);

   }
   else
   {

      write(string(wch));

   }

}


#endif


void stream::exchange(const ::id & id, ::id & idExchange)
{

   stream_exchange(id, idExchange);

}


void stream::exchange(const ::id & id, ::payload & payload)
{

   stream_exchange(id, payload);

}


void stream::exchange(const ::id & id, property & property)
{

  stream_exchange(id, property);

}


void stream::exchange(const ::id & id, string & str)
{

   stream_exchange(id, str);

}


void stream::exchange(const ::id & id, ::matter * pobject)
{

   pobject->exchange(*this);

}


void stream::exchange(const ::id & id, ::matter & matter)
{

   matter.exchange(*this);

}


void stream::exchange(const ::id & id, property_set & set)
{

   stream_exchange(id, set);

}


void stream::exchange(const ::id & id, block & block)
{

   stream_exchange(id, block);

}



