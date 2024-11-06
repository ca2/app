//
//  _dynamic_library.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 
//  2024-06-14 15:50 <3ThomasBorregaardSorensen!!
//  Copyright © 2024 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "dynamic_library.h"


IMPLEMENT_FACTORY(nano_dynamic_library)
{

   pfactory->add_factory_item<::macos::operating_system::dynamic_library, ::operating_system::dynamic_library>();

}



