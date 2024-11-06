// Included enum_dialog_result camilo on 2021-01-21 05:53 PM <3ThomasBorregaardSorensen
#pragma once


#include "acme/constant/element.h"
#include "acme/prototype/string/_u32hash.h"

#include "acme/prototype/comparison/equals.h"
#include "acme/prototype/comparison/hash.h"
#include "acme/prototype/prototype/transfer.h"
#include "acme/prototype/string/string.h"

enum enum_id : ::uptr;


//class atom_space;


class lparam;



//// Lets (AMajor.AMinor) (BMajor.BMinor)
//// order_square(AMajor - BMajor, AMinor - BMinor)
//// Maybe it is better to cache MAJOR_COMPARISON into a variable?
//typename < typename ORDERING >
//constexpr ::std::strong_ordering order squaresuperscript(::std::strong_ordering orderingMajor, ORDERING ordering)
//{
//
//   return orderingMajor != 0 ? orderingMajor : orderingMinor;
//
//}



#ifndef NO_TEMPLATE


#define __id_is_null_ptr(p) (!(p))


inline bool __atom_str_is_empty(const ::ansi_character * psz)
{

   return __id_is_null_ptr(psz) || *psz == '\0';

}


template <typename T>
int __atom_sgn(T x)
{

   return (((T) 0) < x) - (x < ((T) 0));

}


//#define __atom_safe_strcmp(a, b) ::str::order(a, b)
//
//
//#define __atom_safe_stricmp(a, b) ::str::case_insensitive_order(a, b)
//
//
//#define __atom_str_begins(a, b) string_begins(a, b)
//
//
//#define case_insensitive___atom_str_begins(a, b) case_insensitive_string_begins(a, b)


#else


#define __atom_sgn(x) ((0 < (x)) - ((x) < 0))


#define __atom_is_null_ptr(p) (!(p))


#define __atom_str_is_empty(psz) (__atom_is_null_ptr(psz) || *psz == '\0')




//inline int __atom_safe_strcmp(const char * a, const char * b)
//{
//
//   if (__atom_str_is_empty(a))
//   {
//
//      if (__atom_str_is_empty(b))
//      {
//
//         return true;
//
//      }
//      else
//      {
//
//         return -1;
//
//      }
//
//   }
//   else if(__atom_str_is_empty(b))
//   {
//
//      return 1;
//
//   }
//   else
//   {
//
//      return strcmp(a, b);
//
//   }
//
//}
//
//
//inline int __atom_safe_stricmp(const char * a, const char * b)
//{
//
//   if (__atom_str_is_empty(a))
//   {
//
//      if (__atom_str_is_empty(b))
//      {
//
//         return true;
//
//      }
//      else
//      {
//
//         return -1;
//
//      }
//
//   }
//   else if (__atom_str_is_empty(b))
//   {
//
//      return 1;
//
//   }
//   else
//   {
//
//      return stricmp(a, b);
//
//   }
//
//}
//
//inline bool __atom_str_begins(const char * a, const char * b)
//{
//
//   if (__atom_str_is_empty(a))
//   {
//
//      if (__atom_str_is_empty(b))
//      {
//
//         return true;
//
//      }
//      else
//      {
//
//         return false;
//
//      }
//
//   }
//   else if (__atom_str_is_empty(b))
//   {
//
//      return true;
//
//   }
//   else
//   {
//
//      return strncmp(a, b, strlen(b));
//
//   }
//
//}
//
//
//inline bool case_insensitive___atom_str_begins(const char * a, const char * b)
//{
//
//   if (__atom_str_is_empty(a))
//   {
//
//      if (__atom_str_is_empty(b))
//      {
//
//         return true;
//
//      }
//      else
//      {
//
//         return false;
//
//      }
//
//   }
//   else if (__atom_str_is_empty(b))
//   {
//
//      return true;
//
//   }
//   else
//   {
//
//      return strnicmp(a, b, strlen(b));
//
//   }
//
//}


#endif


class CLASS_DECL_ACME atom
{
public:


