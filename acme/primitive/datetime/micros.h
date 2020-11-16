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


   micros & operator = (const secs & secs) { m_iMicroseconds = secs.m_iSeconds * 1'000'000; return *this; }
   micros & operator = (const millis & millis) { m_iMicroseconds = millis.m_iMilliseconds * 1'000; return *this; }
   micros & operator = (const micros & micros) { m_iMicroseconds = micros.m_iMicroseconds; return *this; }
   micros & operator = (const nanos & nanos);
   micros & operator = (const duration & duration);
   micros & operator = (::i64 i) { m_iMicroseconds = i; return *this; }


};

