#include "framework.h"
//#include "acme/prototype/string/get_string.h"
#include "payload.h"
#include "acme/exception/parsing.h"
#include "acme/filesystem/file/file.h"
#include "acme/parallelization/task.h"
//#include "acme/platform/acme.h"
#include "acme/platform/locale.h"
#include "acme/platform/system.h"
#include "acme/prototype/datetime/system_time.h"
#include "acme/prototype/datetime/earth_gregorian_time.h"
////#include "acme/prototype/datetime/earth_time.h"
#include "acme/prototype/collection/string_array.h"
#include "acme/prototype/prototype/memory.h"
//#include "acme/prototype/string/_conv.h"
#include "acme/prototype/string/from_integer.h"
#include "acme/prototype/string/international.h"
#include "acme/prototype/string/network_payload.h"
#include "acme/prototype/string/str.h"
#include "acme/exception/not_implemented.h"
//#include "acme/array.h"
#include "acme/_operating_system.h"


#include "acme/prototype/collection/_container.h"


CLASS_DECL_ACME void copy(::string & str, const ::payload & payload)
{

   str = payload.as_string();

}


CLASS_DECL_ACME void copy(::payload & payload, const int & i)
{

   payload = i;

}


CLASS_DECL_ACME  void copy(::payload & payload, const ::scoped_string & scopedstr)
{

   payload = scopedstr;

}


//void copy(payload * pp, const system_time * ps)
//{
//   ::earth::gregorian_time t;
//   t.set(ps);
//   ::earth::time time;
//   time = t;
//
//   *pp = time;
//}

//
//void copy(::payload * ppayload, const string * pstring)
//{
//
//   *ppayload = *pstring;
//
//}
//
//
//void copy(::payload * ppayload1, const ::payload * ppayload2)
//{
//
//   *ppayload1 = *ppayload2;
//
//}



#if defined(WINDOWS)
//extern _locale_t ::get_task()->locale()->m_locale;
#else
#if defined(__APPLE__)
#include <xlocale.h>
#define _atof_l atof_l
#endif
//extern locale_t ::get_task()->locale()->m_locale;
#endif


payload::payload() :
   m_etype(e_type_new)
#if REFERENCING_DEBUGGING
   ,m_preferer(nullptr)
#endif
{

}


payload::payload(enum_type etype) :
   m_etype(e_type_new)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
{

   set_type(etype, false);

}


//payload::payload(const ::e_status & estatus)
//{
//
//   set_type(type_enum_status);
//
//   m_estatus = estatus;
//
//}


//payload::payload(enum_command ecommand)
//{
//
//   set_type(type_enum_command);
//
//   m_ecommand = ecommand;
//
//}


//payload::payload(enum_check echeck)
//{
//
//   set_type(type_enum_check);
//
//   m_echeck = echeck;
//
//}


payload::payload(nullptr_t) :
   m_etype(e_type_null)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
{

}



//payload::payload(const ::scoped_string & scopedstr)
//{
//
//   m_etype = e_type_new;
//
//   set_string(scopedstr);
//
//}


payload::payload(::subparticle * pelement) :
   m_etype(e_type_new)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
{

#if REFERENCING_DEBUGGING

   //m_preferer = ::allocator::defer_push_referer(pelement, { pelement, this, __FUNCTION_FILE_LINE__ });

   if(pelement->is_referencing_debugging_enabled())
   {

      m_preferer = ::allocator::defer_push_referer(pelement, { this, __FUNCTION_FILE_LINE__ });

   }

#endif

   operator = ((::subparticle *) pelement);

}


payload::payload(const ::subparticle & particle) :
   m_etype(e_type_new)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
{

   operator = (particle);

}




payload::payload(const_char_pointer start, const_char_pointer end) :
m_etype(e_type_new)
#if REFERENCING_DEBUGGING
, m_preferer(nullptr)
#endif
,m_str{ start, end }
{
}


payload::payload(const_char_pointer psz) :
   m_etype(e_type_string)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
   ,m_str(psz)
{

}

payload::payload(const ::scoped_string & scopedstr) :
   m_etype(e_type_string)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
   ,m_str(scopedstr)
{


}


payload::payload(const type_atom & typeatom):
   m_etype(e_type_atom)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
   ,m_atomPayload(typeatom)
{


}


payload::payload(::string * pstr) :
   m_etype(e_type_pstring)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
   ,m_pstr(pstr)
{

}


//payload::payload(bool b)
//{
//
//   m_etype = e_type_new;
//
//   operator = (b);
//
//}


payload::payload(bool * pb) :
   m_etype(e_type_pbool)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
   ,m_pb(pb)
{

}


//payload::payload(int i)
//{
//
//   m_etype = e_type_new;
//
//   operator = (i);
//
//}
//
//
//payload::payload(unsigned int u )
//{
//
//   m_etype = e_type_unsigned_int;
//
//   operator = (u);
//
//}
//
//
//payload::payload(long long i)
//{
//
//   m_etype = e_type_new;
//
//   operator = (i);
//
//}
//
//
//payload::payload(unsigned long long u )
//{
//
//   m_etype = e_type_unsigned_long_long;
//
//   m_hn = u;
//
//}


#ifdef __APPLE__
#ifdef OS64BIT

payload::payload(long l)
#if REFERENCING_DEBUGGING
: m_preferer(nullptr)
#endif
{

   m_etype = e_type_long_long;
   m_hi = (long long) l;

}

#endif
#endif


payload::payload(int * pi) :
   m_etype(e_type_pint)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
   ,m_pi(pi)
{

}



payload::payload(float* pf) :
   m_etype(e_type_pfloat)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
   , m_pf(pf)
{

}

payload::payload(unsigned int * pu) :
   m_etype(e_type_punsigned_int)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
   ,m_pui(pu)
{

}


payload::payload(long long * pll):
   m_etype(e_type_plong_long)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
   ,m_pll(pll)
{

}


payload::payload(double* pd) :
   m_etype(e_type_pdouble)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
   , m_pd(pd)
{

}



payload::payload(unsigned long long * pull) :
   m_etype(e_type_punsigned_long_long)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
   ,m_pull(pull)
{

}


//payload::payload(float float)
//{
//
//   m_etype = e_type_new;
//   operator = (float);
//
//}
//
//
//payload::payload(double d)
//{
//
//   m_etype = e_type_new;
//   operator = (double);
//
//}


payload::payload(const ::file::path & path) :
   m_etype(e_type_path),
   m_ppath(__new__prefix(&m_preferer) new ::file::path_object(path))
{

}


payload::payload(const string_array_base & stra) :
   m_etype(e_type_string_array),
   m_pstra(__new__prefix(&m_preferer) new string_array(stra))
{


}


payload::payload(const ::int_array_base & ia) :
   m_etype(e_type_int_array),
   m_pia(__new__prefix(&m_preferer) new ::int_array(ia))
{

}

payload::payload(const ::long_long_array_base& longlonga) :
   m_etype(e_type_long_long_array),
   m_plonglonga(__new__prefix(&m_preferer) new ::long_long_array(longlonga))
{

}

payload::payload(const ::float_array_base& floata) :
   m_etype(e_type_float_array),
   m_pfloata(__new__prefix(&m_preferer) new ::float_array(floata))
{

}

payload::payload(const ::double_array_base& doublea) :
   m_etype(e_type_double_array),
   m_pdoublea(__new__prefix(&m_preferer) new ::double_array(doublea))
{

}

payload::payload(const payload_array & payloada) :
   m_etype(e_type_payload_array),
   m_ppayloada(__new__prefix(&m_preferer) new payload_array(payloada))
{

}


payload::payload(const ::property_set & set) :
   m_etype(e_type_property_set),
   m_ppropertyset(__new__prefix(&m_preferer) new ::property_set(set))
{

}


payload::payload(const class ::payload & payload) :
   m_etype(e_type_new)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
{

   operator = (payload);

}


//payload::payload(::payload * ppayload) :
//   m_etype(e_type_payload_pointer)
//#if REFERENCING_DEBUGGING
//   , m_preferer(nullptr)
//#endif
//   ,m_ppayload(ppayload)
//{
//
//}


//pack::pack(const ::std::initializer_list < pack >& list_base)
//{
//
//   for (auto& payload : list_base)
//   {
//
//      if (payload.get_type() == e_type_property_set)
//      {
//
//         propset().merge(payload.propset());
//
//      }
//
//   }
//
//}


//payload::payload(const ::property & property) :
//   m_etype(e_type_property)
//#if REFERENCING_DEBUGGING
//   , m_preferer(nullptr)
//#endif
//   ,m_pproperty(øallocate< ::property_particle>(property))
//{
//
//}


//payload::payload(::property * pproperty)
//#if REFERENCING_DEBUGGING
//   : m_preferer(nullptr)
//#endif
//{
//
//   m_etype = e_type_new;
//
//   if (::is_set(pproperty))
//   {
//
//      operator = (pproperty);
//
//   }
//   else
//   {
//
//      clear_data();
//
//   }
//
//}
//

payload::payload(const ::atom & atom) :
   m_etype(e_type_atom)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
   ,m_atomPayload(atom)
{

}


payload::payload(const class time & time) :
   m_etype(e_type_time)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
   ,m_time(time)
{


}


payload::payload(class ::time * ptime) :
   m_etype(e_type_ptime)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
   ,m_ptime(ptime)
{

}


payload::payload(const ::earth::time & earthtime) :
   m_etype(e_type_earth_time)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
   ,m_earthtime(earthtime)
{
   
}


payload::payload(const ::color::color & color) :
   m_etype(e_type_color)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
   ,m_color(color)
{

}


payload::payload(const ::color::hls & hls) :
   m_etype(e_type_hls)
#if REFERENCING_DEBUGGING
   , m_preferer(nullptr)
#endif
   ,m_hls(hls)
{

}


payload::~payload()
{

   payload_release();

}


bool payload::target_constrained_assign(const ::payload & payload)
{

   if (m_etype == payload.m_etype)
   {

      if (m_etype == e_type_string)
      {

         m_str = payload.m_str;

      }
      else
      {

         m_payloadall = payload.m_payloadall;

      }

   }
   else if(m_etype == e_type_char)
   {

      m_ch = payload.as_char();

   }
//   else if(m_etype == e_type_enum_check)
//   {
//
//      m_echeck = payload.echeck();
//
//   }
   else if(m_etype == e_type_string)
   {

      m_str = payload.as_string();

   }
   else
   {

      return false;

   }

   return true;

}


character_count payload::length() const
{

   return this->as_string().length();

}


void payload::as(::string & str) const
{

   str = this->as_string();

}


void payload::as(::memory_base & memory) const
{

   memory = this->as_memory();

}


::enum_type payload::get_type() const
{

   return m_etype;

}


atom::enum_type payload::atom_type() const
{

   if(m_etype != e_type_atom)
   {

      return atom::e_type_not_an_atom;

   }

   return m_atomPayload.m_etype;

}


class ::payload & payload::operator ++(int)
{

   switch(get_type())
   {
   case e_type_new:
   case e_type_null:
   case e_type_string_array:
   case e_type_int_array:
   case e_type_long_long_array:
   case e_type_float_array:
   case e_type_double_array:
   case e_type_empty:
   case e_type_element:
   case e_type_path:
      set_type(e_type_int);
      m_i = 1;
      break;
   case e_type_bool:
      if(!m_b)
      {
         set_type(e_type_int);
         m_i = 1;
      }
      else
      {
         set_type(e_type_int);
         m_i = 2;
      }
      break;
   case e_type_string:
   {
      auto i = atoi(m_str) + 1;
      set_type(e_type_int);
      m_i = i;

   }
      break;
   case e_type_double:
      m_d += 1.0;
      break;
   case e_type_int:
      m_i++;
      break;
   case e_type_unsigned_int:
      m_ui++;
      break;
   default:
      set_type(e_type_int, false);
      m_i = 1;
      break;
   }
   return *this;
}


void payload::set_type(const ::type_atom & typeatom)
{

   set_type(e_type_type, false);

   m_typeatom = typeatom;

}


bool payload::get_type(::type_atom & typeatom) const
{

   if (m_etype != e_type_type)
   {

      return false;

   }

   typeatom = m_typeatom;

   return true;

}


