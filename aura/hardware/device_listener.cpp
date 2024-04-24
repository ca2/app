// Created by camilo on 2022-02-20 12:08 <3ThomasBorregaardSorensen!! (Thomas Likes number 5)! I like also this Infinity up!!
// From windows::device_listener by camilo on 2022-05-15 16:36 <3ThomasBorregaardSorenesen!! and Mummi!!
#include "framework.h"
#include "device_listener.h"
#include "devices.h"
#include "aura/platform/system.h"


namespace hardware
{


   device_listener::device_listener()
   {

   }


   device_listener::~device_listener()
   {


   }


   void device_listener::register_device_listener(enum_device edevice)
   {

      auto psystem = system()->m_paurasystem;

      psystem->defer_initialize_hardware_devices();

      auto phardwaredevices = psystem->hardware_devices();

      if (::is_set(phardwaredevices))
      {

         phardwaredevices->register_device_listener(this, edevice);

      }

   }


   void device_listener::unregister_device_listener(enum_device edevice)
   {

      auto psystem = system()->m_paurasystem;

      auto phardwaredevices = psystem->hardware_devices();

      if (::is_set(phardwaredevices))
      {

         phardwaredevices->unregister_device_listener(this, edevice);

      }

   }


   void device_listener::on_device_nodes_changed()
   {

   }


   void device_listener::on_device_plugged(enum_device edevice)
   {

   }


   void device_listener::on_device_unplugged(enum_device edevice)
   {

   }


} // namespace hardware



