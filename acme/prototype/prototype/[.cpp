#include "framework.h"
#include "acme/platform/acme.h"
#include "acme/operating_system.h"


#if defined(WINDOWS)
//extern _locale_t ::acme::get_c_locale();
#else
#if defined(__APPLE__)
#include <xlocale.h>
#define _atof_l atof_l
#endif
//extern locale_t ::acme::get_c_locale();
#endif

payload::payload(const ::scoped_string & scopedstr)
{

   m_etype = e_type_new;

   set_string(psz);

}


payload::payload(::particle * pparticle)
{

   m_etype = e_type_new;

   operator = ((::element *) pelement);

}


payload::payload(const ::element & element)
{

   m_etype = e_type_new;

   operator = (element);

}


payload::payload(const ::string & str)
{

   m_etype = e_type_new;

   set_string(str);

}


payload::payload(const type & type)
{

   m_etype = e_type_new;

   set_type(type);

}


payload::payload(::string * pstr)
{

   m_etype = e_type_new;

   operator = (pstr);

}


payload::payload(bool b)
{

   m_etype = e_type_new;

   operator = (b);

}


payload::payload(bool * pb)
{

   m_etype = e_type_new;

   operator = (pb);

}


payload::payload(::i32 i)
{

   m_etype = e_type_new;

   operator = (i);

}


payload::payload(::u32 u )
{

   m_etype = e_type_u32;

   operator = (u);

}


payload::payload(::i64 i)
{

   m_etype = e_type_new;

   operator = (i);

}


payload::payload(::u64 u )
{

   m_etype = e_type_u64;

   m_u64 = u;

}


#ifdef __APPLE__
#ifdef OS64BIT

payload::payload(long l)
{

   m_etype = e_type_i64;
   m_i64 = (::i64) l;

}

#endif
#endif


payload::payload(::i32 * pi)
{

   m_etype = e_type_new;
   operator = (pi);

}


payload::payload(::u32 * pinteraction)
{

   m_etype = e_type_new;
   operator = (pinteraction);

}


payload::payload(::i64 * pi)
{

   m_etype = e_type_new;
   operator = (pi);

}


payload::payload(::u64 * pinteraction)
{

   m_etype = e_type_new;
   operator = (pinteraction);

}


payload::payload(::f32 f32)
{

   m_etype = e_type_new;
   operator = (f32);

}


payload::payload(::f64 f64)
{

   m_etype = e_type_new;
   operator = (f64);

}


payload::payload(const ::file::path & path)
{

   m_etype = e_type_new;
   operator = (path);

}


payload::payload(const string_array & payload)
{

   m_etype  = e_type_new;
   operator = (payload);

}


payload::payload(const ::i32_array & ia)
{

   m_etype  = e_type_new;
   operator = (ia);

}


payload::payload(const payload_array & payload)
{

   m_etype  = e_type_new;

   operator = (payload);

}


payload::payload(const property_set & set)
{

   m_etype  = e_type_new;

   operator = (set);

}


payload::payload(const class ::payload & payload)
{

   m_etype = e_type_new;
   operator = (payload);

}


payload::payload(::payload * ppayload)
{

   m_etype = e_type_new;

   operator = (ppayload);

}


pack::pack(const ::std::initializer_list < pack >& list)
{

   for (auto& payload : list)
   {

      if (payload.get_type() == e_type_property_set)
      {

         propset().merge(payload.propset());

      }

   }


}


payload::payload(const ::property & property)
{

   m_etype = e_type_new;

   operator = (property);

}


//payload::payload(const ::procedure & procedure)
//{
//
//    m_etype = e_type_new;
//
//    set_type(e_type_routine, false);
//
//    m_pelementProcedure = procedure;
//    
//    ::increment_reference_count(m_pelementProcedure);
//
//}


//payload::payload(const ::future & future)
//{
//
//   m_etype = e_type_new;
//   zero(m_all);
//   set_type(type_process);
//   m_process = process;
//
//}


payload::payload(::property * pproperty)
{

   m_etype = e_type_new;

   if (::is_set(pproperty))
   {

      operator = (pproperty);

   }
   else
   {

      clear_data();

   }

}


payload::payload(const ::atom & atom)
{

   m_etype = e_type_new;
   operator = (atom);

}


payload::payload(const class time & time)
{

   m_etype = e_type_time;
   m_time = time;

}


payload::payload(::time * ptime)
{

   m_etype = e_type_ptime;
   m_ptime = ptime;

}


payload::payload(const ::earth::time & time)
{
   
   m_etype = e_type_time;
   
   m_time = time.m_i;

}


payload::payload(const ::color::color & color)
{

   m_etype = e_type_color;
   m_color = color;

}


payload::payload(const ::color::hls & hls)
{

   m_etype = e_type_hls;
   m_hls = hls;

}


payload::~payload()
{

   release();

}


bool payload::convert(const ::payload & payload)
{

   if (m_etype == payload.m_etype)
   {

      if (m_etype == e_type_string)
      {

         m_str = payload.m_str;

      }
      else
      {

         ::memory_copy(&m_all, &payload.m_all, sizeof(m_all));

      }

   }
   else if(m_etype == e_type_i8)
   {

      m_i8 = payload.i8();

   }
   else if(m_etype == e_type_enum_check)
   {

      m_echeck = payload.echeck();

   }
   else if(m_etype == e_type_string)
   {

      m_str = payload.string();

   }
   else
   {

      return false;

   }

   return true;

}


strsize payload::length() const
{

   return string().length();

}


void payload::as(::string & str) const
{


}


void payload::as(::memory_base & memory) const
{


}


void payload::as(::atom & atom) const
{


}


::string payload::as_string() const
{

   ::string str;

   as(str);

   return ::transfer(str);

}


::memory payload::as_memory() const
{

   memory memory;

   as(memory);

   return ::transfer(memory);

}


::atom payload::as_id() const
{

   ::atom atom;

   as(atom);

   return ::transfer(atom);

}


//void payload::string(const ::scoped_string & scopedstr) const
//{
//
//   strcpy(psz, string());
//
//}


::enum_type payload::get_type() const
{

   return m_etype;

}


class ::payload & payload::operator ++(::i32)
{

   switch(get_type())
   {
   case e_type_new:
   case e_type_null:
   case e_type_string_array:
   case e_type_i32_array:
   case e_type_empty:
   case e_type_element:
   case e_type_path:
      set_type(e_type_i32);
      m_i32 = 1;
      break;
   case e_type_bool:
      if(!m_b)
      {
         set_type(e_type_i32);
         m_i32 = 1;
      }
      else
      {
         set_type(e_type_i32);
         m_i32 = 2;
      }
      break;
   case e_type_string:
   {
      auto i = atoi(m_str) + 1;
      set_type(e_type_i32);
      m_i32 = i;

   }
      break;
   case e_type_f64:
      m_f64 += 1.0;
      break;
   case e_type_i32:
      m_i32++;
      break;
   case e_type_u32:
      m_u32++;
      break;
   default:
      set_type(e_type_i32, false);
      m_i32 = 1;
      break;
   }
   return *this;
}


void payload::set_type(const ::type_atom & typeatom)
{

   set_type(e_type_type, false);

   m_str = type.m_strName;

}






bool payload::get_type(::type & type) const
{

   if (m_etype != e_type_type)
   {

      return false;

   }

   type.m_strName = m_str;

   return true;

}


void payload::set_type(enum_type etype, bool bConvert)
{

   if (m_etype == e_type_payload_pointer)
   {

      m_ppayload->set_type(etype, bConvert);

   }
   else if (m_etype == e_type_property)
   {

      m_pproperty->set_type(etype, bConvert);

   }
   else if (etype != m_etype)
   {

      release();

      if (bConvert && m_etype != e_type_new)
      {

         switch (etype)
         {
         case e_type_i8:
            m_i32 = this->i8();
            break;
         case e_type_u8:
            m_u32 = this->u8();
            break;
         case e_type_i16:
            m_i32 = this->i16();
            break;
         case e_type_u16:
            m_u32 = this->u16();
            break;
         case e_type_i32:
            m_i32 = this->i32();
            break;
         case e_type_u32:
            m_u32 = this->u32();
            break;
         case e_type_i64:
            m_i64 = this->i64();
            break;
         case e_type_u64:
            m_u64 = this->u64();
            break;
         case e_type_f64:
            m_f64 = this->f64();
            break;
         case e_type_string:
            m_str = ::transfer(this->string());
            break;
         case e_type_id:
            m_atom = ::transfer(this->atom());
            break;
         default:
            ::set_last_status(error_conversion_not_a_number);
            break;

         }

      }
      else if (etype == e_type_string)
      {

         ::new(&m_str) ::string();

      }

      m_etype = etype;

   }

}


void payload::set_string(::string && str)
{

   if (get_type() == e_type_pstring)
   {

      *m_pstr = ::transfer(str);

   }
   else if (get_type() == e_type_payload_pointer)
   {

      m_ppayload->set_string(::transfer(str));

   }
   else if (get_type() == e_type_property)
   {

      m_pproperty->set_string(::transfer(str));

   }
   else
   {

      set_type(e_type_string, false);

      m_str = ::transfer(str);

   }

}


void payload::unset()
{
   set_type(e_type_new, false);
}


void payload::unset(const ::string & strPropertySetKey)
{

   if (get_type() == e_type_property_set)
   {

      propset().erase_by_name(strPropertySetKey);

   }

}


bool payload::ok() const
{
   return get_type() != e_type_parareturn || ::is_return_ok(m_parareturn);
}

bool payload::failed() const
{
   return get_type() == e_type_parareturn && !::is_return_ok(m_parareturn);
}


void payload::set_id(const ::atom & atom)
{

   if(get_type() == e_type_pid)
   {

      *m_pid = atom;

   }
   else if(get_type() == e_type_payload_pointer)
   {

      *m_ppayload = atom;

   }
   else if (get_type() == e_type_property)
   {

      *m_pproperty = atom;

   }
   else
   {

      set_type(e_type_id, false);

      m_atom = atom;

   }

}


class ::payload & payload::operator = (para_return & eret)
{

   set_type(e_type_parareturn, false);

   m_parareturn = eret;

   return *this;

}


class ::payload & payload::operator = (bool b)
{

   if(get_type() == e_type_pbool)
   {

      *m_pb = b;

   }
   else if(get_type() == e_type_payload_pointer)
   {

      *m_ppayload = b;

   }
   else if (get_type() == e_type_property)
   {

      *m_pproperty = b;

   }
   else
   {

      set_type(e_type_bool, false);

      m_b = b;

   }

   return *this;

}


class ::payload & payload::operator = (bool * pb)
{

   set_type(e_type_pbool, false);

   m_pb = pb;

   return *this;

}


class ::payload & payload::operator = (::i32 i)
{

    if(get_type() == e_type_pi32)
   {

       *m_pi32 = i;

   }
   else if(get_type() == e_type_payload_pointer)
   {

       *m_ppayload = i;

   }
   else if (get_type() == e_type_property)
   {

       *m_pproperty = i;

   }
   else
   {

       set_type(e_type_i32, false);

      m_i32 = i;

   }

   return *this;

}


class ::payload & payload::operator = (::i32 * pi)
{

   set_type(e_type_pi32, false);

   m_pi32 = pi;

   return *this;

}


class ::payload & payload::operator = (::u32 * pinteraction)
{

    set_type(e_type_pu32, false);

   m_pu32 = pinteraction;

   return *this;

}


class ::payload & payload::operator = (::i64 * pi)
{

    set_type(e_type_pi64, false);

   m_pi64 = pi;

   return *this;

}


class ::payload & payload::operator = (::u64 * pinteraction)
{

    set_type(e_type_pu64, false);

   m_pu64 = pinteraction;

   return *this;

}


class ::payload & payload::operator = (const ::earth::time & time)
{

    set_type(e_type_time, false);

   m_time = time.get_time();

   return *this;

}


class ::payload & payload::operator = (const ::color::color & color)
{

   set_type(e_type_color, false);

   m_color = color;

   return *this;

}


class ::payload & payload::operator = (const ::color::hls & hls)
{

   set_type(e_type_hls, false);

   m_hls = hls;

   return *this;

}


//#ifdef WINDOWS
//
//
//class ::payload & payload::operator = (const FILETIME & file_time)
//{
//
//   set_type(type_file_time, false);
//
//   m_u64 = make64_from32(file_time.dwLowDateTime, file_time.dwHighDateTime);
//
//   return *this;
//
//}
//
//
//#endif


class ::payload & payload::operator = (::i64 i)
{
   if(get_type() == e_type_pi64)
   {
      *m_pi64 = i;
   }
   else if(get_type() == e_type_payload_pointer)
   {
      *m_ppayload = i;
   }
   else if (get_type() == e_type_property)
   {
      *m_pproperty = i;
   }
   else
   {
      set_type(e_type_i64, false);
      m_i64 = i;
   }
   return *this;
}

class ::payload & payload::operator = (::u64 u)
{
   if(get_type() == e_type_pu64)
   {
      *m_pu64 = u;
   }
   else if(get_type() == e_type_payload_pointer)
   {
      *m_ppayload = u;
   }
   else if (get_type() == e_type_property)
   {
      *m_pproperty = u;
   }
   else
   {
      set_type(e_type_u64, false);
      m_u64 = u;
   }
   return *this;
}


class ::payload & payload::operator = (::u32 u)
{
   set_type(e_type_u32, false);
   m_u32 = u;
   return *this;
}


#if !defined(LINUX) && !defined(MACOS) && !defined(ANDROID) && !defined(APPLE_IOS) && !defined(FREEBSD)

class ::payload & payload::operator = (long l)
{

   set_type(e_type_i32,false);

   m_i32 = l;

   return *this;

}


#endif


#if defined(__APPLE__)
   class ::payload & payload::operator = (long l)
   {
      set_type(e_type_i64,false);
      m_i64 = l;
      return *this;
   }
#endif

#if defined(ANDROID)
   class ::payload & payload::operator = (long l)
   {
      set_type(e_type_i32,false);
      m_i32 = l;
      return *this;
   }
#endif

class ::payload & payload::operator = (::f32 f32)
{
   set_type(e_type_f32, false);
   m_f32 = f32;
   return *this;
}

class ::payload & payload::operator = (::f64 f64)
{
   set_type(e_type_f64, false);
   m_f64 = f64;
   return *this;
}


//class ::payload & payload::operator = (enum_command ecommand)
//{
//   set_type(type_enum_command, false);
//   m_ecommand = ecommand;
//
//   return *this;
//
//}


class ::payload & payload::operator = (::string * pstr)
{

   set_type(e_type_pstring, false);

   m_pstr = pstr;

   return *this;

}


class ::payload & payload::operator = (::atom * pid)
{

   set_type(e_type_pid, false);

   m_pid = pid;

   return *this;

}


class ::payload & payload::operator = (const ::wide_character * pcsz)
{

   set_string(unicode_to_utf8(pcsz));

   return *this;

}


class ::payload & payload::operator = (const ::property & property)
{

   operator = ((const ::payload &)property);

   return *this;

}


class ::payload & payload::operator = (const ::property * pproperty)
{

   if (::is_null(pproperty))
   {

      set_type(e_type_null, false);

   }
   else
   {

      set_type(e_type_property, false);

      m_pproperty = (::property *)pproperty;

   }

   return *this;

}

void payload::increment_reference_count()
{

   switch(m_etype)
   {
      case e_type_element:
         if(m_p) m_p->increment_reference_count();
         break;
      case e_type_string_array:
         if (m_pstra) m_pstra->increment_reference_count();
         break;
      case e_type_i32_array:
         if (m_pia) m_pia->increment_reference_count();
         break;
      case e_type_payload_array:
         if (m_ppayloada) m_ppayloada->increment_reference_count();
         break;
      case e_type_property_set:
         if (m_ppropertyset) m_ppropertyset->increment_reference_count();
         break;
      case e_type_i64_array:
         if (m_p) m_p->increment_reference_count();
         break;
      case e_type_memory:
         if (m_pmemory) m_pmemory->increment_reference_count();
         break;
      case e_type_path:
         if (m_ppath) m_ppath->increment_reference_count();
         break;
      default:
         break;

   };


}


class ::payload & payload::operator = (const class ::payload & payload)
{
   if(m_etype == e_type_payload_pointer)
   {
      if(m_ppayload == &payload)
         return *this;
      m_ppayload->operator = (payload);
      return *this;
   }
   if (m_etype == e_type_property)
   {
      m_pproperty->operator = (payload);
      return *this;
   }
   if(&payload != this)
   {
      switch(((class ::payload &)payload).get_type())
      {
      case e_type_payload_pointer:
         // should dereference (this operator here means a content copy)
         *this  = *((class ::payload &)payload).m_ppayload;
         return *this;
      case e_type_property:
         // should dereference (this operator here means a content copy)
         *this = *((class property&)payload).m_pproperty;
         return *this;
      case e_type_pi32:
         // should dereference (this operator here means a content copy)
         *this  = *((class ::payload &)payload).m_pi32;
         return *this;
      case e_type_pstring:
         // should dereference (this operator here means a content copy)
         *this  = *((class ::payload &)payload).m_pstr;
         return *this;
      default:
         break;
      }

      set_type(payload.get_type(), false);
      if (payload.is_element())
      {

         m_p = payload.m_p; // raw copy, doesn't care for the right member
         increment_reference_count();

      }
      else
      {
         switch (payload.get_type())
         {
         case e_type_bool:
            m_b = payload.m_b;
            break;
         case e_type_i8:
            m_i8 = payload.m_i8;
            break;
         case e_type_u8:
            m_u8 = payload.m_u8;
            break;
         case e_type_i16:
            m_i16 = payload.m_i16;
            break;
         case e_type_u16:
            m_u16 = payload.m_u16;
            break;
         case e_type_i32:
            m_i32 = payload.m_i32;
            break;
         case e_type_u32:
            m_u32 = payload.m_u32;
            break;
         case e_type_i64:
            m_i64 = payload.m_i64;
            break;
         case e_type_u64:
            m_u64 = payload.m_u64;
            break;
         case e_type_pi8:
            m_pi8 = payload.m_pi8;
            break;
         case e_type_pu8:
            m_pu8 = payload.m_pu8;
            break;
         case e_type_pi16:
            m_pi16 = payload.m_pi16;
            break;
         case e_type_pu16:
            m_pu16 = payload.m_pu16;
            break;
         case e_type_pi32:
            m_pi32 = payload.m_pi32;
            break;
         case e_type_pu32:
            m_pu32 = payload.m_pu32;
            break;
         case e_type_pi64:
            m_pi64 = payload.m_pi64;
            break;
         case e_type_pu64:
            m_pu64 = payload.m_pu64;
            break;
         case e_type_f32:
            m_f32 = payload.m_f32;
            break;
         case e_type_f64:
            m_f64 = payload.m_f64;
            break;
         case e_type_string:
            m_str = payload.m_str;
            break;
         case e_type_property:
            m_pproperty=payload.m_pproperty;
            break;
         case e_type_id:
            m_atom = payload.m_atom;
            break;
         default:
            ::memory_copy(m_all, payload.m_all, sizeof(m_all));
            //m_str = payload.m_str;
            break;
         }
      }
   }
   return *this;
}


class ::payload & payload::operator = (const ::i32_array & ia)
{

   ia_reference() = ia;

   return *this;

}


class ::payload & payload::operator = (const class memory & memoryParam)
{

   as_memory() = memoryParam;

   return *this;

}


class ::payload & payload::operator = (const string_array & straParam)
{

   stra_reference() = straParam;

   return *this;

}


class ::payload & payload::operator = (const payload_array & payloadaParam)
{

   payloada_reference() = payloadaParam;

   return *this;

}


class ::payload & payload::operator = (const property_set & propsetParam)
{

   propset_reference() = propsetParam;

   return *this;

}


class ::payload & payload::operator = (const ::atom & atom)
{

   set_id(atom);

   return *this;

}


//class ::payload & payload::operator = (const ::second & second)
//{
//
//   set_type(e_type_secs);
//
//   m_secs = second;
//
//   return *this;
//
//}
//
//
//class ::payload & payload::operator = (::second * psecs)
//{
//
//   set_type(e_type_psecs);
//
//   m_psecs = psecs;
//
//   return *this;
//
//}
//
//
//class ::payload & payload::operator = (const class time & time)
//{
//
//   set_type(e_type_millis);
//
//   m_millis = ::time;
//
//   return *this;
//
//}
//
//
//class ::payload & payload::operator = (::time * pmillis)
//{
//
//   set_type(e_type_pmillis);
//
//   m_pmillis = pmillis;
//
//   return *this;
//
//}
//
//
//class ::payload & payload::operator = (const ::microsecond & microsecond)
//{
//
//   set_type(e_type_micros);
//
//   m_micros = microsecond;
//
//   return *this;
//
//}
//
//
//class ::payload & payload::operator = (::microsecond * pmicros)
//{
//
//   set_type(e_type_pmicros);
//
//   m_pmicros = pmicros;
//
//   return *this;
//
//}
//
//
//class ::payload & payload::operator = (const ::nanosecond & nanosecond)
//{
//
//   set_type(e_type_nanos);
//
//   m_nanos = nanosecond;
//
//   return *this;
//
//}
//
//
//class ::payload & payload::operator = (::nanosecond * pnanos)
//{
//
//   set_type(e_type_pnanos);
//
//   m_pnanos = pnanos;
//
//   return *this;
//
//}


class ::payload & payload::operator = (const class time & time)
{

   set_type(e_type_time);

   m_time = time;

   return *this;

}


class ::payload & payload::operator = (::time * ptime)
{

   set_type(e_type_ptime);

   m_ptime = ptime;

   return *this;

}


::payload & payload::operator = (const ::block & block)
{

   if(m_etype == e_type_payload_pointer)
   {

      return m_ppayload->operator = (block);

   }
   else if(m_etype == e_type_memory)
   {

      *m_pmemory = block;

   }
   else
   {

      set_type(e_type_memory, false);

      m_pmemory = ___new ::memory (block);

   }

   return *this;

}


bool payload::casts_to(::enum_type etype) const
{

   if (m_etype == etype)
   {

      return true;

   }
   else if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->casts_to(etype);

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->casts_to(etype);

   }


   return false;

}


