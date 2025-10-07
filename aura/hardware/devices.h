// Created by camilo on 2022-05-15 12:21 <3ThomasBorregaardSorensen!! and Mummi!!
#pragma once


////#include "acme/prototype/prototype/object.h"
#include "device_listener.h"


namespace hardware
{


   class device_group;


   class CLASS_DECL_AURA devices :
      virtual public ::object
   {
   public:


      map_base < enum_device, ::pointer< device_group > >  m_mapdevicegroup;

      devices();
      ~devices() override;

      virtual void register_device_listener(device_listener* pdevicelistener, enum_device edevice);
      virtual void unregister_device_listener(device_listener * pdevicelistener, enum_device edevice);


      virtual void erase_device_group(device_group * pdevicegroup);
      //virtual void on_register_device_listener(enum_device edevice);


      virtual void update_device_list(enum_device edevice);


   };


} // namespace hardware



