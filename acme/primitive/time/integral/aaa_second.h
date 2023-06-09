//
// Recreated by camilo on 2021-10-05 13:10 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]
// Refactored/Merged by camilon on 2021-10-04 06:45 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]
// // Created by camilo on 2020-11-16. <3Tbs_!!
//

//
//class CLASS_DECL_ACME integral_second_t :
//   public integral_second
//{
//public:
//
//
//   using BASE_TYPE = integral_second;
//
//   
//   constexpr integral_second_t(integral_second second = {}) : integral_second(second) {}
//   integral_second_t(const class time & time);
//
//   integral_second seconds() const { return integral_second(m_i); }
//   integral_nanosecond nanoseconds() const { return integral_nanosecond(0); }
//   integral_millisecond total_milliseconds() const { return integral_millisecond(m_i * 1'000); }
//
//
//};
//
//
//using integral_second = integral_time < integral_second_t >;
//

template <  >
inline integral_second now<integral_second>()
{

   return get_integral_second();

}





