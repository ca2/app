//
// Created by camilo on 31/01/2022 14:38 <3ThomasBorregaardSørensen!!
//
#pragma once


namespace windows
{


   class CLASS_DECL_ACME nano_pen :
      virtual public ::nano_pen,
      virtual public nano_object
   {
   public:


      nano_pen();
      ~nano_pen() override;

      
      void update(::nano_device * pnanodevice) override;


   };


} // namespace windows



