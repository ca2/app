// Refactored/Merged by camilon on 2021-10-04 06:45 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once


class CLASS_DECL_ACME millisecond :
   public time
{
public:


   using timeclass ::time;

   millisecond() : time(e_raw, 0, 1'000'000) {}
   millisecond(const class time & time) : class ::time(time) {}
   template < primitive_integral INTEGRAL >
   millisecond(INTEGRAL integral) : time(::integral_millisecond(integral)) { }
   template < primitive_floating FLOATING >
   millisecond(FLOATING floating) : time(::floating_millisecond(floating)) { }


   bool done() const { return integral_millisecond().m_i >= 1; }


};


//inline class ::time first_class ::time() { return class ::time::first(); }
inline ::millisecond get_millisecond() { return class ::time::now(); }


