// Included enum_dialog_result camilo on 2021-01-21 05:53 PM <3ThomasBorregaardSørensen
#pragma once


#include "acme/primitive/string/_u32hash.h"
#include "acme/primitive/string/string.h"
#include "acme/primitive/comparison/equals.h"
#include "acme/primitive/comparison/hash.h"
#include "acme/primitive/primitive/move.h"


enum enum_id : ::uptr;


//class atom_space;


class lparam;



// Lets (AMajor.AMinor) (BMajor.BMinor)
// compare_square(AMajor - BMajor, AMinor - BMinor)
// Maybe it is better to cache MAJOR_COMPARISON into a variable?
#define __atom_compare_square(MAJOR_COMPARISON, MINOR_COMPARISON) \
((__atom_sgn(MAJOR_COMPARISON) != 0) ? (__atom_sgn(MAJOR_COMPARISON)) : (__atom_sgn(MINOR_COMPARISON)))



#ifndef NO_TEMPLATE


#define __id_is_null_ptr(p) (!(p))


inline bool __atom_str_is_empty(const char * psz)
{

   return __id_is_null_ptr(psz) || *psz == '\0';

}

template <typename T>
int __atom_sgn(T x)
{

   return (((T) 0) < x) - (x < ((T) 0));

}


//#define __atom_safe_strcmp(a, b) ::str().compare(a, b)
//
//
//#define __atom_safe_stricmp(a, b) ::str().compare_ci(a, b)
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
      e_type_id,
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
      e_type_event,

      e_type_text = 1ull << 16,
      e_type_id_text = e_type_id | e_type_text,
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
      e_type_event_text = e_type_event | e_type_text,


   };


   union
   {

      ::iptr               m_iId;
      ::uptr               m_u;
      ::iptr               m_i;
      enum_id              m_eid;
      enum_property        m_eproperty;
      enum_factory         m_efactory;
      enum_task_tool       m_etasktool;
      enum_timer           m_etimer;
      enum_message         m_emessage;
      enum_dialog_result   m_edialogresult;
      enum_event           m_eevent;
      ::string             m_str;
      ::iptr               m_iBody;

   };

   enum_type               m_etype;

//protected:
//
//
//   friend atom_space;
//   inline atom(const char * psz, atom_space *);


public:


   inline atom();
   inline atom(enum_type etype);
   inline atom(enum_id eid);
   inline atom(ENUM_ID EID);
   inline atom(enum_message emessage);
   inline atom(ENUM_MESSAGE EMESSAGE);
   inline atom(enum_impact eimpact);
   inline atom(ENUM_IMPACT EIMPACT);
   inline atom(enum_property eproperty);
   inline atom(enum_factory efactory);
   inline atom(enum_task_tool etasktool);
   inline atom(enum_timer etimer);
   inline atom(enum_dialog_result edialogresult);
   inline atom(enum_event eevent);
   inline atom(enum_type etypeAdd, const atom & atom);
   inline atom(const atom & atom);
   atom(const char * psz);

#ifndef NO_TEMPLATE
   template < primitive_signed SIGNED >
   atom(SIGNED i);
   template < primitive_unsigned UNSIGNED >
   atom(UNSIGNED u);
   atom(const ::string & str);
   //atom(const type & type);
   atom(const ::payload & payload);
