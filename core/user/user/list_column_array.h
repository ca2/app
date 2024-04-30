#pragma once


namespace user
{


   class CLASS_DECL_CORE list_column_array :
   public pointer_array < ::user::list_column >
{
public:


   ::raw::index               m_iFirstGlobalOrderKey;
   list * m_plist;
   index_to_index       m_mapSubItemIndex;


   list_column_array();


   void Initialize(list * plist);
   //index MapConfigIdToKey(const ::scoped_string & strDataKey);

   void clear_cache();



   //index add(list_column * pcolumn);

   void OnChange();

   void erase(::raw::index iColumn);


   //::raw::count NonVisibleGetCount();
   //index NonVisibleMapSubItemToColumn(::raw::index iSubItem);
   void ShowSubItem(::raw::index iSubItem, bool bShow);

   ::raw::index subitem_index(::raw::index iSubItem);
   ::raw::index subitem_visible_index(::raw::index iSubItem);


   ::raw::index control_id_index(const ::atom & atom);

   ::raw::index add(list_column * pcolumn);
   //list_column * GlobalOrderGetPrevious(::raw::index iKey);
   //list_column * GlobalOrderGetNext(::raw::index iKey);

   //index VisibleMapSubItemToColumn(::raw::index iSubItem);
   ::raw::count get_visible_count();

   ::raw::count get_count();


   void erase_all();

   void DISaveOrder();

   void DILoadOrder();

   ::raw::index visible_index_order(::raw::index iIndex);

   ::raw::index order_index(::raw::index iOrder);

   //      index subitem_index(::raw::index iSubItem);
   ::raw::index config_id_index(const ::scoped_string & strDataKey);

   //      index subitem_visible_index(::raw::index iSubItem);
   ::raw::index config_id_visible_index(const ::scoped_string & strDataKey);
   ::raw::index visible_index(::raw::index iKeyVisible);

   ::raw::index get_index(const list_column * pcolumn) const;
   ::raw::index get_visible_index(const list_column * pcolumn) const;
   list_column * get_visible(::raw::index iIndex);
   list_column * get_by_index(::raw::index iIndex);
   list_column * get_by_subitem(::raw::index iSubItem);
   list_column * get_by_control_id(const ::atom & atom);
   list_column * get_by_control(::user::interaction * pinteraction);
   list_column * get_by_config_id(const ::scoped_string & strDataKey);


   /// ::user::interaction * get_control();

};



} // namespace user



