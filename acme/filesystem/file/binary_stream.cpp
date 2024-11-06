// Refactoring by camilo on 2023-07-06 08:08 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "binary_stream.h"


binary_stream::binary_stream() 
{
   
}

binary_stream::binary_stream(const ::file_pointer & pfile) :
   m_pfile(pfile)
{

   initialize(pfile);

   set_ok_flag();

   if (pfile->has_storing_flag())
   {

      defer_set_storing_flag();

   }

}


//binary_stream(const stream_base & stream) 
//{ 
//   
//   m_pfile = dynamic_cast < FILE * >(((stream_base &) stream).get_file());

//   if (!m_pfile)
//   {

//      throw ::exception(error_wrong_type);

//   }

//   if (stream.nok())
//   {
//      set_nok();
//   }
//   else
//   {

//      set_ok_flag();

//   }

//   if (stream.has_storing_flag())
//   {

//      defer_set_storing_flag();

//   }
//}
binary_stream::~binary_stream()
{



}



bool binary_stream::is_end_of_file() const 
{
   
   return m_pfile->is_end_of_file(); 

}


::payload & binary_stream::options()
{

   return m_payloadOptions;

}


::u64 binary_stream::read_buffer_length()
{

   auto i = m_pfile->get_u8();

   if (i < 0)
   {

      set_nok();

      return 0;

   }
   else if (i < 255)
   {

      return i;

   }
   else
   {

      i = m_pfile->get_u16();

      if (i < 0)
      {

         set_nok();

         return 0;

      }
      else if (i < 65535)
      {

         return i;

      }
      else
      {

         ::u64 u64;

         if (!m_pfile->get_u64(u64))
         {

            set_nok();

            return 0;

         }

         return u64;

      }

   }

}





string binary_stream::factory_id_to_text(const ::atom & atom)
{

   return atom.as_string();

}


::atom binary_stream::text_to_factory_id(const ::string & str)
{

   return str;

}


void binary_stream::write_from_hex(const void * pdata, memsize nCount)
{

   m_pfile->write_from_hex({ pdata, nCount });

}



void binary_stream::write(const ::block & block)
{

   m_pfile->write(block);

}


memsize binary_stream::defer_write(const ::block & block)
{

   return m_pfile->defer_write(block);


}


binary_stream & operator <<(binary_stream & stream, const atom & atom)
{

   stream.raw_write(atom.m_etype);

   if (atom.m_etype & ::atom::e_type_text)
   {

      stream << atom.m_str;

   }
   else
   {

      stream << atom.m_iLargest;

   }

   return stream;

}


binary_stream & operator <<(binary_stream&stream, const ::payload & payload)
{

   enum_type etype = payload.get_type();

   int i = etype;

   stream << i;

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
      stream <<(payload.m_str);
   }
   break;
   case e_type_pstring:
   {
      stream <<(*payload.m_pstr);
   }
   break;
   case e_type_i8:
      stream << payload.m_i8;
      break;
   case e_type_i16:
      stream << payload.m_i16;
      break;
   case e_type_u8:
      stream << payload.m_u8;
      break;
   case e_type_u16:
      stream << payload.m_u16;
      break;
   case e_type_i32:
      stream << payload.m_i32;
      break;
   case e_type_i64:
      stream << payload.m_i64;
      break;
   case e_type_u32:
      stream << payload.m_u32;
      break;
   case e_type_u64:
      stream << payload.m_u64;
      break;
   case e_type_pi8:
      stream << *payload.m_pi8;
      break;
   case e_type_pi16:
      stream << *payload.m_pi16;
      break;
   case e_type_pu8:
      stream << *payload.m_pu8;
      break;
   case e_type_pu16:
      stream << *payload.m_pu16;
      break;
   case e_type_pi32:
      stream << *payload.m_pi32;
      break;
   case e_type_pi64:
      stream << *payload.m_pi64;
      break;
   case e_type_pu32:
      stream << *payload.m_pu32;
      break;
   case e_type_pu64:
      stream << *payload.m_pu64;
      break;
   case e_type_f64:
      stream << payload.m_f64;
      break;
   case e_type_bool:
      stream << payload.m_b;
      break;
   case e_type_int_array:
      throw ::exception(todo);
      //*this << payload.ia();
      break;
   case e_type_memory:
      throw ::exception(todo);
      //*this << *payload.m_pfilememory;
      break;
   case e_type_string_array:
      //*this << *payload.m_pfilestra;
      throw ::exception(todo);
      break;
   case e_type_property_set:
      //*this << *payload.m_pfilepropertyset;
      throw ::exception(todo);
      break;
   case e_type_i64_array:
      //*this << *payload.m_pfilei64a;
      throw ::exception(todo);
      break;
      //case type_image:
      //   *this << *payload.m_pfileimage;
      //   break;
   case e_type_atom:
      stream << payload.m_atom;
      break;
   //case e_type_property:
   //{
   //   stream.write_particle(payload.m_pproperty);

   //}
      break;
   case e_type_element:
   case e_type_path:
   {

      stream.write_particle(payload.m_p);

   }
   break;
   default:
      stream.write(::block(e_as_block, payload.m_payloadall));
      //throw ::exception(::exception("payload::write ::payload type not recognized"));
   }

   return stream;

}

