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


//class CLASS_DECL_ACME callstack :
//   virtual public ::matter
//{
//public:


   /*

      format argument
      %m  : module
      %f  : file
      %l  : line
      %ld : line's displacement
      %s  : symbol
      %sd : symbol's displacement

      for example
      "%f(%l) : %m at %s\n"
      "%m.%s + %sd bytes, in %f:line %l\n"

   */


   //char                 _str[4096];
   //char                 _strBuf[4096];
   //char                 _strFile[4096];
   //char                 _strSymbol[4096];
   //char                 _strS[4 * 1024 * 1024];


   /*const char *         m_pszFormat;
   string               m_strCallStack;
   int                  m_iCount;

   void *               m_caller_address;
*/


inline const char* callstack_default_format() { return "%f(%l) %s\n"; }


CLASS_DECL_ACME string get_callstack(const char * pszFormat = callstack_default_format(), i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr, int iCount = -1);



//   ~callstack() override;

//
//   //static void global_enable_stack_trace(bool bEnable = true);
//   static const char* default_format() { return "%f(%l) %s\n"; }
//
//   //string get_dup(const char * pszFormat = default_format(), i32 uiSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, int iCount = -1);
//
//   void trace(const char* pszFormat = default_format(), i32 uiSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, int iCount = -1);
//
//   //string stack_trace() const;
//
//};
//
//
//
