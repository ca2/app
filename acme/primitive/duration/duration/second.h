//
// Refactored/Merged by camilon on 2021-10-04 06:45 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
// // Created by camilo on 2020-11-16. <3Tbs_!!
//


class CLASS_DECL_ACME second :
   public duration
{
public:

   
   using duration::duration;


   second() : duration(e_raw, 1) {}
   second(const ::duration & duration) : ::duration(duration) {}
   template < primitive_integral INTEGRAL >
   second(INTEGRAL integral) : duration(::integral_second(integral)) { }
   template < primitive_floating FLOATING >
   second(FLOATING floating) : duration(::floating_second(floating)) { }

   bool done() const { return integral_second() >= 1_s; }


};


//inline ::second first_second() { return ::duration::first(); }
inline ::second get_second() { return ::duration::now(); }