   using PRIMITIVE_ATOM_TAG = PRIMITIVE_ATOM_TAG_TYPE;

   enum enum_type : int
   {

      e_type_empty = -2,

      e_type_null = -1,

      e_type_integer = 0,
      e_type_id,
      e_type_factory,
      e_type_task_tool,
      e_type_timer,
      e_type_message,
      e_type_subject,
      e_type_property,
      e_type_command,
      //e_type_command_probe,
      //e_type_has_command_handler,
      e_type_update,
      e_type_dialog_result,
      e_type_impact,
      e_type_happening,
      e_type_element,
      e_type_check,
      e_type_status,
      e_type_domainid,

      e_type_not_an_atom = 127,


      e_type_text = 1ull << 8,
      e_type_id_text = e_type_id | e_type_text,
      e_type_factory_text = e_type_factory | e_type_text,
      e_type_task_tool_text = e_type_task_tool | e_type_text,
      e_type_timer_text = e_type_timer | e_type_text,
      e_type_message_text = e_type_message | e_type_text,
      e_type_property_text = e_type_property | e_type_text,
      e_type_command_text = e_type_command | e_type_text,
      //e_type_command_probe_text = e_type_command_probe | e_type_text,
      //e_type_has_command_handler_text = e_type_has_command_handler | e_type_text,
      e_type_update_text = e_type_update | e_type_text,
      e_type_impact_text = e_type_impact | e_type_text,
      e_type_happening_text = e_type_happening | e_type_text,
      e_type_element_text = e_type_element | e_type_text,


      e_type_range = 1ull << 16,
      e_type_id_range = e_type_id | e_type_range,
      e_type_factory_range = e_type_factory | e_type_range,
      e_type_task_tool_range = e_type_task_tool | e_type_range,
      e_type_timer_range = e_type_timer | e_type_range,
      e_type_message_range = e_type_message | e_type_range,
      e_type_property_range = e_type_property | e_type_range,
      e_type_command_range = e_type_command | e_type_range,
      //e_type_command_probe_range = e_type_command_probe | e_type_range,
      //e_type_has_command_handler_range = e_type_has_command_handler | e_type_range,
      e_type_update_range = e_type_update | e_type_range,
      e_type_impact_range = e_type_impact | e_type_range,
      e_type_happening_range = e_type_happening | e_type_range,
      e_type_element_range = e_type_element | e_type_range,


   };


   union
   {

      enum_id              m_eid;
      enum_impact          m_eimpact;
      enum_property        m_eproperty;
      enum_factory         m_efactory;
      enum_task_tool       m_etasktool;
      enum_timer           m_etimer;
      enum_message         m_emessage;
      enum_dialog_result   m_edialogresult;
      enum_happening       m_ehappening;
      enum_element         m_eelement;
      e_status             m_estatus;
      e_command            m_ecommand;
      e_check              m_echeck;
      domain_id            m_domainid;
      ::string             m_str;
      ::ansi_range         m_range;
      ::i64                m_iLargest;
      ::u64                m_uLargest;

   };

   enum_type               m_etype;

//protected:
//
//
//   friend atom_space;
//   inline atom(const ::scoped_string & scopedstr, atom_space *);


public:


   inline atom();
   inline atom(enum_type etype);

   inline atom(enum_id eid);
   inline atom(enum_element eelement);
   //inline atom(::enum_id EID);
   //inline atom(const ::e_command & ecommand);
   inline atom(enum_message emessage);
   //inline atom(ENUM_MESSAGE EMESSAGE);
   inline atom(enum_impact eimpact);
   inline atom(ENUM_IMPACT EIMPACT);
   inline atom(enum_property eproperty);
   inline atom(enum_factory efactory);
   inline atom(enum_task_tool etasktool);
   inline atom(enum_timer etimer);
   inline atom(enum_dialog_result edialogresult);
   inline atom(enum_happening eevent);
   inline atom(enum_check echeck);
   inline atom(enum_status estatus);

