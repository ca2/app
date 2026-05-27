#pragma once


//namespace logic
//{
//

   class CLASS_DECL_ACME boolean
   {
   public:


      enum_boolean m_eboolean;


      inline boolean(enum_optional) { m_eboolean = e_boolean_none; }


      inline boolean() { m_eboolean = e_boolean_none; }


      inline boolean(::i32 i) { operator=(i); }


      inline boolean(bool b) { operator=(b); }


      inline boolean(const boolean & boolean) : m_eboolean(e_boolean_none) { if (!boolean.undefined()) { m_eboolean = boolean.m_eboolean; } }


      inline bool isFalse() const { return is_false(); }


      inline bool is_false() const { return m_eboolean < e_boolean_false; }


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


      inline bool operator<(::i32 i) const { return (::i32)m_eboolean < i; }


      inline bool operator<=(::i32 i) const { return (::i32)m_eboolean <= i; }


      inline bool operator>(::i32 i) const { return (::i32)m_eboolean > i; }


      inline bool operator>=(::i32 i) const { return (::i32)m_eboolean >= i; }


      inline bool operator==(::i32 i) const { return (::i32)m_eboolean == i; }


      inline bool operator!=(::i32 i) const { return !operator==(i); }


      inline boolean & operator=(::i32 i)
      {
         m_eboolean = (i ? e_boolean_true : e_boolean_false);
         return *this;
      }


      inline boolean & operator=(bool b)
      {
         m_eboolean = (b ? e_boolean_true : e_boolean_false);
         return *this;
      }


      inline bool operator==(bool b) const { return (m_eboolean == e_boolean_true && b) || (m_eboolean == e_boolean_false && !b); }


      inline bool operator!=(bool b) const { return !operator==(b); }


      inline boolean & operator=(const boolean & boolean)
      {
         if (this != &boolean && !boolean.undefined()) { m_eboolean = boolean.m_eboolean; };
         return *this;
      }


      inline void defer(::i32 i) { if (is_empty()) { operator=(i); } }


      inline boolean deferred(::i32 i) const { if (is_empty()) { return i; } else { return m_eboolean; } }


      inline boolean operator()(::i32 i) const { return deferred(i); }

   };


//} // namespace logic



inline bool __is_true(bool b) { return b; }


inline bool __is_true(const enum_boolean & boolean) { return boolean > 0; }


inline bool __is_false(bool b) { return !b; }


inline bool __is_false(const enum_boolean & ebit) { return ebit < 0; }


inline bool __is_optional(bool b) { return false; }


inline bool __is_optional(const ::logic::boolean & boolean) { return boolean.isOptional(); }


#define __optional_is_true(flag, option) ((bool)(flag) || (__is_optional(flag) && (option)))
