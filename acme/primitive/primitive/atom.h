// Included enum_dialog_result camilo on 2021-01-21 05:53 PM <3ThomasBorregaardSørensen
#pragma once


#include "acme/primitive/string/_u32hash.h"
// #include "acme/primitive/string/string.h"
#include "acme/primitive/comparison/equals.h"
#include "acme/primitive/comparison/hash.h"
#include "acme/primitive/primitive/transfer.h"


enum enum_id : ::uptr;


//class atom_space;


class lparam;



//// Lets (AMajor.AMinor) (BMajor.BMinor)
//// order_square(AMajor - BMajor, AMinor - BMinor)
//// Maybe it is better to cache MAJOR_COMPARISON into a variable?
//typename < typename ORDERING >
//constexpr ::std::strong_ordering order²(::std::strong_ordering orderingMajor, ORDERING ordering)
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
//#define __atom_str_begins_ci(a, b) string_begins_ci(a, b)


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
//inline bool __atom_str_begins_ci(const char * a, const char * b)
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

   enum enum_type : ::iptr
   {

      e_type_empty = -2,

      e_type_null = -1,

      e_type_integer = 0,
      e_type_atom,
      e_type_factory,
      e_type_task_tool,
      e_type_timer,
      e_type_message,
      e_type_subject,
      e_type_property,
      e_type_command,
      e_type_command_probe,
      e_type_has_command_handler,
      e_type_update,
      e_type_dialog_result,
      e_type_impact,
      e_type_happening,

      e_type_text = 1ull << 16,
      e_type_id_text = e_type_atom | e_type_text,
      e_type_factory_text = e_type_factory | e_type_text,
      e_type_task_tool_text = e_type_task_tool | e_type_text,
      e_type_timer_text = e_type_timer | e_type_text,
      e_type_message_text = e_type_message | e_type_text,
      e_type_property_text = e_type_property | e_type_text,
      e_type_command_text = e_type_command | e_type_text,
      e_type_command_probe_text = e_type_command_probe | e_type_text,
      e_type_has_command_handler_text = e_type_has_command_handler | e_type_text,
      e_type_update_text = e_type_update | e_type_text,
      e_type_impact_text = e_type_impact | e_type_text,
      e_type_happening_text = e_type_happening | e_type_text,


      e_type_range = 1ull << 32,
      e_type_id_range = e_type_atom | e_type_range,
      e_type_factory_range = e_type_factory | e_type_range,
      e_type_task_tool_range = e_type_task_tool | e_type_range,
      e_type_timer_range = e_type_timer | e_type_range,
      e_type_message_range = e_type_message | e_type_range,
      e_type_property_range = e_type_property | e_type_range,
      e_type_command_range = e_type_command | e_type_range,
      e_type_command_probe_range = e_type_command_probe | e_type_range,
      e_type_has_command_handler_range = e_type_has_command_handler | e_type_range,
      e_type_update_range = e_type_update | e_type_range,
      e_type_impact_range = e_type_impact | e_type_range,
      e_type_happening_range = e_type_happening | e_type_range,


   };


   union
   {

      ::iptr               m_iId;
      ::uptr               m_u;
      ::iptr               m_i;
      enum_id              m_eid;
      enum_command         m_ecommand;
      enum_impact          m_eimpact;
      enum_property        m_eproperty;
      enum_factory         m_efactory;
      enum_task_tool       m_etasktool;
      enum_timer           m_etimer;
      enum_message         m_emessage;
      enum_dialog_result   m_edialogresult;
      enum_happening       m_ehappening;
      ::string             m_str;
      ::const_ansi_range   m_range;
      ::iptr               m_iBody;

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
   inline atom(ENUM_ID EID);
   inline atom(const ::e_command & ecommand);
   inline atom(enum_message emessage);
   inline atom(ENUM_MESSAGE EMESSAGE);
   inline atom(enum_impact eimpact);
   inline atom(ENUM_IMPACT EIMPACT);
   inline atom(enum_property eproperty);
   inline atom(enum_factory efactory);
   inline atom(enum_task_tool etasktool);
   inline atom(enum_timer etimer);
   inline atom(enum_dialog_result edialogresult);
   inline atom(enum_happening eevent);
   inline atom(enum_type etypeAdd, const atom & atom);
   inline atom(const atom & atom);
   atom(const ::ansi_character * psz);
   atom(const inline_number_string & inlinenumberstring);

   template < primitive_signed SIGNED >
   atom(SIGNED i);
   template < primitive_unsigned UNSIGNED >
   atom(UNSIGNED u);
   atom(const ::string & str);
   //atom(const const_ansi_range & range);
   //atom(const_ansi_range && range);
   //atom(const const_ansi_range && range);
   //atom(const type & type);
   template < character_range RANGE >
   atom(const RANGE & range);
   template < has_as_string HAS_AS_STRING >
   atom(const HAS_AS_STRING & has_as_string);
   //atom(const ::scoped_string & str);
   //atom(const ::payload & payload);
   //atom(const ::lparam & lparam);
   template < primitive_payload PAYLOAD  >
   atom(const PAYLOAD & payload);
   atom(::atom && atom) { m_etype = atom.m_etype; m_u = atom.m_u; atom.m_etype = e_type_integer; atom.m_u = 0; }
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


   void set_compounded_type(enum_type etype)
   {

      m_etype = compounded_type(etype);

   }

   bool _is_compounded(enum_type etype) const { return (m_etype & 0xffff) == etype;}



   bool is_message() const { return m_etype == e_type_message; }


   bool is_command() const { return _is_compounded(e_type_command); }
   bool is_command_probe() const { return _is_compounded(e_type_command_probe); }
   bool is_has_command_handler() const { return _is_compounded(e_type_has_command_handler); }
   bool is_update() const { return _is_compounded(e_type_update); }


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


   //inline ::std::strong_ordering order(ENUM_ID EID) const { return order((::enum_id)EID); }
   inline bool operator == (ENUM_ID EID) const { return *this == (::enum_id)EID; }
   inline ::std::strong_ordering operator <=> (ENUM_ID EID) const { return *this <=> (::enum_id)EID; }
   //inline bool operator < (ENUM_ID EID) const { return operator<((::enum_id)EID); }
   //inline bool operator <= (ENUM_ID EID) const { return operator<=((::enum_id)EID); }
   //inline bool operator > (ENUM_ID EID) const { return operator>((::enum_id)EID); }
   //inline bool operator >= (ENUM_ID EID) const { return operator>=((::enum_id)EID); }

    inline bool operator == (::enum_command ecommand) const;
    inline ::std::strong_ordering operator <=> (::enum_command ecommand) const;

    inline bool operator == (::enum_impact eimpact) const;
    inline ::std::strong_ordering operator <=> (::enum_impact eid) const;

    inline bool operator == (::ENUM_IMPACT EIMPACT) const { return *this == (::enum_impact)EIMPACT; }
    inline ::std::strong_ordering operator <=> (::ENUM_IMPACT EIMPACT) const { return *this <=> (::enum_impact)EIMPACT; }

    //inline ::std::strong_ordering order(::enum_message emessage) const;
   inline bool operator == (::enum_message emessage) const;
   inline ::std::strong_ordering operator <=> (::enum_message emessage) const;
   //inline bool operator < (::enum_message emessage) const;
   //inline bool operator <= (::enum_message emessage) const;
   //inline bool operator > (::enum_message emessage) const;
   //inline bool operator >= (::enum_message emessage) const;


   //inline ::std::strong_ordering order(ENUM_MESSAGE EID) const { return order((::enum_message)EID); }
   inline bool operator == (ENUM_MESSAGE EID) const { return *this == (::enum_message)EID; }
   inline ::std::strong_ordering operator <=> (ENUM_MESSAGE EID) const { return *this <=> (::enum_message)EID; }
   //inline bool operator < (ENUM_MESSAGE EID) const { return operator<((::enum_message)EID); }
   //inline bool operator <= (ENUM_MESSAGE EID) const { return operator<=((::enum_message)EID); }
   //inline bool operator > (ENUM_MESSAGE EID) const { return operator>((::enum_message)EID); }
   //inline bool operator >= (ENUM_MESSAGE EID) const { return operator>=((::enum_message)EID); }


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


   inline operator ::iptr() const { return as_iptr(); }
   inline operator ::enum_message () const { return as_emessage(); }
   
   inline ::i64 as_i64() const;
   inline ::iptr as_iptr() const;
   inline ::i32 as_i32() const { return (::i32) i64(); }
   inline ::u32 as_u32() const { return (::u32) i64(); }
   inline ::index as_index() const { return (::index)i64(); }
   inline ::u32 as_umessage() const { return u32(); }
   inline ::enum_message as_emessage() const;
   //inline operator const char* () const;
   //inline operator enum_dialog_result () const;


   //::string as_string() const;
   //::string string() const;
   ::string as_string() const;


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

   inline bool is_text() const { return m_etype >= e_type_text; }
   inline bool is_range() const { return m_etype >= e_type_range; }
   inline bool is_integer() const { return m_etype >= 0 && m_etype < e_type_text; }


   //inline atom & operator +=(const ::scoped_string & scopedstr);

   inline operator u32hash() const
   {

      return { (((::u32)m_etype) << 24) ^ (is_text() ? u32_hash(m_str.c_str()).m_u : ((((::u32)m_u) >> 8) & 0xffffffffu)) };

   }


//#ifndef NO_TEMPLATE


   //inline string operator +(const atom & atom) const;
   inline ::string operator +(const ::ansi_character * psz) const;
   inline ::string operator +(const ::string & str) const;


//#endif

};