//
//binary_stream & operator <<(binary_stream&stream,const property & property)
//{
//
//   stream <<(property.m_atom);
//   stream <<((const ::payload &)property);
//
//   return stream;
//
//}
//
//

binary_stream & binary_stream::operator <<(const ::ansi_character * psz)
{

   auto len = string_safe_length(psz);

   write_buffer_length(len);

   write({ psz, len });

   return *this;

}




binary_stream & binary_stream::operator <<(const ::string & str)
{

   write_buffer_length(str.length());

   write(str.as_block());

   return *this;

}

binary_stream & binary_stream::operator <<(const block & block)
{

   write_buffer_length(block.size());

   write(block);

   return *this;

}



binary_stream & binary_stream::operator >>(memory_base & m)
{

   ::u64 u = 0;

   read_length(u);

   m.set_size((memsize)u);

   read(m);

   return *this;

}


binary_stream & binary_stream::operator <<(const memory_base & m)
{

   write_length(m.size());

   write(m);

   return *this;

}


binary_stream & binary_stream::operator >>(atom & atom)
{

   raw_read(atom.m_etype);

   if (atom.m_etype & ::atom::e_type_text)
   {

      string str;

      operator >>(str);

      atom.m_str =  str;

   }
   else
   {

      i64 i;

      operator >>(i);

      atom.m_iLargest = i;

   }
//   else if (atom.m_etype == ::atom::e_type_property)
//   {
//
//      raw_read(atom.m_eproperty);
//
//   }
//   else if (atom.m_etype == ::atom::e_type_factory)
//   {
//
//      raw_read(atom.m_efactory);
//
//   }
//   else if (atom.m_etype == ::atom::e_type_task_tool)
//   {
//
//      raw_read(atom.m_etasktool);
//
//   }

   return *this;

}




binary_stream & operator >>(binary_stream & stream, ::payload & payload)
{

   enum_type etype = e_type_new;

   stream.read_payload_type(etype);

   stream.read_payload_body(payload, etype);

   return stream;

}


void binary_stream::read_payload_type(enum_type & etype)
{

   int i;

   *this >> i;

   //if (!fail())
   //{

   etype = (enum_type)i;

   //}

   return;

}

void binary_stream::save_payload_type(enum_type etype)
{

   int i((int)etype);

   *this << i;

   return;

}


