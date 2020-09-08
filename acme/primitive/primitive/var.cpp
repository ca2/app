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

var::var(const char * psz)
{

   m_etype = type_new;

   set_string(psz);

}


var::var(::generic * pelement)
{

   m_etype = type_new;

   operator = (pelement);

}


var::var(const ::generic & generic)
{

   m_etype = type_new;

   operator = (generic);

}


var::var(const string & str)
{

   m_etype = type_new;

   set_string(str);

}


var::var(const type & type)
{

   m_etype = type_new;

   set_type(type);

}


var::var(string * pstr)
{

   m_etype = type_new;

   operator = (pstr);

}


var::var(bool b)
{

   m_etype = type_new;

   operator = (b);

}


var::var(bool * pb)
{

   m_etype = type_new;

   operator = (pb);

}


var::var(::i32 i)
{

   m_etype = type_new;

   operator = (i);

}


var::var(::u32 ui )
{

   m_etype = type_u32;

   operator = (ui);

}


var::var(::i64 i)
{

   m_etype = type_new;

   operator = (i);

}


var::var(::u64 ui )
{

   m_etype = type_u64;

   m_u64 = ui;

}


#ifdef __APPLE__
#ifdef OS64BIT

var::var(long l)
{

   m_etype = type_i64;
   m_i64 = (::i64) l;

}

#endif
#endif


var::var(::i32 * pi)
{

   m_etype = type_new;
   operator = (pi);

}


var::var(::u32 * pinteraction)
{

   m_etype = type_new;
   operator = (pinteraction);

}


var::var(::i64 * pi)
{

   m_etype = type_new;
   operator = (pi);

}


var::var(::u64 * pinteraction)
{

   m_etype = type_new;
   operator = (pinteraction);

}


var::var(float f)
{

   m_etype = type_new;
   operator = (f);

}


var::var(double d)
{

   m_etype = type_new;
   operator = (d);

}


var::var(const ::file::path & path)
{

   m_etype = type_new;
   operator = (path);

}


var::var(const string_array & var)
{

   m_etype  = type_new;
   operator = (var);

}


var::var(const int_array & ia)
{

   m_etype  = type_new;
   operator = (ia);

}


var::var(const var_array & var)
{

   m_etype  = type_new;
   operator = (var);

}


var::var(const property_set & set)
{

   m_etype  = type_new;
   operator = (set);

}


var::var(const class var & var)
{

   m_i64 = 0;
   m_etype = type_new;
   operator = (var);

}


var::var(class var * pvar)
{

   m_etype = type_new;
   operator = (pvar);

}


pack::pack(const ::std::initializer_list < pack >& list)
{

   for (auto& var : list)
   {

      if (var.get_type() == type_propset)
      {

         propset().merge(var.propset());

      }

   }


}

var::var(const class var * pvar)
{

   m_etype = type_new;
   operator = ( pvar);

}


var::var(const property & prop)
{

   m_etype = type_new;
   xxf_zero(m_all);
   operator = (prop);

}


var::var(const procedure & procedure)
{

    m_etype = type_new;
    xxf_zero(m_all);
    set_type(type_procedure);
    m_functionbase = procedure;

}


var::var(const ::callback & callback)
{

   m_etype = type_new;
   xxf_zero(m_all);
   set_type(type_callback);
   m_functionbase = callback;

}


var::var(property * pproperty)
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


var::var(const property * pproperty)
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


var::var(const id & id)
{

   m_etype = type_new;
   operator = (id);

}


var::var(const ::duration & duration)
{

   m_etype = type_duration;
   m_duration = duration;

}


var::var(::duration * pduration)
{

   m_etype = type_pduration;
   m_pduration = pduration;

}


var::var(const ::datetime::time & time)
{
   m_etype = type_time;
   m_time = time.m_time;
}


var::var(const FILETIME & filetime)
{
   m_etype = type_filetime;
   m_filetime = filetime;
}


var::var(const SYSTEMTIME & systemtime)
{
   m_etype = type_time;
   m_time = ::datetime::time(systemtime).m_time;
}


var::~var()
{

}


bool var::convert(const var& var)
{

   if (m_etype == var.m_etype)
   {

      memcpy(&m_all, &var.m_all, sizeof(m_all));

      m_str = var.m_str;

   }
   else if(m_etype == type_i8)
   {

      m_i8 = var;

   }
   else if(m_etype == type_enum_check)
   {

      m_echeck = (::enum_check)(::i32) var;

   }
   else if(m_etype == type_string)
   {

      m_str = var.get_string();

   }
   else
   {

      return false;

   }

   return true;

}


strsize var::get_length() const
{

   return get_string().get_length();

}


void var::get_string(char * psz) const
{

   strcpy(psz, get_string());

}


::e_type var::get_type() const
{

   return m_etype;

}


class var & var::operator ++(::i32)
{

