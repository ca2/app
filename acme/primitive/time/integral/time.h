#pragma once

//
//template < typename INTEGRAL_TIME_TYPE >
//class integral_time :
//   public INTEGRAL_TIME_TYPE
//{
//public:
//
//
//   using BASE_TYPE = typename INTEGRAL_TIME_TYPE::BASE_TYPE;
//
//
//   constexpr integral_time(BASE_TYPE itime = {}) : INTEGRAL_TIME_TYPE(itime) {}
//   integral_time(const class time & time) : INTEGRAL_TIME_TYPE(time) {}
//
//   integral_time(enum_now)
//   {
//
//      Now();
//
//   }
//
//
//   inline integral_time & Now();
//
//   static inline integral_time now() { return e_now; }
//
//
//   inline integral_time elapsed(const integral_time & timeStop = ::e_now) const
//   {
//
//      return typename INTEGRAL_TIME_TYPE::BASE_TYPE(timeStop.m_i - this->m_i);
//
//   }
//
//   inline integral_time update_elapsed(const integral_time & timeStop = ::now < INTEGRAL_TIME_TYPE >())
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
//   inline integral_time half() const
//   {
//
//      return typename INTEGRAL_TIME_TYPE::BASE_TYPE(this->m_i >> 1);
//
//   }
//
//
//   inline double sawtooth(const integral_time & period)
//   {
//
//      return (double)(elapsed().m_i % period.m_i) / (double)period.m_i;
//
//   }
//
//
//   inline double period_rate(const integral_time & period)
//   {
//
//      return (double)(elapsed().m_i) / (double)period.m_i;
//
//   }
//
//
//   inline bool on_off(const integral_time & period) const
//   {
//
//      return (elapsed().m_i % period.m_i) < period.half().m_i;
//
//   }
//
//
//   inline bool on_off(const integral_time & period, double dRate) const
//   {
//
//      return (elapsed().m_i % period.m_i) < period.m_i * dRate;
//
//   }
//
//
//   //inline class ::time wait() const;
//
//
//
//   template < primitive_integral INTEGRAL >
//   integral_time operator %(INTEGRAL integral) const { return typename INTEGRAL_TIME_TYPE::BASE_TYPE(this->m_i % integral); }
//
//   template < primitive_integral INTEGRAL >
//   integral_time operator /(INTEGRAL integral) const { return typename INTEGRAL_TIME_TYPE::BASE_TYPE(this->m_i / integral); }
//
//   template < primitive_integral INTEGRAL >
//   integral_time operator *(INTEGRAL integral) const { return typename INTEGRAL_TIME_TYPE::BASE_TYPE(this->m_i * integral); }
//
//   template < primitive_integral INTEGRAL >
//   integral_time operator +(INTEGRAL integral) const { return typename INTEGRAL_TIME_TYPE::BASE_TYPE(this->m_i + integral); }
//
//   template < primitive_integral INTEGRAL >
//   integral_time operator -(INTEGRAL integral) const { return typename INTEGRAL_TIME_TYPE::BASE_TYPE(this->m_i - integral); }
//
//
//
//   integral_time operator %(const BASE_TYPE & time) const { return BASE_TYPE(this->m_i % time.m_i); }
//   double operator /(const BASE_TYPE & time) const { return (double)this->m_i / (double)time.m_i; }
//   //integral_time operator *(const BASE_TYPE & time) const { return BASE_TYPE(this->m_i * time.m_i); }
//   integral_time operator +(const BASE_TYPE & time) const { return BASE_TYPE(this->m_i + time.m_i); }
//   integral_time operator -(const BASE_TYPE & time) const { return BASE_TYPE(this->m_i - time.m_i); }
//
//   integral_time operator -() const { return BASE_TYPE(-this->m_i); }
//
//   //bool operator == (const BASE_TYPE & time) const { return this->m_i == time.m_i; }
//   //::std::strong_ordering operator <=>  (const BASE_TYPE & time) const { return this->m_i <=>  time.m_i; }
//   //bool operator >= (const BASE_TYPE & time) const { return this->m_i >= time.m_i; }
//   //bool operator <  (const BASE_TYPE & time) const { return this->m_i <  time.m_i; }
//   //bool operator <= (const BASE_TYPE & time) const { return this->m_i <= time.m_i; }
//   //bool operator != (const BASE_TYPE & time) const { return this->m_i != time.m_i; }
//
//
////   bool operator == (const integral_time & time) const { return this->m_i == time.m_i; }
//  // ::std::strong_ordering operator <=>  (const integral_time & time) const { return this->m_i <=> time.m_i; }
//   //bool operator >= (const integral_time & time) const { return this->m_i >= time.m_i; }
//   //bool operator <  (const integral_time & time) const { return this->m_i < time.m_i; }
//   //bool operator <= (const integral_time & time) const { return this->m_i <= time.m_i; }
//   //bool operator != (const integral_time & time) const { return this->m_i != time.m_i; }
//
////
////   string get_string() const
////   {
////
////      string str;
////
////      to_string(str, (const typename INTEGRAL_TIME_TYPE::BASE_TYPE &) *this);
////
////      return str;
////
////   }
//
//   //__DURATION_SETUP__(integral_time, m_i);
//
//   //DECLARE_COMPARISON_WITH_TIME
//   //DECLARE_COMPARISON_WITH_TIME
//
//
//};
//
//
//template < primitive_floating FLOATING, typename INTEGRAL_TIME_TYPE >
//integral_time < INTEGRAL_TIME_TYPE > operator * (FLOATING floating, const integral_time < INTEGRAL_TIME_TYPE > & integraltime)
//{
//
//   return (typename INTEGRAL_TIME_TYPE::BASE_TYPE) (typename INTEGRAL_TIME_TYPE::BASE_TYPE::BASE_TYPE)(floating * integraltime.m_i);
//
//}
//
//
//template < primitive_integral INTEGRAL, typename INTEGRAL_TIME_TYPE >
//integral_time < INTEGRAL_TIME_TYPE > operator * (INTEGRAL integral, const integral_time < INTEGRAL_TIME_TYPE > & integraltime)
//{
//
//   return (typename INTEGRAL_TIME_TYPE::BASE_TYPE) (typename INTEGRAL_TIME_TYPE::BASE_TYPE::BASE_TYPE)(integral * integraltime.m_i);
//
//}
//
//
//
//
////template < primitive_floating FLOATING, typename INTEGRAL_TIME_TYPE >
////floating_frequency operator * (FLOATING floating, const integral_time < INTEGRAL_TIME_TYPE > & integraltime)
////{
////
////   return (::f64)(floating / integraltime.m_i);
////
////}
//
//