bool payload::is_true(const ::payload & payload, bool bDefault) const
{

   if (payload.get_type() == e_type_bool)
   {

      ASSERT(!bDefault);

      bool bDefault = payload.m_b;

      if (is_element_set())
      {

         return true;

      }
      else
      {
         switch (m_etype)
         {
         case e_type_null:
            return bDefault;
         case e_type_empty:
            return bDefault;
         case e_type_key_exists:
            return true;
         case e_type_string:
            return !m_str.is_empty() && !(m_str.case_insensitive_order("no") == 0 || m_str.case_insensitive_order("false") == 0 || m_str.case_insensitive_order("0") == 0);
         case e_type_i32:
            return m_i32 != 0;
         case e_type_u32:
            return m_u32 != 0;
         case e_type_i64:
            return m_i64 != 0;
         case e_type_u64:
            return m_u64 != 0;
         case e_type_f64:
            return m_f64 != 0;
         case e_type_bool:
            return m_b;
         case e_type_payload_pointer:
            return m_ppayload->is_true(bDefault);
         case e_type_property:
            return m_pproperty->is_true(bDefault);
         case e_type_enum_status:
            return ::succeeded(m_estatus);
         case e_type_enum_check:
            return __bool(m_echeck);
         default:
            return bDefault;
         }

      }

   }
   else
   {

      switch (m_etype)
      {
      case e_type_property_set:
         return m_ppropertyset->is_true(payload, bDefault);
      case e_type_payload_pointer:
         return m_ppayload->is_true(payload, bDefault);
      case e_type_property:
         return m_pproperty->is_true(payload, bDefault);
      default:
         return bDefault;
      }

   }

}



bool payload::is_empty() const
{

   switch(m_etype)
   {
   case e_type_null:
      return true;
   case e_type_empty:
      return true;
   case e_type_empty_argument:
      return true;
   case e_type_new:
      return true;
   case e_type_string:
      return m_str.is_empty();
   case e_type_i32:
      return false;
   case e_type_u32:
      return false;
   case e_type_i64:
      return false;
   case e_type_u64:
      return false;
   case e_type_f64:
      return false;
   case e_type_payload_pointer:
      return m_ppayload->is_empty();
   case e_type_property:
      return m_pproperty->is_empty();
   case e_type_id:
      return m_atom.is_empty();
   case e_type_pid:
      return m_pid->is_empty();


      // element classes
   case e_type_element:
      return is_element_null();
   case e_type_string_array:
      return ::is_null(m_pstra) || m_pstra->is_empty();
   case e_type_i32_array:
      return ::is_null(m_pia) || m_pia->is_empty();
   case e_type_payload_array:
      return ::is_null(m_ppayloada) || m_ppayloada->is_empty();
   case e_type_property_set:
      return ::is_null(m_ppropertyset) || m_ppropertyset->is_empty();
   case e_type_i64_array:
      return ::is_null(m_pi64a) || m_pi64a->is_empty();
   case e_type_memory:
      return ::is_null(m_pmemory) || m_pmemory->is_empty();
   case e_type_path:
      return ::is_null(m_ppath) || m_ppath->is_empty();
   //case type_image:
   //   return m_pimage.ok();

   default:
      return false;
   }
}


bool payload::has_char() const
{

   return string().has_char();

}


bool payload::is_set() const
{

   if (get_type() != e_type_new)
   {

      return true;

   }
   else
   {

      return false;

   }

}


bool payload::is_new() const
{
   if(m_etype == e_type_new)
      return true;
   else
      return false;
}


bool payload::is_null() const
{
   if(m_etype == e_type_null)
      return true;
   else
      return false;
}


bool payload::is_new_or_null() const
{

   return is_new() || is_null();

}




::i32 payload::case_insensitive_order(const class ::payload & payload) const
{
   if(m_etype == ::e_type_i32_array)
   {
      if(payload.m_etype == ::e_type_i32_array)
      {
         //payload = var1.ia() - payload2.ia();
      }
      else
      {
         //payload = var1;
         //payload.ia().erase(payload2.i32());
      }
   }
   else if(m_etype == ::e_type_string_array)
   {
      if(payload.m_etype == ::e_type_string_array)
      {
         //payload = var1.stra() - payload2.stra();
      }
      else
      {
         //payload = var1;
         //payload.stra().erase(payload2.string());
      }
   }
   else if(m_etype == ::e_type_payload_array)
   {
      if(payload.m_etype == ::e_type_payload_array)
      {
         //   payload = var1.payloada() - payload2.payloada();
      }
      else
      {
         // payload = var1;
         //payload.payloada().erase(payload2);
      }
   }
   else if(is_double() || payload.is_double())
   {
      ::f64 f64 = this->f64() - payload.f64();
      if(f64 == 0.0)
         return 0;
      else if(f64 > 0.0)
         return 1;
      else if(f64 < 0.0)
         return -1;
   }
   else if(is_integer() || payload.is_integer())
   {
      return i32() - payload.i32();
   }
   else if(is_natural() || payload.is_natural())
   {
      return (::i32) (u32() - payload.u32());
   }
   else
   {
      return string().case_insensitive_order(payload.string());
   }
   return -2;
}

::i32 payload::case_insensitive_order(const ::scoped_string & scopedstr) const
{
   ::payload payload(psz);
   return case_insensitive_order(payload);
}


::i32 payload::compare(const class ::payload & payload) const
{
   if(m_etype == ::e_type_i32_array)
   {
      if(payload.m_etype == ::e_type_i32_array)
      {
         //payload = var1.ia() - payload2.ia();
      }
      else
      {
         //payload = var1;
         //payload.ia().erase(payload2.i32());
      }
   }
   else if(m_etype == ::e_type_string_array)
   {
      if(payload.m_etype == ::e_type_string_array)
      {
         //payload = var1.stra() - payload2.stra();
      }
      else
      {
         //payload = var1;
         //payload.stra().erase(payload2.string());
      }
   }
   else if(m_etype == ::e_type_payload_array)
   {
      if(payload.m_etype == ::e_type_payload_array)
      {
         //   payload = var1.payloada() - payload2.payloada();
      }
      else
      {
         // payload = var1;
         //payload.payloada().erase(payload2);
      }
   }
   else if(is_double() || payload.is_double())
   {
      ::f64 f64 = this->f64() - payload.f64();
      if(f64 == 0.0)
         return 0;
      else if(f64 > 0.0)
         return 1;
      else if(f64 < 0.0)
         return -1;
   }
   else if(is_integer() || payload.is_integer())
   {
      return i32() - payload.i32();
   }
   else if(is_natural() || payload.is_natural())
   {
      return (::i32) (u32() - payload.u32());
   }
   else
   {
      return string().compare(payload.string());
   }
   return -2;
}

::i32 payload::compare(const ::scoped_string & scopedstr) const
{
   ::payload payload(psz);
   return compare(payload);
}

bool payload::operator == (const class ::payload & payload) const
{
   // if variables are equal:
   // all values of both variables should be equal
   return compare(payload) == 0;
}

bool payload::operator > (const class ::payload & payload) const
{
   return compare(payload) > 0;
}

bool payload::operator < (const class ::payload & payload) const
{
   return compare(payload) < 0;
}

bool payload::operator >= (const class ::payload & payload) const
{
   return compare(payload) >= 0;
}

bool payload::operator <= (const class ::payload & payload) const
{
   return compare(payload) <= 0;
}

bool payload::operator != (const class ::payload & payload) const
{
   return compare(payload) != 0;
}

bool payload::operator == (const ::scoped_string & scopedstr) const
{
   return string() == psz;
}

bool payload::operator < (const ::scoped_string & scopedstr) const
{
   return string() < psz;
}

bool payload::operator <= (const ::scoped_string & scopedstr) const
{
   return string() <= psz;
}

bool payload::operator >= (const ::scoped_string & scopedstr) const
{
   return string() >= psz;
}

bool payload::operator > (const ::scoped_string & scopedstr) const
{
   return string() > psz;
}

bool payload::operator != (const ::scoped_string & scopedstr) const
{
   return string() != psz;
}

bool payload::operator == (const ::string & str) const
{
   return string() == str;
}

bool payload::operator != (const ::string & str) const
{
   return string() != str;
}

bool payload::operator < (const ::string & str) const
{
   return string() < str;
}

bool payload::operator <= (const ::string & str) const
{
   return string() <= str;
}

bool payload::operator >= (const ::string & str) const
{
   return string() >= str;
}

bool payload::operator > (const ::string & str) const
{
   return string() > str;
}

bool payload::operator == (::i32 i) const
{
   return i32() == i;
}

bool payload::operator != (::i32 i) const
{
   return i32() != i;
}

bool payload::operator < (::i32 i) const
{
   return i64() < i;
}

bool payload::operator <= (::i32 i) const
{
   return i64() <= i;
}

bool payload::operator >= (::i32 i) const
{
   return i64() >= i;
}

bool payload::operator > (::i32 i) const
{
   return i64() > i;
}











bool payload::operator == (::i64 i) const
{
   return i64() == i;
}

bool payload::operator != (::i64 i) const
{
   return i64() != i;
}

bool payload::operator < (::i64 i) const
{
   return i64() < i;
}

bool payload::operator <= (::i64 i) const
{
   return i64() <= i;
}

bool payload::operator >= (::i64 i) const
{
   return i64() >= i;
}

bool payload::operator > (::i64 i) const
{
   return i32() > i;
}


























bool payload::operator == (bool b) const
{
   return is_equivalent(get_bool(), b);
}

bool payload::operator != (bool b) const
{
   return is_different(get_bool(), b);
}

bool payload::operator < (bool b) const
{
   return is_lesser(get_bool(), b);
}

bool payload::operator <= (bool b) const
{
   return is_lesser_or_equal(get_bool(), b);
}

bool payload::operator >= (bool b) const
{
   return is_greater_or_equal(get_bool(), b);
}

bool payload::operator > (bool b) const
{
   return is_greater(get_bool(), b);
}

