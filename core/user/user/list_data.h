#pragma once


#include "list_item.h"
#include "mesh_data.h"


namespace user
{


   class CLASS_DECL_CORE list_data :
      virtual public ::user::mesh_data
   {
   public:


      list_data();
      ~list_data() override;

   
      count _001GetColumnCount(mesh * pmesh) override;


   };


} // namespace user



