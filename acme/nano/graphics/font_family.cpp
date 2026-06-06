//
//  font_family.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 05/06/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  19:32 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#include "framework.h"
#include "font_family.h"
#include "acme/platform/node.h"


namespace nano
{


   namespace graphics
   {
   
   
      font_family::font_family()
      {
      
         m_efont = e_font_none;
            
      }
      
   
      font_family::~font_family()
      {
         
      }
         
         
      void font_family::create_font_family(enum_font efont)
      {
         
         m_efont = efont;
         
         m_strFamilyName.clear();
         
      }
   
   
      void font_family::create_font_family_with_name(const ::scoped_string & scopedstrFamilyName)
      {
      
         m_efont = e_font_with_family_name;
         
         m_strFamilyName = scopedstrFamilyName;
         
      }
   
   
      ::string font_family::get_font_family_name()
      {
         
         ::string strFontFamilyName;

         if(m_efont == e_font_with_family_name)
         {
            
            strFontFamilyName = m_strFamilyName;
            
         }
         else
         {
            
            strFontFamilyName = node()->font_name(m_efont);
            
         }
         
         return strFontFamilyName;
         
      }
   
   
   
   } // namespace graphics


} // namespace nanoe



