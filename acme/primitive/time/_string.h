#pragma once


inline ::string as_string(const integral_time < ::integral_second > & time)
{

   return string_format("%llds", time.m_i);

}


inline ::string as_string(const integral_time < ::integral_millisecond >& time)
{

   return string_format("%lldms", time.m_i);

}


