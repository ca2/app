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

   ::id::e_type etype = id.m_etype;

   write(i8(etype));

   if(etype == ::id::type_text)
   {

      write(id.m_psz);

   }
   else if(etype == ::id::type_integer)
   {

      write(id.m_i);

   }

   return;

}


void binary_stream::write(const var & var)
{

   e_type etype = var.get_type();

   ::i32 i = etype;

   *this << i;

   switch (etype)
   {
   case type_parareturn:
   case type_new:
   case type_null:
   case type_key_exists:
   case type_empty:
   case type_empty_argument:
   case type_not_found:
      break;
   case type_string:
   {
      write(var.m_str);
   }
   break;
   case type_pstring:
   {
      write(*var.m_pstr);
   }
   break;
   case type_i8:
      *this << var.m_i8;
      break;
   case type_i16:
      *this << var.m_i16;
      break;
   case type_u8:
      *this << var.m_u8;
      break;
   case type_u16:
      *this << var.m_u16;
      break;
   case type_i32:
      *this << var.m_i32;
      break;
   case type_i64:
      *this << var.m_i64;
      break;
   case type_u32:
      *this << var.m_u32;
      break;
   case type_u64:
      *this << var.m_u64;
      break;
   case type_pi8:
      *this << *var.m_pi8;
      break;
   case type_pi16:
      *this << *var.m_pi16;
      break;
   case type_pu8:
      *this << *var.m_pu8;
      break;
   case type_pu16:
      *this << *var.m_pu16;
      break;
   case type_pi32:
      *this << *var.m_pi32;
      break;
   case type_pi64:
      *this << *var.m_pi64;
      break;
   case type_pu32:
      *this << *var.m_pu32;
      break;
   case type_pu64:
      *this << *var.m_pu64;
      break;
   case type_double:
      *this << var.m_d;
      break;
   case type_bool:
      *this << var.m_b;
      break;
   case type_inta:
      *this << var.inta();
      break;
   case type_memory:
      *this << *var.m_pmemory;
      break;
   case type_stra:
      *this << *var.m_pstra;
      break;
   case type_propset:
      *this << *var.m_pset;
      break;
   case type_i64a:
      *this << *var.m_pi64a;
      break;
   //case type_image:
   //   *this << *var.m_pimage;
   //   break;
   case type_id:
      *this << var.m_id;
      break;
   case type_element:
   case type_path:
   {

      __save_object(*this, var.cast < ::generic >());

   }
   break;
   default:
      write(var.m_all, sizeof(var.m_all));
      //__throw(::exception::exception("var::write var type not recognized"));
   }

   return;

}


