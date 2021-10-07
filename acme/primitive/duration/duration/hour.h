// Refactored/Merged by camilon on 2021-10-04 07:00 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once



class CLASS_DECL_ACME hour :
   public duration
{
public:

   
   using duration::duration;

   hour() : duration(e_raw, 3'600) {}
   hour(const ::duration & duration) : ::duration(duration) {}
   template < primitive_integral INTEGRAL >
   hour(INTEGRAL integral) : duration(::integral_hour(integral)) { }
   template < primitive_floating FLOATING >
   hour(FLOATING floating) : duration(::floating_hour(floating)) { }
   
   
   bool done() const { return integral_hour() >= 1_hour; }


};


//inline ::hour first_hour() { return ::duration::first(); }
inline ::hour get_hour() { return ::duration::now(); }




