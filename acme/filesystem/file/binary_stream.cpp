#include "framework.h"


binary_stream::~binary_stream()
{


}


string binary_stream::factory_id_to_text(const ::id & id)
{

   return id;

}


::id binary_stream::text_to_factory_id(string str)
{

   return str;

}


bool binary_stream::is_open() const
{

   if (m_p.is_null())
   {

      return false;

   }

   if (!m_p->is_opened())
   {

      return false;

   }

   return true;

}


void binary_stream::close()
{

   m_p.release();

}


::file::path binary_stream::get_file_path() const
{

   return m_p->get_file_path();

}


filesize binary_stream::seek(filesize offset, ::file::e_seek eseek)
{

   return m_p->seek(offset, eseek);

}




bool binary_stream::is_stream_null()
{
   //return is_writer_null() && is_reader_null();
   return m_p.is_null();
}


bool binary_stream::is_stream_set()
{
   //return is_writer_set() || is_reader_set();
   return m_p.is_set();
}


void binary_stream::write_from_hex(const void * pdata, memsize nCount)
{

   m_p->write_from_hex(pdata, nCount);


}



void binary_stream::write(const void * pdata, memsize nCount)
{

   m_p->write(pdata, nCount);

}



void binary_stream::write(const void * pdata, memsize nCount, memsize * dwWritten)
{

   m_p->write(pdata, nCount);

   if (dwWritten)
   {

      *dwWritten = nCount;

   }

}



void binary_stream::write(const id & id)
{

   raw_write(id.m_etype);

   if(id.m_etype == ::id::e_type_text)
   {

      write(id.m_psz);

   }
   else if(id.m_etype == ::id::e_type_integer)
   {

      write(id.m_i);

   }
   else if (id.m_etype >= ::id::e_type_property)
   {

      raw_write(id.m_eproperty);

   }
   else if (id.m_etype >= ::id::e_type_factory)
   {

      raw_write(id.m_efactory);

   }
   else if (id.m_etype >= ::id::e_type_thread_tool)
   {

      raw_write(id.m_ethreadtool);

   }

}


void binary_stream::write(const payload & payload)
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
      *this << *payload.m_pmemory;
      break;
   case e_type_stra:
      *this << *payload.m_pstra;
      break;
   case e_type_propset:
      *this << *payload.m_pset;
      break;
   case e_type_i64a:
      *this << *payload.m_pi64a;
      break;
   //case type_image:
   //   *this << *payload.m_pimage;
   //   break;
   case e_type_id:
      *this << payload.m_id;
      break;
   case e_type_element:
   case e_type_path:
   {

      __save_object(*this, payload.cast < ::matter >());

   }
   break;
   default:
      write(payload.m_all, sizeof(payload.m_all));
      //__throw(::exception::exception("payload::write payload type not recognized"));
   }

   return;

}


void binary_stream::write(const property & property)
{

   write(property.m_id);
   write((const payload &) property);

   return;

}


void binary_stream::write(const property_set& set)
{

   __exchange_save_array(*this, (property_set &) set);

   return;

}



void binary_stream::flush()
{

   if (m_p.is_set())
   {

      m_p->flush();

   }

}


bool binary_stream::is_writer_null()
{

   return m_p.is_null();

}


bool binary_stream::is_writer_set()
{

   return m_p.is_set();

}


void binary_stream::write(const ansichar * psz)
{

   auto len = ::str::string_safe_length(psz);

   write_buffer_length(len);

   write(psz, len);

   return;

}


void binary_stream::write(const string & str)
{

   write_buffer_length(str.get_length());

   write(str.c_str(), str.get_length());

   return;

}


void binary_stream::write(const matter * pobject)
{

   pobject->write(*this);

   return;

}


void binary_stream::write(const matter& matter)
{

   matter.write(*this);

   return;

}


void binary_stream::write(const block & block)
{

   write_buffer_length(block.get_size());

   write(block.get_data(), block.get_size());

}


void binary_stream::set_size(filesize len)
{

   m_p->set_size(len);

}


void binary_stream::put(char ch)
{

   write(ch);

   return;

}


void binary_stream::read(memory_base & m)
{

   ::u64 u = 0;

   read_length(u);

   m.set_size((memsize) u);

   read(m.get_data(), m.get_size());

}


void binary_stream::write(const memory_base & m)
{

   write_length(m.get_size());

   write(m.get_data(), m.get_size());

}


void binary_stream::read(id & id)
{

   raw_read(id.m_etype);

   if (id.m_etype == ::id::e_type_text)
   {

      string str;

      read(str);

      id = str;

   }
   else if (id.m_etype == ::id::e_type_integer)
   {

      i64 i;

      read(i);

      id = i;

   }
   else if (id.m_etype == ::id::e_type_property)
   {

      raw_read(id.m_eproperty);

   }
   else if (id.m_etype == ::id::e_type_factory)
   {

      raw_read(id.m_efactory);

   }
   else if (id.m_etype == ::id::e_type_thread_tool)
   {

      raw_read(id.m_ethreadtool);

   }

}



