#pragma once


#include "acme/primitive/primitive/e_check.h"

#pragma pack(push, boolean, 1)


class boolean 
{
public:


   ::u8     m_uOn;
   ::u8     m_uSet;


   //inline boolean(no_initialize_t) { m_uSet = false; }


   constexpr boolean() { m_uSet =0; }


   constexpr boolean(int i) { m_uOn = i ? 1 : 0; m_uSet = 1; }


   //constexpr boolean(bool b) { m_uOn = b ? 1 : 0; m_uSet = 1; }


   constexpr boolean(const boolean & boolean) = default;


   inline constexpr bool is_set_false() const { return m_uSet && !m_uOn; }

   inline constexpr bool is_set_true() const { return m_uSet && m_uOn; }

   inline constexpr bool is_true_default_false() const { return m_uSet && m_uOn; }

   inline constexpr bool undefined() const { return !m_uSet; }

   inline constexpr bool is_set() const { return m_uSet; }

   inline constexpr bool is_false_or_undefined() const { return !m_uSet || !m_uOn; }

   inline constexpr bool is_true_or_undefined() const { return !m_uSet || m_uOn; }

   inline constexpr bool is_false_default_true() const { return !m_uSet || !m_uOn; }

   inline constexpr bool is_true_default_true() const { return !m_uSet || m_uOn; }

   inline constexpr bool is_true(bool bDefault) const { return m_uSet ? m_uOn : bDefault; }

   inline constexpr bool is_false(bool bDefault) const { return m_uSet ? !m_uOn : bDefault; }

   //inline bool is_optional() const { return !m_eboolean; }


   //inline bool isOptional() const { return is_optional(); }


   inline operator bool() const { return is_set_true(); }

   inline bool operator!() const { return is_false_or_undefined(); }


   //inline bool operator<(int i) const { return (int)m_eboolean < i; }


   //inline bool operator<=(int i) const { return (int)m_eboolean <= i; }


   //inline bool operator>(int i) const { return (int)m_eboolean > i; }


   //inline bool operator>=(int i) const { return (int)m_eboolean >= i; }


   inline bool operator==(const boolean & b) const 
   {

      if (this->undefined() || b.undefined())
      {

         return false;

      }
   
      return m_uOn ^ b.m_uOn; 
   
   }


   //inline bool operator!=(int i) const { return !operator==(i); }


   inline boolean & operator=(const ::boolean & b)
   {
      if (b.is_set())
      {
         m_uOn = b.m_uOn;
         m_uSet = 1;
      }
      else
      {
         m_uSet = 0;

      }
      return *this;
   }


   //inline boolean& operator=(bool b)
   //{
   //   m_eboolean = (b ? e_boolean_true : e_boolean_false);
   //   return *this;
   //}


   //inline bool operator==(bool b) const { return (m_eboolean == e_boolean_true && b) || (m_eboolean == e_boolean_false && !b); }


   //inline bool operator!=(bool b) const { return !operator==(b); }


   //inline boolean& operator=(const boolean& boolean)
   //{
   //   if (this != &boolean && !boolean.undefined()) { m_eboolean = boolean.m_eboolean; };
   //   return *this;
   //}


   inline void defer(const boolean & b) { if (this->undefined()) { operator =(b); } }


   inline boolean deferred(const boolean & b) const { if (this->undefined()) { return b; } else { return *this; } }


   inline boolean operator()(const boolean & b = 1) const { return deferred(b); }
   
   inline boolean & operator()(const boolean & b = 0) { return operator =(b); }


   operator ::e_check() const
   {

      if (this->undefined())
      {

         return e_check_undefined;

      }
      else if (m_uOn)
      {

         return e_check_checked;

      }
      else 
      {

         return e_check_unchecked;

      }

   }

};


#pragma pack(pop, boolean)

//inline bool __is_true(bool b) { return b; }
//
//
//inline bool __is_true(const enum_boolean & boolean) { return boolean > 0; }
//
//
//inline bool __is_false(bool b) { return !b; }
//
//
//inline bool __is_false(const enum_boolean & ebit) { return ebit < 0; }
//
//
//inline bool __is_optional(bool b) { return false; }
//
//
//inline bool __is_optional(const ::boolean & boolean) { return boolean.isOptional(); }
//
//
//#define __optional_is_true(flag, option) ((bool)(flag) || (__is_optional(flag) && (option)))
