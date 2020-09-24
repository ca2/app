#pragma once


#include "acme/primitive/comparison/equals.h"
#include "acme/primitive/comparison/hash.h"


enum e_id : ::u64;


struct id_all
{

   ::i64             m_iBody;
   ::i64             m_iType;

};


class CLASS_DECL_ACME id
{
public:


   enum e_type : ::i64
   {

      type_null = 0,
      type_empty = 1,
      type_integer = 2,
      type_text = 3,
      type_property = 4,
      type_factory = 5,
      type_thread_tool = 6,

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
            enum_property        m_eproperty;
            enum_factory         m_efactory;
            enum_thread_tool     m_ethreadtool;
         };

         e_type                  m_etype;


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
   inline id(e_type etype);
   inline id(enum_property eproperty);
   inline id(enum_factory efactory);
   inline id(enum_thread_tool ethreadtool);
   inline id(const id & id);
   id(const char * psz);
   id(::i32 i);
   id(::i64 i);
   id(::u64 u);
   id(const string & str);
   id(const var & var);
   id(const type & type);
   id(::id && id) { m_all = id.m_all; id.m_all = {}; }


   void raw_set(const char * psz);


   string str() const;


   inline bool operator == (const id & id) const;
   inline bool operator != (const id & id) const;
   inline bool operator < (const id & id) const;
   inline bool operator <= (const id & id) const;
   inline bool operator > (const id & id) const;
   inline bool operator >= (const id & id) const;


   inline bool operator == (const char * psz) const;
   inline bool operator != (const char * psz) const;
   inline bool operator < (const char * psz) const;
   inline bool operator <= (const char * psz) const;
   inline bool operator > (const char * psz) const;
   inline bool operator >= (const char * psz) const;


   inline bool operator == (const string & str) const;
   inline bool operator != (const string & str) const;
   inline bool operator < (const string & str) const;
   inline bool operator <= (const string & str) const;
   inline bool operator > (const string & str) const;
   inline bool operator >= (const string & str) const;


   inline bool operator == (::i32 i) const;
   inline bool operator != (::i32 i) const;
   inline bool operator < (::i32 i) const;
   inline bool operator <= (::i32 i) const;
   inline bool operator > (::i32 i) const;
   inline bool operator >= (::i32 i) const;


   inline bool operator == (::i64 i) const;
   inline bool operator != (::i64 i) const;
   inline bool operator < (::i64 i) const;
   inline bool operator <= (::i64 i) const;
   inline bool operator > (::i64 i) const;
   inline bool operator >= (::i64 i) const;


   inline bool operator == (::e_id eid) const;
   inline bool operator != (::e_id eid) const;
   inline bool operator < (::e_id eid) const;
   inline bool operator <= (::e_id eid) const;
   inline bool operator > (::e_id eid) const;
   inline bool operator >= (::e_id eid) const;


   id & operator = (const var & var);
   id & operator = (const property & prop);
   id & operator = (const id & id);
   id & operator = (const char * psz);
   id & operator = (const string & str);
   id & operator = (::i32 i);
   id & operator = (::i64 i);
   id & operator = (::u64 u);
   id & operator = (const enum_property & eproperty);
   id & operator = (const enum_factory & efactory);
   id & operator = (const enum_thread_tool & ethreadtool);


   inline ansistring to_string_base() const { return to_string(); }
   inline operator ::i64() const;
   inline ::i64 i64() const;
   inline ::i32 i32() const { return (::i32) i64(); }
   inline ::u32 u32() const { return (::u32) i64(); }
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


   inline bool is_text() const { return m_etype == type_text; }
   inline bool is_integer() const { return m_etype == type_integer; }


   inline id & operator +=(const char * psz);

   inline id operator +(const id & id) const;
   inline string operator +(const char * psz) const;
   inline string operator +(const string & str) const;


};


inline id::id()
{

   m_all = {};

}


inline id::id(e_type etype) :
   ::id()
{

   if(etype == type_null)
   {

      m_etype = type_null;

   }
   else if(etype == type_empty)
   {

      m_etype = type_empty;

   }
   else if(etype == type_integer)
   {

      m_etype = type_integer;

   }
   else if(etype == type_text)
   {

      operator = ("");

   }

}


inline id::id(enum_property eproperty) :
   m_etype(type_property),
   m_i(eproperty) // used m_i to reset 64-bit field
{

}


inline id::id(enum_factory efactory) :
   m_etype(type_factory),
   m_i(efactory) // used m_i to reset 64-bit field
{

}


inline id::id(enum_thread_tool ethreadtool) :
   m_etype(type_thread_tool),
   m_i(ethreadtool) // used m_i to reset 64-bit field
{

}


inline id::id(const id & id)
{

   m_all = id.m_all;

}


inline id::id(const char * psz, id_space *)
{

   m_etype = type_text;

   m_i = (::i64) (::iptr) psz;

}


inline id::id(::i32 i)
{

   m_etype = type_integer;

   m_i = i;

}


inline id::id(::i64 i)
{

   m_etype = type_integer;

   m_i = i;

}


inline id::id(::u64 u)
{

   m_etype = type_integer;

   m_u = u;

}


inline bool id::operator == (const id & id) const
{

   return m_iType == id.m_iType && m_iBody == id.m_iBody;

}


inline bool id::operator != (const id & id) const
{

   return ! operator == (id);

}


inline bool id::operator < (const id & id) const
{

   return m_iType < id.m_iType || ((m_iType == id.m_iType) && m_iBody < id.m_iBody);

}


inline bool id::operator >(const id & id) const
{

   return m_iType > id.m_iType || ((m_iType == id.m_iType) && m_iBody > id.m_iBody);

}


inline bool id::operator <= (const id & id) const
{

   return id > *this;

}