   inline atom(enum_type etypeAdd, const atom & atom);
   inline atom(const atom & atom);
   inline atom(const domain_id & domainid);
   atom(const ::ansi_character * psz);
   atom(const inline_number_string & inlinenumberstring);

   template < primitive_signed SIGNED >
   atom(SIGNED i);
   template < primitive_unsigned UNSIGNED >
   atom(UNSIGNED u);
   template < primitive_enum ENUM >
   atom(ENUM e);
   atom(const ::string & str);
   //atom(const const_ansi_range & range);
   //atom(const_ansi_range && range);
   //atom(const const_ansi_range && range);
   //atom(const type & type);
   template < character_range RANGE >
   atom(const RANGE & range);
   //template < has_as_string_not_payload HAS_AS_STRING_NOT_PAYLOAD >
   //atom(const HAS_AS_STRING_NOT_PAYLOAD& has_as_string_not_payload);
   ////atom(const ::scoped_string & str);
   ////atom(const ::payload & payload);
   ////atom(const ::lparam & lparam);
   template < primitive_payload PAYLOAD  >
   atom(const PAYLOAD & payload);
   
   atom(::atom && atom)
   { 
      m_etype = atom.m_etype; 
      if (atom.m_etype & e_type_text)
      {
         ::new(&m_str) ::string(::transfer(atom.m_str));
      }
      else
      {
         m_uLargest = atom.m_uLargest;
      }
      atom.m_etype = e_type_integer; 
      atom.m_uLargest = 0; 
   }
   ~atom()
   {

      _defer_free();

      m_etype = e_type_null;

   }

   void _defer_free()
   {

      if (is_text() && !is_range())
      {

         m_str.::string::~string();

      }

   }


   enum_type primitive_type() const
   {

      if(m_etype < 0)
      {

         return m_etype;

      }
      else if(m_etype < e_type_text)
      {

         return e_type_integer;

      }
      else
      {

         return e_type_text;

      }

   }


   // returned compounded_type should have same primitive type as the atom
   enum_type compounded_type(enum_type etypeAdd) const
   {

      return (enum_type) (
         (((::iptr) m_etype) & (~(::iptr)0xffff)) |
         ((::iptr)etypeAdd & (::iptr)0xffff)
         );

   }


   ::atom compounded(enum_type etype) const
   {

      return {compounded_type(etype), *this};

   }


   void set_compounded_type2(enum_type etype)
   {

      m_etype = compounded_type(etype);

   }


   void set_type(enum_type etype)
   {

      if(m_etype != etype)
      {

         if(!is_text(etype) || is_range(etype))
         {

            _defer_free();

         }

      }

      m_etype = etype;

   }

   enum_type get_type() const
   {

      return m_etype;

   }


   bool _is_compounded(enum_type etype) const { return (m_etype & 0xffff) == etype;}



   bool is_message() const { return m_etype == e_type_message; }


   bool is_command() const { return _is_compounded(e_type_command); }
   //bool is_command_probe() const { return _is_compounded(e_type_command_probe); }
   //bool is_has_command_handler() const { return _is_compounded(e_type_has_command_handler); }
   bool is_update() const { return _is_compounded(e_type_update); }


   bool is_true(bool bDefault = false) const;

   inline bool operator == (const atom& atom) const;
   inline ::std::strong_ordering operator <=> (const atom & atom) const;

   inline bool operator == (const ::scoped_string & str) const;
   inline ::std::strong_ordering operator <=> (const ::scoped_string & str) const;

   inline bool operator == (const ::string & str) const;
   inline ::std::strong_ordering operator <=> (const ::string & str) const;

   template < strsize n >
   inline bool operator == (const ::ansi_character (&cha)[n]) const;
   template < strsize n >
   inline ::std::strong_ordering operator <=> (const ::ansi_character (&cha)[n]) const;

   //inline ::std::strong_ordering order(const ::scoped_string & scopedstr) const;
   //inline bool operator == (const ::scoped_string & scopedstr) const;
   //inline ::std::strong_ordering operator <=> (const ::scoped_string & scopedstr) const;
   //inline bool operator < (const ::scoped_string & scopedstr) const;
   //inline bool operator <= (const ::scoped_string & scopedstr) const;
   //inline bool operator > (const ::scoped_string & scopedstr) const;
   //inline bool operator >= (const ::scoped_string & scopedstr) const;


//#ifndef NO_TEMPLATE


