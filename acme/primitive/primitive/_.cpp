#include "framework.h"
#include "acme/primitive/primitive/atom.h"
#include "acme/primitive/primitive/matter.h"


extern ::pointer< ::mutex > g_pmutexChildren;


void _debug_debug_string_string()
{

   ::atom atom("a-ha");

   auto bEndsInHa1 = ::str().ends(atom, "ha");
   auto bEndsInHa2 = ::str().ends_ci(atom, "Ha");


}


void __assert_particle_ok(const ::matter * pOb, const char * pszFileName, i32 nLine)
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

   pOb->assert_ok();

}


CLASS_DECL_ACME void __call(::matter * pmatter)
{
   
   pmatter->run();
   
}



