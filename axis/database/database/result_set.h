// From definition.h by camilo on 2022-09-06 17:21 <3ThomasBorregaardSorensen!!
#pragma once


namespace database
{


   class CLASS_DECL_AXIS result_set :
      virtual public ::object
   {
   public:


      
      __pointer(field_array)     m_pfielda;
      __pointer(row_array)       m_prowa;

      ::count                    m_iMaxRowCount;
      ::count                    m_iMaxColumnCount;


      result_set();


      virtual ::stream & write(::stream & stream) const override;
virtual ::stream & read(::stream & stream) override;


   };


} // namespace database



