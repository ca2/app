#pragma once

#undef new

class property;
class action_context;


#include "acme/memory/property_memory_allocate.h"


namespace xml
{

   class disp_option;

} // namespace xml

//string CLASS_DECL_ACME operator + (const char * psz, const property & prop);
//
//::payload CLASS_DECL_ACME operator - (i32 i, const property & prop);
//::payload CLASS_DECL_ACME operator - (u32 user, const property & prop);
//::payload CLASS_DECL_ACME operator - (i64 i, const property & prop);
//::payload CLASS_DECL_ACME operator - (u64 u, const property & prop);
//::payload CLASS_DECL_ACME operator - (double d, const property & prop);
//::payload CLASS_DECL_ACME operator - (const ::payload & payload, const property & prop);

//::payload CLASS_DECL_ACME operator + (i32 i, const property & prop);
//::payload CLASS_DECL_ACME operator + (u32 user, const property & prop);
//::payload CLASS_DECL_ACME operator + (i64 i, const property & prop);
//::payload CLASS_DECL_ACME operator + (u64 u, const property & prop);
//::payload CLASS_DECL_ACME operator + (double d, const property & prop);
//::payload CLASS_DECL_ACME operator + (const ::payload & payload, const property & prop);

//::payload CLASS_DECL_ACME operator / (i32 i, const property & prop);
//::payload CLASS_DECL_ACME operator / (u32 user, const property & prop);
//::payload CLASS_DECL_ACME operator / (i64 i, const property & prop);
//::payload CLASS_DECL_ACME operator / (u64 u, const property & prop);
//::payload CLASS_DECL_ACME operator / (double d, const property & prop);
//::payload CLASS_DECL_ACME operator / (const ::payload & payload, const property & prop);

//::payload CLASS_DECL_ACME operator * (i32 i, const property & prop);
//::payload CLASS_DECL_ACME operator * (u32 user, const ::property & prop);
//::payload CLASS_DECL_ACME operator * (i64 i, const property & prop);
//::payload CLASS_DECL_ACME operator * (u64 u, const property & prop);
//::payload CLASS_DECL_ACME operator * (double d, const property & prop);
//::payload CLASS_DECL_ACME operator * (const ::payload & payload, const property & prop);


//namespace xml
//{
//
//
//   class disp_option;
//   class department;
//   class document;
//   class node;
//   class tree_schema;
//   class output_tree;
//   class input_tree;
//
//
//} // namespace xml


//using property = payload;


void on_property_construct(property * pproperty);
void on_property_destruct(property * pproperty);


class CLASS_DECL_ACME property : public ::payload
{
public:


   using TYPE1 = ::id;
   using ARG_TYPE1 = const ::id &;
   using TYPE2 = payload;
   using ARG_TYPE2 = const ::payload &;


   ::id              m_id;


   property() { on_property_construct(this); }
   property(const ::id& id) : m_id(id) { on_property_construct(this); }
   property(const ::id& id, const ::payload& varValue) : m_id(id), ::payload(varValue) { on_property_construct(this); }
   property(const ::property& property) : m_id(property.m_id), ::payload(property) { on_property_construct(this); }
   property(::property&& property) : m_id(::move(property.m_id)), ::payload(::move(property)) { on_property_construct(this); }
   ~property() { on_property_destruct(this); }


   void* operator new(size_t size)
   {

      return property_memory_allocate(size);

   }


   void* operator new(size_t size, const char* /* pszFileName */, int /* nLine */)
   {

      return property_memory_allocate(size);

   }


   void operator delete(void * p)
   {

      return property_memory_free(p);

   }


   void operator delete(void * p, const char* /* pszFileName */, int /* nLine */)
   {

      return property_memory_free(p);

   }



   using payload::operator =;

   ::id& element1() { return m_id; };
   const ::id& element1() const { return m_id; };
   ::payload& element2() { return *this; };
   const ::payload& element2() const { return *this; };



   property & operator = (const property & property)
   {

      if(this != &property)
      {

         payload::operator=((const ::payload & )property);

      }

      return *this;

   }


   //inline property operator + (const string & str) const { return property(m_id, to_string() + str); }
   //inline property operator + (const char * psz) const { return property(m_id, to_string() + psz); }
//   inline property operator + (const property & prop) const { return property(m_id, (const ::payload &) *this + (const ::payload &) prop); }


