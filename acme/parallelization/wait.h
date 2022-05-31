// Created by camilo on 2021-10-04 04:57 BRT <3ThomasBorregaardSørensen!!
#pragma once


#ifdef wait
#undef wait
#endif // wait


class CLASS_DECL_ACME wait :
   public time
{
public:


   constexpr wait() : wait(5.0, 1800.0) {}
   constexpr wait(double dWait) : wait(dWait, dWait * 60.0) {}
   constexpr wait(
#if DEBUG
      double,
      double dWait
#else
      double dWait,
      double
#endif
   ) :time(dWait) {}
   wait(const class ::time& time) : time(time.m_d) {}
   wait(const class ::wait& wait) : time(wait.m_d) {}


   static inline double __infinite() { return 1.e9; }

   static inline class ::wait infinite() { return __infinite(); }

   inline operator ::u32() const { return (::u32) ::minimum_maximum(m_d, 0., __infinite()); }

   inline bool is_infinite() const { return m_d >= __infinite(); }

   inline bool is_null() const { return m_d <= 0; }


};



