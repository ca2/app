#include "framework.h"
#include "disp_option.h"
#include "entity.h"


namespace xml
{


   disp_option::disp_option(entities * pentities)
   {

      m_bNewLine = true;
      m_bReferenceValue = true;
      m_pentities = pentities; // &::get_app(pparticle)->get_system()->m_pxml->m_entities;
      m_iTabBase = 0;
      m_chQuote = '"';

   }


} // namespace xml
