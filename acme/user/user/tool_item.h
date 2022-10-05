//
//  tool_item.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 03/Oct/22 18:39
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once


#include "acme/constant/user/tool_item.h"


namespace user
{


   class CLASS_DECL_ACME tool_item:
      virtual public ::item
   {
   public:
      
      
      index                         m_iImage;
      ::image_pointer               m_pimage;
      e_tool_item_state             m_estate;
      e_tool_item_style             m_estyle;
      string                        m_str;
      bool                          m_bEnableIfHasCommandHandler;
      ::write_text::font_pointer    m_pfont;
      
      
      tool_item();
      ~tool_item() override;
      

      bool is_hidden() const { return m_estate & e_tool_item_state_hidden; }
      bool displayed() const { return !is_hidden(); }

      void hide() { m_estate |= e_tool_item_state_hidden; }

      bool should_wrap() const { return m_estate & e_tool_item_state_wrap; }
      void set_should_wrap(bool bSet = true) { return m_estate.set(e_tool_item_state_wrap, bSet); }

      
      bool is_separator() const { return m_estyle & e_tool_item_style_separator; }

      bool is_custom_control() const { return m_estyle & e_tool_item_style_separator; }

   };


//   inline tool_item * __tool_item(::item * pitem)
//   {
//      
//      return (tool_item*) pitem->m_data[0];
//      
//   }


} // namespace user



