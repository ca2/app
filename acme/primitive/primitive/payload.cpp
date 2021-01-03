#include "framework.h"
#include "acme/platform/static_start.h"


#if defined(WINDOWS)
//extern _locale_t ::acme::g_localeC;
#else
#if defined(__APPLE__)
#include <xlocale.h>
#define _atof_l atof_l
#endif
//extern locale_t ::acme::g_localeC;
#endif

payload::payload(const char * psz)
{

   m_etype = type_new;

   set_string(psz);

}


payload::payload(::matter * pmatter)
{

   m_etype = type_new;

   operator = (pmatter);

}


payload::payload(const ::matter & matter)
{

   m_etype = type_new;

   operator = (matter);

}


payload::payload(const string & str)
{

   m_etype = type_new;

   set_string(str);

}


payload::payload(const type & type)
{

   m_etype = type_new;

   set_type(type);

}


payload::payload(string * pstr)
{

   m_etype = type_new;

   operator = (pstr);

}


payload::payload(bool b)
{

   m_etype = type_new;

   operator = (b);

}


payload::payload(bool * pb)
{

   m_etype = type_new;

   operator = (pb);

}


payload::payload(::i32 i)
{

   m_etype = type_new;

   operator = (i);

}


payload::payload(::u32 u )
{

   m_etype = type_u32;

   operator = (u);

}


payload::payload(::i64 i)
{

   m_etype = type_new;

   operator = (i);

}


payload::payload(::u64 u )
{

   m_etype = type_u64;

   m_u64 = u;

}


#ifdef __APPLE__
#ifdef OS64BIT

payload::payload(long l)
{

   m_etype = type_i64;
   m_i64 = (::i64) l;

}

#endif
#endif


payload::payload(::i32 * pi)
{

   m_etype = type_new;
   operator = (pi);

}


payload::payload(::u32 * pinteraction)
{

   m_etype = type_new;
   operator = (pinteraction);

}


payload::payload(::i64 * pi)
{

   m_etype = type_new;
   operator = (pi);

}


payload::payload(::u64 * pinteraction)
{

   m_etype = type_new;
   operator = (pinteraction);

}


payload::payload(float f)
{

   m_etype = type_new;
   operator = (f);

}


payload::payload(double d)
{

   m_etype = type_new;
   operator = (d);

}


payload::payload(const ::file::path & path)
{

   m_etype = type_new;
   operator = (path);

}


payload::payload(const string_array & payload)
{

   m_etype  = type_new;
   operator = (payload);

}


payload::payload(const int_array & ia)
{

   m_etype  = type_new;
   operator = (ia);

}


payload::payload(const var_array & payload)
{

   m_etype  = type_new;
   operator = (payload);

}


payload::payload(const property_set & set)
{

   m_etype  = type_new;
   operator = (set);

}


payload::payload(const class payload & payload)
{

   m_i64 = 0;
   m_etype = type_new;
   operator = (payload);

}


payload::payload(class payload * pvar)
{

   m_etype = type_new;
   operator = (pvar);

}


pack::pack(const ::std::initializer_list < pack >& list)
{

   for (auto& payload : list)
   {

      if (payload.get_type() == type_propset)
      {

         propset().merge(payload.propset());

      }

   }


}

payload::payload(const class payload * pvar)
{

   m_etype = type_new;
   operator = ( pvar);

}


payload::payload(const property & prop)
{

   m_etype = type_new;
   xxf_zero(m_all);
   operator = (prop);

}


payload::payload(const ::promise::routine & routine)
{

    m_etype = type_new;
    xxf_zero(m_all);
    set_type(type_routine);
    m_routine = routine;

}


payload::payload(const ::promise::process & process)
{

   m_etype = type_new;
   xxf_zero(m_all);
   set_type(type_process);
   m_process = process;

}


payload::payload(property * pproperty)
{

   m_etype = type_new;

   if (::is_set(pproperty))
   {

      operator = (pproperty);

   }
   else
   {

      clear_data();

   }

}


payload::payload(const property * pproperty)
{

   m_etype = type_new;

   if (::is_set(pproperty))
   {

      operator = (pproperty);

   }
   else
   {

      clear_data();

   }

}


payload::payload(const id & id)
{

   m_etype = type_new;
   operator = (id);

}


payload::payload(const ::duration & duration)
{

   m_etype = type_duration;
   m_duration = duration;

}


payload::payload(::duration * pduration)
{

   m_etype = type_pduration;
   m_pduration = pduration;

}


payload::payload(const ::datetime::time & time)
{
   m_etype = type_time;
   m_time = time.m_time;
}


#ifdef WINDOWS


payload::payload(const FILETIME & filetime)
{

   m_etype = type_filetime;
   m_u64 = make64_from32(filetime.dwLowDateTime, filetime.dwHighDateTime);

}


payload::payload(const SYSTEMTIME & systemtime)
{
   m_etype = type_time;
   m_time = ::datetime::time(systemtime).m_time;
}


#endif


payload::~payload()
{

}


bool payload::convert(const payload& payload)
{

   if (m_etype == payload.m_etype)
   {

      memcpy(&m_all, &payload.m_all, sizeof(m_all));

      m_str = payload.m_str;

   }
   else if(m_etype == type_i8)
   {

      m_i8 = payload;

   }
   else if(m_etype == type_enum_check)
   {

      m_echeck = (::enum_check)(::i32) payload;

   }
   else if(m_etype == type_string)
   {

      m_str = payload.get_string();

   }
   else
   {

      return false;

   }

   return true;

}


strsize payload::get_length() const
{

   return get_string().get_length();

}


void payload::get_string(char * psz) const
{

   strcpy(psz, get_string());

}


::enum_type payload::get_type() const
{

   return m_etype;

}


class payload & payload::operator ++(::i32)
{

   switch(get_type())
   {
   case type_new:
   case e_type_null:
   case type_stra:
   case type_inta:
   case type_empty:
   case type_element:
   case type_path:
      set_type(type_i32);
      m_i32 = 1;
      break;
   case type_bool:
      if(!m_b)
      {
         set_type(type_i32);
         m_i32 = 1;
      }
      else
      {
         set_type(type_i32);
         m_i32 = 2;
      }
      break;
   case type_string:
      set_type(type_i32);
      m_i32 = atoi(m_str) + 1;
      break;
   case type_double:
      m_d += 1.0;
      break;
   case type_i32:
      m_i32++;
      break;
   case type_u32:
      m_u32++;
      break;
   default:
      set_type(type_i32, false);
      m_i32 = 1;
      break;
   }
   return *this;
}


void payload::set_type(const ::type & type)
{

   set_type(type_type, false);

   m_str = type.m_strName;

}






bool payload::get_type(::type & type) const
{

   if (m_etype != type_type)
   {

      return false;

   }

   type.m_strName = m_str;

   return true;

}


void payload::set_type(enum_type etype, bool bConvert)
{

   if (m_etype == type_pvar)
   {

      m_pvar->set_type(etype, bConvert);

   }
   else if (m_etype == type_prop)
   {

      m_pprop->set_type(etype, bConvert);

   }
   else if (etype != m_etype)
   {

      release();

      if (bConvert && m_etype != type_new)
      {

         switch (etype)
         {
         case type_i32:
            m_i32 = i32();
            break;
         case type_u32:
            m_u32 = u32();
            break;
         case type_i64:
            m_i64 = i64();
            break;
         case type_u64:
            m_u64 = u64();
            break;
         case type_double:
            m_d = get_double();
            break;
         case type_string:
            m_str = get_string();
            break;
         case type_id:
            m_id = get_id();
            break;
         default:
            ::set_last_status(error_conversion_not_a_number);
            break;

         }

      }

      m_etype = etype;

   }

}


void payload::unset()
{
   set_type(type_new, false);
}


void payload::unset(const string & strPropertySetKey)
{

   if (get_type() == type_propset)
   {

      propset().remove_by_name(strPropertySetKey);

   }

}


bool payload::ok() const
{
   return get_type() != type_parareturn || ::is_return_ok(m_parareturn);
}

bool payload::failed() const
{
   return get_type() == type_parareturn && !::is_return_ok(m_parareturn);
}


void payload::set_id(const id & id)
{
   if(get_type() == type_pid)
   {
      *m_pid = id;
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = id;
   }
   else if (get_type() == type_prop)
   {
      *m_pprop = id;
   }
   else
   {
      set_type(type_id, false);
      m_id = id;
   }
}

class payload & payload::operator = (para_return & eret)
{
   set_type(type_parareturn, false);
   m_parareturn = eret;
   return *this;
}

class payload & payload::operator = (bool b)
{
   if(get_type() == type_pbool)
   {
      *m_pb = b;
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = b;
   }
   else if (get_type() == type_prop)
   {
      *m_pprop = b;
   }
   else
   {
      set_type(type_bool, false);
      m_b = b;
   }
   return *this;
}

class payload & payload::operator = (bool * pb)
{
   set_type(type_pbool, false);
   m_pb = pb;
   return *this;
}


class payload & payload::operator = (::i32 i)
{

    if(get_type() == type_pi32)
   {

       *m_pi32 = i;

   }
   else if(get_type() == type_pvar)
   {

       *m_pvar = i;

   }
   else if (get_type() == type_prop)
   {

       *m_pprop = i;

   }
   else
   {

       set_type(type_i32, false);

      m_i32 = i;

   }

   return *this;

}


class payload & payload::operator = (::i32 * pi)
{

   set_type(type_pi32, false);

   m_pi32 = pi;

   return *this;

}


class payload & payload::operator = (::u32 * pinteraction)
{

    set_type(type_pu32, false);

   m_pu32 = pinteraction;

   return *this;

}


class payload & payload::operator = (::i64 * pi)
{

    set_type(type_pi64, false);

   m_pi64 = pi;

   return *this;

}


class payload & payload::operator = (::u64 * pinteraction)
{

    set_type(type_pu64, false);

   m_pu64 = pinteraction;

   return *this;

}


class payload & payload::operator = (const ::datetime::time & time)
{

    set_type(type_time, false);

   m_time = time.get_time();

   return *this;

}


#ifdef WINDOWS


class payload & payload::operator = (const FILETIME & filetime)
{

   set_type(type_filetime, false);

   m_u64 = make64_from32(filetime.dwLowDateTime, filetime.dwHighDateTime);

   return *this;

}


#endif


class payload & payload::operator = (::i64 i)
{
   if(get_type() == type_pi64)
   {
      *m_pi64 = i;
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = i;
   }
   else if (get_type() == type_prop)
   {
      *m_pprop = i;
   }
   else
   {
      set_type(type_i64, false);
      m_i64 = i;
   }
   return *this;
}

class payload & payload::operator = (::u64 u)
{
   if(get_type() == type_pu64)
   {
      *m_pu64 = u;
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = u;
   }
   else if (get_type() == type_prop)
   {
      *m_pprop = u;
   }
   else
   {
      set_type(type_u64, false);
      m_u64 = u;
   }
   return *this;
}


class payload & payload::operator = (::u32 u)
{
   set_type(type_u32, false);
   m_u32 = u;
   return *this;
}


#if !defined(LINUX) && !defined(MACOS) && !defined(ANDROID) && !defined(APPLE_IOS)


class payload & payload::operator = (long l)
{

   set_type(type_i32,false);

   m_i32 = l;

   return *this;

}


class payload & payload::operator = (DWORD dw)
{

   set_type(type_u32,false);

   m_u32 = dw;

   return *this;

}

#endif


#if defined(__APPLE__)
   class payload & payload::operator = (long l)
   {
      set_type(type_i64,false);
      m_i64 = l;
      return *this;
   }
#endif

#if defined(ANDROID)
   class payload & payload::operator = (long l)
   {
      set_type(type_i32,false);
      m_i32 = l;
      return *this;
   }
#endif

class payload & payload::operator = (float f)
{
   set_type(type_float, false);
   m_f = f;
   return *this;
}

class payload & payload::operator = (double d)
{
   set_type(type_double, false);
   m_d = d;
   return *this;
}


//class payload & payload::operator = (enum_command ecommand)
//{
//   set_type(type_enum_command, false);
//   m_ecommand = ecommand;
//
//   return *this;
//
//}


class payload & payload::operator = (string * pstr)
{

   set_type(type_pstring, false);

   m_pstr = pstr;

   return *this;

}


class payload & payload::operator = (id * pid)
{
   set_type(type_pid, false);
   m_pid = pid;
   return *this;
}

//class payload & payload::operator = (const char * psz)
//{
//   set_string(psz);
//   return *this;
//}