//void binary_stream::write_file(const ::file::path & path, const ::matter & matter)
//{
//
//   if (path.is_empty())
//   {
//
//      throw io_exception("link path is empty");
//
//   }
//
//   ::stream stream(e_create_new, get_object(), FIRST_VERSION);
//
//   ::file::e_open nOpenFlags;
//
//   nOpenFlags = ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_truncate | ::file::e_open_defer_create_directory | ::file::e_open_share_exclusive;
//
//   stream.m_pfile = Context.file().get_file(path, nOpenFlags);
//
//   matter.write(*this);
//
//   return;
//
//}
//
//
//void binary_stream::read_file(const ::file::path & path, ::matter & matter)
//{
//
//   if (path.is_empty())
//   {
//
//      throw io_exception("link path is empty");
//
//   }
//
//   ::stream stream(e_create_new, get_object(), FIRST_VERSION);
//
//   stream.m_pfile = Context.file().get_reader(path, ::file::e_open_share_deny_write);
//
//   matter.read(*this);
//
//   return;
//
//}


//void binary_stream::write_link(const string & strLink, const ::matter & matter)
//{
//
//   ::file::path path = get_link_path(matter);
//
//   if (path.is_empty())
//   {
//
//      set_fail_bit();
//
//      return;
//
//   }
//
//   try
//   {
//
//      write_file(path, matter);
//
//   }
//   catch (...)
//   {
//
//      set_fail_bit();
//
//   }
//
//   return;
//
//}
//
//
//void binary_stream::read_link(const string & strLink, ::matter & matter)
//{
//
//   ::file::path path = get_link_path(strLink);
//
//   if (path.is_empty())
//   {
//
//      set_fail_bit();
//
//      return;
//
//   }
//
//   try
//   {
//
//      read_file(path, matter);
//
//   }
//   catch (...)
//   {
//
//      set_fail_bit();
//
//   }
//
//   return;
//
//}
//
//
//bool binary_stream::get_object_link(const ::matter & matter, string & strLink, bool & bLink)
//{
//
//   return false;
//
//}
//
//
//void binary_stream::set_object_link(const ::matter & matter, const string & strLink, bool bReadOnly)
//{
//
//}
//
//
//void binary_stream::write_link(const ::matter & matter)
//{
//
//   string strLink;
//
//   bool bReadOnly;
//
//   if (get_object_link(matter, strLink, bReadOnly))
//   {
//
//      write_link(matter, strLink, bReadOnly);
//
//   }
//
//   return;
//
//}
//
//
//void binary_stream::write_link(const ::matter & matter, const string & strLink, bool bReadOnly)
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
//      write_link(strLink, matter);
//
//   }
//
//   return;
//
//}
//
//void binary_stream::read_link(::matter & matter)
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
//   set_object_link(matter, strLink, bReadOnly);
//
//
//   if (strLink.has_char())
//   {
//
//      read_link(strLink, matter);
//
//   }
//
//   return;
//
//}


//bool binary_stream::get_object_link(const ::matter * preference, string & strLink, bool & bLink)
//{
//
//   return false;
//
//}


//void binary_stream::set_object_link(const ::matter * preference, const string & strLink, bool bReadOnly)
//{
//
//}


//bool binary_stream::write_link(const ::matter * pobject)
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


//void binary_stream::write_link(const ::matter * preference, const string & strLink, bool bReadOnly, ::matter * pobjectSaveOptions)
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
//      Context.save_to_file(strLink, m_pvarOptions, preference);
//
//   }
//
//   return;
//
//}


//void binary_stream::read_link(::matter * preference)
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
//      Context.load_from_file(preference, strLink);
//
//   }
//
//   return;
//
//}


void binary_stream::read(payload & payload)
{

   enum_type etype = e_type_new;

   read_var_type(etype);
   
   return read_var_body(payload, etype);

}


void binary_stream::read_var_type(enum_type & etype)
{

   ::i32 i;

   *this >> i;

   if (!fail())
   {

      etype = (enum_type)i;

   }

   return;

}

void binary_stream::save_var_type(enum_type etype)
{

   ::i32 i((::i32) etype);

   *this << i;

   return;

}


