// Refactored/Merged by camilon on 2021-10-04 06:45 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
// Created by camilo on 2021-10-04 06:34 BRT <3ThomasBorregaardSørensen!!
#pragma once



class CLASS_DECL_ACME minute :
   public duration
{
public:


   using duration::duration;


   minute() : duration(e_raw, 60) {}
   minute(const ::duration & duration) : ::duration(duration) {}
   template < primitive_integral INTEGRAL >
   minute(INTEGRAL integral) : duration(::integral_minute(integral)) { }
   template < primitive_floating FLOATING >
   minute(FLOATING floating) : duration(::floating_minute(floating)) { }

   bool done() const { return integral_minute() >= 1_min; }

};


//inline ::minute first_minute() { return ::duration::first(); }
inline ::minute get_minute() { return ::duration::now(); }



