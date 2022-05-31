// Created by camilo on 2022-05-31 07:28 AM <3ThomasLikesNumber5 (really will he raise ca-square)
#pragma once


template < typename TYPE >
inline bool operator <(const class time& time, const integral_duration < TYPE >& t)
{

   return time.m_d < FLOATING_SECOND(t).m_d;

}


template < typename TYPE >
inline bool operator <=(const class time& time, const integral_duration < TYPE >& t)
{

   return time.m_d <= FLOATING_SECOND(t).m_d;

}


template < typename TYPE >
inline bool operator >(const class time& timeduration, const integral_duration < TYPE >& t)
{

   return timeduration.m_d > FLOATING_SECOND(t).m_d;

}


template < typename TYPE >
inline bool operator >=(const class time& timeduration, const integral_duration < TYPE >& t)
{

   return timeduration.m_d >= FLOATING_SECOND(t).m_d;

}


template < typename TYPE >
inline bool operator ==(const class time& timeduration, const integral_duration < TYPE >& t)
{

   return timeduration.m_d == FLOATING_SECOND(t).m_d;

}


template < typename TYPE >
inline bool operator !=(const class time& timeduration, const integral_duration < TYPE >& t)
{

   return timeduration.m_d != FLOATING_SECOND(t).m_d;

}


template < typename TYPE >
inline bool operator <(const class time & time, const floating_duration < TYPE > & t)
{

   return time.m_d < FLOATING_SECOND(t).m_d;

}


template < typename TYPE >
inline bool operator <=(const class time& time, const floating_duration < TYPE >& t)
{

   return time.m_d <= FLOATING_SECOND(t).m_d;

}


template < typename TYPE >
inline bool operator >(const class time& timeduration, const floating_duration < TYPE >& t)
{

   return timeduration.m_d > FLOATING_SECOND(t).m_d;

}


template < typename TYPE >
inline bool operator >=(const class time& timeduration, const floating_duration < TYPE >& t)
{

   return timeduration.m_d >= FLOATING_SECOND(t).m_d;

}


template < typename TYPE >
inline bool operator ==(const class time& timeduration, const floating_duration < TYPE >& t)
{

   return timeduration.m_d == FLOATING_SECOND(t).m_d;

}


template < typename TYPE >
inline bool operator !=(const class time& timeduration, const floating_duration < TYPE >& t)
{

   return timeduration.m_d != FLOATING_SECOND(t).m_d;

}



inline bool operator < (const class ::time& timeduration1, const class ::time& timeduration2) { return timeduration1.m_d < timeduration2.m_d; }
inline bool operator <= (const class ::time& timeduration1, const class ::time& timeduration2) { return timeduration1.m_d <= timeduration2.m_d; }
inline bool operator > (const class ::time& timeduration1, const class ::time& timeduration2) { return timeduration1.m_d > timeduration2.m_d; }
inline bool operator >= (const class ::time& timeduration1, const class ::time& timeduration2) { return timeduration1.m_d >= timeduration2.m_d; }
inline bool operator == (const class ::time& timeduration1, const class ::time& timeduration2) { return timeduration1.m_d == timeduration2.m_d; }
inline bool operator != (const class ::time& timeduration1, const class ::time& timeduration2) { return timeduration1.m_d != timeduration2.m_d; }

inline class ::time operator + (const class ::time& timeduration1, const class ::time& timeduration2) { return timeduration1.m_d + timeduration2.m_d; }
inline class ::time operator - (const class ::time& timeduration1, const class ::time& timeduration2) { return timeduration1.m_d - timeduration2.m_d; }


template < primitive_number NUMBER >
inline class ::time operator / (const class ::time& timeduration, const NUMBER & number) { return (double) (timeduration.m_d / number); }
template < primitive_number NUMBER >
inline class ::time operator * (const class ::time& timeduration, const NUMBER & number) { return (double) (timeduration.m_d * number); }



