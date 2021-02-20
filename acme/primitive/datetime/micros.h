//
// Created by camilo on 2020-11-16. <3TBS_ [ THE ONLY ] [ THE GOD ] [ THE MAN ]
//
#pragma once


class CLASS_DECL_ACME micros
{
public:


   ::i64       m_i;


   micros() { m_i = 0; }
   micros(::i64 i) { m_i = i; }
   micros(const secs & secs) { m_i = secs.m_i * 1'000'000; }
   micros(const millis & millis) { m_i = millis.m_i * 1'000; }
   micros(const micros & micros) { m_i = micros.m_i; }
   micros(const nanos & nanos);
   micros(const duration & duration);


   micros & operator = (const micros & micros) { m_i = micros.m_i; return *this; }


   void sleep() const;


   void Now();


};



inline millis::millis(const micros & micros) { m_i = micros.m_i / 1'000; }


inline secs::secs(const micros & micros) { m_i = micros.m_i / 1'000'000; }


inline micros operator "" _us(unsigned long long int u) { return (::i64) u; }


