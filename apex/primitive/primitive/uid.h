//
//  uid.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 02/06/19.
//


#pragma once


template < class ENUM >
class flags;


class result;


//class CLASS_DECL_APEX uid
//{
//public:
//
//
//   ::u64                   m_u;
//      flags < ::u64 > *       m_pua;
//
//   inline uid() { clear(); }
//   inline uid(const ::uid & uid) { construct(uid); }
//   inline uid(unsigned short ush) { m_u = (::u64) ush; }
//   inline uid(::u64 u) { if(u < 65536) m_u = u; else construct(*((const flags < ::u64 > *) (uptr) u)); }
//   inline uid(const flags < ::u64 > & ua) { construct(ua); }
//   ~uid();
//
//
//   void construct(const ::uid & uid);
//   void construct(const flags < ::u64 > & ua);
//
//
//   void clear() { m_u = 0; }
//
//
//   bool operator & (::u64 u) const;
//
//   inline uid & operator |=(::u64 u) { return operator +=(u); }
//
//   inline uid & set(::u64 u, bool bSet = true) { if(bSet) operator+=(u); else operator-=(u); return *this; }
//
//   uid & operator +=(::u64 u);
//
//   uid & operator -=(::u64 u);
//
//   void promote();
//
//   void defer_downgrade();
//
//
//};
//
//
//