void binary_stream::read_payload_body(::payload & payload, enum_type etype)
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

      operator >>(payload.m_str);

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
   case e_type_f64:
   {

      payload.set_type(::e_type_f64, false);

      *this >> payload.m_f64;

   }
   break;
   case e_type_f32:
   {

      payload.set_type(::e_type_f32, false);

      *this >> payload.m_f64;

   }
   break;
   case e_type_int_array:
   {

      throw ::exception(todo);

      //throw ::exception(todo);      __exchange_load_array(*this, (::int_array &) payload);

   }
   break;
   case e_type_memory:
   {

      *this >> (::memory &)payload;

   }
   break;
   case e_type_string_array:
   {

      throw ::exception(todo);
      //__exchange_load_array(*this, (string_array &) payload);

   }
   break;
   case e_type_property_set:
   {
      throw ::exception(todo);

      //__exchange_load_array(*this, (property_set &) payload);



   }
   break;
   case e_type_atom:
   {

      payload.set_type(::e_type_atom, false);

      *this >> payload.m_atom;

   }
   break;
   case e_type_element:
   case e_type_path:
   {

      throw ::exception(todo);
      //payload._set_element(::__load_object<::matter>(*this));

   }
   break;
      //case e_type_property:
      //{

      //   auto pproperty = __allocate ::property_particle();

      //   *this >> pproperty->object();

      //   payload._set_element(pproperty);

      //}
      //   break;
   default:
   {
      payload.set_type(etype, false);
      read({ e_as_block ,payload.m_payloadall });
      //payload.release();
      //setstate(::file::failbit); // stream corrupt
      break;
   }
   }

   return;

}


//binary_stream & operator >>(binary_stream &stream, property & property)
//{
//
//   stream >>(property.m_atom);
//   stream >>((::payload &)property);
//
//   return stream;
//
//}

binary_stream & binary_stream::operator >>(string & str)
{

   ::i64 i = 0;

   i = m_pfile->_right_size() > 8 ? read_buffer_length_unbounded() : read_buffer_length();

   //if (!fail() && u > 0)
   if (i > 0)
   {

      auto psz = str.get_buffer((strsize)i);

      memsize s = character_count_to_byte_length(psz, (strsize)i);

      read({ psz, s });

      str.release_buffer((strsize)i);

   }

   return *this;

}



binary_stream & binary_stream::operator >>(block & block)
{

   u64 u = 0;

   u = read_buffer_length();

   if (u != block.size())
   {

      throw ::exception(error_io);

      return *this;

   }

   m_pfile->read(block.data(), block.size());

   return *this;

}


void binary_stream::getline(char * sz, strsize n)
{

   m_pfile->getline(sz, n);

}


void binary_stream::read_to_hex(string & str, filesize tickStart, filesize tickEnd)
{

   memory memory;

#if MEMDLEAK
   memory.m_strTag = "memory://member=stream::read_to_hex";
#endif

   if (tickStart == (filesize)-1)
   {

      tickStart = m_pfile->get_position();

   }
   else
   {
      m_pfile->set_position(tickStart);
   }
   memsize uiPos = 0;
   memsize uRead;
   memory.set_size(1024);

   strsize nCount;

   if (tickEnd == (filesize)-1)
   {

      nCount = ::numeric_info< strsize >::maximum();

   }
   else
   {

      nCount = (strsize)(tickEnd - tickStart);

   }

   while ((uRead = m_pfile->read(&memory.data()[uiPos], minimum(memory.size() - uiPos, (memsize)nCount))) > 0)
   {
      uiPos += uRead;
      nCount -= uRead;
      if (memory.size() - uiPos <= 0)
      {
         memory.allocate_add_up(1024 * 1024);
      }
   }
   memory.set_size((memsize)uiPos);
   memory.to_hex(str);
}



::pointer<::matter>binary_stream::create_object_from_text(::particle * pparticle, string strText)
{

   if (strText.is_empty())
   {

      return nullptr;

   }

   auto atom = text_to_factory_id(strText);

   return __id_create(atom);

}


::pointer < ::subparticle > binary_stream::read_particle()
{

   ::type_atom typeatom;

   *this >> typeatom;

   auto pparticle = __id_create(typeatom);

   pparticle->read_from_stream(*this);

   return pparticle;

}


void binary_stream::write_particle(const ::subparticle * pparticle)
{

   ::type_atom typeatom(pparticle);

   *this << typeatom;

   ((subparticle *)pparticle)->write_to_stream(*this);

}
