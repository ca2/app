//
//  font_family.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 05/06/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  19:32 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#pragma once


namespace nano
{


   namespace graphics
   {
   
   
      class CLASS_DECL_ACME font_family :
         virtual public ::particle
      {
      public:

         
         enum_font      m_efont;
         string         m_strFamilyName;

         
         font_family();
         ~font_family();
         
         virtual void create_font_family(enum_font efont);
         virtual void create_font_family_with_name(const ::scoped_string & scopedstr);
         
         
         virtual ::string get_font_family_name();
         
      
      };
   
   
   } // namespace graphics


} // namespace nanoe



