//
// Created by camilo on 2020-11-16. <3Tbs_!!
//


class CLASS_DECL_ACME secs
{
public:


   ::i64       m_i;


   secs() { m_i = 0; }
   secs(::i64 i) { m_i = i; }
   secs(const secs & secs) { m_i = secs.m_i; }
   secs(const millis & millis);
   secs(const micros & micros);
   secs(const nanos & nanos);
   secs(const duration & duration);


   secs & operator = (const secs & secs) { m_i = secs.m_i; return *this; }

   void sleep() const;

};


inline secs operator "" _s(unsigned long long int u) { return (::i64) u; }



template < primitive_number NUMBER >
inline secs operator *(const ::secs& secs, const NUMBER& number)
{

   return (::i64)(secs.m_i * number);

}


template < primitive_number NUMBER >
inline secs operator /(const ::secs& secs, const NUMBER& number)
{

   return (::i64)(secs.m_i / number);

}




inline ::secs first_sec();
inline ::secs get_secs();





