// Created by camilo on 2021-10-05 12:16 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
#pragma once


template < typename DURATION >
class integral_duration :
   public DURATION
{
public:


   using BASE_TYPE = typename DURATION::BASE_TYPE;


   using DURATION::DURATION;


   integral_duration(const integral_duration & type)
   {

      this->m_i = type.m_i;

   }

   integral_duration(enum_now)
   {

      Now();

   }


   inline integral_duration & Now();

   static inline integral_duration now() { return e_now; }


   inline integral_duration elapsed(const integral_duration & durationStop = ::now < integral_duration >()) const
   {

      return typename DURATION::BASE_TYPE(durationStop.m_i - this->m_i);

   }


   inline integral_duration half() const
   {

      return typename DURATION::BASE_TYPE(this->m_i >> 1);

   }


   inline double sawtooth(const integral_duration & period)
   {

      return (double)(elapsed().m_i % period.m_i) / (double)period.m_i;

   }


   inline double period_rate(const integral_duration & period)
   {

      return (double)(elapsed().m_i) / (double)period.m_i;

   }


   inline bool on_off(const integral_duration & period) const
   {

      return (elapsed().m_i % period.m_i) < half().m_i;

   }


   inline bool on_off(const integral_duration & period, double dRate) const
   {

      return (elapsed().m_i % period.m_i) < period.m_i * dRate;

   }


   operator class ::wait const () { return this->total_milliseconds(); }




   integral_duration operator %(const BASE_TYPE & duration) const { return BASE_TYPE(this->m_i % duration.m_i); }
   double operator /(const BASE_TYPE & duration) const { return (double)this->m_i / (double)duration.m_i; }
   //integral_duration operator *(const BASE_TYPE & duration) const { return BASE_TYPE(this->m_i * duration.m_i); }
   integral_duration operator +(const BASE_TYPE & duration) const { return BASE_TYPE(this->m_i + duration.m_i); }
   integral_duration operator -(const BASE_TYPE & duration) const { return BASE_TYPE(this->m_i - duration.m_i); }

   integral_duration operator -() const { return BASE_TYPE(-this->m_i); }

//   bool operator ==(const BASE_TYPE & duration) const { return this->m_i == duration.m_i; }
//   bool operator >(const BASE_TYPE & duration) const { return this->m_i > duration.m_i; }
//   bool operator >=(const BASE_TYPE & duration) const { return this->m_i >= duration.m_i; }
//   bool operator <(const BASE_TYPE & duration) const { return this->m_i < duration.m_i; }
//   bool operator <=(const BASE_TYPE & duration) const { return this->m_i <= duration.m_i; }
//   bool operator !=(const BASE_TYPE & duration) const { return this->m_i != duration.m_i; }


   string get_string() const
   {

      string str;

      to_string(str, (const typename DURATION::BASE_TYPE &) *this);

      return str;

   }

};


template < primitive_floating FLOATING, typename DURATION >
integral_duration < DURATION > operator * (FLOATING floating, const integral_duration < DURATION > & integralduration)
{

   return (DURATION::BASE_TYPE) (DURATION::BASE_TYPE::BASE_TYPE)(floating * integralduration.m_i);

}


template < primitive_integral INTEGRAL, typename DURATION >
integral_duration < DURATION > operator * (INTEGRAL integral, const integral_duration < DURATION > & integralduration)
{

   return (DURATION::BASE_TYPE)(DURATION::BASE_TYPE::BASE_TYPE)(integral * integralduration.m_i);

}




//template < primitive_floating FLOATING, typename DURATION >
//floating_frequency operator * (FLOATING floating, const integral_duration < DURATION > & integralduration)
//{
//
//   return (::f64)(floating / integralduration.m_i);
//
//}