   ::id name() const { return m_id; }

//};


// As of 2019-Nov, property had no base class(es)
// As of 2020-Jan, property had no base class(es) again
//    - plus: doesn't matter parent property set? m_ppropertyset
//class CLASS_DECL_ACME property : public ::payload
//   //virtual public matter
//{
//public:
//
//   //using CHAR_TYPE = char;
//
//
//   //__pointer(property_set)    m_ppropertyset;
//   ::id                       m_id;
//   ::payload                      m_var;
//
////   property() { }
////
////   //property(property_set * pset);
////
////   property(const property & property) :
////      m_id(property.m_id),
////      m_var(property)
////   {
////   }
////
////   //property(const property * pproperty);
////   //property(const ::property * & pproperty) : property(pproperty.m_p) { }
////   //pr//operty(property_set * pset, const id & strName);
////   //property(property_set * pset, const id & strName, const ::payload & payload, ::matter * pobject = nullptr);
////   template < typename VALUE >
////   property(const ::id & id, const VALUE & value) : m_id(id), m_var(value) { }
////
////   property(const ::id & id) : m_id(id) { }
////
////   property(property && prop) : m_id(::move(prop.m_id)), m_var(::move(prop)) { }
////
////   ~property() { }
////
////
////   /// m_id : m_id is the property key, and
////   /// the property key should be only changed/manipulated by the
////   /// property_map/property_set
////   inline auto & name()
////   {
////      return m_id;
////   }
////
////   inline const auto & name() const
////   {
////      return m_id;
////   }
////
////   inline auto & element1()
////   {
////      return m_id;
////   }
////
////   inline const auto & element1() const
////   {
////      return m_id;
////   }
////
////   inline ::payload & element2()
////   {
////      return m_var;
////   }
////
////   inline const ::payload & element2() const
////   {
////      return m_var;
////   }
////
////
////   const char * c_str() const { return get_ref_string().c_str(); }
////
  inline string & get_json(string & str, bool bNewLine = true) const
   {

      str += "\"";

      str += m_id.str();

      str += "\"";

      str += ": ";

      payload::get_json(str, bNewLine);

      return str;

   }

