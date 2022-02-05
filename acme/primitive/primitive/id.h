// Included enum_dialog_result camilo on 2021-01-21 05:53 PM <3ThomasBorregaardSørensen
#pragma once



#include "acme/primitive/comparison/equals.h"
#include "acme/primitive/comparison/hash.h"
#include "acme/constant/thread.h"


enum enum_id : ::u64;


class id_space;


class lparam;



#ifndef NO_TEMPLATE


#define __id_is_null_ptr(p) (!(p))


inline bool __id_str_is_empty(const char * psz)
{

   return __id_is_null_ptr(psz) || *psz == '\0';

}

template <typename T>
int __id_sgn(T x)
{

   return (((T) 0) < x) - (x < ((T) 0));

}


template <typename A, typename B>
int __id_compare_square(A a, B b)
{

   auto aSgn = __id_sgn(a);

   return aSgn ? aSgn : __id_sgn(b);

}


#define __id_safe_strcmp(a, b) ::str::compare(a, b)


#define __id_safe_stricmp(a, b) ::str::compare_ci(a, b)


#define __id_str_begins(a, b) ::str::begins(a, b)


#define __id_str_begins_ci(a, b) ::str::begins_ci(a, b)


#else


#define __id_sgn(x) ((0 < (x)) - ((x) < 0))


#define __id_is_null_ptr(p) (!(p))


#define __id_str_is_empty(psz) (__id_is_null_ptr(psz) || *psz == '\0')


// Lets (AMajor.AMinor) (BMajor.BMinor)
// compare_square(AMajor - BMajor, AMinor - BMinor)
#define __id_compare_square(MAJOR_COMPARISON, MINOR_COMPARISON) \
(__id_sgn(MAJOR_COMPARISON) != 0 ? (__id_sgn(MAJOR_COMPARISON)) : (__id_sgn(MINOR_COMPARISON)))


inline int __id_safe_strcmp(const char * a, const char * b)
{

   if (__id_str_is_empty(a))
   {

      if (__id_str_is_empty(b))
      {

         return true;

      }
      else
      {

         return -1;

      }

   }
   else if(__id_str_is_empty(b))
   {

      return 1;

   }
   else
   {

      return strcmp(a, b);

   }

}


inline int __id_safe_stricmp(const char * a, const char * b)
{

   if (__id_str_is_empty(a))
   {

      if (__id_str_is_empty(b))
      {

         return true;

      }
      else
      {

         return -1;

      }

   }
   else if (__id_str_is_empty(b))
   {

      return 1;

   }
   else
   {

      return stricmp(a, b);

   }

}

inline bool __id_str_begins(const char * a, const char * b)
{

   if (__id_str_is_empty(a))
   {

      if (__id_str_is_empty(b))
      {

         return true;

      }
      else
      {

         return false;

      }

   }
   else if (__id_str_is_empty(b))
   {

      return true;

   }
   else
   {

      return strncmp(a, b, strlen(b));

   }

}


inline bool __id_str_begins_ci(const char * a, const char * b)
{

   if (__id_str_is_empty(a))
   {

      if (__id_str_is_empty(b))
      {

         return true;

      }
      else
      {

         return false;

      }

   }
   else if (__id_str_is_empty(b))
   {

      return true;

   }
   else
   {

      return strnicmp(a, b, strlen(b));

   }

}


#endif




struct id_all
{

   ::i64             m_iBody;
   ::i64             m_iType;

};


class CLASS_DECL_ACME id
{
public:


   enum enum_type : ::i64
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

      e_type_text = 1ull << 32,
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


   };


   union
   {

      ::i64             m_iId;
      const char *      m_pszId;

      struct
      {

         union
         {

            ::u64                m_u;
            ::i64                m_i;
            const char *         m_psz;
            enum_id              m_eid;
            enum_property        m_eproperty;
            enum_factory         m_efactory;
            enum_task_tool       m_etasktool;
            enum_timer           m_etimer;
            enum_message         m_emessage;
            //enum_topic         m_etopic;
            enum_dialog_result   m_edialogresult;
         };

         enum_type                  m_etype;


      };

      struct
      {

         ::i64             m_iBody;
         ::i64             m_iType;

      };

      id_all                  m_all;

   };

protected:


   friend id_space;
   inline id(const char * psz, id_space *);


