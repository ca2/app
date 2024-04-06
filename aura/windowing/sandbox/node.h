//
//  node.hpp
//  ios_aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-07 21:50 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "aura/platform/node.h"


namespace sandboxed
{


   class CLASS_DECL_ACME node:
      virtual public ::aura::node
   {
   public:
      
      
      node();
      ~node() override;
      
      
      void root_ones(::file::listing & listing) override;

      
      
   };


} // namespace sandboxed



