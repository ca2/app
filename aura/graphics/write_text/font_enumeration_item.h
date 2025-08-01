//
//  font_enumeration_item.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 01/03/22.
//  23:02
///
#pragma once


#include "font.h"
#include "acme/prototype/collection/int_map.h"
////#include "acme/prototype/prototype/object.h"


namespace write_text
{


   class CLASS_DECL_AURA font_enumeration_item :
      virtual public object
   {
   public:

      // 100 Ultra Light
      // 101 Ultra Light Italic
      // 200 Light
      // 201 Light Italic
      int_to_string              m_mapFileName;
      string                     m_strName;
      string                     m_strBranch;
   #ifdef WINDOWS
      wstring                    m_wstrName;
   #endif
      enum_character_set_array   m_echaracterseta;
      


      font_enumeration_item();
   #ifdef WINDOWS
      font_enumeration_item(const ::wide_character* pwideszName);
   #endif
      font_enumeration_item(const ::scoped_string & scopedstrName);
      font_enumeration_item(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrName);
      font_enumeration_item(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrBranch, const ::scoped_string & scopedstrName);
      ~font_enumeration_item() override;


      bool operator < (const font_enumeration_item & item) const
      {

         return m_strName.order(item.m_strName) < 0;

      }

      bool operator == (const font_enumeration_item& item) const
      {

         return //m_strFile == item.m_strFile
             m_strName == item.m_strName;
   //            && m_strName == item.m_strName;
         //                   && m_echaracterset == item.m_echaracterset;

      }

      bool operator != (const font_enumeration_item& item) const { return !this->operator==(item); }

   };


   using enum_item_array = pointer_array < font_enumeration_item >;


} // namespace write_text



