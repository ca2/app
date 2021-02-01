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


class CLASS_DECL_ACME i32_counter :
   public manual_reset_event
{
public:


   interlocked_i32      m_i;

   
   i32_counter(long lCount) : m_i(lCount) {}


   long operator ++()
   {

      auto i = --m_i;

      if (i <= 0)
      {

         SetEvent();

      }

      return i;

   }


   long operator ++(int)
   {

      auto i = m_i;
   
      ++(*this);

      return i;

   }

};


class CLASS_DECL_ACME counter :
   public manual_reset_event
{
public:


   interlocked_count       m_count;


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