#endif // !NO_TEMPLATE
   atom(const ::lparam & lparam);
   atom(::atom && atom) { m_etype = atom.m_etype; m_u = atom.m_u; atom.m_etype = e_type_integer; atom.m_u = 0; }
   ~atom()
   {

      if (is_text())
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


   inline int compare(const atom& atom) const;
   inline bool operator == (const atom& atom) const;
   inline bool operator != (const atom & atom) const;
   inline bool operator < (const atom & atom) const;
   inline bool operator <= (const atom & atom) const;
   inline bool operator > (const atom & atom) const;
   inline bool operator >= (const atom & atom) const;


   inline int compare(const char * psz) const;
   inline bool operator == (const char * psz) const;
   inline bool operator != (const char * psz) const;
   inline bool operator < (const char * psz) const;
   inline bool operator <= (const char * psz) const;
   inline bool operator > (const char * psz) const;
   inline bool operator >= (const char * psz) const;


#ifndef NO_TEMPLATE


   inline int compare(const ::string & str) const;
   inline bool operator == (const ::string & str) const;
   inline bool operator != (const ::string & str) const;
   inline bool operator < (const ::string & str) const;
   inline bool operator <= (const ::string & str) const;
   inline bool operator > (const ::string & str) const;
   inline bool operator >= (const ::string & str) const;



   template < primitive_integral INTEGRAL >
   inline int compare(INTEGRAL i) const;
   template < primitive_integral INTEGRAL >
   inline bool operator == (INTEGRAL i) const;
   template < primitive_integral INTEGRAL >
   inline bool operator != (INTEGRAL i) const;
   template < primitive_integral INTEGRAL >
   inline bool operator < (INTEGRAL i) const;
   template < primitive_integral INTEGRAL >
   inline bool operator <= (INTEGRAL i) const;
   template < primitive_integral INTEGRAL >
   inline bool operator > (INTEGRAL i) const;
   template < primitive_integral INTEGRAL >
   inline bool operator >= (INTEGRAL i) const;


#endif // !NO_TEMPLATE


   inline int compare(::enum_id i) const;
   inline bool operator == (::enum_id eid) const;
   inline bool operator != (::enum_id eid) const;
   inline bool operator < (::enum_id eid) const;
   inline bool operator <= (::enum_id eid) const;
   inline bool operator > (::enum_id eid) const;
   inline bool operator >= (::enum_id eid) const;


   inline int compare(ENUM_ID EID) const { return compare((::enum_id)EID); }
   inline bool operator == (ENUM_ID EID) const { return operator==((::enum_id)EID); }
   inline bool operator != (ENUM_ID EID) const { return operator!=((::enum_id)EID); }
   inline bool operator < (ENUM_ID EID) const { return operator<((::enum_id)EID); }
   inline bool operator <= (ENUM_ID EID) const { return operator<=((::enum_id)EID); }
   inline bool operator > (ENUM_ID EID) const { return operator>((::enum_id)EID); }
   inline bool operator >= (ENUM_ID EID) const { return operator>=((::enum_id)EID); }


   inline int compare(::enum_message emessage) const;
   inline bool operator == (::enum_message emessage) const;
   inline bool operator != (::enum_message emessage) const;
   inline bool operator < (::enum_message emessage) const;
   inline bool operator <= (::enum_message emessage) const;
   inline bool operator > (::enum_message emessage) const;
   inline bool operator >= (::enum_message emessage) const;


   inline int compare(ENUM_MESSAGE EID) const { return compare((::enum_message)EID); }
   inline bool operator == (ENUM_MESSAGE EID) const { return operator==((::enum_message)EID); }
   inline bool operator != (ENUM_MESSAGE EID) const { return operator!=((::enum_message)EID); }
   inline bool operator < (ENUM_MESSAGE EID) const { return operator<((::enum_message)EID); }
   inline bool operator <= (ENUM_MESSAGE EID) const { return operator<=((::enum_message)EID); }
   inline bool operator > (ENUM_MESSAGE EID) const { return operator>((::enum_message)EID); }
   inline bool operator >= (ENUM_MESSAGE EID) const { return operator>=((::enum_message)EID); }


   //inline int compare(::enum_topic etopic) const;
   //inline bool operator == (::enum_topic etopic) const;
   //inline bool operator != (::enum_topic etopic) const;
   //inline bool operator < (::enum_topic etopic) const;
   //inline bool operator <= (::enum_topic etopic) const;
   //inline bool operator > (::enum_topic etopic) const;
   //inline bool operator >= (::enum_topic etopic) const;


   inline int compare(::enum_dialog_result edialogresult) const;
   inline bool operator == (::enum_dialog_result edialogresult) const;
   inline bool operator != (::enum_dialog_result edialogresult) const;
   inline bool operator < (::enum_dialog_result edialogresult) const;
   inline bool operator <= (::enum_dialog_result edialogresult) const;
   inline bool operator > (::enum_dialog_result edialogresult) const;
   inline bool operator >= (::enum_dialog_result edialogresult) const;


   inline int compare(::enum_event i) const;
   inline bool operator == (::enum_event eid) const;
   inline bool operator != (::enum_event eid) const;
   inline bool operator < (::enum_event eid) const;
   inline bool operator <= (::enum_event eid) const;
   inline bool operator > (::enum_event eid) const;
   inline bool operator >= (::enum_event eid) const;


   atom & operator = (const atom & atom);
   //atom & operator = (const char * psz);

//#ifndef NO_TEMPLATE
//
//   atom & operator = (const ::payload & payload);
//   atom & operator = (const property & prop);
//   atom & operator = (const ::string & str);
//
//
//   template < primitive_integer INTEGER >
//   atom & operator = (INTEGER i);
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


   inline operator ::iptr() const;
   inline ::i64 i64() const;
   inline ::iptr iptr() const;
   inline ::i32 i32() const { return (::i32) i64(); }
   inline ::u32 u32() const { return (::u32) i64(); }
   inline ::index index() const { return (::index)i64(); }
   inline ::u32 umessage() const { return u32(); }
   inline operator const char* () const;
   //inline operator enum_message () const;
   //inline operator enum_dialog_result () const;


   ::string as_string() const;
   //::string string() const;
   //inline string as_string() const;


   operator ::string() const { return as_string(); }


   inline bool is_null() const;
   inline bool is_empty() const;
   inline bool has_char() const;
   inline bool is_set() const { return !is_empty(); }
   
   inline void Empty();
   inline void clear();
   

   inline int CompareNoCase(const char * psz) const { return compare_ci(psz); }
   inline int compare_ci(const char * psz) const;


   inline bool begins(const char * pszPrefix) const;
   inline bool begins_ci(const char * pszPrefix) const;

   inline bool ends(const char* pszSuffix) const;
   inline bool ends_ci(const char* pszSuffix) const;

   inline bool is_text() const { return m_etype >= e_type_text; }
   inline bool is_integer() const { return m_etype >= 0 && m_etype < e_type_text; }


   //inline atom & operator +=(const char * psz);

   inline operator u32hash() const
   {

      return { (((::u32)m_etype) << 24) ^ (is_text() ? u32_hash(m_str.c_str()).m_u : ((((::u32)m_u) >> 8) & 0xffffffffu)) };

   }


#ifndef NO_TEMPLATE


   //inline string operator +(const atom & atom) const;
   inline ::string operator +(const char * psz) const;
   inline ::string operator +(const ::string & str) const;


#endif

};


