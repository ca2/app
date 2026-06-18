#include "framework.h"
#include "acme/prototype/mathematics/_random.h"
//#include "acme/prototype/mathematics/numeric.h"







//time time::operator - (const class time & time) const
//{
//
//   return ::time(m_i32 - time.m_i32, m_i32 - time.m_i32);
//
//}
//
//
//time time::operator + (const class time & time) const
//{
//
//   return ::time(m_i32 + time.m_i32, m_i32 + time.m_i32);
//
//}





//time::time(e_time etime)
//{
//
//   m_etime = etime;
//
//}


//CLASS_DECL_ACME void sleep(const class time & time)
//{
//
//   auto tickDuration = time.u32_millis();
//
//   ::sleep((::u32)tickDuration);
//

//}





//void time::sleep() const
//{
//
//   if (m_secs.m_i32 >= 20)
//   {
//
//      ::preempt(m_secs);
//
//   }
//   else if (m_secs.m_i32 > 0 || m_nanos.m_i32 > 20'000'000)
//   {
//
//      ::preempt(::time());
//
//   }
//   else if (m_nanos.m_i32 > 20'000)
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




void time::set(::f128 d, enum_unit eunit)
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
      throw_exception(error_bad_argument, "Unknown time time unit");

   };
}


void time::fset(::f128 d, ::f64 dNano)
{

   dNano += fmod(d, 1.0) * 1000.0 * 1000.0 * 1000.0;

   raw_set(
      posix_time({ posix_time_t{}, (::i64)(floor(d) + floor((dNano / (1000.0 * 1000.0 * 1000.0)))) }),
      nanosecond({nanosecond_t{}, (long)fmod(dNano, 1000.0 * 1000.0 * 1000.0)})
   );

}


void time::fset(::f128 d)
{

   raw_set(
      posix_time{ posix_time_t{}, (::i64)floor(d) },
      nanosecond{ nanosecond_t{}, (long)(fmod(d, 1.0) * 1'000'000'000.0) });

}


class ::time time::fcreate(::f128 d, ::f64 dNano)
{

   time time;

   time.fset(d, dNano);

   return time;

}


