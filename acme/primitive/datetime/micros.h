//
// Created by camilo on 2020-11-16. <3TBS_ [ THE ONLY ] [ THE GOD ] [ THE MAN ]
//
#pragma once


class CLASS_DECL_ACME micros
{
public:


   ::i64       m_iMicroseconds;


   micros() { m_iMicroseconds = 0; }
   micros(::i64 i) { m_iMicroseconds = i; }
   micros(const secs & secs) { m_iMicroseconds = secs.m_iSeconds * 1'000'000; }
   micros(const millis & millis) { m_iMicroseconds = millis.m_iMilliseconds * 1'000; }
   micros(const micros & micros) { m_iMicroseconds = micros.m_iMicroseconds; }
   micros(const nanos & nanos);
   micros(const duration & duration);


   micros & operator = (const micros & micros) { m_iMicroseconds = micros.m_iMicroseconds; return *this; }


   void sleep() const;


};



inline millis::millis(const micros & micros) { m_iMilliseconds = micros.m_iMicroseconds / 1'000; }


inline secs::secs(const micros & micros) { m_iSeconds = micros.m_iMicroseconds / 1'000'000; }


inline micros operator "" _us(unsigned long long int u) { return (::i64) u; }



