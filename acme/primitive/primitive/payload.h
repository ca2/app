#pragma once


#include "type.h"
#include "acme/primitive/datetime/earth_time.h"
#include "acme/primitive/datetime/file_time.h"
#include "acme/primitive/time/time/posix_time.h"
#include "acme/graphics/draw2d/color.h"
#include "pointer.h"
#include "acme/memory/memory.h"
#include "acme/memory/raw_block.h"
#include "acme/platform/procedure.h"
#include "acme/primitive/collection/numeric_array.h"
#include "acme/filesystem/filesystem/path_object.h"
#include  "acme/filesystem/filesystem/path_array.h"
//#include "acme/primitive/datetime/file_time.h"
#include "acme/primitive/string/sz.h"
#include "acme/primitive/primitive/make_particle.h"




inline payload & copy(payload & payload, const class time & time);


enum para_return
{
   e_fail = I32_MINIMUM,
   s_success = 0
};

//class future;
//class function_arg;

bool is_return_ok(para_return eret);

template < typename ENUM >
ENUM enum_default()
{

   return (ENUM)0;

}

struct payload_all_t
{

   ::u8     m_ua[32];

};


class CLASS_DECL_ACME payload
{
public:


   using PRIMITIVE_PAYLOAD_TAG = PRIMITIVE_PAYLOAD_TAG_TYPE;


   enum_type                        m_etype;


   union
   {

      void * m_pvoid;
      para_return                            m_parareturn;
      atom                                   m_atom;
      type_atom                              m_typeatom;
      bool                                   m_b;
      bool * m_pb;
      ::i8                                   m_i8;
      ::u8                                   m_u8;
      ::i16                                  m_i16;
      ::u16                                  m_u16;
      ::i32                                  m_i32;
      ::u32                                  m_u32;
      ::i64                                  m_i64;
      ::u64                                  m_u64;
      ::i8 * m_pi8;
      ::u8 * m_pu8;
      ::i16 * m_pi16;
      ::u16 * m_pu16;
      ::i32 * m_pi32;
      ::u32 * m_pu32;
      ::i64 * m_pi64;
      ::u64 * m_pu64;
      ::string * m_pstr;
      ::f32                                  m_f32;
      ::f32 * m_pf32;
      ::f64                                  m_f64;
      ::f64 * m_pf64;
      //payload * m_ppayload;
      ::earth::time                          m_earthtime;
      file_time                              m_filetime;
      atom * m_patom;
      //::property * m_pproperty;
      //integral_nanosecond                    m_integralnanosecond;
      //integral_nanosecond *                  m_pintegralnanosecond;
      //integral_microsecond                   m_integralmicrosecond;
      //integral_microsecond *                 m_pintegralmicrosecond;
      //integral_millisecond                   m_integralmillisecond;
      //integral_millisecond *                 m_pintegralmillisecond;
      //integral_second                        m_integralsecond;
      //integral_second *                      m_pintegralsecond;
      //integral_minute                        m_integralminute;
      //integral_minute *                      m_pintegralminute;
      //integral_hour                          m_integralhour;
      //integral_hour *                        m_pintegralhour;
      //integral_day                           m_integralday;
      //integral_day *                         m_pintegralday;
      //floating_nanosecond                    m_floatingnanosecond;
      //floating_nanosecond *                  m_pfloatingnanosecond;
      //floating_microsecond                   m_floatingmicrosecond;
      //floating_microsecond *                 m_pfloatingmicrosecond;
      //floating_millisecond                   m_floatingmillisecond;
      //floating_millisecond *                 m_pfloatingmillisecond;
      //floating_second                        m_floatingsecond;
      //floating_second *                      m_pfloatingsecond;
      //floating_minute                        m_floatingminute;
      //floating_minute *                      m_pfloatingminute;
      //floating_hour                          m_floatinghour;
      //floating_hour *                        m_pfloatinghour;
      //floating_day                           m_floatingday;
      //floating_day *                         m_pfloatingday;
      class time                             m_time;
      class time * m_ptime;
      //::e_status                             m_estatus;
      //::e_command                            m_ecommand;
      //::e_check                              m_echeck;
      //::e_flag                               m_eflag;
      ::color::color                         m_color;
      ::color::hls                           m_hls;


      ::subparticle * m_p;
      ::string_array * m_pstra;
      ::i32_array  * m_pia;
      ::payload_array  * m_ppayloada;
      ::property_set  * m_ppropertyset;
      ::i64_array * m_pi64a;
      ::memory * m_pmemory;
      ::file::path_object * m_ppath;
      payload_all_t                          m_payloadall;
      ::string                               m_str;
      ::range < const ::ansi_character * >   m_ansirange;
      ::function_common * m_pfunctioncommon;

   };


#if REFERENCING_DEBUGGING

   
   ::reference_referer * m_preferer;


#endif


   payload();
   payload(no_initialize_t) {}
   payload(enum_type etype);
   payload(std::nullptr_t);
   payload(const ::payload & payload);
   payload(::payload && payload) :
      m_etype(payload.m_etype)
   {
      m_payloadall = payload.m_payloadall;
      payload.m_etype = e_type_new;
      payload.m_payloadall = {};
   }
   template < bool_type BOOL > payload(BOOL b) : m_etype(e_type_bool) {m_b = b;}
   template < char_type CHAR > payload(CHAR c) : m_etype(e_type_i8) {m_i8 = c;}
   template < i8_type I8 > payload(I8 i) : m_etype(e_type_i8) {m_i8 = i;}
   template < same_as < ::u8 > U8 > payload(U8 u) : m_etype(e_type_u8) {m_u8 = u;}
   template < same_as < ::i16 > I16 > payload(I16 i) : m_etype(e_type_i16) {m_i16 = i;}
   template < same_as < ::u16 > U16 > payload(U16 u) : m_etype(e_type_u16) {m_u16 = u;}
   template < same_as < ::i32 > I32 > payload(I32 i) : m_etype(e_type_i32) {m_i32 = i;}
   template < same_as < ::u32 > U32 > payload(U32 u) : m_etype(e_type_u32) {m_u32 = u;}
   template < same_as < ::i64 > I64 > payload(I64 i) : m_etype(e_type_i64) {m_i64 = i;}
   template < same_as < ::u64 > U64 > payload(U64 u) : m_etype(e_type_u64) {m_u64 = u;}
   template < same_as < ::f32 > F32 > payload(F32 f) : m_etype(e_type_f32) {m_f32 = f;}
   template < same_as < ::f64 > F64 > payload(F64 f) : m_etype(e_type_f64) {m_f64 = f;}
#ifdef __APPLE__
#ifdef OS64BIT
   payload(long l);
#endif
#endif
   payload(::i32 * pi);
   payload(::u32 * pu);
   payload(::i64 * pi);
   payload(::u64 * pu);
   payload(bool * pb);
   payload(::string * pstr);
   //payload(::payload * ppayload);
   //payload(::property * pproperty);
   payload(::subparticle * pparticle);
   payload(class ::time * ptime);
   template < character_range CHARACTER_RANGE >
   payload(const CHARACTER_RANGE & range);
   //template < ::collection::count count >
   //payload(const ::ansi_character(&sz)[count]) : payload((const ::ansi_character *)sz, count) {}
   template < primitive_integral INTEGRAL >
   payload(const ::ansi_character * begin, INTEGRAL count) : payload(begin, begin + count) {}
   payload(const ::ansi_character * begin, const ::ansi_character * end);
   payload(const ::ansi_character * psz);
   payload(const ::string & str);
   payload(const ::type_atom & typeatom);
   payload(const ::atom & atom);
   payload(const ::earth::time & time);
   payload(const ::color::color & color);
   payload(const ::color::hls & hls);
   payload(const ::subparticle & particle);
   payload(const ::file::path & path);
   payload(const ::string_array & stra);
   payload(const ::i32_array & ia);
   payload(const ::payload_array & payloada);
   payload(const ::property_set & set);
   //payload(const ::property & property);
   payload(const class time & time);

