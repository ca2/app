#pragma once


namespace xml
{

   
   class CLASS_DECL_AURA property_set_exchange :
      virtual public exportable,
      virtual public importable,
      virtual public ::object
   {
   public:


      property_set * m_ppropertyset;


      property_set_exchange(::object * pobject);
      virtual ~property_set_exchange();


      void xml_export(class output_tree &);
      void xml_import(class input_tree &);


   };


} // namespace xml




