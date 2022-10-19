#pragma once


inline payload & copy(payload & payload, const integral_second & integralsecond);


enum para_return
{
   e_fail = 0x80000000,
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


template < typename PAYLOAD_TYPE >
concept payload_class = (is_derived_from < PAYLOAD_TYPE, ::payload > || ::std::same_as < PAYLOAD_TYPE, ::payload >);


class CLASS_DECL_ACME payload // : public payload_type < payload >
{
public:


   enum_type                        m_etype;


   union
   {

      void *                     m_pvoid;
      para_return                m_parareturn;
      atom                       m_atom;
      type                       m_type;
      bool                       m_b;
      bool *                     m_pb;
      ::i8                       m_i8;
      ::u8                       m_u8;
      ::i16                      m_i16;
      ::u16                      m_u16;
      ::i32                      m_i32;
      ::u32                      m_u32;
      ::i64                      m_i64;
      ::u64                      m_u64;
      ::i8 *                     m_pi8;
      ::u8 *                     m_pu8;
      ::i16 *                    m_pi16;
      ::u16 *                    m_pu16;
      ::i32 *                    m_pi32;
      ::u32 *                    m_pu32;
      ::i64 *                    m_pi64;
      ::u64 *                    m_pu64;
      ::string *                 m_pstr;
      ::f32                      m_f32;
      ::f32 *                    m_pf32;
      ::f64                      m_f64;
      ::f64 *                    m_pf64;
      payload *                  m_ppayload;
      ::earth::time              m_time;
      file_time_t                m_filetime;
      atom *                     m_patom;
      ::property *               m_pproperty;
      integral_nanosecond        m_integralnanosecond;
      integral_nanosecond *      m_pintegralnanosecond;
      integral_microsecond       m_integralmicrosecond;
      integral_microsecond *     m_pintegralmicrosecond;
      integral_millisecond       m_integralmillisecond;
      integral_millisecond *     m_pintegralmillisecond;
      integral_second            m_integralsecond;
      integral_second *          m_pintegralsecond;
      integral_minute            m_integralminute;
      integral_minute *          m_pintegralminute;
      integral_hour              m_integralhour;
      integral_hour *            m_pintegralhour;
      integral_day               m_integralday;
      integral_day *             m_pintegralday;
      floating_nanosecond        m_floatingnanosecond;
      floating_nanosecond *      m_pfloatingnanosecond;
      floating_microsecond       m_floatingmicrosecond;
      floating_microsecond *     m_pfloatingmicrosecond;
      floating_millisecond       m_floatingmillisecond;
      floating_millisecond *     m_pfloatingmillisecond;
      floating_second            m_floatingsecond;
      floating_second *          m_pfloatingsecond;
      floating_minute            m_floatingminute;
      floating_minute *          m_pfloatingminute;
      floating_hour              m_floatinghour;
      floating_hour *            m_pfloatinghour;
      floating_day               m_floatingday;
      floating_day *             m_pfloatingday;
      class duration             m_duration;
      class duration *           m_pduration;
      ::e_status                 m_estatus;
      ::e_command                m_ecommand;
      ::e_check                  m_echeck;
      ::e_flag                   m_eflag;
      ::color::color             m_color;
      ::color::hls               m_hls;


      ::particle *               m_p;
      ::string_array *           m_pstra;
      ::int_array *              m_pia;
      ::payload_array *          m_ppayloada;
      ::property_set *           m_ppropertyset;
      ::i64_array *              m_pi64a;
      ::memory *                 m_pmemory;
      ::file::path_object *      m_ppath;
      ::i64                      m_all[3];
      ::string                   m_str;

   };


   inline payload();
   inline payload(enum_type etype);
   inline payload(std::nullptr_t);
   payload(bool b);
   payload(::i32 i);
   payload(::u32 u);
   payload(::i64 i);
   payload(::u64 u);
   payload(float f);
   payload(double d);
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
   payload(::payload * ppayload);
   payload(::property * pproperty);
   payload(::particle * pobject);
   payload(::duration * pduration);
   payload(const char * psz);
   payload(const ::string & str);
   payload(const ::type & type);
   payload(const ::atom & atom);
   payload(const ::earth::time & time);
   payload(const ::color::color & color);
   payload(const ::color::hls & hls);
   payload(const ::particle & particle);
   payload(const ::file::path & path);
   payload(const ::string_array & payload);
   payload(const ::int_array & payload);
   payload(const ::payload_array & payload);
   payload(const ::property_set & set);
   payload(const ::payload & payload);
   payload(const ::property & prop);
   payload(const ::duration & duration);

   payload(const ::block & block)
   {
      m_etype = e_type_new;
      operator = (block);
   }

