//
// Created by camilo on 2020-11-16. <3ThomasBS_ [ THE ONE GOD ]
//

class CLASS_DECL_ACME nanos
{
public:


   ::i64    m_i;


   nanos() { m_i = 0; }
   nanos(::i64 i) { m_i = i; }
   nanos(const secs & secs) { m_i = secs.m_i * 1'000'000'000; }
   nanos(const millis & millis) { m_i = millis.m_i * 1'000'000; }
   nanos(const micros & micros) { m_i = micros.m_i * 1'000; }
   nanos(const nanos & nanos) { m_i = nanos.m_i; }
   nanos(const duration & duration);


   nanos & operator = (const nanos & nanos) { m_i = nanos.m_i; return *this; }
   nanos & operator -= (const duration & duration) { m_i = m_i - ((::nanos)(duration)).m_i; return *this; }
   nanos & operator += (const duration & duration) { m_i = m_i + ((::nanos)(duration)).m_i; return *this; }

   void sleep() const;


};



inline micros::micros(const nanos & nanos) { m_i = nanos.m_i / 1'000;  }

inline millis::millis(const nanos & nanos) { m_i = nanos.m_i / 1'000'000;  }

inline secs::secs(const nanos & nanos) { m_i = nanos.m_i / 1'000'000'000; }


inline nanos operator "" _ns(unsigned long long int u) { return (::i64) u; }


inline nanos operator -(const ::nanos& nanos1, const ::nanos& nanos2) 
{

   return nanos1.m_i - nanos2.m_i;

}


inline nanos operator +(const ::nanos& nanos1, const ::nanos& nanos2)
{

   return nanos1.m_i + nanos2.m_i;

}


template < primitive_number NUMBER >
inline nanos operator *(const ::nanos& nanos, const NUMBER& number)
{

   return (::i64)(nanos.m_i * number);

}


template < primitive_number NUMBER >
inline nanos operator /(const ::nanos& nanos, const NUMBER& number)
{

   return (::i64)(nanos.m_i / number);

}





CLASS_DECL_ACME::nanos first_nano();
CLASS_DECL_ACME::nanos get_nanos();

