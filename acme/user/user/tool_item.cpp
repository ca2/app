//
//  tool_item.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 03/Oct/22 18:40
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#include "framework.h"
#include "tool_item.h"


namespace user
{


   tool_item::tool_item()
   {
      
      m_ptoolitem                   = this;
      m_eitem                       = e_item_tool;
      m_eelement                    = e_element_item;
      m_iImage                      = -1;
      m_estate                      = e_tool_item_state_none;
      m_estyle                      = e_tool_item_style_none;
      m_bEnableIfHasCommandHandler  = true;
      
   }


   tool_item::~tool_item()
   {
      
      
   }


   bool tool_item::is_hidden() const
   {
      
      return m_estate & e_tool_item_state_hidden; 
   
   }


   bool tool_item::displayed() const
   { 
      
      return !is_hidden(); 
   
   }


   void tool_item::hide() 
   {
      
      m_estate |= e_tool_item_state_hidden; 
   
   }


   bool tool_item::should_wrap() const 
   {
      
      return m_estate & e_tool_item_state_wrap; 
   
   }


   void tool_item::set_should_wrap(bool bSet)
   {
      
      return m_estate.set(e_tool_item_state_wrap, bSet); 
   
   }


   bool tool_item::is_separator() const 
   {
      
      return m_estyle & e_tool_item_style_separator; 
   
   }


   bool tool_item::is_custom_control() const 
   {
      
      return m_estyle & e_tool_item_style_separator; 
   
   }


} // namespace user



