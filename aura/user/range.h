#pragma once


namespace user
{


   class range;

   class CLASS_DECL_AURA list_item_range
   {
   public:


      index      m_iLowerBound;
      index      m_iUpperBound;


      void set(index iLowerBoundListItem, index iUpperBoundListItem);



   };


   class CLASS_DECL_AURA sub_item_range
   {
   public:

      index                m_iLowerBound;
      index                m_iUpperBound;
      list_item_range      m_listitemrange;


      sub_item_range();
      sub_item_range(const sub_item_range& subitemrange);

      void set(index iLowerBoundSubItem, index iUpperBoundSubItem, index iLowerBoundListItem, index iUpperBoundListItem);

      bool has_sub_item(index iSubItem) const;

      sub_item_range& operator =(const sub_item_range& subitemrange);

   };


   class CLASS_DECL_AURA item_range
   {
   public:


      index             m_iLowerBound;
      index             m_iUpperBound;
      sub_item_range    m_subitemrange;


      item_range();
      item_range(const item_range& itemrange);


      void offset(index iOffset);
      void set(index iLowerBoundItem, index iUpperBoundItem, index iLowerBoundSubItem, index iUpperBoundSubItem, index iLowerBoundListItem, index iUpperBoundListItem);
      void set_lower_bound(index iLowerBoundItem);
      void set_upper_bound(index iUpperBoundItem);
      bool has_sub_item(index iSubItem) const;
      index get_lower_bound() const;
      index get_upper_bound() const;
      item_range& operator =(const item_range& itemrange);
      bool has_item(index iItem) const;
      void get_item_indexes(index_array& ia) const;

   };


   class CLASS_DECL_AURA range
   {
   public:


      array < item_range >    m_itemrangea;


      range(const range& range);
      range();


      range& operator = (const range& range);


      bool has_item(index iItem) const;
      bool has_sub_item(index iItem, index iSubItem) const;
      bool erase_item(index iItem);
      bool OnRemoveItem(index iItem);
      void clear();
      void add_item(const item_range& itemrange);
      item_range& ItemAt(index iIndex);
      ::index get_current_item();
      ::count get_item_count() const;
      ::count get_items(index_array& ia) const;
      ::count get_item_indexes(index_array& ia) const;

   };



} // namespace user




