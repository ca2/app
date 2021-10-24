// Refactored/Merged by camilon on 2021-10-04 07:00 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once



class CLASS_DECL_ACME day :
   public duration
{
public:


   using duration::duration;

   day() : duration(e_raw, 86'400) {}
   day(const ::duration & duration) : ::duration(duration) {}
   template < primitive_integral INTEGRAL >
   day(INTEGRAL integral) : duration(::integral_day(integral)) { }
   template < primitive_floating FLOATING >
   day(FLOATING floating) : duration(::floating_day(floating)) { }



   bool done() const { return integral_day() >= 1_day; }


};


//inline ::day first_day() { return ::duration::first(); }
inline ::day get_day() { return ::duration::now(); }


