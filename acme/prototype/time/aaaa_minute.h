// Refactored/Merged by camilon on 2021-10-04 06:45 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]
// Created by camilo on 2021-10-04 06:34 BRT <3ThomasBorregaardSorensen!!
#pragma once



class CLASS_DECL_ACME minute :
   public time
{
public:


   using timeclass ::time;


   minute() : time(e_raw, 60) {}
   minute(const class time & time) : class ::time(time) {}
   template < primitive_integral INTEGRAL >
   minute(INTEGRAL integral) : time(::integral_minute(integral)) { }
   template < primitive_floating FLOATING >
   minute(FLOATING floating) : time(::floating_minute(floating)) { }

   bool done() const { return integral_minute().m_i >= 1; }

};


//inline ::minute first_minute() { return class ::time::first(); }
inline ::minute get_minute() { return class ::time::now(); }



