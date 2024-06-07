// Created by camilo on 2024-06-06 20:54 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/data/property_listener.h"

class property_link;


namespace user
{

   class CLASS_DECL_ACME control :
      virtual property_listener
   {
   protected:
      void initialize_property_link(::property_link & propertylinkTarget, const ::property_link & propertylinkSource);
   public:



   };

}