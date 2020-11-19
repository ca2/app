/*
Copyright (ca) 2001
Author: Konstantin Boukreev
E-mail: konstantin@mail.primorye.ru
Created: 25.12.2001 15:18:21
Version: 1.0.0

Permission to use, copy, modify, distribute and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and
that both that copyright notice and this permission notice appear
in supporting documentation.  Konstantin Boukreev makes no representations
about the suitability of this software for any purpose.
It is provided "as is" without express or implied warranty.

*/
#include "framework.h"


#if defined(LINUX) || defined(ANDROID)

//#include <pthread.h>

#endif


#ifdef __APPLE__

void InstallUncaughtExceptionHandler();

#endif


#ifdef EXCEPTION_TRANSLATOR_USE_SIGNAL
//#include <signal.h>
#define SIG(psig) ((::exception::sig_companion *) psig)
#define m_sig (*SIG(m_psig))
#endif


#ifdef WINDOWS_DESKTOP

// 0x40010005 control C
// 0xc0000135 Dll Not Found
// 0xc0000142 Dll Initialization failed
// 0xc06d007e Module Not Found
// 0xc06d007f Procedure Not Found
// 0x40010008 control-Break

#define EXCEPTION_NO_MEMORY STATUS_NO_MEMORY

LPTOP_LEVEL_EXCEPTION_FILTER WINAPI MyDummySetUnhandledExceptionFilter(
LPTOP_LEVEL_EXCEPTION_FILTER pTopLevelExceptionFilter)

{
   UNREFERENCED_PARAMETER(pTopLevelExceptionFilter);

   return nullptr;
}

bool PreventSetUnhandledExceptionFilter()
{
   /*HMODULE hKernel32 = LoadLibrary("kernel32.dll");
   if (hKernel32 == nullptr) return FALSE;
   void *pOrgEntry = GetProcAddress(hKernel32, "SetUnhandledExceptionFilter");
   if(pOrgEntry ==  nullptr) return FALSE;
   uchar newJump[ 100 ];
   u32 dwOrgEntryAddr = (u32) pOrgEntry;
   dwOrgEntryAddr += 5; // add 5 for 5 op-codes for jmp far
   void *pNewFunc = &MyDummySetUnhandledExceptionFilter;
   u32 dwNewEntryAddr = (u32) pNewFunc;
   u32 dwRelativeAddr = dwNewEntryAddr - dwOrgEntryAddr;
   newJump[ 0 ] = 0xE9;  // JMP absolute
   ::memcpy_dup(&newJump[ 1 ], &dwRelativeAddr, sizeof(pNewFunc));
   SIZE_T bytesWritten;
   bool bRet = WriteProcessMemory(GetCurrentProcess(),
   pOrgEntry, newJump, sizeof(pNewFunc) + 1, &bytesWritten);
   return bRet;*/
   return FALSE;
}

#endif



namespace exception
{


#ifdef EXCEPTION_TRANSLATOR_USE_SIGNAL


   struct sig_companion
   {

      struct sigaction m_saSeg;
      struct sigaction m_saFpe;
      struct sigaction m_saPipe;
      struct sigaction m_saSegOld;
      struct sigaction m_saFpeOld;
      struct sigaction m_saPipeOld;

   };


#endif


   translator::translator()
   {

      m_bSet = false;

#ifdef EXCEPTION_TRANSLATOR_USE_SIGNAL

      m_psig = new sig_companion;

#endif

   }


   translator::~translator()
   {

#ifdef EXCEPTION_TRANSLATOR_USE_SIGNAL

      if(m_psig != nullptr)
      {

         delete (sig_companion *) m_psig;

      }

#endif

   }


#ifdef WINDOWS

