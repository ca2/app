//
// Created by camilo on 2024-06-05 19:18 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/prototype/prototype/action_context.h"


namespace data
{


   class CLASS_DECL_ACME property_listener :
      virtual public ::particle
   {
   public:


      virtual bool on_property_will_change(property_change & change);
      virtual void on_property_changed(property_change & change);


   };


} // namespace data





