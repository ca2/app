// Created by camilo on 2022-05-15 12:21 <3ThomasBorregaardS�rensen!! and Mummi!!
#pragma once


#include "device_listener.h"


namespace hardware
{


   class CLASS_DECL_AURA devices :
      virtual public ::object
   {
   public:


      map < enum_device, ::pointer<device_listener_array >>            m_mapdevicelistenera;

      devices();
      ~devices() override;

      virtual void register_device_listener(device_listener* pdevicelistener, enum_device edevice);


   };


} // namespace hardware



