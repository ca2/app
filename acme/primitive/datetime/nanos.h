//
// Created by camilo on 2020-11-16. <3ThomasBS_ [ THE ONE GOD ]
//

class CLASS_DECL_ACME nanos
{
public:


   ::i64    m_iNanoseconds;


   nanos() { m_iNanoseconds = 0; }
   nanos(::i64 i) { m_iNanoseconds = i; }
   nanos(const secs & secs) { m_iNanoseconds = secs.m_iSeconds * 1'000'000'000; }
   nanos(const millis & millis) { m_iNanoseconds = millis.m_iMilliseconds * 1'000'000; }
   nanos(const micros & micros) { m_iNanoseconds = micros.m_iMicroseconds * 1'000; }
   nanos(const nanos & nanos) { m_iNanoseconds = nanos.m_iNanoseconds; }
   nanos(const duration & duration);


   nanos & operator = (const nanos & nanos) { m_iNanoseconds = nanos.m_iNanoseconds; return *this; }


};



inline micros::micros(const nanos & nanos) { m_iMicroseconds = nanos.m_iNanoseconds / 1'000;  }

inline millis::millis(const nanos & nanos) { m_iMilliseconds = nanos.m_iNanoseconds / 1'000'000;  }

inline secs::secs(const nanos & nanos) { m_iSeconds = nanos.m_iNanoseconds / 1'000'000'000; }


inline nanos operator "" _ns(unsigned long long int u) { return (::i64) u; }



