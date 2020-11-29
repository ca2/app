//
// Created by camilo on 2020-11-16. <3Tbs_!!
//


class CLASS_DECL_ACME secs
{
public:


   ::i64       m_iSeconds;


   secs() { m_iSeconds = 0; }
   secs(::i64 i) { m_iSeconds = i; }
   secs(const secs & secs) { m_iSeconds = secs.m_iSeconds; }
   secs(const millis & millis);
   secs(const micros & micros);
   secs(const nanos & nanos);
   secs(const duration & duration);


   secs & operator = (const secs & secs) { m_iSeconds = secs.m_iSeconds; return *this; }

   void sleep() const;

};


inline secs operator "" _s(unsigned long long int u) { return (::i64) u; }