  string get_json(bool bNewLine = true) const
  {

     string str;

     return get_json(str, bNewLine);

  }

////
      string & get_http_post(string & str) const;
      string get_http_post() const { string str; return get_http_post(str); }
////
////   string_array & stra();
////   int_array & inta();
////   payload_array & payloada();
////   property_set & propset();
////   const string_array & stra() const;
////   const int_array & inta() const;
////   const payload_array & payloada() const;
////   const property_set & propset() const;
////   inline void get_string(char * psz) const;
////   strsize get_length() const;
////
   //string get_xml(::xml::disp_option * opt = ((::xml::disp_option *) 1));
////
////   inline bool has_char() const { return has_char(); }
////
////
////
////
////
////
////   inline ::payload operator()(const id & id) const { return find_property(id); }
////
////   inline ::payload operator()(const char * pszName) const { return find_property(::id(pszName)); }
////
////   inline ::payload operator()(const string & strName) const { return find_property(::id(strName)); }
////
////   inline ::payload operator()(::index iIndex) const { return find_property(::id(iIndex)); }
////
////   inline bool has_property(const ::id & id) const { return m_etype == e_type_property_set ? has_property(id) : false; }
////
////   inline property & operator[](const id & id) { return get_property(id); }
////   inline ::payload operator[](const id & id) const { return find_property(id); }
////
////   inline property & operator[](const char * pszName) { return get_property(::id(pszName)); }
////   inline ::payload operator[](const char * pszName) const { return find_property(::id(pszName)); }
////
////   inline property & operator[](const string & strName) { return get_property(::id(strName)); }
////   inline ::payload operator[](const string & strName) const { return find_property(::id(strName)); }
////
////   inline property & operator[](::index iIndex) { return get_property(::id(iIndex)); }
////   inline ::payload operator[](::index iIndex) const { return find_property(::id(iIndex)); }
////
////#ifdef OS64BIT
////
////   inline property & operator[](i32 iIndex) { return get_property(::id(iIndex)); }
////   inline ::payload operator[](i32 iIndex) const { return find_property((::id) iIndex); }
////
////#endif
////
////   inline property * find_property(const ::id & id) const;
////
////   inline property & get_property(const ::id & id);
////
////   inline bool operator !() const { return is_false(); }
////
////   bool is_false() const;
////   bool is_bool_false() const;
////   bool is_set_false() const;
////
////
////   inline ::payload & get_value()
////   {
////      return m_var;
////   }
////   inline const ::payload & get_value() const
////   {
////      return m_var;
////   }
////   inline void set_value(const ::payload & payload)
////   {
////      m_var = payload;
////   }
////
////   void unset();
////
////
////   inline void   get_value(::payload & value);
////   inline void   get(::payload & value);
////   inline ::payload &  get();
////   inline void   set(const ::payload & payload);
////
////
////   template < typename ENUM >
////   ENUM e(ENUM edefault = enum_default < ENUM >())  const { return e < ENUM > (edefault); }
////
////   ::id get_id(const char * pszOnNull = nullptr) const
////   {
////      return get_id(pszOnNull);
////   }
////
////   bool get_bool() const
////   {
////      return get_bool();
////   }
////
////   ::i32 i32(i32 iDefault = 0) const
////   {
////      return i32(iDefault);
////   }
////
////   template < typename ENUM >
////   ::i32 i32(ENUM edefault = ::enum_default < ENUM > ()) const
////   {
////      return e(edefault);
////   }
////
////   ::u32 u32(u32 uiDefault = 0) const
////   {
////      return u32(uiDefault);
////   }
////
////   ::i64 i64(i64 iDefault = 0) const
////   {
////      return i64(iDefault);
////   }
////   ::millis millis(millis tickDefault = 0) const
////   {
////      return millis(tickDefault);
////   }
////
////   ::u64 u64(u64 uiDefault = 0) const
////   {
////      return u64(uiDefault);
////   }
////
////   double get_double() const
////   {
////      return get_double();
////   }
////
////   string get_string() const
////   {
////      return get_string();
////   }
////
////   string & to_string(string & str) const
////   {
////      return str = get_string();
////   }
////
////   string to_string() const
////   {
////      return get_string();
////   }
////
////   string to_string_base() const
////   {
////      return get_string();
////   }
////
////   void set_string(const char * psz)
////   {
////      m_var = psz;
////   }
////
////   property & operator++(::i32)
////   {
////      m_var++;
////      return *this;
////   }
////
////   property & operator =(const property & prop);
////
////   property & operator =(const property_set & propset)
////   {
////      m_var = propset;
////      return *this;
////   }
////
////   property & operator =(const ::payload & payload)
////   {
////      m_var = payload;
////      return *this;
////   }
////
////   property & operator =(const char * psz)
////   {
////      m_var = psz;
////      return *this;
////   }
////
////   property & operator =(const string & str)
////   {
////      m_var = str;
////      return *this;
////   }
////
////   property & operator =(const ::duration & duration)
////   {
////      m_var = duration;
////      return *this;
////   }
////
////   property & operator =(const ::file::path & path)
////   {
////      m_var = path;
////      return *this;
////   }
////
////   property & operator =(string && str)
////   {
////      m_var = ::move(str);
////      return *this;
////   }
////
////   property & operator =(const string_array & stra)
////   {
////      m_var = stra;
////      return *this;
////   }
////
////   property & operator =(const id & id)
////   {
////      m_var = id;
////      return *this;
////   }
////
////   property & operator =(double d)
////   {
////      m_var = d;
////      return *this;
////   }
////
////   property & operator =(::i32 i)
////   {
////      m_var = i;
////      return *this;
////   }
////
////#ifdef WINDOWS
////
////   property & operator =(::i32 l)
////   {
////      m_var = l;
////      return *this;
////   }
////
////   property & operator =(::u32 dw)
////   {
////      m_var = dw;
////      return *this;
////   }
////
////#endif
////
////   property & operator =(::u32 u)
////   {
////      m_var = u;
////      return *this;
////   }
////
////
////   property & operator =(::i64 i)
////   {
////      m_var = i;
////      return *this;
////   }
////
////   property & operator =(::u64 u)
////   {
////      m_var = u;
////      return *this;
////   }
////
////   property & operator =(::u64 * pinteraction)
////   {
////      m_var = pinteraction;
////      return *this;
////   }
////
////#if !defined(WINDOWS) && !defined(OS64BIT)
////
////   property & operator =(size_t * pinteraction)
////   {
////      m_var = (uptr *) pinteraction;
////      return *this;
////   }
////
////#endif
////
////   property & operator =(bool b)
////   {
////      m_var = b;
////      return *this;
////   }
////
////   // 2018-11-11 macos macos macos macOS macOS macOS MACOS MACOS MACOS
////#if !defined(WINDOWS_DESKTOP) && !defined(LINUX) && !defined(ANDROID)
////
////   property & operator =(size_t * point_i32)
////   {
////      m_var = (::i64 *) point_i32;
////      return *this;
////   }
////
////#endif
////
////   template < class T >
////   property & operator =(const pointer < T > & p)
////   {
////      m_var = p.m_p;
////      return *this;
////   }
////
////   template < class T >
////   property & operator =(const reference < T > & p)
////   {
////      m_var = p.operator T *();
////      return *this;
////   }
////
////   template < class T >
////   property & operator =(const composite < T > & p)
////   {
////      m_var = p.operator T * ();
////      return *this;
////   }
////
////
////   property & operator =(::matter * p)
////   {
////
////      m_var = p;
////
////      return *this;
////
////   }
////
////
////   property & operator =(std::nullptr_t)
////   {
////      set_type(::e_type_null);
////      return *this;
////   }
////
////
////   property & operator = (property && prop)
////   {
////
////      if(this != &prop)
////      {
////         release();
////         m_str.~string();
////         m_id.m_all = prop.m_id.m_all;
////         ::memcpy_dup(&m_var, &prop, sizeof(payload));
////         ::memset(&prop, 0, sizeof(payload));
////      }
////
////      return *this;
////
////   }
////
////
////   property & operator = (const block & block) { m_var = block; return *this; }
////   template < class E >
////   property & operator = (const enumeration < E > & eflag)
////   {
////      m_var = eflag;
////      return *this;
////   }
////
////   template < class T >
////   property & operator = (const memory_template < T > & memory)
////   {
////
////      m_var = memory.block();
////
////      return *this;
////
////   }
////
////   template < class T >
////   T & get_cast(T * pDefault = nullptr)
////   {
////      return get_cast < T >(pDefault);
////   }
////
////   template < class T >
////   __pointer(T) cast(T * pDefault = nullptr)
////   {
////      return cast < T >(pDefault);
////   }
////
////   template < class T >
////   __pointer(T) cast(T * pDefault = nullptr) const
////   {
////      return ((property *) this)->cast < T >(pDefault);
////   }
////
   template < typename T >
   inline __pointer(T)& defer_get(__pointer(T)& pointer) { return pointer = cast < T >(); }
////
////   operator const char *() const
////   {
////      return operator const char *();
////   }
////
////   operator string & ()
////   {
////      return operator string &();
////   }
////
////   operator ::file::path & ()
////   {
////      return operator ::file::path & ();
////   }
////
////   operator id()
////   {
////      return get_id();
////   }
////
////   operator double()
////   {
////      return get_double();
////   }
////
////   operator ::i32()
////   {
////      return operator ::i32();
////   }
////
////#ifdef WINDOWS
////
////   operator ::i32() { return operator ::i32(); }
////   operator ::i32() const { return operator ::i32(); }
////
////#endif
////
////   operator ::u32() { return operator ::u32(); }
////   operator ::u32() const { return operator ::u32(); }
////
////   operator ::i64() { return operator ::i64(); }
////   operator ::i64() const { return operator ::i64(); }
////
////   operator ::u64() { return operator ::u64(); }
////   operator ::u64() const { return operator ::u64(); }
////
////   inline operator bool &() { return operator bool &(); }
////   inline operator bool() const { return operator bool(); }
////
////   ::payload equals_ci_get(const char * pszCompare, ::payload varOnEqual, ::payload varOnDifferent) const;
////   ::payload equals_ci_get(const char * pszCompare, ::payload varOnEqual) const;
////
////   ::count get_count() const;
////   ::count array_get_count() const;
////   bool array_contains(const char * psz, index first = 0, index last = -1) const;
////   bool array_contains_ci(const char * psz, index first = 0, index last = -1) const;
////
////   bool is_set() const;
////   bool is_new() const;
////   bool is_null() const;
////   bool is_new_or_null() const;
////   bool is_empty() const;
////   bool is_true() const;
////
////   inline string implode(const char * pszGlue) const;
////
////   ::payload element_at(index iIndex) const;
////   ::payload at(index iIndex) const;
////
////   ::i32 compare_value_ci(const char * psz) const;
////
////   ::comparison::var_strict strict_compare() const;
////
////   ::i32 str_compare(const property & prop) const;
////
////   bool strict_equal(const property & prop) const;
////   bool strict_equal(const ::payload & payload) const;
////   bool strict_equal(const char * psz) const;
////   bool strict_equal(const string & str) const;
////   bool strict_equal(double d) const;
////   bool strict_equal(::i32 i) const;
////   bool strict_equal(bool b) const;
////
////   bool strict_different(const property & prop) const;
////   bool strict_different(const ::payload & payload) const;
////   bool strict_different(const char * psz) const;
////   bool strict_different(const string & str) const;
////   bool strict_different(double d) const;
////   bool strict_different(::i32 i) const;
////   bool strict_different(bool b) const;
////
////   bool operator == (const property & prop) const;
////   bool operator == (const ::payload & payload) const;
////   bool operator == (const char * psz) const;
////   bool operator == (const string & str) const;
////   bool operator == (::i32 i) const;
////   bool operator == (bool b) const;
////
////   bool operator != (const property & prop) const;
////   bool operator != (const ::payload & payload) const;
////   bool operator != (const char * psz) const;
////   bool operator != (const string & str) const;
////   bool operator != (::i32 i) const;
////   bool operator != (bool b) const;
////
////   bool operator < (const property & prop) const;
////   bool operator < (const ::payload & payload) const;
////   bool operator < (const char * psz) const;
////   bool operator < (const string & str) const;
////   bool operator < (::i32 i) const;
////   bool operator < (bool b) const;
////
////   bool operator <= (const property & prop) const;
////   bool operator <= (const ::payload & payload) const;
////   bool operator <= (const char * psz) const;
////   bool operator <= (const string & str) const;
////   bool operator <= (::i32 i) const;
////   bool operator <= (bool b) const;
////
////   bool operator >= (const property & prop) const;
////   bool operator >= (const ::payload & payload) const;
////   bool operator >= (const char * psz) const;
////   bool operator >= (const string & str) const;
////   bool operator >= (::i32 i) const;
////   bool operator >= (bool b) const;
////
////   bool operator > (const property & prop) const;
////   bool operator > (const ::payload & payload) const;
////   bool operator > (const char * psz) const;
////   bool operator > (const string & str) const;
////   bool operator > (::i32 i) const;
////   bool operator > (bool b) const;
////
////   bool operator == (::i64 i) const;
////   bool operator != (::i64 i) const;
////   bool operator < (::i64 i) const;
////   bool operator <= (::i64 i) const;
////   bool operator >= (::i64 i) const;
////   bool operator > (::i64 i) const;
////
////   ::payload operator + (const char * psz) const;
////   ::payload operator + (const string & str) const;
////
////   ::payload operator - (::i32 i) const;
////   ::payload operator - (::u32 user) const;
////   ::payload operator - (::i64 i) const;
////   ::payload operator - (::u64 u) const;
////   ::payload operator - (double d) const;
////   ::payload operator - (const ::payload & payload) const;
////
////   ::payload operator + (::i32 i) const;
////   ::payload operator + (::u32 user) const;
////   ::payload operator + (::i64 i) const;
////   ::payload operator + (::u64 u) const;
////   ::payload operator + (double d) const;
////   ::payload operator + (const ::payload & payload) const;
////
////   ::payload operator / (::i32 i) const;
////   ::payload operator / (::u32 user) const;
////   ::payload operator / (::i64 i) const;
////   ::payload operator / (::u64 u) const;
////   ::payload operator / (double d) const;
////   ::payload operator / (const ::payload & payload) const;
////
////   ::payload operator * (::i32 i) const;
////   ::payload operator * (::u32 user) const;
////   ::payload operator * (::i64 i) const;
////   ::payload operator * (::u64 u) const;
////   ::payload operator * (double d) const;
////   ::payload operator * (const ::payload & payload) const;
////
////   property & operator -= (::i32 i);
////   property & operator -= (::u32 user);
////   property & operator -= (::i64 i);
////   property & operator -= (::u64 u);
////   property & operator -= (double d);
////   property & operator -= (const ::payload & payload);
////   property & operator -= (const property & prop);
////
////   property & operator += (::i32 i);
////   property & operator += (::u32 user);
////   property & operator += (::i64 i);
////   property & operator += (::u64 u);
////   property & operator += (double d);
////   property & operator += (const ::payload & payload);
////   property & operator += (const property & prop);
////   property & operator += (const char * psz);
////   property & operator += (const string & str);
////
////   property & operator /= (::i32 i);
////   property & operator /= (::u32 user);
////   property & operator /= (::i64 i);
////   property & operator /= (::u64 u);
////   property & operator /= (double d);
////   property & operator /= (const ::payload & payload);
////   property & operator /= (const property & prop);
////
////   property & operator *= (::i32 i);
////   property & operator *= (::u32 user);
////   property & operator *= (::i64 i);
////   property & operator *= (::u64 u);
////   property & operator *= (double d);
////   property & operator *= (const ::payload & payload);
////   property & operator *= (const property & prop);
////
////
////   void parse_json(const string & str);
////   void parse_json(const char * & pszJson,strsize length);
////   void parse_json(const char * & pszJson,const char * pszEnd);
////
////
////   ::payload explode(const char * pszSeparator, bool bAddEmpty = true) const;
////
////
////   void null() { null(); }
////
//
};