class payload & payload::operator = (const widechar * pcsz)
{

   set_string(::str::international::unicode_to_utf8(pcsz));

   return *this;

}


class payload & payload::operator = (const property & prop)
{

   operator = ((const payload &)prop);

   return *this;

}


class payload & payload::operator = (const property * pproperty)
{

   if (::is_null(pproperty))
   {

      set_type(e_type_null, false);

   }
   else
   {

      set_type(type_prop, false);

      m_pprop = (property *)pproperty;

   }

   return *this;

}


class payload & payload::operator = (const class payload & payload)
{
   if(m_etype == type_pvar)
   {
      if(m_pvar == &payload)
         return *this;
      m_pvar->operator = (payload);
      return *this;
   }
   if (m_etype == type_prop)
   {
      m_pprop->operator = (payload);
      return *this;
   }
   if(&payload != this)
   {
      switch(((class payload &)payload).get_type())
      {
      case type_pvar:
         // should dereference (this operator here means a content copy)
         *this  = *((class payload &)payload).m_pvar;
         return *this;
      case type_prop:
         // should dereference (this operator here means a content copy)
         *this = *((class property&)payload).m_pprop;
         return *this;
      case type_pi32:
         // should dereference (this operator here means a content copy)
         *this  = *((class payload &)payload).m_pi32;
         return *this;
      case type_pstring:
         // should dereference (this operator here means a content copy)
         *this  = *((class payload &)payload).m_pstr;
         return *this;
      default:
         break;
      }

      set_type(payload.get_type(), false);
      if (payload.is_element())
      {

         m_p = payload.m_p; // raw copy, doesn't care for the right member

      }
      else
      {
         switch (payload.get_type())
         {
         case type_bool:
            m_b = payload.m_b;
            break;
         case type_i8:
            m_i8 = payload.m_i8;
            break;
         case type_u8:
            m_u8 = payload.m_u8;
            break;
         case type_i16:
            m_i16 = payload.m_i16;
            break;
         case type_u16:
            m_u16 = payload.m_u16;
            break;
         case type_i32:
            m_i32 = payload.m_i32;
            break;
         case type_u32:
            m_u32 = payload.m_u32;
            break;
         case type_i64:
            m_i64 = payload.m_i64;
            break;
         case type_u64:
            m_u64 = payload.m_u64;
            break;
         case type_pi8:
            m_pi8 = payload.m_pi8;
            break;
         case type_pu8:
            m_pu8 = payload.m_pu8;
            break;
         case type_pi16:
            m_pi16 = payload.m_pi16;
            break;
         case type_pu16:
            m_pu16 = payload.m_pu16;
            break;
         case type_pi32:
            m_pi32 = payload.m_pi32;
            break;
         case type_pu32:
            m_pu32 = payload.m_pu32;
            break;
         case type_pi64:
            m_pi64 = payload.m_pi64;
            break;
         case type_pu64:
            m_pu64 = payload.m_pu64;
            break;
         case type_float:
            m_f = payload.m_f;
            break;
         case type_double:
            m_d = payload.m_d;
            break;
         case type_string:
            m_str = payload.m_str;
            break;
         case type_prop:
            m_pprop=payload.m_pprop;
            break;
         case type_id:
            m_id = payload.m_id;
            break;
         default:
            memcpy(m_all, payload.m_all, sizeof(m_all));
            m_str = payload.m_str;
            break;
         }
      }
   }
   return *this;
}

class payload & payload::operator = (const int_array & ia)
{
   inta() = ia;
   return *this;
}


class payload & payload::operator = (const class memory & memoryParam)
{

   memory() = memoryParam;

   return *this;

}


class payload & payload::operator = (const string_array & straParam)
{
   stra() = straParam;
   return *this;
}

class payload & payload::operator = (const var_array & varaParam)
{
   vara() = varaParam;
   return *this;
}

class payload & payload::operator = (const property_set & propsetParam)
{
   propset() = propsetParam;
   return *this;
}

//class payload & payload::operator = (const pair_set_interface & propsetParam)
//{
//   propset() = propsetParam;
//   return *this;
//}
//
//class payload & payload::operator = (const str_str_interface & propsetParam)
//{
//   propset() = propsetParam;
//   return *this;
//}
//
//payload & payload::operator = (const string_composite & reference)
//{
//
//   string str;
//   ::count count = reference.get_length();
//   char * psz = str.get_string_buffer(count);
//   reference.get_string(psz);
//   str.ReleaseBuffer(count);
//   operator = (str);
//
//   return *this;
//
//}

class payload & payload::operator = (const id & id)
{

   set_id(id);
   return *this;

}

/*payload::operator id &()
{
   if(get_type() == type_pvar)
      return m_pvar->operator id &();
   else if(get_type() == type_pid)
      return *m_pid;
   else if(get_type() != type_id)
      m_id = get_id();
   set_type(type_id);
   return m_id;
}


payload::operator string & ()
{
   if(get_type() == type_pvar)
      return m_pvar->operator string &();
   else if(get_type() == type_pstring)
      return *m_pstr;
   else if(get_type() != type_string)
      m_str = get_string();
   set_type(type_string);
   return m_str;
}*/


class payload & payload::operator = (const ::secs & secs)
{

   set_type(type_secs);

   m_secs = secs;

   return *this;

}


class payload & payload::operator = (::secs * psecs)
{

   set_type(type_psecs);

   m_psecs = psecs;

   return *this;

}


class payload & payload::operator = (const ::millis & millis)
{

   set_type(type_millis);

   m_millis = millis;

   return *this;

}


class payload & payload::operator = (::millis * pmillis)
{

   set_type(type_pmillis);

   m_pmillis = pmillis;

   return *this;

}


class payload & payload::operator = (const ::micros & micros)
{

   set_type(type_micros);

   m_micros = micros;

   return *this;

}


class payload & payload::operator = (::micros * pmicros)
{

   set_type(type_pmicros);

   m_pmicros = pmicros;

   return *this;

}


class payload & payload::operator = (const ::nanos & nanos)
{

   set_type(type_nanos);

   m_nanos = nanos;

   return *this;

}


class payload & payload::operator = (::nanos * pnanos)
{

   set_type(type_pnanos);

   m_pnanos = pnanos;

   return *this;

}


class payload & payload::operator = (const ::duration & duration)
{

   set_type(type_duration);

   m_duration = duration;

   return *this;

}


class payload & payload::operator = (::duration * pduration)
{

   set_type(type_pduration);

   m_pduration = pduration;

   return *this;

}


payload & payload::operator = (const block & block)
{

   set_element(__new(class ::memory(block)));

   return *this;

}


payload::operator const char *() const
{

   return get_ref_string();

}


bool payload::casts_to(::enum_type etype) const
{

   if (m_etype == etype)
   {

      return true;

   }
   else if (m_etype == type_pvar)
   {

      return m_pvar->casts_to(etype);

   }
   else if (m_etype == type_prop)
   {

      return m_pprop->casts_to(etype);

   }


   return false;

}


bool payload::is_true(const ::payload & payload, bool bDefault) const
{

   if (payload.get_type() == type_bool)
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
         case type_empty:
            return bDefault;
         case type_key_exists:
            return true;
         case type_string:
            return !m_str.is_empty() && !(m_str.compare_ci("no") == 0 || m_str.compare_ci("false") == 0 || m_str.compare_ci("0") == 0);
         case type_i32:
            return m_i32 != 0;
         case type_u32:
            return m_u32 != 0;
         case type_i64:
            return m_i64 != 0;
         case type_u64:
            return m_u64 != 0;
         case type_double:
            return m_d != 0;
         case type_bool:
            return m_b;
         case type_pvar:
            return m_pvar->is_true(bDefault);
         case type_prop:
            return m_pprop->is_true(bDefault);
         case type_enum_status:
            return ::succeeded(m_estatus);
         case type_enum_check:
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
      case type_propset:
         return m_pset->is_true(payload, bDefault);
      case type_pvar:
         return m_pvar->is_true(payload, bDefault);
      case type_prop:
         return m_pprop->is_true(payload, bDefault);
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
   case type_empty:
      return true;
   case type_empty_argument:
      return true;
   case type_new:
      return true;
   case type_string:
      return m_str.is_empty();
   case type_i32:
      return false;
   case type_u32:
      return false;
   case type_i64:
      return false;
   case type_u64:
      return false;
   case type_double:
      return false;
   case type_pvar:
      return m_pvar->is_empty();
   case type_prop:
      return m_pprop->is_empty();
   case type_id:
      return m_id.is_empty();
   case type_pid:
      return m_pid->is_empty();


      // matter classes
   case type_element:
      return is_element_null();
   case type_stra:
      return ::is_null(m_pstra) || m_pstra->isEmpty();
   case type_inta:
      return ::is_null(m_pia) || m_pia->isEmpty();
   case type_vara:
      return ::is_null(m_pvara) || m_pvara->isEmpty();
   case type_propset:
      return ::is_null(m_pset) || m_pset->isEmpty();
   case type_i64a:
      return ::is_null(m_pi64a) || m_pi64a->isEmpty();
   case type_memory:
      return ::is_null(m_pmemory) || m_pmemory->is_empty();
   case type_path:
      return ::is_null(m_ppath) || m_ppath->is_empty();
   //case type_image:
   //   return !::is_ok(m_pimage);

   default:
      return false;
   }
}


bool payload::has_char() const
{

   return get_string().has_char();

}


