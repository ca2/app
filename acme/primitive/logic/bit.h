#pragma once


namespace logic
{


   class CLASS_DECL_ACME bit
   {
   public:


      enum_bit m_ebit;


      inline bit(enum_optional) { m_ebit = e_bit_none; }


      inline bit() { m_ebit = e_bit_none; }


      inline bit(int i) { operator=(i); }


      inline bit(bool b) { operator=(b); }


      inline bit(const bit & bit) : m_ebit(e_bit_none) { if (!bit.undefined()) { m_ebit = bit.m_ebit; } }


      inline bool isFalse() const { return is_false(); }


      inline bool is_false() const { return m_ebit < e_bit_empty; }


      inline bool undefined() const { return is_empty(); }


      inline bool is_empty() const { return m_ebit == e_bit_empty; }

      inline bool is_set() const { return m_ebit != e_bit_empty; }

      inline bool notTrue() const { return m_ebit < e_bit_yes; }


      inline bool is_none() const { return is_empty(); }


      inline bool is_true() const { return m_ebit > e_bit_empty; }


      inline bool is_true(bool bDefault) const { return m_ebit ? isTrue() : bDefault; }


      inline bool isTrue() const { return is_true(); }


      inline bool is_optional() const { return !m_ebit; }


      inline bool isOptional() const { return is_optional(); }


      inline operator bool() const { return isTrue(); }


      inline bool operator!() const { return isFalse(); }


      inline bool operator<(int i) const { return (int)m_ebit < i; }


      inline bool operator<=(int i) const { return (int)m_ebit <= i; }


      inline bool operator>(int i) const { return (int)m_ebit > i; }


      inline bool operator>=(int i) const { return (int)m_ebit >= i; }


      inline bool operator==(int i) const { return (int)m_ebit == i; }


      inline bool operator!=(int i) const { return !operator==(i); }


      inline bit & operator=(int i)
      {
         m_ebit = (i ? e_bit_true : e_bit_false);
         return *this;
      }


      inline bit & operator=(bool b)
      {
         m_ebit = (b ? e_bit_true : e_bit_false);
         return *this;
      }


      inline bool operator==(bool b) const { return (m_ebit == e_bit_true && b) || (m_ebit == e_bit_false && !b); }


      inline bool operator!=(bool b) const { return !operator==(b); }


      inline bit & operator=(const bit & bit)
      {
         if (this != &bit && !bit.undefined()) { m_ebit = bit.m_ebit; };
         return *this;
      }


      inline void defer(int i) { if (is_empty()) { operator=(i); } }


      inline bit deferred(int i) const { if (is_empty()) { return i; } else { return m_ebit; } }


      inline bit operator()(int i) const { return deferred(i); }

   };


} // namespace logic



inline bool __is_true(bool b) { return b; }


inline bool __is_true(const enum_bit & bit) { return bit > 0; }


inline bool __is_false(bool b) { return !b; }


inline bool __is_false(const enum_bit & ebit) { return ebit < 0; }


inline bool __is_optional(bool b) { return false; }


inline bool __is_optional(const ::logic::bit & bit) { return bit.isOptional(); }


#define __optional_is_true(flag, option) ((bool)(flag) || (__is_optional(flag) && (option)))