public:


   inline id();
   inline id(enum_type etype);
   inline id(enum_id eid);
   inline id(enum_property eproperty);
   inline id(enum_factory efactory);
   inline id(enum_task_tool etasktool);
   inline id(enum_timer etimer);
   inline id(enum_message emessage);
   //inline id(enum_topic etopic);
   inline id(enum_dialog_result edialogresult);
   inline id(enum_type etype, ::i64 i);
   inline id(const id & id);
   id(const char * psz);

#ifndef NO_TEMPLATE
   template < primitive_signed SIGNED >
   id(SIGNED i);
   template < primitive_unsigned UNSIGNED >
   id(UNSIGNED u);
   id(const ::string & str);
   id(const type & type);
   id(const ::payload & payload);
#endif // !NO_TEMPLATE
   id(const ::lparam & lparam);
   id(::id && id) { m_all = id.m_all; id.m_all = {}; }


   void raw_set(const char * psz);

#ifndef NO_TEMPLATE
   string str() const;
#endif

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


   enum_type compounded_type(enum_type etype) const
   {

      return m_iType < 0 ? m_etype : (enum_type)((m_iType & ~0xffffffffll) | (int) etype);

   }


   ::id compounded(enum_type etype) const
   {

      return {compounded_type(etype), m_i};

   }


   void set_compounded_type(enum_type etype)
   {

      m_etype = compounded_type(etype);

   }

   bool _is_compounded(enum_type etype) const { return (m_etype & 0xffffffff) == etype;}



   bool is_message() const { return m_etype == e_type_message; }


   bool is_command() const { return _is_compounded(e_type_command); }
   bool is_command_probe() const { return _is_compounded(e_type_command_probe); }
   bool is_has_command_handler() const { return _is_compounded(e_type_has_command_handler); }
   bool is_update() const { return _is_compounded(e_type_update); }


   inline int compare(const id& id) const;
   inline bool operator == (const id& id) const;
   inline bool operator != (const id & id) const;
   inline bool operator < (const id & id) const;
   inline bool operator <= (const id & id) const;
   inline bool operator > (const id & id) const;
   inline bool operator >= (const id & id) const;


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


   inline int compare(::enum_message emessage) const;
   inline bool operator == (::enum_message emessage) const;
   inline bool operator != (::enum_message emessage) const;
   inline bool operator < (::enum_message emessage) const;
   inline bool operator <= (::enum_message emessage) const;
   inline bool operator > (::enum_message emessage) const;
   inline bool operator >= (::enum_message emessage) const;


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

   id & operator = (const id & id);
   id & operator = (const char * psz);

#ifndef NO_TEMPLATE

   id & operator = (const ::payload & payload);
   id & operator = (const property & prop);
   id & operator = (const ::string & str);


   template < primitive_integer INTEGER >
   id & operator = (INTEGER i);
   template < primitive_natural NATURAL >
   id & operator = (NATURAL u);

#endif // !NO_TEMPLATE


   id & operator = (const enum_id & eid);
   id & operator = (const enum_property & eproperty);
   id & operator = (const enum_factory & efactory);
   id & operator = (const enum_task_tool & etasktool);
   id & operator = (const enum_timer & etimer);
   id & operator = (const enum_message & emessage);
   //id & operator = (const enum_topic & etopic);
   id & operator = (const enum_dialog_result & edialogresult);


#ifndef NO_TEMPLATE

   inline ansistring to_string_base() const { return to_string(); }

#endif

   inline operator ::i64() const;
   inline ::i64 i64() const;
   inline ::i32 i32() const { return (::i32) i64(); }
   inline ::u32 u32() const { return (::u32) i64(); }
   inline ::index index() const { return (::index)i64(); }
   inline ::u32 umessage() const { return u32(); }
   inline operator const char* () const;
   //inline operator enum_message () const;
   //inline operator enum_dialog_result () const;


#ifndef NO_TEMPLATE


   inline void to_string(string & str) const;
   inline string to_string() const;
   //inline string __string() const;

#endif


   inline bool is_null() const;
   inline bool is_empty() const;
   inline bool has_char() const;
   inline void empty();
   inline void clear();


   inline iptr CompareNoCase(const char * psz) const { return compare_ci(psz); }
   inline iptr compare_ci(const char * psz) const;


   inline bool begins(const char * pszPrefix) const;
   inline bool begins_ci(const char * pszPrefix) const;

   inline bool is_text() const { return m_etype >= e_type_text; }
   inline bool is_integer() const { return m_etype >= 0 && m_etype < e_type_text; }


   //inline id & operator +=(const char * psz);