   //inline ::std::strong_ordering order(const ::string & str) const;
   //inline bool operator == (const ::string & str) const;
   //inline ::std::strong_ordering operator <=>(const ::string & str) const;
   //inline bool operator < (const ::string & str) const;
   //inline bool operator <= (const ::string & str) const;
   //inline bool operator > (const ::string & str) const;
   //inline bool operator >= (const ::string & str) const;



   //template < primitive_integral INTEGRAL >
   //inline ::std::strong_ordering order(INTEGRAL i) const;

   template < primitive_integral INTEGRAL >
   inline bool operator == (INTEGRAL i) const;

   template < primitive_integral INTEGRAL >
   inline ::std::strong_ordering operator <=> (INTEGRAL i) const;
   //template < primitive_integral INTEGRAL >
   //inline bool operator < (INTEGRAL i) const;
   //template < primitive_integral INTEGRAL >
   //inline bool operator <= (INTEGRAL i) const;
   //template < primitive_integral INTEGRAL >
   //inline bool operator > (INTEGRAL i) const;
   //template < primitive_integral INTEGRAL >
   //inline bool operator >= (INTEGRAL i) const;


//#endif // !NO_TEMPLATE


   //inline ::std::strong_ordering order(::enum_id eid) const;
   inline bool operator == (::enum_id eid) const;
   inline ::std::strong_ordering operator <=> (::enum_id eid) const;
   //inline bool operator < (::enum_id eid) const;
   //inline bool operator <= (::enum_id eid) const;
   //inline bool operator > (::enum_id eid) const;
   //inline bool operator >= (::enum_id eid) const;


   // //inline ::std::strong_ordering order(::enum_id EID) const { return order((::enum_id)EID); }
   // inline bool operator == (::enum_id EID) const { return *this == (::enum_id)EID; }
   // inline ::std::strong_ordering operator <=> (::enum_id EID) const { return *this <=> (::enum_id)EID; }
   // //inline bool operator < (::enum_id EID) const { return operator<((::enum_id)EID); }
   // //inline bool operator <= (::enum_id EID) const { return operator<=((::enum_id)EID); }
   // //inline bool operator > (::enum_id EID) const { return operator>((::enum_id)EID); }
   // //inline bool operator >= (::enum_id EID) const { return operator>=((::enum_id)EID); }

    inline bool operator == (::enum_command ecommand) const;
    inline ::std::strong_ordering operator <=> (::enum_command ecommand) const;

    inline bool operator == (::enum_impact eimpact) const;
    inline ::std::strong_ordering operator <=> (::enum_impact eid) const;

   inline bool operator == (const ::domain_id & domainid) const;
   inline ::std::strong_ordering operator <=> (const ::domain_id & domainid) const;

    inline bool operator == (::ENUM_IMPACT EIMPACT) const { return *this == (::enum_impact)EIMPACT; }
    inline ::std::strong_ordering operator <=> (::ENUM_IMPACT EIMPACT) const { return *this <=> (::enum_impact)EIMPACT; }

    //inline ::std::strong_ordering order(::enum_message emessage) const;
   inline bool operator == (::enum_message emessage) const;
   inline ::std::strong_ordering operator <=> (::enum_message emessage) const;
   //inline bool operator < (::enum_message emessage) const;
   //inline bool operator <= (::enum_message emessage) const;
   //inline bool operator > (::enum_message emessage) const;
   //inline bool operator >= (::enum_message emessage) const;


