//
// Created by camilo on 8/18/21 06:19 BRT <3TBS_!!
//

#pragma once


namespace user
{


   class CLASS_DECL_AURA interaction_scaler :
      virtual public ::object
   {
   public:


      double                                    m_dScreenScaler;
      double                                    m_dFontScaler;


      interaction_scaler();
      ~interaction_scaler() override;



      virtual void on_display_change(const ::size_i32 & sizeMonitor);
      virtual void on_display_change(::user::interaction * puserinteraction);


      inline double screen_scaler() const {return m_dScreenScaler;}
      inline double font_scaler() const {return m_dFontScaler;}


   };


} // namespace user



