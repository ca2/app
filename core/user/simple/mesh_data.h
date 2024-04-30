#pragma once


#include "core/user/user/mesh_data.h"


class simple_mesh_data:
   public ::user::mesh_data
{
public:



   index_map < index_map < string > >          m_map;


   simple_mesh_data();
   ~simple_mesh_data() override;


   void _001GetSubItemText(::user::mesh_subitem * pitem) override;

   ::raw::count _001GetItemCount() override;
   ::raw::count _001GetColumnCount(::user::mesh * pmesh) override;

   virtual void clear();

};