   // //inline ::std::strong_ordering order(ENUM_MESSAGE EID) const { return order((::enum_message)EID); }
   // inline bool operator == (ENUM_MESSAGE EID) const { return *this == (::enum_message)EID; }
   // inline ::std::strong_ordering operator <=> (ENUM_MESSAGE EID) const { return *this <=> (::enum_message)EID; }
   // //inline bool operator < (ENUM_MESSAGE EID) const { return operator<((::enum_message)EID); }
   // //inline bool operator <= (ENUM_MESSAGE EID) const { return operator<=((::enum_message)EID); }
   // //inline bool operator > (ENUM_MESSAGE EID) const { return operator>((::enum_message)EID); }
   // //inline bool operator >= (ENUM_MESSAGE EID) const { return operator>=((::enum_message)EID); }


   //inline int order(::enum_topic etopic) const;
   //inline bool operator == (::enum_topic etopic) const;
   //inline bool operator != (::enum_topic etopic) const;
   //inline bool operator < (::enum_topic etopic) const;
   //inline bool operator <= (::enum_topic etopic) const;
   //inline bool operator > (::enum_topic etopic) const;
   //inline bool operator >= (::enum_topic etopic) const;


   //inline ::std::strong_ordering order(::enum_dialog_result edialogresult) const;
   inline bool operator == (::enum_dialog_result edialogresult) const;
   inline ::std::strong_ordering operator <=> (::enum_dialog_result edialogresult) const;
   //inline bool operator < (::enum_dialog_result edialogresult) const;
   //inline bool operator <= (::enum_dialog_result edialogresult) const;
   //inline bool operator > (::enum_dialog_result edialogresult) const;
   //inline bool operator >= (::enum_dialog_result edialogresult) const;


   //inline ::std::strong_ordering order(::enum_happening ehappening) const;
   inline bool operator == (::enum_happening ehappening) const;
   inline ::std::strong_ordering operator <=> (::enum_happening ehappening) const;
   //inline bool operator < (::enum_happening ehappening) const;
   //inline bool operator <= (::enum_happening ehappening) const;
   //inline bool operator > (::enum_happening ehappening) const;
   //inline bool operator >= (::enum_happening ehappening) const;


   atom & operator = (const atom & atom);
   //atom & operator = (const ::scoped_string & scopedstr);

//#ifndef NO_TEMPLATE
//
//   atom & operator = (const ::payload & payload);
//   atom & operator = (const property & prop);
//   atom & operator = (const ::string & str);
//
//
   //template < primitive_integer INTEGRAL >
   //atom & operator = (INTEGER i);
//   template < primitive_natural NATURAL >
//   atom & operator = (NATURAL u);
//
//#endif // !NO_TEMPLATE
//
//
//   atom & operator = (const enum_id & eid);
//   atom & operator = (const enum_property & eproperty);
//   atom & operator = (const enum_factory & efactory);
//   atom & operator = (const enum_task_tool & etasktool);
//   atom & operator = (const enum_timer & etimer);
//   atom & operator = (const enum_message & emessage);
//   //atom & operator = (const enum_topic & etopic);
//   atom & operator = (const enum_dialog_result & edialogresult);


   //inline operator ::iptr() const { return as_iptr(); }
   //inline operator ::enum_message () const { return as_emessage(); }
   
