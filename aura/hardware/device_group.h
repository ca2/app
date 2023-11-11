// Created by camilo on 2023-11-11 03:27 <3ThomasBorregaardSorensen!!
#pragma once


#include "device_listener.h"


namespace hardware
{


   class CLASS_DECL_AURA device_group :
      virtual public device_listener_array
   {
   public:


      enum_device    m_edevice;

      ::pointer < devices >         m_pdevices;


      device_group();
      ~device_group() override;


      virtual void initialize_device_group(enum_device edevice, devices * pdevices);


      virtual void on_device_list_updated();


   };

}