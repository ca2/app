/*
 Copyright (ca) 2001 
 Author: Konstantin Boukreev 
 E-mail: konstantin@mail.primorye.ru 
 Created: 07.11.2001 14:17:21
 Version: 1.1.0

 Permission to use, copy, modify, distribute and sell this software
 and its documentation for any purpose is hereby granted without fee,
 provided that the above copyright notice appear in all copies and
 that both that copyright notice and this permission notice appear
 in supporting documentation.  Konstantin Boukreev makes no representations
 about the suitability of this software for any purpose.
 It is provided "as is" without express or implied warranty.


 wrapper class for SetUnhandledExceptionFilter API
*/

#pragma once

#include "ca_Aux2.h"

struct unhandled_policy
{
   long operator () (EXCEPTION_POINTERS *) 
      { return EXCEPTION_CONTINUE_SEARCH; }
};

template <typename P>
class exception_trap :
   public CAuxStdThunk<exception_trap>
{
public:
   typedef P Policy;

protected:
   LPTOP_LEVEL_EXCEPTION_FILTER   m_fn_prev_filter;
   Policy                     m_policy;

public:
   exception_trap(bool, const Policy& point = Policy());
   ~exception_trap();
   
   void install(bool);

   bool is_alive () const   {return m_fn_prev_filter != 0;}
   Policy& get_policy()   {return m_policy;}
         
private:      
   long __stdcall filter (EXCEPTION_POINTERS *);

   static LPTOP_LEVEL_EXCEPTION_FILTER fake () 
   {return (LPTOP_LEVEL_EXCEPTION_FILTER)0xffffffff;}
};

/////////////

template <typename P>
inline exception_trap<P>::exception_trap(bool b, const Policy& point)
   : m_fn_prev_filter(0), m_policy(point)
{
   InitThunk((TMFP)filter, this);
   install(b);
}

template <typename P>
inline exception_trap<P>::~exception_trap()
{
   install(false);
}

template <typename P>
inline void exception_trap<P>::install(bool b)
{
   if (is_alive())
   {      
      SetUnhandledExceptionFilter(m_fn_prev_filter == fake() ? 0 : m_fn_prev_filter);
      m_fn_prev_filter = 0;      
   }

   if (b)
   {         
      m_fn_prev_filter = SetUnhandledExceptionFilter
         ((LPTOP_LEVEL_EXCEPTION_FILTER)GetThunk());
      m_fn_prev_filter = !m_fn_prev_filter ? fake() : m_fn_prev_filter;      
   }
}
   
template <typename P>
inline long __stdcall exception_trap<P>::filter(EXCEPTION_POINTERS * pex)
{
   if (EXCEPTION_STACK_OVERFLOW == pex->ExceptionRecord->ExceptionCode)
   {   
      // stack overflow occurred, 
      // unfortunately it's unable to do anything useful in this case
      return EXCEPTION_CONTINUE_SEARCH;
   }

   long r = EXCEPTION_CONTINUE_SEARCH;
   
   __try
   {          
      r = m_policy(pex);
            
      if  (r == EXCEPTION_CONTINUE_SEARCH &&
         (m_fn_prev_filter && m_fn_prev_filter != fake()) &&
         !IsBadCodePtr((FARPROC)m_fn_prev_filter))
      {            
         r = m_fn_prev_filter(pex);
      }            
   }
   __except(EXCEPTION_EXECUTE_HANDLER)
   {
      r = EXCEPTION_CONTINUE_SEARCH;
   }

   return r;
}

