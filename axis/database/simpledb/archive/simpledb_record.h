#pragma once


namespace simpledb
{


   class CLASS_DECL_CORE record_row :
      virtual public ::object
   {
   public:


      table *     m_ptable;
      string_array     m_straFields;
      ::payload         m_var;


      virtual void io(stream & stream);


   };


} // namespace simpledb



