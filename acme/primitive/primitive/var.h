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



class CLASS_DECL_ACME var :
   public var_type < var >
{
public:


   enum_type                        m_etype;


   union
   {

      void *                     m_pvoid;
      para_return                m_parareturn;
      id                         m_id;
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
      string *                   m_pstr;
      float                      m_f;
      float *                    m_pf;
      double                     m_d;
      double *                   m_pd;
      var *                      m_pvar;
      __time64_t                 m_time;
      FILETIME                   m_filetime;
      id *                       m_pid;
      property *                 m_pprop;
      class duration             m_duration;
      class duration *           m_pduration;
      ::estatus                  m_estatus;
      ::enum_command             m_ecommand;
      ::enum_check               m_echeck;

      ::matter *                 m_p;
      ::string_array *           m_pstra;
      ::int_array *              m_pia;
      ::var_array *              m_pvara;
      ::property_set *           m_pset;
      ::i64_array *              m_pi64a;
      ::memory *                 m_pmemory;
      ::file::path_object *      m_ppath;
      ::method                   m_method;
      ::futurevar           m_future;
      ::i64                      m_all[2];


   };


   string                        m_str;


   inline var();
   inline var(enum_type etype);
   inline var(std::nullptr_t);
   var(bool b);
   var(::i32 i);
   var(::u32 ui);
   var(::i64 i);
   var(::u64 ui);
#ifdef APPLEOS
#ifdef OS64BIT
   var(long l);
#endif
#endif
   var(::i32 * pi);
   var(::u32 * pi);
   var(::i64 * pi);
   var(::u64 * pinteraction);
   var(float f);
   var(double d);
   var(const char * psz);
   var(const string & str);
   var(const type & type);
   var(const id & id);
   var(bool * pb);
   var(const ::datetime::time & time);
   var(const FILETIME & time);
   var(const SYSTEMTIME & time);
   var(string * pstr);
   var(var * pvar);
   var(const var * pvar);
   var(property * pproperty);
   var(::matter * pobject);
   var(const ::matter & matter);
   //var(::image * pimage);
   var(const ::file::path & path);
   var(const string_array & var);
   var(const int_array & var);
   var(const var_array & var);
   var(const property_set & set);
   var(const var & var);
   var(const property & prop);
   var(const method& method);
   var(const futurevar& future);
   var(const property * pproperty);
   var(const class duration & duration);
   var(class duration * pduration);

   var(const block & block)
   {
      m_etype = type_new;
      operator = (block);
   }

   template < class T >
   var(const __pointer(T) & sp)
   {
      m_etype = type_new;
      operator = (sp.m_p);
   }

   template < typename BLOCK_TYPE >
   var(const memory_template < BLOCK_TYPE > & memorytemplate)
   {
      m_etype = type_new;
      operator = (memorytemplate.block());
   }

   template < typename ENUM >
   var(const cflag < ENUM > & eflag)
   {
      m_etype = type_new;
      operator = (eflag);
   }

   var(const ::estatus & estatus)
   {
      m_etype = type_new;
      operator = (estatus.m_estatus);
   }

   ~var();


   void clear_data() { m_all[0] = 0; m_all[1] = 0; }

   void set_type(enum_type enum_type,bool bConvert = true);
   enum_type get_type() const;


   void set_type(const ::type & type);


   template < typename T >
   void set_pointer(const __pointer(T)& p)
   {

      operator[](__type_str(T)) = p;

   }

   template < typename T >
   bool has_pointer() const
   {

      return has_property(__type_str(T));

   }

   template < typename T >
   property * find_pointer() const
   {

      return find_property(__type_str(T));

   }

   template < typename T >
   __pointer(T) pointer() const;

   bool get_type(::type & type) const;

   ::i64 release();

   ::enum_type set_element(::matter * pobject);

   bool is_element() const { return m_etype >= type_element && m_etype < __type_last_element; }

   bool is_element_set() const { return is_element() && ::is_set(m_p); }

   bool is_element_null() const { return is_element() && ::is_null(m_p); }

   bool is_numeric() const;

   inline bool is_number() const
   {

      return is_numeric();

   }

   bool convert(const var& var);


   bool                             get_bool(bool bDefault = false)     const;
   ::i32                          i32(::i32 iDefault = 0)  const;

   template < typename ENUM >
   ENUM                             e(ENUM edefault = enum_default < ENUM >())  const { return (ENUM)i64(edefault); }

#define DECL_VAR_FLAG(ENUMTYPE) \
inline var(::enum_ ## ENUMTYPE e ## ENUMTYPE) { m_etype = ::type_enum_ ## ENUMTYPE; m_e ## ENUMTYPE = e ## ENUMTYPE; } \
inline ::enum_ ## ENUMTYPE e ## ENUMTYPE(::enum_ ## ENUMTYPE e ## ENUMTYPE ## Default = enum_default < ::enum_ ## ENUMTYPE >()) const { return e < ::enum_ ## ENUMTYPE >(e ## ENUMTYPE ## Default); } \
::enum_ ## ENUMTYPE & e ## ENUMTYPE ();         \
inline ::var & operator = (::enum_ ## ENUMTYPE e ## ENUMTYPE) { release(); if(m_etype != ::type_enum_ ## ENUMTYPE) m_etype = ::type_enum_ ## ENUMTYPE; m_e ## ENUMTYPE = e ## ENUMTYPE; return *this; } \
inline bool operator == (::enum_ ## ENUMTYPE e ## ENUMTYPE) const { return m_etype == ::type_enum_ ## ENUMTYPE && m_e ## ENUMTYPE == e ## ENUMTYPE; } \
inline bool operator != (::enum_ ## ENUMTYPE e ## ENUMTYPE) const { return !operator ==(e ## ENUMTYPE); } \
inline operator ::enum_ ## ENUMTYPE() const { return e ## ENUMTYPE(); } \
inline operator ::enum_ ## ENUMTYPE & () { return e ## ENUMTYPE(); } \
inline operator ::e ## ENUMTYPE() const { return e ## ENUMTYPE(); }
   //DECL_VAR_FLAG(status);
   //DECL_VAR_FLAG(command);
   //DECL_VAR_FLAG(check);
#undef DECL_VAR_FLAG
   #define DECL_VAR_ENUM(ENUMTYPE) \
   inline var(::enum_ ## ENUMTYPE e ## ENUMTYPE) { m_etype = ::type_enum_ ## ENUMTYPE; m_e ## ENUMTYPE = e ## ENUMTYPE; } \
   inline ::enum_ ## ENUMTYPE e ## ENUMTYPE(::enum_ ## ENUMTYPE e ## ENUMTYPE ## Default = enum_default < ::enum_ ## ENUMTYPE >()) const { return e < ::enum_ ## ENUMTYPE >(e ## ENUMTYPE ## Default); } \
   ::enum_ ## ENUMTYPE & e ## ENUMTYPE ();         \
   inline ::var & operator = (::enum_ ## ENUMTYPE e ## ENUMTYPE) { release(); if(m_etype != ::type_enum_ ## ENUMTYPE) m_etype = ::type_enum_ ## ENUMTYPE; m_e ## ENUMTYPE = e ## ENUMTYPE; return *this; } \
   inline bool operator == (::enum_ ## ENUMTYPE e ## ENUMTYPE) const { return m_etype == ::type_enum_ ## ENUMTYPE && m_e ## ENUMTYPE == e ## ENUMTYPE; } \
   inline bool operator != (::enum_ ## ENUMTYPE e ## ENUMTYPE) const { return !operator ==(e ## ENUMTYPE); } \
   inline operator ::enum_ ## ENUMTYPE() const { return e ## ENUMTYPE(); } \
   inline operator ::enum_ ## ENUMTYPE & () { return e ## ENUMTYPE(); }
      DECL_VAR_ENUM(status);
      DECL_VAR_ENUM(command);
      DECL_VAR_ENUM(check);
   #undef DECL_VAR_ENUM

   ::u32                            u32(::u32 uiDefault = 0)  const;
   ::i64                            i64(::i64 iDefault = 0)  const;
   inline ::tick                    tick(::tick tickDefault = 0)  const { return i64(); }
   inline ::tick &                  tick() { if (get_type() != type_i64)set_type(type_i64); return (::tick &) m_i64; }
   ::u64                            u64(::u64 uiDefault = 0)  const;
   inline ::iptr                    iptr(iptr iDefault = 0)  const;
   inline ::uptr                    uptr(uptr uiDefault = 0)  const;
   float                            get_float(float fDefault = 0.f)   const;
   double                           get_double(double dDefault = 0.0)   const;
   method                           get_method() const;
   futurevar                        get_future() const;
   //::image *                        image() const;
   //::image * &                      image();
   string                           to_r_string() const;
   string                           get_string(const char * pszOnNull = nullptr) const;
   string &                         get_ref_string(const char * pszOnNull = nullptr);
   const string &                   get_ref_string(const char * pszOnNull = nullptr) const;
   string &                         to_string(string & str) const;
   string                           to_string() const;
   string                           to_string_base() const { return to_string(); }
   id                               get_id(const char * pszOnNull = nullptr)   const;
   id &                             get_ref_id(const char * pszOnNull = nullptr);
   class memory &                   memory();
   string_array &                        stra();
   int_array &                      inta();
   i64_array &                      int64a();
   var_array &                      vara();
   class duration &                 duration();
   property_set &                   propset();
   property &                       prop();
   ::memory                         memory() const;
   const string_array &                  stra() const;
   const int_array &                inta() const;
   const i64_array &                int64a() const;
   const var_array &                vara()  const;
   const property_set &             propset() const;
   const property &                 prop() const;
   const class duration &           duration() const;

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


   var dereference();





   ::comparison::var_strict strict_compare() const;

   void           set_string(const char * psz);
   void           set_string(const string & str);
   void           set_string(string && str);
   void           set_id(const id & id);
   void unset();
   void unset(const string & strPropertySetKey);

   bool is_set() const;
   bool is_new() const;
   bool is_null() const;
   bool is_new_or_null() const;
   bool is_empty() const;
   bool has_char() const;

   bool is_false() const;
   bool is_bool_false() const;
   bool is_set_false() const;
   bool is_true(const ::var & var = false, bool bDefault = false) const;


   bool casts_to(::enum_type etype) const;


   ///property * defer_get_property(const ::id & id) const;
   bool has_property(const ::id & id) const;
   bool is_property_true(const ::id & id) const;
   bool is_property_false(const ::id & id) const;

   var get_topic(const ::id & id) const;
   //var defer_get(const ::id & id) const;

   var & operator ++(::i32);

   bool operator !() const
   {

      return is_false();

   }

   operator bool() const;

#ifdef WINDOWS
   operator LONG() const;
#elif defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN)
   operator long() const;
#endif
   operator ::i8() const;
   operator ::u8() const;
   operator ::i16() const;
   operator ::u16() const;
   operator ::i32() const;
   operator ::u32() const;
   operator ::i64() const;
   operator ::u64() const;
   operator float() const;
   operator double() const;
   operator ::estatus() const;
   operator class duration() const;
   operator ::datetime::file_time() const;
   operator ::datetime::time() const;
   operator block () const;
   operator block ();
   operator class tick() const;

   operator const char * () const;
   operator string & ();


   operator ::memory & ();
   operator ::memory() const;

   operator ::file::path & ();
   operator ::file::path () const;

   //operator ::image * & ();


   inline operator bool &();
   inline operator ::i8 & ();
   inline operator ::u8 & ();
   inline operator ::i16 & () ;
   inline operator ::u16 & () ;
   inline operator ::i32 & () ;
   inline operator ::u32 & () ;
   inline operator ::i64 & () ;
   inline operator ::u64 & () ;
   inline operator float & ();
   inline operator double & ();

   inline operator ::estatus & ();

   void get_string(char * psz) const;

   strsize get_length() const;

   template < typename TYPE >
   inline var & operator = (const __composite(TYPE) & composite)
   {

      set_element(composite.get());

      return *this;

   }

   var& operator = (const ::method& method);
   var& operator = (const ::futurevar& future);

   inline var & operator = (nullptr_t) { set_type(e_type_null, false); return *this; }

   inline var & operator = (::matter * p)
   {

      set_element(p);

      return *this;

   }


   inline var & operator = (::memory * pmemory)
   {

      set_type(type_memory, false);

      m_pmemory = pmemory;

      ::add_ref(m_pmemory);

      return *this;

   }

   var & operator = (const ::matter & o);

   inline var & operator = (const ::file::path & path)
   {
      set_type(type_path, false);
      m_ppath = new ::file::path_object(path);
      return *this;
   }

   template < typename ENUM >
   var& operator = (const cflag < ENUM > & eflag)
   {
      return operator =(eflag.m_eenum);
   }

   var & operator |= (cflag < ::file::e_flag > eflag);

   var& operator = (const ::estatus & estatus)
   {
      return operator =(estatus.m_estatus);
   }

   //inline var & operator = (::image * pimage);


   var & operator = (para_return & eret);
   var & operator = (bool b);
   var & operator = (bool * pb);
   var & operator = (::i32 i);
   var & operator = (::i32 * pi);
   var & operator = (::u32 ui);
   var & operator = (::u32 * pinteraction);
#ifdef WINDOWS
   var & operator = (LPDWORD lpdw);
   var & operator = (LONG l);
   var & operator = (DWORD dw);
#elif defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN)
   var & operator = (long l);
#endif
   var & operator = (::i64 i);
   var & operator = (::i64 * pi);
   var & operator = (::u64 i);
   var & operator = (::u64 * pi);
   var & operator = (float f);
   var & operator = (double d);
   var & operator = (const ::datetime::time & time);
   var & operator = (const FILETIME & time);
   var & operator = (const SYSTEMTIME & time);
   inline var & operator = (const char * psz);
   inline var & operator = (const string & str);
   inline var & operator = (string && str);
   var & operator = (string * pstr);
   var & operator = (var * pvar);
   var & operator = (const var * pvar);
   var & operator = (const widechar * pcsz);

   var & operator = (const property & prop);
   var & operator = (const property * pproperty);
   var & operator = (const var & var);
   var & operator = (const int_array & ia);
   var & operator = (const string_array & stra);
   var & operator = (const class memory & memory);
   var & operator = (const var_array & vara);
   var & operator = (const property_set & propset);
   //var & operator = (const pair_set_interface & propset);
   //var & operator = (const str_str_interface & propset);
//   var & operator = (const string_composite & reference);
   var & operator = (const id & id);
   var & operator = (id * pid);
   var & operator = (const class duration & pid);
   var & operator = (class duration * pduration);
   var & operator = (const block & block);

   template < class T >
   void get_array(T & dsta) const
   {

      for(int i = 0; i < array_get_count(); i++)
      {

         dsta.add((typename T::BASE_TYPE) at(i));

      }

   }

   template < class T >
   var & operator = (const __pointer(T) & sp)
   {

      return this->operator = (sp.m_p);

   }

   template < class T >
   var & operator = (const memory_template < T > & memory)
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
      return ((var *) this)->cast < T >(pDefault);
   }


   template < class T >
   __pointer(T) cast();

   ::matter * matter()
   {
      if (m_etype == type_element) { return m_p; }
      return cast < ::matter >();
   }

   ::matter * matter() const { return ((var *)this)->matter(); }

   template < class T >
   T * cast() const
   {
      return ((var *) this)->cast < T >();
   }


   bool strict_equal(const var & var) const;
   bool strict_equal(const char * psz) const;
   bool strict_equal(const string & str) const;
   bool strict_equal(double d) const;
   bool strict_equal(::i32 i) const;
   bool strict_equal(bool b) const;

   bool strict_different(const var & var) const;
   bool strict_different(const char * psz) const;
   bool strict_different(const string & str) const;
   bool strict_different(double d) const;
   bool strict_different(::i32 i) const;
   bool strict_different(bool b) const;

   friend bool CLASS_DECL_ACME strict_equal(const char * psz,const var & var);
   friend bool CLASS_DECL_ACME strict_equal(const string & str,const var & var);
   friend bool CLASS_DECL_ACME strict_equal(double d,const var & var);
   friend bool CLASS_DECL_ACME strict_equal(::i32 i,const var & var);
   friend bool CLASS_DECL_ACME strict_equal(bool b,const var & var);

   friend bool CLASS_DECL_ACME strict_different(const char * psz,const var & var);
   friend bool CLASS_DECL_ACME strict_different(const string & str,const var & var);
   friend bool CLASS_DECL_ACME strict_different(double d,const var & var);
   friend bool CLASS_DECL_ACME strict_different(::i32 i,const var & var);
   friend bool CLASS_DECL_ACME strict_different(bool b,const var & var);

   ::i32 compare(const var & var) const;
   ::i32 compare(const char * psz) const;

   ::i32 compare_ci(const var & var) const;
   ::i32 compare_ci(const char * psz) const;

   bool operator == (const var & var) const;
   bool operator == (const char * psz) const;
   bool operator == (const string & str) const;
   bool operator == (::i64 i) const;
   bool operator == (::i32 i) const;
   bool operator == (bool b) const;

   bool operator != (const var & var) const;
   bool operator != (const char * psz) const;
   bool operator != (const string & str) const;
   bool operator != (::i64 i) const;
   bool operator != (::i32 i) const;
   bool operator != (bool b) const;

   bool operator < (const var & var) const;
   bool operator < (const char * psz) const;
   bool operator < (const string & str) const;
   bool operator < (::i64 i) const;
   bool operator < (::i32 i) const;
   bool operator < (bool b) const;

   bool operator <= (const var & var) const;
   bool operator <= (const char * psz) const;
   bool operator <= (const string & str) const;
   bool operator <= (::i64 i) const;
   bool operator <= (::i32 i) const;
   bool operator <= (bool b) const;

   bool operator >= (const var & var) const;
   bool operator >= (const char * psz) const;
   bool operator >= (const string & str) const;
   bool operator >= (::i64 i) const;
   bool operator >= (::i32 i) const;
   bool operator >= (bool b) const;

   bool operator > (const var & var) const;
   bool operator > (const char * psz) const;
   bool operator > (const string & str) const;
   bool operator > (::i64 i) const;
   bool operator > (::i32 i) const;
   bool operator > (bool b) const;

   //var & io(::stream & stream);

   //inline var & io(::stream& stream) const
   //{
     // stream.set_storing();
      //return ((var &)*this).io(stream);

   //}

   //template < typename TYPE >
   //void exchange_from(const TYPE & t) { operator =(t); }

   //void exchange_from(const ::matter & matter) { propset().exchange(matter); }

   string implode(const char * pszGlue) const;
   var explode(const char * pszGlue,bool bAddEmpty = true) const;

   var first() const;
   var last() const;
   var first();
   var last();
   inline ::count get_count() const;


   inline property & operator[] (const id & id) { return get_property(id); }
   inline var operator[] (const id & id) const { return find_property(id); }

   inline property & operator[] (const char * psz) { return get_property(::id(psz)); }
   inline var operator[] (const char * psz) const { return find_property(::id(psz)); }

   inline property & operator[] (const string & str) { return get_property(::id(str)); }
   inline var operator[] (const string & str) const { return find_property(::id(str)); }

   inline property & operator[] (::index i) { return get_property(::id(i)); }
   inline var operator[] (::index i) const { return find_property(::id(i)); }

#if OSBIT == 64

   inline property & operator[] (::i32 i) { return get_property(::id(i)); }
   inline var operator[] (::i32 i) const { return find_property(::id(i)); }

#endif

   inline ::index property_index(const ::id & id) const;
   inline ::property * find_property(const ::id & id) const;

   inline property & get_property(const ::id & id);

   var at(index i);
   inline var at(index i) const { return ((var *)this)->at(i); }

   inline ::count array_get_count() const;
   inline index array_get_upper_bound() const;
   bool array_contains(const char * psz,index find = 0,::count count = -1) const;
   bool array_contains_ci(const char * psz,index find = 0,::count count = -1) const;
   bool array_is_empty() const { return array_get_count() <= 0; }

   var equals_ci_get(const char * pszCompare,var varOnEqual,var varOnDifferent) const;
   var equals_ci_get(const char * pszCompare,var varOnEqual) const;


   var operator - (::i32 i) const;
   var operator - (::u32 ui) const;
   var operator - (::i64 i) const;
   var operator - (::u64 ui) const;
   var operator - (double d) const;

   friend var CLASS_DECL_ACME operator - (::i32 i,const var & var);
   friend var CLASS_DECL_ACME operator - (::u32 ui,const var & var);
   friend var CLASS_DECL_ACME operator - (::i64 l,const var & var);
   friend var CLASS_DECL_ACME operator - (::u64 ul,const var & var);
   friend var CLASS_DECL_ACME operator - (double d,const var & var);
   friend var CLASS_DECL_ACME operator - (const var & var1,const var & var2);

   var operator + (::i32 i) const;
   var operator + (::u32 ui) const;
   var operator + (::i64 i) const;
   var operator + (::u64 ui) const;
   var operator + (double d) const;

   var operator + (const string & str) const;
   inline var operator + (const char * psz) const { return *this + string(psz); }

   friend var CLASS_DECL_ACME operator + (::i32 i,const var & var);
   friend var CLASS_DECL_ACME operator + (::u32 ui,const var & var);
   friend var CLASS_DECL_ACME operator + (::i64 l,const var & var);
   friend var CLASS_DECL_ACME operator + (::u64 ul,const var & var);
   friend var CLASS_DECL_ACME operator + (double d,const var & var);
   friend var CLASS_DECL_ACME operator + (const var & var1,const var & var2);

   var operator / (::i32 i) const;
   var operator / (::u32 ui) const;
   var operator / (::i64 i) const;
   var operator / (::u64 ui) const;
   var operator / (double d) const;

   friend var CLASS_DECL_ACME operator / (::i32 i,const var & var);
   friend var CLASS_DECL_ACME operator / (::u32 ui,const var & var);
   friend var CLASS_DECL_ACME operator / (::i64 l,const var & var);
   friend var CLASS_DECL_ACME operator / (::u64 ul,const var & var);
   friend var CLASS_DECL_ACME operator / (double d,const var & var);
   friend var CLASS_DECL_ACME operator / (const var & var1,const var & var2);

   var operator * (::i32 i) const;
   var operator * (::u32 ui) const;
   var operator * (::i64 i) const;
   var operator * (::u64 ui) const;
   var operator * (double d) const;

   ::i32 str_compare(const property & prop) const;

   friend var CLASS_DECL_ACME operator * (::i32 i,const var & var);
   friend var CLASS_DECL_ACME operator * (::u32 ui,const var & var);
   friend var CLASS_DECL_ACME operator * (::i64 l,const var & var);
   friend var CLASS_DECL_ACME operator * (::u64 ul,const var & var);
   friend var CLASS_DECL_ACME operator * (double d,const var & var);
   friend var CLASS_DECL_ACME operator * (const var & var1,const var & var2);

   var & operator -= (::i32 i);
   var & operator -= (::u32 ui);
   var & operator -= (::i64 i);
   var & operator -= (::u64 ui);
   var & operator -= (double d);
   var & operator -= (const var & var);
   //var & operator -= (const property & property);

   var & operator += (::i32 i);
   var & operator += (::u32 ui);
   var & operator += (::i64 i);
   var & operator += (::u64 ui);
   var & operator += (double d);
   var & operator += (const var & var);
   //var & operator += (const property & property);

   var & operator /= (::i32 i);
   var & operator /= (::u32 ui);
   var & operator /= (::i64 i);
   var & operator /= (::u64 ui);
   var & operator /= (double d);
   var & operator /= (const var & var);
   //var & operator /= (const property & property);

   var & operator *= (::i32 i);
   var & operator *= (::u32 ui);
   var & operator *= (::i64 i);
   var & operator *= (::u64 ui);
   var & operator *= (double d);
   var & operator *= (const var & var);
   //var & operator *= (const property & property);

   void consume_number(const char * & psz);
   void consume_number(const char * & psz,const char * pszEnd);
   void consume_identifier(const char * & psz);
   void consume_identifier(const char * & psz,const char * pszEnd);
   void parse_json(const char * & pszJson);
   void parse_json(const char * & pszJson, const char * pszEnd);
   const char * parse_json(const string & strJson);
   ::enum_type find_json_child(const char * & pszJson, const var & var);
   ::enum_type find_json_child(const char * & pszJson, const char * pszEnd, const var & var);
   ::enum_type find_json_id(const char * & pszJson, const char * pszEnd, const var & var);
   bool parse_json_step(const char * & pszJson);
   bool parse_json_step(const char * & pszJson, const char * pszEnd);

   string & get_json(string & str, bool bNewLine = true) const;
   string get_json(bool bNewLine = true) const;



   //#undef new
   // DECLARE_AXIS_FIXED_ALLOC(var)

   void null();

   ::file::path get_file_path() const;

   void _001Add(const string_array & stra);


   ::status::result run();


   void receive_response(const ::var & var);


};


namespace str
{


   inline CLASS_DECL_ACME void from(string & str, const var & var)
   {

      str = var.get_string();

   }


} // namespace str


CLASS_DECL_ACME void var_skip_number(const char *& psz);
CLASS_DECL_ACME void var_skip_number(const char *& psz, const char * pszEnd);
CLASS_DECL_ACME void var_skip_identifier(const char *& psz);
CLASS_DECL_ACME void var_skip_identifier(const char *& psz, const char * pszEnd);
CLASS_DECL_ACME void var_skip_json(const char *& pszJson);
CLASS_DECL_ACME void var_skip_json(const char *& pszJson, const char * pszEnd);


inline bool var::get_bool(bool bDefault) const
{
   return is_true(bDefault);
}


// returns 0 for unknown conversions
inline var::operator ::i8() const
{
   return i8();
}

// returns 0 for unknown conversions
inline var::operator ::u8() const
{
   return u8();
}


// returns 0 for unknown conversions
inline var::operator ::i16() const
{
   return i16();
}

// returns 0 for unknown conversions
inline var::operator ::u16() const
{
   return u16();
}



// returns 0 for unknown conversions
inline var::operator ::i32() const
{
   return i32();
}

// returns 0 for unknown conversions
inline var::operator ::u32() const
{
   return u32();
}

// returns 0 for unknown conversions
inline var::operator ::i64() const
{
   return i64();
}

// returns 0 for unknown conversions
inline var::operator ::u64() const
{
   return u64();
}


// returns 0.0 for unknown conversions?
inline var::operator float() const
{
   return get_float();
}


// returns 0.0 for unknown conversions?
inline var::operator double() const
{
   return get_double();
}

// returns 0.0 for unknown conversions?
inline var::operator ::estatus() const
{
   return estatus();
}

inline var::operator class duration() const
{

   return duration();

}


inline var::operator class tick() const
{

   return tick();

}

inline iptr var::iptr(::iptr iDefault) const
{

#if defined(OS64BIT)

   return i64(iDefault);

#else

   return i32(iDefault);

#endif

}


inline uptr var::uptr(::uptr uiDefault) const
{

#ifdef OS64BIT

   return u64(uiDefault);

#else

   return u32(uiDefault);

#endif

}


#ifdef WINDOWS

inline var::operator LONG () const
{

   return i32();

}

inline var & var::operator = (LPDWORD pinteraction)
{

   return operator = ((::u32 *)pinteraction);

}

#elif defined(__APPLE__) || defined(RASBPIAN)

inline var::operator long() const
{

   return i64();

}

#elif defined(ANDROID)

inline var::operator long() const
{

   return i32();

}

#endif


inline string & var::to_string(string & str) const
{

   return str = get_string();

}

inline string var::to_string() const
{

   return get_string();

}


inline class var & var::operator = (const char * psz)
{

   set_string(psz);

   return *this;

}


inline class var & var::operator = (const string & str)
{

   set_string(str);

   return *this;

}


inline class var & var::operator = (string && str)
{

   set_string(::move(str));

   return *this;

}


inline void var::set_string(const char * psz)
{
   if(get_type() == type_pstring)
   {
      *m_pstr = psz;
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = psz;
   }
   else if (get_type() == type_prop)
   {
      ((var &) *m_pprop) = psz;
   }
   else
   {
      set_type(type_string,false);
      m_str = psz;
   }
}


inline void var::set_string(const string & str)
{

   if(get_type() == type_pstring)
   {
      *m_pstr = str;
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = str;
   }
   else if (get_type() == type_prop)
   {
      ((var&)*m_pprop) = str;
   }
   else
   {
      set_type(type_string,false);
      m_str = str;
   }
}

inline void var::set_string(string && str)
{
   if(get_type() == type_pstring)
   {
      *m_pstr = ::move(str);
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = ::move(str);
   }
   else if (get_type() == type_prop)
   {
      ((var&)*m_pprop) = ::move(str);
   }
   else
   {
      set_type(type_string,false);
      m_str = ::move(str);
   }
}


class CLASS_DECL_ACME ovar :
   virtual public matter
{
public:

   var m_var;

};


//namespace papaya
//{
//
//
//   class CLASS_DECL_ACME topic :
//      public ::var
//   {
//   public:
//
//      using var::var;
//
//      operator string & ()
//      {
//
//         auto & str = ::var::operator string & ();
//
//         set_type(type_string, false);
//
//         return str;
//
//      }
//
//   };
//
//
//} // namespace papaya


inline string CLASS_DECL_ACME operator + (const char * psz, const var & var);

class CLASS_DECL_ACME pack :
   public var
{
public:
   using var::var;
   template < typename TYPE >
   pack(const __pointer(TYPE)& p) { set_pointer(p); }
   pack(const ::std::initializer_list < pack >& list);

};


inline var __visible(var varOptions, bool bVisible = true);

inline var __visible(bool bVisible = true) { return __visible(::type_new, bVisible); }