   switch(get_type())
   {
   case type_new:
   case type_null:
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


void var::set_type(const ::type & type)
{

   set_type(type_type, false);

   m_str = type.m_strName;

}






bool var::get_type(::type & type) const
{

   if (m_etype != type_type)
   {

      return false;

   }

   type.m_strName = m_str;

   return true;

}


void var::set_type(e_type etype, bool bConvert)
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


void var::unset()
{
   set_type(type_new, false);
}


void var::unset(const string & strPropertySetKey)
{

   if (get_type() == type_propset)
   {

      propset().remove_by_name(strPropertySetKey);

   }

}


bool var::ok() const
{
   return get_type() != type_parareturn || ::is_return_ok(m_parareturn);
}

bool var::failed() const
{
   return get_type() == type_parareturn && !::is_return_ok(m_parareturn);
}


void var::set_id(const id & id)
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

class var & var::operator = (para_return & eret)
{
   set_type(type_parareturn, false);
   m_parareturn = eret;
   return *this;
}

class var & var::operator = (bool b)
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

class var & var::operator = (bool * pb)
{
   set_type(type_pbool, false);
   m_pb = pb;
   return *this;
}

class var & var::operator = (::i32 i)
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




class var & var::operator = (::i32 * pi)
{
   set_type(type_pi32, false);
   m_pi32 = pi;
   return *this;
}

class var & var::operator = (::u32 * pinteraction)
{
   set_type(type_pu32, false);
   m_pu32 = pinteraction;
   return *this;
}

class var & var::operator = (::i64 * pi)
{
   set_type(type_pi64, false);
   m_pi64 = pi;
   return *this;
}

class var & var::operator = (::u64 * pinteraction)
{
   set_type(type_pu64, false);
   m_pu64 = pinteraction;
   return *this;
}

class var & var::operator = (const ::datetime::time & time)
{
   set_type(type_time, false);
   m_time = time.get_time();
   return *this;
}

class var & var::operator = (const FILETIME & filetime)
{
   set_type(type_filetime, false);
   m_filetime = filetime;
   return *this;
}

class var & var::operator = (::i64 i)
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

class var & var::operator = (::u64 u)
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


class var & var::operator = (::u32 ui)
{
   set_type(type_u32, false);
   m_u32 = ui;
   return *this;
}

#if !defined(LINUX) && !defined(MACOS) && !defined(ANDROID) && !defined(APPLE_IOS)
class var & var::operator = (LONG l)
{
   set_type(type_i32,false);
   m_i32 = l;
   return *this;
}

class var & var::operator = (DWORD dw)
{
   set_type(type_u32,false);
   m_u32 = dw;
   return *this;
}

#endif


#if defined(__APPLE__)
   class var & var::operator = (long l)
   {
      set_type(type_i64,false);
      m_i64 = l;
      return *this;
   }
#endif

#if defined(ANDROID)
   class var & var::operator = (long l)
   {
      set_type(type_i32,false);
      m_i32 = l;
      return *this;
   }
#endif

class var & var::operator = (float f)
{
   set_type(type_float, false);
   m_f = f;
   return *this;
}

class var & var::operator = (double d)
{
   set_type(type_double, false);
   m_d = d;
   return *this;
}


//class var & var::operator = (enum_command ecommand)
//{
//   set_type(type_enum_command, false);
//   m_ecommand = ecommand;
//
//   return *this;
//
//}


class var & var::operator = (string * pstr)
{

   set_type(type_pstring, false);

   m_pstr = pstr;

   return *this;

}


class var & var::operator = (id * pid)
{
   set_type(type_pid, false);
   m_pid = pid;
   return *this;
}

//class var & var::operator = (const char * psz)
//{
//   set_string(psz);
//   return *this;
//}


class var & var::operator = (const widechar * pcsz)
{

   set_string(::str::international::unicode_to_utf8(pcsz));

   return *this;

}


class var & var::operator = (const property & prop)
{

   operator = ((const var &)prop);

   return *this;

}


class var & var::operator = (const property * pproperty)
{

   if (::is_null(pproperty))
   {

      set_type(type_null, false);

   }
   else
   {

      set_type(type_prop, false);

      m_pprop = (property *)pproperty;

   }

   return *this;

}


class var & var::operator = (const class var & var)
{
   if(m_etype == type_pvar)
   {
      if(m_pvar == &var)
         return *this;
      m_pvar->operator = (var);
      return *this;
   }
   if (m_etype == type_prop)
   {
      m_pprop->operator = (var);
      return *this;
   }
   if(&var != this)
   {
      switch(((class var &)var).get_type())
      {
      case type_pvar:
         // should dereference (this operator here means a content copy)
         *this  = *((class var &)var).m_pvar;
         return *this;
      case type_prop:
         // should dereference (this operator here means a content copy)
         *this = *((class property&)var).m_pprop;
         return *this;
      case type_pi32:
         // should dereference (this operator here means a content copy)
         *this  = *((class var &)var).m_pi32;
         return *this;
      case type_pstring:
         // should dereference (this operator here means a content copy)
         *this  = *((class var &)var).m_pstr;
         return *this;
      default:
         break;
      }

      set_type(var.get_type(), false);
      if (var.is_element())
      {

         m_p = var.m_p; // raw copy, doesn't care for the right member

      }
      else
      {
         switch (var.get_type())
         {
         case type_bool:
            m_b = var.m_b;
            break;
         case type_i8:
            m_i8 = var.m_i8;
            break;
         case type_u8:
            m_u8 = var.m_u8;
            break;
         case type_i16:
            m_i16 = var.m_i16;
            break;
         case type_u16:
            m_u16 = var.m_u16;
            break;
         case type_i32:
            m_i32 = var.m_i32;
            break;
         case type_u32:
            m_u32 = var.m_u32;
            break;
         case type_i64:
            m_i64 = var.m_i64;
            break;
         case type_u64:
            m_u64 = var.m_u64;
            break;
         case type_pi8:
            m_pi8 = var.m_pi8;
            break;
         case type_pu8:
            m_pu8 = var.m_pu8;
            break;
         case type_pi16:
            m_pi16 = var.m_pi16;
            break;
         case type_pu16:
            m_pu16 = var.m_pu16;
            break;
         case type_pi32:
            m_pi32 = var.m_pi32;
            break;
         case type_pu32:
            m_pu32 = var.m_pu32;
            break;
         case type_pi64:
            m_pi64 = var.m_pi64;
            break;
         case type_pu64:
            m_pu64 = var.m_pu64;
            break;
         case type_float:
            m_f = var.m_f;
            break;
         case type_double:
            m_d = var.m_d;
            break;
         case type_string:
            m_str = var.m_str;
            break;
         case type_prop:
            m_pprop=var.m_pprop;
            break;
         case type_id:
            m_id = var.m_id;
            break;
         default:
            memcpy(m_all, var.m_all, sizeof(m_all));
            m_str = var.m_str;
            break;
         }
      }
   }
   return *this;
}

class var & var::operator = (const int_array & ia)
{
   inta() = ia;
   return *this;
}


class var & var::operator = (const class memory & memoryParam)
{

   memory() = memoryParam;

   return *this;

}


class var & var::operator = (const string_array & straParam)
{
   stra() = straParam;
   return *this;
}

class var & var::operator = (const var_array & varaParam)
{
   vara() = varaParam;
   return *this;
}

class var & var::operator = (const property_set & propsetParam)
{
   propset() = propsetParam;
   return *this;
}

//class var & var::operator = (const pair_set_interface & propsetParam)
//{
//   propset() = propsetParam;
//   return *this;
//}
//
//class var & var::operator = (const str_str_interface & propsetParam)
//{
//   propset() = propsetParam;
//   return *this;
//}
//
//var & var::operator = (const string_composite & reference)
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

class var & var::operator = (const id & id)
{

   set_id(id);
   return *this;

}

/*var::operator id &()
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


var::operator string & ()
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


class var & var::operator = (const ::duration & duration)
{


   set_type(type_duration);

   m_duration = duration;

   return *this;

}


class var & var::operator = (::duration * pduration)
{


   set_type(type_pduration);

   m_pduration = pduration;

   return *this;

}


var & var::operator = (const block & block)
{

   set_element(__new(class ::memory(block)));

   return *this;

}


var::operator const char *() const
{

   return get_ref_string();

}


bool var::casts_to(::e_type etype) const
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


bool var::is_true(const ::var & var, bool bDefault) const
{

   if (var.get_type() == type_bool)
   {

      ASSERT(!bDefault);

      bool bDefault = var.m_b;

      if (is_element_set())
      {

         return true;

      }
      else
      {
         switch (m_etype)
         {
         case type_null:
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
         return m_pset->is_true(var, bDefault);
      case type_pvar:
         return m_pvar->is_true(var, bDefault);
      case type_prop:
         return m_pprop->is_true(var, bDefault);
      default:
         return bDefault;
      }

   }

}



bool var::is_empty() const
{

   switch(m_etype)
   {
   case type_null:
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


      // generic classes
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
   case type_image:
      return !::is_ok(m_pimage);

   default:
      return false;
   }
}


bool var::has_char() const
{

   return get_string().has_char();

}


bool var::is_set() const
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


bool var::is_new() const
{
   if(m_etype == type_new)
      return true;
   else
      return false;
}


bool var::is_null() const
{
   if(m_etype == type_null)
      return true;
   else
      return false;
}


bool var::is_new_or_null() const
{

   return is_new() || is_null();

}




::i32 var::compare_ci(const class var & var) const
{
   if(m_etype == ::type_inta)
   {
      if(var.m_etype == ::type_inta)
      {
         //var = var1.inta() - var2.inta();
      }
      else
      {
         //var = var1;
         //var.inta().remove(var2.i32());
      }
   }
   else if(m_etype == ::type_stra)
   {
      if(var.m_etype == ::type_stra)
      {
         //var = var1.stra() - var2.stra();
      }
      else
      {
         //var = var1;
         //var.stra().remove(var2.get_string());
      }
   }
   else if(m_etype == ::type_vara)
   {
      if(var.m_etype == ::type_vara)
      {
         //   var = var1.vara() - var2.vara();
      }
      else
      {
         // var = var1;
         //var.vara().remove(var2);
      }
   }
   else if(is_double() || var.is_double())
   {
      double d = get_double() - var.get_double();
      if(d == 0.0)
         return 0;
      else if(d > 0.0)
         return 1;
      else if(d < 0.0)
         return -1;
   }
   else if(is_integer() || var.is_integer())
   {
      return i32() - var.i32();
   }
   else if(is_natural() || var.is_natural())
   {
      return (::i32) (u32() - var.u32());
   }
   else
   {
      return get_string().compare_ci(var.get_string());
   }
   return -2;
}

::i32 var::compare_ci(const char * psz) const
{
   var var(psz);
   return compare_ci(var);
}


::i32 var::compare(const class var & var) const
{
   if(m_etype == ::type_inta)
   {
      if(var.m_etype == ::type_inta)
      {
         //var = var1.inta() - var2.inta();
      }
      else
      {
         //var = var1;
         //var.inta().remove(var2.i32());
      }
   }
   else if(m_etype == ::type_stra)
   {
      if(var.m_etype == ::type_stra)
      {
         //var = var1.stra() - var2.stra();
      }
      else
      {
         //var = var1;
         //var.stra().remove(var2.get_string());
      }
   }
   else if(m_etype == ::type_vara)
   {
      if(var.m_etype == ::type_vara)
      {
         //   var = var1.vara() - var2.vara();
      }
      else
      {
         // var = var1;
         //var.vara().remove(var2);
      }
   }
   else if(is_double() || var.is_double())
   {
      double d = get_double() - var.get_double();
      if(d == 0.0)
         return 0;
      else if(d > 0.0)
         return 1;
      else if(d < 0.0)
         return -1;
   }
   else if(is_integer() || var.is_integer())
   {
      return i32() - var.i32();
   }
   else if(is_natural() || var.is_natural())
   {
      return (::i32) (u32() - var.u32());
   }
   else
   {
      return get_string().compare(var.get_string());
   }
   return -2;
}

::i32 var::compare(const char * psz) const
{
   var var(psz);
   return compare(var);
}

bool var::operator == (const class var & var) const
{
   // if variables are equal:
   // all values of both variables should be equal
   return compare(var) == 0;
}

bool var::operator > (const class var & var) const
{
   return compare(var) > 0;
}

bool var::operator < (const class var & var) const
{
   return compare(var) < 0;
}

bool var::operator >= (const class var & var) const
{
   return compare(var) >= 0;
}

bool var::operator <= (const class var & var) const
{
   return compare(var) <= 0;
}

bool var::operator != (const class var & var) const
{
   return compare(var) != 0;
}

bool var::operator == (const char * psz) const
{
   return get_string() == psz;
}

bool var::operator < (const char * psz) const
{
   return get_string() < psz;
}

bool var::operator <= (const char * psz) const
{
   return get_string() <= psz;
}

bool var::operator >= (const char * psz) const
{
   return get_string() >= psz;
}

bool var::operator > (const char * psz) const
{
   return get_string() > psz;
}

bool var::operator != (const char * psz) const
{
   return get_string() != psz;
}

bool var::operator == (const string & str) const
{
   return get_string() == str;
}

bool var::operator != (const string & str) const
{
   return get_string() != str;
}

bool var::operator < (const string & str) const
{
   return get_string() < str;
}

bool var::operator <= (const string & str) const
{
   return get_string() <= str;
}

bool var::operator >= (const string & str) const
{
   return get_string() >= str;
}

bool var::operator > (const string & str) const
{
   return get_string() > str;
}

bool var::operator == (::i32 i) const
{
   return i32() == i;
}

bool var::operator != (::i32 i) const
{
   return i32() != i;
}

bool var::operator < (::i32 i) const
{
   return i64() < i;
}

bool var::operator <= (::i32 i) const
{
   return i64() <= i;
}

bool var::operator >= (::i32 i) const
{
   return i64() >= i;
}

bool var::operator > (::i32 i) const
{
   return i64() > i;
}











bool var::operator == (::i64 i) const
{
   return i64() == i;
}

bool var::operator != (::i64 i) const
{
   return i64() != i;
}

bool var::operator < (::i64 i) const
{
   return i64() < i;
}

bool var::operator <= (::i64 i) const
{
   return i64() <= i;
}

bool var::operator >= (::i64 i) const
{
   return i64() >= i;
}

bool var::operator > (::i64 i) const
{
   return i32() > i;
}


























bool var::operator == (bool b) const
{
   return is_equivalent(get_bool(), b);
}

bool var::operator != (bool b) const
{
   return is_different(get_bool(), b);
}

bool var::operator < (bool b) const
{
   return is_lesser(get_bool(), b);
}

bool var::operator <= (bool b) const
{
   return is_lesser_or_equal(get_bool(), b);
}

bool var::operator >= (bool b) const
{
   return is_greater_or_equal(get_bool(), b);
}

bool var::operator > (bool b) const
{
   return is_greater(get_bool(), b);
}

bool var::strict_equal(const class var & var) const
{
   return m_etype == var.m_etype && operator == (var);
}

bool var::strict_equal(const char * psz) const
{
   return m_etype == type_string && m_str == psz;
}

bool var::strict_equal(const string & str) const
{
   return m_etype == type_string && m_str == str;
}

bool var::strict_equal(double d) const
{
   return m_etype == type_double && m_d == d;
}

bool var::strict_equal(::i32 i) const
{
   return m_etype == type_i32 && m_i32 == i;
}

bool var::strict_equal(bool b) const
{
   return m_etype == type_bool && is_equivalent(m_b, b);
}

bool var::strict_different(const class var & var) const
{
   return m_etype != var.m_etype || operator != (var);
}

bool var::strict_different(const char * psz) const
{
   return m_etype != type_string || m_str != psz;
}

bool var::strict_different(const string & str) const
{
   return m_etype != type_string || m_str != str;
}

bool var::strict_different(double d) const
{
   return m_etype != type_double || m_d != d;
}

bool var::strict_different(::i32 i) const
{
   return m_etype != type_i32 || m_i32 != i;
}

bool var::strict_different(bool b) const
{
   return m_etype != type_bool || is_different(m_b, b);
}

bool strict_equal(const char * psz, const class var & var)
{
   return var.m_etype == ::type_string && psz == var.m_str;
}

bool strict_equal(const string & str, const class var & var)
{
   return var.m_etype == ::type_string && str == var.m_str;
}

bool strict_equal(double d, const class var & var)
{
   return var.m_etype == ::type_double && d == var.m_d;
}

bool strict_equal(::i32 i, const class var & var)
{
   return var.m_etype == ::type_i32 && i == var.m_i32;
}

bool strict_equal(bool b, const class var & var)
{
   return var.m_etype == ::type_bool && is_equivalent(b, var.m_b);
}

bool strict_different(const char * psz, const class var & var)
{
   return var.m_etype != ::type_string || psz != var.m_str;
}

bool strict_different(const string & str, const class var & var)
{
   return var.m_etype != ::type_string || str != var.m_str;
}

bool strict_different(double d, const class var & var)
{
   return var.m_etype != ::type_double || d != var.m_d;
}

bool strict_different(::i32 i, const class var & var)
{
   return var.m_etype != ::type_i32 || i != var.m_i32;
}

bool strict_different(bool b, const class var & var)
{
   return var.m_etype != ::type_bool || is_different(b, var.m_b);
}

string var::to_r_string() const
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

string var::get_string(const char * pszOnNull) const
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

      if(m_etype == ::type_null)
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
         
         str = __str(*element());

      }

      return str;

   }
   else
   {
      return m_str;
   }

}

string & var::get_ref_string(const char * pszOnNull)
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

const string & var::get_ref_string(const char * pszOnNull) const
{

   return ((var *)this)->get_ref_string(pszOnNull);

}


id var::get_id(const char * pszOnNull) const
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

      if(m_etype == ::type_null)
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



id & var::get_ref_id(const char * pszOnNull)
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



::i32 var::i32(::i32 iDefault) const
{
   switch(m_etype)
   {
   case type_null:
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
         __throw(overflow_error("var contains id that does not fit 32 bit integer"));
      return (::i32) (::i64) m_id;
   }
   case type_pid:
   {
      if(!is_i32((::i64) *m_pid))
         __throw(overflow_error("var contains id that does not fit 32 bit integer"));
      return (::i32) (::i64) *m_pid;
   }
   default:
      return iDefault;
   }
}

::u32 var::u32(::u32 uiDefault) const
{
   switch(m_etype)
   {
   case type_null:
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

::i64 var::i64(::i64 iDefault) const
{

   try
   {

      switch (m_etype)
      {
      case type_null:
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


::u64 var::u64(::u64 uiDefault) const
{
   switch(m_etype)
   {
   case type_null:
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


procedure var::get_procedure() const
{

   if (get_type() != ::type_procedure)
   {

      return procedure();

   }

   return m_functionbase;


}


callback var::get_callback() const
{

   if (get_type() != ::type_callback)
   {

      return callback();

   }

   return m_functionbase;

}


float var::get_float(float fDefault) const
{
   switch(m_etype)
   {
   case type_null:
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


image * var::image() const
{

   if (m_etype != ::type_element)
   {

      return nullptr;

   }

   return cast < ::image >();

}


double var::get_double(double dDefault) const
{
   double d;
   if(m_etype == type_null)
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


class ::memory & var::memory()
{

   if(get_type() != type_memory)
   {

      set_element(create_memory());

   }

   return *m_pmemory;

}


::memory var::memory() const
{

   if (m_etype != type_memory)
   {

      return memory();

   }

   return *m_pmemory;

}


var::operator ::file::path & ()
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


var::operator ::file::path() const
{

   return get_file_path();

}


string_array & var::stra()
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


int_array & var::inta()
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


i64_array & var::int64a()
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


duration & var::duration()
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


const string_array & var::stra() const
{

   return ((var *)this)->stra();

}


const int_array & var::inta() const
{

   return ((var *)this)->inta();

}


const i64_array & var::int64a() const
{

   return ((var *)this)->int64a();

}


class var & var::operator = (var * pvar)
{

   if (m_pvar == pvar)
   {

      return *this;

   }

   set_type(type_pvar, false);

   m_pvar = pvar;

   return *this;

}


class var & var::operator = (const var * pvar)
{

   return operator =((var*)pvar);

}


var_array & var::vara()
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


property_set & var::propset()
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


const var_array & var::vara() const
{

   return ((var *)this)->vara();

}


const ::duration & var::duration() const
{

   return ((var *)this)->duration();

}


const property_set & var::propset() const
{

   return ((var *)this)->propset();

}


property & var::prop()
{

   if(m_etype != type_prop)
   {

      __throw(exception::exception("var is not a property (1)"));

   }

   return *m_pprop;

}


const property & var::prop() const
{

   return ((var *)this)->prop();

}


string var::implode(const char * pszGlue) const
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


var var::explode(const char * pszGlue, bool bAddEmpty) const
{

   class var var;

   var.stra().add_tokens(get_string(), pszGlue, bAddEmpty);

   return var;

}




::comparison::var_strict var::strict_compare() const
{

   return *this;

}


var var::dereference()
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


//var var::at(index i) const
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
//         return (var *) this;
//      }
//      else
//      {
//         __throw(::exception::exception("index out of bounds"));
//      }
//   }
//}


var var::at(index i)
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

bool var::array_contains(const char * psz, index find, ::count count) const
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
      index upperbound = MIN(array_get_upper_bound(), find + count - 1);
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

bool var::array_contains_ci(const char * psz, index find, index last) const
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
      index upperbound = MIN(array_get_upper_bound(), last);
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


var var::equals_ci_get(const char * pszCompare, var varOnEqual, var varOnDifferent) const
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

var var::equals_ci_get(const char * pszCompare, var varOnEqual) const
{
   if(compare_ci(pszCompare) == 0)
   {
      return varOnEqual;
   }
   else
   {
      return var();
   }
}


var var::operator - (::i32 i) const
{
   return i32() - i;
}

var var::operator - (::u32 user) const
{
   return u32() - user;
}

var var::operator - (::i64 l) const
{
   return i64() - l;
}

var var::operator - (::u64 ul) const
{
   return (::i64) (u64() - ul);
}

var var::operator - (double d) const
{
   return get_double() - d;
}

var operator - (::i32 i, const class var & var)
{
   return i - var.i32();
}

var operator - (::u32 user, const class var & var)
{
   return user - var.u32();
}

var operator - (::i64 l, const class var & var)
{
   return l - var.i64();
}

var operator - (::u64 ul, const class var & var)
{
   return (::i64) (ul - var.u64());
}

var operator - (double d, const class var & var)
{
   return d - var.get_double();
}

var operator - (const class var & var1, const class var & var2)
{
   var var;
   if(var1.m_etype == ::type_inta)
   {
      if(var2.m_etype == ::type_inta)
      {
         var = var1.inta() - var2.inta();
      }
      else
      {
         var = var1;
         var.inta().remove(var2.i32());
      }
   }
   else if(var1.m_etype == ::type_stra)
   {
      if(var2.m_etype == ::type_stra)
      {
         var = var1.stra() - var2.stra();
      }
      else if(var2.is_array())
      {
         var = var1.stra() - const_cast < class var & > (var2).stra();
      }
      else
      {
         var = var1;
         var.stra().remove(var2.get_string());
      }
   }
   else if(var1.m_etype == ::type_vara)
   {
      if(var2.m_etype == ::type_vara)
      {
         var = var1.vara() - var2.vara();
      }
      else
      {
         var = var1;
         var.vara().remove(var2);
      }
   }
   else if(var1.is_double() || var2.is_double())
   {
      var = var1.get_double() - var2.get_double();
   }
   else if(var1.is_integer() || var2.is_integer())
   {
      var = var1.i32() - var2.i32();
   }
   else if(var1.is_natural() || var2.is_natural())
   {
      var = var1.u32() - var2.u32();
   }
   else
   {
      var = atoi(var1.get_string()) - atoi(var2.get_string());
   }
   return var;
}


var var::operator + (::i32 i) const
{
   return i32() + i;
}

var var::operator + (::u32 user) const
{
   return u32() + user;
}

var var::operator + (::i64 l) const
{
   return i64() + l;
}

var var::operator + (::u64 ul) const
{
   return (::u32) (u64() + ul);
}

var var::operator + (const string & str) const
{

   var varRet(*this);

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

var var::operator + (double d) const
{
   return get_double() + d;
}

var operator + (::i32 i, const class var & var)
{
   return i + var.i32();
}

var operator + (::u32 user, const class var & var)
{
   return user + var.u32();
}

var operator + (::i64 l, const class var & var)
{
   return l + var.i64();
}

var operator + (::u64 ul, const class var & var)
{
   return (::u32) (ul + var.u64());
}

var operator + (double d, const class var & var)
{
   return d + var.get_double();
}

var operator + (const class var & var1, const class var & var2)
{
   var var;
   if(var1.m_etype == ::type_inta
         || var1.m_etype == ::type_inta)
   {
      if(var1.m_etype == ::type_inta)
      {
         if(var2.m_etype == ::type_inta)
         {
            var = var1.inta() + var2.inta();
         }
         else
         {
            var = var1;
            var.inta().add(var2.i32());
         }
      }
      else
      {
         var = var2;
         var.inta().add(var1.i32());
      }
   }
   else if(var1.m_etype == ::type_stra
           || var2.m_etype == ::type_stra)
   {
      if(var1.m_etype == ::type_stra)
      {
         if(var2.m_etype == ::type_stra)
         {
            var = var1.stra() + var2.stra();
         }
         else
         {
            var = var1;
            var.stra().add(var2.get_string());
         }
      }
      else
      {
         var = var2;
         var.stra().add(var1.get_string());
      }
   }
   else if(var1.m_etype == ::type_vara
           || var2.m_etype == ::type_vara)
   {
      if(var2.m_etype == ::type_vara)
      {
         if(var2.m_etype == ::type_vara)
         {
            var = var1.vara() + var2.vara();
         }
         else
         {
            var = var1;
            var.vara().add(var2);
         }
      }
      else
      {
         var = var2;
         var.vara().add(var1);
      }
   }
   else if(var1.is_double() && var2.is_double())
   {
      var = var1.get_double() + var2.get_double();
   }
   else if(var1.is_integer() && var2.is_integer())
   {
      var = var1.i32() + var2.i32();
   }
   else if(var1.is_natural() && var2.is_natural())
   {
      var = var1.u32() + var2.u32();
   }
   else
   {
      var = var1.get_string() + var2.get_string();
   }
   return var;
}






















var var::operator / (::i32 i) const
{
   return i32() / i;
}

var var::operator / (::u32 user) const
{
   return u32() / user;
}

var var::operator / (::i64 l) const
{
   return i64() / l;
}

var var::operator / (::u64 ul) const
{

   switch(m_etype)
   {
   case ::type_null:
      return var(type_null);
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

var var::operator / (double d) const
{
   return get_double() / d;
}

var operator / (::i32 i, const class var & var)
{
   return i / var.i32();
}

var operator / (::u32 user, const class var & var)
{
   return user / var.u32();
}

var operator / (::i64 l, const class var & var)
{
   return l / var.i64();
}


var operator / (::u64 ul, const class var & var)
{
   switch(var.m_etype)
   {
   case ::type_null:
      __throw(::exception::exception("division by zero"));
   case ::type_empty:
      __throw(::exception::exception("division by zero"));
   case ::type_i32:
      return (iptr) ul / var.m_i32;
   case ::type_u32:
      return (uptr) ul / var.m_u32;
   case ::type_i64:
      return (::i64) ul / var.m_i64;
   case ::type_u64:
      return (::u64) ul / var.m_u64;
   case ::type_float:
      return (float) ul / var.m_f;
   case ::type_double:
      return (double) ul / var.m_d;
   case ::type_string:
#if defined(LINUX) || defined(ANDROID)
      return (double) ul / atof(var.m_str);
#else
      return (double) ul / _atof_l(var.m_str, ::acme::g_localeC);
#endif
   case ::type_pvar:
      return operator / (ul, *var.m_pvar);
   case ::type_prop:
      return operator / (ul, *var.m_pprop);
   default:
      __throw(::exception::exception("division by zero"));
   }

}




var operator / (double d, const class var & var)
{
   return d / var.get_double();
}

var operator / (const class var & var1, const class var & var2)
{
   var var;
   if(var1.m_etype == ::type_inta)
   {
      if(var2.m_etype == ::type_inta)
      {
         var = var1;
         var.inta().intersect(var2.inta());
      }
      else
      {
         var = var1;
         var.inta().divide(var2.i32());
      }
   }
   else if(var1.m_etype == ::type_stra)
   {
      if(var2.m_etype == ::type_stra)
      {
         //var = var1.stra().intersect(var2.stra());
      }
      else
      {
         var = var1;
         var.stra().remove(var2.get_string());
      }
   }
   else if(var1.m_etype == ::type_vara)
   {
      if(var2.m_etype == ::type_vara)
      {
         //var = var1.vara() / var2.vara();
      }
      else
      {
         var = var1;
         var.vara().remove(var2);
      }
   }
   else if(var1.is_double() || var2.is_double())
   {
      var = var1.get_double() / var2.get_double();
   }
   else if(var1.is_integer() || var2.is_integer())
   {
      var = var1.i32() / var2.i32();
   }
   else if(var1.is_natural() || var2.is_natural())
   {
      var = var1.u32() / var2.u32();
   }
   else
   {
      var = atoi(var1.get_string()) / atoi(var2.get_string());
   }
   return var;
}


var var::operator * (::i32 i) const
{
   return i32() * i;
}

var var::operator * (::u32 user) const
{
   return u32() * user;
}

var var::operator * (::i64 l) const
{
   return i64() * l;
}

var var::operator * (::u64 ul) const
{
   switch(m_etype)
   {
   case ::type_null:
      return var(type_null);
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

var var::operator * (double d) const
{
   return get_double() * d;
}

var operator * (::i32 i, const class var & var)
{
   return i * var.i32();
}

var operator * (::u32 user, const class var & var)
{
   return user * var.u32();
}

var operator * (::i64 l, const class var & var)
{
   return l * var.i64();
}

var operator * (::u64 ul, const class var & var)
{

   switch(var.m_etype)
   {
   case ::type_null:
      return ::var(::type_null);
   case ::type_empty:
      return 0;
   case ::type_i32:
      return (iptr) ul * var.m_i32;
   case ::type_u32:
      return (uptr) ul * var.m_u32;
   case ::type_i64:
      return (::i64) ul * var.m_i64;
   case ::type_u64:
      return (::u64) ul * var.m_u64;
   case ::type_float:
      return (float) ul * var.m_f;
   case ::type_double:
      return (double) ul * var.m_d;
   case ::type_string:
#if defined(LINUX) || defined(ANDROID)
      return (double) ul * atof(var.m_str);
#else
      return (double) ul * _atof_l(var.m_str, ::acme::g_localeC);
#endif
   case ::type_pvar:
      return operator * (ul, *var.m_pvar);
   case ::type_prop:
      return operator * (ul, *var.m_pprop);
   default:
      return 0;
   }

}


var operator * (double d, const class var & var)
{
   return d * var.get_double();
}

var operator * (const class var & var1, const class var & var2)
{

   var var;

   if(var1.m_etype == ::type_inta || var1.m_etype == ::type_inta)
   {

      ::papaya::array::intersection(var.inta(), var1.inta(), var2.inta());

   }
   else if(var1.m_etype == ::type_stra || var2.m_etype == ::type_stra)
   {

      ::papaya::array::intersection(var.stra(), var1.stra(), var2.stra());

   }
   else if(var1.m_etype == ::type_vara || var2.m_etype == ::type_vara)
   {

      ::papaya::array::intersection(var.vara(), var1.vara(), var2.vara());

   }
   else if(var1.is_double() || var2.is_double())
   {

      var = var1.get_double() * var2.get_double();

   }
   else if(var1.is_integer() || var2.is_integer())
   {

      var = var1.i32() * var2.i32();

   }
   else if(var1.is_natural() || var2.is_natural())
   {

      var = var1.u32() * var2.u32();

   }
   else
   {

      var = var1.to_string().intersection(var2.to_string());

   }

   return var;

}

























class var & var::operator -= (::i32 i)
{
   operator =(*this - i);
   return *this;
}

class var & var::operator -= (::u32 user)
{
   operator =(*this - user);
   return *this;
}

class var & var::operator -= (::i64 i)
{
   operator =(*this - i);
   return *this;
}

class var & var::operator -= (::u64 user)
{
   operator =(*this - user);
   return *this;
}

class var & var::operator -= (double d)
{
   operator =(*this - d);
   return *this;
}

class var & var::operator -= (const class var & var)
{
   operator =(*this - var);
   return *this;
}
























class var & var::operator += (::i32 i)
{
   operator =(*this + i);
   return *this;
}

class var & var::operator += (::u32 user)
{
   operator =(*this + user);
   return *this;
}

class var & var::operator += (::i64 i)
{
   operator =(*this + i);
   return *this;
}

class var & var::operator += (::u64 user)
{
   operator =(*this + user);
   return *this;
}

class var & var::operator += (double d)
{
   operator =(*this + d);
   return *this;
}

class var & var::operator += (const class var & var)
{
   operator =(*this + var);
   return *this;
}
























class var & var::operator /= (::i32 i)
{
   operator =(*this / i);
   return *this;
}

class var & var::operator /= (::u32 user)
{
   operator =(*this / user);
   return *this;
}

class var & var::operator /= (::i64 i)
{
   operator =(*this / i);
   return *this;
}

class var & var::operator /= (::u64 user)
{
   operator =(*this / user);
   return *this;
}

class var & var::operator /= (double d)
{
   operator =(*this / d);
   return *this;
}

class var & var::operator /= (const class var & var)
{
   operator =(*this / var);
   return *this;
}
























class var & var::operator *= (::i32 i)
{
   operator =(*this * i);
   return *this;
}

class var & var::operator *= (::u32 user)
{
   operator =(*this * user);
   return *this;
}

class var & var::operator *= (::i64 i)
{
   operator =(*this * i);
   return *this;
}

class var & var::operator *= (::u64 user)
{
   operator =(*this * user);
   return *this;
}

class var & var::operator *= (double d)
{
   operator =(*this * d);
   return *this;
}


class var & var::operator *= (const class var & var)
{

   operator =(*this * var);

   return *this;

}


























bool var::is_scalar() const
{
   if(m_etype == type_new
         || m_etype == type_null
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

bool var::is_real() const
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


bool var::is_boolean() const
{
   if (m_etype == type_double)
   {
      return true;
   }
   return false;
}

bool var::is_double() const
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

bool var::is_integer() const
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

bool var::is_natural() const
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

var::operator bool() const
{

   if (m_etype == type_enum_status)
   {

      return ::succeeded(m_estatus);

   }
   else if (m_etype == type_new
         || m_etype == type_null
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


bool var::is_property_true(const ::id & id) const
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


bool var::is_property_false(const ::id & id) const
{

   return !is_property_true(id);

}

var::operator block () const
{

   return ((var *)this)->operator block ();

}

var::operator block ()
{

   if (get_type() != type_memory)
   {

      __throw(exception::exception(error_wrong_type));

   }

   return *m_pmemory;

}



var var::get_topic(const ::id & id) const
{

   auto pproperty = find_property(id);

   if(!pproperty)
   {

      return *this;

   }

   return *pproperty;

}


//var var::defer_get(const ::id & id) const
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


//property * var::defer_get_property(const ::id & id) const
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


bool var::has_property(const ::id & id) const
{

   return __found(property_index(id));

}


void var::consume_identifier(const char * & psz)
{

   consume_number(psz, psz + strlen(psz) - 1);

}


void var::consume_identifier(const char * & psz, const char * pszEnd)
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
      set_type(::type_null);
   }
   else
   {
      throw_parsing_exception("not expected identifier");
   }
   psz = pszParse;
}

void var::consume_number(const char * & psz)
{
   consume_number(psz, psz + strlen(psz) - 1);
}

void var::consume_number(const char * & psz, const char * pszEnd)
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



void var::parse_json(const char * & pszJson)
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




const char * var::parse_json(const string & strJson)
{

   const char * pszJson = strJson;

   parse_json(pszJson, pszJson + strJson.get_length());

   return pszJson;

}

void var::parse_json(const char *& pszJson, const char * pszEnd)
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

::e_type var::find_json_child(const char *& pszJson, const char * pszEnd, const var & varChild)
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
      ::e_type etype = find_json_id(pszJson, pszEnd, varChild);
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


::e_type var::find_json_id(const char * & pszJson, const char * pszEnd, const var & varChild)
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


bool var::is_numeric() const
{

   switch(get_type())
   {
   case type_parareturn:
   case type_new:
   case type_null:
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
   case type_procedure:
      return false;
   case type_callback:
      return false;
   default:
      __throw(not_implemented());

   };

}



bool is_return_ok(para_return eret)
{
   return ((::i32)eret) >= 0;
}


var str_ends_get(const char * pcsz, const char * pcszSuffix)
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


string var::get_json(bool bNewLine) const
{

   string str;

   return get_json(str, bNewLine);

}


string & var::get_json(string & str, bool bNewLine) const
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



void var::null()
{

   set_type(::type_null);

}




::file::path var::get_file_path() const
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

         path |= ::file::flag_required;

      }

      if (propset().is_true("nocache"))
      {

         path |= ::file::flag_bypass_cache;

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


var & var::operator |= (cflag < ::file::e_flag > eflag)
{

   auto pfile = cast < ::file::file > ();

   if (pfile)
   {

      propset()["file"] = pfile;

   }


   if (m_etype == type_propset)
   {

      if (eflag & ::file::flag_required)
      {

         propset()["required"] = true;

      }

      if (eflag & ::file::flag_bypass_cache)
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


bool var::is_false() const
{

   switch(m_etype)
   {

   /// special meaning
   case type_parareturn:
   case type_new:
   case type_null:
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
      return !m_filetime.dwLowDateTime && ! m_filetime.dwHighDateTime;
   case type_pvar:
      return m_pvar || !*m_pvar;
   case type_prop:
      return m_pprop || !*m_pprop;
   case type_procedure:
         return ::is_null(m_functionbase.m_pobjectTask);
   case type_callback:
         return ::is_null(m_functionbase.m_pobjectTask);

   // generic classes
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
   case type_image:
      return !::is_ok(m_pimage);

   // enum
   case type_enum_command:
   case type_enum_status:
   case type_enum_check:
      return !m_i64;
   case __type_last_element:
         return false;

   }

   return !m_b;

}


bool var::is_set_false() const
{

   switch(m_etype)
   {
   /// special meaning
   case type_parareturn:
   case type_new:
   case type_null:
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
      return !m_filetime.dwLowDateTime && ! m_filetime.dwHighDateTime;
   case type_pvar:
      return m_pvar || !*m_pvar;
   case type_prop:
      return m_pprop || !*m_pprop;
   case type_procedure:
      return ::is_null(m_functionbase.m_pobjectTask);
   case type_callback:
      return ::is_null(m_functionbase.m_pobjectTask);

      // generic classes
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
   case type_image:
      return !::is_ok(m_pimage);

   // enum
   case type_enum_command:
   case type_enum_status:
   case type_enum_check:
      return !m_i64;
   case __type_last_element:
         return false;

   }

   return !m_b;

}


bool var::is_bool_false() const
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
// no change if source string array stream empty
// and avoid duplicate
void var::_001Add(const string_array & straParam)
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


var & var::operator = (const ::generic & o)
{

   set_element((::generic *) &o);

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
      edisplay                   m_edisplay = display_default;
      edisplay                   m_edisplayPrevious = display_none;


   };


} // namespace user


void unit_test_primitive_var_aura_block_arg(var var)
{


}


void unit_test_primitive_var_aura_block()
{

   ::user::window_rect2 r2;

   var var1(r2);

   var var2;

   var2 = r2;

   debug_primitive_var_aura_block_arg(r2);

}


#endif //UNIT_TEST


var::operator ::datetime::time() const
{

   return i64();

}




::image * & var::image()
{

   if (m_etype == ::type_pvar)
   {

      return m_pvar->image();

   }
   else if (m_etype != ::type_path)
   {

      auto ppath = __create < ::file::path_object >();

      *ppath = get_file_path();

      set_element(ppath);

   }

   return m_pimage;

}


var::operator ::image * & ()
{

   return image();

}








#define IMPL_VAR_ENUM(ENUMTYPE) \
::enum_ ## ENUMTYPE & var::e ## ENUMTYPE()         \
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


::status::result var::run()
{

   if (get_type() == type_pvar)
   {

      return m_pvar->run();

   }
   else if (get_type() == type_prop)
   {

      return m_pprop->run();

   }
   else if (get_type() == type_procedure)
   {

      return get_procedure().call();

   }
   else if (get_type() == type_vara)
   {

      ::status::result result;

      for (auto & varFunction : vara())
      {

         if (varFunction.get_type() == type_procedure)
         {

            result.add(varFunction.get_procedure().call());

         }

      }

      return result;

   }
   else
   {

      return error_wrong_type;

   }

}


void var::receive_response(const ::var & var)
{

   if (get_type() == type_pvar)
   {

      m_pvar->receive_response(var);

   }
   else if (get_type() == type_prop)
   {

      m_pprop->receive_response(var);

   }
   else if (get_type() == type_callback)
   {

      get_callback().receive_response(var);

   }
   else if (get_type() == type_vara)
   {

      for (auto& varFunction : this->vara())
      {

         if (varFunction.get_type() == type_callback)
         {
            
            varFunction.get_callback().receive_response(var);

         }

      }

   }

}




var& var::operator = (const ::procedure & procedure)
{

   set_type(type_procedure);

   m_functionbase = procedure;

   return *this;

}

 var& var::operator = (const ::callback & callback)
{

   set_type(type_callback);

   m_functionbase = callback;

   return *this;

}



