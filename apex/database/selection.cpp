#include "framework.h"


namespace database
{


   selection::selection()
   {

   }


   selection::~selection()
   {

   }


   void selection::add_item(class key id)
   {

      selection_item item(id);

      m_itema.add(item);

   }


} // namespace database