using property_pointer = ::property *;


CLASS_DECL_ACME void property_parse_json_id(id & id, const char *& pszJson, const char * pszEnd);
CLASS_DECL_ACME void property_parse_json_value(::payload & payload, const char *& pszJson, const char * pszEnd);
CLASS_DECL_ACME void property_skip_json_id(const char *& pszJson, const char * pszEnd);
CLASS_DECL_ACME void property_skip_json_value(const char *& pszJson, const char * pszEnd);


#include "acme/primitive/collection/ptr_array.h"
#include "acme/primitive/collection/auto_ptr_array.h"


using property_ptra = auto_ptr_array < ::property >;

//using property_map = map < ::id, const ::id &, payload, const ::payload &, ::property >;


//inline bool operator == (const string & str, const property & prop)
//{
//
//   return str == prop.get_string();
//
//}



//inline ::payload CLASS_DECL_ACME operator - (i32 i, const property& prop) { return operator - (i, (const ::payload &) prop); }
//inline ::payload CLASS_DECL_ACME operator - (u32 user, const property& prop) { return operator - (user, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator - (i64 i, const property& prop) { return operator - (i, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator - (u64 u, const property& prop) { return operator - (u, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator - (double d, const property& prop) { return operator - (d, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator - (const ::payload & payload, const property& prop) { return operator - (payload, (const ::payload &)prop); }

