#include "framework.h"


namespace turboc
{


   main::main(::particle * pparticle) :
      ::thread(pparticle)
   {

      m_pfnMain = NULL;

   }


   main::~main()
   {

   }


   int main::run()
   {

      m_iReturnCode = 0;

      ASSERT(m_pfnMain != NULL);

      try
      {

         m_pfnMain();

      }
      catch(...)
      {

         m_iReturnCode = -1;

      }

      ::aura::post_quit_thread(System);

      return m_iReturnCode;

   }


} // namespace userstack



