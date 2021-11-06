#pragma once


namespace user
{


   class list;


   class CLASS_DECL_CORE mesh_data :
      public ::data::data
   {
   public:


      string         m_strMeshSort;


      mesh_data();
      virtual ~mesh_data();


      virtual void _001GetItemText(mesh_item * pitem);

      virtual void _001GetItemImage(mesh_item * pitem);

      virtual void _001GetItemColor(mesh_item * pitem);

      virtual void _001GetGroupText(mesh_item * pitem);

      virtual void _001GetGroupImage(mesh_item * pitem);

      virtual count _001GetItemCount();

      virtual count _001GetColumnCount(mesh * pmesh);

      virtual count _001GetGroupCount();

      virtual ::count _001GetGroupMetaItemCount(index iGroup);

      virtual void _001OnDeleteRange(::user::range & range);

   };


} // namespace user