void binary_stream::write(const property & property)
{

   write(property.m_id);
   write((const var &) property);

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


void binary_stream::write(const generic * pobject)
{

   pobject->write(*this);

   return;

}


void binary_stream::write(const generic& generic)
{

   generic.write(*this);

   return;

}


void binary_stream::write(const block & block)
{

   write_buffer_length(block.get_size());

   write(block.get_data(), block.get_size());

   return;

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

   ::id::e_type etype = (::id::e_type) 0;

   read((i8 &)etype);

   if (etype == ::id::type_text)
   {

      string str;

      read(str);

      id = str;

   }
   else if (etype == ::id::type_integer)
   {

      i64 i;

      read(i);

      id = i;

   }
   else if (etype == ::id::type_empty)
   {

      id = ::id::type_empty;

   }
   else
   {

      id = ::id::type_null;

   }

}



//void binary_stream::write_file(const ::file::path & path, const ::generic & generic)
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
//   ::efileopen nOpenFlags;
//
//   nOpenFlags = ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::mode_truncate | ::file::defer_create_directory | ::file::share_exclusive;
//
//   stream.m_pfile = Context.file().get_file(path, nOpenFlags);
//
//   generic.write(*this);
//
//   return;
//
//}
//
//
//void binary_stream::read_file(const ::file::path & path, ::generic & generic)
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
//   stream.m_pfile = Context.file().get_reader(path, ::file::share_deny_write);
//
//   generic.read(*this);
//
//   return;
//
//}


//void binary_stream::write_link(const string & strLink, const ::generic & generic)
//{
//
//   ::file::path path = get_link_path(generic);
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
//      write_file(path, generic);
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
//void binary_stream::read_link(const string & strLink, ::generic & generic)
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
//      read_file(path, generic);
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
//bool binary_stream::get_object_link(const ::generic & generic, string & strLink, bool & bLink)
//{
//
//   return false;
//
//}
//
//
//void binary_stream::set_object_link(const ::generic & generic, const string & strLink, bool bReadOnly)
//{
//
//}
//
//
//void binary_stream::write_link(const ::generic & generic)
//{
//
//   string strLink;
//
//   bool bReadOnly;
//
//   if (get_object_link(generic, strLink, bReadOnly))
//   {
//
//      write_link(generic, strLink, bReadOnly);
//
//   }
//
//   return;
//
//}
//
//
//void binary_stream::write_link(const ::generic & generic, const string & strLink, bool bReadOnly)
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
//      write_link(strLink, generic);
//
//   }
//
//   return;
//
//}
//
//void binary_stream::read_link(::generic & generic)
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
//   //   generic["read_only_link"] = strLink;
//
//   //}
//   //else
//   //{
//
//   //   generic["link"] = strLink;
//
//   //}
//
//   set_object_link(generic, strLink, bReadOnly);
//
//
//   if (strLink.has_char())
//   {
//
//      read_link(strLink, generic);
//
//   }
//
//   return;
//
//}


//bool binary_stream::get_object_link(const ::generic * preference, string & strLink, bool & bLink)
//{
//
//   return false;
//
//}


//void binary_stream::set_object_link(const ::generic * preference, const string & strLink, bool bReadOnly)
//{
//
//}


//bool binary_stream::write_link(const ::generic * pobject)
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


//void binary_stream::write_link(const ::generic * preference, const string & strLink, bool bReadOnly, ::generic * pobjectSaveOptions)
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


//void binary_stream::read_link(::generic * preference)
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
//   //   generic["read_only_link"] = strLink;
//
//   //}
//   //else
//   //{
//
//   //   generic["link"] = strLink;
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


void binary_stream::read(var & var)
{

   e_type etype = type_new;

   read_var_type(etype);
   
   return read_var_body(var, etype);

}


void binary_stream::read_var_type(e_type & etype)
{

   ::i32 i;

   *this >> i;

   if (!fail())
   {

      etype = (e_type)i;

   }

   return;

}

void binary_stream::save_var_type(e_type etype)
{

   ::i32 i((::i32) etype);

   *this << i;

   return;

}


void binary_stream::read_var_body(var & var, e_type etype)
{

   switch (etype)
   {
   case type_parareturn:
   case type_new:
   case type_null:
   case type_key_exists:
   case type_empty:
   case type_empty_argument:
   case type_not_found:
   {

      var.set_type(etype, false);

      break;

   }
   case type_pstring:
   case type_string:
   {

      var.set_type(type_string, false);

      read(var.m_str);

   }
   break;
   case type_pi32:
   case type_i32:
   {

      var.set_type(type_i32, false);

      *this >> var.m_i32;

   }
   break;
   case type_pi64:
   case type_i64:
   {

      var.set_type(type_i64, false);

      *this >> var.m_i64;

   }
   break;
   case type_pu32:
   case type_u32:
   {

      var.set_type(::type_u32, false);

      *this >> var.m_u32;

   }
   break;
   case type_pu64:
   case type_u64:
   {

      var.set_type(::type_u64, false);

      *this >> var.m_u64;

   }
   break;
   case type_bool:
   {

      var.set_type(::type_bool, false);

      *this >> var.m_b;

   }
   break;
   case type_double:
   {

      var.set_type(::type_double, false);

      *this >> var.m_d;

   }
   break;
   case type_float:
   {

      var.set_type(::type_float, false);

      *this >> var.m_d;

   }
   break;
   case type_inta:
   {

      __exchange_save_array(*this, var.inta());

   }
   break;
   case type_memory:
   {

      *this >> var.memory();

   }
   break;
   case type_stra:
   {

      __exchange_load_array(*this, var.stra());

   }
   break;
   case type_propset:
   {

      __exchange_load_array(*this, var.propset());

   }
   break;
   case type_id:
   {

      var.set_type(::type_id, false);

      *this >> var.m_id;

   }
   break;
   case type_element:
   case type_path:
   {

      var.set_element(::__load_object<::generic>(*this));

   }
   break;
   default:
   {
      var.set_type(etype, false);
      read(var.m_all, sizeof(var.m_all));
      //var.release();
      //setstate(::file::failbit); // stream corrupt
      break;
   }
   }

   return;

}


void binary_stream::read(property & property)
{

   read(property.m_id);
   read((var &) property);

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


void binary_stream::read(generic & generic)
{

   generic.read(*this);

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

   return m_p.is_null() || !(m_p->m_eopen & ::file::mode_read);

}




bool binary_stream::is_reader_set()
{

   return m_p.is_set() && (m_p->m_eopen & ::file::mode_read);

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
   memsize uiRead;
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

   while ((uiRead = read(&memory.get_data()[uiPos], MIN(memory.get_size() - uiPos, (memsize)nCount))) > 0)
   {
      uiPos += uiRead;
      nCount -= uiRead;
      if (memory.get_size() - uiPos <= 0)
      {
         memory.allocate_add_up(1024 * 1024);
      }
   }
   memory.set_size((memsize)uiPos);
   memory.to_hex(str);
}


//__pointer(::generic) binary_stream::create_object_from_text(string strText)
//{
//
//   if (strText.is_empty())
//   {
//
//      return nullptr;
//
//   }
//
//   auto id = text_to_factory_id(strText);
//
//   return get_context_object()->__id_create < ::generic >(id);
//
//}
//




