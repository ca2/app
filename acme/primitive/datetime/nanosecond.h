//
// Refactored/Merged by camilon on 2021-10-04 06:45 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
// Created by camilo on 2020-11-16. <3ThomasBS_ [ THE ONE GOD ]
//



class CLASS_DECL_ACME nanosecond :
   public duration
{
public:


   nanosecond() : nanosecond(1) {}


   nanosecond(const ::duration & duration) : ::duration(duration) {}


   template < primitive_integral INTEGRAL >
   nanosecond(INTEGRAL integral) : ::duration(e_raw, integral / 1'000'000'000, (integral % 1'000'000) * 1'000) {}


   template < primitive_floating FLOATING >
   nanosecond(FLOATING floating) : ::duration(e_raw, (::i64)(floating/ 1'000'000'000.0), (::i64)(fmod(floating, 1'000'000'000.0))) {}


   bool done() const { return integral_nanosecond() >= 1; }


};



inline nanosecond operator "" _ns(unsigned long long int u) { return (::i64)u; }
inline nanosecond operator "" _ηs(unsigned long long int u) { return (::i64)u; }



//class CLASS_DECL_ACME nanosecond
//{
//public:
//
//
//   ::i64    m_i;
//
//
//   nanosecond() { m_i = 0; }
//   nanosecond(::i64 i) { m_i = i; }
//   nanosecond(const second & second) { m_i = second.m_i * 1'000'000'000; }
//   nanosecond(const millisecond & millisecond) { m_i = millisecond.m_i * 1'000'000; }
//   nanosecond(const microsecond & microsecond) { m_i = microsecond.m_i * 1'000; }
//   nanosecond(const nanosecond & nanosecond) { m_i = nanosecond.m_i; }
//   nanosecond(const duration & duration);
//
//
//   nanosecond & operator = (const nanosecond & nanosecond) { m_i = nanosecond.m_i; return *this; }
//   nanosecond & operator -= (const duration & duration) { m_i = m_i - ((::nanosecond)(duration)).m_i; return *this; }
//   nanosecond & operator += (const duration & duration) { m_i = m_i + ((::nanosecond)(duration)).m_i; return *this; }
//
//   void sleep() const;
//   
//   void Now() { m_i = ::_get_nanos(); }
//
//
//};
//
//
//
//inline microsecond::microsecond(const nanosecond & nanosecond) { m_i = nanosecond.m_i / 1'000;  }
//
//inline millisecond::millisecond(const nanosecond & nanosecond) { m_i = nanosecond.m_i / 1'000'000;  }
//
//inline second::second(const nanosecond & nanosecond) { m_i = nanosecond.m_i / 1'000'000'000; }
//
//
//inline nanosecond operator "" _ns(unsigned long long int u) { return (::i64) u; }
//
//
//inline nanosecond operator -(const ::nanosecond& nanos1, const ::nanosecond& nanos2) 
//{
//
//   return nanos1.m_i - nanos2.m_i;
//
//}
//
//
//inline nanosecond operator +(const ::nanosecond& nanos1, const ::nanosecond& nanos2)
//{
//
//   return nanos1.m_i + nanos2.m_i;
//
//}
//
//
//
//
//
//template < primitive_number NUMBER >
//inline nanosecond operator *(const ::nanosecond& nanosecond, const NUMBER& number)
//{
//
//   return (::i64)(nanosecond.m_i * number);
//
//}
//
//
//template < primitive_number NUMBER >
//inline nanosecond operator /(const ::nanosecond& nanosecond, const NUMBER& number)
//{
//
//   return (::i64)(nanosecond.m_i / number);
//
//}
//


inline ::nanosecond first_nanosecond() { return _first_nanosecond(); }
inline ::nanosecond get_nanosecond() { return _get_nanosecond(); }






inline ::duration duration::now() { return get_nanosecond(); }



