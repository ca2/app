#include "framework.h"
#include "selection.h"


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