   inline ::i64 as_i64() const;
   inline ::iptr as_iptr() const;
   inline int as_int() const { return (int) as_i64(); }
   inline unsigned int as_unsigned_int() const { return (unsigned int) as_i64(); }
   inline ::collection::index as_index() const { return (::collection::index)as_i64(); }
   inline unsigned int as_umessage() const { return as_unsigned_int(); }
   inline ::enum_message as_emessage() const;
   inline ::enum_id as_eid() const;
   //inline ::e_check as_echeck() const { return m_etype == e_type_check ? m_echeck : (::e_check) e_check_undefined; }
   //inline ::e_status as_estatus() const { return m_etype == e_type_status ? m_estatus : (::e_status) e_status_none; }


#define IMPLEMENT_ATOM_ENUMERATION(ENUMTYPE) \
   constexpr ::e_ ## ENUMTYPE as_e ## ENUMTYPE() const { return (m_etype == e_type_ ## ENUMTYPE) ? m_e ## ENUMTYPE : (::e_ ## ENUMTYPE) (::enum_ ## ENUMTYPE) 0; } \
   ::e_ ## ENUMTYPE & e ## ENUMTYPE ## _reference() { set_type(e_type_ ## ENUMTYPE); return m_e ## ENUMTYPE; } \
   constexpr atom(const ::e_ ## ENUMTYPE & e):m_etype(e_type_ ## ENUMTYPE), m_iLargest((::iptr)e) { }
//   inline explicit payload(::enum_ ## ENUMTYPE e) { m_etype = ::e_type_enum_ ## ENUMTYPE; m_e ## ENUMTYPE = e; } \
//   inline ::e_ ## ENUMTYPE e ## ENUMTYPE(::enum_ ## ENUMTYPE eDefault = enum_default < ::enum_ ## ENUMTYPE >()) const { return e < ::enum_ ## ENUMTYPE >(eDefault); } \
//   inline operator ::e_ ## ENUMTYPE () const { return ::e_ ## ENUMTYPE(); } \
//   ::e_ ## ENUMTYPE & e_ ## ENUMTYPE ## _reference();         \
//   inline payload & operator = (const ::e_ ## ENUMTYPE & e) &{ set_type(::e_type_enum_ ## ENUMTYPE, false); m_e ## ENUMTYPE = e; return *this; } \
//   inline payload & operator = (::enum_ ## ENUMTYPE e) { set_type(::e_type_enum_ ## ENUMTYPE, false); m_e ## ENUMTYPE = e; return *this; } \
//   inline bool equals_enum (::e_ ## ENUMTYPE e) const { return m_etype == ::e_type_enum_ ## ENUMTYPE && m_e ## ENUMTYPE == e; }
   IMPLEMENT_ATOM_ENUMERATION(status);
   IMPLEMENT_ATOM_ENUMERATION(command);
   IMPLEMENT_ATOM_ENUMERATION(check);
#undef IMPLEMENT_ATOM_ENUMERATION


   //inline operator const char* () const;
   //inline operator enum_dialog_result () const;

   //inline ::e_check & echeck_reference() { if(m_etype != e_type_check) set_compounded_type(e_type_check); return m_echeck; }

   //::string as_string() const;
   //::string string() const;
   ::string as_string() const;
   ::domain_id as_domainid() const;


   //operator ::string() const { return as_string(); }


   inline bool is_null() const;
   inline bool is_empty() const;
   inline bool has_char() const;
   inline bool is_set() const { return !is_empty(); }
   
   inline void Empty();
   inline void clear();
   

   //inline ::std::strong_ordering CompareNoCase(const ::scoped_string & scopedstr) const { return case_insensitive_order(psz); }
   inline ::std::strong_ordering case_insensitive_order(const ::scoped_string & scopedstr) const;


   inline bool begins(const ::scoped_string & scopedstrPrefix) const;
   inline bool case_insensitive_begins(const ::scoped_string & scopedstrPrefix) const;

   inline bool ends(const ::scoped_string & scopedstrSuffix) const;
   inline bool case_insensitive_ends(const ::scoped_string & scopedstrSuffix) const;


   constexpr static bool is_text(enum_type etype) { return etype >= e_type_text; }
   constexpr static bool is_range(enum_type etype) { return etype >= e_type_range; }
   constexpr static bool is_integer(enum_type etype) { return etype >= 0 && etype < e_type_text; }


   constexpr bool is_text() const { return is_text(m_etype); }
   constexpr bool is_range() const { return is_range(m_etype); }
   constexpr bool is_integer() const { return is_integer(m_etype); }


   //inline atom & operator +=(const ::scoped_string & scopedstr);



   //inline string operator +(const atom & atom) const;
   inline ::string operator +(const ::ansi_character * psz) const;
   inline ::string operator +(const ::string & str) const;


   operator ::u32hash() const
   {

      return { 
         (((unsigned int)m_etype) << 24)
         ^
         (
            is_text() ? 
            ::unsigned_int_hash(m_str.c_str()).m_u : 
            ((((unsigned int)m_uLargest) >> 8) & 0xffffffffu)
         ) 
      };

   }


};


