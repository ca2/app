//
// Created by camilo on 2020-11-16. <3ThomasBS_ [ THE ONE GOD ]
//

class CLASS_DECL_ACME nanos
{
public:


   ::i16    m_iNanoseconds;


   nanos() { m_iNanoseconds = 0; }
   nanos(::i64 i) { m_iNanoseconds = i; }


   nanos & operator = (const secs & secs) { m_iNanoseconds = secs.m_iSeconds * 1'000'000'000; return *this; }
   nanos & operator = (const millis & millis) { m_iNanoseconds = millis.m_iMilliseconds * 1'000'000; return *this; }
   nanos & operator = (const micros & micros) { m_iNanoseconds = micros.m_iMicroseconds * 1'000; return *this; }
   nanos & operator = (const nanos & nanos) { m_iNanoseconds = nanos.m_iNanoseconds; return *this; }
   nanos & operator = (const duration & duration);
   nanos & operator = (::i64 i) { m_iNanoseconds = i; return *this; }

};



inline micros & micros::operator = (const nanos & nanos) { m_iMicroseconds = nanos.m_iNanoseconds / 1'000; return *this; }


inline millis & millis::operator = (const nanos & nanos) { m_iMilliseconds = nanos.m_iNanoseconds / 1'000'000; return *this; }

inline secs & secs::operator = (const nanos & nanos) { m_iSeconds = nanos.m_iNanoseconds / 1'000'000'000; return *this; }


inline nanos operator "" _ns(unsigned long long int u) { return (::i64) u; }



