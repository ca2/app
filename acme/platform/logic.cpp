#include "framework.h"

namespace acme
{

   namespace logic
   {

      bool forward_conditional(bool point_i32, bool q)
      {
         return !point_i32 || q;
      }

      bool reverse_conditional(bool point_i32, bool q)
      {
         return  q || !point_i32;
      }

   } // namespace logic

} // namespace acme

