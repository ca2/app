#pragma once


#include "selection_item.h"
//#include "acme/prototype/collection/array.h"

//
//namespace database
//{
//
//
//   class CLASS_DECL_APEX selection
//   {
//   public:
//
//
//      array < selection_item, const selection_item & > m_itema;
//
//
//      selection();
//      virtual ~selection();
//
//
//      void add_item(const ::scoped_string & strDataKey);
//      selection_item & get_item(::collection::index iItem);
//      const selection_item & get_item(::collection::index iItem) const;
//      ::collection::count get_item_count() const;
//
//   };
//
//
//   inline ::collection::count selection::get_item_count() const
//   {
//      return m_itema.get_size();
//   }
//
//   inline selection_item & selection::get_item(::collection::index iItem)
//   {
//      return m_itema.element_at(iItem);
//   }
//   inline const selection_item & selection::get_item(::collection::index iItem) const
//   {
//      return m_itema.element_at(iItem);
//   }
//
//} // namespace database
