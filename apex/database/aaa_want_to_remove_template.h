#pragma once

namespace database
{
   typedef CLASS_DECL_APEX array < selection_item, selection_item & > selection_item_array;
   typedef CLASS_DECL_APEX ref_array < client > client_ptra;

   class CLASS_DECL_APEX record :
      public payload_array
   {
   };

   class CLASS_DECL_APEX query_data :
      public array <record, record &>
   {
   };

   class CLASS_DECL_APEX field_definition : 
      virtual public array < field_definition_item >
   {
   public:
      
   };

} // namespace database
