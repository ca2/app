#pragma once


#include "aqua/primitive/collection/string_to_string_map.h"


namespace aqua
{


   class CLASS_DECL_AQUA application_heap
   {
   public:


      string_to_ptr                                   m_appmap;
      ::file::patha                                   m_straMatterLocator;
      string_table                                    m_stringtable;
      string_table                                    m_stringtableStd;
      map < id, id, string, string >                  m_stringmap;


      application_heap(::object * pobject)
      {

      }


   };



} // namespace aqua



