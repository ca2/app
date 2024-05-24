#pragma once


#include "single_lock.h"
////#include "acid/primitive/primitive/matter.h"


class CLASS_DECL_ACID synchronous_lock :
   public single_lock
{
public:


   explicit synchronous_lock(particle * pparticle) :
      single_lock(pparticle, true)
   {


   }



};


class CLASS_DECL_ACID _synchronous_lock :
   public _single_lock
{
public:


   explicit _synchronous_lock(::particle * pparticle) :
      _single_lock(pparticle, true)
   {


   }


};



