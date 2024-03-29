#pragma once


namespace user
{


   class CLASS_DECL_CORE list_column_array :
   public pointer_array < ::user::list_column >
{
public:


   index               m_iFirstGlobalOrderKey;
   list * m_plist;
   index_to_index       m_mapSubItemIndex;


   list_column_array();


   void Initialize(list * plist);
   //index MapConfigIdToKey(const ::scoped_string & strDataKey);

   void clear_cache();



   //index add(list_column * pcolumn);

   void OnChange();

   void erase(index iColumn);


   //::count NonVisibleGetCount();
   //index NonVisibleMapSubItemToColumn(index iSubItem);
   void ShowSubItem(index iSubItem, bool bShow);

   index subitem_index(index iSubItem);
   index subitem_visible_index(index iSubItem);


   index control_id_index(const ::atom & atom);

   index add(list_column * pcolumn);
   //list_column * GlobalOrderGetPrevious(index iKey);
   //list_column * GlobalOrderGetNext(index iKey);

   //index VisibleMapSubItemToColumn(index iSubItem);
   ::count get_visible_count();

   ::count get_count();


   void erase_all();

   void DISaveOrder();

   void DILoadOrder();

   index visible_index_order(index iIndex);

   index order_index(index iOrder);

   //      index subitem_index(index iSubItem);
   index config_id_index(const ::scoped_string & strDataKey);

   //      index subitem_visible_index(index iSubItem);
   index config_id_visible_index(const ::scoped_string & strDataKey);
   index visible_index(index iKeyVisible);

   ::index get_index(const list_column * pcolumn) const;
   ::index get_visible_index(const list_column * pcolumn) const;
   list_column * get_visible(index iIndex);
   list_column * get_by_index(index iIndex);
   list_column * get_by_subitem(index iSubItem);
   list_column * get_by_control_id(const ::atom & atom);
   list_column * get_by_control(::user::interaction * pinteraction);
   list_column * get_by_config_id(const ::scoped_string & strDataKey);


   /// ::user::interaction * get_control();

};



} // namespace user



