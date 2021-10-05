// Refactored/Merged by camilon on 2021-10-04 06:45 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
// Created by camilo on 2021-10-04 06:34 BRT <3ThomasBorregaardSørensen!!
#pragma once



class CLASS_DECL_ACME minute :
   public duration
{
public:


   minute() : minute(1) {}


   minute(const ::duration & duration) : ::duration(duration) {}


   template < primitive_integral INTEGRAL >
   minute(INTEGRAL integral) : ::duration::duration(e_raw, integral * 60) {}


   template < primitive_floating FLOATING >
   minute(FLOATING floating) : ::duration(e_raw, (::i64)(floating * 60.0), (::i64)(fmod(floating * 60.0, 1.0) * 1'000'000'000.0)) {}


};


inline minute operator "" _minute(unsigned long long int u) { return u; }
inline minute operator "" _minute(long double d) { return d; }



