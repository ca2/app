// Created by camilo on 2022-03-25 11:47 <3ThomasBorregaardSorensen!!
#pragma once


////#include "acme/prototype/prototype/object.h"


namespace draw2d
{


   class CLASS_DECL_AURA host :
      virtual public ::object
   {
   public:


      ::f64                                    m_dScreenScaler;
      ::f64                                    m_dFontScaler;


      host();
      ~host() override;


      inline ::f64 screen_scaler() const {return m_dScreenScaler;}
      inline ::f64 font_scaler() const {return m_dFontScaler;}


      virtual ::f64 point_dpi(::f64 d);

      virtual ::f64 dpiy(::f64 d);


   };


} // namespace draw2d