inline bool id::operator >= (const id & id) const
{

   return id < *this;

}


inline id & id::operator = (const id & id)
{
   
   m_all         = id.m_all;
   
   return *this;

}


inline bool id::operator == (const string & str) const
{
   
   return m_etype == type_text && (m_psz == nullptr ? false : str.compare(m_psz) == 0);

}


inline bool id::operator != (const string & str) const
{
   
   return !operator==(str);

}


inline bool id::operator < (const string & str) const
{

   return (m_etype < type_text) || (m_psz == nullptr ? true : str.compare(m_psz) > 0);

}


inline bool id::operator <= (const string & str) const
{

   return !operator > (str);

}


inline bool id::operator > (const string & str) const
{

   return (m_etype > type_text) || (m_psz == nullptr ? false : str.compare(m_psz) < 0);

}


inline bool id::operator >= (const string & str) const
{
   
   return !operator < (str);

}


inline id::operator const char *() const
{
   
   return (m_etype != type_text || m_psz == nullptr) ? nullptr : m_psz;

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
   return is_null() || m_etype == type_empty || (m_etype == type_text && *m_psz == '\0');
}



inline CLASS_DECL_ACME iptr id_strcmp(const id * pid1,const id * pid2)
{
   return strcmp(pid1->m_psz,pid2->m_psz);
}

inline void id::raw_set(const char * psz)
{

   m_etype     = type_text;
   m_i         = (::i64) (::iptr) psz;

}

inline string id::str() const
{
   if(m_etype == type_null)
   {
      return "(null)";
   }
   else if(m_etype == type_empty)
   {
      return "(empty)";
   }
   else if(m_etype == type_text)
   {
      return m_psz;
   }
   else if(m_etype == type_integer)
   {
      return __str(m_i);
   }
   else
   {
      return string("(type:") + __str(m_iType) + ",body:" + __str(m_iBody) + ")";
   }
}


inline bool id::operator == (const char * psz) const
{
   return m_etype == type_text && (m_psz == nullptr ? psz == nullptr : strcmp(m_psz,psz) == 0);
}
inline bool id::operator != (const char * psz) const
{
   return !operator ==(psz);
}
inline bool id::operator < (const char * psz) const
{
   return m_etype < type_text || (m_etype == type_text && (m_psz == nullptr ? psz != nullptr : strcmp(m_psz,psz) < 0));
}
inline bool id::operator > (const char * psz) const
{
   return m_etype > type_text || (m_etype == type_text && (m_psz == nullptr ? psz == nullptr : strcmp(m_psz,psz) > 0));
}
inline bool id::operator <= (const char * psz) const
{
   return !operator>(psz);
}
inline bool id::operator >= (const char * psz) const
{
   return !operator<(psz);
}



inline bool id::operator == (::i32 i) const
{
   return m_etype == type_integer && m_i == i;
}
inline bool id::operator != (::i32 i) const
{
   return m_etype != type_integer || m_i != i;
}
inline bool id::operator < (::i32 i) const
{
   return m_etype == type_integer && m_i < i;
}
inline bool id::operator <= (::i32 i) const
{
   return m_etype == type_integer && m_i <= i;
}
inline bool id::operator > (::i32 i) const
{
   return m_etype == type_integer && m_i > i;
}
inline bool id::operator >= (::i32 i) const
{
   return m_etype == type_integer && m_i >= i;
}

inline bool id::operator == (::i64 i) const
{
   return m_etype == type_integer && m_i == i;
}
inline bool id::operator != (::i64 i) const
{
   return m_etype != type_integer || m_i != i;
}
inline bool id::operator < (::i64 i) const
{
   return m_etype == type_integer && m_i < i;
}
inline bool id::operator <= (::i64 i) const
{
   return m_etype == type_integer && m_i <= i;
}
inline bool id::operator > (::i64 i) const
{
   return m_etype == type_integer && m_i > i;
}
inline bool id::operator >= (::i64 i) const
{
   return m_etype == type_integer && m_i >= i;
}



inline bool id::operator == (::e_id eid) const
{
   return m_etype == type_integer && m_i == eid;
}
inline bool id::operator != (::e_id eid) const
{
   return m_etype != type_integer || m_i != eid;
}
inline bool id::operator < (::e_id eid) const
{
   return m_etype == type_integer && m_u < eid;
}
inline bool id::operator <= (::e_id eid) const
{
   return m_etype == type_integer && m_u <= eid;
}
inline bool id::operator > (::e_id eid) const
{
   return m_etype == type_integer && m_u > eid;
}
inline bool id::operator >= (::e_id eid) const
{
   return m_etype == type_integer && m_u >= eid;
}

//inline id::operator ::i32 () const
//{
//
//   return i32();
//
//}

inline id::operator ::i64 () const
{

   return i64();

}

inline ::i64 id::i64() const
{

   return m_etype == type_integer ? m_i : 0x8000000000000000ll;

}




//inline id::operator iptr()
//{
//   if(is_number())
//      return m_i;
//   else
//      return 0;
//}

inline bool id::is_null() const
{
   return m_etype == type_null || (m_etype == type_text && m_psz == nullptr);
}

inline bool id::has_char() const
{
   return m_etype == type_text && m_psz != nullptr && *m_psz != '\0';
}

inline void id::empty()
{
   m_etype  = type_empty;
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
      if(psz == nullptr)
         return 0;
      else
         return -1;
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

   //if (key.m_etype == id::type_text)
   //{

   //   return uptr_hash(key.m_psz);

   //}

   return ((((UINT)(uptr)key.m_iType) << 24) & 0xffffffffu) | ((((UINT)(uptr)key.m_iBody) >> 8) & 0xffffffffu);

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