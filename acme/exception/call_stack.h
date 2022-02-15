/*
 Copyright (ca) 2002
 Author: Konstantin Boukreev
 E-mail: konstantin@mail.primorye.ru
 Created: 16.01.2002 12:36:26
 Version: 1.0.0

 Permission to use, copy, modify, distribute and sell this software
 and its documentation for any purpose is hereby granted without fee,
 provided that the above copyright notice appear in all copies and
 that both that copyright notice and this permission notice appear
 in supporting documentation.  Konstantin Boukreev makes no representations
 about the suitability of this software for any purpose.
 It is provided "as is" without express or implied warranty.

 the exception class holding the call stack's information

 exception2 : std_exception

 try {
 }
 catch(exception2& ex) {
   std_cout << ex.trace_call();
 }

*/
#pragma once




class CLASS_DECL_ACME call_stack :
   public ::matter
{
public:


   const char *      m_pszFormat;
   const char *      m_pszCallStack;
   int               m_iCount;

   void *            m_caller_address;


   call_stack(const char * pszFormat = default_format(), i32 iSkip = CALL_STACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr, int iCount = -1);
   virtual ~call_stack();


   //static void global_enable_stack_trace(bool bEnable = true);
   static const char* default_format() { return "%f(%l) %s\n"; }

   const char * get_dup(const char * pszFormat = default_format(), i32 uiSkip = CALL_STACK_DEFAULT_SKIP_TRIGGER, int iCount = -1);

   const char * xxxstack_trace() const;

};


