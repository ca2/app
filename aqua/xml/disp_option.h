#pragma once


////#include "acme/prototype/prototype/object.h"


namespace xml
{

   
   // display optional environment
   class CLASS_DECL_AQUA disp_option :
      virtual public ::object
   {
   public:
   
      
      bool                 m_bNewLine;          // newline when ___new tag
      bool                 m_bReferenceValue;   // do convert from entity to object ( < -> &lt; )
      char                 m_chQuote;           // val="" (default value quotation mark "
      ::pointer<entities> m_pentities;         // entity table for entity encode
      int                  m_iTabBase;          // internal usage
      
      
      disp_option(entities * pentities);
      
      
   };
   

   //extern CLASS_DECL_AQUA disp_option g_optDefault;


} // namespace xml



