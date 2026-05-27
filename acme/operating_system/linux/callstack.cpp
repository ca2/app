#include "framework.h"
#include "acme/operating_system/ansi/call_stack.h"
//#include "_linux.h"

#include <execinfo.h>
#undef USE_MISC


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



