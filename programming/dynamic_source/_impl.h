// added script_interface::is_debug inlining by 
// camilo on 2025-10-26 22:53 <3ThomasBorregaardSørensen!!
#pragma once


//namespace dynamic_source
//{
//
//
//
//
//} // namespace dynamic_source
//


#include "programming/dynamic_source/script_main.h"


namespace dynamic_source
{


   inline bool script_interface::is_debug() const
   {

      return m_pscriptmain1 && m_pscriptmain1->m_iDebug > 0;

   }


} // namespace dynamic_source




