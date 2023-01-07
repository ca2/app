//
// Created by camilo on 2022-10-24 15:03 <3ThomasBorregaardSorensen!!
//
#pragma once


//inline timeclass ::time(const ::integral_nanosecond & integral) : time((const class ::time &)integral) {}
//inline timeclass ::time(const ::floating_nanosecond & floating) : time((const class ::time &)floating) {}
//inline timeclass ::time(const ::integral_microsecond & integral) : time((const class ::time &)integral) {}
//inline timeclass ::time(const ::floating_microsecond & floating) : time((const class ::time &)floating) {}
//inline timeclass ::time(const ::integral_millisecond & integral) : time((const class ::time &)integral) {}
//inline timeclass ::time(const ::floating_millisecond & floating) : time((const class ::time &)floating) {}
//inline timeclass ::time(const ::integral_second & integral) : time((const class ::time &)integral) {}
//inline timeclass ::time(const ::floating_second & floating) : time((const class ::time &)floating) {}
//inline timeclass ::time(const ::integral_minute & integral) : time((const class ::time &)integral) {}
//inline timeclass ::time(const ::floating_minute & floating) : time((const class ::time &)floating) {}
//inline timeclass ::time(const ::integral_hour & integral) : time((const class ::time &)integral) {}
//inline timeclass ::time(const ::floating_hour & floating) : time((const class ::time &)floating) {}
//inline timeclass ::time(const ::integral_day & integral) : time((const class ::time &)integral) {}
//inline timeclass ::time(const ::floating_day & floating) : time((const class ::time &)floating) {}


constexpr class time& time::operator = (const class time & time)
{

   if(this != &time)
   {

      m_iSecond = time.m_iSecond;
      m_iNanosecond = time.m_iNanosecond;

   }

   return *this;

}



