//*****************************************************************************
//
//      Class:          manual_reset_event
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Notifies one or more waiting threads that an event has
//                      occurred.
//
//*****************************************************************************


#pragma once

#define DECLARE_REUSABLE(TYPE) \
TYPE * m_pnext; \
::factory::reusable_factory < TYPE, TYPE > * m_pfactory; \
virtual void delete_this() { if(m_pfactory) m_pfactory->return_back(this); else delete this;}


class CLASS_DECL_ACME manual_reset_event :
   public ::event
{
public:


   DECLARE_REUSABLE(manual_reset_event);


   manual_reset_event(char * sz = nullptr, bool bInitiallyOwn = false);


   void reuse() { ResetEvent(); }

};


template < primitive_integral INTEGRAL >
class counter :
   public manual_reset_event
{
public:


   interlocked < INTEGRAL >      m_interlocked;


   counter(INTEGRAL lCount) : m_interlocked(lCount) {}


   INTEGRAL operator ++()
   {

      INTEGRAL i = --m_interlocked;

      if (i <= 0)
      {

         SetEvent();

      }

      return i;

   }


   INTEGRAL operator ++(int)
   {

      INTEGRAL i = m_interlocked;
   
      ++(*this);

      return i;

   }

};



