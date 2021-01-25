#pragma once


namespace xml
{

   
   class var_exchange :
      public exportable,
      public importable,
      virtual public ::object
   {
   public:
   

      ::payload * m_pvar;


      var_exchange(::layered * pobjectContext);
      virtual ~var_exchange();


      virtual void xml_export(class output_tree &) const override;
      virtual void xml_import(class input_tree &) override;


   };

   
} // namespace xml




