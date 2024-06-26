// Created by camilo on 2024-06-06 20:54 <3ThomasBorregaardSorensen!!
#pragma once




namespace user
{


   class CLASS_DECL_ACME property
   {
   protected:
      ::user::control * m_pusercontrol;
   protected:
      
      property(::user::control * pusercontrol);
      
      void set_data_property(::data::property & propertyTarget, const ::data::property& propertySource);


   public:



   };

}