   //   payload(const ::block & block)
   //   {
   //      m_etype = e_type_new;
   //      operator = (block);
   //   }

   template < class T >
   payload(const ::pointer < T > & p)
   {

      m_etype = e_type_new;

      _set_element(p.m_psubparticle);

   }

   //template < class T >
   //payload(const pointer < T > & p)
   //{
   //   m_etype = e_type_new;
   //   //operator = (p.m_p);
   //   _set_element((T *)p.m_p);
   //}

   //template < class T >
   //payload(const pointer < T >& resultpointer)
   //{
   //   m_etype = e_type_new;

   //   operator = (resultpointer);

   //}

   template < typename BLOCK_TYPE >
   payload(const ::raw_block < BLOCK_TYPE > & rawblock)
   {
      m_etype = e_type_new;
      operator = (rawblock.block());
   }

   //   template < primitive_character CHARACTER2, strsize sizeMaximumLength >
   //   payload(const ::inline_string < CHARACTER2, sizeMaximumLength > & inlinestring) :
   //      payload(::string(inlinestring))
   //   {
   //   }

      //template < typename ENUM >
      //payload(const ::enumeration < ENUM > & eflag)
      //{
      //   m_etype = e_type_new;
      //   operator = (eflag);
      //}

      //template < a_enum ENUM >
      //payload(const ENUM & eenum)
      //{
      //   m_etype = e_type_new;
      //   operator = (eenum);
      //}

   //   template < typename T >
   //   payload(const T & t)
   //   {
   //      m_etype = e_type_new;
   //      operator = (t);
   //   }

   template < primitive_enum ENUM >
   payload(ENUM e) :
   m_etype(e_type_atom),
   m_atom(e)
   {

   }

   ~payload();


   void clear_data() { m_etype = e_type_null; }


   void set_type(enum_type enum_type, bool bConvert = true);
   enum_type get_type() const;
   atom::enum_type atom_type() const;


   void set_type(const ::type_atom & typeatom);


   template < typename T >
   void set_pointer(const ::pointer < T > & p)
   {

      operator[](::type < T >().name()) = p;

   }

   template < typename T >
   bool has_pointer() const
   {

      return has_property(::type < T >().name());

   }

   template < typename T >
   ::property * find_pointer() const
   {

      return find_property(::type < T >().name());

   }

   template < typename TYPE >
   ::pointer < TYPE > pointer() const;

   bool get_type(::type_atom & typeatom) const;

   ::i64 payload_release();

   ::i64 logical_release();

   void _set_element(::subparticle * pelement);

   bool is_element() const { return m_etype >= e_type_element && m_etype < e_type_last_element; }

   bool is_element_set() const { return is_element() && ::is_set(m_p); }

   bool is_element_null() const { return is_element() && ::is_null(m_p); }

   bool is_numeric() const;


   bool has_reference_of_type(enum_type type) const;


   inline bool is_number() const
   {

      return is_numeric();

   }

   bool target_constrained_assign(const ::payload & payload);


   bool                             get_bool(bool bDefault = false)     const;

