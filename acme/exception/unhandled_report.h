/*
 Copyright (ca) 2001 
 Author: Konstantin Boukreev 
 E-mail: konstantin@mail.primorye.ru 
 Created: 27.12.2001 15:49:31
 Version: 1.0.0

 Permission to use, copy, modify, distribute and sell this software
 and its documentation for any purpose is hereby granted without fee,
 provided that the above copyright notice appear in all copies and
 that both that copyright notice and this permission notice appear
 in supporting documentation.  Konstantin Boukreev makes no representations
 about the suitability of this software for any purpose.
 It is provided "as is" without express or implied warranty.

*/

#ifndef _unhandled_report_21e1d9a1_0c5b_4e7f_b0a3_14671ef2f514
#define _unhandled_report_21e1d9a1_0c5b_4e7f_b0a3_14671ef2f514

#if _MSC_VER > 1000 
#pragma once
#endif // _MSC_VER > 1000

#include "exception_trap.h"
#include "sym_engine.h"
#include "translator.h"

struct unhandled_report
{
   stream & m_os;

   unhandled_report(stream & get_system() = std::cout) : m_os(get_system()) {}
   unhandled_report(const unhandled_report& point) : m_os(point.m_os) {}
   unhandled_report& operator = (const unhandled_report&) { return *this; }
   
   long operator () (EXCEPTION_POINTERS * pex) 
   {       
      m_os << "Unhandled exception " 
          << translator::name(pex->ExceptionRecord->ExceptionCode)
          << " (0x" << std::hex << pex->ExceptionRecord->ExceptionCode << ") at "
          << "0x" << pex->ExceptionRecord->ExceptionAddress 
          << std::dec << std::endl;

      m_os << "The stack trace: " << std::endl;
      sym_engine::stack_trace(m_os, pex->ContextRecord);
      
      return EXCEPTION_CONTINUE_SEARCH; 
   }
};

#endif //_unhandled_report_21e1d9a1_0c5b_4e7f_b0a3_14671ef2f514

