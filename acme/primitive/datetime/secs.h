//
// Created by camilo on 2020-11-16. <3Tbs_!!
//


class CLASS_DECL_ACME secs
{
public:


   ::i64       m_iSeconds;


   secs() { m_iSeconds = 0; }
   secs(::i64 i) { m_iSeconds = i; }


   secs & operator = (const secs & secs) { m_iSeconds = secs.m_iSeconds; return *this; }
   secs & operator = (const millis & millis);
   secs & operator = (const micros & micros);
   secs & operator = (const nanos & nanos);
   secs & operator = (const duration & duration);
   secs & operator = (::i64 i) { m_iSeconds = i; return *this; }


};

