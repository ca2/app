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


   //::i8                 _str[4096];
   //::i8                 _strBuf[4096];
   //::i8                 _strFile[4096];
   //::i8                 _strSymbol[4096];
   //::i8                 _strS[4 * 1024 * 1024];


   /*const_char_pointer m_pszFormat;
   string               m_strCallStack;
   ::i32                  m_iCount;

   void *               m_caller_address;
*/




//#if defined(__ANDROID__)
//CLASS_DECL_ACME string unwind_callstack(const ::scoped_string & scopedstrFormat = callstack_default_format(), ::i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, ::i32 iCount = -1);
//#else
//CLASS_DECL_ACME string get_callstack(const ::scoped_string & scopedstrFormat = callstack_default_format(), ::i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr, ::i32 iCount = -1);
//#endif



//   ~callstack() override;

//
//   //static void global_enable_stack_trace(bool bEnable = true);
//   static const_char_pointer default_format() { return "%f(%l) %s\n"; }
//
//   //string get_dup(const ::scoped_string & scopedstrFormat = default_format(), ::i32 uiSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, ::i32 iCount = -1);
//
//   void trace(const ::scoped_string & scopedstrFormat = default_format(), ::i32 uiSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, ::i32 iCount = -1);
//
//   //string xxxstack_trace() const;
//
//};
//
//
//
