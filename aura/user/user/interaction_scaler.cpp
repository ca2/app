//
// Created by camilo on 8/18/21. 06:19 BRT <3TBS_!!
//
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/user/_user.h"
#endif


namespace user
{


   interaction_scaler::interaction_scaler()
   {

      m_dScreenScaler = 1.0;
      m_dFontScaler = 1.0;

   }


   interaction_scaler::~interaction_scaler()
   {


   }


   void interaction_scaler::on_display_change(const ::size_i32 & size)
   {

      double dW = (double) size.cx / 1920.0;

      double dH = (double) size.cy / 1080.0;

      double dScreenScaler = minimum(dW, dH);

      m_dScreenScaler = dScreenScaler;

      m_dFontScaler = dScreenScaler;

   }


   void interaction_scaler::on_display_change(::user::interaction * puserinteraction)
   {

      ::rectangle_i32 rectangleMonitor;

      puserinteraction->best_monitor(&rectangleMonitor);

      on_display_change(rectangleMonitor.size());

   }


} // namespace user



