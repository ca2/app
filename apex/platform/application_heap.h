#pragma once


#include "apex/primitive/collection/string_to_string_map.h"


namespace apex
{


   class CLASS_DECL_APEX application_heap
   {
   public:


      string_to_ptr                                   m_appmap;
      ::file::patha                                   m_straMatterLocator;
      string_table                                    m_stringtable;
      string_table                                    m_stringtableStd;
      map < id, id, string, string >                  m_stringmap;


      application_heap(::layered * pobjectContext)
      {

      }


   };



} // namespace apex



