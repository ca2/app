#include "framework.h"

namespace apex
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

} // namespace apex

