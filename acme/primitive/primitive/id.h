#pragma once


#include "acme/primitive/comparison/equals.h"
#include "acme/primitive/comparison/hash.h"


enum e_id : ::u64;


template <typename T>
int sgn(T val)
{
   return (((T) 0) < val) - (val < ((T) 0));
}


// Lets (AMajor.AMinor) (BMajor.BMinor)
// compare_square(AMajor - BMajor, AMinor - BMinor)
#define __COMPARE_SQUARE(MAJOR_COMPARISON, MINOR_COMPARISON) \
((MAJOR_COMPARISON) != 0 ? ::sgn(MAJOR_COMPARISON) : ::sgn(MINOR_COMPARISON))


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


      e_type_empty = -1,

      e_type_null = 0,

      e_type_integer = 1,
      e_type_id,
      e_type_factory,
      e_type_task_tool,
      e_type_timer,
      e_type_message,
      e_type_property,

      e_type_command = 1 << 16,
      e_type_command_integer = e_type_command,

      e_type_command_probe = 1 << 20,
      e_type_command_probe_integer = e_type_command_probe,

      e_type_has_command_handler = 1 << 24,
      e_type_has_command_handler_integer = e_type_has_command_handler,

      e_type_update = 1 << 28,
      e_type_update_integer = e_type_update,

      e_type_text = 1ull << 32,
      e_type_command_text = e_type_text | e_type_command,
      e_type_update_text = e_type_text | e_type_update,
      e_type_has_command_handler_text = e_type_text | e_type_has_command_handler,
      e_type_command_probe_text = e_type_text | e_type_command_probe_integer,


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
            e_id                 m_eid;
            enum_property        m_eproperty;
            enum_factory         m_efactory;
            enum_task_tool       m_etasktool;
            enum_timer           m_etimer;
            enum_message         m_emessage;
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
   inline id(e_id eid);
   inline id(enum_property eproperty);
   inline id(enum_factory efactory);
   inline id(enum_task_tool etasktool);
   inline id(enum_timer etimer);
   inline id(enum_message emessage);
   inline id(enum_type etype, ::i64 i);
   inline id(const id & id);
   id(const char * psz);
   template < primitive_integer INTEGER >
   id(INTEGER i);
   template < primitive_natural NATURAL >
   id(NATURAL n);
   id(const ::lparam & lparam);
   id(const string & str);
   id(const ::payload & payload);
   id(const type & type);
   id(::id && id) { m_all = id.m_all; id.m_all = {}; }


   void raw_set(const char * psz);


   string str() const;


   enum_type primitive_type() const
   {

      if(m_etype <= 0)
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

      return (enum_type)((m_iType & ~0xffff0000) | (int) etype);

   }


   ::id compounded(enum_type etype) const
   {

      return {compounded_type(etype), m_i};

   }


   void set_compounded_type(enum_type etype)
   {

      m_etype = compounded_type(etype);

   }

   bool _is_compounded(enum_type etype) const { return (m_etype & etype) != 0;}



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


   inline int compare(const string & str) const;
   inline bool operator == (const string & str) const;
   inline bool operator != (const string & str) const;
   inline bool operator < (const string & str) const;
   inline bool operator <= (const string & str) const;
   inline bool operator > (const string & str) const;
   inline bool operator >= (const string & str) const;


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


   inline int compare(::e_id i) const;
   inline bool operator == (::e_id eid) const;
   inline bool operator != (::e_id eid) const;
   inline bool operator < (::e_id eid) const;
   inline bool operator <= (::e_id eid) const;
   inline bool operator > (::e_id eid) const;
   inline bool operator >= (::e_id eid) const;


   inline int compare(::enum_message emessage) const;
   inline bool operator == (::enum_message emessage) const;
   inline bool operator != (::enum_message emessage) const;
   inline bool operator < (::enum_message emessage) const;
   inline bool operator <= (::enum_message emessage) const;
   inline bool operator > (::enum_message emessage) const;
   inline bool operator >= (::enum_message emessage) const;


   id & operator = (const ::payload & payload);
   id & operator = (const property & prop);
   id & operator = (const id & id);
   id & operator = (const char * psz);
   id & operator = (const string & str);
   template < primitive_integer INTEGER >
   id & operator = (INTEGER i);
   template < primitive_natural NATURAL >
   id & operator = (NATURAL u);
   id & operator = (const enum_property & eproperty);
   id & operator = (const enum_factory & efactory);
   id & operator = (const enum_task_tool & etasktool);
   id & operator = (const enum_timer & etimer);
   id & operator = (const enum_message & emessage);


   inline ansistring to_string_base() const { return to_string(); }
   inline operator ::i64() const;
   inline ::i64 i64() const;
   inline ::i32 i32() const { return (::i32) i64(); }
   inline ::u32 u32() const { return (::u32) i64(); }
   inline ::index index() const { return (::index)i64(); }
   inline ::u32 umessage() const { return u32(); }
   inline operator const char* () const;


   inline void to_string(string & str) const;
   inline string to_string() const;
   inline string __string() const;


   inline bool is_null() const;
   inline bool is_empty() const;
   inline bool has_char() const;
   inline void empty();
   inline void clear();


   inline iptr CompareNoCase(const char * psz) const { return compare_ci(psz); }
   inline iptr compare_ci(const char * psz) const;


   inline bool begins(const string & strPrefix) const;
   inline bool begins_ci(const string & strPrefix) const;


   inline bool is_text() const { return m_etype >= e_type_text; }
   inline bool is_integer() const { return m_etype > 0 && m_etype < e_type_text; }


   inline id & operator +=(const char * psz);

   inline id operator +(const id & id) const;
   inline string operator +(const char * psz) const;
   inline string operator +(const string & str) const;


};


