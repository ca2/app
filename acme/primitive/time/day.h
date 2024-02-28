// Refactored/Merged by camilon on 2021-10-04 07:00 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]
#pragma once



class CLASS_DECL_ACME day :
   public time
{
public:


   using timeclass ::time;

   day() : time(e_raw, 86'400) {}
   day(const class time & time) : class ::time(time) {}
   template < primitive_integral INTEGRAL >
   day(INTEGRAL integral) : time(::integral_day(integral)) { }
   template < primitive_floating FLOATING >
   day(FLOATING floating) : time(::floating_day(floating)) { }



   bool done() const { return integral_day().m_i >= 1; }


};


//inline ::day first_day() { return class ::time::first(); }
inline ::day get_day() { return class ::time::now(); }


