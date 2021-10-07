// Created by camilo on 2021-10-04 04:57 BRT <3ThomasBorregaardS�rensen!!
#pragma once


class CLASS_DECL_ACME wait :
   public INTEGRAL_MILLISECOND
{
public:


   wait() : INTEGRAL_MILLISECOND{} {}
   wait(const INTEGRAL_MILLISECOND & integralmillisecond):INTEGRAL_MILLISECOND(integralmillisecond){ }

   static inline ::i64 __infinite() { return 0xffffffffu ; }

   static inline INTEGRAL_MILLISECOND _infinite() { return { __infinite() }; }

   static inline class ::wait infinite() { return _infinite(); }

   inline operator ::u32() const { return (::u32) ::minimum_maximum(m_i, 0, __infinite()); }

   inline bool is_infinite() const { return m_i >= __infinite(); }

   inline bool is_null() const { return m_i <= 0; }

   static inline class ::wait now();

   inline class ::wait elapsed(const class ::wait & waitSample = now()) { return INTEGRAL_MILLISECOND(waitSample.m_i - m_i); }

   inline class ::wait operator +(const class ::wait & wait) const { return INTEGRAL_MILLISECOND(m_i + wait.m_i); }
   inline class ::wait operator -(const class ::wait & wait) const { return INTEGRAL_MILLISECOND(m_i - wait.m_i); }

};
