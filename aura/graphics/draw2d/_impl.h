//
//  draw2d.inl
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 11/03/18.
//
#pragma once


namespace draw2d
{


   ::aura::system* object::get_system()
   {
      
      return ::is_null(acmesystem()) ? dynamic_cast <::aura::system*> (acmesystem()) : nullptr; 
   
   }


} // namespace draw2d



