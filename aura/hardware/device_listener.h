// Created by camilo on 2022-02-20 12:05 <3ThomasBorregaardS�rensen!! (Thomas Likes number 5)!
// From windows::device_listener by camilo on 2022-05-15 16:29 <3ThomasBorregaardSorenesen!! and Mummi!!
#pragma once


//#include "acme/primitive/primitive/matter.h"
#include "aura/constant/hardware.h"


namespace hardware
{


   class CLASS_DECL_AURA device_listener :
      virtual public ::matter
   {
   public:

      
      device_listener();
      ~device_listener() override;


      virtual void register_device_listener(enum_device edevice);


      virtual void on_device_plugged(enum_device edevice);

      virtual void on_device_unplugged(enum_device edevice);


   };


   using device_listener_array = pointer_array < device_listener >;


} //namespace windows


