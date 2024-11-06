//
// Created by camilo on 8/18/21 06:19 BRT <3TBS_!!
//
#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "aura/graphics/draw2d/host.h"


namespace user
{


   class CLASS_DECL_AURA interaction_scaler :
      virtual public ::draw2d::host
   {
   public:


      interaction_scaler();
      ~interaction_scaler() override;


      virtual void on_display_change(const ::int_size & sizeMonitor);
      virtual void on_display_change(::user::interaction * puserinteraction);


   };


} // namespace user