bool payload::is_set() const
{

   if (get_type() != type_new)
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
   if(m_etype == type_new)
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




::i32 payload::compare_ci(const class payload & payload) const
{
   if(m_etype == ::type_inta)
   {
      if(payload.m_etype == ::type_inta)
      {
         //payload = var1.inta() - var2.inta();
      }
      else
      {
         //payload = var1;
         //payload.inta().remove(var2.i32());
      }
   }
   else if(m_etype == ::type_stra)
   {
      if(payload.m_etype == ::type_stra)
      {
         //payload = var1.stra() - var2.stra();
      }
      else
      {
         //payload = var1;
         //payload.stra().remove(var2.get_string());
      }
   }
   else if(m_etype == ::type_vara)
   {
      if(payload.m_etype == ::type_vara)
      {
         //   payload = var1.vara() - var2.vara();
      }
      else
      {
         // payload = var1;
         //payload.vara().remove(var2);
      }
   }
   else if(is_double() || payload.is_double())
   {
      double d = get_double() - payload.get_double();
      if(d == 0.0)
         return 0;
      else if(d > 0.0)
         return 1;
      else if(d < 0.0)
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
      return get_string().compare_ci(payload.get_string());
   }
   return -2;
}

::i32 payload::compare_ci(const char * psz) const
{
   payload payload(psz);
   return compare_ci(payload);
}


::i32 payload::compare(const class payload & payload) const
{
   if(m_etype == ::type_inta)
   {
      if(payload.m_etype == ::type_inta)
      {
         //payload = var1.inta() - var2.inta();
      }
      else
      {
         //payload = var1;
         //payload.inta().remove(var2.i32());
      }
   }
   else if(m_etype == ::type_stra)
   {
      if(payload.m_etype == ::type_stra)
      {
         //payload = var1.stra() - var2.stra();
      }
      else
      {
         //payload = var1;
         //payload.stra().remove(var2.get_string());
      }
   }
   else if(m_etype == ::type_vara)
   {
      if(payload.m_etype == ::type_vara)
      {
         //   payload = var1.vara() - var2.vara();
      }
      else
      {
         // payload = var1;
         //payload.vara().remove(var2);
      }
   }
   else if(is_double() || payload.is_double())
   {
      double d = get_double() - payload.get_double();
      if(d == 0.0)
         return 0;
      else if(d > 0.0)
         return 1;
      else if(d < 0.0)
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
      return get_string().compare(payload.get_string());
   }
   return -2;
}

::i32 payload::compare(const char * psz) const
{
   payload payload(psz);
   return compare(payload);
}

bool payload::operator == (const class payload & payload) const
{
   // if variables are equal:
   // all values of both variables should be equal
   return compare(payload) == 0;
}

bool payload::operator > (const class payload & payload) const
{
   return compare(payload) > 0;
}

bool payload::operator < (const class payload & payload) const
{
   return compare(payload) < 0;
}

bool payload::operator >= (const class payload & payload) const
{
   return compare(payload) >= 0;
}

bool payload::operator <= (const class payload & payload) const
{
   return compare(payload) <= 0;
}

bool payload::operator != (const class payload & payload) const
{
   return compare(payload) != 0;
}

bool payload::operator == (const char * psz) const
{
   return get_string() == psz;
}

bool payload::operator < (const char * psz) const
{
   return get_string() < psz;
}

bool payload::operator <= (const char * psz) const
{
   return get_string() <= psz;
}

bool payload::operator >= (const char * psz) const
{
   return get_string() >= psz;
}

bool payload::operator > (const char * psz) const
{
   return get_string() > psz;
}

bool payload::operator != (const char * psz) const
{
   return get_string() != psz;
}

bool payload::operator == (const string & str) const
{
   return get_string() == str;
}

bool payload::operator != (const string & str) const
{
   return get_string() != str;
}

bool payload::operator < (const string & str) const
{
   return get_string() < str;
}

bool payload::operator <= (const string & str) const
{
   return get_string() <= str;
}

bool payload::operator >= (const string & str) const
{
   return get_string() >= str;
}

bool payload::operator > (const string & str) const
{
   return get_string() > str;
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

bool payload::strict_equal(const class payload & payload) const
{
   return m_etype == payload.m_etype && operator == (payload);
}

bool payload::strict_equal(const char * psz) const
{
   return m_etype == type_string && m_str == psz;
}

bool payload::strict_equal(const string & str) const
{
   return m_etype == type_string && m_str == str;
}

bool payload::strict_equal(double d) const
{
   return m_etype == type_double && m_d == d;
}

bool payload::strict_equal(::i32 i) const
{
   return m_etype == type_i32 && m_i32 == i;
}

bool payload::strict_equal(bool b) const
{
   return m_etype == type_bool && is_equivalent(m_b, b);
}

bool payload::strict_different(const class payload & payload) const
{
   return m_etype != payload.m_etype || operator != (payload);
}

bool payload::strict_different(const char * psz) const
{
   return m_etype != type_string || m_str != psz;
}

bool payload::strict_different(const string & str) const
{
   return m_etype != type_string || m_str != str;
}

bool payload::strict_different(double d) const
{
   return m_etype != type_double || m_d != d;
}

bool payload::strict_different(::i32 i) const
{
   return m_etype != type_i32 || m_i32 != i;
}

bool payload::strict_different(bool b) const
{
   return m_etype != type_bool || is_different(m_b, b);
}

bool strict_equal(const char * psz, const class payload & payload)
{
   return payload.m_etype == ::type_string && psz == payload.m_str;
}

bool strict_equal(const string & str, const class payload & payload)
{
   return payload.m_etype == ::type_string && str == payload.m_str;
}

bool strict_equal(double d, const class payload & payload)
{
   return payload.m_etype == ::type_double && d == payload.m_d;
}

bool strict_equal(::i32 i, const class payload & payload)
{
   return payload.m_etype == ::type_i32 && i == payload.m_i32;
}

bool strict_equal(bool b, const class payload & payload)
{
   return payload.m_etype == ::type_bool && is_equivalent(b, payload.m_b);
}

bool strict_different(const char * psz, const class payload & payload)
{
   return payload.m_etype != ::type_string || psz != payload.m_str;
}

bool strict_different(const string & str, const class payload & payload)
{
   return payload.m_etype != ::type_string || str != payload.m_str;
}

bool strict_different(double d, const class payload & payload)
{
   return payload.m_etype != ::type_double || d != payload.m_d;
}

bool strict_different(::i32 i, const class payload & payload)
{
   return payload.m_etype != ::type_i32 || i != payload.m_i32;
}

bool strict_different(bool b, const class payload & payload)
{
   return payload.m_etype != ::type_bool || is_different(b, payload.m_b);
}

string payload::to_r_string() const
{
   if(is_array())
   {
      string str;
      str += "array (";
      for(::i32 i = 0; i < array_get_count(); i++)
      {
         if(i > 0)
            str += " ";
         str += __str(i);
         str += " => ";
         str += at(i).to_r_string();
         str += ";";
      }
      str += ")";
      return str;
   }
   else
   {
      return get_string();
   }
}

string payload::get_string(const char * pszOnNull) const
{

   if(m_etype == type_pvar)
   {
      return m_pvar->get_string(pszOnNull);
   }
   else if (m_etype == type_prop)
   {
      return m_pprop->get_string(pszOnNull);
   }
   else if(m_etype == type_pstring)
   {
      return *m_pstr;
   }
   else if(m_etype != type_string)
   {
      string str;

      if(m_etype == ::e_type_null)
      {
         str = pszOnNull;
      }
      else if(m_etype == ::type_i32)
      {
         str = __str(m_i32);
      }
      else if(m_etype == ::type_u32)
      {
         str = __str( m_u32);
      }
      else if(m_etype == ::type_i64)
      {
         str = i64toa_dup(m_i64);
      }
      else if(m_etype == ::type_u64)
      {
         str = __str(m_u64);
      }
      else if(m_etype == ::type_double)
      {
         str = __str(m_d);
      }
      else if(m_etype == ::type_id)
      {
         str = m_id;
      }
      else if(m_etype == ::type_pid)
      {
         str = *m_pid;
      }
      else if(m_etype == ::type_stra)
      {
         str = stra().implode("");
      }
      else if(m_etype == ::type_bool)
      {
         str = __str((int)m_b);
      }
      else if (is_element_set())
      {
         
         str = __str(*matter());

      }

      return str;

   }
   else
   {
      return m_str;
   }

}

string & payload::get_ref_string(const char * pszOnNull)
{

   if(m_etype == type_string)
   {

      return m_str;

   }
   else if(m_etype == type_pvar)
   {

      return m_pvar->get_ref_string(pszOnNull);

   }
   else if (m_etype == type_prop)
   {

      return m_pprop->get_ref_string(pszOnNull);

   }
   else if(m_etype == type_pstring)
   {

      return *m_pstr;

   }
   else
   {

      string str = get_string(pszOnNull);

      set_string(str);

      return m_str;

   }

}

const string & payload::get_ref_string(const char * pszOnNull) const
{

   return ((payload *)this)->get_ref_string(pszOnNull);

}


id payload::get_id(const char * pszOnNull) const
{
   if(m_etype == type_pvar)
   {
      return m_pvar->get_id(pszOnNull);
   }
   else if (m_etype == type_prop)
   {
      return m_pprop->get_id(pszOnNull);
   }
   else if(m_etype == type_pid)
   {
      return *m_pid;
   }
   else if(m_etype != type_id)
   {

      ::id id;

      if(m_etype == ::e_type_null)
      {
         id = pszOnNull;
      }
      else if(m_etype == ::type_i32)
      {
         id = m_i32;
      }
      else if(m_etype == ::type_i64)
      {
         id = (::index) m_i64;
      }
      else if(m_etype == ::type_u32)
      {
         id = (::index) m_u32;
      }
      else if(m_etype == ::type_double)
      {
         string str;
         str.Format("%f", m_d);
         id = str;
      }
      else if(m_etype == ::type_string)
      {
         id = m_str;
      }
      else if(m_etype == ::type_pstring)
      {
         id = *m_pstr;
      }

      return id;

   }
   else
   {
      return m_id;
   }
}



id & payload::get_ref_id(const char * pszOnNull)
{
   if(m_etype == type_pvar)
   {
      return m_pvar->get_ref_id(pszOnNull);
   }
   else if (m_etype == type_prop)
   {
      return m_pprop->get_ref_id(pszOnNull);
   }
   else if(m_etype == type_pid)
   {
      return *m_pid;
   }
   else
   {

      m_id = get_id();
      set_type(type_id, false);
      return m_id;

   }

}



::i32 payload::i32(::i32 iDefault) const
{
   switch(m_etype)
   {
   case e_type_null:
      return iDefault;
   case type_empty:
      return iDefault;
   case type_string:
      return atoi(m_str);
   case type_double:
      return (::i32) m_d;
   case type_pi8:
      return (::i32)*m_pi8;
   case type_pi16:
      return (::i32)*m_pi16;
   case type_pi32:
      return (::i32)*m_pi32;
   case type_pi64:
      return (::i32)*m_pi64;
   case type_pu8:
      return (::i32)*m_pu8;
   case type_pu16:
      return (::i32)*m_pu16;
   case type_pu32:
      return (::i32)*m_pu32;
   case type_pu64:
      return (::i32)*m_pu64;
   case type_i8:
      return (::i32) m_i8;
   case type_i16:
      return (::i32) m_i32;
   case type_i32:
      return m_u32;
   case type_i64:
      return (::i32) m_i64;
   case type_u8:
      return (::i32)m_u8;
   case type_u16:
      return (::i32)m_u16;
   case type_u32:
      return (::i32)m_u32;
   case type_u64:
      return (::i32) m_u64;
   case type_element:
   case type_path:
      return iDefault;
   case type_pvar:
      return m_pvar->i32(iDefault);
   case type_prop:
      return m_pprop->i32(iDefault);
   case type_pstring:
      return atoi(*m_pstr);
   case type_id:
   {
      if(!is_i32(m_id))
         __throw(overflow_error("payload contains id that does not fit 32 bit integer"));
      return (::i32) (::i64) m_id;
   }
   case type_pid:
   {
      if(!is_i32((::i64) *m_pid))
         __throw(overflow_error("payload contains id that does not fit 32 bit integer"));
      return (::i32) (::i64) *m_pid;
   }
   default:
      return iDefault;
   }
}

::u32 payload::u32(::u32 uiDefault) const
{
   switch(m_etype)
   {
   case e_type_null:
      return uiDefault;
   case type_empty:
      return uiDefault;
   case type_string:
      return atoi(m_str);
   case type_i32:
      return m_i32;
   case type_u32:
      return (::u32) m_u32;
   case type_element:
   case type_path:
      return (::u32) uiDefault;
   case type_i64:
      return (::u32)m_i64;
   case type_u64:
      return (::u32) m_u64;
   case type_pvar:
      return m_pvar->u32(uiDefault);
   case type_prop:
      return m_pprop->u32(uiDefault);
   default:
      return uiDefault;
   }
}

::i64 payload::i64(::i64 iDefault) const
{

   try
   {

      switch (m_etype)
      {
      case e_type_null:
         return iDefault;
      case type_empty:
         return iDefault;
      case type_string:
         return ansi_to_i64(m_str);
      case type_i8:
         return m_i8;
      case type_u8:
         return m_u8;
      case type_i16:
         return m_i16;
      case type_u16:
         return m_u16;
      case type_i32:
         return m_i32;
      case type_u32:
         return m_u32;
      case type_i64:
         return m_i64;
      case type_u64:
         return m_u64;
      case type_pi8:
         if (::is_null(m_p)) return iDefault;
         return *m_pi8;
      case type_pu8:
         if (::is_null(m_p)) return iDefault;
         return *m_pu8;
      case type_pi16:
         if (::is_null(m_p)) return iDefault;
         return *m_pi16;
      case type_pu16:
         if (::is_null(m_p)) return iDefault;
         return *m_pu16;
      case type_pi32:
         if (::is_null(m_p)) return iDefault;
         return *m_pi32;
      case type_pu32:
         if (::is_null(m_p)) return iDefault;
         return *m_pu32;
      case type_pi64:
         if (::is_null(m_p)) return iDefault;
         return *m_pi64;
      case type_pu64:
         if (::is_null(m_p)) return iDefault;
         return *m_pu64;
      case type_element:
      case type_path:
         return iDefault;
      case type_pvar:
         return m_pvar->i64(iDefault);
      case type_prop:
         return m_pprop->i64(iDefault);
      default:
         return iDefault;

      }
   }
   catch (...)
   {

   }

   return iDefault;

}


::u64 payload::u64(::u64 uiDefault) const
{
   switch(m_etype)
   {
   case e_type_null:
      return uiDefault;
   case type_empty:
      return uiDefault;
   case type_string:
      return atol(m_str);
   case type_i32:
      return m_i32;
   case type_u32:
      return m_u32;
   case type_i64:
      return m_i64;
   case type_u64:
      return m_u64;
   case type_float:
      return (::u64) m_f;
   case type_double:
      return (::u64) m_d;
   case type_element:
   case type_path:
      return uiDefault;
   case type_pvar:
      return m_pvar->u64(uiDefault);
   case type_prop:
      return m_pprop->u64(uiDefault);
   default:
      return uiDefault;
   }

}


::promise::routine payload::get_routine() const
{

   if (get_type() != ::type_routine)
   {

      return ::promise::routine();

   }

   return m_routine;

}


::promise::process payload::get_process() const
{

   if (get_type() != ::type_process)
   {

      return ::promise::process();

   }

   return m_process;

}


float payload::get_float(float fDefault) const
{
   switch(m_etype)
   {
   case e_type_null:
      return fDefault;
   case type_empty:
      return fDefault;
   case type_i32:
      return (float) m_i32;
   case type_u32:
      return (float) m_u32;
   case type_i64:
      return (float) m_i64;
   case type_u64:
      return (float) m_u64;
   case type_float:
      return m_f;
   case type_double:
      return (float) m_d;
   case type_string:
   #if defined(LINUX) || defined(ANDROID)
      return (float) atof(m_str);
   #else
      return (float) _atof_l(m_str, ::acme::g_localeC);
   #endif
   case type_pvar:
      return m_pvar->get_float(fDefault);
   case type_prop:
      return m_pprop->get_float(fDefault);
   default:
      return fDefault;
   }

}


//image * payload::image() const
//{
//
//   if (m_etype != ::type_element)
//   {
//
//      return nullptr;
//
//   }
//
//   return cast < ::image >();
//
//}


double payload::get_double(double dDefault) const
{
   double d;
   if(m_etype == e_type_null)
   {
      return dDefault;
   }
   else if(m_etype == type_empty)
   {
      return dDefault;
   }
   else if(m_etype == ::type_i32)
   {
      d = (double) m_i32;
   }
   else if(m_etype == ::type_u32)
   {

      d = (double) m_u32;

   }
   else if(m_etype == ::type_i64)
   {

      d = (double) m_i64;

   }
   else if(m_etype == ::type_u64)
   {

      d = (double) m_u64;

   }
   else if(m_etype == ::type_float)
   {

      d = (double) m_f;

   }
   else if(m_etype == ::type_double)
   {

      d = m_d;

   }
   else if(m_etype == ::type_string)
   {

#if defined(LINUX) || defined(ANDROID)

      d = atof(m_str);

#else

      d = _atof_l(m_str, ::acme::g_localeC);

#endif

   }
   else if(m_etype == ::type_pvar)
   {

      d = m_pvar->get_double(dDefault);

   }
   else if (m_etype == ::type_prop)
   {

      d = m_pprop->get_double(dDefault);

   }
   else
   {

      return dDefault;

   }

   return d;

}


class ::memory & payload::memory()
{

   if(get_type() != type_memory)
   {

      set_element(create_memory());

   }

   return *m_pmemory;

}


::memory payload::memory() const
{

   if (m_etype != type_memory)
   {

      return memory();

   }

   return *m_pmemory;

}


payload::operator ::file::path & ()
{

   if (m_etype == ::type_pvar)
   {

      return m_pvar->operator ::file::path & ();

   }
   else if (m_etype == ::type_prop)
   {

      return m_pprop->operator ::file::path & ();

   }
   else if (m_etype != ::type_path)
   {

      auto ppath = __create_new < ::file::path_object >();

      ppath->assign(get_file_path());

      set_element(ppath);

   }

   return *m_ppath;

}


payload::operator ::file::path() const
{

   return get_file_path();

}


string_array & payload::stra()
{

   if(m_etype != type_stra)
   {

      auto pstra = __new(string_array());

      pstra->add(*this);

      set_element(pstra);

   }
   else if(::is_null(m_pstra))
   {

      m_pstra = __new(string_array());

      ::add_ref(m_pstra);

   }

   return *m_pstra;

}


int_array & payload::inta()
{

   if(m_etype != type_inta)
   {

      auto pia  = __new(int_array());

      for(::i32 i = 0; i < array_get_count(); i++)
      {

         pia->add((::i32) at(i));

      }

      set_type(type_inta, false);

      set_element(pia);

   }
   else if (::is_null(m_pia))
   {

      m_pia = __new(int_array());

      ::add_ref(m_pia);

   }

   return *m_pia;

}


i64_array & payload::int64a()
{

   if(m_etype != type_i64a)
   {

      auto pia  = __new(i64_array());

      for(index i = 0; i < array_get_count(); i++)
      {

         pia->add(at(i).i64());

      }

      set_type(type_i64a, false);

      set_element(pia);

   }
   else if(::is_null(m_pi64a))
   {

      m_pi64a = __new(i64_array());

      add_ref(m_pi64a);

   }

   return *m_pi64a;

}


duration & payload::duration()
{

   if (m_etype == type_duration)
   {

      return m_duration;

   }
   else if (m_etype == type_pduration)
   {

      return *m_pduration;

   }
   else
   {

      set_type(type_duration);

      m_duration.set_null();

      return m_duration;

   }

}


const string_array & payload::stra() const
{

   return ((payload *)this)->stra();

}


const int_array & payload::inta() const
{

   return ((payload *)this)->inta();

}


const i64_array & payload::int64a() const
{

   return ((payload *)this)->int64a();

}


class payload & payload::operator = (payload * pvar)
{

   if (m_pvar == pvar)
   {

      return *this;

   }

   set_type(type_pvar, false);

   m_pvar = pvar;

   return *this;

}


class payload & payload::operator = (const payload * pvar)
{

   return operator =((payload*)pvar);

}


var_array & payload::vara()
{

   if(m_etype == type_pvar)
   {

      return m_pvar->vara();

   }
   else if (m_etype == type_prop)
   {

      return m_pprop->vara();

   }
   else if(m_etype != type_vara)
   {

      auto pvara  = __new(var_array());

      if (is_empty() || !operator bool())
      {

      }
      else
      {

         for (::i32 i = 0; i < array_get_count(); i++)
         {

            pvara->add(at(i));

         }

      }

      set_element(pvara);

   }
   else if (::is_null(m_pvara))
   {

      m_pvara = new var_array();

   }

   return *m_pvara;

}


property_set & payload::propset()
{


   if (m_etype == type_pvar)
   {

      return m_pvar->propset();

   }
   else if (m_etype == type_prop)
   {

      return m_pprop->propset();

   }
   else if (m_etype != type_propset)
   {

      auto pset = __new(property_set());

      if (is_empty() || !operator bool())
      {

      }
      else
      {

         for (::i32 i = 0; i < array_get_count(); i++)
         {

            pset->set_at(i, at(i));

         }

      }

      set_element(pset);

   }
   else if (::is_null(m_pset))
   {

      m_pset = new property_set();

   }

   return *m_pset;

}


const var_array & payload::vara() const
{

   return ((payload *)this)->vara();

}


const ::duration & payload::duration() const
{

   return ((payload *)this)->duration();

}


const property_set & payload::propset() const
{

   return ((payload *)this)->propset();

}


property & payload::prop()
{

   if(m_etype != type_prop)
   {

      __throw(exception::exception("payload is not a property (1)"));

   }

   return *m_pprop;

}


const property & payload::prop() const
{

   return ((payload *)this)->prop();

}


string payload::implode(const char * pszGlue) const
{
   if(get_type() == type_propset)
   {
      return propset().implode(pszGlue);
   }
   else if(get_type() == type_vara)
   {
      return vara().implode(pszGlue);
   }
   else if(get_type() == type_stra)
   {
      return stra().implode(pszGlue);
   }
   return "";
}


payload payload::explode(const char * pszGlue, bool bAddEmpty) const
{

   class payload payload;

   payload.stra().add_tokens(get_string(), pszGlue, bAddEmpty);

   return payload;

}




::comparison::var_strict payload::strict_compare() const
{

   return *this;

}


payload payload::dereference()
{
   if(get_type() == type_pvar)
      return m_pvar->dereference();
   else if (get_type() == type_prop)
      return m_pprop->dereference();
   else if(get_type() == type_pstring)
      return *m_pstr;
   else if(get_type() == type_i32)
      return *m_pi32;
   else if(get_type() == type_pbool)
      return *m_pb;
   else
      return *this;
}


//payload payload::at(index i) const
//{
//
//   switch(m_etype)
//   {
//   case type_inta:
//      return &m_pia->element_at(i);
//   case type_stra:
//      return &m_pstra->element_at(i);
//   case type_vara:
//      return &m_pvara->element_at(i);
//   case type_propset:
//      return &m_pset->element_at(i).element2();
//   case type_pvar:
//      return m_pvar->at(i);
//   default:
//      if(i == 0)
//      {
//         return (payload *) this;
//      }
//      else
//      {
//         __throw(::exception::exception("index out of bounds"));
//      }
//   }
//}


payload payload::at(index i)
{
   switch(m_etype)
   {
   case type_inta:
      return &m_pia->element_at(i);
   case type_stra:
      return &m_pstra->element_at(i);
   case type_vara:
      return &m_pvara->element_at(i);
   case type_propset:
      return m_pset->ptr_at(i);
   case type_pvar:
      return m_pvar->at(i);
   case type_prop:
      return m_pprop->at(i);
   default:
      if(i == 0)
      {
         return this;
      }
      else
      {
         __throw(::exception::exception("index out of bounds"));
      }
   }
}

bool payload::array_contains(const char * psz, index find, ::count count) const
{
   switch(m_etype)
   {
   case type_inta:
      return inta().contains(atoi(psz), find, count);
   case type_stra:
      return stra().contains(psz, find, count);
   case type_vara:
      return vara().contains(psz, find, count);
   case type_propset:
      return propset().contains_value(psz, find, count);
   default:
   {
      index upperbound = min(array_get_upper_bound(), find + count - 1);
      for(index i = find; i <= upperbound; i++)
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

bool payload::array_contains_ci(const char * psz, index find, index last) const
{
   switch(m_etype)
   {
   case type_bool:
      return false;
   case type_inta:
      return inta().contains(atoi(psz), find, last);
   case type_stra:
      return stra().contains_ci(psz, find, last);
   case type_vara:
      return vara().contains_ci(psz, find, last);
   case type_propset:
      return propset().contains_value_ci(psz, find, last);
   default:
   {
      index upperbound = min(array_get_upper_bound(), last);
      for(index i = find; i <= upperbound; i++)
      {
         if(at(i).get_string().compare_ci(psz) == 0)
         {
            return true;
         }
      }
   }
   }
   return false;
}


payload payload::equals_ci_get(const char * pszCompare, payload varOnEqual, payload varOnDifferent) const
{
   if(compare_ci(pszCompare) == 0)
   {
      return varOnEqual;
   }
   else
   {
      return varOnDifferent;
   }
}

payload payload::equals_ci_get(const char * pszCompare, payload varOnEqual) const
{
   if(compare_ci(pszCompare) == 0)
   {
      return varOnEqual;
   }
   else
   {
      return payload();
   }
}


payload payload::operator - (::i32 i) const
{
   return i32() - i;
}

payload payload::operator - (::u32 user) const
{
   return u32() - user;
}

payload payload::operator - (::i64 l) const
{
   return i64() - l;
}

payload payload::operator - (::u64 ul) const
{
   return (::i64) (u64() - ul);
}

payload payload::operator - (double d) const
{
   return get_double() - d;
}

payload operator - (::i32 i, const class payload & payload)
{
   return i - payload.i32();
}

payload operator - (::u32 user, const class payload & payload)
{
   return user - payload.u32();
}

payload operator - (::i64 l, const class payload & payload)
{
   return l - payload.i64();
}

payload operator - (::u64 ul, const class payload & payload)
{
   return (::i64) (ul - payload.u64());
}

payload operator - (double d, const class payload & payload)
{
   return d - payload.get_double();
}

payload operator - (const class payload & var1, const class payload & var2)
{
   payload payload;
   if(var1.m_etype == ::type_inta)
   {
      if(var2.m_etype == ::type_inta)
      {
         payload = var1.inta() - var2.inta();
      }
      else
      {
         payload = var1;
         payload.inta().remove(var2.i32());
      }
   }
   else if(var1.m_etype == ::type_stra)
   {
      if(var2.m_etype == ::type_stra)
      {
         payload = var1.stra() - var2.stra();
      }
      else if(var2.is_array())
      {
         payload = var1.stra() - const_cast < class payload & > (var2).stra();
      }
      else
      {
         payload = var1;
         payload.stra().remove(var2.get_string());
      }
   }
   else if(var1.m_etype == ::type_vara)
   {
      if(var2.m_etype == ::type_vara)
      {
         payload = var1.vara() - var2.vara();
      }
      else
      {
         payload = var1;
         payload.vara().remove(var2);
      }
   }
   else if(var1.is_double() || var2.is_double())
   {
      payload = var1.get_double() - var2.get_double();
   }
   else if(var1.is_integer() || var2.is_integer())
   {
      payload = var1.i32() - var2.i32();
   }
   else if(var1.is_natural() || var2.is_natural())
   {
      payload = var1.u32() - var2.u32();
   }
   else
   {
      payload = atoi(var1.get_string()) - atoi(var2.get_string());
   }
   return payload;
}


payload payload::operator + (::i32 i) const
{
   return i32() + i;
}

payload payload::operator + (::u32 user) const
{
   return u32() + user;
}

payload payload::operator + (::i64 l) const
{
   return i64() + l;
}

payload payload::operator + (::u64 ul) const
{
   return (::u32) (u64() + ul);
}

payload payload::operator + (const string & str) const
{

   payload varRet(*this);

   if (varRet.is_real())
   {

      if (::str::is_integer(str))
      {

         varRet += strtod(str, nullptr);

      }
      else
      {

         varRet.set_string(varRet.get_string() + str);

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

         varRet.set_string(varRet.get_string() + str);

      }

   }
   else
   {

      varRet.set_string(varRet.get_string() + str);

   }

   return varRet;

}

payload payload::operator + (double d) const
{
   return get_double() + d;
}

payload operator + (::i32 i, const class payload & payload)
{
   return i + payload.i32();
}

payload operator + (::u32 user, const class payload & payload)
{
   return user + payload.u32();
}

payload operator + (::i64 l, const class payload & payload)
{
   return l + payload.i64();
}

payload operator + (::u64 ul, const class payload & payload)
{
   return (::u32) (ul + payload.u64());
}

payload operator + (double d, const class payload & payload)
{
   return d + payload.get_double();
}

payload operator + (const class payload & var1, const class payload & var2)
{
   payload payload;
   if(var1.m_etype == ::type_inta
         || var1.m_etype == ::type_inta)
   {
      if(var1.m_etype == ::type_inta)
      {
         if(var2.m_etype == ::type_inta)
         {
            payload = var1.inta() + var2.inta();
         }
         else
         {
            payload = var1;
            payload.inta().add(var2.i32());
         }
      }
      else
      {
         payload = var2;
         payload.inta().add(var1.i32());
      }
   }
   else if(var1.m_etype == ::type_stra
           || var2.m_etype == ::type_stra)
   {
      if(var1.m_etype == ::type_stra)
      {
         if(var2.m_etype == ::type_stra)
         {
            payload = var1.stra() + var2.stra();
         }
         else
         {
            payload = var1;
            payload.stra().add(var2.get_string());
         }
      }
      else
      {
         payload = var2;
         payload.stra().add(var1.get_string());
      }
   }
   else if(var1.m_etype == ::type_vara
           || var2.m_etype == ::type_vara)
   {
      if(var2.m_etype == ::type_vara)
      {
         if(var2.m_etype == ::type_vara)
         {
            payload = var1.vara() + var2.vara();
         }
         else
         {
            payload = var1;
            payload.vara().add(var2);
         }
      }
      else
      {
         payload = var2;
         payload.vara().add(var1);
      }
   }
   else if(var1.is_double() && var2.is_double())
   {
      payload = var1.get_double() + var2.get_double();
   }
   else if(var1.is_integer() && var2.is_integer())
   {
      payload = var1.i32() + var2.i32();
   }
   else if(var1.is_natural() && var2.is_natural())
   {
      payload = var1.u32() + var2.u32();
   }
   else
   {
      payload = var1.get_string() + var2.get_string();
   }
   return payload;
}






















payload payload::operator / (::i32 i) const
{
   return i32() / i;
}

payload payload::operator / (::u32 user) const
{
   return u32() / user;
}

payload payload::operator / (::i64 l) const
{
   return i64() / l;
}

payload payload::operator / (::u64 ul) const
{

   switch(m_etype)
   {
   case ::e_type_null:
      return payload(e_type_null);
   case ::type_empty:
      return 0.0 / ul; // throws division by zero exception if ul stream zero
   case ::type_i32:
      return m_i32 / (::index) ul;
   case ::type_u32:
      return m_u32 / (::uptr) ul;
   case ::type_i64:
      return m_i64 / (::i64) ul;
   case ::type_u64:
      return m_u64 / (::u64) ul;
   case ::type_float:
      return m_f / (float) ul;
   case ::type_double:
      return m_d / (double) ul;
   case ::type_string:
#if defined(LINUX) || defined(ANDROID)
      return atof(m_str) / (double) ul;
#else
      return _atof_l(m_str, ::acme::g_localeC) / (double) ul;
#endif
   case ::type_pvar:
      return m_pvar->operator / (ul);
   case ::type_prop:
      return m_pprop->operator / (ul);
   default:
      return 0.0 / ul; // throws division by zero exception if ul stream zero
   }

}

payload payload::operator / (double d) const
{
   return get_double() / d;
}

payload operator / (::i32 i, const class payload & payload)
{
   return i / payload.i32();
}

payload operator / (::u32 user, const class payload & payload)
{
   return user / payload.u32();
}

payload operator / (::i64 l, const class payload & payload)
{
   return l / payload.i64();
}


payload operator / (::u64 ul, const class payload & payload)
{
   switch(payload.m_etype)
   {
   case ::e_type_null:
      __throw(::exception::exception("division by zero"));
   case ::type_empty:
      __throw(::exception::exception("division by zero"));
   case ::type_i32:
      return (iptr) ul / payload.m_i32;
   case ::type_u32:
      return (uptr) ul / payload.m_u32;
   case ::type_i64:
      return (::i64) ul / payload.m_i64;
   case ::type_u64:
      return (::u64) ul / payload.m_u64;
   case ::type_float:
      return (float) ul / payload.m_f;
   case ::type_double:
      return (double) ul / payload.m_d;
   case ::type_string:
#if defined(LINUX) || defined(ANDROID)
      return (double) ul / atof(payload.m_str);
#else
      return (double) ul / _atof_l(payload.m_str, ::acme::g_localeC);
#endif
   case ::type_pvar:
      return operator / (ul, *payload.m_pvar);
   case ::type_prop:
      return operator / (ul, *payload.m_pprop);
   default:
      __throw(::exception::exception("division by zero"));
   }

}




payload operator / (double d, const class payload & payload)
{
   return d / payload.get_double();
}

payload operator / (const class payload & var1, const class payload & var2)
{
   payload payload;
   if(var1.m_etype == ::type_inta)
   {
      if(var2.m_etype == ::type_inta)
      {
         payload = var1;
         payload.inta().intersect(var2.inta());
      }
      else
      {
         payload = var1;
         payload.inta().divide(var2.i32());
      }
   }
   else if(var1.m_etype == ::type_stra)
   {
      if(var2.m_etype == ::type_stra)
      {
         //payload = var1.stra().intersect(var2.stra());
      }
      else
      {
         payload = var1;
         payload.stra().remove(var2.get_string());
      }
   }
   else if(var1.m_etype == ::type_vara)
   {
      if(var2.m_etype == ::type_vara)
      {
         //payload = var1.vara() / var2.vara();
      }
      else
      {
         payload = var1;
         payload.vara().remove(var2);
      }
   }
   else if(var1.is_double() || var2.is_double())
   {
      payload = var1.get_double() / var2.get_double();
   }
   else if(var1.is_integer() || var2.is_integer())
   {
      payload = var1.i32() / var2.i32();
   }
   else if(var1.is_natural() || var2.is_natural())
   {
      payload = var1.u32() / var2.u32();
   }
   else
   {
      payload = atoi(var1.get_string()) / atoi(var2.get_string());
   }
   return payload;
}


payload payload::operator * (::i32 i) const
{
   return i32() * i;
}

payload payload::operator * (::u32 user) const
{
   return u32() * user;
}

payload payload::operator * (::i64 l) const
{
   return i64() * l;
}

payload payload::operator * (::u64 ul) const
{
   switch(m_etype)
   {
   case ::e_type_null:
      return payload(e_type_null);
   case ::type_empty:
      return 0.0;
   case ::type_i32:
      return m_i32 * (::index) ul;
   case ::type_u32:
      return m_u32 * (::uptr) ul;
   case ::type_i64:
      return m_i64 * (::i64) ul;
   case ::type_u64:
      return m_u64 * (::u64) ul;
   case ::type_float:
      return m_f * (float) ul;
   case ::type_double:
      return m_d * (double) ul;
   case ::type_string:
#if defined(LINUX) || defined(ANDROID)

      return atof(m_str) * (double) ul;
#else
      return _atof_l(m_str, ::acme::g_localeC) * (double) ul;
#endif
   case ::type_pvar:
      return m_pvar->operator * (ul);
   case ::type_prop:
      return m_pprop->operator * (ul);
   default:
      return 0.0;
   }

}

payload payload::operator * (double d) const
{
   return get_double() * d;
}

payload operator * (::i32 i, const class payload & payload)
{
   return i * payload.i32();
}

payload operator * (::u32 user, const class payload & payload)
{
   return user * payload.u32();
}

payload operator * (::i64 l, const class payload & payload)
{
   return l * payload.i64();
}

payload operator * (::u64 ul, const class payload & payload)
{

   switch(payload.m_etype)
   {
   case ::e_type_null:
      return ::payload(::e_type_null);
   case ::type_empty:
      return 0;
   case ::type_i32:
      return (iptr) ul * payload.m_i32;
   case ::type_u32:
      return (uptr) ul * payload.m_u32;
   case ::type_i64:
      return (::i64) ul * payload.m_i64;
   case ::type_u64:
      return (::u64) ul * payload.m_u64;
   case ::type_float:
      return (float) ul * payload.m_f;
   case ::type_double:
      return (double) ul * payload.m_d;
   case ::type_string:
#if defined(LINUX) || defined(ANDROID)
      return (double) ul * atof(payload.m_str);
#else
      return (double) ul * _atof_l(payload.m_str, ::acme::g_localeC);
#endif
   case ::type_pvar:
      return operator * (ul, *payload.m_pvar);
   case ::type_prop:
      return operator * (ul, *payload.m_pprop);
   default:
      return 0;
   }

}


payload operator * (double d, const class payload & payload)
{
   return d * payload.get_double();
}

payload operator * (const class payload & var1, const class payload & var2)
{

   payload payload;

   if(var1.m_etype == ::type_inta || var1.m_etype == ::type_inta)
   {

      ::papaya::array::intersection(payload.inta(), var1.inta(), var2.inta());

   }
   else if(var1.m_etype == ::type_stra || var2.m_etype == ::type_stra)
   {

      ::papaya::array::intersection(payload.stra(), var1.stra(), var2.stra());

   }
   else if(var1.m_etype == ::type_vara || var2.m_etype == ::type_vara)
   {

      ::papaya::array::intersection(payload.vara(), var1.vara(), var2.vara());

   }
   else if(var1.is_double() || var2.is_double())
   {

      payload = var1.get_double() * var2.get_double();

   }
   else if(var1.is_integer() || var2.is_integer())
   {

      payload = var1.i32() * var2.i32();

   }
   else if(var1.is_natural() || var2.is_natural())
   {

      payload = var1.u32() * var2.u32();

   }
   else
   {

      payload = var1.to_string().intersection(var2.to_string());

   }

   return payload;

}

























class payload & payload::operator -= (::i32 i)
{
   operator =(*this - i);
   return *this;
}

class payload & payload::operator -= (::u32 user)
{
   operator =(*this - user);
   return *this;
}

class payload & payload::operator -= (::i64 i)
{
   operator =(*this - i);
   return *this;
}

class payload & payload::operator -= (::u64 user)
{
   operator =(*this - user);
   return *this;
}

class payload & payload::operator -= (double d)
{
   operator =(*this - d);
   return *this;
}

class payload & payload::operator -= (const class payload & payload)
{
   operator =(*this - payload);
   return *this;
}
























class payload & payload::operator += (::i32 i)
{
   operator =(*this + i);
   return *this;
}

class payload & payload::operator += (::u32 user)
{
   operator =(*this + user);
   return *this;
}

class payload & payload::operator += (::i64 i)
{
   operator =(*this + i);
   return *this;
}

class payload & payload::operator += (::u64 user)
{
   operator =(*this + user);
   return *this;
}

class payload & payload::operator += (double d)
{
   operator =(*this + d);
   return *this;
}

class payload & payload::operator += (const class payload & payload)
{
   operator =(*this + payload);
   return *this;
}
























class payload & payload::operator /= (::i32 i)
{
   operator =(*this / i);
   return *this;
}

class payload & payload::operator /= (::u32 user)
{
   operator =(*this / user);
   return *this;
}

class payload & payload::operator /= (::i64 i)
{
   operator =(*this / i);
   return *this;
}

class payload & payload::operator /= (::u64 user)
{
   operator =(*this / user);
   return *this;
}

class payload & payload::operator /= (double d)
{
   operator =(*this / d);
   return *this;
}

class payload & payload::operator /= (const class payload & payload)
{
   operator =(*this / payload);
   return *this;
}
























class payload & payload::operator *= (::i32 i)
{
   operator =(*this * i);
   return *this;
}

class payload & payload::operator *= (::u32 user)
{
   operator =(*this * user);
   return *this;
}

class payload & payload::operator *= (::i64 i)
{
   operator =(*this * i);
   return *this;
}

class payload & payload::operator *= (::u64 user)
{
   operator =(*this * user);
   return *this;
}

class payload & payload::operator *= (double d)
{
   operator =(*this * d);
   return *this;
}


class payload & payload::operator *= (const class payload & payload)
{

   operator =(*this * payload);

   return *this;

}


























bool payload::is_scalar() const
{
   if(m_etype == type_new
         || m_etype == e_type_null
         || m_etype == type_empty)
   {
      return false;
   }
   else if(m_etype == type_string
           || m_etype == type_i32
           || m_etype == type_i32
           || m_etype == type_u32
           || m_etype == type_bool
           || m_etype == type_double)
   {
      return true;
   }
   else if(m_etype == type_stra
           || m_etype == type_inta
           || m_etype == type_vara
           || m_etype == type_propset)
   {
      return false;
   }
   else if(m_etype == type_prop)
   {
      return prop().is_scalar();
   }
   else if(m_etype == type_element)
   {
      return false;
   }
   else if (m_etype == type_path)
   {
      return false;
   }
   else
   {
      return false;
   }
}

bool payload::is_real() const
{
   if(m_etype == type_double || m_etype == type_float)
   {
      return true;
   }
   // simple, lazy, slow, and a bit incorrect
   // incorrect because atof and atoi returns partials results even if it
   // encounters non-numerical symbols
   else
   {
      string str = get_string();
#if defined(LINUX) || defined(ANDROID)
      if(is_scalar()
            && (fmod(atof(str), 1.0) == 0.0
                && fabs(atof(str)) <= pow(2.0, 31.0)))
#else
      if(is_scalar()
            && (fmod(_atof_l(str, ::acme::g_localeC), 1.0) == 0.0
                && fabs(_atof_l(str, ::acme::g_localeC)) <= pow(2.0, 31.0)))
#endif
      {
         str.trim();
         if(str.get_length() == 0)
            return false;
         else if(str[0] == '+'
                 || str[0] == '-'
                 || ansi_char_is_digit(str[0]))
         {
            ::i32 i;
            for(i = 1; i < str.get_length(); i++)
            {
               if(ansi_char_is_digit(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot1;
               }
               if(isspace(str[i]))
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
            for(; i < str.get_length(); i++)
            {
               if(ansi_char_is_digit(str[i]))
                  continue;
               if(str[i] == 'e' || str[i] == 'E')
                  goto e;
               return false;
            }
sp1:
            for(; i < str.get_length(); i++)
            {
               if(isspace(str[i]))
                  continue;
               if(str[i] == 'e' || str[i] == 'E')
                  goto e;
               return false;
            }
e:
//sp2:
            for(; i < str.get_length(); i++)
            {
               if(isspace(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot2;
               }
               if(ansi_char_is_digit(str[i]))
               {
                  i++;
                  break;
               }
               return false;
            }
            for(; i < str.get_length(); i++)
            {
               if(ansi_char_is_digit(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot2;
               }
               return false;
            }
dot2:
            for(; i < str.get_length(); i++)
            {
               if(ansi_char_is_digit(str[i]))
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
   if (m_etype == type_double)
   {
      return true;
   }
   return false;
}

bool payload::is_double() const
{
   if(m_etype == type_double)
   {
      return true;
   }
   // simple, lazy, slow, and a bit incorrect
   // incorrect because atof and atoi returns partials results even if it
   // encounters non-numerical symbols
   else
   {
      string str = get_string();
#if defined(LINUX) || defined(ANDROID)
      if(is_scalar()
            && (fmod(atof(str), 1.0) == 0.0
                && fabs(atof(str)) <= pow(2.0, 31.0)))
#else
      if(is_scalar()
            && (fmod(_atof_l(str, ::acme::g_localeC), 1.0) == 0.0
                && fabs(_atof_l(str, ::acme::g_localeC)) <= pow(2.0, 31.0)))
#endif
      {
         str.trim();
         if(str.get_length() == 0)
            return false;
         else if(str[0] == '+'
                 || str[0] == '-'
                 || ansi_char_is_digit(str[0]))
         {
            ::i32 i;
            for(i = 1; i < str.get_length(); i++)
            {
               if(ansi_char_is_digit(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot1;
               }
               if(isspace(str[i]))
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
            for(; i < str.get_length(); i++)
            {
               if(ansi_char_is_digit(str[i]))
                  continue;
               if(str[i] == 'e' || str[i] == 'E')
                  goto e;
               return false;
            }
sp1:
            for(; i < str.get_length(); i++)
            {
               if(isspace(str[i]))
                  continue;
               if(str[i] == 'e' || str[i] == 'E')
                  goto e;
               return false;
            }
e:
//sp2:
            for(; i < str.get_length(); i++)
            {
               if(isspace(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot2;
               }
               if(ansi_char_is_digit(str[i]))
               {
                  i++;
                  break;
               }
               return false;
            }
            for(; i < str.get_length(); i++)
            {
               if(ansi_char_is_digit(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot2;
               }
               return false;
            }
dot2:
            for(; i < str.get_length(); i++)
            {
               if(ansi_char_is_digit(str[i]))
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
   if(m_etype == type_i32 || m_etype == type_i64)
   {
      return true;
   }
   // simple, lazy, slow, and a bit incorrect
   // incorrect because atof and atoi returns partials results even if it
   // encounters non-numerical symbols
   else
   {
      string str = get_string();
#if defined(LINUX) || defined(ANDROID)
      if(is_scalar()
            && (fmod(atof(str), 1.0) == 0.0
                && fabs(atof(str)) <= pow(2.0, 31.0)))
#else
      if(is_scalar()
            && (fmod(_atof_l(str, ::acme::g_localeC), 1.0) == 0.0
                && fabs(_atof_l(str, ::acme::g_localeC)) <= pow(2.0, 31.0)))
#endif
      {
         str.trim();
         if(str.get_length() == 0)
            return false;
         else if(str[0] == '+'
                 || str[0] == '-'
                 || ansi_char_is_digit(str[0]))
         {
            for(index i = 1; i < str.get_length(); i++)
            {
               if(!ansi_char_is_digit(str[i]))
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
   if(m_etype == type_u32 || m_etype == type_u64)
   {
      return true;
   }
   // simple, lazy, slow, and a bit incorrect
   // incorrect because atof and atoi returns partials results even if it
   // encounters non-numerical symbols
   else
   {
      string str = get_string();
#if defined(LINUX) || defined(ANDROID)
      if(is_scalar()
            && (fmod(atof(str), 1.0) == 0.0
                && fabs(atof(str)) <= pow(2.0, 31.0)))
#else
      if(is_scalar()
            && (fmod(_atof_l(str, ::acme::g_localeC), 1.0) == 0.0
                && fabs(_atof_l(str, ::acme::g_localeC)) <= pow(2.0, 31.0)))
#endif
      {
         str.trim();
         if(str.get_length() == 0)
            return false;
         else if(str[0] == '+'
                 || ansi_char_is_digit(str[0]))
         {
            for(index i = 1; i < str.get_length(); i++)
            {
               if(!ansi_char_is_digit(str[i]))
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

payload::operator bool() const
{

   if (m_etype == type_enum_status)
   {

      return ::succeeded(m_estatus);

   }
   else if (m_etype == type_new
         || m_etype == e_type_null
         || m_etype == type_empty
         || m_etype == type_empty_argument
         || m_etype == type_not_found)
   {

      return false;

   }
   else if (m_etype == type_key_exists
            || m_etype == type_filetime
            || m_etype == type_time)
   {

      return true;

   }
   else if (m_etype == type_bool)
   {

      return m_b;

   }
   else if (m_etype == type_enum_check)
   {

      return __bool(m_echeck);

   }
   else if (m_etype == type_pbool)
   {

      return m_pb != nullptr && *m_pb;

   }
   else if(m_etype == type_i32 || m_etype == type_u32)
   {

      return m_i32 != 0;

   }
   else if (m_etype == type_i64 || m_etype == type_u64)
   {

      return m_i64 != 0;

   }
   else if (m_etype == type_i32 || m_etype == type_u32)
   {

      return m_pi32 != nullptr && *m_pi32 != 0;

   }
   else if (m_etype == type_i64 || m_etype == type_u64)
   {

      return m_pi64 != nullptr && *m_pi64 != 0;

   }
   else if(m_etype == type_string)
   {

      return ::papaya::is_true(m_str);

   }
   else if (m_etype == type_pstring)
   {

      return m_pstr != nullptr && ::papaya::is_true(*m_pstr);

   }
   else if (m_etype == type_id)
   {

      return (m_id.is_text() && ::papaya::is_true(m_id.m_psz)) || (m_id.is_integer() && m_id.m_i != 0);

   }
   else if (m_etype == type_pid)
   {

      return m_pid != nullptr && ((m_pid->is_text() && ::papaya::is_true(m_pid->m_psz)) || (m_pid->is_integer() && m_pid->m_i != 0));

   }
   else if (m_etype == type_inta)
   {

      return m_pia != nullptr && (m_pia->get_count() >= 2 || (m_pia->get_count() == 1 && !m_pia->element_at(0)));

   }
   else if (m_etype == type_i64a)
   {

      return m_pi64a != nullptr && (m_pi64a->get_count() >= 2 || (m_pi64a->get_count() == 1 && !m_pi64a->element_at(0)));

   }
   else if (m_etype == type_stra)
   {

      return m_pstra != nullptr && (m_pstra->get_count() >= 2 || (m_pstra->get_count() == 1 && ::papaya::is_true(m_pstra->element_at(0))));

   }
   else if (m_etype == type_float)
   {

      return m_f != 0.0f;

   }
   else if (m_etype == type_double)
   {

      return m_d != 0.0;

   }
   else if (m_etype == type_pvar)
   {

      if (this == m_pvar)
      {

         return true;

      }

      return m_pvar->operator bool();

   }
   else if (m_etype == type_prop)
   {

      return m_pprop->operator bool();

   }
   else if (m_etype == type_vara)
   {

      return m_pvara != nullptr && (m_pvara->get_count() >= 2 || (m_pvara->get_count() == 1 && m_pvara->element_at(0).is_true()));

   }
   else if (m_etype == type_propset)
   {

      return m_pset != nullptr && ::papaya::array::every::is_true(m_pset->values());

   }
   else if (m_etype == type_duration)
   {

      return m_duration.operator bool();

   }
   else if (m_etype == type_pduration)
   {

      return m_pduration != nullptr && m_pduration->operator bool();

   }
   else if (m_etype == type_i8)
   {

      return m_i8 != '\0';

   }
   else if (m_etype == type_u8)
   {

      return m_u8 != 0;

   }
   else
   {

      return m_p != nullptr;

   }

}


bool payload::is_property_true(const ::id & id) const
{

   auto pproperty = find_property(id);

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


bool payload::is_property_false(const ::id & id) const
{

   return !is_property_true(id);

}

payload::operator block () const
{

   return ((payload *)this)->operator block ();

}

payload::operator block ()
{

   if (get_type() != type_memory)
   {

      __throw(exception::exception(error_wrong_type));

   }

   return *m_pmemory;

}



payload payload::get_topic(const ::id & id) const
{

   auto pproperty = find_property(id);

   if(!pproperty)
   {

      return *this;

   }

   return *pproperty;

}


//payload payload::defer_get(const ::id & id) const
//{
//
//   auto pproperty = defer_get_property(id);
//
//   if(::is_null(pproperty))
//   {
//
//      return type_new;
//
//   }
//
//   return *pproperty;
//
//}


//property * payload::defer_get_property(const ::id & id) const
//{
//   if(get_type() == type_propset)
//   {
//      return dynamic_cast < const property_set * > (m_pointer.m_p)->defer_get(id);
//   }
//   else if(get_type() == type_pvar)
//   {
//      return m_pvar->defer_get_property(id);
//   }
//   else if(get_type() == type_element)
//   {
//      if(cast < property_set >() != nullptr)
//      {
//         return cast < property_set >()->defer_get(id);
//      }
//      //else if(cast < property >() != nullptr)
//      //{
//      //   return cast < property >()->name().compare_ci(lpszName) == 0;
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


bool payload::has_property(const ::id & id) const
{

   return __found(property_index(id));

}


void payload::consume_identifier(const char * & psz)
{

   consume_number(psz, psz + strlen(psz) - 1);

}


void payload::consume_identifier(const char * & psz, const char * pszEnd)
{

   const char * pszParse = psz;

   ::str::consume_spaces(pszParse, 0, pszEnd);

   const char * pszStart = pszParse;

   while (ansi_char_is_alphabetic(*pszParse) && pszParse <= pszEnd)
   {

      pszParse++;

   }

   string str(pszStart, pszParse - pszStart);

   if (str.compare_ci("false") == 0)
   {

      operator = (false);

   }
   else if (str.compare_ci("true") == 0)
   {

      operator = (true);
   }
   else if (str.compare_ci("null") == 0)
   {
      set_type(::e_type_null);
   }
   else
   {
      throw_parsing_exception("not expected identifier");
   }
   psz = pszParse;
}

void payload::consume_number(const char * & psz)
{
   consume_number(psz, psz + strlen(psz) - 1);
}

void payload::consume_number(const char * & psz, const char * pszEnd)
{
   const char * pszParse = psz;
   bool bSigned = false;
   bool bFloat = false;
   ::str::consume_spaces(pszParse, 0, pszEnd);
   const char * pszStart = pszParse;
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

      throw_parsing_exception("empty string : not a number");

   }

   string strNumber(pszStart, pszParse - pszStart);

   if(bFloat)
   {

#if defined(LINUX) || defined(ANDROID)

      double d = atof(strNumber);

#else

      double d = _atof_l(strNumber, ::acme::g_localeC);

#endif

      operator = (d);

   }
   else
   {

      ::i64 i = (::i64) atoll(strNumber);

      operator = (i);

   }

   psz = pszParse;

}



void payload::parse_json(const char * & pszJson)
{
   parse_json(pszJson, pszJson + strlen(pszJson) - 1);
}

namespace str
{
   string consume_quoted_value_ex(const char * & pszXml,const char * pszEnd);
}



void var_skip_identifier(const char *& psz)
{
   var_skip_number(psz, psz + strlen(psz) - 1);
}


void var_skip_identifier(const char *& psz, const char * pszEnd)
{
   const char * pszParse = psz;
   ::str::consume_spaces(pszParse, 0, pszEnd);
   const char * pszStart = pszParse;
   while (ansi_char_is_alphabetic(*pszParse) && pszParse <= pszEnd)
      pszParse++;
   strsize iLen = pszParse - pszStart;
   if (iLen == 5 && ansi_count_compare_ci(pszStart, "false", 5) == 0)
   {
   }
   else if (iLen == 4)
   {
      if (ansi_count_compare_ci(pszStart, "true", 4) == 0)
      {
      }
      else if (ansi_count_compare_ci(pszStart, "null", 4) == 0)
      {
      }
      else
      {
         throw_parsing_exception("not expected identifier");
      }
   }
   else
   {
      throw_parsing_exception("not expected identifier");
   }
   psz = pszParse;
}



void var_skip_number(const char *& psz)
{
   var_skip_number(psz, psz + strlen(psz) - 1);
}

void var_skip_number(const char *& psz, const char * pszEnd)
{
   const char * pszParse = psz;
   ::str::consume_spaces(pszParse, 0, pszEnd);
   const char * pszStart = pszParse;
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
      throw_parsing_exception("empty string : not a number");
   }
   psz = pszParse;
}


void var_skip_json(const char *& pszJson, const char * pszEnd)
{

   ::str::consume_spaces(pszJson, 0, pszEnd);

   if (*pszJson == '{')
   {

      property_set_skip_json(pszJson, pszEnd);

   }
   else if (*pszJson == '\"')
   {

      ::str::skip_quoted_value_ex(pszJson, pszEnd);

   }
   else if (*pszJson == '\'')
   {

      ::str::skip_quoted_value_ex(pszJson, pszEnd);

   }
   else if (ansi_char_is_digit(*pszJson) || *pszJson == '-' || *pszJson == '.')
   {

      var_skip_number(pszJson, pszEnd);

   }
   else if (*pszJson == '[')
   {

      var_array_skip_json(pszJson, pszEnd);

   }
   else if (*pszJson == ']')
   {

      ::output_debug_string("");

   }
   else if (*pszJson == '\0')
   {

      ::output_debug_string("");

   }
   else
   {

      var_skip_identifier(pszJson, pszEnd);

   }

}


void var_skip_json(const char *& pszJson)
{
   var_skip_json(pszJson, pszJson + strlen(pszJson) - 1);
}




const char * payload::parse_json(const string & strJson)
{

   const char * pszJson = strJson;

   parse_json(pszJson, pszJson + strJson.get_length());

   return pszJson;

}

void payload::parse_json(const char *& pszJson, const char * pszEnd)
{
   ::str::consume_spaces(pszJson, 0, pszEnd);
   if (*pszJson == '{')
   {
      propset().parse_json(pszJson, pszEnd);
   }
   else if (*pszJson == '\"')
   {
      operator = (::str::consume_quoted_value_ex(pszJson, pszEnd));
   }
   else if (ansi_char_is_digit(*pszJson) || *pszJson == '-' || *pszJson == '.')
   {
      consume_number(pszJson, pszEnd);
   }
   else if (*pszJson == '[')
   {
      vara().parse_json(pszJson, pszEnd);
   }
   else if (*pszJson == ']')
   {
      ::output_debug_string("");

      //pszJson++;

   }
   else if (*pszJson == '\0')
   {
      ::output_debug_string("");
   }
   else
   {
      consume_identifier(pszJson, pszEnd);
   }
}

::enum_type payload::find_json_child(const char *& pszJson, const char * pszEnd, const payload & varChild)
{

   ::str::consume_spaces(pszJson, 0, pszEnd);

   if (*pszJson == '{')
   {

      ::str::consume_spaces(pszJson, 0, pszEnd);

      if (*pszJson == '\0')
      {

         return ::type_new;

      }

      ::str::consume(pszJson, "{", 1, pszEnd);

      ::str::consume_spaces(pszJson, 0, pszEnd);

      if (*pszJson == '}')
      {

         pszJson++;

         return ::type_new;

      }

      ::id id;

      while (true)
      {

         property_parse_json_id(id, pszJson, pszEnd);

         if (varChild.get_string().compare_ci(id) == 0)
         {

            ::str::consume_spaces(pszJson, 0, pszEnd);
            ::str::consume(pszJson, ":", 1, pszEnd);


            return ::type_propset;

         }

         property_skip_json_value(pszJson, pszEnd);

         ::str::consume_spaces(pszJson, 0, pszEnd);

         if (*pszJson == ',')
         {
            pszJson++;
            continue;
         }
         else if (*pszJson == '}')
         {
            pszJson++;
            return ::type_new;
         }
         else
         {

            string str = "not expected character : ";

            str += pszJson;

            throw_json_parsing_exception(str);

         }

      }

   }
   else if (*pszJson == '\"')
   {
      operator=(::str::consume_quoted_value_ex(pszJson, pszEnd));
      if (operator == (varChild))
      {
         return ::type_string;
      }
      else
      {
         return ::type_new;
      }
   }
   else if (ansi_char_is_digit(*pszJson) || *pszJson == '-' || *pszJson == '.')
   {
      consume_number(pszJson, pszEnd);
      if (operator == (varChild))
      {
         return get_type();
      }
      else
      {
         return ::type_new;
      }
   }
   else if (*pszJson == '[')
   {
      ::str::consume_spaces(pszJson, 0, pszEnd);
      ::str::consume(pszJson, "[", 1, pszEnd);
      ::enum_type etype = find_json_id(pszJson, pszEnd, varChild);
      if (etype == ::type_new)
      {

         return ::type_new;

      }

      ::str::consume_spaces(pszJson, 0, pszEnd);

      if (*pszJson == ']')
      {
         pszJson++;

         return etype;

      }

      return ::type_new;

   }
   else if (*pszJson == ']')
   {
      ::output_debug_string("");
      return ::type_new;
   }
   else if (*pszJson == '\0')
   {
      ::output_debug_string("");
      return ::type_new;
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
         return ::type_new;
      }
   }

}


::enum_type payload::find_json_id(const char * & pszJson, const char * pszEnd, const payload & varChild)
{

   ::str::consume_spaces(pszJson, 0, pszEnd);

   if (*pszJson == '{')
   {

      return ::type_new;


   }
   else if (*pszJson == '\"')
   {
      operator=(::str::consume_quoted_value_ex(pszJson, pszEnd));
      if (operator == (varChild))
      {
         return ::type_string;
      }
      else
      {
         return ::type_new;
      }
   }
   else if (ansi_char_is_digit(*pszJson) || *pszJson == '-' || *pszJson == '.')
   {
      consume_number(pszJson, pszEnd);
      if (operator == (varChild))
      {
         return get_type();
      }
      else
      {
         return ::type_new;
      }
   }
   else if (*pszJson == '[')
   {

      return ::type_new;

   }
   else if (*pszJson == ']')
   {
      return ::type_new;
   }
   else if (*pszJson == '\0')
   {
      return ::type_new;
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
         return ::type_new;
      }
   }
}


bool payload::is_numeric() const
{

   switch(get_type())
   {
   case type_parareturn:
   case type_new:
   case e_type_null:
   case type_empty:
   case type_empty_argument:
      return false;

   case type_string: // may be improved MBI
      return false;

   case type_pstring: // may be improved MBI
      return false;

   case type_i8:
   case type_pi8:
   case type_u8:
   case type_pu8:
   case type_i16:
   case type_pi16:
   case type_u16:
   case type_pu16:
   case type_i32:
   case type_pi32:
   case type_u32:
   case type_pu32:
   case type_i64:
   case type_pi64:
   case type_u64:
   case type_pu64:
      return true;

   case type_pvar:
      return m_pvar->is_numeric();
   case type_prop:
      return m_pprop->is_numeric();


   case type_element:
   case type_path:
      return false;

   case type_bool:
   case type_pbool:
      return false;

   case type_double:
      return true;

   case type_stra:
   case type_inta:
   case type_vara:
   case type_propset:
   case type_memory:
      return false;

   case type_time:
   case type_filetime:
      return false;

   case type_id:
      return false; // m_id.is_number(); // may be improved MBI

   case type_pid:
      return false; // m_pid->is_number(); // may be improved MBI

   case type_i64a:
      return false;
   case type_routine:
      return false;
   case type_process:
      return false;
   default:
      __throw(not_implemented());

   };

}



bool is_return_ok(para_return eret)
{
   return ((::i32)eret) >= 0;
}


payload str_ends_get(const char * pcsz, const char * pcszSuffix)
{

   string str(pcsz);

   string strSuffix(pcszSuffix);

   strsize iLen = strSuffix.get_length();

   if(str.Right(iLen) == pcszSuffix)

   {

      return str.Left(str.get_length() - iLen);

   }

   return false;

}


string payload::get_json(bool bNewLine) const
{

   string str;

   return get_json(str, bNewLine);

}


string & payload::get_json(string & str, bool bNewLine) const
{

   if (is_null())
   {

      return str += "null";

   }
   else if (get_type() == ::type_propset)
   {

      return propset().get_json(str, bNewLine);

   }
   else if (get_type() == ::type_stra)
   {

      return stra().get_json(str, bNewLine);

   }
   else if (get_type() == ::type_inta)
   {

      return inta().get_json(str, bNewLine);

   }
   else if (get_type() == ::type_i64a)
   {

      return int64a().get_json(str, bNewLine);

   }
   else if (get_type() == ::type_vara)
   {

      return vara().get_json(str, bNewLine);

   }
   else if (is_numeric())
   {

      return str += get_string();

   }
   else if (get_type() == ::type_bool)
   {

      return str += operator bool() ? "true" : "false";

   }
   else
   {

      string strValue;

      strValue = get_string();

      strValue.replace("\"", "\\\"");

      return str += ("\"" + strValue + "\"");

   }

}



void payload::null()
{

   set_type(::e_type_null);

}




::file::path payload::get_file_path() const
{

   if(m_etype == type_element)
   {

      auto pfile = cast < ::file::file >();

      if (pfile)
      {

         auto path = pfile->get_file_path();

         return path;

      }

   }

   if(m_etype == type_propset)
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
   else if (m_etype == type_path)
   {

      auto ppath = cast < ::file::path_object > ();

      if (ppath)
      {

         return *ppath;

      }

   }

   return ::file::path(get_string());

}


payload & payload::operator |= (cflag < ::file::enum_flag > eflag)
{

   auto pfile = cast < ::file::file > ();

   if (pfile)
   {

      propset()["file"] = pfile;

   }


   if (m_etype == type_propset)
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
   else if (m_etype == type_path)
   {

      auto ppath = cast < ::file::path_object > ();

      if (ppath)
      {

         *ppath |= eflag;

      }

   }
   else
   {

      auto ppath = __new(::file::path_object(get_file_path()));

      *ppath |= eflag;

      set_element(ppath);

   }

   return *this;

}


bool payload::is_false() const
{

   switch(m_etype)
   {

   /// special meaning
   case type_parareturn:
   case type_new:
   case e_type_null:
   case type_empty:
   case type_empty_argument:
   case type_not_found:
      return false;

   case type_key_exists:
      return false;
   // integral
   case type_bool:
      return !m_b;
   case type_pbool:
      return !*m_pb;
   case type_i8:
      return !m_i8;
   case type_pi8:
      return !m_pi8 || !*m_pi8;
   case type_byte:
      return !m_u8;
   case type_pu8:
      return !m_pu8 || !*m_pu8;
   case type_i16:
      return !m_i16;
   case type_pi16:
      return !m_pi16 || !*m_pi16;
   case type_u16:
      return !m_u16;
   case type_pu16:
      return !m_pu16 || !*m_pu16;
   case type_i32:
      return !m_i32;
   case type_pi32:
      return !m_pi32 || !*m_pi32;
   case type_u32:
      return !m_u32;
   case type_pu32:
      return !m_pu32 || !*m_pu32;
   case type_i64:
      return !m_i64;
   case type_pi64:
      return !m_pi64 || !*m_pi64;
   case type_u64:
      return !m_u64;
   case type_pu64:
      return !m_pu64 || !*m_pu64;

   // floating point
   case type_pfloat:
      return !*m_pf;
   case type_float:
      return !m_f;
   case type_pdouble:
      return !*m_pd;
   case type_double:
      return !m_d;

   // simple classes
   case type_string:
      return m_str.is_empty() || !m_str.compare_ci("false")  || !m_str.compare_ci("no");
   case type_pstring:
      return !m_pstr || m_pstr->is_empty() || !m_pstr->compare_ci("false")  || !m_pstr->compare_ci("no");
   case type_type:
      return m_str.is_empty();
   case type_duration:
      return m_duration.is_null();
   case type_pduration:
      return !m_pduration || m_pduration->is_null();
   case type_id:
      return m_id.is_empty() || !m_id.compare_ci("false") || !m_id.compare_ci("no");
   case type_pid:
      return !m_pid || m_pid->is_empty() || !m_pid->compare_ci("false") || !m_pid->compare_ci("no");
   case type_time:
      return !m_time;
   case type_filetime:
      return !m_filetime;
   case type_pvar:
      return m_pvar || !*m_pvar;
   case type_prop:
      return m_pprop || !*m_pprop;
   case type_routine:
         return !m_routine;
   case type_process:
         return !m_process;

   // matter classes
   case type_element:
      return is_element_null();
   case type_stra:
      return ::is_null(m_pstra) || m_pstra->isEmpty();
   case type_inta:
      return ::is_null(m_pia) || m_pia->isEmpty();
   case type_vara:
      return ::is_null(m_pvara) || m_pvara->isEmpty();
   case type_propset:
      return ::is_null(m_pset) || m_pset->isEmpty();
   case type_i64a:
      return ::is_null(m_pi64a) || m_pi64a->isEmpty();
   case type_memory:
      return ::is_null(m_pmemory) || m_pmemory->is_empty();
   case type_path:
      return ::is_null(m_ppath) || m_ppath->is_empty();
   //case type_image:
   //   return !::is_ok(m_pimage);

   // enum
   case type_secs:
      return !m_secs.m_iSeconds;
   case type_psecs:
      return !m_psecs || !m_psecs->m_iSeconds;
   case type_millis:
      return !m_millis.m_iMilliseconds;
   case type_pmillis:
      return !m_pmillis || !m_pmillis->m_iMilliseconds;
   case type_micros:
      return !m_micros.m_iMicroseconds;
   case type_pmicros:
      return !m_pmicros || !m_pmicros->m_iMicroseconds;
   case type_nanos:
      return !m_nanos.m_iNanoseconds;
   case type_pnanos:
      return !m_pnanos || !m_pnanos->m_iNanoseconds;
   case type_enum_command:
   case type_enum_status:
   case type_enum_check:
      return !m_i64;
   case __type_last_element:
         return false;

   }

   return !m_b;

}


bool payload::is_set_false() const
{

   switch(m_etype)
   {
   /// special meaning
   case type_parareturn:
   case type_new:
   case e_type_null:
   case type_empty:
   case type_empty_argument:
   case type_not_found:
      return false;

   case type_key_exists:
      return false;
   // integral
   case type_bool:
      return !m_b;
   case type_pbool:
      return !*m_pb;
   case type_i8:
      return !m_i8;
   case type_pi8:
      return !m_pi8 || !*m_pi8;
   case type_byte:
      return !m_u8;
   case type_pu8:
      return !m_pu8 || !*m_pu8;
   case type_i16:
      return !m_i16;
   case type_pi16:
      return !m_pi16 || !*m_pi16;
   case type_u16:
      return !m_u16;
   case type_pu16:
      return !m_pu16 || !*m_pu16;
   case type_i32:
      return !m_i32;
   case type_pi32:
      return !m_pi32 || !*m_pi32;
   case type_u32:
      return !m_u32;
   case type_pu32:
      return !m_pu32 || !*m_pu32;
   case type_i64:
      return !m_i64;
   case type_pi64:
      return !m_pi64 || !*m_pi64;
   case type_u64:
      return !m_u64;
   case type_pu64:
      return !m_pu64 || !*m_pu64;
   // floating point
   case type_pfloat:
      return !*m_pf;
   case type_float:
      return !m_f;
   case type_pdouble:
      return !*m_pd;
   case type_double:
      return !m_d;
   // simple classes
   case type_string:
      return m_str.is_empty() || !m_str.compare_ci("false")  || !m_str.compare_ci("no");
   case type_pstring:
      return !m_pstr || m_pstr->is_empty() || !m_pstr->compare_ci("false")  || !m_pstr->compare_ci("no");
   case type_type:
      return m_str.is_empty();
   case type_duration:
      return m_duration.is_null();
   case type_pduration:
      return !m_pduration || m_pduration->is_null();
   case type_id:
      return m_id.is_empty() || !m_id.compare_ci("false") || !m_id.compare_ci("no");
   case type_pid:
      return !m_pid || m_pid->is_empty() || !m_pid->compare_ci("false") || !m_pid->compare_ci("no");
   case type_time:
      return !m_time;
   case type_filetime:
      return !m_filetime;
   case type_pvar:
      return m_pvar || !*m_pvar;
   case type_prop:
      return m_pprop || !*m_pprop;
   case type_routine:
      return !m_routine;
   case type_process:
      return !m_process;

      // matter classes
   case type_element:
      return is_element_null();
   case type_stra:
      return ::is_null(m_pstra) || m_pstra->isEmpty();
   case type_inta:
      return ::is_null(m_pia) || m_pia->isEmpty();
   case type_vara:
      return ::is_null(m_pvara) || m_pvara->isEmpty();
   case type_propset:
      return ::is_null(m_pset) || m_pset->isEmpty();
   case type_i64a:
      return ::is_null(m_pi64a) || m_pi64a->isEmpty();
   case type_memory:
      return ::is_null(m_pmemory) || m_pmemory->is_empty();
   case type_path:
      return ::is_null(m_ppath) || m_ppath->is_empty();
   //case type_image:
   //   return !::is_ok(m_pimage);

   // enum
   case type_secs:
      return !m_secs.m_iSeconds;
   case type_psecs:
      return !m_psecs || !m_psecs->m_iSeconds;
   case type_millis:
      return !m_millis.m_iMilliseconds;
   case type_pmillis:
      return !m_pmillis || !m_pmillis->m_iMilliseconds;
   case type_micros:
      return !m_micros.m_iMicroseconds;
   case type_pmicros:
      return !m_pmicros || !m_pmicros->m_iMicroseconds;
   case type_nanos:
      return !m_nanos.m_iNanoseconds;
   case type_pnanos:
      return !m_pnanos || !m_pnanos->m_iNanoseconds;
   case type_enum_command:
   case type_enum_status:
   case type_enum_check:
      return !m_i64;
   case __type_last_element:
         return false;

   }

   return !m_b;

}


bool payload::is_bool_false() const
{

   if (m_etype == type_pbool)
   {

      return !*m_pb;

   }
   else if (m_etype == type_bool)
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

      if(get_string().compare_ci(straParam[0]) == 0)
      {

         return;

      }
      else if(is_empty())
      {

         operator = (straParam[0]);

         return;

      }

   }

   stra().add_unique_ci(straParam);

}


payload & payload::operator = (const ::matter & o)
{

   set_element((::matter *) &o);

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
      rect                       m_rectRestored = nullptr;
      rect                       m_rectWindow = nullptr;
      int                        m_iControlBoxRightToLeft = 0;
      edisplay                   m_edisplay = e_display_default;
      edisplay                   m_edisplayPrevious = e_display_none;


   };


} // namespace user


void unit_test_primitive_var_acme_block_arg(payload payload)
{


}


void unit_test_primitive_var_acme_block()
{

   ::user::window_rect2 r2;

   payload var1(r2);

   payload var2;

   var2 = r2;

   debug_primitive_var_acme_block_arg(r2);

}


#endif //UNIT_TEST


payload::operator ::datetime::time() const
{

   return i64();

}




//::image * & payload::image()
//{
//
//   if (m_etype == ::type_pvar)
//   {
//
//      return m_pvar->image();
//
//   }
//   else if (m_etype != ::type_path)
//   {
//
//      auto ppath = __create < ::file::path_object >();
//
//      *ppath = get_file_path();
//
//      set_element(ppath);
//
//   }
//
//   return m_pimage;
//
//}


//payload::operator ::image * & ()
//{
//
//   return image();
//
//}








#define IMPL_VAR_ENUM(ENUMTYPE) \
::enum_ ## ENUMTYPE & payload::e ## ENUMTYPE()         \
{                                                  \
                                                   \
   if(m_etype == ::type_pvar)                      \
   {                                               \
                                                   \
      return m_pvar-> e ## ENUMTYPE ();            \
                                                   \
   }                                               \
   else if(m_etype == ::type_prop)                      \
   {                                               \
                                                   \
      return m_pprop-> e ## ENUMTYPE ();            \
                                                   \
   }                                               \
         \
   if(m_etype != ::type_enum_ ## ENUMTYPE)        \
   {                                               \
                                                   \
      m_etype = ::type_enum_ ## ENUMTYPE;              \
      xxf_zero(m_all);   \
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


::status::result payload::run()
{

   if (get_type() == type_pvar)
   {

      return m_pvar->run();

   }
   else if (get_type() == type_prop)
   {

      return m_pprop->run();

   }
   else if (get_type() == type_routine)
   {

      return m_routine();

   }
   else if (get_type() == type_vara)
   {

      ::status::result result;

      for (auto & varFunction : vara())
      {

         if (varFunction.get_type() == type_routine)
         {

            result.add(varFunction.m_routine());

         }

      }

      return result;

   }
   else
   {

      return error_wrong_type;

   }

}


void payload::receive_response(const ::payload & payload)
{

   if (get_type() == type_pvar)
   {

      m_pvar->receive_response(payload);

   }
   else if (get_type() == type_prop)
   {

      m_pprop->receive_response(payload);

   }
   else if (get_type() == type_process)
   {

      m_process(payload);

   }
   else if (get_type() == type_vara)
   {

      for (auto& varFunction : this->vara())
      {

         if (varFunction.get_type() == type_process)
         {
            
            varFunction.m_process(payload);

         }

      }

   }

}


payload& payload::operator = (const ::promise::routine & routine)
{

   set_type(type_routine);

   m_routine = routine;

   return *this;

}


payload& payload::operator = (const ::promise::process & process)
{

   set_type(type_process);

   m_process = process;

   return *this;

}



