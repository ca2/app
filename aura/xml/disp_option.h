#pragma once


namespace xml
{

   
   // display optional environment
   class CLASS_DECL_AURA disp_option :
      virtual public ::context_object
   {
   public:
   
      
      bool                 m_bNewLine;          // newline when new tag
      bool                 m_bReferenceValue;   // do convert from entity to context_object ( < -> &lt; )
      char                 m_chQuote;           // val="" (default value quotation mark "
      __pointer(entities)  m_pentities;         // entity table for entity encode
      i32                  m_iTabBase;          // internal usage
      
      
      disp_option(entities * pentities);
      
      
   };
   

   //extern CLASS_DECL_AURA disp_option g_optDefault;


} // namespace xml



