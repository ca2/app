// Refactored/Merged by camilon on 2021-10-04 07:00 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once



class CLASS_DECL_ACME day :
   public duration
{
public:


   day() : day(1) {}


   day(const ::duration & duration) : ::duration(duration) {}


   template < primitive_integral INTEGRAL >
   day(INTEGRAL integral) : ::duration::duration(e_raw, integral * 86'400) {}


   template < primitive_floating FLOATING >
   day(FLOATING floating) : ::duration(e_raw, (::i64)(floating * 86'400.0), (::i64)(fmod(floating * 86'400.0, 1.0) * 1'000'000'000.0)) {}


   bool done() const { return integral_day() >= 1; }


};


inline day operator "" _day(unsigned long long int u) { return u; }
inline day operator "" _day(long double d) { return d; }



