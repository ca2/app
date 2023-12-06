// Created by camilo on 2023-11-24 14:58 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "primitive.h"
#include "acme/platform/system.h"
#include "acme/primitive/mathematics/mathematics.h"


namespace primitive
{


   primitive::primitive()
   {


   }


   primitive::~primitive()
   {


   }


   void primitive::on_initialize_particle()
   {

      ::particle::on_initialize_particle();

      if (!system()->m_pmathematics)
      {

         throw ::exception(error_wrong_state);

      }

      m_pmathematics = system()->m_pmathematics;

   }


   class time primitive::random(const class time & d1, const class time & d2)
   {

      auto iSeconds = m_pmathematics->random(d1.m_iSecond, d2.m_iSecond);

      class ::time time(iSeconds, m_pmathematics->random(
         (::i64)(((::i64)iSeconds > d1.m_iSecond) ? 0 : d1.m_iNanosecond),
         (::i64)(((::i64)iSeconds < d2.m_iSecond) ? 999'999'999 : d2.m_iNanosecond)));

      return time;

   }



} // namespace primitive


