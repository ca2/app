#include "framework.h"
#include "acme/prototype/prototype/atom.h"
//#include "acme/prototype/prototype/matter.h"
#include "acme/prototype/string/str.h"


//extern ::pointer< ::mutex > g_pmutexChildren;


void _debug_debug_string_string()
{

   ::atom atom("a-ha");

   /*auto bEndsInHa1 = string_ends<const ::ansi_character>(atom, "ha");
   auto bEndsInHa2 = case_insensitive_string_ends<const ::ansi_character>(atom, "Ha");*/

}


void __assert_particle_ok(const ::particle * p, const_char_pointer pszFileName, int nLine)
{

   if (p == nullptr)
   {

      if(!__assert_failed_line(pszFileName, nLine))
      {

         debug_break();

      }

      return;

   }

   if (!is_memory_segment_ok(p, sizeof(::particle)))
   {

      if (__assert_failed_line(pszFileName, nLine))
      {

         debug_break();

      }

      return;

   }

   if (!is_memory_segment_ok(*(const void **)p, sizeof(void *)))
   {

      if (!__assert_failed_line(pszFileName, nLine))
      {

         debug_break();

      }

      return;

   }

   p->assert_particle_ok();

}


CLASS_DECL_ACME void __call(::particle * pparticle)
{
   
   pparticle->run();
   
}



