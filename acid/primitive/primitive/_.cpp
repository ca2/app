#include "framework.h"
#include "acid/primitive/primitive/atom.h"
//#include "acid/primitive/primitive/matter.h"
#include "acid/primitive/string/str.h"


//extern ::pointer< ::mutex > g_pmutexChildren;


void _debug_debug_string_string()
{

   ::atom atom("a-ha");

   /*auto bEndsInHa1 = string_ends<const ::ansi_character>(atom, "ha");
   auto bEndsInHa2 = string_ends_ci<const ::ansi_character>(atom, "Ha");*/

}


void __assert_particle_ok(const ::particle * pOb, const ::ansi_character * pszFileName, i32 nLine)
{

   if (pOb == nullptr)
   {

      if(!__assert_failed_line(pszFileName, nLine))
      {

         debug_break();

      }

      return;

   }

   if (!is_memory_segment_ok(pOb, sizeof(matter)))
   {

      if (__assert_failed_line(pszFileName, nLine))
      {

         debug_break();

      }

      return;

   }

   if (!is_memory_segment_ok(*(const void **)pOb, sizeof(void *)))
   {

      if (!__assert_failed_line(pszFileName, nLine))
      {

         debug_break();

      }

      return;

   }

   //pOb->assert_ok();

}


CLASS_DECL_ACID void __call(::particle * pparticle)
{
   
   pparticle->run();
   
}



