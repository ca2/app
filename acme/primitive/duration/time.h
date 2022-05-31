// Created by camilo on 2022-05-31 05:43 AM <3ThomasLikesNumber5 (really will he raise ca-square)
#pragma once


class CLASS_DECL_ACME time
{
public:


   double      m_d; // seconds


   time() {}
   time(enum_zero) : m_d(0.) {}
   time(double d) : m_d(d) {}
   time(const class ::time & time) : m_d(time.m_d) {}


   static inline class ::time now();

   inline class ::time elapsed(const class ::time & waitSample = now()) { return waitSample.m_d - m_d; }


};



