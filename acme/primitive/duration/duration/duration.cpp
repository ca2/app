#include "framework.h"
#include "acme/primitive/mathematics/_random.h"
//#include "acme/primitive/mathematics/numeric.h"


void duration::normalize()
{

   m_iSecond += m_iNanosecond / SECOND_NANOS;

   m_iNanosecond %= SECOND_NANOS;

   int iSecondSign = ::numeric::sign(m_iSecond);

   int iNanosecondSign = ::numeric::sign(m_iNanosecond);

   if (iSecondSign == -iNanosecondSign && iSecondSign != 0)
   {

      m_iSecond -= iSecondSign;

      m_iNanosecond += iSecondSign * SECOND_NANOS;

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
      throw_exception(error_bad_argument, "Unknown time duration unit");

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
      throw_exception(error_bad_argument, "Unknown time duration unit");

   };
}




void duration::fset(long double d, double dNano)
{

   dNano += fmod(d, 1.0) * 1000.0 * 1000.0 * 1000.0;

   raw_set((time_t)(floor(d) + floor((dNano / (1000.0 * 1000.0 * 1000.0)))), (long)fmod(dNano, 1000.0 * 1000.0 * 1000.0));

}


void duration::fset(long double d)
{

   raw_set((time_t)floor(d), (long)(fmod(d, 1.0) * 1'000'000'000.0));

}


//CLASS_DECL_ACME void sleep(const duration & duration)
//{
//
//   auto tickDuration = duration.u32_millis();
//
//   ::sleep((::u32)tickDuration);
//

//}





//void duration::sleep() const
//{
//
//   if (m_secs.m_i >= 20)
//   {
//
//      ::preempt(m_secs);
//
//   }
//   else if (m_secs.m_i > 0 || m_nanos.m_i > 20'000'000)
//   {
//
//      ::preempt(::duration());
//
//   }
//   else if (m_nanos.m_i > 20'000)
//   {
//
//      ::preempt(microsecond());
//
//   }
//   else
//   {
//
//      ::preempt(nanosecond());
//
//   }
//
//}
//





CLASS_DECL_ACME duration __random(const duration & d1, const duration & d2)
{

   auto iSeconds = __random(d1.m_iSecond, d2.m_iSecond);

   return duration(iSeconds, __random(
                                      (::i64)(((::i64)iSeconds > d1.m_iSecond) ? 0 : d1.m_iNanosecond),
                                      (::i64)(((::i64)iSeconds < d2.m_iSecond) ? 999'999'999 : d2.m_iNanosecond)));

}








::duration duration::half() const
{

   auto nanosecond = (m_iSecond * 1'000'000'000 + m_iNanosecond);

   auto iSecond = (::i64)(nanosecond / 1'000'000'000);

   auto iNanosecond = (long)(nanosecond % 1'000'000'000);

   return { e_raw, iSecond, iNanosecond };

}



class ::duration & duration::operator %= (const class ::duration & duration)
{

   auto nanosecondThis = m_iSecond * 1'000'000'000+ m_iNanosecond;

   auto nanosecond = duration.m_iSecond * 1'000'000'000 + duration.m_iNanosecond;

   nanosecondThis %= nanosecond;

   m_iSecond = nanosecondThis / 1'000'000'000;

   m_iNanosecond = nanosecondThis % 1'000'000'000;

   return *this;

}


class ::duration duration::operator % (const class ::duration & duration) const
{

   ::duration durationResult(*this);

   durationResult %= duration;

   return durationResult;

}


double duration::operator / (const class ::duration & duration) const
{

   auto nanosecondThis = m_iSecond * 1'000'000'000 + m_iNanosecond;

   auto nanosecond = duration.m_iSecond * 1'000'000'000 + duration.m_iNanosecond;

   return (double)nanosecondThis / (double)nanosecond;

}

