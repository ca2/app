#include "framework.h"

namespace aura
{

   namespace logic
   {

      bool forward_conditional(bool point, bool q)
      {
         return !point || q;
      }

      bool reverse_conditional(bool point, bool q)
      {
         return  q || !point;
      }

   } // namespace logic

} // namespace aura

