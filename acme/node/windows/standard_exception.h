#pragma once


namespace windows
{


   class CLASS_DECL_ACME standard_exception :
      public ::exception::exception
   {
   public:


      friend class ::exception::translator;


#ifdef WINDOWS
      EXCEPTION_POINTERS * m_ppointers;
#else
      i32            m_iSignal;
      void * m_psiginfo;
#ifndef ANDROID
      ucontext_t     m_ucontext;
#endif
#endif




#ifdef WINDOWS
      u32         code() const { return m_ppointers->ExceptionRecord->ExceptionCode; }
      void * address() const { return m_ppointers->ExceptionRecord->ExceptionAddress; }
      EXCEPTION_POINTERS * info() const { return m_ppointers; }
      const char * name() const { return ::exception::translator::name(code()); }
      const char * description() const { return ::exception::translator::description(code()); }
#else
      u32         code() const;
      void * address() const;
      const void * info() const;    // siginfo_t *
      const char * name() const;
      const char * description() const;
#ifndef ANDROID
      const ucontext_t * context() const;
#endif
#endif
      bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation[0]; }
      uptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation[1]; }



      standard_exception(EXCEPTION_POINTERS * ppointers) :
         exception(nullptr, error_exception, DEFAULT_SE_EXCEPTION_CALLSTACK_SKIP),
         m_ppointers(ppointers)
      {

      }


#ifdef WINDOWS


      //standard_exception(EXCEPTION_POINTERS * ppointers) :
      //   exception(error_exception, DEFAULT_SE_EXCEPTION_CALLSTACK_SKIP),
      //   m_ppointers(ppointers)
      //{

      //}

#else

      static void * siginfodup(void * psiginfo);
      static void siginfofree(void * psiginfo);

      standard_exception(i32 iSignal, void * psiginfo, void * pc, i32 iSkip = DEFAULT_SE_EXCEPTION_CALLSTACK_SKIP, void * caller_address = nullptr) :
         exception(error_exception, iSkip, caller_address),
         m_iSignal(iSignal),
         m_psiginfo(siginfodup(psiginfo))
#ifndef ANDROID
         , m_ucontext(*(ucontext_t *)pc)
#endif
      { /*_ASSERTE(psiginfo != 0);*/
      }

#endif


      virtual ~standard_exception()
      {
#ifndef WINDOWS
         siginfofree(m_psiginfo);
#endif
      }


      //u32         code() const { return m_ppointers->ExceptionRecord->ExceptionCode; }
      //void * address() const { return m_ppointers->ExceptionRecord->ExceptionAddress; }


   };


#ifdef WINDOWS

   class standard_no_memory : public standard_exception
   {
   public:


      standard_no_memory(EXCEPTION_POINTERS * ppointers) :
         standard_exception(ppointers)
      {

      }

   public:
      size_t mem_size() const { return info()->ExceptionRecord->ExceptionInformation[0]; }
   };

   class standard_access_violation : public standard_exception
   {
   public:

      standard_access_violation(EXCEPTION_POINTERS * ppointers) :
         standard_exception(ppointers)
      {

      }

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


} // namespace windows




