#pragma once


inline void to_string(string& str, const integral_duration < ::integral_second_t > & duration)
{

   str.format("%llds", duration.m_i);

}


inline void to_string(string& str, const integral_duration < ::integral_millisecond_t >& duration)
{

   str.format("%lldms", duration.m_i);

}


