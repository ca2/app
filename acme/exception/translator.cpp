// Created on 2021-04-29 1:03 PM BRT <3TBS_!! Second celebration of Mummis Birthday 70!!
#include "framework.h"


//namespace exception
//{


   exception_translator::exception_translator()
   {

      m_bSet = false;

//#ifdef EXCEPTION_TRANSLATOR_USE_SIGNAL
//
//      m_psig = new sig_companion;
//
//#endif

   }


   exception_translator::~exception_translator()
   {

#ifdef EXCEPTION_TRANSLATOR_USE_SIGNAL

//      if (m_psig != nullptr)
//      {
//
//         delete (sig_companion*)m_psig;
//
//      }

#endif

   }


//#ifdef WINDOWS
//
//   void __cdecl translator::filter2(u32 uiCode, EXCEPTION_POINTERS* ppointers)
//   {
//
//      if (g_bExiting)
//      {
//
//         return;
//
//      }
//
//      __UNREFERENCED_PARAMETER(uiCode);
//
//      //::acme::application * papp = ::get_app();
//
//      switch (ppointers->ExceptionRecord->ExceptionCode)
//      {
//#ifdef WINDOWS_DESKTOP
//      case EXCEPTION_NO_MEMORY:                 throw ::exception(::windows::standard_no_memory(ppointers));                  break;
//#endif
//      case EXCEPTION_ACCESS_VIOLATION:          throw ::exception(::windows::standard_access_violation(ppointers));           break;
//      case EXCEPTION_DATATYPE_MISALIGNMENT:     throw ::exception(::windows::standard_datatype_misalignment(ppointers));      break;
//      case EXCEPTION_BREAKPOINT:                throw ::exception(::windows::standard_breakpoint(ppointers));                 break;
//      case EXCEPTION_SINGLE_STEP:               throw ::exception(::windows::standard_single_step(ppointers));                break;
//      case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:     throw ::exception(::windows::standard_array_bounds_exceeded(ppointers));      break;
//      case EXCEPTION_FLT_DENORMAL_OPERAND:      throw ::exception(::windows::standard_flt_denormal_operand(ppointers));       break;
//      case EXCEPTION_FLT_DIVIDE_BY_ZERO:        throw ::exception(::windows::standard_flt_divide_by_zero(ppointers));         break;
//      case EXCEPTION_FLT_INEXACT_RESULT:        throw ::exception(::windows::standard_flt_inexact_result(ppointers));         break;
//      case EXCEPTION_FLT_INVALID_OPERATION:     throw ::exception(::windows::standard_flt_invalid_operation(ppointers));      break;
//      case EXCEPTION_FLT_OVERFLOW:              throw ::exception(::windows::standard_flt_overflow(ppointers));               break;
//      case EXCEPTION_FLT_STACK_CHECK:           throw ::exception(::windows::standard_flt_stack_check(ppointers));            break;
//      case EXCEPTION_FLT_UNDERFLOW:             throw ::exception(::windows::standard_flt_underflow(ppointers));              break;
//      case EXCEPTION_INT_DIVIDE_BY_ZERO:        throw ::exception(::windows::standard_int_divide_by_zero(ppointers));         break;
//      case EXCEPTION_INT_OVERFLOW:              throw ::exception(::windows::standard_int_overflow(ppointers));               break;
//      case EXCEPTION_PRIV_INSTRUCTION:          throw ::exception(::windows::standard_priv_instruction(ppointers));           break;
//      case EXCEPTION_IN_PAGE_ERROR:             throw ::exception(::windows::standard_in_page_error(ppointers));              break;
//      case EXCEPTION_ILLEGAL_INSTRUCTION:       throw ::exception(::windows::standard_illegal_instruction(ppointers));        break;
//      case EXCEPTION_NONCONTINUABLE_EXCEPTION:  throw ::exception(::windows::standard_noncontinuable_exception(ppointers));   break;
//      case EXCEPTION_STACK_OVERFLOW:            throw ::exception(::windows::standard_stack_overflow(ppointers));             break;
//      case EXCEPTION_INVALID_DISPOSITION:       throw ::exception(::windows::standard_invalid_disposition(ppointers));        break;
//      case EXCEPTION_GUARD_PAGE:                throw ::exception(::windows::standard_guard_page(ppointers));                 break;
//      case EXCEPTION_INVALID_HANDLE:            throw ::exception(::windows::standard_invalid_handle(ppointers));             break;
//      case 0xE06D7363:                          throw ::exception(::windows::standard_microsoft_cpp(ppointers));              break;
//      case 0x40080201:                          throw ::exception(::windows::standard_winrt_originate_error(ppointers));      break;
//      default:                                  throw ::exception(::windows::standard_exception(ppointers));                  break;
//      };
//
//   }
//
//#endif
//
//
//#ifndef WINDOWS
//
//   void filter_sigsegv(i32 signal, siginfo_t* psiginfo, void* pc);
//   void filter_sigfpe(i32 signal, siginfo_t* psiginfo, void* pc);
//   void filter_sigpipe(i32 signal, siginfo_t* psiginfo, void* pc);
//
//#endif

   
//   void translator::filter(u32 uiCode, _EXCEPTION_POINTERS* point_i32)
//   {
//
//
//   }


   bool exception_translator::attach()
   {

      if (!m_bSet)
      {

//#ifdef WINDOWS
//
//         m_pfn = _set_se_translator(&translator::filter2);
//
//         //m_pfn = SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER) GetThunk());
//
//         //PreventSetUnhandledExceptionFilter();
//
//         //EnforceFilter(true);
//
//#else
//
//#if defined(__APPLE__)
//
//         ::InstallUncaughtExceptionHandler();
//
//#endif
//
//         output_debug_string("exception standard translator");
//
//#if defined(__SANITIZE_ADDRESS__) || defined(__FOR_PERF__)
//
//         INFORMATION("sanitize address compilation, not going to install standard exception translator");
//
//#else
//
//         __zero(m_sig.m_saSeg);
//
//         m_sig.m_saSeg.sa_flags = SA_SIGINFO;
//
//         m_sig.m_saSeg.sa_sigaction = &filter_sigsegv;
//
//         if (sigaction(SIGSEGV, &m_sig.m_saSeg, &m_sig.m_saSegOld) < 0)
//         {
//
//            output_debug_string("failed to install segmentation fault signal handler");
//
//         }
//
//         __zero(m_sig.m_saFpe);
//
//         m_sig.m_saSeg.sa_flags = SA_SIGINFO;
//
//         m_sig.m_saFpe.sa_sigaction = &filter_sigfpe;
//
//         if (sigaction(SIGFPE, &m_sig.m_saFpe, &m_sig.m_saFpeOld) < 0)
//         {
//
//            output_debug_string("failed to install floating point_i32 exception signal handler");
//
//         }
//
//         __zero(m_sig.m_saPipe);
//
//         m_sig.m_saSeg.sa_flags = SA_SIGINFO;
//
//         m_sig.m_saPipe.sa_sigaction = &filter_sigpipe;
//
//         if (sigaction(SIGPIPE, &m_sig.m_saPipe, &m_sig.m_saPipeOld) < 0)
//         {
//
//            output_debug_string("failed to install pipe signal handler");
//
//         }
//
//#endif
//
//#endif

         m_bSet = true;

         return true;

      }
      else
      {

         return false;

      }

   }


   bool exception_translator::detach()
   {

      if (m_bSet)
      {

//#ifdef WINDOWS
//
//         _set_se_translator(m_pfn);
//
//#else

         /*sigaction(SIGSEGV, &m_sig.m_saSegOld, nullptr);

         sigaction(SIGFPE, &m_sig.m_saFpeOld, nullptr);

#endif*/

         m_bSet = false;

         return true;

      }
      else
      {

         return false;

      }

   }


