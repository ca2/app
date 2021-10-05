//
// Refactored/Merged by camilon on 2021-10-04 06:45 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
// // Created by camilo on 2020-11-16. <3Tbs_!!
//


class CLASS_DECL_ACME second :
   public duration
{
public:


   second() : second(1) {}


   second(const ::duration & duration) : ::duration(duration) {}


   template < primitive_integral INTEGRAL >
   second(INTEGRAL integral) : ::duration(e_raw, (::i64) integral) {}


   template < primitive_floating FLOATING >
   second(FLOATING floating) : ::duration(e_raw, (::i64)(floating), (::i64)(fmod(floating, 1.0) * 1'000'000'000.0)) {}


   bool done() const { return integral_second() >= 1; }


};


inline second operator "" _s(unsigned long long int u) { return u; }
inline second operator "" _s(long double d) { return d; }


inline ::i64 _first_second();
inline ::i64 _get_second();
inline double _second() { return _get_nanosecond() / 1'000'000'000.0; }


inline ::second first_second() { return _first_second(); }
inline ::second get_second() { return _get_second(); }



