#pragma once



//#include "acme/prototype/collection/array.h"


namespace database
{

   
   class CLASS_DECL_AXIS field_definition_item : 
      virtual public ::particle
   {
   public:

      
      enum enum_type
      {
         
         type_none,
         type_text
            
      };


      string      m_strName;
      int         m_iSize;
      enum_type      m_etype;

      
      field_definition_item();
      field_definition_item(const field_definition_item & item);

      field_definition_item & operator = (const field_definition_item & item);
      //field_definition_item & operator = (const xml::node & node);


      enum_type field_str_to_type(const ::scoped_string & scopedstrType);

      
   };


   class CLASS_DECL_AXIS field_definition : 
      virtual public array < field_definition_item >
   {
   public:

      
   };



} // namespace simpledb





