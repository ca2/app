// Created by camilo on 2021-10-05 12:31 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once


template < typename DURATION >
class floating_duration :
   public DURATION
{
public:


   using BASE_DURATION = DURATION;
   using BASE_TYPE = typename BASE_DURATION::BASE_TYPE;


   using DURATION::DURATION;


//   floating_duration(const floating_duration & type) :
//      DURATION(type)
//   {
//
//   }

   floating_duration(enum_now)
   {

      Now();

   }


   inline floating_duration elapsed(const floating_duration & durationStop = ::now < DURATION >()) const
   {

      return durationStop.m_d - this->m_d;

   }


   inline floating_duration update_elapsed(const floating_duration & durationStop = e_now)
   {

      auto elapsed = durationStop - *this;

      operator=(durationStop);

      return elapsed;

   }


   inline floating_duration half() const
   {

      return this->m_d/ 2.0;

   }


   inline double sawtooth(const floating_duration & period)
   {

      return fmod(elapsed().m_d, period.m_d) / period.m_d;

   }

   
   inline class floating_duration & Now() 
   { 
      
      return operator=(::now <floating_duration>()); 
   
   }


   inline double period_rate(const floating_duration & period)
   {

      return elapsed().m_d / period.m_d;

   }


   inline bool on_off(const floating_duration & period) const
   {

      return fmod(elapsed() , period.m_d) < half();


   }


   inline bool on_off(const floating_duration & period, double dRate) const
   {

      return fmod(elapsed().m_d, period.m_d) < period.m_d * dRate;


   }

   

   template < primitive_floating FLOATING >
   floating_duration operator %(FLOATING floating) const { return typename DURATION::BASE_TYPE(fmod(this->m_d, floating)); }

   template < primitive_floating FLOATING >
   floating_duration operator /(FLOATING floating) const { return typename DURATION::BASE_TYPE(this->m_d / floating); }

   template < primitive_floating FLOATING >
   floating_duration operator *(FLOATING floating) const { return typename DURATION::BASE_TYPE(this->m_d * floating); }

   template < primitive_floating FLOATING >
   floating_duration operator +(FLOATING floating) const { return typename DURATION::BASE_TYPE(this->m_d + floating); }

   template < primitive_floating FLOATING >
   floating_duration operator -(FLOATING floating) const { return typename DURATION::BASE_TYPE(this->m_d - floating); }


   floating_duration operator %(const BASE_TYPE & duration) const { return typename DURATION::BASE_TYPE(fmod(this->m_d, duration.m_d)); }
   double operator /(const BASE_TYPE & duration) const { return this->m_d / duration.m_d; }
   // floating_duration operator *(const BASE_TYPE & duration) const { return BASE_TYPE(this->m_d * duration.m_d); }
   floating_duration operator +(const BASE_TYPE & duration) const { return typename DURATION::BASE_TYPE(this->m_d + duration.m_d); }
   floating_duration operator -(const BASE_TYPE & duration) const { return typename DURATION::BASE_TYPE(this->m_d - duration.m_d); }

   
   floating_duration operator -() const { return typename DURATION::BASE_TYPE(-this->m_d); }


   bool operator ==(const BASE_TYPE & duration) const { return this->m_d == duration.m_d; }
   bool operator >(const BASE_TYPE & duration) const { return this->m_d > duration.m_d; }
   bool operator >=(const BASE_TYPE & duration) const { return this->m_d >= duration.m_d; }
   bool operator <(const BASE_TYPE & duration) const { return this->m_d < duration.m_d; }
   bool operator <=(const BASE_TYPE & duration) const { return this->m_d <= duration.m_d; }
   bool operator !=(const BASE_TYPE & duration) const { return this->m_d != duration.m_d; }


};



