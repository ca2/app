// Refactored/Merged by camilon on 2021-10-04 07:00 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
#pragma once


class CLASS_DECL_ACME hour :
   public time
{
public:

   
   using timeclass ::time;

   hour() : time(e_raw, 3'600) {}
   hour(const class time & time) : class ::time(time) {}
   template < primitive_integral INTEGRAL >
   hour(INTEGRAL integral) : time(::integral_hour(integral)) { }
   template < primitive_floating FLOATING >
   hour(FLOATING floating) : time(::floating_hour(floating)) { }
   
   
   bool done() const { return integral_hour().m_i >= 1; }


};


//inline ::hour first_hour() { return class ::time::first(); }
inline ::hour get_hour() { return class ::time::now(); }