   void __cdecl translator::filter2(u32 uiCode, EXCEPTION_POINTERS * ppointers)
   {

      if (g_bExiting)
      {

         return;

      }

      UNREFERENCED_PARAMETER(uiCode);

      //::acme::application * papp = ::get_context_application();

      switch (ppointers->ExceptionRecord->ExceptionCode)
      {
#ifdef WINDOWS_DESKTOP
      case EXCEPTION_NO_MEMORY:                 __throw(standard_no_memory(ppointers));                  break;
#endif
      case EXCEPTION_ACCESS_VIOLATION:          __throw(standard_access_violation(ppointers));           break;
      case EXCEPTION_DATATYPE_MISALIGNMENT:     __throw(standard_datatype_misalignment(ppointers));      break;
      case EXCEPTION_BREAKPOINT:                __throw(standard_breakpoint(ppointers));                 break;
      case EXCEPTION_SINGLE_STEP:               __throw(standard_single_step(ppointers));                break;
      case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:     __throw(standard_array_bounds_exceeded(ppointers));      break;
      case EXCEPTION_FLT_DENORMAL_OPERAND:      __throw(standard_flt_denormal_operand(ppointers));       break;
      case EXCEPTION_FLT_DIVIDE_BY_ZERO:        __throw(standard_flt_divide_by_zero(ppointers));         break;
      case EXCEPTION_FLT_INEXACT_RESULT:        __throw(standard_flt_inexact_result(ppointers));         break;
      case EXCEPTION_FLT_INVALID_OPERATION:     __throw(standard_flt_invalid_operation(ppointers));      break;
      case EXCEPTION_FLT_OVERFLOW:              __throw(standard_flt_overflow(ppointers));               break;
      case EXCEPTION_FLT_STACK_CHECK:           __throw(standard_flt_stack_check(ppointers));            break;
      case EXCEPTION_FLT_UNDERFLOW:             __throw(standard_flt_underflow(ppointers));              break;
      case EXCEPTION_INT_DIVIDE_BY_ZERO:        __throw(standard_int_divide_by_zero(ppointers));         break;
      case EXCEPTION_INT_OVERFLOW:              __throw(standard_int_overflow(ppointers));               break;
      case EXCEPTION_PRIV_INSTRUCTION:          __throw(standard_priv_instruction(ppointers));           break;
      case EXCEPTION_IN_PAGE_ERROR:             __throw(standard_in_page_error(ppointers));              break;
      case EXCEPTION_ILLEGAL_INSTRUCTION:       __throw(standard_illegal_instruction(ppointers));        break;
      case EXCEPTION_NONCONTINUABLE_EXCEPTION:  __throw(standard_noncontinuable_exception(ppointers));   break;
      case EXCEPTION_STACK_OVERFLOW:            __throw(standard_stack_overflow(ppointers));             break;
      case EXCEPTION_INVALID_DISPOSITION:       __throw(standard_invalid_disposition(ppointers));        break;
      case EXCEPTION_GUARD_PAGE:                __throw(standard_guard_page(ppointers));                 break;
      case EXCEPTION_INVALID_HANDLE:            __throw(standard_invalid_handle(ppointers));             break;
      case 0xE06D7363:                          __throw(standard_microsoft_cpp(ppointers));              break;
      case 0x40080201:                          __throw(standard_winrt_originate_error(ppointers));      break;
      default:                                  __throw(standard_exception(ppointers));                  break;
      };

   }

#endif


#ifndef WINDOWS

   void filter_sigsegv(i32 signal,siginfo_t * psiginfo,void * pc);
   void filter_sigfpe(i32 signal,siginfo_t * psiginfo,void * pc);
   void filter_sigpipe(i32 signal,siginfo_t * psiginfo,void * pc);

#endif


   bool translator::attach()
   {

      if(!m_bSet)
      {

#ifdef WINDOWS

         m_pfn = _set_se_translator(&translator::filter2);

         //m_pfn = SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER) GetThunk());

         //PreventSetUnhandledExceptionFilter();

         //EnforceFilter(true);

#else

#if defined(__APPLE__)

         ::InstallUncaughtExceptionHandler();

#endif

         output_debug_string("exception standard translator");

#if defined(__SANITIZE_ADDRESS__) || defined(__FOR_PERF__)

         INFO("sanitize address compilation, not going to install standard exception translator");

#else

         ·zero(m_sig.m_saSeg);

         m_sig.m_saSeg.sa_flags = SA_SIGINFO;

         m_sig.m_saSeg.sa_sigaction = &filter_sigsegv;

         if(sigaction(SIGSEGV, &m_sig.m_saSeg, &m_sig.m_saSegOld) < 0)
         {

            output_debug_string("failed to install segmentation fault signal handler");

         }

         ·zero(m_sig.m_saFpe);

         m_sig.m_saSeg.sa_flags = SA_SIGINFO;

         m_sig.m_saFpe.sa_sigaction = &filter_sigfpe;

         if(sigaction(SIGFPE, &m_sig.m_saFpe, &m_sig.m_saFpeOld) < 0)
         {

            output_debug_string("failed to install floating point exception signal handler");

         }

         ·zero(m_sig.m_saPipe);

         m_sig.m_saSeg.sa_flags = SA_SIGINFO;

         m_sig.m_saPipe.sa_sigaction = &filter_sigpipe;

         if(sigaction(SIGPIPE,&m_sig.m_saPipe,&m_sig.m_saPipeOld) < 0)
         {

            output_debug_string("failed to install pipe signal handler");

         }

#endif

#endif

         m_bSet = true;

         return true;

      }
      else
      {

         return false;

      }

   }


