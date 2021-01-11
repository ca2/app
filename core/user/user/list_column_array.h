#pragma once


namespace user
{


   class CLASS_DECL_CORE list_column_array :
   public pointer_array < ::user::list_column >
{
public:


   index               m_iFirstGlobalOrderKey;
   list * m_plist;


   list_column_array();


   void Initialize(list * plist);
   //index MapConfigIdToKey(const ::database::key & key);





   //index add(list_column * pcolumn);

   void OnChange();

   void remove(index iColumn);


   //::count NonVisibleGetCount();
   //index NonVisibleMapSubItemToColumn(index iSubItem);
   void ShowSubItem(index iSubItem, bool bShow);

   index subitem_index(index iSubItem);
   index subitem_visible_index(index iSubItem);


   index control_id_index(const ::id & id);

   index add(list_column * pcolumn);
   //list_column * GlobalOrderGetPrevious(index iKey);
   //list_column * GlobalOrderGetNext(index iKey);

   //index VisibleMapSubItemToColumn(index iSubItem);
   ::count VisibleGetCount();

   ::count get_count();


   void remove_all();

   void DISaveOrder();

   void DILoadOrder();

   index visible_index_order(index iIndex);

   index order_index(index iOrder);

   //      index subitem_index(index iSubItem);
   index config_id_index(const ::database::key & key);

   //      index subitem_visible_index(index iSubItem);
   index config_id_visible_index(const ::database::key & key);
   index visible_index(index iKeyVisible);

   ::index get_index(const list_column * pcolumn) const;
   ::index get_visible_index(const list_column * pcolumn) const;
   list_column * get_visible(index iIndex);
   list_column * get_by_index(index iIndex);
   list_column * get_by_subitem(index iSubItem);
   list_column * get_by_control_id(const ::id & id);
   list_column * get_by_control(::user::interaction * pinteraction);
   list_column * get_by_config_id(const ::database::key & key);


   /// ::user::interaction * get_control();

};



} // namespace user