//bool payload::strictly_equal(const class ::payload & payload) const
//{
//   return m_etype == payload.m_etype && operator == (payload);
//}
//
//bool payload::strictly_equal(const ::scoped_string & scopedstr) const
//{
//   return m_etype == e_type_string && m_str == psz;
//}
//
//bool payload::strictly_equal(const ::string & str) const
//{
//   return m_etype == e_type_string && m_str == str;
//}
//
//bool payload::strictly_equal(::f64 f64) const
//{
//   return m_etype == e_type_f64 && m_f64 == f64;
//}
//
//bool payload::strictly_equal(::i32 i) const
//{
//   return m_etype == e_type_i32 && m_i32 == i;
//}
//
//bool payload::strictly_equal(bool b) const
//{
//   return m_etype == e_type_bool && is_equivalent(m_b, b);
//}
//
//bool payload::strictly_different(const class ::payload & payload) const
//{
//   return m_etype != payload.m_etype || operator != (payload);
//}
//
//bool payload::strictly_different(const ::scoped_string & scopedstr) const
//{
//   return m_etype != e_type_string || m_str != psz;
//}
//
//bool payload::strictly_different(const ::string & str) const
//{
//   return m_etype != e_type_string || m_str != str;
//}
//
//bool payload::strictly_different(::f64 f64) const
//{
//   return m_etype != e_type_f64 || m_f64 != f64;
//}
//
//bool payload::strictly_different(::i32 i) const
//{
//   return m_etype != e_type_i32 || m_i32 != i;
//}
//
//bool payload::strictly_different(bool b) const
//{
//   return m_etype != e_type_bool || is_different(m_b, b);
//}


string payload::get_recursive_string() const
{

   if(is_array())
   {

      ::string str;

      str += "array (";

      for(::i32 i = 0; i < array_get_count(); i++)
      {
         if(i > 0)
            str += " ";
         str += as_string(i);
         str += " => ";
         str += at(i).get_recursive_string();
         str += ";";
      }
      str += ")";
      return str;
   }
   else
   {
      return ::string();
   }
}

string payload::string(const ::scoped_string & scopedstrOnNull) const
{
   if(m_etype == e_type_payload_pointer)
   {
      return m_ppayload->string(pszOnNull);
   }
   else if (m_etype == e_type_property)
   {
      return m_pproperty->string(pszOnNull);
   }
   else if(m_etype == e_type_pstring)
   {
      return *m_pstr;
   }
   else if(m_etype != e_type_string)
   {
      ::string str;

      if(m_etype == ::e_type_null)
      {
         str = pszOnNull;
      }
      else if(m_etype == ::e_type_i32)
      {
         str = as_string(m_i32);
      }
      else if(m_etype == ::e_type_u32)
      {
         str = as_string( m_u32);
      }
      else if(m_etype == ::e_type_i64)
      {
         str = i64toa_dup(m_i64);
      }
      else if(m_etype == ::e_type_u64)
      {
         str = as_string(m_u64);
      }
      else if(m_etype == ::e_type_f64)
      {
         str = as_string(m_f64);
      }
      else if(m_etype == ::e_type_id)
      {
         str = m_atom;
      }
      else if(m_etype == ::e_type_pid)
      {
         str = *m_pid;
      }
      else if(m_etype == ::e_type_string_array)
      {
         str = stra().implode("");
      }
      else if(m_etype == ::e_type_bool)
      {
         str = as_string((int)m_b);
      }
      else if (is_element_set())
      {
         
         str = as_string(*element());

      }

      return str;

   }
   else
   {
      return m_str;
   }

}

//string & payload::as_string(const ::scoped_string & scopedstrOnNull)
string & payload::string_reference(const ::scoped_string & scopedstrOnNull)
{

   if(m_etype == e_type_string)
   {

      return m_str;

   }
   else if(m_etype == e_type_payload_pointer)
   {

      return m_ppayload->string_reference(pszOnNull);

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->string_reference(pszOnNull);

   }
   else if(m_etype == e_type_pstring)
   {

      return *m_pstr;

   }
   else
   {

      ::string str = this->string(pszOnNull);

      set_string(str);

      return m_str;

   }

}




//const string & payload::get_ref_string(const ::scoped_string & scopedstrOnNull) const
//{
//
//   return ((::payload *)this)->get_ref_string(pszOnNull);
//
//}


::atom payload::atom(const ::atom & idDefault) const
{

   if(m_etype == e_type_payload_pointer)
   {

      return m_ppayload->atom(idDefault);

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->atom(idDefault);

   }
   else if(m_etype == e_type_pid)
   {

      return *m_pid;

   }
   else if(m_etype != e_type_id)
   {

      ::atom atom;

      if (m_etype == ::e_type_i8)
      {

         atom = (::collection::index) m_i8;

      }
      else if (m_etype == ::e_type_u8)
      {

         atom = (::collection::index)m_u8;

      }
      else if (m_etype == ::e_type_i16)
      {

         atom = (::collection::index)m_i8;

      }
      else if (m_etype == ::e_type_u16)
      {

         atom = (::collection::index)m_u8;

      }
      else if(m_etype == ::e_type_i32)
      {
         
         atom = m_i32;

      }
      else if (m_etype == ::e_type_u32)
      {

         atom = (::collection::index) m_u32;

      }
      else if(m_etype == ::e_type_i64)
      {

         atom = (::collection::index) m_i64;

      }
      else if(m_etype == ::e_type_u64)
      {

         atom = (::collection::index) m_u64;

      }
      else if (m_etype == ::e_type_f32)
      {

         ::string str;

         str.formatf("%f", m_f32);

         atom = str;

      }
      else if(m_etype == ::e_type_f64)
      {

         ::string str;

         str.formatf("%f", m_f64);

         atom = str;

      }
      else if(m_etype == ::e_type_string)
      {

         atom = m_str;

      }
      else if(m_etype == ::e_type_pstring)
      {

         atom = *m_pstr;

      }
      else
      {

         atom = idDefault;

      }

      return atom;

   }
   else
   {

      return m_atom;

   }

}


::atom & payload::id_reference(const ::atom & idDefault)
{

   if(m_etype == e_type_payload_pointer)
   {

      return m_ppayload->id_reference(idDefault);

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->id_reference(idDefault);

   }
   else if(m_etype == e_type_pid)
   {

      return *m_pid;

   }
   else
   {

      auto atom = this->atom(idDefault);

      set_type(e_type_id, false);

      m_atom = ::transfer(atom);

      return m_atom;

   }

}



::i32 payload::i32(::i32 iDefault) const
{
   switch(m_etype)
   {
   case e_type_null:
      return iDefault;
   case e_type_empty:
      return iDefault;
   case e_type_string:
      return atoi(m_str);
   case e_type_f64:
      return (::i32) m_f64;
   case e_type_pi8:
      return (::i32)*m_pi8;
   case e_type_pi16:
      return (::i32)*m_pi16;
   case e_type_pi32:
      return (::i32)*m_pi32;
   case e_type_pi64:
      return (::i32)*m_pi64;
   case e_type_pu8:
      return (::i32)*m_pu8;
   case e_type_pu16:
      return (::i32)*m_pu16;
   case e_type_pu32:
      return (::i32)*m_pu32;
   case e_type_pu64:
      return (::i32)*m_pu64;
   case e_type_i8:
      return (::i32) m_i8;
   case e_type_i16:
      return (::i32) m_i32;
   case e_type_i32:
      return m_u32;
   case e_type_i64:
      return (::i32) m_i64;
   case e_type_u8:
      return (::i32)m_u8;
   case e_type_u16:
      return (::i32)m_u16;
   case e_type_u32:
      return (::i32)m_u32;
   case e_type_u64:
      return (::i32) m_u64;
   case e_type_element:
   case e_type_path:
      return iDefault;
   case e_type_payload_pointer:
      return m_ppayload->i32(iDefault);
   case e_type_property:
      return m_pproperty->i32(iDefault);
   case e_type_pstring:
      return atoi(*m_pstr);
   case e_type_id:
   {
      if(!fits_i32(m_atom.i64()))
         throw ::exception(error_overflow, "::payload contains atom that does not fit 32 bit integer");
      return (::i32) (::i64) m_atom;
   }
   case e_type_pid:
   {
      if(!fits_i32(m_pid->i64()))
         throw ::exception(error_overflow, "::payload contains atom that does not fit 32 bit integer");
      return (::i32) (::i64) *m_pid;
   }
   default:
      return iDefault;
   }
}

//
//i32 & payload::as_i32()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_i32();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_i32();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      ::i32 i = this->i32();
//
//      set_type(e_type_i32, false);
//
//      m_i32 = i;
//
//   }
//
//   return m_i32;
//
//}
//


::u32 payload::u32(::u32 uiDefault) const
{
   switch(m_etype)
   {
   case e_type_null:
      return uiDefault;
   case e_type_empty:
      return uiDefault;
   case e_type_string:
      return atoi(m_str);
   case e_type_i32:
      return m_i32;
   case e_type_u32:
      return (::u32) m_u32;
   case e_type_element:
   case e_type_path:
      return (::u32) uiDefault;
   case e_type_i64:
      return (::u32)m_i64;
   case e_type_u64:
      return (::u32) m_u64;
   case e_type_payload_pointer:
      return m_ppayload->u32(uiDefault);
   case e_type_property:
      return m_pproperty->u32(uiDefault);
   default:
      return uiDefault;
   }
}

//
//u32 & payload::as_u32()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_u32();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_u32();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      ::u32 i = this->u32();
//
//      set_type(e_type_u32, false);
//
//      m_u32 = i;
//
//   }
//
//   return m_u32;
//
//}
//
//

::i64 payload::i64(::i64 iDefault) const
{

   try
   {

      switch (m_etype)
      {
      case e_type_null:
         return iDefault;
      case e_type_empty:
         return iDefault;
      case e_type_string:
         return ansi_to_i64(m_str);
      case e_type_i8:
         return m_i8;
      case e_type_u8:
         return m_u8;
      case e_type_i16:
         return m_i16;
      case e_type_u16:
         return m_u16;
      case e_type_i32:
         return m_i32;
      case e_type_u32:
         return m_u32;
      case e_type_i64:
         return m_i64;
      case e_type_u64:
         return m_u64;
      case e_type_pi8:
         if (::is_null(m_p)) return iDefault;
         return *m_pi8;
      case e_type_pu8:
         if (::is_null(m_p)) return iDefault;
         return *m_pu8;
      case e_type_pi16:
         if (::is_null(m_p)) return iDefault;
         return *m_pi16;
      case e_type_pu16:
         if (::is_null(m_p)) return iDefault;
         return *m_pu16;
      case e_type_pi32:
         if (::is_null(m_p)) return iDefault;
         return *m_pi32;
      case e_type_pu32:
         if (::is_null(m_p)) return iDefault;
         return *m_pu32;
      case e_type_pi64:
         if (::is_null(m_p)) return iDefault;
         return *m_pi64;
      case e_type_pu64:
         if (::is_null(m_p)) return iDefault;
         return *m_pu64;
      case e_type_element:
      case e_type_path:
         return iDefault;
      case e_type_payload_pointer:
         return m_ppayload->i64(iDefault);
      case e_type_property:
         return m_pproperty->i64(iDefault);
      case e_type_enum_command:
         return m_ecommand;
      case e_type_enum_status:
         return m_estatus;
      case e_type_enum_check:
         return m_echeck;
      case e_type_enum_flag:
         return m_eflag;
      default:
         return iDefault;

      }
   }
   catch (...)
   {

   }

   return iDefault;

}



#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBERRYPIOS) || defined(WINDOWS)


long payload::get_long(long lDefault) const
{
   
   return (long) this->i64(lDefault);
   
}


unsigned long payload::get_unsigned_long(unsigned long ulDefault) const
{
   
   return (unsigned long) this->u64(ulDefault);
   
}


#endif

//
//i64 & payload::as_i64()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_i64();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_i64();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      ::i64 i = this->i64();
//
//      set_type(e_type_i64, false);
//
//      m_i64 = i;
//
//   }
//
//   return m_i64;
//
//}
//
//

::u64 payload::u64(::u64 uiDefault) const
{
   switch(m_etype)
   {
   case e_type_null:
      return uiDefault;
   case e_type_empty:
      return uiDefault;
   case e_type_string:
      return atol(m_str);
   case e_type_i32:
      return m_i32;
   case e_type_u32:
      return m_u32;
   case e_type_i64:
      return m_i64;
   case e_type_u64:
      return m_u64;
   case e_type_f32:
      return (::u64) m_f32;
   case e_type_f64:
      return (::u64) m_f64;
   case e_type_element:
   case e_type_path:
      return uiDefault;
   case e_type_payload_pointer:
      return m_ppayload->u64(uiDefault);
   case e_type_property:
      return m_pproperty->u64(uiDefault);
   default:
      return uiDefault;
   }

}

//
//
//u64 & payload::as_u64()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_u64();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_u64();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      ::u64 i = this->u64();
//
//      set_type(e_type_u64, false);
//
//      m_u64 = i;
//
//   }
//
//   return m_u64;
//
//}
//


::procedure payload::get_procedure() const
{

   if (get_type() != ::e_type_element)
   {

      return ::procedure();

   }

   return m_p;

}


bool payload::get_bool(bool bDefault) const
{
   
   return is_true(bDefault);

}


::enum_check & payload::enum_check_reference()
{

   if (m_etype != e_type_enum_check)
   {

      m_echeck = get_bool() ? e_check_checked : e_check_unchecked;

   }

   return m_echeck;

}


bool & payload::bool_reference()
{

   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->bool_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->bool_reference();

   }
   else if (m_etype != e_type_bool)
   {

      bool b = is_true();

      set_type(e_type_bool, false);

      m_b = b;

   }

   return m_b;

}



::i8 payload::i8(::i8 iDefault) const
{
   switch (m_etype)
   {
   case e_type_null:
      return iDefault;
   case e_type_empty:
      return iDefault;
   case e_type_i32:
      return (::i8)m_i32;
   case e_type_u32:
      return (::i8)m_u32;
   case e_type_i64:
      return (::i8)m_i64;
   case e_type_u64:
      return (::i8)m_u64;
   case e_type_f32:
      return (::i8) m_f32;
   case e_type_f64:
      return (::i8)m_f64;
   case e_type_string:
#if defined(LINUX) || defined(ANDROID) || defined(FREEBSD)
      return (::i8)atof(m_str);
#else
      return (::i8)_atof_l(m_str, ::acme::get_c_locale());
#endif
   case e_type_payload_pointer:
      return m_ppayload->i8(iDefault);
   case e_type_property:
      return m_pproperty->i8(iDefault);
   default:
      return iDefault;
   }

}







::u8 payload::u8(::u8 uDefault) const
{
   switch (m_etype)
   {
   case e_type_null:
      return uDefault;
   case e_type_empty:
      return uDefault;
   case e_type_i32:
      return (::u8)m_i32;
   case e_type_u32:
      return (::u8)m_u32;
   case e_type_i64:
      return (::u8)m_i64;
   case e_type_u64:
      return (::u8)m_u64;
   case e_type_f32:
      return (::u8)m_f32;
   case e_type_f64:
      return (::u8)m_f64;
   case e_type_string:
#if defined(LINUX) || defined(ANDROID) || defined(FREEBSD)
      return (::u8)atof(m_str);
#else
      return (::u8)_atof_l(m_str, ::acme::get_c_locale());
#endif
   case e_type_payload_pointer:
      return m_ppayload->u8(uDefault);
   case e_type_property:
      return m_pproperty->u8(uDefault);
   default:
      return uDefault;
   }

}


//u8 & payload::as_u8()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_u8();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_u8();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      ::u8 i = this->u8();
//
//      set_type(e_type_u8, false);
//
//      m_u8 = i;
//
//   }
//
//   return m_u8;
//
//}



::i16 payload::i16(::i16 iDefault) const
{
   switch (m_etype)
   {
   case e_type_null:
      return iDefault;
   case e_type_empty:
      return iDefault;
   case e_type_i32:
      return (::i16)m_i32;
   case e_type_u32:
      return (::i16)m_u32;
   case e_type_i64:
      return (::i16)m_i64;
   case e_type_u64:
      return (::i16)m_u64;
   case e_type_f32:
      return (::i16)m_f32;
   case e_type_f64:
      return (::i16)m_f64;
   case e_type_string:
#if defined(LINUX) || defined(ANDROID) || defined(FREEBSD)
      return (::i16)atof(m_str);
#else
      return (::i16)_atof_l(m_str, ::acme::get_c_locale());
#endif
   case e_type_payload_pointer:
      return m_ppayload->i16(iDefault);
   case e_type_property:
      return m_pproperty->i16(iDefault);
   default:
      return iDefault;
   }

}



//i16 & payload::as_i16()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_i16();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_i16();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      ::i16 i = this->i16();
//
//      set_type(e_type_i16, false);
//
//      m_i16 = i;
//
//   }
//
//   return m_i16;
//
//}