inline atom::atom()
{

   m_etype = e_type_null;

   m_u = 0;

}


inline atom::atom(enum_type etype)
{

   m_etype = etype;

   m_u = 0;

}


inline atom::atom(enum_id eid) :
   m_etype(e_type_id),
   m_i((::iptr) eid) // used m_i to reset 64-bit field
{

}


inline atom::atom(ENUM_ID EID) :
   atom((::enum_id)EID) // used m_i to reset 64-bit field
{

}


inline atom::atom(enum_message emessage) :
   m_etype(e_type_message),
   m_i((::iptr)emessage) // used m_i to reset 64-bit field
{

}


inline atom::atom(ENUM_MESSAGE EMESSAGE) :
   atom((::enum_message)EMESSAGE)
{
 
}


inline atom::atom(enum_impact eimpact) :
   m_etype(e_type_impact),
   m_i((::iptr)eimpact) // used m_i to reset 64-bit field
{

}


inline atom::atom(ENUM_IMPACT EIMPACT) :
   atom((::enum_impact) EIMPACT)
{

}


inline atom::atom(enum_property eproperty) :
   m_etype(e_type_property),
   m_i((::iptr)eproperty) // used m_i to reset 64-bit field
{

}


inline atom::atom(enum_factory efactory) :
   m_etype(e_type_factory),
   m_i((::i64)efactory) // used m_i to reset 64-bit field
{

}


