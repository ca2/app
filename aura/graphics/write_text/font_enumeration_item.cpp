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


   font_enumeration_item::font_enumeration_item(const ::string & strName) :
      m_strName(strName)
   {

      //m_mapFileName[0] = strName;

#ifdef WINDOWS

      m_wstrName = strName;

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


   font_enumeration_item::font_enumeration_item(const ::string & strFile, const ::string & strName) :
      m_strName(strName)
   {

      m_mapFileName[0] = strFile;

#ifdef WINDOWS

      m_wstrName = strName;

#endif

   }


   font_enumeration_item::font_enumeration_item(const ::string & strFile, const ::string & strBranch, const ::string & strName) :
      m_strName(strName)
   {

      m_mapFileName[0] = strFile;

      m_strBranch = strBranch;

#ifdef WINDOWS

      m_wstrName = strName;

#endif

   }


   font_enumeration_item::~font_enumeration_item()
   {

   }


} // namespace write_text