::u16 payload::u16(::u16 uDefault) const
{
   switch (m_etype)
   {
   case e_type_null:
      return uDefault;
   case e_type_empty:
      return uDefault;
   case e_type_i32:
      return (::u16)m_i32;
   case e_type_u32:
      return (::u16)m_u32;
   case e_type_i64:
      return (::u16)m_i64;
   case e_type_u64:
      return (::u16)m_u64;
   case e_type_f32:
      return (::u16)m_f32;
   case e_type_f64:
      return (::u16)m_f64;
   case e_type_string:
#if defined(LINUX) || defined(ANDROID) || defined(FREEBSD)
      return (::u16)atof(m_str);
#else
      return (::u16)_atof_l(m_str, ::acme::get_c_locale());
#endif
   case e_type_payload_pointer:
      return m_ppayload->u16(uDefault);
   case e_type_property:
      return m_pproperty->u16(uDefault);
   default:
      return uDefault;
   }

}


//
//u16 & payload::as_u16()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_u16();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_u16();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      ::u16 i = this->u16();
//
//      set_type(e_type_u16, false);
//
//      m_u16 = i;
//
//   }
//
//   return m_u16;
//
//}
//


::f32 payload::f32(::f32 fDefault) const
{
   switch(m_etype)
   {
   case e_type_null:
      return fDefault;
   case e_type_empty:
      return fDefault;
   case e_type_i32:
      return (::f32) m_i32;
   case e_type_u32:
      return (::f32) m_u32;
   case e_type_i64:
      return (::f32) m_i64;
   case e_type_u64:
      return (::f32) m_u64;
   case e_type_f32:
      return m_f32;
   case e_type_f64:
      return (::f32) m_f64;
   case e_type_string:
   #if defined(LINUX) || defined(ANDROID) || defined(FREEBSD)
      return (::f32) atof(m_str);
   #else
      return (::f32) _atof_l(m_str, ::acme::get_c_locale());
   #endif
   case e_type_payload_pointer:
      return m_ppayload->f32(fDefault);
   case e_type_property:
      return m_pproperty->f32(fDefault);
   default:
      return fDefault;
   }

}
//
//f32 & payload::as_f32()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_f32();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_f32();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      ::f32 i = this->f32();
//
//      set_type(e_type_f32, false);
//
//      m_f32 = i;
//
//   }
//
//   return m_f32;
//
//}
//



//::image::image *payload::image::image() const
//{
//
//   if (m_etype != ::e_type_element)
//   {
//
//      return nullptr;
//
//   }
//
//   return cast < ::image::image >();
//
//}


::f64 payload::f64(::f64 dDefault) const
{
   ::f64 f64;
   if(m_etype == e_type_null)
   {
      return dDefault;
   }
   else if(m_etype == e_type_empty)
   {
      return dDefault;
   }
   else if(m_etype == ::e_type_i32)
   {
      f64 = (::f64) m_i32;
   }
   else if(m_etype == ::e_type_u32)
   {

      f64 = (::f64) m_u32;

   }
   else if(m_etype == ::e_type_i64)
   {

      f64 = (::f64) m_i64;

   }
   else if(m_etype == ::e_type_u64)
   {

      f64 = (::f64) m_u64;

   }
   else if(m_etype == ::e_type_f32)
   {

      f64 = (::f64) m_f32;

   }
   else if(m_etype == ::e_type_f64)
   {

      f64 = m_f64;

   }
   else if(m_etype == ::e_type_string)
   {

#if defined(LINUX) || defined(ANDROID) || defined(FREEBSD)

      f64 = atof(m_str);

#else

      f64 = _atof_l(m_str, ::acme::get_c_locale());

#endif

   }
   else if(m_etype == ::e_type_payload_pointer)
   {

      f64 = m_ppayload->f64(dDefault);

   }
   else if (m_etype == ::e_type_property)
   {

      f64 = m_pproperty->f64(dDefault);

   }
   else
   {

      return dDefault;

   }

   return f64;

}

//
//f64 & payload::as_f64()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_f64();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_f64();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      ::f64 i = this->f64();
//
//      set_type(e_type_f64, false);
//
//      m_f64 = i;
//
//   }
//
//   return m_f64;
//
//}
//


::color::color payload::color(const ::color::color & colorDefault) const
{

   color::color color;

   if(m_etype == e_type_color)
   {

      color = m_color;

   }
   else if(m_etype == e_type_hls)
   {

      color = m_hls;

   }
   else
   {

      color = colorDefault;

   }

   return color;

}


::color::hls payload::hls(const ::color::hls & hlsDefault) const
{

   color::hls hls;

   if(m_etype == e_type_color)
   {

      hls = m_color;

   }
   else if(m_etype == e_type_hls)
   {

      hls = m_hls;

   }
   else
   {

      hls = hlsDefault;

   }

   return hls;

}


class ::memory & payload::memory_reference()
{

   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->memory_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->memory_reference();

   }
   else if(m_etype != e_type_memory)
   {

      set_type(e_type_memory, false);

      m_pmemory = ___new ::memory ();

   }
   else if(::is_null(m_pmemory))
   {

      m_pmemory = ___new ::memory ();

   }

   return *m_pmemory;

}


::memory payload::memory() const
{

   if (m_etype != e_type_memory)
   {

      return memory();

   }

   return *m_pmemory;

}


::file::path & payload::file_path_reference()
{

   if (m_etype == ::e_type_payload_pointer)
   {

      return m_ppayload->file_path_reference();

   }
   else if (m_etype == ::e_type_property)
   {

      return m_pproperty->file_path_reference();

   }
   else if (m_etype != ::e_type_path)
   {

      auto ppath = ___new ::file::path_object ();

      ppath->assign(get_file_path());

      set_type(e_type_path, false);

      m_ppath = ppath;

   }

   return *m_ppath;

}


payload::operator ::file::path() const
{

   return get_file_path();

}


string_array payload::stra() const
{

   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->stra();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->stra();

   }
   else if (m_etype != e_type_string_array)
   {

      string_array stra;

      try
      {

         auto c = array_get_count();

         for (::collection::index i = 0; i < c; i++)
         {

            stra.add(at(i).get_string());

         }

      }
      catch (...)
      {

      }

      //set_type(e_type_string_array, false);

      //m_pstra = pstra;

      return stra;

   }
   else if (::is_null(m_pstra))
   {

      //m_pstra = ___new string_array();

      return string_array();

   }

   return *m_pstra;

}


string_array & payload::stra_reference()
{

   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->stra_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->stra_reference();

   }
   else if (m_etype != e_type_string_array)
   {

      auto pstra = ___new string_array();

      try
      {

         auto c = array_get_count();

         for (::collection::index i = 0; i < c; i++)
         {

            pstra->add(at(i).get_string());

         }

      }
      catch (...)
      {

      }

      set_type(e_type_string_array, false);

      m_pstra = pstra;

   }
   else if(::is_null(m_pstra))
   {

      m_pstra = ___new string_array();

   }

   return *m_pstra;

}


::i32_array payload::ia() const
{

   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->ia();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->ia();

   }
   else if (m_etype != e_type_i32_array)
   {

      ::i32_array ia;

      try
      {

         auto c = array_get_count();

         for (::collection::index i = 0; i < c; i++)
         {

            ia.add(at(i).i32());

         }

      }
      catch (...)
      {

      }

      return ia;

   }
   else if (::is_null(m_pia))
   {

      return ::i32_array();

   }

   return *m_pia;

}


::i32_array & payload::ia_reference()
{

   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->ia_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->ia_reference();

   }
   else if(m_etype != e_type_i32_array)
   {

      auto pia = ___new ::i32_array ();

      try
      {

         auto c = array_get_count();

         for(::collection::index i = 0; i < c; i++)
         {

            pia->add(at(i).i32());

         }

      }
      catch(...)
      {

      }

      set_type(e_type_i32_array, false);

      m_pia = pia;

   }
   else if (::is_null(m_pia))
   {

      m_pia = ___new ::i32_array ();

   }

   return *m_pia;

}


i64_array payload::i64a() const
{

   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->i64a();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->i64a();

   }
   else if (m_etype != e_type_i64_array)
   {

      i64_array i64a;

      try
      {

         auto c = array_get_count();

         for (::collection::index i = 0; i < c; i++)
         {

            i64a.add(at(i).i64());

         }

      }
      catch (...)
      {

      }

      //set_type(e_type_i64_array, false);

      //m_pi64a = pia64;

      return i64a;

   }
   else if (::is_null(m_pi64a))
   {

      //m_pi64a = ___new i64_array();
      return i64_array();

   }

   return *m_pi64a;

}


i64_array & payload::i64a_reference()
{

   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->i64a_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->i64a_reference();

   }
   else if(m_etype != e_type_i64_array)
   {

      auto pia64  = ___new i64_array();

      try
      {

         auto c = array_get_count();

         for (::collection::index i = 0; i < c; i++)
         {

            pia64->add(at(i).i64());

         }

      }
      catch (...)
      {

      }

      set_type(e_type_i64_array, false);

      m_pi64a = pia64;

   }
   else if(::is_null(m_pi64a))
   {

      m_pi64a = ___new i64_array();

   }

   return *m_pi64a;

}


time payload::time() const
{

   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->time();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->time();

   }
   else    if (m_etype == e_type_time)
   {

      return m_time;

   }
   else if (m_etype == e_type_ptime)
   {

      return *m_ptime;

   }
   else if(is_integer())
   {

      return integral_second(i64());

   }
   else if (is_floating())
   {

      return floating_second(f64());

   }
   else
   {

      return floating_second(f64());

   }

}



time & payload::time_reference()
{

   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->time_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->time_reference();

   }
   else if (m_etype == e_type_time)
   {

      return m_time;

   }
   else if (m_etype == e_type_ptime)
   {

      return *m_ptime;

   }
   else
   {

      set_type(e_type_time);

      m_time.set_null();

      return m_time;

   }

}


//string_array payload::stra() const
//{
//
//   return ((::payload *)this)->stra();
//
//}
//

//const ::i32_array & payload::ia() const
//{
//
//   return ((::payload *)this)->ia();
//
//}


//const i64_array & payload::i64a() const
//{
//
//   return ((::payload *)this)->int64a();
//
//}


class ::payload & payload::operator = (::payload * pvar)
{

   if (m_ppayload == pvar)
   {

      return *this;

   }

   set_type(e_type_payload_pointer, false);

   m_ppayload = pvar;

   return *this;

}


class ::payload & payload::operator = (const ::payload * pvar)
{

   return operator =((::payload*)pvar);

}


payload_array payload::payloada() const
{

   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->payloada();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->payloada();

   }
   else if (m_etype != e_type_payload_array)
   {

      payload_array payloada;

      try
      {

         if (is_empty() || !get_bool())
         {

         }
         else
         {

            for (::i32 i = 0; i < array_get_count(); i++)
            {

               payloada.add(at(i));

            }

         }

      }
      catch (...)
      {

      }

      //set_type(e_type_payload_array, false);

      //m_ppayloada = pvara;

      return payloada;

   }
   else if (::is_null(m_ppayloada))
   {

      //m_ppayloada = ___new payload_array();

      return payload_array();

   }

   return *m_ppayloada;

}


payload_array & payload::payloada_reference()
{

   if(m_etype == e_type_payload_pointer)
   {

      return m_ppayload->payloada_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->payloada_reference();

   }
   else if(m_etype != e_type_payload_array)
   {

      auto pvara  = ___new payload_array();

      try
      {

         if (is_empty() || !get_bool())
         {

         }
         else
         {

            for (::i32 i = 0; i < array_get_count(); i++)
            {

               pvara->add(at(i));

            }

         }

      }
      catch (...)
      {

      }

      set_type(e_type_payload_array, false);

      m_ppayloada = pvara;

   }
   else if (::is_null(m_ppayloada))
   {

      m_ppayloada = ___new payload_array();

   }

   return *m_ppayloada;

}


property_set payload::propset() const
{

   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->propset();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->propset();

   }
   else if (m_etype != e_type_property_set)
   {

      property_set set;

      if (is_empty() || !get_bool())
      {

      }
      else
      {

         for (::i32 i = 0; i < array_get_count(); i++)
         {

            set.set_at(i, at(i));

         }

      }

      //set_type(e_type_property_set, false);

      //m_ppropertyset = pset;

      return set;

   }
   else if (::is_null(m_ppropertyset))
   {

      //m_ppropertyset = ___new property_set();

      return property_set();

   }

   return *m_ppropertyset;

}


property_set & payload::propset_reference()
{

   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->propset_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->propset_reference();

   }
   else if (m_etype != e_type_property_set)
   {

      auto pset = ___new property_set();

      if (is_empty() || !get_bool())
      {

      }
      else
      {

         for (::i32 i = 0; i < array_get_count(); i++)
         {

            pset->set_at(i, at(i));

         }

      }

      set_type(e_type_property_set, false);

      m_ppropertyset = pset;

   }
   else if (::is_null(m_ppropertyset))
   {

      m_ppropertyset = ___new property_set();

   }

   return *m_ppropertyset;

}


//const payload_array & payload::as_payloada() const
//{
//
//   return ((::payload *)this)->payloada();
//
//}


//const ::time & payload::as_time() const
//{
//
//   return ((::payload *)this)->time();
//
//}


//const property_set & payload::as_propset() const
//{
//
//   return ((::payload *)this)->propset();
//
//}


::property payload::property() const
{

   if (m_etype != e_type_property)
   {

      throw ::exception(error_wrong_state, "::payload is not a property (1)");

   }

   return *m_pproperty;

}



property & payload::property_reference()
{

   if(m_etype != e_type_property)
   {

      throw ::exception(error_wrong_state, "::payload is not a property (1)");

   }

   return *m_pproperty;

}


//const property & payload::property() const
//{
//
//   return ((::payload *)this)->property();
//
//}


string payload::implode(const ::scoped_string & scopedstrGlue) const
{

   if(get_type() == e_type_property_set)
   {

      return propset().implode(pszGlue);

   }
   else if(get_type() == e_type_payload_array)
   {

      return payloada().implode(pszGlue);

   }
   else if(get_type() == e_type_string_array)
   {

      return stra().implode(pszGlue);

   }

   return "";

}


::payload payload::explode(const ::scoped_string & scopedstrGlue, bool bAddEmpty) const
{

   class ::payload payload;

   payload.stra().add_tokens(string(), pszGlue, bAddEmpty);

   return payload;

}




::comparison::var_strict payload::strictly_compare() const
{

   return *this;

}


::payload payload::dereference()
{
   if(get_type() == e_type_payload_pointer)
      return m_ppayload->dereference();
   else if (get_type() == e_type_property)
      return m_pproperty->dereference();
   else if(get_type() == e_type_pstring)
      return *m_pstr;
   else if(get_type() == e_type_i32)
      return *m_pi32;
   else if(get_type() == e_type_pbool)
      return *m_pb;
   else
      return *this;
}


//::payload payload::at(::collection::index i) const
//{
//
//   switch(m_etype)
//   {
//   case e_type_i32_array:
//      return &m_pia->element_at(i);
//   case e_type_string_array:
//      return &m_pstra->element_at(i);
//   case e_type_payload_array:
//      return &m_ppayloada->element_at(i);
//   case e_type_property_set:
//      return &m_ppropertyset->element_at(i).element2();
//   case e_type_payload_pointer:
//      return m_ppayload->at(i);
//   default:
//      if(i == 0)
//      {
//         return (::payload *) this;
//      }
//      else
//      {
//         throw ::exception(::exception("index out of bounds"));
//      }
//   }
//}


::payload payload::at(::collection::index i)
{
   switch(m_etype)
   {
   case e_type_i32_array:
      return &m_pia->element_at(i);
   case e_type_string_array:
      return &m_pstra->element_at(i);
   case e_type_payload_array:
      return &m_ppayloada->element_at(i);
   case e_type_property_set:
      return m_ppropertyset->ptr_at(i);
   case e_type_payload_pointer:
      return m_ppayload->at(i);
   case e_type_property:
      return m_pproperty->at(i);
   default:
      if(i == 0)
      {
         return this;
      }
      else
      {

         throw ::exception(error_index_out_of_bounds, "index out of bounds");

         return error_failed;

      }

   }

}


