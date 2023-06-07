//
// Refactored/Merged by camilon on 2021-10-04 06:45 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]
// Created by camilo on 2020-11-16. <3ThomasBS_ [ THE ONE GOD ]
//


class CLASS_DECL_ACME nanosecond :
   public duration
{
public:


   using duration::duration;

   nanosecond() : duration(e_raw, 0, 1) {}
   nanosecond(const class ::time & time) : ::duration(duration) {}
   template < primitive_integral INTEGRAL >
   nanosecond(INTEGRAL integral) : duration(::integral_nanosecond(integral)) { }
   template < primitive_floating FLOATING >
   nanosecond(FLOATING floating) : duration(::floating_nanosecond(floating)) { }


   bool done() const { return integral_nanosecond().m_i >= 1; }


};


//CLASS_DECL_ACME ::nanosecond first_nanosecond();
CLASS_DECL_ACME ::nanosecond get_nanosecond();


//inline ::duration duration::first()
//{
//
//   return _first_integral_nanosecond();
//
//}