   template < class T >
   payload(const ::pointer < T > & p)
   {
      m_etype = e_type_new;
      operator = (p.m_p);
   }

   template < class T >
   payload(const ptr < T > & p)
   {
      m_etype = e_type_new;
      operator = (p.m_p);
   }

   //template < class T >
   //payload(const pointer < T >& resultpointer)
   //{
   //   m_etype = e_type_new;

   //   operator = (resultpointer);

   //}

   template < typename BLOCK_TYPE >
   payload(const ::memory_template < BLOCK_TYPE > & memorytemplate)
   {
      m_etype = e_type_new;
      operator = (memorytemplate.block());
   }

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

   template < typename T >
   payload(const T & t)
   {
      m_etype = e_type_new;
      operator = (t);
   }


   //payload(const ::e_status & estatus)
   //{
   //   m_etype = e_type_new;
   //   operator = (estatus.m_estatus);
   //}

   ~payload();


   void clear_data() { m_all[0] = 0; m_all[1] = 0; }


   void set_type(enum_type enum_type, bool bConvert = true);
   enum_type get_type() const;


   void set_type(const ::type & type);


   template < typename T >
   void set_pointer(const ::pointer < T > & p)
   {

      operator[](__type_name < T >()) = p;

   }

   template < typename T >
   bool has_pointer() const
   {

      return has_property(__type_name < T >());

   }

   template < typename T >
   ::property * find_pointer() const
   {

      return find_property(__type_name < T >());

   }

   template < typename T >
   ::pointer < T > pointer() const;

   bool get_type(::type & type) const;

   ::i64 release();

   void _set_element(::particle * pelement);

   bool is_element() const { return m_etype >= e_type_element && m_etype < e_type_last_element; }

   bool is_element_set() const { return is_element() && ::is_set(m_p); }

   bool is_element_null() const { return is_element() && ::is_null(m_p); }

   bool is_numeric() const;

   inline bool is_number() const
   {

      return is_numeric();

   }

   bool convert(const ::payload & payload);


   bool                             get_bool(bool bDefault = false)     const;

