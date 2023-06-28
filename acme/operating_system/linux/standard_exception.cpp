#include "framework.h"
#include "_linux.h"
#include "standard_exception.h"
//#include "acme/exception/standard.h"



standard_exception::standard_exception(i32 iSignal, void * psiginfo, void * pc, i32 iSkip, void * caller_address) :
::exception(error_exception, nullptr, nullptr, iSkip, caller_address),
m_iSignal(iSignal),
m_psiginfo(siginfodup(psiginfo)),
m_ucontext(*((::ucontext_t *)pc))
{

   /*_ASSERTE(psiginfo != 0);*/

}


#if defined(ANDROID) || defined(RASPBERRYPIOS)


standard_access_violation::standard_access_violation (i32 signal, void * psiginfo, void * pc) :
      ::standard_exception(signal, psiginfo, pc)
   {

   }


#elif defined(FREEBSD_UNIX)


standard_access_violation::standard_access_violation (i32 signal, void * psiginfo, void * pc) :
   standard_exception(signal, psiginfo, pc, 3, (void *) pc)
{


}


#elif defined(LINUX) || defined(__APPLE__) || defined(SOLARIS)


#ifdef LINUX
standard_access_violation::standard_access_violation (i32 signal, void * psiginfo, void * pc) :
#ifdef _LP64
standard_exception(signal, psiginfo, pc, 6, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.rip)
#else
standard_exception(signal, psiginfo, pc, 3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.eip)
#endif
#else
#ifdef _LP64
#ifdef __arm64__
   standard_exception(signal, psiginfo, pc, 3, (void *) ((ucontext_t *) pc)->uc_mcontext->__ss.__pc)
#else
   standard_exception(signal, psiginfo, pc, 3, (void *) ((ucontext_t *) pc)->uc_mcontext->__ss.__rip)
#endif
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
//       ::standard_exception(pparticle, signal, psiginfo, pc)
{

}

#endif

/*       sig_ucontext_t * uc = (sig_ucontext_t *)ucontext;

       void * caller_address = (void *) uc->uc_mcontext.eip; // x86 specific

       str += "signal " + ansi_string_from_i64(sig_num) +
                 +" (" + ansi_string_from_i64(sig_num) + "), address is "  +
                 itohex_dup(info->si_addr) + " from " + itohex_dup(caller_address) + "\n\n";*/


void * standard_exception::siginfodup(void * psiginfo)
{

   auto p = malloc(sizeof(siginfo_t));

   memcpy(p, psiginfo, sizeof(siginfo_t));

   return p;

}


void standard_exception::siginfofree(void * psiginfo)
{

   ::free(psiginfo);

}



