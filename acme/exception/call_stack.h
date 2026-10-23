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

// Thread-local context: ordinary exception construction defaults to false.
CLASS_DECL_ACME bool call_stack_within_signal_handler();
CLASS_DECL_ACME bool call_stack_set_within_signal_handler(bool bWithinSignalHandler);

class call_stack_signal_handler_scope
{
public:
   bool m_bPrevious;
   call_stack_signal_handler_scope() : m_bPrevious(call_stack_set_within_signal_handler(true)) {}
   ~call_stack_signal_handler_scope() { call_stack_set_within_signal_handler(m_bPrevious); }
   call_stack_signal_handler_scope(const call_stack_signal_handler_scope &) = delete;
};


// restoring call stack class
// avoiding ::string usage

class CLASS_DECL_ACME call_stack :
   public ::matter
{
public:


   const_char_pointer m_pszFormat;
   const_char_pointer m_pszCallStack;
   ::i32               m_iCount;

   void *            m_caller_address;
   static constexpr ::u32 TRACE_MAX_STACK_FRAMES = 99;
   static constexpr ::u32 MODULE_BUF_SIZE = 4096U;


   void * m_stack[TRACE_MAX_STACK_FRAMES];
   void * m_modulea[TRACE_MAX_STACK_FRAMES];
   ::u32 m_u32ModulePathLength[TRACE_MAX_STACK_FRAMES];
#if defined(WINDOWS)
   wchar_t m_szaModulePath[TRACE_MAX_STACK_FRAMES][MODULE_BUF_SIZE];
#else
   char m_szaModulePath[TRACE_MAX_STACK_FRAMES][MODULE_BUF_SIZE];
#endif
   ::u32 m_u32Hash;

   call_stack();
   ~call_stack() override;


   //virtual void
   //call_stack(const_char_pointer pszFormat = default_format(), ::i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr, ::i32 iCount = -1);
   virtual void capture(::i32 iSkip = -1, void * caller_address = nullptr, ::i32 iCount = -1);
   //static void global_enable_stack_trace(bool bEnable = true);
   virtual const_char_pointer default_format() { return "%f(%l) %s\n"; }

   //virtual const_char_pointer get_dup(const_char_pointer pszFormat = nullptr, ::i32 uiSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, ::i32 iCount = -1);
   virtual const_char_pointer trace(const_char_pointer pszFormat = nullptr);
   virtual ::i32 _prepare_trace(const_char_pointer pszFormat = nullptr);
   virtual const_char_pointer _trace(::i32 iSize,const_char_pointer pszFormat = nullptr);

   //const_char_pointer stack_trace() const;

};


