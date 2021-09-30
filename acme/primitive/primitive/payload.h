#pragma once



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


class CLASS_DECL_ACME payload :
   public payload_type < payload >
{
public:


   enum_type                        m_etype;


   union
   {

      void * m_pvoid;
      para_return                m_parareturn;
      id                         m_id;
      bool                       m_b;
      bool * m_pb;
      ::i8                       m_i8;
      ::u8                       m_u8;
      ::i16                      m_i16;
      ::u16                      m_u16;
      ::i32                      m_i32;
      ::u32                      m_u32;
      ::i64                      m_i64;
      ::u64                      m_u64;
      ::i8 * m_pi8;
      ::u8 * m_pu8;
      ::i16 * m_pi16;
      ::u16 * m_pu16;
      ::i32 * m_pi32;
      ::u32 * m_pu32;
      ::i64 * m_pi64;
      ::u64 * m_pu64;
      ::string * m_pstr;
      ::f32                      m_f32;
      ::f32 * m_pf32;
      ::f64                     m_f64;
      ::f64 * m_pf64;
      payload * m_ppayload;
      ::datetime::time           m_time;
      filetime_t                 m_filetime;
      id * m_pid;
      ::property * m_pproperty;
      class secs                 m_secs;
      class secs * m_psecs;
      class millis               m_millis;
      class millis * m_pmillis;
      class micros               m_micros;
      class micros * m_pmicros;
      class nanos                m_nanos;
      class nanos * m_pnanos;
      class duration             m_duration;
      class duration * m_pduration;
      ::enum_status              m_estatus;
      ::enum_command             m_ecommand;
      ::enum_check               m_echeck;
      ::color::color             m_color;
      ::color::hls               m_hls;


      ::matter * m_p;
      ::string_array * m_pstra;
      ::int_array * m_pia;
      ::payload_array * m_ppayloada;
      ::property_set * m_ppropertyset;
      ::i64_array * m_pi64a;
      ::memory * m_pmemory;
      ::file::path_object * m_ppath;
      ::matter * m_pmatterRoutine;
      ::i64                      m_all[2];
      ::string                     m_str;

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
   payload(::matter * pobject);
   payload(::duration * pduration);
   payload(const char * psz);
   payload(const ::string & str);
   payload(const ::type & type);
   payload(const ::id & id);
   payload(const ::datetime::time & time);
   payload(const ::color::color & color);
   payload(const ::color::hls & hls);
   payload(const ::matter & matter);
   payload(const ::file::path & path);
   payload(const ::string_array & payload);
   payload(const ::int_array & payload);
   payload(const ::payload_array & payload);
   payload(const ::property_set & set);
   payload(const ::payload & payload);
   payload(const ::routine & routine);
   payload(const ::property & prop);
   payload(const ::duration & duration);

   payload(const ::block & block)
   {
      m_etype = e_type_new;
      operator = (block);
   }

   template < class T >
   payload(const __pointer(T) & p)
   {
      m_etype = e_type_new;
      operator = (p.m_p);
   }

   template < class T >
   payload(const ::extended::transport<T> & resultpointer)
   {
      m_etype = e_type_new;

      operator = (resultpointer);

   }

   template < typename BLOCK_TYPE >
   payload(const ::memory_template < BLOCK_TYPE > & memorytemplate)
   {
      m_etype = e_type_new;
      operator = (memorytemplate.block());
   }

   template < typename ENUM >
   payload(const ::enumeration < ENUM > & eflag)
   {
      m_etype = e_type_new;
      operator = (eflag);
   }

   template < a_enum ENUM >
   payload(const ENUM & eenum)
   {
      m_etype = e_type_new;
      operator = (eenum);
   }

   template < typename T >
   payload(const T & t)
   {
      m_etype = e_type_new;
      operator = (t);
   }


   payload(const ::e_status & estatus)
   {
      m_etype = e_type_new;
      operator = (estatus.m_estatus);
   }

   ~payload();


   void clear_data() { m_all[0] = 0; m_all[1] = 0; }


   void set_type(enum_type enum_type, bool bConvert = true);
   enum_type get_type() const;


   void set_type(const ::type & type);


   template < typename T >
   void set_pointer(const __pointer(T) & p)
   {

      operator[](__type_str(T)) = p;

   }

   template < typename T >
   bool has_pointer() const
   {

      return has_property(__type_str(T));

   }

   template < typename T >
   ::property * find_pointer() const
   {

      return find_property(__type_str(T));

   }

   template < typename T >
   __pointer(T) pointer() const;

   bool get_type(::type & type) const;

   ::i64 release();

   void _set_matter(::matter * pmatter);
   void _set_element(::matter * pmatter);

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
   inline payload(::enum_ ## ENUMTYPE e ## ENUMTYPE) { m_etype = ::e_type_enum_ ## ENUMTYPE; m_e ## ENUMTYPE = e ## ENUMTYPE; } \
   inline ::enum_ ## ENUMTYPE e ## ENUMTYPE(::enum_ ## ENUMTYPE e ## ENUMTYPE ## Default = enum_default < ::enum_ ## ENUMTYPE >()) const { return e < ::enum_ ## ENUMTYPE >(e ## ENUMTYPE ## Default); } \
   ::enum_ ## ENUMTYPE & as_e ## ENUMTYPE ();         \
   inline payload & operator = (::enum_ ## ENUMTYPE e ## ENUMTYPE) { release(); if(m_etype != ::e_type_enum_ ## ENUMTYPE) m_etype = ::e_type_enum_ ## ENUMTYPE; m_e ## ENUMTYPE = e ## ENUMTYPE; return *this; } \
   inline bool operator == (::enum_ ## ENUMTYPE e ## ENUMTYPE) const { return m_etype == ::e_type_enum_ ## ENUMTYPE && m_e ## ENUMTYPE == e ## ENUMTYPE; } \
   inline bool operator != (::enum_ ## ENUMTYPE e ## ENUMTYPE) const { return !operator ==(e ## ENUMTYPE); }
   DECL_VAR_ENUM(status);
   DECL_VAR_ENUM(command);
   DECL_VAR_ENUM(check);
#undef DECL_VAR_ENUM


   inline ::secs & as_secs() { if (get_type() != e_type_secs)set_type(e_type_secs); return m_secs; }
   inline ::millis & as_millis() { if (get_type() != e_type_millis)set_type(e_type_millis); return m_millis; }
   inline ::micros & as_micros() { if (get_type() != e_type_micros)set_type(e_type_micros); return m_micros; }
   inline ::nanos & as_nanos() { if (get_type() != e_type_nanos)set_type(e_type_nanos); return m_nanos; }


   ::string & as_string(::string & str);
   ::id & as_id(const ::id & idDefault = nullptr);

   ::memory & as_memory();

   ::string_array & as_stra();
   ::int_array & as_ia();
   ::i64_array & as_i64a();
   ::payload_array & as_payloada();
   ::duration & as_duration();
   ::property_set & as_propset();
   ::property & as_property();


   inline ::secs secs()  const { return duration().secs(); }
   inline ::millis millis()  const { return duration().millis(); }
   inline ::micros micros()  const { return duration().micros(); }
   inline ::nanos nanos()  const { return duration().nanos(); }


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
   ::color::color color(const ::color::color & colorDefault = ::color::color())  const;
   ::color::hls hls(const ::color::hls & hlsDefault = ::color::hls())  const;


   ::routine               get_routine() const;


   ::string string(const char * pszOnNull = nullptr) const;
   ::string to_string() const;
   ::string to_recursive_string() const;
   ::id id(const ::id & idDefault = nullptr)   const;

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
   bool is_real() const;
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
   void           set_id(const ::id & id);
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
   bool is_true(const payload & payload = false, bool bDefault = false) const;


   bool casts_to(::enum_type etype) const;


   ///property * defer_get_property(const ::id & id) const;
   bool has_property(const ::id & id) const;
   bool is_property_true(const ::id & id) const;
   bool is_property_false(const ::id & id) const;


   bool begins(const ::string & strPrefix) const { return to_string().begins(strPrefix); }
   bool ends(const ::string & strSuffix) const { return to_string().ends(strSuffix); }
   bool begins_ci(const ::string & strPrefix) const { return to_string().begins_ci(strPrefix); }
   bool ends_ci(const ::string & strSuffix) const { return to_string().ends_ci(strSuffix); }

   payload get_topic(const ::id & id) const;
   //payload defer_get(const ::id & id) const;

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


   operator bool() const;

   operator ::i8() const;
   operator ::u8() const;
   operator ::i16() const;
   operator ::u16() const;
   operator ::i32() const;
   operator ::u32() const;
   operator ::i64() const;
   operator ::u64() const;
   
#if defined(__APPLE__) || defined(RASBPIAN) || defined(ANDROID)
   operator long() const;
   operator unsigned long() const;
#endif


   
   operator ::f32() const;
   operator ::f64() const;
   operator ::string() const;
   operator ::memory() const;
   operator ::file::path() const;


   ::filetime filetime() const;
   ::datetime::time datetime_time() const;
   ::color::color color() const;
   ::color::hls color_hls() const;
   ::block block() const;


   ::string & as_string(const char * pszOnNull = nullptr);


   ::file::path & as_file_path();


   ::filetime & as_filetime();
   ::datetime::time & as_datetime_time();
   ::color::color & as_color();
   ::color::hls & as_color_hls();

   template < typename TYPE >
   inline TYPE & as(TYPE & t);



   bool & as_bool();
#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN) || defined(WINDOWS)
   long & as_long();
   unsigned long & as_unsigned_long();
#endif
   ::i8 &  as_i8();
   ::u8 &  as_u8();
   ::i16 & as_i16();
   ::u16 & as_u16();
   ::i32 & as_i32();
   ::u32 & as_u32();
   ::i64 & as_i64();
   ::u64 & as_u64();
   ::f32 & as_f32();
   ::f64 & as_f64();


   strsize get_length() const;

   template < typename TYPE >
   inline payload & operator = (const __composite(TYPE) & composite)
   {

      _set_element(composite.get());

      return *this;

   }

   payload& operator = (const ::routine & routine);

   inline payload & operator = (nullptr_t) { set_type(e_type_null, false); return *this; }

   inline payload & operator = (::matter * pmatter)
   {

      _set_element(pmatter);

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




   payload & operator = (const ::matter & o);

   inline payload & operator = (const ::file::path & path)
   {
      set_type(e_type_path, false);
      m_ppath = new ::file::path_object(path);
      return *this;
   }

   template < typename ENUM >
   payload& operator = (const enumeration < ENUM > & eflag)
   {
      return operator =(eflag.m_eenum);
   }

   template < a_enum ENUM >
   payload & operator = (const ENUM & eenum)
   {
      return operator =((::i64) eenum);
   }

   payload & operator |= (enumeration < ::file::enum_flag > eflag);

   payload& operator = (const ::e_status & estatus)
   {
      return operator =(estatus.m_estatus);
   }

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
   payload & operator = (const ::datetime::time & time);
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
   payload & operator = (const ::id & id);
   payload & operator = (::id * pid);
   payload & operator = (const ::secs & secs);
   payload & operator = (class ::secs * pduration);
   payload & operator = (const ::millis & millis);
   payload & operator = (class ::millis * pmillis);
   payload & operator = (const ::micros & micros);
   payload & operator = (class ::micros * pmicros);
   payload & operator = (const ::nanos & nanos);
   payload & operator = (class ::nanos * pnanos);
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

   template < class T >
   payload & operator = (const __pointer(T) & p)
   {

      return this->operator = (p.m_p);

   }

   template < class T >
   payload & operator = (const ::extended::transport < T > & resultpointer)
   {

      if (!resultpointer)
      {
         
         return operator=(resultpointer.m_estatus);

      }
      else
      {
         
         return operator = (resultpointer.m_p);

      }

   }

   template < an_object T >
   payload & operator = (const T & t)
   {

      __copy(this, &t);

      return *this;

   }

   template < class T >
   payload & operator = (const memory_template < T > & memory)
   {

      return this->operator = (memory.block());

   }


   template < class T >
   __pointer(T) cast(T * pDefault);

   template < class T >
   T & defer_create_type(T * pdefault = nullptr)
   {

      __pointer(T) p = pdefault;

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
   __pointer(T) cast(T * pDefault) const
   {
      return ((payload *) this)->cast < T >(pDefault);
   }


   template < class T >
   __pointer(T) cast();

   ::matter * matter()
   {
      if (m_etype == e_type_element) { return m_p; }
      return cast < ::matter >();
   }

   ::matter * matter() const { return ((payload *)this)->matter(); }

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


   inline ::property & operator[] (const ::id & id) { return get_property(id); }
   inline ::payload operator[] (const ::id & id) const { return find_property(id); }

   inline ::property & operator[] (const char * psz) { return get_property(::id(psz)); }
   inline ::payload operator[] (const char * psz) const { return find_property(::id(psz)); }

   inline ::property & operator[] (const ::string & str) { return get_property(::id(str)); }
   inline ::payload operator[] (const ::string & str) const { return find_property(::id(str)); }

   inline ::property & operator[] (::index i) { return get_property(::id(i)); }
   inline ::payload operator[] (::index i) const { return find_property(::id(i)); }

#if OSBIT == 64

   inline ::property & operator[] (::i32 i) { return get_property(::id(i)); }
   inline ::payload operator[] (::i32 i) const { return find_property(::id(i)); }

#endif

   inline ::index property_index(const ::id & id) const;
   inline ::property * find_property(const ::id & id) const;

   inline ::property & get_property(const ::id & id);

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
   void parse_json(const char * & pszJson);
   void parse_json(const char * & pszJson, const char * pszEnd);
   const char * parse_json(const ::string & strJson);
   ::enum_type find_json_child(const char * & pszJson, const payload & payload);
   ::enum_type find_json_child(const char * & pszJson, const char * pszEnd, const payload & payload);
   ::enum_type find_json_id(const char * & pszJson, const char * pszEnd, const payload & payload);
   bool parse_json_step(const char * & pszJson);
   bool parse_json_step(const char * & pszJson, const char * pszEnd);

   ::string & get_json(::string & str, bool bNewLine = true) const;
   ::string get_json(bool bNewLine = true) const;



   //#undef new
   // DECLARE_AXIS_FIXED_ALLOC(payload)

   void null();

   ::file::path get_file_path() const;

   void _001Add(const ::string_array & stra);


   ::extended::status run();

   ::extended::status operator()() { return run(); }

   void receive_response(const payload & payload);


};



class CLASS_DECL_ACME payload_reference
{
public:

   payload & m_payload;

   payload_reference(payload & payload) :
      m_payload(payload)
   {

   }

   operator enum_check & () { return m_payload.as_echeck(); }

   operator bool & () { return m_payload.as_bool(); }
   operator i8 & () { return m_payload.as_i8(); }
   operator u8 & () { return m_payload.as_u8(); }
   operator i16 & () { return m_payload.as_i16(); }
   operator u16 & () { return m_payload.as_u16(); }
   operator i32 & () { return m_payload.as_i32(); }
   operator u32 & () { return m_payload.as_u32(); }
   operator i64 & () { return m_payload.as_i64(); }
   operator u64 & () { return m_payload.as_u64(); }
   
   
#ifdef __APPLE__
   
   operator long & () { return m_payload.as_long(); }
   operator unsigned long & () { return m_payload.as_unsigned_long(); }
   
#endif
   

   operator f32 & () { return m_payload.as_f32(); }
   operator f64 & () { return m_payload.as_f64(); }


   operator secs & () { return m_payload.as_secs(); }
   operator millis & () { return m_payload.as_millis(); }
   operator micros & () { return m_payload.as_micros(); }
   operator nanos & () { return m_payload.as_nanos(); }

   operator duration & () { return m_payload.as_duration(); }
   operator datetime::time & () { return m_payload.as_datetime_time(); }


   operator string & () { return m_payload.as_string(); }
   operator property & () { return m_payload.as_property(); }


   operator int_array & () { return m_payload.as_ia(); }
   operator i64_array & () { return m_payload.as_i64a(); }
   operator string_array & () { return m_payload.as_stra(); }
   operator payload_array & () { return m_payload.as_payloada(); }
   operator property_set & () { return m_payload.as_propset(); }
   operator ::file::path & () { return m_payload.as_file_path(); }


};





class CLASS_DECL_ACME payload_cast
{
public:

   const payload & m_payload;

   payload_cast(const ::payload & payload) :
      m_payload(payload)
   {

   }


   operator enum_check () const { return m_payload.echeck(); }

   operator bool () const { return m_payload.get_bool(); }
   operator i8 ()const { return m_payload.i8(); }
   operator u8 ()const { return m_payload.u8(); }
   operator i16 () const { return m_payload.i16(); }
   operator u16 ()const { return m_payload.u16(); }
   operator i32 () const { return m_payload.i32(); }
   operator u32 ()const { return m_payload.u32(); }
   operator i64 () const { return m_payload.i64(); }
   operator u64 ()const { return m_payload.u64(); }

   operator f32 () const { return m_payload.f32(); }
   operator f64 ()const { return m_payload.f64(); }

   operator secs ()const { return m_payload.secs(); }
   operator millis ()const { return m_payload.millis(); }
   operator micros () const { return m_payload.micros(); }
   operator nanos ()const { return m_payload.nanos(); }

   operator duration ()const { return m_payload.duration(); }
   operator datetime::time ()const { return m_payload.datetime_time(); }


   operator string ()const { return m_payload.string(); }
   //operator property ()const { return m_payload.property(); }


   operator int_array ()const { return m_payload.ia(); }
   operator i64_array ()const { return m_payload.i64a(); }
   operator string_array ()const { return m_payload.stra(); }
   inline operator payload_array () const;
   inline operator property_set () const;
   inline operator ::file::path () const;


};




namespace str
{


   inline CLASS_DECL_ACME void from(::string & str, const payload & payload)
   {

      str = payload;

   }


} // namespace str


CLASS_DECL_ACME void var_skip_number(const char *& psz);
CLASS_DECL_ACME void var_skip_number(const char *& psz, const char * pszEnd);
CLASS_DECL_ACME void var_skip_identifier(const char *& psz);
CLASS_DECL_ACME void var_skip_identifier(const char *& psz, const char * pszEnd);
CLASS_DECL_ACME void var_skip_json(const char *& pszJson);
CLASS_DECL_ACME void var_skip_json(const char *& pszJson, const char * pszEnd);




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
//inline payload::operator ::e_status() const
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
//inline payload::operator class secs() const
//{
//
//   return secs();
//
//}


//inline payload::operator class millis() const
//{
//
//   return millis();
//
//}
//
//
//inline payload::operator class micros() const
//{
//
//   return micros();
//
//}
//
//
//inline payload::operator class nanos() const
//{
//
//   return nanos();
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


#elif defined(ANDROID)

inline payload::operator long() const
{

   return i32();

}

#endif


inline ::string & payload::as_string(::string & str)
{

   return str = this->string();

}

inline ::string payload::to_string() const
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
   virtual public matter
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
   pack(const __pointer(TYPE)& p) { set_pointer(p); }
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

//#define __reference(payload) ::payload_reference(payload)






template < typename TYPE >
TYPE & payload::as(TYPE & t)
{

   return t = payload_reference(*this);

}