   bool translator::detach()
   {

      if(m_bSet)
      {

#ifdef WINDOWS

         _set_se_translator(m_pfn);

#else

         sigaction(SIGSEGV,&m_sig.m_saSegOld,nullptr);

         sigaction(SIGFPE,&m_sig.m_saFpeOld,nullptr);

#endif

         m_bSet = false;

         return true;

      }
      else
      {

         return false;

      }

   }


#ifdef WINDOWS


   void translator::filter(u32 uiCode, EXCEPTION_POINTERS * ppointers)
   {

      UNREFERENCED_PARAMETER(uiCode);

      switch (ppointers->ExceptionRecord->ExceptionCode)
      {
#ifdef WINDOWS_DESKTOP
      case EXCEPTION_NO_MEMORY:                 __throw(standard_no_memory(ppointers));                  break;
#endif
      case EXCEPTION_ACCESS_VIOLATION:          __throw(standard_access_violation(ppointers));           break;
      case EXCEPTION_DATATYPE_MISALIGNMENT:     __throw(standard_datatype_misalignment(ppointers));      break;
      case EXCEPTION_BREAKPOINT:                __throw(standard_breakpoint(ppointers));                 break;
      case EXCEPTION_SINGLE_STEP:               __throw(standard_single_step(ppointers));                break;
      case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:     __throw(standard_array_bounds_exceeded(ppointers));      break;
      case EXCEPTION_FLT_DENORMAL_OPERAND:      __throw(standard_flt_denormal_operand(ppointers));       break;
      case EXCEPTION_FLT_DIVIDE_BY_ZERO:        __throw(standard_flt_divide_by_zero(ppointers));         break;
      case EXCEPTION_FLT_INEXACT_RESULT:        __throw(standard_flt_inexact_result(ppointers));         break;
      case EXCEPTION_FLT_INVALID_OPERATION:     __throw(standard_flt_invalid_operation(ppointers));      break;
      case EXCEPTION_FLT_OVERFLOW:              __throw(standard_flt_overflow(ppointers));               break;
      case EXCEPTION_FLT_STACK_CHECK:           __throw(standard_flt_stack_check(ppointers));            break;
      case EXCEPTION_FLT_UNDERFLOW:             __throw(standard_flt_underflow(ppointers));              break;
      case EXCEPTION_INT_DIVIDE_BY_ZERO:        __throw(standard_int_divide_by_zero(ppointers));         break;
      case EXCEPTION_INT_OVERFLOW:              __throw(standard_int_overflow(ppointers));               break;
      case EXCEPTION_PRIV_INSTRUCTION:          __throw(standard_priv_instruction(ppointers));           break;
      case EXCEPTION_IN_PAGE_ERROR:             __throw(standard_in_page_error(ppointers));              break;
      case EXCEPTION_ILLEGAL_INSTRUCTION:       __throw(standard_illegal_instruction(ppointers));        break;
      case EXCEPTION_NONCONTINUABLE_EXCEPTION:  __throw(standard_noncontinuable_exception(ppointers));   break;
      case EXCEPTION_STACK_OVERFLOW:            __throw(standard_stack_overflow(ppointers));             break;
      case EXCEPTION_INVALID_DISPOSITION:       __throw(standard_invalid_disposition(ppointers));        break;
      };

   }


