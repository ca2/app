// Created by camilo on 2021-10-05 12:31 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]
#pragma once

//
//template < typename FLOATING_TIME_TYPE >
//class floating_time :
//   public FLOATING_TIME_TYPE
//{
//public:
//
//
//   using BASE_DURATION = FLOATING_TIME_TYPE;
//   using BASE_TYPE = typename BASE_DURATION::BASE_TYPE;
//
//
//   constexpr floating_time(BASE_TYPE t = {}) : FLOATING_TIME_TYPE(t) {}
//   floating_time(const class time & time) : FLOATING_TIME_TYPE(time) {}
//
////   floating_time(const floating_time & type) :
////      FLOATING_TIME_TYPE(type)
////   {
////
////   }
//
//   floating_time(enum_now)
//   {
//
//      Now();
//
//   }
//
//
//   inline floating_time elapsed(const floating_time & timeStop = ::now < FLOATING_TIME_TYPE >()) const
//   {
//
//      return timeStop.m_d - this->m_d;
//
//   }
//
//
//   inline floating_time update_elapsed(const floating_time & timeStop = now_t{})
//   {
//
//      auto elapsed = timeStop - *this;
//
//      operator=(timeStop);
//
//      return elapsed;
//
//   }
//
//
//   inline floating_time half() const
//   {
//
//      return this->m_d/ 2.0;
//
//   }
//
//
//   inline double sawtooth(const floating_time & period)
//   {
//
//      return fmod(elapsed().m_d, period.m_d) / period.m_d;
//
//   }
//
//   
//   inline class floating_time & Now() 
//   { 
//      
//      return operator=(::now <floating_time>()); 
//   
//   }
//
//
//   inline double period_rate(const floating_time & period)
//   {
//
//      return elapsed().m_d / period.m_d;
//
//   }
//
//
//   inline bool on_off(const floating_time & period) const
//   {
//
//      return fmod(elapsed() , period.m_d) < half();
//
//
//   }
//
//
//   inline bool on_off(const floating_time & period, double dRate) const
//   {
//
//      return fmod(elapsed().m_d, period.m_d) < period.m_d * dRate;
//
//
//   }
//
//   
//
//   template < primitive_floating FLOATING >
//   floating_time operator %(FLOATING floating) const { return typename FLOATING_TIME_TYPE::BASE_TYPE(fmod(this->m_d, floating)); }
//
//   template < primitive_floating FLOATING >
//   floating_time operator /(FLOATING floating) const { return typename FLOATING_TIME_TYPE::BASE_TYPE(this->m_d / floating); }
//
//   template < primitive_floating FLOATING >
//   floating_time operator *(FLOATING floating) const { return typename FLOATING_TIME_TYPE::BASE_TYPE(this->m_d * floating); }
//
//   template < primitive_floating FLOATING >
//   floating_time operator +(FLOATING floating) const { return typename FLOATING_TIME_TYPE::BASE_TYPE(this->m_d + floating); }
//
//   template < primitive_floating FLOATING >
//   floating_time operator -(FLOATING floating) const { return typename FLOATING_TIME_TYPE::BASE_TYPE(this->m_d - floating); }
//
//
//   floating_time operator %(const BASE_TYPE & time) const { return typename FLOATING_TIME_TYPE::BASE_TYPE(fmod(this->m_d, time.m_d)); }
//   double operator /(const BASE_TYPE & time) const { return this->m_d / time.m_d; }
//   // floating_time operator *(const BASE_TYPE & time) const { return BASE_TYPE(this->m_d * time.m_d); }
//   floating_time operator +(const BASE_TYPE & time) const { return typename FLOATING_TIME_TYPE::BASE_TYPE(this->m_d + time.m_d); }
//   floating_time operator -(const BASE_TYPE & time) const { return typename FLOATING_TIME_TYPE::BASE_TYPE(this->m_d - time.m_d); }
//
//   
//   floating_time operator -() const { return typename FLOATING_TIME_TYPE::BASE_TYPE(-this->m_d); }
//
//
//   //bool operator ==(const BASE_TYPE & time) const { return this->m_d == time.m_d; }
//   //bool operator >(const BASE_TYPE & time) const { return this->m_d > time.m_d; }
//   //bool operator >=(const BASE_TYPE & time) const { return this->m_d >= time.m_d; }
//   //bool operator <(const BASE_TYPE & time) const { return this->m_d < time.m_d; }
//   //bool operator <=(const BASE_TYPE & time) const { return this->m_d <= time.m_d; }
//   //bool operator !=(const BASE_TYPE & time) const { return this->m_d != time.m_d; }
//
//
//
//   //__DURATION_SETUP__(floating_time, m_d);
//
//
//   //DECLARE_COMPARISON_WITH_TIME
//
//
//
//};
//
//
//
