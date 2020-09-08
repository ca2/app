#pragma once

namespace database
{
   typedef CLASS_DECL_AQUA array < selection_item, selection_item & > selection_item_array;
   typedef CLASS_DECL_AQUA ref_array < client > client_ptra;

   class CLASS_DECL_AQUA record :
      public var_array
   {
   };

   class CLASS_DECL_AQUA query_data :
      public array <record, record &>
   {
   };

   class CLASS_DECL_AQUA field_definition : 
      virtual public array < field_definition_item >
   {
   public:
      
   };

} // namespace database