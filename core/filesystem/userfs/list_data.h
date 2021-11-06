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
      ::duration m_durationLastFileSizeGet;

      list_item_array            m_itema;



      list_data();
      virtual ~list_data();


      inline __pointer(::userfs::list_item) item(index i) { return m_itema.get_item(i); }

      virtual void update();

      virtual void _001GetItemText(::user::mesh_item * pitem);

      virtual count _001GetItemCount();

      virtual void _001GetItemImage(::user::mesh_item * pitem);


   };


} // namespace userfs