inline atom::atom(enum_task_tool etasktool) :
   m_etype(e_type_task_tool),
   m_i((::iptr)etasktool) // used m_i to reset 64-bit field
{

}


inline atom::atom(enum_timer etimer) :
   m_etype(e_type_timer),
   m_i((::iptr)etimer) // used m_i to reset 64-bit field
{

}






//inline atom::atom(enum_topic etopic) :
//   m_etype(e_type_subject),
//   m_etopic(etopic)
//{
//
//}


inline atom::atom(enum_dialog_result edialogresult) :
   m_etype(e_type_dialog_result),
   m_i((::iptr)edialogresult) // used m_i to reset 64-bit field
{

}


inline atom::atom(enum_event eevent) :
   m_etype(e_type_event),
   m_i((::iptr)eevent) // used m_i to reset 64-bit field
{

}



// This constructor shouldn't change the primitive type of
// the atom argument.
inline atom::atom(enum_type etypeAdd, const ::atom & atom)
{

   if (atom.is_text())
   {

      m_etype = (enum_type) (etypeAdd | e_type_text);

      ::new(&m_str) ::string(atom.m_str);

   } 
   else if (atom.is_integer())
   {

      m_etype = etypeAdd;

      m_iBody = atom.m_iBody;

   }
   else
   {

      m_etype = etypeAdd;

      m_iBody = 0;

   }

}




inline atom::atom(const atom & atom)
{

   if (atom.is_text())
   {

      m_etype = atom.m_etype;

      new(&m_str) ::string(atom.m_str);

   }
   else
   {

      m_u = atom.m_u;
      m_etype = atom.m_etype;

   }

}


//inline atom::atom(const char * psz, atom_space *)
//{
//
//   m_etype = e_type_text;
//
//   m_i = (::i64) (::iptr) psz;
//
//}

#ifndef NO_TEMPLATE

template < primitive_signed SIGNED >
inline atom::atom(SIGNED i)
{

   m_etype = e_type_integer;

   m_i = (::iptr) i;

}


template < primitive_unsigned UNSIGNED >
inline atom::atom(UNSIGNED u)
{

   m_etype = e_type_integer;

   m_u = u;

}

#endif


inline int atom::compare(const atom & atom) const
{

   auto compare = m_etype - atom.m_etype;

   return __atom_compare_square(compare, is_text() ? m_str.compare(atom.m_str) : (m_iBody - atom.m_iBody));

}


inline bool atom::operator == (const atom & atom) const
{

   return compare(atom) == 0;

}


inline bool atom::operator != (const atom & atom) const
{

   return compare(atom) != 0;

}


inline bool atom::operator < (const atom & atom) const
{

   return compare(atom) < 0;

}


inline bool atom::operator >(const atom & atom) const
{

   return compare(atom) > 0;

}


inline bool atom::operator <= (const atom & atom) const
{

   return compare(atom) <= 0;

}


inline bool atom::operator >= (const atom & atom) const
{

   return compare(atom) >= 0;

}


inline atom & atom::operator = (const atom & atom)
{

   if (atom.is_text())
   {

      if (is_text())
      {

         m_str = atom.m_str;

      }
      else
      {

         ::new(&m_str) ::string(atom.m_str);

      }

      m_etype = atom.m_etype;

   }
   else
   {

      if (is_text())
      {

         m_str.::string::to_string();

      }

      m_etype = atom.m_etype;
      m_u = atom.m_u;

   }

   return *this;

}


#ifndef NO_TEMPLATE


inline int atom::compare(const ::string & str) const
{

   return is_text() ? m_str.compare(str) : -1;

}


inline bool atom::operator == (const ::string & str) const
{

   return compare(str) == 0;

}


inline bool atom::operator != (const ::string & str) const
{

   return compare(str) != 0;

}


inline bool atom::operator < (const ::string & str) const
{

   return compare(str) < 0;

}


