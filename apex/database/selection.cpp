#include "framework.h"
#include "selection.h"
#include "selection_item.h"


namespace database
{


   selection::selection()
   {

   }


   selection::~selection()
   {

   }


   void selection::add_item(class key atom)
   {

      selection_item item(atom);

      m_itema.add(item);

   }


} // namespace database








