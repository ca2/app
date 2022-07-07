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
      ~mesh_data() override;


      virtual void _001GetSubItemText(mesh_subitem * pitem);

      virtual void _001GetSubItemImage(mesh_subitem * pitem);

      virtual void _001GetSubItemColor(mesh_subitem * pitem);

      virtual void _001GetGroupItemText(mesh_group * pgroup);

      virtual void _001GetGroupImage(mesh_group * pgroup);

      virtual count _001GetItemCount();

      virtual count _001GetColumnCount(mesh * pmesh);

      virtual count _001GetGroupCount();

      virtual ::count _001GetGroupMetaItemCount(index iGroup);

      virtual void _001OnDeleteRange(::user::range & range);


   };


} // namespace user



