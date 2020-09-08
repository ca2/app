
#include "framework.h"
#include <stdio.h>
//#include "acme/xml/_.h"




::file::path stream::get_file_path() const
{

   return "";

}


void stream::add_exception(::exception::exception * pexception)
{

   set_fail_bit();

}


void stream::on_catch_all_exception()
{

   set_fail_bit();

}


//void stream::write_object(const ::id & id, ::generic * pobject)
//{
//
//   auto strId = factory_id_to_text(pobject->type_name());
//
//   exchange(property_id, strId);
//
//   pobject->exchange(*this);
//
//}
//
//
//__pointer(::generic) stream::read_object(const ::id & id)
//{
//
//   string strId;
//
//   exchange(property_id, strId);
//
//   auto pobject = create_object_from_text(strId);
//
//   pobject->exchange(*this);
//
//   return pobject;
//
//}


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

      __throw(invalid_argument_exception());

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

   ::id::e_type etype = id.m_etype;

   write(i8(etype));

   if (etype == ::id::type_text)
   {

      write(id.m_psz);

   }
   else if (etype == ::id::type_integer)
   {

      write(id.m_i);

   }

}


void stream::write(const var & var)
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
      *this << var.memory();
      break;
   case type_stra:
      *this << var.stra();
      break;
   case type_propset:
      *this << var.propset();
      break;
   case type_id:
      *this << var.m_id;
      break;
   case type_element:
   case type_path:
   {

      __save_object(*this, var.cast <::generic>());

   }
   break;
   default:
      __throw(::exception::exception("var::write var type not recognized"));
   }

}


void stream::write(const property & property)
{

   write(property.m_id);
   write((const var &) property);

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


void stream::write(const ::generic * pobject)
{

   pobject->write(*this);

}


void stream::write(const ::generic & generic)
{

   generic.write(*this);

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



//bool stream::get_object_link(const ::generic * preference, string & strLink, bool & bLink)
//{
//
//   return false;
//
//}
//
//
//void stream::set_object_link(const ::generic * preference, const string & strLink, bool bReadOnly)
//{
//
//}
//
//
//bool stream::write_link(const ::generic * pobject)
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


//void stream::write_link(const ::generic * preference, const string & strLink, bool bReadOnly, ::generic * pobjectSaveOptions)
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
//
//
//void stream::read_link(::generic * preference)
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


void stream::read(unsigned long & ui)
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


//void stream::read(POINT & point)
//{
//
//   set_fail_bit();
//
//}
//
//
//void stream::read(SIZE & size)
//{
//
//   set_fail_bit();
//
//}
//
//
//void stream::read(RECT & rect)
//{
//
//   set_fail_bit();
//
//}


void stream::read(id & id)
{

   set_fail_bit();

}


void stream::read(var & var)
{

   set_fail_bit();

}


void stream::read_var_type(e_type & etype)
{

   set_fail_bit();

}


void stream::read_var_body(var & var, e_type etype)
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


void stream::read(::generic& generic)
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



void stream::save_var_type(e_type etype)
{

   ::i32 i((::i32) etype);

   *this << i;

   return;

}


//void stream::xml_export(const ::xml::exportable & xmlexportable)
//{
//
//   __throw(todo("xml"));
//   //string strXml;
//
//   //::xml::output_tree outputtree(get_context_object());
//
//   //xmlexportable.xml_export(outputtree);
//
//   //return write(outputtree.m_pdocument->get_xml());
//
//}




//void stream::xml_import(::xml::importable & xmlimportable)
//{
//
//   __throw(todo("xml"));
//   //string strXml;
//
//   //read(strXml);
//
//   //::xml::input_tree inputtree(get_context_object(), strXml);
//
//   //xmlimportable.xml_import(inputtree);
//
//   //return;
//
//}


var & stream::options()
{

   if (!m_pvarOptions)
   {

      m_pvarOptions = new var();

   }

   return *m_pvarOptions;

}


//__pointer(::generic) stream::create_object_from_text(string strText)
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


void stream::exchange(const ::id & id, const char * psz)
{

   if(is_loading())
   {

      throw io_exception();

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

      throw io_exception();

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


void stream::exchange(const ::id & id, var & var)
{

   stream_exchange(id, var);

}


void stream::exchange(const ::id & id, property & property)
{

  stream_exchange(id, property);

}


void stream::exchange(const ::id & id, string & str)
{

   stream_exchange(id, str);

}


void stream::exchange(const ::id & id, ::generic * pobject)
{

   pobject->exchange(*this);

}


void stream::exchange(const ::id & id, ::generic & generic)
{

   generic.exchange(*this);

}


void stream::exchange(const ::id & id, property_set & set)
{

   stream_exchange(id, set);

}


void stream::exchange(const ::id & id, block & block)
{

   stream_exchange(id, block);

}



