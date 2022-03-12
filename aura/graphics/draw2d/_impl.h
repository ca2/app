//
//  draw2d.inl
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 11/03/18.
//
#pragma once


namespace draw2d
{


   ::aura::system* object::get_system()
   {
      
      return ::is_null(m_psystem) ? dynamic_cast <::aura::system*> (m_psystem) : nullptr; 
   
   }


} // namespace draw2d