#ifndef NO_TEMPLATE


   //inline string operator +(const id & id) const;
   inline string operator +(const char * psz) const;
   inline string operator +(const ::string & str) const;


#endif

};


inline id::id()
{

   m_etype = e_type_null;

}


inline id::id(enum_type etype)
{

   if(etype == e_type_null)
   {

      m_etype = e_type_null;

   }
   else if(etype == e_type_empty)
   {

      m_etype = e_type_empty;

   }
   else if(etype == e_type_integer)
   {

      m_etype = e_type_integer;

      m_i = 0;

   }
   else if(etype == e_type_text)
   {

      operator = ("");

   }

}


inline id::id(enum_id eid) :
   m_etype(e_type_id),
   m_eid(eid) // used m_i to reset 64-bit field
{

}


inline id::id(enum_property eproperty) :
   m_etype(e_type_property),
   m_eproperty(eproperty) // used m_i to reset 64-bit field
{

}


inline id::id(enum_factory efactory) :
   m_etype(e_type_factory),
   m_efactory(efactory) // used m_i to reset 64-bit field
{

}


inline id::id(enum_task_tool etasktool) :
   m_etype(e_type_task_tool),
   m_etasktool(etasktool) // used m_i to reset 64-bit field
{

}


inline id::id(enum_timer etimer) :
   m_etype(e_type_timer),
   m_etimer(etimer)
{

}



inline id::id(enum_message emessage) :
   m_etype(e_type_message),
   m_emessage(emessage)
{

}


//inline id::id(enum_topic etopic) :
//   m_etype(e_type_subject),
//   m_etopic(etopic)
//{
//
//}


inline id::id(enum_dialog_result edialogresult) :
   m_etype(e_type_dialog_result),
   m_edialogresult(edialogresult)
{

}


inline id::id(enum_type etype, ::i64 i) :
   m_etype(etype),
   m_i(i)
{

}


inline id::id(const id & id)
{

   m_all = id.m_all;

}


inline id::id(const char * psz, id_space *)
{

   m_etype = e_type_text;

   m_i = (::i64) (::iptr) psz;

}

#ifndef NO_TEMPLATE

template < primitive_signed SIGNED >
inline id::id(SIGNED i)
{

   m_etype = e_type_integer;

   m_i = i;

}


template < primitive_unsigned UNSIGNED >
inline id::id(UNSIGNED u)
{

   m_etype = e_type_integer;

   m_u = u;

}

#endif


inline int id::compare(const id & id) const
{

   return __id_compare_square(m_iType - id.m_iType, m_iBody - id.m_iBody);

}


inline bool id::operator == (const id & id) const
{

   return compare(id) == 0;

}


inline bool id::operator != (const id & id) const
{

   return compare(id) != 0;

}


inline bool id::operator < (const id & id) const
{

   return compare(id) < 0;

}


inline bool id::operator >(const id & id) const
{

   return compare(id) > 0;

}


inline bool id::operator <= (const id & id) const
{

   return compare(id) <= 0;

}


inline bool id::operator >= (const id & id) const
{

   return compare(id) >= 0;

}


inline id & id::operator = (const id & id)
{

   m_all         = id.m_all;

   return *this;

}


#ifndef NO_TEMPLATE


inline int id::compare(const ::string & str) const
{

   return __id_compare_square(primitive_type() - e_type_text, ansi_compare(m_psz, str.c_str()));

}


inline bool id::operator == (const ::string & str) const
{

   return compare(str) == 0;

}


inline bool id::operator != (const ::string & str) const
{

   return compare(str) != 0;

}


inline bool id::operator < (const ::string & str) const
{

   return compare(str) < 0;

}


inline bool id::operator <= (const ::string & str) const
{

   return compare(str) <= 0;

}


inline bool id::operator > (const ::string & str) const
{

   return compare(str) > 0;

}


inline bool id::operator >= (const ::string & str) const
{

   return compare(str) >= 0;

}


#endif


inline id::operator const char *() const
{

   return primitive_type() == e_type_text ? m_psz : nullptr;

}


#ifndef NO_TEMPLATE

inline void id::to_string(string & strRet) const
{

   strRet =  str();

}


inline string id::to_string() const
{

   return str();

}

#endif

//inline string id::__string() const
//{
//
//   return str();
//
//}


inline bool id::is_empty() const
{

   return is_null() || m_etype == e_type_empty || (primitive_type() == e_type_text && *m_psz == '\0');

}


