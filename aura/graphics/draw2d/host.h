// Created by camilo on 2022-03-25 11:47 <3ThomasBorregaardSørensen!!
#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA host :
      virtual public object
   {
   public:


      double                                    m_dScreenScaler;
      double                                    m_dFontScaler;


      host();
      ~host() override;


      inline double screen_scaler() const {return m_dScreenScaler;}
      inline double font_scaler() const {return m_dFontScaler;}


      virtual double point_dpi(double d);

      virtual double dpiy(double d);


   };


} // namespace draw2d



