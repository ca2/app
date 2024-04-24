#pragma once


#include "aura/primitive/collection/string_to_string_map.h"


namespace aura
{


   class CLASS_DECL_AURA application_heap
   {
   public:


      string_to_ptr                                   m_appmap;
      ::file::path_array                                   m_straMatterLocator;
      string_table                                    m_stringtable;
      string_table                                    m_stringtableStd;
      map < atom, atom, string, string >                  m_stringmap;


      application_heap(::particle * pparticle)
      {

      }


   };



} // namespace aura



