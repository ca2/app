//
// Recreated by camilo on 2021-10-05 13:01 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
// Refactored/Merged by camilo on 2021-10-04 06:45 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
// Created by camilo on 2020-11-16. <3ThomasBS_ [ THE ONE GOD ]
//


class CLASS_DECL_ACME integral_nanosecond_t :
   public INTEGRAL_NANOSECOND
{
public:


   using BASE_TYPE = INTEGRAL_NANOSECOND;


   integral_nanosecond_t(INTEGRAL_NANOSECOND nanosecond = {}): INTEGRAL_NANOSECOND(nanosecond) {}


   INTEGRAL_SECOND seconds() const { return INTEGRAL_SECOND(m_i / 1'000'000'000); }
   INTEGRAL_NANOSECOND nanoseconds() const { return INTEGRAL_NANOSECOND(m_i % 1'000'000'000); }
   INTEGRAL_MILLISECOND total_milliseconds() const { return INTEGRAL_MILLISECOND(m_i / 1'000'000); }


};


using integral_nanosecond = integral_duration < integral_nanosecond_t >;


constexpr INTEGRAL_NANOSECOND operator "" _ns(unsigned long long int u) { return (INTEGRAL_NANOSECOND)u; }


CLASS_DECL_ACME INTEGRAL_NANOSECOND get_integral_nanosecond();

inline INTEGRAL_MICROSECOND get_integral_microsecond() { return INTEGRAL_MICROSECOND(get_integral_nanosecond().m_i / 1'000); }

inline INTEGRAL_MILLISECOND get_integral_millisecond() { return INTEGRAL_MILLISECOND(get_integral_nanosecond().m_i / 1'000'000); }

inline INTEGRAL_SECOND get_integral_second() { return INTEGRAL_SECOND(get_integral_nanosecond().m_i / 1'000'000'000); }

inline INTEGRAL_MINUTE get_integral_minute() { return INTEGRAL_MINUTE(get_integral_nanosecond().m_i / 60'000'000'000); }

inline INTEGRAL_HOUR get_integral_hour() { return INTEGRAL_HOUR(get_integral_nanosecond().m_i / 3'600'000'000'000); }

inline INTEGRAL_DAY get_integral_day() { return INTEGRAL_DAY(get_integral_nanosecond().m_i / 86'400'000'000'000); }


template <  >
inline integral_nanosecond now<integral_nanosecond>()
{

   return get_integral_nanosecond();

}




