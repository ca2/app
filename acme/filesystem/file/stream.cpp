#include "framework.h"
#include <stdio.h>
//#include "stream.h"


bool  stream_base::is_version(int i)
{

   return i == 0;

}
//::file::path stream::get_file_path() const
//{
//
//   return "";
//
//}


//void stream::add_exception(const ::exception & exception)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void stream::on_catch_all_exception()
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void binary_stream::write_element(const ::atom & atom, ::particle * pparticle)
//{
//
//   auto strId = factory_id_to_text(::type(pelement).name());
//
//   exchange(e_property_id, strId);
//
//   pelement->exchange(*this);
//
//}
//
//
//::pointer<::element>binary_stream::read_element(const ::atom & atom)
//{
//
//   string strId;
//
//   exchange(e_property_id, strId);
//
//   auto pparticle = create_object_from_text(strId);
//
//   pparticle->exchange(*this);
//
//   return pparticle;
//
//}
//
//
//bool stream::is_open() const
//{
//
//   return false;
//
//}
//
//
//bool stream::is_stream_null() const
//{
//
//   return true;
//
//}
//
//
//bool stream::is_stream_set() const
//{
//
//   return true;
//
//}
//
//
//
//void * stream::get_internal_data()
//{
//
//   return nullptr;
//
//}
//
//
//memsize stream::get_internal_data_size() const
//{
//
//   return 0;
//
//}
//
//
//bool stream::set_internal_data_size(memsize c)
//{
//
//   if (c != 0)
//   {
//
//      throw ::exception(error_io);
//
//      return false;
//
//   }
//
//   return true;
//
//}
//filesize stream::get_position() const
//{
//
//   return 0;
//
//}
//
//
//void stream::read(memory_base & m)
//{
//
//
//}
//
//
//bool stream::is_reader_null() const
//{
//
//   return true;
//
//}
//
//
//bool stream::is_reader_set() const
//{
//
//   return false;
//
//}
//
//
//void stream::read_to_hex(string & str, filesize iStart, filesize iEnd)
//{
//
//
//}
//
//
//void stream::write_from_hex(const void * pdata, memsize nCount)
//{
//
//
//}
//
//
//void stream::write(const void * pdata, memsize nCount)
//{
//
//
//}
//
//
//void stream::write(const void * pdata, memsize nCount, memsize * dwWritten)
//{
//
//
//}
//
//
//bool stream::is_writer_null()
//{
//
//   return true;
//
//}
//
//
//bool stream::is_writer_set()
//{
//
//   return false;
//
//}
//
//
//void stream::flush()
//{
//
//
//}
//
//
//void stream::set_length(filesize len)
//{
//
//   if (len != 0)
//   {
//
//      throw ::exception(error_bad_argument);
//
//   }
//
//}
//
//
////
////   if(m_pfile.is_null())
////      return false;
////
////   if(!m_pfile->is_open())
////      return false;
////
////   return true;
////
////}
////
////
////
//////stream::stream()
//////{
////
//////}
////
////
//////stream::stream(file * pfile):
//////   m_pfile(pfile)
//////{
////
//////}
////
////
//////   stream::stream(const stream & stream) :
//////      stream(stream)
//////   {
//////
//////   }
////
////
//////stream::~stream()
//////{
////
//////}
////
////
//////   void stream::operator = (const stream & stream)
//////   {
//////      istream::operator = (stream);
//////      ostream::operator = (stream);
//////      return;
//////   }
////
////
//void stream::close()
//{
//}
//void stream::getline(char * sz, character_count n)
//{
//
//   if (n > 0)
//   {
//
//      throw ::exception(error_io);
//
//   }
//  // m_pfile->getline(sz, n);
//
////   return;
//
//}
//
//
//
////void static_debug_load_object()
////{
////
////   ::pointer<::file::path_object>ppathobject;
////
////   memory_stream stream;
////
////   ::factory_item::load_object(stream, ppathobject);
////
////}
//
//
//
//
//
//stream::~stream()
//{
//
//   close();
//
//   if (m_pvarOptions)
//   {
//
//      ::acme::del(m_pvarOptions);
//
//   }
//
//}
//
//
//string stream::factory_id_to_text(const ::atom & atom)
//{
//
//   return atom.as_string();
//
//}
//
//
//::atom stream::text_to_factory_id(string strType)
//{
//
//   return strType;
//
//}
//
//
//::file::fmtflags stream_meta::setf(::file::fmtflags flagsAdd)
//{
//
//   ::file::fmtflags fmtflagsOld = m_fmtflags;
//
//   m_fmtflags = (::file::fmtflags) ((unsigned int)m_fmtflags | (unsigned int)flagsAdd);
//
//   return fmtflagsOld;
//
//}
//
//
//::file::fmtflags stream_meta::setf(::file::fmtflags flagsAdd, ::file::fmtflags flagsRemove)
//{
//
//   ::file::fmtflags fmtflagsOld = m_fmtflags;
//
//   m_fmtflags = (::file::fmtflags) (((unsigned int)m_fmtflags | (unsigned int)flagsAdd) & (~(unsigned int)flagsRemove));
//
//   return fmtflagsOld;
//
//}
//
//
//
//
//



