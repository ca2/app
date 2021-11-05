//
// Recreated by camilo on 2021-10-05 13:10 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
// Refactored/Merged by camilon on 2021-10-04 06:45 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
// // Created by camilo on 2020-11-16. <3Tbs_!!
//


class CLASS_DECL_ACME integral_second_t :
   public INTEGRAL_SECOND
{
public:


   using BASE_TYPE = INTEGRAL_SECOND;

   
   integral_second_t(INTEGRAL_SECOND second = {}) : INTEGRAL_SECOND(second) {}


   INTEGRAL_SECOND seconds() const { return INTEGRAL_SECOND(m_i); }
   INTEGRAL_NANOSECOND nanoseconds() const { return INTEGRAL_NANOSECOND(0); }
   INTEGRAL_MILLISECOND total_milliseconds() const { return INTEGRAL_MILLISECOND(m_i * 1'000); }


};


using integral_second = integral_duration < integral_second_t >;


template <  >
inline integral_second now<integral_second>()
{

   return get_integral_second();

}





