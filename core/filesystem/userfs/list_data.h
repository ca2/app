#pragma once


namespace userfs
{


   class CLASS_DECL_CORE list_data :
      public ::user::list_data
   {
   public:


      index                      m_iNameSubItem;
      index                      m_iNameSubItemText;
      index                      m_iSelectionSubItem;
      index                      m_iSizeSubItem;
      ::duration                 m_durationLastFileSizeGet;

      list_item_array            m_itema;



      list_data();
      ~list_data() override;


      inline ::userfs::list_item * item(index i) { return m_itema.get_item(i); }

      virtual void update();

      void _001GetSubItemText(::user::mesh_subitem * psubitem) override;

      count _001GetItemCount() override;

      void _001GetSubItemImage(::user::mesh_subitem * psubitem) override;


   };


} // namespace userfs

