// Camilo Sasuke Tsumanuma 2020-03-08
#pragma once


inline bool __enum_is_ok(const ::enum_object& e) { return (e & e_object_success) != 0; }
inline bool __enum_is_failed(const ::enum_object & e) { return (e & e_object_failure) != 0 || ( e & e_object_timeout) != 0 ; }


class eobject
{
public:


   enum_object       m_eobject;


   eobject() { m_eobject = (enum_object)0; }
   eobject(const std::initializer_list < enum_object >& list) { m_eobject = (enum_object)0; for (auto& e : list) add(e); }
   eobject(enum_object e) { m_eobject = e; }
   eobject(::i64 i) { m_eobject = (enum_object)i; }
   eobject(const eobject& e) { m_eobject = e.m_eobject; }

   inline void add(enum_object e) { m_eobject = (enum_object)(e | m_eobject); }

   inline eobject& operator |= (enum_object e) { add(e); return *this; }
   inline eobject& operator &= (enum_object e) { m_eobject = (enum_object)(m_eobject & e); return *this; }

   inline eobject& operator |= (const eobject& e) { m_eobject = (enum_object)(e.m_eobject | m_eobject); return *this; }
   inline eobject& operator &= (const eobject& e) { m_eobject = (enum_object)(m_eobject & e.m_eobject); return *this; }

   inline eobject& operator += (enum_object e) { return operator |= (e); }
   inline eobject& operator -= (enum_object e) { return operator &= ((enum_object)~(i64)(e)); }

   inline eobject& operator += (const eobject& e) { return operator |= ((enum_object)e.m_eobject); }
   inline eobject& operator -= (const eobject& e) { return operator &= ((enum_object)~(i64)(e.m_eobject)); }

   inline eobject& operator ^= (const eobject& e) { toggle(e);  return *this; }

   inline eobject operator + (const eobject & t) const { auto copy = *this; copy.add(t); return copy; }

   inline eobject operator - (enum_object e) const { return (enum_object)(m_eobject & ~((i64)e)); }

   //template < typename TYPE >
   //eobject operator + (const TYPE & t) const { auto copy = *this; copy.add(t); return copy; }


   inline eobject operator | (enum_object e) const { return (enum_object)(m_eobject | e); }
   inline eobject operator & (enum_object e) const { return (enum_object)(m_eobject & e); }

   inline bool is(enum_object e) const { return (i64)(m_eobject & e) == (i64)e; }
   inline bool has(enum_object e) const { return is(e); }

   void erase(enum_object e) { operator -= (e); }
   void add(const eobject& e) { operator += (e); }
   void unset(const eobject& e) { erase(e); }
   void set(const eobject& e) { add(e); }
   void erase(const eobject& e) { operator -= (e); }
   void clear() { m_eobject = (enum_object)0; }

   void set(enum_object e, bool bSet) { if (bSet) set(e); else unset(e); }
   void toggle(enum_object e) { if (is(e)) unset(e); else set(e); }

   eobject& operator = (const eobject& e) { m_eobject = e.m_eobject; return *this; }


   bool operator == (const eobject& e) const { return m_eobject == e.m_eobject; }
   bool operator == (enum_object e) const { return m_eobject == e; }


   enum_object& eflag() { return (enum_object&)m_eobject; }
   enum_object eflag() const { return (enum_object)m_eobject; }

   bool operator !()
   {

      return __enum_is_failed((enum_object)m_eobject);

   }

   operator enum_object& ()
   {
      return (enum_object&)m_eobject;
   }

   operator enum_object() const
   {

      return (enum_object)m_eobject;
   }


   eobject& operator ++(int)
   {

      m_eobject = (enum_object)((::i64) m_eobject + 1);

      return *this;

   }


   eobject& operator %=(const enum_object& eenum)
   {

      m_eobject = (enum_object)((::i64) m_eobject % (::i64) eenum);

      return *this;

   }

   eobject& rotate(const enum_object& eenum)
   {

      if ((::i64) m_eobject < 0)
      {

         m_eobject = (enum_object)0;

      }

      this->operator++(0);

      return this->operator %=(eenum);

   }

    #ifndef __OBJC__
       IMPL_OPERATOR_PLUS(eobject);
    #endif

    
};


inline bool __enum_is_ok(const ::eobject& e) { return __enum_is_ok(e.m_eobject); }
inline bool __enum_is_failed(const ::eobject & e) { return __enum_is_failed(e.m_eobject); }





