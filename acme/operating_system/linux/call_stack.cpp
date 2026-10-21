#include "platform.h"
#include "acme/operating_system/ansi/call_stack.h"
#include "acme/exception/call_stack.h"
//#include "_linux.h"

#include <execinfo.h>
#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#undef USE_MISC


void call_stack::capture(::i32 iSkip, void * caller_address, ::i32 iCount)
{

   free((void *)m_pszCallStack);
   m_pszCallStack = nullptr;
   m_caller_address = caller_address;
   m_u32Hash = 0;
   m_iCount = 0;

   if (iCount == 0)
   {
      return;
   }

   auto frames = ::backtrace(m_stack, TRACE_MAX_STACK_FRAMES);
   // The first frame is capture itself; negative skip selects the default.
   auto skip = iSkip < 0 ? (frames > 0 ? 1 : 0) : (iSkip >= frames ? frames : iSkip + 1);
   // A supplied caller address selects the start when present in this stack.
   if (caller_address)
   {
      for (int i = skip; i < frames; ++i)
      {
         if (m_stack[i] == caller_address)
         {
            skip = i;
            break;
         }
      }
   }
   auto count = frames - skip;
   if (iCount >= 0 && count > iCount)
   {
      count = iCount;
   }
   for (int i = 0; i < count; ++i)
   {
      m_stack[i] = m_stack[i + skip];
      auto address = (uintptr_t)m_stack[i];
      // Fold every byte so that the hash includes all bits of a 64-bit PC.
      for (size_t byte = 0; byte < sizeof(address); ++byte)
      {
         m_u32Hash = m_u32Hash * 33 + (address & 0xff);
         address >>= 8;
      }
   }
   m_iCount = count;

}


::i32 call_stack::_prepare_trace(const_char_pointer pszFormat)
{

   // Match the Windows backend's module + offset representation.
   ::i32 size = 64;
   for (::i32 i = 0; i < m_iCount; ++i)
   {
      Dl_info info = {};
      const char * path = "(unknown)";
      m_modulea[i] = nullptr;
      if (::dladdr(m_stack[i], &info))
      {
         m_modulea[i] = info.dli_fbase;
         if (info.dli_fname && *info.dli_fname)
         {
            path = info.dli_fname;
         }
      }
      ::snprintf(m_szaModulePath[i], MODULE_BUF_SIZE, "%s", path);
      m_u32ModulePathLength[i] = ::strlen(m_szaModulePath[i]);
      size += m_u32ModulePathLength[i] + 64;
   }
   return size;

}


const_char_pointer call_stack::_trace(::i32 iSize, const_char_pointer pszFormat)
{

   if (iSize <= 0)
   {
      return nullptr;
   }
   auto trace = (char *)::malloc(iSize);
   if (!trace)
   {
      return nullptr;
   }
   trace[0] = '\0';
   auto written = ::snprintf(trace, iSize, "Stack hash: 0x%08x\n", (unsigned int)m_u32Hash);
   size_t used = written < 0 ? 0 : (size_t)written;
   for (::i32 i = 0; i < m_iCount && used < (size_t)iSize; ++i)
   {
      auto offset = (uintptr_t)m_stack[i] - (uintptr_t)m_modulea[i];
      written = ::snprintf(trace + used, iSize - used, "%02d:%s+0x%016llx\n",
         i, m_szaModulePath[i], (unsigned long long)offset);
      if (written < 0)
      {
         break;
      }
      used += (size_t)written;
   }
   return trace;

}


string get_callstack(::particle * pparticle, const_char_pointer pszFormat, ::i32 iSkip, void * caller_address, ::i32 iCount)
{

   const size_t iMaximumFramesToCapture = 64;

   void * stack[iMaximumFramesToCapture];

   auto frames = ::backtrace(stack, iMaximumFramesToCapture);

   return _ansi_stack_trace(pparticle, stack, frames, pszFormat, iSkip);

}

template < typename TYPE >
class malloc_array
{
public:

   TYPE **   m_pp;


   malloc_array(TYPE ** pp): m_pp(pp) { }


   ~malloc_array()
   {

      auto pp = m_pp;

      while(*pp)
      {

         free(*pp);

         pp++;

      }

   }


   TYPE ** operator ->() {return m_pp;}

   operator TYPE **() {return m_pp;}

   TYPE ** get() {return m_pp;}

};



//} // namespace exception

#ifdef __USE_BFD

#define _GNU_SOURCE
#include <stdio.h>

#include <dlfcn.h>

#include <execinfo.h>
#include <signal.h>
#include <bfd.h>
#undef USE_MISC


/* globals retained across calls to resolve. */
static const_char_pointer moda[]= {"/ca2/stage/x86/libapex.so", "/ca2/stage/x86/libbase.so", "/ca2/stage/x86/libcore.so", nullptr};
static bfd* abfda[64];
static asymbol **symsa[64];
static asection *texta[64];
static ::i32 bfdcount = 0;

::i32 free_resolve_addr_file_func_line()
{

   ::i32 i = 0;

   while(i < 64)
   {

      if(abfda[i] == nullptr)
      {

         return i;

      }

      i++;

   }

   return -1;

}

bool prep_resolve_addr_file_func_line(const_char_pointer f)
{

   ::i32 i = free_resolve_addr_file_func_line();

   if(i < 0)
   {

      return false;

   }

   bfd* & abfd = abfda[i];

   asymbol ** & syms = symsa[i];

   asection * & text = texta[i];

   abfd = bfd_openr(f, 0);

   if (!abfd)
   {

      fprintf(stderr, "bfd_openr failed: ");

      return false;

   }

   /* oddly, this is required for it to work... */
   bfd_check_format(abfd,bfd_object);

   ::u32 storage_needed = bfd_get_symtab_upper_bound(abfd);

   syms = (asymbol **) malloc(storage_needed);

   ::u32 cSymbols = bfd_canonicalize_symtab(abfd, syms);

   text = bfd_get_section_by_name(abfd, ".text");

   return true;

}


void init_resolve_addr_file_func_line()
{

   if(bfdinit)
      return;

   bfdinit = 1;

   zero(abfda);

   zero(symsa);

   zero(texta)

   bfd_init();

   ::i8 ename[1024];

   ::i32 l = readlink("/proc/self/exe",ename,sizeof(ename));

   if (l == -1)
   {

      fprintf(stderr, "failed to find executable\n");

      return false;

   }

   ename[l] = 0;

   prep_resolve_addr_file_func_line(ename);

   const_char_pointer *point = (const_char_pointer *) moda;

   while(*point)
   {

      if(prep_resolve_addr_file_func_line(*point))
      {
         bfdcount++;

      }

      point++;

   }

}

bool resolve_addr_file_func_line1(bfd* abfd, asymbol **syms, asection *text, void *address, const_char_pointer *filename, const_char_pointer *func, ::u32 & iLine)
{
   long offset = ((long)address) - text->vma;
   if (offset > 0)
   {
      *filename = nullptr;
      *func = nullptr;

      if (bfd_find_nearest_line(abfd, text, syms, offset, filename, func, &iLine) && *filename)
         return true;
      return false;
   }
   return false;
}


bool resolve_addr_file_func_line(void *address, const_char_pointer *filename, const_char_pointer *func, ::u32 & iLine)
{
   ::i32 i;
   while(i < bfdcount)
   {

      if(resolve_addr_file_func_line1(abfda[i], symsa[i], texta[i],address, filename, func, iLine))
         return true;

      i++;

   }
   return false;
}


#endif