bool payload::array_contains(const ::scoped_string & scopedstr, ::collection::index find, ::collection::count count) const
{

   switch(m_etype)
   {
   case e_type_i32_array:
      return ia().contains(atoi(psz), find, count);
   case e_type_string_array:
      return stra().contains(psz, find, count);
   case e_type_payload_array:
      return payloada().contains(psz, find, count);
   case e_type_property_set:
      return propset().contains_payload(psz, find, count);
   default:
   {
      ::collection::index upperbound = minimum(array_get_upper_bound(), find + count - 1);
      for(::collection::index i = find; i <= upperbound; i++)
      {
         if(at(i) == psz)
         {
            return true;
         }
      }
   }
   }
   return false;
}

bool payload::case_insensitive_array_contains(const ::scoped_string & scopedstr, ::collection::index find, ::collection::index last) const
{
   switch(m_etype)
   {
   case e_type_bool:
      return false;
   case e_type_i32_array:
      return ia().contains(atoi(psz), find, last);
   case e_type_string_array:
      return stra().case_insensitive_contains(psz, find, last);
   case e_type_payload_array:
      return payloada().case_insensitive_contains(psz, find, last);
   case e_type_property_set:
      return propset().case_insensitive_contains_value(psz, find, last);
   default:
   {
      ::collection::index upperbound = minimum(array_get_upper_bound(), last);
      for(::collection::index i = find; i <= upperbound; i++)
      {
         if(at(i).string().case_insensitive_order(psz) == 0)
         {
            return true;
         }
      }
   }
   }
   return false;
}


::payload payload::equals_ci_get(const ::scoped_string & scopedstrCompare, ::payload varOnEqual, ::payload varOnDifferent) const
{
   if(case_insensitive_order(pszCompare) == 0)
   {
      return varOnEqual;
   }
   else
   {
      return varOnDifferent;
   }
}

::payload payload::equals_ci_get(const ::scoped_string & scopedstrCompare, ::payload varOnEqual) const
{
   if(case_insensitive_order(pszCompare) == 0)
   {
      return varOnEqual;
   }
   else
   {
      return payload();
   }
}



::payload payload::operator + (const ::string & str) const
{

   ::payload varRet(*this);

   if (varRet.is_floating())
   {

      if (::str::is_integer(str))
      {

         varRet += strtod(str, nullptr);

      }
      else
      {

         varRet.set_string(varRet.string() + str);

      }

   }
   else if (varRet.is_integer())
   {

      if (::str::is_integer(str))
      {

         varRet += ansi_to_i64(str);

      }
      else
      {

         varRet.set_string(varRet.string() + str);

      }

   }
   else
   {

      varRet.set_string(varRet.string() + str);

   }

   return varRet;

}


::payload payload::operator + (const ::scoped_string & scopedstr) const
{
   
   return *this + ::string(psz); 

}












//
//
//
//
//::payload payload::operator / (::i32 i) const
//{
//   return i32() / i;
//}
//
//::payload payload::operator / (::u32 user) const
//{
//   return u32() / user;
//}
//
//::payload payload::operator / (::i64 l) const
//{
//   return i64() / l;
//}
//
//::payload payload::operator / (::u64 ul) const
//{
//
//   switch(m_etype)
//   {
//   case ::e_type_null:
//      return payload(e_type_null);
//   case ::e_type_empty:
//      return 0.0 / ul; // throws division by zero exception if ul stream zero
//   case ::e_type_i32:
//      return m_i32 / (::collection::index) ul;
//   case ::e_type_u32:
//      return m_u32 / (::uptr) ul;
//   case ::e_type_i64:
//      return m_i64 / (::i64) ul;
//   case ::e_type_u64:
//      return m_u64 / (::u64) ul;
//   case ::e_type_f32:
//      return m_f32 / (::f32) ul;
//   case ::e_type_f64:
//      return m_f64 / (::f64) ul;
//   case ::e_type_string:
//#if defined(LINUX) || defined(ANDROID)
//      return atof(m_str) / (::f64) ul;
//#else
//      return _atof_l(m_str, ::acme::get_c_locale()) / (::f64) ul;
//#endif
//   case ::e_type_payload_pointer:
//      return m_ppayload->operator / (ul);
//   case ::e_type_property:
//      return m_pproperty->operator / (ul);
//   default:
//      return 0.0 / ul; // throws division by zero exception if ul stream zero
//   }
//
//}
//
//::payload payload::operator / (f64 f64) const
//{
//   return f64() / f64;
//}
//
//::payload operator / (::i32 i, const class ::payload & payload)
//{
//   return i / payload.i32();
//}
//
//::payload operator / (::u32 user, const class ::payload & payload)
//{
//   return user / payload.u32();
//}
//
//::payload operator / (::i64 l, const class ::payload & payload)
//{
//   return l / payload.i64();
//}
//
//
//::payload operator / (::u64 ul, const class ::payload & payload)
//{
//   switch(payload.m_etype)
//   {
//   case ::e_type_null:
//      throw ::exception(::exception("division by zero"));
//   case ::e_type_empty:
//      throw ::exception(::exception("division by zero"));
//   case ::e_type_i32:
//      return (iptr) ul / payload.m_i32;
//   case ::e_type_u32:
//      return (uptr) ul / payload.m_u32;
//   case ::e_type_i64:
//      return (::i64) ul / payload.m_i64;
//   case ::e_type_u64:
//      return (::u64) ul / payload.m_u64;
//   case ::e_type_f32:
//      return (::f32) ul / payload.m_f32;
//   case ::e_type_f64:
//      return (::f64) ul / payload.m_f64;
//   case ::e_type_string:
//#if defined(LINUX) || defined(ANDROID)
//      return (::f64) ul / atof(payload.m_str);
//#else
//      return (::f64) ul / _atof_l(payload.m_str, ::acme::get_c_locale());
//#endif
//   case ::e_type_payload_pointer:
//      return operator / (ul, *payload.m_ppayload);
//   case ::e_type_property:
//      return operator / (ul, *payload.m_pproperty);
//   default:
//      throw ::exception(::exception("division by zero"));
//   }
//
//}
//
//
//
//
//::payload operator / (f64 f64, const class ::payload & payload)
//{
//   return f64 / payload.f64();
//}
//
//
//::payload payload::operator * (::i32 i) const
//{
//   return i32() * i;
//}
//
//::payload payload::operator * (::u32 user) const
//{
//   return u32() * user;
//}
//
//::payload payload::operator * (::i64 l) const
//{
//   return i64() * l;
//}
//
//::payload payload::operator * (::u64 ul) const
//{
//   switch(m_etype)
//   {
//   case ::e_type_null:
//      return payload(e_type_null);
//   case ::e_type_empty:
//      return 0.0;
//   case ::e_type_i32:
//      return m_i32 * (::collection::index) ul;
//   case ::e_type_u32:
//      return m_u32 * (::uptr) ul;
//   case ::e_type_i64:
//      return m_i64 * (::i64) ul;
//   case ::e_type_u64:
//      return m_u64 * (::u64) ul;
//   case ::e_type_f32:
//      return m_f32 * (::f32) ul;
//   case ::e_type_f64:
//      return m_f64 * (::f64) ul;
//   case ::e_type_string:
//#if defined(LINUX) || defined(ANDROID)
//
//      return atof(m_str) * (::f64) ul;
//#else
//      return _atof_l(m_str, ::acme::get_c_locale()) * (::f64) ul;
//#endif
//   case ::e_type_payload_pointer:
//      return m_ppayload->operator * (ul);
//   case ::e_type_property:
//      return m_pproperty->operator * (ul);
//   default:
//      return 0.0;
//   }
//
//}
//
//::payload payload::operator * (f64 f64) const
//{
//   return f64() * f64;
//}
//
//::payload operator * (::i32 i, const class ::payload & payload)
//{
//   return i * payload.i32();
//}
//
//::payload operator * (::u32 user, const class ::payload & payload)
//{
//   return user * payload.u32();
//}
//
//::payload operator * (::i64 l, const class ::payload & payload)
//{
//   return l * payload.i64();
//}
//
//::payload operator * (::u64 ul, const class ::payload & payload)
//{
//
//   switch(payload.m_etype)
//   {
//   case ::e_type_null:
//      return ::e_type_null;
//   case ::e_type_empty:
//      return 0;
//   case ::e_type_i32:
//      return (iptr) ul * payload.m_i32;
//   case ::e_type_u32:
//      return (uptr) ul * payload.m_u32;
//   case ::e_type_i64:
//      return (::i64) ul * payload.m_i64;
//   case ::e_type_u64:
//      return (::u64) ul * payload.m_u64;
//   case ::e_type_f32:
//      return (::f32) ul * payload.m_f32;
//   case ::e_type_f64:
//      return (::f64) ul * payload.m_f64;
//   case ::e_type_string:
//#if defined(LINUX) || defined(ANDROID)
//      return (::f64) ul * atof(payload.m_str);
//#else
//      return (::f64) ul * _atof_l(payload.m_str, ::acme::get_c_locale());
//#endif
//   case ::e_type_payload_pointer:
//      return operator * (ul, *payload.m_ppayload);
//   case ::e_type_property:
//      return operator * (ul, *payload.m_pproperty);
//   default:
//      return 0;
//   }
//
//}
//
//
//::payload operator * (f64 f64, const class ::payload & payload)
//{
//   return f64 * payload.f64();
//}
//




















//
//class ::payload & payload::operator -= (::i32 i)
//{
//   operator =(*this - i);
//   return *this;
//}
//
//class ::payload & payload::operator -= (::u32 user)
//{
//   operator =(*this - user);
//   return *this;
//}
//
//class ::payload & payload::operator -= (::i64 i)
//{
//   operator =(*this - i);
//   return *this;
//}
//
//class ::payload & payload::operator -= (::u64 user)
//{
//   operator =(*this - user);
//   return *this;
//}
//
//class ::payload & payload::operator -= (f64 f64)
//{
//   operator =(*this - f64);
//   return *this;
//}
//
//class ::payload & payload::operator -= (const class ::payload & payload)
//{
//   operator =(*this - payload);
//
//   return *this;
//
//}
//
//
//
//

//
//
//
//class ::payload & payload::operator += (::i32 i)
//{
//   operator =(*this + i);
//   return *this;
//}
//
//class ::payload & payload::operator += (::u32 user)
//{
//   operator =(*this + user);
//   return *this;
//}
//
//class ::payload & payload::operator += (::i64 i)
//{
//   operator =(*this + i);
//   return *this;
//}
//
//class ::payload & payload::operator += (::u64 user)
//{
//   operator =(*this + user);
//   return *this;
//}
//
//class ::payload & payload::operator += (f64 f64)
//{
//   operator =(*this + f64);
//   return *this;
//}
//
//class ::payload & payload::operator += (const class ::payload & payload)
//{
//   operator =(*this + payload);
//   return *this;
//}
//
//
//
//



















//
//class ::payload & payload::operator /= (::i32 i)
//{
//   operator =(*this / i);
//   return *this;
//}
//
//class ::payload & payload::operator /= (::u32 user)
//{
//   operator =(*this / user);
//   return *this;
//}
//
//class ::payload & payload::operator /= (::i64 i)
//{
//   operator =(*this / i);
//   return *this;
//}
//
//class ::payload & payload::operator /= (::u64 user)
//{
//   operator =(*this / user);
//   return *this;
//}
//
//class ::payload & payload::operator /= (f64 f64)
//{
//   operator =(*this / f64);
//   return *this;
//}
//
//class ::payload & payload::operator /= (const class ::payload & payload)
//{
//   operator =(*this / payload);
//   return *this;
//}
//
//
//
//
//
//















//
//
//
//class ::payload & payload::operator *= (::i32 i)
//{
//   operator =(*this * i);
//   return *this;
//}
//
//class ::payload & payload::operator *= (::u32 user)
//{
//   operator =(*this * user);
//   return *this;
//}
//
//class ::payload & payload::operator *= (::i64 i)
//{
//   operator =(*this * i);
//   return *this;
//}
//
//class ::payload & payload::operator *= (::u64 user)
//{
//   operator =(*this * user);
//   return *this;
//}
//
//class ::payload & payload::operator *= (f64 f64)
//{
//   operator =(*this * f64);
//   return *this;
//}
//
//
//class ::payload & payload::operator *= (const class ::payload & payload)
//{
//
//   operator =(*this * payload);
//
//   return *this;
//
//}


























bool payload::is_scalar() const
{
   if(m_etype == e_type_new
         || m_etype == e_type_null
         || m_etype == e_type_empty)
   {
      return false;
   }
   else if(m_etype == e_type_string
           || m_etype == e_type_i32
           || m_etype == e_type_i32
           || m_etype == e_type_u32
           || m_etype == e_type_bool
           || m_etype == e_type_f64)
   {
      return true;
   }
   else if(m_etype == e_type_string_array
           || m_etype == e_type_i32_array
           || m_etype == e_type_payload_array
           || m_etype == e_type_property_set)
   {
      return false;
   }
   else if(m_etype == e_type_property)
   {
      return property().is_scalar();
   }
   else if(m_etype == e_type_element)
   {
      return false;
   }
   else if (m_etype == e_type_path)
   {
      return false;
   }
   else
   {
      return false;
   }
}


