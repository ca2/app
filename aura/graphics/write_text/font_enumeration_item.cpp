//
//  font_enumeration_item.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 04/03/22.
//  00:43
#include "framework.h"
#include "font.h"
#include "font_enumeration_item.h"


namespace write_text
{


   font_enumeration_item::font_enumeration_item()
   {


   }


   font_enumeration_item::font_enumeration_item(const ::scoped_string & scopedstrName) :
      m_strName(scopedstrName)
   {

      //m_mapFileName[0] = strName;

#ifdef WINDOWS

      m_wstrName = scopedstrName;

#endif

   }


#ifdef WINDOWS


   font_enumeration_item::font_enumeration_item(const ::wide_character * pwideszName) :
      m_wstrName(pwideszName)
   {

//      string strName = m_wstrName;

//      m_mapFileName[0] = strName;
      m_strName = pwideszName;

   }


#endif


   font_enumeration_item::font_enumeration_item(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrName) :
      m_strName(scopedstrName)
   {

      m_mapFileName[0] = scopedstrFile;

#ifdef WINDOWS

      m_wstrName = scopedstrName;

#endif

   }


   font_enumeration_item::font_enumeration_item(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrBranch, const ::scoped_string & scopedstrName) :
      m_strName(scopedstrName)
   {

      m_mapFileName[0] = scopedstrFile;

      m_strBranch = scopedstrBranch;

#ifdef WINDOWS

      m_wstrName = scopedstrName;

#endif

   }


   font_enumeration_item::~font_enumeration_item()
   {

   }


} // namespace write_text



