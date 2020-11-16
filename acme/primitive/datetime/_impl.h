#pragma once


inline duration& duration::operator = (const ::duration & duration)
{

   if(this != &duration)
   {

      m_iSeconds = duration.m_iSeconds;
      m_iNanoseconds = duration.m_iNanoseconds;

   }

   return *this;

}


inline void duration::sleep() const
{

   ::sleep(*this);

}



