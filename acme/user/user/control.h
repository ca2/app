// Created by camilo on 2024-06-08 00:24 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/data/property_container.h"
#include "acme/prototype/data/property_listener.h"


namespace user
{


   class CLASS_DECL_ACME control :
      virtual public ::data::property_container,
      virtual public ::data::property_listener
   {
   public:


      control();
      ~control() override;


   };


};