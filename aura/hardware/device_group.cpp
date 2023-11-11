// Created by camilo on 2023-11-11 03:34 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "device_group.h"
#include "devices.h"


namespace hardware
{


   device_group::device_group()
   {


   }


   device_group::~device_group()
   {


   }


   void device_group::initialize_device_group(enum_device edevice, devices * pdevices)
   {

      m_edevice = edevice;

      m_pdevices = pdevices;

   }


   void device_group::finalize_device_group()
   {


      
   }


   void device_group::on_device_list_updated()
   {

      m_pdevices->update_device_list(m_edevice);

      for (auto & pdevicelistener : *this)
      {

         pdevicelistener->on_device_nodes_changed();

      }

   }

   void device_group::on_device_plugged()
   {

      m_pdevices->update_device_list(m_edevice);

      for (auto & pdevicelistener : *this)
      {

         pdevicelistener->on_device_plugged(m_edevice);

      }

   }


   void device_group::on_device_unplugged()
   {

      m_pdevices->update_device_list(m_edevice);

      for (auto & pdevicelistener : *this)
      {

         pdevicelistener->on_device_unplugged(m_edevice);

      }

   }


} // namespace hardware


