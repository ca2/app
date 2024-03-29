// Created by camilo on 2022-02-20 12:22 <3ThomasBorregaardSoerensen!!
// From windowing_win32::devices by camilo on 2022-05-15 17:08 <3ThomasBorregaardSoerensen!! and Mummi!!
#include "framework.h"
#include "device_group.h"
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

      auto & pdevicegroup = m_mapdevicegroup[edevice];

      __defer_construct(pdevicegroup);

      pdevicegroup->add(pdevicelistener);

      pdevicegroup->initialize_device_group(edevice, this);

   }


   void devices::unregister_device_listener(device_listener * pdevicelistener, enum_device edevice)
   {

      auto & pdevicegroup = m_mapdevicegroup[edevice];

      if (!pdevicegroup)
      {

         return;

      }

      pdevicegroup->initialize_device_group(edevice, this);

      pdevicegroup->erase(pdevicelistener);

   }

   //void devices::on_register_device_listener(::hardware::enum_device edevice)
   //{


   //}


   void devices::update_device_list(enum_device edevice)
   {


   }

   
   void devices::erase_device_group(device_group * pdevicegroup)
   {

      m_mapdevicegroup.erase_item(pdevicegroup->m_edevice);

      if (m_mapdevicegroup.is_empty())
      {

      }

   }

} // namespace hardware



