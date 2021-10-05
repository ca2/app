//
// Refactored/Merged by camilon on 2021-10-04 06:45 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
// Created by camilo on 2020-11-16. <3TBS_ [ THE ONLY ] [ THE GOD ] [ THE MAN ]
//
#pragma once


class CLASS_DECL_ACME microsecond :
   public duration
{
public:


   microsecond() : microsecond(1) {}


   microsecond(const ::duration & duration) : ::duration(duration) {}


   template < primitive_integral INTEGRAL >
   microsecond(INTEGRAL integral) : ::duration(e_raw, integral / 1'000'000, (integral % 1'000'000) * 1'000) {}


   template < primitive_floating FLOATING >
   microsecond(FLOATING floating) : ::duration(e_raw, (::i64)(floating / 1'000'000.0), (::i64)(fmod(floating, 1'000'000.0) * 1'000.0)) {}


   bool done() const { return integral_microsecond() >= 1; }


};


inline microsecond operator "" _us(unsigned long long int u) { return (::i64) u; }
inline microsecond operator "" _μs(unsigned long long int u) { return (::i64) u; }


//template < primitive_number NUMBER >
//inline microsecond operator *(const ::microsecond& microsecond, const NUMBER& number)
//{
//
//   return (::i64)(microsecond.m_i * number);
//
//}
//
//
//template < primitive_number NUMBER >
//inline microsecond operator /(const ::microsecond& microsecond, const NUMBER& number)
//{
//
//   return (::i64)(microsecond.m_i / number);
//
//}



inline ::i64 _first_microsecond();
inline ::i64 _get_microsecond();
inline double _microsecond() { return _get_nanosecond() / 1'000.0; }


inline ::microsecond first_microsecond() { return _first_microsecond(); }
inline ::microsecond get_microsecond() { return _get_microsecond(); }



