#pragma once


//#include "acme/primitive/collection/array.h"


namespace user
{


   class range;


   class CLASS_DECL_AURA list_item_range
   {
   public:


      ::raw::index      m_iLowerBound;
      ::raw::index      m_iUpperBound;


      void set(::raw::index iLowerBoundListItem, ::raw::index iUpperBoundListItem);



   };


   class CLASS_DECL_AURA sub_item_range
   {
   public:

      ::raw::index                m_iLowerBound;
      ::raw::index                m_iUpperBound;
      list_item_range      m_listitemrange;


      sub_item_range();
      sub_item_range(const sub_item_range& subitemrange);

      void set(::raw::index iLowerBoundSubItem, ::raw::index iUpperBoundSubItem, ::raw::index iLowerBoundListItem, ::raw::index iUpperBoundListItem);

      bool has_sub_item(::raw::index iSubItem) const;

      sub_item_range& operator =(const sub_item_range& subitemrange);

   };


   class CLASS_DECL_AURA item_range
   {
   public:


      ::raw::index             m_iLowerBound;
      ::raw::index             m_iUpperBound;
      sub_item_range    m_subitemrange;


      item_range();
      item_range(const item_range& itemrange);


      void offset(::raw::index iOffset);
      void set(::raw::index iLowerBoundItem, ::raw::index iUpperBoundItem, ::raw::index iLowerBoundSubItem, ::raw::index iUpperBoundSubItem, ::raw::index iLowerBoundListItem, ::raw::index iUpperBoundListItem);
      void set_lower_bound(::raw::index iLowerBoundItem);
      void set_upper_bound(::raw::index iUpperBoundItem);
      bool has_sub_item(::raw::index iSubItem) const;
      ::raw::index get_lower_bound() const;
      ::raw::index get_upper_bound() const;
      item_range& operator =(const item_range& itemrange);
      bool has_item(::raw::index iItem) const;
      void get_item_indexes(index_array& ia) const;

   };


   class CLASS_DECL_AURA range
   {
   public:


      array < item_range >    m_itemrangea;


      range(const range& range);
      range();


      range& operator = (const range& range);


      bool has_item(::raw::index iItem) const;
      bool has_sub_item(::raw::index iItem, ::raw::index iSubItem) const;
      bool erase_item(::raw::index iItem);
      bool OnRemoveItem(::raw::index iItem);
      void clear();
      void add_item(const item_range& itemrange);
      item_range& ItemAt(::raw::index iIndex);
      ::raw::index get_current_item();
      ::raw::count get_item_count() const;
      ::raw::count get_items(index_array& ia) const;
      ::raw::count get_item_indexes(index_array& ia) const;

   };



} // namespace user




