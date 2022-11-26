#pragma once


inline ::string to_string(const integral_time < ::integral_second_t > & time)
{

   return string_format("%llds", time.m_i);

}


inline ::string as_string(const integral_time < ::integral_millisecond_t >& time)
{

   return string_format("%lldms", time.m_i);

}


