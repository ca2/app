// Created by camilo on 2022-02-20 12:22 <3ThomasBorregaardSørensen!!
// From windowing_win32::devices by camilo on 2022-05-15 17:08 <3ThomasBorregaardSørensen!! and Mummi!!
#include "framework.h"
#include "devices.h"


namespace hardware
{


   devices::devices()
   {

   }


   devices::~devices()
   {

   }

   
   void devices::register_device_listener(device_listener* pdevicelistener, enum_device edevice)
   {

      __defer_construct_new(m_mapdevicelistenera[edevice]);

      m_mapdevicelistenera[edevice]->add(pdevicelistener);

   }


} // namespace hardware



