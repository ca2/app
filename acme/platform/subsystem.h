// Created by camilo on 2022-10-09 20:55 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/parallelization/mutex.h"
#include "acme/primitive/collection/string_map.h"
#include "acme/primitive/primitive/element.h"


namespace acme
{


   using library_map = string_map < ::pointer < ::acme::library > >;


} // namespace acme


class CLASS_DECL_ACME subsystem :
   virtual public ::particle
{
public:


   ::critical_section               m_criticalsection;
   ::acme::library_map              m_mapLibrary;
   

   subsystem();
   ~subsystem();


   static subsystem * get();


};
