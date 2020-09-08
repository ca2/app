/*
 Copyright (ca) 2001
 Author: Konstantin Boukreev
 E-mail: konstantin@mail.primorye.ru
 Created: 25.12.2001 14:47:20
 Version: 1.0.0

 Permission to use, copy, modify, distribute and sell this software
 and its documentation for any purpose is hereby granted without fee,
 provided that the above copyright notice appear in all copies and
 that both that copyright notice and this permission notice appear
 in supporting documentation.  Konstantin Boukreev makes no representations
 about the suitability of this software for any purpose.
 It is provided "as is" without express or implied warranty.

 wrapper class for _set_standard_translator API
 maps Win32 exceptions (C structured exceptions) into C++ typed exceptions.
*/

#pragma once

#if defined(ANDROID)

#include <signal.h>
#include <ucontext.h>


#if OSBIT == 64

#define DEFAULT_SE_EXCEPTION_callstack_SKIP 3000

#else

#define DEFAULT_SE_EXCEPTION_callstack_SKIP 0

#endif

#elif defined(WINDOWS)

#include <eh.h>


#if OSBIT == 64

#define DEFAULT_SE_EXCEPTION_callstack_SKIP 3000

#else

#define DEFAULT_SE_EXCEPTION_callstack_SKIP 0

#endif


#define DECLARE_SE_EXCEPTION_CLASS(name) class CLASS_DECL_AURA name : public standard_exception \
   { \
   \
      friend class translator; \
   \
   protected: \
   \
         name (EXCEPTION_POINTERS * ppointers) : \
            ::standard_exception(ppointers) \
      { \
        \
      } \
      \
      \
   };

#elif defined(APPLEOS)


#include <sys/ucontext.h>
#include <signal.h>

#if OSBIT == 64

#define DEFAULT_SE_EXCEPTION_callstack_SKIP 3000

#else

#define DEFAULT_SE_EXCEPTION_callstack_SKIP 0

#endif

#else

#include <signal.h>
#include <ucontext.h>


#if OSBIT == 64

#define DEFAULT_SE_EXCEPTION_callstack_SKIP 3000

#else

#define DEFAULT_SE_EXCEPTION_callstack_SKIP 0

#endif

#endif


class CLASS_DECL_AURA standard_exception :
   public ::exception::exception
{
public:


   friend class ::exception::translator;


#ifdef WINDOWS
   EXCEPTION_POINTERS * m_ppointers;
#else
   i32            m_iSignal;
   void *      m_psiginfo;
#ifndef ANDROID
   ucontext_t     m_ucontext;
#endif
#endif


#ifdef WINDOWS
   u32         code() const         { return m_ppointers->ExceptionRecord->ExceptionCode; }
   void *               address() const      { return m_ppointers->ExceptionRecord->ExceptionAddress; }
   EXCEPTION_POINTERS * info() const         { return m_ppointers; }
   const char *         name() const         { return ::exception::translator::name(code()); }
   const char *         description() const  { return ::exception::translator::description(code()); }
#else
   u32         code() const;
   void *               address() const;
   const void *    info() const;    // siginfo_t *
   const char *         name() const;
   const char *         description() const;
#ifndef ANDROID
   const ucontext_t *   context() const;
#endif
#endif



#ifdef WINDOWS


   standard_exception(EXCEPTION_POINTERS * ppointers) :
      exception(error_exception, DEFAULT_SE_EXCEPTION_callstack_SKIP),
      m_ppointers(ppointers)
   {

   }

#else

   static void * siginfodup(void * psiginfo);
   static void siginfofree(void * psiginfo);

   standard_exception(i32 iSignal, void * psiginfo, void * pc, i32 iSkip = DEFAULT_SE_EXCEPTION_callstack_SKIP, void * caller_address = nullptr) :
      exception(error_exception, iSkip, caller_address),
      m_iSignal(iSignal),
      m_psiginfo(siginfodup(psiginfo))
#ifndef ANDROID
      ,m_ucontext(*(ucontext_t *)pc)
#endif
   { /*_ASSERTE(psiginfo != 0);*/ }

#endif


   virtual ~standard_exception()
   {
#ifndef WINDOWS
      siginfofree(m_psiginfo);
#endif
   }


};

#if defined(LINUX)

typedef struct _sig_ucontext
{
   unsigned long     uc_flags;
   struct ucontext   *uc_link;
   stack_t           uc_stack;
   sigcontext uc_mcontext;
   sigset_t          uc_sigmask;

} sig_ucontext_t;

#endif

namespace exception
{

   class standard_access_violation : public standard_exception
   {
   public:
#if defined(ANDROID) || defined(RASPBIAN)


      standard_access_violation (i32 signal, void * psiginfo, void * pc) :
         ::standard_exception(signal, psiginfo, pc)
      {

      }

#elif defined(FREEBSD_UNIX)
      standard_access_violation (i32 signal, void * psiginfo, void * pc) :
         standard_exception(signal, psiginfo, pc, 3, (void *) pc)
      {

      }


#elif defined(LINUX) || defined(APPLEOS) || defined(SOLARIS)
      standard_access_violation (i32 signal, void * psiginfo, void * pc) :
#ifdef LINUX
#ifdef _LP64
         standard_exception(signal, psiginfo, pc, 3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.rip)
#else
         ::callstack(3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.eip)
#endif
#else
#ifdef _LP64
         standard_exception(signal, psiginfo, pc, 3, (void *) ((ucontext_t *) pc)->uc_mcontext->__ss.__rip)
#else
#ifdef SOLARIS
         ::callstack(3, (void *) ((ucontext_t *) pc)->uc_mcontext.gregs[EIP])
#elif defined(APPLE_IOS)
         ::callstack(3, (void *) nullptr)
#else
         //::callstack(3, (void *) ((ucontext_t *) pc)->uc_mcontext.eip)
#endif
#endif
#endif
//         ::exception::exception(),
         //       ::standard_exception(pobject, signal, psiginfo, pc)
      {

      }

