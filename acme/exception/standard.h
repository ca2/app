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

#define DEFAULT_SE_EXCEPTION_CALLSTACK_SKIP 3000

#else

#define DEFAULT_SE_EXCEPTION_CALLSTACK_SKIP 0

#endif

#elif defined(WINDOWS)

#elif defined(__APPLE__)


#include <sys/ucontext.h>
#include <signal.h>

#if OSBIT == 64

#define DEFAULT_SE_EXCEPTION_CALLSTACK_SKIP 3000

#else

#define DEFAULT_SE_EXCEPTION_CALLSTACK_SKIP 0

#endif

#else

#include <signal.h>
#include <ucontext.h>


#if OSBIT == 64

#define DEFAULT_SE_EXCEPTION_CALLSTACK_SKIP 3000

#else

#define DEFAULT_SE_EXCEPTION_CALLSTACK_SKIP 0

#endif

#endif


class CLASS_DECL_ACME standard_exception :
   public ::exception
{
public:


   friend class ::exception_translator;


#ifdef WINDOWS
   //EXCEPTION_POINTERS * m_ppointers;
#else
   i32            m_iSignal;
   void *      m_psiginfo;
#ifndef ANDROID
   ucontext_t     m_ucontext;
#endif
#endif


#ifdef WINDOWS
   //EXCEPTION_POINTERS * info() const         { return m_ppointers; }
#else
   u32         code() const;
   void *               address() const;
   const void *    info() const;    // siginfo_t *
   const char *         name() const;
   const char *         description() const;
#ifndef ANDROID
   const ::ucontext_t *   ucontext() const;
#endif
#endif



#if !defined(WINDOWS)

   static void * siginfodup(void * psiginfo);
   static void siginfofree(void * psiginfo);

#ifdef ANDROID

   standard_exception(i32 iSignal, void * psiginfo, void * pc, i32 iSkip = DEFAULT_SE_EXCEPTION_CALLSTACK_SKIP) :
      ::exception(error_exception, nullptr, nullptr, iSkip),
      m_iSignal(iSignal),
      m_psiginfo(siginfodup(psiginfo))
   {

   /*_ASSERTE(psiginfo != 0);*/

   }

#else

   standard_exception(i32 iSignal, void * psiginfo, void * pc, i32 iSkip = DEFAULT_SE_EXCEPTION_CALLSTACK_SKIP,
                      void * caller_address = nullptr) :
      ::exception(error_exception, nullptr, nullptr, iSkip, caller_address),
      m_iSignal(iSignal),
      m_psiginfo(siginfodup(psiginfo)),
      m_ucontext(*((::ucontext_t *)pc))
   {

      /*_ASSERTE(psiginfo != 0);*/

   }

#endif

#endif //!def(WINDOWS)


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

//namespace exception
//{
//
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


#elif defined(LINUX) || defined(__APPLE__) || defined(SOLARIS)
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
//         ::exception(),
         //       ::standard_exception(pobject, signal, psiginfo, pc)
      {

      }

      /*       sig_ucontext_t * uc = (sig_ucontext_t *)ucontext;

             void * caller_address = (void *) uc->uc_mcontext.eip; // x86 specific

             str += "signal " + ansi_string_from_i64(sig_num) +
                       +" (" + ansi_string_from_i64(sig_num) + "), address is "  +
                       itohex_dup(info->si_addr) + " from " + itohex_dup(caller_address) + "\n\n";*/

#else



   public:
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
         //standard_exception(iSignal, psiginfo, pc, 3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.rip),
         standard_exception(iSignal, psiginfo, pc, 3, (void *) ((ucontext_t *) pc)->uc_mcontext.mc_rip)
         //::callstack(3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.eip),
      {

      }


   public:
      //   bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
      // uptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
   };


#elif defined(LINUX) || defined(__APPLE__)

   class standard_sigfpe : public standard_exception
   {
   public:
      standard_sigfpe (i32 iSignal, siginfo_t * psiginfo, void * pc) :
#ifdef LINUX
#ifdef _LP64
         standard_exception(iSignal, psiginfo, pc, 3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.rip)
         //::callstack(3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.rip),
#else
#ifdef __arm__
		 standard_exception(iSignal, psiginfo, pc, 3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.arm_ip)
         //::callstack(3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.eip),
#else
		 standard_exception(iSignal, psiginfo, pc, 3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.rip)
         //::callstack(3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.eip),

#endif
#endif
#else
#ifdef _LP64
      
#ifdef __ARM_ARCH_ISA_A64
         standard_exception(iSignal, psiginfo, pc, 3, (void *) ((ucontext_t *) pc)->uc_mcontext->__ss.__pc)
#else
      standard_exception(iSignal, psiginfo, pc, 3, (void *) ((ucontext_t *) pc)->uc_mcontext->__ss.__rip)

#endif

#else
#if defined(APPLE_IOS)
         ::callstack(3, nullptr),
#else
         //::callstack(3, (void *) ((ucontext_t *) pc)->uc_mcontext.eip),
#endif
#endif
#endif
//         ::exception(),
//         standard_exception(iSignal, psiginfo, pc)
      {

      }


   public:
      //   bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
      // uptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
   };

#endif


//} // namespace exception

/*#else


#include "translator.h"
#if !defined(__APPLE__)
#include <ucontext.h>
#include <sys/ucontext.h>
#endif*/

/*class CLASS_DECL_ACME standard_exception :
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
   standard_sigsegv (siginfo_t * psiginfo, void * pc) : ::matter(pobject), standard_exception(psiginfo, pc) {}
public:
   //bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
   //uptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
};*/

/*class standard_sigfpe : public standard_exception
{
   friend class translator;
protected:
   standard_sigfpe (siginfo_t * psiginfo, void * pc) : ::matter(pobject), standard_exception(psiginfo, pc) {}
public:
//   bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
  // uptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
};

#endif*/