   template < typename ENUM >
   ENUM                             e(ENUM edefault = enum_default < ENUM >())  const { return (ENUM)i64(edefault); }

#define DECL_VAR_FLAG(ENUMTYPE) \
inline payload(::enum_ ## ENUMTYPE e ## ENUMTYPE) { m_etype = ::e_type_enum_ ## ENUMTYPE; m_e ## ENUMTYPE = e ## ENUMTYPE; } \
inline ::enum_ ## ENUMTYPE e ## ENUMTYPE(::enum_ ## ENUMTYPE e ## ENUMTYPE ## Default = enum_default < ::enum_ ## ENUMTYPE >()) const { return e < ::enum_ ## ENUMTYPE >(e ## ENUMTYPE ## Default); } \
::enum_ ## ENUMTYPE & as_e ## ENUMTYPE ();         \
inline payload & operator = (::enum_ ## ENUMTYPE e ## ENUMTYPE) { release(); if(m_etype != ::e_type_enum_ ## ENUMTYPE) m_etype = ::e_type_enum_ ## ENUMTYPE; m_e ## ENUMTYPE = e ## ENUMTYPE; return *this; } \
inline bool operator == (::enum_ ## ENUMTYPE e ## ENUMTYPE) const { return m_etype == ::e_type_enum_ ## ENUMTYPE && m_e ## ENUMTYPE == e ## ENUMTYPE; } \
inline bool operator != (::enum_ ## ENUMTYPE e ## ENUMTYPE) const { return !operator ==(e ## ENUMTYPE); }
#undef DECL_VAR_FLAG



#define DECL_VAR_ENUM(ENUMTYPE) \
   inline payload(const ::e_ ## ENUMTYPE & e) { m_etype = ::e_type_enum_ ## ENUMTYPE; m_e ## ENUMTYPE = e; } \
   inline ::e_ ## ENUMTYPE e ## ENUMTYPE(::enum_ ## ENUMTYPE eDefault = enum_default < ::enum_ ## ENUMTYPE >()) const { return e < ::enum_ ## ENUMTYPE >(eDefault); } \
   inline operator ::e_ ## ENUMTYPE () const { return ::e_ ## ENUMTYPE(); } \
   ::e_ ## ENUMTYPE & e_ ## ENUMTYPE ## _reference();         \
   inline payload & operator = (const ::e_ ## ENUMTYPE & e) { set_type(::e_type_enum_ ## ENUMTYPE, false); m_e ## ENUMTYPE = e; return *this; } \
   inline payload & operator = (::enum_ ## ENUMTYPE e) { set_type(::e_type_enum_ ## ENUMTYPE, false); m_e ## ENUMTYPE = e; return *this; } \
   inline bool operator == (::e_ ## ENUMTYPE e) const { return m_etype == ::e_type_enum_ ## ENUMTYPE && m_e ## ENUMTYPE == e; } \
   inline bool operator != (::e_ ## ENUMTYPE e) const { return !operator ==(e); }
   DECL_VAR_ENUM(status);
   DECL_VAR_ENUM(command);
   DECL_VAR_ENUM(check);
#undef DECL_VAR_ENUM


   //inline ::second & as_secs() { if (get_type() != e_type_secs)set_type(e_type_secs); return m_secs; }
   //inline ::duration & as_millis() { if (get_type() != e_type_millis)set_type(e_type_millis); return m_millis; }
   //inline ::microsecond & as_micros() { if (get_type() != e_type_micros)set_type(e_type_micros); return m_micros; }
   //inline ::nanosecond & as_nanos() { if (get_type() != e_type_nanos)set_type(e_type_nanos); return m_nanos; }

   void as(::string & str) const;
   void as(::memory_base & memory) const;


#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN) || defined(WINDOWS)
   long get_long(long lDefault = 0) const;
   unsigned long get_unsigned_long(unsigned long ulDefault = 0) const;
#endif


   ::i8 i8(::i8 iDefault = 0) const;
   ::u8 u8(::u8 uDefault = 0) const;
   ::i16 i16(::i16 iDefault = 0) const;
   ::u16 u16(::u16 uDefault = 0) const;
   ::i32 i32(::i32 iDefault = 0)  const;
   ::u32 u32(::u32 uiDefault = 0)  const;
   ::i64 i64(::i64 iDefault = 0)  const;
   ::u64 u64(::u64 uiDefault = 0)  const;
   ::f32 f32(::f32 fDefault = 0) const;
   ::f64 f64(::f64 fDefault = 0) const;


   inline ::iptr iptr(iptr iDefault = 0)  const;
   inline ::uptr uptr(uptr uiDefault = 0)  const;

   ::file::path file_path() const;
   ::file_time file_time() const;
   ::earth::time earth_time() const;
   ::color::color color(const ::color::color & colorDefault = ::color::color())  const;
   ::color::hls hls(const ::color::hls & hlsDefault = ::color::hls())  const;
   ::block block() const;


   ::procedure get_procedure() const;


   ::string string(const char * pszOnNull = nullptr) const;
   ::string get_string() const;
   ::string get_recursive_string() const;
   ::atom atom(const ::atom & idDefault = nullptr)   const;

   ::memory memory() const;
   ::string_array stra() const;
   ::int_array ia() const;
   ::i64_array i64a() const;
   ::payload_array payloada()  const;
   ::property_set propset() const;
   ::duration duration() const;
   ::property property() const;


   bool is_scalar() const;
   inline bool is_array() const;
   bool is_floating() const;
   bool is_integer() const;
   bool is_natural() const;
   bool is_boolean() const;
   bool is_double() const;
   bool is_duration() const;

   bool ok() const;
   bool failed() const;


   payload dereference();





   ::comparison::var_strict strictly_compare() const;

   void           set_string(const char * psz);
   void           set_string(const ::string & str);
   void           set_string(::string && str);
   void           set_id(const ::atom & atom);
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


   bool begins(const ::string & strPrefix) const { return get_string().begins(strPrefix); }
   bool ends(const ::string & strSuffix) const { return get_string().ends(strSuffix); }
   bool begins_ci(const ::string & strPrefix) const { return get_string().begins_ci(strPrefix); }
   bool ends_ci(const ::string & strSuffix) const { return get_string().ends_ci(strSuffix); }

   payload get_topic(const ::atom & atom) const;
   //payload defer_get(const ::atom & atom) const;

   payload & operator ++(::i32);

   template < payload_class PAYLOAD >
   payload operator +(const PAYLOAD & payload) const;
   template < payload_class PAYLOAD >
   payload operator -(const PAYLOAD & payload) const;
   template < payload_class PAYLOAD >
   payload operator *(const PAYLOAD & payload) const;
   template < payload_class PAYLOAD >
   payload operator /(const PAYLOAD & payload) const;

   template < payload_class PAYLOAD >
   payload & operator +=(const PAYLOAD & payload);
   template < payload_class PAYLOAD >
   payload & operator -=(const PAYLOAD & payload);
   template < payload_class PAYLOAD >
   payload & operator *=(const PAYLOAD & payload);
   template < payload_class PAYLOAD >
   payload & operator /=(const PAYLOAD & payload);

   bool operator !() const
   {

      return is_false();

   }


   bool b() const;

   operator bool() const { return this->b(); }

   operator ::i8() const { return this->i8(); }
   operator ::u8() const { return this->u8(); }
   operator ::i16() const { return this->i16(); }
   operator ::u16() const { return this->u16(); }
   operator ::i32() const { return this->i32(); }
   operator ::u32() const { return this->u32(); }
   operator ::i64() const { return this->i64(); }
   operator ::u64() const { return this->u64(); }



   operator ::f32() const { return this->f32(); }
   operator ::f64() const { return this->f64(); }
   //operator ::string() const;
   //::memory memory() const;
   //operator ::file::path() const { return this->file_path(); }


   operator ::file_time() const { return this->file_time(); }
   operator ::earth::time() const { return this->earth_time(); }
   operator ::color::color() const { return this->color(); }
   operator ::color::hls() const { return this->hls(); }
   operator ::block() const { return this->block(); }

   ::string & string_reference(const char * pszOnNull = nullptr);

   ::memory & memory_reference();


   ::atom & id_reference(const ::atom & idDefault);


   ::string_array & string_array_reference();
   ::i32_array & i32_array_reference();
   ::i64_array & i64_array_reference();
   ::payload_array & payload_array_reference();
   ::duration & duration_reference();
   ::property_set & property_set_reference();
   ::property & property_reference();


   ::file::path & file_path_reference();


   ::file_time & file_time_reference();
   ::earth::time & earth_time_reference();
   ::color::color & color_reference();
   ::color::hls & color_hls_reference();

   //operator ::enum_check &();


   bool & bool_reference();
#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN) || defined(WINDOWS)
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

   strsize length() const;

   template < typename TYPE >
   inline payload & operator = (const ::pointer<TYPE> & pointer)
   {

      _set_element(pointer.m_pparticle);

      return *this;

   }

    inline payload & operator = (const ::procedure & procedure)
    {

       _set_element(procedure.m_p);

       return *this;

    }

   inline payload & operator = (nullptr_t) { set_type(e_type_null, false); return *this; }

   inline payload & operator = (::particle * pelement)
   {

      _set_element(pelement);

      return *this;

   }


   inline payload & operator = (::memory * pmemory)
   {

      set_type(e_type_memory, false);

      m_pmemory = pmemory;

      ::increment_reference_count(m_pmemory);

      return *this;

   }

   template < typename PREDICATE >
   void predicate_each(PREDICATE predicate)
   {

      auto c = array_get_count();
      
      for (auto i = 0; i < c; i++)
      {

         predicate(at(i));

      }

   }


   void increment_reference_count();




   payload & operator = (const ::particle & o);

   inline payload & operator = (const ::file::path & path)
   {
      set_type(e_type_path, false);
      m_ppath = memory_new ::file::path_object(path);
      return *this;
   }

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

   payload & operator = (para_return & eret);
   payload & operator = (bool b);
   payload & operator = (bool * pb);
   payload & operator = (::i32 i);
   payload & operator = (::i32 * pi);
   payload & operator = (::u32 u);
   payload & operator = (::u32 * pinteraction);
#ifdef WINDOWS
#elif defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN)
   payload & operator = (long l);
#endif
   payload & operator = (::i64 i);
   payload & operator = (::i64 * pi);
   payload & operator = (::u64 i);
   payload & operator = (::u64 * pi);
   payload & operator = (float f);
   payload & operator = (double d);
#ifdef WINDOWS
   payload & operator = (long l);
#endif
   payload & operator = (const ::earth::time & time);
   payload & operator = (const ::color::color & color);
   payload & operator = (const ::color::hls & color);
   inline payload & operator = (const char * psz);
   inline payload & operator = (const ::string & str);
   inline payload & operator = (::string && str);
   payload & operator = (::string * pstr);
   payload & operator = (::payload * pvar);
   payload & operator = (const ::payload * pvar);
   payload & operator = (const ::widechar * pcsz);

   payload & operator = (const ::property & prop);
   payload & operator = (const ::property * pproperty);
   payload & operator = (const ::payload & payload);
   payload & operator = (const ::int_array & ia);
   payload & operator = (const ::string_array & stra);
   payload & operator = (const ::memory & memory);
   payload & operator = (const ::payload_array & payloada);
   payload & operator = (const ::property_set & propset);
   payload & operator = (const ::atom & atom);
   payload & operator = (::atom * pid);
   //payload & operator = (const ::second & second);
   //payload & operator = (class ::second * pduration);
   //payload & operator = (const ::duration & duration);
   //payload & operator = (class ::duration * pmillis);
   //payload & operator = (const ::microsecond & microsecond);
   //payload & operator = (class ::microsecond * pmicros);
   //payload & operator = (const ::nanosecond & nanosecond);
   //payload & operator = (class ::nanosecond * pnanos);
   payload & operator = (const ::duration & duration);
   payload & operator = (class ::duration * pduration);
   payload & operator = (const ::block & block);

   template < class ARRAY >
   void get_array(ARRAY & array) const
   {

      auto count = this->array_get_count();

      for(int i = 0; i < count; i++)
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

   template < class T >
   payload& operator = (const ptr < T > & p)
   {

      return this->operator = (p.m_p);

   }
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
   payload & operator = (const T & t)
   {

      ::copy(*this, t);

      return *this;

   }


   template < class T >
   payload & operator = (const memory_template < T > & memory)
   {

      return this->operator = (memory.block());

   }


   template < class T >
   ::pointer< T > cast(T * pDefault);

   template < class T >
   T & defer_create_type(T * pdefault = nullptr)
   {

      ::pointer< T > p = pdefault;

      if (!p)
      {

         p = __new(T);

         operator =(p);

      }

      return *p;

   }


   template < class T >
   T & get_cast(T * pDefault);


   template < class T >
   ::pointer< T > cast(T * pDefault) const
   {
      return ((payload *) this)->cast < T >(pDefault);
   }


   template < class T >
   ::pointer< T > cast();

   ::particle * particle()
   {
      if (m_etype == e_type_element) { return m_p; }
      return cast < ::particle >();
   }

   ::particle * particle() const { return ((payload *)this)->particle(); }

   template < class T >
   T * cast() const
   {
      return ((payload *) this)->cast < T >();
   }


   bool strictly_equal(const payload & payload) const;
   bool strictly_equal(const char * psz) const;
   bool strictly_equal(const ::string & str) const;
   bool strictly_equal(double d) const;
   bool strictly_equal(::i32 i) const;
   bool strictly_equal(bool b) const;

   bool strictly_different(const payload & payload) const;
   bool strictly_different(const char * psz) const;
   bool strictly_different(const ::string & str) const;
   bool strictly_different(double d) const;
   bool strictly_different(::i32 i) const;
   bool strictly_different(bool b) const;

   //friend bool CLASS_DECL_ACME strict_equal(const char * psz,const payload & payload);
   //friend bool CLASS_DECL_ACME strict_equal(const ::string & str,const payload & payload);
   //friend bool CLASS_DECL_ACME strict_equal(double d,const payload & payload);
   //friend bool CLASS_DECL_ACME strict_equal(::i32 i,const payload & payload);
   //friend bool CLASS_DECL_ACME strict_equal(bool b,const payload & payload);

   //friend bool CLASS_DECL_ACME strict_different(const char * psz,const payload & payload);
   //friend bool CLASS_DECL_ACME strict_different(const ::string & str,const payload & payload);
   //friend bool CLASS_DECL_ACME strict_different(double d,const payload & payload);
   //friend bool CLASS_DECL_ACME strict_different(::i32 i,const payload & payload);
   //friend bool CLASS_DECL_ACME strict_different(bool b,const payload & payload);

   ::i32 compare(const payload & payload) const;
   ::i32 compare(const char * psz) const;

   ::i32 compare_ci(const payload & payload) const;
   ::i32 compare_ci(const char * psz) const;

   bool operator == (const payload & payload) const;
   bool operator == (const char * psz) const;
   bool operator == (const ::string & str) const;
   bool operator == (::i64 i) const;
   bool operator == (::i32 i) const;
   bool operator == (bool b) const;

   bool operator != (const payload & payload) const;
   bool operator != (const char * psz) const;
   bool operator != (const ::string & str) const;
   bool operator != (::i64 i) const;
   bool operator != (::i32 i) const;
   bool operator != (bool b) const;

   bool operator < (const payload & payload) const;
   bool operator < (const char * psz) const;
   bool operator < (const ::string & str) const;
   bool operator < (::i64 i) const;
   bool operator < (::i32 i) const;
   bool operator < (bool b) const;

   bool operator <= (const payload & payload) const;
   bool operator <= (const char * psz) const;
   bool operator <= (const ::string & str) const;
   bool operator <= (::i64 i) const;
   bool operator <= (::i32 i) const;
   bool operator <= (bool b) const;

   bool operator >= (const payload & payload) const;
   bool operator >= (const char * psz) const;
   bool operator >= (const ::string & str) const;
   bool operator >= (::i64 i) const;
   bool operator >= (::i32 i) const;
   bool operator >= (bool b) const;

   bool operator > (const payload & payload) const;
   bool operator > (const char * psz) const;
   bool operator > (const ::string & str) const;
   bool operator > (::i64 i) const;
   bool operator > (::i32 i) const;
   bool operator > (bool b) const;


   ::string implode(const char * pszGlue) const;
   payload explode(const char * pszGlue,bool bAddEmpty = true) const;

   payload first() const;
   payload last() const;
   payload first();
   payload last();
   inline ::count get_count() const;


   inline ::property & operator[] (const ::atom & atom) { return get_property(atom); }
   inline ::payload operator[] (const ::atom & atom) const { return find_property(atom); }

   inline ::property & operator[] (const char * psz) { return get_property(::atom(psz)); }
   inline ::payload operator[] (const char * psz) const { return find_property(::atom(psz)); }

   inline ::property & operator[] (const ::string & str) { return get_property(::atom(str)); }
   inline ::payload operator[] (const ::string & str) const { return find_property(::atom(str)); }

   inline ::property & operator[] (::index i) { return get_property(::atom(i)); }
   inline ::payload operator[] (::index i) const { return find_property(::atom(i)); }

#if OSBIT == 64

   inline ::property & operator[] (::i32 i) { return get_property(::atom(i)); }
   inline ::payload operator[] (::i32 i) const { return find_property(::atom(i)); }

#endif

   ::index property_index(const ::atom & atom) const;
   ::property * find_property(const ::atom & atom) const;

   ::property & get_property(const ::atom & atom);

   ::payload at(index i);
   inline ::payload at(index i) const { return ((::payload *)this)->at(i); }

   inline ::count array_get_count() const;
   inline ::index array_get_upper_bound() const;
   bool array_contains(const char * psz,::index find = 0,::count count = -1) const;
   bool array_contains_ci(const char * psz,::index find = 0,::count count = -1) const;
   bool array_is_empty() const { return array_get_count() <= 0; }

   ::payload equals_ci_get(const char * pszCompare,::payload varOnEqual,payload varOnDifferent) const;
   ::payload equals_ci_get(const char * pszCompare,::payload varOnEqual) const;

   template < primitive_integral INTEGRAL >
   ::payload operator - (INTEGRAL i) const;
   template < primitive_floating FLOATING >
   ::payload operator - (FLOATING f) const;


   template < primitive_integral INTEGRAL >
   ::payload operator + (INTEGRAL i) const;
   template < primitive_floating FLOATING >
   ::payload operator + (FLOATING f) const;

   ::payload operator + (const ::string & str) const;
   ::payload operator + (const char * psz) const;

   template < primitive_integral INTEGRAL >
   ::payload operator / (INTEGRAL i) const;
   template < primitive_floating FLOATING >
   ::payload operator / (FLOATING f) const;

   template < primitive_integral INTEGRAL >
   ::payload operator * (INTEGRAL i) const;
   template < primitive_floating FLOATING >
   ::payload operator * (FLOATING d) const;

   ::i32 str_compare(const ::property & prop) const;



   template < primitive_integral INTEGRAL >
   ::payload & operator -= (INTEGRAL i);
   template < primitive_floating FLOATING >
   ::payload & operator -= (FLOATING f);


   template < primitive_integral INTEGRAL >
   ::payload & operator += (INTEGRAL i);
   template < primitive_floating FLOATING >
   ::payload & operator += (FLOATING f);

   ::payload & operator += (const ::string & str);
   inline ::payload & operator += (const char * psz) { return *this += ::string(psz); }

   template < primitive_integral INTEGRAL >
   ::payload & operator /= (INTEGRAL i);
   template < primitive_floating FLOATING >
   ::payload & operator /= (FLOATING f);

   template < primitive_integral INTEGRAL >
   ::payload & operator *= (INTEGRAL i);
   template < primitive_floating FLOATING >
   ::payload & operator *= (FLOATING d);


   void consume_number(const char * & psz);
   void consume_number(const char * & psz,const char * pszEnd);
   void consume_identifier(const char * & psz);
   void consume_identifier(const char * & psz,const char * pszEnd);
   void parse_network_payload(const char * & pszJson);
   void parse_network_payload(const char * & pszJson, const char * pszEnd);
   const char * parse_network_payload(const ::string & strJson);
   ::enum_type find_network_payload_child(const char * & pszJson, const payload & payload);
   ::enum_type find_network_payload_child(const char * & pszJson, const char * pszEnd, const payload & payload);
   ::enum_type find_network_payload_id(const char * & pszJson, const char * pszEnd, const payload & payload);
   bool parse_network_payload_step(const char * & pszJson);
   bool parse_network_payload_step(const char * & pszJson, const char * pszEnd);

   ::string & get_network_payload(::string & str, bool bNewLine = true) const;
   ::string get_network_payload(bool bNewLine = true) const;



   //
   // DECLARE_AXIS_FIXED_ALLOC(payload)

   void null();



   void _001Add(const ::string_array & stra);


   void run();

   void operator()() { return run(); }

   void receive_response(const payload & payload);


};







//
//namespace str
//{


   //inline CLASS_DECL_ACME void from(::string & str, const payload & payload)
   //{

   //   str = payload;

   //}

//
//} // namespace str


CLASS_DECL_ACME void var_skip_number(const char *& psz);
CLASS_DECL_ACME void var_skip_number(const char *& psz, const char * pszEnd);
CLASS_DECL_ACME void var_skip_identifier(const char *& psz);
CLASS_DECL_ACME void var_skip_identifier(const char *& psz, const char * pszEnd);
CLASS_DECL_ACME void var_skip_network_payload(const char *& pszJson);
CLASS_DECL_ACME void var_skip_network_payload(const char *& pszJson, const char * pszEnd);




//#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN) || defined(WINDOWS)
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


//inline payload::operator class duration() const
//{
//
//   return duration();
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


//inline payload::operator class ::duration() const
//{
//
//   return ::duration();
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


inline iptr payload::iptr(::iptr iDefault) const
{

#if defined(OS64BIT)

   return i64(iDefault);

#else

   return i32(iDefault);

#endif

}


inline uptr payload::uptr(::uptr uiDefault) const
{

#ifdef OS64BIT

   return u64(uiDefault);

#else

   return u32(uiDefault);

#endif

}


#ifdef WINDOWS

#elif defined(__APPLE__) || defined(RASBPIAN)

inline payload::operator long() const
{

   return i64();

}



// returns 0 for unknown conversions
inline payload::operator unsigned long() const
{
#if LONG_IS_32BIT
   return u32();
#else
   return u64();
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


//inline ::string & payload::string_reference(const char * pszOnNull)
//{
//
//   set_type(e_type_string, true);
//
//   return m_str;
//
//}




inline ::string payload::get_string() const
{

   return this->string();

}


inline class payload & payload::operator = (const char * psz)
{

   set_string(psz);

   return *this;

}


inline class payload & payload::operator = (const ::string & str)
{

   set_string(str);

   return *this;

}


inline class payload & payload::operator = (::string && str)
{

   set_string(::move(str));

   return *this;

}


inline void payload::set_string(const char * psz)
{

   if(get_type() == e_type_pstring)
   {

      *m_pstr = psz;

   }
   else if(get_type() == e_type_payload_pointer)
   {

      *m_ppayload = psz;

   }
   else if (get_type() == e_type_property)
   {

      ((payload &) *m_pproperty) = psz;

   }
   else
   {

      set_type(e_type_string,false);

      m_str = psz;

   }

}


inline void payload::set_string(const ::string & str)
{

   if(get_type() == e_type_pstring)
   {

      *m_pstr = str;

   }
   else if(get_type() == e_type_payload_pointer)
   {

      *m_ppayload = str;

   }
   else if (get_type() == e_type_property)
   {

      ((payload&)*m_pproperty) = str;

   }
   else
   {

      set_type(e_type_string,false);

      m_str = str;

   }

}



class CLASS_DECL_ACME payload_object :
   virtual public particle
{
public:

   payload m_payload;

};



class CLASS_DECL_ACME pack :
   public payload
{
public:


   using payload::payload;


   template < typename TYPE >
   pack(const ::pointer<TYPE>& p) { set_pointer(p); }
   pack(const ::std::initializer_list < pack >& list);

};


inline payload __visible(payload varOptions, bool bVisible = true);

inline payload __visible(bool bVisible = true) { return __visible(::e_type_new, bVisible); }





template < primitive_integral INTEGRAL >
inline ::payload payload::operator - (INTEGRAL i) const
{
   return ((INTEGRAL)*this) - i;
}


template < primitive_floating FLOATING >
inline ::payload payload::operator - (FLOATING f) const
{
   return ((FLOATING)*this) - f;
}


template < primitive_integral INTEGRAL >
inline ::payload payload::operator + (INTEGRAL i) const
{
   return ((INTEGRAL)*this) + i;
}


template < primitive_floating FLOATING >
inline ::payload payload::operator + (FLOATING f) const
{
   return ((FLOATING)*this) + f;
}


template < primitive_integral INTEGRAL >
inline ::payload payload::operator / (INTEGRAL i) const
{
   return ((INTEGRAL)*this) / i;
}


template < primitive_floating FLOATING >
inline ::payload payload::operator / (FLOATING f) const
{
   return ((FLOATING)*this) / f;
}


template < primitive_integral INTEGRAL >
inline ::payload payload::operator * (INTEGRAL i) const
{
   return ((INTEGRAL)*this) * i;
}


template < primitive_floating FLOATING >
inline ::payload payload::operator * (FLOATING f) const
{
   return ((FLOATING)*this) * f;
}


#include "payload_cast.h"


template < primitive_integral INTEGRAL, payload_class PAYLOAD >
inline ::payload operator - (INTEGRAL i, const PAYLOAD & payload)
{
   return i - ((INTEGRAL)payload_cast(payload));
}


template < primitive_floating FLOATING, payload_class PAYLOAD >
inline ::payload operator - (FLOATING i, const PAYLOAD & payload)
{
   return i - ((FLOATING)payload_cast(payload));
}


template < primitive_integral INTEGRAL, payload_class PAYLOAD >
inline ::payload operator + (INTEGRAL i, const PAYLOAD & payload)
{
   return i +((INTEGRAL)payload_cast(payload));
}


template < primitive_floating FLOATING, payload_class PAYLOAD >
inline ::payload operator + (FLOATING i, const PAYLOAD & payload)
{
   return i + ((FLOATING)payload_cast(payload));
}


template < primitive_integral INTEGRAL, payload_class PAYLOAD >
inline ::payload operator / (INTEGRAL i, const PAYLOAD & payload)
{
   return i / ((INTEGRAL)payload_cast(payload));
}


template < primitive_floating FLOATING, payload_class PAYLOAD >
inline ::payload operator / (FLOATING i, const PAYLOAD & payload)
{
   return i / ((FLOATING)payload_cast(payload));
}


template < primitive_integral INTEGRAL, payload_class PAYLOAD >
inline ::payload operator * (INTEGRAL i, const PAYLOAD & payload)
{
   return i * ((INTEGRAL)payload_cast(payload));
}


template < primitive_floating FLOATING, payload_class PAYLOAD >
inline ::payload operator * (FLOATING i, const PAYLOAD & payload)
{
   return i * ((FLOATING)payload_cast(payload));
}



template < primitive_integral INTEGRAL >
inline ::payload & payload::operator -= (INTEGRAL i) 
{
   return *this = ((INTEGRAL)payload_cast(*this)) - i;
}


template < primitive_floating FLOATING >
inline ::payload & payload::operator -= (FLOATING f)
{
   return *this = ((FLOATING)payload_cast(*this)) - f;
}


template < primitive_integral INTEGRAL >
inline ::payload & payload::operator += (INTEGRAL i)
{
   return *this = ((INTEGRAL)(payload_cast(*this))) + i;
}


template < primitive_floating FLOATING >
inline ::payload & payload::operator += (FLOATING f)
{
   return *this = ((FLOATING) payload_cast(*this)) + f;
}


template < primitive_integral INTEGRAL >
inline ::payload & payload::operator /= (INTEGRAL i)
{
   return *this = ((INTEGRAL)payload_cast(*this)) / i;
}


template < primitive_floating FLOATING >
inline ::payload & payload::operator /= (FLOATING f)
{
   return *this = ((FLOATING)payload_cast(*this)) / f;
}


template < primitive_integral INTEGRAL >
inline ::payload & payload::operator *= (INTEGRAL i)
{
   return *this = ((INTEGRAL)payload_cast(*this)) * i;
}


template < primitive_floating FLOATING >
inline ::payload & payload::operator *= (FLOATING f)
{
   return *this = ((FLOATING)payload_cast(*this)) * f;
}







template < payload_class PAYLOAD >
inline bool strictly_equal(const char * psz, const PAYLOAD & payload);
template < payload_class PAYLOAD >
inline bool strictly_equal(const ::string & str, const PAYLOAD & payload);
template < payload_class PAYLOAD >
inline bool strictly_equal(double d, const PAYLOAD & payload);
template < payload_class PAYLOAD >
inline bool strictly_equal(::i32 i, const PAYLOAD & payload);
template < payload_class PAYLOAD >
inline bool strictly_equal(bool b, const PAYLOAD & payload);


template < payload_class PAYLOAD >
inline bool strictly_different(const char * psz, const PAYLOAD & payload);
template < payload_class PAYLOAD >
inline bool strictly_different(const ::string & str, const PAYLOAD & payload);
template < payload_class PAYLOAD >
inline bool strictly_different(double d, const PAYLOAD & payload);
template < payload_class PAYLOAD >
inline bool strictly_different(::i32 i, const PAYLOAD & payload);
template < payload_class PAYLOAD >
inline bool strictly_different(bool b, const PAYLOAD & payload);


#include "payload_reference.h"


inline ::payload_reference __reference(payload & payload)
{

   return payload;

}



//#include "payload_reference.h"
//
//
//template < typename TYPE >
//TYPE & payload::reference(TYPE & t)
//{
//
//   return t = payload_reference(*this);
//
//}
//

CLASS_DECL_ACME::string __string(const ::payload & payload);


inline payload & copy(payload & payload, const integral_second & integralsecond)
{

   payload.set_type(e_type_integral_second);

   payload.m_integralsecond = integralsecond;

   return payload;

}



