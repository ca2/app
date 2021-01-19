#include "framework.h"
//#include <math.h>

//#define SECOND_NANOS 1000




void duration::normalize()
{

   m_secs.m_iSeconds += m_nanos.m_iNanoseconds / SECOND_NANOS;

   m_nanos.m_iNanoseconds %= SECOND_NANOS;

   int iSecondSign = ::papaya::sgn(m_secs.m_iSeconds);

   int iNanosecondsSign = ::papaya::sgn(m_nanos.m_iNanoseconds);

   if (iSecondSign == -iNanosecondsSign && iSecondSign != 0)
   {

      m_secs.m_iSeconds -= iSecondSign;

      m_nanos.m_iNanoseconds += iSecondSign * SECOND_NANOS;

   }

}





//duration duration::operator - (const duration & duration) const
//{
//
//   return ::duration(m_iSeconds - duration.m_iSeconds, m_iNanoseconds - duration.m_iNanoseconds);
//
//}
//
//
//duration duration::operator + (const duration & duration) const
//{
//
//   return ::duration(m_iSeconds + duration.m_iSeconds, m_iNanoseconds + duration.m_iNanoseconds);
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
      __throw(invalid_argument_exception("Unknown time duration unit"));

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
      __throw(invalid_argument_exception("Unknown time duration unit"));

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

   if (m_secs.m_iSeconds >= 20)
   {

      ::sleep(m_secs);

   }
   else if (m_secs.m_iSeconds > 0 || m_nanos.m_iNanoseconds > 20'000'000)
   {

      ::sleep(millis());

   }
   else if (m_nanos.m_iNanoseconds > 20'000)
   {

      ::sleep(micros());

   }
   else
   {

      ::sleep(nanos());

   }

}



