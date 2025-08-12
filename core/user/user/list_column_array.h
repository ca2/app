#pragma once


namespace user
{


   class CLASS_DECL_CORE list_column_array :
   public pointer_array < ::user::list_column >
{
public:


   ::collection::index               m_iFirstGlobalOrderKey;
   list_base * m_plist;
   index_to_index       m_mapSubItemIndex;


   list_column_array();


   void Initialize(list_base * plist);
   //index MapConfigIdToKey(const ::scoped_string & strDataKey);

   void clear_cache();



   //index add(list_column * pcolumn);

   void OnChange();

   void erase(::collection::index iColumn);


   //::collection::count NonVisibleGetCount();
   //index NonVisibleMapSubItemToColumn(::collection::index iSubItem);
   void ShowSubItem(::collection::index iSubItem, bool bShow);

   ::collection::index subitem_index(::collection::index iSubItem);
   ::collection::index subitem_visible_index(::collection::index iSubItem);


   ::collection::index control_id_index(const ::atom & atom);

   ::collection::index add(list_column * pcolumn);
   //list_column * GlobalOrderGetPrevious(::collection::index iKey);
   //list_column * GlobalOrderGetNext(::collection::index iKey);

   //index VisibleMapSubItemToColumn(::collection::index iSubItem);
   ::collection::count get_visible_count();

   ::collection::count get_count();


   void erase_all();

   void DISaveOrder();

   void DILoadOrder();

   ::collection::index visible_index_order(::collection::index iIndex);

   ::collection::index order_index(::collection::index iOrder);

   //      index subitem_index(::collection::index iSubItem);
   ::collection::index config_id_index(const ::scoped_string & strDataKey);

   //      index subitem_visible_index(::collection::index iSubItem);
   ::collection::index config_id_visible_index(const ::scoped_string & strDataKey);
   ::collection::index visible_index(::collection::index iKeyVisible);

   ::collection::index get_index(const list_column * pcolumn) const;
   ::collection::index get_visible_index(const list_column * pcolumn) const;
   list_column * get_visible(::collection::index iIndex);
   list_column * get_by_index(::collection::index iIndex);
   list_column * get_by_subitem(::collection::index iSubItem);
   list_column * get_by_control_id(const ::atom & atom);
   list_column * get_by_control(::user::interaction * pinteraction);
   list_column * get_by_config_id(const ::scoped_string & strDataKey);


   /// ::user::interaction * get_control();

};



} // namespace user



