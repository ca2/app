#include "framework.h"
//#include <math.h>

//#define SECOND_NANOS 1000




void duration::normalize()
{

   m_secs.m_i += m_nanos.m_i / SECOND_NANOS;

   m_nanos.m_i %= SECOND_NANOS;

   int iSecondSign = ::papaya::sgn(m_secs.m_i);

   int iNanosecondsSign = ::papaya::sgn(m_nanos.m_i);

   if (iSecondSign == -iNanosecondsSign && iSecondSign != 0)
   {

      m_secs.m_i -= iSecondSign;

      m_nanos.m_i += iSecondSign * SECOND_NANOS;

   }

}





//duration duration::operator - (const duration & duration) const
//{
//
//   return ::duration(m_i - duration.m_i, m_i - duration.m_i);
//
//}
//
//
//duration duration::operator + (const duration & duration) const
//{
//
//   return ::duration(m_i + duration.m_i, m_i + duration.m_i);
//
//}





//duration::duration(e_duration eduration)
//{
//
//   m_eduration = eduration;
//
//}



void duration::set(i64 i, enum_unit eunit)
{

   switch (eunit)
   {
   case unit_nanos:
      raw_set(i / (1000 * 1000 * 1000), i % (1000 * 1000 * 1000));
      break;
   case unit_micros:
      raw_set(i / (1000 * 1000), (i / 1000) % (1000 * 1000 * 1000));
      break;
   case unit_millis:
      raw_set(i / 1000, (i / (1000 * 1000)) % (1000 * 1000 * 1000));
      break;
   case unit_seconds:
      raw_set(i, 0);
      break;
   case unit_minutes:
      raw_set(i * 60, 0);
      break;
   case unit_hours:
      raw_set(i * 60 * 60, 0);
      break;
   default:
      __throw(error_invalid_argument, "Unknown time duration unit");

   };

}

void duration::set(long double d, enum_unit eunit)
{

   switch (eunit)
   {
   case unit_nanos:
      fset(0.0, d);
      break;
   case unit_micros:
      fset(0.0, (d / 1000.0));
      break;
   case unit_millis:
      fset(0.0, d / (1000.0 * 1000.0));
      break;
   case unit_seconds:
      fset(d, 0.0);
      break;
   case unit_minutes:
      fset(d * 60.0, 0.0);
      break;
   case unit_hours:
      fset(d * 60.0 * 60.0, 0.0);
      break;
   default:
      __throw(error_invalid_argument, "Unknown time duration unit");

   };
}




void duration::fset(long double d, double dNano)
{

   dNano += fmod(d, 1.0) * 1000.0 * 1000.0 * 1000.0;

   raw_set((i64)(floor(d) + floor((dNano / (1000.0 * 1000.0 * 1000.0)))), (i64)fmod(dNano, 1000.0 * 1000.0 * 1000.0));

}


void duration::fset(long double d)
{

   raw_set((i64)floor(d), (i64)(fmod(d, 1.0) * 1'000'000'000.0));

}


//CLASS_DECL_ACME void sleep(const duration & duration)
//{
//
//   auto tickDuration = duration.u32_millis();
//
//   ::sleep((::u32)tickDuration);
//

//}





void duration::sleep() const
{

   if (m_secs.m_i >= 20)
   {

      ::preempt(m_secs);

   }
   else if (m_secs.m_i > 0 || m_nanos.m_i > 20'000'000)
   {

      ::preempt(millis());

   }
   else if (m_nanos.m_i > 20'000)
   {

      ::preempt(micros());

   }
   else
   {

      ::preempt(nanos());

   }

}






CLASS_DECL_ACME duration __random(const duration & d1, const duration & d2)
{

   auto iSeconds = __random(d1.m_secs.m_i, d2.m_secs.m_i);

   return duration(iSeconds, __random(
                                      (::i64)(((::i64)iSeconds > d1.m_secs.m_i) ? 0 : d1.m_nanos.m_i),
                                      (::i64)(((::i64)iSeconds < d2.m_secs.m_i) ? 999'999'999 : d2.m_nanos.m_i)));

}