bool payload::is_floating() const
{

   if(m_etype == e_type_f64 || m_etype == e_type_f32)
   {

      return true;

   }
   // simple, lazy, slow, and a bit incorrect
   // incorrect because atof and atoi returns partials results even if it
   // encounters non-numerical symbols
   else
   {

      ::string str = string();

#if defined(LINUX) || defined(ANDROID) || defined(FREEBSD)
      if(is_scalar()
            && (fmod(atof(str), 1.0) == 0.0
                && fabs(atof(str)) <= pow(2.0, 31.0)))
#else
      if(is_scalar()
            && (fmod(_atof_l(str, ::acme::get_c_locale()), 1.0) == 0.0
                && fabs(_atof_l(str, ::acme::get_c_locale())) <= pow(2.0, 31.0)))
#endif
      {
         str.trim();
         if(str.length() == 0)
            return false;
         else if(str[0] == '+'
                 || str[0] == '-'
                 || ansi_char_isdigit(str[0]))
         {
            ::i32 i;
            for(i = 1; i < str.length(); i++)
            {
               if(ansi_char_isdigit(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot1;
               }
               if(character_isspace(str[i]))
               {
                  i++;
                  goto sp1;
               }
               if(str[i] == 'e' || str[i] == 'E')
               {
                  i++;
                  goto e;
               }
               return false;
            }
dot1:
            for(; i < str.length(); i++)
            {
               if(ansi_char_isdigit(str[i]))
                  continue;
               if(str[i] == 'e' || str[i] == 'E')
                  goto e;
               return false;
            }
sp1:
            for(; i < str.length(); i++)
            {
               if(character_isspace(str[i]))
                  continue;
               if(str[i] == 'e' || str[i] == 'E')
                  goto e;
               return false;
            }
e:
//sp2:
            for(; i < str.length(); i++)
            {
               if(character_isspace(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot2;
               }
               if(ansi_char_isdigit(str[i]))
               {
                  i++;
                  break;
               }
               return false;
            }
            for(; i < str.length(); i++)
            {
               if(ansi_char_isdigit(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot2;
               }
               return false;
            }
dot2:
            for(; i < str.length(); i++)
            {
               if(ansi_char_isdigit(str[i]))
                  continue;
               return false;
            }
            return true;
         }
         else
            return false;
      }
      else
      {
         return false;
      }
   }

}


bool payload::is_boolean() const
{
   if (m_etype == e_type_f64)
   {
      return true;
   }
   return false;
}

bool payload::is_double() const
{
   if(m_etype == e_type_f64)
   {
      return true;
   }
   // simple, lazy, slow, and a bit incorrect
   // incorrect because atof and atoi returns partials results even if it
   // encounters non-numerical symbols
   else
   {
      
      ::string str = string();

#if defined(LINUX) || defined(ANDROID) || defined(FREEBSD)
      if(is_scalar()
            && (fmod(atof(str), 1.0) == 0.0
                && fabs(atof(str)) <= pow(2.0, 31.0)))
#else
      if(is_scalar()
            && (fmod(_atof_l(str, ::acme::get_c_locale()), 1.0) == 0.0
                && fabs(_atof_l(str, ::acme::get_c_locale())) <= pow(2.0, 31.0)))
#endif
      {
         str.trim();
         if(str.length() == 0)
            return false;
         else if(str[0] == '+'
                 || str[0] == '-'
                 || ansi_char_isdigit(str[0]))
         {
            ::i32 i;
            for(i = 1; i < str.length(); i++)
            {
               if(ansi_char_isdigit(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot1;
               }
               if(character_isspace(str[i]))
               {
                  i++;
                  goto sp1;
               }
               if(str[i] == 'e' || str[i] == 'E')
               {
                  i++;
                  goto e;
               }
               return false;
            }
dot1:
            for(; i < str.length(); i++)
            {
               if(ansi_char_isdigit(str[i]))
                  continue;
               if(str[i] == 'e' || str[i] == 'E')
                  goto e;
               return false;
            }
sp1:
            for(; i < str.length(); i++)
            {
               if(character_isspace(str[i]))
                  continue;
               if(str[i] == 'e' || str[i] == 'E')
                  goto e;
               return false;
            }
e:
//sp2:
            for(; i < str.length(); i++)
            {
               if(character_isspace(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot2;
               }
               if(ansi_char_isdigit(str[i]))
               {
                  i++;
                  break;
               }
               return false;
            }
            for(; i < str.length(); i++)
            {
               if(ansi_char_isdigit(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot2;
               }
               return false;
            }
dot2:
            for(; i < str.length(); i++)
            {
               if(ansi_char_isdigit(str[i]))
                  continue;
               return false;
            }
            return true;
         }
         else
            return false;
      }
      else
      {
         return false;
      }
   }

}

bool payload::is_integer() const
{
   if(m_etype == e_type_i32 || m_etype == e_type_i64)
   {
      return true;
   }
   // simple, lazy, slow, and a bit incorrect
   // incorrect because atof and atoi returns partials results even if it
   // encounters non-numerical symbols
   else
   {
      
      ::string str = string();

#if defined(LINUX) || defined(ANDROID) || defined(FREEBSD)
      if(is_scalar()
            && (fmod(atof(str), 1.0) == 0.0
                && fabs(atof(str)) <= pow(2.0, 31.0)))
#else
      if(is_scalar()
            && (fmod(_atof_l(str, ::acme::get_c_locale()), 1.0) == 0.0
                && fabs(_atof_l(str, ::acme::get_c_locale())) <= pow(2.0, 31.0)))
#endif
      {
         str.trim();
         if(str.length() == 0)
            return false;
         else if(str[0] == '+'
                 || str[0] == '-'
                 || ansi_char_isdigit(str[0]))
         {
            for(::collection::index i = 1; i < str.length(); i++)
            {
               if(!ansi_char_isdigit(str[i]))
                  return false;
            }
            return true;
         }
         else
            return false;
      }
      else
      {
         return false;
      }
   }
}

bool payload::is_natural() const
{
   if(m_etype == e_type_u32 || m_etype == e_type_u64)
   {
      return true;
   }
   // simple, lazy, slow, and a bit incorrect
   // incorrect because atof and atoi returns partials results even if it
   // encounters non-numerical symbols
   else
   {
      
      ::string str = string();

#if defined(LINUX) || defined(ANDROID) || defined(FREEBSD)
      if(is_scalar()
            && (fmod(atof(str), 1.0) == 0.0
                && fabs(atof(str)) <= pow(2.0, 31.0)))
#else
      if(is_scalar()
            && (fmod(_atof_l(str, ::acme::get_c_locale()), 1.0) == 0.0
                && fabs(_atof_l(str, ::acme::get_c_locale())) <= pow(2.0, 31.0)))
#endif
      {
         str.trim();
         if(str.length() == 0)
            return false;
         else if(str[0] == '+'
                 || ansi_char_isdigit(str[0]))
         {
            for(::collection::index i = 1; i < str.length(); i++)
            {
               if(!ansi_char_isdigit(str[i]))
                  return false;
            }
            return true;
         }
         else
            return false;
      }
      else
      {
         return false;
      }
   }
}


//bool payload::get_bool(bool bDefault) const
//{
//
//   if (m_etype == e_type_enum_status)
//   {
//
//      return ::succeeded(m_estatus);
//
//   }
//   else if (m_etype == e_type_new
//         || m_etype == e_type_null
//         || m_etype == e_type_empty
//         || m_etype == e_type_empty_argument
//         || m_etype == e_type_not_found)
//   {
//
//      return false;
//
//   }
//   else if (m_etype == e_type_key_exists
//            || m_etype == e_type_file_time
//            || m_etype == e_type_time)
//   {
//
//      return true;
//
//   }
//   else if (m_etype == e_type_bool)
//   {
//
//      return m_b;
//
//   }
//   else if (m_etype == e_type_enum_check)
//   {
//
//      return __bool(m_echeck);
//
//   }
//   else if (m_etype == e_type_pbool)
//   {
//
//      return m_pb != nullptr && *m_pb;
//
//   }
//   else if(m_etype == e_type_i32 || m_etype == e_type_u32)
//   {
//
//      return m_i32 != 0;
//
//   }
//   else if (m_etype == e_type_i64 || m_etype == e_type_u64)
//   {
//
//      return m_i64 != 0;
//
//   }
//   else if (m_etype == e_type_i32 || m_etype == e_type_u32)
//   {
//
//      return m_pi32 != nullptr && *m_pi32 != 0;
//
//   }
//   else if (m_etype == e_type_i64 || m_etype == e_type_u64)
//   {
//
//      return m_pi64 != nullptr && *m_pi64 != 0;
//
//   }
//   else if(m_etype == e_type_string)
//   {
//
//      return ::papaya::is_true(m_str);
//
//   }
//   else if (m_etype == e_type_pstring)
//   {
//
//      return m_pstr != nullptr && ::papaya::is_true(*m_pstr);
//
//   }
//   else if (m_etype == e_type_id)
//   {
//
//      return (m_atom.is_text() && ::papaya::is_true(m_atom.m_psz)) || (m_atom.is_integer() && m_atom.m_i != 0);
//
//   }
//   else if (m_etype == e_type_pid)
//   {
//
//      return m_pid != nullptr && ((m_pid->is_text() && ::papaya::is_true(m_pid->m_psz)) || (m_pid->is_integer() && m_pid->m_i != 0));
//
//   }
//   else if (m_etype == e_type_i32_array)
//   {
//
//      return m_pia != nullptr && (m_pia->get_count() >= 2 || (m_pia->get_count() == 1 && !m_pia->element_at(0)));
//
//   }
//   else if (m_etype == e_type_i64_array)
//   {
//
//      return m_pi64a != nullptr && (m_pi64a->get_count() >= 2 || (m_pi64a->get_count() == 1 && !m_pi64a->element_at(0)));
//
//   }
//   else if (m_etype == e_type_string_array)
//   {
//
//      return m_pstra != nullptr && (m_pstra->get_count() >= 2 || (m_pstra->get_count() == 1 && ::papaya::is_true(m_pstra->element_at(0))));
//
//   }
//   else if (m_etype == e_type_f32)
//   {
//
//      return m_f32 != 0.0f;
//
//   }
//   else if (m_etype == e_type_f64)
//   {
//
//      return m_f64 != 0.0;
//
//   }
//   else if (m_etype == e_type_payload_pointer)
//   {
//
//      if (this == m_ppayload)
//      {
//
//         return true;
//
//      }
//
//      return m_ppayload->operator bool();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->operator bool();
//
//   }
//   else if (m_etype == e_type_payload_array)
//   {
//
//      return m_ppayloada != nullptr && (m_ppayloada->get_count() >= 2 || (m_ppayloada->get_count() == 1 && m_ppayloada->element_at(0).is_true()));
//
//   }
//   else if (m_etype == e_type_property_set)
//   {
//
//      return m_ppropertyset != nullptr && ::papaya::array::every::is_true(m_ppropertyset->values());
//
//   }
//   else if (m_etype == e_type_time)
//   {
//
//      return m_time.operator bool();
//
//   }
//   else if (m_etype == e_type_ptime)
//   {
//
//      return m_ptime != nullptr && m_ptime->operator bool();
//
//   }
//   else if (m_etype == e_type_i8)
//   {
//
//      return m_i8 != '\0';
//
//   }
//   else if (m_etype == e_type_u8)
//   {
//
//      return m_u8 != 0;
//
//   }
//   else
//   {
//
//      return m_p != nullptr;
//
//   }
//
//}


bool payload::is_property_true(const ::atom & atom) const
{

   auto pproperty = find_property(atom);

   if (!pproperty)
   {

      return false;

   }

   if (pproperty->is_empty())
   {

      return true;

   }

   return pproperty->is_true();

}


bool payload::is_property_false(const ::atom & atom) const
{

   return !is_property_true(atom);

}

//::block payload::block () const
//{
//
//   return ((::payload *)this)->operator block ();
//
//}

block payload::block () const
{

   if (get_type() != e_type_memory)
   {

      throw ::exception(error_wrong_type);

   }

   return *m_pmemory;

}



::payload payload::get_topic(const ::atom & atom) const
{

   auto pproperty = find_property(atom);

   if(!pproperty)
   {

      return *this;

   }

   return *pproperty;

}


//::payload payload::defer_get(const ::atom & atom) const
//{
//
//   auto pproperty = defer_get_property(atom);
//
//   if(::is_null(pproperty))
//   {
//
//      return e_type_new;
//
//   }
//
//   return *pproperty;
//
//}


//property * payload::defer_get_property(const ::atom & atom) const
//{
//   if(get_type() == e_type_property_set)
//   {
//      return dynamic_cast < const property_set * > (m_pointer.m_p)->defer_get(atom);
//   }
//   else if(get_type() == e_type_payload_pointer)
//   {
//      return m_ppayload->defer_get_property(atom);
//   }
//   else if(get_type() == e_type_element)
//   {
//      if(cast < property_set >() != nullptr)
//      {
//         return cast < property_set >()->defer_get(atom);
//      }
//      //else if(cast < property >() != nullptr)
//      //{
//      //   return cast < property >()->name().case_insensitive_order(lpszName) == 0;
//      //}
//      else
//      {
//         return nullptr;
//      }
//   }
//   else
//   {
//      return nullptr;
//   }
//}


bool payload::has_property(const ::atom & atom) const
{

   return __found(property_index(atom));

}


void payload::consume_identifier(const char * & psz)
{

   consume_number(psz, psz + strlen(psz) - 1);

}


void payload::consume_identifier(const char * & psz, const ::ansi_character * pszEnd)
{

   const ::scoped_string & scopedstrParse = psz;

   ::str::consume_spaces(pszParse, 0, pszEnd);

   const ::scoped_string & scopedstrStart = pszParse;

   while (ansi_char_isalpha(*pszParse) && pszParse <= pszEnd)
   {

      pszParse++;

   }

   ::string str(pszStart, pszParse - pszStart);

   if (str.case_insensitive_order("false") == 0)
   {

      operator = (false);

   }
   else if (str.case_insensitive_order("true") == 0)
   {

      operator = (true);
   }
   else if (str.case_insensitive_order("null") == 0)
   {
      set_type(::e_type_null);
   }
   else
   {
      throw ::parsing_exception("not expected identifier");
   }
   psz = pszParse;
}

void payload::consume_number(const char * & psz)
{
   consume_number(psz, psz + strlen(psz) - 1);
}

void payload::consume_number(const char * & psz, const ::ansi_character * pszEnd)
{
   const ::scoped_string & scopedstrParse = psz;
   bool bSigned = false;
   bool bFloat = false;
   ::str::consume_spaces(pszParse, 0, pszEnd);
   const ::scoped_string & scopedstrStart = pszParse;
   if(*pszParse == '-')
   {
      bSigned = true;
      pszParse++;
   }
   if(*pszParse == '.')
   {
      bFloat = true;
      pszParse++;
   }
   while(*pszParse != '\0' && *pszParse >= '0' && *pszParse <= '9')
   {
      pszParse++;
   }
   if(*pszParse == 'e' || *pszParse == 'E')
   {
      pszParse++;
      bFloat = true;
      if(*pszParse == '-')
      {
         bSigned = true;
         pszParse++;
      }
      if(*pszParse == '.')
      {
         bFloat = true;
         pszParse++;
      }
      while(*pszParse != '\0' && *pszParse >= '0' && *pszParse <= '9')
      {
         pszParse++;
      }
      goto end;
   }
   if(*pszParse == '.')
   {
      bFloat = true;
      pszParse++;
   }
   while(*pszParse != '\0' && *pszParse >= '0' && *pszParse <= '9')
   {
      pszParse++;
   }
   if(*pszParse == 'e' || *pszParse == 'E')
   {
      pszParse++;
      bFloat = true;
      if(*pszParse == '-')
      {
         bSigned = true;
         pszParse++;
      }
      if(*pszParse == '.')
      {
         bFloat = true;
         pszParse++;
      }
      while(*pszParse != '\0' && *pszParse >= '0' && *pszParse <= '9')
      {
         pszParse++;
      }
      goto end;
   }

end:

   if(pszParse == pszStart)
   {

      throw ::parsing_exception("empty string : not a number");

   }

   ::string strNumber(pszStart, pszParse - pszStart);

   if(bFloat)
   {

#if defined(LINUX) || defined(ANDROID) || defined(FREEBSD)

      ::f64 f64 = atof(strNumber);

#else

      ::f64 f64 = _atof_l(strNumber, ::acme::get_c_locale());

#endif

      operator = (f64);

   }
   else
   {

      ::i64 i = (::i64) atoll(strNumber);

      operator = (i);

   }

   psz = pszParse;

}



void payload::parse_network_payload(const char * & pszJson)
{

   parse_network_payload(pszJson, pszJson + strlen(pszJson) - 1);

}





void var_skip_identifier(const char *& psz)
{
   var_skip_number(psz, psz + strlen(psz) - 1);
}


void var_skip_identifier(const char *& psz, const ::ansi_character * pszEnd)
{
   const ::scoped_string & scopedstrParse = psz;
   ::str::consume_spaces(pszParse, 0, pszEnd);
   const ::scoped_string & scopedstrStart = pszParse;
   while (ansi_char_isalpha(*pszParse) && pszParse <= pszEnd)
      pszParse++;
   strsize iLen = pszParse - pszStart;
   if (iLen == 5 && case_insensitive_ansi_count_compare(pszStart, "false", 5) == 0)
   {
   }
   else if (iLen == 4)
   {
      if (case_insensitive_ansi_count_compare(pszStart, "true", 4) == 0)
      {
      }
      else if (case_insensitive_ansi_count_compare(pszStart, "null", 4) == 0)
      {
      }
      else
      {
         throw ::parsing_exception("not expected identifier");
      }
   }
   else
   {
      throw ::parsing_exception("not expected identifier");
   }
   psz = pszParse;
}



void var_skip_number(const char *& psz)
{
   var_skip_number(psz, psz + strlen(psz) - 1);
}

void var_skip_number(const char *& psz, const ::ansi_character * pszEnd)
{
   const ::scoped_string & scopedstrParse = psz;
   ::str::consume_spaces(pszParse, 0, pszEnd);
   const ::scoped_string & scopedstrStart = pszParse;
   if (*pszParse == '-')
   {
      pszParse++;
   }
   if (*pszParse == '.')
   {
      pszParse++;
   }
   while (*pszParse != '\0' && *pszParse >= '0' && *pszParse <= '9')
   {
      pszParse++;
   }
   if (*pszParse == 'e' || *pszParse == 'E')
   {
      pszParse++;
      if (*pszParse == '-')
      {
         pszParse++;
      }
      if (*pszParse == '.')
      {
         pszParse++;
      }
      while (*pszParse != '\0' && *pszParse >= '0' && *pszParse <= '9')
      {
         pszParse++;
      }
      goto end;
   }
   if (*pszParse == '.')
   {
      pszParse++;
   }
   while (*pszParse != '\0' && *pszParse >= '0' && *pszParse <= '9')
   {
      pszParse++;
   }
   if (*pszParse == 'e' || *pszParse == 'E')
   {
      pszParse++;
      if (*pszParse == '-')
      {
         pszParse++;
      }
      if (*pszParse == '.')
      {
         pszParse++;
      }
      while (*pszParse != '\0' && *pszParse >= '0' && *pszParse <= '9')
      {
         pszParse++;
      }
      goto end;
   }
end:
   if (pszParse == pszStart)
   {
      throw ::parsing_exception("empty string : not a number");
   }
   psz = pszParse;
}


void var_skip_network_payload(const char *& pszJson, const ::ansi_character * pszEnd)
{

   ::str::consume_spaces(pszJson, 0, pszEnd);

   if (*pszJson == '{')
   {

      property_set_skip_network_payload(pszJson, pszEnd);

   }
   else if (*pszJson == '\"')
   {

      ::str::skip_quoted_value_ex(pszJson, pszEnd);

   }
   else if (*pszJson == '\'')
   {

      ::str::skip_quoted_value_ex(pszJson, pszEnd);

   }
   else if (ansi_char_isdigit(*pszJson) || *pszJson == '-' || *pszJson == '.')
   {

      var_skip_number(pszJson, pszEnd);

   }
   else if (*pszJson == '[')
   {

      var_array_skip_network_payload(pszJson, pszEnd);

   }
   else if (*pszJson == ']')
   {

      informationf("");

   }
   else if (*pszJson == '\0')
   {

      informationf("");

   }
   else
   {

      var_skip_identifier(pszJson, pszEnd);

   }

}


void var_skip_network_payload(const char *& pszJson)
{
   var_skip_network_payload(pszJson, pszJson + strlen(pszJson) - 1);
}




const char * payload::parse_network_payload(const ::string & strJson)
{

   const ::ansi_character * pszJson = strJson;

   parse_network_payload(pszJson, pszJson + strJson.length());

   return pszJson;

}


void payload::parse_network_payload(const char *& pszJson, const ::ansi_character * pszEnd)
{

   ::str::consume_spaces(pszJson, 0, pszEnd);

   if (*pszJson == '{')
   {

      propset_reference().parse_network_payload(pszJson, pszEnd);

   }
   else if (*pszJson == '\"')
   {

      ::string str = ::str::consume_quoted_value_ex(pszJson, pszEnd);

      if(str.case_insensitive_begins_eat("hls://"))
      {

         string_array stra;

         stra.explode(":", str);

         if(stra.get_count() == 3)
         {

            ::f64 dH = atof(stra[0]);

            ::f64 dL = atof(stra[1]);

            ::f64 dS = atof(stra[2]);

            if(dH >= 0.0 && dH <= 1.0
            && dL >= 0.0 && dL <= 1.0
            && dS >= 0.0 && dS <= 1.0)
            {

               set_type(e_type_hls);

               m_hls = {dH, dL, dS};

               return;

            }

         }

      }

      operator=(str);

   }
   else if (ansi_char_isdigit(*pszJson) || *pszJson == '-' || *pszJson == '.')
   {

      consume_number(pszJson, pszEnd);

   }
   else if (*pszJson == '[')
   {

      payloada_reference().parse_network_payload(pszJson, pszEnd);

   }
   else if (*pszJson == ']')
   {

      informationf("");

      //pszJson++;

   }
   else if (*pszJson == '\0')
   {

      informationf("");

   }
   else
   {

      consume_identifier(pszJson, pszEnd);

   }

}


::enum_type payload::find_network_payload_child(const char *& pszJson, const ::ansi_character * pszEnd, const ::payload & varChild)
{

   ::str::consume_spaces(pszJson, 0, pszEnd);

   if (*pszJson == '{')
   {

      ::str::consume_spaces(pszJson, 0, pszEnd);

      if (*pszJson == '\0')
      {

         return ::e_type_new;

      }

      ::str::consume(pszJson, "{", 1, pszEnd);

      ::str::consume_spaces(pszJson, 0, pszEnd);

      if (*pszJson == '}')
      {

         pszJson++;

         return ::e_type_new;

      }

      ::atom atom;

      while (true)
      {

         property_parse_network_payload_id(atom, pszJson, pszEnd);

         if (varChild.string().case_insensitive_order(atom) == 0)
         {

            ::str::consume_spaces(pszJson, 0, pszEnd);
            ::str::consume(pszJson, ":", 1, pszEnd);


            return ::e_type_property_set;

         }

         property_skip_network_payload_value(pszJson, pszEnd);

         ::str::consume_spaces(pszJson, 0, pszEnd);

         if (*pszJson == ',')
         {
            pszJson++;
            continue;
         }
         else if (*pszJson == '}')
         {
            pszJson++;
            return ::e_type_new;
         }
         else
         {

            ::string str = "not expected character : ";

            str += pszJson;

            throw ::parsing_exception(str);

         }

      }

   }
   else if (*pszJson == '\"')
   {
      operator=(::str::consume_quoted_value_ex(pszJson, pszEnd));
      if (operator == (varChild))
      {
         return ::e_type_string;
      }
      else
      {
         return ::e_type_new;
      }
   }
   else if (ansi_char_isdigit(*pszJson) || *pszJson == '-' || *pszJson == '.')
   {
      consume_number(pszJson, pszEnd);
      if (operator == (varChild))
      {
         return get_type();
      }
      else
      {
         return ::e_type_new;
      }
   }
   else if (*pszJson == '[')
   {
      ::str::consume_spaces(pszJson, 0, pszEnd);
      ::str::consume(pszJson, "[", 1, pszEnd);
      ::enum_type etype = find_network_payload_id(pszJson, pszEnd, varChild);
      if (etype == ::e_type_new)
      {

         return ::e_type_new;

      }

      ::str::consume_spaces(pszJson, 0, pszEnd);

      if (*pszJson == ']')
      {
         pszJson++;

         return etype;

      }

      return ::e_type_new;

   }
   else if (*pszJson == ']')
   {
      informationf("");
      return ::e_type_new;
   }
   else if (*pszJson == '\0')
   {
      informationf("");
      return ::e_type_new;
   }
   else
   {
      consume_identifier(pszJson, pszEnd);
      if (operator==(varChild))
      {
         return get_type();
      }
      else
      {
         return ::e_type_new;
      }
   }

}


::enum_type payload::find_network_payload_id(const char * & pszJson, const ::ansi_character * pszEnd, const ::payload & varChild)
{

   ::str::consume_spaces(pszJson, 0, pszEnd);

   if (*pszJson == '{')
   {

      return ::e_type_new;


   }
   else if (*pszJson == '\"')
   {
      operator=(::str::consume_quoted_value_ex(pszJson, pszEnd));
      if (operator == (varChild))
      {
         return ::e_type_string;
      }
      else
      {
         return ::e_type_new;
      }
   }
   else if (ansi_char_isdigit(*pszJson) || *pszJson == '-' || *pszJson == '.')
   {
      consume_number(pszJson, pszEnd);
      if (operator == (varChild))
      {
         return get_type();
      }
      else
      {
         return ::e_type_new;
      }
   }
   else if (*pszJson == '[')
   {

      return ::e_type_new;

   }
   else if (*pszJson == ']')
   {
      return ::e_type_new;
   }
   else if (*pszJson == '\0')
   {
      return ::e_type_new;
   }
   else
   {
      consume_identifier(pszJson, pszEnd);
      if (operator==(varChild))
      {
         return get_type();
      }
      else
      {
         return ::e_type_new;
      }
   }
}


bool payload::is_numeric() const
{

   auto etype = get_type();

   switch(etype)
   {
   case e_type_parareturn:
   case e_type_new:
   case e_type_null:
   case e_type_empty:
   case e_type_empty_argument:
      return false;

   case e_type_string: // may be improved MBI
      return false;

   case e_type_pstring: // may be improved MBI
      return false;

   case e_type_i8:
   case e_type_pi8:
   case e_type_u8:
   case e_type_pu8:
   case e_type_i16:
   case e_type_pi16:
   case e_type_u16:
   case e_type_pu16:
   case e_type_i32:
   case e_type_pi32:
   case e_type_u32:
   case e_type_pu32:
   case e_type_i64:
   case e_type_pi64:
   case e_type_u64:
   case e_type_pu64:
      return true;

   case e_type_payload_pointer:
      return m_ppayload->is_numeric();
   case e_type_property:
      return m_pproperty->is_numeric();


   case e_type_element:
   case e_type_path:
      return false;

   case e_type_bool:
   case e_type_pbool:
      return false;

   case e_type_f64:
      return true;

   case e_type_string_array:
   case e_type_i32_array:
   case e_type_payload_array:
   case e_type_property_set:
   case e_type_memory:
      return false;

   case e_type_time:
   case e_type_file_time:
      return false;

   case e_type_id:
      return false; // m_atom.is_number(); // may be improved MBI

   case e_type_pid:
      return false; // m_pid->is_number(); // may be improved MBI

   case e_type_i64_array:
      return false;
   //case e_type_routine:
   //   return false;
//   case e_type_process:
//      return false;
      case e_type_hls:
      case e_type_color:
         return true;
   default:
   {
      throw ::not_implemented();

      return false;

   }

   };

}



bool is_return_ok(para_return eret)
{
   return ((::i32)eret) >= 0;
}


::payload str_ends_get(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrSuffix)
{

   string str(pcsz);

   string strSuffix(pcszSuffix);

   strsize iLen = strSuffix.length();

   if(str.right(iLen) == pcszSuffix)

   {

      return str.left(str.length() - iLen);

   }

   return false;

}


string payload::get_network_payload(bool bNewLine) const
{

   ::string str;

   return get_network_payload(str, bNewLine);

}


string & payload::get_network_payload(::string & str, bool bNewLine) const
{

   if (is_null())
   {

      return str += "null";

   }
   else if (get_type() == ::e_type_property_set)
   {

      return propset().get_network_payload(str, bNewLine);

   }
   else if (get_type() == ::e_type_string_array)
   {

      return stra().get_network_payload(str, bNewLine);

   }
   else if (get_type() == ::e_type_i32_array)
   {

      return ia().get_network_payload(str, bNewLine);

   }
   else if (get_type() == ::e_type_i64_array)
   {

      return i64a().get_network_payload(str, bNewLine);

   }
   else if (get_type() == ::e_type_payload_array)
   {

      return payloada().get_network_payload(str, bNewLine);

   }
   else if (get_type() == ::e_type_hls)
   {

      ::string strHls;

      strHls.formatf("\"hls://%f32:%f32:%f32\"", m_hls.m_dH, m_hls.m_dL, m_hls.m_dS);

      str += strHls;

      return str;

   }
   else if (is_numeric())
   {

      return str += string();

   }
   else if (get_type() == ::e_type_bool)
   {

      return str += get_bool() ? "true" : "false";

   }
   else
   {

      ::string strValue;

      strValue = string();

      strValue.replace_with("\\\"", "\"");

      return str += ("\"" + strValue + "\"");

   }

}



void payload::null()
{

   set_type(::e_type_null);

}




::file::path payload::get_file_path() const
{

   if(m_etype == e_type_element)
   {

      auto pfile = cast < ::file::file >();

      if (pfile)
      {

         auto path = pfile->get_file_path();

         return path;

      }

   }

   if(m_etype == e_type_property_set)
   {

      ::file::path path;

      if(auto purl = find_property("url"))
      {

         path = purl->get_file_path();

      }
      else if(has_property("path"))
      {

         path = propset()["path"].get_file_path();

      }

      if (propset().is_true("required"))
      {

         path |= ::file::e_flag_required;

      }

      if (propset().is_true("nocache"))
      {

         path |= ::file::e_flag_bypass_cache;

      }

      return path;

   }
   else if (m_etype == e_type_path)
   {

      auto ppath = cast < ::file::path_object > ();

      if (ppath)
      {

         return *ppath;

      }

   }

   return ::file::path(string());

}


::payload & payload::operator |= (enumeration < ::file::enum_flag > eflag)
{


   if(m_etype == e_type_payload_pointer)
   {

      return m_ppayload->operator |=(eflag);

   }

   auto pfile = cast < ::file::file > ();

   if (pfile)
   {

      propset()["file"] = pfile;

   }


   if (m_etype == e_type_property_set)
   {

      if (eflag & ::file::e_flag_required)
      {

         propset()["required"] = true;

      }

      if (eflag & ::file::e_flag_bypass_cache)
      {

         propset()["nocache"] = true;

      }

   }
   else if (m_etype == e_type_path)
   {

      auto ppath = cast < ::file::path_object > ();

      if (ppath)
      {

         *ppath |= eflag;

      }

   }
   else
   {

      auto ppath = __allocate< ::file::path_object(get_file_path >());

      *ppath |= eflag;

      set_type(e_type_path, false);

      m_ppath = ppath;

   }

   return *this;

}


bool payload::is_false() const
{

   switch(m_etype)
   {

   /// special meaning
   case e_type_parareturn:
   case e_type_new:
   case e_type_null:
   case e_type_empty:
   case e_type_empty_argument:
   case e_type_not_found:
      return false;

   case e_type_key_exists:
      return false;
   // integral
   case e_type_bool:
      return !m_b;
   case e_type_pbool:
      return !*m_pb;
   case e_type_i8:
      return !m_i8;
   case e_type_pi8:
      return !m_pi8 || !*m_pi8;
   case e_type_byte:
      return !m_u8;
   case e_type_pu8:
      return !m_pu8 || !*m_pu8;
   case e_type_i16:
      return !m_i16;
   case e_type_pi16:
      return !m_pi16 || !*m_pi16;
   case e_type_u16:
      return !m_u16;
   case e_type_pu16:
      return !m_pu16 || !*m_pu16;
   case e_type_i32:
      return !m_i32;
   case e_type_pi32:
      return !m_pi32 || !*m_pi32;
   case e_type_u32:
      return !m_u32;
   case e_type_pu32:
      return !m_pu32 || !*m_pu32;
   case e_type_i64:
      return !m_i64;
   case e_type_pi64:
      return !m_pi64 || !*m_pi64;
   case e_type_u64:
      return !m_u64;
   case e_type_pu64:
      return !m_pu64 || !*m_pu64;

   // floating point_i32
   case e_type_pfloat:
      return !*m_pf32;
   case e_type_f32:
      return !m_f32;
   case e_type_pdouble:
      return !*m_pf64;
   case e_type_f64:
      return !m_f64;

   // simple classes
   case e_type_string:
      return m_str.is_empty() || !m_str.case_insensitive_order("false")  || !m_str.case_insensitive_order("no");
   case e_type_pstring:
      return !m_pstr || m_pstr->is_empty() || !m_pstr->case_insensitive_order("false")  || !m_pstr->case_insensitive_order("no");
   case e_type_type:
      return m_str.is_empty();
   case e_type_time:
      return m_time.is_null();
   case e_type_ptime:
      return !m_ptime || m_ptime->is_null();
   case e_type_id:
      return m_atom.is_empty() || !m_atom.case_insensitive_order("false") || !m_atom.case_insensitive_order("no");
   case e_type_pid:
      return !m_pid || m_pid->is_empty() || !m_pid->case_insensitive_order("false") || !m_pid->case_insensitive_order("no");
   case e_type_time:
      return !m_time.m_i;
   case e_type_file_time:
      return !m_filetime;
   case e_type_payload_pointer:
      return m_ppayload || !*m_ppayload;
   case e_type_property:
      return m_pproperty || !*m_pproperty;
   //case e_type_routine:
   //      return ::is_null(m_pelementProcedure);
   //case e_type_process:
     //    return !m_process;

   // element classes
   case e_type_element:
      return is_element_null();
   case e_type_string_array:
      return ::is_null(m_pstra) || m_pstra->is_empty();
   case e_type_i32_array:
      return ::is_null(m_pia) || m_pia->is_empty();
   case e_type_payload_array:
      return ::is_null(m_ppayloada) || m_ppayloada->is_empty();
   case e_type_property_set:
      return ::is_null(m_ppropertyset) || m_ppropertyset->is_empty();
   case e_type_i64_array:
      return ::is_null(m_pi64a) || m_pi64a->is_empty();
   case e_type_memory:
      return ::is_null(m_pmemory) || m_pmemory->is_empty();
   case e_type_path:
      return ::is_null(m_ppath) || m_ppath->is_empty();
   //case type_image:
   //   return m_pimage.ok();

   // enum
   case e_type_integral_nanosecond:
      return !m_integralnanosecond.m_i;
   case e_type_pintegral_nanosecond:
      return !m_pintegralnanosecond || !m_pintegralnanosecond->m_i;
      case e_type_integral_microsecond:
         return !m_integralmicrosecond.m_i;
      case e_type_pintegral_microsecond:
         return !m_pintegralmicrosecond || !m_pintegralmicrosecond->m_i;
      case e_type_integral_millisecond:
         return !m_integralmillisecond.m_i;
      case e_type_pintegral_millisecond:
         return !m_pintegralmillisecond || !m_pintegralmillisecond->m_i;
      case e_type_integral_second:
         return !m_integralsecond.m_i;
      case e_type_pintegral_second:
         return !m_pintegralsecond || !m_pintegralsecond->m_i;
      case e_type_integral_minute:
         return !m_integralminute.m_i;
      case e_type_pintegral_minute:
         return !m_pintegralminute || !m_pintegralminute->m_i;
      case e_type_integral_hour:
         return !m_integralhour.m_i;
      case e_type_pintegral_hour:
         return !m_pintegralhour || !m_pintegralhour->m_i;
      case e_type_integral_day:
         return !m_integralday.m_i;
      case e_type_pintegral_day:
         return !m_pintegralday || !m_pintegralday->m_i;
      case e_type_floating_nanosecond:
         return !m_floatingnanosecond.m_d;
      case e_type_pfloating_nanosecond:
         return !m_pfloatingnanosecond || !m_pfloatingnanosecond->m_d;
         case e_type_floating_microsecond:
            return !m_floatingmicrosecond.m_d;
         case e_type_pfloating_microsecond:
            return !m_pfloatingmicrosecond || !m_pfloatingmicrosecond->m_d;
         case e_type_floating_millisecond:
            return !m_floatingmillisecond.m_d;
         case e_type_pfloating_millisecond:
            return !m_pfloatingmillisecond || !m_pfloatingmillisecond->m_d;
         case e_type_floating_second:
            return !m_floatingsecond.m_d;
         case e_type_pfloating_second:
            return !m_pfloatingsecond || !m_pfloatingsecond->m_d;
         case e_type_floating_minute:
            return !m_floatingminute.m_d;
         case e_type_pfloating_minute:
            return !m_pfloatingminute || !m_pfloatingminute->m_d;
         case e_type_floating_hour:
            return !m_floatinghour.m_d;
         case e_type_pfloating_hour:
            return !m_pfloatinghour || !m_pfloatinghour->m_d;
         case e_type_floating_day:
            return !m_floatingday.m_d;
         case e_type_pfloating_day:
            return !m_pfloatingday || !m_pfloatingday->m_d;
   case e_type_enum_command:
   case e_type_enum_status:
   case e_type_enum_check:
      case e_type_enum_flag:
      return !m_i64;
   case e_type_color:
      return !m_color.u32;
   case e_type_hls:
      return m_hls.m_dL == 0.0;
   case e_type_last_element:
      return false;

   }

   return !m_b;

}


bool payload::is_set_false() const
{

   switch(m_etype)
   {
   /// special meaning
   case e_type_parareturn:
   case e_type_new:
   case e_type_null:
   case e_type_empty:
   case e_type_empty_argument:
   case e_type_not_found:
      return false;

   case e_type_key_exists:
      return false;
   // integral
   case e_type_bool:
      return !m_b;
   case e_type_pbool:
      return !*m_pb;
   case e_type_i8:
      return !m_i8;
   case e_type_pi8:
      return !m_pi8 || !*m_pi8;
   case e_type_byte:
      return !m_u8;
   case e_type_pu8:
      return !m_pu8 || !*m_pu8;
   case e_type_i16:
      return !m_i16;
   case e_type_pi16:
      return !m_pi16 || !*m_pi16;
   case e_type_u16:
      return !m_u16;
   case e_type_pu16:
      return !m_pu16 || !*m_pu16;
   case e_type_i32:
      return !m_i32;
   case e_type_pi32:
      return !m_pi32 || !*m_pi32;
   case e_type_u32:
      return !m_u32;
   case e_type_pu32:
      return !m_pu32 || !*m_pu32;
   case e_type_i64:
      return !m_i64;
   case e_type_pi64:
      return !m_pi64 || !*m_pi64;
   case e_type_u64:
      return !m_u64;
   case e_type_pu64:
      return !m_pu64 || !*m_pu64;
   // floating point_i32
   case e_type_pfloat:
      return !*m_pf32;
   case e_type_f32:
      return !m_f32;
   case e_type_pdouble:
      return !*m_pf64;
   case e_type_f64:
      return !m_f64;
   // simple classes
   case e_type_string:
      return m_str.is_empty() || !m_str.case_insensitive_order("false")  || !m_str.case_insensitive_order("no");
   case e_type_pstring:
      return !m_pstr || m_pstr->is_empty() || !m_pstr->case_insensitive_order("false")  || !m_pstr->case_insensitive_order("no");
   case e_type_type:
      return m_str.is_empty();
   case e_type_time:
      return m_time.is_null();
   case e_type_ptime:
      return !m_ptime || m_ptime->is_null();
   case e_type_id:
      return m_atom.is_empty() || !m_atom.case_insensitive_order("false") || !m_atom.case_insensitive_order("no");
   case e_type_pid:
      return !m_pid || m_pid->is_empty() || !m_pid->case_insensitive_order("false") || !m_pid->case_insensitive_order("no");
   case e_type_time:
      return !m_time.m_i;
   case e_type_file_time:
      return !m_filetime;
   case e_type_payload_pointer:
      return m_ppayload || !*m_ppayload;
   case e_type_property:
      return m_pproperty || !*m_pproperty;
   //case e_type_routine:
   //   return ::is_null(m_pelementProcedure);
   //case type_process:
   //   return !m_process;

      // element classes
   case e_type_element:
      return is_element_null();
   case e_type_string_array:
      return ::is_null(m_pstra) || m_pstra->is_empty();
   case e_type_i32_array:
      return ::is_null(m_pia) || m_pia->is_empty();
   case e_type_payload_array:
      return ::is_null(m_ppayloada) || m_ppayloada->is_empty();
   case e_type_property_set:
      return ::is_null(m_ppropertyset) || m_ppropertyset->is_empty();
   case e_type_i64_array:
      return ::is_null(m_pi64a) || m_pi64a->is_empty();
   case e_type_memory:
      return ::is_null(m_pmemory) || m_pmemory->is_empty();
   case e_type_path:
      return ::is_null(m_ppath) || m_ppath->is_empty();
   //case type_image:
   //   return m_pimage.ok();

   // enum
      case e_type_integral_nanosecond:
         return !m_integralnanosecond.m_i;
      case e_type_pintegral_nanosecond:
         return !m_pintegralnanosecond || !m_pintegralnanosecond->m_i;
         case e_type_integral_microsecond:
            return !m_integralmicrosecond.m_i;
         case e_type_pintegral_microsecond:
            return !m_pintegralmicrosecond || !m_pintegralmicrosecond->m_i;
         case e_type_integral_millisecond:
            return !m_integralmillisecond.m_i;
         case e_type_pintegral_millisecond:
            return !m_pintegralmillisecond || !m_pintegralmillisecond->m_i;
         case e_type_integral_second:
            return !m_integralsecond.m_i;
         case e_type_pintegral_second:
            return !m_pintegralsecond || !m_pintegralsecond->m_i;
         case e_type_integral_minute:
            return !m_integralminute.m_i;
         case e_type_pintegral_minute:
            return !m_pintegralminute || !m_pintegralminute->m_i;
         case e_type_integral_hour:
            return !m_integralhour.m_i;
         case e_type_pintegral_hour:
            return !m_pintegralhour || !m_pintegralhour->m_i;
         case e_type_integral_day:
            return !m_integralday.m_i;
         case e_type_pintegral_day:
            return !m_pintegralday || !m_pintegralday->m_i;
         case e_type_floating_nanosecond:
            return !m_floatingnanosecond.m_d;
         case e_type_pfloating_nanosecond:
            return !m_pfloatingnanosecond || !m_pfloatingnanosecond->m_d;
            case e_type_floating_microsecond:
               return !m_floatingmicrosecond.m_d;
            case e_type_pfloating_microsecond:
               return !m_pfloatingmicrosecond || !m_pfloatingmicrosecond->m_d;
            case e_type_floating_millisecond:
               return !m_floatingmillisecond.m_d;
            case e_type_pfloating_millisecond:
               return !m_pfloatingmillisecond || !m_pfloatingmillisecond->m_d;
            case e_type_floating_second:
               return !m_floatingsecond.m_d;
            case e_type_pfloating_second:
               return !m_pfloatingsecond || !m_pfloatingsecond->m_d;
            case e_type_floating_minute:
               return !m_floatingminute.m_d;
            case e_type_pfloating_minute:
               return !m_pfloatingminute || !m_pfloatingminute->m_d;
            case e_type_floating_hour:
               return !m_floatinghour.m_d;
            case e_type_pfloating_hour:
               return !m_pfloatinghour || !m_pfloatinghour->m_d;
            case e_type_floating_day:
               return !m_floatingday.m_d;
            case e_type_pfloating_day:
               return !m_pfloatingday || !m_pfloatingday->m_d;
   case e_type_enum_command:
   case e_type_enum_status:
   case e_type_enum_check:
      case e_type_enum_flag:
      return !m_i64;
   case e_type_color:
      return !m_color.u32;
   case e_type_hls:
      return m_hls.m_dL == 0.0;
   case e_type_last_element:
         return false;

   }

   return !m_b;

}


bool payload::is_bool_false() const
{

   if (m_etype == e_type_pbool)
   {

      return !*m_pb;

   }
   else if (m_etype == e_type_bool)
   {

      return !m_b;

   }
   else
   {

      return false;

   }

}


// try to set string scalar if suitable.
// no machine if source string array stream empty
// and avoid duplicate
void payload::_001Add(const string_array & straParam)
{

   if(straParam.get_count() <= 0)
   {

      return;

   }

   if(straParam.get_count() == 1)
   {

      if(string().case_insensitive_order(straParam[0]) == 0)
      {

         return;

      }
      else if(is_empty())
      {

         operator = (straParam[0]);

         return;

      }

   }

   stra().case_insensitive_add_unique(straParam);

}


::payload & payload::operator = (const ::element & o)
{

   _set_element((::element *) &o);

   return *this;

}


#ifdef UNIT_TEST


namespace user
{


   __memory(window_rect2)
   {

      bool                       m_bZoomed = false;
      bool                       m_bFullScreen = false;
      bool                       m_bIconic = false;
      rectangle_i32                       m_rectangleRestored = nullptr;
      rectangle_i32                       m_rectangleWindow = nullptr;
      int                        m_iControlBoxRightToLeft = 0;
      edisplay                   m_edisplay = e_display_default;
      edisplay                   m_edisplayPrevious = e_display_none;


   };


} // namespace user


void unit_test_primitive_var_acme_block_arg(::payload payload)
{


}


void unit_test_primitive_var_acme_block()
{

   ::user::window_rect2 r2;

   ::payload var1(r2);

   ::payload payload2;

   payload2 = r2;

   debug_primitive_var_acme_block_arg(r2);

}


#endif //UNIT_TEST


::earth::time payload::datetime_time () const
{

   return i64();

}


::earth::time & payload::datetime_time_reference()
{

   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->datetime_time_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->datetime_time_reference();

   }
   else if (m_etype != e_type_time)
   {

      auto i =i64();

      set_type(e_type_time, false);

      m_time = i;


   }

   return m_time;

}




//::color::color payload::color() const
//{
//
//   return color();
//
//}


//i8 & payload::as_i8()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_i8();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_i8();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      ::i8 i = this->i8();
//
//      set_type(e_type_i8, false);
//
//      m_i8 = i;
//
//   }
//
//   return m_i8;
//
//}


#define IMPLEMENT_PAYLOAD_NUMBER(NUMBERTYPE)             \
::NUMBERTYPE & payload::NUMBERTYPE ## _reference()       \
{                                                        \
                                                         \
   if (m_etype == e_type_payload_pointer)                \
   {                                                     \
                                                         \
      return m_ppayload->NUMBERTYPE ## _reference();     \
                                                         \
   }                                                     \
   else if (m_etype == e_type_property)                  \
   {                                                     \
                                                         \
      return m_pproperty->NUMBERTYPE ## _reference();    \
                                                         \
   }                                                     \
   else if (m_etype != e_type_ ## NUMBERTYPE)            \
   {                                                     \
                                                         \
      auto number = this->NUMBERTYPE();                  \
                                                         \
      set_type(e_type_ ## NUMBERTYPE, false);            \
                                                         \
      m_## NUMBERTYPE = number;                          \
                                                         \
   }                                                     \
                                                         \
   return m_ ## NUMBERTYPE;                              \
                                                         \
}                                                
IMPLEMENT_PAYLOAD_NUMBER(i8);
IMPLEMENT_PAYLOAD_NUMBER(u8);
IMPLEMENT_PAYLOAD_NUMBER(i16);
IMPLEMENT_PAYLOAD_NUMBER(u16);
IMPLEMENT_PAYLOAD_NUMBER(i32);
IMPLEMENT_PAYLOAD_NUMBER(u32);
IMPLEMENT_PAYLOAD_NUMBER(i64);
IMPLEMENT_PAYLOAD_NUMBER(u64);
IMPLEMENT_PAYLOAD_NUMBER(f32);
IMPLEMENT_PAYLOAD_NUMBER(f64);
#undef IMPLEMENT_PAYLOAD_NUMBER




#define IMPL_VAR_ENUM(ENUMTYPE) \
::enum_ ## ENUMTYPE & payload::as_e ## ENUMTYPE()         \
{                                                  \
                                                   \
   if(m_etype == ::e_type_payload_pointer)                      \
   {                                               \
                                                   \
      return m_ppayload->as_e ## ENUMTYPE ();            \
                                                   \
   }                                               \
   else if(m_etype == ::e_type_property)                      \
   {                                               \
                                                   \
      return m_pproperty->as_e ## ENUMTYPE ();            \
                                                   \
   }                                               \
         \
   if(m_etype != ::e_type_enum_ ## ENUMTYPE)        \
   {                                               \
                                                   \
      m_etype = ::e_type_enum_ ## ENUMTYPE;              \
      zero(m_all);   \
                                                   \
   }                                               \
                                                   \
   return m_e ## ENUMTYPE;                         \
                                                   \
}
IMPL_VAR_ENUM(status);
IMPL_VAR_ENUM(command);
IMPL_VAR_ENUM(check);
#undef IMPL_VAR_ENUM


//::extended::status payload::run()
void payload::run()
{

   if (get_type() == e_type_payload_pointer)
   {

      return m_ppayload->run();

   }
   else if (get_type() == e_type_property)
   {

      return m_pproperty->run();

   }
   else if (get_type() == e_type_element)
   {

      return m_p->run();

   }
   //else if (get_type() == e_type_routine)
   //{

   //   return this->get_routine()();

   //}
   else if (get_type() == e_type_payload_array)
   {

      //::extended::status result;

      for (auto & varFunction : payloada())
      {

         varFunction();

      }

      //return result;

   }
   else
   {

      throw ::exception(error_wrong_type);

   }

}


void payload::receive_response(const ::payload & payload)
{

   if (get_type() == e_type_payload_pointer)
   {

      m_ppayload->receive_response(payload);

   }
   else if (get_type() == e_type_property)
   {

      m_pproperty->receive_response(payload);

   }
   //else if (get_type() == type_process)
   //{

   //   m_process(payload);

   //}
   //else if (get_type() == e_type_payload_array)
   //{

   //   for (auto& varFunction : this->payloada())
   //   {

   //      if (varFunction.get_type() == type_process)
   //      {
   //         
   //         varFunction.m_process(payload);

   //      }

   //   }

   //}

}


//::payload& payload::operator = (const ::procedure & procedure)
//{
//
//   set_type(e_type_routine, false);
//
//   m_pelementProcedure = procedure;
//
//   ::increment_reference_count(m_pelementProcedure);
//
//   return *this;
//
//}


//::payload& payload::operator = (const ::future & future)
//{
//
//   set_type(type_process);
//
//   m_process = process;
//
//   return *this;
//
//}



#ifdef _DEBUG

void number_operator_payload_test()
{

   int l = 9457;

   payload payload("2948572345");


   auto x = l + payload;

}


#endif


#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBERRYPIOS) || defined(WINDOWS)


long & payload::long_reference()
{
   
   if(m_etype == e_type_i64)
   {
      
      return (long &) m_i64;
      
   }
   else if(m_etype == e_type_pi64)
   {
      
      return (long &)*m_pi64;
      
   }
   else
   {
   
      set_type(e_type_i64);
   
      return (long &) m_i64;
      
   }

}


unsigned long & payload::unsigned_long_reference()
{

   if(m_etype == e_type_u64)
   {
      
      return (unsigned long &) m_u64;
      
   }
   else if(m_etype == e_type_pu64)
   {
      
      return (unsigned long &)*m_pu64;
      
   }
   else
   {
   
      set_type(e_type_u64);
   
      return (unsigned long &) m_u64;
      
   }

}


#endif

