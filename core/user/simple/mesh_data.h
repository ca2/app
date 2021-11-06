#pragma once


class simple_mesh_data:
   public ::user::mesh_data
{
public:



   index_map < index_map < string > >          m_map;


   simple_mesh_data();
   virtual ~simple_mesh_data();


   virtual void _001GetItemText(::user::mesh_item * pitem);

   virtual ::count _001GetItemCount();
   virtual ::count _001GetColumnCount(::user::mesh * pmesh);

   virtual void clear();

};
