// Created by camilo on 2022-03-25 11:47 <3ThomasBorregaardS�rensen!!
#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA host :
      virtual public object
   {
   public:


      host();
      ~host() override;


      virtual double point_dpi(double d);

      virtual double dpiy(double d);


   };


} // namespace draw2d



