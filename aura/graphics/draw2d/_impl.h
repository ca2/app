//
//  draw2d.inl
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 11/03/18.
//
#pragma once


namespace draw2d
{


   ::aura::system* objectacmesystem()
   {
      
      return ::is_null(system()) ? dynamic_cast <::aura::system*> (system()) : nullptr; 
   
   }


} // namespace draw2d



