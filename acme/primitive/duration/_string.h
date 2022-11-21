#pragma once


inline ::string to_string(const integral_duration < ::integral_second_t > & duration)
{

   return string_format("%llds", duration.m_i);

}


inline ::string as_string(const integral_duration < ::integral_millisecond_t >& duration)
{

   return string_format("%lldms", duration.m_i);

}


