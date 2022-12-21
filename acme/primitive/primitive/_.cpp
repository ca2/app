#include "framework.h"
#include "acme/primitive/primitive/atom.h"
//#include "acme/primitive/primitive/matter.h"
#include "acme/primitive/string/str.h"


extern ::pointer< ::mutex > g_pmutexChildren;


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

   if (!__is_valid_address(pOb, sizeof(matter)))
   {

      if (__assert_failed_line(pszFileName, nLine))
      {

         debug_break();

      }

      return;

   }

   if (!__is_valid_address(*(void **)pOb, sizeof(void *), false))
   {

      if (!__assert_failed_line(pszFileName, nLine))
      {

         debug_break();

      }

      return;

   }

   //pOb->assert_ok();

}


CLASS_DECL_ACME void __call(::particle * pparticle)
{
   
   pparticle->run();
   
}



