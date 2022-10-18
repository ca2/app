// Created by camilo on 2021-10-05 15:07 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once


template < typename DURATION >
inline class ::wait integral_duration < DURATION >::wait() const
{ 

   return ::duration(*this).integral_microsecond().m_i / 1'000'000.0;

}


DEFINE_COMPARISON_WITH_DURATION(time)



