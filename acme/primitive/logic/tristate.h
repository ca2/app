#pragma once


class CLASS_DECL_ACME tristate
{
public:


   enum_boolean m_eboolean;


   inline tristate(enum_optional) { m_eboolean = e_boolean_none; }


   inline tristate() { m_eboolean = e_boolean_none; }


   inline tristate(int i) { operator=(i); }


   inline tristate(bool b) { operator=(b); }


   inline tristate(const tristate& boolean) : m_eboolean(e_boolean_none) { if (!boolean.undefined()) { m_eboolean = boolean.m_eboolean; } }


   inline bool isFalse() const { return is_false(); }


   inline bool is_false() const { return m_eboolean < e_boolean_empty; }


   inline bool undefined() const { return is_empty(); }


   inline bool is_empty() const { return m_eboolean == e_boolean_empty; }

   inline bool is_set() const { return m_eboolean != e_boolean_empty; }

   inline bool notTrue() const { return m_eboolean < e_boolean_yes; }


   inline bool is_none() const { return is_empty(); }


   inline bool is_true() const { return m_eboolean > e_boolean_empty; }


   inline bool is_true(bool bDefault) const { return m_eboolean ? isTrue() : bDefault; }


   inline bool isTrue() const { return is_true(); }


   inline bool is_optional() const { return !m_eboolean; }


   inline bool isOptional() const { return is_optional(); }


   inline operator bool() const { return isTrue(); }


   inline bool operator!() const { return isFalse(); }


   inline bool operator<(int i) const { return (int)m_eboolean < i; }


   inline bool operator<=(int i) const { return (int)m_eboolean <= i; }


   inline bool operator>(int i) const { return (int)m_eboolean > i; }


   inline bool operator>=(int i) const { return (int)m_eboolean >= i; }


   inline bool operator==(int i) const { return (int)m_eboolean == i; }


   inline bool operator!=(int i) const { return !operator==(i); }


   inline tristate & operator=(int i)
   {
      m_eboolean = (i ? e_boolean_true : e_boolean_false);
      return *this;
   }


   inline tristate& operator=(bool b)
   {
      m_eboolean = (b ? e_boolean_true : e_boolean_false);
      return *this;
   }


   inline bool operator==(bool b) const { return (m_eboolean == e_boolean_true && b) || (m_eboolean == e_boolean_false && !b); }


   inline bool operator!=(bool b) const { return !operator==(b); }


   inline tristate& operator=(const tristate& boolean)
   {
      if (this != &boolean && !boolean.undefined()) { m_eboolean = boolean.m_eboolean; };
      return *this;
   }


   inline void defer(int i) { if (is_empty()) { operator=(i); } }


   inline tristate deferred(int i) const { if (is_empty()) { return i; } else { return m_eboolean; } }


   inline tristate operator()(int i) const { return deferred(i); }

};




inline bool __is_true(bool b) { return b; }


inline bool __is_true(const enum_boolean & boolean) { return boolean > 0; }


inline bool __is_false(bool b) { return !b; }


inline bool __is_false(const enum_boolean & ebit) { return ebit < 0; }


inline bool __is_optional(bool b) { return false; }


inline bool __is_optional(const ::tristate & tristate) { return tristate.isOptional(); }


#define __optional_is_true(flag, option) ((bool)(flag) || (__is_optional(flag) && (option)))
