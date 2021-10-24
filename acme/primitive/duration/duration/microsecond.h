//
// Refactored/Merged by camilon on 2021-10-04 06:45 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
// Created by camilo on 2020-11-16. <3TBS_ [ THE ONLY ] [ THE GOD ] [ THE MAN ]
//
#pragma once


class CLASS_DECL_ACME microsecond :
   public duration
{
public:


   using duration::duration;
   
   microsecond() : duration(e_raw, 0, 1'000) {}
   microsecond(const ::duration & duration) : ::duration(duration) {}
   template < primitive_integral INTEGRAL >
   microsecond(INTEGRAL integral) : duration(::integral_microsecond(integral)) { }
   template < primitive_floating FLOATING >
   microsecond(FLOATING floating) : duration(::floating_microsecond(floating)) { }


   bool done() const { return integral_microsecond() >= 1_µs; }


};


//inline ::microsecond first_microsecond() { return ::duration::first(); }
inline ::microsecond get_microsecond() { return ::duration::now(); }



