#include "framework.h"
#include "aqua/xml.h"


namespace xml
{


   disp_option::disp_option(entities * pentities)
   {

      m_bNewLine = true;
      m_bReferenceValue = true;
      m_pentities = pentities; // &::get_application(pobject)->get_system()->m_pxml->m_entities;
      m_iTabBase = 0;
      m_chQuote = '"';

   }


} // namespace xml
