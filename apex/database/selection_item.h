#pragma once


#include "key.h"


namespace database
{


   class CLASS_DECL_APEX selection_item
   {
   public:


      key     m_datakey;


      selection_item();
      selection_item(const key & key);
      selection_item(const selection_item & selection_item);
      ~selection_item();


   };


} // namespace database




