#pragma once

namespace database
{
   typedef CLASS_DECL_AURA array < selection_item, selection_item & > selection_item_array;
   typedef CLASS_DECL_AURA ref_array < client > client_ptra;

   class CLASS_DECL_AURA record :
      public var_array
   {
   };

   class CLASS_DECL_AURA query_data :
      public array <record, record &>
   {
   };

   class CLASS_DECL_AURA field_definition : 
      virtual public array < field_definition_item >
   {
   public:
      
   };

} // namespace database