inline bool atom::operator <= (const ::string & str) const
{

   return compare(str) <= 0;

}


inline bool atom::operator > (const ::string & str) const
{

   return compare(str) > 0;

}


inline bool atom::operator >= (const ::string & str) const
{

   return compare(str) >= 0;

}


inline ::string atom::operator +(const char * psz) const
{

   return this->as_string() + psz;

}


inline ::string atom::operator +(const ::string & str) const
{

   return this->as_string() + str;

}


//inline void atom::as(::string & str) const
//{
//
//   str = this->string();
//
//}


#endif


inline atom::operator const char *() const
{

   return is_text() ? m_str.c_str() : nullptr;

}



//inline string atom::as_string() const
//{
//
//   return str();
//
//}


inline bool atom::is_empty() const
{

   return is_null() || m_etype == e_type_empty || (is_text() && m_str.is_empty());

}


inline CLASS_DECL_ACME iptr id_strcmp(const atom * pid1,const atom * pid2)
{

   return pid1->m_str.compare(pid2->m_str);

}


inline int atom::compare(const char * psz) const
{

   return is_text() ? m_str.compare(psz) : -1;

}


inline bool atom::operator == (const char * psz) const
{

   return compare(psz) == 0;

}


inline bool atom::operator != (const char * psz) const
{

   return compare(psz) != 0;


}

inline bool atom::operator < (const char * psz) const
{

   return compare(psz) < 0;

}


inline bool atom::operator > (const char * psz) const
{

   return compare(psz) > 0;

}



inline bool atom::operator <= (const char * psz) const
{

   return compare(psz) <= 0;

}


inline bool atom::operator >= (const char * psz) const
{

   return compare(psz) >= 0;

}


#ifndef NO_TEMPLATE


template < primitive_integral INTEGRAL >
inline int atom::compare(INTEGRAL i) const
{

   auto compare = (::i32)primitive_type() - (::i32)e_type_integer;

   return __atom_compare_square(compare, (::i64) m_i - (::i64)i);

}


template < primitive_integral INTEGRAL >
inline bool atom::operator == (INTEGRAL i) const
{

   return compare(i)== 0;

}


template < primitive_integral INTEGRAL >
inline bool atom::operator != (INTEGRAL i) const
{

   return compare(i) != 0;

}


template < primitive_integral INTEGRAL >
inline bool atom::operator < (INTEGRAL i) const
{

   return compare(i) < 0;

}


template < primitive_integral INTEGRAL >
inline bool atom::operator <= (INTEGRAL i) const
{

   return compare(i) <= 0;

}


template < primitive_integral INTEGRAL >
inline bool atom::operator > (INTEGRAL i) const
{

   return compare(i) > 0;

}


template < primitive_integral INTEGRAL >
inline bool atom::operator >= (INTEGRAL i) const
{

   return compare(i) >= 0;

}


#endif


inline int atom::compare(::enum_id eid) const
{

   auto compare = m_etype - e_type_id;

   return __atom_compare_square(compare, m_i - eid);

}


inline bool atom::operator == (::enum_id eid) const
{

   return compare(eid) == 0;

}


inline bool atom::operator != (::enum_id eid) const
{

   return compare(eid) != 0;

}


inline bool atom::operator < (::enum_id eid) const
{

   return compare(eid) < 0;

}


inline bool atom::operator <= (::enum_id eid) const
{

   return compare(eid) <= 0;

}


inline bool atom::operator > (::enum_id eid) const
{

   return compare(eid) > 0;

}


inline bool atom::operator >= (::enum_id eid) const
{

   return compare(eid) >= 0;

}


inline int atom::compare(::enum_message emessage) const
{

   auto compare = m_etype - e_type_message;

   return __atom_compare_square(compare, m_emessage - emessage);

}


inline bool atom::operator == (::enum_message emessage) const
{

   return compare(emessage) == 0;

}


inline bool atom::operator != (::enum_message emessage) const
{

   return compare(emessage) != 0;

}


