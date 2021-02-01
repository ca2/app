#pragma once

namespace acme
{

   namespace logic
   {

      CLASS_DECL_ACME bool forward_conditional(bool point_i32, bool q); // it tests point_i32 before
      CLASS_DECL_ACME bool reverse_conditional(bool point_i32, bool q); // it tests q before

   } // namespace logic

} // namespace acme

