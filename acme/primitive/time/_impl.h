//
// Created by camilo on 2022-10-24 15:03 <3ThomasBorregaardSorensen!!
//
#pragma once


//inline timeclass ::time(const ::INTEGRAL_NANOSECOND & integral) : time((const class ::time &)integral) {}
//inline timeclass ::time(const ::FLOATING_NANOSECOND & floating) : time((const class ::time &)floating) {}
//inline timeclass ::time(const ::INTEGRAL_MICROSECOND & integral) : time((const class ::time &)integral) {}
//inline timeclass ::time(const ::FLOATING_MICROSECOND & floating) : time((const class ::time &)floating) {}
//inline timeclass ::time(const ::INTEGRAL_MILLISECOND & integral) : time((const class ::time &)integral) {}
//inline timeclass ::time(const ::FLOATING_MILLISECOND & floating) : time((const class ::time &)floating) {}
//inline timeclass ::time(const ::INTEGRAL_SECOND & integral) : time((const class ::time &)integral) {}
//inline timeclass ::time(const ::FLOATING_SECOND & floating) : time((const class ::time &)floating) {}
//inline timeclass ::time(const ::INTEGRAL_MINUTE & integral) : time((const class ::time &)integral) {}
//inline timeclass ::time(const ::FLOATING_MINUTE & floating) : time((const class ::time &)floating) {}
//inline timeclass ::time(const ::INTEGRAL_HOUR & integral) : time((const class ::time &)integral) {}
//inline timeclass ::time(const ::FLOATING_HOUR & floating) : time((const class ::time &)floating) {}
//inline timeclass ::time(const ::INTEGRAL_DAY & integral) : time((const class ::time &)integral) {}
//inline timeclass ::time(const ::FLOATING_DAY & floating) : time((const class ::time &)floating) {}


inline class time& time::operator = (const class time & time)
{

   if(this != &time)
   {

      m_iSecond = time.m_iSecond;
      m_iNanosecond = time.m_iNanosecond;

   }

   return *this;

}



