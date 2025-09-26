#pragma once


#include "core/user/user/mesh_data.h"


class simple_mesh_data:
   public ::user::mesh_data
{
public:



   index_map_base < index_map_base < string > >          m_map;


   simple_mesh_data();
   ~simple_mesh_data() override;


   void _001GetSubItemText(::user::mesh_subitem * pitem) override;

   ::collection::count _001GetItemCount() override;
   ::collection::count _001GetColumnCount(::user::mesh * pmesh) override;

   virtual void clear();

};
