// Created by camilo on 2023-11-24 14:58 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "prototype.h"
#include "acme/platform/system.h"
#include "acme/prototype/mathematics/mathematics.h"


namespace prototype
{


   prototype::prototype()
   {


   }


   prototype::~prototype()
   {


   }

#ifdef DEBUG
   long long prototype::increment_reference_count()
   {

      return ::particle::increment_reference_count();

   }
   long long prototype::decrement_reference_count()
   {
      return ::particle::decrement_reference_count();
   }
#endif

   void prototype::on_initialize_particle()
   {

      ::particle::on_initialize_particle();

      if (!system()->mathematics())
      {

         throw ::exception(error_wrong_state);

      }

      m_pmathematics = system()->mathematics();

   }


   class time prototype::random(const class time & d1, const class time & d2)
   {

      auto iSeconds = m_pmathematics->random(d1.m_iSecond, d2.m_iSecond);

      class ::time time(iSeconds, m_pmathematics->random(
         (long long)(((long long)iSeconds > d1.m_iSecond) ? 0 : d1.m_iNanosecond),
         (long long)(((long long)iSeconds < d2.m_iSecond) ? 999'999'999 : d2.m_iNanosecond)));

      return time;

   }



} // namespace prototype


