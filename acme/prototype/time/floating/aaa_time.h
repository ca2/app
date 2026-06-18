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
//      return timeStop.m_f64 - this->m_f64;
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
//      return this->m_f64/ 2.0;
//
//   }
//
//
//   inline ::f64 sawtooth(const floating_time & period)
//   {
//
//      return fmod(elapsed().m_f64, period.m_f64) / period.m_f64;
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
//   inline ::f64 period_rate(const floating_time & period)
//   {
//
//      return elapsed().m_f64 / period.m_f64;
//
//   }
//
//
//   inline bool on_off(const floating_time & period) const
//   {
//
//      return fmod(elapsed() , period.m_f64) < half();
//
//
//   }
//
//
//   inline bool on_off(const floating_time & period, ::f64 dRate) const
//   {
//
//      return fmod(elapsed().m_f64, period.m_f64) < period.m_f64 * dRate;
//
//
//   }
//
//   
//
//   template < prototype_floating FLOATING >
//   floating_time operator %(FLOATING floating) const { return typename FLOATING_TIME_TYPE::BASE_TYPE(fmod(this->m_f64, floating)); }
//
//   template < prototype_floating FLOATING >
//   floating_time operator /(FLOATING floating) const { return typename FLOATING_TIME_TYPE::BASE_TYPE(this->m_f64 / floating); }
//
//   template < prototype_floating FLOATING >
//   floating_time operator *(FLOATING floating) const { return typename FLOATING_TIME_TYPE::BASE_TYPE(this->m_f64 * floating); }
//
//   template < prototype_floating FLOATING >
//   floating_time operator +(FLOATING floating) const { return typename FLOATING_TIME_TYPE::BASE_TYPE(this->m_f64 + floating); }
//
//   template < prototype_floating FLOATING >
//   floating_time operator -(FLOATING floating) const { return typename FLOATING_TIME_TYPE::BASE_TYPE(this->m_f64 - floating); }
//
//
//   floating_time operator %(const BASE_TYPE & time) const { return typename FLOATING_TIME_TYPE::BASE_TYPE(fmod(this->m_f64, time.m_f64)); }
//   ::f64 operator /(const BASE_TYPE & time) const { return this->m_f64 / time.m_f64; }
//   // floating_time operator *(const BASE_TYPE & time) const { return BASE_TYPE(this->m_f64 * time.m_f64); }
//   floating_time operator +(const BASE_TYPE & time) const { return typename FLOATING_TIME_TYPE::BASE_TYPE(this->m_f64 + time.m_f64); }
//   floating_time operator -(const BASE_TYPE & time) const { return typename FLOATING_TIME_TYPE::BASE_TYPE(this->m_f64 - time.m_f64); }
//
//   
//   floating_time operator -() const { return typename FLOATING_TIME_TYPE::BASE_TYPE(-this->m_f64); }
//
//
//   //bool operator ==(const BASE_TYPE & time) const { return this->m_f64 == time.m_f64; }
//   //bool operator >(const BASE_TYPE & time) const { return this->m_f64 > time.m_f64; }
//   //bool operator >=(const BASE_TYPE & time) const { return this->m_f64 >= time.m_f64; }
//   //bool operator <(const BASE_TYPE & time) const { return this->m_f64 < time.m_f64; }
//   //bool operator <=(const BASE_TYPE & time) const { return this->m_f64 <= time.m_f64; }
//   //bool operator !=(const BASE_TYPE & time) const { return this->m_f64 != time.m_f64; }
//
//
//
//   //__DURATION_SETUP__(floating_time, m_f64);
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