//#ifdef WINDOWS
//
//
//   void translator::filter(u32 uiCode, EXCEPTION_POINTERS* ppointers)
//   {
//
//      __UNREFERENCED_PARAMETER(uiCode);
//
//      switch (ppointers->ExceptionRecord->ExceptionCode)
//      {
//#ifdef WINDOWS_DESKTOP
//      case EXCEPTION_NO_MEMORY:                 throw ::exception(::windows::standard_no_memory(ppointers));                  break;
//#endif
//      case EXCEPTION_ACCESS_VIOLATION:          throw ::exception(::windows::standard_access_violation(ppointers));           break;
//      case EXCEPTION_DATATYPE_MISALIGNMENT:     throw ::exception(::windows::standard_datatype_misalignment(ppointers));      break;
//      case EXCEPTION_BREAKPOINT:                throw ::exception(::windows::standard_breakpoint(ppointers));                 break;
//      case EXCEPTION_SINGLE_STEP:               throw ::exception(::windows::standard_single_step(ppointers));                break;
//      case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:     throw ::exception(::windows::standard_array_bounds_exceeded(ppointers));      break;
//      case EXCEPTION_FLT_DENORMAL_OPERAND:      throw ::exception(::windows::standard_flt_denormal_operand(ppointers));       break;
//      case EXCEPTION_FLT_DIVIDE_BY_ZERO:        throw ::exception(::windows::standard_flt_divide_by_zero(ppointers));         break;
//      case EXCEPTION_FLT_INEXACT_RESULT:        throw ::exception(::windows::standard_flt_inexact_result(ppointers));         break;
//      case EXCEPTION_FLT_INVALID_OPERATION:     throw ::exception(::windows::standard_flt_invalid_operation(ppointers));      break;
//      case EXCEPTION_FLT_OVERFLOW:              throw ::exception(::windows::standard_flt_overflow(ppointers));               break;
//      case EXCEPTION_FLT_STACK_CHECK:           throw ::exception(::windows::standard_flt_stack_check(ppointers));            break;
//      case EXCEPTION_FLT_UNDERFLOW:             throw ::exception(::windows::standard_flt_underflow(ppointers));              break;
//      case EXCEPTION_INT_DIVIDE_BY_ZERO:        throw ::exception(::windows::standard_int_divide_by_zero(ppointers));         break;
//      case EXCEPTION_INT_OVERFLOW:              throw ::exception(::windows::standard_int_overflow(ppointers));               break;
//      case EXCEPTION_PRIV_INSTRUCTION:          throw ::exception(::windows::standard_priv_instruction(ppointers));           break;
//      case EXCEPTION_IN_PAGE_ERROR:             throw ::exception(::windows::standard_in_page_error(ppointers));              break;
//      case EXCEPTION_ILLEGAL_INSTRUCTION:       throw ::exception(::windows::standard_illegal_instruction(ppointers));        break;
//      case EXCEPTION_NONCONTINUABLE_EXCEPTION:  throw ::exception(::windows::standard_noncontinuable_exception(ppointers));   break;
//      case EXCEPTION_STACK_OVERFLOW:            throw ::exception(::windows::standard_stack_overflow(ppointers));             break;
//      case EXCEPTION_INVALID_DISPOSITION:       throw ::exception(::windows::standard_invalid_disposition(ppointers));        break;
//      };
//
//   }
//
//
//   string translator::name(u32 uiCode)
//   {
//
//      string str;
//
//      switch (uiCode)
//      {
//#ifdef WINDOWS_DESKTOP
//      case EXCEPTION_NO_MEMORY:                 str = "No Memory";                  break;
//#endif
//      case EXCEPTION_ACCESS_VIOLATION:          str = "Access Violation";           break;
//      case EXCEPTION_DATATYPE_MISALIGNMENT:     str = "Datatype Misalignment";      break;
//      case EXCEPTION_BREAKPOINT:                str = "Breakpoint";                 break;
//      case EXCEPTION_SINGLE_STEP:               str = "Single Step";                break;
//      case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:     str = "Array Bounds Exceeded";      break;
//      case EXCEPTION_FLT_DENORMAL_OPERAND:      str = "Float Denormal Operand";     break;
//      case EXCEPTION_FLT_DIVIDE_BY_ZERO:        str = "Float Divide by Zero";       break;
//      case EXCEPTION_FLT_INEXACT_RESULT:        str = "Float Inexact Result";       break;
//      case EXCEPTION_FLT_INVALID_OPERATION:     str = "Float Invalid Operation";    break;
//      case EXCEPTION_FLT_OVERFLOW:              str = "Float Overflow";             break;
//      case EXCEPTION_FLT_STACK_CHECK:           str = "Float Stack Check";          break;
//      case EXCEPTION_FLT_UNDERFLOW:             str = "Float Underflow";            break;
//      case EXCEPTION_INT_DIVIDE_BY_ZERO:        str = "Integer Divide by Zero";     break;
//      case EXCEPTION_INT_OVERFLOW:              str = "Integer Overflow";           break;
//      case EXCEPTION_PRIV_INSTRUCTION:          str = "Privileged Instruction";     break;
//      case EXCEPTION_IN_PAGE_ERROR:             str = "In Page Error";              break;
//      case EXCEPTION_ILLEGAL_INSTRUCTION:       str = "Illegal Instruction";        break;
//      case EXCEPTION_NONCONTINUABLE_EXCEPTION:  str = "Noncontinuable Exception";   break;
//      case EXCEPTION_STACK_OVERFLOW:            str = "Stack Overflow";             break;
//      case EXCEPTION_INVALID_DISPOSITION:       str = "Invalid Disposition";        break;
//      case EXCEPTION_GUARD_PAGE:                str = "Guard Page";                 break;
//      case EXCEPTION_INVALID_HANDLE:            str = "Invalid Handle";             break;
//      case 0xE06D7363:                          str = "Microsoft C++ Exception";    break;
//      default:
//         str = "0x";
//         str += hex::lower_from(uiCode);
//         break;
//      };
//
//      return str;
//
//   }
//
//
//   string translator::description(u32 uiCode)
//   {
//
//      string str;
//
//      switch (uiCode)
//      {
//#ifdef WINDOWS_DESKTOP
//      case EXCEPTION_NO_MEMORY:
//         str = "The allocation attempt failed because of a lack of available memory or heap corruption.";
//         break;
//#endif
//      case EXCEPTION_ACCESS_VIOLATION:
//         str = "The thread attempted to read from or write to a virtual address for which it does not have the appropriate access";
//         break;
//      case EXCEPTION_DATATYPE_MISALIGNMENT:
//         str = "The thread attempted to read or write data that is misaligned on hardware that does not provide alignment. For example, 16-bit values must be aligned on 2-byte boundaries, 32-bit values on 4-byte boundaries, and so on";
//         break;
//      case EXCEPTION_BREAKPOINT:
//         str = "A breakpoint was encountered";
//         break;
//      case EXCEPTION_SINGLE_STEP:
//         str = "A trace trap or other single-instruction mechanism signaled that one instruction has been executed";
//         break;
//      case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
//         str = "The thread attempted to access an bastandard_array matter that is out of bounds, and the underlying hardware supports bounds checking";
//         break;
//      case EXCEPTION_FLT_DENORMAL_OPERAND:
//         str = "One of the operands in a floating-point_i32 operation is denormal. A denormal value is one that is too small to represent as a standard floating-point_i32 value";
//         break;
//      case EXCEPTION_FLT_DIVIDE_BY_ZERO:
//         str = "The thread attempted to divide a floating-point_i32 value by a floating-point_i32 divisor of zero";
//         break;
//      case EXCEPTION_FLT_INEXACT_RESULT:
//         str = "The result of a floating-point_i32 operation cannot be represented exactly as a decimal fraction";
//         break;
//      case EXCEPTION_FLT_INVALID_OPERATION:
//         str = "This exception represents any floating-point_i32 exception not included in this list";
//         break;
//      case EXCEPTION_FLT_OVERFLOW:
//         str = "The exponent of a floating-point_i32 operation is greater than the magnitude allowed by the corresponding type";
//         break;
//      case EXCEPTION_FLT_STACK_CHECK:
//         str = "The stack overflowed or underflowed as the result of a floating-point_i32 operation";
//         break;
//      case EXCEPTION_FLT_UNDERFLOW:
//         str = "The exponent of a floating-point_i32 operation is less than the magnitude allowed by the corresponding type";
//         break;
//      case EXCEPTION_INT_DIVIDE_BY_ZERO:
//         str = "The thread attempted to divide an integer value by an integer divisor of zero";
//         break;
//      case EXCEPTION_INT_OVERFLOW:
//         str = "The result of an integer operation caused a carry out of the most significant bit of the result";
//         break;
//      case EXCEPTION_PRIV_INSTRUCTION:
//         str = "The thread attempted to execute an instruction whose operation is not allowed in the current machine mode";
//         break;
//      case EXCEPTION_IN_PAGE_ERROR:
//         str = "The thread tried to access a page that was not present, and the system was unable to load the page. For example, this exception might occur if a network connection is lost while running a program over the network";
//         break;
//      case EXCEPTION_ILLEGAL_INSTRUCTION:
//         str = "The thread tried to execute an invalid instruction";
//         break;
//      case EXCEPTION_NONCONTINUABLE_EXCEPTION:
//         str = "The thread attempted to continue execution after a noncontinuable exception occurred";
//         break;
//      case EXCEPTION_STACK_OVERFLOW:
//         str = "The thread used up its stack";
//         break;
//      case EXCEPTION_INVALID_DISPOSITION:
//         str = "An exception handler returned an invalid disposition to the exception dispatcher. Programmers using a high-level language such as C should never encounter this exception";
//         break;
//      case EXCEPTION_GUARD_PAGE:
//         str = "Guard Page Exception";
//         break;
//      case EXCEPTION_INVALID_HANDLE:
//         str = "Invalid Handle Exception";
//         break;
//      case 0xE06D7363:
//         str = "Microsoft C++ Exception";
//         break;
//      default:
//         str = "Unknown Exception (Not currently known by acme platform)";
//         break;
//      };
//
//      return str;
//
//   }


#ifdef WINDOWS


   string exception_translator::_get_standard_exception_name(u32 uiCode)
   {

      return "";

   }


   string exception_translator::_get_standard_exception_description(u32 uiCode)
   {

      return "";

   }


#endif

//
//} // namespace translator
//
//

