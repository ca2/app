// From definition.h by camilo on 2022-09-06 17:19 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/prototype/prototype/matter.h"


namespace database
{



   class CLASS_DECL_AXIS field :
      virtual public ::matter
   {
   public:


      ::collection::index             m_iIndex;
      enum_data_type    m_edatatype;
      string            m_strName;
      string            m_strDisplayMame;
      string            m_strFieldTable;
      bool              m_bReadOnly;
      character_count           m_iLength;
      unsigned long long               m_ulFlag;


      field();

//      virtual ::stream & write(::stream & stream) const override;
//virtual ::stream & read(::stream & stream) override;

   };




} // namespace database