inline bool atom::operator < (::enum_message emessage) const
{

   return compare(emessage) < 0;

}


inline bool atom::operator <= (::enum_message emessage) const
{

   return compare(emessage) <= 0;

}


inline bool atom::operator > (::enum_message emessage) const
{

   return compare(emessage) > 0;

}


inline bool atom::operator >= (::enum_message emessage) const
{

   return compare(emessage) >= 0;

}


//inline int atom::compare(::enum_topic etopic) const
//{
//
//   return __atom_compare_square(m_etype - e_type_subject, m_etopic - etopic);
//
//}
//
//
//inline bool atom::operator == (::enum_topic etopic) const
//{
//
//   return compare(etopic) == 0;
//
//}
//
//
//inline bool atom::operator != (::enum_topic etopic) const
//{
//
//   return compare(etopic) != 0;
//
//}
//
//
//inline bool atom::operator < (::enum_topic etopic) const
//{
//
//   return compare(etopic) < 0;
//
//}
//
//
//inline bool atom::operator <= (::enum_topic etopic) const
//{
//
//   return compare(etopic) <= 0;
//
//}
//
//
//inline bool atom::operator > (::enum_topic etopic) const
//{
//
//   return compare(etopic) > 0;
//
//}
//
//
//inline bool atom::operator >= (::enum_topic etopic) const
//{
//
//   return compare(etopic) >= 0;
//
//}




inline int atom::compare(::enum_dialog_result edialogresult) const
{

   auto compare = m_etype - e_type_dialog_result;

   return __atom_compare_square(compare, m_edialogresult - edialogresult);

}


inline bool atom::operator == (::enum_dialog_result edialogresult) const
{

   return compare(edialogresult) == 0;

}


inline bool atom::operator != (::enum_dialog_result edialogresult) const
{

   return compare(edialogresult) != 0;

}


inline bool atom::operator < (::enum_dialog_result edialogresult) const
{

   return compare(edialogresult) < 0;

}


inline bool atom::operator <= (::enum_dialog_result edialogresult) const
{

   return compare(edialogresult) <= 0;

}


inline bool atom::operator > (::enum_dialog_result edialogresult) const
{

   return compare(edialogresult) > 0;

}


inline bool atom::operator >= (::enum_dialog_result edialogresult) const
{

   return compare(edialogresult) >= 0;

}



inline int atom::compare(::enum_event eid) const
{

   auto compare = m_etype - e_type_id;

   return __atom_compare_square(compare, m_i - eid);

}


inline bool atom::operator == (::enum_event eid) const
{

   return compare(eid) == 0;

}


inline bool atom::operator != (::enum_event eid) const
{

   return compare(eid) != 0;

}


inline bool atom::operator < (::enum_event eid) const
{

   return compare(eid) < 0;

}


inline bool atom::operator <= (::enum_event eid) const
{

   return compare(eid) <= 0;

}


inline bool atom::operator > (::enum_event eid) const
{

   return compare(eid) > 0;

}


inline bool atom::operator >= (::enum_event eid) const
{

   return compare(eid) >= 0;

}


inline atom::operator ::iptr () const
{

   return iptr();

}


inline ::i64 atom::i64() const
{

   return primitive_type() == e_type_integer ? m_i : 0x8000000000000000ll;

}


inline ::iptr atom::iptr() const
{

   return primitive_type() == e_type_integer ? m_i : INTPTR_MIN;

}


//inline atom::operator enum_message () const
//{
//
//   return m_etype == e_type_message ? m_emessage : e_message_undefined;
//
//}
//
//
//inline atom::operator enum_dialog_result () const
//{
//
//   return m_etype == e_type_dialog_result ? m_edialogresult : e_dialog_result_none;
//
//}


inline bool atom::is_null() const
{

   return m_etype == e_type_null || (is_text() && m_str.is_empty());

}


inline bool atom::has_char() const
{

   return is_text() && m_str.has_char();

}


inline void atom::Empty()
{

   m_etype  = e_type_empty;

   m_i      = 0;

}