inline id::id()
{

   m_all = {};

}


inline id::id(enum_type etype) :
   ::id()
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

   }
   else if(etype == e_type_text)
   {

      operator = ("");

   }

}


inline id::id(e_id eid) :
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


template < primitive_integer INTEGER >
inline id::id(INTEGER i)
{

   m_etype = e_type_integer;

   m_i = i;

}


template < primitive_natural UNSIGNED >
inline id::id(UNSIGNED u)
{

   m_etype = e_type_integer;

   m_u = u;

}


inline id::id(const ::lparam& lparam)
{

   m_etype = e_type_integer;

   m_u = lparam.m_lparam;

}


inline int id::compare(const id & id) const
{

   return __COMPARE_SQUARE(m_iType - id.m_iType, m_iBody - id.m_iBody);

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


inline int id::compare(const string & str) const
{

   return __COMPARE_SQUARE(primitive_type() - e_type_text, ansi_compare(m_psz, str.c_str()));

}


inline bool id::operator == (const string & str) const
{

   return compare(str) == 0;

}


inline bool id::operator != (const string & str) const
{

   return compare(str) != 0;

}


inline bool id::operator < (const string & str) const
{

   return compare(str) < 0;

}


inline bool id::operator <= (const string & str) const
{

   return compare(str) <= 0;

}


inline bool id::operator > (const string & str) const
{

   return compare(str) > 0;

}


inline bool id::operator >= (const string & str) const
{

   return compare(str) >= 0;

}


inline id::operator const char *() const
{

   return primitive_type() == e_type_text ? m_psz : nullptr;

}


inline void id::to_string(string & strRet) const
{

   strRet =  str();

}


inline string id::to_string() const
{

   return str();

}


inline string id::__string() const
{

   return str();

}


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

      return __str(m_i);

   }
   else
   {

      return string("(type:") + __str(m_iType) + ",body:" + __str(m_iBody) + ")";

   }

}


inline int id::compare(const char * psz) const
{

   return __COMPARE_SQUARE(primitive_type() - e_type_text, ansi_compare(m_psz, psz));

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


template < primitive_integral INTEGRAL >
inline int id::compare(INTEGRAL i) const
{

   return __COMPARE_SQUARE(primitive_type() - e_type_integer, m_i - i);

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


inline int id::compare(::e_id eid) const
{

   return __COMPARE_SQUARE(m_etype - e_type_id, m_i - eid);

}


inline bool id::operator == (::e_id eid) const
{

   return compare(eid) == 0;

}


inline bool id::operator != (::e_id eid) const
{

   return compare(eid) != 0;

}


inline bool id::operator < (::e_id eid) const
{

   return compare(eid) < 0;

}


inline bool id::operator <= (::e_id eid) const
{

   return compare(eid) <= 0;

}


inline bool id::operator > (::e_id eid) const
{

   return compare(eid) > 0;

}


inline bool id::operator >= (::e_id eid) const
{

   return compare(eid) >= 0;

}


inline int id::compare(::enum_message emessage) const
{

   return __COMPARE_SQUARE(m_etype - e_type_message, m_i - emessage);

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


inline id::operator ::i64 () const
{

   return i64();

}


inline ::i64 id::i64() const
{

   return primitive_type() == e_type_integer ? m_i : 0x8000000000000000ll;

}


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

   m_all = {};

}


inline CLASS_DECL_ACME id & id::operator += (const char * psz) { return operator = (string(*this) + string(psz)); }


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

      return ansi_compare_ci(m_psz,psz);

   }

}


template < >
inline bool EqualElements< id >(id element1, id element2)
{

   return element1 == element2;

}


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


inline string CLASS_DECL_ACME operator + (const char * psz, const ::id & id);


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



