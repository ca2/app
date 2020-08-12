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


class CLASS_DECL_AURA manual_reset_event :
   public event
{
public:


      manual_reset_event(char * sz = nullptr, bool bInitiallyOwn = false);


};


class CLASS_DECL_AURA counter :
   public manual_reset_event
{
public:


      interlocked_long m_long;

   counter(long lCount) : m_long(lCount) {}


   long operator ++()
   {

      long l = --m_long;

      if (l <= 0)
      {

         SetEvent();

      }

      return l;

   }

   long operator ++(int)
   {

      long l = m_long;
   
      ++(*this);

      return l;

   }

};


