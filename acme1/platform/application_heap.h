#pragma once


#include "acme/primitive/collection/string_to_string_map.h"


namespace acme
{


   class CLASS_DECL_ACME application_heap
   {
   public:


      string_to_ptr                                   m_appmap;
      ::file::patha                                   m_straMatterLocator;
      string_table                                    m_stringtable;
      string_table                                    m_stringtableStd;
      map < id, id, string, string >                  m_stringmap;


      application_heap(::generic * pobject)
      {

      }


   };



} // namespace acme



