// Refactored/Merged by camilon on 2021-10-04 06:45 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
#pragma once


class CLASS_DECL_ACME millisecond :
   public duration
{
public:


   using duration::duration;

   millisecond() : duration(e_raw, 0, 1'000'000) {}
   millisecond(const ::duration & duration) : ::duration(duration) {}
   template < primitive_integral INTEGRAL >
   millisecond(INTEGRAL integral) : duration(::integral_millisecond(integral)) { }
   template < primitive_floating FLOATING >
   millisecond(FLOATING floating) : duration(::floating_millisecond(floating)) { }


   bool done() const { return integral_millisecond() >= 1_ms; }


};


//inline ::duration first_::duration() { return ::duration::first(); }
inline ::millisecond get_millisecond() { return ::duration::now(); }


