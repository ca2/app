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



