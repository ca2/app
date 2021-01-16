#include "framework.h"






#ifdef DEBUG_FLAGS

namespace ___FlagsDebug
{
   
   
   void FlagsDebug();

   enum ___EFlagsDebug
   {
      ___FlagsDebugA,
      ___FlagsDebugB,
      ___FlagsDebugC,
      ___FlagsDebugD,
      ___FlagsDebugE,
   };
   void FlagsDebug()
   {
      flags < ___EFlagsDebug > flagsdebug;
      flagsdebug.add(___FlagsDebugA);
      flagsdebug.remove(___FlagsDebugB);
      flags < ___EFlagsDebug > flagsdebugB;
      flagsdebugB = flagsdebug;
   
   
      flags < ___EFlagsDebug > flagsdebugC;
      flagsdebugC.add(___FlagsDebugA);
      flagsdebugC.add(___FlagsDebugB);
      flagsdebugC.add(___FlagsDebugC);
      flagsdebugC.add(___FlagsDebugD);
      ASSERT(flagsdebugC.has(___FlagsDebugA));
      ASSERT(flagsdebugC.has(___FlagsDebugB));
      ASSERT(flagsdebugC.has(___FlagsDebugD));
      ASSERT(flagsdebugC.has(___FlagsDebugD));
      ASSERT(!flagsdebugC.has(___FlagsDebugE));
      flagsdebugC.remove(___FlagsDebugD);
      ASSERT(flagsdebugC.has(___FlagsDebugA));
      ASSERT(flagsdebugC.has(___FlagsDebugB));
      ASSERT(flagsdebugC.has(___FlagsDebugD));
      ASSERT(!flagsdebugC.has(___FlagsDebugD));
      ASSERT(!flagsdebugC.has(___FlagsDebugE));
   }

} // namespace ___FlagsDebug

#endif // DEBUG_FLAGS




