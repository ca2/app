//
//  toolbar_item.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 03/Oct/22 18:39
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


namespace user
{


   class CLASS_DECL_ACME toolbar_item:
   virtual public ::item
   {
   public:
      
      
      //index                               m_iIndex;
      index                               m_iImage;
      ::image_pointer                     m_pimage;
      //atom                                  m_atom;
      e_toolbar_item_state                m_estate;
      e_toolbar_item_style                m_estyle;
      string                              m_str;
      //::rectangle_i32                              m_rectangle;
      bool                                m_bEnableIfHasCommandHandler;
      ::write_text::font_pointer              m_pfont;
      
      
      toolbar_item()
      ~toolbar_item() override;
      
      
   };


   inline toolbar_item * __toolbar_item(::item * pitem)
   {
      
      return (toolbar_item*) pitem->m_data[0];
      
   }


} // namespace user