//void stream::write(const atom & atom)
//{
//
//   ::atom::enum_type etype = atom.m_etype;
//
//   write(char(etype));
//
//   if (etype == ::atom::e_type_text)
//   {
//
//      write(atom.m_psz);
//
//   }
//   else if (etype == ::atom::e_type_integer)
//   {
//
//      write(atom.m_i);
//
//   }
//
//}
//
//
//void stream::write(const ::payload & payload)
//{
//
//   enum_type etype = payload.get_type();
//
//   int i = etype;
//
//   *this << i;
//
//   switch (etype)
//   {
//   case e_type_parareturn:
//   case e_type_new:
//   case e_type_null:
//   case e_type_key_exists:
//   case e_type_empty:
//   case e_type_empty_argument:
//   case e_type_not_found:
//      break;
//   case e_type_string:
//   {
//      write(payload.m_str);
//   }
//   break;
//   case e_type_pstring:
//   {
//      write(*payload.m_pstr);
//   }
//   break;
//   case e_type_char:
//      *this << payload.m_ch;
//      break;
//   case e_type_short:
//      *this << payload.m_sh;
//      break;
//   case e_type_unsigned_char:
//      *this << payload.m_uch;
//      break;
//   case e_type_unsigned_short:
//      *this << payload.m_ush;
//      break;
//   case e_type_int:
//      *this << payload.m_i;
//      break;
//   case e_type_huge_integer:
//      *this << payload.m_hi;
//      break;
//   case e_type_unsigned_int:
//      *this << payload.m_ui;
//      break;
//   case e_type_huge_natural:
//      *this << payload.m_hn;
//      break;
//   case e_type_pchar:
//      *this << *payload.m_pch;
//      break;
//   case e_type_pshort:
//      *this << *payload.m_psh;
//      break;
//   case e_type_punsigned_char:
//      *this << *payload.m_puch;
//      break;
//   case e_type_punsigned_short:
//      *this << *payload.m_push;
//      break;
//   case e_type_pint:
//      *this << *payload.m_pi;
//      break;
//   case e_type_pi64:
//      *this << *payload.m_pi64;
//      break;
//   case e_type_punsigned_int:
//      *this << *payload.m_pui;
//      break;
//   case e_type_pu64:
//      *this << *payload.m_pu64;
//      break;
//   case e_type_double:
//      *this << payload.m_d;
//      break;
//   case e_type_bool:
//      *this << payload.m_b;
//      break;
//   case e_type_int_array:
//      *this << payload.ia();
//      break;
//   case e_type_memory:
//      *this << payload.memory();
//      break;
//   case e_type_string_array:
//      *this << payload.stra();
//      break;
//   case e_type_property_set:
//      *this << payload.propset();
//      break;
//   case e_type_atom:
//      *this << payload.m_atom;
//      break;
//   case e_type_element:
//   case e_type_path:
//   {
//
//      __save_object(*this, payload.cast <::matter>());
//
//   }
//   break;
//   default:
//      throw ::exception(error_io, "payload::write ::payload type not recognized");
//   }
//
//}
//
//
//void stream::write(const property & property)
//{
//
//   write(property.m_atom);
//   write((const ::payload &) property);
//
//}
//
//
//
//
//
//
//void stream::write(const ::ansi_character * psz)
//{
//
//   auto len = ::str::string_safe_length(psz);
//
//   write_buffer_length(len);
//
//   write(psz, len);
//
//}
//
//
//void stream::write(const ::string & str)
//{
//
//   write_buffer_length(str.length());
//
//   write(str.c_str(), str.length());
//
//}
//
//
//void stream::write(const ::particle * pparticle)
//{
//
//   pparticle->write(*this);
//
//}
//
//
//void stream::write(const ::matter & matter)
//{
//
//   matter.write(*this);
//
//}
//
//
//
//void stream::write(const ::property_set & set)
//{
//
//   throw ::exception(error_io);
//
//}
//
//void stream::write(const block & block)
//{
//
//   write_buffer_length(block.get_size());
//
//   write(block.get_data(), block.get_size());
//
//}
//
//
//
//void stream::put(char ch)
//{
//
//   write(ch);
//
//}
//
//
//void stream::write(const memory_base & m)
//{
//
//   write(m.get_data(), m.get_size());
//
//}
//
//
//
////bool stream::get_object_link(const ::matter * preference, string & strLink, bool & bLink)
////{
////
////   return false;
////
////}
////
////
////void stream::set_object_link(const ::matter * preference, const ::string & strLink, bool bReadOnly)
////{
////
////}
////
////
////bool stream::write_link(const ::particle * pparticle)
////{
////
////   string strLink;
////
////   bool bReadOnly;
////
////   if (!get_object_link(pparticle, strLink, bReadOnly))
////   {
////
////      return false;
////
////   }
////
////   write_link(pparticle, strLink, bReadOnly);
////
////   return true;
////
////}
//
//
////void stream::write_link(const ::matter * preference, const ::string & strLink, bool bReadOnly, ::matter * pobjectSaveOptions)
////{
////
////   write(bReadOnly);
////
////   write(strLink);
////
////   if (bReadOnly)
////   {
////
////      return;
////
////   }
////
////   if (strLink.has_character())
////   {
////
////      m_papplication->save_to_file(strLink, m_pvarOptions, preference);
////
////   }
////
////   return;
////
////}
////
////
////void stream::read_link(::matter * preference)
////{
////
////   string strLink;
////
////   bool bReadOnly;
////
////   read(bReadOnly);
////
////   read(strLink);
////
////   //if (bReadOnly)
////   //{
////
////   //   matter["read_only_link"] = strLink;
////
////   //}
////   //else
////   //{
////
////   //   matter["link"] = strLink;
////
////   //}
////
////   set_object_link(preference, strLink, bReadOnly);
////
////   if (strLink.has_character())
////   {
////
////      m_papplication->load_from_file(preference, strLink);
////
////   }
////
////   return;
////
////}
//
//
//void stream::read(bool & b)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void stream::read(char & ch)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void stream::read(uchar & uch)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//#ifdef WINDOWS
//void stream::read(unichar & wch)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//
//#endif
//void stream::read(char & i)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void stream::read(short & i)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void stream::read(unsigned short & u)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void stream::read(int & i)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void stream::read(unsigned int & u)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void stream::read(huge_integer & i)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void stream::read(huge_natural & u)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//#if defined(__APPLE__) || defined(ANDROID) || defined(WINDOWS) || defined(RASPBERRYPIOS)
//
//
//void stream::read(long& l)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void stream::read(unsigned long & u)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//#endif
//
//
//void stream::read(float & f)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void stream::read(double & d)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
////void stream::read(::int_point & point)
////{
////
////   throw ::exception(error_io);
////
////}
////
////
////void stream::read(::int_size & size)
////{
////
////   throw ::exception(error_io);
////
////}
////
////
////void stream::read(::int_rectangle & rectangle)
////{
////
////   throw ::exception(error_io);
////
////}
//
//
//void stream::read(atom & atom)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void stream::read(::payload & payload)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void stream::read_var_type(enum_type & etype)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void stream::read_var_body(::payload & payload, enum_type etype)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void stream::read(property & property)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void stream::read(string & str)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//void stream::read(::matter& matter)
//{
//
//   throw ::exception(error_io);
//
//
//}
//
//
//void stream::read(::property_set& set)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//
//void stream::read(block & block)
//{
//
//   throw ::exception(error_io);
//
//}
//
//
//
//void stream::save_var_type(enum_type etype)
//{
//
//   int i((int) etype);
//
//   *this << i;
//
//   return;
//
//}
//
//
//::payload & stream::options()
//{
//
//   if (!m_pvarOptions)
//   {
//
//      m_pvarOptions = __allocate ::payload();
//
//   }
//
//   return *m_pvarOptions;
//
//}
//
//
//::pointer<::matter>stream::create_object_from_text(string strText)
//{
//
//   if (strText.is_empty())
//   {
//
//      return nullptr;
//
//   }
//
//   auto atom = text_to_factory_id(strText);
//
//   return __id_create < ::matter >(atom);
//
//}
//
//
//void stream::exchange(const ::atom & atom, const ::scoped_string & scopedstr)
//{
//
//   if(is_loading())
//   {
//
//      throw ::exception(error_io);
//
//   }
//   else
//   {
//
//      write(string(psz));
//
//   }
//
//}
//
//
//#ifdef WINDOWS
//
//
//void stream::exchange(const ::atom & atom, const unichar * wch)
//{
//
//   if(is_loading())
//   {
//
//      throw ::exception(error_io);
//
//   }
//   else
//   {
//
//      write(string(wch));
//
//   }
//
//}
//
//
//#endif
//
//
//void stream::exchange(const ::atom & atom, ::atom & idExchange)
//{
//
//   stream_exchange(atom, idExchange);
//
//}
//
//
//void stream::exchange(const ::atom & atom, ::payload & payload)
//{
//
//   stream_exchange(atom, payload);
//
//}
//
//
//void stream::exchange(const ::atom & atom, property & property)
//{
//
//  stream_exchange(atom, property);
//
//}
//
//
//void stream::exchange(const ::atom & atom, string & str)
//{
//
//   stream_exchange(atom, str);
//
//}
//
//
//void stream::exchange(const ::atom & atom, ::particle * pparticle)
//{
//
//   pparticle->exchange(*this);
//
//}
//
//
//void stream::exchange(const ::atom & atom, ::matter & matter)
//{
//
//   matter.exchange(*this);
//
//}
//
//
//void stream::exchange(const ::atom & atom, property_set & set)
//{
//
//   stream_exchange(atom, set);
//
//}
//
//
//void stream::exchange(const ::atom & atom, block & block)
//{
//
//   stream_exchange(atom, block);
//
//}
//
//
//


//filesize stream_base::precision(char prec)
//{
//
//   return m_precision = prec;
//
//}
//
//
//filesize stream_base::width() const
//{
//
//   return m_width;
//
//}
//
//filesize stream_base::width(char prec)
//{
//
//   return m_width = prec;
//
//}
//
//
//filesize stream_base::precision() const
//{
//
//   return m_precision;
//
//}
//