inline CLASS_DECL_ACME iptr id_strcmp(const id * pid1,const id * pid2)
{

   return strcmp(pid1->m_psz,pid2->m_psz);

}


inline void id::raw_set(const char * psz)
{

   m_etype     = e_type_text;
   m_i         = (::i64) (::iptr) psz;

}


#ifndef NO_TEMPLATE


inline string id::str() const
{

   if(m_etype == e_type_null)
   {

      return "(null)";

   }
   else if(m_etype == e_type_empty)
   {

      return "(empty)";

   }
   else if(is_text())
   {

      return m_psz;

   }
   else if(is_integer())
   {

      return __string(m_i);

   }
   else
   {

      return string("(type:") + __string(m_iType) + ",body:" + __string(m_iBody) + ")";

   }

}


#endif


inline int id::compare(const char * psz) const
{

   return __id_compare_square(primitive_type() - e_type_text, __id_safe_strcmp(m_psz, psz));

}


inline bool id::operator == (const char * psz) const
{

   return compare(psz) == 0;

}


inline bool id::operator != (const char * psz) const
{

   return compare(psz) != 0;


}

inline bool id::operator < (const char * psz) const
{

   return compare(psz) < 0;

}


inline bool id::operator > (const char * psz) const
{

   return compare(psz) > 0;

}



inline bool id::operator <= (const char * psz) const
{

   return compare(psz) <= 0;

}


inline bool id::operator >= (const char * psz) const
{

   return compare(psz) >= 0;

}


#ifndef NO_TEMPLATE


template < primitive_integral INTEGRAL >
inline int id::compare(INTEGRAL i) const
{

   return __id_compare_square((::i32)primitive_type() - (::i32)e_type_integer, (::i64) m_i - (::i64)i);

}


template < primitive_integral INTEGRAL >
inline bool id::operator == (INTEGRAL i) const
{

   return compare(i)== 0;

}


template < primitive_integral INTEGRAL >
inline bool id::operator != (INTEGRAL i) const
{

   return compare(i) != 0;

}


template < primitive_integral INTEGRAL >
inline bool id::operator < (INTEGRAL i) const
{

   return compare(i) < 0;

}


template < primitive_integral INTEGRAL >
inline bool id::operator <= (INTEGRAL i) const
{

   return compare(i) <= 0;

}


template < primitive_integral INTEGRAL >
inline bool id::operator > (INTEGRAL i) const
{

   return compare(i) > 0;

}


template < primitive_integral INTEGRAL >
inline bool id::operator >= (INTEGRAL i) const
{

   return compare(i) >= 0;

}


#endif


inline int id::compare(::enum_id eid) const
{

   return __id_compare_square(m_etype - e_type_id, m_i - eid);

}


inline bool id::operator == (::enum_id eid) const
{

   return compare(eid) == 0;

}


inline bool id::operator != (::enum_id eid) const
{

   return compare(eid) != 0;

}


inline bool id::operator < (::enum_id eid) const
{

   return compare(eid) < 0;

}


inline bool id::operator <= (::enum_id eid) const
{

   return compare(eid) <= 0;

}


inline bool id::operator > (::enum_id eid) const
{

   return compare(eid) > 0;

}


inline bool id::operator >= (::enum_id eid) const
{

   return compare(eid) >= 0;

}


inline int id::compare(::enum_message emessage) const
{

   return __id_compare_square(m_etype - e_type_message, m_emessage - emessage);

}


inline bool id::operator == (::enum_message emessage) const
{

   return compare(emessage) == 0;

}


inline bool id::operator != (::enum_message emessage) const
{

   return compare(emessage) != 0;

}


inline bool id::operator < (::enum_message emessage) const
{

   return compare(emessage) < 0;

}


inline bool id::operator <= (::enum_message emessage) const
{

   return compare(emessage) <= 0;

}


inline bool id::operator > (::enum_message emessage) const
{

   return compare(emessage) > 0;

}


inline bool id::operator >= (::enum_message emessage) const
{

   return compare(emessage) >= 0;

}