void payload::set_type(enum_type etype, bool bConvert)
{

/*   if (m_etype == e_type_payload_pointer)
   {

      m_ppayload->set_type(etype, bConvert);

   }
   else if (m_etype == e_type_property)
   {

      m_pproperty->set_type(etype, bConvert);

   }
   else */if (etype != m_etype)
   {

      payload_release();

      if (bConvert && m_etype != e_type_new)
      {

         switch (etype)
         {
         case e_type_char:
            m_i = this->as_char();
            break;
         case e_type_unsigned_char:
            m_ui = this->as_unsigned_char();
            break;
         case e_type_short:
            m_i = this->as_short();
            break;
         case e_type_unsigned_short:
            m_ui = this->as_unsigned_short();
            break;
         case e_type_int:
            m_i = this->as_int();
            break;
         case e_type_unsigned_int:
            m_ui = this->as_unsigned_int();
            break;
         case e_type_long_long:
            m_hi = this->as_long_long();
            break;
         case e_type_unsigned_long_long:
            m_hn = this->as_unsigned_long_long();
            break;
         case e_type_double:
            m_d = this->as_double();
            break;
         case e_type_string:
            m_str = ::transfer(this->as_string());
            break;
         case e_type_atom:
            m_atomPayload = ::transfer(this->as_atom());
            break;
         default:
            ::set_last_status(error_conversion_not_a_number);
            break;

         }

      }
      else
      {

         if (etype == e_type_string)
         {

            ::new(&m_str) ::string();

         }
         else if (etype == e_type_atom)
         {

            ::new(&m_atomPayload) ::atom();

         }
         else if (etype >= e_type_element && etype < e_type_last_element)
         {

            m_payloadall = {};

         }

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
   //else if (get_type() == e_type_payload_pointer)
   //{

   //   m_ppayload->set_string(::transfer(str));

   //}
   //else if (get_type() == e_type_property)
   //{

   //   m_pproperty->set_string(::transfer(str));

   //}
   else
   {

      set_type(e_type_string, false);

      m_str = ::transfer(str);

   }

}


void payload::set_string(const ::string & str)
{

   if (get_type() == e_type_string)
   {

      m_str = str;

   }
   else if (get_type() == e_type_pstring)
   {

      *m_pstr = str;

   }
   //else if (get_type() == e_type_payload_pointer)
   //{

   //   m_ppayload->set_string(str);

   //}
   //else if (get_type() == e_type_property)
   //{

   //   m_pproperty->set_string(str);

   //}
   else
   {

      set_type(e_type_string, false);

      m_str = str;

   }

}


//void payload::set_string(::string && str)
//{
//
//   if (get_type() == e_type_string)
//   {
//
//      m_str = ::transfer(str);
//
//   }
//   else if (get_type() == e_type_pstring)
//   {
//
//      m_pstr->assign(::transfer(str));
//
//   }
//   else if (get_type() == e_type_payload_pointer)
//   {
//
//      m_ppayload->set_string(::transfer(str));
//
//   }
//   else if (get_type() == e_type_property)
//   {
//
//      m_pproperty->set_string(::transfer(str));
//
//   }
//   else
//   {
//
//      set_type(e_type_string, false);
//
//      ::new(&m_str) ::string(::transfer(str));
//
//   }
//
//}


void payload::unset()
{
   set_type(e_type_new, false);
}


void payload::unset(const ::scoped_string & scopedstrPropertySetKey)
{

   if (get_type() == e_type_property_set)
   {

      property_set_reference().erase_by_name(scopedstrPropertySetKey);

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

   if(get_type() == e_type_patom)
   {

      *m_patom = atom;

   }
   //else if(get_type() == e_type_payload_pointer)
   //{

   //   *m_ppayload = atom;

   //}
   //else if (get_type() == e_type_property)
   //{

   //   *m_pproperty = atom;

   //}
   else
   {

      if (get_type() != e_type_atom)
      {

         set_type(e_type_atom, false);

      }

      m_atomPayload = atom;

   }

}


class ::payload & payload::operator = (para_return & eret)
{

   set_type(e_type_parareturn, false);

   m_parareturn = eret;

   return *this;

}


//class ::payload & payload::operator = (bool b)
//{
//
//   if(get_type() == e_type_pbool)
//   {
//
//      *m_pb = b;
//
//   }
//   else if(get_type() == e_type_payload_pointer)
//   {
//
//      *m_ppayload = b;
//
//   }
//   else if (get_type() == e_type_property)
//   {
//
//      *m_pproperty = b;
//
//   }
//   else
//   {
//
//      set_type(e_type_bool, false);
//
//      m_b = b;
//
//   }
//
//   return *this;
//
//}


//class ::payload & payload::operator = (bool * pb)
//{
//
//   set_type(e_type_pbool, false);
//
//   m_pb = pb;
//
//   return *this;
//
//}


//class ::payload & payload::operator = (int i)
//{
//
//    if(get_type() == e_type_pint)
//   {
//
//       *m_pi = i;
//
//   }
//   else if(get_type() == e_type_payload_pointer)
//   {
//
//       *m_ppayload = i;
//
//   }
//   else if (get_type() == e_type_property)
//   {
//
//       *m_pproperty = i;
//
//   }
//   else
//   {
//
//       set_type(e_type_int, false);
//
//      m_i = i;
//
//   }
//
//   return *this;
//
//}
//
//
//class ::payload & payload::operator = (int * pi)
//{
//
//   set_type(e_type_pint, false);
//
//   m_pi = pi;
//
//   return *this;
//
//}
//
//
//class ::payload & payload::operator = (unsigned int * pinteraction)
//{
//
//    set_type(e_type_punsigned_int, false);
//
//   m_pui = pinteraction;
//
//   return *this;
//
//}
//
//
//class ::payload & payload::operator = (long long * pi)
//{
//
//    set_type(e_type_plong_long, false);
//
//   m_pll = pi;
//
//   return *this;
//
//}
//
//
//class ::payload & payload::operator = (unsigned long long * pinteraction)
//{
//
//    set_type(e_type_punsigned_long_long, false);
//
//   m_pull = pinteraction;
//
//   return *this;
//
//}


class ::payload & payload::operator = (const ::earth::time & time)
{

    set_type(e_type_time, false);

   m_earthtime = time.get_time();

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
//   m_hn = make64_from32(file_time.dwLowDateTime, file_time.dwHighDateTime);
//
//   return *this;
//
//}
//
//
//#endif


//class ::payload & payload::operator = (long long i)
//{
//   if(get_type() == e_type_plong_long)
//   {
//      *m_pll = i;
//   }
//   else if(get_type() == e_type_payload_pointer)
//   {
//      *m_ppayload = i;
//   }
//   else if (get_type() == e_type_property)
//   {
//      *m_pproperty = i;
//   }
//   else
//   {
//      set_type(e_type_long_long, false);
//      m_hi = i;
//   }
//   return *this;
//}
//
//
//class ::payload & payload::operator = (unsigned long long u)
//{
//   if(get_type() == e_type_punsigned_long_long)
//   {
//      *m_pull = u;
//   }
//   else if(get_type() == e_type_payload_pointer)
//   {
//      *m_ppayload = u;
//   }
//   else if (get_type() == e_type_property)
//   {
//      *m_pproperty = u;
//   }
//   else
//   {
//      set_type(e_type_unsigned_long_long, false);
//      m_hn = u;
//   }
//   return *this;
//}
//
//
//class ::payload & payload::operator = (unsigned int u)
//{
//   set_type(e_type_unsigned_int, false);
//   m_ui = u;
//   return *this;
//}


#if !defined(LINUX) && !defined(MACOS) && !defined(__ANDROID__) && !defined(APPLE_IOS) && !defined(__BSD__)

class ::payload & payload::operator = (long l)
{

   set_type(e_type_int,false);

   m_i = l;

   return *this;

}


#endif


#if defined(__APPLE__)
   class ::payload & payload::operator = (long l)
   {
      set_type(e_type_long_long,false);
      m_hi = l;
      return *this;
   }
#endif

#if defined(__ANDROID__)
   class ::payload & payload::operator = (long l)
   {
      set_type(e_type_int,false);
      m_i = l;
      return *this;
   }
#endif

//class ::payload & payload::operator = (float float)
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      m_ppayload->operator = (float);
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      m_pproperty->operator =(float);
//
//   }
//   else if (m_etype == e_type_pdouble)
//   {
//
//      *m_pd = float;
//
//   }
//   else if (m_etype == e_type_pfloat)
//   {
//
//      *m_pf = float;
//
//   }
//   else if (m_etype == e_type_pchar)
//   {
//
//      *m_pch = (char)float;
//
//   }
//   else if (m_etype == e_type_pshort)
//   {
//
//      *m_psh = (short)float;
//
//   }
//   else if (m_etype == e_type_pint)
//   {
//
//      *m_pi = (int)float;
//
//   }
//   else if (m_etype == e_type_plong_long)
//   {
//
//      *m_pll = (long long)float;
//
//   }
//   else
//   {
//
//      if (m_etype != e_type_float)
//      {
//
//         set_type(e_type_float, false);
//
//      }
//
//      m_f = float;
//
//   }
//
//   return *this;
//
//}
//
//
//class ::payload & payload::operator = (double d)
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      m_ppayload->operator = (double);
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      m_pproperty->operator =(double);
//
//   }
//   else if (m_etype == e_type_pdouble)
//   {
//
//      *m_pd = d;
//
//   }
//   else if (m_etype == e_type_pfloat)
//   {
//
//      *m_pf = (float) d;
//
//   }
//   else if (m_etype == e_type_pchar)
//   {
//
//      *m_pch = (char) d;
//
//   }
//   else if (m_etype == e_type_pshort)
//   {
//
//      *m_psh = (short)d;
//
//   }
//   else if (m_etype == e_type_pint)
//   {
//
//      *m_pi = (int)d;
//
//   }
//   else if (m_etype == e_type_plong_long)
//   {
//
//      *m_pll = (long long)d;
//
//   }
//   else
//   {
//      if (m_etype != e_type_double)
//      {
//         set_type(e_type_double, false);
//
//      }
//      m_d = d;
//
//   }
//
//   return *this;
//
//}


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

   set_type(e_type_patom, false);

   m_patom = pid;

   return *this;

}


class ::payload & payload::operator = (const ::wide_character * pcsz)
{

   set_string(unicode_to_utf8(pcsz));

   return *this;

}

class ::payload& payload::operator = (const ::ansi_character* pcsz)
{

   set_string(pcsz);

   return *this;

}


class ::payload & payload::operator = (const ::property & property)
{

   operator = ((const ::payload &)property);

   return *this;

}


//class ::payload & payload::operator = (const ::property * pproperty)
//{
//
//   if (::is_null(pproperty))
//   {
//
//      set_type(e_type_null, false);
//
//   }
//   else
//   {
//
//      set_type(e_type_property, false);
//
//      m_pproperty = øallocate ::property_particle ();
//
//      m_pproperty->object() = *pproperty;
//
//   }
//
//   return *this;
//
//}
//

void payload::payload_increment_reference_count()
{

   switch(m_etype)
   {
      case e_type_element:
         if(m_p) m_p->increment_reference_count();
         break;
      case e_type_string_array:
         if (m_pstra) m_pstra->increment_reference_count();
         break;
      case e_type_int_array:
         if (m_pia) m_pia->increment_reference_count();
         break;
      case e_type_float_array:
         if (m_pfloata) m_pfloata->increment_reference_count();
         break;
      case e_type_payload_array:
         if (m_ppayloada) m_ppayloada->increment_reference_count();
         break;
      case e_type_property_set:
         if (m_ppropertyset) m_ppropertyset->increment_reference_count();
         break;
      case e_type_long_long_array:
         if (m_plonglonga) m_plonglonga->increment_reference_count();
         break;
      case e_type_double_array:
         if (m_pdoublea) m_pdoublea->increment_reference_count();
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
   //if(m_etype == e_type_payload_pointer)
   //{
   //   if(m_ppayload == &payload)
   //      return *this;
   //   m_ppayload->operator = (payload);
   //   return *this;
   //}
   //if (m_etype == e_type_property)
   //{
   //   m_pproperty->object()= payload;
   //   return *this;
   //}
   if(&payload != this)
   {
      switch (((class ::payload &)payload).get_type())
      {
         //case e_type_payload_pointer:
         //   // should dereference (this operator here means a content copy)
         //   *this  = *((class ::payload &)payload).m_ppayload;
         //   return *this;
         //case e_type_property:
         //   // should dereference (this operator here means a content copy)
         //   *this = ((class ::payload&)payload).m_pproperty->object();
         //   return *this;
      case e_type_property_set:
         // should dereference (this operator here means a content copy)
         set_type(payload.get_type(), false);
         m_ppropertyset = payload.m_ppropertyset;
         __refdbg_assign_referer_for(m_ppropertyset);
         m_ppropertyset->increment_reference_count();
         return *this;
      case e_type_pint:
         // should dereference (this operator here means a content copy)
         *this  = *((class ::payload &)payload).m_pi;
         return *this;
      case e_type_pstring:
         // should dereference (this operator here means a content copy)
         *this  = *((class ::payload &)payload).m_pstr;
         return *this;
      default:
         break;
      }

      set_type(payload.get_type(), false);
      
      auto etypeSource = payload.get_type();

      if (etypeSource == e_type_path)
      {

         m_ppath = __new__prefix(&m_preferer) new ::file::path_object(*payload.m_ppath);

      }
      else if (etypeSource == e_type_property_set)
      {

         m_ppropertyset = __new__prefix(&m_preferer) new ::property_set(*payload.m_ppropertyset);

      }
      else if (etypeSource == e_type_int_array)
      {

         m_pia = __new__prefix(&m_preferer) new ::int_array(*payload.m_pia);

      }
      else if (etypeSource == e_type_long_long_array)
      {

         m_plonglonga = __new__prefix(&m_preferer) new ::long_long_array(*payload.m_plonglonga);

      }
      else if (etypeSource == e_type_float_array)
      {

         m_pfloata = __new__prefix(&m_preferer) new ::float_array(*payload.m_pfloata);

      }
      else if (etypeSource == e_type_double_array)
      {

         m_pdoublea = __new__prefix(&m_preferer) new ::double_array(*payload.m_pdoublea);

      }
      else if (etypeSource == e_type_payload_array)
      {

         //m_ppayloada = ___new ::payload_array(*payload.m_ppayloada);

         m_ppayloada = payload.m_ppayloada;

         __refdbg_add_referer

         m_ppayloada->increment_reference_count();

      }
      else if (etypeSource == e_type_string_array)
      {

         m_pstra = __new__prefix(&m_preferer) new ::string_array(*payload.m_pstra);

      }
      else if (payload.is_element())
      {

         m_p = payload.m_p; // raw copy, doesn't care for the right member

         if(m_p->is_referencing_debugging_enabled())
         {

            __refdbg_assign_referer_for(m_p);

         }

         payload_increment_reference_count();

      }
      else
      {
         switch (payload.get_type())
         {
         case e_type_bool:
            m_b = payload.m_b;
            break;
         case e_type_char:
            m_ch = payload.m_ch;
            break;
         case e_type_unsigned_char:
            m_uch = payload.m_uch;
            break;
         case e_type_short:
            m_sh = payload.m_sh;
            break;
         case e_type_unsigned_short:
            m_ush = payload.m_ush;
            break;
         case e_type_int:
            m_i = payload.m_i;
            break;
         case e_type_unsigned_int:
            m_ui = payload.m_ui;
            break;
         case e_type_long_long:
            m_hi = payload.m_hi;
            break;
         case e_type_unsigned_long_long:
            m_hn = payload.m_hn;
            break;
         case e_type_pchar:
            m_pch = payload.m_pch;
            break;
         case e_type_punsigned_char:
            m_puch = payload.m_puch;
            break;
         case e_type_pshort:
            m_psh = payload.m_psh;
            break;
         case e_type_punsigned_short:
            m_push = payload.m_push;
            break;
         case e_type_pint:
            m_pi = payload.m_pi;
            break;
         case e_type_punsigned_int:
            m_pui = payload.m_pui;
            break;
         case e_type_plong_long:
            m_pll = payload.m_pll;
            break;
         case e_type_punsigned_long_long:
            m_pull = payload.m_pull;
            break;
         case e_type_float:
            m_f = payload.m_f;
            break;
         case e_type_double:
            m_d = payload.m_d;
            break;
         case e_type_string:
            m_str = payload.m_str;
            break;
         //case e_type_property:
         //   m_pproperty=payload.m_pproperty;
         //   break;
         case e_type_atom:
            m_atomPayload = payload.m_atomPayload;
            break;
         default:
            m_payloadall = payload.m_payloadall;
            //m_str = payload.m_str;
            break;
         }
      }
   }
   return *this;
}


class ::payload & payload::operator = (const ::int_array_base & ia)
{

   //if (m_etype == e_type_payload_pointer)
   //{

   //   m_ppayload->operator = (ia);

   //}
   //else if (m_etype == e_type_property)
   //{

   //   m_pproperty->object() = ia; 

   //}
   //else
   {

      if (m_etype != e_type_int_array)
      {

         set_type(e_type_int_array, false);

      }

      if (::is_null(m_pia))
      {

         m_pia = ___new int_array(ia);

      }
      else
      {

         *m_pia = ia;

      }

   }

   return *this;

}


class ::payload& payload::operator = (const ::long_long_array_base& longlonga)
{

   //if (m_etype == e_type_payload_pointer)
   //{

   //   m_ppayload->operator = (ia);

   //}
   //else if (m_etype == e_type_property)
   //{

   //   m_pproperty->object() = ia; 

   //}
   //else
   {

      if (m_etype != e_type_long_long_array)
      {

         set_type(e_type_long_long_array, false);

      }

      if (::is_null(m_plonglonga))
      {

         m_plonglonga = ___new long_long_array(longlonga);

      }
      else
      {

         *m_plonglonga = longlonga;

      }

   }

   return *this;

}


class ::payload& payload::operator = (const ::float_array_base& floata)
{

   //if (m_etype == e_type_payload_pointer)
   //{

   //   m_ppayload->operator = (ia);

   //}
   //else if (m_etype == e_type_property)
   //{

   //   m_pproperty->object() = ia; 

   //}
   //else
   {

      if (m_etype != e_type_float_array)
      {

         set_type(e_type_float_array, false);

      }

      if (::is_null(m_pfloata))
      {

         m_pfloata = ___new float_array(floata);

      }
      else
      {

         *m_pfloata = floata;

      }

   }

   return *this;

}




class ::payload& payload::operator = (const ::double_array_base& doublea)
{

   //if (m_etype == e_type_payload_pointer)
   //{

   //   m_ppayload->operator = (ia);

   //}
   //else if (m_etype == e_type_property)
   //{

   //   m_pproperty->object() = ia; 

   //}
   //else
   {

      if (m_etype != e_type_double_array)
      {

         set_type(e_type_double_array, false);

      }

      if (::is_null(m_pdoublea))
      {

         m_pdoublea = ___new double_array(doublea);

      }
      else
      {

         *m_pdoublea = doublea;

      }

   }

   return *this;

}


//class ::payload& payload::operator = (const ::float_array_base& floata)
//{
//
//   //if (m_etype == e_type_payload_pointer)
//   //{
//
//   //   m_ppayload->operator = (ia);
//
//   //}
//   //else if (m_etype == e_type_property)
//   //{
//
//   //   m_pproperty->object() = ia; 
//
//   //}
//   //else
//   {
//
//      if (m_etype != e_type_float_array)
//      {
//
//         set_type(e_type_float_array, false);
//
//      }
//
//      if (::is_null(m_pfloata))
//      {
//
//         m_pfloata = ___new float_array(floata);
//
//      }
//      else
//      {
//
//         *m_pfloata = floata;
//
//      }
//
//   }
//
//   return *this;
//
//}

class ::payload & payload::operator = (const class memory & memory)
{

   //if (m_etype == e_type_payload_pointer)
   //{

   //   m_ppayload->operator = (memory);

   //}
   //else if (m_etype == e_type_property)
   //{

   //   m_pproperty->object() = memory;

   //}
   //else
   {

      if (m_etype != e_type_memory)
      {

         set_type(e_type_memory, false);

      }

      if (::is_null(m_pmemory))
      {

         m_pmemory = ___new ::memory(memory);

      }
      else
      {

         *m_pmemory = memory;

      }

   }

   return *this;

}


class ::payload & payload::operator = (const string_array_base & stra)
{

   //if (m_etype == e_type_payload_pointer)
   //{

   //   m_ppayload->operator = (stra);

   //}
   //else if (m_etype == e_type_property)
   //{

   //   m_pproperty->object() = stra;

   //}
   //else
   {

      if (m_etype != e_type_string_array)
      {

         set_type(e_type_string_array, false);

      }

      if (::is_null(m_pstra))
      {

         m_pstra = __new__prefix(&m_preferer) new ::string_array(stra);

      }
      else
      {

         *m_pstra = stra;

      }

   }

   return *this;

//}
//release();
//
//   set_type(e_type_string_array, false);
//
//   m_pstra = ___new ::string_array_base(stra);
//
//   return *this;

}


class ::payload & payload::operator = (const payload_array & payloada)
{
   //{

      //if (m_etype == e_type_payload_pointer)
      //{

      //   m_ppayload->operator = (payloada);

      //}
      //else if (m_etype == e_type_property)
      //{

      //   m_pproperty->object() = payloada;

      //}
      //else
      {

         if (m_etype != e_type_payload_array)
         {

            set_type(e_type_payload_array, false);

         }

         if (::is_null(m_ppayloada))
         {

            m_ppayloada = __new__prefix(&m_preferer) new ::payload_array(payloada);

         }
         else
         {

            *m_ppayloada = payloada;

         }

      }

      return *this;

   //}

   //release();

   //set_type(e_type_payload_array, false);

   //m_ppayloada = ___new ::payload_array(payloada);

   //return *this;

}


class ::payload & payload::operator = (const ::property_set & propertyset)
{

   //if (m_etype == e_type_payload_pointer)
   //{

   //   m_ppayload->operator = (propertyset);

   //}
   //else if (m_etype == e_type_property)
   //{

   //   m_pproperty->object() = propertyset;

   //}
   //else
   {

      if (m_etype != e_type_property_set)
      {

         set_type(e_type_property_set, false);

      }

      if (::is_null(m_ppropertyset))
      {

         m_ppropertyset = __new__prefix(&m_preferer) new ::property_set(propertyset);

      }
      else
      {

         *m_ppropertyset = propertyset;

      }

   }


   //release();

   //set_type(e_type_property_set, false);

   //m_ppropertyset = ___new ::property_set(propertyset);

   return *this;

}


class ::payload & payload::operator = (const ::atom & atom)
{

   //if (m_etype == e_type_payload_pointer)
   //{

   //   m_ppayload->set_id(atom);

   //}
   //else if (m_etype == e_type_property)
   //{

   //   m_pproperty->set_id(atom);

   //}
   //else
   {

      if (m_etype != e_type_atom)
      {

         set_type(e_type_atom, false);

      }

      set_id(atom);

   }

   return *this;

}


class ::payload & payload::operator = (const class time & time)
{
   //{

      //if (m_etype == e_type_payload_pointer)
      //{

      //   m_ppayload->operator =(time);

      //}
      //else if (m_etype == e_type_property)
      //{

      //   m_pproperty->object() = time;

      //}
      //else
      {

         if (m_etype != e_type_time)
         {

            set_type(e_type_time, false);

         }

         m_time = time;

      }

   //   return *this;


   //set_type(e_type_time, false);

   //m_time = time;

   return *this;

}


class ::payload & payload::operator = (class time * ptime)
{

   set_type(e_type_ptime, false);

   m_ptime = ptime;

   return *this;

}


::payload & payload::operator = (const ::block & block)
{

/*   if(m_etype == e_type_payload_pointer)
   {

      return m_ppayload->operator = (block);

   }
   else if (m_etype == e_type_property)
   {

      m_pproperty->object() = block;

   }
   else*/ if(m_etype == e_type_memory)
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
   //else if (m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->casts_to(etype);

   //}
   //else if (m_etype == e_type_property)
   //{

   //   return m_pproperty->casts_to(etype);

   //}


   return false;

}


//bool payload::is_property_true(const ::atom & atom, bool bDefault) const
//{
//
//   switch (m_etype)
//   {
//   case e_type_property_set:
//      return m_ppropertyset->is_true(atom, bDefault);
//   case e_type_payload_pointer:
//      return m_ppayload->is_property_true(atom, bDefault);
//   case e_type_property:
//      return m_pproperty->is_property_true(atom, bDefault);
//   default:
//      return bDefault;
//   }
//
//}


bool payload::is_true_or_empty() const
{

   if(is_empty())
   {

      return true;

   }

   return is_true();

}


bool payload::is_true() const
{

   //if (m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->is_true(bDefault);

   //}
   //else if (m_etype == e_type_property)
   //{

   //   return m_pproperty->is_true(bDefault);

   //}
   //else
   {
      switch (m_etype)
      {
      case e_type_null:
         return false;
      case e_type_empty:
         return false;
      case e_type_key_exists:
         return true;
      case e_type_string:
         return !m_str.is_empty() && m_str.case_insensitive_order("no") != 0 && m_str.case_insensitive_order("false") != 0 && m_str.order("0") != 0;
      case e_type_pstring:
         return m_pstr && !m_pstr->is_empty() && m_pstr->case_insensitive_order("no") != 0 && m_pstr->case_insensitive_order("false") != 0 && m_pstr->order("0") != 0;
      case e_type_int:
         return m_i != 0;
      case e_type_unsigned_int:
         return m_ui != 0;
      case e_type_long_long:
         return m_hi != 0;
      case e_type_unsigned_long_long:
         return m_hn != 0;
      case e_type_double:
         return m_d != 0;
      case e_type_bool:
         return m_b;
      //case e_type_payload_pointer:
      //   return m_ppayload->is_true(bDefault);
      //case e_type_property:
      //   return m_pproperty->is_true(bDefault);
      case e_type_atom:
         return m_atomPayload.is_true();
//      case e_type_enum_status:
//         return m_estatus.succeeded();
//      case e_type_enum_check:
//         return __bool(m_echeck);
      default:
         return false;
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
   case e_type_int:
      return false;
   case e_type_unsigned_int:
      return false;
   case e_type_long_long:
      return false;
   case e_type_unsigned_long_long:
      return false;
   case e_type_double:
      return false;
   //case e_type_payload_pointer:
   //   return m_ppayload->is_empty();
   //case e_type_property:
   //   return m_pproperty->is_empty();
   case e_type_atom:
      return m_atomPayload.is_empty();
   case e_type_patom:
      return m_patom->is_empty();


      // particle classes
   case e_type_element:
      return is_element_null();
   case e_type_string_array:
      return ::is_null(m_pstra) || m_pstra->is_empty();
   case e_type_int_array:
      return ::is_null(m_pia) || m_pia->is_empty();
   case e_type_float_array:
      return ::is_null(m_pfloata) || m_pfloata->is_empty();
   case e_type_payload_array:
      return ::is_null(m_ppayloada) || m_ppayloada->is_empty();
   case e_type_property_set:
      return ::is_null(m_ppropertyset) || m_ppropertyset->is_empty();
   case e_type_long_long_array:
      return ::is_null(m_plonglonga) || m_plonglonga->is_empty();
   case e_type_double_array:
      return ::is_null(m_pdoublea) || m_pdoublea->is_empty();
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


bool payload::has_character() const
{

   switch (m_etype)
   {
   case e_type_null:
      return false;
   case e_type_empty:
      return false;
   case e_type_empty_argument:
      return false;
   case e_type_new:
      return false;
   case e_type_string:
      return m_str.has_character();
   case e_type_int:
      return true;
   case e_type_unsigned_int:
      return true;
   case e_type_long_long:
      return true;
   case e_type_unsigned_long_long:
      return true;
   case e_type_double:
      return true;
   //case e_type_payload_pointer:
   //   return m_ppayload->has_character();
   //case e_type_property:
   //   return m_pproperty->has_character();
   case e_type_atom:
      return m_atomPayload.has_character();
   case e_type_patom:
      return m_patom->has_character();
   case e_type_element:
      return !is_element_null();
   case e_type_string_array:
      return ::is_set(m_pstra) && m_pstra->has_element();
   case e_type_int_array:
      return ::is_set(m_pia) && m_pia->has_element();
   case e_type_float_array:
      return ::is_set(m_pfloata) && m_pfloata->has_element();
   case e_type_payload_array:
      return ::is_set(m_ppayloada) && m_ppayloada->has_element();
   case e_type_property_set:
      return ::is_set(m_ppropertyset) && m_ppropertyset->has_property();
   case e_type_long_long_array:
      return ::is_set(m_plonglonga) && m_plonglonga->has_element();
   case e_type_double_array:
      return ::is_set(m_pdoublea) && m_pdoublea->has_element();
   case e_type_memory:
      return ::is_set(m_pmemory) && !m_pmemory->is_empty();
   case e_type_path:
      return ::is_set(m_ppath) && m_ppath->has_character();
      //case type_image:
      //   return m_pimage.ok();

   default:
      return false;
   }
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


::std::strong_ordering payload::case_insensitive_order(const class ::payload & payload) const
{

   if (has_reference_of_type(::e_type_int_array))
   {

      if (payload.has_reference_of_type(::e_type_int_array))
      {

         return int_array_reference() <=> payload.int_array_reference();

      }
      else
      {

         return as_string_array() <=> payload.as_string_array();

      }

   }
   else if (has_reference_of_type(::e_type_long_long_array))
   {

      if (payload.has_reference_of_type(::e_type_long_long_array))
      {

         return long_long_array_reference() <=> payload.long_long_array_reference();

      }
      else
      {

         return as_string_array() <=> payload.as_string_array();

      }

   }
   else if (has_reference_of_type(::e_type_float_array))
   {

      if (payload.has_reference_of_type(::e_type_float_array))
      {

         return float_array_reference() <=> payload.float_array_reference();

      }
      else
      {

         return as_string_array() <=> payload.as_string_array();

      }

   }
   else if (has_reference_of_type(::e_type_double_array))
   {

      if (payload.has_reference_of_type(::e_type_double_array))
      {

         return double_array_reference().order(payload.double_array_reference());

      }
      else
      {

         return as_string_array() <=> payload.as_string_array();

      }

   }
   else if (has_reference_of_type(::e_type_string_array))
   {

      if (payload.has_reference_of_type(::e_type_string_array))
      {

         return string_array_reference().case_insensitive_order(payload.string_array_reference());

      }
      else
      {

         return string_array_reference().case_insensitive_order(payload.as_string_array());

      }

   }
   else if (has_reference_of_type(::e_type_payload_array))
   {

      if (payload.has_reference_of_type(::e_type_payload_array))
      {

         return payload_array_reference().case_insensitive_order(payload.payload_array_reference());

      }
      else
      {

         return payload_array_reference().case_insensitive_order(payload.as_payload_array());

      }

   }
   //else if (is_integer())
   //{

   //   return this->get_string().order(payload.string());

   //}
   //else if (is_floating())
   //{

   //   return this->get_string().order(payload.string());

   //}
   else
   {

      return this->as_string().case_insensitive_order(payload.as_string());

   }

}


//::std::strong_ordering payload::case_insensitive_order(const ::scoped_string & scopedstr) const
//{
//   ::payload payload(scopedstr);
//   return case_insensitive_order(payload);
//}



bool payload::equals_payload(const payload & payload) const
{

   return order_payload(payload) == 0;

}


//bool payload::equals(const ::scoped_string & scopedstr) const
//{
//
//   return order(scopedstr) == 0;
//
//}


bool payload::case_insensitive_equals(const payload & payload) const
{

   return case_insensitive_order(payload) == 0;

}


//bool payload::case_insensitive_equals(const ::scoped_string & scopedstr) const
//{
//
//   return case_insensitive_order(scopedstr) == 0;
//
//}


::std::strong_ordering payload::order_payload(const class ::payload & payload) const
{

   if(has_reference_of_type(::e_type_int_array))
   {
      
      if(payload.has_reference_of_type(::e_type_int_array))
      {

         return int_array_reference() <=> payload.int_array_reference();

      }
      else
      {

         return as_string_array() <=> payload.as_string_array();

      }

   }
   else if (has_reference_of_type(::e_type_long_long_array))
   {

      if (payload.has_reference_of_type(::e_type_long_long_array))
      {

         return long_long_array_reference() <=> payload.long_long_array_reference();

      }
      else
      {

         return as_string_array() <=> payload.as_string_array();

      }

   }
   else if (has_reference_of_type(::e_type_float_array))
   {

      if (payload.has_reference_of_type(::e_type_float_array))
      {

         return float_array_reference() <=> payload.float_array_reference();

      }
      else
      {

         return as_string_array() <=> payload.as_string_array();

      }

   }
   else if (has_reference_of_type(::e_type_double_array))
   {

      if (payload.has_reference_of_type(::e_type_double_array))
      {

         return double_array_reference() <=> payload.double_array_reference();

      }
      else
      {

         return as_string_array() <=> payload.as_string_array();

      }

   }
   else if(has_reference_of_type(::e_type_string_array))
   {
      
      if(payload.has_reference_of_type(::e_type_string_array))
      {
         
         return string_array_reference() <=> payload.string_array_reference();

      }
      else
      {
         
         return string_array_reference() <=> payload.as_string_array();

      }

   }
   else if(has_reference_of_type(::e_type_payload_array))
   {

      if(payload.has_reference_of_type(::e_type_payload_array))
      {

         return payload_array_reference() <=> payload.payload_array_reference();

      }
      else
      {

         return payload_array_reference() <=> payload.as_payload_array();

      }

   }
   //else if(is_integer())
   //{

   //   return as_long_long() <=> payload.as_long_long();

   //}
   //else if (is_floating())
   //{

   //   return ::std::strong_order(as_double(), payload.as_double());

   //}
   else
   {

      return this->as_string().order(payload.as_string());

   }

}


//::std::strong_ordering payload::order(const ::scoped_string & scopedstr) const
//{
//
//   ::payload payload(scopedstr);
//
//   return order(payload);
//
//}


//bool payload::equals_payload(const class ::payload & payload) const
//{
//   // if variables are equal:
//   // all values of both variables should be equal
//   return equals(payload);
//}


::std::strong_ordering payload::operator <=> (const ::payload & payload) const
{
   
   return order_payload(payload);

}


//bool payload::operator > (const class ::payload & payload) const
//{
//
//   return compare(payload) > 0;
//
//}
//
//bool payload::operator < (const class ::payload & payload) const
//{
//   return compare(payload) < 0;
//}
//
//bool payload::operator >= (const class ::payload & payload) const
//{
//   return compare(payload) >= 0;
//}
//
//bool payload::operator <= (const class ::payload & payload) const
//{
//   return compare(payload) <= 0;
//}
//
//bool payload::operator != (const class ::payload & payload) const
//{
//   return compare(payload) != 0;
//}


bool payload::equals_scoped_string(const ::scoped_string & scopedstr) const
{

   return equals_payload(scopedstr);

}


::std::strong_ordering payload::operator <=> (const ::scoped_string & scopedstr) const
{
   
   return order_payload(scopedstr);

}


//bool payload::operator < (const ::scoped_string & scopedstr) const
//{
//   return get_string() < psz;
//}
//
//bool payload::operator <= (const ::scoped_string & scopedstr) const
//{
//   return get_string() <= psz;
//}
//
//bool payload::operator >= (const ::scoped_string & scopedstr) const
//{
//   return get_string() >= psz;
//}
//
//bool payload::operator > (const ::scoped_string & scopedstr) const
//{
//   return get_string() > psz;
//}
//
//bool payload::operator != (const ::scoped_string & scopedstr) const
//{
//   return get_string() != psz;
//}


//bool payload::operator == (const ::scoped_string & scopedstr) const
//{
//
//   return equals(str);
//
//}


::std::strong_ordering payload::operator <=> (const ::string & str) const
{

   return order_payload(str);

}


//bool payload::operator != (const ::scoped_string & scopedstr) const
//{
//   return get_string() != str;
//}
//
//bool payload::operator < (const ::scoped_string & scopedstr) const
//{
//   return get_string() < str;
//}
//
//bool payload::operator <= (const ::scoped_string & scopedstr) const
//{
//   return get_string() <= str;
//}
//
//bool payload::operator >= (const ::scoped_string & scopedstr) const
//{
//   return get_string() >= str;
//}
//
//bool payload::operator > (const ::scoped_string & scopedstr) const
//{
//   return get_string() > str;
//}


bool payload::equals_signed (long long i) const
{
   return as_long_long() == i;
}


bool payload::equals_unsigned(unsigned long long u) const
{
   return as_unsigned_long_long() == u;
}


::std::strong_ordering payload::operator <=> (int i) const
{
   return as_int() <=> i;
}

//bool payload::operator != (int i) const
//{
//   return as_int() != i;
//}
//
//bool payload::operator < (int i) const
//{
//   return as_long_long() < i;
//}
//
//bool payload::operator <= (int i) const
//{
//   return as_long_long() <= i;
//}
//
//bool payload::operator >= (int i) const
//{
//   return as_long_long() >= i;
//}
//
//bool payload::operator > (int i) const
//{
//   return as_long_long() > i;
//}









//
//
//bool payload::operator == (long long i) const
//{
//   return as_long_long() == i;
//}


::std::strong_ordering payload::operator <=> (long long i) const
{
   return as_long_long() <=> i;
}

//bool payload::operator != (long long i) const
//{
//   return as_long_long() != i;
//}
//
//bool payload::operator < (long long i) const
//{
//   return as_long_long() < i;
//}
//
//bool payload::operator <= (long long i) const
//{
//   return as_long_long() <= i;
//}
//
//bool payload::operator >= (long long i) const
//{
//   return as_long_long() >= i;
//}
//
//bool payload::operator > (long long i) const
//{
//   return as_int() > i;
//}
























//
//
//bool payload::operator == (bool b) const
//{
//   return is_equivalent(get_bool(), b);
//}


::std::strong_ordering payload::operator <=> (bool b) const
{
   
   return ::comparison::get_bool_int(get_bool()) <=> ::comparison::get_bool_int(b);
   
}

//bool payload::operator != (bool b) const
//{
//   return is_different(get_bool(), b);
//}
//
//bool payload::operator < (bool b) const
//{
//   return is_lesser(get_bool(), b);
//}
//
//bool payload::operator <= (bool b) const
//{
//   return is_lesser_or_equal(get_bool(), b);
//}
//
//bool payload::operator >= (bool b) const
//{
//   return is_greater_or_equal(get_bool(), b);
//}
//
//bool payload::operator > (bool b) const
//{
//   return is_greater(get_bool(), b);
//}

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
//bool payload::strictly_equal(const ::scoped_string & scopedstr) const
//{
//   return m_etype == e_type_string && m_str == str;
//}
//
//bool payload::strictly_equal(double d) const
//{
//   return m_etype == e_type_double && m_d == d;
//}
//
//bool payload::strictly_equal(int i) const
//{
//   return m_etype == e_type_int && m_i == i;
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
//bool payload::strictly_different(const ::scoped_string & scopedstr) const
//{
//   return m_etype != e_type_string || m_str != str;
//}
//
//bool payload::strictly_different(double d) const
//{
//   return m_etype != e_type_double || m_d != d;
//}
//
//bool payload::strictly_different(int i) const
//{
//   return m_etype != e_type_int || m_i != i;
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

      for(int i = 0; i < array_get_count(); i++)
      {

         if(i > 0)
         {

            str += " ";

         }

         str += ::as_string(i);

         str += " => ";

         str += at(i).get_recursive_string();

         str += ";";

      }

      str += ")";

      return str;

   }
   else
   {
      
      return this->as_string();

   }

}


::posix_time payload::as_time(const class ::time & timeDefault) const
{

/*   if (m_etype == e_type_payload_pointer)
   {
      return m_ppayload->as_time(timeDefault);
   }
   else if (m_etype == e_type_property)
   {
      return m_pproperty->as_time(timeDefault);
   }
   else*/ if (m_etype != e_type_time)
   {

      class ::time time;

      if (m_etype == ::e_type_null)
      {

         time = timeDefault;

      }
      else if (is_integer())
      {

         time.m_iSecond = as_long_long();

      }
      else if (is_floating())
      {

         auto f = double();

         time.m_iSecond = (long long)floor(f);
         time.m_iNanosecond = (long long)(fmod(f, 1.0) * 1'000'000'000.0);

      }
      else 
      {

         time = timeDefault;

      }

      return time;

   }
   else
   {

      return m_time;

   }

}




string payload::as_string(const ::scoped_string & scopedstrOnNull) const
{

/*   if(m_etype == e_type_payload_pointer)
   {
      return m_ppayload->as_string(scopedstrOnNull);
   }
   else if (m_etype == e_type_property)
   {
      return m_pproperty->as_string(scopedstrOnNull);
   }
   else*/ if(m_etype == e_type_pstring)
   {
      return *m_pstr;
   }
   else if (m_etype == e_type_path)
   {
      return *m_ppath;
   }
   else if(m_etype != e_type_string)
   {

      ::string str;

      if(m_etype == ::e_type_null)
      {

         str = scopedstrOnNull;

      }
      else if(m_etype == ::e_type_int)
      {

         str = ::as_string(m_i);

      }
      else if(m_etype == ::e_type_unsigned_int)
      {

         str = ::as_string( m_ui);

      }
      else if(m_etype == ::e_type_long_long)
      {

         str = i64toa_dup(m_hi);

      }
      else if(m_etype == ::e_type_unsigned_long_long)
      {

         str = ::as_string(m_hn);

      }
      else if(m_etype == ::e_type_double)
      {

         str = ::as_string(m_d);

      }
      else if(m_etype == ::e_type_atom)
      {

         str = m_atomPayload;

      }
      else if(m_etype == ::e_type_patom)
      {

         str = *m_patom;

      }
      else if(m_etype == ::e_type_string_array)
      {

         str = as_string_array().implode("");

      }
      else if(m_etype == ::e_type_bool)
      {

         str = ::as_string((int)m_b);

      }
      //else if (m_etype == ::e_type_payload_pointer)
      //{

      //   str = m_ppayload->get_network_payload();

      //}
      else if (m_etype == ::e_type_property_set)
      {

         str = m_ppropertyset->get_network_payload();

      }
      //else if (m_etype == ::e_type_property)
      //{

      //   str = m_ppropertyset->get_network_payload();

      //}
      else if (m_etype == ::e_type_ansi_range)
      {

         str.assign(m_ansirange.data(), m_ansirange.size());

      }
      else if (is_element_set())
      {
         
         copy(str, *as_subparticle());

      }

      return str;

   }
   else
   {

      return m_str;

   }

}


//string & payload::get_string(const ::scoped_string & scopedstrOnNull)
string & payload::string_reference()
{

   if(m_etype == e_type_string)
   {

      return m_str;

   }
   //else if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->string_reference();

   //}
   //else if (m_etype == e_type_property)
   //{

   //   return m_pproperty->string_reference();

   //}
   else if(m_etype == e_type_pstring)
   {

      return *m_pstr;

   }
   else
   {

      ::string str = this->as_string();

      set_string(str);

      return m_str;

   }

}


//const string & payload::get_ref_string(const ::scoped_string & scopedstrOnNull) const
//{
//
//   return ((::payload *)this)->get_ref_string(scopedstrOnNull);
//
//}


::atom payload::as_atom() const
{

   return this->as_atom({});

}


::atom payload::as_atom(const ::atom & idDefault) const
{

/*   if(m_etype == e_type_payload_pointer)
   {

      return m_ppayload->as_atom(idDefault);

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->as_atom(idDefault);

   }
   else*/ if(m_etype == e_type_patom)
   {

      return *m_patom;

   }
   else if(m_etype != e_type_atom)
   {

      ::atom atom;

      if (m_etype == ::e_type_char)
      {

         atom = (::collection::index) m_ch;

      }
      else if (m_etype == ::e_type_unsigned_char)
      {

         atom = (::collection::index)m_uch;

      }
      else if (m_etype == ::e_type_short)
      {

         atom = (::collection::index)m_ch;

      }
      else if (m_etype == ::e_type_unsigned_short)
      {

         atom = (::collection::index)m_uch;

      }
      else if(m_etype == ::e_type_int)
      {
         
         atom = m_i;

      }
      else if (m_etype == ::e_type_unsigned_int)
      {

         atom = (::collection::index) m_ui;

      }
      else if(m_etype == ::e_type_long_long)
      {

         atom = (::collection::index) m_hi;

      }
      else if(m_etype == ::e_type_unsigned_long_long)
      {

         atom = (::collection::index) m_hn;

      }
      else if (m_etype == ::e_type_float)
      {

         ::string str;

         str.formatf("%f", m_f);

         atom = str;

      }
      else if(m_etype == ::e_type_double)
      {

         ::string str;

         str.formatf("%f", m_d);

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

      return m_atomPayload;

   }

}


::atom & payload::atom_reference()
{

/*   if(m_etype == e_type_payload_pointer)
   {

      return m_ppayload->atom_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->atom_reference();

   }
   else*/ if(m_etype == e_type_patom)
   {

      return *m_patom;

   }
   else
   {

      auto atom = this->as_atom();

      set_type(e_type_atom, false);

      m_atomPayload = ::transfer(atom);

      return m_atomPayload;

   }

}


int payload::as_int(int iDefault) const
{

   switch(m_etype)
   {
   case e_type_null:
      return iDefault;
   case e_type_empty:
      return iDefault;
   case e_type_string:
      return atoi(m_str);
   case e_type_double:
      return (int) m_d;
   case e_type_pchar:
      return (int)*m_pch;
   case e_type_pshort:
      return (int)*m_psh;
   case e_type_pint:
      return (int)*m_pi;
   case e_type_plong_long:
      return (int)*m_pll;
   case e_type_punsigned_char:
      return (int)*m_puch;
   case e_type_punsigned_short:
      return (int)*m_push;
   case e_type_punsigned_int:
      return (int)*m_pui;
   case e_type_punsigned_long_long:
      return (int)*m_pull;
   case e_type_char:
      return (int) m_ch;
   case e_type_short:
      return (int) m_i;
   case e_type_int:
      return m_ui;
   case e_type_long_long:
      return (int) m_hi;
   case e_type_unsigned_char:
      return (int)m_uch;
   case e_type_unsigned_short:
      return (int)m_ush;
   case e_type_unsigned_int:
      return (int)m_ui;
   case e_type_unsigned_long_long:
      return (int) m_hn;
   case e_type_element:
   case e_type_path:
      return iDefault;
   //case e_type_payload_pointer:
   //   return m_ppayload->as_int(iDefault);
   //case e_type_property:
   //   return m_pproperty->as_int(iDefault);
   case e_type_pstring:
      return atoi(*m_pstr);
   case e_type_atom:
   {
      if(!fits_int(m_atomPayload.as_long_long()))
         throw ::exception(error_overflow, "::payload contains atom that does not fit 32 bit integer");
      return (int) (long long) m_atomPayload.as_long_long();
   }
   case e_type_patom:
   {
      if(!fits_int(m_patom->as_long_long()))
         throw ::exception(error_overflow, "::payload contains atom that does not fit 32 bit integer");
      return (int) (long long) m_patom->as_long_long();
   }
   default:
      return iDefault;
   }

}


//
//int & payload::as_int()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_int();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_int();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      int i = this->as_int();
//
//      set_type(e_type_int, false);
//
//      m_i = i;
//
//   }
//
//   return m_i;
//
//}
//


unsigned int payload::as_unsigned_int(unsigned int uiDefault) const
{
   switch(m_etype)
   {
   case e_type_null:
      return uiDefault;
   case e_type_empty:
      return uiDefault;
   case e_type_string:
      return atoi(m_str);
   case e_type_int:
      return m_i;
   case e_type_unsigned_int:
      return (unsigned int) m_ui;
   case e_type_element:
   case e_type_path:
      return (unsigned int) uiDefault;
   case e_type_long_long:
      return (unsigned int)m_hi;
   case e_type_unsigned_long_long:
      return (unsigned int) m_hn;
   //case e_type_payload_pointer:
   //   return m_ppayload->as_unsigned_int(uiDefault);
   //case e_type_property:
   //   return m_pproperty->as_unsigned_int(uiDefault);
   default:
      return uiDefault;
   }
}

//
//unsigned int & payload::as_unsigned_int()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_unsigned_int();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_unsigned_int();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      unsigned int i = this->as_unsigned_int();
//
//      set_type(e_type_unsigned_int, false);
//
//      m_ui = i;
//
//   }
//
//   return m_ui;
//
//}
//
//

long long payload::as_long_long(long long iDefault) const
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
         return ansi_to_long_long(m_str);
      case e_type_char:
         return m_ch;
      case e_type_unsigned_char:
         return m_uch;
      case e_type_short:
         return m_sh;
      case e_type_unsigned_short:
         return m_ush;
      case e_type_int:
         return m_i;
      case e_type_unsigned_int:
         return m_ui;
      case e_type_long_long:
         return m_hi;
      case e_type_unsigned_long_long:
         return m_hn;
      case e_type_atom:
         return m_atomPayload.as_long_long();
      case e_type_pchar:
         if (::is_null(m_pch)) return iDefault;
         return *m_pch;
      case e_type_punsigned_char:
         if (::is_null(m_puch)) return iDefault;
         return *m_puch;
      case e_type_pshort:
         if (::is_null(m_psh)) return iDefault;
         return *m_psh;
      case e_type_punsigned_short:
         if (::is_null(m_push)) return iDefault;
         return *m_push;
      case e_type_pint:
         if (::is_null(m_pi)) return iDefault;
         return *m_pi;
      case e_type_punsigned_int:
         if (::is_null(m_pui)) return iDefault;
         return *m_pui;
      case e_type_plong_long:
         if (::is_null(m_pll)) return iDefault;
         return *m_pll;
      case e_type_punsigned_long_long:
         if (::is_null(m_pull)) return iDefault;
         return *m_pull;
      case e_type_element:
      case e_type_path:
         return iDefault;
      //case e_type_payload_pointer:
      //   return m_ppayload->as_long_long(iDefault);
      //case e_type_property:
      //   return m_pproperty->as_long_long(iDefault);
//      case e_type_enum_command:
//         return m_ecommand;
//      case e_type_enum_status:
//         return m_estatus.m_eenum;
//      case e_type_enum_check:
//         return m_echeck.m_echeck;
//      case e_type_enum_flag:
//         return m_eflag;
      default:
         return iDefault;

      }
   }
   catch (...)
   {

   }

   return iDefault;

}



#if defined(__APPLE__) || defined(__ANDROID__) || defined(RASPBERRYPIOS) || defined(WINDOWS)


long payload::get_long(long lDefault) const
{
   
   return (long) this->as_long_long(lDefault);
   
}


unsigned long payload::get_unsigned_long(unsigned long ulDefault) const
{
   
   return (unsigned long) this->as_unsigned_long_long(ulDefault);
   
}


#endif

//
//long long & payload::as_long_long()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_long_long();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_long_long();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      long long i = this->as_long_long();
//
//      set_type(e_type_long_long, false);
//
//      m_hi = i;
//
//   }
//
//   return m_hi;
//
//}
//
//

unsigned long long payload::as_unsigned_long_long(unsigned long long uiDefault) const
{
   switch(m_etype)
   {
   case e_type_null:
      return uiDefault;
   case e_type_empty:
      return uiDefault;
   case e_type_string:
      return atol(m_str);
   case e_type_int:
      return m_i;
   case e_type_unsigned_int:
      return m_ui;
   case e_type_long_long:
      return m_hi;
   case e_type_unsigned_long_long:
      return m_hn;
   case e_type_float:
      return (unsigned long long) m_f;
   case e_type_double:
      return (unsigned long long) m_d;
   case e_type_element:
   case e_type_path:
      return uiDefault;
   //case e_type_payload_pointer:
   //   return m_ppayload->as_unsigned_long_long(uiDefault);
   //case e_type_property:
   //   return m_pproperty->as_unsigned_long_long(uiDefault);
   default:
      return uiDefault;
   }

}

//
//
//unsigned long long & payload::as_unsigned_long_long()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_unsigned_long_long();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_unsigned_long_long();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      unsigned long long i = this->as_unsigned_long_long();
//
//      set_type(e_type_unsigned_long_long, false);
//
//      m_hn = i;
//
//   }
//
//   return m_hn;
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


bool payload::get_bool() const
{
   
   return is_true();

}


//payload::operator ::enum_check & ()
//{
//
//   if (m_etype != e_type_enum_check)
//   {
//
//      m_echeck = get_bool() ? e_check_checked : e_check_unchecked;
//
//   }
//
//   return m_echeck;
//
//}
//

bool & payload::bool_reference()
{

/*   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->bool_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->bool_reference();

   }
   else*/ if (m_etype != e_type_bool)
   {

      bool b = is_true();

      set_type(e_type_bool, false);

      m_b = b;

   }

   return m_b;

}


bool payload::as_bool() const
{

   return get_bool();

}


char payload::as_char(char iDefault) const
{
   switch (m_etype)
   {
   case e_type_null:
      return iDefault;
   case e_type_empty:
      return iDefault;
   case e_type_int:
      return (char)m_i;
   case e_type_unsigned_int:
      return (char)m_ui;
   case e_type_long_long:
      return (char)m_hi;
   case e_type_unsigned_long_long:
      return (char)m_hn;
   case e_type_float:
      return (char) m_f;
   case e_type_double:
      return (char)m_d;
   case e_type_string:
#if defined(LINUX) || defined(__ANDROID__) || defined(__BSD__)
      return (char)atof(m_str);
#else
      return (char)_atof_l(m_str, ::get_task()->locale()->m_locale);
#endif
   //case e_type_payload_pointer:
   //   return m_ppayload->as_char(iDefault);
   //case e_type_property:
   //   return m_pproperty->as_char(iDefault);
   default:
      return iDefault;
   }

}







unsigned char payload::as_unsigned_char(unsigned char uDefault) const
{
   switch (m_etype)
   {
   case e_type_null:
      return uDefault;
   case e_type_empty:
      return uDefault;
   case e_type_int:
      return (unsigned char)m_i;
   case e_type_unsigned_int:
      return (unsigned char)m_ui;
   case e_type_long_long:
      return (unsigned char)m_hi;
   case e_type_unsigned_long_long:
      return (unsigned char)m_hn;
   case e_type_float:
      return (unsigned char)m_f;
   case e_type_double:
      return (unsigned char)m_d;
   case e_type_string:
#if defined(LINUX) || defined(__ANDROID__) || defined(__BSD__)
      return (unsigned char)atof(m_str);
#else
      return (unsigned char)_atof_l(m_str, ::get_task()->locale()->m_locale);
#endif
   //case e_type_payload_pointer:
   //   return m_ppayload->as_unsigned_char(uDefault);
   //case e_type_property:
   //   return m_pproperty->as_unsigned_char(uDefault);
   default:
      return uDefault;
   }

}


//unsigned char & payload::as_unsigned_char()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_unsigned_char();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_unsigned_char();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      unsigned char i = this->as_unsigned_char();
//
//      set_type(e_type_unsigned_char, false);
//
//      m_uch = i;
//
//   }
//
//   return m_uch;
//
//}



short payload::as_short(short iDefault) const
{
   switch (m_etype)
   {
   case e_type_null:
      return iDefault;
   case e_type_empty:
      return iDefault;
   case e_type_int:
      return (short)m_i;
   case e_type_unsigned_int:
      return (short)m_ui;
   case e_type_long_long:
      return (short)m_hi;
   case e_type_unsigned_long_long:
      return (short)m_hn;
   case e_type_float:
      return (short)m_f;
   case e_type_double:
      return (short)m_d;
   case e_type_string:
#if defined(LINUX) || defined(__ANDROID__) || defined(__BSD__)
      return (short)atof(m_str);
#else
      return (short)_atof_l(m_str, ::get_task()->locale()->m_locale);
#endif
   //case e_type_payload_pointer:
   //   return m_ppayload->as_short(iDefault);
   //case e_type_property:
   //   return m_pproperty->as_short(iDefault);
   default:
      return iDefault;
   }

}



//short & payload::as_short()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_short();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_short();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      short i = this->as_short();
//
//      set_type(e_type_short, false);
//
//      m_sh = i;
//
//   }
//
//   return m_sh;
//
//}



unsigned short payload::as_unsigned_short(unsigned short uDefault) const
{
   switch (m_etype)
   {
   case e_type_null:
      return uDefault;
   case e_type_empty:
      return uDefault;
   case e_type_int:
      return (unsigned short)m_i;
   case e_type_unsigned_int:
      return (unsigned short)m_ui;
   case e_type_long_long:
      return (unsigned short)m_hi;
   case e_type_unsigned_long_long:
      return (unsigned short)m_hn;
   case e_type_float:
      return (unsigned short)m_f;
   case e_type_double:
      return (unsigned short)m_d;
   case e_type_string:
#if defined(LINUX) || defined(__ANDROID__) || defined(__BSD__)
      return (unsigned short)atof(m_str);
#else
      return (unsigned short)_atof_l(m_str, ::get_task()->locale()->m_locale);
#endif
   //case e_type_payload_pointer:
   //   return m_ppayload->as_unsigned_short(uDefault);
   //case e_type_property:
   //   return m_pproperty->as_unsigned_short(uDefault);
   default:
      return uDefault;
   }

}


//
//unsigned short & payload::as_unsigned_short()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_unsigned_short();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_unsigned_short();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      unsigned short i = this->as_unsigned_short();
//
//      set_type(e_type_unsigned_short, false);
//
//      m_ush = i;
//
//   }
//
//   return m_ush;
//
//}
//


float payload::as_float(float fDefault) const
{
   switch(m_etype)
   {
   case e_type_null:
      return fDefault;
   case e_type_empty:
      return fDefault;
   case e_type_int:
      return (float) m_i;
   case e_type_unsigned_int:
      return (float) m_ui;
   case e_type_long_long:
      return (float) m_hi;
   case e_type_unsigned_long_long:
      return (float) m_hn;
   case e_type_float:
      return m_f;
   case e_type_double:
      return (float) m_d;
   case e_type_string:
   #if defined(LINUX) || defined(__ANDROID__) || defined(__BSD__)
      return (float) atof(m_str);
   #else
      return (float) _atof_l(m_str, ::get_task()->locale()->m_locale);
   #endif
   //case e_type_payload_pointer:
   //   return m_ppayload->as_float(fDefault);
   //case e_type_property:
   //   return m_pproperty->as_float(fDefault);
   default:
      return fDefault;
   }

}
//
//float & payload::as_float()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_float();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_float();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      float i = this->as_float();
//
//      set_type(e_type_float, false);
//
//      m_f = i;
//
//   }
//
//   return m_f;
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


double payload::as_double(double dDefault) const
{
   double d;
   if(m_etype == e_type_null)
   {
      return dDefault;
   }
   else if(m_etype == e_type_empty)
   {
      return dDefault;
   }
   else if(m_etype == ::e_type_int)
   {
      d = (double) m_i;
   }
   else if(m_etype == ::e_type_unsigned_int)
   {

      d = (double) m_ui;

   }
   else if(m_etype == ::e_type_long_long)
   {

      d = (double) m_hi;

   }
   else if(m_etype == ::e_type_unsigned_long_long)
   {

      d = (double) m_hn;

   }
   else if(m_etype == ::e_type_float)
   {

      d = (double) m_f;

   }
   else if(m_etype == ::e_type_double)
   {

      d = m_d;

   }
   else if(m_etype == ::e_type_string)
   {

#if defined(LINUX) || defined(__ANDROID__) || defined(__BSD__)

      d = atof(m_str);

#else
      
      auto ptask = ::get_task();
      
      ::locale * plocale = nullptr;
      
      if(ptask)
      {
         
         plocale = ::get_task()->locale();
         
      }
      
      if(plocale)
      {
         
         d = _atof_l(m_str, plocale->m_locale);
         
      }
      else
      {
         
         d = atof(m_str);
      
      }

#endif

   }
   //else if(m_etype == ::e_type_payload_pointer)
   //{

   //   d = m_ppayload->as_double(dDefault);

   //}
   //else if (m_etype == ::e_type_property)
   //{

   //   d = m_pproperty->as_double(dDefault);

   //}
   else
   {

      return dDefault;

   }

   return d;

}

//
//double & payload::as_double()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_double();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_double();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      double i = this->as_double();
//
//      set_type(e_type_double, false);
//
//      m_d = i;
//
//   }
//
//   return m_d;
//
//}
//


::color::color payload::as_color(const ::color::color & colorDefault) const
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


::color::hls payload::as_hls(const ::color::hls & hlsDefault) const
{

   color::hls hls;

   if(m_etype == e_type_color)
   {

      hls = m_color.get_hls();

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

/*   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->memory_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->memory_reference();

   }
   else*/ if(m_etype != e_type_memory)
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


::memory payload::as_memory() const
{

   if (m_etype != e_type_memory)
   {

      return {};

   }

   return *m_pmemory;

}


::file::path & payload::file_path_reference()
{

/*   if (m_etype == ::e_type_payload_pointer)
   {

      return m_ppayload->file_path_reference();

   }
   else if (m_etype == ::e_type_property)
   {

      return m_pproperty->file_path_reference();

   }
   else*/ if (m_etype != ::e_type_path)
   {

      auto ppath = __new__prefix(&m_preferer) new ::file::path_object();

      ppath->assign_range(as_file_path());

      set_type(e_type_path, false);

      m_ppath = ppath;

   }

   return *m_ppath;

}


//payload::file_path() const
//{
//
//   return get_file_path();
//
//}


string_array_base payload::as_string_array() const
{

/*   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->as_string_array();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->as_string_array();

   }
   else*/ 
   if (m_etype != e_type_string_array)
   {

      string_array_base stra;

      if (m_etype == e_type_string)
      {

         stra.add(as_string());

      }
      else if (m_etype == e_type_key_exists)
      {

         stra.add({});

      }
      else
      {

         try
         {

            auto c = array_get_count();

            for (::collection::index i = 0; i < c; i++)
            {

               stra.add(at(i).as_string());

            }

         }
         catch (...)
         {

         }

      }
      //set_type(e_type_string_array, false);

      //m_pstra = pstra;

      return ::transfer(stra);

   }
   else if (::is_null(m_pstra))
   {

      //m_pstra = ___new string_array_base();

      return {};

   }

   return *m_pstra;

}


string_array_base & payload::string_array_reference()
{

/*   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->string_array_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->string_array_reference();

   }
   else*/ if (m_etype != e_type_string_array)
   {


#if REFERENCING_DEBUGGING

      ::reference_referer* prefererNew = nullptr;

#endif

      auto pstra = __new__prefix(&prefererNew) new string_array();

      try
      {

         auto c = array_get_count();

         for (::collection::index i = 0; i < c; i++)
         {

            pstra->add(at(i).as_string());

         }

      }
      catch (...)
      {

      }

      set_type(e_type_string_array, false);

#if REFERENCING_DEBUGGING

      m_preferer = prefererNew;

#endif

      m_pstra = pstra;

   }
   else if(::is_null(m_pstra))
   {

      m_pstra = __new__prefix(&m_preferer) new string_array();

   }

   return *m_pstra;

}


::int_array_base payload::as_int_array() const
{

/*   if (m_etype == e_type_payload_pointer)
   {

      return ::transfer(m_ppayload->as_int_array());

   }
   else if (m_etype == e_type_property)
   {

      return ::transfer(m_pproperty->as_int_array());

   }
   else*/ if (m_etype != e_type_int_array)
   {

      ::int_array_base ia;

      try
      {

         auto c = array_get_count();

         for (::collection::index i = 0; i < c; i++)
         {

            ia.add(at(i).as_int());

         }

      }
      catch (...)
      {

      }

      return ::transfer(ia);

   }
   else if (::is_null(m_pia))
   {

      return {};

   }

   return *m_pia;

}


int_array_base & payload::int_array_reference()
{

/*   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->int_array_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->int_array_reference();

   }
   else*/ if(m_etype != e_type_int_array)
   {

      auto pia = __new__prefix(&m_preferer) new ::int_array();

      try
      {

         auto c = array_get_count();

         for(::collection::index i = 0; i < c; i++)
         {

            pia->add(at(i).as_int());

         }

      }
      catch(...)
      {

      }

      set_type(e_type_int_array, false);

      m_pia = pia;

   }
   else if (::is_null(m_pia))
   {

      m_pia = __new__prefix(&m_preferer) new ::int_array();

   }

   return *m_pia;

}


long_long_array_base payload::as_long_long_array() const
{

/*   if (m_etype == e_type_payload_pointer)
   {

      return ::transfer(m_ppayload->as_long_long_array());

   }
   else if (m_etype == e_type_property)
   {

      return ::transfer(m_pproperty->as_long_long_array());

   }
   else*/ if (m_etype != e_type_long_long_array)
   {

      long_long_array_base i64a;

      try
      {

         auto c = array_get_count();

         for (::collection::index i = 0; i < c; i++)
         {

            i64a.add(at(i).as_long_long());

         }

      }
      catch (...)
      {

      }

      //set_type(e_type_long_long_array, false);

      //m_plonglonga = pia64;

      return ::transfer(i64a);

   }
   else if (::is_null(m_plonglonga))
   {

      //m_plonglonga = ___new long_long_array_base();
      return {};

   }

   return *m_plonglonga;

}


::long_long_array_base & payload::long_long_array_reference()
{

/*   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->long_long_array_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->long_long_array_reference();

   }
   else*/ if(m_etype != e_type_long_long_array)
   {

      auto pia64  = ___new long_long_array();

      try
      {

         auto c = array_get_count();

         for (::collection::index i = 0; i < c; i++)
         {

            pia64->add(at(i).as_long_long());

         }

      }
      catch (...)
      {

      }

      set_type(e_type_long_long_array, false);

      m_plonglonga = pia64;

   }
   else if(::is_null(m_plonglonga))
   {

      m_plonglonga = ___new long_long_array();

   }

   return *m_plonglonga;

}


::float_array_base payload::as_float_array() const
{

   /*   if (m_etype == e_type_payload_pointer)
      {

         return ::transfer(m_ppayload->as_int_array());

      }
      else if (m_etype == e_type_property)
      {

         return ::transfer(m_pproperty->as_int_array());

      }
      else*/ if (m_etype != e_type_float_array)
      {

         ::float_array_base floata;

         try
         {

            auto c = array_get_count();

            for (::collection::index i = 0; i < c; i++)
            {

               floata.add(at(i).as_int());

            }

         }
         catch (...)
         {

         }

         return ::transfer(floata);

      }
      else if (::is_null(m_pfloata))
      {

         return {};

      }

      return *m_pfloata;

}


float_array_base& payload::float_array_reference()
{

   /*   if (m_etype == e_type_payload_pointer)
      {

         return m_ppayload->int_array_reference();

      }
      else if (m_etype == e_type_property)
      {

         return m_pproperty->int_array_reference();

      }
      else*/ if (m_etype != e_type_float_array)
      {

         auto pfloata = __new__prefix(&m_preferer) new ::float_array();

         try
         {

            auto c = array_get_count();

            for (::collection::index i = 0; i < c; i++)
            {

               pfloata->add(at(i).as_float());

            }

         }
         catch (...)
         {

         }

         set_type(e_type_float_array, false);

         m_pfloata = pfloata;

      }
      else if (::is_null(m_pfloata))
      {

         m_pfloata = __new__prefix(&m_preferer) new ::float_array();

      }

      return *m_pfloata;

}



::double_array_base payload::as_double_array() const
{

   /*   if (m_etype == e_type_payload_pointer)
      {

         return ::transfer(m_ppayload->as_int_array());

      }
      else if (m_etype == e_type_property)
      {

         return ::transfer(m_pproperty->as_int_array());

      }
      else*/ if (m_etype != e_type_double_array)
      {

         ::double_array_base doublea;

         try
         {

            auto c = array_get_count();

            for (::collection::index i = 0; i < c; i++)
            {

               doublea.add(at(i).as_double());

            }

         }
         catch (...)
         {

         }

         return ::transfer(doublea);

      }
      else if (::is_null(m_pdoublea))
      {

         return {};

      }

      return *m_pdoublea;

}


double_array_base& payload::double_array_reference()
{

   /*   if (m_etype == e_type_payload_pointer)
      {

         return m_ppayload->int_array_reference();

      }
      else if (m_etype == e_type_property)
      {

         return m_pproperty->int_array_reference();

      }
      else*/ if (m_etype != e_type_double_array)
      {

         auto pdoublea = __new__prefix(&m_preferer) new ::double_array();

         try
         {

            auto c = array_get_count();

            for (::collection::index i = 0; i < c; i++)
            {

               pdoublea->add(at(i).as_double());

            }

         }
         catch (...)
         {

         }

         set_type(e_type_double_array, false);

         m_pdoublea = pdoublea;

      }
      else if (::is_null(m_pdoublea))
      {

         m_pdoublea = __new__prefix(&m_preferer) new ::double_array();

      }

      return *m_pdoublea;

}



class ::time payload::as_time() const
{

/*   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->as_time();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->as_time();

   }
   else */   if (m_etype == e_type_time)
   {

      return m_time;

   }
   else if (m_etype == e_type_ptime)
   {

      return *m_ptime;

   }
   else if(is_integer())
   {

      return second_time(as_long_long());

   }
   else if (is_floating())
   {

      return second_time(as_double());

   }
   else
   {

      return second_time(as_double());

   }

}


class ::time & payload::time_reference()
{

/*   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->time_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->time_reference();

   }
   else*/ if (m_etype == e_type_time)
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


::file_time & payload::file_time_reference()
{

   //if (m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->file_time_reference();

   //}
   //else if (m_etype == e_type_property)
   //{

   //   return m_pproperty->file_time_reference();

   //}
   //else
   {

      if (m_etype != e_type_file_time)
      {

         set_type(e_type_file_time);

      }

      return *(::file_time *)&m_filetime;

   }

}


::color::color & payload::color_reference()
{

   //if (m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->color_reference();

   //}
   //else if (m_etype == e_type_property)
   //{

   //   return m_pproperty->color_reference();

   //}
   //else
   {

      if (m_etype != e_type_color)
      {

         set_type(e_type_color);

      }

      return m_color;

   }

}


::color::hls & payload::color_hls_reference()
{

   //if (m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->color_hls_reference();

   //}
   //else if (m_etype == e_type_property)
   //{

   //   return m_pproperty->color_hls_reference();

   //}
   //else
   {

      if (m_etype != e_type_hls)
      {

         set_type(e_type_hls);

      }

      return m_hls;

   }

}


//class ::payload & payload::operator = (::payload * ppayload)
//{
//
//   if (m_ppayload == ppayload)
//   {
//
//      return *this;
//
//   }
//
//   set_type(e_type_payload_pointer, false);
//
//   m_ppayload = ppayload;
//
//   return *this;
//
//}


//class ::payload & payload::operator = (const ::payload * pvar)
//{
//
//   return operator =((::payload*)pvar);
//
//}
//

payload_array payload::as_payload_array() const
{

/*   if (m_etype == e_type_payload_pointer)
   {

      return ::transfer(m_ppayload->as_payload_array());

   }
   else if (m_etype == e_type_property)
   {

      return ::transfer(m_pproperty->as_payload_array());

   }
   else*/ if (m_etype != e_type_payload_array)
   {

      payload_array payloada;

      try
      {

         if (is_empty() || !get_bool())
         {

         }
         else
         {

            for (int i = 0; i < array_get_count(); i++)
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

      return ::transfer(payloada);

   }
   else if (::is_null(m_ppayloada))
   {

      //m_ppayloada = ___new payload_array();

      return {};

   }

   return *m_ppayloada;

}


payload_array & payload::payload_array_reference ()
{

/*   if(m_etype == e_type_payload_pointer)
   {

      return m_ppayload->payload_array_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->payload_array_reference();

   }
   else*/ if(m_etype != e_type_payload_array)
   {

      auto pvara  = __new__prefix(&m_preferer) new payload_array();

      try
      {

         if (is_empty() || !get_bool())
         {

         }
         else
         {

            for (int i = 0; i < array_get_count(); i++)
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

      m_ppayloada = __new__prefix(&m_preferer) new payload_array();

   }

   return *m_ppayloada;

}


::property_set payload::as_property_set() const
{

/*   if (m_etype == e_type_payload_pointer)
   {

      return ::transfer(m_ppayload->as_property_set());

   }
   else if (m_etype == e_type_property)
   {

      return ::transfer(m_pproperty->as_property_set());

   }
   else*/ if (m_etype != e_type_property_set)
   {

      ::property_set set;

      if (is_empty() || !get_bool())
      {

      }
      else
      {

         for (int i = 0; i < array_get_count(); i++)
         {

            set.set_at(i, at(i));

         }

      }

      //set_type(e_type_property_set, false);

      //m_ppropertyset = pset;

      return ::transfer(set);

   }
   else if (::is_null(m_ppropertyset))
   {
      //m_ppropertyset = ___new ::property_set();

      return {};

   }

   return *m_ppropertyset;

}


::property_set & payload::property_set_reference()
{

/*   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->property_set_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->property_set_reference();

   }
   else*/ if (m_etype != e_type_property_set)
   {

      __check_refdbg

//#if REFERENCING_DEBUGGING
//
//      auto prefererNew = ::allocator::defer_add_referer({ this, __FUNCTION_FILE_LINE__ });
//
//#endif

      //auto psetNew = __raw_new ::property_set();

#if REFERENCING_DEBUGGING

      ::reference_referer* prefererNew = nullptr;

#endif

      auto psetNew = __new__prefix(&prefererNew) new ::property_set();

      __check_refdbg

      if (is_empty() || !get_bool())
      {

      }
      else if(is_array())
      {

         for (int i = 0; i < array_get_count(); i++)
         {

            psetNew->set_at(i, at(i));

         }

      }
      else
      {

         psetNew->set_at(0, *this);

      }

      set_type(e_type_property_set, false);

#if REFERENCING_DEBUGGING

      m_preferer = prefererNew;

#endif

      m_ppropertyset = psetNew;

   }
   else if (::is_null(m_ppropertyset))
   {

//#if REFERENCING_DEBUGGING
//
//      m_preferer = ::allocator::defer_add_referer({ this, __FUNCTION_FILE_LINE__ });
//
//#endif

      m_ppropertyset = __new__prefix(&m_preferer) new ::property_set();

   }

   return *m_ppropertyset;

}


//const payload_array & payload::as_payloada() const
//{
//
//   return ((::payload *)this)->payloada();
//
//}


//const class ::time & payload::as_time() const
//{
//
//   return ((::payload *)this)->time();
//
//}


//const ::property_set & payload::as_propset() const
//{
//
//   return ((::payload *)this)->propset();
//
//}


//::property payload::as_property() const
//{
//
//
//   //if (m_etype == e_type_payload_pointer)
//   //{
//
//   //   return ::transfer(m_ppayload->as_property());
//
//   //}
//   //else if (m_etype != e_type_property)
//   //{
//
//   //   throw ::exception(error_wrong_state, "::payload is not a property (1)");
//
//   //}
//
//   return *m_pproperty;
//
//}


//property & payload::property_reference ()
//{
//
//   //if (m_etype == e_type_payload_pointer)
//   //{
//
//   //   return m_ppayload->property_reference();
//
//   //}
//   //else if (m_etype == e_type_property)
//   //{
//
//   //   return m_pproperty->property_reference();
//
//   //}
//   if(m_etype != e_type_property)
//   {
//
//      throw ::exception(error_wrong_state, "::payload is not a property (1)");
//
//   }
//
//   return *m_pproperty;
//
//}
//

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

      return as_property_set().implode(scopedstrGlue);

   }
   else if(get_type() == e_type_payload_array)
   {

      return as_payload_array().implode(scopedstrGlue);

   }
   else if(get_type() == e_type_string_array)
   {

      return as_string_array().implode(scopedstrGlue);

   }

   return {};

}


::payload payload::explode(const ::scoped_string & scopedstrGlue, bool bAddEmpty) const
{

   class ::payload payload;

   payload.as_string_array().add_tokens(*this, scopedstrGlue, bAddEmpty);

   return payload;

}



//
//::comparison::var_strict payload::strictly_compare() const
//{
//
//   return *this;
//
//}


::payload payload::dereference()
{
/*   if(get_type() == e_type_payload_pointer)
      return m_ppayload->dereference();
   else if (get_type() == e_type_property)
      return m_pproperty->dereference();
   else*/ if(get_type() == e_type_pstring)
      return *m_pstr;
   else if(get_type() == e_type_int)
      return *m_pi;
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
//   case e_type_int_array:
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


//
//
//
//
//property * payload::find_property_index(::iptr i) const
//{
//
//
//
//property & payload::get_property_index(::iptr i)
//{
//
//   return propset().get(i);
//
//}


//
//property * payload::find_property(const_char_pointer psz) const
//{
//
//   if (!casts_to(e_type_property_set))
//   {
//
//      return nullptr;
//
//   }
//
//   return propset().find(scopedstr);
//
//}
//


::payload payload::find_property_by_text(const ::scoped_string& scopedstr) const
{
   //
   ///*   if (m_etype == e_type_payload_pointer)
   //   {
   //
   //      return m_ppayload->find_property_by_text(scopedstr);
   //
   //   }
   //   else if (m_etype == e_type_property)
   //   {
   //
   //      return m_pproperty->find_property_by_text(scopedstr);
   //
   //   }
   //   else */
   //   //{

   if (m_etype == e_type_property_set)
   {

      auto iIndex = m_ppropertyset->index_of_string(scopedstr);

      if (iIndex >= 0)
      {

         return m_ppropertyset->property_at(iIndex);

      }

   }

   return e_type_new;

}


::payload payload::find_property(const ::atom & atom) const
{

   if (atom.is_text())
   {

/*      if (m_etype == e_type_payload_pointer)
      {

         return m_ppayload->find_property_by_text(atom.m_str);

      }
      else if (m_etype == e_type_property)
      {

         return m_pproperty->find_property_by_text(atom.m_str);

      }
      else*/
      
      if (m_etype == e_type_property_set)
      {

         auto pproperty = m_ppropertyset->find(atom);

         if (pproperty)
         {

            return *pproperty;

         }

      }

      return e_type_new;

   }
   else
   {

      if (casts_to(e_type_property_set))
      {

         auto pproperty = property_set_reference().find(atom);

         if (pproperty)
         {

            return *pproperty;

         }

      }
      else if (this->is_array())
      {

         return this->at(atom.as_iptr());

      }

      return e_type_new;

   }


}


property & payload::get_property(const ::atom & atom)
{

   if (atom.is_text())
   {

/*      if (m_etype == e_type_payload_pointer)
      {

         return m_ppayload->get_property(atom);

      }
      else if (m_etype == e_type_property)
      {

         return m_pproperty->get_property(atom);

      }
      else*/ if (m_etype == e_type_property_set)
      {

         return m_ppropertyset->property(atom);

      }

   }
   else
   {

      if (casts_to(e_type_property_set))
      {

         return property_set_reference().property(atom);

      }

   }

   auto& propertyset = property_set_reference();

   auto iNew = propertyset.add_property(atom);

   return propertyset.property_at(iNew);

}


//::payload payload::operator[] (const ::atom & atom) 
//{ 
//
///*   if (m_etype == ::e_type_payload_pointer)
//   {
//    
//      return m_ppayload->operator[](atom);
//      
//   }  
//   else if (m_etype == ::e_type_property) 
//   { 
//     
//      return m_pproperty->operator[](atom);
//      
//   }
//   else*/ if (atom.is_integer())
//   {
//
//      if (is_array())
//      {
//
//         return at(atom.as_index());
//
//      }
//      else if (is_text())
//      {
//
//         return as_string()[atom.as_index()];
//
//      }
//      else
//      {
//
//         return property_set_reference()[atom];
//
//      }
//
//   }
//   else
//   {
//
//      return property_set_reference()[atom];
//
//   }
//
//}
//
//
//::payload payload::operator[] (const ::atom & atom) const
//{
//
///*   if (m_etype == ::e_type_payload_pointer)
//   {
//
//      return m_ppayload->operator[](atom);
//
//   }
//   else if (m_etype == ::e_type_property)
//   {
//
//      return m_pproperty->operator[](atom);
//
//   }
//   else*/ if (m_etype == ::e_type_property_set)
//   {
//
//      return find_property(atom);
//
//   }
//   else if (atom.is_integer())
//   {
//
//      if (is_array())
//      {
//
//         return at(atom.as_index());
//
//      }
//      else if (is_text())
//      {
//
//         return as_string()[atom.as_index()];
//
//      }
//      else
//      {
//
//         return e_type_new;
//
//      }
//
//
//   }
//   else
//   {
//
//      return e_type_new;
//
//   }
//
//}


::collection::index payload::index_of(const ::atom & atom) const
{

/*   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->index_of(atom);

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->index_of(atom);

   }
   else*/ if (m_etype == e_type_property_set)
   {

      return m_ppropertyset->index_of(atom);

   }

   return -1;

}


::payload payload::at(::collection::index i)
{
   switch(m_etype)
   {
   case e_type_int_array:
      return &m_pia->element_at(i);
   case e_type_float_array:
      return &m_pfloata->element_at(i);
   case e_type_long_long_array:
      return &m_plonglonga->element_at(i);
   case e_type_double_array:
      return &m_pdoublea->element_at(i);
   case e_type_string_array:
      return &m_pstra->element_at(i);
   case e_type_payload_array:
      return m_ppayloada->element_at(i);
   case e_type_property_set:
      return m_ppropertyset->property_at(i);
   //case e_type_payload_pointer:
   //   return m_ppayload->at(i);
   //case e_type_property:
   //   return m_pproperty->at(i);
   default:
      if(i == 0)
      {
         return *this;
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
   case e_type_int_array:
      return as_int_array().contains(atoi(scopedstr), find, count);
   case e_type_string_array:
      return as_string_array().contains(scopedstr, find, count);
   case e_type_payload_array:
      return as_payload_array().contains(scopedstr, find, count);
   case e_type_property_set:
      return as_property_set().contains_payload_count(scopedstr, find, count);
   default:
   {
      ::collection::index upperbound = minimum(array_get_upper_bound(), find + count - 1);
      for(::collection::index i = find; i <= upperbound; i++)
      {
         if(at(i) == scopedstr)
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
   case e_type_int_array:
      return as_int_array().contains(atoi(scopedstr), find, last);
   case e_type_string_array:
      return as_string_array().case_insensitive_contains(scopedstr, find, last);
   case e_type_payload_array:
      return as_payload_array().case_insensitive_contains(scopedstr, find, last);
   case e_type_property_set:
      return as_property_set().case_insensitive_contains_string_count(scopedstr, find, last);
   default:
   {
      ::collection::index upperbound = minimum(array_get_upper_bound(), last);
      for(::collection::index i = find; i <= upperbound; i++)
      {
         if(at(i).case_insensitive_equals(scopedstr))
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
   if(case_insensitive_equals(scopedstrCompare))
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
   if(case_insensitive_equals(scopedstrCompare))
   {
      return varOnEqual;
   }
   else
   {
      return {};
   }
}



//::payload payload::operator + (const ::scoped_string & scopedstr) const
//{
//
//   ::payload varRet(*this);
//
//   if (varRet.is_floating())
//   {
//
//      if (::str::is_integer(str))
//      {
//
//         varRet += strtod(str, nullptr);
//
//      }
//      else
//      {
//
//         varRet.set_string(varRet.get_string() + str);
//
//      }
//
//   }
//   else if (varRet.is_integer())
//   {
//
//      if (::str::is_integer(str))
//      {
//
//         varRet += ansi_to_long_long(str);
//
//      }
//      else
//      {
//
//         varRet.set_string(varRet.get_string() + str);
//
//      }
//
//   }
//   else
//   {
//
//      varRet.set_string(varRet.get_string() + str);
//
//   }
//
//   return varRet;
//
//}


//::payload payload::operator + (const ::scoped_string & scopedstr) const
//{
//
//   return *this + ::string(scopedstr);
//
//}












//
//
//
//
//::payload payload::operator / (int i) const
//{
//   return as_int() / i;
//}
//
//::payload payload::operator / (unsigned int user) const
//{
//   return as_unsigned_int() / user;
//}
//
//::payload payload::operator / (long long l) const
//{
//   return as_long_long() / l;
//}
//
//::payload payload::operator / (unsigned long long ul) const
//{
//
//   switch(m_etype)
//   {
//   case ::e_type_null:
//      return payload(e_type_null);
//   case ::e_type_empty:
//      return 0.0 / ul; // throws division by zero exception if ul stream zero
//   case ::e_type_int:
//      return m_i / (::collection::index) ul;
//   case ::e_type_unsigned_int:
//      return m_ui / (::uptr) ul;
//   case ::e_type_long_long:
//      return m_hi / (long long) ul;
//   case ::e_type_unsigned_long_long:
//      return m_hn / (unsigned long long) ul;
//   case ::e_type_float:
//      return m_f / (float) ul;
//   case ::e_type_double:
//      return m_d / (double) ul;
//   case ::e_type_string:
//#if defined(LINUX) || defined(__ANDROID__)
//      return atof(m_str) / (double) ul;
//#else
//      return _atof_l(m_str, ::get_task()->locale()->m_locale) / (double) ul;
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
//::payload payload::operator / (double d) const
//{
//   return as_double() / d;
//}
//
//::payload operator / (int i, const class ::payload & payload)
//{
//   return i / payload.as_int();
//}
//
//::payload operator / (unsigned int user, const class ::payload & payload)
//{
//   return user / payload.as_unsigned_int();
//}
//
//::payload operator / (long long l, const class ::payload & payload)
//{
//   return l / payload.as_long_long();
//}
//
//
//::payload operator / (unsigned long long ul, const class ::payload & payload)
//{
//   switch(payload.m_etype)
//   {
//   case ::e_type_null:
//      throw ::exception(::exception("division by zero"));
//   case ::e_type_empty:
//      throw ::exception(::exception("division by zero"));
//   case ::e_type_int:
//      return (iptr) ul / payload.m_i;
//   case ::e_type_unsigned_int:
//      return (uptr) ul / payload.m_ui;
//   case ::e_type_long_long:
//      return (long long) ul / payload.m_hi;
//   case ::e_type_unsigned_long_long:
//      return (unsigned long long) ul / payload.m_hn;
//   case ::e_type_float:
//      return (float) ul / payload.m_f;
//   case ::e_type_double:
//      return (double) ul / payload.m_d;
//   case ::e_type_string:
//#if defined(LINUX) || defined(__ANDROID__)
//      return (double) ul / atof(payload.m_str);
//#else
//      return (double) ul / _atof_l(payload.m_str, ::get_task()->locale()->m_locale);
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
//::payload operator / (double d, const class ::payload & payload)
//{
//   return double / payload.as_double();
//}
//
//
//::payload payload::operator * (int i) const
//{
//   return as_int() * i;
//}
//
//::payload payload::operator * (unsigned int user) const
//{
//   return as_unsigned_int() * user;
//}
//
//::payload payload::operator * (long long l) const
//{
//   return as_long_long() * l;
//}
//
//::payload payload::operator * (unsigned long long ul) const
//{
//   switch(m_etype)
//   {
//   case ::e_type_null:
//      return payload(e_type_null);
//   case ::e_type_empty:
//      return 0.0;
//   case ::e_type_int:
//      return m_i * (::collection::index) ul;
//   case ::e_type_unsigned_int:
//      return m_ui * (::uptr) ul;
//   case ::e_type_long_long:
//      return m_hi * (long long) ul;
//   case ::e_type_unsigned_long_long:
//      return m_hn * (unsigned long long) ul;
//   case ::e_type_float:
//      return m_f * (float) ul;
//   case ::e_type_double:
//      return m_d * (double) ul;
//   case ::e_type_string:
//#if defined(LINUX) || defined(__ANDROID__)
//
//      return atof(m_str) * (double) ul;
//#else
//      return _atof_l(m_str, ::get_task()->locale()->m_locale) * (double) ul;
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
//::payload payload::operator * (double d) const
//{
//   return as_double() * d;
//}
//
//::payload operator * (int i, const class ::payload & payload)
//{
//   return i * payload.as_int();
//}
//
//::payload operator * (unsigned int user, const class ::payload & payload)
//{
//   return user * payload.as_unsigned_int();
//}
//
//::payload operator * (long long l, const class ::payload & payload)
//{
//   return l * payload.as_long_long();
//}
//
//::payload operator * (unsigned long long ul, const class ::payload & payload)
//{
//
//   switch(payload.m_etype)
//   {
//   case ::e_type_null:
//      return ::e_type_null;
//   case ::e_type_empty:
//      return 0;
//   case ::e_type_int:
//      return (iptr) ul * payload.m_i;
//   case ::e_type_unsigned_int:
//      return (uptr) ul * payload.m_ui;
//   case ::e_type_long_long:
//      return (long long) ul * payload.m_hi;
//   case ::e_type_unsigned_long_long:
//      return (unsigned long long) ul * payload.m_hn;
//   case ::e_type_float:
//      return (float) ul * payload.m_f;
//   case ::e_type_double:
//      return (double) ul * payload.m_d;
//   case ::e_type_string:
//#if defined(LINUX) || defined(__ANDROID__)
//      return (double) ul * atof(payload.m_str);
//#else
//      return (double) ul * _atof_l(payload.m_str, ::get_task()->locale()->m_locale);
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
//::payload operator * (double d, const class ::payload & payload)
//{
//   return double * payload.as_double();
//}
//




















//
//class ::payload & payload::operator -= (int i)
//{
//   operator =(*this - i);
//   return *this;
//}
//
//class ::payload & payload::operator -= (unsigned int user)
//{
//   operator =(*this - user);
//   return *this;
//}
//
//class ::payload & payload::operator -= (long long i)
//{
//   operator =(*this - i);
//   return *this;
//}
//
//class ::payload & payload::operator -= (unsigned long long user)
//{
//   operator =(*this - user);
//   return *this;
//}
//
//class ::payload & payload::operator -= (double d)
//{
//   operator =(*this - double);
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
//class ::payload & payload::operator += (int i)
//{
//   operator =(*this + i);
//   return *this;
//}
//
//class ::payload & payload::operator += (unsigned int user)
//{
//   operator =(*this + user);
//   return *this;
//}
//
//class ::payload & payload::operator += (long long i)
//{
//   operator =(*this + i);
//   return *this;
//}
//
//class ::payload & payload::operator += (unsigned long long user)
//{
//   operator =(*this + user);
//   return *this;
//}
//
//class ::payload & payload::operator += (double d)
//{
//   operator =(*this + double);
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
//class ::payload & payload::operator /= (int i)
//{
//   operator =(*this / i);
//   return *this;
//}
//
//class ::payload & payload::operator /= (unsigned int user)
//{
//   operator =(*this / user);
//   return *this;
//}
//
//class ::payload & payload::operator /= (long long i)
//{
//   operator =(*this / i);
//   return *this;
//}
//
//class ::payload & payload::operator /= (unsigned long long user)
//{
//   operator =(*this / user);
//   return *this;
//}
//
//class ::payload & payload::operator /= (double d)
//{
//   operator =(*this / double);
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
//class ::payload & payload::operator *= (int i)
//{
//   operator =(*this * i);
//   return *this;
//}
//
//class ::payload & payload::operator *= (unsigned int user)
//{
//   operator =(*this * user);
//   return *this;
//}
//
//class ::payload & payload::operator *= (long long i)
//{
//   operator =(*this * i);
//   return *this;
//}
//
//class ::payload & payload::operator *= (unsigned long long user)
//{
//   operator =(*this * user);
//   return *this;
//}
//
//class ::payload & payload::operator *= (double d)
//{
//   operator =(*this * double);
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
           || m_etype == e_type_int
           || m_etype == e_type_int
           || m_etype == e_type_unsigned_int
           || m_etype == e_type_bool
           || m_etype == e_type_double)
   {
      return true;
   }
   else if(m_etype == e_type_string_array
           || m_etype == e_type_int_array
           || m_etype == e_type_payload_array
           || m_etype == e_type_property_set)
   {
      return false;
   }
   //else if(m_etype == e_type_property)
   //{
   //   return property().is_scalar();
   //}
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

   if(m_etype == e_type_double || m_etype == e_type_float)
   {

      return true;

   }
   // simple, lazy, slow, and a bit incorrect
   // incorrect because atof and atoi returns partials results even if it
   // encounters non-numerical symbols
   else
   {

      auto str = ::transfer(this->as_string());

//#if defined(LINUX) || defined(__ANDROID__) || defined(FREEBSD) || defined(OPENBSD)
//      if(is_scalar()
//            && (fmod(atof(str), 1.0) == 0.0
//                && fabs(atof(str)) <= pow(2.0, 31.0)))
//#else
//      if(is_scalar()
//            && (fmod(_atof_l(str, ::get_task()->locale()->m_locale), 1.0) == 0.0
//                && fabs(_atof_l(str, ::get_task()->locale()->m_locale)) <= pow(2.0, 31.0)))
//#endif
      {
         str.trim();
         if(str.length() == 0)
            return false;
         else if(str[0] == '+'
                 || str[0] == '-'
                 || ansi_char_isdigit(str[0]))
         {
            int i;
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
      //else
      //{
      //   return false;
      //}
   }

}


bool payload::is_boolean() const
{
   if (m_etype == e_type_double)
   {
      return true;
   }
   return false;
}

bool payload::is_double() const
{
   if(m_etype == e_type_double)
   {
      return true;
   }
   else if(is_floating())
   {

      return true;
      
   }
   else
   {

      return false;

   }

}


bool payload::is_integer() const
{
   if(m_etype == e_type_int || m_etype == e_type_long_long)
   {
      return true;
   }
   // simple, lazy, slow, and a bit incorrect
   // incorrect because atof and atoi returns partials results even if it
   // encounters non-numerical symbols
   else
   {
      
      auto str = ::transfer(this->as_string());

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
      {
         return false;

      }
   }

}


bool payload::is_natural() const
{
   if(m_etype == e_type_unsigned_int || m_etype == e_type_unsigned_long_long)
   {
      return true;
   }
   // simple, lazy, slow, and a bit incorrect
   // incorrect because atof and atoi returns partials results even if it
   // encounters non-numerical symbols
   else
   {
      
      ::string str(::transfer(string()));

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
}


bool payload::is_text() const
{

   if(m_etype == e_type_string || m_etype == e_type_path)
   {

      return true;

   }
   else if(m_etype == e_type_pstring)
   {

      return true;

   }
   //else if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->is_text();

   //}
   //else if(m_etype == e_type_property)
   //{

   //   return m_pproperty->is_text();

   //}
   else
   {

      return false;

   }

}


bool payload::is_fairly_convertible_to_text() const
{

   if(m_etype == e_type_string || m_etype == e_type_path)
   {

      return true;

   }
   else if(m_etype == e_type_pstring)
   {

      return true;

   }
   //else if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->is_text();

   //}
   //else if(m_etype == e_type_property)
   //{

   //   return m_pproperty->is_text();

   //}
   else if(is_number())
   {

      return true;

   }
   else
   {

      return false;

   }

}


bool payload::has_string_reference() const
{

   if (m_etype == e_type_string || m_etype == e_type_path)
   {

      return true;

   }
   else if (m_etype == e_type_pstring)
   {

      return true;

   }
   //else if (m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->has_string_reference();

   //}
   //else if (m_etype == e_type_property)
   //{

   //   return m_pproperty->has_string_reference();

   //}
   else
   {

      return false;

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
//   else if(m_etype == e_type_int || m_etype == e_type_unsigned_int)
//   {
//
//      return m_i != 0;
//
//   }
//   else if (m_etype == e_type_long_long || m_etype == e_type_unsigned_long_long)
//   {
//
//      return m_hi != 0;
//
//   }
//   else if (m_etype == e_type_int || m_etype == e_type_unsigned_int)
//   {
//
//      return m_pi != nullptr && *m_pi != 0;
//
//   }
//   else if (m_etype == e_type_long_long || m_etype == e_type_unsigned_long_long)
//   {
//
//      return m_pll != nullptr && *m_pll != 0;
//
//   }
//   else if(m_etype == e_type_string)
//   {
//
//      return ::acme::is_true(m_str);
//
//   }
//   else if (m_etype == e_type_pstring)
//   {
//
//      return m_pstr != nullptr && ::acme::is_true(*m_pstr);
//
//   }
//   else if (m_etype == e_type_atom)
//   {
//
//      return (m_atomPayload.is_text() && ::acme::is_true(m_atomPayload.m_psz)) || (m_atomPayload.is_integer() && m_atomPayload.m_i != 0);
//
//   }
//   else if (m_etype == e_type_patom)
//   {
//
//      return m_patom != nullptr && ((m_patom->is_text() && ::acme::is_true(m_patom->m_psz)) || (m_patom->is_integer() && m_patom->m_i != 0));
//
//   }
//   else if (m_etype == e_type_int_array)
//   {
//
//      return m_pia != nullptr && (m_pia->get_count() >= 2 || (m_pia->get_count() == 1 && !m_pia->element_at(0)));
//
//   }
//   else if (m_etype == e_type_long_long_array)
//   {
//
//      return m_plonglonga != nullptr && (m_plonglonga->get_count() >= 2 || (m_plonglonga->get_count() == 1 && !m_plonglonga->element_at(0)));
//
//   }
//   else if (m_etype == e_type_string_array)
//   {
//
//      return m_pstra != nullptr && (m_pstra->get_count() >= 2 || (m_pstra->get_count() == 1 && ::acme::is_true(m_pstra->element_at(0))));
//
//   }
//   else if (m_etype == e_type_float)
//   {
//
//      return m_f != 0.0f;
//
//   }
//   else if (m_etype == e_type_double)
//   {
//
//      return m_d != 0.0;
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
//      return m_ppropertyset != nullptr && ::acme::array::every::is_true(m_ppropertyset->values());
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
//   else if (m_etype == e_type_char)
//   {
//
//      return m_ch != '\0';
//
//   }
//   else if (m_etype == e_type_unsigned_char)
//   {
//
//      return m_uch != 0;
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

   auto property = find_property(atom);

   if (property.is_empty())
   {

      return false;

   }

   return property.is_true();

}


bool payload::is_property_false(const ::atom & atom) const
{

   return !is_property_true(atom);

}



bool payload::begins_eat(const ::scoped_string & scopedstrPrefix)
{

   auto str = ::transfer(this->as_string());

   if(!str.begins_eat(scopedstrPrefix))
   {

      return false;

   }

   operator =(str);

   return true;

}


bool payload::ends_eat(const ::scoped_string & scopedstrSuffix)
{

   auto str = ::transfer(this->as_string());

   if(!str.ends_eat(scopedstrSuffix))
   {

      return false;

   }

   operator =(str);

   return true;

}


bool payload::case_insensitive_begins_eat(const ::scoped_string & scopedstrPrefix)
{

   auto str = ::transfer(this->as_string());

   if(!str.case_insensitive_begins_eat(scopedstrPrefix))
   {

      return false;

   }

   operator =(str);

   return true;

}


bool payload::case_insensitive_ends_eat(const ::scoped_string & scopedstrSuffix)
{

   auto str = ::transfer(this->as_string());

   if(!str.case_insensitive_ends_eat(scopedstrSuffix))
   {

      return false;

   }

   operator =(str);

   return true;

}


//::block payload::block () const
//{
//
//   return ((::payload *)this)->operator block ();
//
//}

block payload::as_block () const
{

   if (get_type() != e_type_memory)
   {

      throw ::exception(error_wrong_type);

   }

   return *m_pmemory;

}



::payload payload::get_topic(const ::atom & atom) const
{

   auto property = find_property(atom);

   if(property.is_empty())
   {

      return *this;

   }

   return property;

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
//      return dynamic_cast < const ::property_set * > (m_pointer.m_p)->defer_get(atom);
//   }
//   else if(get_type() == e_type_payload_pointer)
//   {
//      return m_ppayload->defer_get_property(atom);
//   }
//   else if(get_type() == e_type_element)
//   {
//      if(cast < ::property_set >() != nullptr)
//      {
//         return cast < ::property_set >()->defer_get(atom);
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

   return found(index_of(atom));

}


bool payload::is_property_true_or_empty(const ::atom & atom) const
{

   auto property = find_property(atom);

   if(property.is_empty())
   {

      return true;

   }

   return property.is_true_or_empty();

}


//void payload::consume_identifier(::ansi_range & range)
//{
//
//   consume_number(scopedstr, psz + strlen(scopedstr) - 1);
//
//}


void payload::consume_identifier(::ansi_range & range)
{

   range.consume_spaces(0);

   const_char_pointer pszStart = range.m_begin;

   while (ansi_char_isalpha(*range.m_begin) && range.has_character())
   {

      range.m_begin++;

   }

   ::string str(pszStart, range.m_begin - pszStart);

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

}

//
//void payload::consume_number(const_char_pointer &psz)
//{
//
//   consume_number(scopedstr, psz + strlen(scopedstr) - 1);
//
//}

void payload::consume_number(::ansi_range & range)
{
   //bool bSigned = false;
   bool bFloat = false;
   range.consume_spaces(0);
   const_char_pointer pszStart = range.m_begin;
   if(*range.m_begin == '-')
   {
      //bSigned = true;
      range.m_begin++;
   }
   if(*range.m_begin == '.')
   {
      bFloat = true;
      range.m_begin++;
   }
   while(*range.m_begin != '\0' && *range.m_begin >= '0' && *range.m_begin <= '9')
   {
      range.m_begin++;
   }
   if(*range.m_begin == 'e' || *range.m_begin == 'E')
   {
      range.m_begin++;
      bFloat = true;
      if(*range.m_begin == '-')
      {
         //bSigned = true;
         range.m_begin++;
      }
      if(*range.m_begin == '.')
      {
         bFloat = true;
         range.m_begin++;
      }
      while(*range.m_begin != '\0' && *range.m_begin >= '0' && *range.m_begin <= '9')
      {
         range.m_begin++;
      }
      goto end;
   }
   if(*range.m_begin == '.')
   {
      bFloat = true;
      range.m_begin++;
   }
   while(*range.m_begin != '\0' && *range.m_begin >= '0' && *range.m_begin <= '9')
   {
      range.m_begin++;
   }
   if(*range.m_begin == 'e' || *range.m_begin == 'E')
   {
      range.m_begin++;
      bFloat = true;
      if(*range.m_begin == '-')
      {
         //bSigned = true;
         range.m_begin++;
      }
      if(*range.m_begin == '.')
      {
         bFloat = true;
         range.m_begin++;
      }
      while(*range.m_begin != '\0' && *range.m_begin >= '0' && *range.m_begin <= '9')
      {
         range.m_begin++;
      }
      goto end;
   }

end:

   if(range.m_begin == pszStart)
   {

      throw ::parsing_exception("empty string : not a number");

   }

   ::string strNumber(pszStart, range.m_begin - pszStart);

   if(bFloat)
   {

//#if defined(LINUX) || defined(__ANDROID__) || defined(FREEBSD) || defined(OPENBSD)

      double d = atof(strNumber);

      //if (bSigned)
      //{

      //   d = -d;

      //}

//#else

      //double d = _atof_l(strNumber, ::get_task()->locale()->m_locale);

//#endif

      operator = (d);

   }
   else
   {

      long long i = (long long) atoll(strNumber);

      //if (bSigned)
      //{
      //   
      //   i = -i;

      //}

      operator = (i);

   }

   //psz = pszParse;

}


//
//void payload::parse_network_payload(const_char_pointer &pszJson)
//{
//
//   parse_network_payload(scopedstrJson, pszJson + strlen(scopedstrJson) - 1);
//
//}





//void var_skip_identifier(const_char_pointer &psz)
//{
//   var_skip_number(scopedstr, psz + strlen(scopedstr) - 1);
//}


void payload_skip_identifier(::ansi_range & range)
{
   range.consume_spaces(0);
   const_char_pointer pszStart = range.m_begin;
   while (ansi_char_isalpha(*range.m_begin) && range.has_character())
      range.m_begin++;
   character_count iLen = range.m_begin - pszStart;
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
   
   //psz = pszParse;

}



//void var_skip_number(const_char_pointer &psz)
//{
//   var_skip_number(scopedstr, psz + strlen(scopedstr) - 1);
//}

void payload_skip_number(::ansi_range & range)
{

   range.consume_spaces(0);

   const_char_pointer pszStart = range.m_begin;

   if (*range.m_begin == '-')
   {
      range.m_begin++;
   }
   if (*range.m_begin == '.')
   {
      range.m_begin++;
   }
   while (*range.m_begin != '\0' && *range.m_begin >= '0' && *range.m_begin <= '9')
   {
      range.m_begin++;
   }
   if (*range.m_begin == 'e' || *range.m_begin == 'E')
   {
      range.m_begin++;
      if (*range.m_begin == '-')
      {
         range.m_begin++;
      }
      if (*range.m_begin == '.')
      {
         range.m_begin++;
      }
      while (*range.m_begin != '\0' && *range.m_begin >= '0' && *range.m_begin <= '9')
      {
         range.m_begin++;
      }
      goto end;
   }
   if (*range.m_begin == '.')
   {
      range.m_begin++;
   }
   while (*range.m_begin != '\0' && *range.m_begin >= '0' && *range.m_begin <= '9')
   {
      range.m_begin++;
   }
   if (*range.m_begin == 'e' || *range.m_begin == 'E')
   {
      range.m_begin++;
      if (*range.m_begin == '-')
      {
         range.m_begin++;
      }
      if (*range.m_begin == '.')
      {
         range.m_begin++;
      }
      while (*range.m_begin != '\0' && *range.m_begin >= '0' && *range.m_begin <= '9')
      {
         range.m_begin++;
      }
      goto end;
   }
end:
   if (range.m_begin == pszStart)
   {
      throw ::parsing_exception("empty string : not a number");
   }
}


void payload_skip_network_payload(::ansi_range & range)
{

   range.consume_spaces(0);

   if (*range.m_begin == '{')
   {

      property_set_skip_network_payload(range);

   }
   else if (*range.m_begin == '\"')
   {

      range.skip_quoted_value_ex();

   }
   else if (*range.m_begin == '\'')
   {

      range.skip_quoted_value_ex();

   }
   else if (ansi_char_isdigit(*range.m_begin) || *range.m_begin == '-' || *range.m_begin == '.')
   {

      payload_skip_number(range);

   }
   else if (*range.m_begin == '[')
   {

      payload_array_skip_network_payload(range);

   }
   else if (*range.m_begin == ']')
   {

      informationf("");

   }
   else if (*range.m_begin == '\0')
   {

      informationf("");

   }
   else
   {

      payload_skip_identifier(range);

   }

}


//void var_skip_network_payload(const_char_pointer &pszJson)
//{
//   var_skip_network_payload(scopedstrJson, pszJson + strlen(scopedstrJson) - 1);
//}




const_char_pointer payload::parse_network_payload(const ::scoped_string & scopedstrNetworkPayload)
{

   auto range = scopedstrNetworkPayload();

   parse_network_payload(range);

   return range.m_begin;

}


void payload::parse_network_payload(::ansi_range & range)
{

   range.consume_spaces(0);

   if (*range.m_begin == '{')
   {

      property_set_reference().parse_network_payload(range);

   }
   else if (*range.m_begin == '\"')
   {

      ::string str = range.consume_quoted_value_ex();

      if(str.case_insensitive_begins_eat("hls://"))
      {

         string_array_base stra;

         stra.explode(":", str);

         if(stra.get_count() == 3)
         {

            double dH = atof(stra[0]);

            double dL = atof(stra[1]);

            double dS = atof(stra[2]);

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
   else if (ansi_char_isdigit(*range.m_begin) || *range.m_begin == '-' || *range.m_begin == '.')
   {

      consume_number(range);

   }
   else if (*range.m_begin == '[')
   {

      payload_array_reference().parse_network_payload(range);

   }
   else if (*range.m_begin == ']')
   {

      informationf("");

      //pszJson++;

   }
   else if (*range.m_begin == '\0')
   {

      informationf("");

   }
   else
   {

      consume_identifier(range);

   }

}


::enum_type payload::find_network_payload_child(::ansi_range & range, const ::payload & payloadChild)
{

   range.consume_spaces(0);

   if (range.is_empty())
   {
      
      informationf("");

      return ::e_type_new;

   }
   else if (*range.m_begin == '\0')
   {

      informationf("");

      return ::e_type_new;

   }
   else if (*range.m_begin == '{')
   {

      range.consume_spaces(0);

      if (range.is_empty())
      {

         return ::e_type_new;

      }

      range.consume("{");

      range.consume_spaces(0);

      if (*range.m_begin == '}')
      {

         range.m_begin++;

         return ::e_type_new;

      }

      ::atom atom;

      while (true)
      {

         property_parse_network_payload_item(atom, range);

         if (payloadChild.case_insensitive_equals(atom))
         {

            range.consume_spaces(0);

            range.consume(":");

            return ::e_type_property_set;

         }

         property_skip_network_payload_payload(range);

         range.consume_spaces(0);

         if (*range.m_begin == ',')
         {
            range.m_begin++;
            continue;
         }
         else if (*range.m_begin == '}')
         {
            range.m_begin++;
            return ::e_type_new;
         }
         else
         {

            ::string str = "not expected character : ";

            str += range.m_begin;

            throw ::parsing_exception(str);

         }

      }

   }
   else if (*range.m_begin == '\"')
   {
      operator=(range.consume_quoted_value_ex());
      if (*this == payloadChild)
      {
         return ::e_type_string;
      }
      else
      {
         return ::e_type_new;
      }
   }
   else if (ansi_char_isdigit(*range.m_begin) || *range.m_begin == '-' || *range.m_begin== '.')
   {
      consume_number(range);
      if (*this == payloadChild)
      {
         return get_type();
      }
      else
      {
         return ::e_type_new;
      }
   }
   else if (*range.m_begin == '[')
   {
      //range.consume_spaces(0);
      range.consume("[");
      ::enum_type etype = find_network_payload_id(range, payloadChild);
      if (etype == ::e_type_new)
      {

         return ::e_type_new;

      }

      range.consume_spaces(0);

      if (*range.m_begin == ']')
      {
         range.m_begin++;

         return etype;

      }

      return ::e_type_new;

   }
   else if (*range.m_begin == ']')
   {
      informationf("");
      return ::e_type_new;
   }
   else
   {
      consume_identifier(range);
      if (*this==payloadChild)
      {
         return get_type();
      }
      else
      {
         return ::e_type_new;
      }
   }

}


::enum_type payload::find_network_payload_id(::ansi_range & range, const ::payload & payloadChild)
{

   range.consume_spaces(0);

   if (range.is_empty())
   {

      return e_type_new;

   }
   else if (*range.m_begin == '{')
   {

      return ::e_type_new;


   }
   else if (*range.m_begin == '\"')
   {
      operator=(range.consume_quoted_value_ex());
      if (*this == payloadChild)
      {
         return ::e_type_string;
      }
      else
      {
         return ::e_type_new;
      }
   }
   else if (ansi_char_isdigit(*range.m_begin) || *range.m_begin == '-' || *range.m_begin == '.')
   {
      consume_number(range);
      if (*this == payloadChild)
      {
         return get_type();
      }
      else
      {
         return ::e_type_new;
      }
   }
   else if (*range.m_begin == '[')
   {

      return ::e_type_new;

   }
   else if (*range.m_begin == ']')
   {
      return ::e_type_new;
   }
   else if (*range.m_begin == '\0')
   {
      return ::e_type_new;
   }
   else
   {
      consume_identifier(range);
      if (*this == payloadChild)
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

   case e_type_char:
   case e_type_pchar:
   case e_type_unsigned_char:
   case e_type_punsigned_char:
   case e_type_short:
   case e_type_pshort:
   case e_type_unsigned_short:
   case e_type_punsigned_short:
   case e_type_int:
   case e_type_pint:
   case e_type_unsigned_int:
   case e_type_punsigned_int:
   case e_type_long_long:
   case e_type_plong_long:
   case e_type_unsigned_long_long:
   case e_type_punsigned_long_long:
      return true;

   //case e_type_payload_pointer:
   //   return m_ppayload->is_numeric();
   //case e_type_property:
   //   return m_pproperty->is_numeric();


   case e_type_element:
   case e_type_path:
      return false;

   case e_type_bool:
   case e_type_pbool:
   case e_type_key_exists:
      return false;

   case e_type_double:
      return true;

   case e_type_string_array:
   case e_type_int_array:
   case e_type_float_array:
   case e_type_long_long_array:
   case e_type_double_array:
   case e_type_payload_array:
   case e_type_property_set:
   case e_type_memory:
      return false;

   case e_type_time:
   case e_type_file_time:
      return false;

   case e_type_atom:
      return false; // m_atomPayload.is_number(); // may be improved MBI

   case e_type_patom:
      return false; // m_patom->is_number(); // may be improved MBI

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


bool payload::has_reference_of_type(enum_type etype) const
{

/*   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->has_reference_of_type(etype);

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->has_reference_of_type(etype);

   }
   else*/ if (m_etype == etype)
   {

      return true;

   }
   else
   {

      return false;

   }

}


const ::string_array_base & payload::string_array_reference() const
{

   if(m_etype == e_type_string_array)
   {

      return *m_pstra;

   }
   //else if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->string_array_reference();

   //}
   //else if(m_etype == e_type_property)
   //{

   //   return m_pproperty->string_array_reference();

   //}
   else
   {

      throw ::exception(error_unexpected);

   }

}


const ::int_array_base & payload::int_array_reference() const
{

   if(m_etype == e_type_int_array)
   {

      return *m_pia;

   }
   //else if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->int_array_reference();

   //}
   //else if(m_etype == e_type_property)
   //{

   //   return m_pproperty->int_array_reference();

   //}
   //else
   {

      throw ::exception(error_unexpected);

   }

}


const ::long_long_array_base & payload::long_long_array_reference() const
{

   if(m_etype == e_type_long_long_array)
   {

      return *m_plonglonga;

   }
   //else if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->long_long_array_reference();

   //}
   //else if(m_etype == e_type_property)
   //{

   //   return m_pproperty->long_long_array_reference();

   //}
   //else
   {

      throw ::exception(error_unexpected);

   }

}


const ::float_array_base& payload::float_array_reference() const
{

   if (m_etype == e_type_float_array)
   {

      return *m_pfloata;

   }
   //else if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->int_array_reference();

   //}
   //else if(m_etype == e_type_property)
   //{

   //   return m_pproperty->int_array_reference();

   //}
   //else
   {

      throw ::exception(error_unexpected);

   }

}


const ::double_array_base& payload::double_array_reference() const
{

   if (m_etype == e_type_double_array)
   {

      return *m_pdoublea;

   }
   //else if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->long_long_array_reference();

   //}
   //else if(m_etype == e_type_property)
   //{

   //   return m_pproperty->long_long_array_reference();

   //}
   //else
   {

      throw ::exception(error_unexpected);

   }

}

const ::payload_array & payload::payload_array_reference() const
{

   if(m_etype == e_type_payload_array)
   {

      return *m_ppayloada;

   }
   //else if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->payload_array_reference();

   //}
   //else if(m_etype == e_type_property)
   //{

   //   return m_pproperty->payload_array_reference();

   //}
   else
   {

      throw ::exception(error_unexpected);

   }

}


const class ::time & payload::time_reference() const
{

   if(m_etype == e_type_time)
   {

      return m_time;

   }
   //else if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->time_reference();

   //}
   //else if(m_etype == e_type_property)
   //{

   //   return m_pproperty->time_reference();

   //}
   else
   {

      throw ::exception(error_unexpected);

   }

}


const ::property_set & payload::property_set_reference() const
{

   if(m_etype == e_type_property_set)
   {

      return *m_ppropertyset;

   }
   //else if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->property_set_reference();

   //}
   //else if(m_etype == e_type_property)
   //{

   //   return m_pproperty->property_set_reference();

   //}
   else
   {

      throw ::exception(error_unexpected);

   }

}


const ::property & payload::property_reference() const
{

   //if(m_etype == e_type_property)
   //{

   //   return *m_pproperty;

   //}
   //else if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->property_reference();

   //}
   //else
   {

      throw ::exception(error_unexpected);

   }

}


const ::file::path & payload::file_path_reference() const
{

   if(m_etype == e_type_path)
   {

      return *m_ppath;

   }
   //else if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->file_path_reference();

   //}
   //else if(m_etype == e_type_property)
   //{

   //   return m_pproperty->file_path_reference();

   //}
   else
   {

      throw ::exception(error_unexpected);

   }

}


const ::file_time &payload:: file_time_reference() const
{

   if(m_etype == e_type_file_time)
   {

      return *(const ::file_time *) &m_filetime;

   }
   //else if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->file_time_reference();

   //}
   //else if(m_etype == e_type_property)
   //{

   //   return m_pproperty->file_time_reference();

   //}
   else
   {

      throw ::exception(error_unexpected);

   }

}


const ::earth::time & payload::earth_time_reference() const
{

   if(m_etype == e_type_earth_time)
   {

      return m_earthtime;

   }
   //else if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->earth_time_reference();

   //}
   //else if(m_etype == e_type_property)
   //{

   //   return m_pproperty->earth_time_reference();

   //}
   else
   {

      throw ::exception(error_unexpected);

   }

}


const ::color::color & payload::color_reference() const
{

   if(m_etype == e_type_color)
   {

      return m_color;

   }
   //else if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->color_reference();

   //}
   //else if(m_etype == e_type_property)
   //{

   //   return m_pproperty->color_reference();

   //}
   else
   {

      throw ::exception(error_unexpected);

   }

}


const ::color::hls & payload::color_hls_reference() const
{

   if(m_etype == e_type_hls)
   {

      return m_hls;

   }
   //else if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->color_hls_reference();

   //}
   //else if(m_etype == e_type_property)
   //{

   //   return m_pproperty->color_hls_reference();

   //}
   else
   {

      throw ::exception(error_unexpected);

   }

}


bool is_return_ok(para_return eret)
{

   return ((int)eret) >= 0;

}


//::payload str_ends_get(const_char_pointer psz, const_char_pointer pszSuffix)
//{
//
//   string str(pcsz);
//
//   string strSuffix(pcszSuffix);
//
//   character_count iLen = strSuffix.length();
//
//   if(str.right(iLen) == pcszSuffix)
//
//   {
//
//      return str.left(str.length() - iLen);
//
//   }
//
//   return false;
//
//}


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

      return property_set_reference().get_network_payload(str, bNewLine);

   }
   else if (get_type() == ::e_type_string_array)
   {

      return string_array_reference().get_network_payload(str, bNewLine);

   }
   else if (get_type() == ::e_type_int_array)
   {

      return ::get_network_payload(str, *m_pia, bNewLine);

   }
   else if (get_type() == ::e_type_long_long_array)
   {

      return ::get_network_payload(str, *m_plonglonga, bNewLine);

   }
   else if (get_type() == ::e_type_float_array)
   {

      return ::get_network_payload(str, *m_pfloata, bNewLine);

   }
   else if (get_type() == ::e_type_double_array)
   {

      return ::get_network_payload(str, *m_pdoublea, bNewLine);

   }
   else if (get_type() == ::e_type_payload_array)
   {

      return payload_array_reference().get_network_payload(str, bNewLine);

   }
   else if (get_type() == ::e_type_hls)
   {

      ::string strHls;

      strHls.formatf("\"hls://%float:%float:%float\"", m_hls.m_dH, m_hls.m_dL, m_hls.m_dS);

      str += strHls;

      return str;

   }
   else if (is_numeric())
   {

      return str += this->as_string();

   }
   else if (get_type() == ::e_type_bool)
   {

      return str += get_bool() ? "true" : "false";

   }
   else
   {

      auto strValue = ::transfer(this->as_string());

      strValue.replace_with("\\\"", "\"");

      return str += ("\"" + strValue + "\"");

   }

}



void payload::null()
{

   set_type(::e_type_null);

}


::file::path payload::as_file_path() const
{

   if(m_etype == e_type_element)
   {

      auto pfile = cast < ::file::file >();

      if (pfile)
      {

         auto path = pfile->get_file_path();

         return ::transfer(path);

      }

   }

   if(m_etype == e_type_property_set)
   {

      ::file::path path;

      if (has_property("url"))
      {

         path = find_property("url").as_file_path();

      }
      else if(has_property("path"))
      {

         path = find_property("path").as_file_path();

      }

      if (as_property_set().is_true("required"))
      {

         path.flags() |= ::file::e_flag_required;

      }

      if (as_property_set().is_true("nocache"))
      {

         path.flags() |= ::file::e_flag_bypass_cache;

      }

      return ::transfer(path);

   }
   else if (m_etype == e_type_path)
   {

      return (::file::path&)* m_ppath;

   }

   return this->as_string();

}


::url::url payload::as_url() const
{

   auto path = as_file_path();

   return path;

}


::payload & payload::operator |= (enumeration < ::file::enum_flag > eflag)
{

   //if(m_etype == e_type_payload_pointer)
   //{

   //   return m_ppayload->operator |=(eflag);

   //}

   auto pfile = cast < ::file::file > ();

   if (pfile)
   {

      property_set_reference()["file"] = pfile;

   }

   if (m_etype == e_type_property_set)
   {

      if (eflag & ::file::e_flag_required)
      {

         property_set_reference()["required"] = true;

      }

      if (eflag & ::file::e_flag_bypass_cache)
      {

         property_set_reference()["nocache"] = true;

      }

   }
   else if (m_etype == e_type_path)
   {

      auto ppath = cast < ::file::path_object > ();

      if (ppath)
      {

         ppath->flags() |= eflag;

      }

   }
   else
   {

#if REFERENCING_DEBUGGING

      ::reference_referer* prefererNew = nullptr;

#endif

      auto ppath = __new__prefix(&prefererNew) new ::file::path_object(as_file_path());

      ppath->flags() |= eflag;

      set_type(e_type_path, false);

#if REFERENCING_DEBUGGING

      m_preferer = prefererNew;

#endif

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
   case e_type_char:
      return !m_ch;
   case e_type_pchar:
      return !m_pch || !*m_pch;
   case e_type_unsigned_char:
      return !m_uch;
   case e_type_punsigned_char:
      return !m_puch || !*m_puch;
   case e_type_short:
      return !m_sh;
   case e_type_pshort:
      return !m_psh || !*m_psh;
   case e_type_unsigned_short:
      return !m_ush;
   case e_type_punsigned_short:
      return !m_push || !*m_push;
   case e_type_int:
      return !m_i;
   case e_type_pint:
      return !m_pi || !*m_pi;
   case e_type_unsigned_int:
      return !m_ui;
   case e_type_punsigned_int:
      return !m_pui || !*m_pui;
   case e_type_long_long:
      return !m_hi;
   case e_type_plong_long:
      return !m_pll || !*m_pll;
   case e_type_unsigned_long_long:
      return !m_hn;
   case e_type_punsigned_long_long:
      return !m_pull || !*m_pull;

   // floating int_point
   case e_type_pfloat:
      return !*m_pf;
   case e_type_float:
      return !m_f;
   case e_type_pdouble:
      return !*m_pd;
   case e_type_double:
      return !m_d;

   // simple classes
   case e_type_string:
      return m_str.is_empty() || m_str.case_insensitive_order("false") == 0  || m_str.case_insensitive_order("no") == 0 || m_str.case_insensitive_order("0") == 0;
   case e_type_pstring:
      return !m_pstr || m_pstr->is_empty() || m_pstr->case_insensitive_order("false") == 0 || m_pstr->case_insensitive_order("no") == 0 || m_pstr->case_insensitive_order("0") == 0;
   case e_type_type:
      return m_str.is_empty();
   case e_type_time:
      return m_time <= 0_s;
   case e_type_ptime:
      return !m_ptime || *m_ptime <= 0_s;
   case e_type_atom:
      return m_atomPayload.is_empty() || m_atomPayload == 0 || m_atomPayload.case_insensitive_order("false") == 0 || m_atomPayload.case_insensitive_order("no") == 0 || m_atomPayload == "0";
   case e_type_patom:
      return !m_patom || m_patom->is_empty() || *m_patom == 0 || m_patom->case_insensitive_order("false") == 0 || m_patom->case_insensitive_order("no") == 0 || *m_patom == "0";
   case e_type_earth_time:
      return !m_earthtime.m_iSecond;
   case e_type_file_time:
      return !m_filetime.m_uFileTime;
   //case e_type_payload_pointer:
   //   return m_ppayload || !*m_ppayload;
   //case e_type_property:
   //   return m_pproperty || !*m_pproperty;
   //case e_type_routine:
   //      return ::is_null(m_pelementProcedure);
   //case e_type_process:
     //    return !m_process;

   // particle classes
   case e_type_element:
      return is_element_null();
   case e_type_string_array:
      return ::is_null(m_pstra) || m_pstra->is_empty();
   case e_type_int_array:
      return ::is_null(m_pia) || m_pia->is_empty();
   case e_type_float_array:
      return ::is_null(m_pfloata) || m_pfloata->is_empty();
   case e_type_payload_array:
      return ::is_null(m_ppayloada) || m_ppayloada->is_empty();
   case e_type_property_set:
      return ::is_null(m_ppropertyset) || m_ppropertyset->is_empty();
   case e_type_long_long_array:
      return ::is_null(m_plonglonga) || m_plonglonga->is_empty();
   case e_type_double_array:
      return ::is_null(m_pdoublea) || m_pdoublea->is_empty();
   case e_type_memory:
      return ::is_null(m_pmemory) || m_pmemory->is_empty();
   case e_type_path:
      return ::is_null(m_ppath) || m_ppath->is_empty();
   //case type_image:
   //   return m_pimage.ok();

   // enum
   //case e_type_integral_nanosecond:
   //   return !m_integralnanosecond.m_i;
   //case e_type_pintegral_nanosecond:
   //   return !m_pintegralnanosecond || !m_pintegralnanosecond->m_i;
   //   case e_type_integral_microsecond:
   //      return !m_integralmicrosecond.m_i;
   //   case e_type_pintegral_microsecond:
   //      return !m_pintegralmicrosecond || !m_pintegralmicrosecond->m_i;
   //   case e_type_integral_millisecond:
   //      return !m_integralmillisecond.m_i;
   //   case e_type_pintegral_millisecond:
   //      return !m_pintegralmillisecond || !m_pintegralmillisecond->m_i;
   //   case e_type_integral_second:
   //      return !m_integralsecond.m_i;
   //   case e_type_pintegral_second:
   //      return !m_pintegralsecond || !m_pintegralsecond->m_i;
   //   case e_type_integral_minute:
   //      return !m_integralminute.m_i;
   //   case e_type_pintegral_minute:
   //      return !m_pintegralminute || !m_pintegralminute->m_i;
   //   case e_type_integral_hour:
   //      return !m_integralhour.m_i;
   //   case e_type_pintegral_hour:
   //      return !m_pintegralhour || !m_pintegralhour->m_i;
   //   case e_type_integral_day:
   //      return !m_integralday.m_i;
   //   case e_type_pintegral_day:
   //      return !m_pintegralday || !m_pintegralday->m_i;
   //   case e_type_floating_nanosecond:
   //      return !m_fingnanosecond.m_d;
   //   case e_type_pfloating_nanosecond:
   //      return !m_pfloatingnanosecond || !m_pfloatingnanosecond->m_d;
   //      case e_type_floating_microsecond:
   //         return !m_fingmicrosecond.m_d;
   //      case e_type_pfloating_microsecond:
   //         return !m_pfloatingmicrosecond || !m_pfloatingmicrosecond->m_d;
   //      case e_type_floating_millisecond:
   //         return !m_fingmillisecond.m_d;
   //      case e_type_pfloating_millisecond:
   //         return !m_pfloatingmillisecond || !m_pfloatingmillisecond->m_d;
   //      case e_type_floating_second:
   //         return !m_fingsecond.m_d;
   //      case e_type_pfloating_second:
   //         return !m_pfloatingsecond || !m_pfloatingsecond->m_d;
   //      case e_type_floating_minute:
   //         return !m_fingminute.m_d;
   //      case e_type_pfloating_minute:
   //         return !m_pfloatingminute || !m_pfloatingminute->m_d;
   //      case e_type_floating_hour:
   //         return !m_finghour.m_d;
   //      case e_type_pfloating_hour:
   //         return !m_pfloatinghour || !m_pfloatinghour->m_d;
   //      case e_type_floating_day:
   //         return !m_fingday.m_d;
   //      case e_type_pfloating_day:
   //         return !m_pfloatingday || !m_pfloatingday->m_d;
//   case e_type_enum_command:
//   case e_type_enum_status:
//   case e_type_enum_check:
//      case e_type_enum_flag:
//      return !m_hi;
   case e_type_color:
      return !m_color.m_ui;
   case e_type_hls:
      return m_hls.m_dL == 0.0;
   case e_type_last_element:
      return false;
   default:
      throw exception(error_wrong_state);
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
   case e_type_char:
      return !m_ch;
   case e_type_pchar:
      return !m_pch || !*m_pch;
   case e_type_unsigned_char:
      return !m_uch;
   case e_type_punsigned_char:
      return !m_puch || !*m_puch;
   case e_type_short:
      return !m_sh;
   case e_type_pshort:
      return !m_psh || !*m_psh;
   case e_type_unsigned_short:
      return !m_ush;
   case e_type_punsigned_short:
      return !m_push || !*m_push;
   case e_type_int:
      return !m_i;
   case e_type_pint:
      return !m_pi || !*m_pi;
   case e_type_unsigned_int:
      return !m_ui;
   case e_type_punsigned_int:
      return !m_pui || !*m_pui;
   case e_type_long_long:
      return !m_hi;
   case e_type_plong_long:
      return !m_pll || !*m_pll;
   case e_type_unsigned_long_long:
      return !m_hn;
   case e_type_punsigned_long_long:
      return !m_pull || !*m_pull;
   // floating int_point
   case e_type_pfloat:
      return !*m_pf;
   case e_type_float:
      return !m_f;
   case e_type_pdouble:
      return !*m_pd;
   case e_type_double:
      return !m_d;
   // simple classes
   case e_type_string:
      return m_str.is_empty() || m_str.case_insensitive_order("false") == 0 || m_str.case_insensitive_order("no") == 0 || m_str.case_insensitive_order("0") == 0;
   case e_type_pstring:
      return !m_pstr || m_pstr->is_empty() || m_pstr->case_insensitive_order("false") == 0 || m_pstr->case_insensitive_order("no") == 0 || m_pstr->case_insensitive_order("0") == 0;
   case e_type_type:
      return m_str.is_empty();
   case e_type_time:
      return m_time <= 0;
   case e_type_ptime:
      return !m_ptime || *m_ptime <= 0_s;
   case e_type_atom:
      return m_atomPayload.is_empty() || m_atomPayload == 0|| m_atomPayload.case_insensitive_order("false") == 0 || m_atomPayload.case_insensitive_order("no") == 0 || m_atomPayload.case_insensitive_order("0") == 0;
   case e_type_patom:
      return !m_patom || m_patom->is_empty()|| *m_patom == 0 || m_patom->case_insensitive_order("false") == 0 || m_patom->case_insensitive_order("no") == 0 || m_patom->case_insensitive_order("0") == 0;
   case e_type_earth_time:
      return !m_earthtime.m_iSecond;
   case e_type_file_time:
      return !m_filetime.m_uFileTime;
   //case e_type_payload_pointer:
   //   return m_ppayload && m_ppayload->is_set_false();
   //case e_type_property:
   //   return m_pproperty && m_pproperty->is_set_false();
   //case e_type_routine:
   //   return ::is_null(m_pelementProcedure);
   //case type_process:
   //   return !m_process;

      // particle classes
   case e_type_element:
      return is_element_null();
   case e_type_string_array:
      return ::is_null(m_pstra) || m_pstra->is_empty();
   case e_type_int_array:
      return ::is_null(m_pia) || m_pia->is_empty();
   case e_type_float_array:
      return ::is_null(m_pfloata) || m_pfloata->is_empty();
   case e_type_payload_array:
      return ::is_null(m_ppayloada) || m_ppayloada->is_empty();
   case e_type_property_set:
      return ::is_null(m_ppropertyset) || m_ppropertyset->is_empty();
   case e_type_long_long_array:
      return ::is_null(m_plonglonga) || m_plonglonga->is_empty();
   case e_type_double_array:
      return ::is_null(m_pdoublea) || m_pdoublea->is_empty();
   case e_type_memory:
      return ::is_null(m_pmemory) || m_pmemory->is_empty();
   case e_type_path:
      return ::is_null(m_ppath) || m_ppath->is_empty();
   //case type_image:
   //   return m_pimage.ok();

   // enum
      //case e_type_integral_nanosecond:
      //   return !m_integralnanosecond.m_i;
      //case e_type_pintegral_nanosecond:
      //   return !m_pintegralnanosecond || !m_pintegralnanosecond->m_i;
      //   case e_type_integral_microsecond:
      //      return !m_integralmicrosecond.m_i;
      //   case e_type_pintegral_microsecond:
      //      return !m_pintegralmicrosecond || !m_pintegralmicrosecond->m_i;
      //   case e_type_integral_millisecond:
      //      return !m_integralmillisecond.m_i;
      //   case e_type_pintegral_millisecond:
      //      return !m_pintegralmillisecond || !m_pintegralmillisecond->m_i;
      //   case e_type_integral_second:
      //      return !m_integralsecond.m_i;
      //   case e_type_pintegral_second:
      //      return !m_pintegralsecond || !m_pintegralsecond->m_i;
      //   case e_type_integral_minute:
      //      return !m_integralminute.m_i;
      //   case e_type_pintegral_minute:
      //      return !m_pintegralminute || !m_pintegralminute->m_i;
      //   case e_type_integral_hour:
      //      return !m_integralhour.m_i;
      //   case e_type_pintegral_hour:
      //      return !m_pintegralhour || !m_pintegralhour->m_i;
      //   case e_type_integral_day:
      //      return !m_integralday.m_i;
      //   case e_type_pintegral_day:
      //      return !m_pintegralday || !m_pintegralday->m_i;
      //   case e_type_floating_nanosecond:
      //      return !m_fingnanosecond.m_d;
      //   case e_type_pfloating_nanosecond:
      //      return !m_pfloatingnanosecond || !m_pfloatingnanosecond->m_d;
      //      case e_type_floating_microsecond:
      //         return !m_fingmicrosecond.m_d;
      //      case e_type_pfloating_microsecond:
      //         return !m_pfloatingmicrosecond || !m_pfloatingmicrosecond->m_d;
      //      case e_type_floating_millisecond:
      //         return !m_fingmillisecond.m_d;
      //      case e_type_pfloating_millisecond:
      //         return !m_pfloatingmillisecond || !m_pfloatingmillisecond->m_d;
      //      case e_type_floating_second:
      //         return !m_fingsecond.m_d;
      //      case e_type_pfloating_second:
      //         return !m_pfloatingsecond || !m_pfloatingsecond->m_d;
      //      case e_type_floating_minute:
      //         return !m_fingminute.m_d;
      //      case e_type_pfloating_minute:
      //         return !m_pfloatingminute || !m_pfloatingminute->m_d;
      //      case e_type_floating_hour:
      //         return !m_finghour.m_d;
      //      case e_type_pfloating_hour:
      //         return !m_pfloatinghour || !m_pfloatinghour->m_d;
      //      case e_type_floating_day:
      //         return !m_fingday.m_d;
      //      case e_type_pfloating_day:
      //         return !m_pfloatingday || !m_pfloatingday->m_d;
//   case e_type_enum_command:
//   case e_type_enum_status:
//   case e_type_enum_check:
//      case e_type_enum_flag:
//      return !m_hi;
   case e_type_color:
      return !m_color.m_ui;
   case e_type_hls:
      return m_hls.m_dL == 0.0;
   case e_type_last_element:
         return false;
   default:
      throw exception(error_wrong_state);
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
void payload::_001Add(const string_array_base & straParam)
{

   if(straParam.get_count() <= 0)
   {

      return;

   }

   if(straParam.get_count() == 1)
   {

      if(case_insensitive_order(straParam[0]) == 0)
      {

         return;

      }
      else if(is_empty())
      {

         operator = (straParam[0]);

         return;

      }

   }

   string_array_reference().case_insensitive_append_unique(straParam);

}


::payload & payload::operator = (const ::subparticle & o)
{

   _set_element((::subparticle *) &o);

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
      int_rectangle                       m_rectangleRestored = nullptr;
      int_rectangle                       m_rectangleWindow = nullptr;
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


::file_time payload::as_file_time() const
{

/*   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->as_file_time();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->as_file_time();

   }
   else */   if (m_etype == e_type_file_time)
   {

      return m_filetime;

   }
   //else if (m_etype == e_type_pfile_time)
   //{

   //   return *m_ptime;

   //}
   else if (is_integer())
   {

      return { file_time_t{}, as_unsigned_long_long() };

   }
   else if (is_floating())
   {

      return  { file_time_t{}, as_unsigned_long_long() };

   }
   else
   {

      return { file_time_t{},  as_unsigned_long_long() };

   }

}
//
//
//::file_time & payload::file_time_reference()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->file_time_reference();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->file_time_reference();
//
//   }
//   else if (m_etype == e_type_file_time)
//   {
//
//      return m_time;
//
//   }
//   else if (m_etype == e_type_ptime)
//   {
//
//      return *m_ptime;
//
//   }
//   else
//   {
//
//      set_type(e_type_time);
//
//      m_time.set_null();
//
//      return m_time;
//
//   }
//
//}



::earth::time payload::as_earth_time () const
{

   return posix_time{ posix_time_t{}, as_long_long() };

}


::earth::time & payload::earth_time_reference ()
{

/*   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->earth_time_reference();

   }
   else if (m_etype == e_type_property)
   {

      return m_pproperty->earth_time_reference();

   }
   else */
   if (m_etype != e_type_earth_time)
   {

      auto i =as_long_long();

      set_type(e_type_time, false);

      m_earthtime.m_iSecond = i;


   }

   return m_earthtime;

}




//::color::color payload::color() const
//{
//
//   return color();
//
//}


//char & payload::as_char()
//{
//
//   if (m_etype == e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_char();
//
//   }
//   else if (m_etype == e_type_property)
//   {
//
//      return m_pproperty->as_char();
//
//   }
//   else if (m_etype != e_type_bool)
//   {
//
//      char i = this->as_char();
//
//      set_type(e_type_char, false);
//
//      m_ch = i;
//
//   }
//
//   return m_ch;
//
//}


#define IMPLEMENT_PAYLOAD_NUMBER(NUMBER_TYPE, NUMBER_NAME, NUMBER_SHORT_NAME, UPPER_CASE_NAME)             \
NUMBER_TYPE & payload::NUMBER_NAME ## _reference()         \
{                                                        \
                                                         \
/*   if (m_etype == e_type_payload_pointer && m_ppayload != this)                \
   {                                                     \
                                                         \
      return m_ppayload->NUMBER_TYPE ## _reference();        \
                                                         \
   }                                                     \
   else if (m_etype == e_type_property && m_pproperty != this)                  \
   {                                                     \
                                                         \
      return m_pproperty->NUMBER_TYPE ## _reference();       \
                                                         \
   }                                                     \
   else*/ if (m_etype != e_type_ ## NUMBER_NAME)            \
   {                                                     \
                                                         \
      auto number = this->as_ ## NUMBER_NAME();                       \
                                                         \
      set_type(e_type_ ## NUMBER_NAME, false);            \
                                                         \
      m_## NUMBER_SHORT_NAME = number;                          \
                                                         \
   }                                                     \
                                                         \
   return m_ ## NUMBER_SHORT_NAME;                              \
                                                         \
}    
DO_FOR_NUMBER_TYPES(IMPLEMENT_PAYLOAD_NUMBER)
#undef IMPLEMENT_PAYLOAD_NUMBER




//#define IMPL_VAR_ENUM(ENUMTYPE) \
//e_ ## ENUMTYPE & payload::e_ ## ENUMTYPE ## _reference()         \
//{                                                  \
//                                                   \
//   if(m_etype == ::e_type_payload_pointer)                      \
//   {                                               \
//                                                   \
//      return m_ppayload->e_ ## ENUMTYPE ## _reference();            \
//                                                   \
//   }                                               \
//   else if(m_etype == ::e_type_property)                      \
//   {                                               \
//                                                   \
//      return m_pproperty->e_ ## ENUMTYPE ## _reference();            \
//                                                   \
//   }                                               \
//         \
//   if(m_etype != ::e_type_enum_ ## ENUMTYPE)        \
//   {                                               \
//                                                   \
//      m_etype = ::e_type_enum_ ## ENUMTYPE;              \
//      zero(m_all);   \
//                                                   \
//   }                                               \
//                                                   \
//   return m_e ## ENUMTYPE;                         \
//                                                   \
//}
//IMPL_VAR_ENUM(status);
//IMPL_VAR_ENUM(command);
//IMPL_VAR_ENUM(check);
//#undef IMPL_VAR_ENUM


//::extended::status payload::run()
void payload::defer_run_payload()
{

/*   if (get_type() == e_type_payload_pointer)
   {

      return m_ppayload->defer_run_payload();

   }
   else if (get_type() == e_type_property)
   {

      return m_pproperty->defer_run_payload();

   }
   else*/ if (get_type() == e_type_element)
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

      auto & payloada = payload_array_reference();

      for (auto & payload : payloada)
      {

         payload.defer_run_payload();

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

   //if (get_type() == e_type_payload_pointer)
   //{

   //   m_ppayload->receive_response(payload);

   //}
   //else if (get_type() == e_type_property)
   //{

   //   m_pproperty->receive_response(payload);

   //}
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


#if defined(__APPLE__) || defined(__ANDROID__) || defined(RASPBERRYPIOS) || defined(WINDOWS)


long & payload::long_reference()
{
   
   if(m_etype == e_type_long_long)
   {
      
      return (long &) m_hi;
      
   }
   else if(m_etype == e_type_plong_long)
   {
      
      return (long &)*m_pll;
      
   }
   else
   {
   
      set_type(e_type_long_long);
   
      return (long &) m_hi;
      
   }

}


unsigned long & payload::unsigned_long_reference()
{

   if(m_etype == e_type_unsigned_long_long)
   {
      
      return (unsigned long &) m_hn;
      
   }
   else if(m_etype == e_type_punsigned_long_long)
   {
      
      return (unsigned long &)*m_pull;
      
   }
   else
   {
   
      set_type(e_type_unsigned_long_long);
   
      return (unsigned long &) m_hn;
      
   }

}


#endif


CLASS_DECL_ACME ::string as_string(const ::payload & payload)
{

   return ::transfer(payload.as_string()());

}


payload & payload::operator = (::memory * pmemory)
{

   set_type(e_type_memory, false);

   m_pmemory = pmemory;

   ::increment_reference_count(m_pmemory);

   return *this;

}


::subparticle * payload::get_subparticle()
{

switch (m_etype)
{
case e_type_element:
return m_p;
case e_type_string_array:
return m_pstra;
case e_type_int_array:
return m_pia;
case e_type_float_array:
   return m_pfloata;
case e_type_payload_array:
return m_ppayloada;
case e_type_property_set:
return m_ppropertyset;
case e_type_long_long_array:
return m_plonglonga;
case e_type_double_array:
   return m_pdoublea;
case e_type_memory:
return m_pmemory;
case e_type_path:
return m_ppath;
default:
   return nullptr;
break;
}

return nullptr;


}


::payload payload::first() const
{

   return at(0);

}


::payload payload::last() const
{

   if (array_get_count() == 0)
   {

      return first();

   }
   else
   {

      return at(array_get_upper_bound());

   }

}


::payload payload::first()
{

   return at(0);

}


::payload payload::last()
{

   if (array_get_count() == 0)
   {

      return first();

   }
   else
   {

      return at(array_get_upper_bound());

   }

}




//bool strictly_equal(const_char_pointer psz, const class ::payload & payload)
//{
//   return payload.m_etype == ::e_type_string && payload.m_str == psz;
//}
//
//bool strictly_equal(const ::scoped_string & scopedstr, const class ::payload & payload)
//{
//   return payload.m_etype == ::e_type_string && str == payload.m_str;
//}
//
//bool strictly_equal(double d, const class ::payload & payload)
//{
//   return payload.m_etype == ::e_type_double && d == payload.m_d;
//}
//
//bool strictly_equal(int i, const class ::payload & payload)
//{
//   return payload.m_etype == ::e_type_int && i == payload.m_i;
//}
//
//bool strictly_equal(bool b, const class ::payload & payload)
//{
//   return payload.m_etype == ::e_type_bool && is_equivalent(b, payload.m_b);
//}
//
//bool strictly_different(const_char_pointer psz, const class ::payload & payload)
//{
//   return !strictly_equal(scopedstr, payload);
//}
//
//bool strictly_different(const ::scoped_string & scopedstr, const class ::payload & payload)
//{
//   return !strictly_equal(str, payload);
//}
//
//bool strictly_different(double d, const class ::payload & payload)
//{
//   return !strictly_equal(d, payload);
//}
//
//bool strictly_different(int i, const class ::payload & payload)
//{
//   return !strictly_equal(i, payload);
//}
//
//bool strictly_different(bool b, const class ::payload & payload)
//{
//   return !strictly_equal(b, payload);
//}



CLASS_DECL_ACME char & copy(char & i, const payload & payload)
{

   return i = payload.as_char();

}


CLASS_DECL_ACME unsigned char & copy(unsigned char & u, const payload & payload)
{

   return u = payload.as_unsigned_char();

}


CLASS_DECL_ACME short & copy(short & i, const payload & payload)
{

   return i = payload.as_short();

}


CLASS_DECL_ACME unsigned short & copy(unsigned short & u, const payload & payload)
{

return u = payload.as_unsigned_short();

}


CLASS_DECL_ACME int & copy(int & i, const payload & payload)
{

   return i = payload.as_int();

}


CLASS_DECL_ACME unsigned int & copy(unsigned int & u, const payload & payload)
{

   return u = payload.as_unsigned_int();

}


CLASS_DECL_ACME long long & copy(long long & i, const payload & payload)
{

   return i = payload.as_long_long();

}


CLASS_DECL_ACME unsigned long long & copy(unsigned long long & u, const payload & payload)
{

   return u = payload.as_unsigned_long_long();

}


// CLASS_DECL_ACME float & copy(float & f, const payload & payload)
// {
//
//    return f = payload.as_float();
//
// }
//
//
// CLASS_DECL_ACME double & copy(double & f, const payload & payload)
// {
//
//    return f = payload.as_double();
//
// }


::collection::count payload::get_count() const
{
   switch (m_etype)
   {
      case e_type_bool:
         return 1;
      case e_type_int_array:
         return ::is_null(m_pia) ? 0 : m_pia->get_count();
      case e_type_float_array:
         return ::is_null(m_pfloata) ? 0 : m_pfloata->get_count();
      case e_type_long_long_array:
         return ::is_null(m_plonglonga) ? 0 : m_plonglonga->get_count();
      case e_type_double_array:
         return ::is_null(m_pdoublea) ? 0 : m_pdoublea->get_count();
      case e_type_string_array:
         return ::is_null(m_pstra) ? 0 : m_pstra->get_count();
      case e_type_payload_array:
         return ::is_null(m_ppayloada) ? 0 : m_ppayloada->get_count();
      case e_type_property_set:
         return ::is_null(m_ppropertyset) ? 0 : m_ppropertyset->property_count();
      //case e_type_property:
      //   return ::is_null(m_pproperty) ? 0 : m_pproperty->get_count();
      case e_type_empty:
      case e_type_null:
      case e_type_new:
      case e_type_empty_argument:
         return 0;
      default:
         return 1;
   }
}


::collection::count payload::array_get_count() const
{
   if (m_etype == e_type_new
       || m_etype == e_type_null
       || m_etype == e_type_empty
       || m_etype == e_type_empty_argument)
   {
      return -1; // indicates that this ::payload is not an array
   }
   else if (is_array())
      return this->get_count();
   else
      return 1; // this ::payload is an scalar or object that can be retrieved through "array_" methods
}



::collection::index payload::array_get_upper_bound() const
{
   if (m_etype == e_type_new
       || m_etype == e_type_null
       || m_etype == e_type_empty
       || m_etype == e_type_empty_argument)
   {
      return -1; // indicates that this ::payload is not an array
   }
   else if (is_array())
      return this->get_count() - 1;
   else
      return 0; // this ::payload is an scalar or object that can be retrieved through "array_" methods
}


bool payload::is_array() const
{

   if (m_etype == e_type_string_array
       || m_etype == e_type_int_array
      || m_etype == e_type_long_long_array
      || m_etype == e_type_float_array
      || m_etype == e_type_double_array
       || m_etype == e_type_payload_array
       || m_etype == e_type_property_set)
   {
      return true;
   }
   //else if (m_etype == e_type_property)
   //{
   //   return this->property_reference().is_array();
   //}
   else if (m_etype == e_type_element)
   {
      return false;
   }
   else
   {
      return false;
   }
}



//bool operator == (const ::scoped_string & scopedstr, const ::payload & payload)
//{
//
//   return str == payload.get_string();
//
//}



//atom& atom::operator = (const ::payload & payload)
//{
//
//   if (payload.is_null())
//   {
//      m_all = {};
//      return *this;
//   }
//   else if (payload.is_empty())
//   {
//      return operator =("");
//   }
//   else if (payload.is_integer())
//   {
//      return operator = (payload.iptr());
//   }
//   else
//   {
//      return operator = (payload.get_string());
//   }
//
//}
//
//atom& atom::operator = (const property& prop)
//{
//
//   return operator = ((const ::payload&)prop);
//
//}
//


//template < primitive_payload PAYLOAD >
//::payload payload::operator - (const PAYLOAD & payload2) const
//{
//
//   ::payload payload;
//
//   if (m_etype == ::e_type_int_array)
//   {
//
//      if (payload2.m_etype == ::e_type_int_array)
//      {
//
//         payload = ia() - payload2.ia();
//
//      }
//      else
//      {
//
//         payload = *this;
//
//         payload.ia().erase(payload2.as_int());
//
//      }
//
//   }
//   else if (m_etype == ::e_type_string_array)
//   {
//
//      if (payload2.m_etype == ::e_type_string_array)
//      {
//
//         payload = stra() - payload2.stra();
//
//      }
//      else if (payload2.is_array())
//      {
//
//         payload = stra() - payload2.stra();
//
//      }
//      else
//      {
//
//         payload = *this;
//
//         payload.stra().erase(payload2.get_string());
//
//      }
//
//   }
//   else if (m_etype == ::e_type_payload_array)
//   {
//      if (payload2.m_etype == ::e_type_payload_array)
//      {
//         payload = payloada() - payload2.payloada();
//      }
//      else
//      {
//         payload = *this;
//         payload.payloada().erase(payload2);
//      }
//   }
//   else if (is_double() || payload2.is_double())
//   {
//      payload = as_double() - payload2.as_double();
//   }
//   else if (is_integer() || payload2.is_integer())
//   {
//      payload = as_int() - payload2.as_int();
//   }
//   else if (is_natural() || payload2.is_natural())
//   {
//      payload = as_unsigned_int() - payload2.as_unsigned_int();
//   }
//   else
//   {
//      payload = atoi(get_string()) - atoi(payload2.get_string());
//   }
//   return payload;
//}
//
//template < primitive_payload PAYLOAD >
//::payload payload::operator + (const PAYLOAD & payload2) const
//{
//
//   ::payload payload;
//
//   if (m_etype == ::e_type_int_array || m_etype == ::e_type_int_array)
//   {
//
//      if (m_etype == ::e_type_int_array)
//      {
//
//         if (payload2.m_etype == ::e_type_int_array)
//         {
//
//            payload = ia() + payload2.ia();
//
//         }
//         else
//         {
//
//            payload = *this;
//
//            payload.ia().add(payload2.as_int());
//
//         }
//
//      }
//      else
//      {
//
//         payload = payload2;
//
//         payload.ia().add(as_int());
//
//      }
//
//   }
//   else if (m_etype == ::e_type_string_array || payload2.m_etype == ::e_type_string_array)
//   {
//
//      if (m_etype == ::e_type_string_array)
//      {
//
//         if (payload2.m_etype == ::e_type_string_array)
//         {
//
//            payload = stra() + payload2.stra();
//
//         }
//         else
//         {
//
//            payload = *this;
//
//            payload.stra().add(payload2.get_string());
//
//         }
//
//      }
//      else
//      {
//
//         payload = payload2;
//
//         payload.stra().add(get_string());
//
//      }
//
//   }
//   else if (m_etype == ::e_type_payload_array || payload2.m_etype == ::e_type_payload_array)
//   {
//
//      if (payload2.m_etype == ::e_type_payload_array)
//      {
//
//         if (payload2.m_etype == ::e_type_payload_array)
//         {
//
//            payload = payloada() + payload2.payloada();
//
//         }
//         else
//         {
//
//            payload = *this;
//
//            payload.payloada().add(payload2);
//
//         }
//
//      }
//      else
//      {
//
//         payload = payload2;
//
//         payload.payloada().add(*this);
//
//      }
//
//   }
//   else if ((is_double() && payload2.is_number()) || (is_number() && payload2.is_double()))
//   {
//
//      payload = as_double() + payload2.as_double();
//
//   }
//   else if (is_integer() && payload2.is_integer())
//   {
//
//      payload = as_int() + payload2.as_int();
//
//   }
//   else if (is_natural() && payload2.is_natural())
//   {
//
//      payload = as_unsigned_int() + payload2.as_unsigned_int();
//
//   }
//   else
//   {
//
//      payload = get_string() + payload2.get_string();
//
//   }
//
//   return payload;
//
//}





//template < primitive_payload PAYLOAD >
//::payload payload::operator / (const PAYLOAD & payload2) const
//{
//
//   ::payload payload;
//
//   if (m_etype == ::e_type_int_array)
//   {
//      if (payload2.m_etype == ::e_type_int_array)
//      {
//         payload = *this;
//         payload.ia().intersect(payload2.ia());
//      }
//      else
//      {
//         payload = *this;
//         payload.ia().divide(payload2.as_int());
//      }
//   }
//   else if (m_etype == ::e_type_string_array)
//   {
//      if (payload2.m_etype == ::e_type_string_array)
//      {
//         //payload = stra().intersect(payload2.stra());
//      }
//      else
//      {
//         payload = *this;
//         payload.stra().erase(payload2.get_string());
//      }
//   }
//   else if (m_etype == ::e_type_payload_array)
//   {
//      if (payload2.m_etype == ::e_type_payload_array)
//      {
//         //payload = payloada() / payload2.payloada();
//      }
//      else
//      {
//         payload = *this;
//         payload.payloada().erase(payload2);
//      }
//   }
//   else if (is_double() || payload2.is_double())
//   {
//      payload = as_double() / payload2.as_double();
//   }
//   else if (is_integer() || payload2.is_integer())
//   {
//      payload = as_int() / payload2.as_int();
//   }
//   else if (is_natural() || payload2.is_natural())
//   {
//      payload = as_unsigned_int() / payload2.as_unsigned_int();
//   }
//   else
//   {
//      payload = atoi(get_string()) / atoi(payload2.get_string());
//   }
//   return payload;
//}



//template < primitive_payload PAYLOAD >
//::payload payload:: operator * (const PAYLOAD & payload2) const
//{
//
//   ::payload payload;
//
//   if (m_etype == ::e_type_int_array || m_etype == ::e_type_int_array)
//   {
//
//      ::acme::array::intersection(payload.ia(), ia(), payload2.ia());
//
//   }
//   else if (m_etype == ::e_type_string_array || payload2.m_etype == ::e_type_string_array)
//   {
//
//      ::acme::array::intersection(payload.stra(), stra(), payload2.stra());
//
//   }
//   else if (m_etype == ::e_type_payload_array || payload2.m_etype == ::e_type_payload_array)
//   {
//
//      ::acme::array::intersection(payload.payloada(), payloada(), payload2.payloada());
//
//   }
//   else if (is_double() || payload2.is_double())
//   {
//
//      payload = as_double() * payload2.as_double();
//
//   }
//   else if (is_integer() || payload2.is_integer())
//   {
//
//      payload = as_int() * payload2.as_int();
//
//   }
//   else if (is_natural() || payload2.is_natural())
//   {
//
//      payload = as_unsigned_int() * payload2.as_unsigned_int();
//
//   }
//   else
//   {
//
//      payload = get_string().intersection(payload2.to_string());
//
//   }
//
//   return payload;
//
//}








//template < primitive_payload PAYLOAD >
//::payload & payload:: operator -= (const PAYLOAD & payload)
//{
//
//   *this = *this - payload;
//
//   return *this;
//
//}
//
//
//template < primitive_payload PAYLOAD >
//::payload & payload:: operator += (const PAYLOAD & payload)
//{
//
//   *this = *this + payload;
//
//   return *this;
//
//}
//
//
//template < primitive_payload PAYLOAD >
//::payload & payload:: operator /= (const PAYLOAD & payload)
//{
//
//   *this = *this / payload;
//
//   return *this;
//
//}
//
//
//template < primitive_payload PAYLOAD >
//::payload & payload:: operator *= (const PAYLOAD & payload)
//{
//
//   *this = *this * payload;
//
//   return *this;
//
//}







//payload::operator bool() const { return this->get_bool(); }
//
//payload::operator ::as_char() const { return this->as_char(); }
//payload::operator ::as_unsigned_char() const { return this->as_unsigned_char(); }
//payload::operator ::as_short() const { return this->as_short(); }
//payload::operator ::as_unsigned_short() const { return this->as_unsigned_short(); }
//payload::operator ::as_int() const { return this->as_int(); }
//payload::operator ::as_unsigned_int() const { return this->as_unsigned_int(); }
//payload::operator ::as_long_long() const { return this->as_long_long(); }
//payload::operator ::as_unsigned_long_long() const { return this->as_unsigned_long_long(); }
//payload::operator ::as_float() const { return this->as_float(); }
//payload::operator ::as_double() const { return this->as_double(); }
//
//
//payload::operator ::get_string() const
//{
//
//   return this->get_string();
//
//}


payload & payload::operator = (const ::file::path & path)
{

   //if (m_etype == e_type_payload_pointer)
   //{

   //   m_ppayload->operator = (path);

   //}
   //else if (m_etype == e_type_property)
   //{

   //   m_pproperty->object() = path;

   //}
   //else
   {

      if (m_etype != e_type_path)
      {

         set_type(e_type_path, false);

      }

      if (::is_null(m_ppath))
      {

         m_ppath = __new__prefix(&m_preferer) new ::file::path_object(path);

      }
      else
      {

         ((::file::path &) * m_ppath) = path;

      }

   }

   return *this;

}


bool succeeded(const ::payload & payload)
{

   if (payload.m_etype == e_type_atom && payload.m_atomPayload.m_estatus)
   {

      return payload.m_atomPayload.m_estatus.succeeded();

   }
   else if (payload.is_integer())
   {

      return payload.as_long_long() >= 0;

   }
   else
   {

      throw ::exception(error_unexpected_situation);

   }

}



//class ::payload & payload::operator -= (const class property & property) { operator -=(property);  return *this; }
//class ::payload & payload::operator += (const class property & property) { operator +=(property);  return *this; }
//class ::payload & payload::operator /= (const class property & property) { operator /=(property);  return *this; }
//class ::payload & payload::operator *= (const class property & property) { operator *=(property);  return *this; }



payload payload::addition(const ::payload & payload) const
{

   ::payload payloadResult(*this);

   payloadResult += payload;

   return ::transfer(payloadResult);

}


payload  payload::subtraction(const ::payload & payload) const
{

   ::payload payloadResult(*this);

   payloadResult -= payload;

   return ::transfer(payloadResult);

}


payload payload::multiplication(const ::payload & payload) const
{

   ::payload payloadResult(*this);

   payloadResult *= payload;

   return ::transfer(payloadResult);

}


payload  payload::division(const ::payload & payload) const
{

   ::payload payloadResult(*this);

   payloadResult /= payload;

   return ::transfer(payloadResult);

}


enum_type payload::integer_type() const
{

   switch(get_type())
   {
      case e_type_new:
      case e_type_null:
      case e_type_string_array:
      case e_type_int_array:
      case e_type_long_long_array:
      case e_type_float_array:
      case e_type_double_array:
      case e_type_empty:
      case e_type_element:
      case e_type_path:
         return e_type_not_found;
      case e_type_bool:
         return e_type_char;
      case e_type_string:
         return e_type_not_found;
      case e_type_float:
         return e_type_not_found;
      case e_type_double:
         return e_type_not_found;
      case e_type_pfloat:
         return e_type_not_found;
      case e_type_pdouble:
         return e_type_not_found;
      case e_type_unsigned_char:
         return e_type_unsigned_char;
      case e_type_char:
         return e_type_char;
      case e_type_unsigned_short:
         return e_type_unsigned_short;
      case e_type_short:
         return e_type_short;
      case e_type_unsigned_int:
         return e_type_unsigned_int;
      case e_type_int:
         return e_type_int;
      case e_type_unsigned_long_long:
         return e_type_unsigned_int;
      case e_type_long_long:
         return e_type_int;
      case e_type_punsigned_char:
         return e_type_unsigned_char;
      case e_type_pchar:
         return e_type_char;
      case e_type_punsigned_short:
         return e_type_unsigned_short;
      case e_type_pshort:
         return e_type_short;
      case e_type_punsigned_int:
         return e_type_unsigned_int;
      case e_type_pint:
         return e_type_int;
      case e_type_punsigned_long_long:
         return e_type_unsigned_long_long;
      case e_type_plong_long:
         return e_type_long_long;
      default:
         break;
   }
   return e_type_not_found;

}


enum_type payload::left_hand_integer_type() const
{

   switch(get_type())
   {
      case e_type_new:
      case e_type_null:
      case e_type_string_array:
      case e_type_int_array:
      case e_type_float_array:
      case e_type_long_long_array:
      case e_type_double_array:
      case e_type_empty:
      case e_type_element:
      case e_type_path:
         return e_type_not_found;
      case e_type_bool:
         return e_type_char;
      case e_type_string:
         return e_type_not_found;
      case e_type_float:
         return e_type_not_found;
      case e_type_double:
         return e_type_not_found;
      case e_type_pfloat:
         return e_type_not_found;
      case e_type_pdouble:
         return e_type_not_found;
      case e_type_unsigned_char:
         return e_type_unsigned_char;
      case e_type_char:
         return e_type_char;
      case e_type_unsigned_short:
         return e_type_unsigned_short;
      case e_type_short:
         return e_type_short;
      case e_type_unsigned_int:
         return e_type_unsigned_int;
      case e_type_int:
         return e_type_int;
      case e_type_unsigned_long_long:
         return e_type_unsigned_int;
      case e_type_long_long:
         return e_type_int;
      case e_type_punsigned_char:
         return e_type_punsigned_char;
      case e_type_pchar:
         return e_type_pchar;
      case e_type_punsigned_short:
         return e_type_punsigned_short;
      case e_type_pshort:
         return e_type_pshort;
      case e_type_punsigned_int:
         return e_type_punsigned_int;
      case e_type_pint:
         return e_type_pint;
      case e_type_punsigned_long_long:
         return e_type_punsigned_long_long;
      case e_type_plong_long:
         return e_type_plong_long;
      default:
    break;
   }
   return e_type_not_found;

}


enum_type payload::floating_type() const
{

   switch(get_type())
   {
      case e_type_new:
      case e_type_null:
      case e_type_string_array:
      case e_type_int_array:
      case e_type_float_array:
      case e_type_long_long_array:
      case e_type_double_array:
      case e_type_empty:
      case e_type_element:
      case e_type_path:
         return e_type_not_found;
      case e_type_bool:
         return e_type_char;
      case e_type_string:
         return e_type_not_found;
      case e_type_float:
         return e_type_float;
      case e_type_double:
         return e_type_double;
      case e_type_pfloat:
         return e_type_float;
      case e_type_pdouble:
         return e_type_double;
      case e_type_unsigned_char:
         return e_type_not_found;
      case e_type_char:
         return e_type_not_found;
      case e_type_unsigned_short:
         return e_type_not_found;
      case e_type_short:
         return e_type_not_found;
      case e_type_unsigned_int:
         return e_type_not_found;
      case e_type_int:
         return e_type_not_found;
      case e_type_unsigned_long_long:
         return e_type_not_found;
      case e_type_long_long:
         return e_type_not_found;
      case e_type_punsigned_char:
         return e_type_not_found;
      case e_type_pchar:
         return e_type_not_found;
      case e_type_punsigned_short:
         return e_type_not_found;
      case e_type_pshort:
         return e_type_not_found;
      case e_type_punsigned_int:
         return e_type_not_found;
      case e_type_pint:
         return e_type_not_found;
      case e_type_punsigned_long_long:
         return e_type_not_found;
      case e_type_plong_long:
         return e_type_not_found;
      default:
break;
   }

   return e_type_not_found;

}


enum_type payload::left_hand_floating_type() const
{

   switch(get_type())
   {
      case e_type_new:
      case e_type_null:
      case e_type_string_array:
      case e_type_int_array:
      case e_type_float_array:
      case e_type_long_long_array:
      case e_type_double_array:
      case e_type_empty:
      case e_type_element:
      case e_type_path:
         return e_type_not_found;
      case e_type_bool:
         return e_type_char;
      case e_type_string:
         return e_type_not_found;
      case e_type_float:
         return e_type_float;
      case e_type_double:
         return e_type_double;
      case e_type_pfloat:
         return e_type_pfloat;
      case e_type_pdouble:
         return e_type_pdouble;
      case e_type_unsigned_char:
         return e_type_not_found;
      case e_type_char:
         return e_type_not_found;
      case e_type_unsigned_short:
         return e_type_not_found;
      case e_type_short:
         return e_type_not_found;
      case e_type_unsigned_int:
         return e_type_not_found;
      case e_type_int:
         return e_type_not_found;
      case e_type_unsigned_long_long:
         return e_type_not_found;
      case e_type_long_long:
         return e_type_not_found;
      case e_type_punsigned_char:
         return e_type_not_found;
      case e_type_pchar:
         return e_type_not_found;
      case e_type_punsigned_short:
         return e_type_not_found;
      case e_type_pshort:
         return e_type_not_found;
      case e_type_punsigned_int:
         return e_type_not_found;
      case e_type_pint:
         return e_type_not_found;
      case e_type_punsigned_long_long:
         return e_type_not_found;
      case e_type_plong_long:
         return e_type_not_found;
      default:
         break;
   }

   return e_type_not_found;

}


payload & payload::add(const ::payload & payload)
{

   if(get_type() == e_type_int_array)
   {

      if(payload.get_type() == e_type_int_array)
      {

         int_array_reference().append(payload.int_array_reference());

      }
      else if(payload.get_type() == e_type_long_long_array)
      {

         int_array_reference().append(payload.long_long_array_reference());

      }
      else if (payload.get_type() == e_type_float_array)
      {

         int_array_reference().append(payload.float_array_reference());

      }
      else if (payload.get_type() == e_type_double_array)
      {

         int_array_reference().append(payload.double_array_reference());

      }
      else
      {

         // simple implementation
         int_array_reference().add(payload.as_int());

      }

   }
   else if(get_type() == e_type_long_long_array)
   {

      if(payload.get_type() == e_type_long_long_array)
      {

         long_long_array_reference().add(payload.long_long_array_reference());

      }
      else if(payload.get_type() == e_type_int_array)
      {

         long_long_array_reference().add(payload.int_array_reference());

      }
      else if (payload.get_type() == e_type_double_array)
      {

         long_long_array_reference().add(payload.double_array_reference());

      }
      else if (payload.get_type() == e_type_float_array)
      {

         long_long_array_reference().add(payload.float_array_reference());

      }
      else
      {

         // simple implementation
         long_long_array_reference().add(payload.as_long_long());

      }

   }
   else if (get_type() == e_type_float_array)
   {

      if (payload.get_type() == e_type_int_array)
      {

         float_array_reference().append(payload.int_array_reference());

      }
      else if (payload.get_type() == e_type_long_long_array)
      {

         float_array_reference().append(payload.long_long_array_reference());

      }
      else if (payload.get_type() == e_type_float_array)
      {

         float_array_reference().append(payload.float_array_reference());

      }
      else if (payload.get_type() == e_type_double_array)
      {

         float_array_reference().append(payload.double_array_reference());

      }
      else
      {

         // simple implementation
         float_array_reference().add(payload.as_float());

      }

   }
   else if (get_type() == e_type_double_array)
   {

      if (payload.get_type() == e_type_long_long_array)
      {

         double_array_reference().add(payload.long_long_array_reference());

      }
      else if (payload.get_type() == e_type_int_array)
      {

         double_array_reference().add(payload.int_array_reference());

      }
      else if (payload.get_type() == e_type_double_array)
      {

         double_array_reference().add(payload.double_array_reference());

      }
      else if (payload.get_type() == e_type_float_array)
      {

         double_array_reference().add(payload.float_array_reference());

      }
      else
      {

         // simple implementation
         double_array_reference().add(payload.as_double());

      }

   }
   else if(get_type() == e_type_string_array)
   {

      if(payload.get_type() == e_type_string_array)
      {

         string_array_reference().append(payload.string_array_reference());

      }
      else if(payload.get_type() == e_type_int_array)
      {

          ::generic::container::append(string_array_reference(), payload.int_array_reference());

      }
      else if(payload.get_type() == e_type_long_long_array)
      {

          ::generic::container::append(string_array_reference(), payload.long_long_array_reference());

      }
      else if (payload.get_type() == e_type_float_array)
      {

         ::generic::container::append(string_array_reference(), payload.float_array_reference());

      }
      else if (payload.get_type() == e_type_double_array)
      {

         ::generic::container::append(string_array_reference(), payload.double_array_reference());

      }
      else if(payload.get_type() == e_type_payload_array)
      {

          ::generic::container::append(string_array_reference(), payload.payload_array_reference());

      }
      else
      {

         // simple implementation
         string_array_reference().add(payload.as_string());

      }

   }
   else if(get_type() == e_type_payload_array)
   {

      if(payload.get_type() == e_type_payload_array)
      {

         payload_array_reference().append(payload.payload_array_reference());

      }
      else if(payload.get_type() == e_type_int_array)
      {

          ::generic::container::append(payload_array_reference(), payload.int_array_reference());

      }
      else if(payload.get_type() == e_type_long_long_array)
      {

          ::generic::container::append(payload_array_reference(), payload.long_long_array_reference());

      }
      else if (payload.get_type() == e_type_float_array)
      {

         ::generic::container::append(payload_array_reference(), payload.float_array_reference());

      }
      else if (payload.get_type() == e_type_double_array)
      {

         ::generic::container::append(payload_array_reference(), payload.double_array_reference());

      }
      else if(payload.get_type() == e_type_string_array)
      {

          ::generic::container::append(payload_array_reference(), payload.string_array_reference());

      }
      else
      {

         // simple implementation
         payload_array_reference().add(payload);

      }

   }
   else if(is_integer())
   {

      if(payload.is_integer())
      {

         auto etype = maximum(left_hand_integer_type(), payload.integer_type());

         if(etype != get_type())
         {

            set_type(etype);

         }

         switch(etype)
         {
            case e_type_unsigned_char:
               if((unsigned short) m_uch + (unsigned short) payload.as_unsigned_char() >= 256)
               {
                  set_type(e_type_unsigned_short);
                  m_ush += payload.as_unsigned_char();
               }
               else
               {
                  m_uch += payload.as_unsigned_char();
               }
               break;
            case e_type_char:
               if(((short) m_ch + (short) payload.as_char() >= 129 )|| ((short) m_ch + (short) payload.as_char() < -128))
               {
                  set_type(e_type_short);
                  m_sh += payload.as_char();
               }
               else
               {
                  m_ch += payload.as_char();
               }
               break;
            case e_type_unsigned_short:
               if((unsigned int) m_ush + (unsigned int) payload.as_unsigned_short() >= 65536)
               {
                  set_type(e_type_unsigned_int);
                  m_ui += payload.as_unsigned_short();
               }
               else
               {
                  m_ush += payload.as_unsigned_short();
               }
               break;
            case e_type_short:
               if(((int) m_sh + (int) payload.as_short() >= 32769) || ((int) m_sh + (int) payload.as_short() < -32768))
               {
                  set_type(e_type_int);
                  m_i += payload.as_short();
               }
               else
               {
                  m_sh += payload.as_short();
               }
               break;
            case e_type_unsigned_int:
               if((unsigned long long) m_ui + (unsigned long long) payload.as_unsigned_int() >= (unsigned long long) UINT_MAX)
               {
                  set_type(e_type_unsigned_long_long);
                  m_hn += payload.as_unsigned_int();
               }
               else
               {
                  m_ui += payload.as_unsigned_int();
               }
               break;
            case e_type_int:
               if(((long long) m_i + (long long) payload.as_int() > (long long) INT_MAX) || ((long long) m_i + (long long) payload.as_int() < (long long) INT_MIN))
               {
                  set_type(e_type_long_long);
                  m_hi += payload.as_int();
               }
               else
               {
                  m_i += payload.as_int();
               }
               break;
            case e_type_unsigned_long_long:
               m_hn += payload.as_unsigned_long_long();
               break;
            case e_type_long_long:
               m_hi += payload.as_long_long();
               break;
            case e_type_punsigned_char:
               *m_puch += payload.as_unsigned_char();
               break;
            case e_type_pchar:
               *m_pch += payload.as_char();
               break;
            case e_type_punsigned_short:
               *m_push += payload.as_unsigned_short();
               break;
            case e_type_pshort:
               *m_psh += payload.as_short();
               break;
            case e_type_punsigned_int:
               *m_pui += payload.as_unsigned_int();
               break;
            case e_type_pint:
               *m_pi += payload.as_int();
               break;
            case e_type_punsigned_long_long:
               *m_pull += payload.as_unsigned_long_long();
               break;
            case e_type_plong_long:
               *m_pll += payload.as_long_long();
               break;
            default:
               throw ::exception(error_unexpected, "unexpected result from cast/promotion");
         };

      }
      else if(payload.is_floating())
      {

         auto etype = maximum(left_hand_integer_type(), payload.floating_type());

         if(etype != get_type())
         {

            set_type(etype);

         }

         switch(etype)
         {
            case e_type_float:
               m_f += payload.as_unsigned_int();
               break;
            case e_type_double:
               m_d += payload.as_double();
               break;
            case e_type_punsigned_char:
               *m_puch += payload.as_unsigned_char();
               break;
            case e_type_pchar:
               *m_pch += payload.as_char();
               break;
            case e_type_punsigned_short:
               *m_push += payload.as_unsigned_short();
               break;
            case e_type_pshort:
               *m_psh += payload.as_short();
               break;
            case e_type_punsigned_int:
               *m_pui += payload.as_unsigned_int();
               break;
            case e_type_pint:
               *m_pi += payload.as_int();
               break;
            case e_type_punsigned_long_long:
               *m_pull += payload.as_unsigned_long_long();
               break;
            case e_type_plong_long:
               *m_pll += payload.as_long_long();
               break;
            default:
               throw ::exception(error_unexpected, "unexpected result from cast/promotion");

         };

      }
      else if(payload.is_text())
      {

         operator= (this->as_string() + payload.as_string());

      }
      else
      {

         throw ::not_implemented("yet to be done");

      }

   }
   else if(is_floating())
   {

      if(payload.is_integer())
      {

         auto etype = maximum(left_hand_floating_type(), payload.integer_type());

         if(etype != get_type())
         {

            set_type(etype);

         }

         switch(etype)
         {
            case e_type_float:
               m_f += payload.as_float();
               break;
            case e_type_double:
               m_d += payload.as_double();
               break;
            case e_type_pfloat:
               *m_pf += payload.as_float();
               break;
            case e_type_pdouble:
               *m_pd += payload.as_double();
               break;
            default:
               throw ::exception(error_unexpected, "unexpected result from cast/promotion");
         };

      }
      else if(payload.is_floating())
      {

         auto etype = maximum(left_hand_floating_type(), payload.floating_type());

         if(etype != get_type())
         {

            set_type(etype);

         }

         switch(etype)
         {
            case e_type_float:
               m_f += payload.as_float();
               break;
            case e_type_double:
               m_d += payload.as_double();
               break;
            case e_type_pfloat:
               *m_pf += payload.as_float();
               break;
            case e_type_pdouble:
               *m_pd += payload.as_double();
               break;
            default:
               throw ::exception(error_unexpected, "unexpected result from cast/promotion");
         };


      }
      else if(payload.is_text())
      {

         operator= (this->as_string() + payload.as_string());

      }
      else
      {

         throw ::not_implemented("yet to be done");

      }

   }
   else if(payload.is_text())
   {

      operator= (this->as_string() + payload.as_string());

   }
   else
   {

      throw ::not_implemented("yet to be done");

   }

   return *this;

}


payload & payload::subtract(const ::payload & payload)
{

   if(is_integer())
   {

      if(payload.is_integer())
      {

         auto etype = maximum(left_hand_integer_type(), payload.integer_type());

         if(etype != get_type())
         {

            set_type(etype);

         }

         switch(etype)
         {
            case e_type_unsigned_char:
               if((short) m_uch - (short) payload.as_short() < 0)
               {
                  set_type(e_type_short);
                  m_sh -= payload.as_unsigned_char();
               }
               else
               {
                  m_uch -= payload.as_unsigned_char();
               }
               break;
            case e_type_char:
               if(((short) m_ch - (short) payload.as_char() >= 129) || ((short) m_ch - (short) payload.as_char() <=  -128))
               {
                  set_type(e_type_short);
                  m_sh -= payload.as_char();
               }
               else
               {
                  m_ch -= payload.as_char();
               }
               break;
            case e_type_unsigned_short:
               if((int) m_ush - (int) payload.as_int() < 0)
               {
                  set_type(e_type_int);
                  m_i -= payload.as_unsigned_int();
               }
               else
               {
                  m_ush -= payload.as_unsigned_short();
               }
               break;
            case e_type_short:
               if(((int) m_sh - (int) payload.as_short() >= 32769) || ((int) m_sh - (int) payload.as_short() < -32768))
               {
                  set_type(e_type_int);
                  m_i -= payload.as_short();
               }
               else
               {
                  m_sh -= payload.as_short();
               }
               break;
            case e_type_unsigned_int:
               if((long long) m_ui - (long long) payload.as_long_long() < 0)
               {
                  set_type(e_type_long_long);
                  m_hi -= payload.as_long_long();
               }
               else
               {
                  m_ui -= payload.as_unsigned_int();
               }
               break;
            case e_type_int:
               if(((long long) m_i + (long long) payload.as_int() >= (long long) INT_MAX) || ((long long) m_i - (long long) payload.as_int() < (long long) INT_MIN))
               {
                  set_type(e_type_long_long);
                  m_hi -= payload.as_int();
               }
               else
               {
                  m_i -= payload.as_int();
               }
               break;
            case e_type_unsigned_long_long:
               m_hn -= payload.as_unsigned_long_long();
               break;
            case e_type_long_long:
               m_hi -= payload.as_long_long();
               break;
            case e_type_punsigned_char:
               *m_puch -= payload.as_unsigned_char();
               break;
            case e_type_pchar:
               *m_pch -= payload.as_char();
               break;
            case e_type_punsigned_short:
               *m_push -= payload.as_unsigned_short();
               break;
            case e_type_pshort:
               *m_psh -= payload.as_short();
               break;
            case e_type_punsigned_int:
               *m_pui -= payload.as_unsigned_int();
               break;
            case e_type_pint:
               *m_pi -= payload.as_int();
               break;
            case e_type_punsigned_long_long:
               *m_pull -= payload.as_unsigned_long_long();
               break;
            case e_type_plong_long:
               *m_pll -= payload.as_long_long();
               break;
            default:
               throw ::exception(error_unexpected, "unexpected result from cast/promotion");
         };

      }
      else if(payload.is_floating())
      {

         auto etype = maximum(left_hand_integer_type(), payload.floating_type());

         if(etype != get_type())
         {

            set_type(etype);

         }

         switch(etype)
         {
            case e_type_float:
               m_f -= payload.as_unsigned_int();
               break;
            case e_type_double:
               m_d -= payload.as_double();
               break;
            case e_type_punsigned_char:
               *m_puch -= payload.as_unsigned_char();
               break;
            case e_type_pchar:
               *m_pch -= payload.as_char();
               break;
            case e_type_punsigned_short:
               *m_push -= payload.as_unsigned_short();
               break;
            case e_type_pshort:
               *m_psh -= payload.as_short();
               break;
            case e_type_punsigned_int:
               *m_pui -= payload.as_unsigned_int();
               break;
            case e_type_pint:
               *m_pi -= payload.as_int();
               break;
            case e_type_punsigned_long_long:
               *m_pull -= payload.as_unsigned_long_long();
               break;
            case e_type_plong_long:
               *m_pll -= payload.as_long_long();
               break;
            default:
               throw ::exception(error_unexpected, "unexpected result from cast/promotion");

         };

      }
      else if(payload.is_text())
      {

         throw ::exception(error_unexpected);

      }
      else
      {

         throw ::not_implemented("yet to be done");

      }

   }
   else if(is_floating())
   {

      if(payload.is_integer())
      {

         auto etype = maximum(left_hand_floating_type(), payload.integer_type());

         if(etype != get_type())
         {

            set_type(etype);

         }

         switch(etype)
         {
            case e_type_float:
               m_f -= payload.as_float();
               break;
            case e_type_double:
               m_d -= payload.as_double();
               break;
            case e_type_pfloat:
               *m_pf -= payload.as_float();
               break;
            case e_type_pdouble:
               *m_pd -= payload.as_double();
               break;
            default:
               throw ::exception(error_unexpected, "unexpected result from cast/promotion");
         };

      }
      else if(payload.is_floating())
      {

         auto etype = maximum(left_hand_floating_type(), payload.floating_type());

         if(etype != get_type())
         {

            set_type(etype);

         }

         switch(etype)
         {
            case e_type_float:
               m_f -= payload.as_float();
               break;
            case e_type_double:
               m_d -= payload.as_double();
               break;
            case e_type_pfloat:
               *m_pf -= payload.as_float();
               break;
            case e_type_pdouble:
               *m_pd -= payload.as_double();
               break;
            default:
               throw ::exception(error_unexpected, "unexpected result from cast/promotion");
         };


      }
      else if(payload.is_text())
      {

         throw ::exception(error_unexpected);

      }
      else
      {

         throw ::not_implemented("yet to be done");

      }

   }
   else if(payload.is_text())
   {

      throw ::exception(error_unexpected);

   }
   else
   {

      throw ::not_implemented("yet to be done");

   }

   return *this;
}


payload &  payload::multiply(const ::payload & payload)
{

   if (is_integer())
   {

      if (payload.is_integer())
      {

         auto etype = maximum(left_hand_integer_type(), payload.integer_type());

         if (etype != get_type())
         {

            set_type(etype);

         }

         switch (etype)
         {
            case e_type_unsigned_char:
               if ((unsigned short) m_uch + (unsigned short) payload.as_unsigned_char() >= 256)
               {
                  set_type(e_type_unsigned_short);
                  m_ush *= payload.as_unsigned_char();
               } else
               {
                  m_uch *= payload.as_unsigned_char();
               }
               break;
            case e_type_char:
               if ((short) m_ch + (short) payload.as_char() >= 129)
               {
                  set_type(e_type_short);
                  m_sh *= payload.as_char();
               } else
               {
                  m_ch *= payload.as_char();
               }
               break;
            case e_type_unsigned_short:
               if ((unsigned int) m_ush + (unsigned int) payload.as_unsigned_short() >= 65536)
               {
                  set_type(e_type_unsigned_int);
                  m_ui *= payload.as_unsigned_short();
               } else
               {
                  m_ush *= payload.as_unsigned_short();
               }
               break;
            case e_type_short:
               if ((int) m_sh + (int) payload.as_short() >= 32769)
               {
                  set_type(e_type_int);
                  m_i *= payload.as_short();
               } else
               {
                  m_sh *= payload.as_short();
               }
               break;
            case e_type_unsigned_int:
               if ((unsigned long long) m_ui + (unsigned long long) payload.as_unsigned_int() >= 65536)
               {
                  set_type(e_type_unsigned_long_long);
                  m_hn *= payload.as_unsigned_int();
               } else
               {
                  m_ui *= payload.as_unsigned_int();
               }
               break;
            case e_type_int:
               if ((long long) m_i + (long long) payload.as_int() >= 64769)
               {
                  set_type(e_type_long_long);
                  m_hi *= payload.as_int();
               } else
               {
                  m_i *= payload.as_int();
               }
               break;
            case e_type_unsigned_long_long:
               m_hn *= payload.as_unsigned_long_long();
               break;
            case e_type_long_long:
               m_hi *= payload.as_long_long();
               break;
            case e_type_punsigned_char:
               *m_puch *= payload.as_unsigned_char();
               break;
            case e_type_pchar:
               *m_pch *= payload.as_char();
               break;
            case e_type_punsigned_short:
               *m_push *= payload.as_unsigned_short();
               break;
            case e_type_pshort:
               *m_psh *= payload.as_short();
               break;
            case e_type_punsigned_int:
               *m_pui *= payload.as_unsigned_int();
               break;
            case e_type_pint:
               *m_pi *= payload.as_int();
               break;
            case e_type_punsigned_long_long:
               *m_pull *= payload.as_unsigned_long_long();
               break;
            case e_type_plong_long:
               *m_pll *= payload.as_long_long();
               break;
            default:
               throw ::exception(error_unexpected, "unexpected result from cast/promotion");
         };

      }
      else if (payload.is_floating())
      {

         auto etype = maximum(left_hand_integer_type(), payload.floating_type());

         if (etype != get_type())
         {

            set_type(etype);

         }

         switch (etype)
         {
            case e_type_float:
               m_f *= payload.as_unsigned_int();
               break;
            case e_type_double:
               m_d *= payload.as_double();
               break;
            case e_type_punsigned_char:
               *m_puch *= payload.as_unsigned_char();
               break;
            case e_type_pchar:
               *m_pch *= payload.as_char();
               break;
            case e_type_punsigned_short:
               *m_push *= payload.as_unsigned_short();
               break;
            case e_type_pshort:
               *m_psh *= payload.as_short();
               break;
            case e_type_punsigned_int:
               *m_pui *= payload.as_unsigned_int();
               break;
            case e_type_pint:
               *m_pi *= payload.as_int();
               break;
            case e_type_punsigned_long_long:
               *m_pull *= payload.as_unsigned_long_long();
               break;
            case e_type_plong_long:
               *m_pll *= payload.as_long_long();
               break;
            default:
               throw ::exception(error_unexpected, "unexpected result from cast/promotion");

         };

      } else if (payload.is_text())
      {

         operator= (as_file_path().folder() / payload.as_file_path().name());

      } else
      {

         throw ::not_implemented("yet to be done");

      }

   }
   else if (is_floating())
   {

      if (payload.is_integer())
      {

         auto etype = maximum(left_hand_floating_type(), payload.integer_type());

         if (etype != get_type())
         {

            set_type(etype);

         }

         switch (etype)
         {
            case e_type_float:
               m_f *= payload.as_float();
               break;
            case e_type_double:
               m_d *= payload.as_double();
               break;
            case e_type_pfloat:
               *m_pf *= payload.as_float();
               break;
            case e_type_pdouble:
               *m_pd *= payload.as_double();
               break;
            default:
               throw ::exception(error_unexpected, "unexpected result from cast/promotion");
         };

      } else if (payload.is_floating())
      {

         auto etype = maximum(left_hand_floating_type(), payload.floating_type());

         if (etype != get_type())
         {

            set_type(etype);

         }

         switch (etype)
         {
            case e_type_float:
               m_f *= payload.as_float();
               break;
            case e_type_double:
               m_d *= payload.as_double();
               break;
            case e_type_pfloat:
               *m_pf *= payload.as_float();
               break;
            case e_type_pdouble:
               *m_pd *= payload.as_double();
               break;
            default:
               throw ::exception(error_unexpected, "unexpected result from cast/promotion");
         };


      }
      else if (payload.is_text())
      {

         operator= (as_file_path().folder() / payload.as_file_path().name());

      }
      else
      {

         throw ::not_implemented("yet to be done");

      }

   }
   else if (payload.is_text())
   {

      operator= (as_file_path().folder() / payload.as_file_path().name());

   }
   else
   {

      throw ::not_implemented("yet to be done");

   }

   return *this;

}

   
payload &  payload::divide(const ::payload & payload)
{

   if(is_integer())
   {

      if(payload.is_integer())
      {

         auto etype = maximum(left_hand_integer_type(), payload.integer_type());

         if(etype != get_type())
         {

            set_type(etype);

         }

         switch(etype)
         {
            case e_type_unsigned_char:
               if((unsigned short) m_uch + (unsigned short) payload.as_unsigned_char() >= 256)
               {
                  set_type(e_type_unsigned_short);
                  m_ush /= payload.as_unsigned_char();
               }
               else
               {
                  m_uch /= payload.as_unsigned_char();
               }
               break;
            case e_type_char:
               if((short) m_ch + (short) payload.as_char() >= 129)
               {
                  set_type(e_type_short);
                  m_sh /= payload.as_char();
               }
               else
               {
                  m_ch /= payload.as_char();
               }
               break;
            case e_type_unsigned_short:
               if((unsigned int) m_ush + (unsigned int) payload.as_unsigned_short() >= 65536)
               {
                  set_type(e_type_unsigned_int);
                  m_ui /= payload.as_unsigned_short();
               }
               else
               {
                  m_ush /= payload.as_unsigned_short();
               }
               break;
            case e_type_short:
               if((int) m_sh + (int) payload.as_short() >= 32769)
               {
                  set_type(e_type_int);
                  m_i /= payload.as_short();
               }
               else
               {
                  m_sh /= payload.as_short();
               }
               break;
            case e_type_unsigned_int:
               if((unsigned long long) m_ui + (unsigned long long) payload.as_unsigned_int() >= 65536)
               {
                  set_type(e_type_unsigned_long_long);
                  m_hn /= payload.as_unsigned_int();
               }
               else
               {
                  m_ui /= payload.as_unsigned_int();
               }
               break;
            case e_type_int:
               if((long long) m_i + (long long) payload.as_int() >= 64769)
               {
                  set_type(e_type_long_long);
                  m_hi /= payload.as_int();
               }
               else
               {
                  m_i /= payload.as_int();
               }
               break;
            case e_type_unsigned_long_long:
               m_hn /= payload.as_unsigned_long_long();
               break;
            case e_type_long_long:
               m_hi /= payload.as_long_long();
               break;
            case e_type_punsigned_char:
               *m_puch /= payload.as_unsigned_char();
               break;
            case e_type_pchar:
               *m_pch /= payload.as_char();
               break;
            case e_type_punsigned_short:
               *m_push /= payload.as_unsigned_short();
               break;
            case e_type_pshort:
               *m_psh /= payload.as_short();
               break;
            case e_type_punsigned_int:
               *m_pui /= payload.as_unsigned_int();
               break;
            case e_type_pint:
               *m_pi /= payload.as_int();
               break;
            case e_type_punsigned_long_long:
               *m_pull /= payload.as_unsigned_long_long();
               break;
            case e_type_plong_long:
               *m_pll /= payload.as_long_long();
               break;
            default:
               throw ::exception(error_unexpected, "unexpected result from cast/promotion");
         };

      }
      else if(payload.is_floating())
      {

         auto etype = maximum(left_hand_integer_type(), payload.floating_type());

         if(etype != get_type())
         {

            set_type(etype);

         }

         switch(etype)
         {
            case e_type_float:
               m_f /= payload.as_unsigned_int();
               break;
            case e_type_double:
               m_d /= payload.as_double();
               break;
            case e_type_punsigned_char:
               *m_puch /= payload.as_unsigned_char();
               break;
            case e_type_pchar:
               *m_pch /= payload.as_char();
               break;
            case e_type_punsigned_short:
               *m_push /= payload.as_unsigned_short();
               break;
            case e_type_pshort:
               *m_psh /= payload.as_short();
               break;
            case e_type_punsigned_int:
               *m_pui /= payload.as_unsigned_int();
               break;
            case e_type_pint:
               *m_pi /= payload.as_int();
               break;
            case e_type_punsigned_long_long:
               *m_pull /= payload.as_unsigned_long_long();
               break;
            case e_type_plong_long:
               *m_pll /= payload.as_long_long();
               break;
            default:
               throw ::exception(error_unexpected, "unexpected result from cast/promotion");

         };

      }
      else if(payload.is_text())
      {

         operator= (as_file_path() / payload.as_file_path());

      }
      else
      {

         throw ::not_implemented("yet to be done");

      }

   }
   else if(is_floating())
   {

      if(payload.is_integer())
      {

         auto etype = maximum(left_hand_floating_type(), payload.integer_type());

         if(etype != get_type())
         {

            set_type(etype);

         }

         switch(etype)
         {
            case e_type_float:
               m_f /= payload.as_float();
               break;
            case e_type_double:
               m_d /= payload.as_double();
               break;
            case e_type_pfloat:
               *m_pf /= payload.as_float();
               break;
            case e_type_pdouble:
               *m_pd /= payload.as_double();
               break;
            default:
               throw ::exception(error_unexpected, "unexpected result from cast/promotion");
         };

      }
      else if(payload.is_floating())
      {

         auto etype = maximum(left_hand_floating_type(), payload.floating_type());

         if(etype != get_type())
         {

            set_type(etype);

         }

         switch(etype)
         {
            case e_type_float:
               m_f /= payload.as_float();
               break;
            case e_type_double:
               m_d /= payload.as_double();
               break;
            case e_type_pfloat:
               *m_pf /= payload.as_float();
               break;
            case e_type_pdouble:
               *m_pd /= payload.as_double();
               break;
            default:
               throw ::exception(error_unexpected, "unexpected result from cast/promotion");
         };


      }
      else if(payload.is_text())
      {

         operator= (as_file_path() / payload.as_file_path());

      }
      else
      {

         throw ::not_implemented("yet to be done");

      }

   }
   else if(payload.is_text())
   {

      operator= (as_file_path() / payload.as_file_path());

   }
   else
   {

      throw ::not_implemented("yet to be done");

   }

   return *this;

}






CLASS_DECL_ACME ::string & copy(::string & str, const ::payload * ppayload)
{

   return str = ppayload->as_string();

}

bool payload::begins(const ::scoped_string & scopedstrPrefix) const
{

   return this->as_string().begins(scopedstrPrefix);

}


bool payload::ends(const ::scoped_string & scopedstrSuffix) const
{

   return this->as_string().ends(scopedstrSuffix);

}


bool payload::case_insensitive_begins(const ::scoped_string & scopedstrPrefix) const
{

   return this->as_string().case_insensitive_begins(scopedstrPrefix);

}

bool payload::case_insensitive_ends(const ::scoped_string & scopedstrSuffix) const
{

   return this->as_string().case_insensitive_ends(scopedstrSuffix);

}


//template < primitive_payload PAYLOAD, primitive_number NUMBER >
//inline void copy(PAYLOAD * ppayload, const NUMBER * pnumber)
//{
//
//   *ppayload = *pnumber;
//
//}

void test_payload()
{

   ::payload payload1("payload1");

   ::payload payload2("payload2");


   ::payload payload3 = payload1 + payload2;


}

//
//property & payload::get_property(const_char_pointer psz)
//{
//
//   return propset().get(scopedstr);
//
//}



// CLASS_DECL_ACME::string as_string(const ::payload & payload)
// {
//
//    return payload.as_string();
//
// }


CLASS_DECL_ACME subparticle * as_subparticle(const payload & payload)
{
   
   return payload.as_subparticle();
   
}



