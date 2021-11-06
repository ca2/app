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


class CLASS_DECL_ACME long_counter :
   public manual_reset_event
{
public:


   interlocked_long m_long;

   
   long_counter(long lCount) : m_long(lCount) {}


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


class CLASS_DECL_ACME counter :
   public manual_reset_event
{
public:


   interlocked_count m_count;

   counter(::count lCount) : m_count(lCount) {}


   ::count operator ++()
   {

      ::count c = --m_count;

      if (c <= 0)
      {

         SetEvent();

      }

      return c;

   }

   ::count operator ++(int)
   {

      ::count c = m_count;

      ++(*this);

      return c;

   }

};
