#pragma once


#include "acme/prototype/data/tree.h"
#include "acme/prototype/data/tree_item.h"
#include "item.h"


namespace filehandler
{


   class CLASS_DECL_CORE tree_interface :
      virtual public ::data::tree < item >
   {
   public:


      tree_interface();
      virtual ~tree_interface();


      void update_list();


   };


} // namespace filehandler







