#include "aura/platform.h"
#include "acme/platform/system.h"
#include "aura/user/user/range.h"

namespace
{
   ::user::item_range interval(::collection::index lower, ::collection::index upper)
   {
      ::user::item_range result;
      result.set(lower, upper, 2, 4, 6, 8);
      return result;
   }
}

int main()
{
   ::platform::system runtime;
   // Compare every small interval subtraction with the expected selected rows.
   for (int lower = 0; lower < 8; ++lower)
   for (int upper = lower; upper < 8; ++upper)
   for (int clearLower = 0; clearLower < 8; ++clearLower)
   for (int clearUpper = clearLower; clearUpper < 8; ++clearUpper)
   {
      ::user::range selection;
      selection.add_item(interval(lower, upper));
      selection.clear_item(interval(clearLower, clearUpper));
      for (int row = 0; row < 9; ++row)
         if (selection.has_item(row) != (row >= lower && row <= upper
            && !(row >= clearLower && row <= clearUpper))) return 1;
      for (const auto & remaining : selection.m_itemrangea)
      {
         if (remaining.get_lower_bound() > remaining.get_upper_bound()) return 2;
         if (remaining.m_subitemrange.m_iLowerBound != 2
            || remaining.m_subitemrange.m_iUpperBound != 4
            || remaining.m_subitemrange.m_listitemrange.m_iLowerBound != 6
            || remaining.m_subitemrange.m_listitemrange.m_iUpperBound != 8) return 3;
      }
      if (clearLower <= lower && clearUpper >= upper
         && selection.m_itemrangea.has_element()) return 4;
   }
   ::user::range selection;
   selection.add_item(interval(0, 4));
   selection.add_item(interval(3, 9));
   selection.add_item(interval(12, 12));
   selection.clear_item(interval(2, 7));
   if (selection.get_item_count() != 3 || selection.has_item(3)
      || !selection.has_item(0) || !selection.has_item(8) || !selection.has_item(12)) return 5;
   selection.clear_item(selection.ItemAt(0)); // The argument may alias the array.
   if (selection.has_item(0) || selection.has_item(1) || selection.get_item_count() != 2) return 6;
   selection.clear_item(interval(12, 12));
   if (selection.has_item(12) || selection.get_item_count() != 1) return 7;
   selection.clear_item(interval(-1, -1));
   selection.clear_item(interval(9, 8));
   if (!selection.has_item(8) || !selection.has_item(9)) return 8;
   selection.clear_item(interval(0, 20));
   if (selection.m_itemrangea.has_element()) return 9;
   selection.clear_item(interval(0, 20));
   return 0;
}
