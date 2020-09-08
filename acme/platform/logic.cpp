#include "framework.h"

namespace acme
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

} // namespace acme

