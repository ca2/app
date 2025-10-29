//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2022-11-05 15:48 BRT.
#include "framework.h"



//::string & copy(::string & str, const integral_nanosecond & integral)
//{
//
//   str.formatf("%" PRId64 "ns", integral.m_i);
//
//   return str;
//
//}
//
//
//::string & copy(::string & str, const integral_microsecond & integral)
//{
//
//   str.formatf("%" PRId64 "μs", integral.m_i);
//
//   return str;
//
//}
//
//
//::string & copy(::string & str, const integral_millisecond & integral)
//{
//
//   str.formatf("%" PRId64 "ms", integral.m_i);
//
//   return str;
//
//}
//
//
//::string & copy(::string & str, const integral_second & integral)
//{
//
//   str.formatf("%" PRId64 "s", integral.m_i);
//
//   return str;
//
//}
//
//
//::string & copy(::string & str, const integral_minute & integral)
//{
//
//   str.formatf("%" PRId64 "minute(s)", integral.m_i);
//
//   return str;
//
//}
//
//
//::string & copy(::string & str, const integral_hour & integral)
//{
//
//   str.formatf("%" PRId64 "hour(s)", integral.m_i);
//
//   return str;
//
//}
//
//
//::string & copy(::string & str, const integral_day & integral)
//{
//
//   str.formatf("%" PRId64 "day(s)", integral.m_i);
//
//   return str;
//
//}


CLASS_DECL_ACME ::string _017Time(const class ::time& time)
{

   if (time.is_null())
   {

      return "0";

   }

   auto dMillis = time.floating_millisecond();

   if (dMillis >= 1'000.0)
   {

      auto dSeconds = dMillis / 1'000.0;

      return ::string_formatf("%0.2fs", dSeconds);

   }
   else if (dMillis >= 1.0)
   {

      return ::string_formatf("%0.2fms", dMillis);

   }
   else
   {

      auto dMicros = dMillis * 1'000.0;

      if (dMicros >= 1.0)
      {

         return ::string_formatf("%0.2fμs", dMicros);

      }
      else
      {

         auto dNanos = dMicros * 1'000.0;

         return ::string_formatf("%0.2fηs", dNanos);

      }

   }

}