//inline ::payload CLASS_DECL_ACME operator + (i32 i, const property& prop) { return operator + (i, (const ::payload &) prop); }
//inline ::payload CLASS_DECL_ACME operator + (u32 user, const property& prop) { return operator + (user, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator + (i64 i, const property& prop) { return operator + (i, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator + (u64 u, const property& prop) { return operator + (u, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator + (double d, const property& prop) { return operator + (d, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator + (const ::payload & payload, const property& prop) { return payload, (const ::payload &)prop); }

//inline ::payload CLASS_DECL_ACME operator / (i32 i, const property& prop) { return operator / (i, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator / (u32 user, const property& prop) { return operator / (user, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator / (i64 i, const property& prop) { return operator / (i, (const ::payload&)prop); }
//inline ::payload CLASS_DECL_ACME operator / (u64 u, const property& prop) { return operator / (u, (const ::payload&)prop); }
//inline ::payload CLASS_DECL_ACME operator / (double d, const property& prop) { return operator / (d, (const ::payload&) prop); }
//inline ::payload CLASS_DECL_ACME operator / (const ::payload & payload, const property& prop) { return operator / (payload, (const ::payload&) prop); }

//inline ::payload CLASS_DECL_ACME operator * (i32 i, const property& prop) { return operator * (i, (const ::payload&) prop); }
//inline ::payload CLASS_DECL_ACME operator * (u32 user, const ::property& prop) { return operator * (user, (const ::payload&) prop); }
//inline ::payload CLASS_DECL_ACME operator * (i64 i, const property& prop) { return operator * (i, (const ::payload&) prop); }
//inline ::payload CLASS_DECL_ACME operator * (u64 u, const property& prop) { return operator * (u, (const ::payload&)prop); }
//inline ::payload CLASS_DECL_ACME operator * (double d, const property& prop) { return operator * (d, (const ::payload&)prop); }
//inline ::payload CLASS_DECL_ACME operator * (const ::payload & payload, const property& prop) { return operator * (payload, (const ::payload&)prop); }


#define new ACME_NEW