   string translator::name(u32 uiCode)
   {

      string str;

      switch (uiCode)
      {
#ifdef WINDOWS_DESKTOP
      case EXCEPTION_NO_MEMORY:                 str = "No Memory";                  break;
#endif
      case EXCEPTION_ACCESS_VIOLATION:          str = "Access Violation";           break;
      case EXCEPTION_DATATYPE_MISALIGNMENT:     str = "Datatype Misalignment";      break;
      case EXCEPTION_BREAKPOINT:                str = "Breakpoint";                 break;
      case EXCEPTION_SINGLE_STEP:               str = "Single Step";                break;
      case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:     str = "Array Bounds Exceeded";      break;
      case EXCEPTION_FLT_DENORMAL_OPERAND:      str = "Float Denormal Operand";     break;
      case EXCEPTION_FLT_DIVIDE_BY_ZERO:        str = "Float Divide by Zero";       break;
      case EXCEPTION_FLT_INEXACT_RESULT:        str = "Float Inexact Result";       break;
      case EXCEPTION_FLT_INVALID_OPERATION:     str = "Float Invalid Operation";    break;
      case EXCEPTION_FLT_OVERFLOW:              str = "Float Overflow";             break;
      case EXCEPTION_FLT_STACK_CHECK:           str = "Float Stack Check";          break;
      case EXCEPTION_FLT_UNDERFLOW:             str = "Float Underflow";            break;
      case EXCEPTION_INT_DIVIDE_BY_ZERO:        str = "Integer Divide by Zero";     break;
      case EXCEPTION_INT_OVERFLOW:              str = "Integer Overflow";           break;
      case EXCEPTION_PRIV_INSTRUCTION:          str = "Privileged Instruction";     break;
      case EXCEPTION_IN_PAGE_ERROR:             str = "In Page Error";              break;
      case EXCEPTION_ILLEGAL_INSTRUCTION:       str = "Illegal Instruction";        break;
      case EXCEPTION_NONCONTINUABLE_EXCEPTION:  str = "Noncontinuable Exception";   break;
      case EXCEPTION_STACK_OVERFLOW:            str = "Stack Overflow";             break;
      case EXCEPTION_INVALID_DISPOSITION:       str = "Invalid Disposition";        break;
      case EXCEPTION_GUARD_PAGE:                str = "Guard Page";                 break;
      case EXCEPTION_INVALID_HANDLE:            str = "Invalid Handle";             break;
      case 0xE06D7363:                          str = "Microsoft C++ Exception";    break;
      default:
         str = "0x";
         str += hex::lower_from(uiCode);
         break;
      };

      return str;

   }


   string translator::description(u32 uiCode)
   {

      string str;

      switch(uiCode)
      {
#ifdef WINDOWS_DESKTOP
      case EXCEPTION_NO_MEMORY:
         str = "The allocation attempt failed because of a lack of available memory or heap corruption.";
         break;
#endif
      case EXCEPTION_ACCESS_VIOLATION:
         str = "The thread attempted to read from or write to a virtual address for which it does not have the appropriate access";
         break;
      case EXCEPTION_DATATYPE_MISALIGNMENT:
         str = "The thread attempted to read or write data that is misaligned on hardware that does not provide alignment. For example, 16-bit values must be aligned on 2-byte boundaries, 32-bit values on 4-byte boundaries, and so on";
         break;
      case EXCEPTION_BREAKPOINT:
         str = "A breakpoint was encountered";
         break;
      case EXCEPTION_SINGLE_STEP:
         str = "A trace trap or other single-instruction mechanism signaled that one instruction has been executed";
         break;
      case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
         str = "The thread attempted to access an bastandard_array matter that is out of bounds, and the underlying hardware supports bounds checking";
         break;
      case EXCEPTION_FLT_DENORMAL_OPERAND:
         str = "One of the operands in a floating-point operation is denormal. A denormal value is one that is too small to represent as a standard floating-point value";
         break;
      case EXCEPTION_FLT_DIVIDE_BY_ZERO:
         str = "The thread attempted to divide a floating-point value by a floating-point divisor of zero";
         break;
      case EXCEPTION_FLT_INEXACT_RESULT:
         str = "The result of a floating-point operation cannot be represented exactly as a decimal fraction";
         break;
      case EXCEPTION_FLT_INVALID_OPERATION:
         str = "This exception represents any floating-point exception not included in this list";
         break;
      case EXCEPTION_FLT_OVERFLOW:
         str = "The exponent of a floating-point operation is greater than the magnitude allowed by the corresponding type";
         break;
      case EXCEPTION_FLT_STACK_CHECK:
         str = "The stack overflowed or underflowed as the result of a floating-point operation";
         break;
      case EXCEPTION_FLT_UNDERFLOW:
         str = "The exponent of a floating-point operation is less than the magnitude allowed by the corresponding type";
         break;
      case EXCEPTION_INT_DIVIDE_BY_ZERO:
         str = "The thread attempted to divide an integer value by an integer divisor of zero";
         break;
      case EXCEPTION_INT_OVERFLOW:
         str = "The result of an integer operation caused a carry out of the most significant bit of the result";
         break;
      case EXCEPTION_PRIV_INSTRUCTION:
         str = "The thread attempted to execute an instruction whose operation is not allowed in the current machine mode";
         break;
      case EXCEPTION_IN_PAGE_ERROR:
         str = "The thread tried to access a page that was not present, and the system was unable to load the page. For example, this exception might occur if a network connection is lost while running a program over the network";
         break;
      case EXCEPTION_ILLEGAL_INSTRUCTION:
         str = "The thread tried to execute an invalid instruction";
         break;
      case EXCEPTION_NONCONTINUABLE_EXCEPTION:
         str = "The thread attempted to continue execution after a noncontinuable exception occurred";
         break;
      case EXCEPTION_STACK_OVERFLOW:
         str = "The thread used up its stack";
         break;
      case EXCEPTION_INVALID_DISPOSITION:
         str = "An exception handler returned an invalid disposition to the exception dispatcher. Programmers using a high-level language such as C should never encounter this exception";
         break;
      case EXCEPTION_GUARD_PAGE:
         str = "Guard Page Exception";
         break;
      case EXCEPTION_INVALID_HANDLE:
         str = "Invalid Handle Exception";
         break;
      case 0xE06D7363:
         str = "Microsoft C++ Exception";
         break;
      default:
         str = "Unknown Exception (Not currently known by acme platform)";
         break;
      };

      return str;

   }


#else