inline void atom::clear()
{

   m_etype = e_type_null;

}


//inline CLASS_DECL_ACME atom & atom::operator += (const char * psz) { return operator = (string(*this) + string(psz)); }


inline int atom::compare_ci(const char * psz) const
{

   if(m_str.is_empty())
   {

      if (::is_empty(psz))
      {

         return 0;

      }
      else
      {

         return -1;

      }

   }
   else if(::is_empty(psz))
   {

      return 1;

   }
   else
   {

      return m_str.compare_ci(psz);

   }

}


template < >
inline bool EqualElements< atom >(atom element1, atom element2)
{

   return element1 == element2;

}



//inline string CLASS_DECL_ACME operator + (const char * psz, const ::atom & atom);

//
//namespace acme
//{
//
//   CLASS_DECL_ACME ::atom atom(const char* psz);
//
//}
//
//
//class CLASS_DECL_ACME __atom :
//public atom
//{
//
//public:
//
//   using atom::atom;
//
//};


inline bool atom::begins(const char * pszCandidatePrefix) const
{

   if (__atom_str_is_empty(pszCandidatePrefix))
   {

      return true;

   }

   if (is_empty() || is_integer())
   {

      return false;

   }
   else if (is_text())
   {

      return m_str.begins(pszCandidatePrefix);

   }
   else
   {

      throw "Unexpected::atom m_etype";

      return false;

   }

}


inline bool atom::begins_ci(const char * pszCandidatePrefix) const
{

   if (__atom_str_is_empty(pszCandidatePrefix))
   {

      return true;

   }

   if (is_empty())
   {

      return false;

   }
   else if (is_text())
   {

      return m_str.begins_ci(pszCandidatePrefix);

   }
   else
   {

      throw "Unexpected ::atom m_etype";

      return false;

   }

}


inline bool atom::ends(const char* pszCandidateSuffix) const
{

   if (__atom_str_is_empty(pszCandidateSuffix))
   {

      return true;

   }

   if (is_empty() || is_integer())
   {

      return false;

   }
   else if (is_text())
   {

      return m_str.ends(pszCandidateSuffix);

   }
   else
   {

      throw "Unexpected::atom m_etype";

      return false;

   }

}


inline bool atom::ends_ci(const char* pszCandidateSuffix) const
{

   if (__atom_str_is_empty(pszCandidateSuffix))
   {

      return true;

   }

   if (is_empty())
   {

      return false;

   }
   else if (is_text())
   {

      return m_str.ends_ci(pszCandidateSuffix);

   }
   else
   {

      throw "Unexpected ::atom m_etype";

      return false;

   }

}






inline void from_string(::atom & atom, const ansichar * psz)
{

   atom = psz;

}


inline atom::atom(const char * psz) :
   m_str(psz)
{

   m_etype = e_type_text;

   //m_str.::string::string(psz);

}


inline atom::atom(const ::lparam & lparam)
{

   m_etype = e_type_integer;

   m_u = lparam.m_lparam;

}

#ifndef NO_TEMPLATE
inline atom::atom(const ::string& str) :
   m_str(str)
{

   m_etype = e_type_text;

}
#endif

//template < typename CHAR >
//inline string_base < CHAR >::string_base(const ::atom & atom) :
//   string_base(atom.string())
//{
//
//
//}


//template < typename CHAR >
//string_base < CHAR > & string_base < CHAR >::operator+=(const ::atom & atom)
//{
//
//   return append(atom);
//
//}
//
//
//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR > string_base < TYPE_CHAR >::operator +(const ::atom & atom) const
//{
//
//   string_base < TYPE_CHAR > str(*this);
//
//   str += atom;
//
//   return str;
//
//}




inline ::string operator+(const char * psz, const ::atom & atom)
{

   return string(psz) + string(atom);

}


template < primitive_character CHARACTER >
inline ::string_base < CHARACTER > & operator+=(::string_base < CHARACTER > & str, const ::atom & atom)
{

   return str.operator += ((::string) atom);

}

