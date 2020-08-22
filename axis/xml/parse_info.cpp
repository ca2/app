#include "framework.h"
#include "axis/xml/_.h"


namespace xml
{


   parse_info::parse_info(entities * pentities)
   {

      m_bTrimValue      = false;
      m_bEntityValue    = true;
      m_bForceParse     = false;
      m_pentities       = pentities;

      m_bErrorOccur     = false;
      m_pszErrorPointer = nullptr;
      m_eparseerror     = parse_error_welformed;
      m_chEscapeValue   = '\\';
   }


} // namespace xml



