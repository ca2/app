#pragma once

namespace constraint
{
   template <class CLASS > void constraint_min(CLASS & ca, const CLASS & cMin)
   {
      if(ca < cMin)
      {
         ca = cMin;
      }
   }
}
