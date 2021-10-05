// Refactored/Merged by camilon on 2021-10-04 07:00 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once



class CLASS_DECL_ACME hour :
   public duration
{
public:


   hour() : hour(1) {}


   hour(const ::duration & duration) : ::duration(duration) {}


   template < primitive_integral INTEGRAL >
   hour(INTEGRAL integral) : ::duration::duration(e_raw, integral * 3'600) {}


   template < primitive_floating FLOATING >
   hour(FLOATING floating) : ::duration(e_raw, (::i64)(floating * 3'600.0), (::i64)(fmod(floating * 3'600.0, 1.0) * 1'000'000'000.0)) {}


   bool done() const { return integral_hour() >= 1; }


};


inline hour operator "" _hour(unsigned long long int u) { return u; }
inline hour operator "" _hour(long double d) { return d; }