//inline int id::compare(::enum_topic etopic) const
//{
//
//   return __id_compare_square(m_etype - e_type_subject, m_etopic - etopic);
//
//}
//
//
//inline bool id::operator == (::enum_topic etopic) const
//{
//
//   return compare(etopic) == 0;
//
//}
//
//
//inline bool id::operator != (::enum_topic etopic) const
//{
//
//   return compare(etopic) != 0;
//
//}
//
//
//inline bool id::operator < (::enum_topic etopic) const
//{
//
//   return compare(etopic) < 0;
//
//}
//
//
//inline bool id::operator <= (::enum_topic etopic) const
//{
//
//   return compare(etopic) <= 0;
//
//}
//
//
//inline bool id::operator > (::enum_topic etopic) const
//{
//
//   return compare(etopic) > 0;
//
//}
//
//
//inline bool id::operator >= (::enum_topic etopic) const
//{
//
//   return compare(etopic) >= 0;
//
//}




inline int id::compare(::enum_dialog_result edialogresult) const
{

   return __id_compare_square(m_etype - e_type_dialog_result, m_edialogresult - edialogresult);

}


inline bool id::operator == (::enum_dialog_result edialogresult) const
{

   return compare(edialogresult) == 0;

}


inline bool id::operator != (::enum_dialog_result edialogresult) const
{

   return compare(edialogresult) != 0;

}


inline bool id::operator < (::enum_dialog_result edialogresult) const
{

   return compare(edialogresult) < 0;

}


inline bool id::operator <= (::enum_dialog_result edialogresult) const
{

   return compare(edialogresult) <= 0;

}


inline bool id::operator > (::enum_dialog_result edialogresult) const
{

   return compare(edialogresult) > 0;

}


inline bool id::operator >= (::enum_dialog_result edialogresult) const
{

   return compare(edialogresult) >= 0;

}


inline id::operator ::i64 () const
{

   return i64();

}


inline ::i64 id::i64() const
{

   return primitive_type() == e_type_integer ? m_i : 0x8000000000000000ll;

}


//inline id::operator enum_message () const
//{
//
//   return m_etype == e_type_message ? m_emessage : e_message_undefined;
//
//}
//
//
//inline id::operator enum_dialog_result () const
//{
//
//   return m_etype == e_type_dialog_result ? m_edialogresult : e_dialog_result_none;
//
//}


inline bool id::is_null() const
{

   return m_etype == e_type_null || (primitive_type() == e_type_text && m_psz == nullptr);

}


inline bool id::has_char() const
{

   return primitive_type() == e_type_text && m_psz != nullptr && *m_psz != '\0';

}


inline void id::empty()
{

   m_etype  = e_type_empty;

   m_i      = 0;

}


inline void id::clear()
{

   m_etype = e_type_null;

}


//inline CLASS_DECL_ACME id & id::operator += (const char * psz) { return operator = (string(*this) + string(psz)); }


inline iptr id::compare_ci(const char * psz) const
{

   if(m_psz == nullptr)
   {

      if (psz == nullptr)
      {

         return 0;

      }
      else
      {

         return -1;

      }

   }
   else if(psz == nullptr)
   {

      return 1;

   }
   else
   {

      return __id_safe_stricmp(m_psz,psz);

   }

}


template < >
inline bool EqualElements< id >(id element1, id element2)
{

   return element1 == element2;

}


#ifndef NO_TEMPLATE


template < >
inline uptr uptr_hash< const id & >(const id & key)
{

   return ((((::u32)(uptr)key.m_iType) << 24) & 0xffffffffu) | ((((::u32)(uptr)key.m_iBody) >> 8) & 0xffffffffu);

}


template < >
inline uptr uptr_hash< id>(id key)
{

   return uptr_hash<const id & > ((const id &)key);

}


#endif

//inline string CLASS_DECL_ACME operator + (const char * psz, const ::id & id);


namespace acme
{

   CLASS_DECL_ACME ::id id(const char* psz);

}


class CLASS_DECL_ACME __id :
public id
{

public:

   using id::id;

};






inline bool id::begins(const char * pszCandidatePrefix) const
{

   if (__id_str_is_empty(pszCandidatePrefix))
   {

      return true;

   }

   if (is_empty() || is_integer())
   {

      return false;

   }
   else if (is_text())
   {

      return __id_str_begins(m_psz, pszCandidatePrefix);

   }
   else
   {

      throw "Unexpected::id m_etype";

      return false;

   }

}


inline bool id::begins_ci(const char * pszCandidatePrefix) const
{

   if (__id_str_is_empty(pszCandidatePrefix))
   {

      return true;

   }

   if (is_empty())
   {

      return false;

   }
   else if (is_text())
   {

      return strncmp(m_psz, pszCandidatePrefix, strlen(pszCandidatePrefix)) == 0;

   }
   else
   {

      throw "Unexpected ::id m_etype";

      return false;

   }

}