   void filter_sigsegv(i32 signal, siginfo_t * psiginfo, void * pc)
   {

//      sigset_t set;
//      sigemptyset(&set);
//      sigaddset(&set, SIGSEGV);
//      pthread_sigmask(SIG_UNBLOCK, &set, nullptr);

      __throw(standard_access_violation(signal, psiginfo, pc));

   }


   void filter_sigfpe(i32 signal, siginfo_t * psiginfo, void * pc)
   {

      //sigset_t set;
      //sigemptyset(&set);
      //sigaddset(&set, SIGSEGV);
      //sigprocmask(SIG_UNBLOCK, &set, nullptr);

      __throw(standard_sigfpe(signal, psiginfo, pc));

   }


   void filter_sigpipe(i32 signal, siginfo_t * psiginfo, void * pc)
   {

//      sigset_t set;
//      sigemptyset(&set);
//      sigaddset(&set, SIGSEGV);
//      sigprocmask(SIG_UNBLOCK, &set, nullptr);

//       __throw(standard_sigfpe(nullptr, signal, psiginfo, pc));

   }


#endif


/*

   the_standard_translator the_standard_translator::s_thesetranslator;

   the_standard_translator::the_standard_translator()
   {

      attach();

   }

   the_standard_translator::~the_standard_translator()
   {

      detach();

   }

*/


} // namespace exception


CLASS_DECL_ACME bool g_bExiting;


#ifndef WINDOWS


void * standard_exception::siginfodup(void * psiginfo)
{

   siginfo_t * psiginfoDup = new siginfo_t;

   *psiginfoDup = * (siginfo_t *) psiginfo;

   return psiginfoDup;

}


void standard_exception::siginfofree(void * psiginfo)
{

   delete (siginfo_t *)psiginfo;

}


u32 standard_exception::code() const
{

   return ((siginfo_t *)m_psiginfo)->si_code;

}


void * standard_exception::address() const
{

   return ((siginfo_t *)m_psiginfo)->si_addr;

}


const void * standard_exception::info() const
{

   return m_psiginfo;

}


const char * standard_exception::name() const
{

   //return ::exception::translator::name(code());
   return "";

}


const char * standard_exception::description() const
{

   //return ::exception::translator::description(code());
   return "";

}


#ifndef ANDROID


const ucontext_t * standard_exception::context() const
{

   return &m_ucontext;

}


#endif
#endif


