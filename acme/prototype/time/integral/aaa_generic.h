// Created by camilo on 2023-01-06 23:09 <3ThomasBorregaardSorensen!!
#pragma once


//#include "operator.h"

//
//namespace generic
//{
//
//
//   namespace time
//   {
//
//
//      template < integral_time_unit INTEGRAL_TIME_UNIT >
//      INTEGRAL_TIME_UNIT elapsed(const INTEGRAL_TIME_UNIT & integraltime)
//      {
//
//         return { ::time::now() - integraltime.m_i};
//
//      }
//
//
//      template < integral_time_unit INTEGRAL_TIME_UNIT >
//      inline bool on_off(const INTEGRAL_TIME_UNIT & integraltime, const INTEGRAL_TIME_UNIT & period)
//      {
//
//         return (elapsed(integraltime).m_i % period.m_i) < (period.m_i / 2);
//
//      }
//
//
//      template < integral_time_unit INTEGRAL_TIME_UNIT >
//      inline ::f64 period_rate(const INTEGRAL_TIME_UNIT & integraltime, const INTEGRAL_TIME_UNIT & period)
//      {
//
//         return (::f64)(elapsed(integraltime).m_i) / (::f64)(period.m_i);
//
//      }
//
//
//   } // namespace time
//
//
//} // namespace generic
//
//
