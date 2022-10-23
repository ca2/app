// Created by camilo on 2022-10-09 20:55 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/parallelization/mutex.h"
#include "acme/primitive/collection/map.h"


class CLASS_DECL_ACME subsystem :
   virtual public ::element
{
public:
   
   
   ::mutex                                                           m_mutexLibrary4;
   ::acme::library_map                                               m_mapLibrary4;
   

   subsystem();
   ~subsystem();


   static subsystem * get();


};
