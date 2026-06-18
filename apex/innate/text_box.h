
//
//  text_box.h
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 04/04/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//

#pragma once

#include "apex/innate/window.h"


namespace innate
{


   class CLASS_DECL_APEX text_box :
      public innate::window
   {
   public:
      
      
      ::pointer < ::innate_ui::text_box > m_pinnatetextbox;
      
      text_box();
      ~text_box() override;
      
   };


} // namespace public


