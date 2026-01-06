#pragma once


#include "type.h"
#include "acme/prototype/datetime/earth_time.h"
#include "acme/prototype/datetime/file_time.h"
#include "acme/prototype/time/time/posix_time.h"
#include "acme/graphics/draw2d/color.h"
#include "pointer.h"
#include "acme/memory/memory.h"
#include "acme/memory/raw_block.h"
#include "acme/platform/procedure.h"
#include "acme/prototype/collection/numeric_array.h"
#include "acme/filesystem/filesystem/path_object.h"
#include  "acme/filesystem/filesystem/path_array.h"
//#include "acme/prototype/datetime/file_time.h"
#include "acme/prototype/string/sz.h"
#include "acme/prototype/prototype/make_particle.h"
#include "acme/prototype/string/_character_range.h"

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

   //unsigned char     m_ua[32];
   unsigned char     m_ua[40];

};


class CLASS_DECL_ACME payload :
   public memory_quantum
{
public:


   using PRIMITIVE_PAYLOAD_TAG = PRIMITIVE_PAYLOAD_TAG_TYPE;
   payload * refdbg_this() const { return (payload*)this; }

   enum_type                        m_etype;


   union
   {

      void * m_pvoid;
      para_return                            m_parareturn;
      atom                                   m_atomPayload;
      //type                                   m_type;
      bool                                   m_b;
      bool * m_pb;
      char                                   m_ch;
      unsigned char                          m_uch;
      short                                  m_sh;
      unsigned short                         m_ush;
      int                                    m_i;
#if defined(__APPLE__) || defined(__ANDROID__) || defined(RASPBERRYPIOS)
      //long                                   m_l;
      //unsigned long                          m_ul;
#endif
      unsigned int                           m_ui;
      long long                           m_hi;
      unsigned long long                           m_hn;
      char *                                 m_pch;
      unsigned char * m_puch;
      short * m_psh;
      unsigned short * m_push;
      int * m_pi;
      unsigned int * m_pui;
      long long * m_pll;
      unsigned long long * m_pull;
      ::string * m_pstr;
      float                                  m_f;
      float * m_pf;
      double                                  m_d;
      double * m_pd;
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
      ::int_array  * m_pia;
      ::float_array* m_pfloata;
      ::payload_array  * m_ppayloada;
      ::property_set  * m_ppropertyset;
      ::long_long_array * m_plonglonga;
      ::double_array* m_pdoublea;
      ::memory * m_pmemory;
      ::file::path_object * m_ppath;
      payload_all_t                          m_payloadall;
      ::string                               m_str;
      ::character_range < const_char_pointer >m_ansirange;
      ::function_common_base *               m_pfunctioncommonbase;

   };


#if REFERENCING_DEBUGGING

   
   ::reference_referer * m_preferer;


#endif


   payload() : m_etype(e_type_new) REFDBG(, m_preferer(nullptr)) { }
   payload(no_initialize_t) { }
   payload(enum_type etype);
   payload(nullptr_t);
   payload(const ::payload & payload);
   //template < typename ITERATOR_TYPE, int t_size >
   //payload(const const_string_range_static_array < ITERATOR_TYPE, t_size >& a) :
   //   payload(::string(a))
   //{  }
   payload(::payload && payload) :
      m_etype(payload.m_etype)
   {
      m_payloadall = payload.m_payloadall;
#if REFERENCING_DEBUGGING
      m_preferer = payload.m_preferer;
      payload.m_preferer = nullptr;
#endif
      payload.m_etype = e_type_new;
      payload.m_payloadall = {};
   }
   template < bool_type BOOL > payload(BOOL b) : m_etype(e_type_bool) {m_b = b;}
   template < same_as < char > CHAR > payload(CHAR c) : m_etype(e_type_char) {m_ch = c;}
   //template < i8_type I8 > payload(I8 i) : m_etype(e_type_char) {m_ch = i;}
   template < same_as < unsigned char > UNSIGNED_CHAR > payload(UNSIGNED_CHAR uch) : m_etype(e_type_unsigned_char) {m_uch = uch;}
   template < same_as < short > SHORT > payload(SHORT sh) : m_etype(e_type_short) {m_sh = sh;}
   template < same_as < unsigned short > UNSIGNED_SHORT > payload(UNSIGNED_SHORT ush) : m_etype(e_type_unsigned_short) {m_ush = ush;}
   template < same_as < int > INT > payload(INT i) : m_etype(e_type_int) {m_i = i;}
   template < same_as < unsigned int > UNSIGNED_INT > payload(UNSIGNED_INT ui) : m_etype(e_type_unsigned_int) {m_ui = ui;}
   template < same_as < long long > LONG_LONG > payload(LONG_LONG hi) : m_etype(e_type_long_long) {m_hi = hi;}
   template < same_as < unsigned long long > UNSIGNED_LONG_LONG > payload(UNSIGNED_LONG_LONG hn) : m_etype(e_type_unsigned_long_long) {m_hn = hn;}
   template < same_as < float > FLOAT > payload(FLOAT f) : m_etype(e_type_float) {m_f = f;}
   template < same_as < double > DOUBLE > payload(DOUBLE d) : m_etype(e_type_double) {m_d = d;}
#ifdef __APPLE__
#ifdef OS64BIT
   payload(long l);
#endif
#endif
   payload(int * pi);
   payload(float * pf);
   payload(unsigned int * pu);
   payload(long long * pi);
   payload(double * pd);
   payload(unsigned long long * pu);
   payload(bool * pb);
   payload(::string * pstr);
   //payload(::payload * ppayload);
   //payload(::property * pproperty);
   payload(::subparticle * pparticle);
   payload(class ::time * ptime);
   template < prototype_character_range CHARACTER_RANGE >
   payload(const CHARACTER_RANGE & range);
   //template < ::collection::count count >
   //payload(const ::ansi_character(&sz)[count]) : payload((const_char_pointer )sz, count) {}
   template < prototype_integral INTEGRAL >
   payload(const_char_pointer begin, INTEGRAL count) : payload(begin, begin + count) {}
   payload(const_char_pointer begin, const_char_pointer end);
   payload(const_char_pointer psz);
   payload(const ::scoped_string & scopedstr);
   //payload(const ::platform::type & type);
   payload(const ::atom & atom);
   payload(const ::earth::time & time);
   payload(const ::color::color & color);
   payload(const ::color::hls & hls);
   payload(const ::subparticle & particle);
   payload(const ::file::path & path);
   payload(const ::string_array_base & stra);
   payload(const ::int_array_base & ia);
   payload(const ::long_long_array_base& ia);
   payload(const ::float_array_base& ia);
   payload(const ::double_array_base& ia);
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
   payload(const ::raw_block < BLOCK_TYPE > & rawblock) :
      payload(e_type_new)
   {

      //m_etype = e_type_new;
      operator = (rawblock.block());

   }


   payload(const ::inline_number_string & a) :
      payload(e_type_new)
   {
      
      //m_etype = e_type_new;
      operator = (a);

   }


   //   template < prototype_character CHARACTER2, character_count sizeMaximumLength >
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

   template < prototype_enum ENUM >
   payload(ENUM e) :
   m_etype(e_type_atom),
   m_atomPayload(e)
   {

   }

   ~payload();


   void clear_data() { m_etype = e_type_null; }


   void set_type(enum_type enum_type, bool bConvert = true);
   enum_type get_type() const;
   atom::enum_type atom_type() const;


   //void set_type(const ::platform::type & type);


   template < typename T >
   void set_pointer(const ::pointer < T > & p)
   {

      operator[](::platform::type(p)) = p;

   }

   template < typename T >
   bool has_pointer() const
   {

      return has_property(::platform::type(::type<T>()));

   }

   template < typename T >
   ::property * find_pointer() const
   {

      return _find_property(::platform::type(::type<T>()));

   }

   template < typename TYPE >
   ::pointer < TYPE > pointer() const;

   //bool get_type(::platform::type & type) const;

   long long payload_release();

   long long logical_release();

   void _set_element(::subparticle * pelement);

   bool is_element() const { return m_etype >= e_type_element && m_etype < e_type_last_element; }

   bool is_element_set() const { return is_element() && ::is_set(m_p); }

   bool is_element_null() const { return is_element() && ::is_null(m_p); }

   bool is_numeric() const;


   bool has_reference_of_type(enum_type etype) const;


   inline bool is_number() const
   {

      return is_numeric();

   }

   bool target_constrained_assign(const ::payload & payload);


   bool                             get_bool()     const;

   template < typename ENUM >
   ENUM                             e(ENUM edefault = enum_default < ENUM >())  const { return (ENUM)(long long)(edefault); }

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
   inline payload(const ::e_ ## ENUMTYPE & e) : m_etype(e_type_atom),m_atomPayload(e) { } \
   inline ::e_ ## ENUMTYPE as_e ## ENUMTYPE() const { return as_atom().as_e ## ENUMTYPE(); } \
   inline ::e_ ## ENUMTYPE & e ## ENUMTYPE ## _reference() { return atom_reference().e ## ENUMTYPE ## _reference(); }
   IMPLEMENT_PAYLOAD_ENUMERATION(status);
   IMPLEMENT_PAYLOAD_ENUMERATION(command);
   IMPLEMENT_PAYLOAD_ENUMERATION(check);
#undef IMPLEMENT_PAYLOAD_ENUMERATION


   template < prototype_enum ENUM >
   bool operator ==(ENUM e) const
   {

      if (m_etype == e_type_atom)
      {

         return m_atomPayload == e;

      }
      else if (m_etype == e_type_patom)
      {

         return *m_patom == e;

      }

      return operator == (::as_long_long(e));

   }


   //inline ::second & as_secs() { if (get_type() != e_type_secs)set_type(e_type_secs); return m_secs; }
   //inline class ::time & as_millis() { if (get_type() != e_type_millis)set_type(e_type_millis); return m_millis; }
   //inline ::microsecond & as_micros() { if (get_type() != e_type_micros)set_type(e_type_micros); return m_micros; }
   //inline ::nanosecond & as_nanos() { if (get_type() != e_type_nanos)set_type(e_type_nanos); return m_nanos; }

   void as(::string & str) const;
   void as(::memory_base & memory) const;


#if defined(__APPLE__) || defined(__ANDROID__) || defined(RASPBERRYPIOS) || defined(WINDOWS)
   long get_long(long lDefault = 0) const;
   unsigned long get_unsigned_long(unsigned long ulDefault = 0) const;
#endif

   char & as(char & i) const { return i = as_char(); }
   unsigned char & as(unsigned char & u) const { return u = as_unsigned_char(); }
   short & as(short & i) const { return i = as_short(); }
   unsigned short & as(unsigned short & u) const { return u = as_unsigned_short(); }
   int & as(int & i)  const { return i = as_int(); }
   unsigned int & as(unsigned int & u)  const { return u = as_unsigned_int(); }
   long long & as(long long & i)  const { return i = as_long_long(); }
   unsigned long long & as(unsigned long long & u)  const { return u = as_unsigned_long_long(); }
   float & as(float & f) const { return f = as_float(); }
   double & as(double & f) const { return f = as_double(); }


   char as_char(char iDefault = 0) const;
   unsigned char as_unsigned_char(unsigned char uDefault = 0) const;
   short as_short(short iDefault = 0) const;
   unsigned short as_unsigned_short(unsigned short uDefault = 0) const;
   int as_int(int iDefault = 0)  const;
   unsigned int as_unsigned_int(unsigned int uiDefault = 0)  const;
   long long as_long_long(long long iDefault = 0)  const;
   unsigned long long as_unsigned_long_long(unsigned long long uiDefault = 0)  const;
   float as_float(float fDefault = 0) const;
   double as_double(double fDefault = 0) const;


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


   ::posix_time as_posix_time(long long iDefault = 0) const
   {

      return { posix_time_t{}, this->as_long_long() };

   }


   ::posix_time as_time(const class ::time & timeDefault) const;

   ::string as_string(const ::scoped_string & scopedstrOnNull) const;
   ::string as_string() const;
   ::string get_recursive_string() const;
   ::atom as_atom() const;
   ::atom as_atom(const ::atom & idDefault) const;

   ::memory as_memory() const;
   ::string_array_base as_string_array() const;
   ::int_array_base as_int_array() const;
   ::long_long_array_base as_long_long_array() const;
   ::float_array_base as_float_array() const;
   ::double_array_base as_double_array() const;
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
   void unset(const ::scoped_string & scopedstrPropertySetKey);

   bool is_set() const;
   bool is_new() const;
   bool is_null() const;
   bool is_new_or_null() const;
   bool is_empty() const;
   bool has_character() const;

   bool is_false() const;
   bool is_bool_false() const;
   bool is_set_false() const;
   bool is_true() const;
   bool is_true_or_empty() const;

   //bool is_property_true(const ::atom & atom, bool bDefault = false) const;

   bool casts_to(::enum_type etype) const;


   ///property * defer_get_property(const ::atom & atom) const;
   bool has_property(const ::atom & atom) const;
   bool is_property_true_or_empty(const ::atom & atom) const;
   bool is_property_true(const ::atom & atom) const;
   bool is_property_false(const ::atom & atom) const;


   bool begins(const ::scoped_string & scopedstrPrefix) const;
   bool ends(const ::scoped_string & scopedstrSuffix) const;
   bool case_insensitive_begins(const ::scoped_string & scopedstrPrefix) const;
   bool case_insensitive_ends(const ::scoped_string & scopedstrSuffix) const;

   bool begins_eat(const ::scoped_string & scopedstrPrefix);
   bool ends_eat(const ::scoped_string & scopedstrSuffix);
   bool case_insensitive_begins_eat(const ::scoped_string & scopedstrPrefix);
   bool case_insensitive_ends_eat(const ::scoped_string & scopedstrSuffix);

   payload get_topic(const ::atom & atom) const;
   //payload defer_get(const ::atom & atom) const;

   payload & operator ++(int);

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

   operator char() const { return this->as_char(); }
   operator unsigned char() const { return this->as_unsigned_char(); }
   operator short() const { return this->as_short(); }
   operator unsigned short() const { return this->as_unsigned_short(); }
   operator int() const { return this->as_int(); }
   operator unsigned int() const { return this->as_unsigned_int(); }
   operator long long()const { return this->as_long_long(); }
   operator unsigned long long() const { return this->as_unsigned_long_long(); }



   operator float() const { return this->as_float(); }
   operator double() const { return this->as_double(); }
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


   ::string_array_base & string_array_reference();
   ::int_array_base & int_array_reference();
   ::long_long_array_base & long_long_array_reference();
   ::float_array_base& float_array_reference();
   ::double_array_base & double_array_reference();
   ::payload_array & payload_array_reference();
   class ::time & time_reference();
   ::property_set & property_set_reference();
   //::property & property_reference();

   ::file::path & file_path_reference();

   ::file_time & file_time_reference();
   ::earth::time & earth_time_reference();
   ::color::color & color_reference();
   ::color::hls & color_hls_reference();

   const ::string_array_base & string_array_reference() const;
   const ::int_array_base & int_array_reference() const;
   const ::long_long_array_base & long_long_array_reference() const;
   const ::float_array_base& float_array_reference() const;
   const ::double_array_base& double_array_reference() const;
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
#if defined(__APPLE__) || defined(__ANDROID__) || defined(RASPBERRYPIOS) || defined(WINDOWS)
   long & long_reference();
   unsigned long & unsigned_long_reference();
#endif
   char & char_reference();
   unsigned char & unsigned_char_reference();
   short & short_reference();
   unsigned short & unsigned_short_reference();
   int & int_reference();
   unsigned int & unsigned_int_reference();
   long long & long_long_reference();
   unsigned long long & unsigned_long_long_reference();
   float & float_reference();
   double & double_reference();


   template < prototype_signed SIGNED >
   inline SIGNED & reference()
   {

      if constexpr(sizeof(SIGNED) == 8)
      {

         return (SIGNED&) this->long_long_reference();

      }
      else if constexpr(sizeof(SIGNED) == 4)
      {

         return (SIGNED&) this->int_reference();

      }
      else if constexpr(sizeof(SIGNED) == 2)
      {

         return (SIGNED&) this->short_reference();

      }
      else if constexpr(sizeof(SIGNED) == 1)
      {

         return (SIGNED&) this->char_reference();

      }
      else
      {

         throw "todo";

      }


   }


   template < prototype_unsigned UNSIGNED >
   inline UNSIGNED & reference()
   {

      if constexpr(sizeof(UNSIGNED) == 8)
      {

         return (UNSIGNED&) this->unsigned_long_long_reference();

      }
      else if constexpr(sizeof(UNSIGNED) == 4)
      {

         return (UNSIGNED&) this->unsigned_int_reference();

      }
      else if constexpr(sizeof(UNSIGNED) == 2)
      {

         return (UNSIGNED&) this->unsigned_short_reference();

      }
      else if constexpr(sizeof(UNSIGNED) == 1)
      {

         return (UNSIGNED&) this->unsigned_char_reference();

      }
      else
      {

         throw "todo";

      }


   }


   template < prototype_const CONST_TYPE >
   CONST_TYPE & reference() const
   {

      return (CONST_TYPE &) ((::payload*)this)->reference<non_const<CONST_TYPE>>();

   }


   template < prototype_non_const NON_CONST_TYPE >
   NON_CONST_TYPE * raw_pointer()
   {

      return &reference<NON_CONST_TYPE>();

   }


   template < prototype_const CONST_TYPE >
   CONST_TYPE * raw_pointer() const
   {

      return &reference<CONST_TYPE>();

   }


   character_count length() const;


   template < typename TYPE >
   inline payload & operator = (const ::pointer<TYPE> & pointer)
   {

      _set_element(pointer.m_psubparticle);

      return *this;

   }


   template < prototype_function FUNCTION >
   inline payload & operator = (const FUNCTION & function)
   {

      _set_element(function.m_p);

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

   int & _as(int & i) const
   {

      i = as_int();

      return i;

   }

   ::string & _as(::string & str) const
   {

      str = as_string();

      return str;

   }

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
   //   return operator =((long long) eenum);
   //}

   payload & operator |= (enumeration < ::file::enum_flag > eflag);

   //payload& operator = (const ::e_status & estatus)
   //{
   //   return operator =(estatus.m_estatus);
   //}

   //payload & operator = (const payload & eret);

   payload & operator = (para_return & eret);
#ifdef WINDOWS
#elif defined(__APPLE__) || defined(__ANDROID__) || defined(RASPBERRYPIOS)
   payload & operator = (long l);
#endif


   payload & assign_bool            (bool               b)   { return __assign_primitive(  m_b , e_type_bool  , b ); }

#define NUMBER_TYPE_OPERATION(NUMBER_TYPE, NUMBER_NAME, NUMBER_SHORT_NAME, UPPER_CASE_NAME) \
payload & assign_## NUMBER_NAME (NUMBER_TYPE NUMBER_SHORT_NAME) { return __assign_primitive(m_## NUMBER_SHORT_NAME , e_type_## NUMBER_NAME, NUMBER_SHORT_NAME ); }
   DO_FOR_NUMBER_TYPES(NUMBER_TYPE_OPERATION)
#undef NUMBER_TYPE_OPERATION
   //payload & assign_char            (char              ch)   { return __assign_primitive( m_ch , e_type_char    , i ); }
   //payload & assign_unsigned_char   (unsigned char    uch)   { return __assign_primitive(m_uch , e_type_unsigned_char    , u ); }
   //payload & assign_short           (short             sh)   { return __assign_primitive( m_sh , e_type_short   , i ); }
   //payload & assign_unsigned_short  (unsigned short   ush)   { return __assign_primitive(m_ush , e_type_unsigned_short   , u ); }
   //payload & assign_int             (int                i)   { return __assign_primitive(  m_i , e_type_int   , i ); }
   //payload & assign_unsigned_int    (unsigned int       u)   { return __assign_primitive( m_ui , e_type_unsigned_int   , u ); }
   //payload & assign_long_long    (long long      hi)   { return __assign_primitive( m_hi , e_type_long_long   , i ); }
   //payload & assign_unsigned_long_long    (unsigned long long      hn)   { return __assign_primitive( m_hn , e_type_unsigned_long_long   , u ); }
   //payload & assign_float             (float              f)   { return __assign_primitive(  m_f , e_type_float   , f ); }
   //payload & assign_double             (double             d)   { return __assign_primitive(  m_d , e_type_double   , f ); }


   payload & assign_pbool  (bool  * pb)   { return __assign_primitive_pointer(m_pb     , e_type_pbool , pb); }
   payload & assign_pi8    (char  * pi)   { return __assign_primitive_pointer(m_pch    , e_type_pchar   , pi); }
   payload & assign_pu8    (unsigned char  * pu)   { return __assign_primitive_pointer(m_puch    , e_type_punsigned_char   , pu); }
   payload & assign_pi16   (short * pi)   { return __assign_primitive_pointer(m_psh   , e_type_pshort  , pi); }
   payload & assign_pu16   (unsigned short * pu)   { return __assign_primitive_pointer(m_push   , e_type_punsigned_short  , pu); }
   payload & assign_pi32   (int * pi)   { return __assign_primitive_pointer(m_pi   , e_type_pint  , pi); }
   payload & assign_pu32   (unsigned int * pu)   { return __assign_primitive_pointer(m_pui   , e_type_punsigned_int  , pu); }
   payload & assign_pi64   (long long * pi)   { return __assign_primitive_pointer(m_pll   , e_type_plong_long  , pi); }
   payload & assign_pu64   (unsigned long long * pu)   { return __assign_primitive_pointer(m_pull   , e_type_punsigned_long_long  , pu); }
   payload & assign_pf32   (float * pf)   { return __assign_primitive_pointer(m_pf   , e_type_pfloat  , pf); }
   payload & assign_pf64   (double * pf)   { return __assign_primitive_pointer(m_pd   , e_type_pdouble  , pf); }

protected:


   template < typename PRIMITIVE >
   bool __assign_to_held_pointer_member(PRIMITIVE prototype)
   {

      if(get_type() == e_type_pbool)
      {

         *m_pb = (bool) prototype;

      }
      else if(get_type() == e_type_punsigned_char)
      {

         *m_puch = (unsigned char) prototype;

      }
      else if(get_type() == e_type_pchar)
      {

         *m_pch = (char) prototype;

      }
      else if(get_type() == e_type_punsigned_short)
      {

         *m_push = (unsigned short) prototype;

      }
      else if(get_type() == e_type_pshort)
      {

         *m_psh = (short) prototype;

      }
      else if(get_type() == e_type_punsigned_int)
      {

         *m_pui = (unsigned int) prototype;

      }
      else if(get_type() == e_type_pint)
      {

         *m_pi = (int) prototype;

      }
      else if(get_type() == e_type_punsigned_long_long)
      {

         *m_pull = (unsigned long long) prototype;

      }
      else if(get_type() == e_type_plong_long)
      {

         *m_pll = (long long) prototype;

      }
      else if(get_type() == e_type_pfloat)
      {

         *m_pf = (float) prototype;

      }
      else if(get_type() == e_type_pdouble)
      {

         *m_pd = (double) prototype;

      }
      else
      {

         return false;

      }

      return true;

   }


   template < typename PRIMITIVE >
   payload& __assign_primitive(PRIMITIVE& member, enum_type etype, PRIMITIVE prototype);


   template < typename PRIMITIVE >
   payload & __assign_primitive_pointer(PRIMITIVE * & member, enum_type etype, PRIMITIVE * pprimitive)
   {

      set_type(etype, false);

      member = pprimitive;

      return *this;

   }


public:
   template < bool_type BOOL > payload & operator=(BOOL b) { return assign_bool(b); }
#define NUMBER_TYPE_OPERATION(NUMBER_TYPE, NUMBER_NAME, NUMBER_SHORT_NAME, UPPER_CASE_NAME) \
template < same_as < NUMBER_TYPE > UPPER_CASE_NAME > payload & operator = (UPPER_CASE_NAME NUMBER_SHORT_NAME) \
{return assign_## NUMBER_NAME(NUMBER_SHORT_NAME);}
   DO_FOR_NUMBER_TYPES(NUMBER_TYPE_OPERATION)
#undef NUMBER_TYPE_OPERATION

   //template < char_type CHAR > payload & operator=(CHAR c) { return assign_char(c); }
   //template < i8_type I8 > payload & operator=(I8 i) { return assign_char(i); }
   //template < same_as < unsigned char > U8 > payload & operator=(U8 u) { return assign_unsigned_char(u); }
   //template < same_as < short > I16 > payload & operator=(I16 i) { return assign_short(i); }
   //template < same_as < unsigned short > U16 > payload & operator=(U16 u) { return assign_unsigned_short(u); }
   //template < same_as < int > I32 > payload & operator=(I32 i) { return assign_int(i); }
   //template < same_as < unsigned int > U32 > payload & operator=(U32 u) { return assign_unsigned_int(u); }
   //template < same_as < long long > I64 > payload & operator=(I64 i) { return assign_long_long(i); }
   //template < same_as < unsigned long long > U64 > payload & operator=(U64 u) { return assign_unsigned_long_long(u); }
   //template < same_as < float > F32 > payload & operator=(F32 f) { return assign_float(f); }
   //template < same_as < double > F64 > payload & operator=(F64 f) { return assign_double(f); }


   payload & assign_pointer(char * pi) { return assign_pi8(pi); }
   payload & assign_pointer(unsigned char * pu) { return assign_pu8(pu); }
   payload & assign_pointer(short * pi) { return assign_pi16(pi); }
   payload & assign_pointer(unsigned short * pu) { return assign_pu16(pu); }
   payload & assign_pointer(int * pi) { return assign_pi32(pi); }
   payload & assign_pointer(float* pf) { return assign_pf32(pf); }
   payload & assign_pointer(unsigned int * pu) { return assign_pu32(pu); }
   payload & assign_pointer(long long * pi) { return assign_pi64(pi); }
   payload & assign_pointer(double* pd) { return assign_pf64(pd); }
   payload & assign_pointer(unsigned long long * pu) { return assign_pu64(pu); }

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

   //template < prototype_character CHARACTER, int t_size >
   //payload & operator = (const const_string_range_static_array< const CHARACTER *, t_size > & a)
   //{

   //   return this->operator=(::string(a));

   //}
   payload & operator = (const ::payload & payload);
   payload & operator = (const ::int_array_base & ia);
   payload& operator = (const ::long_long_array_base& longlonga);
   payload& operator = (const ::float_array_base& floata);
   payload& operator = (const ::double_array_base& doublea);
   payload & operator = (const ::string_array_base & stra);
   payload & operator = (const ::memory & memory);
   payload & operator = (const ::payload_array & payloada);
   payload & operator = (const ::property_set & propset);
   payload & operator = (const ::atom & atom);
   payload & operator = (::atom * pid);
   template < prototype_enum ENUM >
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

   template < character_count n >
   payload & operator = (const char(&cha)[n])
   {

      return this->operator = (::string(cha));

   }


   //template < prototype_subparticle T >
   //T * cast();

   template < prototype_subparticle T >
   ::pointer < T > cast(T* pDefault = nullptr);

   template < class T >
   T & defer_create_type(T * pdefault = nullptr)
   {

      ::pointer< T > p = pdefault;

      if (!p)
      {

         p = øallocate T();

         operator =(p);

      }

      return *p;

   }


   template < typename T >
   T & as_type();


   //template < class T >
   //::ptr< T > cast(T * pDefault) const
   //{
   //   return ((payload *)this)->cast < T >(pDefault);
   //}


   //template < class T >
   //::pointer< T > cast();

   ::subparticle * as_subparticle()
   {
      if (m_etype == e_type_element) { return m_p; }
      return cast < ::subparticle >();
   }

   ::subparticle * as_subparticle() const { return ((payload *)this)->as_subparticle(); }

   template < prototype_particle T >
   T * cast() const
   {
      return ((payload *)this)->cast < T >();
   }


   ::subparticle * get_subparticle();

   //   bool strictly_equal(const payload & payload) const;
   //   bool strictly_equal(const ::scoped_string & scopedstr) const;
   //   bool strictly_equal(const ::scoped_string & scopedstr) const;
   //   bool strictly_equal(double d) const;
   //   bool strictly_equal(int i) const;
   //   bool strictly_equal(bool b) const;
   //
   //   bool strictly_different(const payload & payload) const;
   //   bool strictly_different(const ::scoped_string & scopedstr) const;
   //   bool strictly_different(const ::scoped_string & scopedstr) const;
   //   bool strictly_different(double d) const;
   //   bool strictly_different(int i) const;
   //   bool strictly_different(bool b) const;

      //friend bool CLASS_DECL_ACME strict_equal(const ::scoped_string & scopedstr,const payload & payload);
      //friend bool CLASS_DECL_ACME strict_equal(const ::scoped_string & scopedstr,const payload & payload);
      //friend bool CLASS_DECL_ACME strict_equal(double d,const payload & payload);
      //friend bool CLASS_DECL_ACME strict_equal(int i,const payload & payload);
      //friend bool CLASS_DECL_ACME strict_equal(bool b,const payload & payload);

      //friend bool CLASS_DECL_ACME strict_different(const ::scoped_string & scopedstr,const payload & payload);
      //friend bool CLASS_DECL_ACME strict_different(const ::scoped_string & scopedstr,const payload & payload);
      //friend bool CLASS_DECL_ACME strict_different(double d,const payload & payload);
      //friend bool CLASS_DECL_ACME strict_different(int i,const payload & payload);
      //friend bool CLASS_DECL_ACME strict_different(bool b,const payload & payload);

   //bool equals(const payload & payload) const;
   //bool equals(const ::scoped_string & scopedstr) const;

   bool case_insensitive_equals(const payload & payload) const;

   ::std::strong_ordering order_payload(const payload & payload) const;

   ::std::strong_ordering case_insensitive_order(const ::payload & payload) const;


   bool equals_payload(const ::payload & payload) const;
   bool equals_signed(long long i) const;
   bool equals_unsigned(unsigned long long u) const;
   bool equals_scoped_string(const ::scoped_string & scopedstr) const;


   template < prototype_character CHARACTER >
   bool operator == (const CHARACTER * psz) const { return equals_scoped_string(psz); }
   template < prototype_character CHARACTER  >
   bool operator == (const character_range < const CHARACTER * > & range) const { return equals_scoped_string(range); }
   template < prototype_character CHARACTER  >
   bool operator == (const scoped_string_base < const CHARACTER * > & scoped_string) const { return equals_scoped_string(scoped_string); }
   template < prototype_character CHARACTER  >
   bool operator == (const string_base < const CHARACTER * > & string) const { return equals_scoped_string(string); }
   template < prototype_character CHARACTER  >
   bool operator == (const string_range < const CHARACTER * > & string_range) const { return equals_scoped_string(string_range); }
   //bool operator == (const ::scoped_string & scopedstr) const;
   template < prototype_signed SIGNED >
   bool operator == (SIGNED i) const { return equals_signed(i); }
   template < prototype_unsigned UNSIGNED >
   bool operator == (UNSIGNED u) const { return equals_unsigned(u); }
   //bool operator == (int i) const;
   //bool operator == (bool b) const;

   //bool operator != (const payload & payload) const;
   //bool operator != (const ::scoped_string & scopedstr) const;
   //bool operator != (const ::scoped_string & scopedstr) const;
   //bool operator != (long long i) const;
   //bool operator != (int i) const;
   //bool operator != (bool b) const;

   ::std::strong_ordering operator <=> (const payload & payload) const;
   ::std::strong_ordering operator <=> (const ::scoped_string & scopedstr) const;
   ::std::strong_ordering operator <=> (const ::string & str) const;
   ::std::strong_ordering operator <=> (long long i) const;
   ::std::strong_ordering operator <=> (int i) const;
   ::std::strong_ordering operator <=> (bool b) const;

   //bool operator <= (const payload & payload) const;
   //bool operator <= (const ::scoped_string & scopedstr) const;
   //bool operator <= (const ::scoped_string & scopedstr) const;
   //bool operator <= (long long i) const;
   //bool operator <= (int i) const;
   //bool operator <= (bool b) const;

   //bool operator >= (const payload & payload) const;
   //bool operator >= (const ::scoped_string & scopedstr) const;
   //bool operator >= (const ::scoped_string & scopedstr) const;
   //bool operator >= (long long i) const;
   //bool operator >= (int i) const;
   //bool operator >= (bool b) const;

   //bool operator > (const payload & payload) const;
   //bool operator > (const ::scoped_string & scopedstr) const;
   //bool operator > (const ::scoped_string & scopedstr) const;
   //bool operator > (long long i) const;
   //bool operator > (int i) const;
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
   ::property * _find_property(const ::atom & atom) const;
   ::property & get_property(const ::atom & atom); // { return atom.is_text() ? get_property_text_key((const ::scoped_string &)atom.m_str) : get_property_index(atom.m_i); }

   ::payload find_property_by_text(const ::scoped_string & scopedstr) const; 

   ::payload find_property_by_name(const ::scoped_string &scopedstr) const; 



   //::payload operator[] (const ::atom & atom);
   //::payload operator[] (const ::atom & atom) const;
   template < prototype_integral INTEGRAL >
   inline ::payload operator[] (INTEGRAL i) { return at(i); }
   template < prototype_integral INTEGRAL >
   inline ::payload operator[] (INTEGRAL i) const { return at(i); }

   template < prototype_character CHARACTER >
   inline ::property & operator[] (const CHARACTER * psz) { return get_property(psz); }
   template < prototype_character CHARACTER >
   inline ::payload operator[] (const CHARACTER * psz) const { return find_property_by_name(psz); }

   template < prototype_character_range RANGE >
   inline ::property & operator[] (const RANGE & range) { return get_property(range); }
   template < prototype_character_range RANGE >
   inline ::payload operator[](const RANGE &range) const
   {
      return find_property_by_name(range);
   }

   template < has_as_string HAS_AS_STRING >
   inline ::property & operator[] (const HAS_AS_STRING & has_as_string) 
   requires (!prototype_character_range<HAS_AS_STRING>)
   { return get_property(has_as_string.as_string()); }
   template < has_as_string HAS_AS_STRING >
   inline ::payload operator[] (const HAS_AS_STRING & has_as_string) const
   requires (!prototype_character_range<HAS_AS_STRING>)
   {
      return find_property_by_name(has_as_string.as_string());
   }

   template < has_get_string HAS_GET_STRING >
   inline ::property & operator[] (const HAS_GET_STRING & has_get_string) 
   requires (!prototype_character_range<HAS_GET_STRING> && has_as_string<HAS_GET_STRING>)
   { return get_property(has_get_string.get_string()); }
   template < has_get_string HAS_GET_STRING >
   inline ::payload operator[] (const HAS_GET_STRING & has_get_string) const 
   requires (!prototype_character_range<HAS_GET_STRING>&& has_as_string<HAS_GET_STRING>)
   {
      return find_property_by_name(has_get_string.get_string());
   }


   //inline ::property & operator[] (::iptr i);
   //inline ::payload operator[] (::iptr i) const;

//#if OSBIT == 64
//
//   inline ::property & operator[] (int i) { return get_property(::atom(i)); }
//   inline ::payload operator[] (int i) const { return find_property(::atom(i)); }
//
//#endif


   ::payload equals_ci_get(const ::scoped_string & scopedstrCompare,::payload varOnEqual,payload varOnDifferent) const;
   ::payload equals_ci_get(const ::scoped_string & scopedstrCompare,::payload varOnEqual) const;

   template < prototype_integral INTEGRAL >
   ::payload operator - (INTEGRAL i) const;
   template < prototype_floating FLOATING >
   ::payload operator - (FLOATING f) const;


   template < prototype_integral INTEGRAL >
   ::payload operator + (INTEGRAL i) const;
   template < prototype_floating FLOATING >
   ::payload operator + (FLOATING f) const;

   //::payload operator + (const ::scoped_string & scopedstr) const;
   //::payload operator + (const ::scoped_string & scopedstr) const;
   //::payload operator + (const ::inline_number_string & inline_number_string) const;

   template < prototype_integral INTEGRAL >
   ::payload operator / (INTEGRAL i) const;
   template < prototype_floating FLOATING >
   ::payload operator / (FLOATING f) const;

   template < prototype_integral INTEGRAL >
   ::payload operator * (INTEGRAL i) const;
   template < prototype_floating FLOATING >
   ::payload operator * (FLOATING d) const;

   ::std::strong_ordering str_compare(const ::property & prop) const;



   template < prototype_integral INTEGRAL >
   ::payload & operator -= (INTEGRAL i);
   template < prototype_floating FLOATING >
   ::payload & operator -= (FLOATING f);


   template < prototype_integral INTEGRAL >
   ::payload & operator += (INTEGRAL i);
   template < prototype_floating FLOATING >
   ::payload & operator += (FLOATING f);

   //::payload & operator += (const ::scoped_string & scopedstr);
   //::payload & operator += (const ::scoped_string & scopedstr);
   //::payload & operator += (const ::inline_number_string & inline_number_string);
   //template < character_count n >
   //::payload & operator += (const ::ansi_character (&cha)[n]) { return *this += ::scoped_string(cha);}

   //template < typename ITERATOR_TYPE, int t_size >
   //::payload & operator += (const const_string_range_static_array < ITERATOR_TYPE, t_size > & a) { return *this += ::string(a);}

   template < prototype_integral INTEGRAL >
   ::payload & operator /= (INTEGRAL i);
   template < prototype_floating FLOATING >
   ::payload & operator /= (FLOATING f);

   template < prototype_integral INTEGRAL >
   ::payload & operator *= (INTEGRAL i);
   template < prototype_floating FLOATING >
   ::payload & operator *= (FLOATING d);


   void consume_number(::ansi_range & range);
   //void consume_number((::ansi_range & range);
   void consume_identifier(::ansi_range & range);
   //void consume_identifier((::ansi_range & range);
   void parse_network_payload(::ansi_range & range);
   //void parse_network_payload((::ansi_range & range);
   const_char_pointer parse_network_payload(const ::scoped_string & scopedstrNetworkPayload);
   ::enum_type find_network_payload_child(::ansi_range & range, const payload & payload);
   //::enum_type find_network_payload_child((::ansi_range & range, const payload & payload);
   ::enum_type find_network_payload_id(::ansi_range & range, const payload & payload);
   bool parse_network_payload_step(::ansi_range & range);
   // bool parse_network_payload_step(const_char_pointer &pszJson, const_char_pointer pszEnd);

   ::string & get_network_payload(::string & str, bool bNewLine = true) const;
   ::string get_network_payload(bool bNewLine = true) const;



   //
   // DECLARE_AXIS_FIXED_ALLOC(payload)

   void null();



   void _001Add(const ::string_array_base & stra);


   void defer_run_payload();

   void receive_response(const payload & payload);


};


#include "acme/prototype/collection/__payload_array.h"


#include "__payload_reference.h"
#include "acme/prototype/collection/property_set.h"
#include "acme/prototype/prototype/url.h"



//
//namespace str
//{


   //inline CLASS_DECL_ACME void from(::string & str, const payload & payload)
   //{

   //   str = payload;

   //}

//
//} // namespace str


//CLASS_DECL_ACME void var_skip_number(const_char_pointer &psz);
CLASS_DECL_ACME void payload_skip_number(::ansi_range & range);
//CLASS_DECL_ACME void var_skip_identifier(const_char_pointer &psz);
CLASS_DECL_ACME void payload_skip_identifier(::ansi_range & range);
//CLASS_DECL_ACME void var_skip_network_payload(const_char_pointer &pszJson);
CLASS_DECL_ACME void payload_skip_network_payload(::ansi_range & range);




//#if defined(__APPLE__) || defined(__ANDROID__) || defined(RASPBERRYPIOS) || defined(WINDOWS)
//
//
//inline payload::operator long &()
//{
//
//   set_type(e_type_long_long);
//
//   return (long &) m_hi;
//
//}
//
//
//inline payload::operator unsigned long &()
//{
//
//   set_type(e_type_unsigned_long_long);
//
//   return (unsigned long &) m_hn;
//
//}
//
//
//#endif


// returns 0 for unknown conversions
//inline payload::operator char() const
//{
//   return char();
//}

// returns 0 for unknown conversions
//inline payload::operator unsigned char() const
//{
//   return unsigned char();
//}


// returns 0 for unknown conversions
//inline payload::operator short() const
//{
//   return short();
//}

// returns 0 for unknown conversions
//inline payload::operator unsigned short() const
//{
//   return unsigned short();
//}



// returns 0 for unknown conversions
//inline payload::operator int() const
//{
//   return int();
//}

// returns 0 for unknown conversions
//inline payload::operator unsigned int() const
//{
//   return unsigned int();
//}


// returns 0 for unknown conversions
//inline payload::operator long long()const
//{
//   return long_long;
//}

// returns 0 for unknown conversions
//inline payload::operator unsigned long long() const
//{
//   return unsigned_long_long;
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

   return as_long_long(iDefault);

#else

   return as_int(iDefault);

#endif

}


inline uptr payload::as_uptr(::uptr uiDefault) const
{

#ifdef OS64BIT

   return as_unsigned_long_long(uiDefault);

#else

   return as_unsigned_int(uiDefault);

#endif

}


#ifdef WINDOWS

//#elif defined(__APPLE__) || defined(RASBPIAN)
#elif defined(RASBPIAN)

inline payload::operator long() const
{

   return as_long_long();

}



// returns 0 for unknown conversions
inline payload::operator unsigned long() const
{
#if LONG_IS_32BIT
   return as_unsigned_int();
#else
   return as_unsigned_long_long();
#endif
}


//#elif defined(__ANDROID__)
//
//inline payload::operator long() const
//{
//
//   return int();
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


//template < prototype_character_range RANGE, prototype_payload PAYLOAD >
//::string operator + (const RANGE & range, const PAYLOAD & has_as_string);


template < prototype_payload PAYLOAD1, prototype_payload PAYLOAD2 >
inline PAYLOAD1 operator +(const PAYLOAD1 & payload1, const PAYLOAD2 & payload2)
{

   auto payload = payload1;

   payload.addition(payload2);

   return ::transfer(payload);

}


template < prototype_payload PAYLOAD1, prototype_payload PAYLOAD2 >
inline PAYLOAD1 & operator +=(PAYLOAD1 & payload1, const PAYLOAD2 & payload2)
{

   return payload1.add(payload2);

}


template < prototype_payload PAYLOAD, character_pointer CHARACTER_POINTER >
inline ::string operator +(const PAYLOAD & payload, CHARACTER_POINTER psz)
{

   ::string str(payload);

   str.append(psz);

   return ::transfer(str);

}


template < prototype_payload PAYLOAD, prototype_character CHARACTER >
inline PAYLOAD & operator +=(PAYLOAD & payload, const CHARACTER * psz)
{

   payload = ::string(payload.as_string() + psz);

   return payload;

}


//template < prototype_character CHARACTER, prototype_payload PAYLOAD >
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


CLASS_DECL_ACME void copy(::string & str, const ::payload & payload);
CLASS_DECL_ACME void copy(::payload & payload, const int & i);
CLASS_DECL_ACME  void copy(::payload & payload, const ::scoped_string & scopedstr);


template < prototype_payload PAYLOAD1, prototype_payload PAYLOAD2 >
inline bool operator == (const PAYLOAD1 & payload1, const PAYLOAD2 & payload2)
{

   return payload1.equals_payload(payload2);

}





template < prototype_character_range CHARACTER_RANGE >
payload::payload(const CHARACTER_RANGE& range) :
   payload(no_initialize_t{})
{

   m_etype = e_type_string;
   zero(m_str);
   m_str = range;

}


template < prototype_character CHARACTER, prototype_payload PAYLOAD >
inline ::file::path operator / (
   const ::character_range < const CHARACTER * > & range,
   const PAYLOAD & payload)
{

   return ::file::path(range) / payload.as_file_path();

}