      /*       sig_ucontext_t * uc = (sig_ucontext_t *)ucontext;

             void * caller_address = (void *) uc->uc_mcontext.eip; // x86 specific

             str += "signal " + ansi_string_from_i64(sig_num) +
                       +" (" + ansi_string_from_i64(sig_num) + "), address is "  +
                       itohex_dup(info->si_addr) + " from " + itohex_dup(caller_address) + "\n\n";*/

#else


      standard_access_violation (EXCEPTION_POINTERS * ppointers) :
         ::standard_exception(ppointers)
      {

      }


   public:
      bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
      uptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
#endif
   };
#if defined(ANDROID) || defined(RASPBIAN)

   class standard_sigfpe : public standard_exception
   {
   public:


      standard_sigfpe(i32 iSignal,void * psiginfo,void * pc):
         standard_exception(iSignal, psiginfo, pc)
      {

      }



      //   bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
      // uptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
   };

#elif defined(FREEBSD)

   class standard_sigfpe : public standard_exception
   {
   public:
      standard_sigfpe (i32 iSignal, siginfo_t * psiginfo, void * pc) :
         standard_exception(iSignal, psiginfo, pc, 3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.rip),
         ::callstack(3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.eip),
      {

      }


   public:
      //   bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
      // uptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
   };


#elif defined(LINUX) || defined(APPLEOS)

   class standard_sigfpe : public standard_exception
   {
   public:
      standard_sigfpe (i32 iSignal, siginfo_t * psiginfo, void * pc) :
#ifdef LINUX
#ifdef _LP64
         standard_exception(iSignal, psiginfo, pc, 3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.rip)
         //::callstack(3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.rip),
#else
         ::callstack(3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.eip),
#endif
#else
#ifdef _LP64
         standard_exception(iSignal, psiginfo, pc, 3, (void *) ((ucontext_t *) pc)->uc_mcontext->__ss.__rip)

#else
#if defined(APPLE_IOS)
         ::callstack(3, nullptr),
#else
         //::callstack(3, (void *) ((ucontext_t *) pc)->uc_mcontext.eip),
#endif
#endif
#endif
//         ::exception::exception(),
//         standard_exception(iSignal, psiginfo, pc)
      {

      }


   public:
      //   bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
      // uptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
   };

#endif


#ifdef WINDOWS

   class standard_no_memory : public standard_exception
   {
   public:


      standard_no_memory (EXCEPTION_POINTERS * ppointers) :
         ::standard_exception(ppointers)
      {

      }

   public:
      size_t mem_size() const { return info()->ExceptionRecord->ExceptionInformation [0]; }
   };


   DECLARE_SE_EXCEPTION_CLASS(standard_datatype_misalignment)
   DECLARE_SE_EXCEPTION_CLASS(standard_breakpoint)
   DECLARE_SE_EXCEPTION_CLASS(standard_single_step)
   DECLARE_SE_EXCEPTION_CLASS(standard_array_bounds_exceeded)
   DECLARE_SE_EXCEPTION_CLASS(standard_flt_denormal_operand)
   DECLARE_SE_EXCEPTION_CLASS(standard_flt_divide_by_zero)
   DECLARE_SE_EXCEPTION_CLASS(standard_flt_inexact_result)
   DECLARE_SE_EXCEPTION_CLASS(standard_flt_invalid_operation)
   DECLARE_SE_EXCEPTION_CLASS(standard_flt_overflow)
   DECLARE_SE_EXCEPTION_CLASS(standard_flt_stack_check)
   DECLARE_SE_EXCEPTION_CLASS(standard_flt_underflow)
   DECLARE_SE_EXCEPTION_CLASS(standard_int_divide_by_zero)
   DECLARE_SE_EXCEPTION_CLASS(standard_int_overflow)
   DECLARE_SE_EXCEPTION_CLASS(standard_priv_instruction)
   DECLARE_SE_EXCEPTION_CLASS(standard_in_page_error)
   DECLARE_SE_EXCEPTION_CLASS(standard_illegal_instruction)
   DECLARE_SE_EXCEPTION_CLASS(standard_noncontinuable_exception)
   DECLARE_SE_EXCEPTION_CLASS(standard_stack_overflow)
   DECLARE_SE_EXCEPTION_CLASS(standard_invalid_disposition)
   DECLARE_SE_EXCEPTION_CLASS(standard_guard_page)
   DECLARE_SE_EXCEPTION_CLASS(standard_invalid_handle)
   DECLARE_SE_EXCEPTION_CLASS(standard_microsoft_cpp)
   DECLARE_SE_EXCEPTION_CLASS(standard_winrt_originate_error)

#endif

} // namespace exception

/*#else


#include "translator.h"
#if !defined(APPLEOS)
#include <ucontext.h>
#include <sys/ucontext.h>
#endif*/

/*class CLASS_DECL_AURA standard_exception :
   public bastandard_exception
{
public:
   friend class translator;


   ~standard_exception() {}

protected:

private:
};*/

/*class standard_sigsegv : public standard_exception
{
   friend class translator;
protected:
   standard_sigsegv (siginfo_t * psiginfo, void * pc) : ::object(pobject), standard_exception(psiginfo, pc) {}
public:
   //bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
   //uptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
};*/

/*class standard_sigfpe : public standard_exception
{
   friend class translator;
protected:
   standard_sigfpe (siginfo_t * psiginfo, void * pc) : ::object(pobject), standard_exception(psiginfo, pc) {}
public:
//   bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
  // uptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
};

#endif*/