void binary_stream::read_var_body(payload & payload, enum_type etype)
{

   switch (etype)
   {
   case e_type_parareturn:
   case e_type_new:
   case e_type_null:
   case e_type_key_exists:
   case e_type_empty:
   case e_type_empty_argument:
   case e_type_not_found:
   {

      payload.set_type(etype, false);

      break;

   }
   case e_type_pstring:
   case e_type_string:
   {

      payload.set_type(e_type_string, false);

      read(payload.m_str);

   }
   break;
   case e_type_pi32:
   case e_type_i32:
   {

      payload.set_type(e_type_i32, false);

      *this >> payload.m_i32;

   }
   break;
   case e_type_pi64:
   case e_type_i64:
   {

      payload.set_type(e_type_i64, false);

      *this >> payload.m_i64;

   }
   break;
   case e_type_pu32:
   case e_type_u32:
   {

      payload.set_type(::e_type_u32, false);

      *this >> payload.m_u32;

   }
   break;
   case e_type_pu64:
   case e_type_u64:
   {

      payload.set_type(::e_type_u64, false);

      *this >> payload.m_u64;

   }
   break;
   case e_type_bool:
   {

      payload.set_type(::e_type_bool, false);

      *this >> payload.m_b;

   }
   break;
   case e_type_double:
   {

      payload.set_type(::e_type_double, false);

      *this >> payload.m_d;

   }
   break;
   case e_type_float:
   {

      payload.set_type(::e_type_float, false);

      *this >> payload.m_d;

   }
   break;
   case e_type_inta:
   {

      __exchange_save_array(*this, payload.inta());

   }
   break;
   case e_type_memory:
   {

      *this >> payload.memory();

   }
   break;
   case e_type_stra:
   {

      __exchange_load_array(*this, payload.stra());

   }
   break;
   case e_type_propset:
   {

      __exchange_load_array(*this, payload.propset());

   }
   break;
   case e_type_id:
   {

      payload.set_type(::e_type_id, false);

      *this >> payload.m_id;

   }
   break;
   case e_type_element:
   case e_type_path:
   {

      payload.set_element(::__load_object<::matter>(*this));

   }
   break;
   default:
   {
      payload.set_type(etype, false);
      read(payload.m_all, sizeof(payload.m_all));
      //payload.release();
      //setstate(::file::failbit); // stream corrupt
      break;
   }
   }

   return;

}


void binary_stream::read(property & property)
{

   read(property.m_id);
   read((payload &) property);

   return;

}


void binary_stream::read(string & str)
{

   ::u64 u = 0;

   read_buffer_length(u);

   if (!fail() && u > 0)
   {

      auto psz = str.get_string_buffer((strsize) u);

      memsize s = str::char_length_to_byte_length(psz, (strsize)u);

      read(psz, s);

      str.release_string_buffer((strsize)u);

   }

   return;

}




filesize binary_stream::get_position()
{

   return m_p->get_position();

}


void binary_stream::read(matter & matter)
{

   matter.read(*this);

   return;

}


void binary_stream::read(property_set & set)
{

   __exchange_load_array(*this, set);

   return;

}


void binary_stream::read(block & block)
{

   u64 u = 0;

   read_buffer_length(u);

   if (u != block.get_size())
   {

      set_fail_bit();

      return;

   }

   m_p->read(block.get_data(), block.get_size());

}



void * binary_stream::get_internal_data()
{

   return m_p->get_internal_data();

}




memsize binary_stream::get_internal_data_size() const
{

   return m_p->get_internal_data_size();

}




bool binary_stream::set_internal_data_size(memsize c)
{

   return m_p->set_internal_data_size(c);

}




filesize binary_stream::get_position() const
{

   return m_p->get_position();

}




int binary_stream::get()
{

   return m_p->get();

}




int binary_stream::peek()
{

   return m_p->peek();

}




void binary_stream::getline(char * sz, strsize n)
{

   m_p->getline(sz, n);

   return;

}



//::memsize binary_stream::gcount()
//{
//
//   return m_p->gcount();
//
//}



filesize binary_stream::seek_from_begin(filesize position)
{

   return m_p->seek_from_begin(position);

}










::filesize binary_stream::get_left() const
{

   return m_p->get_left();

}




bool binary_stream::is_reader_null()
{

   return m_p.is_null() || !(m_p->m_eopen & ::file::e_open_read);

}




bool binary_stream::is_reader_set()
{

   return m_p.is_set() && (m_p->m_eopen & ::file::e_open_read);

}




void binary_stream::read_to_hex(string & str, filesize tickStart, filesize tickEnd)
{

   memory memory;

#if MEMDLEAK
   memory.m_strTag = "memory://member=stream::read_to_hex";
#endif

   if (tickStart == (filesize)-1)
   {

      tickStart = get_position();

   }
   else
   {
      m_p->seek_from_begin(tickStart);
   }
   memsize uiPos = 0;
   memsize uRead;
   memory.set_size(1024);

   strsize nCount;

   if (tickEnd == (filesize)-1)
   {

      nCount = ::numeric_info< strsize >::max();

   }
   else
   {

      nCount = (strsize)(tickEnd - tickStart);

   }

   while ((uRead = read(&memory.get_data()[uiPos], min(memory.get_size() - uiPos, (memsize)nCount))) > 0)
   {
      uiPos += uRead;
      nCount -= uRead;
      if (memory.get_size() - uiPos <= 0)
      {
         memory.allocate_add_up(1024 * 1024);
      }
   }
   memory.set_size((memsize)uiPos);
   memory.to_hex(str);
}


__pointer(::matter) binary_stream::create_object_from_text(string strText)
{

   if (strText.is_empty())
   {

      return nullptr;

   }

   auto id = text_to_factory_id(strText);

   return __id_create < ::matter >(id);

}