   template < typename ENUM >
   ENUM                             e(ENUM edefault = enum_default < ENUM >())  const { return (ENUM)i64(edefault); }

//#define DECL_VAR_FLAG(ENUMTYPE) \
//inline payload(::enum_ ## ENUMTYPE e ## ENUMTYPE) { m_etype = ::e_type_enum_ ## ENUMTYPE; m_e ## ENUMTYPE = e ## ENUMTYPE; } \
//inline ::enum_ ## ENUMTYPE e ## ENUMTYPE(::enum_ ## ENUMTYPE e ## ENUMTYPE ## Default = enum_default < ::enum_ ## ENUMTYPE >()) const { return e < ::enum_ ## ENUMTYPE >(e ## ENUMTYPE ## Default); } \
//::enum_ ## ENUMTYPE & as_e ## ENUMTYPE ();         \
//inline payload & operator = (::enum_ ## ENUMTYPE e ## ENUMTYPE)  { release(); if(m_etype != ::e_type_enum_ ## ENUMTYPE) m_etype = ::e_type_enum_ ## ENUMTYPE; m_e ## ENUMTYPE = e ## ENUMTYPE; return *this; } \
//inline bool operator == (::enum_ ## ENUMTYPE e ## ENUMTYPE) const { return m_etype == ::e_type_enum_ ## ENUMTYPE && m_e ## ENUMTYPE == e ## ENUMTYPE; }
//#undef DECL_VAR_FLAG
//


//#define DECL_VAR_ENUM(ENUMTYPE) \
//   inline explicit payload(const ::e_ ## ENUMTYPE & e) { m_etype = ::e_type_enum_ ## ENUMTYPE; m_e ## ENUMTYPE = e; } \
//   inline explicit payload(::enum_ ## ENUMTYPE e) { m_etype = ::e_type_enum_ ## ENUMTYPE; m_e ## ENUMTYPE = e; } \
//   inline ::e_ ## ENUMTYPE e ## ENUMTYPE(::enum_ ## ENUMTYPE eDefault = enum_default < ::enum_ ## ENUMTYPE >()) const { return e < ::enum_ ## ENUMTYPE >(eDefault); } \
//   inline operator ::e_ ## ENUMTYPE () const { return ::e_ ## ENUMTYPE(); } \
//   ::e_ ## ENUMTYPE & e_ ## ENUMTYPE ## _reference();         \
//   inline payload & operator = (const ::e_ ## ENUMTYPE & e) &{ set_type(::e_type_enum_ ## ENUMTYPE, false); m_e ## ENUMTYPE = e; return *this; } \
//   inline payload & operator = (::enum_ ## ENUMTYPE e) { set_type(::e_type_enum_ ## ENUMTYPE, false); m_e ## ENUMTYPE = e; return *this; } \
//   inline bool equals_enum (::e_ ## ENUMTYPE e) const { return m_etype == ::e_type_enum_ ## ENUMTYPE && m_e ## ENUMTYPE == e; }
//   DECL_VAR_ENUM(status);
//   DECL_VAR_ENUM(command);
//   DECL_VAR_ENUM(check);
//#undef DECL_VAR_ENUM


#define IMPLEMENT_PAYLOAD_ENUMERATION(ENUMTYPE) \
   inline payload(const ::e_ ## ENUMTYPE & e) : m_etype(e_type_atom),m_atom(e) { } \
   inline ::e_ ## ENUMTYPE as_e ## ENUMTYPE() const { return as_atom().as_e ## ENUMTYPE(); } \
   inline ::e_ ## ENUMTYPE & e ## ENUMTYPE ## _reference() { return atom_reference().e ## ENUMTYPE ## _reference(); }
   IMPLEMENT_PAYLOAD_ENUMERATION(status);
   IMPLEMENT_PAYLOAD_ENUMERATION(command);
   IMPLEMENT_PAYLOAD_ENUMERATION(check);
#undef IMPLEMENT_PAYLOAD_ENUMERATION


   template < primitive_enum ENUM >
   bool operator ==(ENUM e) const
   {

      if (m_etype == e_type_atom)
      {

         return m_atom == e;

      }
      else if (m_etype == e_type_patom)
      {

         return *m_patom == e;

      }

      return operator == (::as_i64(e));

   }


   //inline ::second & as_secs() { if (get_type() != e_type_secs)set_type(e_type_secs); return m_secs; }
   //inline class ::time & as_millis() { if (get_type() != e_type_millis)set_type(e_type_millis); return m_millis; }
   //inline ::microsecond & as_micros() { if (get_type() != e_type_micros)set_type(e_type_micros); return m_micros; }
   //inline ::nanosecond & as_nanos() { if (get_type() != e_type_nanos)set_type(e_type_nanos); return m_nanos; }

   void as(::string & str) const;
   void as(::memory_base & memory) const;


#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBERRYPIOS) || defined(WINDOWS)
   long get_long(long lDefault = 0) const;
   unsigned long get_unsigned_long(unsigned long ulDefault = 0) const;
#endif

   ::i8 & as(::i8 & i) const { return i = as_i8(); }
   ::u8 & as(::u8 & u) const { return u = as_u8(); }
   ::i16 & as(::i16 & i) const { return i = as_i16(); }
   ::u16 & as(::u16 & u) const { return u = as_u16(); }
   ::i32 & as(::i32 & i)  const { return i = as_i32(); }
   ::u32 & as(::u32 & u)  const { return u = as_u32(); }
   ::i64 & as(::i64 & i)  const { return i = as_i64(); }
   ::u64 & as(::u64 & u)  const { return u = as_u64(); }
   ::f32 & as(::f32 & f) const { return f = as_f32(); }
   ::f64 & as(::f64 & f) const { return f = as_f64(); }


   ::i8 as_i8(::i8 iDefault = 0) const;
   ::u8 as_u8(::u8 uDefault = 0) const;
   ::i16 as_i16(::i16 iDefault = 0) const;
   ::u16 as_u16(::u16 uDefault = 0) const;
   ::i32 as_i32(::i32 iDefault = 0)  const;
   ::u32 as_u32(::u32 uiDefault = 0)  const;
   ::i64 as_i64(::i64 iDefault = 0)  const;
   ::u64 as_u64(::u64 uiDefault = 0)  const;
   ::f32 as_f32(::f32 fDefault = 0) const;
   ::f64 as_f64(::f64 fDefault = 0) const;


   inline ::iptr as_iptr(::iptr iDefault = 0)  const;
   inline ::uptr as_uptr(::uptr uiDefault = 0)  const;

   ::file::path as_file_path() const;
   ::url::url as_url() const;
   ::file_time as_file_time() const;
   ::earth::time as_earth_time() const;
   ::color::color as_color(const ::color::color & colorDefault = ::color::color())  const;
   ::color::hls as_hls(const ::color::hls & hlsDefault = ::color::hls())  const;
   ::block as_block() const;


   ::procedure get_procedure() const;


   ::posix_time as_posix_time(::i64 iDefault = 0) const
   {

      return { posix_time_t{}, this->as_i64() };

   }


   ::posix_time as_time(const class ::time & timeDefault) const;

   ::string as_string(const ::scoped_string & scopedstrOnNull) const;
   ::string as_string() const;
   ::string get_recursive_string() const;
   ::atom as_atom() const;
   ::atom as_atom(const ::atom & idDefault) const;

   ::memory as_memory() const;
   ::string_array as_string_array() const;
   ::i32_array as_i32_array() const;
   ::i64_array as_i64_array() const;
   ::payload_array as_payload_array()  const;
   ::property_set as_property_set() const;
   class ::time as_time() const;
   //::property as_property() const;


   bool is_scalar() const;
   bool is_array() const;
   bool is_floating() const;
   bool is_integer() const;
   bool is_natural() const;
   bool is_boolean() const;
   bool is_double() const;
   bool is_time() const;
   bool is_text() const;
   bool is_fairly_convertible_to_text() const;
   bool has_string_reference() const;

   bool ok() const;
   bool failed() const;


   enum_type integer_type() const;
   enum_type left_hand_integer_type() const;

   enum_type floating_type() const;
   enum_type left_hand_floating_type() const;


   payload dereference();





   //::comparison::var_strict strictly_compare() const;

   //void set_string(const ::const_ansi_range & ansirange);
   void set_string(const ::string & str);
   void set_string(::string && str);
   void set_id(const ::atom & atom);
   void unset();
   void unset(const ::string & strPropertySetKey);

   bool is_set() const;
   bool is_new() const;
   bool is_null() const;
   bool is_new_or_null() const;
   bool is_empty() const;
   bool has_char() const;

   bool is_false() const;
   bool is_bool_false() const;
   bool is_set_false() const;
   bool is_true(bool bDefault = false) const;

   //bool is_property_true(const ::atom & atom, bool bDefault = false) const;

   bool casts_to(::enum_type etype) const;


   ///property * defer_get_property(const ::atom & atom) const;
   bool has_property(const ::atom & atom) const;
   bool is_property_true(const ::atom & atom, bool bDefault = false) const;
   bool is_property_false(const ::atom & atom) const;


   bool begins(const ::string & strPrefix) const;
   bool ends(const ::string & strSuffix) const;
   bool case_insensitive_begins(const ::string & strPrefix) const;
   bool case_insensitive_ends(const ::string & strSuffix) const;

   bool begins_eat(const ::string & strPrefix);
   bool ends_eat(const ::string & strSuffix);
   bool case_insensitive_begins_eat(const ::string & strPrefix);
   bool case_insensitive_ends_eat(const ::string & strSuffix);

   payload get_topic(const ::atom & atom) const;
   //payload defer_get(const ::atom & atom) const;

   payload & operator ++(::i32);

   //payload operator +(const ::payload & payload) const;
   payload operator -(const ::payload & payload) const;
   payload operator *(const ::payload & payload) const;
   payload operator /(const ::payload & payload) const;

   //payload & operator +=(const ::payload & payload);
   payload & operator -=(const ::payload & payload);
   payload & operator *=(const ::payload & payload);
   payload & operator /=(const ::payload & payload);


   payload addition(const ::payload & payload) const;
   payload subtraction(const ::payload & payload) const;
   payload multiplication(const ::payload & payload) const;
   payload division(const ::payload & payload) const;

   payload & add(const ::payload & payload);
   payload & subtract(const ::payload & payload);
   payload & multiply(const ::payload & payload);
   payload & divide(const ::payload & payload);

   bool operator !() const
   {

      return !as_bool();

   }


   bool as_bool() const;

   operator bool() const { return this->as_bool(); }

   operator ::i8() const { return this->as_i8(); }
   operator ::u8() const { return this->as_u8(); }
   operator ::i16() const { return this->as_i16(); }
   operator ::u16() const { return this->as_u16(); }
   operator ::i32() const { return this->as_i32(); }
   operator ::u32() const { return this->as_u32(); }
   operator ::i64() const { return this->as_i64(); }
   operator ::u64() const { return this->as_u64(); }



   operator ::f32() const { return this->as_f32(); }
   operator ::f64() const { return this->as_f64(); }
   //operator ::string() const;
   //::memory memory() const;
   //operator ::file::path() const { return this->as_file_path(); }


   //operator ::string() const { return this->as_string(); }
   //operator ::file::path() const { return this->file_path(); }

   operator ::file_time() const { return this->as_file_time(); }
   operator ::earth::time() const { return this->as_earth_time(); }
   operator ::color::color() const { return this->as_color(); }
   operator ::color::hls() const { return this->as_hls(); }
   operator ::block() const { return this->as_block(); }

   ::string & string_reference();

   ::memory & memory_reference();


   ::atom & atom_reference();


   ::string_array & string_array_reference();
   ::i32_array & i32_array_reference();
   ::i64_array & i64_array_reference();
   ::payload_array & payload_array_reference();
   class ::time & time_reference();
   ::property_set & property_set_reference();
   //::property & property_reference();

   ::file::path & file_path_reference();

   ::file_time & file_time_reference();
   ::earth::time & earth_time_reference();
   ::color::color & color_reference();
   ::color::hls & color_hls_reference();

   const ::string_array & string_array_reference() const;
   const ::i32_array & i32_array_reference() const;
   const ::i64_array & i64_array_reference() const;
   const ::payload_array & payload_array_reference() const;
   const class time & time_reference() const;
   const ::property_set & property_set_reference() const;
   const ::property & property_reference() const;




   const ::file::path & file_path_reference() const;
   const ::file_time & file_time_reference() const;
   const ::earth::time & earth_time_reference() const;
   const ::color::color & color_reference() const;
   const ::color::hls & color_hls_reference() const;


   //operator ::enum_check &();


   bool & bool_reference();
#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBERRYPIOS) || defined(WINDOWS)
   long & long_reference();
   unsigned long & unsigned_long_reference();
#endif
   ::i8 & i8_reference();
   ::u8 & u8_reference();
   ::i16 & i16_reference();
   ::u16 & u16_reference();
   ::i32 & i32_reference();
   ::u32 & u32_reference();
   ::i64 & i64_reference();
   ::u64 & u64_reference();
   ::f32 & f32_reference();
   ::f64 & f64_reference();


   template < primitive_signed SIGNED >
   inline SIGNED & reference()
   {

      if constexpr(sizeof(SIGNED) == 8)
      {

         return (SIGNED&) this->i64_reference();

      }
      else if constexpr(sizeof(SIGNED) == 4)
      {

         return (SIGNED&) this->i32_reference();

      }
      else if constexpr(sizeof(SIGNED) == 2)
      {

         return (SIGNED&) this->i16_reference();

      }
      else if constexpr(sizeof(SIGNED) == 1)
      {

         return (SIGNED&) this->i8_reference();

      }
      else
      {

         throw "todo";

      }


   }


   template < primitive_unsigned UNSIGNED >
   inline UNSIGNED & reference()
   {

      if constexpr(sizeof(UNSIGNED) == 8)
      {

         return (UNSIGNED&) this->u64_reference();

      }
      else if constexpr(sizeof(UNSIGNED) == 4)
      {

         return (UNSIGNED&) this->u32_reference();

      }
      else if constexpr(sizeof(UNSIGNED) == 2)
      {

         return (UNSIGNED&) this->u16_reference();

      }
      else if constexpr(sizeof(UNSIGNED) == 1)
      {

         return (UNSIGNED&) this->u8_reference();

      }
      else
      {

         throw "todo";

      }


   }


   template < primitive_const CONST_TYPE >
   CONST_TYPE & reference() const
   {

      return (CONST_TYPE &) ((::payload*)this)->reference<non_const<CONST_TYPE>>();

   }


   template < primitive_non_const NON_CONST_TYPE >
   NON_CONST_TYPE * raw_pointer()
   {

      return &reference<NON_CONST_TYPE>();

   }


   template < primitive_const CONST_TYPE >
   CONST_TYPE * raw_pointer() const
   {

      return &reference<CONST_TYPE>();

   }


   strsize length() const;


   template < typename TYPE >
   inline payload & operator = (const ::pointer<TYPE> & pointer)
   {

      _set_element(pointer.m_psubparticle);

      return *this;

   }

   template < primitive_function FUNCTION >
   inline payload & operator = (const FUNCTION & function)
   {

      _set_element(function.m_pbase);

      return *this;

   }

   inline payload & operator = (nullptr_t){ set_type(e_type_null, false); return *this; }

   inline payload & operator = (::subparticle * pelement)
   {

      _set_element(pelement);

      return *this;

   }



   payload & operator = (::memory * pmemory);

   template < typename PREDICATE >
   void predicate_each(PREDICATE predicate)
   {

      auto c = array_get_count();

      for (auto i = 0; i < c; i++)
      {

         predicate(at(i));

      }

   }


   void payload_increment_reference_count();




   payload & operator = (const ::subparticle & o);

   payload & operator = (const ::file::path & path);

   //template < typename ENUM >
   //payload& operator = (const enumeration < ENUM > & eflag)
   //{
   //   return operator =(eflag.m_eenum);
   //}

   //template < a_enum ENUM >
   //payload & operator = (const ENUM & eenum)
   //{
   //   return operator =((::i64) eenum);
   //}

   payload & operator |= (enumeration < ::file::enum_flag > eflag);

   //payload& operator = (const ::e_status & estatus)
   //{
   //   return operator =(estatus.m_estatus);
   //}

   //payload & operator = (const payload & eret);

   payload & operator = (para_return & eret);
#ifdef WINDOWS
#elif defined(__APPLE__) || defined(ANDROID) || defined(RASPBERRYPIOS)
   payload & operator = (long l);
#endif


   payload & assign_bool   (bool     b)   { return __assign_primitive(m_b   , e_type_bool  , b ); }
   payload & assign_i8     (::i8     i)   { return __assign_primitive(m_i8  , e_type_i8    , i ); }
   payload & assign_u8     (::u8     u)   { return __assign_primitive(m_u8  , e_type_u8    , u ); }
   payload & assign_i16    (::i16    i)   { return __assign_primitive(m_i16 , e_type_i16   , i ); }
   payload & assign_u16    (::u16    u)   { return __assign_primitive(m_u16 , e_type_u16   , u ); }
   payload & assign_i32    (::i32    i)   { return __assign_primitive(m_i32 , e_type_i32   , i ); }
   payload & assign_u32    (::u32    u)   { return __assign_primitive(m_u32 , e_type_u32   , u ); }
   payload & assign_i64    (::i64    i)   { return __assign_primitive(m_i64 , e_type_i64   , i ); }
   payload & assign_u64    (::u64    u)   { return __assign_primitive(m_u64 , e_type_u64   , u ); }
   payload & assign_f32    (::f32    f)   { return __assign_primitive(m_f32 , e_type_f32   , f ); }
   payload & assign_f64    (::f64    f)   { return __assign_primitive(m_f64 , e_type_f64   , f ); }


   payload & assign_pbool  (bool  * pb)   { return __assign_primitive_pointer(m_pb     , e_type_pbool , pb); }
   payload & assign_pi8    (::i8  * pi)   { return __assign_primitive_pointer(m_pi8    , e_type_pi8   , pi); }
   payload & assign_pu8    (::u8  * pu)   { return __assign_primitive_pointer(m_pu8    , e_type_pu8   , pu); }
   payload & assign_pi16   (::i16 * pi)   { return __assign_primitive_pointer(m_pi16   , e_type_pi16  , pi); }
   payload & assign_pu16   (::u16 * pu)   { return __assign_primitive_pointer(m_pu16   , e_type_pu16  , pu); }
   payload & assign_pi32   (::i32 * pi)   { return __assign_primitive_pointer(m_pi32   , e_type_pi32  , pi); }
   payload & assign_pu32   (::u32 * pu)   { return __assign_primitive_pointer(m_pu32   , e_type_pu32  , pu); }
   payload & assign_pi64   (::i64 * pi)   { return __assign_primitive_pointer(m_pi64   , e_type_pi64  , pi); }
   payload & assign_pu64   (::u64 * pu)   { return __assign_primitive_pointer(m_pu64   , e_type_pu64  , pu); }
   payload & assign_pf32   (::f32 * pf)   { return __assign_primitive_pointer(m_pf32   , e_type_pf32  , pf); }
   payload & assign_pf64   (::f64 * pf)   { return __assign_primitive_pointer(m_pf64   , e_type_pf64  , pf); }

protected:


   template < typename PRIMITIVE >
   bool __assign_to_held_pointer_member(PRIMITIVE primitive)
   {

      if(get_type() == e_type_pbool)
      {

         *m_pb = (bool) primitive;

      }
      else if(get_type() == e_type_pu8)
      {

         *m_pu8 = (::u8) primitive;

      }
      else if(get_type() == e_type_pi8)
      {

         *m_pi8 = (::i8) primitive;

      }
      else if(get_type() == e_type_pu16)
      {

         *m_pu16 = (::u16) primitive;

      }
      else if(get_type() == e_type_pi16)
      {

         *m_pi16 = (::i16) primitive;

      }
      else if(get_type() == e_type_pu32)
      {

         *m_pu32 = (::u32) primitive;

      }
      else if(get_type() == e_type_pi32)
      {

         *m_pi32 = (::i32) primitive;

      }
      else if(get_type() == e_type_pu64)
      {

         *m_pu64 = (::u64) primitive;

      }
      else if(get_type() == e_type_pi64)
      {

         *m_pi64 = (::i64) primitive;

      }
      else if(get_type() == e_type_pf32)
      {

         *m_pf32 = (::f32) primitive;

      }
      else if(get_type() == e_type_pf64)
      {

         *m_pf64 = (::f64) primitive;

      }
      else
      {

         return false;

      }

      return true;

   }


   template < typename PRIMITIVE >
   payload& __assign_primitive(PRIMITIVE& member, enum_type etype, PRIMITIVE primitive);


   template < typename PRIMITIVE >
   payload & __assign_primitive_pointer(PRIMITIVE * & member, enum_type etype, PRIMITIVE * pprimitive)
   {

      set_type(etype, false);

      member = pprimitive;

      return *this;

   }


public:
   template < bool_type BOOL > payload & operator=(BOOL b) { return assign_bool(b); }
   template < char_type CHAR > payload & operator=(CHAR c) { return assign_char(c); }
   template < i8_type I8 > payload & operator=(I8 i) { return assign_i8(i); }
   template < same_as < ::u8 > U8 > payload & operator=(U8 u) { return assign_u8(u); }
   template < same_as < ::i16 > I16 > payload & operator=(I16 i) { return assign_i16(i); }
   template < same_as < ::u16 > U16 > payload & operator=(U16 u) { return assign_u16(u); }
   template < same_as < ::i32 > I32 > payload & operator=(I32 i) { return assign_i32(i); }
   template < same_as < ::u32 > U32 > payload & operator=(U32 u) { return assign_u32(u); }
   template < same_as < ::i64 > I64 > payload & operator=(I64 i) { return assign_i64(i); }
   template < same_as < ::u64 > U64 > payload & operator=(U64 u) { return assign_u64(u); }
   template < same_as < ::f32 > F32 > payload & operator=(F32 f) { return assign_f32(f); }
   template < same_as < ::f64 > F64 > payload & operator=(F64 f) { return assign_f64(f); }


   payload & operator=(i8 * pi) { return assign_pi8(pi); }
   payload & operator=(u8 * pu) { return assign_pu8(pu); }
   payload & operator=(i16 * pi) { return assign_pi16(pi); }
   payload & operator=(u16 * pu) { return assign_pu16(pu); }
   payload & operator=(i32 * pi) { return assign_pi32(pi); }
   payload & operator=(u32 * pu) { return assign_pu32(pu); }
   payload & operator=(i64 * pi) { return assign_pi64(pi); }
   payload & operator=(u64 * pu) { return assign_pu64(pu); }
   payload & operator=(f32 * pf) { return assign_pf32(pf); }
   payload & operator=(f64 * pf) { return assign_pf64(pf); }

#ifdef WINDOWS
   payload & operator = (long l);
#endif
   payload & operator = (const ::earth::time & time);
   payload & operator = (const ::color::color & color);
   payload & operator = (const ::color::hls & color);
   inline payload & operator = (const ::scoped_string & scopedstr);
   inline payload & operator = (const ::string & str);
   inline payload & operator = (::string && str);
   inline payload & operator = (::const_ansi_range ansirange);
   inline payload & operator = (const ::inline_number_string & str);
   payload & operator = (::string * pstr);
   //payload & operator = (::payload * pvar);
   //payload & operator = (const ::payload * pvar);
   payload & operator = (const ::wide_character * pcsz);
   payload& operator = (const ::ansi_character* pcsz);

   payload & operator = (const ::property & prop);
   //payload & operator = (const ::property * pproperty);
   payload & operator = (const ::payload & payload);
   payload & operator = (const ::i32_array & ia);
   payload & operator = (const ::string_array & stra);
   payload & operator = (const ::memory & memory);
   payload & operator = (const ::payload_array & payloada);
   payload & operator = (const ::property_set & propset);
   payload & operator = (const ::atom & atom);
   payload & operator = (::atom * pid);
   template < primitive_enum ENUM >
   payload & operator = (ENUM e) { this->operator = ((const ::atom &) e); return *this; }
   //payload & operator = (const ::second & second);
   //payload & operator = (class ::second * ptime);
   //payload & operator = (const class time & time);
   //payload & operator = (class ::time * pmillis);
   //payload & operator = (const ::microsecond & microsecond);
   //payload & operator = (class ::microsecond * pmicros);
   //payload & operator = (const ::nanosecond & nanosecond);
   //payload & operator = (class ::nanosecond * pnanos);
   payload & operator = (const class time & time);
   payload & operator = (class ::time * ptime);
   payload & operator = (const ::block & block);

   template < class ARRAY >
   void get_array(ARRAY & array) const
   {

      auto count = this->array_get_count();

      for (int i = 0; i < count; i++)
      {

         ::payload payloadItem = at(i);

         typename ARRAY::BASE_TYPE typeNewItem;

         ::assign(typeNewItem, payloadItem);

         array.add(typeNewItem);

      }

   }

   //template < class T >
   //payload & operator = (const pointer< T > & p)
   //{

   //   return this->operator = (p.m_p);

   //}

   //template < class T >
   //payload & operator = (const ::pointer < T > & p)
   //{

   //   return this->operator = (p.m_p);

   //}
   //template < class T >
   //payload & operator = (const pointer < T > & resultpointer)
   //{

   //   if (!resultpointer)
   //   {
   //      
   //      return operator=(resultpointer.m_estatus);

   //   }
   //   else
   //   {
   //      
   //      return operator = (resultpointer.m_p);

   //   }

   //}

   template < an_object T >
   payload & assign_copy(const T & t)
   {

      ::copy(*this, t);

      return *this;

   }


   template < class T >
   payload & operator = (const raw_block < T > & rawblock)
   {

      return this->operator = (rawblock.block());

   }

   template < strsize n >
   payload & operator = (const char(&cha)[n])
   {

      return this->operator = (::string(cha));

   }


   template < class T >
   ::pointer< T > cast(T * pDefault);

   template < class T >
   T & defer_create_type(T * pdefault = nullptr)
   {

      ::pointer< T > p = pdefault;

      if (!p)
      {

         p = __call__allocate< T >();

         operator =(p);

      }

      return *p;

   }


   template < class T >
   T & get_cast(T * pDefault);


   //template < class T >
   //::ptr< T > cast(T * pDefault) const
   //{
   //   return ((payload *)this)->cast < T >(pDefault);
   //}


   template < class T >
   ::pointer< T > cast();

   ::subparticle * as_subparticle()
   {
      if (m_etype == e_type_element) { return m_p; }
      return cast < ::subparticle >();
   }

   ::subparticle * as_subparticle() const { return ((payload *)this)->as_subparticle(); }

   template < class T >
   T * cast() const
   {
      return ((payload *)this)->cast < T >();
   }


   ::subparticle * get_subparticle();

   //   bool strictly_equal(const payload & payload) const;
   //   bool strictly_equal(const ::scoped_string & scopedstr) const;
   //   bool strictly_equal(const ::string & str) const;
   //   bool strictly_equal(double d) const;
   //   bool strictly_equal(::i32 i) const;
   //   bool strictly_equal(bool b) const;
   //
   //   bool strictly_different(const payload & payload) const;
   //   bool strictly_different(const ::scoped_string & scopedstr) const;
   //   bool strictly_different(const ::string & str) const;
   //   bool strictly_different(double d) const;
   //   bool strictly_different(::i32 i) const;
   //   bool strictly_different(bool b) const;

      //friend bool CLASS_DECL_ACME strict_equal(const ::scoped_string & scopedstr,const payload & payload);
      //friend bool CLASS_DECL_ACME strict_equal(const ::string & str,const payload & payload);
      //friend bool CLASS_DECL_ACME strict_equal(double d,const payload & payload);
      //friend bool CLASS_DECL_ACME strict_equal(::i32 i,const payload & payload);
      //friend bool CLASS_DECL_ACME strict_equal(bool b,const payload & payload);

      //friend bool CLASS_DECL_ACME strict_different(const ::scoped_string & scopedstr,const payload & payload);
      //friend bool CLASS_DECL_ACME strict_different(const ::string & str,const payload & payload);
      //friend bool CLASS_DECL_ACME strict_different(double d,const payload & payload);
      //friend bool CLASS_DECL_ACME strict_different(::i32 i,const payload & payload);
      //friend bool CLASS_DECL_ACME strict_different(bool b,const payload & payload);

   //bool equals(const payload & payload) const;
   //bool equals(const ::scoped_string & scopedstr) const;

   bool case_insensitive_equals(const payload & payload) const;

   ::std::strong_ordering order_payload(const payload & payload) const;

   ::std::strong_ordering case_insensitive_order(const ::payload & payload) const;


   bool equals_payload(const ::payload & payload) const;
   bool equals_signed(::i64 i) const;
   bool equals_unsigned(::u64 u) const;
   bool equals_scoped_string(const ::scoped_string & scopedstr) const;


   template < primitive_character CHARACTER >
   bool operator == (const CHARACTER * psz) const { return equals_scoped_string(psz); }
   template < primitive_character CHARACTER  >
   bool operator == (const range < const CHARACTER * > & range) const { return equals_scoped_string(range); }
   template < primitive_character CHARACTER  >
   bool operator == (const scoped_string_base < const CHARACTER * > & scoped_string) const { return equals_scoped_string(scoped_string); }
   template < primitive_character CHARACTER  >
   bool operator == (const string_base < const CHARACTER * > & string) const { return equals_scoped_string(string); }
   template < primitive_character CHARACTER  >
   bool operator == (const string_range < const CHARACTER * > & string_range) const { return equals_scoped_string(string_range); }
   //bool operator == (const ::string & str) const;
   template < primitive_signed SIGNED >
   bool operator == (SIGNED i) const { return equals_signed(i); }
   template < primitive_unsigned UNSIGNED >
   bool operator == (UNSIGNED u) const { return equals_unsigned(u); }
   //bool operator == (::i32 i) const;
   //bool operator == (bool b) const;

   //bool operator != (const payload & payload) const;
   //bool operator != (const ::scoped_string & scopedstr) const;
   //bool operator != (const ::string & str) const;
   //bool operator != (::i64 i) const;
   //bool operator != (::i32 i) const;
   //bool operator != (bool b) const;

   ::std::strong_ordering operator <=> (const payload & payload) const;
   ::std::strong_ordering operator <=> (const ::scoped_string & scopedstr) const;
   ::std::strong_ordering operator <=> (const ::string & str) const;
   ::std::strong_ordering operator <=> (::i64 i) const;
   ::std::strong_ordering operator <=> (::i32 i) const;
   ::std::strong_ordering operator <=> (bool b) const;

   //bool operator <= (const payload & payload) const;
   //bool operator <= (const ::scoped_string & scopedstr) const;
   //bool operator <= (const ::string & str) const;
   //bool operator <= (::i64 i) const;
   //bool operator <= (::i32 i) const;
   //bool operator <= (bool b) const;

   //bool operator >= (const payload & payload) const;
   //bool operator >= (const ::scoped_string & scopedstr) const;
   //bool operator >= (const ::string & str) const;
   //bool operator >= (::i64 i) const;
   //bool operator >= (::i32 i) const;
   //bool operator >= (bool b) const;

   //bool operator > (const payload & payload) const;
   //bool operator > (const ::scoped_string & scopedstr) const;
   //bool operator > (const ::string & str) const;
   //bool operator > (::i64 i) const;
   //bool operator > (::i32 i) const;
   //bool operator > (bool b) const;


   ::string implode(const ::scoped_string & scopedstrGlue) const;
   payload explode(const ::scoped_string & scopedstrGlue,bool bAddEmpty = true) const;

   payload first() const;
   payload last() const;
   payload first();
   payload last();
   ::collection::count get_count() const;


   ::payload at(::collection::index i);
   inline ::payload at(::collection::index i) const { return ((::payload *)this)->at(i); }


   ::collection::count array_get_count() const;
   ::collection::index array_get_upper_bound() const;
   bool array_contains(const ::scoped_string & scopedstr, ::collection::index find = 0, ::collection::count count = -1) const;
   bool case_insensitive_array_contains(const ::scoped_string & scopedstr, ::collection::index find = 0, ::collection::count count = -1) const;
   bool array_is_empty() const { return array_get_count() <= 0; }


   ::collection::index index_of(const ::atom & atom) const;
   //::property * find_property_index(::iptr i) const;
   //::property & get_property_index(::iptr i);
   //::property * find_property(const ::scoped_string & scopedstr) const;
   //::property & get_property(const ::scoped_string & scopedstr);
   ::payload find_property(const ::atom & atom) const; // { return atom.is_text() ? find_property_text_key((const ::scoped_string &)atom.m_str) : find_property_index(atom.m_i); }
   ::property & get_property(const ::atom & atom); // { return atom.is_text() ? get_property_text_key((const ::scoped_string &)atom.m_str) : get_property_index(atom.m_i); }

   ::payload find_property_by_text(const ::scoped_string & scopedstr) const; 



   //::payload operator[] (const ::atom & atom);
   //::payload operator[] (const ::atom & atom) const;
   template < primitive_integral INTEGRAL >
   inline ::payload operator[] (INTEGRAL i) { return at(i); }
   template < primitive_integral INTEGRAL >
   inline ::payload operator[] (INTEGRAL i) const { return at(i); }

   template < primitive_character CHARACTER >
   inline ::property & operator[] (const CHARACTER * psz) { return get_property(psz); }
   template < primitive_character CHARACTER >
   inline ::payload operator[] (const CHARACTER * psz) const { return find_property_by_text(psz); }

   template < character_range RANGE >
   inline ::property & operator[] (const RANGE & range) { return get_property(range); }
   template < character_range RANGE >
   inline ::payload operator[] (const RANGE & range) const { return find_property_by_text(range); }

   template < has_as_string HAS_AS_STRING >
   inline ::property & operator[] (const HAS_AS_STRING & has_as_string) { return get_property(has_as_string.as_string()); }
   template < has_as_string HAS_AS_STRING >
   inline ::payload operator[] (const HAS_AS_STRING & has_as_string) const { return find_property_by_text(has_as_string.as_string()); }

   template < has_get_string HAS_GET_STRING >
   inline ::property & operator[] (const HAS_GET_STRING & has_get_string) { return get_property(has_get_string.get_string()); }
   template < has_get_string HAS_GET_STRING >
   inline ::payload operator[] (const HAS_GET_STRING & has_get_string) const { return find_property_by_text(has_get_string.get_string()); }


   //inline ::property & operator[] (::iptr i);
   //inline ::payload operator[] (::iptr i) const;

//#if OSBIT == 64
//
//   inline ::property & operator[] (::i32 i) { return get_property(::atom(i)); }
//   inline ::payload operator[] (::i32 i) const { return find_property(::atom(i)); }
//
//#endif


   ::payload equals_ci_get(const ::scoped_string & scopedstrCompare,::payload varOnEqual,payload varOnDifferent) const;
   ::payload equals_ci_get(const ::scoped_string & scopedstrCompare,::payload varOnEqual) const;

   template < primitive_integral INTEGRAL >
   ::payload operator - (INTEGRAL i) const;
   template < primitive_floating FLOATING >
   ::payload operator - (FLOATING f) const;


   template < primitive_integral INTEGRAL >
   ::payload operator + (INTEGRAL i) const;
   template < primitive_floating FLOATING >
   ::payload operator + (FLOATING f) const;

   //::payload operator + (const ::scoped_string & scopedstr) const;
   //::payload operator + (const ::string & str) const;
   //::payload operator + (const ::inline_number_string & inline_number_string) const;

   template < primitive_integral INTEGRAL >
   ::payload operator / (INTEGRAL i) const;
   template < primitive_floating FLOATING >
   ::payload operator / (FLOATING f) const;

   template < primitive_integral INTEGRAL >
   ::payload operator * (INTEGRAL i) const;
   template < primitive_floating FLOATING >
   ::payload operator * (FLOATING d) const;

   ::std::strong_ordering str_compare(const ::property & prop) const;



   template < primitive_integral INTEGRAL >
   ::payload & operator -= (INTEGRAL i);
   template < primitive_floating FLOATING >
   ::payload & operator -= (FLOATING f);


   template < primitive_integral INTEGRAL >
   ::payload & operator += (INTEGRAL i);
   template < primitive_floating FLOATING >
   ::payload & operator += (FLOATING f);

   //::payload & operator += (const ::scoped_string & scopedstr);
   //::payload & operator += (const ::string & str);
   //::payload & operator += (const ::inline_number_string & inline_number_string);
   //template < strsize n >
   //::payload & operator += (const ::ansi_character (&cha)[n]) { return *this += ::scoped_string(cha);}

   template < primitive_integral INTEGRAL >
   ::payload & operator /= (INTEGRAL i);
   template < primitive_floating FLOATING >
   ::payload & operator /= (FLOATING f);

   template < primitive_integral INTEGRAL >
   ::payload & operator *= (INTEGRAL i);
   template < primitive_floating FLOATING >
   ::payload & operator *= (FLOATING d);


   void consume_number(::ansi_range & range);
   //void consume_number((::ansi_range & range);
   void consume_identifier(::ansi_range & range);
   //void consume_identifier((::ansi_range & range);
   void parse_network_payload(::ansi_range & range);
   //void parse_network_payload((::ansi_range & range);
   const char * parse_network_payload(const ::scoped_string & scopedstrNetworkPayload);
   ::enum_type find_network_payload_child(::ansi_range & range, const payload & payload);
   //::enum_type find_network_payload_child((::ansi_range & range, const payload & payload);
   ::enum_type find_network_payload_id(::ansi_range & range, const payload & payload);
   bool parse_network_payload_step(::ansi_range & range);
   // bool parse_network_payload_step(const char *& pszJson, const ::ansi_character * pszEnd);

   ::string & get_network_payload(::string & str, bool bNewLine = true) const;
   ::string get_network_payload(bool bNewLine = true) const;



   //
   // DECLARE_AXIS_FIXED_ALLOC(payload)

   void null();



   void _001Add(const ::string_array & stra);


   void defer_run_payload();

   void receive_response(const payload & payload);


};


#include "acme/primitive/collection/__payload_array.h"


#include "__payload_reference.h"
#include "acme/primitive/collection/property_set.h"
#include "acme/primitive/primitive/url.h"



//
//namespace str
//{


