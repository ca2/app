#pragma once


//#include "acme/prototype/collection/array.h"


namespace user
{


   class range;


   class CLASS_DECL_AURA list_item_range
   {
   public:


      ::collection::index      m_iLowerBound;
      ::collection::index      m_iUpperBound;


      void set(::collection::index iLowerBoundListItem, ::collection::index iUpperBoundListItem);



   };


   class CLASS_DECL_AURA sub_item_range
   {
   public:

      ::collection::index                m_iLowerBound;
      ::collection::index                m_iUpperBound;
      list_item_range      m_listitemrange;


      sub_item_range();
      sub_item_range(const sub_item_range& subitemrange);

      void set(::collection::index iLowerBoundSubItem, ::collection::index iUpperBoundSubItem, ::collection::index iLowerBoundListItem, ::collection::index iUpperBoundListItem);

      bool has_sub_item(::collection::index iSubItem) const;

      sub_item_range& operator =(const sub_item_range& subitemrange);

   };


   class CLASS_DECL_AURA item_range
   {
   public:


      ::collection::index             m_iLowerBound;
      ::collection::index             m_iUpperBound;
      sub_item_range    m_subitemrange;


      item_range();
      item_range(const item_range& itemrange);


      void offset(::collection::index iOffset);
      void set(::collection::index iLowerBoundItem, ::collection::index iUpperBoundItem, ::collection::index iLowerBoundSubItem, ::collection::index iUpperBoundSubItem, ::collection::index iLowerBoundListItem, ::collection::index iUpperBoundListItem);
      void set_lower_bound(::collection::index iLowerBoundItem);
      void set_upper_bound(::collection::index iUpperBoundItem);
      bool has_sub_item(::collection::index iSubItem) const;
      ::collection::index get_lower_bound() const;
      ::collection::index get_upper_bound() const;
      item_range& operator =(const item_range& itemrange);
      bool has_item(::collection::index iItem) const;
      void get_item_indexes(index_array& ia) const;

   };


   class CLASS_DECL_AURA range
   {
   public:


      array < item_range >    m_itemrangea;


      range(const range& range);
      range();


      range& operator = (const range& range);


      bool has_item(::collection::index iItem) const;
      bool has_sub_item(::collection::index iItem, ::collection::index iSubItem) const;
      bool erase_item(::collection::index iItem);
      bool OnRemoveItem(::collection::index iItem);
      void clear();
      void add_item(const item_range& itemrange);
      item_range& ItemAt(::collection::index iIndex);
      ::collection::index get_current_item();
      ::collection::count get_item_count() const;
      ::collection::count get_items(index_array& ia) const;
      ::collection::count get_item_indexes(index_array& ia) const;

   };



} // namespace user




