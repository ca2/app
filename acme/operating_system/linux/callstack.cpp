#include "framework.h"
#include "acme/operating_system/ansi/callstack.h"
#include "_linux.h"
#include <execinfo.h>
#include <cxxabi.h>
#undef USE_MISC

string get_callstack(const char* pszFormat, i32 iSkip, void * caller_address, int iCount)
{


   const size_t iMaximumFramesToCapture = 64;

   void * stack[iMaximumFramesToCapture];

   auto frames = ::backtrace(stack, iMaximumFramesToCapture);

   return _ansi_stack_trace(stack, frames, pszFormat);

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
static const char * moda[]= {"/ca2/stage/x86/libapex.so", "/ca2/stage/x86/libbase.so", "/ca2/stage/x86/libcore.so", nullptr};
static bfd* abfda[64];
static asymbol **symsa[64];
static asection *texta[64];
static int bfdcount = 0;

int free_resolve_addr_file_func_line()
{

   int i = 0;

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

bool prep_resolve_addr_file_func_line(const char * f)
{

   int i = free_resolve_addr_file_func_line();

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

      perror("bfd_openr failed: ");

      return false;

   }

   /* oddly, this is required for it to work... */
   bfd_check_format(abfd,bfd_object);

   unsigned storage_needed = bfd_get_symtab_upper_bound(abfd);

   syms = (asymbol **) malloc(storage_needed);

   unsigned cSymbols = bfd_canonicalize_symtab(abfd, syms);

   text = bfd_get_section_by_name(abfd, ".text");

   return true;

}


void init_resolve_addr_file_func_line()
{

   if(bfdinit)
      return;

   bfdinit = 1;

   __zero(abfda);

   __zero(symsa);

   __zero(texta)

   bfd_init();

   char ename[1024];

   int l = readlink("/proc/self/exe",ename,sizeof(ename));

   if (l == -1)
   {

      perror("failed to find executable\n");

      return false;

   }

   ename[l] = 0;

   prep_resolve_addr_file_func_line(ename);

   const char ** point = (const char **) moda;

   while(*point)
   {

      if(prep_resolve_addr_file_func_line(*point))
      {
         bfdcount++;

      }

      point++;

   }

}

bool resolve_addr_file_func_line1(bfd* abfd, asymbol **syms, asection *text, void *address, const char * * filename, const char ** func, unsigned & iLine)
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


bool resolve_addr_file_func_line(void *address, const char * * filename, const char ** func, unsigned & iLine)
{
   int i;
   while(i < bfdcount)
   {

      if(resolve_addr_file_func_line1(abfda[i], symsa[i], texta[i],address, filename, func, iLine))
         return true;

      i++;

   }
   return false;
}


#endif


void backtrace_symbol_parse(string & strSymbolName, string & strAddress, char * pmessage, void * address)
{

   char * pszMangledName = nullptr;

   char * pszOffsetBegin = nullptr;

   char * pszOffsetEnd = nullptr;

   // find parantheses and +address offset surrounding mangled name
   for (char * psz = pmessage; *psz; ++psz)
   {

      if (*psz == '(')
      {

         pszMangledName = psz;

      }
      else if (*psz == '+')
      {

         pszOffsetBegin = psz;

      }
      else if (*psz == ')')
      {

         pszOffsetEnd = psz;

         break;

      }

   }

   if (pszMangledName && pszOffsetBegin && pszOffsetEnd && pszMangledName < pszOffsetBegin)
   {

      *pszMangledName++ = '\0';
      *pszOffsetBegin++ = '\0';
      *pszOffsetEnd++ = '\0';

      i32 status;

      acme::malloc < char * > pszRealName = abi::__cxa_demangle(pszMangledName, 0, 0, &status);

      const char * pszSymbolName;

      if (status == 0)
      {

         strSymbolName = (const char *) (char *) pszRealName;

      }
      else
      {

         strSymbolName = pszMangledName;

      }

      strAddress = pszOffsetEnd;

   }

}