   //inline CLASS_DECL_ACME void from(::string & str, const payload & payload)
   //{

   //   str = payload;

   //}

//
//} // namespace str


//CLASS_DECL_ACME void var_skip_number(const char *& psz);
CLASS_DECL_ACME void payload_skip_number(::ansi_range & range);
//CLASS_DECL_ACME void var_skip_identifier(const char *& psz);
CLASS_DECL_ACME void payload_skip_identifier(::ansi_range & range);
//CLASS_DECL_ACME void var_skip_network_payload(const char *& pszJson);
CLASS_DECL_ACME void payload_skip_network_payload(::ansi_range & range);




//#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBERRYPIOS) || defined(WINDOWS)
//
//
//inline payload::operator long &()
//{
//
//   set_type(e_type_i64);
//
//   return (long &) m_i64;
//
//}
//
//
//inline payload::operator unsigned long &()
//{
//
//   set_type(e_type_u64);
//
//   return (unsigned long &) m_u64;
//
//}
//
//
//#endif


// returns 0 for unknown conversions
//inline payload::operator ::i8() const
//{
//   return i8();
//}

// returns 0 for unknown conversions
//inline payload::operator ::u8() const
//{
//   return u8();
//}


// returns 0 for unknown conversions
//inline payload::operator ::i16() const
//{
//   return i16();
//}

// returns 0 for unknown conversions
//inline payload::operator ::u16() const
//{
//   return u16();
//}



// returns 0 for unknown conversions
//inline payload::operator ::i32() const
//{
//   return i32();
//}

// returns 0 for unknown conversions
//inline payload::operator ::u32() const
//{
//   return u32();
//}


// returns 0 for unknown conversions
//inline payload::operator ::i64() const
//{
//   return i64();
//}

// returns 0 for unknown conversions
//inline payload::operator ::u64() const
//{
//   return u64();
//}





// returns 0.0 for unknown conversions?
//inline payload::operator float() const
//{
//
//   return get_float();
//
//}


// returns 0.0 for unknown conversions?
//inline payload::operator double() const
//{
//
//   return get_double();
//
//}


// returns 0.0 for unknown conversions?
//inline payload::operator void() const
//{
//
//   return estatus();
//
//}


//inline payload::operator class time() const
//{
//
//   return time();
//
//}
//
//
//inline payload::operator class second() const
//{
//
//   return second();
//
//}


//inline payload::operator class ::time() const
//{
//
//   return class ::time();
//
//}
//
//
//inline payload::operator class microsecond() const
//{
//
//   return microsecond();
//
//}
//
//
//inline payload::operator class nanosecond() const
//{
//
//   return nanosecond();
//
//}


inline iptr payload::as_iptr(::iptr iDefault) const
{

#if defined(OS64BIT)

   return as_i64(iDefault);

#else

   return as_i32(iDefault);

#endif

}


inline uptr payload::as_uptr(::uptr uiDefault) const
{

#ifdef OS64BIT

   return as_u64(uiDefault);

#else

   return as_u32(uiDefault);

#endif

}


#ifdef WINDOWS

//#elif defined(__APPLE__) || defined(RASBPIAN)
#elif defined(RASBPIAN)

inline payload::operator long() const
{

   return as_i64();

}



// returns 0 for unknown conversions
inline payload::operator unsigned long() const
{
#if LONG_IS_32BIT
   return as_u32();
#else
   return as_u64();
#endif
}


//#elif defined(ANDROID)
//
//inline payload::operator long() const
//{
//
//   return i32();
//
//}

#endif


//inline ::string & payload::string_reference(const ::scoped_string & scopedstrOnNull)
//{
//
//   set_type(e_type_string, true);
//
//   return m_str;
//
//}


inline ::payload __visible(::payload varOptions, bool bVisible);

inline payload __visible(bool bVisible = true);


//template < character_range RANGE, primitive_payload PAYLOAD >
//::string operator + (const RANGE & range, const PAYLOAD & has_as_string);


template < primitive_payload PAYLOAD1, primitive_payload PAYLOAD2 >
inline PAYLOAD1 operator +(const PAYLOAD1 & payload1, const PAYLOAD2 & payload2)
{

   auto payload = payload1;

   payload.addition(payload2);

   return ::transfer(payload);

}


template < primitive_payload PAYLOAD1, primitive_payload PAYLOAD2 >
inline PAYLOAD1 & operator +=(PAYLOAD1 & payload1, const PAYLOAD2 & payload2)
{

   return payload1.add(payload2);

}


template < primitive_payload PAYLOAD, primitive_character CHARACTER >
inline ::string operator +(const PAYLOAD & payload, const CHARACTER * psz)
{

   ::string str(payload);

   str.append(psz);

   return ::transfer(str);

}


template < primitive_payload PAYLOAD, primitive_character CHARACTER >
inline PAYLOAD & operator +=(PAYLOAD & payload, const CHARACTER * psz)
{

   payload = payload.as_string() + ::string(psz);

   return payload;

}


//template < primitive_character CHARACTER, primitive_payload PAYLOAD >
//inline ::string operator +(const CHARACTER * psz, const PAYLOAD & payload)
//{
//
//   ::string str(psz);
//
//   str.append(payload.get_string());
//
//   return ::transfer(str);
//
//}


template < primitive_payload PAYLOAD, character_range RANGE >
::string operator + (const PAYLOAD & payload, const RANGE & range)
{

   return ::transfer(::string(payload) + ::string(range));

}


template < primitive_payload PAYLOAD, character_range RANGE >
PAYLOAD & operator += (PAYLOAD& payload, const RANGE& range)
{

   string str = payload.as_string() + ::string(range);

   payload = str;

   return payload;

}


CLASS_DECL_ACME void copy(::string & str, const ::payload & payload);
CLASS_DECL_ACME void copy(::payload & payload, const int & i);
CLASS_DECL_ACME  void copy(::payload & payload, const ::string & str);


template < primitive_payload PAYLOAD1, primitive_payload PAYLOAD2 >
inline bool operator == (const PAYLOAD1 & payload1, const PAYLOAD2 & payload2)
{

   return payload1.equals_payload(payload2);

}



