#pragma once


////#include "acme/primitive/primitive/object.h"


namespace xml
{


   class node;

   // Parse info.
   class CLASS_DECL_AQUA parse_info :
      virtual public ::object
   {
   public:

      
      bool                 m_bTrimValue;        // [set] do trim when parse?
      bool                 m_bEntityValue;      // [set] do convert from object to entity? ( &lt; -> < )
      ::pointer<entities> m_pentities;         // [set] entity table for entity decode
      char                 m_chEscapeValue;     // [set] escape value (default '\\')
      bool                 m_bForceParse;       // [set] force parse even if xml is not welformed

      string               m_strXml;            // [get] xml source
      bool                 m_bErrorOccur;       // [get] is occurance of error?
      const char *         m_pszErrorPointer;   // [get] error position of xml source
      enum_parse_error     m_eparseerror;       // [get] error code
      string               m_strError;          // [get] error string

      ::pointer<::xml::document>       m_pdocument;

      
      parse_info(entities * pentities);
      
      
   };

   
   CLASS_DECL_AQUA char * LoadOtherNodes( node * node, bool* pbRet, const ::scoped_string & scopedstrXml, parse_info * pi = nullptr);
   

} // namespace xml





