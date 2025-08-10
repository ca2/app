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


unsigned long long binary_stream::read_buffer_length()
{

   auto i = m_pfile->get_unsigned_char();

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

      i = m_pfile->get_unsigned_short();

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

         unsigned long long ull;

         if (!m_pfile->get_unsigned_long_long(ull))
         {

            set_nok();

            return 0;

         }

         return ull;

      }

   }

}





string binary_stream::factory_id_to_text(const ::atom & atom)
{

   return atom.as_string();

}


::atom binary_stream::text_to_factory_id(const ::scoped_string & scopedstr)
{

   return scopedstr;

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
   case e_type_char:
      stream << payload.m_ch;
      break;
   case e_type_short:
      stream << payload.m_sh;
      break;
   case e_type_unsigned_char:
      stream << payload.m_uch;
      break;
   case e_type_unsigned_short:
      stream << payload.m_ush;
      break;
   case e_type_int:
      stream << payload.m_i;
      break;
   case e_type_long_long:
      stream << payload.m_hi;
      break;
   case e_type_unsigned_int:
      stream << payload.m_ui;
      break;
   case e_type_unsigned_long_long:
      stream << payload.m_hn;
      break;
   case e_type_pchar:
      stream << *payload.m_pch;
      break;
   case e_type_pshort:
      stream << *payload.m_psh;
      break;
   case e_type_punsigned_char:
      stream << *payload.m_puch;
      break;
   case e_type_punsigned_short:
      stream << *payload.m_push;
      break;
   case e_type_pint:
      stream << *payload.m_pi;
      break;
   case e_type_plong_long:
      stream << *payload.m_phi;
      break;
   case e_type_punsigned_int:
      stream << *payload.m_pui;
      break;
   case e_type_punsigned_long_long:
      stream << *payload.m_phn;
      break;
   case e_type_double:
      stream << payload.m_d;
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
   case e_type_long_long_array:
      //*this << *payload.m_pfilei64a;
      throw ::exception(todo);
      break;
      //case type_image:
      //   *this << *payload.m_pfileimage;
      //   break;
   case e_type_atom:
      stream << payload.m_atomPayload;
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

binary_stream & binary_stream::operator <<(const_char_pointer psz)
{

   auto len = string_safe_length(psz);

   write_buffer_length(len);

   write({ psz, len });

   return *this;

}




binary_stream & binary_stream::operator <<(const ::range < const_char_pointer >& range)
{

   write_buffer_length(range.size());

   write(::as_block(range));

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

   unsigned long long u = 0;

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

      long long i;

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
   case e_type_pint:
   case e_type_int:
   {

      payload.set_type(e_type_int, false);

      *this >> payload.m_i;

   }
   break;
   case e_type_plong_long:
   case e_type_long_long:
   {

      payload.set_type(e_type_long_long, false);

      *this >> payload.m_hi;

   }
   break;
   case e_type_punsigned_int:
   case e_type_unsigned_int:
   {

      payload.set_type(::e_type_unsigned_int, false);

      *this >> payload.m_ui;

   }
   break;
   case e_type_punsigned_long_long:
   case e_type_unsigned_long_long:
   {

      payload.set_type(::e_type_unsigned_long_long, false);

      *this >> payload.m_hn;

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
   case e_type_int_array:
   {

      throw ::exception(todo);

      //throw ::exception(todo);      __exchange_load_array(*this, (::int_array_base &) payload);

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
      //__exchange_load_array(*this, (string_array_base &) payload);

   }
   break;
   case e_type_property_set:
   {
      throw ::exception(todo);

      //__exchange_load_array(*this, (::property_set &) payload);



   }
   break;
   case e_type_atom:
   {

      payload.set_type(::e_type_atom, false);

      *this >> payload.m_atomPayload;

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

   long long i = 0;

   i = m_pfile->_right_size() > 8 ? read_buffer_length_unbounded() : read_buffer_length();

   //if (!fail() && u > 0)
   if (i > 0)
   {

      auto psz = str.get_buffer((character_count)i);

      memsize s = character_count_to_byte_length(psz, (character_count)i);

      read({ psz, s });

      str.release_buffer((character_count)i);

   }

   return *this;

}



binary_stream & binary_stream::operator >>(block & block)
{

   unsigned long long u = 0;

   u = read_buffer_length();

   if (u != block.size())
   {

      throw ::exception(error_io);

      return *this;

   }

   m_pfile->read(block.data(), block.size());

   return *this;

}


void binary_stream::getline(char * sz, character_count n)
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

   character_count nCount;

   if (tickEnd == (filesize)-1)
   {

      nCount = ::numeric_info< character_count >::maximum();

   }
   else
   {

      nCount = (character_count)(tickEnd - tickStart);

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



::pointer<::matter>binary_stream::create_object_from_text(::particle * pparticle, const ::scoped_string & scopedstrText)
{

   if (scopedstrText.is_empty())
   {

      return nullptr;

   }

   auto atom = text_to_factory_id(scopedstrText);

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
