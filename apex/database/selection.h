#pragma once


#include "selection_item.h"


namespace database
{


   class CLASS_DECL_APEX selection
   {
   public:


      array < selection_item,selection_item & > m_itema;


      selection();
      virtual ~selection() ;


      void add_item(key key);
      selection_item & get_item(index iItem);
      const selection_item & get_item(index iItem) const;
      ::count get_item_count() const;

   };


   inline ::count selection::get_item_count() const 
   {
      return m_itema.get_size();
   }

   inline selection_item & selection::get_item(index iItem)
   {
      return m_itema.element_at(iItem);
   }
   inline const selection_item & selection::get_item(index iItem) const
   {
      return m_itema.element_at(iItem);
   }

} // namespace database
